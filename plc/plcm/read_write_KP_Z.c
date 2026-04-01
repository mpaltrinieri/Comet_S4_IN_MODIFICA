
/*
        --------------------------------------------------------------
        TITOLO:         read_write_KP_Z
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione cambio KP su asse Z
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
//R6369		// (Z) la scrittura del kp temporaneo ha dato errore
//R6376		// (Z) la scrittura del KP definitivo ha dato errore
//R6380		// (Z) la lettura KP ha dato errore
//R6381		// (Z) non è stato riscritto correttamente il kp definitivo
//R6382		// (Z) KP_errato, diverso da quello definitivo

#include  "all.inc"

void change_KP_spazio_Z(USHORT num_AX, double kpval, BOOL Enable_RW_KP_Z, double fe_threshold_max, double fe_threshold_min)
{
	static double kpSpazio = 0;
	double val2write = 0;
	// unsigned int axis_moving_Z, axis_enabled_Z;
	//static BOOL Start_getParam_Z = FALSE, Start_setParam_Z = FALSE;
	//static BOOL Error_getParam_Z = FALSE, Error_setParam_Z = FALSE;
	//static BOOL Busy_Z = FALSE;
	//static BOOL done_Z = FALSE;
	static RTPLC_STATUS status = -10;
	static RTPLC_STATUS ret_getParam = -10;
	static RTPLC_STATUS ret_setParam = -10;

	if (PON)
	{
		R[R_kp_letto_Z] = 999;
	}

	axis_moving_Z =  ((unsigned short)AXSTATUS[num_AX].statusFlags.MOV) /*|| O_MOT_Z*/;  // Asse in movimento

	if(axis_moving_Z)             rit_axis_moving_Z = ((SHORT)(R[R_RIT_MOV_Z]));	// ritardo asse fermo
	else if (rit_axis_moving_Z>0) rit_axis_moving_Z = rit_axis_moving_Z-1 ;

	axis_moving2_Z = (axis_moving_Z || (rit_axis_moving_Z > 0));

	axis_enabled_Z = (unsigned short)AXSTATUS[num_AX].statusFlags2.SON; // Asse abilitato
	
	R[R_perror_Z] = (AXSTATUS[num_AX].perror);
	R[R_fabs_perror_Z] = fabs(AXSTATUS[num_AX].perror);
	
	SKIP_RW_KP_Z = (Busy_Z && RP_TSuppl[TS_TIMEOUT_RW_KP_Z]);	//	Tempo massimo disponibile per recupero errore inseguimento

	err_inseg_ko_Z = (R[R_fabs_perror_Z] >= fe_threshold_max);
	err_inseg_ok_Z = (R[R_fabs_perror_Z] <= fe_threshold_min);

	ABIL_CH_KP_01_Z = ( ( fabs(R[R_ABIL_CH_KP_Z]-1) ) < 0.2 );
	ABIL_CH_KP_02_Z = ( ( fabs(R[R_ABIL_CH_KP_Z]-2) ) < 0.2 );
	ABIL_CH_KP_03_Z = ( ( fabs(R[R_ABIL_CH_KP_Z]-3) ) < 0.2 );
	ABIL_CH_KP_04_Z = ( ( fabs(R[R_ABIL_CH_KP_Z]-4) ) < 0.2 );

	Attiva_KP_max_Z = 
		( ABIL_CH_KP_02_Z && M64  ) ||			// durante riferimento e ricerca morse lascia KP alto 
		( ABIL_CH_KP_03_Z && M253 );			// attivazione KP alto da M (occorre aggiunger M253/M254 nell'ISO)

	if (!Attiva_KP_max_Z)	R[R_KP_defin_Z] = R[R_KP_STD_Z];
	else					R[R_KP_defin_Z] = R[R_KP_ALTO_Z];

	KP_errato_Z = ( ( ( fabs(R[R_kp_letto_Z]-R[R_KP_defin_Z]) ) > 0.3 ) && (R[R_kp_letto_Z]<998) ) ;

	if ( KP_errato_Z && ( (RW_KP_STATUS_Z < 0) || (RW_KP_STATUS_Z > 29) ) )  { Abil_da_KP_err_Z=1; R[R_CONT_KP_Z_22] += 1; }	// KP_errato, diverso da quello definitivo
	if (!KP_errato_Z )                                                       { Abil_da_KP_err_Z=0; R[R_CONT_KP_Z_23] += 1; }

	if(ABIL_CH_KP_04_Z && err_inseg_ko_Z && !axis_moving2_Z) Attesa_err_inseg_ko_Z = 1;		// debug: permette di verificare il valore finale di inseguimento da recuperare, prima di procedere
	if(PLS_START_CYCLE_I || O_RESET)                         Attesa_err_inseg_ko_Z = 0;

	Abilitaz_CH_Z = (MANO || AUTO) && !O_RESET_MASTER && !O_RESET_SLAVE && axis_enabled_Z && Enable_RW_KP_Z && !SKIP_RW_KP_Z && !axis_moving2_Z && /*!inhibit &&*/ 
					((err_inseg_ko_Z && !Attiva_KP_max_Z) || Abil_da_KP_err_Z) && !Attesa_err_inseg_ko_Z;

	Cambio_KP_attivo_Z = Abilitaz_CH_Z || (RW_KP_STATUS_Z>=0);

	//if(O_RESET)	// abilitando questa parte il passaggio man/auto attiva il KP temp ma non riscrive quello di tarature perchè lo stato va a -10 
	//{
	//	status = -10;
	//	Start_getParam_Z = FALSE;
	//	Start_setParam_Z = FALSE;
	//	Error_getParam_Z = FALSE;
	//	Error_setParam_Z = FALSE;
	//}

	if( RESET_ALL || (R[R_CONT_KP_Z_00]>MAX_CONT_R) ) R[R_CONT_KP_Z_00] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_01]>MAX_CONT_R) ) R[R_CONT_KP_Z_01] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_02]>MAX_CONT_R) ) R[R_CONT_KP_Z_02] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_03]>MAX_CONT_R) ) R[R_CONT_KP_Z_03] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_04]>MAX_CONT_R) ) R[R_CONT_KP_Z_04] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_05]>MAX_CONT_R) ) R[R_CONT_KP_Z_05] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_06]>MAX_CONT_R) ) R[R_CONT_KP_Z_06] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_07]>MAX_CONT_R) ) R[R_CONT_KP_Z_07] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_08]>MAX_CONT_R) ) R[R_CONT_KP_Z_08] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_09]>MAX_CONT_R) ) R[R_CONT_KP_Z_09] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_10]>MAX_CONT_R) ) R[R_CONT_KP_Z_10] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_11]>MAX_CONT_R) ) R[R_CONT_KP_Z_11] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_12]>MAX_CONT_R) ) R[R_CONT_KP_Z_12] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_13]>MAX_CONT_R) ) R[R_CONT_KP_Z_13] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_14]>MAX_CONT_R) ) R[R_CONT_KP_Z_14] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_15]>MAX_CONT_R) ) R[R_CONT_KP_Z_15] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_16]>MAX_CONT_R) ) R[R_CONT_KP_Z_16] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_17]>MAX_CONT_R) ) R[R_CONT_KP_Z_17] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_18]>MAX_CONT_R) ) R[R_CONT_KP_Z_18] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_19]>MAX_CONT_R) ) R[R_CONT_KP_Z_19] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_20]>MAX_CONT_R) ) R[R_CONT_KP_Z_20] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_21]>MAX_CONT_R) ) R[R_CONT_KP_Z_21] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_22]>MAX_CONT_R) ) R[R_CONT_KP_Z_22] = 0;
	if( RESET_ALL || (R[R_CONT_KP_Z_23]>MAX_CONT_R) ) R[R_CONT_KP_Z_23] = 0;

	if( RESET_ALL || (R[R_CONT_SCRITTURE_KP1_Z]>MAX_CONT_R) ) R[R_CONT_SCRITTURE_KP1_Z] = 0;
	if( RESET_ALL || (R[R_CONT_SCRITTURE_KP2_Z]>MAX_CONT_R) ) R[R_CONT_SCRITTURE_KP2_Z] = 0;
	if( RESET_ALL || (R[R_CONT_LETTURE_KP_Z]   >MAX_CONT_R) ) R[R_CONT_LETTURE_KP_Z] = 0;


	if(axis_moving2_Z || !Abilitaz_CH_Z)	// || !Enable_RW_KP_Z
	{
		done_Z = FALSE;			// *** flag di esecuz già effettuata (attualmente non usato) ***
	}

	switch (status)
	{
		case -10:  // idle (si arriva qui anche dopo eventuali errori)
			RW_KP_STATUS_Z = (SHORT) status;
			R[R_CONT_KP_Z_00] += 1;

			Busy_Z = FALSE;
			Error_getParam_Z = FALSE;
			Error_setParam_Z = FALSE;
			Start_getParam_Z = FALSE;
			Start_setParam_Z = FALSE;
			
			if(Abilitaz_CH_Z)
			{
				R[R_CONT_KP_Z_01] += 1;	
				if(err_inseg_ko_Z  && !Attiva_KP_max_Z)  status = 10;
				if(Abil_da_KP_err_Z || Attiva_KP_max_Z)  status = 21;
			}
			////else
			////{
			////	R[R_CONT_KP_Z_02] += 1;
			////	status = 30;				// legger continuamente il KP a volte impedisce l'attivazione/disattivazione delle correzioni
			////}
		break;

		case 10: // preparazione per write KP temporaneo
			RW_KP_STATUS_Z = (SHORT) status;
			R[R_CONT_KP_Z_03] += 1;
			
			if(!Abilitaz_CH_Z)
			{
				R[R_CONT_KP_Z_04] += 1;	
				status = 30;
			}
			else
			{
				R[R_CONT_KP_Z_05] += 1;	
				Start_setParam_Z = TRUE;	//  
				Error_setParam_Z = FALSE;	//  
				status = 12;
			}
		break;

		case 12: // write KP temporaneo
			RW_KP_STATUS_Z = (SHORT) status;
			
			if(!Abilitaz_CH_Z)
			{
				R[R_CONT_KP_Z_06] += 1;
				status = 21;	// forse era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
				//if( SET_KP_STATUS_Z > 0 )
				//{
				//	R[R_CONT_KP_Z_06] += 1;
				//	status = 21;	// era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
				//}
				//else
				//{
				//	R[R_CONT_KP_Z_07] += 1;
				//	//old @@@ status = -10;
				//	status = 30;
				//}
			}
			else
			{
				R[R_CONT_KP_Z_08] += 1;
				val2write = kpval;
				ret_setParam = setParam_Z(num_AX, val2write);
				R[R_kp_scritto_Z] = val2write;

				if(Error_setParam_Z == TRUE)  //la scrittura del kp temporaneo ha dato errore
				{
					R[R_CONT_KP_Z_09] += 1;
					Start_setParam_Z = FALSE;
					if(ret_setParam == (RTPLC_STATUS) 0)
					{
						status = 21;	// era iniziata la scrittura del kp temp, va a riscrivere il kp letto da tarature
					}
				}
				else if((End_setParam_Z == TRUE) && (ret_setParam == (RTPLC_STATUS) 0) ) // scrittura KP temporaneo terminata correttamente
				{
					R[R_CONT_KP_Z_10] += 1;
					R[R_CONT_SCRITTURE_KP1_Z] += 1;
					status = 20;
				}
			}
		break;
	
		case 20: // wait status 
			RW_KP_STATUS_Z = (SHORT) status;
			R[R_CONT_KP_Z_11] += 1;
			Busy_Z = TRUE;				

			if( err_inseg_ok_Z || !Abilitaz_CH_Z || Abil_da_KP_err_Z )	// attesa err ins < soglia finale, oppure riscrittura immediata kp iniziale se cade abilitazione o se scade il tempo
			{
				R[R_CONT_KP_Z_12] += 1;
				status = 21;
			}
		break;
	
		case 21: // preparazione per restore prev KP
			RW_KP_STATUS_Z = (SHORT) status;
			R[R_CONT_KP_Z_13] += 1;
			Busy_Z = FALSE;				

			Start_setParam_Z = TRUE;	//  
			Error_setParam_Z = FALSE;	//  
			Busy_Z = FALSE;
			status = 22;
		break;

		case 22:  // restore prev KP
			RW_KP_STATUS_Z = (SHORT) status;
			R[R_CONT_KP_Z_15] += 1;
			Busy_Z = FALSE;

			val2write = R[R_KP_defin_Z];  // val delle tarature inserito anche in confmac
			ret_setParam = setParam_Z(num_AX, val2write);
			R[R_kp_scritto_Z] = val2write;

			if(Error_setParam_Z == TRUE)  //la scrittura del KP definitivo ha dato errore
			{
				R[R_CONT_KP_Z_16] += 1;
				Start_setParam_Z = FALSE;
				if(ret_setParam == (RTPLC_STATUS) 0)
				{
					status = 30;
				}
			}
			else if((End_setParam_Z == TRUE) && (ret_setParam == (RTPLC_STATUS) 0) ) // scrittura KP_tarature terminata correttamente
			{
				R[R_CONT_KP_Z_17] += 1;
				R[R_CONT_SCRITTURE_KP2_Z] += 1;
				Start_setParam_Z = FALSE;
				done_Z = TRUE;
				status = 30;
			}
		break;
	
		case 30: // preparazione per read KP
			RW_KP_STATUS_Z = (SHORT) status;
			R[R_CONT_KP_Z_18] += 1;

			Busy_Z = FALSE;
			Start_setParam_Z = FALSE;	
			Start_getParam_Z = TRUE;	

			Error_setParam_Z = FALSE;	
			Error_getParam_Z = FALSE;	
			status = 32;
		break;

		case 32: // read KP
			RW_KP_STATUS_Z = (SHORT) status;
			R[R_CONT_KP_Z_19] += 1;

			ret_getParam = getParam_Z(num_AX, &kpSpazio);
			R[R_kp_letto_Z] = kpSpazio;

			if(Error_getParam_Z == TRUE)  //la lettura KP ha dato errore
			{
				R[R_CONT_KP_Z_20] += 1;
				Start_getParam_Z = FALSE;
				if(ret_getParam == (RTPLC_STATUS) 0)
				{
					status = -10;
				}
			}
			else if((End_getParam_Z == TRUE) && (ret_getParam == (RTPLC_STATUS) 0) ) // lettura KP terminata correttamente
			{
				R[R_CONT_LETTURE_KP_Z] += 1;

				if ( ( fabs(R[R_kp_letto_Z]-R[R_KP_defin_Z]) ) > 0.3 )	
				{
					R[R_CONT_KP_Z_21] += 1;		// errore, non è stato riscritto correttamente il kp definitivo
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


RTPLC_STATUS getParam_Z(USHORT num_AX, double *kpSpazio) 
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
			GET_KP_STATUS_Z = (SHORT) status;
            if (Start_getParam_Z) 
			{
				End_getParam_Z = FALSE;
				Error_getParam_Z = FALSE;

				fbResult = AxisCmd(0, num_AX, OMCNC_CMD_CLEARALLCOMMANDS, &(s.param));
				if (fbResult == 0) {
					getKpSpazio_Z(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Z) Richiesta lettura kp di spazio");
				}
				if (fbResult < 0) {
					getKpSpazio_Z(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Z) CleanCommand KO in getParam");
				}

                //getKpSpazio_Z(0, num_AX, kpSpazio, &s);
                //NEXT_STATUS(status, "(Z) Richiesta lettura kp di spazio");
            } 
            break;

        case 1:
			GET_KP_STATUS_Z = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                ERROR_STATUS(status, "(Z) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else 
			{
                JUMP_STATUS(status, 11, "(Z) AxisCmd in getParam_Z() eseguita");
            }
            break;

        case 11:
			GET_KP_STATUS_Z = (SHORT) status;
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
            if (FB_SUCCESS(fbResult)) 
			{
                NEXT_STATUS(status, "(Z) Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else if (FB_FAILURE(fbResult)) 
			{
                LOG_MSG2(1, "(Z) Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				JUMP_STATUS(status, 60, "(Z) Errore nella lettura Kp di spazio");
            }
            break;

        case 12:
			GET_KP_STATUS_Z = (SHORT) status;
            Start_getParam_Z = FALSE;
			End_getParam_Z = TRUE;
			*kpSpazio = s.param.param[0];
			RESET_STATUS(status, "(Z) Lettura valore attuale Kp=%f di spazio", *kpSpazio);
            break;
			
		case 60:
			GET_KP_STATUS_Z = (SHORT) status;
            Start_getParam_Z = FALSE;
			Error_getParam_Z = TRUE;
			RESET_STATUS(status, "(Z) Errore nella lettura Kp di spazio");		
		break;		

        default:
			GET_KP_STATUS_Z = (SHORT) status;
		    Start_getParam_Z = FALSE;
			Error_getParam_Z = FALSE;
            RESET_STATUS(status, "");
            break;
    }
	FB_EXIT(status);
}

RTPLC_STATUS setParam_Z(USHORT num_AX, double kpSpazio) 
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
			SET_KP_STATUS_Z = (SHORT) status;
            if (Start_setParam_Z) 
			{
				Error_setParam_Z = FALSE;
				End_setParam_Z = FALSE;

				fbResult = AxisCmd(0, num_AX, OMCNC_CMD_CLEARALLCOMMANDS, &(s.param));

				if (fbResult == 0) {
					setKpSpazio_Z(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Z) CleanCommand OK in setParam, Richiesta scrittura kp di spazio");
				}
				if (fbResult < 0) {
					setKpSpazio_Z(0, num_AX, kpSpazio, &s);
					NEXT_STATUS(status, "(Z) CleanCommand KO in setParam");
				}

                //setKpSpazio_Z(0, num_AX, kpSpazio, &s);
                //NEXT_STATUS(status, "(Z) Richiesta scrittura kp di spazio");
            } 	
            break;

        case 1:
			SET_KP_STATUS_Z = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                ERROR_STATUS(status, "(Z) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } 
			else 
			{
                JUMP_STATUS(status, 11, "(Z) AxisCmd in setParam_Z() eseguita");
            }
            break;

        case 11:
			SET_KP_STATUS_Z = (SHORT) status;
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) 
			{
                LOG_MSG2(1, "(Z) Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				JUMP_STATUS(status, 60, "(Z) Errore nella scrittura Kp di spazio");	
            } 
			else 
			{
                NEXT_STATUS(status, "(Z) Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            }
            break;

        case 12:
			SET_KP_STATUS_Z = (SHORT) status;
            Start_setParam_Z = FALSE;
			End_setParam_Z = TRUE;
            RESET_STATUS(status, "(Z) Scrittura valore Kp=%f di spazio", kpSpazio);
            break;
			
		case 60:
			SET_KP_STATUS_Z = (SHORT) status;
			Start_setParam_Z = FALSE;
			Error_setParam_Z = TRUE;
			RESET_STATUS(status, "(Z) Errore nella scrittura Kp di spazio");		
		break;			

        default:
			SET_KP_STATUS_Z = (SHORT) status;
			Start_setParam_Z = FALSE;
			Error_setParam_Z = TRUE;
            RESET_STATUS(status, "");
            break;
    }
	FB_EXIT(status);
}


void getKpSpazio_Z(USHORT channel, USHORT axis, double *kpSpazio, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_GETPARAM;
    s->param.param[0] = axgpcKp;
    s->outValue = kpSpazio;
}

void setKpSpazio_Z(USHORT channel, USHORT axis, double kpSpazio, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_PUTPARAM;
    s->param.param[0] = axppcKp;
    s->param.param[1] = kpSpazio;
}
