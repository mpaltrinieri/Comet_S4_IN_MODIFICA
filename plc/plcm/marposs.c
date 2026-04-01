/*
        --------------------------------------------------------------
        TITOLO:         MARPOSS
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione tastatore Marposs
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    marposs(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          MARPOSS_TOUCH_I   Tastatore in battuta
                        MARPOSS_NOERR_I   Tastatore non in errore
                        MARPOSS_LOWBA_I   Tastatore low battery
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         START_MARPOSS_O   Start misura marposs
                        MARPOSS_ERROR_AL  All. Tastatore Marposs
                        MARPOSS_ERROR_FAL Flag Tastatore Marposs
                        MARPOSS_LOWBA_AL  All. Low battery Marposs
                        MARPOSS_LOWBA_FAL Flag Low battery Marposs
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        SXT 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           15-04-00
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Pecchi Andrea
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"

void    marposs(PPLCMAIN_LOCVARS locvars)

{
	if ( (R[R_MARPOSS]>0.5) && (R[R_INPUT_LATCH_PROBE]<0.5) )
	{
		// INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE 
		if (PON)
		{
			//
		}


		// ESECUZIONE PROGRAMMA SIMULATO 
		if (SIMULATORE_SU_CN || SIMULATORE_SU_PC)
		{
			MARPOSS_NOERR_I = START_MARPOSS_O;
			MARPOSS_LOWBA_I = 0;
			R[R_MARPOSS] = (float)0;
		}



		// Info x cnc
		R[R_MARPOSS_TOUCH] = MARPOSS_TOUCH_I;


		// RESET ALLARMI MARPOSS 
		if (RESET_ALL || RESET_MC)
		{
			MARPOSS_ERROR_FAL = 0;
			MARPOSS_LOWBA_FAL = 0;
		}

		// RESET ALLARMI MARPOSS SOLO CON RESET CNC
		if (RESET_MC)
		{
			MARPOSS_TOUCH_FAL = 0;
			MARPOSS_ST_TOUCH_FAL = 0;
			MARPOSS_NOTOUCH_FAL = 0;
			MARPOSS_INDEX_FAL = 0;
			CORREZ_TOO_BIG_FAL = 0;
		}


		// START MARPOSS 
		if (Mg_MC(118))
		{
			START_MARPOSS = 1;
			//Mr_MC(118);	spostato reset x mantener correttam abilitato il settaggio di VERFALS
		}
		if (Mg_MC(119) || RESET_MC)
		{
			//START_MARPOSS = 0;  spegnere il tastatore solo al cambio utensile
			Mr_MC(118);
			Mr_MC(119);
		}

		if(Mg_MC(174) || RESET_MC || M02)
		{
			Mr_MC(174);
			START_MARPOSS = 0;
		}

		if(!MARPOSS_TOUCH_I)
		{
			Mr_MC(175);  //reset funzione ausiliaria di attesa spegnimento ingresso marposs in battuta
		}

		//if ((AUTO && !START_MARPOSS))
		//	TIMESTARTMARPOSS1 = 6000;
		//else if (TIMESTARTMARPOSS1 >0)
		//	{
		//	TIMESTARTMARPOSS1--;
		//	}


		// Marposs va in errore dopo un po che è attivato se non incontra il pezzo; si resetta solo togliendo temporaneam START_MARPOSS_O
		RESET_MARPOSS = !MARPOSS_NOERR_I && (RESET_ALL || RESET_MC);  

		// Sulla SXT (come sulla K30) la centralina marposs è programmata in modo da richiedere che START_MARPOSS_O=1 durante tutta la/e tastatura/e
		// (rimane 1 tra varie tastature)
		START_MARPOSS_O = (AUTO && START_MARPOSS && !RESET_MARPOSS || MANO && LAMP_TEST);



		// Interruzione programma da PLC 
		if (Mg_MC(118) && !TASTATURA_ATTIVA)    //TASTATURA_ATTIVA: tastatura con battuta di precisione attiva
		{
			VERFALS_CH0 = AUTO && START_MARPOSS && MARPOSS_TOUCH_I && MARPOSS_NOERR_I;
		}

		// Marposs in errore 
		if (MARPOSS_NOERR_I)
		{
			if (R[R_AB_MODULO_TAST] == 1)
				TIMEMARPOSS1 = 100;
			if (R[R_AB_MODULO_TAST] == 0)
				TIMEMARPOSS1 = 1;
		}
		else
		{
			if (TIMEMARPOSS1 > 0)
				TIMEMARPOSS1--;
		}

		APP_MARPOSS_NOERR = (TIMEMARPOSS1 > 0);

		if (RP_START_MARPOSS && !MARPOSS_NOERR_I)
		{
			R[R_PROBE_ERROR]  = 1;
		}
		if (RP_START_MARPOSS && !APP_MARPOSS_NOERR)
		{
			MARPOSS_ERROR_FAL = 1;
		}

		// Marposs batteria bassa 
		if (RP_START_MARPOSS && MARPOSS_LOWBA_I)			// <- START_MARPOSS
			MARPOSS_LOWBA_FAL = 1;

		// HOLD DA TASTATORE MARPOSS 
		MARPOSS_HOLD = START_MARPOSS && !MARPOSS_NOERR_I && O_LAV_CH0 ;


		if (Mg_MC(177) || RESET_MC)	// Controllo stato tastatore: FINE tastatore non premuto
		{
			Mr_MC(177);
			Mr_MC(178);
		}

		// TASTATORE GIA' IN BATTUTA AD INIZIO TASTATA
		if (Mg_MC(178) && MARPOSS_TOUCH_I && MARPOSS_NOERR_I)
			MARPOSS_TOUCH_FAL = 1;


		// TASTATORE ANCORA IN BATTUTA DOPO FINE TASTATA
		if (Mg_MC(176) && MARPOSS_TOUCH_I && MARPOSS_NOERR_I)
			MARPOSS_ST_TOUCH_FAL = 1;
		Mr_MC(176);


		// PEZZO NON RILEVATO
		if (Mg_MC(179) && !MARPOSS_TOUCH_I && MARPOSS_NOERR_I)
			MARPOSS_NOTOUCH_FAL = 1;
		Mr_MC(179);

		// ERRORE INDICE TASTATURA
		if (Mg_MC(184))
			MARPOSS_INDEX_FAL = 1;
		Mr_MC(184);

		// Verifica della entità delle correzioni: se troppo grandi dai allarme
		if(Mg_MC(120) && (   ((R[R_ID_TAST_X]>0.5) && ( ABS(R[R_APP_CORR_X]) >= ABS(R[R_MAX_TAST]/2.0) )  ) || 
			                 ((R[R_ID_TAST_Y]>0.5) && ( ABS(R[R_APP_CORR_Y]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||
				             ((R[R_ID_TAST_Z]>0.5) && ( ABS(R[R_APP_CORR_Z]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||

							 ((R[R_ID1_TAST_OBLIQUA]>0.5) && ( ABS(R[R_APP_CORR_TAST1_OBL_X]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||
							 ((R[R_ID1_TAST_OBLIQUA]>0.5) && ( ABS(R[R_APP_CORR_TAST1_OBL_Y]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||
							 ((R[R_ID1_TAST_OBLIQUA]>0.5) && ( ABS(R[R_APP_CORR_TAST1_OBL_Z]) >= ABS(R[R_MAX_TAST]/2.0) )  )
						 )
			)
						CORREZ_TOO_BIG_FAL = 1;     // correzioni troppo grandi (qualche problema si è verificato sulla tastatura)
		Mr_MC(120);

	}
	else if((R[R_MARPOSS]>0.5) && (R[R_INPUT_LATCH_PROBE]>0.5))
	{
		// INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE 
		if (PON)
		{
			CASE_LETTURA_MORSE_AX_XYZ = 0;
		}


		// ESECUZIONE PROGRAMMA SIMULATO 
		if (SIMULATORE_SU_CN || SIMULATORE_SU_PC)
		{
			MARPOSS_NOERR_I = START_MARPOSS_O;
			MARPOSS_LOWBA_I = 0;
			R[R_MARPOSS] = (float)0;
		}



		// Info x cnc
		R[R_MARPOSS_TOUCH] = MARPOSS_TOUCH_I;


		// RESET ALLARMI MARPOSS 
		if (RESET_ALL || RESET_MC)
		{
			MARPOSS_ERROR_FAL = 0;
			MARPOSS_LOWBA_FAL = 0;
		}

		// RESET ALLARMI MARPOSS SOLO CON RESET CNC
		if (RESET_MC)
		{
			MARPOSS_TOUCH_FAL = 0;
			MARPOSS_ST_TOUCH_FAL = 0;
			MARPOSS_NOTOUCH_FAL = 0;
			MARPOSS_INDEX_FAL = 0;
			CORREZ_TOO_BIG_FAL = 0;
		}


		// START MARPOSS 
		if (Mg_MC(118))
		{
			START_MARPOSS = 1;
			// Mr_MC(118);	spostato reset x mantener correttam abilitato il settaggio di VERFALS
		}
		if (Mg_MC(119) || RESET_MC)
		{
			//START_MARPOSS = 0;  spegnere il tastatore solo al cambio utensile
			Mr_MC(118);
			Mr_MC(119);
		}

		if(Mg_MC(174) || RESET_MC || M02)
		{
			Mr_MC(174);
			START_MARPOSS = 0;
		}

		if(!MARPOSS_TOUCH_I)
		{
			Mr_MC(175);  //reset funzione ausiliaria di attesa spegnimento ingresso marposs in battuta
		}

		//if ((AUTO && !START_MARPOSS))
		//	TIMESTARTMARPOSS1 = 6000;
		//else if (TIMESTARTMARPOSS1 >0)
		//	{
		//	TIMESTARTMARPOSS1--;
		//	}


		// Marposs va in errore dopo un po che è attivato se non incontra il pezzo; si resetta solo togliendo temporaneam START_MARPOSS_O
		RESET_MARPOSS = !MARPOSS_NOERR_I && (RESET_ALL || RESET_MC);  

		// Sulla SXT (come sulla K30) la centralina marposs è programmata in modo da richiedere che START_MARPOSS_O=1 durante tutta la/e tastatura/e
		// (rimane 1 tra varie tastature)
		START_MARPOSS_O = (AUTO && START_MARPOSS && !RESET_MARPOSS || MANO && LAMP_TEST);

		
		//************ LETTURA CORREZIONE TASTATORE TRAMITE INGRESSO LATCH SU AZIONAMENTO ASSI X, Y, Z *************		
		//latch_abort_condition_AX_X = RTPLC_FALSE;
		//FB_LatchAbort_Execute_AX_X = ( ACTIVE_M118 && RESET_MC );

		Omcnc_LatchAbort(&locvars->FB_LatchAbort_AX_X,
			FB_LatchAbort_Execute_AX_X,
			0,    // Numero del canale
			AX_X_CH0,
			&LatchAbort_Done_AX_X,
			&LatchAbort_Busy_AX_X,
			&LatchAbort_Error_AX_X,
			&LatchAbort_ErrorID_AX_X);
			
		//latch_abort_condition_AX_Y = RTPLC_FALSE;
		//FB_LatchAbort_Execute_AX_Y = ( ACTIVE_M118 && RESET_MC );

		Omcnc_LatchAbort(&locvars->FB_LatchAbort_AX_Y,
			FB_LatchAbort_Execute_AX_Y,
			0,    // Numero del canale
			AX_Y_CH0,
			&LatchAbort_Done_AX_Y,
			&LatchAbort_Busy_AX_Y,
			&LatchAbort_Error_AX_Y,
			&LatchAbort_ErrorID_AX_Y);

		//latch_abort_condition_AX_Z = RTPLC_FALSE;
		//FB_LatchAbort_Execute_AX_Z = ( ACTIVE_M118 && RESET_MC );

		Omcnc_LatchAbort(&locvars->FB_LatchAbort_AX_Z,
			FB_LatchAbort_Execute_AX_Z,
			0,    // Numero del canale
			AX_Z_CH0,
			&LatchAbort_Done_AX_Z,
			&LatchAbort_Busy_AX_Z,
			&LatchAbort_Error_AX_Z,
			&LatchAbort_ErrorID_AX_Z);

		if(!Mg_MC(118))
		{
			ACTIVE_M118 = 0;
		}
		
		latch_start_condition_AX_X = (RTPLC_BIT) (ACTIVE_M118);
		latch_start_condition_AX_Y = (RTPLC_BIT) (ACTIVE_M118);
		latch_start_condition_AX_Z = (RTPLC_BIT) (ACTIVE_M118);
		
		FB_LatchPos_Execute_AX_X = latch_start_condition_AX_X;
		FB_LatchPos_Execute_AX_Y = latch_start_condition_AX_Y;
		FB_LatchPos_Execute_AX_Z = latch_start_condition_AX_Z;

		Omcnc_LatchPos(&locvars->FB_LatchPos_AX_X,
			FB_LatchPos_Execute_AX_X,
			0,                            // Numero del canale
			AX_X_CH0,                     // Numero dell'asse
			1,                            // IndexLatch
			RTPLC_FALSE,                  // FrontNegative: 0= contatto N.O., 1= contatto N.C.
			(R[R_FCPOS_X]-R[R_FCNEG_X]),  // MaxDistance
			&LatchPos_Done_AX_X,
			&LatchPos_Busy_AX_X,
			&LatchPos_Error_AX_X,
			&LatchPos_ErrorID_AX_X,
			&latchError_AX_X,
			&latchArrived_AX_X,
			&latchArrived2_AX_X,
			&latchPosition_AX_X,
			&latchPosition2_AX_X);
			
		Omcnc_LatchPos(&locvars->FB_LatchPos_AX_Y,
			FB_LatchPos_Execute_AX_Y,
			0,                            // Numero del canale
			AX_Y_CH0,                     // Numero dell'asse
			1,                            // IndexLatch
			RTPLC_FALSE,                  // FrontNegative: 0= contatto N.O., 1= contatto N.C.
			(R[R_FCPOS_Y]-R[R_FCNEG_Y]),  // MaxDistance
			&LatchPos_Done_AX_Y,
			&LatchPos_Busy_AX_Y,
			&LatchPos_Error_AX_Y,
			&LatchPos_ErrorID_AX_Y,
			&latchError_AX_Y,
			&latchArrived_AX_Y,
			&latchArrived2_AX_Y,
			&latchPosition_AX_Y,
			&latchPosition2_AX_Y);

		Omcnc_LatchPos(&locvars->FB_LatchPos_AX_Z,
			FB_LatchPos_Execute_AX_Z,
			0,                            // Numero del canale
			AX_Z_CH0,                     // Numero dell'asse
			1,                            // IndexLatch
			RTPLC_FALSE,                  // FrontNegative: 0= contatto N.O., 1= contatto N.C.
			(R[R_FCPOS_Z]-R[R_FCNEG_Z]),  // MaxDistance
			&LatchPos_Done_AX_Z,
			&LatchPos_Busy_AX_Z,
			&LatchPos_Error_AX_Z,
			&LatchPos_ErrorID_AX_Z,
			&latchError_AX_Z,
			&latchArrived_AX_Z,
			&latchArrived2_AX_Z,
			&latchPosition_AX_Z,
			&latchPosition2_AX_Z);			

		//latch_err_AX_X = latchError_AX_X --> Superata la MaxDistance senza trovare il latch
		if (latchError_AX_X) {
			latch_err_AX_X = RTPLC_TRUE;
		}
		
		//latch_err_AY_Y = latchError_AY_Y --> Superata la MaYDistance senza trovare il latch
		if (latchError_AX_Y) {
			latch_err_AX_Y = RTPLC_TRUE;
		}

		//latch_err_AZ_Z = latchError_AZ_Z --> Superata la MaZDistance senza trovare il latch
		if (latchError_AX_Z) {
			latch_err_AX_Z = RTPLC_TRUE;
		}		

		//latch_success = latchArrived;
		DP_latchArrived_AX_X = 0;
		if(latchArrived_AX_X && !app_latchArrived_AX_X)
			DP_latchArrived_AX_X = 1;
		app_latchArrived_AX_X = latchArrived_AX_X;

		//latch_success = latchArrived2;
		DP_latchArrived2_AX_X = 0;
		if(latchArrived2_AX_X && !app_latchArrived2_AX_X)
			DP_latchArrived2_AX_X = 1;
		app_latchArrived2_AX_X = latchArrived2_AX_X;

		//latch_success = latchArrived;
		DP_latchArrived_AX_Y = 0;
		if(latchArrived_AX_Y && !app_latchArrived_AX_Y)
			DP_latchArrived_AX_Y = 1;
		app_latchArrived_AX_Y = latchArrived_AX_Y;

		//latch_success = latchArrived2;
		DP_latchArrived2_AX_Y = 0;
		if(latchArrived2_AX_Y && !app_latchArrived2_AX_Y)
			DP_latchArrived2_AX_Y = 1;
		app_latchArrived2_AX_Y = latchArrived2_AX_Y;

		//latch_success = latchArrived;
		DP_latchArrived_AX_Z = 0;
		if(latchArrived_AX_Z && !app_latchArrived_AX_Z)
			DP_latchArrived_AX_Z = 1;
		app_latchArrived_AX_Z = latchArrived_AX_Z;

		//latch_success = latchArrived2;
		DP_latchArrived2_AX_Z = 0;
		if(latchArrived2_AX_Z && !app_latchArrived2_AX_Z)
			DP_latchArrived2_AX_Z = 1;
		app_latchArrived2_AX_Z = latchArrived2_AX_Z;		
		
		//*** DERIVATA POSITIVA DI M118 ***
		DP_M118 = 0;
		if((Mg_MC(118) && !TASTATURA_ATTIVA) && !APP_M118)
			DP_M118 = 1;
		APP_M118 = (Mg_MC(118) && !TASTATURA_ATTIVA);   //TASTATURA_ATTIVA: tastatura con battuta di precisione attiva

		//*** START MACCHINA A STATI ***
		if(DP_M118)
		{
			CASE_LETTURA_MORSE_AX_XYZ = 10;
		}

		//***** MACCHINA A STATI PER LETTURA CORREZIONI TASTATORE *****
		switch(CASE_LETTURA_MORSE_AX_XYZ)
		{
		case 0:  // stato idle
			break;

		case 10: // stato di partenza dell'execute della FB
			if(!Mg_MC(118))
			{
				ACTIVE_M118 = 0;
				CASE_LETTURA_MORSE_AX_XYZ = 0;
			}
			else
			{
				ACTIVE_M118 = 1;
				LATCH_AX_X_ARRIVED = 0;
				LATCH_AX_Y_ARRIVED = 0;
				LATCH_AX_Z_ARRIVED = 0;
				ABORT_CMD_LATCH_AX_X_ESEG = 0;
				ABORT_CMD_LATCH_AX_Y_ESEG = 0;
				ABORT_CMD_LATCH_AX_Z_ESEG = 0;
				ABORT_LATCH_AX_X_ESEG = 0;    
				ABORT_LATCH_AX_Y_ESEG = 0;    
				ABORT_LATCH_AX_Z_ESEG = 0;    

				CASE_LETTURA_MORSE_AX_XYZ = 20;
			}
			break;

		case 20: // stato del latch arrived
			// Lettura valore origine:
			read_var (VL_FLOT, 5041, -1, AX_X_CH0, &VAL_ORIGIN_AX_X);
			read_var (VL_FLOT, 5041, -1, AX_Y_CH0, &VAL_ORIGIN_AX_Y);
			read_var (VL_FLOT, 5041, -1, AX_Z_CH0, &VAL_ORIGIN_AX_Z);
			
			// Lettura valore traslazione assoluta
			read_var (VL_FLOT, 5040, -1, AX_X_CH0, &VAL_TRASL_ABS_AX_X);
			read_var (VL_FLOT, 5040, -1, AX_Y_CH0, &VAL_TRASL_ABS_AX_Y);
			read_var (VL_FLOT, 5040, -1, AX_Z_CH0, &VAL_TRASL_ABS_AX_Z);

			// Lettura valore traslazione incrementale
			read_var (VL_FLOT, 5039, -1, AX_X_CH0, &VAL_TRASL_INC_AX_X);
			read_var (VL_FLOT, 5039, -1, AX_Y_CH0, &VAL_TRASL_INC_AX_Y);
			read_var (VL_FLOT, 5039, -1, AX_Z_CH0, &VAL_TRASL_INC_AX_Z);
			if(!Mg_MC(118))
			{
				ACTIVE_M118 = 0;
				CASE_LETTURA_MORSE_AX_XYZ = 50;
			}
				
			if(DP_latchArrived_AX_X || DP_latchArrived_AX_Y || DP_latchArrived_AX_Z)
			{
				VERFALS_CH0 = AUTO && START_MARPOSS && MARPOSS_NOERR_I;
			}
			
			if(DP_latchArrived_AX_X)
			{
				locvars->latch_success_AX_X = RTPLC_TRUE;
				pos_value_touch1_AX_X = latchPosition_AX_X;
				LATCH_AX_X_ARRIVED = 1;				
			}
			if(DP_latchArrived_AX_Y)
			{
				locvars->latch_success_AX_Y = RTPLC_TRUE;
				pos_value_touch1_AX_Y = latchPosition_AX_Y;
				LATCH_AX_Y_ARRIVED = 1;				
			}
			if(DP_latchArrived_AX_Z)
			{
				locvars->latch_success_AX_Z = RTPLC_TRUE;
				pos_value_touch1_AX_Z = latchPosition_AX_Z;
				LATCH_AX_Z_ARRIVED = 1;				
			}			
			
			if(DP_latchArrived2_AX_X)
			{
				locvars->latch_success_AX_X = RTPLC_TRUE;
				pos_value_touch2_AX_X = latchPosition2_AX_X;
				LATCH_AX_X_ARRIVED = 1;
			}
			if(DP_latchArrived2_AX_Y)
			{
				locvars->latch_success_AX_Y = RTPLC_TRUE;
				pos_value_touch2_AX_Y = latchPosition2_AX_Y;
				LATCH_AX_Y_ARRIVED = 1;
			}
			if(DP_latchArrived2_AX_Z)
			{
				locvars->latch_success_AX_Z = RTPLC_TRUE;
				pos_value_touch2_AX_Z = latchPosition2_AX_Z;
				LATCH_AX_Z_ARRIVED = 1;
			}

			if(LATCH_AX_X_ARRIVED && LATCH_AX_Y_ARRIVED && LATCH_AX_Z_ARRIVED)
			{
				CASE_LETTURA_MORSE_AX_XYZ = 30;
				ACTIVE_M118 = 0;
			}

			break;
		
		case 30: // stato di scrittura su aree R delle quote assi al touch
			{
				R[R_VAL_X_IN_TOUCH_LATCH] = pos_value_touch1_AX_X;   // Valore assoluto posizione asse X al touch
				R[R_VAL_Y_IN_TOUCH_LATCH] = pos_value_touch1_AX_Y;   // Valore assoluto posizione asse Y al touch
				R[R_VAL_Z_IN_TOUCH_LATCH] = pos_value_touch1_AX_Z;   // Valore assoluto posizione asse Z al touch

				R[R_POS_TOUCH_PROBE_AX_X] = (pos_value_touch1_AX_X - (VAL_ORIGIN_AX_X + VAL_TRASL_ABS_AX_X + VAL_TRASL_INC_AX_X));
				R[R_POS_TOUCH_PROBE_AX_Y] = (pos_value_touch1_AX_Y - (VAL_ORIGIN_AX_Y + VAL_TRASL_ABS_AX_Y + VAL_TRASL_INC_AX_Y));
				R[R_POS_TOUCH_PROBE_AX_Z] = (pos_value_touch1_AX_Z - (VAL_ORIGIN_AX_Z + VAL_TRASL_ABS_AX_Z + VAL_TRASL_INC_AX_Z));
				
				CASE_LETTURA_MORSE_AX_XYZ = 40;
			}
			break;
			
		case 40: // stato di attesa di fine FB
			{
				pos_value_touch1_AX_X = 0;
				pos_value_touch1_AX_Y = 0;
				pos_value_touch1_AX_Z = 0;
				pos_value_touch2_AX_X = 0;
				pos_value_touch2_AX_Y = 0;
				pos_value_touch2_AX_Z = 0;	

				VERFALS_CH0 = 0;

				CASE_LETTURA_MORSE_AX_XYZ = 0;
			}
			break;

		case 50:
			{
				pos_value_touch1_AX_X = 0;
				pos_value_touch1_AX_Y = 0;
				pos_value_touch1_AX_Z = 0;
				pos_value_touch2_AX_X = 0;
				pos_value_touch2_AX_Y = 0;
				pos_value_touch2_AX_Z = 0;

				VERFALS_CH0 = 0;

				if(!LatchPos_Busy_AX_X)
				{
					FB_LatchAbort_Execute_AX_X = RTPLC_TRUE;
					ABORT_CMD_LATCH_AX_X_ESEG = 1;
				}

				if(!LatchPos_Busy_AX_Y)
				{
					FB_LatchAbort_Execute_AX_Y = RTPLC_TRUE;
					ABORT_CMD_LATCH_AX_Y_ESEG = 1;
				}

				if(!LatchPos_Busy_AX_Z)
				{
					FB_LatchAbort_Execute_AX_Z = RTPLC_TRUE;
					ABORT_CMD_LATCH_AX_Z_ESEG = 1;
				}
				if(ABORT_CMD_LATCH_AX_X_ESEG && ABORT_CMD_LATCH_AX_Y_ESEG && ABORT_CMD_LATCH_AX_Z_ESEG)
				{
					CASE_LETTURA_MORSE_AX_XYZ = 55;
				}
			}
			break;

		case 55:
			{
				if(LatchAbort_Done_AX_X || LatchAbort_Error_AX_X)
				{
					FB_LatchAbort_Execute_AX_X = RTPLC_FALSE;
					ABORT_LATCH_AX_X_ESEG = 1;
				}
				if(LatchAbort_Done_AX_Y || LatchAbort_Error_AX_Y)
				{
					FB_LatchAbort_Execute_AX_Y = RTPLC_FALSE;
					ABORT_LATCH_AX_Y_ESEG = 1;
				}
				if(LatchAbort_Done_AX_Z || LatchAbort_Error_AX_Z)
				{
					FB_LatchAbort_Execute_AX_Z = RTPLC_FALSE;
					ABORT_LATCH_AX_Z_ESEG = 1;
				}
				if(ABORT_LATCH_AX_X_ESEG && ABORT_LATCH_AX_Y_ESEG && ABORT_LATCH_AX_Z_ESEG)
				{
					CASE_LETTURA_MORSE_AX_XYZ = 0;
				}
			}
			break;

		default:
			break;
		}
		//***** FINE MACCHINA A STATI PER QUOTE CORREZIONI TASTATORE *****

		if (RESET_MC) {
			latch_err_AX_X = RTPLC_FALSE;
			locvars->latch_success_AX_X = RTPLC_FALSE;

			latch_err_AX_Y = RTPLC_FALSE;
			locvars->latch_success_AX_Y = RTPLC_FALSE;

			latch_err_AX_Z = RTPLC_FALSE;
			locvars->latch_success_AX_Z = RTPLC_FALSE;			
		}
		

		// Marposs in errore 
		if (MARPOSS_NOERR_I)
		{
			if (R[R_AB_MODULO_TAST] == 1)
				TIMEMARPOSS1 = 100;
			if (R[R_AB_MODULO_TAST] == 0)
				TIMEMARPOSS1 = 1;
		}
		else
		{
			if (TIMEMARPOSS1 > 0)
				TIMEMARPOSS1--;
		}

		APP_MARPOSS_NOERR = (TIMEMARPOSS1 > 0);

		if (RP_START_MARPOSS && !MARPOSS_NOERR_I)
		{
			R[R_PROBE_ERROR]  = 1;
		}
		if (RP_START_MARPOSS && !APP_MARPOSS_NOERR)
		{
			MARPOSS_ERROR_FAL = 1;
		}

		// Marposs batteria bassa 
		if (RP_START_MARPOSS && MARPOSS_LOWBA_I)			// <- START_MARPOSS
			MARPOSS_LOWBA_FAL = 1;

		// HOLD DA TASTATORE MARPOSS 
		MARPOSS_HOLD = START_MARPOSS && !MARPOSS_NOERR_I && O_LAV_CH0;


		if (Mg_MC(177) || RESET_MC)	// Controllo stato tastatore: FINE tastatore non premuto
		{
			Mr_MC(177);
			Mr_MC(178);
		}

		// TASTATORE GIA' IN BATTUTA AD INIZIO TASTATA
		if (Mg_MC(178) && MARPOSS_TOUCH_I && MARPOSS_NOERR_I)
			MARPOSS_TOUCH_FAL = 1;


		// TASTATORE ANCORA IN BATTUTA DOPO FINE TASTATA
		if (Mg_MC(176) && MARPOSS_TOUCH_I && MARPOSS_NOERR_I)
			MARPOSS_ST_TOUCH_FAL = 1;
		Mr_MC(176);


		// PEZZO NON RILEVATO
		if (Mg_MC(179) && !MARPOSS_TOUCH_I && MARPOSS_NOERR_I)
			MARPOSS_NOTOUCH_FAL = 1;
		Mr_MC(179);

		// ERRORE INDICE TASTATURA
		if (Mg_MC(184))
			MARPOSS_INDEX_FAL = 1;
		Mr_MC(184);

		// Verifica della entità delle correzioni: se troppo grandi dai allarme
		if(Mg_MC(120) && (   ((R[R_ID_TAST_X]>0.5) && ( ABS(R[R_APP_CORR_X]) >= ABS(R[R_MAX_TAST]/2.0) )  ) || 
			                 ((R[R_ID_TAST_Y]>0.5) && ( ABS(R[R_APP_CORR_Y]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||
				             ((R[R_ID_TAST_Z]>0.5) && ( ABS(R[R_APP_CORR_Z]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||

							 ((R[R_ID1_TAST_OBLIQUA]>0.5) && ( ABS(R[R_APP_CORR_TAST1_OBL_X]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||
							 ((R[R_ID1_TAST_OBLIQUA]>0.5) && ( ABS(R[R_APP_CORR_TAST1_OBL_Y]) >= ABS(R[R_MAX_TAST]/2.0) )  ) ||
							 ((R[R_ID1_TAST_OBLIQUA]>0.5) && ( ABS(R[R_APP_CORR_TAST1_OBL_Z]) >= ABS(R[R_MAX_TAST]/2.0) )  )
						 )
			)
						CORREZ_TOO_BIG_FAL = 1;     // correzioni troppo grandi (qualche problema si è verificato sulla tastatura)
		Mr_MC(120);


	}
	else
	{
		MARPOSS_ERROR_FAL = 0;
		MARPOSS_LOWBA_FAL = 0;
		MARPOSS_TOUCH_FAL = 0;
		MARPOSS_ST_TOUCH_FAL = 0;
		MARPOSS_NOTOUCH_FAL = 0;
		MARPOSS_INDEX_FAL = 0;
		CORREZ_TOO_BIG_FAL = 0;
		Mr_MC(118);
		Mr_MC(119);
		Mr_MC(174);
		Mr_MC(175);
		MARPOSS_HOLD = 0;
	}

}
