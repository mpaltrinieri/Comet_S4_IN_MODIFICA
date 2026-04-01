/*
        --------------------------------------------------------------
        TITOLO:         MINIMOTOR ETHERCAT
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Lettura corrente-tensione da Minimotor
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    read_SDO_minimotor(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:           
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        XTE 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           30-01-2020
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include "all.inc"

#define STATO_IDLE_ETH_MINIMOTOR            0

#define STATO_INI_ETH_MINIMOTOR           100
#define STATO_SET_TIME_WAIT_ETH_MINIMOTOR 110
#define STATO_WAIT_ETH_MINIMOTOR          120

#define STATO_READIN1_ETH_MINIMOTOR       300
#define STATO_READIN2_ETH_MINIMOTOR       310
#define STATO_READIN3_ETH_MINIMOTOR       320
#define STATO_READIN4_ETH_MINIMOTOR       330
#define STATO_READIN5_ETH_MINIMOTOR       340

#define STATO_ERROR_ETH_MINIMOTOR         990

//#define IND_ETHERCAT_M07      "Ethercat|1025"
//#define IND_ETHERCAT_M08      "Ethercat|1022"
//#define IND_ETHERCAT_M09      "Ethercat|1019"
#define IND_ETHERCAT_M10      "Ethercat|1016"
#define IND_ETHERCAT_M11      "Ethercat|1013"
#define IND_ETHERCAT_M12      "Ethercat|1010"
#define IND_ETHERCAT_M13      "Ethercat|1011"
#define IND_ETHERCAT_M14      "Ethercat|1014"
#define IND_ETHERCAT_M15      "Ethercat|1017"
//#define IND_ETHERCAT_M16      "Ethercat|1020"
//#define IND_ETHERCAT_M17      "Ethercat|1023"
//#define IND_ETHERCAT_M18      "Ethercat|1026"

//unsigned char dataRead1_M07[2], dataRead2_M07[2], dataRead3_M07[4], dataRead4_M07[2];
//unsigned char dataRead1_M08[2], dataRead2_M08[2], dataRead3_M08[4], dataRead4_M08[2];
//unsigned char dataRead1_M09[2], dataRead2_M09[2], dataRead3_M09[4], dataRead4_M09[2];
unsigned char dataRead1_M10[2], dataRead2_M10[2], dataRead3_M10[4], dataRead4_M10[2];
unsigned char dataRead1_M11[2], dataRead2_M11[2], dataRead3_M11[4], dataRead4_M11[2];
unsigned char dataRead1_M12[2], dataRead2_M12[2], dataRead3_M12[4], dataRead4_M12[2];
unsigned char dataRead1_M13[2], dataRead2_M13[2], dataRead3_M13[4], dataRead4_M13[2];
unsigned char dataRead1_M14[2], dataRead2_M14[2], dataRead3_M14[4], dataRead4_M14[2];
unsigned char dataRead1_M15[2], dataRead2_M15[2], dataRead3_M15[4], dataRead4_M15[2];
//unsigned char dataRead1_M16[2], dataRead2_M16[2], dataRead3_M16[4], dataRead4_M16[2];
//unsigned char dataRead1_M17[2], dataRead2_M17[2], dataRead3_M17[4], dataRead4_M17[2];
//unsigned char dataRead1_M18[2], dataRead2_M18[2], dataRead3_M18[4], dataRead4_M18[2];

//RTPLC_VARIANT inReadBuffer1_M07, inReadBuffer2_M07, inReadBuffer3_M07, inReadBuffer4_M07;
//RTPLC_VARIANT inReadBuffer1_M08, inReadBuffer2_M08, inReadBuffer3_M08, inReadBuffer4_M08;
//RTPLC_VARIANT inReadBuffer1_M09, inReadBuffer2_M09, inReadBuffer3_M09, inReadBuffer4_M09;
RTPLC_VARIANT inReadBuffer1_M10, inReadBuffer2_M10, inReadBuffer3_M10, inReadBuffer4_M10;
RTPLC_VARIANT inReadBuffer1_M11, inReadBuffer2_M11, inReadBuffer3_M11, inReadBuffer4_M11;
RTPLC_VARIANT inReadBuffer1_M12, inReadBuffer2_M12, inReadBuffer3_M12, inReadBuffer4_M12;
RTPLC_VARIANT inReadBuffer1_M13, inReadBuffer2_M13, inReadBuffer3_M13, inReadBuffer4_M13;
RTPLC_VARIANT inReadBuffer1_M14, inReadBuffer2_M14, inReadBuffer3_M14, inReadBuffer4_M14;
RTPLC_VARIANT inReadBuffer1_M15, inReadBuffer2_M15, inReadBuffer3_M15, inReadBuffer4_M15;
//RTPLC_VARIANT inReadBuffer1_M16, inReadBuffer2_M16, inReadBuffer3_M16, inReadBuffer4_M16;
//RTPLC_VARIANT inReadBuffer1_M17, inReadBuffer2_M17, inReadBuffer3_M17, inReadBuffer4_M17;
//RTPLC_VARIANT inReadBuffer1_M18, inReadBuffer2_M18, inReadBuffer3_M18, inReadBuffer4_M18;

//ULONG numByteRead1_M07, numByteRead2_M07, numByteRead3_M07, numByteRead4_M07;
//ULONG numByteRead1_M08, numByteRead2_M08, numByteRead3_M08, numByteRead4_M08;
//ULONG numByteRead1_M09, numByteRead2_M09, numByteRead3_M09, numByteRead4_M09;
ULONG numByteRead1_M10, numByteRead2_M10, numByteRead3_M10, numByteRead4_M10;
ULONG numByteRead1_M11, numByteRead2_M11, numByteRead3_M11, numByteRead4_M11;
ULONG numByteRead1_M12, numByteRead2_M12, numByteRead3_M12, numByteRead4_M12;
ULONG numByteRead1_M13, numByteRead2_M13, numByteRead3_M13, numByteRead4_M13;
ULONG numByteRead1_M14, numByteRead2_M14, numByteRead3_M14, numByteRead4_M14;
ULONG numByteRead1_M15, numByteRead2_M15, numByteRead3_M15, numByteRead4_M15;
//ULONG numByteRead1_M16, numByteRead2_M16, numByteRead3_M16, numByteRead4_M16;
//ULONG numByteRead1_M17, numByteRead2_M17, numByteRead3_M17, numByteRead4_M17;
//ULONG numByteRead1_M18, numByteRead2_M18, numByteRead3_M18, numByteRead4_M18;
//
//RTPLC_STATUS ret_iosOpen_Minimotor_M07, ret_iosRead_Minimotor_M07;
//RTPLC_STATUS ret_iosOpen_Minimotor_M08, ret_iosRead_Minimotor_M08;
//RTPLC_STATUS ret_iosOpen_Minimotor_M09, ret_iosRead_Minimotor_M09;
RTPLC_STATUS ret_iosOpen_Minimotor_M10, ret_iosRead_Minimotor_M10;
RTPLC_STATUS ret_iosOpen_Minimotor_M11, ret_iosRead_Minimotor_M11;
RTPLC_STATUS ret_iosOpen_Minimotor_M12, ret_iosRead_Minimotor_M12;
RTPLC_STATUS ret_iosOpen_Minimotor_M13, ret_iosRead_Minimotor_M13;
RTPLC_STATUS ret_iosOpen_Minimotor_M14, ret_iosRead_Minimotor_M14;
RTPLC_STATUS ret_iosOpen_Minimotor_M15, ret_iosRead_Minimotor_M15;
//RTPLC_STATUS ret_iosOpen_Minimotor_M16, ret_iosRead_Minimotor_M16;
//RTPLC_STATUS ret_iosOpen_Minimotor_M17, ret_iosRead_Minimotor_M17;
//RTPLC_STATUS ret_iosOpen_Minimotor_M18, ret_iosRead_Minimotor_M18;

void read_SDO_minimotor()
{

	//if(CONF_ASSE_M07)
	//{
	//	static ULONG minimotorHandle = 0;
	//	static RTPLC_STRING buffer_str = {0};
	//	static char *buffer = IND_ETHERCAT_M07;
	//	static short int TIME_COUNTER_M07 = 0;
	//	
	//	inReadBuffer1_M07.value.arr.data = dataRead1_M07;
	//	inReadBuffer1_M07.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
	//	
	//	inReadBuffer2_M07.value.arr.data = dataRead2_M07;
	//	inReadBuffer2_M07.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer3_M07.value.arr.data = dataRead3_M07;
	//	inReadBuffer3_M07.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer4_M07.value.arr.data = dataRead4_M07;
	//	inReadBuffer4_M07.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	switch (CASE_ECAT_M07_MINIMOTOR)
	//	{
	//	case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
	//		{
	//			if(PON)
	//			{
	//				memset(&buffer_str, 0, sizeof(buffer_str));
	//				buffer_str.size = _strlen(buffer);
	//				buffer_str.sz = buffer;
	//			}
	//			
	//			if(O_MOV_M07 && (R[R_ABIL_READ_SDO_M07]>0.5))
	//			{
	//				CASE_ECAT_M07_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//		}
	//		break;

	//	case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
	//		{
	//				ret_iosOpen_Minimotor_M07 = iosOpen(&buffer_str, &minimotorHandle);
	//				if (ret_iosOpen_Minimotor_M07 == RTPLC_STATUS_OK) 
	//				{
	//					//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
	//					//rtplctrace4(1,_T("CASE_ECAT_M07_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1025-> ret_iosOpen_Minimotor_M07=(%d)"),CASE_ECAT_M07_MINIMOTOR,ret_iosOpen_Minimotor_M07);

	//					R[R_MAX_CURRENT_M07] = -1000.0;
	//					R[R_MIN_CURRENT_M07] = 1000.0;

	//					R[R_MAX_VOLT_M07] = -1000.0;
	//					R[R_MIN_VOLT_M07] = 1000.0;
	//					
	//					CASE_ECAT_M07_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M07)) 
	//				{
	//					//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
	//					//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1025-> CASE_ECAT_M07_MINIMOTOR=(%d)"),CASE_ECAT_M07_MINIMOTOR);
	//					CASE_ECAT_M07_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//			
	//		}
	//		break;
	//		
	//	case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
	//	{
	//		if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
	//		{
	//			TIME_COUNTER_M07 = 1;
	//		}
	//		else
	//		{
	//			TIME_COUNTER_M07 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
	//		}
	//		CASE_ECAT_M07_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
	//	}
	//	break;
	//	
	//	case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
	//		{
	//				if((R[R_ABIL_READ_SDO_M07]>0.5) && (TIME_COUNTER_M07 > 0))
	//					TIME_COUNTER_M07--;

	//				if(TIME_COUNTER_M07<=0)
	//				{
	//					CASE_ECAT_M07_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
	//		{
	//				inReadBuffer1_M07.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M07 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M07, &numByteRead1_M07, 150);
	//				if (ret_iosRead_Minimotor_M07 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_CURRENT_ECAT_M07 = (short) (  ( (dataRead1_M07[1]<<8) & 0xFF00)+(dataRead1_M07[0] & 0xFF));
	//					R[R_ACTUAL_CURRENT_M07] = ((double) WORD_CURRENT_ECAT_M07) / 1000.0;

	//					if(R[R_ACTUAL_CURRENT_M07]>R[R_MAX_CURRENT_M07]) R[R_MAX_CURRENT_M07]=R[R_ACTUAL_CURRENT_M07];
	//					if(R[R_ACTUAL_CURRENT_M07]<R[R_MIN_CURRENT_M07]) R[R_MIN_CURRENT_M07]=R[R_ACTUAL_CURRENT_M07];

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M07[1].dataRead1_M07[0]"),dataRead1_M07[1],dataRead1_M07[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M07_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M07=(%d)"),CASE_ECAT_M07_MINIMOTOR,ret_iosRead_Minimotor_M07);

	//					CASE_ECAT_M07_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M07)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M07_MINIMOTOR=(%d)"),CASE_ECAT_M07_MINIMOTOR);
	//					CASE_ECAT_M07_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
	//		{
	//				inReadBuffer1_M07.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M07 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M07, &numByteRead1_M07, 150);
	//				if (ret_iosRead_Minimotor_M07 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_CURRENT_ECAT_M07 = (unsigned short) (  ( (dataRead1_M07[1]<<8) & 0xFF00)+(dataRead1_M07[0] & 0xFF));
	//					R[R_PARAM_MAX_CURRENT_M07] = ((double) WORD1_CURRENT_ECAT_M07) / 1000.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M07[1].dataRead1_M07[0]"),dataRead1_M07[1],dataRead1_M07[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M07_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M07=(%d)"),CASE_ECAT_M07_MINIMOTOR,ret_iosRead_Minimotor_M07);

	//					CASE_ECAT_M07_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M07)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M07_MINIMOTOR=(%d)"),CASE_ECAT_M07_MINIMOTOR);
	//					CASE_ECAT_M07_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
	//		{
	//				inReadBuffer2_M07.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M07 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M07, &numByteRead2_M07, 150);
	//				if (ret_iosRead_Minimotor_M07 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_VOLTAGE_ECAT_M07 = (unsigned short) (( (dataRead2_M07[1]<<8) & 0xFF00)+(dataRead2_M07[0] & 0xFF));
	//					
	//					R[R_ACTUAL_VOLT_M07] = ((double) WORD1_VOLTAGE_ECAT_M07) /10.0;

	//					if(R[R_ACTUAL_VOLT_M07]>R[R_MAX_VOLT_M07]) R[R_MAX_VOLT_M07]=R[R_ACTUAL_VOLT_M07];
	//					if(R[R_ACTUAL_VOLT_M07]<R[R_MIN_VOLT_M07]) R[R_MIN_VOLT_M07]=R[R_ACTUAL_VOLT_M07];

	//					//rtplctrace4(1,_T("%x %x = dataRead2_M07[1].dataRead2_M07[0]"),dataRead2_M07[1],dataRead2_M07[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M07_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M07=(%d)"),CASE_ECAT_M07_MINIMOTOR,ret_iosRead_Minimotor_M07);

	//					CASE_ECAT_M07_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M07)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M07_MINIMOTOR=(%d)"),CASE_ECAT_M07_MINIMOTOR);
	//					CASE_ECAT_M07_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
	//		{
	//				inReadBuffer3_M07.value.arr.size = 4;
	//				ret_iosRead_Minimotor_M07 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M07, &numByteRead3_M07, 150);
	//				if (ret_iosRead_Minimotor_M07 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_COUNT_FLT_ECAT_M07 = (unsigned long) (  ( (dataRead3_M07[3]<<24) & 0xFF000000) + ( (dataRead3_M07[2]<<16) & 0xFF0000) + 
	//					                                               ( (dataRead3_M07[1]<<8) & 0xFF00)+(dataRead3_M07[0] & 0xFF)   );
	//					
	//					R[R_COUNTER_FILTRO_M07] = (double) WORD_COUNT_FLT_ECAT_M07;

	//					//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M07[3].dataRead3_M07[2].dataRead3_M07[1].dataRead3_M07[0]"),dataRead3_M07[1],dataRead3_M07[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M07_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M07=(%d)"),CASE_ECAT_M07_MINIMOTOR,ret_iosRead_Minimotor_M07);

	//					CASE_ECAT_M07_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M07)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M07_MINIMOTOR=(%d)"),CASE_ECAT_M07_MINIMOTOR);
	//					CASE_ECAT_M07_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;			
	//		
	//	case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
	//		{
	//				inReadBuffer4_M07.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M07 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M07, &numByteRead4_M07, 150);
	//				if (ret_iosRead_Minimotor_M07 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_OUTPUT_PWR_ECAT_M07 = (short) (  ( (dataRead4_M07[1]<<8) & 0xFF00)+(dataRead4_M07[0] & 0xFF)   );
	//					
	//					R[R_OUTPUT_PWR_M07] = ((double) WORD_OUTPUT_PWR_ECAT_M07) / 1.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead4_M07[1].dataRead4_M07[0]"),dataRead4_M07[1],dataRead4_M07[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M07_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M07=(%d)"),CASE_ECAT_M07_MINIMOTOR,ret_iosRead_Minimotor_M07);

	//					CASE_ECAT_M07_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//					
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M07)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M07_MINIMOTOR=(%d)"),CASE_ECAT_M07_MINIMOTOR);
	//					CASE_ECAT_M07_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_ERROR_ETH_MINIMOTOR:
	//		{
	//			if(minimotorHandle != 0)
	//			{
	//				iosClose(minimotorHandle);
	//				minimotorHandle = 0;
	//				//rtplctrace4(1,_T("CASE_ECAT_M07_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1025-"),CASE_ECAT_M07_MINIMOTOR);
	//				CASE_ECAT_M07_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//			else
	//			{
	//				CASE_ECAT_M07_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}

	//		}
	//		break;			

	//	}
	//}
	//else
	//{
	//}

	//if(CONF_ASSE_M08)
	//{
	//	static ULONG minimotorHandle = 0;
	//	static RTPLC_STRING buffer_str = {0};
	//	static char *buffer = IND_ETHERCAT_M08;
	//	static short int TIME_COUNTER_M08 = 0;
	//	
	//	inReadBuffer1_M08.value.arr.data = dataRead1_M08;
	//	inReadBuffer1_M08.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
	//	
	//	inReadBuffer2_M08.value.arr.data = dataRead2_M08;
	//	inReadBuffer2_M08.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer3_M08.value.arr.data = dataRead3_M08;
	//	inReadBuffer3_M08.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer4_M08.value.arr.data = dataRead4_M08;
	//	inReadBuffer4_M08.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	switch (CASE_ECAT_M08_MINIMOTOR)
	//	{
	//	case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
	//		{
	//			if(PON)
	//			{
	//				memset(&buffer_str, 0, sizeof(buffer_str));
	//				buffer_str.size = _strlen(buffer);
	//				buffer_str.sz = buffer;
	//			}
	//			
	//			if(O_MOV_M08 && (R[R_ABIL_READ_SDO_M08]>0.5))
	//			{
	//				CASE_ECAT_M08_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//		}
	//		break;

	//	case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
	//		{
	//				ret_iosOpen_Minimotor_M08 = iosOpen(&buffer_str, &minimotorHandle);
	//				if (ret_iosOpen_Minimotor_M08 == RTPLC_STATUS_OK) 
	//				{
	//					//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
	//					//rtplctrace4(1,_T("CASE_ECAT_M08_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1022-> ret_iosOpen_Minimotor_M08=(%d)"),CASE_ECAT_M08_MINIMOTOR,ret_iosOpen_Minimotor_M08);

	//					R[R_MAX_CURRENT_M08] = -1000.0;
	//					R[R_MIN_CURRENT_M08] = 1000.0;

	//					R[R_MAX_VOLT_M08] = -1000.0;
	//					R[R_MIN_VOLT_M08] = 1000.0;
	//					
	//					CASE_ECAT_M08_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M08)) 
	//				{
	//					//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
	//					//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1022-> CASE_ECAT_M08_MINIMOTOR=(%d)"),CASE_ECAT_M08_MINIMOTOR);
	//					CASE_ECAT_M08_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//			
	//		}
	//		break;
	//		
	//	case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
	//	{
	//		if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
	//		{
	//			TIME_COUNTER_M08 = 1;
	//		}
	//		else
	//		{
	//			TIME_COUNTER_M08 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
	//		}
	//		CASE_ECAT_M08_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
	//	}
	//	break;
	//	
	//	case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
	//		{
	//				if((R[R_ABIL_READ_SDO_M08]>0.5) && (TIME_COUNTER_M08 > 0))
	//					TIME_COUNTER_M08--;

	//				if(TIME_COUNTER_M08<=0)
	//				{
	//					CASE_ECAT_M08_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
	//		{
	//				inReadBuffer1_M08.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M08 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M08, &numByteRead1_M08, 150);
	//				if (ret_iosRead_Minimotor_M08 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_CURRENT_ECAT_M08 = (short) (  ( (dataRead1_M08[1]<<8) & 0xFF00)+(dataRead1_M08[0] & 0xFF));
	//					R[R_ACTUAL_CURRENT_M08] = ((double) WORD_CURRENT_ECAT_M08) / 1000.0;

	//					if(R[R_ACTUAL_CURRENT_M08]>R[R_MAX_CURRENT_M08]) R[R_MAX_CURRENT_M08]=R[R_ACTUAL_CURRENT_M08];
	//					if(R[R_ACTUAL_CURRENT_M08]<R[R_MIN_CURRENT_M08]) R[R_MIN_CURRENT_M08]=R[R_ACTUAL_CURRENT_M08];

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M08[1].dataRead1_M08[0]"),dataRead1_M08[1],dataRead1_M08[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M08_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M08=(%d)"),CASE_ECAT_M08_MINIMOTOR,ret_iosRead_Minimotor_M08);

	//					CASE_ECAT_M08_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M08)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M08_MINIMOTOR=(%d)"),CASE_ECAT_M08_MINIMOTOR);
	//					CASE_ECAT_M08_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
	//		{
	//				inReadBuffer1_M08.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M08 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M08, &numByteRead1_M08, 150);
	//				if (ret_iosRead_Minimotor_M08 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_CURRENT_ECAT_M08 = (unsigned short) (  ( (dataRead1_M08[1]<<8) & 0xFF00)+(dataRead1_M08[0] & 0xFF));
	//					R[R_PARAM_MAX_CURRENT_M08] = ((double) WORD1_CURRENT_ECAT_M08) / 1000.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M08[1].dataRead1_M08[0]"),dataRead1_M08[1],dataRead1_M08[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M08_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M08=(%d)"),CASE_ECAT_M08_MINIMOTOR,ret_iosRead_Minimotor_M08);

	//					CASE_ECAT_M08_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M08)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M08_MINIMOTOR=(%d)"),CASE_ECAT_M08_MINIMOTOR);
	//					CASE_ECAT_M08_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
	//		{
	//				inReadBuffer2_M08.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M08 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M08, &numByteRead2_M08, 150);
	//				if (ret_iosRead_Minimotor_M08 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_VOLTAGE_ECAT_M08 = (unsigned short) (( (dataRead2_M08[1]<<8) & 0xFF00)+(dataRead2_M08[0] & 0xFF));
	//					
	//					R[R_ACTUAL_VOLT_M08] = ((double) WORD1_VOLTAGE_ECAT_M08) /10.0;

	//					if(R[R_ACTUAL_VOLT_M08]>R[R_MAX_VOLT_M08]) R[R_MAX_VOLT_M08]=R[R_ACTUAL_VOLT_M08];
	//					if(R[R_ACTUAL_VOLT_M08]<R[R_MIN_VOLT_M08]) R[R_MIN_VOLT_M08]=R[R_ACTUAL_VOLT_M08];

	//					//rtplctrace4(1,_T("%x %x = dataRead2_M08[1].dataRead2_M08[0]"),dataRead2_M08[1],dataRead2_M08[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M08_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M08=(%d)"),CASE_ECAT_M08_MINIMOTOR,ret_iosRead_Minimotor_M08);

	//					CASE_ECAT_M08_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M08)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M08_MINIMOTOR=(%d)"),CASE_ECAT_M08_MINIMOTOR);
	//					CASE_ECAT_M08_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
	//		{
	//				inReadBuffer3_M08.value.arr.size = 4;
	//				ret_iosRead_Minimotor_M08 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M08, &numByteRead3_M08, 150);
	//				if (ret_iosRead_Minimotor_M08 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_COUNT_FLT_ECAT_M08 = (unsigned long) (  ( (dataRead3_M08[3]<<24) & 0xFF000000) + ( (dataRead3_M08[2]<<16) & 0xFF0000) + 
	//					                                               ( (dataRead3_M08[1]<<8) & 0xFF00)+(dataRead3_M08[0] & 0xFF)   );
	//					
	//					R[R_COUNTER_FILTRO_M08] = (double) WORD_COUNT_FLT_ECAT_M08;

	//					//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M08[3].dataRead3_M08[2].dataRead3_M08[1].dataRead3_M08[0]"),dataRead3_M08[1],dataRead3_M08[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M08_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M08=(%d)"),CASE_ECAT_M08_MINIMOTOR,ret_iosRead_Minimotor_M08);

	//					CASE_ECAT_M08_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M08)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M08_MINIMOTOR=(%d)"),CASE_ECAT_M08_MINIMOTOR);
	//					CASE_ECAT_M08_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;			
	//		
	//	case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
	//		{
	//				inReadBuffer4_M08.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M08 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M08, &numByteRead4_M08, 150);
	//				if (ret_iosRead_Minimotor_M08 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_OUTPUT_PWR_ECAT_M08 = (short) (  ( (dataRead4_M08[1]<<8) & 0xFF00)+(dataRead4_M08[0] & 0xFF)   );
	//					
	//					R[R_OUTPUT_PWR_M08] = ((double) WORD_OUTPUT_PWR_ECAT_M08) / 1.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead4_M08[1].dataRead4_M08[0]"),dataRead4_M08[1],dataRead4_M08[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M08_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M08=(%d)"),CASE_ECAT_M08_MINIMOTOR,ret_iosRead_Minimotor_M08);

	//					CASE_ECAT_M08_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//					
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M08)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M08_MINIMOTOR=(%d)"),CASE_ECAT_M08_MINIMOTOR);
	//					CASE_ECAT_M08_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_ERROR_ETH_MINIMOTOR:
	//		{
	//			if(minimotorHandle != 0)
	//			{
	//				iosClose(minimotorHandle);
	//				minimotorHandle = 0;
	//				//rtplctrace4(1,_T("CASE_ECAT_M08_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1022-"),CASE_ECAT_M08_MINIMOTOR);
	//				CASE_ECAT_M08_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//			else
	//			{
	//				CASE_ECAT_M08_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}

	//		}
	//		break;			

	//	}
	//}
	//else
	//{
	//}

	//if(CONF_ASSE_M09)
	//{
	//	static ULONG minimotorHandle = 0;
	//	static RTPLC_STRING buffer_str = {0};
	//	static char *buffer = IND_ETHERCAT_M09;
	//	static short int TIME_COUNTER_M09 = 0;
	//	
	//	inReadBuffer1_M09.value.arr.data = dataRead1_M09;
	//	inReadBuffer1_M09.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
	//	
	//	inReadBuffer2_M09.value.arr.data = dataRead2_M09;
	//	inReadBuffer2_M09.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer3_M09.value.arr.data = dataRead3_M09;
	//	inReadBuffer3_M09.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer4_M09.value.arr.data = dataRead4_M09;
	//	inReadBuffer4_M09.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	switch (CASE_ECAT_M09_MINIMOTOR)
	//	{
	//	case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
	//		{
	//			if(PON)
	//			{
	//				memset(&buffer_str, 0, sizeof(buffer_str));
	//				buffer_str.size = _strlen(buffer);
	//				buffer_str.sz = buffer;
	//			}
	//			
	//			if(O_MOV_M09 && (R[R_ABIL_READ_SDO_M09]>0.5))
	//			{
	//				CASE_ECAT_M09_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//		}
	//		break;

	//	case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
	//		{
	//				ret_iosOpen_Minimotor_M09 = iosOpen(&buffer_str, &minimotorHandle);
	//				if (ret_iosOpen_Minimotor_M09 == RTPLC_STATUS_OK) 
	//				{
	//					//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
	//					//rtplctrace4(1,_T("CASE_ECAT_M09_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1019-> ret_iosOpen_Minimotor_M09=(%d)"),CASE_ECAT_M09_MINIMOTOR,ret_iosOpen_Minimotor_M09);

	//					R[R_MAX_CURRENT_M09] = -1000.0;
	//					R[R_MIN_CURRENT_M09] = 1000.0;

	//					R[R_MAX_VOLT_M09] = -1000.0;
	//					R[R_MIN_VOLT_M09] = 1000.0;
	//					
	//					CASE_ECAT_M09_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M09)) 
	//				{
	//					//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
	//					//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1019-> CASE_ECAT_M09_MINIMOTOR=(%d)"),CASE_ECAT_M09_MINIMOTOR);
	//					CASE_ECAT_M09_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//			
	//		}
	//		break;
	//		
	//	case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
	//	{
	//		if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
	//		{
	//			TIME_COUNTER_M09 = 1;
	//		}
	//		else
	//		{
	//			TIME_COUNTER_M09 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
	//		}
	//		CASE_ECAT_M09_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
	//	}
	//	break;
	//	
	//	case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
	//		{
	//				if((R[R_ABIL_READ_SDO_M09]>0.5) && (TIME_COUNTER_M09 > 0))
	//					TIME_COUNTER_M09--;

	//				if(TIME_COUNTER_M09<=0)
	//				{
	//					CASE_ECAT_M09_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
	//		{
	//				inReadBuffer1_M09.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M09 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M09, &numByteRead1_M09, 150);
	//				if (ret_iosRead_Minimotor_M09 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_CURRENT_ECAT_M09 = (short) (  ( (dataRead1_M09[1]<<8) & 0xFF00)+(dataRead1_M09[0] & 0xFF));
	//					R[R_ACTUAL_CURRENT_M09] = ((double) WORD_CURRENT_ECAT_M09) / 1000.0;

	//					if(R[R_ACTUAL_CURRENT_M09]>R[R_MAX_CURRENT_M09]) R[R_MAX_CURRENT_M09]=R[R_ACTUAL_CURRENT_M09];
	//					if(R[R_ACTUAL_CURRENT_M09]<R[R_MIN_CURRENT_M09]) R[R_MIN_CURRENT_M09]=R[R_ACTUAL_CURRENT_M09];

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M09[1].dataRead1_M09[0]"),dataRead1_M09[1],dataRead1_M09[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M09_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M09=(%d)"),CASE_ECAT_M09_MINIMOTOR,ret_iosRead_Minimotor_M09);

	//					CASE_ECAT_M09_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M09)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M09_MINIMOTOR=(%d)"),CASE_ECAT_M09_MINIMOTOR);
	//					CASE_ECAT_M09_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
	//		{
	//				inReadBuffer1_M09.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M09 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M09, &numByteRead1_M09, 150);
	//				if (ret_iosRead_Minimotor_M09 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_CURRENT_ECAT_M09 = (unsigned short) (  ( (dataRead1_M09[1]<<8) & 0xFF00)+(dataRead1_M09[0] & 0xFF));
	//					R[R_PARAM_MAX_CURRENT_M09] = ((double) WORD1_CURRENT_ECAT_M09) / 1000.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M09[1].dataRead1_M09[0]"),dataRead1_M09[1],dataRead1_M09[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M09_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M09=(%d)"),CASE_ECAT_M09_MINIMOTOR,ret_iosRead_Minimotor_M09);

	//					CASE_ECAT_M09_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M09)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M09_MINIMOTOR=(%d)"),CASE_ECAT_M09_MINIMOTOR);
	//					CASE_ECAT_M09_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
	//		{
	//				inReadBuffer2_M09.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M09 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M09, &numByteRead2_M09, 150);
	//				if (ret_iosRead_Minimotor_M09 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_VOLTAGE_ECAT_M09 = (unsigned short) (( (dataRead2_M09[1]<<8) & 0xFF00)+(dataRead2_M09[0] & 0xFF));
	//					
	//					R[R_ACTUAL_VOLT_M09] = ((double) WORD1_VOLTAGE_ECAT_M09) /10.0;

	//					if(R[R_ACTUAL_VOLT_M09]>R[R_MAX_VOLT_M09]) R[R_MAX_VOLT_M09]=R[R_ACTUAL_VOLT_M09];
	//					if(R[R_ACTUAL_VOLT_M09]<R[R_MIN_VOLT_M09]) R[R_MIN_VOLT_M09]=R[R_ACTUAL_VOLT_M09];

	//					//rtplctrace4(1,_T("%x %x = dataRead2_M09[1].dataRead2_M09[0]"),dataRead2_M09[1],dataRead2_M09[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M09_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M09=(%d)"),CASE_ECAT_M09_MINIMOTOR,ret_iosRead_Minimotor_M09);

	//					CASE_ECAT_M09_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M09)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M09_MINIMOTOR=(%d)"),CASE_ECAT_M09_MINIMOTOR);
	//					CASE_ECAT_M09_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
	//		{
	//				inReadBuffer3_M09.value.arr.size = 4;
	//				ret_iosRead_Minimotor_M09 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M09, &numByteRead3_M09, 150);
	//				if (ret_iosRead_Minimotor_M09 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_COUNT_FLT_ECAT_M09 = (unsigned long) (  ( (dataRead3_M09[3]<<24) & 0xFF000000) + ( (dataRead3_M09[2]<<16) & 0xFF0000) + 
	//					                                               ( (dataRead3_M09[1]<<8) & 0xFF00)+(dataRead3_M09[0] & 0xFF)   );
	//					
	//					R[R_COUNTER_FILTRO_M09] = (double) WORD_COUNT_FLT_ECAT_M09;

	//					//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M09[3].dataRead3_M09[2].dataRead3_M09[1].dataRead3_M09[0]"),dataRead3_M09[1],dataRead3_M09[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M09_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M09=(%d)"),CASE_ECAT_M09_MINIMOTOR,ret_iosRead_Minimotor_M09);

	//					CASE_ECAT_M09_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M09)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M09_MINIMOTOR=(%d)"),CASE_ECAT_M09_MINIMOTOR);
	//					CASE_ECAT_M09_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;			
	//		
	//	case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
	//		{
	//				inReadBuffer4_M09.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M09 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M09, &numByteRead4_M09, 150);
	//				if (ret_iosRead_Minimotor_M09 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_OUTPUT_PWR_ECAT_M09 = (short) (  ( (dataRead4_M09[1]<<8) & 0xFF00)+(dataRead4_M09[0] & 0xFF)   );
	//					
	//					R[R_OUTPUT_PWR_M09] = ((double) WORD_OUTPUT_PWR_ECAT_M09) / 1.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead4_M09[1].dataRead4_M09[0]"),dataRead4_M09[1],dataRead4_M09[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M09_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M09=(%d)"),CASE_ECAT_M09_MINIMOTOR,ret_iosRead_Minimotor_M09);

	//					CASE_ECAT_M09_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//					
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M09)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M09_MINIMOTOR=(%d)"),CASE_ECAT_M09_MINIMOTOR);
	//					CASE_ECAT_M09_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_ERROR_ETH_MINIMOTOR:
	//		{
	//			if(minimotorHandle != 0)
	//			{
	//				iosClose(minimotorHandle);
	//				minimotorHandle = 0;
	//				//rtplctrace4(1,_T("CASE_ECAT_M09_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1019-"),CASE_ECAT_M09_MINIMOTOR);
	//				CASE_ECAT_M09_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//			else
	//			{
	//				CASE_ECAT_M09_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}

	//		}
	//		break;			

	//	}
	//}
	//else
	//{
	//}

	if(CONF_ASSE_M10)
	{
		static ULONG minimotorHandle = 0;
		static RTPLC_STRING buffer_str = {0};
		static char *buffer = IND_ETHERCAT_M10;
		static short int TIME_COUNTER_M10 = 0;
		
		inReadBuffer1_M10.value.arr.data = dataRead1_M10;
		inReadBuffer1_M10.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		inReadBuffer2_M10.value.arr.data = dataRead2_M10;
		inReadBuffer2_M10.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer3_M10.value.arr.data = dataRead3_M10;
		inReadBuffer3_M10.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer4_M10.value.arr.data = dataRead4_M10;
		inReadBuffer4_M10.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		switch (CASE_ECAT_M10_MINIMOTOR)
		{
		case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
			{
				if(PON)
				{
					memset(&buffer_str, 0, sizeof(buffer_str));
					buffer_str.size = _strlen(buffer);
					buffer_str.sz = buffer;
				}
				
				if(O_MOV_M10 && (R[R_ABIL_READ_SDO_M10]>0.5))
				{
					CASE_ECAT_M10_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
			}
			break;

		case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
			{
					ret_iosOpen_Minimotor_M10 = iosOpen(&buffer_str, &minimotorHandle);
					if (ret_iosOpen_Minimotor_M10 == RTPLC_STATUS_OK) 
					{
						//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
						//rtplctrace4(1,_T("CASE_ECAT_M10_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1016-> ret_iosOpen_Minimotor_M10=(%d)"),CASE_ECAT_M10_MINIMOTOR,ret_iosOpen_Minimotor_M10);

						R[R_MAX_CURRENT_M10] = -1000.0;
						R[R_MIN_CURRENT_M10] = 1000.0;

						R[R_MAX_VOLT_M10] = -1000.0;
						R[R_MIN_VOLT_M10] = 1000.0;
						
						CASE_ECAT_M10_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M10)) 
					{
						//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
						//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1016-> CASE_ECAT_M10_MINIMOTOR=(%d)"),CASE_ECAT_M10_MINIMOTOR);
						CASE_ECAT_M10_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
				
			}
			break;
			
		case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
		{
			if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
			{
				TIME_COUNTER_M10 = 1;
			}
			else
			{
				TIME_COUNTER_M10 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
			}
			CASE_ECAT_M10_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
		}
		break;
		
		case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
			{
					if((R[R_ABIL_READ_SDO_M10]>0.5) && (TIME_COUNTER_M10 > 0))
						TIME_COUNTER_M10--;

					if(TIME_COUNTER_M10<=0)
					{
						CASE_ECAT_M10_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
			{
					inReadBuffer1_M10.value.arr.size = 2;
					ret_iosRead_Minimotor_M10 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M10, &numByteRead1_M10, 150);
					if (ret_iosRead_Minimotor_M10 == RTPLC_STATUS_OK) 
					{
						WORD_CURRENT_ECAT_M10 = (short) (  ( (dataRead1_M10[1]<<8) & 0xFF00)+(dataRead1_M10[0] & 0xFF));
						R[R_ACTUAL_CURRENT_M10] = ((double) WORD_CURRENT_ECAT_M10) / 1000.0;

						if(R[R_ACTUAL_CURRENT_M10]>R[R_MAX_CURRENT_M10]) R[R_MAX_CURRENT_M10]=R[R_ACTUAL_CURRENT_M10];
						if(R[R_ACTUAL_CURRENT_M10]<R[R_MIN_CURRENT_M10]) R[R_MIN_CURRENT_M10]=R[R_ACTUAL_CURRENT_M10];

						//rtplctrace4(1,_T("%x %x = dataRead1_M10[1].dataRead1_M10[0]"),dataRead1_M10[1],dataRead1_M10[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M10_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M10=(%d)"),CASE_ECAT_M10_MINIMOTOR,ret_iosRead_Minimotor_M10);

						CASE_ECAT_M10_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M10)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M10_MINIMOTOR=(%d)"),CASE_ECAT_M10_MINIMOTOR);
						CASE_ECAT_M10_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
			{
					inReadBuffer1_M10.value.arr.size = 2;
					ret_iosRead_Minimotor_M10 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M10, &numByteRead1_M10, 150);
					if (ret_iosRead_Minimotor_M10 == RTPLC_STATUS_OK) 
					{
						WORD1_CURRENT_ECAT_M10 = (unsigned short) (  ( (dataRead1_M10[1]<<8) & 0xFF00)+(dataRead1_M10[0] & 0xFF));
						R[R_PARAM_MAX_CURRENT_M10] = ((double) WORD1_CURRENT_ECAT_M10) / 1000.0;

						//rtplctrace4(1,_T("%x %x = dataRead1_M10[1].dataRead1_M10[0]"),dataRead1_M10[1],dataRead1_M10[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M10_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M10=(%d)"),CASE_ECAT_M10_MINIMOTOR,ret_iosRead_Minimotor_M10);

						CASE_ECAT_M10_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M10)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M10_MINIMOTOR=(%d)"),CASE_ECAT_M10_MINIMOTOR);
						CASE_ECAT_M10_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
			{
					inReadBuffer2_M10.value.arr.size = 2;
					ret_iosRead_Minimotor_M10 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M10, &numByteRead2_M10, 150);
					if (ret_iosRead_Minimotor_M10 == RTPLC_STATUS_OK) 
					{
						WORD1_VOLTAGE_ECAT_M10 = (unsigned short) (( (dataRead2_M10[1]<<8) & 0xFF00)+(dataRead2_M10[0] & 0xFF));
						
						R[R_ACTUAL_VOLT_M10] = ((double) WORD1_VOLTAGE_ECAT_M10) /10.0;

						if(R[R_ACTUAL_VOLT_M10]>R[R_MAX_VOLT_M10]) R[R_MAX_VOLT_M10]=R[R_ACTUAL_VOLT_M10];
						if(R[R_ACTUAL_VOLT_M10]<R[R_MIN_VOLT_M10]) R[R_MIN_VOLT_M10]=R[R_ACTUAL_VOLT_M10];

						//rtplctrace4(1,_T("%x %x = dataRead2_M10[1].dataRead2_M10[0]"),dataRead2_M10[1],dataRead2_M10[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M10_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M10=(%d)"),CASE_ECAT_M10_MINIMOTOR,ret_iosRead_Minimotor_M10);

						CASE_ECAT_M10_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M10)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M10_MINIMOTOR=(%d)"),CASE_ECAT_M10_MINIMOTOR);
						CASE_ECAT_M10_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
			{
					inReadBuffer3_M10.value.arr.size = 4;
					ret_iosRead_Minimotor_M10 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M10, &numByteRead3_M10, 150);
					if (ret_iosRead_Minimotor_M10 == RTPLC_STATUS_OK) 
					{
						WORD_COUNT_FLT_ECAT_M10 = (unsigned long) (  ( (dataRead3_M10[3]<<24) & 0xFF000000) + ( (dataRead3_M10[2]<<16) & 0xFF0000) + 
						                                               ( (dataRead3_M10[1]<<8) & 0xFF00)+(dataRead3_M10[0] & 0xFF)   );
						
						R[R_COUNTER_FILTRO_M10] = (double) WORD_COUNT_FLT_ECAT_M10;

						//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M10[3].dataRead3_M10[2].dataRead3_M10[1].dataRead3_M10[0]"),dataRead3_M10[1],dataRead3_M10[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M10_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M10=(%d)"),CASE_ECAT_M10_MINIMOTOR,ret_iosRead_Minimotor_M10);

						CASE_ECAT_M10_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M10)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M10_MINIMOTOR=(%d)"),CASE_ECAT_M10_MINIMOTOR);
						CASE_ECAT_M10_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;			
			
		case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
			{
					inReadBuffer4_M10.value.arr.size = 2;
					ret_iosRead_Minimotor_M10 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M10, &numByteRead4_M10, 150);
					if (ret_iosRead_Minimotor_M10 == RTPLC_STATUS_OK) 
					{
						WORD_OUTPUT_PWR_ECAT_M10 = (short) (  ( (dataRead4_M10[1]<<8) & 0xFF00)+(dataRead4_M10[0] & 0xFF)   );
						
						R[R_OUTPUT_PWR_M10] = ((double) WORD_OUTPUT_PWR_ECAT_M10) / 1.0;

						//rtplctrace4(1,_T("%x %x = dataRead4_M10[1].dataRead4_M10[0]"),dataRead4_M10[1],dataRead4_M10[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M10_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M10=(%d)"),CASE_ECAT_M10_MINIMOTOR,ret_iosRead_Minimotor_M10);

						CASE_ECAT_M10_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
						
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M10)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M10_MINIMOTOR=(%d)"),CASE_ECAT_M10_MINIMOTOR);
						CASE_ECAT_M10_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_ERROR_ETH_MINIMOTOR:
			{
				if(minimotorHandle != 0)
				{
					iosClose(minimotorHandle);
					minimotorHandle = 0;
					//rtplctrace4(1,_T("CASE_ECAT_M10_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1016-"),CASE_ECAT_M10_MINIMOTOR);
					CASE_ECAT_M10_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
				else
				{
					CASE_ECAT_M10_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}

			}
			break;			

		}
	}
	else
	{
	}

	if(CONF_ASSE_M11)
	{
		static ULONG minimotorHandle = 0;
		static RTPLC_STRING buffer_str = {0};
		static char *buffer = IND_ETHERCAT_M11;
		static short int TIME_COUNTER_M11 = 0;
		
		inReadBuffer1_M11.value.arr.data = dataRead1_M11;
		inReadBuffer1_M11.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		inReadBuffer2_M11.value.arr.data = dataRead2_M11;
		inReadBuffer2_M11.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer3_M11.value.arr.data = dataRead3_M11;
		inReadBuffer3_M11.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer4_M11.value.arr.data = dataRead4_M11;
		inReadBuffer4_M11.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		switch (CASE_ECAT_M11_MINIMOTOR)
		{
		case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
			{
				if(PON)
				{
					memset(&buffer_str, 0, sizeof(buffer_str));
					buffer_str.size = _strlen(buffer);
					buffer_str.sz = buffer;
				}
				
				if(O_MOV_M11 && (R[R_ABIL_READ_SDO_M11]>0.5))
				{
					CASE_ECAT_M11_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
			}
			break;

		case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
			{
					ret_iosOpen_Minimotor_M11 = iosOpen(&buffer_str, &minimotorHandle);
					if (ret_iosOpen_Minimotor_M11 == RTPLC_STATUS_OK) 
					{
						//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
						//rtplctrace4(1,_T("CASE_ECAT_M11_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1013-> ret_iosOpen_Minimotor_M11=(%d)"),CASE_ECAT_M11_MINIMOTOR,ret_iosOpen_Minimotor_M11);

						R[R_MAX_CURRENT_M11] = -1000.0;
						R[R_MIN_CURRENT_M11] = 1000.0;

						R[R_MAX_VOLT_M11] = -1000.0;
						R[R_MIN_VOLT_M11] = 1000.0;
						
						CASE_ECAT_M11_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M11)) 
					{
						//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
						//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1013-> CASE_ECAT_M11_MINIMOTOR=(%d)"),CASE_ECAT_M11_MINIMOTOR);
						CASE_ECAT_M11_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
				
			}
			break;
			
		case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
		{
			if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
			{
				TIME_COUNTER_M11 = 1;
			}
			else
			{
				TIME_COUNTER_M11 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
			}
			CASE_ECAT_M11_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
		}
		break;
		
		case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
			{
					if((R[R_ABIL_READ_SDO_M11]>0.5) && (TIME_COUNTER_M11 > 0))
						TIME_COUNTER_M11--;

					if(TIME_COUNTER_M11<=0)
					{
						CASE_ECAT_M11_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
			{
					inReadBuffer1_M11.value.arr.size = 2;
					ret_iosRead_Minimotor_M11 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M11, &numByteRead1_M11, 150);
					if (ret_iosRead_Minimotor_M11 == RTPLC_STATUS_OK) 
					{
						WORD_CURRENT_ECAT_M11 = (short) (  ( (dataRead1_M11[1]<<8) & 0xFF00)+(dataRead1_M11[0] & 0xFF));
						R[R_ACTUAL_CURRENT_M11] = ((double) WORD_CURRENT_ECAT_M11) / 1000.0;

						if(R[R_ACTUAL_CURRENT_M11]>R[R_MAX_CURRENT_M11]) R[R_MAX_CURRENT_M11]=R[R_ACTUAL_CURRENT_M11];
						if(R[R_ACTUAL_CURRENT_M11]<R[R_MIN_CURRENT_M11]) R[R_MIN_CURRENT_M11]=R[R_ACTUAL_CURRENT_M11];

						//rtplctrace4(1,_T("%x %x = dataRead1_M11[1].dataRead1_M11[0]"),dataRead1_M11[1],dataRead1_M11[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M11_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M11=(%d)"),CASE_ECAT_M11_MINIMOTOR,ret_iosRead_Minimotor_M11);

						CASE_ECAT_M11_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M11)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M11_MINIMOTOR=(%d)"),CASE_ECAT_M11_MINIMOTOR);
						CASE_ECAT_M11_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
			{
					inReadBuffer1_M11.value.arr.size = 2;
					ret_iosRead_Minimotor_M11 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M11, &numByteRead1_M11, 150);
					if (ret_iosRead_Minimotor_M11 == RTPLC_STATUS_OK) 
					{
						WORD1_CURRENT_ECAT_M11 = (unsigned short) (  ( (dataRead1_M11[1]<<8) & 0xFF00)+(dataRead1_M11[0] & 0xFF));
						R[R_PARAM_MAX_CURRENT_M11] = ((double) WORD1_CURRENT_ECAT_M11) / 1000.0;

						//rtplctrace4(1,_T("%x %x = dataRead1_M11[1].dataRead1_M11[0]"),dataRead1_M11[1],dataRead1_M11[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M11_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M11=(%d)"),CASE_ECAT_M11_MINIMOTOR,ret_iosRead_Minimotor_M11);

						CASE_ECAT_M11_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M11)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M11_MINIMOTOR=(%d)"),CASE_ECAT_M11_MINIMOTOR);
						CASE_ECAT_M11_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
			{
					inReadBuffer2_M11.value.arr.size = 2;
					ret_iosRead_Minimotor_M11 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M11, &numByteRead2_M11, 150);
					if (ret_iosRead_Minimotor_M11 == RTPLC_STATUS_OK) 
					{
						WORD1_VOLTAGE_ECAT_M11 = (unsigned short) (( (dataRead2_M11[1]<<8) & 0xFF00)+(dataRead2_M11[0] & 0xFF));
						
						R[R_ACTUAL_VOLT_M11] = ((double) WORD1_VOLTAGE_ECAT_M11) /10.0;

						if(R[R_ACTUAL_VOLT_M11]>R[R_MAX_VOLT_M11]) R[R_MAX_VOLT_M11]=R[R_ACTUAL_VOLT_M11];
						if(R[R_ACTUAL_VOLT_M11]<R[R_MIN_VOLT_M11]) R[R_MIN_VOLT_M11]=R[R_ACTUAL_VOLT_M11];

						//rtplctrace4(1,_T("%x %x = dataRead2_M11[1].dataRead2_M11[0]"),dataRead2_M11[1],dataRead2_M11[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M11_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M11=(%d)"),CASE_ECAT_M11_MINIMOTOR,ret_iosRead_Minimotor_M11);

						CASE_ECAT_M11_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M11)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M11_MINIMOTOR=(%d)"),CASE_ECAT_M11_MINIMOTOR);
						CASE_ECAT_M11_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
			{
					inReadBuffer3_M11.value.arr.size = 4;
					ret_iosRead_Minimotor_M11 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M11, &numByteRead3_M11, 150);
					if (ret_iosRead_Minimotor_M11 == RTPLC_STATUS_OK) 
					{
						WORD_COUNT_FLT_ECAT_M11 = (unsigned long) (  ( (dataRead3_M11[3]<<24) & 0xFF000000) + ( (dataRead3_M11[2]<<16) & 0xFF0000) + 
						                                               ( (dataRead3_M11[1]<<8) & 0xFF00)+(dataRead3_M11[0] & 0xFF)   );
						
						R[R_COUNTER_FILTRO_M11] = (double) WORD_COUNT_FLT_ECAT_M11;

						//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M11[3].dataRead3_M11[2].dataRead3_M11[1].dataRead3_M11[0]"),dataRead3_M11[1],dataRead3_M11[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M11_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M11=(%d)"),CASE_ECAT_M11_MINIMOTOR,ret_iosRead_Minimotor_M11);

						CASE_ECAT_M11_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M11)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M11_MINIMOTOR=(%d)"),CASE_ECAT_M11_MINIMOTOR);
						CASE_ECAT_M11_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;			
			
		case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
			{
					inReadBuffer4_M11.value.arr.size = 2;
					ret_iosRead_Minimotor_M11 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M11, &numByteRead4_M11, 150);
					if (ret_iosRead_Minimotor_M11 == RTPLC_STATUS_OK) 
					{
						WORD_OUTPUT_PWR_ECAT_M11 = (short) (  ( (dataRead4_M11[1]<<8) & 0xFF00)+(dataRead4_M11[0] & 0xFF)   );
						
						R[R_OUTPUT_PWR_M11] = ((double) WORD_OUTPUT_PWR_ECAT_M11) / 1.0;

						//rtplctrace4(1,_T("%x %x = dataRead4_M11[1].dataRead4_M11[0]"),dataRead4_M11[1],dataRead4_M11[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M11_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M11=(%d)"),CASE_ECAT_M11_MINIMOTOR,ret_iosRead_Minimotor_M11);

						CASE_ECAT_M11_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
						
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M11)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M11_MINIMOTOR=(%d)"),CASE_ECAT_M11_MINIMOTOR);
						CASE_ECAT_M11_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_ERROR_ETH_MINIMOTOR:
			{
				if(minimotorHandle != 0)
				{
					iosClose(minimotorHandle);
					minimotorHandle = 0;
					//rtplctrace4(1,_T("CASE_ECAT_M11_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1013-"),CASE_ECAT_M11_MINIMOTOR);
					CASE_ECAT_M11_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
				else
				{
					CASE_ECAT_M11_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}

			}
			break;			

		}
	}
	else
	{
	}

	if(CONF_ASSE_M12)
	{
		static ULONG minimotorHandle = 0;
		static RTPLC_STRING buffer_str = {0};
		static char *buffer = IND_ETHERCAT_M12;
		static short int TIME_COUNTER_M12 = 0;
		
		inReadBuffer1_M12.value.arr.data = dataRead1_M12;
		inReadBuffer1_M12.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		inReadBuffer2_M12.value.arr.data = dataRead2_M12;
		inReadBuffer2_M12.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer3_M12.value.arr.data = dataRead3_M12;
		inReadBuffer3_M12.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer4_M12.value.arr.data = dataRead4_M12;
		inReadBuffer4_M12.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		switch (CASE_ECAT_M12_MINIMOTOR)
		{
		case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
			{
				if(PON)
				{
					memset(&buffer_str, 0, sizeof(buffer_str));
					buffer_str.size = _strlen(buffer);
					buffer_str.sz = buffer;
				}
				
				if(O_MOV_M12 && (R[R_ABIL_READ_SDO_M12]>0.5))
				{
					CASE_ECAT_M12_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
			}
			break;

		case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
			{
					ret_iosOpen_Minimotor_M12 = iosOpen(&buffer_str, &minimotorHandle);
					if (ret_iosOpen_Minimotor_M12 == RTPLC_STATUS_OK) 
					{
						//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
						//rtplctrace4(1,_T("CASE_ECAT_M12_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1010-> ret_iosOpen_Minimotor_M12=(%d)"),CASE_ECAT_M12_MINIMOTOR,ret_iosOpen_Minimotor_M12);

						R[R_MAX_CURRENT_M12] = -1000.0;
						R[R_MIN_CURRENT_M12] = 1000.0;

						R[R_MAX_VOLT_M12] = -1000.0;
						R[R_MIN_VOLT_M12] = 1000.0;
						
						CASE_ECAT_M12_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M12)) 
					{
						//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
						//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1010-> CASE_ECAT_M12_MINIMOTOR=(%d)"),CASE_ECAT_M12_MINIMOTOR);
						CASE_ECAT_M12_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
				
			}
			break;
			
		case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
		{
			if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
			{
				TIME_COUNTER_M12 = 1;
			}
			else
			{
				TIME_COUNTER_M12 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
			}
			CASE_ECAT_M12_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
		}
		break;
		
		case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
			{
					if((R[R_ABIL_READ_SDO_M12]>0.5) && (TIME_COUNTER_M12 > 0))
						TIME_COUNTER_M12--;

					if(TIME_COUNTER_M12<=0)
					{
						CASE_ECAT_M12_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
			{
					inReadBuffer1_M12.value.arr.size = 2;
					ret_iosRead_Minimotor_M12 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M12, &numByteRead1_M12, 150);
					if (ret_iosRead_Minimotor_M12 == RTPLC_STATUS_OK) 
					{
						WORD_CURRENT_ECAT_M12 = (short) (  ( (dataRead1_M12[1]<<8) & 0xFF00)+(dataRead1_M12[0] & 0xFF));
						R[R_ACTUAL_CURRENT_M12] = ((double) WORD_CURRENT_ECAT_M12) / 1000.0;

						if(R[R_ACTUAL_CURRENT_M12]>R[R_MAX_CURRENT_M12]) R[R_MAX_CURRENT_M12]=R[R_ACTUAL_CURRENT_M12];
						if(R[R_ACTUAL_CURRENT_M12]<R[R_MIN_CURRENT_M12]) R[R_MIN_CURRENT_M12]=R[R_ACTUAL_CURRENT_M12];

						//rtplctrace4(1,_T("%x %x = dataRead1_M12[1].dataRead1_M12[0]"),dataRead1_M12[1],dataRead1_M12[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M12_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M12=(%d)"),CASE_ECAT_M12_MINIMOTOR,ret_iosRead_Minimotor_M12);

						CASE_ECAT_M12_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M12)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M12_MINIMOTOR=(%d)"),CASE_ECAT_M12_MINIMOTOR);
						CASE_ECAT_M12_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
			{
					inReadBuffer1_M12.value.arr.size = 2;
					ret_iosRead_Minimotor_M12 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M12, &numByteRead1_M12, 150);
					if (ret_iosRead_Minimotor_M12 == RTPLC_STATUS_OK) 
					{
						WORD1_CURRENT_ECAT_M12 = (unsigned short) (  ( (dataRead1_M12[1]<<8) & 0xFF00)+(dataRead1_M12[0] & 0xFF));
						R[R_PARAM_MAX_CURRENT_M12] = ((double) WORD1_CURRENT_ECAT_M12) / 1000.0;

						//rtplctrace4(1,_T("%x %x = dataRead1_M12[1].dataRead1_M12[0]"),dataRead1_M12[1],dataRead1_M12[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M12_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M12=(%d)"),CASE_ECAT_M12_MINIMOTOR,ret_iosRead_Minimotor_M12);

						CASE_ECAT_M12_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M12)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M12_MINIMOTOR=(%d)"),CASE_ECAT_M12_MINIMOTOR);
						CASE_ECAT_M12_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
			{
					inReadBuffer2_M12.value.arr.size = 2;
					ret_iosRead_Minimotor_M12 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M12, &numByteRead2_M12, 150);
					if (ret_iosRead_Minimotor_M12 == RTPLC_STATUS_OK) 
					{
						WORD1_VOLTAGE_ECAT_M12 = (unsigned short) (( (dataRead2_M12[1]<<8) & 0xFF00)+(dataRead2_M12[0] & 0xFF));
						
						R[R_ACTUAL_VOLT_M12] = ((double) WORD1_VOLTAGE_ECAT_M12) /10.0;

						if(R[R_ACTUAL_VOLT_M12]>R[R_MAX_VOLT_M12]) R[R_MAX_VOLT_M12]=R[R_ACTUAL_VOLT_M12];
						if(R[R_ACTUAL_VOLT_M12]<R[R_MIN_VOLT_M12]) R[R_MIN_VOLT_M12]=R[R_ACTUAL_VOLT_M12];

						//rtplctrace4(1,_T("%x %x = dataRead2_M12[1].dataRead2_M12[0]"),dataRead2_M12[1],dataRead2_M12[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M12_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M12=(%d)"),CASE_ECAT_M12_MINIMOTOR,ret_iosRead_Minimotor_M12);

						CASE_ECAT_M12_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M12)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M12_MINIMOTOR=(%d)"),CASE_ECAT_M12_MINIMOTOR);
						CASE_ECAT_M12_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
			{
					inReadBuffer3_M12.value.arr.size = 4;
					ret_iosRead_Minimotor_M12 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M12, &numByteRead3_M12, 150);
					if (ret_iosRead_Minimotor_M12 == RTPLC_STATUS_OK) 
					{
						WORD_COUNT_FLT_ECAT_M12 = (unsigned long) (  ( (dataRead3_M12[3]<<24) & 0xFF000000) + ( (dataRead3_M12[2]<<16) & 0xFF0000) + 
						                                               ( (dataRead3_M12[1]<<8) & 0xFF00)+(dataRead3_M12[0] & 0xFF)   );
						
						R[R_COUNTER_FILTRO_M12] = (double) WORD_COUNT_FLT_ECAT_M12;

						//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M12[3].dataRead3_M12[2].dataRead3_M12[1].dataRead3_M12[0]"),dataRead3_M12[1],dataRead3_M12[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M12_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M12=(%d)"),CASE_ECAT_M12_MINIMOTOR,ret_iosRead_Minimotor_M12);

						CASE_ECAT_M12_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M12)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M12_MINIMOTOR=(%d)"),CASE_ECAT_M12_MINIMOTOR);
						CASE_ECAT_M12_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;			
			
		case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
			{
					inReadBuffer4_M12.value.arr.size = 2;
					ret_iosRead_Minimotor_M12 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M12, &numByteRead4_M12, 150);
					if (ret_iosRead_Minimotor_M12 == RTPLC_STATUS_OK) 
					{
						WORD_OUTPUT_PWR_ECAT_M12 = (short) (  ( (dataRead4_M12[1]<<8) & 0xFF00)+(dataRead4_M12[0] & 0xFF)   );
						
						R[R_OUTPUT_PWR_M12] = ((double) WORD_OUTPUT_PWR_ECAT_M12) / 1.0;

						//rtplctrace4(1,_T("%x %x = dataRead4_M12[1].dataRead4_M12[0]"),dataRead4_M12[1],dataRead4_M12[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M12_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M12=(%d)"),CASE_ECAT_M12_MINIMOTOR,ret_iosRead_Minimotor_M12);

						CASE_ECAT_M12_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
						
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M12)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M12_MINIMOTOR=(%d)"),CASE_ECAT_M12_MINIMOTOR);
						CASE_ECAT_M12_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_ERROR_ETH_MINIMOTOR:
			{
				if(minimotorHandle != 0)
				{
					iosClose(minimotorHandle);
					minimotorHandle = 0;
					//rtplctrace4(1,_T("CASE_ECAT_M12_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1010-"),CASE_ECAT_M12_MINIMOTOR);
					CASE_ECAT_M12_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
				else
				{
					CASE_ECAT_M12_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}

			}
			break;			

		}
	}
	else
	{
	}

	if(CONF_ASSE_M13)
	{
		static ULONG minimotorHandle = 0;
		static RTPLC_STRING buffer_str = {0};
		static char *buffer = IND_ETHERCAT_M13;
		static short int TIME_COUNTER_M13 = 0;
		
		inReadBuffer1_M13.value.arr.data = dataRead1_M13;
		inReadBuffer1_M13.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		inReadBuffer2_M13.value.arr.data = dataRead2_M13;
		inReadBuffer2_M13.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer3_M13.value.arr.data = dataRead3_M13;
		inReadBuffer3_M13.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer4_M13.value.arr.data = dataRead4_M13;
		inReadBuffer4_M13.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		switch (CASE_ECAT_M13_MINIMOTOR)
		{
		case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
			{
				if(PON)
				{
					memset(&buffer_str, 0, sizeof(buffer_str));
					buffer_str.size = _strlen(buffer);
					buffer_str.sz = buffer;
				}
				
				if(O_MOV_M13 && (R[R_ABIL_READ_SDO_M13]>0.5))
				{
					CASE_ECAT_M13_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
			}
			break;

		case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
			{
					ret_iosOpen_Minimotor_M13 = iosOpen(&buffer_str, &minimotorHandle);
					if (ret_iosOpen_Minimotor_M13 == RTPLC_STATUS_OK) 
					{
						//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
						//rtplctrace4(1,_T("CASE_ECAT_M13_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1011-> ret_iosOpen_Minimotor_M13=(%d)"),CASE_ECAT_M13_MINIMOTOR,ret_iosOpen_Minimotor_M13);

						R[R_MAX_CURRENT_M13] = -1000.0;
						R[R_MIN_CURRENT_M13] = 1000.0;

						R[R_MAX_VOLT_M13] = -1000.0;
						R[R_MIN_VOLT_M13] = 1000.0;
						
						CASE_ECAT_M13_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M13)) 
					{
						//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
						//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1011-> CASE_ECAT_M13_MINIMOTOR=(%d)"),CASE_ECAT_M13_MINIMOTOR);
						CASE_ECAT_M13_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
				
			}
			break;
			
		case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
		{
			if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
			{
				TIME_COUNTER_M13 = 1;
			}
			else
			{
				TIME_COUNTER_M13 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
			}
			CASE_ECAT_M13_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
		}
		break;
		
		case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
			{
					if((R[R_ABIL_READ_SDO_M13]>0.5) && (TIME_COUNTER_M13 > 0))
						TIME_COUNTER_M13--;

					if(TIME_COUNTER_M13<=0)
					{
						CASE_ECAT_M13_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
			{
					inReadBuffer1_M13.value.arr.size = 2;
					ret_iosRead_Minimotor_M13 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M13, &numByteRead1_M13, 150);
					if (ret_iosRead_Minimotor_M13 == RTPLC_STATUS_OK) 
					{
						WORD_CURRENT_ECAT_M13 = (short) (  ( (dataRead1_M13[1]<<8) & 0xFF00)+(dataRead1_M13[0] & 0xFF));
						R[R_ACTUAL_CURRENT_M13] = ((double) WORD_CURRENT_ECAT_M13) / 1000.0;

						if(R[R_ACTUAL_CURRENT_M13]>R[R_MAX_CURRENT_M13]) R[R_MAX_CURRENT_M13]=R[R_ACTUAL_CURRENT_M13];
						if(R[R_ACTUAL_CURRENT_M13]<R[R_MIN_CURRENT_M13]) R[R_MIN_CURRENT_M13]=R[R_ACTUAL_CURRENT_M13];

						//rtplctrace4(1,_T("%x %x = dataRead1_M13[1].dataRead1_M13[0]"),dataRead1_M13[1],dataRead1_M13[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M13_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M13=(%d)"),CASE_ECAT_M13_MINIMOTOR,ret_iosRead_Minimotor_M13);

						CASE_ECAT_M13_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M13)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M13_MINIMOTOR=(%d)"),CASE_ECAT_M13_MINIMOTOR);
						CASE_ECAT_M13_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
			{
					inReadBuffer1_M13.value.arr.size = 2;
					ret_iosRead_Minimotor_M13 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M13, &numByteRead1_M13, 150);
					if (ret_iosRead_Minimotor_M13 == RTPLC_STATUS_OK) 
					{
						WORD1_CURRENT_ECAT_M13 = (unsigned short) (  ( (dataRead1_M13[1]<<8) & 0xFF00)+(dataRead1_M13[0] & 0xFF));
						R[R_PARAM_MAX_CURRENT_M13] = ((double) WORD1_CURRENT_ECAT_M13) / 1000.0;

						//rtplctrace4(1,_T("%x %x = dataRead1_M13[1].dataRead1_M13[0]"),dataRead1_M13[1],dataRead1_M13[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M13_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M13=(%d)"),CASE_ECAT_M13_MINIMOTOR,ret_iosRead_Minimotor_M13);

						CASE_ECAT_M13_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M13)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M13_MINIMOTOR=(%d)"),CASE_ECAT_M13_MINIMOTOR);
						CASE_ECAT_M13_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
			{
					inReadBuffer2_M13.value.arr.size = 2;
					ret_iosRead_Minimotor_M13 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M13, &numByteRead2_M13, 150);
					if (ret_iosRead_Minimotor_M13 == RTPLC_STATUS_OK) 
					{
						WORD1_VOLTAGE_ECAT_M13 = (unsigned short) (( (dataRead2_M13[1]<<8) & 0xFF00)+(dataRead2_M13[0] & 0xFF));
						
						R[R_ACTUAL_VOLT_M13] = ((double) WORD1_VOLTAGE_ECAT_M13) /10.0;

						if(R[R_ACTUAL_VOLT_M13]>R[R_MAX_VOLT_M13]) R[R_MAX_VOLT_M13]=R[R_ACTUAL_VOLT_M13];
						if(R[R_ACTUAL_VOLT_M13]<R[R_MIN_VOLT_M13]) R[R_MIN_VOLT_M13]=R[R_ACTUAL_VOLT_M13];

						//rtplctrace4(1,_T("%x %x = dataRead2_M13[1].dataRead2_M13[0]"),dataRead2_M13[1],dataRead2_M13[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M13_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M13=(%d)"),CASE_ECAT_M13_MINIMOTOR,ret_iosRead_Minimotor_M13);

						CASE_ECAT_M13_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M13)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M13_MINIMOTOR=(%d)"),CASE_ECAT_M13_MINIMOTOR);
						CASE_ECAT_M13_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
			{
					inReadBuffer3_M13.value.arr.size = 4;
					ret_iosRead_Minimotor_M13 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M13, &numByteRead3_M13, 150);
					if (ret_iosRead_Minimotor_M13 == RTPLC_STATUS_OK) 
					{
						WORD_COUNT_FLT_ECAT_M13 = (unsigned long) (  ( (dataRead3_M13[3]<<24) & 0xFF000000) + ( (dataRead3_M13[2]<<16) & 0xFF0000) + 
						                                               ( (dataRead3_M13[1]<<8) & 0xFF00)+(dataRead3_M13[0] & 0xFF)   );
						
						R[R_COUNTER_FILTRO_M13] = (double) WORD_COUNT_FLT_ECAT_M13;

						//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M13[3].dataRead3_M13[2].dataRead3_M13[1].dataRead3_M13[0]"),dataRead3_M13[1],dataRead3_M13[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M13_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M13=(%d)"),CASE_ECAT_M13_MINIMOTOR,ret_iosRead_Minimotor_M13);

						CASE_ECAT_M13_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M13)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M13_MINIMOTOR=(%d)"),CASE_ECAT_M13_MINIMOTOR);
						CASE_ECAT_M13_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;			
			
		case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
			{
					inReadBuffer4_M13.value.arr.size = 2;
					ret_iosRead_Minimotor_M13 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M13, &numByteRead4_M13, 150);
					if (ret_iosRead_Minimotor_M13 == RTPLC_STATUS_OK) 
					{
						WORD_OUTPUT_PWR_ECAT_M13 = (short) (  ( (dataRead4_M13[1]<<8) & 0xFF00)+(dataRead4_M13[0] & 0xFF)   );
						
						R[R_OUTPUT_PWR_M13] = ((double) WORD_OUTPUT_PWR_ECAT_M13) / 1.0;

						//rtplctrace4(1,_T("%x %x = dataRead4_M13[1].dataRead4_M13[0]"),dataRead4_M13[1],dataRead4_M13[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M13_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M13=(%d)"),CASE_ECAT_M13_MINIMOTOR,ret_iosRead_Minimotor_M13);

						CASE_ECAT_M13_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
						
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M13)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M13_MINIMOTOR=(%d)"),CASE_ECAT_M13_MINIMOTOR);
						CASE_ECAT_M13_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_ERROR_ETH_MINIMOTOR:
			{
				if(minimotorHandle != 0)
				{
					iosClose(minimotorHandle);
					minimotorHandle = 0;
					//rtplctrace4(1,_T("CASE_ECAT_M13_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1011-"),CASE_ECAT_M13_MINIMOTOR);
					CASE_ECAT_M13_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
				else
				{
					CASE_ECAT_M13_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}

			}
			break;			

		}
	}
	else
	{
	}

	if(CONF_ASSE_M14)
	{
		static ULONG minimotorHandle = 0;
		static RTPLC_STRING buffer_str = {0};
		static char *buffer = IND_ETHERCAT_M14;
		static short int TIME_COUNTER_M14 = 0;
		
		inReadBuffer1_M14.value.arr.data = dataRead1_M14;
		inReadBuffer1_M14.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		inReadBuffer2_M14.value.arr.data = dataRead2_M14;
		inReadBuffer2_M14.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer3_M14.value.arr.data = dataRead3_M14;
		inReadBuffer3_M14.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer4_M14.value.arr.data = dataRead4_M14;
		inReadBuffer4_M14.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		switch (CASE_ECAT_M14_MINIMOTOR)
		{
		case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
			{
				if(PON)
				{
					memset(&buffer_str, 0, sizeof(buffer_str));
					buffer_str.size = _strlen(buffer);
					buffer_str.sz = buffer;
				}
				
				if(O_MOV_M14 && (R[R_ABIL_READ_SDO_M14]>0.5))
				{
					CASE_ECAT_M14_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
			}
			break;

		case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
			{
					ret_iosOpen_Minimotor_M14 = iosOpen(&buffer_str, &minimotorHandle);
					if (ret_iosOpen_Minimotor_M14 == RTPLC_STATUS_OK) 
					{
						//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
						//rtplctrace4(1,_T("CASE_ECAT_M14_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1014-> ret_iosOpen_Minimotor_M14=(%d)"),CASE_ECAT_M14_MINIMOTOR,ret_iosOpen_Minimotor_M14);

						R[R_MAX_CURRENT_M14] = -1000.0;
						R[R_MIN_CURRENT_M14] = 1000.0;

						R[R_MAX_VOLT_M14] = -1000.0;
						R[R_MIN_VOLT_M14] = 1000.0;
						
						CASE_ECAT_M14_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M14)) 
					{
						//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
						//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1014-> CASE_ECAT_M14_MINIMOTOR=(%d)"),CASE_ECAT_M14_MINIMOTOR);
						CASE_ECAT_M14_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
				
			}
			break;
			
		case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
		{
			if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
			{
				TIME_COUNTER_M14 = 1;
			}
			else
			{
				TIME_COUNTER_M14 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
			}
			CASE_ECAT_M14_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
		}
		break;
		
		case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
			{
					if((R[R_ABIL_READ_SDO_M14]>0.5) && (TIME_COUNTER_M14 > 0))
						TIME_COUNTER_M14--;

					if(TIME_COUNTER_M14<=0)
					{
						CASE_ECAT_M14_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
			{
					inReadBuffer1_M14.value.arr.size = 2;
					ret_iosRead_Minimotor_M14 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M14, &numByteRead1_M14, 150);
					if (ret_iosRead_Minimotor_M14 == RTPLC_STATUS_OK) 
					{
						WORD_CURRENT_ECAT_M14 = (short) (  ( (dataRead1_M14[1]<<8) & 0xFF00)+(dataRead1_M14[0] & 0xFF));
						R[R_ACTUAL_CURRENT_M14] = ((double) WORD_CURRENT_ECAT_M14) / 1000.0;

						if(R[R_ACTUAL_CURRENT_M14]>R[R_MAX_CURRENT_M14]) R[R_MAX_CURRENT_M14]=R[R_ACTUAL_CURRENT_M14];
						if(R[R_ACTUAL_CURRENT_M14]<R[R_MIN_CURRENT_M14]) R[R_MIN_CURRENT_M14]=R[R_ACTUAL_CURRENT_M14];

						//rtplctrace4(1,_T("%x %x = dataRead1_M14[1].dataRead1_M14[0]"),dataRead1_M14[1],dataRead1_M14[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M14_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M14=(%d)"),CASE_ECAT_M14_MINIMOTOR,ret_iosRead_Minimotor_M14);

						CASE_ECAT_M14_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M14)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M14_MINIMOTOR=(%d)"),CASE_ECAT_M14_MINIMOTOR);
						CASE_ECAT_M14_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
			{
					inReadBuffer1_M14.value.arr.size = 2;
					ret_iosRead_Minimotor_M14 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M14, &numByteRead1_M14, 150);
					if (ret_iosRead_Minimotor_M14 == RTPLC_STATUS_OK) 
					{
						WORD1_CURRENT_ECAT_M14 = (unsigned short) (  ( (dataRead1_M14[1]<<8) & 0xFF00)+(dataRead1_M14[0] & 0xFF));
						R[R_PARAM_MAX_CURRENT_M14] = ((double) WORD1_CURRENT_ECAT_M14) / 1000.0;

						//rtplctrace4(1,_T("%x %x = dataRead1_M14[1].dataRead1_M14[0]"),dataRead1_M14[1],dataRead1_M14[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M14_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M14=(%d)"),CASE_ECAT_M14_MINIMOTOR,ret_iosRead_Minimotor_M14);

						CASE_ECAT_M14_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M14)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M14_MINIMOTOR=(%d)"),CASE_ECAT_M14_MINIMOTOR);
						CASE_ECAT_M14_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
			{
					inReadBuffer2_M14.value.arr.size = 2;
					ret_iosRead_Minimotor_M14 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M14, &numByteRead2_M14, 150);
					if (ret_iosRead_Minimotor_M14 == RTPLC_STATUS_OK) 
					{
						WORD1_VOLTAGE_ECAT_M14 = (unsigned short) (( (dataRead2_M14[1]<<8) & 0xFF00)+(dataRead2_M14[0] & 0xFF));
						
						R[R_ACTUAL_VOLT_M14] = ((double) WORD1_VOLTAGE_ECAT_M14) /10.0;

						if(R[R_ACTUAL_VOLT_M14]>R[R_MAX_VOLT_M14]) R[R_MAX_VOLT_M14]=R[R_ACTUAL_VOLT_M14];
						if(R[R_ACTUAL_VOLT_M14]<R[R_MIN_VOLT_M14]) R[R_MIN_VOLT_M14]=R[R_ACTUAL_VOLT_M14];

						//rtplctrace4(1,_T("%x %x = dataRead2_M14[1].dataRead2_M14[0]"),dataRead2_M14[1],dataRead2_M14[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M14_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M14=(%d)"),CASE_ECAT_M14_MINIMOTOR,ret_iosRead_Minimotor_M14);

						CASE_ECAT_M14_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M14)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M14_MINIMOTOR=(%d)"),CASE_ECAT_M14_MINIMOTOR);
						CASE_ECAT_M14_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
			{
					inReadBuffer3_M14.value.arr.size = 4;
					ret_iosRead_Minimotor_M14 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M14, &numByteRead3_M14, 150);
					if (ret_iosRead_Minimotor_M14 == RTPLC_STATUS_OK) 
					{
						WORD_COUNT_FLT_ECAT_M14 = (unsigned long) (  ( (dataRead3_M14[3]<<24) & 0xFF000000) + ( (dataRead3_M14[2]<<16) & 0xFF0000) + 
						                                               ( (dataRead3_M14[1]<<8) & 0xFF00)+(dataRead3_M14[0] & 0xFF)   );
						
						R[R_COUNTER_FILTRO_M14] = (double) WORD_COUNT_FLT_ECAT_M14;

						//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M14[3].dataRead3_M14[2].dataRead3_M14[1].dataRead3_M14[0]"),dataRead3_M14[1],dataRead3_M14[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M14_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M14=(%d)"),CASE_ECAT_M14_MINIMOTOR,ret_iosRead_Minimotor_M14);

						CASE_ECAT_M14_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M14)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M14_MINIMOTOR=(%d)"),CASE_ECAT_M14_MINIMOTOR);
						CASE_ECAT_M14_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;			
			
		case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
			{
					inReadBuffer4_M14.value.arr.size = 2;
					ret_iosRead_Minimotor_M14 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M14, &numByteRead4_M14, 150);
					if (ret_iosRead_Minimotor_M14 == RTPLC_STATUS_OK) 
					{
						WORD_OUTPUT_PWR_ECAT_M14 = (short) (  ( (dataRead4_M14[1]<<8) & 0xFF00)+(dataRead4_M14[0] & 0xFF)   );
						
						R[R_OUTPUT_PWR_M14] = ((double) WORD_OUTPUT_PWR_ECAT_M14) / 1.0;

						//rtplctrace4(1,_T("%x %x = dataRead4_M14[1].dataRead4_M14[0]"),dataRead4_M14[1],dataRead4_M14[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M14_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M14=(%d)"),CASE_ECAT_M14_MINIMOTOR,ret_iosRead_Minimotor_M14);

						CASE_ECAT_M14_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
						
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M14)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M14_MINIMOTOR=(%d)"),CASE_ECAT_M14_MINIMOTOR);
						CASE_ECAT_M14_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_ERROR_ETH_MINIMOTOR:
			{
				if(minimotorHandle != 0)
				{
					iosClose(minimotorHandle);
					minimotorHandle = 0;
					//rtplctrace4(1,_T("CASE_ECAT_M14_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1014-"),CASE_ECAT_M14_MINIMOTOR);
					CASE_ECAT_M14_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
				else
				{
					CASE_ECAT_M14_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}

			}
			break;			

		}
	}
	else
	{
	}

	if(CONF_ASSE_M15)
	{
		static ULONG minimotorHandle = 0;
		static RTPLC_STRING buffer_str = {0};
		static char *buffer = IND_ETHERCAT_M15;
		static short int TIME_COUNTER_M15 = 0;
		
		inReadBuffer1_M15.value.arr.data = dataRead1_M15;
		inReadBuffer1_M15.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
		
		inReadBuffer2_M15.value.arr.data = dataRead2_M15;
		inReadBuffer2_M15.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer3_M15.value.arr.data = dataRead3_M15;
		inReadBuffer3_M15.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		inReadBuffer4_M15.value.arr.data = dataRead4_M15;
		inReadBuffer4_M15.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

		switch (CASE_ECAT_M15_MINIMOTOR)
		{
		case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
			{
				if(PON)
				{
					memset(&buffer_str, 0, sizeof(buffer_str));
					buffer_str.size = _strlen(buffer);
					buffer_str.sz = buffer;
				}
				
				if(O_MOV_M15 && (R[R_ABIL_READ_SDO_M15]>0.5))
				{
					CASE_ECAT_M15_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
			}
			break;

		case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
			{
					ret_iosOpen_Minimotor_M15 = iosOpen(&buffer_str, &minimotorHandle);
					if (ret_iosOpen_Minimotor_M15 == RTPLC_STATUS_OK) 
					{
						//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
						//rtplctrace4(1,_T("CASE_ECAT_M15_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1017-> ret_iosOpen_Minimotor_M15=(%d)"),CASE_ECAT_M15_MINIMOTOR,ret_iosOpen_Minimotor_M15);

						R[R_MAX_CURRENT_M15] = -1000.0;
						R[R_MIN_CURRENT_M15] = 1000.0;

						R[R_MAX_VOLT_M15] = -1000.0;
						R[R_MIN_VOLT_M15] = 1000.0;
						
						CASE_ECAT_M15_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M15)) 
					{
						//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
						//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1017-> CASE_ECAT_M15_MINIMOTOR=(%d)"),CASE_ECAT_M15_MINIMOTOR);
						CASE_ECAT_M15_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
				
			}
			break;
			
		case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
		{
			if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
			{
				TIME_COUNTER_M15 = 1;
			}
			else
			{
				TIME_COUNTER_M15 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
			}
			CASE_ECAT_M15_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
		}
		break;
		
		case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
			{
					if((R[R_ABIL_READ_SDO_M15]>0.5) && (TIME_COUNTER_M15 > 0))
						TIME_COUNTER_M15--;

					if(TIME_COUNTER_M15<=0)
					{
						CASE_ECAT_M15_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
			{
					inReadBuffer1_M15.value.arr.size = 2;
					ret_iosRead_Minimotor_M15 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M15, &numByteRead1_M15, 150);
					if (ret_iosRead_Minimotor_M15 == RTPLC_STATUS_OK) 
					{
						WORD_CURRENT_ECAT_M15 = (short) (  ( (dataRead1_M15[1]<<8) & 0xFF00)+(dataRead1_M15[0] & 0xFF));
						R[R_ACTUAL_CURRENT_M15] = ((double) WORD_CURRENT_ECAT_M15) / 1000.0;

						if(R[R_ACTUAL_CURRENT_M15]>R[R_MAX_CURRENT_M15]) R[R_MAX_CURRENT_M15]=R[R_ACTUAL_CURRENT_M15];
						if(R[R_ACTUAL_CURRENT_M15]<R[R_MIN_CURRENT_M15]) R[R_MIN_CURRENT_M15]=R[R_ACTUAL_CURRENT_M15];

						//rtplctrace4(1,_T("%x %x = dataRead1_M15[1].dataRead1_M15[0]"),dataRead1_M15[1],dataRead1_M15[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M15_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M15=(%d)"),CASE_ECAT_M15_MINIMOTOR,ret_iosRead_Minimotor_M15);

						CASE_ECAT_M15_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M15)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M15_MINIMOTOR=(%d)"),CASE_ECAT_M15_MINIMOTOR);
						CASE_ECAT_M15_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
			{
					inReadBuffer1_M15.value.arr.size = 2;
					ret_iosRead_Minimotor_M15 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M15, &numByteRead1_M15, 150);
					if (ret_iosRead_Minimotor_M15 == RTPLC_STATUS_OK) 
					{
						WORD1_CURRENT_ECAT_M15 = (unsigned short) (  ( (dataRead1_M15[1]<<8) & 0xFF00)+(dataRead1_M15[0] & 0xFF));
						R[R_PARAM_MAX_CURRENT_M15] = ((double) WORD1_CURRENT_ECAT_M15) / 1000.0;

						//rtplctrace4(1,_T("%x %x = dataRead1_M15[1].dataRead1_M15[0]"),dataRead1_M15[1],dataRead1_M15[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M15_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M15=(%d)"),CASE_ECAT_M15_MINIMOTOR,ret_iosRead_Minimotor_M15);

						CASE_ECAT_M15_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M15)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M15_MINIMOTOR=(%d)"),CASE_ECAT_M15_MINIMOTOR);
						CASE_ECAT_M15_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
			{
					inReadBuffer2_M15.value.arr.size = 2;
					ret_iosRead_Minimotor_M15 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M15, &numByteRead2_M15, 150);
					if (ret_iosRead_Minimotor_M15 == RTPLC_STATUS_OK) 
					{
						WORD1_VOLTAGE_ECAT_M15 = (unsigned short) (( (dataRead2_M15[1]<<8) & 0xFF00)+(dataRead2_M15[0] & 0xFF));
						
						R[R_ACTUAL_VOLT_M15] = ((double) WORD1_VOLTAGE_ECAT_M15) /10.0;

						if(R[R_ACTUAL_VOLT_M15]>R[R_MAX_VOLT_M15]) R[R_MAX_VOLT_M15]=R[R_ACTUAL_VOLT_M15];
						if(R[R_ACTUAL_VOLT_M15]<R[R_MIN_VOLT_M15]) R[R_MIN_VOLT_M15]=R[R_ACTUAL_VOLT_M15];

						//rtplctrace4(1,_T("%x %x = dataRead2_M15[1].dataRead2_M15[0]"),dataRead2_M15[1],dataRead2_M15[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M15_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M15=(%d)"),CASE_ECAT_M15_MINIMOTOR,ret_iosRead_Minimotor_M15);

						CASE_ECAT_M15_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M15)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M15_MINIMOTOR=(%d)"),CASE_ECAT_M15_MINIMOTOR);
						CASE_ECAT_M15_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;
			
		case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
			{
					inReadBuffer3_M15.value.arr.size = 4;
					ret_iosRead_Minimotor_M15 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M15, &numByteRead3_M15, 150);
					if (ret_iosRead_Minimotor_M15 == RTPLC_STATUS_OK) 
					{
						WORD_COUNT_FLT_ECAT_M15 = (unsigned long) (  ( (dataRead3_M15[3]<<24) & 0xFF000000) + ( (dataRead3_M15[2]<<16) & 0xFF0000) + 
						                                               ( (dataRead3_M15[1]<<8) & 0xFF00)+(dataRead3_M15[0] & 0xFF)   );
						
						R[R_COUNTER_FILTRO_M15] = (double) WORD_COUNT_FLT_ECAT_M15;

						//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M15[3].dataRead3_M15[2].dataRead3_M15[1].dataRead3_M15[0]"),dataRead3_M15[1],dataRead3_M15[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M15_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M15=(%d)"),CASE_ECAT_M15_MINIMOTOR,ret_iosRead_Minimotor_M15);

						CASE_ECAT_M15_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M15)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M15_MINIMOTOR=(%d)"),CASE_ECAT_M15_MINIMOTOR);
						CASE_ECAT_M15_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;			
			
		case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
			{
					inReadBuffer4_M15.value.arr.size = 2;
					ret_iosRead_Minimotor_M15 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M15, &numByteRead4_M15, 150);
					if (ret_iosRead_Minimotor_M15 == RTPLC_STATUS_OK) 
					{
						WORD_OUTPUT_PWR_ECAT_M15 = (short) (  ( (dataRead4_M15[1]<<8) & 0xFF00)+(dataRead4_M15[0] & 0xFF)   );
						
						R[R_OUTPUT_PWR_M15] = ((double) WORD_OUTPUT_PWR_ECAT_M15) / 1.0;

						//rtplctrace4(1,_T("%x %x = dataRead4_M15[1].dataRead4_M15[0]"),dataRead4_M15[1],dataRead4_M15[0]);
						//rtplctrace4(1,_T("CASE_ECAT_M15_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M15=(%d)"),CASE_ECAT_M15_MINIMOTOR,ret_iosRead_Minimotor_M15);

						CASE_ECAT_M15_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
						
					}
					else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M15)) 
					{
						//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M15_MINIMOTOR=(%d)"),CASE_ECAT_M15_MINIMOTOR);
						CASE_ECAT_M15_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
					}
			}
			break;

		case STATO_ERROR_ETH_MINIMOTOR:
			{
				if(minimotorHandle != 0)
				{
					iosClose(minimotorHandle);
					minimotorHandle = 0;
					//rtplctrace4(1,_T("CASE_ECAT_M15_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1017-"),CASE_ECAT_M15_MINIMOTOR);
					CASE_ECAT_M15_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}
				else
				{
					CASE_ECAT_M15_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
				}

			}
			break;			

		}
	}
	else
	{
	}

	//if(CONF_ASSE_M16)
	//{
	//	static ULONG minimotorHandle = 0;
	//	static RTPLC_STRING buffer_str = {0};
	//	static char *buffer = IND_ETHERCAT_M16;
	//	static short int TIME_COUNTER_M16 = 0;
	//	
	//	inReadBuffer1_M16.value.arr.data = dataRead1_M16;
	//	inReadBuffer1_M16.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
	//	
	//	inReadBuffer2_M16.value.arr.data = dataRead2_M16;
	//	inReadBuffer2_M16.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer3_M16.value.arr.data = dataRead3_M16;
	//	inReadBuffer3_M16.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer4_M16.value.arr.data = dataRead4_M16;
	//	inReadBuffer4_M16.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	switch (CASE_ECAT_M16_MINIMOTOR)
	//	{
	//	case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
	//		{
	//			if(PON)
	//			{
	//				memset(&buffer_str, 0, sizeof(buffer_str));
	//				buffer_str.size = _strlen(buffer);
	//				buffer_str.sz = buffer;
	//			}
	//			
	//			if(O_MOV_M16 && (R[R_ABIL_READ_SDO_M16]>0.5))
	//			{
	//				CASE_ECAT_M16_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//		}
	//		break;

	//	case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
	//		{
	//				ret_iosOpen_Minimotor_M16 = iosOpen(&buffer_str, &minimotorHandle);
	//				if (ret_iosOpen_Minimotor_M16 == RTPLC_STATUS_OK) 
	//				{
	//					//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
	//					//rtplctrace4(1,_T("CASE_ECAT_M16_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1020-> ret_iosOpen_Minimotor_M16=(%d)"),CASE_ECAT_M16_MINIMOTOR,ret_iosOpen_Minimotor_M16);

	//					R[R_MAX_CURRENT_M16] = -1000.0;
	//					R[R_MIN_CURRENT_M16] = 1000.0;

	//					R[R_MAX_VOLT_M16] = -1000.0;
	//					R[R_MIN_VOLT_M16] = 1000.0;
	//					
	//					CASE_ECAT_M16_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M16)) 
	//				{
	//					//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
	//					//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1020-> CASE_ECAT_M16_MINIMOTOR=(%d)"),CASE_ECAT_M16_MINIMOTOR);
	//					CASE_ECAT_M16_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//			
	//		}
	//		break;
	//		
	//	case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
	//	{
	//		if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
	//		{
	//			TIME_COUNTER_M16 = 1;
	//		}
	//		else
	//		{
	//			TIME_COUNTER_M16 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
	//		}
	//		CASE_ECAT_M16_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
	//	}
	//	break;
	//	
	//	case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
	//		{
	//				if((R[R_ABIL_READ_SDO_M16]>0.5) && (TIME_COUNTER_M16 > 0))
	//					TIME_COUNTER_M16--;

	//				if(TIME_COUNTER_M16<=0)
	//				{
	//					CASE_ECAT_M16_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
	//		{
	//				inReadBuffer1_M16.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M16 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M16, &numByteRead1_M16, 150);
	//				if (ret_iosRead_Minimotor_M16 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_CURRENT_ECAT_M16 = (short) (  ( (dataRead1_M16[1]<<8) & 0xFF00)+(dataRead1_M16[0] & 0xFF));
	//					R[R_ACTUAL_CURRENT_M16] = ((double) WORD_CURRENT_ECAT_M16) / 1000.0;

	//					if(R[R_ACTUAL_CURRENT_M16]>R[R_MAX_CURRENT_M16]) R[R_MAX_CURRENT_M16]=R[R_ACTUAL_CURRENT_M16];
	//					if(R[R_ACTUAL_CURRENT_M16]<R[R_MIN_CURRENT_M16]) R[R_MIN_CURRENT_M16]=R[R_ACTUAL_CURRENT_M16];

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M16[1].dataRead1_M16[0]"),dataRead1_M16[1],dataRead1_M16[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M16_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M16=(%d)"),CASE_ECAT_M16_MINIMOTOR,ret_iosRead_Minimotor_M16);

	//					CASE_ECAT_M16_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M16)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M16_MINIMOTOR=(%d)"),CASE_ECAT_M16_MINIMOTOR);
	//					CASE_ECAT_M16_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
	//		{
	//				inReadBuffer1_M16.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M16 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M16, &numByteRead1_M16, 150);
	//				if (ret_iosRead_Minimotor_M16 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_CURRENT_ECAT_M16 = (unsigned short) (  ( (dataRead1_M16[1]<<8) & 0xFF00)+(dataRead1_M16[0] & 0xFF));
	//					R[R_PARAM_MAX_CURRENT_M16] = ((double) WORD1_CURRENT_ECAT_M16) / 1000.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M16[1].dataRead1_M16[0]"),dataRead1_M16[1],dataRead1_M16[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M16_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M16=(%d)"),CASE_ECAT_M16_MINIMOTOR,ret_iosRead_Minimotor_M16);

	//					CASE_ECAT_M16_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M16)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M16_MINIMOTOR=(%d)"),CASE_ECAT_M16_MINIMOTOR);
	//					CASE_ECAT_M16_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
	//		{
	//				inReadBuffer2_M16.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M16 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M16, &numByteRead2_M16, 150);
	//				if (ret_iosRead_Minimotor_M16 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_VOLTAGE_ECAT_M16 = (unsigned short) (( (dataRead2_M16[1]<<8) & 0xFF00)+(dataRead2_M16[0] & 0xFF));
	//					
	//					R[R_ACTUAL_VOLT_M16] = ((double) WORD1_VOLTAGE_ECAT_M16) /10.0;

	//					if(R[R_ACTUAL_VOLT_M16]>R[R_MAX_VOLT_M16]) R[R_MAX_VOLT_M16]=R[R_ACTUAL_VOLT_M16];
	//					if(R[R_ACTUAL_VOLT_M16]<R[R_MIN_VOLT_M16]) R[R_MIN_VOLT_M16]=R[R_ACTUAL_VOLT_M16];

	//					//rtplctrace4(1,_T("%x %x = dataRead2_M16[1].dataRead2_M16[0]"),dataRead2_M16[1],dataRead2_M16[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M16_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M16=(%d)"),CASE_ECAT_M16_MINIMOTOR,ret_iosRead_Minimotor_M16);

	//					CASE_ECAT_M16_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M16)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M16_MINIMOTOR=(%d)"),CASE_ECAT_M16_MINIMOTOR);
	//					CASE_ECAT_M16_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
	//		{
	//				inReadBuffer3_M16.value.arr.size = 4;
	//				ret_iosRead_Minimotor_M16 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M16, &numByteRead3_M16, 150);
	//				if (ret_iosRead_Minimotor_M16 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_COUNT_FLT_ECAT_M16 = (unsigned long) (  ( (dataRead3_M16[3]<<24) & 0xFF000000) + ( (dataRead3_M16[2]<<16) & 0xFF0000) + 
	//					                                               ( (dataRead3_M16[1]<<8) & 0xFF00)+(dataRead3_M16[0] & 0xFF)   );
	//					
	//					R[R_COUNTER_FILTRO_M16] = (double) WORD_COUNT_FLT_ECAT_M16;

	//					//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M16[3].dataRead3_M16[2].dataRead3_M16[1].dataRead3_M16[0]"),dataRead3_M16[1],dataRead3_M16[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M16_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M16=(%d)"),CASE_ECAT_M16_MINIMOTOR,ret_iosRead_Minimotor_M16);

	//					CASE_ECAT_M16_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M16)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M16_MINIMOTOR=(%d)"),CASE_ECAT_M16_MINIMOTOR);
	//					CASE_ECAT_M16_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;			
	//		
	//	case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
	//		{
	//				inReadBuffer4_M16.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M16 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M16, &numByteRead4_M16, 150);
	//				if (ret_iosRead_Minimotor_M16 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_OUTPUT_PWR_ECAT_M16 = (short) (  ( (dataRead4_M16[1]<<8) & 0xFF00)+(dataRead4_M16[0] & 0xFF)   );
	//					
	//					R[R_OUTPUT_PWR_M16] = ((double) WORD_OUTPUT_PWR_ECAT_M16) / 1.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead4_M16[1].dataRead4_M16[0]"),dataRead4_M16[1],dataRead4_M16[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M16_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M16=(%d)"),CASE_ECAT_M16_MINIMOTOR,ret_iosRead_Minimotor_M16);

	//					CASE_ECAT_M16_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//					
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M16)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M16_MINIMOTOR=(%d)"),CASE_ECAT_M16_MINIMOTOR);
	//					CASE_ECAT_M16_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_ERROR_ETH_MINIMOTOR:
	//		{
	//			if(minimotorHandle != 0)
	//			{
	//				iosClose(minimotorHandle);
	//				minimotorHandle = 0;
	//				//rtplctrace4(1,_T("CASE_ECAT_M16_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1020-"),CASE_ECAT_M16_MINIMOTOR);
	//				CASE_ECAT_M16_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//			else
	//			{
	//				CASE_ECAT_M16_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}

	//		}
	//		break;			

	//	}
	//}
	//else
	//{
	//}

	//if(CONF_ASSE_M17)
	//{
	//	static ULONG minimotorHandle = 0;
	//	static RTPLC_STRING buffer_str = {0};
	//	static char *buffer = IND_ETHERCAT_M17;
	//	static short int TIME_COUNTER_M17 = 0;
	//	
	//	inReadBuffer1_M17.value.arr.data = dataRead1_M17;
	//	inReadBuffer1_M17.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
	//	
	//	inReadBuffer2_M17.value.arr.data = dataRead2_M17;
	//	inReadBuffer2_M17.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer3_M17.value.arr.data = dataRead3_M17;
	//	inReadBuffer3_M17.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer4_M17.value.arr.data = dataRead4_M17;
	//	inReadBuffer4_M17.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	switch (CASE_ECAT_M17_MINIMOTOR)
	//	{
	//	case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
	//		{
	//			if(PON)
	//			{
	//				memset(&buffer_str, 0, sizeof(buffer_str));
	//				buffer_str.size = _strlen(buffer);
	//				buffer_str.sz = buffer;
	//			}
	//			
	//			if(O_MOV_M17 && (R[R_ABIL_READ_SDO_M17]>0.5))
	//			{
	//				CASE_ECAT_M17_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//		}
	//		break;

	//	case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
	//		{
	//				ret_iosOpen_Minimotor_M17 = iosOpen(&buffer_str, &minimotorHandle);
	//				if (ret_iosOpen_Minimotor_M17 == RTPLC_STATUS_OK) 
	//				{
	//					//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
	//					//rtplctrace4(1,_T("CASE_ECAT_M17_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1023-> ret_iosOpen_Minimotor_M17=(%d)"),CASE_ECAT_M17_MINIMOTOR,ret_iosOpen_Minimotor_M17);

	//					R[R_MAX_CURRENT_M17] = -1000.0;
	//					R[R_MIN_CURRENT_M17] = 1000.0;

	//					R[R_MAX_VOLT_M17] = -1000.0;
	//					R[R_MIN_VOLT_M17] = 1000.0;
	//					
	//					CASE_ECAT_M17_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M17)) 
	//				{
	//					//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
	//					//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1023-> CASE_ECAT_M17_MINIMOTOR=(%d)"),CASE_ECAT_M17_MINIMOTOR);
	//					CASE_ECAT_M17_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//			
	//		}
	//		break;
	//		
	//	case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
	//	{
	//		if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
	//		{
	//			TIME_COUNTER_M17 = 1;
	//		}
	//		else
	//		{
	//			TIME_COUNTER_M17 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
	//		}
	//		CASE_ECAT_M17_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
	//	}
	//	break;
	//	
	//	case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
	//		{
	//				if((R[R_ABIL_READ_SDO_M17]>0.5) && (TIME_COUNTER_M17 > 0))
	//					TIME_COUNTER_M17--;

	//				if(TIME_COUNTER_M17<=0)
	//				{
	//					CASE_ECAT_M17_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
	//		{
	//				inReadBuffer1_M17.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M17 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M17, &numByteRead1_M17, 150);
	//				if (ret_iosRead_Minimotor_M17 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_CURRENT_ECAT_M17 = (short) (  ( (dataRead1_M17[1]<<8) & 0xFF00)+(dataRead1_M17[0] & 0xFF));
	//					R[R_ACTUAL_CURRENT_M17] = ((double) WORD_CURRENT_ECAT_M17) / 1000.0;

	//					if(R[R_ACTUAL_CURRENT_M17]>R[R_MAX_CURRENT_M17]) R[R_MAX_CURRENT_M17]=R[R_ACTUAL_CURRENT_M17];
	//					if(R[R_ACTUAL_CURRENT_M17]<R[R_MIN_CURRENT_M17]) R[R_MIN_CURRENT_M17]=R[R_ACTUAL_CURRENT_M17];

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M17[1].dataRead1_M17[0]"),dataRead1_M17[1],dataRead1_M17[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M17_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M17=(%d)"),CASE_ECAT_M17_MINIMOTOR,ret_iosRead_Minimotor_M17);

	//					CASE_ECAT_M17_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M17)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M17_MINIMOTOR=(%d)"),CASE_ECAT_M17_MINIMOTOR);
	//					CASE_ECAT_M17_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
	//		{
	//				inReadBuffer1_M17.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M17 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M17, &numByteRead1_M17, 150);
	//				if (ret_iosRead_Minimotor_M17 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_CURRENT_ECAT_M17 = (unsigned short) (  ( (dataRead1_M17[1]<<8) & 0xFF00)+(dataRead1_M17[0] & 0xFF));
	//					R[R_PARAM_MAX_CURRENT_M17] = ((double) WORD1_CURRENT_ECAT_M17) / 1000.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M17[1].dataRead1_M17[0]"),dataRead1_M17[1],dataRead1_M17[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M17_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M17=(%d)"),CASE_ECAT_M17_MINIMOTOR,ret_iosRead_Minimotor_M17);

	//					CASE_ECAT_M17_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M17)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M17_MINIMOTOR=(%d)"),CASE_ECAT_M17_MINIMOTOR);
	//					CASE_ECAT_M17_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
	//		{
	//				inReadBuffer2_M17.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M17 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M17, &numByteRead2_M17, 150);
	//				if (ret_iosRead_Minimotor_M17 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_VOLTAGE_ECAT_M17 = (unsigned short) (( (dataRead2_M17[1]<<8) & 0xFF00)+(dataRead2_M17[0] & 0xFF));
	//					
	//					R[R_ACTUAL_VOLT_M17] = ((double) WORD1_VOLTAGE_ECAT_M17) /10.0;

	//					if(R[R_ACTUAL_VOLT_M17]>R[R_MAX_VOLT_M17]) R[R_MAX_VOLT_M17]=R[R_ACTUAL_VOLT_M17];
	//					if(R[R_ACTUAL_VOLT_M17]<R[R_MIN_VOLT_M17]) R[R_MIN_VOLT_M17]=R[R_ACTUAL_VOLT_M17];

	//					//rtplctrace4(1,_T("%x %x = dataRead2_M17[1].dataRead2_M17[0]"),dataRead2_M17[1],dataRead2_M17[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M17_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M17=(%d)"),CASE_ECAT_M17_MINIMOTOR,ret_iosRead_Minimotor_M17);

	//					CASE_ECAT_M17_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M17)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M17_MINIMOTOR=(%d)"),CASE_ECAT_M17_MINIMOTOR);
	//					CASE_ECAT_M17_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
	//		{
	//				inReadBuffer3_M17.value.arr.size = 4;
	//				ret_iosRead_Minimotor_M17 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M17, &numByteRead3_M17, 150);
	//				if (ret_iosRead_Minimotor_M17 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_COUNT_FLT_ECAT_M17 = (unsigned long) (  ( (dataRead3_M17[3]<<24) & 0xFF000000) + ( (dataRead3_M17[2]<<16) & 0xFF0000) + 
	//					                                               ( (dataRead3_M17[1]<<8) & 0xFF00)+(dataRead3_M17[0] & 0xFF)   );
	//					
	//					R[R_COUNTER_FILTRO_M17] = (double) WORD_COUNT_FLT_ECAT_M17;

	//					//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M17[3].dataRead3_M17[2].dataRead3_M17[1].dataRead3_M17[0]"),dataRead3_M17[1],dataRead3_M17[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M17_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M17=(%d)"),CASE_ECAT_M17_MINIMOTOR,ret_iosRead_Minimotor_M17);

	//					CASE_ECAT_M17_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M17)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M17_MINIMOTOR=(%d)"),CASE_ECAT_M17_MINIMOTOR);
	//					CASE_ECAT_M17_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;			
	//		
	//	case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
	//		{
	//				inReadBuffer4_M17.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M17 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M17, &numByteRead4_M17, 150);
	//				if (ret_iosRead_Minimotor_M17 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_OUTPUT_PWR_ECAT_M17 = (short) (  ( (dataRead4_M17[1]<<8) & 0xFF00)+(dataRead4_M17[0] & 0xFF)   );
	//					
	//					R[R_OUTPUT_PWR_M17] = ((double) WORD_OUTPUT_PWR_ECAT_M17) / 1.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead4_M17[1].dataRead4_M17[0]"),dataRead4_M17[1],dataRead4_M17[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M17_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M17=(%d)"),CASE_ECAT_M17_MINIMOTOR,ret_iosRead_Minimotor_M17);

	//					CASE_ECAT_M17_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//					
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M17)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M17_MINIMOTOR=(%d)"),CASE_ECAT_M17_MINIMOTOR);
	//					CASE_ECAT_M17_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_ERROR_ETH_MINIMOTOR:
	//		{
	//			if(minimotorHandle != 0)
	//			{
	//				iosClose(minimotorHandle);
	//				minimotorHandle = 0;
	//				//rtplctrace4(1,_T("CASE_ECAT_M17_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1023-"),CASE_ECAT_M17_MINIMOTOR);
	//				CASE_ECAT_M17_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//			else
	//			{
	//				CASE_ECAT_M17_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}

	//		}
	//		break;			

	//	}
	//}
	//else
	//{
	//}

	//if(CONF_ASSE_M18)
	//{
	//	static ULONG minimotorHandle = 0;
	//	static RTPLC_STRING buffer_str = {0};
	//	static char *buffer = IND_ETHERCAT_M18;
	//	static short int TIME_COUNTER_M18 = 0;
	//	
	//	inReadBuffer1_M18.value.arr.data = dataRead1_M18;
	//	inReadBuffer1_M18.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;
	//	
	//	inReadBuffer2_M18.value.arr.data = dataRead2_M18;
	//	inReadBuffer2_M18.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer3_M18.value.arr.data = dataRead3_M18;
	//	inReadBuffer3_M18.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	inReadBuffer4_M18.value.arr.data = dataRead4_M18;
	//	inReadBuffer4_M18.vt = RTPLC_FORMAT_ARRAY | RTPLC_FORMAT_UINT8;

	//	switch (CASE_ECAT_M18_MINIMOTOR)
	//	{
	//	case STATO_IDLE_ETH_MINIMOTOR: //stato di attesa
	//		{
	//			if(PON)
	//			{
	//				memset(&buffer_str, 0, sizeof(buffer_str));
	//				buffer_str.size = _strlen(buffer);
	//				buffer_str.sz = buffer;
	//			}
	//			
	//			if(O_MOV_M18 && (R[R_ABIL_READ_SDO_M18]>0.5))
	//			{
	//				CASE_ECAT_M18_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//		}
	//		break;

	//	case STATO_INI_ETH_MINIMOTOR:  // apertura del canale relativo al minimotor: iosOpen
	//		{
	//				ret_iosOpen_Minimotor_M18 = iosOpen(&buffer_str, &minimotorHandle);
	//				if (ret_iosOpen_Minimotor_M18 == RTPLC_STATUS_OK) 
	//				{
	//					//rtplctrace4(1,_T("minimotorHandle = %d"),minimotorHandle);
	//					//rtplctrace4(1,_T("CASE_ECAT_M18_MINIMOTOR=%d ***OK: Apertura canale Ethercat indirizzo_1026-> ret_iosOpen_Minimotor_M18=(%d)"),CASE_ECAT_M18_MINIMOTOR,ret_iosOpen_Minimotor_M18);

	//					R[R_MAX_CURRENT_M18] = -1000.0;
	//					R[R_MIN_CURRENT_M18] = 1000.0;

	//					R[R_MAX_VOLT_M18] = -1000.0;
	//					R[R_MIN_VOLT_M18] = 1000.0;
	//					
	//					CASE_ECAT_M18_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosOpen_Minimotor_M18)) 
	//				{
	//					//rtplctrace4(1,_T("buffer_str.sz = %s, buffer_str.size =%d"),buffer_str.sz, buffer_str.size);
	//					//rtplctrace4(1,_T("Impossibile aprire il canale Ethercat indirizzo_1026-> CASE_ECAT_M18_MINIMOTOR=(%d)"),CASE_ECAT_M18_MINIMOTOR);
	//					CASE_ECAT_M18_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//			
	//		}
	//		break;
	//		
	//	case STATO_SET_TIME_WAIT_ETH_MINIMOTOR:
	//	{
	//		if(R[R_NCICLI_DELAY_READ_SDO]<= 0.0)
	//		{
	//			TIME_COUNTER_M18 = 1;
	//		}
	//		else
	//		{
	//			TIME_COUNTER_M18 = (unsigned int) R[R_NCICLI_DELAY_READ_SDO];
	//		}
	//		CASE_ECAT_M18_MINIMOTOR = STATO_WAIT_ETH_MINIMOTOR;
	//	}
	//	break;
	//	
	//	case STATO_WAIT_ETH_MINIMOTOR:  // attesa selezione lettura corrente-tensione
	//		{
	//				if((R[R_ABIL_READ_SDO_M18]>0.5) && (TIME_COUNTER_M18 > 0))
	//					TIME_COUNTER_M18--;

	//				if(TIME_COUNTER_M18<=0)
	//				{
	//					CASE_ECAT_M18_MINIMOTOR = STATO_READIN1_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN1_ETH_MINIMOTOR:  // Lettura corrente attuale
	//		{
	//				inReadBuffer1_M18.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M18 = iosRead(minimotorHandle, 1, 0x3011, 0, 0, &inReadBuffer1_M18, &numByteRead1_M18, 150);
	//				if (ret_iosRead_Minimotor_M18 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_CURRENT_ECAT_M18 = (short) (  ( (dataRead1_M18[1]<<8) & 0xFF00)+(dataRead1_M18[0] & 0xFF));
	//					R[R_ACTUAL_CURRENT_M18] = ((double) WORD_CURRENT_ECAT_M18) / 1000.0;

	//					if(R[R_ACTUAL_CURRENT_M18]>R[R_MAX_CURRENT_M18]) R[R_MAX_CURRENT_M18]=R[R_ACTUAL_CURRENT_M18];
	//					if(R[R_ACTUAL_CURRENT_M18]<R[R_MIN_CURRENT_M18]) R[R_MIN_CURRENT_M18]=R[R_ACTUAL_CURRENT_M18];

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M18[1].dataRead1_M18[0]"),dataRead1_M18[1],dataRead1_M18[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M18_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3011-> ret_iosRead_Minimotor_M18=(%d)"),CASE_ECAT_M18_MINIMOTOR,ret_iosRead_Minimotor_M18);

	//					CASE_ECAT_M18_MINIMOTOR = STATO_READIN2_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M18)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M18_MINIMOTOR=(%d)"),CASE_ECAT_M18_MINIMOTOR);
	//					CASE_ECAT_M18_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_READIN2_ETH_MINIMOTOR:  // Lettura corrente massima impostata in parametro
	//		{
	//				inReadBuffer1_M18.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M18 = iosRead(minimotorHandle, 1, 0x3012, 0, 0, &inReadBuffer1_M18, &numByteRead1_M18, 150);
	//				if (ret_iosRead_Minimotor_M18 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_CURRENT_ECAT_M18 = (unsigned short) (  ( (dataRead1_M18[1]<<8) & 0xFF00)+(dataRead1_M18[0] & 0xFF));
	//					R[R_PARAM_MAX_CURRENT_M18] = ((double) WORD1_CURRENT_ECAT_M18) / 1000.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead1_M18[1].dataRead1_M18[0]"),dataRead1_M18[1],dataRead1_M18[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M18_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3012-> ret_iosRead_Minimotor_M18=(%d)"),CASE_ECAT_M18_MINIMOTOR,ret_iosRead_Minimotor_M18);

	//					CASE_ECAT_M18_MINIMOTOR = STATO_READIN3_ETH_MINIMOTOR;
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M18)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3011-> CASE_ECAT_M18_MINIMOTOR=(%d)"),CASE_ECAT_M18_MINIMOTOR);
	//					CASE_ECAT_M18_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN3_ETH_MINIMOTOR:  // Lettura tensione attuale
	//		{
	//				inReadBuffer2_M18.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M18 = iosRead(minimotorHandle, 1, 0x3010, 0, 0, &inReadBuffer2_M18, &numByteRead2_M18, 150);
	//				if (ret_iosRead_Minimotor_M18 == RTPLC_STATUS_OK) 
	//				{
	//					WORD1_VOLTAGE_ECAT_M18 = (unsigned short) (( (dataRead2_M18[1]<<8) & 0xFF00)+(dataRead2_M18[0] & 0xFF));
	//					
	//					R[R_ACTUAL_VOLT_M18] = ((double) WORD1_VOLTAGE_ECAT_M18) /10.0;

	//					if(R[R_ACTUAL_VOLT_M18]>R[R_MAX_VOLT_M18]) R[R_MAX_VOLT_M18]=R[R_ACTUAL_VOLT_M18];
	//					if(R[R_ACTUAL_VOLT_M18]<R[R_MIN_VOLT_M18]) R[R_MIN_VOLT_M18]=R[R_ACTUAL_VOLT_M18];

	//					//rtplctrace4(1,_T("%x %x = dataRead2_M18[1].dataRead2_M18[0]"),dataRead2_M18[1],dataRead2_M18[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M18_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3010-> ret_iosRead_Minimotor_M18=(%d)"),CASE_ECAT_M18_MINIMOTOR,ret_iosRead_Minimotor_M18);

	//					CASE_ECAT_M18_MINIMOTOR = STATO_READIN4_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M18)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3010-> CASE_ECAT_M18_MINIMOTOR=(%d)"),CASE_ECAT_M18_MINIMOTOR);
	//					CASE_ECAT_M18_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;
	//		
	//	case STATO_READIN4_ETH_MINIMOTOR:  // Lettura contatore intervento filtro su posizione richiesta
	//		{
	//				inReadBuffer3_M18.value.arr.size = 4;
	//				ret_iosRead_Minimotor_M18 = iosRead(minimotorHandle, 1, 0x3019, 0, 0, &inReadBuffer3_M18, &numByteRead3_M18, 150);
	//				if (ret_iosRead_Minimotor_M18 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_COUNT_FLT_ECAT_M18 = (unsigned long) (  ( (dataRead3_M18[3]<<24) & 0xFF000000) + ( (dataRead3_M18[2]<<16) & 0xFF0000) + 
	//					                                               ( (dataRead3_M18[1]<<8) & 0xFF00)+(dataRead3_M18[0] & 0xFF)   );
	//					
	//					R[R_COUNTER_FILTRO_M18] = (double) WORD_COUNT_FLT_ECAT_M18;

	//					//rtplctrace4(1,_T("%x %x %x %x = dataRead3_M18[3].dataRead3_M18[2].dataRead3_M18[1].dataRead3_M18[0]"),dataRead3_M18[1],dataRead3_M18[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M18_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3019-> ret_iosRead_Minimotor_M18=(%d)"),CASE_ECAT_M18_MINIMOTOR,ret_iosRead_Minimotor_M18);

	//					CASE_ECAT_M18_MINIMOTOR = STATO_READIN5_ETH_MINIMOTOR;

	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M18)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M18_MINIMOTOR=(%d)"),CASE_ECAT_M18_MINIMOTOR);
	//					CASE_ECAT_M18_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;			
	//		
	//	case STATO_READIN5_ETH_MINIMOTOR:  // Lettura potenza in uscita
	//		{
	//				inReadBuffer4_M18.value.arr.size = 2;
	//				ret_iosRead_Minimotor_M18 = iosRead(minimotorHandle, 1, 0x3014, 0, 0, &inReadBuffer4_M18, &numByteRead4_M18, 150);
	//				if (ret_iosRead_Minimotor_M18 == RTPLC_STATUS_OK) 
	//				{
	//					WORD_OUTPUT_PWR_ECAT_M18 = (short) (  ( (dataRead4_M18[1]<<8) & 0xFF00)+(dataRead4_M18[0] & 0xFF)   );
	//					
	//					R[R_OUTPUT_PWR_M18] = ((double) WORD_OUTPUT_PWR_ECAT_M18) / 1.0;

	//					//rtplctrace4(1,_T("%x %x = dataRead4_M18[1].dataRead4_M18[0]"),dataRead4_M18[1],dataRead4_M18[0]);
	//					//rtplctrace4(1,_T("CASE_ECAT_M18_MINIMOTOR=%d ***OK: Lettura Ethercat SDO=0x3014-> ret_iosRead_Minimotor_M18=(%d)"),CASE_ECAT_M18_MINIMOTOR,ret_iosRead_Minimotor_M18);

	//					CASE_ECAT_M18_MINIMOTOR = STATO_SET_TIME_WAIT_ETH_MINIMOTOR;
	//					
	//				}
	//				else if (RTPLC_STATUS_FAILED(ret_iosRead_Minimotor_M18)) 
	//				{
	//					//rtplctrace4(1,_T("Errore Lettura SDO=0x3019-> CASE_ECAT_M18_MINIMOTOR=(%d)"),CASE_ECAT_M18_MINIMOTOR);
	//					CASE_ECAT_M18_MINIMOTOR = STATO_ERROR_ETH_MINIMOTOR;
	//				}
	//		}
	//		break;

	//	case STATO_ERROR_ETH_MINIMOTOR:
	//		{
	//			if(minimotorHandle != 0)
	//			{
	//				iosClose(minimotorHandle);
	//				minimotorHandle = 0;
	//				//rtplctrace4(1,_T("CASE_ECAT_M18_MINIMOTOR=%d ***OK: Chiusura canale Ethercat indirizzo_1026-"),CASE_ECAT_M18_MINIMOTOR);
	//				CASE_ECAT_M18_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}
	//			else
	//			{
	//				CASE_ECAT_M18_MINIMOTOR = STATO_INI_ETH_MINIMOTOR;
	//			}

	//		}
	//		break;			

	//	}
	//}
	//else
	//{
	//}
}
