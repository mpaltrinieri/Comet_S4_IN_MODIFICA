/*
        --------------------------------------------------------------
        TITOLO:         CONTATORI BRIDGE
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione contatori su Bridge Isac
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    contatori_bridge(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:       
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:      
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        PHN 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           11-04-2019
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Medici Stefano
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

//NB: SEQUENZA CORRETTA DI INCLUSIONE CHE DEVE ESSER PRESENTE NEI PROGETTI:
	//#include <rtplc.h>			// Inclusioni RTPLC
	//#include <rtplc_14_extensions.h> // Inclusioni RTPLC per accesso a Ethercat
	//#include <iosoptmod.h>      // Inclusioni per FB di accesso ai canali Ethercat


#include "all.inc"
#include "contatori_bridge.h"
#include "contatori_bridge_save_file.h"


#define NDELAY_FILE_LOG_CREATE 10


static			ULONG handle_BRIDGE				= 0;
RTPLC_STRING	iosStringOpen;
RTPLC_STATUS	ret_iosOpen_BRIDGE				= 0;
RTPLC_STATUS	ret_iosClose_BRIDGE				= 0;
RTPLC_STATUS	write_result_BRIDGE				= 0;
RTPLC_STATUS	read_result_BRIDGE				= 0;
int				CNT_BRIDGE_REOPEN_DELAY_INI		= CNT_BRIDGE_REOPEN_DELAY_INI_DEFAULT;
int				CNT_DELAY_POLLING_CONT_INI		= CNT_DELAY_POLLING_CONT_INI_DEFAULT;
ULONG			ULONG_data_write_BRIDGE			= 0;
ULONG			ULONG_data_read_BRIDGE			= 0;
ULONG			dimdata_read_BRIDGE				= 0;
RTPLC_VARIANT	data_BRIDGE;
//ULONG			cnt_bridge_control_word			= CNT_BRIDGE_CONTROL_WORD_DEFAULT;


int				time_or_step					= 0;
int				cntDelayStart					= NDELAY_FILE_LOG_CREATE;


void contatori_bridge_0(void);
void contatori_bridge_0_pon(void);
void contatori_bridge_not_present_0(void);
void contatori_bridge_Output_Standard(void);

int ret_cnt_cont_subindex (int);


void contatori_bridge_Output_Standard(void)
{

	// FILE DRILL
	// N:\Prodotti\Progetti Cnc 7_0\Istruzioni contatori Bridge\file_contaore_2020_01_16
	// D:\COMETS4\DRILL\CONF\CONTAORE.TXT
	// ----------------------------------------------------------------------------------------------------
	// SIMBOLO..DESCRIZIONE................................................................POSSIBILI VALORI
	// ----------------------------------------------------------------------------------------------------
	// INDEX    Indice del contatore                                                       1-16
	// DESC     Testo descrittivo                                                          Testo 
	// RESET    Abilitazione reset contatore (disabilitato obbligatoriam. per i primi 4)   1=Consente il reset;  0=no  0-1
	// VARR     Indice della variabile R che contiene il dato                              Vedi tabella variabile per ciascuna macchina 
	// TIMER    0=contatore a eventi.  1=contatore a tempo                                 0-1


	// [CONTATORE1]
	// Total machine working time
	CNT_1_O = CICLO_ON;

	// [CONTATORE2]
	// Total spindle working time
	CNT_2_O = (AUTO && !MANDRINO_FERMO);

	// [CONTATORE3]
	// Number of tool changes
	CNT_3_O = (R[R_ACT_TOOL]>0.5) && ( ( fabs ( R[R_ACT_TOOL]-R[R_ACT_TOOL_OLD] ) ) > 0.5 );

	// [CONTATORE4]
	// Free
	CNT_4_O = 0;
	
	// [CONTATORE5]
	// Current spindle working time
	CNT_5_O = (CNT_2_O);

	// [CONTATORE6]
	// Free
	CNT_6_O = 0;

	// [CONTATORE7]
	// Free
	CNT_7_O = 0;

	// [CONTATORE8]
	// Free
	CNT_8_O = 0;

	// [CONTATORE9]
	// Free
	CNT_9_O = 0;

	// [CONTATORE10]
	// Free
	CNT_10_O = 0;

	// [CONTATORE11]
	// Free
	CNT_11_O = 0;

	// [CONTATORE12]
	// Free
	CNT_12_O = 0;

	// [CONTATORE13]
	// Free
	CNT_13_O = 0;

	// [CONTATORE14]
	// Free
	CNT_14_O = 0;

	// [CONTATORE15]
	// Free
	CNT_15_O = 0;

	// [CONTATORE16]
	// Free
	CNT_16_O = 0;

	R[R_ACT_TOOL_OLD] = R[R_ACT_TOOL];

}


void contatori_bridge(void)
{
	//Per la configurazione di progetto Simu non sono gestiti i contatori
	switch ((int)R[R_CNT_BRIDGE_TYPE])
	{
	case 0:
	default:
		contatori_bridge_Output_Standard();
		break;
	}

#ifndef _DEBUG
	switch ((int)R[R_CNT_BRIDGE])
	{
	case 1:
		contatori_bridge_0_pon();
		contatori_bridge_save_file_pon ();
		contatori_bridge_0();
		contatori_bridge_save_file ();
		break;
	case 0:
	default:
		contatori_bridge_0_pon();
		contatori_bridge_save_file_pon ();
		contatori_bridge_not_present_0();
		break;
	}
#endif

	//Per la configurazione di progetto Simu non sono gestiti i contatori
#ifdef _DEBUG
	switch ((int)R[R_CNT_BRIDGE])
	{
	case 0:
	case 1:
	default:
		contatori_bridge_not_present_0();
		break;
	}
	
#endif

}


void contatori_bridge_not_present_0(void)
{
	CNT_ERROR_FAL						= 0;
	CNT_BRIDGE_STATE_INFO_INIT_DONE_FMS	= 0;
}


void contatori_bridge_0_pon(void)
{
	if (PON)
	{
		//Inizializzazione contatori
		if (R[R_DELAY_REOPEN]<=0)			CNT_BRIDGE_REOPEN_DELAY_INI	= ncicplc ((float)(CNT_BRIDGE_REOPEN_DELAY_INI_DEFAULT/1000.0));
		else								CNT_BRIDGE_REOPEN_DELAY_INI	= ncicplc ((float)(R[R_DELAY_REOPEN]/1000.0));

		if (R[R_DELAY_POLLING_CONT]<=0)		CNT_DELAY_POLLING_CONT_INI	= ncicplc ((float)(CNT_DELAY_POLLING_CONT_INI_DEFAULT/1000.0));
		else								CNT_DELAY_POLLING_CONT_INI	= ncicplc ((float)(R[R_DELAY_POLLING_CONT]/1000.0));
	
		if (R[R_CNT_BRIDGE_CONTROL_WORD]) cnt_bridge_control_word = (ULONG) R[R_CNT_BRIDGE_CONTROL_WORD]; 
			
		R[R_CNT_CNTR_WORD] = cnt_bridge_control_word;

		start_cb_file = 0;

		cntDelayStart = NDELAY_FILE_LOG_CREATE;
	}
}

void contatori_bridge_0(void)
{

	if (RESET_ALL || RESET_MC)
	{
		CNT_ERROR_FAL	= 0;
	}

	tS(TS_RIT_CONTAORE,(unsigned char) 1);

	if(!RP_TSuppl[TS_RIT_CONTAORE]) return;

	switch (CNT_BRIDGE_STATE)
	{

		//________ Inizializzazione comunicazione ____________________

	case CNT_BRIDGE_STATE_INIT:
		if (!handle_BRIDGE)	CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_OPEN;
		else				CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_IDLE;
		break;
	case CNT_BRIDGE_STATE_OPEN:
		iosStringOpen.size = strlen (BRIDGE_ADDRESS);
		iosStringOpen.sz = BRIDGE_ADDRESS;
		ret_iosOpen_BRIDGE = iosOpen (&iosStringOpen, &handle_BRIDGE);
		if (ret_iosOpen_BRIDGE == RTPLC_STATUS_OK)			CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_IDLE;
		else if (RTPLC_STATUS_FAILED(ret_iosOpen_BRIDGE))	CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_ERR_OPENING;
		break;
	
	case CNT_BRIDGE_CHECK_IF_CLOSE:
		if (handle_BRIDGE) CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_CLOSE;
		else 
		{ 
			CNT_BRIDGE_REOPEN_DELAY = CNT_BRIDGE_REOPEN_DELAY_INI;	
			CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_WAIT_BEFOR_REOPEN;
		}
		break;
	case CNT_BRIDGE_STATE_CLOSE:
		ret_iosClose_BRIDGE = iosClose(handle_BRIDGE);
		if (ret_iosClose_BRIDGE == RTPLC_STATUS_OK)			
		{
			handle_BRIDGE = 0; 
			CNT_BRIDGE_REOPEN_DELAY = CNT_BRIDGE_REOPEN_DELAY_INI;
			CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_WAIT_BEFOR_REOPEN;
		}
		else if (RTPLC_STATUS_FAILED(ret_iosClose_BRIDGE)) CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_ERR_OPENING;
		break;
	case CNT_BRIDGE_STATE_WAIT_BEFOR_REOPEN:
		if (--CNT_BRIDGE_REOPEN_DELAY<0) CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_INIT;
		break;



		//_______ Inizializzazione del Bridge _____

		// Bridge vergine -> inizializza le 4 password
	case CNT_BRIDGE_STATE_INI_PASSWORD_1:
		//Scrittura password 1 default per sproteggere
		ULONG_data_write_BRIDGE = CNT_PASSWORD_BASE_1;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_1;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_INI_PASSWORD_2;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;
		//Scrittura password 2 default per sproteggere
	case CNT_BRIDGE_STATE_INI_PASSWORD_2:
		ULONG_data_write_BRIDGE = CNT_PASSWORD_BASE_2;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_2;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_INI_PASSWORD_3;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;
		//Scrittura password 3 default per sproteggere
	case CNT_BRIDGE_STATE_INI_PASSWORD_3:
		ULONG_data_write_BRIDGE = CNT_PASSWORD_BASE_3;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_3;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_INI_PASSWORD_4;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;
		//Scrittura password 4 default per sproteggere
	case CNT_BRIDGE_STATE_INI_PASSWORD_4:
		ULONG_data_write_BRIDGE = CNT_PASSWORD_BASE_4;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_4;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_SET_PASSWORD_1;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;

		//Scrittura password emmegisoft 1
	case CNT_BRIDGE_STATE_SET_PASSWORD_1:
		ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_1;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_1;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_SET_PASSWORD_2;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;
		//Scrittura password emmegisoft 2
	case CNT_BRIDGE_STATE_SET_PASSWORD_2:
		ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_2;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_2;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_SET_PASSWORD_3;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;
		//Scrittura password emmegisoft 3
	case CNT_BRIDGE_STATE_SET_PASSWORD_3:
		ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_3;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_3;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_SET_PASSWORD_4;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;
		//Scrittura password emmegisoft 4
	case CNT_BRIDGE_STATE_SET_PASSWORD_4:
		ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_4;

		CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_4;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_SET_CONTROL_WORD;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;

		//Scrittura tipo contatori
	case CNT_BRIDGE_STATE_SET_CONTROL_WORD:
		ULONG_data_write_BRIDGE = cnt_bridge_control_word;

		CNT_INDEX_TMP			= CNT_PDO_CONTROL_INDEX;
		CNT_SUBINDEX_TMP		= CNT_PDO_CONTROL_SUBINDEX;
		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_END_INI;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		break;

	case CNT_BRIDGE_STATE_END_INI:
		MM_CNT_MM_INDEX = (int) R[R_TYPE_MACHINE];
		CNT_BRIDGE_STATE_INFO_INIT_DONE_FMS	= 1;
		CNT_BRIDGE_STATE					= CNT_BRIDGE_STATE_IDLE;
		break;



	//___ Loop attesa comandi o eventi ______________________

	case CNT_BRIDGE_STATE_IDLE:
		{
			// Bridge vergine
			if ( ((int)(MM_CNT_MM_INDEX)) != ((int)(R[R_TYPE_MACHINE])) ) 
			{
				CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_INI_PASSWORD_1; 
				break;
			}

			if ((int)R[R_CNT_COMMAND]==CNT_COMMAND_SET_CONT)
			{
				R[R_CNT_COMMAND]	= 0;
				CNT_CONT_INDEX		= (USHORT) R[R_CNT_INDEX];

				//I primi 4 contatori non sono accessibili con questo comando
				if ((CNT_CONT_INDEX > CNT_MAX_NUM) || (CNT_CONT_INDEX <= 0) || (CNT_CONT_INDEX==1) || (CNT_CONT_INDEX==2) || (CNT_CONT_INDEX==3) || (CNT_CONT_INDEX==4))
				{
					R[R_CNT_RESULT]			= CNT_RESULT_COMMAND_KO;
					CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_ERR_COMMAND; 
				}
				else 
				{					
					time_or_step = ((int) (cnt_bridge_control_word >> (CNT_CONT_INDEX-1))) & ((int)1); 
					
					//Contatore a tempo
					if (time_or_step)	CNT_CONT_VALUE		= (ULONG) (R[R_CNT_VALUE] * CNT_CONVERSIONE);
					//Contatore a eventi
					else				CNT_CONT_VALUE		= (ULONG) (R[R_CNT_VALUE]);		
					
					R[R_CNT_RESULT]			= CNT_RESULT_COMMAND_STARTED;
					CNT_BRIDGE_STATE_TMP2	= CNT_BRIDGE_STATE_IDLE;
					CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_COMMAND_WRITE_START;
				}
				break;
			}

			if (CNT_COMMAND_2==CNT_COMMAND_SET_CONT)				
			{
				CNT_COMMAND_2 = 0;

				CNT_CONT_INDEX		= (USHORT) R[R_CNT_INDEX];


				if ((CNT_CONT_INDEX > CNT_MAX_NUM) || (CNT_CONT_INDEX <= 0))
				{
					R[R_CNT_RESULT]			= CNT_RESULT_COMMAND_KO;
					CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_ERR_COMMAND; 
				}
				else 
				{
					time_or_step = ((int) (cnt_bridge_control_word >> (CNT_CONT_INDEX-1))) & ((int)1); 
					
					//Contatore a tempo
					if (time_or_step)	CNT_CONT_VALUE		= (ULONG) (R[R_CNT_VALUE] * CNT_CONVERSIONE);
					//Contatore a eventi
					else				CNT_CONT_VALUE		= (ULONG) (R[R_CNT_VALUE]);

					R[R_CNT_RESULT]			= CNT_RESULT_COMMAND_STARTED;
					CNT_BRIDGE_STATE_TMP2	= CNT_BRIDGE_STATE_IDLE;
					CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_COMMAND_WRITE_START;
				}
				break;
			}
			else if (CNT_COMMAND_2==CNT_COMMAND_RESET_ALL)
			{
				CNT_COMMAND_2			= 0;
				R[R_CNT_RESULT]			= CNT_RESULT_COMMAND_STARTED;

				CNT_BRIDGE_STATE_TMP1	= CNT_BRIDGE_STATE_IDLE;
				CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_RESET_ALL_START;
				break;
			}

			//Lettura dei contatori
			if (--CNT_DELAY_POLLING_CONT < 0)
			{
				CNT_DELAY_POLLING_CONT	= CNT_DELAY_POLLING_CONT_INI;

				CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_READ_CONT_START;
			}
			break;
		}


		//_______ Comando lettura di tutti i contatori __________

	case CNT_BRIDGE_STATE_READ_CONT_START:
		CNT_CONT_INDEX			= 1;
		
		CNT_INDEX_TMP			= CNT_PDO_VALUE_INDEX;
		CNT_SUBINDEX_TMP		= ret_cnt_cont_subindex (CNT_CONT_INDEX);

		CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_READ_CONT_LOOP;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_READ;
		break;

	case CNT_BRIDGE_STATE_READ_CONT_LOOP:
		
		time_or_step = ((int) (cnt_bridge_control_word >> (CNT_CONT_INDEX-1))) & ((int)1); 
					
		//Contatore a tempo
		if (time_or_step)	R[R_CONTAORE_START+CNT_CONT_INDEX-1] = (double) ((double)ULONG_data_read_BRIDGE/CNT_CONVERSIONE);
		//Contatore a eventi
		else				R[R_CONTAORE_START+CNT_CONT_INDEX-1] = (double) (ULONG_data_read_BRIDGE);		

		if (++CNT_CONT_INDEX>CNT_MAX_NUM)
		{
			CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_IDLE;
			
			//Se non è mai stato fatto al termine del ritardo comanda la scrittura dei contatori su file
			if (cntDelayStart) 
				{
					if (!(--cntDelayStart))
					{
					contatori_bridge_create_string();
						start_cb_file = 1; //Comanda la scrittura dei contatori su file
					}
				}
		}
		else
		{
			CNT_INDEX_TMP			= CNT_PDO_VALUE_INDEX;
			CNT_SUBINDEX_TMP		= ret_cnt_cont_subindex (CNT_CONT_INDEX);

			CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_READ_CONT_LOOP;
			CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_READ;
		}
		break;


		//_______ Comando reset tutti i contatori __________

	case CNT_BRIDGE_STATE_RESET_ALL_START:
		CNT_CONT_INDEX = 1;
		CNT_CONT_VALUE = 0;

		CNT_BRIDGE_STATE_TMP2	= CNT_BRIDGE_STATE_RESET_ALL_LOOP;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_COMMAND_WRITE_START;
		break;

	case CNT_BRIDGE_STATE_RESET_ALL_LOOP:
		if (++CNT_CONT_INDEX > CNT_MAX_NUM) 
		{
			R[R_CNT_RESULT]			= CNT_RESULT_COMMAND_OK;
			CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_IDLE;
		}
		else 
		{
			CNT_BRIDGE_STATE_TMP2	= CNT_BRIDGE_STATE_RESET_ALL_LOOP;
			CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_COMMAND_WRITE_START;
		}
		break;



		//_______ Comando di base scrittura di un contatore _____

		//Sprotezione
	case CNT_BRIDGE_STATE_COMMAND_WRITE_START:
		{			
			switch (CNT_CONT_INDEX)
			{
			case 1:
			case 2:
			case 3:
			case 4:
				ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_1;
				CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_1;
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_2;
				CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_2;
				break;
			case 9:
			case 10:
			case 11:
			case 12:
				ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_3;
				CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_3;
				break;
			case 13:
			case 14:
			case 15:
			case 16:
				ULONG_data_write_BRIDGE = CNT_PASSWORD_EMMEGISOFT_4;
				CNT_SUBINDEX_TMP		= CNT_PDO_ACCESS_PASSWORD_SUBINDEX_4;
				break;
			}

			CNT_INDEX_TMP			= CNT_PDO_ACCESS_PASSWORD_INDEX;

			CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_COMMAND_WRITE_CONT;
			CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		}
		break;

		//Scrittura
	case CNT_BRIDGE_STATE_COMMAND_WRITE_CONT:
		{
			ULONG_data_write_BRIDGE = CNT_CONT_VALUE;

			CNT_INDEX_TMP			= CNT_PDO_VALUE_INDEX;
			CNT_SUBINDEX_TMP =  ret_cnt_cont_subindex (CNT_CONT_INDEX);

			CNT_BRIDGE_STATE_TMP3	= CNT_BRIDGE_STATE_COMMAND_WRITE_END;
			CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_WRITE;
		}
		break;
		
		//Termine
	case CNT_BRIDGE_STATE_COMMAND_WRITE_END:
		R[R_CNT_RESULT]			= CNT_RESULT_COMMAND_OK;
		CNT_BRIDGE_STATE		= CNT_BRIDGE_STATE_TMP2;
		break;



		//_______ Comando di base scrittura generico ____________
	case CNT_BRIDGE_STATE_WRITE:
		data_BRIDGE.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		data_BRIDGE.value.arr.data = &ULONG_data_write_BRIDGE;
		data_BRIDGE.value.arr.size = sizeof (ULONG_data_write_BRIDGE);
		write_result_BRIDGE = iosWrite (handle_BRIDGE, 1, CNT_INDEX_TMP, (UCHAR) CNT_SUBINDEX_TMP, 0, &data_BRIDGE, CNT_WRITE_TIMEOUT);		
		if (write_result_BRIDGE == RTPLC_STATUS_OK)			CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_TMP3; //Passa allo stato successivo
		else if	(RTPLC_STATUS_FAILED(write_result_BRIDGE))	CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_ERR_WRITING;
		break;


		//_______ Comando di base lettura generico ____________
	case CNT_BRIDGE_STATE_READ:
		data_BRIDGE.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		data_BRIDGE.value.arr.data = &ULONG_data_read_BRIDGE;
		data_BRIDGE.value.arr.size = sizeof (ULONG_data_read_BRIDGE);
		//par 1 = sdo
		read_result_BRIDGE = iosRead (handle_BRIDGE, 1, CNT_INDEX_TMP, (UCHAR) CNT_SUBINDEX_TMP, 0, &data_BRIDGE, &dimdata_read_BRIDGE, CNT_READ_TIMEOUT);
		if (read_result_BRIDGE == RTPLC_STATUS_OK)			CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_TMP3; //Passa allo stato successivo
		else if	(RTPLC_STATUS_FAILED(write_result_BRIDGE))	CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_ERR_READING;
		break;


		//________ ALLARMI RESETTABILI _________________
	case CNT_BRIDGE_STATE_ERR_OPENING:
		
		//Se i contatori non sono abilitati
		CNT_ERROR_FAL = 1;
		if (RESET_ALL || RESET_MC) {CNT_ERROR_FAL = 0; CNT_BRIDGE_STATE = CNT_BRIDGE_CHECK_IF_CLOSE;}
		break;

	case CNT_BRIDGE_STATE_ERR_READING:
	case CNT_BRIDGE_STATE_ERR_WRITING:
	case CNT_BRIDGE_STATE_ERR_COMMAND:
	case CNT_BRIDGE_STATE_ERR_CLOSING:

		CNT_ERROR_FAL = 1;
		if (RESET_ALL || RESET_MC) {CNT_ERROR_FAL = 0; CNT_BRIDGE_STATE = CNT_BRIDGE_STATE_IDLE;}
		break;


	}
}



int ret_cnt_cont_subindex (int cnt_cont_index)
{
	switch (cnt_cont_index)
	{
	case 1:
		return CNT_PDO_VALUE_SUBINDEX_1;
		break;
	case 2:
		return CNT_PDO_VALUE_SUBINDEX_2;
		break;
	case 3:
		return CNT_PDO_VALUE_SUBINDEX_3;
		break;
	case 4:
		return CNT_PDO_VALUE_SUBINDEX_4;
		break;
	case 5:
		return CNT_PDO_VALUE_SUBINDEX_5;
		break;
	case 6:
		return CNT_PDO_VALUE_SUBINDEX_6;
		break;
	case 7:
		return CNT_PDO_VALUE_SUBINDEX_7;
		break;
	case 8:
		return CNT_PDO_VALUE_SUBINDEX_8;
		break;
	case 9:
		return CNT_PDO_VALUE_SUBINDEX_9;
		break;
	case 10:
		return CNT_PDO_VALUE_SUBINDEX_10;
		break;
	case 11:
		return CNT_PDO_VALUE_SUBINDEX_11;
		break;
	case 12:
		return CNT_PDO_VALUE_SUBINDEX_12;
		break;
	case 13:
		return CNT_PDO_VALUE_SUBINDEX_13;
		break;
	case 14:
		return CNT_PDO_VALUE_SUBINDEX_14;
		break;
	case 15:
		return CNT_PDO_VALUE_SUBINDEX_15;
		break;
	case 16:
		return CNT_PDO_VALUE_SUBINDEX_16;
		break;
	default:
		return 0;
	}
}
