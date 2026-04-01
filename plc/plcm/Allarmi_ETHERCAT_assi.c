/*
        --------------------------------------------------------------
        TITOLO:         LETTURA PARAMETRI ETHERCAT ASSE _X
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    allarmi_ethercat_assi(void)
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
        AUTORI:         Daniele Formuso
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------
*/


#include "all.inc"




void allarmi_ethercat_assi(void)
{
	if( (R[R_ABIL_LETTURA_STATO_ASSE_X]>0.5) || (R[R_ABIL_LETTURA_STATO_ASSE_Y]>0.5) || (R[R_ABIL_LETTURA_STATO_ASSE_Z]>0.5) ||     
		(R[R_ABIL_LETTURA_STATO_ASSE_A]>0.5) || (R[R_ABIL_LETTURA_STATO_ASSE_W]>0.5) ||
		(AF_ASSE_0_CH_NUM_TECH01_ADDRESS>0.5)  || (AF_ASSE_1_CH_NUM_TECH01_ADDRESS>0.5)  || (AF_ASSE_2_CH_NUM_TECH01_ADDRESS>0.5) ||
		(AF_ASSE_3_CH_NUM_TECH01_ADDRESS>0.5)  || (AF_ASSE_4_CH_NUM_TECH01_ADDRESS>0.5)  
	)
	{
		// Verifica stato batteria azionamenti
		if ( RESET_ALL || RESET_MC )
		{
			BATTERIA_LOWLEVEL_ASSE_X_FAL = 0;
			BATTERIA_LOWLEVEL_ASSE_Y_FAL = 0;
			BATTERIA_LOWLEVEL_ASSE_Z_FAL = 0;
			BATTERIA_LOWLEVEL_ASSE_A_FAL = 0;
			BATTERIA_LOWLEVEL_ASSE_W_FAL = 0;
			
			MT_OVERFLOW_ASSE_X_FAL = 0;
			MT_OVERFLOW_ASSE_Y_FAL = 0;
			MT_OVERFLOW_ASSE_Z_FAL = 0;
			MT_OVERFLOW_ASSE_A_FAL = 0;
			MT_OVERFLOW_ASSE_W_FAL = 0;

			CLEAR_ENCODER_ERROR_ASSE_X_FAL = 0;
            CLEAR_ENCODER_ERROR_ASSE_Y_FAL = 0;
            CLEAR_ENCODER_ERROR_ASSE_Z_FAL = 0;
            CLEAR_ENCODER_ERROR_ASSE_A_FAL = 0;
            CLEAR_ENCODER_ERROR_ASSE_W_FAL = 0;
			
			UNDER_VOLTAGE_ASSE_X_FAL = 0;
			UNDER_VOLTAGE_ASSE_Y_FAL = 0;
			UNDER_VOLTAGE_ASSE_Z_FAL = 0;
			UNDER_VOLTAGE_ASSE_A_FAL = 0;
			UNDER_VOLTAGE_ASSE_W_FAL = 0;
			
			MOTORE_SENZA_FASE_ASSE_X_FAL = 0;
			MOTORE_SENZA_FASE_ASSE_Y_FAL = 0;
			MOTORE_SENZA_FASE_ASSE_Z_FAL = 0;
			MOTORE_SENZA_FASE_ASSE_A_FAL = 0;
			MOTORE_SENZA_FASE_ASSE_W_FAL = 0;
			
			OVERSHOOT_SPEED_ASSE_X_FAL = 0;
			OVERSHOOT_SPEED_ASSE_Y_FAL = 0;
			OVERSHOOT_SPEED_ASSE_Z_FAL = 0;
			OVERSHOOT_SPEED_ASSE_A_FAL = 0;
			OVERSHOOT_SPEED_ASSE_W_FAL = 0;

			// Reset dei flag di appoggio
			Batteria_LowLevel_Asse_X = 0;
			Batteria_LowLevel_Asse_Y = 0;
			Batteria_LowLevel_Asse_Z = 0;
			Batteria_LowLevel_Asse_A = 0;
			Batteria_LowLevel_Asse_W = 0;
			
			MT_Overflow_Asse_X = 0;
			MT_Overflow_Asse_Y = 0;
			MT_Overflow_Asse_Z = 0;
			MT_Overflow_Asse_A = 0;
			MT_Overflow_Asse_W = 0;
			
			Clear_Encoder_Error_Asse_X = 0;
			Clear_Encoder_Error_Asse_Y = 0;
			Clear_Encoder_Error_Asse_Z = 0;
			Clear_Encoder_Error_Asse_A = 0;
			Clear_Encoder_Error_Asse_W = 0;
			
			Under_Voltage_Asse_X = 0;
			Under_Voltage_Asse_Y = 0;
			Under_Voltage_Asse_Z = 0;
			Under_Voltage_Asse_A = 0;
			Under_Voltage_Asse_W = 0;
			
			Motore_Senza_Fase_Asse_X = 0;
			Motore_Senza_Fase_Asse_Y = 0;
			Motore_Senza_Fase_Asse_Z = 0;
			Motore_Senza_Fase_Asse_A = 0;
			Motore_Senza_Fase_Asse_W = 0;
			
			Overshoot_Speed_Asse_X = 0;
			Overshoot_Speed_Asse_Y = 0;
			Overshoot_Speed_Asse_Z = 0;
			Overshoot_Speed_Asse_A = 0;
			Overshoot_Speed_Asse_W = 0;

		}
		
		if(RESET_MC)
		{
			QUOTA_ENCODER_PERSA_ASSE_X_FAL = 0;	
			QUOTA_ENCODER_PERSA_ASSE_Y_FAL = 0;
			QUOTA_ENCODER_PERSA_ASSE_Z_FAL = 0;
			QUOTA_ENCODER_PERSA_ASSE_A_FAL = 0;
			QUOTA_ENCODER_PERSA_ASSE_W_FAL = 0;
			
			POS_ENCODER_NOINIT_ASSE_X_FAL = 0;
			POS_ENCODER_NOINIT_ASSE_Y_FAL = 0;
			POS_ENCODER_NOINIT_ASSE_Z_FAL = 0;
			POS_ENCODER_NOINIT_ASSE_A_FAL = 0;
			POS_ENCODER_NOINIT_ASSE_W_FAL = 0;
			
			// Reset dei flag di appoggio
			Quota_Encoder_persa_Asse_X = 0;
			Quota_Encoder_persa_Asse_Y = 0;
			Quota_Encoder_persa_Asse_Z = 0;
			Quota_Encoder_persa_Asse_A = 0;
			Quota_Encoder_persa_Asse_W = 0;
			
			Pos_Encoder_NoInit_Asse_X = 0;
			Pos_Encoder_NoInit_Asse_Y = 0;
			Pos_Encoder_NoInit_Asse_Z = 0;
			Pos_Encoder_NoInit_Asse_A = 0;
			Pos_Encoder_NoInit_Asse_W = 0;
		}
		

		// Appoggi pilotaggio timer (per visualizzazione e semplificazione)
		APP_P_CHECK_BATTERY_ON =  ( RP_PON && !(RP_CHECK_BATTERY_OFF) );		// Appoggio pilotaggio timer ON : dopo 1 ora (3600 secondi) di OFF
		APP_P_CHECK_BATTERY_OFF = ( RP_PON &&  (RP_CHECK_BATTERY_ON ) );		// Appoggio pilotaggio timer OFF: dopo 5 secondi di ON


		//******** Timer per verififcare e dare allarme livello batteria per 5 secondi una volta all'ora
		P_CHECK_BATTERY_ON =  APP_P_CHECK_BATTERY_ON;			// Pilotaggio timer ON 
		P_CHECK_BATTERY_OFF = APP_P_CHECK_BATTERY_OFF;			// Pilotaggio timer OFF


		// Abilitazione inizio lettura parametri azionamenti
		ABIL_CHECK_BATTERY_LEVEL = APP_P_CHECK_BATTERY_ON && !( RP_CHECK_BATTERY_ON );


		read_params_asse_X();
		read_params_asse_Y();
		read_params_asse_Z();
		read_params_asse_A();
		read_params_asse_W();


		// Diagnostica relativa al warning 0x060 --> Livello batteria encoder basso e posizione assoluta persa 
		//                                          (compare con livello batteria <2.8 V ma solo alla riaccensione dell'azionamento, ad azionamento acceso l'encoder è alimentato dall'azionamento)                                                                                                    
		Quota_Encoder_persa_Asse_X = Status_Bit_Asse_X_07 && (Error_Code_Group_Asse_X==DELTA_ALL_BATT_QUOTA_PERSA_GR) && (Error_Code_Num_Asse_X==DELTA_ALL_BATT_QUOTA_PERSA_NU);
		Quota_Encoder_persa_Asse_Y = Status_Bit_Asse_Y_07 && (Error_Code_Group_Asse_Y==DELTA_ALL_BATT_QUOTA_PERSA_GR) && (Error_Code_Num_Asse_Y==DELTA_ALL_BATT_QUOTA_PERSA_NU);
		Quota_Encoder_persa_Asse_Z = Status_Bit_Asse_Z_07 && (Error_Code_Group_Asse_Z==DELTA_ALL_BATT_QUOTA_PERSA_GR) && (Error_Code_Num_Asse_Z==DELTA_ALL_BATT_QUOTA_PERSA_NU);
		Quota_Encoder_persa_Asse_A = Status_Bit_Asse_A_07 && (Error_Code_Group_Asse_A==DELTA_ALL_BATT_QUOTA_PERSA_GR) && (Error_Code_Num_Asse_A==DELTA_ALL_BATT_QUOTA_PERSA_NU);
		Quota_Encoder_persa_Asse_W = Status_Bit_Asse_W_07 && (Error_Code_Group_Asse_W==DELTA_ALL_BATT_QUOTA_PERSA_GR) && (Error_Code_Num_Asse_W==DELTA_ALL_BATT_QUOTA_PERSA_NU);
		
		// In automatico deve essere un allarme, mentre in manuale deve essere un messaggio perchè l'asse deve essere mosso in jog fino allo zero meccanico per poi provare a cambiare la batteria e resettare encoder
		if ( Quota_Encoder_persa_Asse_X ) QUOTA_ENCODER_PERSA_ASSE_X_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Quota_Encoder_persa_Asse_Y ) QUOTA_ENCODER_PERSA_ASSE_Y_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Quota_Encoder_persa_Asse_Z ) QUOTA_ENCODER_PERSA_ASSE_Z_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Quota_Encoder_persa_Asse_A ) QUOTA_ENCODER_PERSA_ASSE_A_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Quota_Encoder_persa_Asse_W ) QUOTA_ENCODER_PERSA_ASSE_W_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);

		QUOTA_ENCODER_PERSA_ASSE_X_FMS = Quota_Encoder_persa_Asse_X && !QUOTA_ENCODER_PERSA_ASSE_X_FAL;
		QUOTA_ENCODER_PERSA_ASSE_Y_FMS = Quota_Encoder_persa_Asse_Y && !QUOTA_ENCODER_PERSA_ASSE_Y_FAL;
		QUOTA_ENCODER_PERSA_ASSE_Z_FMS = Quota_Encoder_persa_Asse_Z && !QUOTA_ENCODER_PERSA_ASSE_Z_FAL;
		QUOTA_ENCODER_PERSA_ASSE_A_FMS = Quota_Encoder_persa_Asse_A && !QUOTA_ENCODER_PERSA_ASSE_A_FAL;
		QUOTA_ENCODER_PERSA_ASSE_W_FMS = Quota_Encoder_persa_Asse_W && !QUOTA_ENCODER_PERSA_ASSE_W_FAL;
		
		// Diagnostica relativa al warning 0x061 --> Livello batteria encoder basso (compare con batteria tra 2.8-3.1 V, livello nominale 3.6-3.7 V)
		Batteria_LowLevel_Asse_X = Status_Bit_Asse_X_07 && (Error_Code_Group_Asse_X==DELTA_ALL_BATT_SCARICA_GR) && (Error_Code_Num_Asse_X==DELTA_ALL_BATT_SCARICA_NU);
		Batteria_LowLevel_Asse_Y = Status_Bit_Asse_Y_07 && (Error_Code_Group_Asse_Y==DELTA_ALL_BATT_SCARICA_GR) && (Error_Code_Num_Asse_Y==DELTA_ALL_BATT_SCARICA_NU);
		Batteria_LowLevel_Asse_Z = Status_Bit_Asse_Z_07 && (Error_Code_Group_Asse_Z==DELTA_ALL_BATT_SCARICA_GR) && (Error_Code_Num_Asse_Z==DELTA_ALL_BATT_SCARICA_NU);
		Batteria_LowLevel_Asse_A = Status_Bit_Asse_A_07 && (Error_Code_Group_Asse_A==DELTA_ALL_BATT_SCARICA_GR) && (Error_Code_Num_Asse_A==DELTA_ALL_BATT_SCARICA_NU);
		Batteria_LowLevel_Asse_W = Status_Bit_Asse_W_07 && (Error_Code_Group_Asse_W==DELTA_ALL_BATT_SCARICA_GR) && (Error_Code_Num_Asse_W==DELTA_ALL_BATT_SCARICA_NU);
		
		if ( Batteria_LowLevel_Asse_X && ABIL_CHECK_BATTERY_LEVEL) BATTERIA_LOWLEVEL_ASSE_X_FAL = 1;  // Da allarme per 5 secondi, dopo non da più allarme per 1 ora
		if ( Batteria_LowLevel_Asse_Y && ABIL_CHECK_BATTERY_LEVEL) BATTERIA_LOWLEVEL_ASSE_Y_FAL = 1;
		if ( Batteria_LowLevel_Asse_Z && ABIL_CHECK_BATTERY_LEVEL) BATTERIA_LOWLEVEL_ASSE_Z_FAL = 1;
		if ( Batteria_LowLevel_Asse_A && ABIL_CHECK_BATTERY_LEVEL) BATTERIA_LOWLEVEL_ASSE_A_FAL = 1;
		if ( Batteria_LowLevel_Asse_W && ABIL_CHECK_BATTERY_LEVEL) BATTERIA_LOWLEVEL_ASSE_W_FAL = 1;

		BATTERIA_LOWLEVEL_ASSE_X_FMS = Batteria_LowLevel_Asse_X && !BATTERIA_LOWLEVEL_ASSE_X_FAL;  // Se il livello batteria è basso, nell'ora in cui non da allarme visualizzo un messaggio
		BATTERIA_LOWLEVEL_ASSE_Y_FMS = Batteria_LowLevel_Asse_Y && !BATTERIA_LOWLEVEL_ASSE_Y_FAL;
		BATTERIA_LOWLEVEL_ASSE_Z_FMS = Batteria_LowLevel_Asse_Z && !BATTERIA_LOWLEVEL_ASSE_Z_FAL;
		BATTERIA_LOWLEVEL_ASSE_A_FMS = Batteria_LowLevel_Asse_A && !BATTERIA_LOWLEVEL_ASSE_A_FAL;
		BATTERIA_LOWLEVEL_ASSE_W_FMS = Batteria_LowLevel_Asse_W && !BATTERIA_LOWLEVEL_ASSE_W_FAL;
		
		// Diagnostica relativa al warning 0x062 --> overflow sui giri massimi del multiturn dell'encoder assoluto
		MT_Overflow_Asse_X = Status_Bit_Asse_X_07 && (Error_Code_Group_Asse_X==DELTA_MT_OVERFLOW_GR) && (Error_Code_Num_Asse_X==DELTA_MT_OVERFLOW_NU);
		MT_Overflow_Asse_Y = Status_Bit_Asse_Y_07 && (Error_Code_Group_Asse_Y==DELTA_MT_OVERFLOW_GR) && (Error_Code_Num_Asse_Y==DELTA_MT_OVERFLOW_NU);
		MT_Overflow_Asse_Z = Status_Bit_Asse_Z_07 && (Error_Code_Group_Asse_Z==DELTA_MT_OVERFLOW_GR) && (Error_Code_Num_Asse_Z==DELTA_MT_OVERFLOW_NU);
		MT_Overflow_Asse_A = Status_Bit_Asse_A_07 && (Error_Code_Group_Asse_A==DELTA_MT_OVERFLOW_GR) && (Error_Code_Num_Asse_A==DELTA_MT_OVERFLOW_NU);
		MT_Overflow_Asse_W = Status_Bit_Asse_W_07 && (Error_Code_Group_Asse_W==DELTA_MT_OVERFLOW_GR) && (Error_Code_Num_Asse_W==DELTA_MT_OVERFLOW_NU);
		
		// In automatico deve essere un allarme, mentre in manuale deve essere un messaggio perchè l'asse deve essere mosso in jog fino allo zero meccanico per poi provare a risolvere resettando encoder
		if ( MT_Overflow_Asse_X ) MT_OVERFLOW_ASSE_X_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( MT_Overflow_Asse_Y ) MT_OVERFLOW_ASSE_Y_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( MT_Overflow_Asse_Z ) MT_OVERFLOW_ASSE_Z_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( MT_Overflow_Asse_A ) MT_OVERFLOW_ASSE_A_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( MT_Overflow_Asse_W ) MT_OVERFLOW_ASSE_W_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);

		MT_OVERFLOW_ASSE_X_FMS = MT_Overflow_Asse_X && !MT_OVERFLOW_ASSE_X_FAL;
        MT_OVERFLOW_ASSE_Y_FMS = MT_Overflow_Asse_Y && !MT_OVERFLOW_ASSE_Y_FAL;
        MT_OVERFLOW_ASSE_Z_FMS = MT_Overflow_Asse_Z && !MT_OVERFLOW_ASSE_Z_FAL;
        MT_OVERFLOW_ASSE_A_FMS = MT_Overflow_Asse_A && !MT_OVERFLOW_ASSE_A_FAL;
        MT_OVERFLOW_ASSE_W_FMS = MT_Overflow_Asse_W && !MT_OVERFLOW_ASSE_W_FAL;
		
		// Diagnostica relativa al warning 0x06A --> Posizione assoluta encoder non inizializzata
		Pos_Encoder_NoInit_Asse_X = Status_Bit_Asse_X_07 && (Error_Code_Group_Asse_X==DELTA_POS_ENCODER_PERSA_GR) && (Error_Code_Num_Asse_X==DELTA_POS_ENCODER_PERSA_NU);
		Pos_Encoder_NoInit_Asse_Y = Status_Bit_Asse_Y_07 && (Error_Code_Group_Asse_Y==DELTA_POS_ENCODER_PERSA_GR) && (Error_Code_Num_Asse_Y==DELTA_POS_ENCODER_PERSA_NU);
		Pos_Encoder_NoInit_Asse_Z = Status_Bit_Asse_Z_07 && (Error_Code_Group_Asse_Z==DELTA_POS_ENCODER_PERSA_GR) && (Error_Code_Num_Asse_Z==DELTA_POS_ENCODER_PERSA_NU);
		Pos_Encoder_NoInit_Asse_A = Status_Bit_Asse_A_07 && (Error_Code_Group_Asse_A==DELTA_POS_ENCODER_PERSA_GR) && (Error_Code_Num_Asse_A==DELTA_POS_ENCODER_PERSA_NU);
		Pos_Encoder_NoInit_Asse_W = Status_Bit_Asse_W_07 && (Error_Code_Group_Asse_W==DELTA_POS_ENCODER_PERSA_GR) && (Error_Code_Num_Asse_W==DELTA_POS_ENCODER_PERSA_NU);
		
		// In automatico deve essere un allarme, mentre in manuale deve essere un messaggio perchè l'asse deve essere mosso in jog fino allo zero meccanico per poi resettare encoder
		if ( Pos_Encoder_NoInit_Asse_X ) POS_ENCODER_NOINIT_ASSE_X_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Pos_Encoder_NoInit_Asse_Y ) POS_ENCODER_NOINIT_ASSE_Y_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Pos_Encoder_NoInit_Asse_Z ) POS_ENCODER_NOINIT_ASSE_Z_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Pos_Encoder_NoInit_Asse_A ) POS_ENCODER_NOINIT_ASSE_A_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);
		if ( Pos_Encoder_NoInit_Asse_W ) POS_ENCODER_NOINIT_ASSE_W_FAL = (AUTO || MANO && !GEST_OPERATORE_MAN);

		POS_ENCODER_NOINIT_ASSE_X_FMS = Pos_Encoder_NoInit_Asse_X && !POS_ENCODER_NOINIT_ASSE_X_FAL;
		POS_ENCODER_NOINIT_ASSE_Y_FMS = Pos_Encoder_NoInit_Asse_Y && !POS_ENCODER_NOINIT_ASSE_Y_FAL;
		POS_ENCODER_NOINIT_ASSE_Z_FMS = Pos_Encoder_NoInit_Asse_Z && !POS_ENCODER_NOINIT_ASSE_Z_FAL;
		POS_ENCODER_NOINIT_ASSE_A_FMS = Pos_Encoder_NoInit_Asse_A && !POS_ENCODER_NOINIT_ASSE_A_FAL;
		POS_ENCODER_NOINIT_ASSE_W_FMS = Pos_Encoder_NoInit_Asse_W && !POS_ENCODER_NOINIT_ASSE_W_FAL;
		
		// Diagnostica relativa al warning 0x070 --> Funzione di reset encoder assoluto non riuscita
		Clear_Encoder_Error_Asse_X = Status_Bit_Asse_X_07 && (Error_Code_Group_Asse_X==DELTA_CLEAR_ENCODER_ERR_GR) && (Error_Code_Num_Asse_X==DELTA_CLEAR_ENCODER_ERR_NU);
		Clear_Encoder_Error_Asse_Y = Status_Bit_Asse_Y_07 && (Error_Code_Group_Asse_Y==DELTA_CLEAR_ENCODER_ERR_GR) && (Error_Code_Num_Asse_Y==DELTA_CLEAR_ENCODER_ERR_NU);
		Clear_Encoder_Error_Asse_Z = Status_Bit_Asse_Z_07 && (Error_Code_Group_Asse_Z==DELTA_CLEAR_ENCODER_ERR_GR) && (Error_Code_Num_Asse_Z==DELTA_CLEAR_ENCODER_ERR_NU);
		Clear_Encoder_Error_Asse_A = Status_Bit_Asse_A_07 && (Error_Code_Group_Asse_A==DELTA_CLEAR_ENCODER_ERR_GR) && (Error_Code_Num_Asse_A==DELTA_CLEAR_ENCODER_ERR_NU);
		Clear_Encoder_Error_Asse_W = Status_Bit_Asse_W_07 && (Error_Code_Group_Asse_W==DELTA_CLEAR_ENCODER_ERR_GR) && (Error_Code_Num_Asse_W==DELTA_CLEAR_ENCODER_ERR_NU);
		
		if ( Clear_Encoder_Error_Asse_X ) CLEAR_ENCODER_ERROR_ASSE_X_FAL = 1;
		if ( Clear_Encoder_Error_Asse_Y ) CLEAR_ENCODER_ERROR_ASSE_Y_FAL = 1;
		if ( Clear_Encoder_Error_Asse_Z ) CLEAR_ENCODER_ERROR_ASSE_Z_FAL = 1;
		if ( Clear_Encoder_Error_Asse_A ) CLEAR_ENCODER_ERROR_ASSE_A_FAL = 1;
		if ( Clear_Encoder_Error_Asse_W ) CLEAR_ENCODER_ERROR_ASSE_W_FAL = 1;
		
		// Diagnostica relativa all'allarme 0x003 --> La tensione DC del circuito principale è più bassa del valore standard
		Under_Voltage_Asse_X = Status_Bit_Asse_X_03 && (Error_Code_Group_Asse_X==DELTA_UNDER_VOLTAGE_GR) && (Error_Code_Num_Asse_X==DELTA_UNDER_VOLTAGE_NU);
		Under_Voltage_Asse_Y = Status_Bit_Asse_Y_03 && (Error_Code_Group_Asse_Y==DELTA_UNDER_VOLTAGE_GR) && (Error_Code_Num_Asse_Y==DELTA_UNDER_VOLTAGE_NU);
		Under_Voltage_Asse_Z = Status_Bit_Asse_Z_03 && (Error_Code_Group_Asse_Z==DELTA_UNDER_VOLTAGE_GR) && (Error_Code_Num_Asse_Z==DELTA_UNDER_VOLTAGE_NU);
		Under_Voltage_Asse_A = Status_Bit_Asse_A_03 && (Error_Code_Group_Asse_A==DELTA_UNDER_VOLTAGE_GR) && (Error_Code_Num_Asse_A==DELTA_UNDER_VOLTAGE_NU);
		Under_Voltage_Asse_W = Status_Bit_Asse_W_03 && (Error_Code_Group_Asse_W==DELTA_UNDER_VOLTAGE_GR) && (Error_Code_Num_Asse_W==DELTA_UNDER_VOLTAGE_NU);
		
		if ( Under_Voltage_Asse_X ) UNDER_VOLTAGE_ASSE_X_FAL = 1;
		if ( Under_Voltage_Asse_Y ) UNDER_VOLTAGE_ASSE_Y_FAL = 1;
		if ( Under_Voltage_Asse_Z ) UNDER_VOLTAGE_ASSE_Z_FAL = 1;
		if ( Under_Voltage_Asse_A ) UNDER_VOLTAGE_ASSE_A_FAL = 1;
		if ( Under_Voltage_Asse_W ) UNDER_VOLTAGE_ASSE_W_FAL = 1;
		
		// Diagnostica relativa all'allarme 0x022 --> Mancanza di una fase in ingresso
		Motore_Senza_Fase_Asse_X = Status_Bit_Asse_X_03 && (Error_Code_Group_Asse_X==DELTA_MOTORE_SENZA_FASE_GR) && (Error_Code_Num_Asse_X==DELTA_MOTORE_SENZA_FASE_NU);
		Motore_Senza_Fase_Asse_Y = Status_Bit_Asse_Y_03 && (Error_Code_Group_Asse_Y==DELTA_MOTORE_SENZA_FASE_GR) && (Error_Code_Num_Asse_Y==DELTA_MOTORE_SENZA_FASE_NU);
		Motore_Senza_Fase_Asse_Z = Status_Bit_Asse_Z_03 && (Error_Code_Group_Asse_Z==DELTA_MOTORE_SENZA_FASE_GR) && (Error_Code_Num_Asse_Z==DELTA_MOTORE_SENZA_FASE_NU);
		Motore_Senza_Fase_Asse_A = Status_Bit_Asse_A_03 && (Error_Code_Group_Asse_A==DELTA_MOTORE_SENZA_FASE_GR) && (Error_Code_Num_Asse_A==DELTA_MOTORE_SENZA_FASE_NU);
		Motore_Senza_Fase_Asse_W = Status_Bit_Asse_W_03 && (Error_Code_Group_Asse_W==DELTA_MOTORE_SENZA_FASE_GR) && (Error_Code_Num_Asse_W==DELTA_MOTORE_SENZA_FASE_NU);
		
		if ( Motore_Senza_Fase_Asse_X ) MOTORE_SENZA_FASE_ASSE_X_FAL = 1;
		if ( Motore_Senza_Fase_Asse_Y ) MOTORE_SENZA_FASE_ASSE_Y_FAL = 1;
		if ( Motore_Senza_Fase_Asse_Z ) MOTORE_SENZA_FASE_ASSE_Z_FAL = 1;
		if ( Motore_Senza_Fase_Asse_A ) MOTORE_SENZA_FASE_ASSE_A_FAL = 1;
		if ( Motore_Senza_Fase_Asse_W ) MOTORE_SENZA_FASE_ASSE_W_FAL = 1;
		
		// Diagnostica relativa al warning 0x047 --> Velocità motore in overshoot rispetto al valore massimo di targa
		Overshoot_Speed_Asse_X = Status_Bit_Asse_X_07 && (Error_Code_Group_Asse_X==DELTA_OVERSHOOT_SPEED_GR) && (Error_Code_Num_Asse_X==DELTA_OVERSHOOT_SPEED_NU);
		Overshoot_Speed_Asse_Y = Status_Bit_Asse_Y_07 && (Error_Code_Group_Asse_Y==DELTA_OVERSHOOT_SPEED_GR) && (Error_Code_Num_Asse_Y==DELTA_OVERSHOOT_SPEED_NU);
		Overshoot_Speed_Asse_Z = Status_Bit_Asse_Z_07 && (Error_Code_Group_Asse_Z==DELTA_OVERSHOOT_SPEED_GR) && (Error_Code_Num_Asse_Z==DELTA_OVERSHOOT_SPEED_NU);
		Overshoot_Speed_Asse_A = Status_Bit_Asse_A_07 && (Error_Code_Group_Asse_A==DELTA_OVERSHOOT_SPEED_GR) && (Error_Code_Num_Asse_A==DELTA_OVERSHOOT_SPEED_NU);
		Overshoot_Speed_Asse_W = Status_Bit_Asse_W_07 && (Error_Code_Group_Asse_W==DELTA_OVERSHOOT_SPEED_GR) && (Error_Code_Num_Asse_W==DELTA_OVERSHOOT_SPEED_NU);
		
		if ( Overshoot_Speed_Asse_X ) OVERSHOOT_SPEED_ASSE_X_FAL = 1;
		if ( Overshoot_Speed_Asse_Y ) OVERSHOOT_SPEED_ASSE_Y_FAL = 1;
		if ( Overshoot_Speed_Asse_Z ) OVERSHOOT_SPEED_ASSE_Z_FAL = 1;
		if ( Overshoot_Speed_Asse_A ) OVERSHOOT_SPEED_ASSE_A_FAL = 1;
		if ( Overshoot_Speed_Asse_W ) OVERSHOOT_SPEED_ASSE_W_FAL = 1;
	
		// Diagnostica relativa al warning 0x023 --> Messaggio di Motore in preallarme da sovraccarico
		PRE_OVERLOAD_ASSE_X_FMS = Status_Bit_Asse_X_07 && (Error_Code_Group_Asse_X==DELTA_PRE_OVERLOAD_GR) && (Error_Code_Num_Asse_X==DELTA_PRE_OVERLOAD_NU);
		PRE_OVERLOAD_ASSE_Y_FMS = Status_Bit_Asse_Y_07 && (Error_Code_Group_Asse_Y==DELTA_PRE_OVERLOAD_GR) && (Error_Code_Num_Asse_Y==DELTA_PRE_OVERLOAD_NU);
		PRE_OVERLOAD_ASSE_Z_FMS = Status_Bit_Asse_Z_07 && (Error_Code_Group_Asse_Z==DELTA_PRE_OVERLOAD_GR) && (Error_Code_Num_Asse_Z==DELTA_PRE_OVERLOAD_NU);
		PRE_OVERLOAD_ASSE_A_FMS = Status_Bit_Asse_A_07 && (Error_Code_Group_Asse_A==DELTA_PRE_OVERLOAD_GR) && (Error_Code_Num_Asse_A==DELTA_PRE_OVERLOAD_NU);
		PRE_OVERLOAD_ASSE_W_FMS = Status_Bit_Asse_W_07 && (Error_Code_Group_Asse_W==DELTA_PRE_OVERLOAD_GR) && (Error_Code_Num_Asse_W==DELTA_PRE_OVERLOAD_NU);
	}
	else
	{		
		QUOTA_ENCODER_PERSA_ASSE_X_FAL = 0;	
		QUOTA_ENCODER_PERSA_ASSE_Y_FAL = 0;
		QUOTA_ENCODER_PERSA_ASSE_Z_FAL = 0;
		QUOTA_ENCODER_PERSA_ASSE_A_FAL = 0;
		QUOTA_ENCODER_PERSA_ASSE_W_FAL = 0;

		BATTERIA_LOWLEVEL_ASSE_X_FAL = 0;
		BATTERIA_LOWLEVEL_ASSE_Y_FAL = 0;
		BATTERIA_LOWLEVEL_ASSE_Z_FAL = 0;
		BATTERIA_LOWLEVEL_ASSE_A_FAL = 0;
		BATTERIA_LOWLEVEL_ASSE_W_FAL = 0;

		MT_OVERFLOW_ASSE_X_FAL = 0;		
		MT_OVERFLOW_ASSE_Y_FAL = 0;		
		MT_OVERFLOW_ASSE_Z_FAL = 0;		
		MT_OVERFLOW_ASSE_A_FAL = 0;		
		MT_OVERFLOW_ASSE_W_FAL = 0;		
		
		POS_ENCODER_NOINIT_ASSE_X_FAL = 0;
		POS_ENCODER_NOINIT_ASSE_Y_FAL = 0;
		POS_ENCODER_NOINIT_ASSE_Z_FAL = 0;
		POS_ENCODER_NOINIT_ASSE_A_FAL = 0;
		POS_ENCODER_NOINIT_ASSE_W_FAL = 0;
		
		CLEAR_ENCODER_ERROR_ASSE_X_FAL = 0;
		CLEAR_ENCODER_ERROR_ASSE_Y_FAL = 0;
		CLEAR_ENCODER_ERROR_ASSE_Z_FAL = 0;
		CLEAR_ENCODER_ERROR_ASSE_A_FAL = 0;
		CLEAR_ENCODER_ERROR_ASSE_W_FAL = 0;
		
		UNDER_VOLTAGE_ASSE_X_FAL = 0;
		UNDER_VOLTAGE_ASSE_Y_FAL = 0;
		UNDER_VOLTAGE_ASSE_Z_FAL = 0;
		UNDER_VOLTAGE_ASSE_A_FAL = 0;
		UNDER_VOLTAGE_ASSE_W_FAL = 0;
		
		MOTORE_SENZA_FASE_ASSE_X_FAL = 0;
		MOTORE_SENZA_FASE_ASSE_Y_FAL = 0;
		MOTORE_SENZA_FASE_ASSE_Z_FAL = 0;
		MOTORE_SENZA_FASE_ASSE_A_FAL = 0;
		MOTORE_SENZA_FASE_ASSE_W_FAL = 0;
		
		OVERSHOOT_SPEED_ASSE_X_FAL = 0;
		OVERSHOOT_SPEED_ASSE_Y_FAL = 0;
		OVERSHOOT_SPEED_ASSE_Z_FAL = 0;
		OVERSHOOT_SPEED_ASSE_A_FAL = 0;
		OVERSHOOT_SPEED_ASSE_W_FAL = 0;

		QUOTA_ENCODER_PERSA_ASSE_X_FMS = 0;
		QUOTA_ENCODER_PERSA_ASSE_Y_FMS = 0;
		QUOTA_ENCODER_PERSA_ASSE_Z_FMS = 0;
		QUOTA_ENCODER_PERSA_ASSE_A_FMS = 0;
		QUOTA_ENCODER_PERSA_ASSE_W_FMS = 0;

		BATTERIA_LOWLEVEL_ASSE_X_FMS = 0;
		BATTERIA_LOWLEVEL_ASSE_Y_FMS = 0;
		BATTERIA_LOWLEVEL_ASSE_Z_FMS = 0;
		BATTERIA_LOWLEVEL_ASSE_A_FMS = 0;
		BATTERIA_LOWLEVEL_ASSE_W_FMS = 0;

		POS_ENCODER_NOINIT_ASSE_X_FMS = 0;
		POS_ENCODER_NOINIT_ASSE_Y_FMS = 0;
		POS_ENCODER_NOINIT_ASSE_Z_FMS = 0;
		POS_ENCODER_NOINIT_ASSE_A_FMS = 0;
		POS_ENCODER_NOINIT_ASSE_W_FMS = 0;

		MT_OVERFLOW_ASSE_X_FMS = 0;
		MT_OVERFLOW_ASSE_Y_FMS = 0;
		MT_OVERFLOW_ASSE_Z_FMS = 0;
		MT_OVERFLOW_ASSE_A_FMS = 0;
		MT_OVERFLOW_ASSE_W_FMS = 0;

		PRE_OVERLOAD_ASSE_X_FMS = 0;
		PRE_OVERLOAD_ASSE_Y_FMS = 0;
		PRE_OVERLOAD_ASSE_Z_FMS = 0;
		PRE_OVERLOAD_ASSE_A_FMS = 0;
		PRE_OVERLOAD_ASSE_W_FMS = 0;
	}
}