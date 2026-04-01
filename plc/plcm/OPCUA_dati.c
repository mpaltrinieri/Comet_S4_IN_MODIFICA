/*
        --------------------------------------------------------------
        TITOLO:         OPCUA dati
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione passaggio dati al plc iec
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    com_con_inverter(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:           
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CR4 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           24-07-2023
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"


typedef union {
    double Double_H;
    struct { float fl_high, fl_low; } asFloat;
} rxDoubleHigh;

typedef union {
    double Double_L;
    struct { float fl_high, fl_low; } asFloat;
} rxDoubleLow;

rxDoubleHigh Double_ALTO = {0.0};
rxDoubleLow Double_BASSO = {0.0};


char matricolaRxd[sizeof(double)+sizeof(double)] = "000000000000000";
char matricolaRxf[sizeof(Double_ALTO.Double_H)+sizeof(Double_BASSO.Double_L)] = "000000000000000";
char consensoLetturaMatricola02[sizeof(double)+1] = "\0";
char consensoLetturaMatricola01[sizeof(double)+1] = "\0";

char versione_vplc_Rxd[sizeof(double)+sizeof(double)] = "000000000000000";
char versione_vplc_Rxf[sizeof(Double_ALTO.Double_H)+sizeof(Double_BASSO.Double_L)] = "000000000000000";
char consensoLettura_versione_vplc_02[sizeof(double)+1] = "\0";
char consensoLettura_versione_vplc_01[sizeof(double)+1] = "\0";


void OPCUA_dati(void)
{
	if( (AF_INVERTER_0_COM01_MODBUS>0.5)      || (AF_ASSE_0_CH_NUM_TECH01_ADDRESS>0.5) || (AF_ASSE_1_CH_NUM_TECH01_ADDRESS>0.5) ||
		(AF_ASSE_2_CH_NUM_TECH01_ADDRESS>0.5) || (AF_ASSE_3_CH_NUM_TECH01_ADDRESS>0.5) || (AF_ASSE_4_CH_NUM_TECH01_ADDRESS>0.5) )
	{
		int counter_inverter = 0;
		//***********************************************************************************************
		//**************** LETTURA DEL NUMERO DI MATRICOLA MACCHINA *************************************
		//***********************************************************************************************
		memcpy(consensoLetturaMatricola02, &R[R_MATRICOLA_MACCHINA_02], sizeof(R[R_MATRICOLA_MACCHINA_02]));
		memcpy(consensoLetturaMatricola01, &R[R_MATRICOLA_MACCHINA_01], sizeof(R[R_MATRICOLA_MACCHINA_01]));

		if(strcmp(consensoLetturaMatricola02, "\0") && !LETTURA_MATRICOLA_ESEG)
		{
			consensoLetturaMatricola02[sizeof(double)+1] = '\0';
			rtplctrace3(3, _T("consensoLetturaMatricola02 = %s "), consensoLetturaMatricola02);

			consensoLetturaMatricola01[sizeof(double)+1] = '\0';
			rtplctrace3(3, _T("consensoLetturaMatricola01 = %s "), consensoLetturaMatricola01);

			// Decodifica con 2 double
			memcpy(matricolaRxd, &R[R_MATRICOLA_MACCHINA_02], sizeof(R[R_MATRICOLA_MACCHINA_02]));
			memcpy(matricolaRxd+sizeof(R[R_MATRICOLA_MACCHINA_01]), &R[R_MATRICOLA_MACCHINA_01], sizeof(R[R_MATRICOLA_MACCHINA_01]));

			rtplctrace3(3, _T("Dai double --> Matricola = %s "), matricolaRxd);

			Double_ALTO.Double_H = R[R_MATRICOLA_MACCHINA_02];
			Double_BASSO.Double_L = R[R_MATRICOLA_MACCHINA_01];

			// Decodifica con 4 float
			//memcpy(matricolaRxf, &Double_ALTO.asFloat.fl_high, sizeof(Double_ALTO.asFloat.fl_high));
			//memcpy(matricolaRxf+sizeof(Double_ALTO.asFloat.fl_high), &Double_ALTO.asFloat.fl_low, sizeof(Double_ALTO.asFloat.fl_low));
			//memcpy(matricolaRxf+sizeof(Double_ALTO.asFloat.fl_high)+sizeof(Double_ALTO.asFloat.fl_low), &Double_BASSO.asFloat.fl_high, sizeof(Double_BASSO.asFloat.fl_high));
			//memcpy(matricolaRxf+sizeof(Double_ALTO.asFloat.fl_high)+sizeof(Double_ALTO.asFloat.fl_low)+sizeof(Double_BASSO.asFloat.fl_low), &Double_BASSO.asFloat.fl_low, sizeof(Double_BASSO.asFloat.fl_low));

			// Appoggio numero di matricola sulle aree di scambio del plc iec
			NUM_MATRICOLA_VAR03 = Double_ALTO.asFloat.fl_high;
			NUM_MATRICOLA_VAR02 = Double_ALTO.asFloat.fl_low;
			NUM_MATRICOLA_VAR01 = Double_BASSO.asFloat.fl_high;
			NUM_MATRICOLA_VAR00 = Double_BASSO.asFloat.fl_low;


			// Decodifica con 4 float
			memcpy(matricolaRxf, &NUM_MATRICOLA_VAR03, sizeof(NUM_MATRICOLA_VAR03));
			memcpy(matricolaRxf+sizeof(NUM_MATRICOLA_VAR03), &NUM_MATRICOLA_VAR02, sizeof(NUM_MATRICOLA_VAR02));
			memcpy(matricolaRxf+sizeof(NUM_MATRICOLA_VAR03)+sizeof(NUM_MATRICOLA_VAR02), &NUM_MATRICOLA_VAR01, sizeof(NUM_MATRICOLA_VAR01));
			memcpy(matricolaRxf+sizeof(NUM_MATRICOLA_VAR03)+sizeof(NUM_MATRICOLA_VAR02)+sizeof(NUM_MATRICOLA_VAR01), &NUM_MATRICOLA_VAR00, sizeof(NUM_MATRICOLA_VAR00));

			rtplctrace3(3, _T("Dai float --> Matricola = %s "), matricolaRxf);

			LETTURA_MATRICOLA_ESEG = 1;
		}

		if(R[R_DEBUG_NUM_MATRICOLA]>0.5)
		{
			rtplctrace3(3, _T("consensoLetturaMatricola02 = %s "), consensoLetturaMatricola02);
			rtplctrace3(3, _T("consensoLetturaMatricola01 = %s "), consensoLetturaMatricola01);
			rtplctrace3(3, _T("Dai double --> Matricola = %s "), matricolaRxd);
			rtplctrace3(3, _T("Dai float --> Matricola = %s "), matricolaRxf);

			R[R_DEBUG_NUM_MATRICOLA] = 0.0;
		}

		//***********************************************************************************************
		//**************** FINE LETTURA DEL NUMERO DI MATRICOLA MACCHINA ********************************
		//***********************************************************************************************

		//***********************************************************************************************
		//**************** LETTURA VERSIONE VPLC  *******************************************************
		//***********************************************************************************************
		Double_ALTO.asFloat.fl_high  = 0.0f;
		Double_BASSO.asFloat.fl_low  = 0.0f;

		memcpy(consensoLettura_versione_vplc_02, &R[R_VERSIONE_VPLC_02], sizeof(R[R_VERSIONE_VPLC_02]));
		memcpy(consensoLettura_versione_vplc_01, &R[R_VERSIONE_VPLC_01], sizeof(R[R_VERSIONE_VPLC_01]));

		if(strcmp(consensoLettura_versione_vplc_02, "\0") && !LETTURA_VERSIONE_VPLC_ESEG)
		{
			consensoLettura_versione_vplc_02[sizeof(double)+1] = '\0';
			rtplctrace3(3, _T("consensoLettura_versione_vplc_02 = %s "), consensoLettura_versione_vplc_02);

			consensoLettura_versione_vplc_01[sizeof(double)+1] = '\0';
			rtplctrace3(3, _T("consensoLettura_versione_vplc_01 = %s "), consensoLettura_versione_vplc_01);

			// Decodifica con 2 double
			memcpy(versione_vplc_Rxd, &R[R_VERSIONE_VPLC_02], sizeof(R[R_VERSIONE_VPLC_02]));
			memcpy(versione_vplc_Rxd+sizeof(R[R_VERSIONE_VPLC_01]), &R[R_VERSIONE_VPLC_01], sizeof(R[R_VERSIONE_VPLC_01]));

			rtplctrace3(3, _T("Dai double --> Versione VPLC = %s "), versione_vplc_Rxd);

			Double_ALTO.Double_H = R[R_VERSIONE_VPLC_02];
			Double_BASSO.Double_L = R[R_VERSIONE_VPLC_01];

			// Appoggio della versione del VPLC sulle aree di scambio del plc iec
			AF_VERSIONE_VPLC_VAR03 = Double_ALTO.asFloat.fl_high;
			AF_VERSIONE_VPLC_VAR02 = Double_ALTO.asFloat.fl_low;
			AF_VERSIONE_VPLC_VAR01 = Double_BASSO.asFloat.fl_high;
			AF_VERSIONE_VPLC_VAR00 = Double_BASSO.asFloat.fl_low;


			// Decodifica con 4 float
			memcpy(versione_vplc_Rxf, &AF_VERSIONE_VPLC_VAR03, sizeof(AF_VERSIONE_VPLC_VAR03));
			memcpy(versione_vplc_Rxf+sizeof(AF_VERSIONE_VPLC_VAR03), &AF_VERSIONE_VPLC_VAR02, sizeof(AF_VERSIONE_VPLC_VAR02));
			memcpy(versione_vplc_Rxf+sizeof(AF_VERSIONE_VPLC_VAR03)+sizeof(AF_VERSIONE_VPLC_VAR02), &AF_VERSIONE_VPLC_VAR01, sizeof(AF_VERSIONE_VPLC_VAR01));
			memcpy(versione_vplc_Rxf+sizeof(AF_VERSIONE_VPLC_VAR03)+sizeof(AF_VERSIONE_VPLC_VAR02)+sizeof(AF_VERSIONE_VPLC_VAR01), &AF_VERSIONE_VPLC_VAR00, sizeof(AF_VERSIONE_VPLC_VAR00));

			rtplctrace3(3, _T("Dai float --> Versione VPLC = %s "), versione_vplc_Rxf);

			LETTURA_VERSIONE_VPLC_ESEG = 1;
		}
		//***********************************************************************************************
		//**************** FINE LETTURA DELLA VERSIONE DEL VPLC *****************************************
		//***********************************************************************************************

		//***********************************************************************************************
		//**************** GESTIONE DEL NUMERO MANDRINO GESTITO DA INVERTER *****************************
		//***********************************************************************************************

		for (counter_inverter=0; counter_inverter<(sizeof(opcUaNumSpindles)/sizeof(opcUaNumSpindles[0])); counter_inverter++)
			opcUaNumSpindles[counter_inverter] = (WORD) 0;

		//Inverter mandrino: è l'unico inverter gestito in questa macchina
		if (AF_INVERTER_0_COM01_MODBUS) opcUaNumSpindles[0] = (WORD) 1;
		else                            opcUaNumSpindles[0] = (WORD) 0;


		//*********************************************************
		//***** Lettura tipo utensile da HDRILL *******************
		//*********************************************************
		if(PON)
		{
			TYPE_UT_ACT_ON_SPINDLE = -1.0f;
		}

		//***** Ritardo di abilitazione della coda allarmi per il plc iec. Durante lo start framework di allarmi ne compaiono molti
		//***** si vuole evitare che questi vengano intercettati dal plc iec
		tS(TS_RIT_ENABLE_CODE_ALARM, (unsigned char) P_PON);

		//****************************************************************
		//******** CODA ALLARMI DA PASSARE AL PLC IEC ********************
		//****************************************************************
		if(RP_TSuppl[TS_RIT_ENABLE_CODE_ALARM])
		{
			//CODE_ALARM_VAR00 = (float) R[R_ALL_0];
			//CODE_ALARM_VAR01 = (float) R[R_ALL_1];
			//CODE_ALARM_VAR02 = (float) R[R_ALL_2];
			//CODE_ALARM_VAR03 = (float) R[R_ALL_3];
			//CODE_ALARM_VAR04 = (float) R[R_ALL_4];

			CODE_ALARM_VAR00 = (float) R[R_ALL_OPCUA_0];
			CODE_ALARM_VAR01 = (float) R[R_ALL_OPCUA_1];
			CODE_ALARM_VAR02 = (float) R[R_ALL_OPCUA_2];
			CODE_ALARM_VAR03 = (float) R[R_ALL_OPCUA_3];
			CODE_ALARM_VAR04 = (float) R[R_ALL_OPCUA_4];

			CODE_WARNING_VAR00 = (float) R[R_MES_0];
			CODE_WARNING_VAR01 = (float) R[R_MES_1];
			CODE_WARNING_VAR02 = (float) R[R_MES_2];
			CODE_WARNING_VAR03 = (float) R[R_MES_3];
			CODE_WARNING_VAR04 = (float) R[R_MES_4];
		}


		//****************************************************************
		//********* TIPO UTENSILE PASSATO DA DRILL/HDRILL ****************
		//****************************************************************
		//********* Nessuno          -1  *********************************
		//********* FRESA             0  *********************************
		//********* PUNTA             1  *********************************
		//********* SVASATORE         2  *********************************
		//********* LAMA              3  *********************************
		//********* MASCHIATORE       4  *********************************
		//********* TASTATORE         5  *********************************
		//********* <Disponibile>     6  *********************************
		//********* TASTATORE X       7  *********************************
		//********* FRESA A DISCO     8  *********************************

		// TYPE_UT_ACT_ON_SPINDLE : tipo di utensile attivo sul mandrino, appoggio di R[R_TIPO_TOOL_HDRILL_TO_PLC_1] passata da HDRILL 
		if( AUTO && CICLO_ON && (R[R_ACT_TOOL]>0.5) && 
			((R[R_ACT_TOOL]>(R[R_NEXT_TOOL]-0.1)) && (R[R_ACT_TOOL]<(R[R_NEXT_TOOL]+0.1)))  )  //nel cambio utensili aspettiamo che R610=R611
			TYPE_UT_ACT_ON_SPINDLE = (float) R[R_TIPO_TOOL_HDRILL_TO_PLC_1];
		else if ((R[R_ACT_TOOL]<0.5) || UTSCON_ACT)
			TYPE_UT_ACT_ON_SPINDLE = -1.0f;

		//****************** NUMERO UTENSILE ATTIVO SU MANDRINO ***********************************
		NUM_UT_ACT_ON_SPINDLE = (short) R[R_ACT_TOOL];

		//*********************************************************
		//***** Lettura stato macchina ****************************
		//*********************************************************

		if(RESET_MC || M02)
		{
			R[R_STATO_MACCH_HDRILL_TO_PLC] = 0.0;
		}

		// Flag di appoggio assi macchina in JOG
		ASSI_MACCHINA_IN_JOG = (O_JPOS_CH0 || O_JNEG_CH0 ||
			                    O_JPOS_CH1 || O_JNEG_CH1 ||
								O_JPOS_CH2 || O_JNEG_CH2);

		if(ALLARMI_PRES && !EMERGENZA_FAL)
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_ALARM;           // macchina in allarme ma non in emergenza
		else if(ALLARMI_PRES && EMERGENZA_FAL)
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_EMERGENCY;       // macchina in emergenza
		else if(PC_HOLD && !ALLARMI_PRES)
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_HOLD;            // macchina in pausa (Hold condition)
		else if(M64)
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_SETUP;           // macchina in riferimento assi: azzeramento in corso
		else if(MANO && !M64 && !ASSI_MACCHINA_IN_JOG)
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_ON;              // macchina pronta in manuale (ma non in riferimento assi)
		else if(MANO && !M64 && ASSI_MACCHINA_IN_JOG)
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_JOG;             // movimento assi manuale attivo (assi in JOG)
		else if(AUTO && !CICLO_ON)
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_READY;           // macchina in pronta in automatico ma non in ciclo
		//**********************************************************************************************
		//******** I SEGUENTI 3 SONO STATI MACCHINA CHE DOVEVANO ESSERE PASSATI DA HDRILL, ALLA FINE SI E' DECISO DI FARLI RICOSTRUIRE DAL PLC MACCHINA *********************
		else if(  (R[R_STATO_MACCH_HDRILL_TO_PLC] < (MACH_STATUS_WAIT+0.1)) && (R[R_STATO_MACCH_HDRILL_TO_PLC] > (MACH_STATUS_WAIT-0.1)) )
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_WAIT;                  // attesa operazione operatore con ciclo automatico in corso
		else if(  (R[R_STATO_MACCH_HDRILL_TO_PLC] < (MACH_STATUS_TOOL_CHANGE+0.1)) && (R[R_STATO_MACCH_HDRILL_TO_PLC] > (MACH_STATUS_TOOL_CHANGE-0.1)) )
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_TOOL_CHANGE; 
		else if(  (R[R_STATO_MACCH_HDRILL_TO_PLC] < (MACH_STATUS_WORKING+0.1)) && (R[R_STATO_MACCH_HDRILL_TO_PLC] > (MACH_STATUS_WORKING-0.1)) )
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_WORKING;               // Lavorazione attiva, utensile a contatto con il pezzo
		else if(  (R[R_STATO_MACCH_HDRILL_TO_PLC] < (MACH_STATUS_POSITIONING+0.1)) && (R[R_STATO_MACCH_HDRILL_TO_PLC] > (MACH_STATUS_POSITIONING-0.1)) || (AUTO && CICLO_ON) )
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_POSITIONING;           // Tutti i movimenti assi ad esclusione del ciclo di lavorazione
		else
			STATO_MACCHINA_PER_OPCUA = (float) MACH_STATUS_OFFLINE;               // Stato macchina sconosciuto e/o macchina spenta


		//****** APPOGGIO VARIABILE DI ENDURANCE CHE VIENE ESPOSTA SU SERVER OPCUA ************
		AF_ENDURANCE = (float) R[R_ENDURANCE_OPCUA];
		//****** APPOGGIO VARIABILE DI TIPO MACCHINA CHE VIENE ESPOSTA SU SERVER OPCUA ************
		AF_MACHINE_TYPE = (float) R[R_TYPE_MACHINE];

	}
	else
	{
	}
}