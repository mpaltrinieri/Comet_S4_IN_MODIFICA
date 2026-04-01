/*

        --------------------------------------------------------------
        TITOLO          CONTATORI_BRIDGE_SAVE_FILE
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    EMMEGI QUADRA
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void contatori_bridge_save_file(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        QUADRA 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           24-07-2019
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Medici Stefano
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include "all.inc"
#include "contatori_bridge.h"
#include "contatori_bridge_save_file.h"

#define MAX_FILE_RETRIES 4
#define MAX_COMMAND_FILE_RETRIES 100

RTPLC_STRING cb_fileName;

RTPLC_STRING cb_riga_file;
RTPLC_CHARSTRING cb_riga_file_buffer[256];

RTPLC_STRING fileName_Contatori;

ULONG fileHandle = 0;
int fileRetries = 0;
int cmdFileRetries = MAX_COMMAND_FILE_RETRIES;


void contatori_bridge_save_file_0 (void);
void contatori_bridge_save_file_1 (void);

void contatori_bridge_save_file_pon (void)
{
	fileRetries = 0;
	cmdFileRetries = MAX_COMMAND_FILE_RETRIES;
}


void contatori_bridge_save_file (void)
{
	switch ((int)R[R_CNT_BRIDGE_SAVE_FILE_TEST])
	{
		case 0:
			contatori_bridge_save_file_0 ();
			break;
		case 1:
			contatori_bridge_save_file_1 ();
			break;
	}

}


void contatori_bridge_save_file_1 (void)
{

	RTPLC_STATUS fbResult = FB_EXIT_FAILURE;	
	
	//Generazione del log file ritardato rispetto la richiesta per evitare accessi ai file contemporanei
	if (start_cb_file && (cb_command == CB_COMMAND_IDLE)) 
	{
		cb_command = CB_COMMAND_START; 
		start_cb_file = 0;
	}
	
	
	switch (cb_command)
	{
	case CB_COMMAND_START: //start
		fileName_Contatori.size = ARRAY_SIZE(CB_FILE_NAME)-1;
		fileName_Contatori.sz = CB_FILE_NAME;
		if (cb_status == CB_STATUS_IDLE) {cb_status = CB_STATUS_START; cb_command  = CB_COMMAND_IDLE;}
		break;
	case CB_COMMAND_RESET: //reset
		cb_status = CB_STATUS_TRYCLOSE_1;
		cb_command  = CB_COMMAND_IDLE;
		break;
	case CB_COMMAND_IDLE: //null
		break;
	default:
		cb_command  = CB_COMMAND_IDLE;
		break;
	}

	switch(cb_status) {

		case CB_STATUS_IDLE: // Idle
			break;
        
		case CB_STATUS_START: // Inizio macchina a stati con chiusura ottimistica handle
			if (fileHandle != 0) 
			{
                cb_status = CB_STATUS_TRYCLOSE_1; //Tentativo chiusura handle aperto
                break;
            }

		case CB_STATUS_OPEN: // Apertura file
			{
			RTPLC_STRING openMode = {ARRAY_SIZE("a+")-1, "a+"};
			fbResult = omfileopen(&fileName_Contatori, &openMode, &fileHandle);
			if (fbResult == RTPLC_STATUS_OK) {cmdFileRetries = MAX_COMMAND_FILE_RETRIES; cb_status = CB_STATUS_WRITE;} 
			else if (RTPLC_STATUS_FAILED(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_OPEN_ERR;} //"Errore durante chiamata di omfileopen (%d)
			else if (--cmdFileRetries<=0) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_WAIT_OPEN_ERR;}
			}
			break;

        case CB_STATUS_WRITE: // Scrittura file
			fbResult = omfilewriteline(fileHandle, &cb_riga_file);
			if (fbResult == RTPLC_STATUS_OK) {cmdFileRetries = MAX_COMMAND_FILE_RETRIES; cb_status = CB_STATUS_ABORT;}
			else if (RTPLC_STATUS_FAILED(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_WRITE_ERR;} //Errore durante chiamata di omfilewriteline (%d)
			else if (--cmdFileRetries<=0) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_WAIT_WRITE_ERR;}
			break;

        case CB_STATUS_ABORT: // Annullo operazioni in sospeso (se presenti)
            fbResult = omfileAbort(fileHandle);
            if (fbResult == RTPLC_STATUS_OK) {cmdFileRetries = MAX_COMMAND_FILE_RETRIES; cb_status = CB_STATUS_CLOSE;}
            else if (RTPLC_STATUS_FAILED(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_ABORT_ERR;} //"Errore durante chiamata di omfileabort (%d)
			else if (--cmdFileRetries<=0) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_WAIT_ABORT_ERR;}
            break;

        case CB_STATUS_CLOSE: // Chiusura file
            fbResult = omfileclose(fileHandle);
			if (fbResult == RTPLC_STATUS_OK) {cmdFileRetries = MAX_COMMAND_FILE_RETRIES; fileHandle = 0; cb_status = CB_STATUS_IDLE;}
            else if (RTPLC_STATUS_FAILED(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1;cb_status = CB_STATUS_CLOSE_ERR;} //"Errore durante chiamata di omfileclose (%d)
			else if (--cmdFileRetries<=0) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_WAIT_CLOSE_ERR;}
            break;



		case CB_STATUS_TRYCLOSE_1: //Tentativo chiusura handle aperto
            fileRetries = 0;
            cb_status = CB_STATUS_TRYCLOSE_2;
			cmdFileRetries = MAX_COMMAND_FILE_RETRIES;

		case CB_STATUS_TRYCLOSE_2:
            fbResult = omfileAbort(fileHandle);
			if (fbResult == RTPLC_STATUS_OK) {cmdFileRetries = MAX_COMMAND_FILE_RETRIES; cb_status = CB_STATUS_TRYCLOSE_3;}
            else if (RTPLC_STATUS_FAILED(fbResult))
			{
                if (++fileRetries > MAX_FILE_RETRIES) 
				{
                    fileHandle = 0;
					fileRetries = 0;
					cmdFileRetries = MAX_COMMAND_FILE_RETRIES;
                    cb_status = CB_STATUS_START; //Probabile handle invalido
                }
            }
			else if (--cmdFileRetries<=0) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_WAIT_ABORT2_ERR;}

            break;

        case CB_STATUS_TRYCLOSE_3: 
			fbResult = omfileclose(fileHandle);
			if (fbResult == RTPLC_STATUS_OK) 
			{
				fileHandle = 0;
				fileRetries = 0;
				cmdFileRetries = MAX_COMMAND_FILE_RETRIES; 
				cb_status = CB_STATUS_START;
			} 
			else if (RTPLC_STATUS_FAILED(fbResult))
			{
				if (fbResult == W322RTPLC_STATUS(ERROR_FILE_NOT_FOUND)) 
				{
					// fileHandle gia’ distrutto
					fileHandle = 0;
					fileRetries = 0;
					cmdFileRetries = MAX_COMMAND_FILE_RETRIES; 
					cb_status = CB_STATUS_START;
				} 
				else 
				{
					fileRetries++;
					if (fileRetries < MAX_FILE_RETRIES) 
					{
						cb_status = CB_STATUS_TRYCLOSE_2; //riprova omfileAbort
						cmdFileRetries = MAX_COMMAND_FILE_RETRIES; 
					}
					else
					{
						fileHandle = 0;
						fileRetries = 0;
						cmdFileRetries = MAX_COMMAND_FILE_RETRIES; 
						cb_status = CB_STATUS_START; //Probabile handle_2 invalido
					}
				}
			}
			else if (--cmdFileRetries<=0) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1; cb_status = CB_STATUS_WAIT_CLOSE2_ERR;}

            break;

		case CB_STATUS_OPEN_ERR:		//Errore
		case CB_STATUS_WAIT_OPEN_ERR:	//Errore
		case CB_STATUS_WRITE_ERR:		//Errore
		case CB_STATUS_WAIT_WRITE_ERR:	//Errore
		case CB_STATUS_ABORT_ERR:		//Errore
		case CB_STATUS_CLOSE_ERR:		//Errore
		case CB_STATUS_WAIT_ABORT_ERR:	//Errore
		case CB_STATUS_WAIT_CLOSE_ERR:	//Errore
		case CB_STATUS_WAIT_ABORT2_ERR:	//Errore
		case CB_STATUS_WAIT_CLOSE2_ERR:	//Errore
			if (RESET_MC) CONTATORI_BRIDGE_SAVE_FILE_FMS = 0;
			break;

		default:
			if ((fileHandle != 0) && FB_SUCCESS(omfileclose(fileHandle))){fileHandle = 0; cb_status = CB_STATUS_IDLE;}
		    break;
	}
}

void contatori_bridge_save_file_0 (void)
{
	RTPLC_STATUS fbResult = FB_EXIT_FAILURE;	
	
	//Generazione del log file ritardato rispetto la richiesta per evitare accessi ai file contemporanei
	if (start_cb_file && (cb_command == CB_COMMAND_IDLE)) 
	{
		cb_command = CB_COMMAND_START; 
		start_cb_file = 0;
	}
	
	switch (cb_command)
	{
	case CB_COMMAND_START: //start
		fileName_Contatori.size = ARRAY_SIZE(CB_FILE_NAME)-1;
		fileName_Contatori.sz = CB_FILE_NAME;
		if (!cb_status) cb_status = CB_STATUS_START;
		cb_command  = CB_COMMAND_IDLE;
		break;
	case CB_COMMAND_RESET: //reset
		cb_status = CB_STATUS_TRYCLOSE_1;
		cb_command  = CB_COMMAND_IDLE;
		break;
	case CB_COMMAND_IDLE: //null
	default:
		cb_command  = CB_COMMAND_IDLE;
		break;
	}

	switch(cb_status) {

		case CB_STATUS_IDLE: // Idle
			break;
        
		case CB_STATUS_START: // Inizio macchina a stati con chiusura ottimistica handle
			// SERVE SOLO SU SAT_XT:  if (!PILOT_CONF)  break;

			if (fileHandle != 0) 
			{
                cb_status = CB_STATUS_TRYCLOSE_1; //Tentativo chiusura handle aperto
                break;
            }

		case CB_STATUS_OPEN: // Apertura file
			{
			RTPLC_STRING openMode = {ARRAY_SIZE("a+")-1, "a+"};
			fbResult = omfileopen(&fileName_Contatori, &openMode, &fileHandle);
			if (FB_SUCCESS(fbResult)) {cb_status = CB_STATUS_WRITE;} 
			else if (FB_FAILURE(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1;cb_status = CB_STATUS_OPEN_ERR;} //"Errore durante chiamata di omfileopen (%d)
			}
			break;

        case CB_STATUS_WRITE: // Scrittura file
			fbResult = omfilewriteline(fileHandle, &cb_riga_file);
			if (FB_SUCCESS(fbResult)) {cb_status = CB_STATUS_CLOSE;}
			else if (FB_FAILURE(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1;cb_status = CB_STATUS_WRITE_ERR;} //Errore durante chiamata di omfilewriteline (%d)
			break;

        //case CB_STATUS_ABORT: // Annullo operazioni in sospeso (se presenti)
        //    fbResult = omfileAbort(fileHandle);
        //    if (FB_SUCCESS(fbResult)) {cb_status = CB_STATUS_CLOSE;}
        //    else if (FB_FAILURE(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1;cb_status = CB_STATUS_ABORT_ERR;} //"Errore durante chiamata di omfileabort (%d)
        //    break;

        case CB_STATUS_CLOSE: // Chiusura file
            fbResult = omfileclose(fileHandle);
			if (FB_SUCCESS(fbResult)) {fileHandle = 0; cb_status = CB_STATUS_IDLE;}
            else if (FB_FAILURE(fbResult)) {CONTATORI_BRIDGE_SAVE_FILE_FMS = 1;cb_status = CB_STATUS_CLOSE_ERR;} //"Errore durante chiamata di omfileclose (%d)
            break;



		case CB_STATUS_TRYCLOSE_1: //Tentativo chiusura handle aperto
            fileRetries = 0;
            cb_status = CB_STATUS_TRYCLOSE_2;

		case CB_STATUS_TRYCLOSE_2:
            fbResult = omfileAbort(fileHandle);
			if (FB_SUCCESS(fbResult)) {cb_status = CB_STATUS_TRYCLOSE_3;}
            else if (FB_FAILURE(fbResult)) 
			{
                if (++fileRetries > MAX_FILE_RETRIES) 
				{
                    fileHandle = 0;
					fileRetries = 0;
                    cb_status = CB_STATUS_START; //Probabile handle invalido
                }
            }
            break;

        case CB_STATUS_TRYCLOSE_3: 
			fbResult = omfileclose(fileHandle);
			if (FB_SUCCESS(fbResult)) 
			{
				fileHandle = 0;
				fileRetries = 0;
				cb_status = CB_STATUS_START;
			} 
			else if (FB_FAILURE(fbResult)) 
			{
				if (fbResult == W322RTPLC_STATUS(ERROR_FILE_NOT_FOUND)) 
				{
					// fileHandle gia’ distrutto
					fileHandle = 0;
					fileRetries = 0;
					cb_status = CB_STATUS_START;
				} 
				else 
				{
					fileRetries++;
					if (fileRetries < MAX_FILE_RETRIES) 
						cb_status = CB_STATUS_TRYCLOSE_2; //riprova omfileAbort
					else
					{
						fileHandle = 0;
						fileRetries = 0;
						cb_status = CB_STATUS_START; //Probabile handle_2 invalido
					}
				}
			}
            break;

		case CB_STATUS_OPEN_ERR: //Errore
		case CB_STATUS_WRITE_ERR: //Errore
		case CB_STATUS_ABORT_ERR: //Errore
		case CB_STATUS_CLOSE_ERR: //Errore
			if (RESET_MC) CONTATORI_BRIDGE_SAVE_FILE_FMS = 0;
			break;

		default:
			if ((fileHandle != 0) && FB_SUCCESS(omfileclose(fileHandle))){fileHandle = 0; cb_status = CB_STATUS_IDLE;}
		    break;
	}
}


void contatori_bridge_create_string (void)
{
	RTPLC_STRING cb_riga_file_formato;

	double cnt_value_read[CNT_MAX_NUM];

	int ncnt=0;

	int t_o_s = 0;

	for (ncnt=0; ncnt<CNT_MAX_NUM; ncnt++)
	{
		t_o_s = ((int) (cnt_bridge_control_word >> ncnt)) & ((int)1); 

		//Contatore a tempo [h]
		if (t_o_s)	cnt_value_read[ncnt]		= (double) (R[R_CONTAORE_START+ncnt] / (60.0*60.0));
		//Contatore a eventi
		else		cnt_value_read[ncnt]		= (double) (R[R_CONTAORE_START+ncnt]);		
	}

	cb_riga_file.size = ARRAY_SIZE(cb_riga_file_buffer);
	cb_riga_file.sz = cb_riga_file_buffer;
	
	// crea riga file log
	cb_riga_file_formato.sz = "%02d/%02d/%02d;%02d:%02d:%02d;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f";
	cb_riga_file_formato.size = strlen(cb_riga_file_formato.sz);

	vsrprintf(&cb_riga_file, &cb_riga_file_formato, 
		dateTime.dayInMonth, dateTime.month, dateTime.year,
		dayTime.hour, dayTime.min, dayTime.sec,
		cnt_value_read[0],cnt_value_read[1],cnt_value_read[2],cnt_value_read[3],
		cnt_value_read[4],cnt_value_read[5],cnt_value_read[6],cnt_value_read[7],
		cnt_value_read[8],cnt_value_read[9],cnt_value_read[10],cnt_value_read[11],
		cnt_value_read[12],cnt_value_read[13],cnt_value_read[14],cnt_value_read[15]);

	cb_riga_file.size = strlen(cb_riga_file.sz); 

}
