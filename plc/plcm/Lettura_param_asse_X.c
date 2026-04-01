/*
        --------------------------------------------------------------
        TITOLO:         LETTURA PARAMETRI ETHERCAT ASSE _X
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    read_params_asse_X(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:           
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           03-05-2020
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

	//DELTA_IA-ASDA_A2-E_UM_EN_20150430.pdf
	//6.3 Overview of Object Group 6000h

	//6041h VAR Statusword UNSIGNED16 RO
	//603Fh VAR Error Code UNSIGNED16 RO
	
*/

#include "all.inc"

// CASE_ETHERCAT_ASSE_X:
#define STATO_INI_ETH_ASSE_X            100
#define STATO_SET_TIME_WAIT_ETH_ASSE_X  110
#define STATO_WAIT_ETH_ASSE_X           120

#define STATO_READ_VERS_FIRMW_ASSE_X    200
#define STATO_READ_SUBVERS_FIRMW_ASSE_X 210

#define STATO_READ_STATUS_WORD_ASSE_X   300
#define STATO_READ_ERR_CODE_GR_ASSE_X   310
#define STATO_READ_ERR_CODE_NU_ASSE_X   320

#define STATO_READ_VOLT_BATTERY_ASSE_X  400
#define STATO_READ_LOAD_PERCENT_ASSE_X  410
#define STATO_READ_PEAK_LOAD_ASSE_X     420
#define STATO_READ_ABS_SYSTEM_ASSE_X    430

#define STATO_ERROR_ETH_ASSE_X          990
#define STATO_CLOSE_CANALE_ASSE_X      1000


// Canale di comunicazione dell'asse
ULONG Handle_asse_X;
RTPLC_STATUS ret_iosOpen_asse_X;
char *indirizzo_asse_X = IND_ETHERCAT_X;	
RTPLC_STRING RS_indirizzo_asse_X = {0};

// Lettura della versione firmware dell'asse
RTPLC_STATUS  FIRMW_ret_iosRead_asse_X;
ULONG         FIRMW_num_Byte_Letti_asse_X;
RTPLC_VARIANT FIRMW_buffer_letto_da_asse_X;
unsigned char FIRMW_byte_letto_da_asse_X[2] = {0};

// Lettura della sub-versione firmware dell'asse
RTPLC_STATUS  SUBFIRMW_ret_iosRead_asse_X;
ULONG         SUBFIRMW_num_Byte_Letti_asse_X;
RTPLC_VARIANT SUBFIRMW_buffer_letto_da_asse_X;
unsigned char SUBFIRMW_byte_letto_da_asse_X[4] = {0};

// Status word dell'asse
RTPLC_STATUS  ST_WO_ret_iosRead_asse_X;
ULONG         ST_WO_num_Byte_Letti_asse_X;
RTPLC_VARIANT ST_WO_buffer_letto_da_asse_X;
unsigned char ST_WO_byte_letto_da_asse_X[2] = {0};

// Error Code Group dell'asse
RTPLC_STATUS  E_C_G_ret_iosRead_asse_X;
ULONG         E_C_G_num_Byte_Letti_asse_X;
RTPLC_VARIANT E_C_G_buffer_letto_da_asse_X;
unsigned char E_C_G_byte_letto_da_asse_X[2] = {0};

// Error Code Number dell'asse
RTPLC_STATUS  E_C_N_ret_iosRead_asse_X;
ULONG         E_C_N_num_Byte_Letti_asse_X;
RTPLC_VARIANT E_C_N_buffer_letto_da_asse_X;
unsigned char E_C_N_byte_letto_da_asse_X[2] = {0};

// Oggetti del nuovo firmware dell'asse
RTPLC_STATUS  OBJECT1_ret_iosRead_asse_X;
ULONG         OBJECT1_num_Byte_Letti_asse_X;
RTPLC_VARIANT OBJECT1_buffer_letto_da_asse_X;
unsigned char OBJECT1_byte_letto_da_asse_X[4] = {0};

// Oggetti del nuovo firmware dell'asse
RTPLC_STATUS  OBJECT2_ret_iosRead_asse_X;
ULONG         OBJECT2_num_Byte_Letti_asse_X;
RTPLC_VARIANT OBJECT2_buffer_letto_da_asse_X;
unsigned char OBJECT2_byte_letto_da_asse_X[4] = {0};

// Oggetti del nuovo firmware dell'asse
RTPLC_STATUS  OBJECT3_ret_iosRead_asse_X;
ULONG         OBJECT3_num_Byte_Letti_asse_X;
RTPLC_VARIANT OBJECT3_buffer_letto_da_asse_X;
unsigned char OBJECT3_byte_letto_da_asse_X[4] = {0};

// Oggetti del nuovo firmware dell'asse
RTPLC_STATUS  OBJECT4_ret_iosRead_asse_X;
ULONG         OBJECT4_num_Byte_Letti_asse_X;
RTPLC_VARIANT OBJECT4_buffer_letto_da_asse_X;
unsigned char OBJECT4_byte_letto_da_asse_X[2] = {0};


void read_params_asse_X(void)
{

	if( !(AF_ASSE_0_CH_NUM_TECH01_ADDRESS>0.5) && (R[R_ABIL_LETTURA_STATO_ASSE_X]>0.5) && CONF_ASSE_X)
	{
		static short int TIME_COUNTER_ASSE_X = 0;
		double Double_SubVers_Firmware_Asse_X, App_SubVers_Firmware_Asse_X;
		int Int_SubVers_Firmware_Asse_X;

		if(PON)
		{
			Handle_asse_X = 0;
			memset(&RS_indirizzo_asse_X, 0, sizeof(RS_indirizzo_asse_X));
			RS_indirizzo_asse_X.size = _strlen(indirizzo_asse_X);
			RS_indirizzo_asse_X.sz = indirizzo_asse_X;
		
			CASE_ETHERCAT_ASSE_X = STATO_INI_ETH_ASSE_X;
		}

		if(DP_RIT_PON)
		{
			R[R_MAX_PERCENT_LOAD_ASSE_X] = (double) 0.0;
		}

		FIRMW_buffer_letto_da_asse_X.value.arr.data = FIRMW_byte_letto_da_asse_X;
		FIRMW_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		SUBFIRMW_buffer_letto_da_asse_X.value.arr.data = SUBFIRMW_byte_letto_da_asse_X;
		SUBFIRMW_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;		
		
		ST_WO_buffer_letto_da_asse_X.value.arr.data = ST_WO_byte_letto_da_asse_X;
		ST_WO_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		E_C_G_buffer_letto_da_asse_X.value.arr.data = E_C_G_byte_letto_da_asse_X;
		E_C_G_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		E_C_N_buffer_letto_da_asse_X.value.arr.data = E_C_N_byte_letto_da_asse_X;
		E_C_N_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		OBJECT1_buffer_letto_da_asse_X.value.arr.data = OBJECT1_byte_letto_da_asse_X;
		OBJECT1_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		OBJECT2_buffer_letto_da_asse_X.value.arr.data = OBJECT2_byte_letto_da_asse_X;
		OBJECT2_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		OBJECT3_buffer_letto_da_asse_X.value.arr.data = OBJECT3_byte_letto_da_asse_X;
		OBJECT3_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		OBJECT4_buffer_letto_da_asse_X.value.arr.data = OBJECT4_byte_letto_da_asse_X;
		OBJECT4_buffer_letto_da_asse_X.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		switch (CASE_ETHERCAT_ASSE_X)
		{

		case STATO_INI_ETH_ASSE_X:  // apertura del canale relativo all'asse: iosOpen
			{
					ret_iosOpen_asse_X = iosOpen(&RS_indirizzo_asse_X, &Handle_asse_X);
					
					if (ret_iosOpen_asse_X == RTPLC_STATUS_OK) 
					{
						//rtplctrace4(1,_T("Handle_asse_X = %d"),Handle_asse_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Apertura canale Ethercat indirizzo_1002-> ret_iosOpen_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,ret_iosOpen_asse_X);
						
						CASE_ETHERCAT_ASSE_X = STATO_SET_TIME_WAIT_ETH_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosOpen_asse_X)) 
					{
						//rtplctrace4(1,_T("RS_indirizzo_asse_X.sz = %s, RS_indirizzo_asse_X.size =%d"),RS_indirizzo_asse_X.sz, RS_indirizzo_asse_X.size);
						//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1002-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;

		case STATO_SET_TIME_WAIT_ETH_ASSE_X:  // setta il ritardo dopo cui fare nuovamente la lettura
			{
				if(R[R_NCICLI_DELAY_READ_OBJECT]<= 0.0)
				{
					TIME_COUNTER_ASSE_X = 1;
				}
				else
				{
					TIME_COUNTER_ASSE_X = (unsigned int) R[R_NCICLI_DELAY_READ_OBJECT];
				}						

				CASE_ETHERCAT_ASSE_X = STATO_WAIT_ETH_ASSE_X;
			}
			break;

		case STATO_WAIT_ETH_ASSE_X:  // attesa abilitazione lettura stato asse
			{
					if(RP_PON && (TIME_COUNTER_ASSE_X > 0))
						TIME_COUNTER_ASSE_X--;
					
					if( DP_RIT_PON || (TIME_COUNTER_ASSE_X<=0) )
					{	
						if(!READ_FIRMW_ESEG_ASSE_X)  // se lettura versione firmware non ancora eseguita
							CASE_ETHERCAT_ASSE_X = STATO_READ_VERS_FIRMW_ASSE_X;
						else
							CASE_ETHERCAT_ASSE_X = STATO_READ_STATUS_WORD_ASSE_X;						
					}
			}
			break;
			
		// Lettura oggetto 0x2000 (par P0-00): lettura della versione firmware dell'azionamento
		case STATO_READ_VERS_FIRMW_ASSE_X:
			{
					FIRMW_buffer_letto_da_asse_X.value.arr.size = 2;
					FIRMW_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x2000, 0, 0, &FIRMW_buffer_letto_da_asse_X, &FIRMW_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (FIRMW_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Vers_Firmware_Asse_X = (unsigned int)(  ( (FIRMW_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(FIRMW_byte_letto_da_asse_X[0] & 0xFF)   );

						//rtplctrace4(1,_T("%x %x = FIRMW_byte_letto_da_asse_X[1].FIRMW_byte_letto_da_asse_X[0]"),FIRMW_byte_letto_da_asse_X[1],FIRMW_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x2000-> FIRMW_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,FIRMW_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_READ_SUBVERS_FIRMW_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(FIRMW_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x2000-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x2000-> FIRMW_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,FIRMW_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;
			
		// Lettura oggetto 0x2500 (par P5-00): lettura della sub-versione firmware dell'azionamento (i 16 bit meno significativi)
		case STATO_READ_SUBVERS_FIRMW_ASSE_X:
			{
					SUBFIRMW_buffer_letto_da_asse_X.value.arr.size = 4;
					SUBFIRMW_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x2500, 0, 0, &SUBFIRMW_buffer_letto_da_asse_X, &SUBFIRMW_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (SUBFIRMW_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						SubVers_Firmware_Asse_X = (unsigned long)( ( (SUBFIRMW_byte_letto_da_asse_X[3]<<24) & 0xFF000000) + ( (SUBFIRMW_byte_letto_da_asse_X[2]<<16) & 0xFF0000) +  
							                                ( (SUBFIRMW_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(SUBFIRMW_byte_letto_da_asse_X[0] & 0xFF)   );

						Double_SubVers_Firmware_Asse_X = ((double) SubVers_Firmware_Asse_X)/10000.0;
						Int_SubVers_Firmware_Asse_X = (unsigned int) Double_SubVers_Firmware_Asse_X;

						App_SubVers_Firmware_Asse_X = Double_SubVers_Firmware_Asse_X - (double) Int_SubVers_Firmware_Asse_X;

						//La lettura versione firmware e subfirmware deve dare come risultato minimo 1643.8534
						R[R_VERS_FIRMW_ASSE_X] = (  ( ((double) Vers_Firmware_Asse_X) / 1.0) + App_SubVers_Firmware_Asse_X  );
						
						//rtplctrace4(1,_T("%x %x %x %x = SUBFIRMW_byte_letto_da_asse_X[3].SUBFIRMW_byte_letto_da_asse_X[2].SUBFIRMW_byte_letto_da_asse_X[1].SUBFIRMW_byte_letto_da_asse_X[0]"),
						//	             SUBFIRMW_byte_letto_da_asse_X[3],SUBFIRMW_byte_letto_da_asse_X[2],SUBFIRMW_byte_letto_da_asse_X[1],SUBFIRMW_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x2500-> SUBFIRMW_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,SUBFIRMW_ret_iosRead_asse_X);

						READ_FIRMW_ESEG_ASSE_X = 1;
						
						if(R[R_VERS_FIRMW_ASSE_X] >= VERS_MIN_FIRMW_DELTA)
							CASE_ETHERCAT_ASSE_X = STATO_READ_STATUS_WORD_ASSE_X;
						else
							CASE_ETHERCAT_ASSE_X = STATO_CLOSE_CANALE_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(SUBFIRMW_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x2500-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x2500-> SUBFIRMW_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,SUBFIRMW_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;			

		case STATO_READ_STATUS_WORD_ASSE_X:
			{
					ST_WO_buffer_letto_da_asse_X.value.arr.size = 2;
					ST_WO_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x6041, 0, 0, &ST_WO_buffer_letto_da_asse_X, &ST_WO_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// PDO
					if (ST_WO_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Status_Word_Asse_X = (unsigned int)( (ST_WO_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(ST_WO_byte_letto_da_asse_X[0] & 0x00FF);

						//rtplctrace4(1,_T("%x %x = ST_WO_byte_letto_da_asse_X[1].ST_WO_byte_letto_da_asse_X[0]"),ST_WO_byte_letto_da_asse_X[1],ST_WO_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x6041-> ST_WO_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,ST_WO_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_READ_ERR_CODE_GR_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(ST_WO_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x6041-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;

		case STATO_READ_ERR_CODE_GR_ASSE_X:
			{
					E_C_G_buffer_letto_da_asse_X.value.arr.size = 2;
					E_C_G_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x603F, 0, 0, &E_C_G_buffer_letto_da_asse_X, &E_C_G_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (E_C_G_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Error_Code_Group_Asse_X = (unsigned int)( (E_C_G_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(E_C_G_byte_letto_da_asse_X[0] & 0x00FF);

						//rtplctrace4(1,_T("%x %x = E_C_G_byte_letto_da_asse_X[1].E_C_G_byte_letto_da_asse_X[0]"),E_C_G_byte_letto_da_asse_X[1],E_C_G_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x603F-> E_C_G_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,E_C_G_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_READ_ERR_CODE_NU_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(E_C_G_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x603F-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x603F-> E_C_G_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,E_C_G_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;


		case STATO_READ_ERR_CODE_NU_ASSE_X:
			{
					E_C_N_buffer_letto_da_asse_X.value.arr.size = 2;
					E_C_N_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x2001, 0, 0, &E_C_N_buffer_letto_da_asse_X, &E_C_N_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (E_C_N_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Error_Code_Num_Asse_X = (unsigned int)( (E_C_N_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(E_C_N_byte_letto_da_asse_X[0] & 0x00FF);

						//rtplctrace4(1,_T("%x %x = E_C_N_byte_letto_da_asse_X[1].E_C_N_byte_letto_da_asse_X[0]"),E_C_N_byte_letto_da_asse_X[1],E_C_N_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x2001-> E_C_N_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,E_C_N_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_READ_VOLT_BATTERY_ASSE_X;

					}
					else if (RTPLC_STATUS_FAILED(E_C_N_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x2001-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x2001-> E_C_N_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,E_C_N_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;

		// Lettura oggetto 0x2009 (par P0-09): livello di tensione attuale della batteria	
		case STATO_READ_VOLT_BATTERY_ASSE_X:
			{
					OBJECT1_buffer_letto_da_asse_X.value.arr.size = 4;
					OBJECT1_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x2009, 0, 0, &OBJECT1_buffer_letto_da_asse_X, &OBJECT1_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (OBJECT1_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Volt_Batteria_Act_Asse_X = (unsigned long)(  ( (OBJECT1_byte_letto_da_asse_X[3]<<24) & 0xFF000000) + ( (OBJECT1_byte_letto_da_asse_X[2]<<16) & 0xFF0000) + 
						                                               ( (OBJECT1_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(OBJECT1_byte_letto_da_asse_X[0] & 0xFF)   );

						R[R_VOLT_BATTERIA_ACT_ASSE_X] = ((double) Volt_Batteria_Act_Asse_X) / 10.0;
						
						//rtplctrace4(1,_T("%x %x %x %x = OBJECT1_byte_letto_da_asse_X[3].OBJECT1_byte_letto_da_asse_X[2].OBJECT1_byte_letto_da_asse_X[1].OBJECT1_byte_letto_da_asse_X[0]"),
						//	             OBJECT1_byte_letto_da_asse_X[3],OBJECT1_byte_letto_da_asse_X[2],OBJECT1_byte_letto_da_asse_X[1],OBJECT1_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x2009-> OBJECT1_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT1_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_READ_LOAD_PERCENT_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(OBJECT1_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x2009-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x2009-> OBJECT1_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT1_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;

		// Lettura oggetto 0x200A (par P0-10): load %	
		case STATO_READ_LOAD_PERCENT_ASSE_X:
			{
					OBJECT2_buffer_letto_da_asse_X.value.arr.size = 4;
					OBJECT2_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x200A, 0, 0, &OBJECT2_buffer_letto_da_asse_X, &OBJECT2_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (OBJECT2_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Percent_Load_Asse_X = (unsigned long)(  ( (OBJECT2_byte_letto_da_asse_X[3]<<24) & 0xFF000000) + ( (OBJECT2_byte_letto_da_asse_X[2]<<16) & 0xFF0000) + 
						                                          ( (OBJECT2_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(OBJECT2_byte_letto_da_asse_X[0] & 0xFF)   );

						R[R_PERCENT_LOAD_ASSE_X] = ((double) Percent_Load_Asse_X) / 1.0;
						
						if(R[R_PERCENT_LOAD_ASSE_X]>R[R_MAX_PERCENT_LOAD_ASSE_X]) R[R_MAX_PERCENT_LOAD_ASSE_X] = R[R_PERCENT_LOAD_ASSE_X];
						
						//rtplctrace4(1,_T("%x %x %x %x = OBJECT2_byte_letto_da_asse_X[3].OBJECT2_byte_letto_da_asse_X[2].OBJECT2_byte_letto_da_asse_X[1].OBJECT2_byte_letto_da_asse_X[0]"),
						//	             OBJECT2_byte_letto_da_asse_X[3],OBJECT2_byte_letto_da_asse_X[2],OBJECT2_byte_letto_da_asse_X[1],OBJECT2_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x200A-> OBJECT2_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT2_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_READ_PEAK_LOAD_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(OBJECT2_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x200A-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x200A-> OBJECT2_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT2_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;

		// Lettura oggetto 0x200B (par P0-11): peak load
		case STATO_READ_PEAK_LOAD_ASSE_X:
			{
					OBJECT3_buffer_letto_da_asse_X.value.arr.size = 4;
					OBJECT3_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x200B, 0, 0, &OBJECT3_buffer_letto_da_asse_X, &OBJECT3_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (OBJECT3_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Peak_Load_Asse_X = (unsigned long)(  ( (OBJECT3_byte_letto_da_asse_X[3]<<24) & 0xFF000000) + ( (OBJECT3_byte_letto_da_asse_X[2]<<16) & 0xFF0000) + 
						                                       ( (OBJECT3_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(OBJECT3_byte_letto_da_asse_X[0] & 0xFF)   );
						
						R[R_PEAK_LOAD_ASSE_X] = ((double) Peak_Load_Asse_X) / 1.0;
						
						//rtplctrace4(1,_T("%x %x %x %x = OBJECT3_byte_letto_da_asse_X[3].OBJECT3_byte_letto_da_asse_X[2].OBJECT3_byte_letto_da_asse_X[1].OBJECT3_byte_letto_da_asse_X[0]"),
						//	             OBJECT3_byte_letto_da_asse_X[3],OBJECT3_byte_letto_da_asse_X[2],OBJECT3_byte_letto_da_asse_X[1],OBJECT3_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x200B-> OBJECT3_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT3_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_READ_ABS_SYSTEM_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(OBJECT3_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x200B-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x200B-> OBJECT3_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT3_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;

		// Lettura oggetto 0x2032 (par P0-50): lettura dello stato del sistema di coordinate assolute
		case STATO_READ_ABS_SYSTEM_ASSE_X:
			{
					OBJECT4_buffer_letto_da_asse_X.value.arr.size = 2;
					OBJECT4_ret_iosRead_asse_X = iosRead(Handle_asse_X, 1, 0x2032, 0, 0, &OBJECT4_buffer_letto_da_asse_X, &OBJECT4_num_Byte_Letti_asse_X, RW_ETH_TIMEOUT);	// SDO
					if (OBJECT4_ret_iosRead_asse_X == RTPLC_STATUS_OK) 
					{
						Abs_System_Asse_X = (unsigned int)(  ( (OBJECT4_byte_letto_da_asse_X[1]<<8) & 0xFF00)+(OBJECT4_byte_letto_da_asse_X[0] & 0xFF)   );
						
						//rtplctrace4(1,_T("%x %x = OBJECT4_byte_letto_da_asse_X[1].OBJECT4_byte_letto_da_asse_X[0]"),OBJECT4_byte_letto_da_asse_X[1],OBJECT4_byte_letto_da_asse_X[0]);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Lettura Ethercat SDO=0x2032-> OBJECT4_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT4_ret_iosRead_asse_X);

						CASE_ETHERCAT_ASSE_X = STATO_SET_TIME_WAIT_ETH_ASSE_X;
					}
					else if (RTPLC_STATUS_FAILED(OBJECT4_ret_iosRead_asse_X)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x2032-> CASE_ETHERCAT_ASSE_X=(%d)"),CASE_ETHERCAT_ASSE_X);
						//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***KO: Lettura Ethercat SDO=0x2032-> OBJECT4_ret_iosRead_asse_X=(%d)"),CASE_ETHERCAT_ASSE_X,OBJECT4_ret_iosRead_asse_X);
						CASE_ETHERCAT_ASSE_X = STATO_ERROR_ETH_ASSE_X;
					}
			}
			break;

		case STATO_ERROR_ETH_ASSE_X:
			{
				READ_FIRMW_ESEG_ASSE_X = 0;
				if(Handle_asse_X != 0)
				{
					iosClose(Handle_asse_X);
					Handle_asse_X = 0;
					//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Chiusura canale Ethercat indirizzo_1002-"),CASE_ETHERCAT_ASSE_X);
					CASE_ETHERCAT_ASSE_X = STATO_INI_ETH_ASSE_X;
				}
				else
				{
					CASE_ETHERCAT_ASSE_X = STATO_INI_ETH_ASSE_X;
				}
			}
			break;
			
		case STATO_CLOSE_CANALE_ASSE_X:
			{
				if(Handle_asse_X != 0)
				{
					iosClose(Handle_asse_X);
					Handle_asse_X = 0;
					//rtplctrace4(1,_T("CASE_ETHERCAT_ASSE_X=%d ***OK: Versione firmware < 1643.8534 "),CASE_ETHERCAT_ASSE_X);
				}
			}
			break;
		}
	}
	else if( (AF_ASSE_0_CH_NUM_TECH01_ADDRESS>0.5) && CONF_ASSE_X )
	{
		if(PON)
		{
			// Abilita l'errore di comunicazione con azionamento asse X. Se il plc iec non riesce più a comunicare con azionamento passerà
			// codice di errore 9999 in AF_NUM_ERROR_ASSE_0. IL plc macchina deve settare un allarme ASSE_0_COM_ERROR_FAL:
			// - con la COM su azionamento viene solo letto lo stato allora l'allarme viene dato solo una volta dopo l'accensione,
			//   dopo si consente di resettarlo e non potrà più ricomparire fino alla prossima riaccensione della macchina
			ENABLE_ASSE_0_COM_ERROR = 1;
		}

		// Definisco timer per ritardo positivo su ENABLE_ASSE_0_COM_ERROR, evitiamo di prendere dei falsi allarmi di comunicazione su COM
		// quando il CN è appena andato in start
		tS(TS_RIT_ENABLE_ASSE_0_COM_ERROR, (unsigned char) ENABLE_ASSE_0_COM_ERROR);

		if(RESET_ALL || RESET_MC)
		{
			ASSE_0_COM_ERROR_FAL = 0;
		}
		// Nel caso delle macchine multicanale per gli assi condivisi il plc macchina deve 
		// modificare la variabile AF_ASSE_0_CH_NUM_TECH00_ADDRESS con indicazione del canale e del numero asse

		// *** Variabili di scambio con il plc iec
        R[R_VERS_FIRMW_ASSE_X] = AF_VERS_FW_ASSE_0;
		Status_Word_Asse_X = (unsigned int) AF_STATUS_WORD_ASSE_0;
		Error_Code_Group_Asse_X = (unsigned short) AF_ERROR_CODE_GROUP_ASSE_0;
		Error_Code_Num_Asse_X = (short int) AF_NUM_ERROR_ASSE_0;
		R[R_VOLT_BATTERIA_ACT_ASSE_X] = AF_VOLT_BATTERIA_ASSE_0;
		R[R_PERCENT_LOAD_ASSE_X] = AF_PERCENT_LOAD_ASSE_0;

		if(AF_PERCENT_LOAD_ASSE_0>R[R_MAX_PERCENT_LOAD_ASSE_X]) 
			R[R_MAX_PERCENT_LOAD_ASSE_X] = AF_PERCENT_LOAD_ASSE_0;

		if( RP_TSuppl[TS_RIT_ENABLE_ASSE_0_COM_ERROR] && ((Error_Code_Num_Asse_X > 9998) && (Error_Code_Num_Asse_X < 10000)) )
		{
			ENABLE_ASSE_0_COM_ERROR = 0;    // disabilita allarme di comunicazione COM, l'allarme potrà ricomparire solo dopo il prossimo restart
			ASSE_0_COM_ERROR_FAL = 1;
		}

		// ****** SET dell'indicazione al plc iec di asse che si muove in G0 (ovvero alla massima velocità ***********
		if(RP_PON && !READ_SETTING_ASSE_X_ESEG)
		{
			read_var (VL_FLOT, 4054, -1, AX_X_CH0, &APP_VEL_MAX_ASSE_X);      /* V4054/0 = velocita' massima (mm/ciclo assi) asse X in taratura */
			VEL_MAX_ASSE_X = (APP_VEL_MAX_ASSE_X / CICLO_ASSI) * 60;          // VEL_MAX_ASSE_X = velocità massima asse X espressa in mm/min
			READ_SETTING_ASSE_X_ESEG = 1;
		}

		// Reset flag Asse X si sta muovendo in G0
		AF_MOVING_IN_G0_ASSE_0 = 0;
				
		// Lettura velocità attuale assi:
		read_var (VL_FLOT, 6058, -1, AX_X_CH0, &APP_VEL_ACT_ASSE_X);            /* V4058/0 = velocita' attuale (mm/ciclo assi) asse X */
		VEL_ACT_ASSE_X = (APP_VEL_ACT_ASSE_X / CICLO_ASSI) * 60;          // VEL_ACT_ASSE_X = velocità attuale asse X espressa in mm/min

		AF_VEL_ACT_ASSE_0 = (VEL_ACT_ASSE_X / 60);   // AF_VEL_ACT_ASSE_0 = velocità passata al plc iec in mm/s

		// Set del flag di asse che si sta muovendo in G0 (considero l'asse in G0 se la sua velocità è maggiore del 95% di quella massima
		if(RP_PON && READ_SETTING_ASSE_X_ESEG && (ABS(VEL_ACT_ASSE_X) > (0.95 * VEL_MAX_ASSE_X)))   
			AF_MOVING_IN_G0_ASSE_0 = 1;  // Asse X si sta muovendo in G0

	}

}