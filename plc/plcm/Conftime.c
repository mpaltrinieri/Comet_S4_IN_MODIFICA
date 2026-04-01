/*

        --------------------------------------------------------------
        TITOLO          CONFTIME
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    EMMEGI SATELLITE
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void conftime(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        SXT 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           20-02-2014
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include "all.inc"
#include "CONFTIME.INC"

#define STATO_FILE_CNFT_IDLE        0    // Stato inattivo
#define STATO_FILE_CNFT_EXIST       10   // Stato di verifica esistenza del file
#define STATO_FILE_CNFT_OPEN        20   // Stato di apertura del file: se non esiste viene creato
#define STATO_FILE_CNFT_WRHEAD      30   // Stato di scrittura della riga di testa del file
#define STATO_FILE_CNFT_ELEMARRAY   40   // Stato di ordinamento elementi di array di strutture
#define STATO_FILE_CNFT_WRLINE      50   // Stato di scrittura delle singole righe del file
#define STATO_FILE_CNFT_INCELEM     60   // Stato di incremento elemento struttura da scrivere sul file
#define STATO_FILE_CNFT_WREND       70   // Stato di scrittura riga finale del file
#define STATO_FILE_CNFT_CLOSE       80   // Stato di chiusura del file 
#define STATO_FILE_CNFT_ERROR       1000 // Stato di errore


RTPLC_STATUS Esito_omfileexistsR;
RTPLC_STATUS Esito_omfileopenR;
RTPLC_STATUS Esito_omfilewritelineT;
RTPLC_STATUS Esito_omfilewritelineR;
RTPLC_STATUS Esito_omfilewritelineF;
RTPLC_STATUS Esito_omfilecloseR;
RTPLC_STATUS Esito_omfilecloseERR;

BOOL omfileexistsR_eseguita;
BOOL omfileopenR_eseguita;
BOOL omfilewritelineT_eseguita;
BOOL omfilewritelineR_eseguita;
BOOL omfilewritelineF_eseguita;
BOOL omfilecloseR_eseguita;
BOOL omfilecloseERR_eseguita;

ULONG handle_fileCNFT;			//handle del file

RTPLC_STRING nomefileCNFT;
RTPLC_STRING openmode_fileCNFT;
RTPLC_STRING testa_fileCNFT;
RTPLC_STRING formato_rigaCNFT;
RTPLC_STRING riga_fileCNFT;
RTPLC_CHARSTRING riga_fileCNFT_buffer[MAX_BUFFER_RIGA];

RTPLC_STRING end_fileCNFT;

RTPLC_BIT file_CNFT_exist;


StructElemFile ELEM_FILE[MAX_NUM_STRUCT_ARRAY];

void ordinaArray(StructElemFile *p_struct_array, unsigned short indice_elem_struct)
{
	int index1, index2;
	unsigned short int temp1; 
	double temp2; 
	char *temp3;
	
	for(index1 = 1; index1 < indice_elem_struct; index1++)
	{
		for(index2 = (indice_elem_struct-1); index2 >= index1; index2--)
		{
			if(p_struct_array[index2-1].NUM_VAR_R > p_struct_array[index2].NUM_VAR_R)
			{
				temp1 = p_struct_array[index2-1].NUM_VAR_R;
				p_struct_array[index2-1].NUM_VAR_R = p_struct_array[index2].NUM_VAR_R;
				p_struct_array[index2].NUM_VAR_R = temp1;
				
				temp2=p_struct_array[index2-1].VAL_VAR_R;
				p_struct_array[index2-1].VAL_VAR_R = p_struct_array[index2].VAL_VAR_R;
				p_struct_array[index2].VAL_VAR_R = temp2;
				
				temp3 = p_struct_array[index2-1].COMMENTO;
				p_struct_array[index2-1].COMMENTO = p_struct_array[index2].COMMENTO;
				p_struct_array[index2].COMMENTO = temp3;
				
			}
		}
	}
	
}


void conftime()
{

	if(PON)
	{
		INDEX_ELEM_CONFTIME = 0;
		INDEX_ELEM_FILE = 0;
		SCRIVI_FILE_CONFTIME = 0;
		WRITE_FILE_CONFTIME = STATO_FILE_CNFT_IDLE;

		Esito_omfileexistsR = 0;
		Esito_omfileopenR = 0;
		Esito_omfilewritelineT = 0;
		Esito_omfilewritelineR = 0;
		Esito_omfilewritelineF = 0;
		Esito_omfilecloseR = 0;
		Esito_omfilecloseERR = 0;

		file_CNFT_exist = 0;

		omfileexistsR_eseguita = 0;
		omfileopenR_eseguita = 0;
		omfilewritelineT_eseguita = 0;
		omfilewritelineR_eseguita = 0;
		omfilewritelineF_eseguita = 0;
		omfilecloseR_eseguita = 0;
		omfilecloseERR_eseguita = 0;

		memset(ELEM_FILE, 0, sizeof(ELEM_FILE)); //inizializza l'area di memoria dell'array di strutture
	}


	nomefileCNFT.sz = "%base%\\lav\\lav\\CONFTIME.CS4";
	nomefileCNFT.size = strlen(nomefileCNFT.sz);

	testa_fileCNFT.sz = "{TABELLA DI MEMORIZZAZIONE DURATA MOVIMENTI PNEUMATICI}";
	testa_fileCNFT.size = strlen(testa_fileCNFT.sz);

	end_fileCNFT.sz = "RET\n";
	end_fileCNFT.size = strlen(end_fileCNFT.sz);

	riga_fileCNFT.size = ARRAY_SIZE(riga_fileCNFT_buffer);	// definizione del buffer riga
	riga_fileCNFT.sz = riga_fileCNFT_buffer;				// setta e istanzia


	if(DN_AUXON && ALIM_PRES_I && !SIMULATORE_ON && (R[R_WRITE_CONFTIME] >= 0.5)) //Condizione che determina la partenza della scrittura del file CONFTIME
	{
		SCRIVI_FILE_CONFTIME = 1;
	}

	switch (WRITE_FILE_CONFTIME)
	{
	case STATO_FILE_CNFT_IDLE:
		if(SCRIVI_FILE_CONFTIME)
		{
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_EXIST;
		}
		break;
	case STATO_FILE_CNFT_EXIST:
		// VERIFICA ESISTENZA FILE CONFTIME /////////////////////////////////////////////////////////////////////////
		if (!omfileexistsR_eseguita)		// verifica se file report esiste già
		{
			rtplctrace(1,_T("Scrivi CONFTIME - esegue omfileexists"));

			Esito_omfileexistsR = omfileexists( &(nomefileCNFT),  &(file_CNFT_exist));
			if(Esito_omfileexistsR > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfileexistsR_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if (Esito_omfileexistsR < 0)	
		{
			//Errore in verifica file
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN VERIFICA FILE REPORT  Esito_omfileexistsR=%d"),Esito_omfileexistsR);
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ERROR;
		}
		if(!Esito_omfileexistsR && !file_CNFT_exist && omfileexistsR_eseguita)
		{
			openmode_fileCNFT.size = strlen("a");	    // definisce lunghezza
	        openmode_fileCNFT.sz = "a";					// setta e istanzia
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_OPEN; //crea il file e appende alla fine
			omfileexistsR_eseguita = 0;				// reset flag
		}
		if(!Esito_omfileexistsR && file_CNFT_exist && omfileexistsR_eseguita)
		{
			openmode_fileCNFT.size = strlen("w");	    // definisce lunghezza
	        openmode_fileCNFT.sz = "w";				    // setta e istanzia
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_OPEN; //apri il file in scrittura cancellandone il contenuto
			omfileexistsR_eseguita = 0;				// reset flag
		}	
		break;
	case STATO_FILE_CNFT_OPEN:
		// APERTURA FILE CONFTIME  /////////////////////////////////////////////////////////////////////////
		if (!omfileopenR_eseguita)	// 
		{
			rtplctrace(1,_T("Apertura File CONFTIME - esegue omfileopen"));
			nomefileCNFT.size = strlen(nomefileCNFT.sz);
			Esito_omfileopenR = omfileopen(&nomefileCNFT, &openmode_fileCNFT, &handle_fileCNFT);
			if(Esito_omfileopenR > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfileopenR_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if ( (Esito_omfileopenR < 0) || (handle_fileCNFT == 0) )	
		{
			//Errore in apertura file
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN APERTURA FILE CONFTIME  Esito_omfileopenR=%d"),Esito_omfileopenR);
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN APERTURA FILE CONFTIME  handle_fileCNFT=%d"),handle_fileCNFT);
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ERROR;
		}
		if(!Esito_omfileopenR && omfileopenR_eseguita)
		{
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_WRHEAD;
			omfileopenR_eseguita = 0;				// reset flag
		}
		break;

	case STATO_FILE_CNFT_WRHEAD: //scrive riga di testa file CONFTIME
		// SCRITTURA RIGA TESTA NEL FILE CONFTIME ////////////////////////////////////////////////////////////////////////
		if ( !omfilewritelineT_eseguita && (handle_fileCNFT != 0) )
		{
			rtplctrace(1,_T("Scrivi CONFTIME - esegue omfilewritelineT"));
			Esito_omfilewritelineT = omfilewriteline( handle_fileCNFT , &testa_fileCNFT );

			if(Esito_omfilewritelineT > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfilewritelineT_eseguita = 1;				// anche in caso di esito negativo x errore
			rtplctrace(1,_T("Scrivi CONFTIME - SCRITTA RIGA TESTA -  testa_fileCNFT.sz=%s"),testa_fileCNFT.sz);
		}

		if ( (Esito_omfilewritelineT < 0) || (handle_fileCNFT == 0) )	
		{
			//Errore in apertura file
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN SCRITTURA FILE REPORT  Esito_omfilewritelineT=%d"),Esito_omfilewritelineT);
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN SCRITTURA FILE REPORT  handle_fileCNFT=%d"),handle_fileCNFT);
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ERROR;
		}
		if(!Esito_omfilewritelineT && omfilewritelineT_eseguita)
		{
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ELEMARRAY;
			omfilewritelineT_eseguita = 0;				// reset flag
			INDEX_ELEM_FILE = 0;                        // reset inziale indice
		}
		break;

	case STATO_FILE_CNFT_ELEMARRAY:     //ordina gli elementi dell'array di strutture
		ordinaArray(ELEM_FILE, INDEX_ELEM_CONFTIME);
        WRITE_FILE_CONFTIME = STATO_FILE_CNFT_WRLINE;
    break; 
	
	case STATO_FILE_CNFT_WRLINE:     //scrive una riga sul file CONFTIME
		if ( !omfilewritelineR_eseguita && (handle_fileCNFT != 0) )
		{
			rtplctrace(1,_T("Scrivi CONFTIME - esegue omfilewritelineR"));

			// accoda riga nel file CONFTIME
			formato_rigaCNFT.sz = "R%d = %d  %s";
			formato_rigaCNFT.size = strlen(formato_rigaCNFT.sz);
			rtplctrace(1, formato_rigaCNFT.sz, ELEM_FILE[INDEX_ELEM_FILE].NUM_VAR_R, (long) ELEM_FILE[INDEX_ELEM_FILE].VAL_VAR_R, ELEM_FILE[INDEX_ELEM_FILE].COMMENTO);
			
			vsrprintf(&riga_fileCNFT, &formato_rigaCNFT, ELEM_FILE[INDEX_ELEM_FILE].NUM_VAR_R, (long) ELEM_FILE[INDEX_ELEM_FILE].VAL_VAR_R, ELEM_FILE[INDEX_ELEM_FILE].COMMENTO);
           		
			riga_fileCNFT.size = strlen(riga_fileCNFT.sz); 

			rtplctrace(1, riga_fileCNFT.sz, ELEM_FILE[INDEX_ELEM_FILE].NUM_VAR_R, (long) ELEM_FILE[INDEX_ELEM_FILE].VAL_VAR_R, ELEM_FILE[INDEX_ELEM_FILE].COMMENTO);

			Esito_omfilewritelineR = omfilewriteline( handle_fileCNFT , &riga_fileCNFT);

			if(Esito_omfilewritelineR > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfilewritelineR_eseguita = 1;				// anche in caso di esito negativo x errore
			rtplctrace(1,_T("crea_report - SCRITTA RIGA -  riga_fileCNFT.sz=%s"),riga_fileCNFT.sz);
		}

		if ( (Esito_omfilewritelineR < 0) || (handle_fileCNFT == 0) )	
		{
			//Errore in apertura file
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN SCRITTURA FILE CONFTIME  Esito_omfilewritelineR=%d"),Esito_omfilewritelineR);
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN SCRITTURA FILE CONFTIME  handle_fileCNFT=%d"),handle_fileCNFT);
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ERROR;
			break;
		}
		if(!Esito_omfilewritelineR && omfilewritelineR_eseguita)
		{
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_INCELEM;
			omfilewritelineR_eseguita = 0;				// reset flag
		}
		break;

	case STATO_FILE_CNFT_INCELEM:     //punta a elemento successivo dell'array
        INDEX_ELEM_FILE++;
		if(INDEX_ELEM_FILE < INDEX_ELEM_CONFTIME)
		{
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_WRLINE;
		}
		else
		{
            WRITE_FILE_CONFTIME = STATO_FILE_CNFT_WREND;
		}
		break;

	case STATO_FILE_CNFT_WREND:   //scrive fine del file
		// SCRITTURA RIGA FINALE NEL FILE CONFTIME ////////////////////////////////////////////////////////////////////////
		if ( !omfilewritelineF_eseguita && (handle_fileCNFT != 0))
		{
			rtplctrace(1,_T("Scrivi CONFTIME - esegue omfilewritelineT"));
			Esito_omfilewritelineF = omfilewriteline( handle_fileCNFT , &end_fileCNFT );

			if(Esito_omfilewritelineF > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfilewritelineF_eseguita = 1;				// anche in caso di esito negativo x errore
			rtplctrace(1,_T("Scrivi CONFTIME - SCRITTA RIGA FINALE -  end_fileCNFT.sz=%s"),end_fileCNFT.sz);
		}

		if ( (omfilewritelineF_eseguita < 0) || (handle_fileCNFT == 0) )	
		{
			//Errore in apertura file
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN SCRITTURA FILE CONFTIME  omfilewritelineF_eseguita=%d"),omfilewritelineF_eseguita);
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN SCRITTURA FILE CONFTIME  handle_fileCNFT=%d"),handle_fileCNFT);
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ERROR;
		}
		if(!Esito_omfilewritelineF && omfilewritelineF_eseguita)
		{
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_CLOSE;
			omfilewritelineF_eseguita = 0;				// reset flag
		}
		break;
	case STATO_FILE_CNFT_CLOSE: //chiusura del file CONFTIME
		// CHIUSURA FILE CONFTIME /////////////////////////////////////////////////////////////////////////
		if(handle_fileCNFT && !omfilecloseR_eseguita)	
		{
			rtplctrace(1,_T("Scrivi CONFTIME - esegue omfileclose"));
			Esito_omfilecloseR = omfileclose(handle_fileCNFT);
			if (Esito_omfilecloseR > 0) return;		// 1/2=in corso  0=terminato  <0=errore
			omfilecloseR_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if (Esito_omfilecloseR < 0)
		{
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN CHIUSURA FILE CONFTIME  Esito_omfilecloseR=%d"),Esito_omfilecloseR);
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN CHIUSURA FILE CONFTIME  handle_fileCNFT=%d"),handle_fileCNFT);
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ERROR;
		}
		if(!Esito_omfilecloseR && omfilecloseR_eseguita)
		{
			SCRIVI_FILE_CONFTIME = 0;		// reset flag abilitaz scrittura file (se l'esecuzione arriva quì, son terminate tutte le 4 fasi)
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_IDLE;
			omfilecloseR_eseguita = 0;
			INDEX_ELEM_CONFTIME = 0;
		}
		break;

	case STATO_FILE_CNFT_ERROR:
		//Reset di tutti i flag restituiti dalle funzioni di OMFILE
		if( Esito_omfileexistsR || Esito_omfileopenR || Esito_omfilewritelineT || Esito_omfilewritelineR ||
			Esito_omfilewritelineF || Esito_omfilecloseR || file_CNFT_exist)
		{
			Esito_omfileexistsR = 0;
			Esito_omfileopenR = 0;
			Esito_omfilewritelineT = 0;
			Esito_omfilewritelineR = 0;
			Esito_omfilewritelineF = 0;
			Esito_omfilecloseR = 0;

			file_CNFT_exist = 0;
		}
        //Reset di tutti i flag delle funzioni OMFILE eseguite
		if(omfileexistsR_eseguita || omfileopenR_eseguita || omfilewritelineT_eseguita || omfilewritelineR_eseguita ||
		   omfilewritelineF_eseguita || omfilecloseR_eseguita)
		{
			omfileexistsR_eseguita = 0;
			omfileopenR_eseguita = 0;
			omfilewritelineT_eseguita = 0;
			omfilewritelineR_eseguita = 0;
			omfilewritelineF_eseguita = 0;
			omfilecloseR_eseguita = 0;
		}
        
		// CHIUSURA FILE CONFTIME /////////////////////////////////////////////////////////////////////////
		if(handle_fileCNFT && !omfilecloseERR_eseguita)	
		{
			rtplctrace(1,_T("Scrivi CONFTIME - esegue omfileclose"));
			Esito_omfilecloseERR = omfileclose(handle_fileCNFT);
			if (Esito_omfilecloseR > 0) return;		// 1/2=in corso  0=terminato  <0=errore
			omfilecloseERR_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if (Esito_omfilecloseERR < 0)
		{
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN CHIUSURA FILE CONFTIME  Esito_omfilecloseR=%d"),Esito_omfilecloseERR);
			rtplctrace(1,_T("Scrivi CONFTIME - ERRORE IN CHIUSURA FILE CONFTIME  handle_fileCNFT=%d"),handle_fileCNFT);
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_ERROR;
		}
		if(!Esito_omfilecloseERR && omfilecloseERR_eseguita)
		{
			SCRIVI_FILE_CONFTIME = 0;		// reset flag abilitaz scrittura file
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_IDLE;
			omfilecloseERR_eseguita = 0;
			INDEX_ELEM_CONFTIME = 0;
		}
		else if(!handle_fileCNFT && !omfilecloseERR_eseguita) //se non vi sono file aperti salta a stato iniziale
		{
			SCRIVI_FILE_CONFTIME = 0;		// reset flag abilitaz scrittura file
			WRITE_FILE_CONFTIME = STATO_FILE_CNFT_IDLE;
			omfilecloseERR_eseguita = 0;
			INDEX_ELEM_CONFTIME = 0;
		}
		break;
	}
}
