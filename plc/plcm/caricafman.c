//----------------------------------------------------------------------------
// TITOLO      : caricafman.c
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Gestione caricamento funzioni manuali da file su MGPilot
//----------------------------------------------------------------------------

#include "all.inc"
#include "caricafman.h"

#ifdef _DEBUG
// Queste funzioni non sono supportate dal simulatore
#undef omcanWriteSDO_UCHAR
#define omcanWriteSDO_UCHAR(...)  (FB_EXIT_SUCCESS)
#undef omcanWriteSDO
#define omcanWriteSDO(...) (FB_EXIT_SUCCESS)
#undef omcanOpen
#define omcanOpen(...) (FB_EXIT_SUCCESS)
#undef omcanClose
#define omcanClose(...) do { } while(FALSE)
#endif

CNC_MESSAGE_TABLE cncMsgTable;


//----------------------------------------------------------------------------
// FUNZIONE:    selFman
// DESCRIZIONE: Indica quali funzioni manuali eliminare perchè non presenti o
//              disattivate da configurazione macchina
// INPUT:       nFman - numero della funzione manuale da esaminare
// OUTPUT:      TRUE se la funzioni deve essere inclusa
//              FALSE se la funzione deve essere eliminata
//----------------------------------------------------------------------------
BOOL selFman(int nFman)
{

	UT_01_ESISTENTE = ( 1 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  1 <(R[R_CKT_NR_PINZA]-0.5) ) || (  1 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_02_ESISTENTE = ( 2 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  2 <(R[R_CKT_NR_PINZA]-0.5) ) || (  2 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_03_ESISTENTE = ( 3 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  3 <(R[R_CKT_NR_PINZA]-0.5) ) || (  3 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_04_ESISTENTE = ( 4 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  4 <(R[R_CKT_NR_PINZA]-0.5) ) || (  4 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_05_ESISTENTE = ( 5 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  5 <(R[R_CKT_NR_PINZA]-0.5) ) || (  5 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_06_ESISTENTE = ( 6 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  6 <(R[R_CKT_NR_PINZA]-0.5) ) || (  6 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_07_ESISTENTE = ( 7 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  7 <(R[R_CKT_NR_PINZA]-0.5) ) || (  7 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_08_ESISTENTE = ( 8 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  8 <(R[R_CKT_NR_PINZA]-0.5) ) || (  8 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_09_ESISTENTE = ( 9 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || (  9 <(R[R_CKT_NR_PINZA]-0.5) ) || (  9 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_10_ESISTENTE = (10 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( 10 <(R[R_CKT_NR_PINZA]-0.5) ) || ( 10 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_11_ESISTENTE = (11 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( 11 <(R[R_CKT_NR_PINZA]-0.5) ) || ( 11 >(R[R_CKT_NR_PINZA]+0.5) ) );
	UT_12_ESISTENTE = (12 < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( 12 <(R[R_CKT_NR_PINZA]-0.5) ) || ( 12 >(R[R_CKT_NR_PINZA]+0.5) ) );


    if ( (nFman == 0) && TRUE) //Prova Lampade,
    {   
         return TRUE;    
    } 
    else if( (nFman == 1) && TRUE) // Riferimento Assi
    {
        return TRUE;
    }
    else if( (nFman == 2) && CONF_RIPARO_ANT) //codice funz. man. AND variabile R come da confmac
    {
        return TRUE;
    }
    else if( (nFman == 5) && TRUE) 
    {
        return TRUE;
    }
    else if( (nFman == 6) && TRUE) 
    {
        return TRUE;
    }
    else if( ( (nFman == 7) || (nFman == 95) ) && CONF_ASSE_W)
    {
        return TRUE;
    }
    else if( ( (nFman == 10) || (nFman == 90) ) && CONF_ASSE_X)
    {
        return TRUE;
    }
    else if( ( (nFman == 11) || (nFman == 91) ) && CONF_ASSE_Y)
    {
        return TRUE;
    }
    else if( ( (nFman == 12) || (nFman == 92) ) && CONF_ASSE_Z)
    {
        return TRUE;
    }
    else if( ( (nFman == 13) || (nFman == 93) ) && CONF_ASSE_A)
    {
        return TRUE;
    }
    //else if( ( (nFman == 14) || (nFman == 94) ) && CONF_ASSE_C)
    //{
    //    return TRUE;
    //}
    else if( (nFman == 15) && CONF_MANDRINO)
    {
        return TRUE;
    }
    else if ((nFman == 16) && (R[R_BATT_PRECISIONE]!=0))
    {
        return TRUE;
    }
    else if( (nFman == 17) && CONF_REF_LUBRICA)
    {
        return TRUE;
    }
    else if( (nFman == 18) && CONF_REF_SPECIALE)
    {
        return TRUE;
    }
    else if( (nFman == 19) && TRUE)
    {
        return TRUE;
    }
    else if( (nFman == 20) && CONF_MANDRINO)
    {
        return TRUE;
    }
    else if( (
		( (nFman == 21) && UT_01_ESISTENTE ) || 
		( (nFman == 22) && UT_02_ESISTENTE ) || 
		( (nFman == 23) && UT_03_ESISTENTE ) ||
		( (nFman == 24) && UT_04_ESISTENTE ) || 
		( (nFman == 25) && UT_05_ESISTENTE ) || 
		( (nFman == 26) && UT_06_ESISTENTE ) ||
		( (nFman == 27) && UT_07_ESISTENTE ) || 
		( (nFman == 28) && UT_08_ESISTENTE ) || 
		( (nFman == 29) && UT_09_ESISTENTE ) ||
		( (nFman == 30) && UT_10_ESISTENTE ) || 
		( (nFman == 31) && UT_11_ESISTENTE ) || 
		( (nFman == 32) && UT_12_ESISTENTE ) 
		) && (CONF_MAGUT_12POSTI || CONF_MAGUT_10POSTI) )
    {
        return TRUE;
    }
    else if( (nFman == 33) && (CONF_MORSA_10 || CONF_MORSA_11 || CONF_MORSA_12 ||
                         CONF_MORSA_13 || CONF_MORSA_14 || CONF_MORSA_15))
    {
        return TRUE;
    }
    else if( (nFman == 37) && CONF_MORSA_10)
    {
        return TRUE;
    }
    else if( (nFman == 38) && CONF_MORSA_11)
    {
        return TRUE;
    }
    else if( (nFman == 39) && CONF_MORSA_12)
    {
        return TRUE;
    }
    else if( (nFman == 40) && CONF_MORSA_13)
    {
        return TRUE;
    }
    else if( (nFman == 41) && CONF_MORSA_14)
    {
        return TRUE;
    }
    else if( (nFman == 42) && CONF_MORSA_15)
    {
        return TRUE;
    }
    else if( (nFman == 47) && CONF_RILEV_MORSE_AX_X)
    {
        return TRUE;
    }
    else if( (nFman == 48) && CONF_BATTUTA_SX1)
    {
        return TRUE;
    }
    else if( (nFman == 49) && CONF_BATTUTA_DX4)
    {
        return TRUE;
    }
    else if( (nFman == 50) && (R[R_INGRASS_PATT] > 0.5))
    {
        return TRUE;
    }
    else if( (nFman == 54) && (CONF_ASSE_M10 || CONF_ZIMMER_MORSA_10) )
    {
        return TRUE;
    }
    else if( (nFman == 55)  && (CONF_ASSE_M11 || CONF_ZIMMER_MORSA_11) )
    {
        return TRUE;
    }
    else if( (nFman == 56) && (CONF_ASSE_M12 || CONF_ZIMMER_MORSA_12) )
    {
        return TRUE;
    }
    else if( (nFman == 57) && (CONF_ASSE_M13 || CONF_ZIMMER_MORSA_13) )
    {
        return TRUE;
    }
    else if( (nFman == 58) && (CONF_ASSE_M14 || CONF_ZIMMER_MORSA_14) )
    {
        return TRUE;
    }
    else if( (nFman == 59) && (CONF_ASSE_M15 || CONF_ZIMMER_MORSA_15) )
    {
        return TRUE;
    }
    else if( (nFman == 64) && CONF_TAVOLA_PRES)
    {
        return TRUE;
    }
    else if( (nFman == 69) && CONF_TRASC_MORSE_AX_X)
    {
        return TRUE;
    }
    else if( (nFman == 74) && CONF_ASSE_M10)
    {
        return TRUE;
    }
    else if( (nFman == 75) && CONF_ASSE_M11)
    {
        return TRUE;
    }
    else if( (nFman == 76) && CONF_ASSE_M12)
    {
        return TRUE;
    }
    else if( (nFman == 77) && CONF_ASSE_M13)
    {
        return TRUE;
    }
    else if( (nFman == 78) && CONF_ASSE_M14)
    {
        return TRUE;
    }
    else if( (nFman == 79) && CONF_ASSE_M15)
    {
        return TRUE;
    }
    else if( (nFman == 83) && CONF_TRASP)
    {
        return TRUE;
    }
    else if( (nFman == 84) && CONF_ASPIRATORI)
    {
        return TRUE;
    }
    else if( (nFman == 99) && TRUE)
    {
        return TRUE;
    }
    else if( (nFman == 100) && CONF_VIS_BASSA)
    {
        return TRUE;
    }
    else if( (nFman == 101) && CONF_VIS_ALTA)
    {
        return TRUE;
    }
	//else if( (nFman == 160) && TRUE) // Ripristina assi condivisi (per evoluzioni future)
	//{
	//	return TRUE;
	//}
	else if( ( (nFman == 180) || (nFman == 181) || (nFman == 182) || (nFman == 183) || (nFman == 184) || (nFman == 185) || (nFman == 186) || 
		       (nFman == 187) || (nFman == 188) || (nFman == 189) || (nFman == 190) || (nFman == 191) || (nFman == 192) || (nFman == 193) || 
			   (nFman == 194) || (nFman == 195) ) && (R[R_VOLANTINO_PRES]>0.5) && CONF_FUNZ_ISO_ABIL )
	{
		return TRUE;
	}
    else return FALSE;
}


RTPLC_STATUS initMGPilot(ULONG canHandle, BOOL reset)
{
    static RTPLC_STATUS status = 0;
    RTPLC_STATUS fbResult = FB_EXIT_FAILURE;

    FB_ENTER();

    if (reset) {
        FB_RESET();

        status = 0;

        FB_EXIT(FB_EXIT_SUCCESS);
    }

    switch (status) {
        case 0:
            NEXT_STATUS(status, "");

        case 1: { // Numero elementi F1
            UCHAR data = 6;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3110, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 2: { // Numero elementi F2
            UCHAR data = 6;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3111, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 3: { // Numero elementi F3
            UCHAR data = 6;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3112, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;


        case 4: { // Titolo F1
            RTPLC_VARIANT data;
            CHAR value[] = "- FUNZIONI MANUALI -";
            data.vt = RTPLC_FORMAT_UINT8 | RTPLC_FORMAT_ARRAY;
            data.value.arr.size = _strlen(value);
            data.value.arr.data = value;
            fbResult = omcanWriteSDO(canHandle, 0x3110, 2, &data, data.value.arr.size, MGPILOT_CAN_TIMEOUT);
          } break;

        case 5: { // Titolo F2
            RTPLC_VARIANT data;
            CHAR value[] = "- ALLARMI -";
            data.vt = RTPLC_FORMAT_UINT8 | RTPLC_FORMAT_ARRAY;
            data.value.arr.size = _strlen(value);
            data.value.arr.data = value;
            fbResult = omcanWriteSDO(canHandle, 0x3111, 2, &data, data.value.arr.size, MGPILOT_CAN_TIMEOUT);
          } break;

        case 6: { // Titolo F3
            RTPLC_VARIANT data;
            CHAR value[] = "- ATTENZIONI -";
            data.vt = RTPLC_FORMAT_UINT8 | RTPLC_FORMAT_ARRAY;
            data.value.arr.size = _strlen(value);
            data.value.arr.data = value;
            fbResult = omcanWriteSDO(canHandle, 0x3112, 2, &data, data.value.arr.size, MGPILOT_CAN_TIMEOUT);
          } break;


        case 7: { // Tipo menù F1 (saltato per crash pilot)
            UCHAR data = 0;
            fbResult = 0;//omcanWriteSDO_UCHAR(canHandle, 0x3110, 3, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 8: { // Tipo menù F2 (saltato per crash pilot)
            UCHAR data = 1;
            fbResult = 0;//omcanWriteSDO_UCHAR(canHandle, 0x3111, 3, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 9: { // Tipo menù F3 (saltato per crash pilot)
            UCHAR data = 1;
            fbResult = 0;//omcanWriteSDO_UCHAR(canHandle, 0x3112, 3, &data, MGPILOT_CAN_TIMEOUT);
          } break;


        case 10: { // Numero voci da visualizzare F1
            UCHAR data = MGPILOT_MAX_F1_ROWS;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3110, 4, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 11: { // Numero voci da visualizzare F2
            UCHAR data = MGPILOT_MAX_F23_ROWS;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3111, 4, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 12: { // Numero voci da visualizzare F3
            UCHAR data = MGPILOT_MAX_F23_ROWS;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3112, 4, &data, MGPILOT_CAN_TIMEOUT);
          } break;


        case 13: { // Visualizzazione indice a lato titolo F1
            UCHAR data = 0;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3110, 5, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 14: { // Visualizzazione indice a lato titolo F2
            UCHAR data = 1;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3111, 5, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 15: { // Visualizzazione indice a lato titolo F3
            UCHAR data = 1;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3112, 5, &data, MGPILOT_CAN_TIMEOUT);
          } break;


        case 16: { // Numero di comandi contestuali F1
            UCHAR data = MGPILOT_MAX_CTX_ROWS;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3118, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 17: { // Numero di comandi contestuali F2
            UCHAR data = 0;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3119, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 18: { // Numero di comandi contestuali F3
            UCHAR data = 0;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x311A, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;


        case 19: { // Numero voci menù F1
            UCHAR data = MGPILOT_MAX_F1_ROWS;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3100, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 20: { // Numero voci menù F2
            UCHAR data = MGPILOT_MAX_F23_ROWS;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3101, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 21: { // Numero voci menù F3
            UCHAR data = MGPILOT_MAX_F23_ROWS;
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3102, 0, &data, MGPILOT_CAN_TIMEOUT);
          } break;

        case 22:
            //fbResult = getMGPilotNode() ? RTPLC_STATUS_ERRORFLAG : RTPLC_STATUS_OK;
            fbResult = RTPLC_STATUS_OK;
            break;

        case 23: 
            RESET_STATUS(status, "Configurazione terminata con successo");
            break;

        default:
            break;
    }

    // Gestione centralizzata avanzamento / errori
    if (status > 0) {
        if (FB_SUCCESS(fbResult))
            NEXT_STATUS(status, "Passo %d eseguito con successo", status-1);
        else if (FB_FAILURE(fbResult))
            ERROR_STATUS(status, "Errore durante il passo %d (%d)", status-1, RTPLC_STATUS2W32(fbResult));
    }

    FB_EXIT(status);
}

RTPLC_STATUS loadMGPilot(BOOL reset)
{
    const int minFunzMan = 0;
    const int maxFunzMan = minFunzMan + (&FUNZ_MAN_LAST_WORD - &FUNZ_MAN_FIRST_WORD + 1)*8*sizeof(FUNZ_MAN_FIRST_WORD) - 1;
    const int MAX_FILE_RETRIES = 10;

    static status = 0;

    static ULONG canHandle = 0;
    static RTPLC_STRING* fileName;
    static ULONG fileHandle = 0;
    static int fileRetries = 0;

    static int fileLineNum = 0;
    static int index = 0;
  
    static RTPLC_CHARSTRING buffer[MAX(MGPILOT_MAX_F1_ROW_LEN, MGPILOT_MAX_F23_ROW_LEN)+1] = {0};
    static RTPLC_STRING buffer_str = {0};
    static RTPLC_VARIANT buffer_var = {0};

#ifdef SIMUPC
	BUF_RTPLC_STRING(cntxFileName, 128);
	BUF_RTPLC_STRING(manmessFileName, 128);
	BUF_RTPLC_STRING(openMode, 12);		
#else
	CST_RTPLC_STRING(cntxFileName, FMAN_MANCNTX_FILE_NAME);
	CST_RTPLC_STRING(manmessFileName, FMAN_MANMESS_FILE_NAME);
#endif


    RTPLC_STATUS fbResult = RTPLC_STATUS_OK;

#ifdef SIMUPC
	strcpy (cntxFileName_str, FMAN_MANCNTX_FILE_NAME);
	strcpy (manmessFileName_str, FMAN_MANMESS_FILE_NAME);
	strcpy (openMode_str, "rb");
#endif

    FB_ENTER();

    if (reset) {
        FB_RESET();       

        status = 0;

        fileLineNum = 0;
        index = 0;

        memset(buffer, 0, sizeof(buffer));

        memset(&buffer_str, 0, sizeof(buffer_str));
        buffer_str.size = ARRAY_SIZE(buffer);
        buffer_str.sz = buffer;

        memset(&buffer_var, 0, sizeof(buffer_var));
        buffer_var.vt = RTPLC_FORMAT_UINT8 | RTPLC_FORMAT_ARRAY;
        buffer_var.value.arr.data = &buffer;
        buffer_var.value.arr.size = 0;

        memset(&fmanMap, 0, sizeof(fmanMap));

        FB_EXIT(FB_EXIT_SUCCESS);
    }

	// Macchina a stati 
	switch(status) {
        case 0:
            if (canHandle != 0) {
                omcanClose(canHandle);
                canHandle = 0;
            }
            if (fileHandle != 0) {
                JUMP_STATUS(status, 100, "");
                break;
            }
            NEXT_STATUS(status, "Apertura canale pilot");

        case 1: // Apertura canale pilot
	        fbResult = omcanOpen(MGPILOT_ADDRESS, &canHandle);
            if (FB_SUCCESS(fbResult)) {
                initMGPilot(canHandle, TRUE); // Reset
                NEXT_STATUS(status, "Configurazione menu");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Impossibile aprire il canale (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 2: // Configurazione MGPilot
	        fbResult = initMGPilot(canHandle, FALSE);
            if (FB_SUCCESS(fbResult)) {
                fileName = &cntxFileName;
                NEXT_STATUS(status, "Lettura voci contestuali");
            } else if (FB_FAILURE(fbResult)) {
                omcanAbort(canHandle);
                ERROR_STATUS(status, "Errore durante la configurazione (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 12:
            fileName = &manmessFileName;
		case 3: { // Verifica esistenza file
			RTPLC_BIT fileExists = FALSE;
            fbResult = omfileexists(fileName, &fileExists);
			if (FB_SUCCESS(fbResult)) {
                if (fileExists) NEXT_STATUS(status, "");
                else ERROR_STATUS(status, "Impossibile trovare il file");
            } else if (FB_FAILURE(fbResult)) {
				ERROR_STATUS(status, "Errore durante chiamata di omfileexists (%d)", RTPLC_STATUS2W32(fbResult));
			}}
			break;

        case 13:
		case 4: { // Apertura file
#ifndef SIMUPC
			CST_RTPLC_STRING(openMode, "rb");
#endif
			
            fbResult = omfileopen(fileName, &openMode, &fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileopen (%d)", RTPLC_STATUS2W32(fbResult));
            }}
			break;

        case 14:
        case 5: // Posizionamento all'inizio del file
            fbResult = omfileseek(fileHandle, 0, omfsBegin);
			if (FB_SUCCESS(fbResult)) {
                fileLineNum = 0;
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
				JUMP_STATUS(status, 100, "Errore durante chiamata di omfileseek (%d)", RTPLC_STATUS2W32(fbResult));
            }
			break;

        case 6: // Lettura voce contestuale
		    fbResult = omfilereadline(fileHandle, &buffer_str);
            if (FB_SUCCESS(fbResult)) {
                if (buffer[0] != '\0') {
                    int i = 0;
                    fileLineNum++; // Incremento le linee acquisite

                    while (_isprint(buffer[i]) && (i < MGPILOT_MAX_CTX_ROW_LEN)) i++; // Prendo tutti i caratteri stampabili fino alla lunghezza massima
                    if (i == 0) { // Errore, riga non stampabile o vuota
                        if (FMAN_ERRORONPARSE) ERROR_STATUS(status, "Riga non valida alla posizione %d", fileLineNum);
                        else LOG_MSG2(1, "Saltata riga %d", fileLineNum);
                    }
                    buffer[i] = '\0'; // Tronco la riga
                    buffer_var.value.arr.size = i; // Dimensione stringa

                    index++;
                    fmanMap.cntxCount++;
                    NEXT_STATUS(status, "");
                } else {
                    memset(buffer, ' ', MGPILOT_MAX_CTX_ROW_LEN);
                    buffer[MGPILOT_MAX_CTX_ROW_LEN] = '\0';
                    buffer_var.value.arr.size = MGPILOT_MAX_CTX_ROW_LEN;
		            SKIP_STATUS(status, "Raggiunta fine del file, elaborate %d linee", fileLineNum); 
                }
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Impossibile leggere il file (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 11:
        case 7: // Scrittura voce contestuale
            fbResult = omcanWriteSDO(canHandle, 0x3108, (UCHAR)index, &buffer_var, buffer_var.value.arr.size, MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult)) {
                if (index < MGPILOT_MAX_CTX_ROWS) {
                    PREV_STATUS(status, "Scritta voce contestuale %d - %s", index, buffer); 
                } else {
                    NEXT_STATUS(status, "Scritta voce contestuale %d - %s", index, buffer);
                }
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore di scrittura voce contestuale (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 18:
        case 8: // Annullo operazioni in sospeso (se presenti)
            fbResult = omfileAbort(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileabort (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 19:
        case 9: // Chiusura file
		    fbResult = omfileclose(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Impossibile chiudere il file");
            }
            break;

        case 10: // Scrivo linee contestuali mancanti
            if (index < MGPILOT_MAX_CTX_ROWS) {
                index++;
                NEXT_STATUS(status, "");
            } else {
                SKIP_STATUS(status, "Fine scrittura voci contestuali");
            }
            break;
            
	    case 15: // Lettura linee del file delle voci di menu
		    fbResult = omfilereadline(fileHandle, &buffer_str);
            if (FB_SUCCESS(fbResult)) {
                if (buffer[0] != '\0') {
                    int fmanIndex = 0;
                    int offset = 0, i = 0;
                    BOOL error = FALSE;
                    
                    fileLineNum++;
                    error = (sscanf(buffer, " %d ; %d%n %n", &fmanIndex, &index, &offset, &offset) < 2)
                         && IN_RANGE(fmanIndex, minFunzMan, maxFunzMan) && IN_RANGE(index, 0, fmanMap.cntxCount);
                    
                    if (error) { // Gestione riga errata / non riconosciuta
                        if (FMAN_ERRORONPARSE) ERROR_STATUS(status, "Errore durante la lettura del file alla linea %d", fileLineNum);
                        else LOG_MSG2(1, "Saltata linea %d", fileLineNum);
                        break;
                    }

                    if (!selFman(fmanIndex)) { // Salto funzioni manuali disattivate
                        LOG_MSG2(1, "Trovata funzione manuale %d disattivata alla riga %d", fmanIndex, fileLineNum);
                        break; 
                    }
                    
                    fmanMap.map[fmanMap.fmanCount++] = fmanIndex;
                    buffer_var.value.arr.data = &buffer[offset];

					/***** MODIFICATO SOTTO IL 19-01-2017: aggiunge un carattere in piu ripetto al limite della riga
                    while (_isprint(buffer[offset+i]) && (i < MGPILOT_MAX_F1_ROW_LEN)) i++;
                    while (isspace(buffer[offset+i])) i--;
                    if (i < MGPILOT_MAX_F1_ROW_LEN) i++;
                    buffer[offset+i] = ' '; // Aggiungo spazio finale
                    buffer[offset+i+1] = '\0'; // Tronco la riga
                    buffer_var.value.arr.size = i + 1; // Dimensione stringa
					*************************************************************************************/

                    while (_isprint(buffer[offset+i]) && (i < (MGPILOT_MAX_F1_ROW_LEN-1))) i++;
					
					while(!(_isprint(buffer[offset+i])) ) i--;  //deve decrementare il contatore se incontra il terminatore sulle stringhe corte
                    while (isspace(buffer[offset+i])) i--;      //elimina tutti gli spazi
					
                    if (i < (MGPILOT_MAX_F1_ROW_LEN-1)) i++;
					
                    buffer[offset+i] = ' '; // Aggiungo spazio finale
                    buffer[offset+i+1] = '\0'; // Tronco la riga
                    buffer_var.value.arr.size = i + 1; // Dimensione stringa

                    NEXT_STATUS(status, "");
                } else {
                    memset(buffer, ' ', MGPILOT_MAX_F1_ROW_LEN);
                    buffer[MGPILOT_MAX_F1_ROW_LEN] = '\0';
                    buffer_var.value.arr.size = MGPILOT_MAX_F1_ROW_LEN;
                    index = fmanMap.fmanCount + 1; // Prima riga da cancellare
		            JUMP_STATUS(status, 18, "Raggiunta fine del file, elaborate %d linee", fileLineNum); 
                }
            } else if (FB_FAILURE(fbResult)) {
			    ERROR_STATUS(status, "Impossibile leggere il file (%d)", RTPLC_STATUS2W32(fbResult));
		    }
            break;

        case 16: // Scrittura linea menù F1 su pilot
            fbResult = omcanWriteSDO(canHandle, 0x3100, (UCHAR)fmanMap.fmanCount, &buffer_var, buffer_var.value.arr.size, MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult))
                NEXT_STATUS(status, "Scritta funzione manuale %d riga menu %d - %s", fmanMap.map[fmanMap.fmanCount-1], fmanMap.fmanCount, buffer_var.value.arr.data);
            else if (FB_FAILURE(fbResult))
                ERROR_STATUS(status, "Errore di scrittura menu (%d)", RTPLC_STATUS2W32(fbResult));
            break;

        case 17: // Associazione riga di contesto
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3118, (UCHAR)fmanMap.fmanCount, &((UCHAR)index), MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult)) {
                JUMP_STATUS(status, 15, "Associata voce %d a contesto %d", fmanMap.fmanCount, index);
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore associazione contesto (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 20:
            if (index < MGPILOT_MAX_F1_ROWS) {
                fbResult = omcanWriteSDO(canHandle, 0x3100, (UCHAR)index, &buffer_var, buffer_var.value.arr.size, MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult)) {
                    LOG_MSG2(2, "Cancellata riga menu %d", index++);
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore di scrittura menu (%d)", RTPLC_STATUS2W32(fbResult));
            }
            } else {
                NEXT_STATUS(status, "Fine scrittura voci menu");
            }
            break;

        case 21: // Scrittura lunghezza effettiva menù F1
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3110, 4, &((UCHAR)fmanMap.fmanCount), MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "Numero voci menu disponibili %d", fmanMap.fmanCount);
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante il troncamento delle funzioni manuali");
            }
            break;

        case 22: // Preparo buffers per cancellare F2 ed F3
            index = 1;
            memset(buffer, ' ', sizeof(buffer));
            buffer[ARRAY_SIZE(buffer)-1] = '\0';
            buffer_var.value.arr.size = ARRAY_SIZE(buffer)-1;
            NEXT_STATUS(status, "");
        case 23: // Cancello contenuto F2
            if (index < MGPILOT_MAX_F23_ROWS) {
                fbResult = omcanWriteSDO(canHandle, 0x3101, (UCHAR)index, &buffer_var, buffer_var.value.arr.size, MGPILOT_CAN_TIMEOUT);
                if (FB_SUCCESS(fbResult)) {
                    index++;
                } else if (FB_FAILURE(fbResult)) {
                    LOG_MSG2(2, "Errore di cacellazione riga %d di F2", index);
                    index++;
                }
            } else {
                index = 0;
                NEXT_STATUS(status, "Terminata cancellazione pagina F2");
            }
            break;

        case 24:
            if (index < MGPILOT_MAX_F23_ROWS) {
                fbResult = omcanWriteSDO(canHandle, 0x3102, (UCHAR)index, &buffer_var, buffer_var.value.arr.size, MGPILOT_CAN_TIMEOUT);
                if (FB_SUCCESS(fbResult)) {
                    index++;
                } else if (FB_FAILURE(fbResult)) {
                    LOG_MSG2(2, "Errore di cacellazione riga %d di F3", index);
                    index++;
                }
            } else {
                index = 0;
                NEXT_STATUS(status, "Terminata cancellazione pagina F3");
            }
            break;

        case 25: // Chiusura handle canbus
		    omcanClose(canHandle);
            canHandle = 0;
            RESET_STATUS(status, "Inizializzazione completata con successo");
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

        case 102:
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
            }
            break;

        default:
            if ((fileHandle != 0) && FB_SUCCESS(omfileclose(fileHandle)))
                fileHandle = 0;
            if (canHandle != 0) {
                omcanClose(canHandle);
                canHandle = 0;
            }
            break;
    }

    FB_EXIT(status);
}

RTPLC_STATUS loadCncMsg(BOOL reset)
{
    const int MAX_FILE_RETRIES = 10;

    static RTPLC_STATUS status = 0;
    static ULONG fileHandle = 0;
    static int fileLineNum = 0;
    static int fileRetries = 0;

    static RTPLC_CHARSTRING buffer[MGPILOT_MAX_F23_ROW_LEN+3] = {0};
    static RTPLC_VARIANT buffer_var = {0};
    static ULONG buflen = 0;

#ifdef SIMUPC
	BUF_RTPLC_STRING(fileName, 128);
	BUF_RTPLC_STRING(openMode, 12);
#else
	CST_RTPLC_STRING(fileName, FMAN_CNCMSG_FILE_NAME);
#endif

    RTPLC_STATUS fbResult = RTPLC_STATUS_OK;

#ifdef SIMUPC
	strcpy (fileName_str, FMAN_CNCMSG_FILE_NAME);
	strcpy (openMode_str, "rb");
#endif

    FB_ENTER();

    if (reset) {
        FB_RESET();       

        status = 0;
        fileLineNum = 0;
        fileRetries = 0;

        memset(&cncMsgTable, 0, sizeof(cncMsgTable));

        memset(&buffer, 0, ARRAY_SIZE(buffer));

        memset(&buffer_var, 0, sizeof(buffer_var));
        buffer_var.vt = RTPLC_FORMAT_UINT8 | RTPLC_FORMAT_ARRAY;
        buffer_var.value.arr.data = buffer;
        buffer_var.value.arr.size = ARRAY_SIZE(buffer);
        buflen = 0;

        FB_EXIT(FB_EXIT_SUCCESS);
    }

    // Macchina a stati
    switch(status) {
        case 0:
            if (fileHandle != 0) {
                JUMP_STATUS(status, 100, "");
                break;
            }
            NEXT_STATUS(status, "Verifica esistenza file messaggi");

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
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileopen (%d)", RTPLC_STATUS2W32(fbResult));
            }}
            break;

        case 3: // Posizionamento all'inizio del file
            fbResult = omfileseek(fileHandle, 0, omfsBegin);
            if (FB_SUCCESS(fbResult)) {
                fileLineNum = 0;
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                JUMP_STATUS(status, 100, "Errore durante chiamata di omfileseek (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 4: // Lettura righe
        case 5:
        case 6:
            fbResult = omfileread(fileHandle, &buffer_var, &buflen);
            if (FB_SUCCESS(fbResult)) {
                char *eb, *es, *linePtr;
                if (buflen <= 0) {
                    NEXT_STATUS(status, "Raggiunta fine del file, elaborate %d linee", fileLineNum);
                    break;
                }
                
                eb = es = &((PRTPLC_CHARSTRING)buffer_var.value.arr.data)[buflen - 1];
                while ((es >= buffer) && (*es != '\r') && (*es != '\n') && (*es != '\0')) es--;
                if (es < buffer) {
                    ERROR_STATUS(status, "Riga %d troppo lunga nel file", fileLineNum);
                    break;
                }
                *es = '\0';
                                
                if ((linePtr = strtok(buffer, "\r\n")) == NULL) break;            
                do {
                    int index, offset;            
                    if (linePtr >= es) break;

                    fileLineNum++;

                    index = -1, offset = -1;
                    sscanf(linePtr, " [ALARM] %n%*[^\r\n]%n", &index, &offset);
                    if ((index > 0) && (index > offset)) {
                        JUMP_STATUS(status, 5, "Trovato tag [ALARM] alla linea %d", fileLineNum);
                        continue;
                    }

                    index = -1, offset = -1;
                    sscanf(linePtr, " [MSG] %n%*[^\r\n]%n", &index, &offset);
                    if ((index > 0) && (index > offset)) {
                        JUMP_STATUS(status, 6, "Trovato tag [MSG] alla linea %d", fileLineNum);
                        continue;
                    }

                    if (status == 4) continue;

                    index = -1, offset = -1;
                    if (sscanf(linePtr, " %d = %n", &index, &offset) < 1) continue;
                    if (status == 5) {
                        if (!IN_RANGE(index, 0, ARRAY_SIZE(cncMsgTable.alarmsStr)-1) || (offset < 0)) {
                            LOG_MSG2(2, "Impossibile caricare la riga %d", fileLineNum);
                        } else {
                            LOG_MSG2(2, "Caricato allarme %d=%s", index, linePtr+offset);
                            strncpy(cncMsgTable.alarmsStr[index], linePtr+offset, ARRAY_SIZE(cncMsgTable.alarmsStr[index]));
                            cncMsgTable.alarmsStr[index][ARRAY_SIZE(cncMsgTable.alarmsStr[index])-1] = '\0';
                        }
                    } else if (status == 6) {
                        if (!IN_RANGE(index, 0, ARRAY_SIZE(cncMsgTable.messagesStr)-1) || (offset < 0)) {
                            LOG_MSG2(2, "Impossibile caricare la riga %d", fileLineNum);
                        } else {
                            LOG_MSG2(2, "Caricato messaggio %d=%s", index, linePtr+offset);
                            strncpy(cncMsgTable.messagesStr[index], linePtr+offset, ARRAY_SIZE(cncMsgTable.messagesStr[index]));
                            cncMsgTable.messagesStr[index][ARRAY_SIZE(cncMsgTable.messagesStr[index])-1] = '\0';
                        }
                    }
                } while ((linePtr = strtok(NULL, "\r\n")) != NULL);

                memmove(buffer, es+1, (eb-es)*sizeof(buffer[0]));
                buffer_var.value.arr.data = buffer+(eb-es);                     
                buffer_var.value.arr.size = ARRAY_SIZE(buffer)-(eb-es);
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante la chiamata di omfileread (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 7: // Annullo operazioni in sospeso (se presenti)
            fbResult = omfileAbort(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileabort (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 8: // Chiusura file
            fbResult = omfileclose(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                RESET_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Impossibile chiudere il file");
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

        case 102:
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
            }
            break;

	    default:
            if ((fileHandle != 0) && FB_SUCCESS(omfileclose(fileHandle)))
                fileHandle = 0;
		    break;
	}

    FB_EXIT(status);
}

RTPLC_STATUS writeRemCtrl(BOOL reset)
{
    const int minFunzMan = 0;
    const int maxFunzMan = minFunzMan + (&FUNZ_MAN_LAST_WORD - &FUNZ_MAN_FIRST_WORD + 1)*8*sizeof(FUNZ_MAN_FIRST_WORD) - 1;
    const int MAX_FILE_RETRIES = 10;

    static RTPLC_STATUS status = 0;
    static ULONG fileHandle = 0;
    static int fileRetries = 0;

	static RTPLC_CHARSTRING wBuffer[25] = {0};
	static RTPLC_STRING wBuffer_str = {0};

	static RTPLC_CHARSTRING rBuffer[25] = {0};
	static RTPLC_STRING rBuffer_str = {0};

    static int index = 0;

#ifdef SIMUPC
	BUF_RTPLC_STRING(fileName, 128);
	BUF_RTPLC_STRING(openMode, 12);
	BUF_RTPLC_STRING(openModeW, 12);
#else
	CST_RTPLC_STRING(fileName, FMAN_SELREM_FILE_NAME);
#endif
	
    RTPLC_STATUS fbResult = FB_EXIT_FAILURE;

#ifdef SIMUPC
	strcpy (fileName_str, FMAN_SELREM_FILE_NAME);
	strcpy (openMode_str, "rb");
	strcpy (openModeW_str, "wb");
#endif

    FB_ENTER();

    if (reset) {
        FB_RESET();

		status = 0;
        fileRetries = 0;

        memset(&wBuffer, 0, ARRAY_SIZE(wBuffer));
        memset(&rBuffer, 0, ARRAY_SIZE(rBuffer));

        memset(&wBuffer_str, 0, sizeof(wBuffer_str));
        wBuffer_str.size = ARRAY_SIZE(wBuffer);
        wBuffer_str.sz = wBuffer;

        memset(&rBuffer_str, 0, sizeof(rBuffer_str));
        rBuffer_str.size = ARRAY_SIZE(rBuffer);
        rBuffer_str.sz = rBuffer;

        index = minFunzMan;

        FB_EXIT(FB_EXIT_SUCCESS);
    }

	switch(status) {
        case 0: // Inizio macchina a stati con chiusura ottimistica handle
            if (fileHandle != 0) {
                JUMP_STATUS(status, 100, "");
                break;
            }
            NEXT_STATUS(status, "");

        case 1:
        case 2: { // Apertura file
#ifndef SIMUPC
				CST_RTPLC_STRING(openMode, "rb");
#endif
			
            fbResult = omfileopen(&fileName, &openMode, &fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                JUMP_STATUS(status, 7, "File REM_CTRL non trovato (%d)", RTPLC_STATUS2W32(fbResult));
            }}
			break; 

        case 3: // Posizionamento ad inizio del file
            fbResult = omfileseek(fileHandle, 0, omfsBegin);
			if (FB_SUCCESS(fbResult)) {
                index = minFunzMan ;
                _strcpy(wBuffer, "[HIDE_COMMAND]");
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
				JUMP_STATUS(status, 100, "Errore durante chiamata di omfileseek (%d)", RTPLC_STATUS2W32(fbResult));
            }
			break;

        case 4:
            fbResult = omfilereadline(fileHandle, &rBuffer_str);
			if (FB_SUCCESS(fbResult)) {
                if (_strcmp(wBuffer, rBuffer) != 0) {
                    NEXT_STATUS(status, "Il file REM_CTRL deve essere aggiornato");
                } else { 
                    BOOL selected = TRUE;
                    while ((index <= maxFunzMan) && selected) {
                        selected = selFman(index);
                        if (!selected) sprintf(wBuffer, "%03d = 1", index);
                        index++;
                    }
                    if (selected) JUMP_STATUS(status, 10, "Il file REM_CTRL corrisponde alle impostazioni attuali");
                }
            } else if (FB_FAILURE(fbResult)) {
				JUMP_STATUS(status, 100, "Errore durante chiamata di omfileseek (%d)", RTPLC_STATUS2W32(fbResult));
            }
			break;

        case 5: 
        case 10: // Annullo operazioni in sospeso (se presenti)
            fbResult = omfileAbort(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileabort (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 6: 
        case 11: // Chiusura file
            fbResult = omfileclose(fileHandle);
            if (FB_SUCCESS(fbResult)) {
                fileHandle = 0;
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileclose (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 12:
            RESET_STATUS(status, "Fine aggiornamento REM_CTRL");
            break;

		case 7: { // Apertura file
#ifndef SIMUPC
			CST_RTPLC_STRING(openMode, "wb");
			fbResult = omfileopen(&fileName, &openMode, &fileHandle);
#else
			fbResult = omfileopen(&fileName, &openModeW, &fileHandle);
#endif
		
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omfileopen (%d)", RTPLC_STATUS2W32(fbResult));
            }}
			break;

        case 8: // Posizionamento ad inizio del file
            fbResult = omfileseek(fileHandle, 0, omfsBegin);
			if (FB_SUCCESS(fbResult)) {
				index = minFunzMan;
                _strcpy(wBuffer, "[HIDE_COMMAND]");
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
				JUMP_STATUS(status, 100, "Errore durante chiamata di omfileseek (%d)", RTPLC_STATUS2W32(fbResult));
            }
			break;

        case 9: // Scrittura file
            fbResult = omfilewriteline(fileHandle, &wBuffer_str);
            if (FB_SUCCESS(fbResult)) {
                BOOL selected = TRUE;
                while ((index <= maxFunzMan) && selected) {
                    selected = selFman(index);
                    if (!selected) sprintf(wBuffer, "%03d = 1", index);
                    index++;
                }
                if (selected) NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
				ERROR_STATUS(status, "Errore durante chiamata di omfilewriteline (%d)", RTPLC_STATUS2W32(fbResult));
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
            if ((fileHandle != 0) && FB_SUCCESS(omfileclose(fileHandle)))
                fileHandle = 0;
		    break;

    }

    FB_EXIT(status);
}

RTPLC_STATUS updateF2F3(BOOL reset)
{
    const RTPLC_CHARSTRING blankStr[] = " ";

    static status = 0;
    static ULONG canHandle = 0;

    static int index = 0;
    static double *rPtr = NULL;
    static double memAlarms[MGPILOT_MAX_F23_ROWS], memMessages[MGPILOT_MAX_F23_ROWS];
    static RTPLC_VARIANT buffer_var = {0};

    RTPLC_STATUS fbResult = RTPLC_STATUS_OK;

    FB_ENTER();

    if (reset) {
        FB_RESET();       

        status = 0;
        
        index = 0;
        rPtr = NULL;
        memset(memAlarms, 0xFF, sizeof(memAlarms));
        memset(memMessages, 0xFF, sizeof(memMessages));
        
        memset(&buffer_var, 0, sizeof(buffer_var));
        buffer_var.vt = RTPLC_FORMAT_UINT8 | RTPLC_FORMAT_ARRAY;

        FB_EXIT(FB_EXIT_SUCCESS);
    }

    // Macchina a stati 
    switch(status) {
        case 0:
            if (canHandle != 0) {
                omcanClose(canHandle);
                canHandle = 0;
            }
            NEXT_STATUS(status, "Apertura canale pilot");

        case 1: // Apertura canale pilot
            fbResult = omcanOpen(MGPILOT_ADDRESS, &canHandle);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "Scrittura menu F2 ed F3 menu");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Impossibile aprire il canale (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 2:
            index = 0;
            rPtr = &R[ALARM_FIRST_R];
            NEXT_STATUS(status, "");
        case 3: {
            BOOL finded = FALSE;
            while (     (rPtr <= &R[ALARM_LAST_R]) && (index < MGPILOT_MAX_F23_ROWS)
                    && !(finded =    IN_RANGE(*rPtr, 0, ALARM_LAST_AL-ALARM_FIRST_AL) 
                                  && (*rPtr < ARRAY_SIZE(cncMsgTable.alarmsStr))
                                  && (*rPtr != memAlarms[index])))
            {
                rPtr++; index++;
            }
            if (finded) {
                if (*rPtr != 0) buffer_var.value.arr.data = &cncMsgTable.alarmsStr[(int)*rPtr];
                else buffer_var.value.arr.data = (LPVOID)&blankStr;
                buffer_var.value.arr.size = strlen(buffer_var.value.arr.data);
                memAlarms[index] = *rPtr;
                NEXT_STATUS(status, "");
            } else {
                SKIP_STATUS(status, "");
            }
            } break;

        case 4: // Aggiornamento menù F2
            fbResult = omcanWriteSDO(canHandle, 0x3101, (UCHAR)index+1, &buffer_var, buffer_var.value.arr.size, MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult)) {
                LOG_MSG2(2, "Allarme riga %d: %s", index, buffer_var.value.arr.data);
                rPtr++; index++;
                PREV_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omcanWriteSDO (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 5:
            index = 0;
            rPtr = &R[ALARM_FIRST_R];
            while ((*rPtr != 0) && (rPtr++ < &R[ALARM_LAST_R])) index++;
            NEXT_STATUS(status, "");
        case 6:
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3111, 4, (PUCHAR)&index, MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omcanWriteSDO (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 7:
            index = 0;
            rPtr = &R[MESSAGE_FIRST_R];
            NEXT_STATUS(status, "");
        case 8: {
            BOOL finded = FALSE;
            while (    (rPtr <= &R[MESSAGE_LAST_R]) && (index < MGPILOT_MAX_F23_ROWS)
                   && !(finded =    IN_RANGE(*rPtr, 0, MESSAGE_LAST_MS-MESSAGE_FIRST_MS) 
                                 && (*rPtr < ARRAY_SIZE(cncMsgTable.messagesStr))
                                 && (*rPtr != memMessages[index])))
            {
                rPtr++; index++;
            }
            if (finded) {
                if (*rPtr != 0) buffer_var.value.arr.data = &cncMsgTable.alarmsStr[(int)*rPtr];
                else buffer_var.value.arr.data = (LPVOID)&blankStr;
                buffer_var.value.arr.size = strlen(buffer_var.value.arr.data);
                memMessages[index] = *rPtr;
                NEXT_STATUS(status, "");
            } else {
                SKIP_STATUS(status, "");
            }
            } break;
            
        case 9: // Aggiornamento menù F3
            fbResult = omcanWriteSDO(canHandle, 0x3102, (UCHAR)index+1, &buffer_var, buffer_var.value.arr.size, MGPILOT_CAN_TIMEOUT);
            if (FB_SUCCESS(fbResult)) {
                LOG_MSG2(2, "Messaggio riga %d: %s", index, buffer_var.value.arr.data);
                rPtr++; index++;
                PREV_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omcanWriteSDO (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;


        case 10:
            index = 0;
            rPtr = &R[MESSAGE_FIRST_R];
            while ((*rPtr != 0) && (rPtr++ < &R[MESSAGE_LAST_R])) index++;
            NEXT_STATUS(status, "");
        case 11:
            fbResult = omcanWriteSDO_UCHAR(canHandle, 0x3112, 4, (PUCHAR)&index, MGPILOT_CAN_TIMEOUT);
             if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore durante chiamata di omcanWriteSDO (%d)", RTPLC_STATUS2W32(fbResult));
            }
            break;

        case 12:
            JUMP_STATUS(status, 2, "");
            break;

        default:
            break;
    }

    FB_EXIT(status);
}
