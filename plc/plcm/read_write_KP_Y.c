
/*
        --------------------------------------------------------------
        TITOLO:         read_write_KP_Y
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione cambio KP su asse Y
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
//R6339		// (Y) la scrittura del kp temporaneo ha dato errore
//R6346		// (Y) la scrittura del KP definitivo ha dato errore
//R6350		// (Y) la lettura KP ha dato errore
//R6351		// (Y) non è stato riscritto correttamente il kp definitivo
//R6352		// (Y) KP_errato, diverso da quello definitivo

#include  "all.inc"

void change_KP_spazio_Y(USHORT num_AX, double kpval, BOOL Enable_RW_KP_Y, double fe_threshold_max, double fe_threshold_min)
{
	static double kpSpazio = 0;
	double val2write = 0;
	// unsigned int axis_moving_Y, axis_enabled_Y;
	//static BOOL Start_getParam_Y = FALSE, Start_setParam_Y = FALSE;
	//static BOOL Error_getParam_Y = FALSE, Error_setParam_Y = FALSE;
	//static BOOL Busy_Y = FALSE;
	//static BOOL done_Y = FALSE;
	static RTPLC_STATUS status = -10;
	static RTPLC_STATUS ret_getParam = -10;
	static RTPLC_STATUS ret_setParam = -10;

	if (PON)
	{
		R[R_kp_letto_Y] = 999;
	}

	axis_moving_Y =  ((unsigned short)AXSTATUS[num_AX].statusFlags.MOV) /*|| O_MOT_Y*/;  // Asse in movimento

	if(axis_moving_Y)             rit_axis_moving_Y = ((SHORT)(R[R_RIT_MOV_Y]));	// ritardo asse fermo
	else if (rit_axis_moving_Y>0) rit_axis_moving_Y = rit_axis_moving_Y-1 ;

	axis_moving2_Y = (axis_moving_Y || (rit_axis_moving_Y > 0));
	
	axis_enabled_Y = (unsigned short)AXSTATUS[num_AX].statusFlags2.SON; // Asse abilitato
	
	R[R_perror_Y] = (AXSTATUS[num_AX].perror);
	R[R_fabs_perror_Y] = fabs(AXSTATUS[num_AX].perror);
	
	SKIP_RW_KP_Y = (Busy_Y && RP_TSuppl[TS_TIMEOUT_RW_KP_Y]);	//	Tempo massimo disponibile per recupero errore inseguimento

	err_inseg_ko_Y = (R[R_fabs_perror_Y] >= fe_threshold_max);
	err_inseg_ok_Y = (R[R_fabs_perror_Y] <= fe_threshold_min);

	ABIL_CH_KP_01_Y = ( ( fabs(R[R_ABIL_CH_KP_Y]-1) ) < 0.2 );
	ABIL_CH_KP_02_Y = ( ( fabs(R[R_ABIL_CH_KP_Y]-2) ) < 0.2 );
	ABIL_CH_KP_03_Y = ( ( fabs(R[R_ABIL_CH_KP_Y]-3) ) < 0.2 );
	ABIL_CH_KP_04_Y = ( ( fabs(R[R_ABIL_CH_KP_Y]-4) ) < 0.2 );

	Attiva_KP_max_Y = 
		( ABIL_CH_KP_02_Y && M64  ) ||			// durante riferimento e ricerca morse lascia KP alto 
		( ABIL_CH_KP_03_Y && M253 );			// attivazione KP alto da M (occorre aggiunger M253/M254 nell'ISO)

	if (!Attiva_KP_max_Y)	R[R_KP_defin_Y] = R[R_KP_STD_Y];
	else					R[R_KP_defin_Y] = R[R_KP_ALTO_Y];

	KP_errato_Y = ( ( ( fabs(R[R_kp_letto_Y]-R[R_KP_defin_Y]) ) > 0.3 ) && (R[R_kp_letto_Y]<998) ) ;

	if ( KP_errato_Y && ( (RW_KP_STATUS_Y < 0) || (RW_KP_STATUS_Y > 29) ) )  { Abil_da_KP_err_Y=1; R[R_CONT_KP_Y_22] += 1; }	// KP_errato, diverso da quello definitivo
	if (!KP_errato_Y )                                                       { Abil_da_KP_err_Y=0; R[R_CONT_KP_Y_23] += 1; }

	if(ABIL_CH_KP_04_Y && err_inseg_ko_Y && !axis_moving2_Y) Attesa_err_inseg_ko_Y = 1;		// debug: permette di verificare il valore finale di inseguimento da recuperare, prima di procedere
	if(PLS_START_CYCLE_I || O_RESET)                         Attesa_err_inseg_ko_Y = 0;

	Abilitaz_CH_Y = (MANO || AUTO) && !O_RESET_MASTER && !O_RESET_SLAVE && axis_enabled_Y && Enable_RW_KP_Y && !SKIP_RW_KP_Y && !axis_moving2_Y && /*!inhibit &&*/ 
					((err_inseg_ko_Y && !Attiva_KP_max_Y) || Abil_da_KP_err_Y) && !Attesa_err_inseg_ko_Y;

	Cambio_KP_attivo_Y = Abilitaz_CH_Y || (RW_KP_STATUS_Y>=0);

	//if(O_RESET)	// abilitando questa parte il passaggio man/auto attiva il KP temp ma non riscrive quello di tarature perchè lo stato va a -10 
	//{
	//	status = -10;
	//	Start_getParam_Y = FALSE;
	//	Start_setParam_Y = FALSE;
	//	Error_getParam_Y = FALSE;
	//	Error_setParam_Y = FALSE;
	//}

	if( RESET_ALL || (R[R_CONT_KP_Y_00]>MAX_CONT_R) ) R[R_CONT_KP_Y_00] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_01]>MAX_CONT_R) ) R[R_CONT_KP_Y_01] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_02]>MAX_CONT_R) ) R[R_CONT_KP_Y_02] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_03]>MAX_CONT_R) ) R[R_CONT_KP_Y_03] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_04]>MAX_CONT_R) ) R[R_CONT_KP_Y_04] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_05]>MAX_CONT_R) ) R[R_CONT_KP_Y_05] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_06]>MAX_CONT_R) ) R[R_CONT_KP_Y_06] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_07]>MAX_CONT_R) ) R[R_CONT_KP_Y_07] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_08]>MAX_CONT_R) ) R[R_CONT_KP_Y_08] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_09]>MAX_CONT_R) ) R[R_CONT_KP_Y_09] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_10]>MAX_CONT_R) ) R[R_CONT_KP_Y_10] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_11]>MAX_CONT_R) ) R[R_CONT_KP_Y_11] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_12]>MAX_CONT_R) ) R[R_CONT_KP_Y_12] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_13]>MAX_CONT_R) ) R[R_CONT_KP_Y_13] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_14]>MAX_CONT_R) ) R[R_CONT_KP_Y_14] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_15]>MAX_CONT_R) ) R[R_CONT_KP_Y_15] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_16]>MAX_CONT_R) ) R[R_CONT_KP_Y_16] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_17]>MAX_CONT_R) ) R[R_CONT_KP_Y_17] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_18]>MAX_CONT_R) ) R[R_CONT_KP_Y_18] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_19]>MAX_CONT_R) ) R[R_CONT_KP_Y_19] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_20]>MAX_CONT_R) ) R[R_CONT_KP_Y_20] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_21]>MAX_CONT_R) ) R[R_CONT_KP_Y_21] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_22]>MAX_CONT_R) ) R[R_CONT_KP_Y_22] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Y_23]>MAX_CONT_R) ) R[R_CONT_KP_Y_23] = 0;

	if( RESET_ALL || (R[R_CONT_SCRITTURE_KP1_Y]>MAX_CONT_R) ) R[R_CONT_SCRITTURE_KP1_Y] = 0;
	if( RESET_ALL || (R[R_CONT_SCRITTURE_KP2_Y]>MAX_CONT_R) ) R[R_CONT_SCRITTURE_KP2_Y] = 0;
	if( RESET_ALL || (R[R_CONT_LETTURE_KP_Y]   >MAX_CONT_R) ) R[R_CONT_LETTURE_KP_Y] = 0;


	if(axis_moving2_Y || !Abilitaz_CH_Y)	// || !Enable_RW_KP_Y
	{
		done_Y = FALSE;			// *** flag di esecuz già effettuata (attualmente non usato) ***
	}

	switch (status)
	{
		case -10:  // idle (si arriva qui anche dopo eventuali errori)
			RW_KP_STATUS_Y = (SHORT) status;
			R[R_CONT_KP_Y_00] += 1;

			Busy_Y = FALSE;
			Error_getParam_Y = FALSE;
			Error_setParam_Y = FALSE;
			Start_getParam_Y = FALSE;
			Start_setParam_Y = FALSE;
			
			if(Abilitaz_CH_Y)
			{
				R[R_CONT_KP_Y_01] += 1;	
				if(err_inseg_ko_Y  && !Attiva_KP_max_Y)  status = 10;
				if(Abil_da_KP_err_Y || Attiva_KP_max_Y)  status = 21;
			}
			////else
			////{
			////	R[R_CONT_KP_Y_02] += 1;	
			////	status = 30;				// legger continuamente il KP a volte impedisce l'attivazione/disattivazione delle correzioni
			////}
		break;

		case 10: // preparazione per write KP temporaneo
			RW_KP_STATUS_Y = (SHORT) status;
			R[R_CONT_KP_Y_03] += 1;
			
			if(!Abilitaz_CH_Y)
			{
				R[R_CONT_KP_Y_04] += 1;	
				status = 30;
			}
			else
			{
				R[R_CONT_KP_Y_05] += 1;	
				Start_setParam_Y = TRUE;	//  
				Error_setParam_Y = FALSE;	//  
				status = 12;
			}
		break;

		case 12: // write KP temporaneo
			RW_KP_STATUS_Y = (SHORT) status;
			
			if(!Abilitaz_CH_Y)
			{
				R[R_CONT_KP_Y_06] += 1;
				status = 21;	// forse era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
				//if( SET_KP_STATUS_Y > 0 )
				//{
				//	R[R_CONT_KP_Y_06] += 1;
				//	status = 21;	// era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
				//}
				//else
				//{
				//	R[R_CONT_KP_Y_07] += 1;
				//	//old @@@ status = -10;
				//	status = 30;
				//}
			}
			else
			{
				R[R_CONT_KP_Y_08] += 1;
				val2write = kpval;
				ret_setParam = setParam_Y(num_AX, val2write);
				R[R_kp_scritto_Y] = val2write;

				if(Error_setParam_Y == TRUE)  //la scrittura del kp temporaneo ha dato errore
				{
					R[R_CONT_KP_Y_09] += 1;
					Start_setParam_Y = FALSE;
					if(ret_setParam == (RTPLC_STATUS) 0)
					{
						status = 21;	// era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
					}
				}
				else if((End_setParam_Y == TRUE) && (ret_setParam == (RTPLC_STATUS) 0) ) // scrittura KP temporaneo terminata correttamente
				{
					R[R_CONT_KP_Y_10] += 1;
					R[R_CONT_SCRITTURE_KP1_Y] += 1;
					status = 20;
				}
			}
		break;
	
		case 20: // wait status 
			RW_KP_STATUS_Y = (SHORT) status;
			R[R_CONT_KP_Y_11] += 1;
			Busy_Y = TRUE;				

			if( err_inseg_ok_Y || !Abilitaz_CH_Y || Abil_da_KP_err_Y )	// attesa err ins < soglia finale, oppure riscrittura immediata kp iniziale se cade abilitazione o se scade il tempo
			{
				R[R_CONT_KP_Y_12] += 1;
				status = 21;
			}
		break;
	
		case 21: // preparazione per restore prev KP
			RW_KP_STATUS_Y = (SHORT) status;
			R[R_CONT_KP_Y_13] += 1;
			Busy_Y = FALSE;				

			Start_setParam_Y = TRUE;	//  
			Error_setParam_Y = FALSE;	//  
			Busy_Y = FALSE;
			status = 22;
		break;

		case 22:  // restore prev KP
			RW_KP_STATUS_Y = (SHORT) status;
			R[R_CONT_KP_Y_15] += 1;
			Busy_Y = FALSE;

			val2write = R[R_KP_defin_Y];  // val delle tarature inserito anche in confmac
			ret_setParam = setParam_Y(num_AX, val2write);
			R[R_kp_scritto_Y] = val2write;

			if(Error_setParam_Y == TRUE)  //la scrittura del KP definitivo ha dato errore
			{
				R[R_CONT_KP_Y_16] += 1;
				Start_setParam_Y = FALSE;
				if(ret_setParam == (RTPLC_STATUS) 0)
				{
					status = 30;
				}
			}
			else if((End_setParam_Y == TRUE) && (ret_setParam == (RTPLC_STATUS) 0) ) // scrittura KP_tarature terminata correttamente
			{
				R[R_CONT_KP_Y_17] += 1;
				R[R_CONT_SCRITTURE_KP2_Y] += 1;
				Start_setParam_Y = FALSE;
				done_Y = TRUE;
				status = 30;
			}
		break;
	
		case 30: // preparazione per read KP
			RW_KP_STATUS_Y = (SHORT) status;
			R[R_CONT_KP_Y_18] += 1;

			Busy_Y = FALSE;
			Start_setParam_Y = FALSE;	
			Start_getParam_Y = TRUE;	

			Error_setParam_Y = FALSE;	
			Error_getParam_Y = FALSE;	
			status = 32;
		break;

		case 32: // read KP
			RW_KP_STATUS_Y = (SHORT) status;
			R[R_CONT_KP_Y_19] += 1;

			ret_getParam = getParam_Y(num_AX, &kpSpazio);
			R[R_kp_letto_Y] = kpSpazio;

			if(Error_getParam_Y == TRUE)  //la lettura KP ha dato errore
			{
				R[R_CONT_KP_Y_20] += 1;
				Start_getParam_Y = FALSE;
				if(ret_getParam == (RTPLC_STATUS) 0)
				{
					status = -10;
				}
			}
			else if((End_getParam_Y == TRUE) && (ret_getParam == (RTPLC_STATUS) 0) ) // lettura KP terminata correttamente
			{
				R[R_CONT_LETTURE_KP_Y] += 1;

				if ( ( fabs(R[R_kp_letto_Y]-R[R_KP_defin_Y]) ) > 0.3 )	
				{
					R[R_CONT_KP_Y_21] += 1;		// errore, non è stato riscritto correttamente il kp definitivo
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


RTPLC_STATUS getParam_Y(USHORT num_AX, double *kpSpazio) 
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
			GET_KP_STATUS_Y = (SHORT) status;
            if (Start_getParam_Y) 
			{
				End_getParam_Y = FALSE;
				Error_getParam_Y = FALSE;

				fbResult = AxisCmd(0, num_AX, OMCNC_CMD_CLEARALLCOMMANDS, &(s.param));
				if (fbResult == 0) {
					getKpSpazio_Y(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Y) Richiesta lettura kp di spazio");
				}
				if (fbResult < 0) {
					getKpSpazio_Y(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Y) CleanCommand KO in getParam");
				}

                //getKpSpazio_Y(0, num_AX, kpSpazio, &s);
                //NEXT_STATUS(status, "(Y) Richiesta lettura kp di spazio");
            } 
            break;

        case 1:
			GET_KP_STATUS_Y = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                ERROR_STATUS(status, "(Y) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else 
			{
                JUMP_STATUS(status, 11, "(Y) AxisCmd in getParam_Y() eseguita");
            }
            break;

        case 11:
			GET_KP_STATUS_Y = (SHORT) status;
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
            if (FB_SUCCESS(fbResult)) 
			{
                NEXT_STATUS(status, "(Y) Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else if (FB_FAILURE(fbResult)) 
			{
                LOG_MSG2(1, "(Y) Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				JUMP_STATUS(status, 60, "(Y) Errore nella lettura Kp di spazio");
            }
            break;

        case 12:
			GET_KP_STATUS_Y = (SHORT) status;
            Start_getParam_Y = FALSE;
			End_getParam_Y = TRUE;
			*kpSpazio = s.param.param[0];
			RESET_STATUS(status, "(Y) Lettura valore attuale Kp=%f di spazio", *kpSpazio);
            break;
			
		case 60:
			GET_KP_STATUS_Y = (SHORT) status;
            Start_getParam_Y = FALSE;
			Error_getParam_Y = TRUE;
			RESET_STATUS(status, "(Y) Errore nella lettura Kp di spazio");		
		break;		

        default:
			GET_KP_STATUS_Y = (SHORT) status;
		    Start_getParam_Y = FALSE;
			Error_getParam_Y = FALSE;
            RESET_STATUS(status, "");
            break;
    }
	FB_EXIT(status);
}

RTPLC_STATUS setParam_Y(USHORT num_AX, double kpSpazio) 
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
			SET_KP_STATUS_Y = (SHORT) status;
            if (Start_setParam_Y) 
			{
				Error_setParam_Y = FALSE;
				End_setParam_Y = FALSE;

				fbResult = AxisCmd(0, num_AX, OMCNC_CMD_CLEARALLCOMMANDS, &(s.param));

				if (fbResult == 0) {
					setKpSpazio_Y(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Y) CleanCommand OK in setParam, Richiesta scrittura kp di spazio");
				}
				if (fbResult < 0) {
					setKpSpazio_Y(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Y) CleanCommand KO in setParam");
				}

                //setKpSpazio_Y(0, num_AX, kpSpazio, &s);
                //NEXT_STATUS(status, "(Y) Richiesta scrittura kp di spazio");
            } 	
            break;

        case 1:
			SET_KP_STATUS_Y = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                ERROR_STATUS(status, "(Y) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else 
			{
                JUMP_STATUS(status, 11, "(Y) AxisCmd in setParam_Y() eseguita");
            }
            break;

        case 11:
			SET_KP_STATUS_Y = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                LOG_MSG2(1, "(Y) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				JUMP_STATUS(status, 60, "(Y) Errore nella scrittura Kp di spazio");	
            } 
			else 
			{
                NEXT_STATUS(status, "(Y) Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            }
            break;

        case 12:
			SET_KP_STATUS_Y = (SHORT) status;
            Start_setParam_Y = FALSE;
			End_setParam_Y = TRUE;
            RESET_STATUS(status, "(Y) Scrittura valore Kp=%f di spazio", kpSpazio);
            break;
			
		case 60:
			SET_KP_STATUS_Y = (SHORT) status;
			Start_setParam_Y = FALSE;
			Error_setParam_Y = TRUE;
			RESET_STATUS(status, "(Y) Errore nella scrittura Kp di spazio");		
		break;			

        default:
			SET_KP_STATUS_Y = (SHORT) status;
			Start_setParam_Y = FALSE;
			Error_setParam_Y = TRUE;
            RESET_STATUS(status, "");
            break;
    }
	FB_EXIT(status);
}


void getKpSpazio_Y(USHORT channel, USHORT axis, double *kpSpazio, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_GETPARAM;
    s->param.param[0] = axgpcKp;
    s->outValue = kpSpazio;
}

void setKpSpazio_Y(USHORT channel, USHORT axis, double kpSpazio, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_PUTPARAM;
    s->param.param[0] = axppcKp;
    s->param.param[1] = kpSpazio;
}
