
/*
        --------------------------------------------------------------
        TITOLO:         read_write_KP_X
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione cambio KP su asse X
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       
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
        DATA:           14-04-2016
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Daniele Formuso
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

//R debug errori:
//R6309		// (X) la scrittura del kp temporaneo ha dato errore
//R6316		// (X) la scrittura del KP definitivo ha dato errore
//R6320		// (X) la lettura KP ha dato errore
//R6321		// (X) non è stato riscritto correttamente il kp definitivo
//R6322		// (X) KP_errato, diverso da quello definitivo

#include  "all.inc"

void change_KP_spazio_X(USHORT num_AX, double kpval, BOOL Enable_RW_KP_X, double fe_threshold_max, double fe_threshold_min)
{
	static double kpSpazio = 0;
	double val2write = 0;
	// unsigned int axis_moving_X, axis_enabled_X;
	//static BOOL Start_getParam_X = FALSE, Start_setParam_X = FALSE;
	//static BOOL Error_getParam_X = FALSE, Error_setParam_X = FALSE;
	//static BOOL Busy_X = FALSE;
	//static BOOL done_X = FALSE;
	static RTPLC_STATUS status = -10;
	static RTPLC_STATUS ret_getParam = -10;
	static RTPLC_STATUS ret_setParam = -10;

	if (PON)
	{
		R[R_kp_letto_X] = 999;
	}

	axis_moving_X =  ((unsigned short)AXSTATUS[num_AX].statusFlags.MOV) /*|| O_MOT_X*/;  // Asse in movimento

	if(axis_moving_X)             rit_axis_moving_X = ((SHORT)(R[R_RIT_MOV_X]));	//	ritardo asse fermo
	else if (rit_axis_moving_X>0) rit_axis_moving_X = rit_axis_moving_X-1 ;

	axis_moving2_X = (axis_moving_X || (rit_axis_moving_X > 0));

	axis_enabled_X = (unsigned short)AXSTATUS[num_AX].statusFlags2.SON; // Asse abilitato
	
	R[R_perror_X] = (AXSTATUS[num_AX].perror);
	R[R_fabs_perror_X] = fabs(AXSTATUS[num_AX].perror);
	
	SKIP_RW_KP_X = (Busy_X && RP_TSuppl[TS_TIMEOUT_RW_KP_X]);	//	Tempo massimo disponibile per recupero errore inseguimento

	err_inseg_ko_X = (R[R_fabs_perror_X] >= fe_threshold_max);
	err_inseg_ok_X = (R[R_fabs_perror_X] <= fe_threshold_min);

	ABIL_CH_KP_01_X = ( ( fabs(R[R_ABIL_CH_KP_X]-1) ) < 0.2 );
	ABIL_CH_KP_02_X = ( ( fabs(R[R_ABIL_CH_KP_X]-2) ) < 0.2 );
	ABIL_CH_KP_03_X = ( ( fabs(R[R_ABIL_CH_KP_X]-3) ) < 0.2 );
	ABIL_CH_KP_04_X = ( ( fabs(R[R_ABIL_CH_KP_X]-4) ) < 0.2 );

	Attiva_KP_max_X = 
		( ABIL_CH_KP_02_X && (M64 || M110 || M152 || M245) ) ||		// durante riferimento e ricerca morse lascia KP alto 
		( ABIL_CH_KP_03_X && M253 );								// attivazione KP alto da M (occorre aggiunger M253/M254 nell'ISO)

	if (!Attiva_KP_max_X)	R[R_KP_defin_X] = R[R_KP_STD_X];
	else					R[R_KP_defin_X] = R[R_KP_ALTO_X];

	KP_errato_X = ( ( ( fabs(R[R_kp_letto_X]-R[R_KP_defin_X]) ) > 0.3 ) && (R[R_kp_letto_X]<998) ) ;

	if ( KP_errato_X && ( (RW_KP_STATUS_X < 0) || (RW_KP_STATUS_X > 29) ) )  { Abil_da_KP_err_X=1; R[R_CONT_KP_X_22] += 1; }	// KP_errato, diverso da quello definitivo
	if (!KP_errato_X )                                                       { Abil_da_KP_err_X=0; R[R_CONT_KP_X_23] += 1; }

	if(ABIL_CH_KP_04_X && err_inseg_ko_X && !axis_moving2_X) Attesa_err_inseg_ko_X = 1;		// debug: permette di verificare il valore finale di inseguimento da recuperare, prima di procedere
	if(PLS_START_CYCLE_I || O_RESET)                         Attesa_err_inseg_ko_X = 0;

	Abilitaz_CH_X = (MANO || AUTO) && !O_RESET_MASTER && !O_RESET_SLAVE && axis_enabled_X && Enable_RW_KP_X && !SKIP_RW_KP_X && !axis_moving2_X && /*!inhibit &&*/ 
					((err_inseg_ko_X && !Attiva_KP_max_X) || Abil_da_KP_err_X) && !Attesa_err_inseg_ko_X /*&& !Cambio_COR_attivo_X*/;

	Cambio_KP_attivo_X = Abilitaz_CH_X || (RW_KP_STATUS_X>=0);

	//if(O_RESET)	// abilitando questa parte il passaggio man/auto attiva il KP temp ma non riscrive quello di tarature perchè lo stato va a -10 
	//{
	//	status = -10;
	//	Start_getParam_X = FALSE;
	//	Start_setParam_X = FALSE;
	//	Error_getParam_X = FALSE;
	//	Error_setParam_X = FALSE;
	//}

	if( RESET_ALL || (R[R_CONT_KP_X_00]>MAX_CONT_R) ) R[R_CONT_KP_X_00] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_01]>MAX_CONT_R) ) R[R_CONT_KP_X_01] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_02]>MAX_CONT_R) ) R[R_CONT_KP_X_02] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_03]>MAX_CONT_R) ) R[R_CONT_KP_X_03] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_04]>MAX_CONT_R) ) R[R_CONT_KP_X_04] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_05]>MAX_CONT_R) ) R[R_CONT_KP_X_05] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_06]>MAX_CONT_R) ) R[R_CONT_KP_X_06] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_07]>MAX_CONT_R) ) R[R_CONT_KP_X_07] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_08]>MAX_CONT_R) ) R[R_CONT_KP_X_08] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_09]>MAX_CONT_R) ) R[R_CONT_KP_X_09] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_10]>MAX_CONT_R) ) R[R_CONT_KP_X_10] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_11]>MAX_CONT_R) ) R[R_CONT_KP_X_11] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_12]>MAX_CONT_R) ) R[R_CONT_KP_X_12] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_13]>MAX_CONT_R) ) R[R_CONT_KP_X_13] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_14]>MAX_CONT_R) ) R[R_CONT_KP_X_14] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_15]>MAX_CONT_R) ) R[R_CONT_KP_X_15] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_16]>MAX_CONT_R) ) R[R_CONT_KP_X_16] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_17]>MAX_CONT_R) ) R[R_CONT_KP_X_17] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_18]>MAX_CONT_R) ) R[R_CONT_KP_X_18] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_19]>MAX_CONT_R) ) R[R_CONT_KP_X_19] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_20]>MAX_CONT_R) ) R[R_CONT_KP_X_20] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_21]>MAX_CONT_R) ) R[R_CONT_KP_X_21] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_22]>MAX_CONT_R) ) R[R_CONT_KP_X_22] = 0;
	if( RESET_ALL || (R[R_CONT_KP_X_23]>MAX_CONT_R) ) R[R_CONT_KP_X_23] = 0;

	if( RESET_ALL || (R[R_CONT_SCRITTURE_KP1_X]>MAX_CONT_R) ) R[R_CONT_SCRITTURE_KP1_X] = 0;
	if( RESET_ALL || (R[R_CONT_SCRITTURE_KP2_X]>MAX_CONT_R) ) R[R_CONT_SCRITTURE_KP2_X] = 0;
	if( RESET_ALL || (R[R_CONT_LETTURE_KP_X]   >MAX_CONT_R) ) R[R_CONT_LETTURE_KP_X] = 0;


	if(axis_moving2_X || !Abilitaz_CH_X)	// || !Enable_RW_KP_X
	{
		done_X = FALSE;			// *** flag di esecuz già effettuata (attualmente non usato) ***
	}

	switch (status)
	{
		case -10:  // idle (si arriva qui anche dopo eventuali errori)
			RW_KP_STATUS_X = (SHORT) status;
			R[R_CONT_KP_X_00] += 1;

			Busy_X = FALSE;
			Error_getParam_X = FALSE;
			Error_setParam_X = FALSE;
			Start_getParam_X = FALSE;
			Start_setParam_X = FALSE;
			
			if(Abilitaz_CH_X)
			{
				R[R_CONT_KP_X_01] += 1;	
				if(err_inseg_ko_X  && !Attiva_KP_max_X)  status = 10;
				if(Abil_da_KP_err_X || Attiva_KP_max_X)  status = 21;
			}
			////else
			////{
			////	R[R_CONT_KP_X_02] += 1;	
			////	status = 30;				// legger continuamente il KP a volte impedisce l'attivazione/disattivazione delle correzioni
			////}
		break;

		case 10: // preparazione per write KP temporaneo
			RW_KP_STATUS_X = (SHORT) status;
			R[R_CONT_KP_X_03] += 1;
			
			if(!Abilitaz_CH_X)
			{
				R[R_CONT_KP_X_04] += 1;	
				status = 30;
			}
			else
			{
				R[R_CONT_KP_X_05] += 1;	
				Start_setParam_X = TRUE;	//  
				Error_setParam_X = FALSE;	//  
				status = 12;
			}
		break;

		case 12: // write KP temporaneo
			RW_KP_STATUS_X = (SHORT) status;
			
			if(!Abilitaz_CH_X)
			{
				R[R_CONT_KP_X_06] += 1;
				status = 21;	// forse era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
				//if( SET_KP_STATUS_X > 0 )
				//{
				//	R[R_CONT_KP_X_06] += 1;
				//	status = 21;	// era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
				//}
				//else
				//{
				//	R[R_CONT_KP_X_07] += 1;
				//	//old @@@ status = -10;
				//	status = 30;
				//}
			}
			else
			{
				R[R_CONT_KP_X_08] += 1;
				val2write = kpval;
				ret_setParam = setParam_X(num_AX, val2write);
				R[R_kp_scritto_X] = val2write;

				if(Error_setParam_X == TRUE)  //la scrittura del kp temporaneo ha dato errore
				{
					R[R_CONT_KP_X_09] += 1;
					Start_setParam_X = FALSE;
					if(ret_setParam == (RTPLC_STATUS) 0)
					{
						status = 21;	// era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
					}
				}
				else if((End_setParam_X == TRUE) && (ret_setParam == (RTPLC_STATUS) 0) ) // scrittura KP temporaneo terminata correttamente
				{
					R[R_CONT_KP_X_10] += 1;
					R[R_CONT_SCRITTURE_KP1_X] += 1;
					status = 20;
				}
			}
		break;
	
		case 20: // wait status 
			RW_KP_STATUS_X = (SHORT) status;
			R[R_CONT_KP_X_11] += 1;
			Busy_X = TRUE;				

			if( err_inseg_ok_X || !Abilitaz_CH_X || Abil_da_KP_err_X )	// attesa err ins < soglia finale, oppure riscrittura immediata kp iniziale se cade abilitazione o se scade il tempo
			{
				R[R_CONT_KP_X_12] += 1;
				status = 21;
			}
		break;
	
		case 21: // preparazione per restore prev KP
			RW_KP_STATUS_X = (SHORT) status;
			R[R_CONT_KP_X_13] += 1;
			Busy_X = FALSE;				

			Start_setParam_X = TRUE;	//  
			Error_setParam_X = FALSE;	//  
			Busy_X = FALSE;
			status = 22;
		break;

		case 22:  // restore prev KP
			RW_KP_STATUS_X = (SHORT) status;
			R[R_CONT_KP_X_15] += 1;
			Busy_X = FALSE;

			val2write = R[R_KP_defin_X];  // val delle tarature inserito anche in confmac
			ret_setParam = setParam_X(num_AX, val2write);
			R[R_kp_scritto_X] = val2write;

			if(Error_setParam_X == TRUE)  //la scrittura del KP definitivo ha dato errore
			{
				R[R_CONT_KP_X_16] += 1;
				Start_setParam_X = FALSE;
				if(ret_setParam == (RTPLC_STATUS) 0)
				{
					status = 30;
				}
			}
			else if((End_setParam_X == TRUE) && (ret_setParam == (RTPLC_STATUS) 0) ) // scrittura KP_tarature terminata correttamente
			{
				R[R_CONT_KP_X_17] += 1;
				R[R_CONT_SCRITTURE_KP2_X] += 1;
				Start_setParam_X = FALSE;
				done_X = TRUE;
				status = 30;
			}
		break;
	
		case 30: // preparazione per read KP
			RW_KP_STATUS_X = (SHORT) status;
			R[R_CONT_KP_X_18] += 1;

			Busy_X = FALSE;
			Start_setParam_X = FALSE;	
			Start_getParam_X = TRUE;	

			Error_setParam_X = FALSE;	
			Error_getParam_X = FALSE;	
			status = 32;
		break;

		case 32: // read KP
			RW_KP_STATUS_X = (SHORT) status;
			R[R_CONT_KP_X_19] += 1;

			ret_getParam = getParam_X(num_AX, &kpSpazio);
			R[R_kp_letto_X] = kpSpazio;

			if(Error_getParam_X == TRUE)  //la lettura KP ha dato errore
			{
				R[R_CONT_KP_X_20] += 1;
				Start_getParam_X = FALSE;
				if(ret_getParam == (RTPLC_STATUS) 0)
				{
					status = -10;
				}
			}
			else if((End_getParam_X == TRUE) && (ret_getParam == (RTPLC_STATUS) 0) ) // lettura KP terminata correttamente
			{
				R[R_CONT_LETTURE_KP_X] += 1;

				if ( ( fabs(R[R_kp_letto_X]-R[R_KP_defin_X]) ) > 0.3 )	
				{
					R[R_CONT_KP_X_21] += 1;		// errore, non è stato riscritto correttamente il kp definitivo
					status = 21;				// torna direttam a impostare il kp giusto
				}
				else
				{
					status = -10;
				}
			}
		break;
		
		default:
		break;
	}

}


RTPLC_STATUS getParam_X(USHORT num_AX, double *kpSpazio) 
{
    static RTPLC_STATUS status = 0;
    static CmdAxisStruct s = {0};
    RTPLC_STATUS fbResult = FB_EXIT_FAILURE;

    //if (fbReset) {
    //    FB_RESET();
    //    status = 0;
    //    FB_EXIT(FB_EXIT_SUCCESS);
    //}

    switch (status) {
		
        case 0:
			GET_KP_STATUS_X = (SHORT) status;
            if (Start_getParam_X) 
			{
				End_getParam_X = FALSE;
				Error_getParam_X = FALSE;

				fbResult = AxisCmd(0, num_AX, OMCNC_CMD_CLEARALLCOMMANDS, &(s.param));
				if (fbResult == 0) {
					getKpSpazio_X(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(X) Richiesta lettura kp di spazio");
				}
				if (fbResult < 0) {
					getKpSpazio_X(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(X) CleanCommand KO in getParam");
				}

                //getKpSpazio_X(0, num_AX, kpSpazio, &s);
                //NEXT_STATUS(status, "(X) Richiesta lettura kp di spazio");
            } 
            break;

        case 1:
			GET_KP_STATUS_X = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                ERROR_STATUS(status, "(X) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else 
			{
                JUMP_STATUS(status, 11, "(X) AxisCmd in getParam_X() eseguita");
            }
            break;

        case 11:
			GET_KP_STATUS_X = (SHORT) status;
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
            if (FB_SUCCESS(fbResult)) 
			{
                NEXT_STATUS(status, "(X) Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else if (FB_FAILURE(fbResult)) 
			{
                LOG_MSG2(1, "(X) Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				JUMP_STATUS(status, 60, "(X) Errore nella lettura Kp di spazio");
            }
            break;

        case 12:
			GET_KP_STATUS_X = (SHORT) status;
            Start_getParam_X = FALSE;
			End_getParam_X = TRUE;
			*kpSpazio = s.param.param[0];
			RESET_STATUS(status, "(X) Lettura valore attuale Kp=%f di spazio", *kpSpazio);
            break;
			
		case 60:
			GET_KP_STATUS_X = (SHORT) status;
            Start_getParam_X = FALSE;
			Error_getParam_X = TRUE;
			RESET_STATUS(status, "(X) Errore nella lettura Kp di spazio");		
		break;		

        default:
			GET_KP_STATUS_X = (SHORT) status;
		    Start_getParam_X = FALSE;
			Error_getParam_X = FALSE;
            RESET_STATUS(status, "");
            break;
    }
	FB_EXIT(status);
}

RTPLC_STATUS setParam_X(USHORT num_AX, double kpSpazio) 
{
    static RTPLC_STATUS status = 0;
    static CmdAxisStruct s = {0};
    RTPLC_STATUS fbResult = FB_EXIT_FAILURE;

    //if (fbReset) {
    //    FB_RESET();
    //    status = 0;
    //    FB_EXIT(FB_EXIT_SUCCESS);
    //}

    switch (status) {

        case 0:
			SET_KP_STATUS_X = (SHORT) status;
            if (Start_setParam_X) 
			{
				Error_setParam_X = FALSE;
				End_setParam_X = FALSE;

				fbResult = AxisCmd(0, num_AX, OMCNC_CMD_CLEARALLCOMMANDS, &(s.param));

				if (fbResult == 0) {
					setKpSpazio_X(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(X) CleanCommand OK in setParam, Richiesta scrittura kp di spazio");
				}
				if (fbResult < 0) {
					setKpSpazio_X(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(X) CleanCommand KO in setParam");
				}

                //setKpSpazio_X(0, num_AX, kpSpazio, &s);
                //NEXT_STATUS(status, "(X) Richiesta scrittura kp di spazio");
            } 	
            break;

        case 1:
			SET_KP_STATUS_X = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                ERROR_STATUS(status, "(X) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else 
			{
                JUMP_STATUS(status, 11, "(X) AxisCmd in setParam_X() eseguita");
            }
            break;

        case 11:
			SET_KP_STATUS_X = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                LOG_MSG2(1, "(X) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				JUMP_STATUS(status, 60, "(X) Errore nella scrittura Kp di spazio");	
            } 
			else 
			{
                NEXT_STATUS(status, "(X) Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            }
            break;

        case 12:
			SET_KP_STATUS_X = (SHORT) status;
            Start_setParam_X = FALSE;
			End_setParam_X = TRUE;
            RESET_STATUS(status, "(X) Scrittura valore Kp=%f di spazio", kpSpazio);
            break;
			
		case 60:
			SET_KP_STATUS_X = (SHORT) status;
			Start_setParam_X = FALSE;
			Error_setParam_X = TRUE;
			RESET_STATUS(status, "(X) Errore nella scrittura Kp di spazio");		
		break;			

        default:
			SET_KP_STATUS_X = (SHORT) status;
			Start_setParam_X = FALSE;
			Error_setParam_X = TRUE;
            RESET_STATUS(status, "");
            break;
    }
	FB_EXIT(status);
}


void getKpSpazio_X(USHORT channel, USHORT axis, double *kpSpazio, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_GETPARAM;
    s->param.param[0] = axgpcKp;
    s->outValue = kpSpazio;
}

void setKpSpazio_X(USHORT channel, USHORT axis, double kpSpazio, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_PUTPARAM;
    s->param.param[0] = axppcKp;
    s->param.param[1] = kpSpazio;
}
