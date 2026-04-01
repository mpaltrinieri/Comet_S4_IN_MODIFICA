//----------------------------------------------------------------------------
// TITOLO      : caricaconfmac.c
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Gestione caricamento variabili da configurazione macchina
//----------------------------------------------------------------------------

#include "all.inc"
#include "caricaconfmac.h"


// Tipi di token disponibili
typedef enum {
    RET_TOKEN,
    SKIP_COMMENT_TOKEN,
    SKIP_WORD_TOKEN,
    A_ASSIGN_TOKEN,
    D_A_ASSIGN_TOKEN,
    BL_A_ASSIGN_TOKEN,
    BH_A_ASSIGN_TOKEN,
    F_A_ASSIGN_TOKEN,
    R_ASSIGN_TOKEN, 
    CANC_ASSIGN_TOKEN,
    T_ASSIGN_TOKEN,
    TS_ASSIGN_TOKEN,
    TSD_ASSIGN_TOKEN,
} tokenTypeEnum;

// Struttura che contiene i pattern da cercare
typedef struct {
    tokenTypeEnum type;
    char *str;
} patternStruct;


//----------------------------------------------------------------------------
// FUNZIONE:    parseConfmac
// DESCRIZIONE: Cerca il token RET ignorandone il case nella stringa passata, 
//              quindi legge una serie d'assegnazioni e valorizza le variabili
//              PLC corrispondenti. Ignora linee vuote ed accetta la presenza 
//              di commenti.
// INPUT:       str - stringa di cui effettuare il parsing formattato secondo
//                    lo schema {<variabile><posizione> = <valore>}*. Si possono
//                    inserire commenti iniziandoli con { e terminandoli con } 
//                    o CONFMAC_SEPARATOR. Inoltre è possibile inserire più
//                    assegnazioni sulla medesima riga.
// OUTPUT:      =0 in caso di successo ed alla fine del parsing.
//              >0 in caso di parsing in corso e richiesta ulteriori dati.
//              <0 in caso d'errore irreversibile. Gli errori di parsing 
//                 sono considerati tali se CONFMAC_ERRORONPARSE è vero.
//              CONFMAC_ERROR_WORD contiene il codice.
// NOTE:        La funzione, dopo aver trovato il RET, modifica str inserendo 
//              al termine di ogni record (identificato da CONFMAC_SEPARATOR) 
//              il carattere '\0'.
//----------------------------------------------------------------------------
RTPLC_STATUS parseConfmac(char *str, BOOL reset)
{
	static RTPLC_STATUS status;
    char *c = str;
	FB_ENTER();

	if (reset) {
		FB_RESET();

#ifdef TIMERSSUPPL_INC_INCLUDED
        memset(TSuppl, 0, sizeof(TSuppl));
        memset(TSimu, 0, sizeof(TSimu));
#endif

		status = 0;

		FB_EXIT(FB_EXIT_SUCCESS);
	}

	switch (status) {
		case 0:
			NEXT_STATUS(status, "");

		case 1:
			if (*c == '\0') // File vuoto
				FB_EXIT(FB_EXIT_SUCCESS);

			{ // Cerco RET (ignora il case), salto i commenti e le stringhe non riconosciute
				const patternStruct pattern[] = {
					{ SKIP_COMMENT_TOKEN, " {%*1[}\r\n]%n %n" },			// Commento vuoto
					{ SKIP_COMMENT_TOKEN, " {%*[^}\r\n]%*1[}\r\n]%n %n" },	// Commento
					{ SKIP_COMMENT_TOKEN, " {%*[^}\r\n]%n %n" },            // Commento a fine buffer
					{ SKIP_WORD_TOKEN,    " %*1[Rr]%*1[Ee]%*1[Tt]%*[^{\t\v\r\n ]%n %n" }, // RET non seguito da spazio o commento
					{ RET_TOKEN,          " %*1[Rr]%*1[Ee]%*1[Tt]%n{" },	// RET seguito da commento, spazio o a fine file
					{ SKIP_WORD_TOKEN,    " %*[^{\r\n\t\v ]%n %n" }			// Parola
				};

				int i;
				do {
					int offset = 0;

					// Analisi in sequenza di tutti i pattern accettati
					for(i = 0; i < ARRAY_SIZE(pattern); i++) {
						if (sscanf(c, pattern[i].str, &offset, &offset) == EOF) { 
							ERROR_STATUS(status, "Errore durante la valutazione dei token");
							FB_EXIT(status);
						}
						if (offset != 0) break;
					}

					// Valutazione azione ed argomenti
					switch (pattern[i].type) {
						case RET_TOKEN:
						case SKIP_WORD_TOKEN:
						case SKIP_COMMENT_TOKEN:
							c += offset;
							break;
						default: // Errore irreversibile di parsing
							ERROR_STATUS(status, "Errore di sintassi nel file");
							FB_EXIT(status);
					}
				} while ((*c != '\0') && (pattern[i].type != RET_TOKEN));

				if (pattern[i].type == RET_TOKEN)
					NEXT_STATUS(status, "Trovato RET");
				else
					break;
			}

		case 2:
			if (*c == '\0') // Raggiunta fine del file
				FB_EXIT(FB_EXIT_SUCCESS);

			{ // Cerco i pattern d'assegnazione, salto i commenti e le stringhe non riconosciute
				const patternStruct pattern[] = {
					{ SKIP_COMMENT_TOKEN, " {%n%*[^}]%n}%n %n" },                     // Commento
					{ A_ASSIGN_TOKEN,     " %*1[Aa]%u = %li%n %n" },                // Variabile A tipo word
					{ D_A_ASSIGN_TOKEN,   " %*1[Dd]_%*1[Aa]%u = %li%n %n" },        // Variabile A tipo double word
					{ BL_A_ASSIGN_TOKEN,  " %*1[Bb]%*1[Ll]_%*1[Aa]%u = %li%n %n" }, // Variabile A tipo byte basso
					{ BH_A_ASSIGN_TOKEN,  " %*1[Bb]%*1[Hh]_%*1[Aa]%u = %li%n %n" }, // Variabile A tipo byte alto
					{ F_A_ASSIGN_TOKEN,   " %*1[Ff]_%*1[Aa]%u = %g%n %n" },         // Variabile A tipo float
					{ R_ASSIGN_TOKEN,     " %*1[Rr]%u = %g%n %n" },                 // Variabile R
					{ CANC_ASSIGN_TOKEN,  " #%u = %g%n %n" },                       // Variabile cancelletto
					{ T_ASSIGN_TOKEN,     " %*1[Tt]%u = %g%n %n" },                 // Variabile Timer standard
                    { TS_ASSIGN_TOKEN,    " %*1[Tt]%*1[Ss]%u = %g%n %n" },          // Variabile Timer supplementare
                    { TSD_ASSIGN_TOKEN,   " %*1[Tt]%*1[Ss]%*1[Dd]%u = %g%n %n" },   // Variabile Timer simulazione
					{ SKIP_WORD_TOKEN,    " %*[^{\t\v ]%n %n" }                     // Token sconosciuto
				};

				struct {
					double *r;
					double *c;
					DATI *a;
				} var = { 
					(double*)GetDatiCnc(ARERRE), 
					(double*)GetDatiCnc(ARECANC), 
					(DATI*)GetDatiPlc(DATVOL) 
				};


				// Ricerca pattern
				c = strtok(c, CONFMAC_SEPARATOR);
				while (c != NULL) {
					int i = 0;
					union { int offset; unsigned int u; } v1 = {0};
					union { int offset; long int li; double g; } v2 = {0};
					union { int offset; } v3 = {0};

					// Salta linee vuote / terminate
					while (isspace((int)*c)) c++;
					if (*c == '\0') {
						c = strtok(NULL, CONFMAC_SEPARATOR);
						continue;
					}

					// Analisi in sequenza di tutti i pattern accettati
					for(; i < ARRAY_SIZE(pattern); i++) {
						if (sscanf(c, pattern[i].str, &v1, &v2, &v3, &v3) == EOF) { 
							ERROR_STATUS(status, "Errore durante la valutazione dei token");
							FB_EXIT(status); 
						}
						if ((v1.offset != 0) || (v2.offset != 0) || (v3.offset != 0)) break;
					}

					// Valutazione azione ed argomenti
					switch (pattern[i].type) {
						case SKIP_WORD_TOKEN:
							if (CONFMAC_ERRORONPARSE) {
								ERROR_STATUS(status, "Errore di sintassi");
								FB_EXIT(status); // Se configurato emetto errore
							}
						case SKIP_COMMENT_TOKEN:
							c += max(max(v1.offset, v2.offset), v3.offset); // Salto la parola / commento
							break;
						case A_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u/2, 0, ARRAY_SIZE(p_dplc_v3->aa)-1)) {
							if ((v1.u%2) == 0)
								var.a[v1.u/2].word.l.word = (short int)v2.li;
							else
								var.a[v1.u/2].word.h.word = (short int)v2.li;
                                LOG_MSG2(2, "A%u=%d", v1.u, v2.li);
                            } else {
                                LOG_MSG2(2, "A%u=%d oltre range array", v1.u, v2.li);
                            }
							c += v3.offset;
							break;
						case D_A_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u/2, 0, ARRAY_SIZE(p_dplc_v3->aa)-1)) {
                                var.a[v1.u/2].dword = (long int)v2.li;
                                LOG_MSG2(2, "D_A%u=%d", v1.u, v2.li);
                            } else {
                                LOG_MSG2(2, "D_A%u=%d oltre range array", v1.u, v2.li);
                            }
							c += v3.offset;
							break;
						case BL_A_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u/2, 0, ARRAY_SIZE(p_dplc_v3->aa)-1)) {
							if ((v1.u%2) == 0)
								var.a[v1.u/2].word.l.byte.l = (signed char)v2.li;
							else
								var.a[v1.u/2].word.h.byte.l = (signed char)v2.li;
                                LOG_MSG2(2, "BL_A%u=%d", v1.u, v2.li);
                            } else {
                                LOG_MSG2(2, "BL_A%u=%d oltre range array", v1.u, v2.li);
                            }
							c += v3.offset;
							break;
						case BH_A_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u/2, 0, ARRAY_SIZE(p_dplc_v3->aa)-1)) {
							if ((v1.u%2) == 0)
								var.a[v1.u/2].word.l.byte.h = (signed char)v2.li;
							else
								var.a[v1.u/2].word.h.byte.h = (signed char)v2.li;
                                LOG_MSG2(2, "BH_A%u=%d", v1.u, v2.li);
                            } else {
                                LOG_MSG2(2, "BH_A%u=%d oltre range array", v1.u, v2.li);
                            }
							c += v3.offset;
							break;
						case F_A_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u/2, 0, ARRAY_SIZE(p_dplc_v3->aa)-1)) {
                                var.a[v1.u/2].fl = (float)v2.g;
                                LOG_MSG2(2, "F_A%u=%f", v1.u, v2.g);
                            } else {
                                LOG_MSG2(2, "F_A%u=%f oltre range array", v1.u, v2.g);
                            }
							c += v3.offset;
							break;
						case R_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u, 0, 16383)) {
							var.r[v1.u] = v2.g;
                                LOG_MSG2(2, "R%u=%f", v1.u, v2.g);
                            } else {
                                LOG_MSG2(2, "R%u=%f oltre range array", v1.u, v2.g);
                            }
							c += v3.offset;
							break;
						case CANC_ASSIGN_TOKEN:
							var.c[v1.u] = v2.g;
							c += v3.offset;
							LOG_MSG2(2, "#%u=%f", v1.u, v2.g);
							break;
                        case T_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u, 0, (Q_TEMP)-1)) {
								lotime((unsigned short)v1.u, (float)v2.g);
                                LOG_MSG2(2, "T%u=%f", v1.u, v2.g);
                            } else {
                                LOG_MSG2(2, "T%u=%f oltre range array", v1.u, v2.g);
                            }
							c += v3.offset;
							break;
						case TS_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u, 0, ARRAY_SIZE(maxTSuppl)-1)) {
                                maxTSuppl[v1.u] = (unsigned int)v2.g;
                                LOG_MSG2(2, "TS%u=%f", v1.u, v2.g);
                            } else {
                                LOG_MSG2(2, "TS%u=%f oltre range array", v1.u, v2.g);
                            }
							c += v3.offset;
							break;
						case TSD_ASSIGN_TOKEN:
                            if (IN_RANGE(v1.u, 0, ARRAY_SIZE(maxTSimu)-1)) {
                                maxTSimu[v1.u] = (unsigned int)v2.g;
                                LOG_MSG2(2, "TSD%u=%f", v1.u, v2.g);
                            } else {
                                LOG_MSG2(2, "TSD%u=%f oltre range array", v1.u, v2.g);
                            }
							c += v3.offset;
							break;
						default: // Pattern sconosciuto, errore irreversibile
							ERROR_STATUS(status, "Errore di sintassi");
							FB_EXIT(status);
							break;
					}
				}
			}
			break;
	}

    FB_EXIT(status);
}


//----------------------------------------------------------------------------
// FUNZIONE:    processConfmac
// DESCRIZIONE: Carica il file d'origine, lo interpreta e carica i valori
//              nelle opportune variabili PLC.
//              Gestisce eventuali errori di apertura file, lettura file, 
//              allocazione di memoria, chiusura file ecc...
// INPUT:       In CONFMAC_FILE_NAME percorso relativo a workextend del file
//              file di configurazione
// OUTPUT:      =0 in caso di successo e termine della funzione.
//              >0 in caso di elaborazione in corso.
//              <0 in caso di errore irreversibile.
//              In caso d'errore. CONFMAC_ERROR_WORD contiene il codice
//----------------------------------------------------------------------------       
RTPLC_STATUS processConfmac(BOOL reset)
{
    const int MAX_FILE_RETRIES = 10;

    static RTPLC_STATUS status = 0;
    static ULONG fileHandle = 0;
    static int fileRetries = 0;

	static RTPLC_CHARSTRING buffer[2048] = {0};
	static RTPLC_VARIANT buffer_var = {0};
	static ULONG buflen = 0;

#ifdef SIMUPC
	BUF_RTPLC_STRING(fileName, 128);
	BUF_RTPLC_STRING(openMode, 12);
#else
	CST_RTPLC_STRING(fileName, CONFMAC_FILE_NAME);
#endif


    RTPLC_STATUS fbResult = RTPLC_STATUS_OK;

    FB_ENTER();

#ifdef SIMUPC
	strcpy (fileName_str, CONFMAC_FILE_NAME);
	strcpy (openMode_str, "rb");
#endif

    if (reset) {
        FB_RESET();       

		status = 0;
        fileRetries = 0;

        memset(&buffer, 0, ARRAY_SIZE(buffer));

		memset(&buffer_var, 0, sizeof(buffer_var));
		buffer_var.vt = RTPLC_FORMAT_UINT8 | RTPLC_FORMAT_ARRAY;
	    buffer_var.value.arr.data = buffer;
	    buffer_var.value.arr.size = ARRAY_SIZE(buffer);
		buflen = 0;

        FB_EXIT(FB_EXIT_SUCCESS);
    }

    switch (status) {
        case 0: // Inizio macchina a stati con chiusura ottimistica handle
            if (fileHandle != 0) {
                JUMP_STATUS(status, 100, "");
                break;
            }
            NEXT_STATUS(status, "");

		case 1: { // Verifica esistenza file
			RTPLC_BIT fileExists = FALSE;
            fbResult = omfileexists(&fileName, &fileExists);
			if (FB_SUCCESS(fbResult)) {
                if (fileExists) NEXT_STATUS(status, "");
                else ERROR_STATUS(status, "Impossibile trovare il file");
            } else if (FB_FAILURE(fbResult)) {
				ERROR_STATUS(status, "Errore durante chiamata di omfileexists (%d)", RTPLC_STATUS2W32(fbResult));
			}}
			break;

		case 2: { // Apertura file

#ifndef SIMUPC
			CST_RTPLC_STRING(openMode, "rb");
#endif

            fbResult = omfileopen(&fileName, &openMode, &fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
                //NEXT_STATUS(status, "passo via");	/* DEBUG */
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileopen (%d)", RTPLC_STATUS2W32(fbResult));
            }}
			break;

        case 3: // Posizionamento ad inizio del confmac
            fbResult = omfileseek(fileHandle, 0, omfsBegin);
			if (FB_SUCCESS(fbResult)) {
				parseConfmac(NULL, TRUE);
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
				JUMP_STATUS(status, 100, "Errore durante chiamata di omfileseek (%d)", RTPLC_STATUS2W32(fbResult));
            }
			break;

		case 4: // Lettura confmac a blocchi ed interpretazione
            fbResult = omfileread(fileHandle, &buffer_var, &buflen);
			if (FB_SUCCESS(fbResult)) {
				char *eb, *es;
				if (buflen <= 0) {
					NEXT_STATUS(status, "");
					break;
				}
                
				eb = es = &((PRTPLC_CHARSTRING)buffer_var.value.arr.data)[buflen - 1];
				while ((es >= buffer) && (*es != '\r') && (*es != '\n') && (*es != '\0')) es--;
				if (es < buffer) {
					ERROR_STATUS(status, "Riga troppo lunga nel file");
					break;
                }
                *es = '\0';					
				
				fbResult = parseConfmac(buffer, FALSE);
				if (FB_FAILURE(fbResult)) {
					ERROR_STATUS(status, "Errore durante il parsing del file (%d)", RTPLC_STATUS2W32(fbResult));
				} else {
					memmove(buffer, es+1, (eb-es)*sizeof(buffer[0]));
					buffer_var.value.arr.data = buffer+(eb-es);                     
					buffer_var.value.arr.size = ARRAY_SIZE(buffer)-(eb-es);
				}
			} else if (FB_FAILURE(fbResult)) {
				ERROR_STATUS(status, "Errore durante la chiamata di omfileread (%d)", RTPLC_STATUS2W32(fbResult));
            }
			break;

        case -4:
        case 5: // Annullo operazioni in sospeso (se presenti)
            fbResult = omfileAbort(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileabort (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case -5:
        case 6: // Chiusura confmac
            fbResult = omfileclose(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                fileHandle = 0;
                RESET_STATUS(status, "Fine lettura confmac");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileclose (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 100:
            fileRetries = 0;
            NEXT_STATUS(status, "Tentativo chiusura handle aperto");
        case 101:
            fbResult = omfileAbort(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                if (++fileRetries > MAX_FILE_RETRIES) {
                    fileHandle = 0;
					fileRetries = 0;
                    JUMP_STATUS(status, 1, "Probabile handle invalido");
                }
            }
            break;

        case 102: {
            fbResult = omfileclose(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                fileHandle = 0;
				fileRetries = 0;
                JUMP_STATUS(status, 1, "");
			} else if (FB_FAILURE(fbResult)) {
				PREV_STATUS(status, "");
				if (++fileRetries > MAX_FILE_RETRIES) {
                    fileHandle = 0;
					fileRetries = 0;
					JUMP_STATUS(status, 1, "");
				}
			}}
            break;

        default:
            break;
    }

    FB_EXIT(status);
}
