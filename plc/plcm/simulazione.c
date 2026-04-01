/*
        --------------------------------------------------------------
        TITOLO:         Simulazione
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione Simulazione
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    Simulazione(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:     
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:    
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.001
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           31-08-2006
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"


#define START_SIMU_IDLE             0  //stato inattivo macchina a stati per start simulazione
#define START_SIMU_AUXON           10  //stato axon macchina a stati per start simulazione
#define START_SIMU_AUTO            20  //stato automatico macchina a stati per start simulazione
#define START_SIMU_CYCLE           30  //stato start ciclo macchina a stati per start simulazione
#define START_SIMU_DELAY          100  //stato reset timer ritardi per simulazione per start simulazione




void    simulazione(void)
{


	// Operazioni da eseguire in simulazione TIME-X
	if(SIMULATORE_SU_CN)
	{

		R[R_0] = 123456;


		if (PON)
		{
			R[R_SEL] = (float) 1;
		}


		R[R_SIM_AUX] = 1;

		//Elimino per ora l'allarme di utensile sconosciuto
		R[R_UTSCON] = 0;
		UTSCON = 0;

		//*************** MACCHINA A STATI PER LA PARTENZA DEL SIMULATORE *****************

		if(PON)
		{
			STATE_SIMU_MACHINE = START_SIMU_IDLE;
		}

		switch(STATE_SIMU_MACHINE)
		{

		case START_SIMU_IDLE:
			AUX_INSER_I = 1;	//	(RITAUXINS<=0);							// (2001,02)
			SEL_AUTO_I = (RITSELAUTO<=0) && (R[R_START] > 0.5);		// (2001,11)
			SEL_MANU_I = !SEL_AUTO_I;								// (2001,12)

			if(!RP_PON || (R[R_START] < 0.5))
			{
				RITAUXINS = 200;
				RITSELAUTO = 100;
				RITSTCYCLE1 = 100;
			}
			else if(RITAUXINS > 0)
				RITAUXINS --;

			if(RP_PON && (RITAUXINS<=0)) 
				STATE_SIMU_MACHINE = START_SIMU_AUXON;

			break;

		case START_SIMU_AUXON:
			SEL_AUTO_I = (RITSELAUTO<=0) && (R[R_START] > 0.5);
			SEL_MANU_I = !SEL_AUTO_I;
			AUX_INSER_I = (RITAUXINS<=0);

			if(AUX_INSER_I && (RITSELAUTO>0) ) 
				RITSELAUTO --;

			if(AUX_INSER_I && (RITSELAUTO<=0))
				STATE_SIMU_MACHINE = START_SIMU_AUTO;
			break;

		case START_SIMU_AUTO:
			AUX_INSER_I = (RITAUXINS<=0);
			SEL_AUTO_I = (RITSELAUTO<=0);
			SEL_MANU_I = !SEL_AUTO_I;

			if(SEL_AUTO_I && (RITSTCYCLE1>0))
				RITSTCYCLE1--;


			if(SEL_AUTO_I && (RITSTCYCLE1<=0))
			{
				STATE_SIMU_MACHINE = START_SIMU_CYCLE;
			}
			break;

		case START_SIMU_CYCLE:
			AUX_INSER_I = (RITAUXINS<=0);
			SEL_AUTO_I = (RITSELAUTO<=0) || (R[R_DOUBLE] > 0.5);
			SEL_MANU_I = !SEL_AUTO_I;

			if (!RP_AUXON || !RP_AUTO || RESET_MC || (R[R_START]>1.5) )   // (R470>1) permette di cambiar il ciclo da eseguire
			{
				RITSTCYCLE2 = 100;
				R[R_4040] +=1;

				if(R[R_4040] > 9999) R[R_4040] = 0;

				if( (R[R_START]>1.5) && (R[R_DRILL_START]>0.5) )  // Serve per riparire dopo M00
					R[R_START] = 1.0;
			}
			else if (RITSTCYCLE2 > 0)
			{
				RITSTCYCLE2--;
				R[R_4041] += 1;

				if(R[R_4041] > 9999) R[R_4041] = 0;
			}

			if(DP_M00)
			{
				R[R_START] = 2.0;
			}

			// Costruisco la derivata positiva di M00
			DP_M00 = 0;
			if(M00 && !APP_M00_OLD)
				DP_M00 = 1;

			APP_M00_OLD = M00;

			R[R_DRILL_START]  = (RITSTCYCLE2>5) && (RITSTCYCLE2<20);
			
			if(R[R_SEND_RESET] > 0.5)  R[R_4034] += 1;
			if(R[R_CLOSE_CYCLE] > 0.5) R[R_4035] += 1;

			if(R[R_4034] > 9999) R[R_4034] = 0;
			if(R[R_4035] > 9999) R[R_4035] = 0;

			if((R[R_START]<0.5))
			{
				STATE_SIMU_MACHINE = START_SIMU_DELAY;
			}

			break;

		case START_SIMU_DELAY:
			RITAUXINS = 200;
			RITSELAUTO = 100;
			RITSTCYCLE1 = 100;
			RITSTCYCLE2 = 0;

			STATE_SIMU_MACHINE = START_SIMU_IDLE;
			break;

		}

		//***************************************************************************************

		ALIM_PRES_I = 1;
		NO_EMERG_I  = 1;
		//AUX_INSER_I         = (RITAUXINS == 0);

		ARIA_PRES_I		= 1;
		TERM_GEN_I		= 1;
		ARIA_PRES_I		= 1;
		LOAD_INVERTEROK_I   = 1;
		VEL_INVERTEROK_I    = 1;
		INV_NONBLOC_I		= 1;
		MEM_INPUT_MAND_FERMO = 1;
		OUT_MAC_ABIL_I		= 1;
		UOMO_MORTO_I        = 1;

		TERM_GEN_I			= 1;
		//SEL_MANU_I          = (O_JOG || SIMULATORE_ON) && !SEL_AUTO_I;
		//SEL_AUTO_I          = (RITAUXINS == 0);
		TEMP_OK_I			= 1;

		CENTRALINA_OK_I		= 1;
		FLUSSOSTATO_OK_I	= 1;
		TERM_FRIGO_OK_I     = 1;
		TERM_TRASP_OK_I		= 1;

		TERM_ASP_OK_I		= 1;


		MARPOSS_LOWBA_I		= 1;
		LIV_LUB_NO_BASSO_I	= 1;
		LIV_LUB_NO_ALTO_I	= 1;
		RIPARO_POST_SX_CH_I	= 1;
		RIPARO_POST_DX_CH_I	= 1;

		ALIM_MM_OK_I		= 1;

		GANCIO_MAG_NOINS_I      = 1;

		//******* FORZA POSIZIONI MORSE ALL'ACCENSIONE ******
		// inizializza posizione morse
		if ((!RP_PON && !MORSE_MOTORIZZATE) || (MORSE_MOTORIZZATE && ALMENO_UN_ASSE_MORSA_NON_RIFERITO))
		{
			if(CONF_MORSA_10) R[R_POS_ATTUALE_M10] = 1000;
			else             R[R_POS_ATTUALE_M10] = 0;

			if(CONF_MORSA_11) R[R_POS_ATTUALE_M11] = 1400;
			else             R[R_POS_ATTUALE_M11] = 0;

			if(CONF_MORSA_12) R[R_POS_ATTUALE_M12] = 1800;
			else             R[R_POS_ATTUALE_M12] = 0;


			if(CONF_MORSA_13) R[R_POS_ATTUALE_M13] = 2200;
			else             R[R_POS_ATTUALE_M13] = 0;

			if(CONF_MORSA_14) R[R_POS_ATTUALE_M14] = 2600;
			else             R[R_POS_ATTUALE_M14] = 0;

			if(CONF_MORSA_15) R[R_POS_ATTUALE_M15] = 3000;
			else             R[R_POS_ATTUALE_M15] = 0;

		}

		// In simulazione forzo a zero il controllo posizione morse
		CONF_POS_MORSE = 0;


		//******* FINE FORZATURA PRESENZA MICRO MORSA IN RICERCA MORSE MOTORIZZATE ******


		// Pulsanti simulati con il programma Funzioni manuali
		/*
		PLS_A_I = (R[R_SIM_PLS_A] == 1) || (R[R_AIUTA_PLS] == 7);
		PLS_B_I = (R[R_SIM_PLS_B] == 1) || (R[R_AIUTA_PLS] == 8);


		AUX_INSER_I			= (R[R_SIM_AUX] == 1);
		PLS_START_CYCLE_I	= (R[R_SIM_START] == 1);
		SEL_AUTO_I			= (R[R_SIM_AUTO] == 2);	    //STRINGA_SIMU = SEL_MANU_I && PLS_START_CYCLE_I;
		SEL_MANU_I			= !SEL_AUTO_I;
		*/

		// Simulo l'ingresso di utensile presente
		TOOL_PRES_SUP_I = TOOL_PRES_INF_I = UT0_ACT;

		tavola_simu();

		battuta_sx1_simu();
		battuta_dx4_simu();

		mandrino_simu();

		// Alta pressione regolata
		//Simulazione alta pressione
		if(CONF_MORSA_10 || CONF_MORSA_11 || CONF_MORSA_12 || CONF_MORSA_13 || CONF_MORSA_14 || CONF_MORSA_15)
		{
			PRESS_MORSE_HP_I = 1;
		}

	    riparo_simu();
		////OUT_MAC_ABIL_I   = ( (FTL_APPO_RIPARO_CH_INP && !CONF_VIS_ALTA) || RIP_ANT_CH_SICUR_I) ;

		rilev_morse_ax_X_simu();

		trasc_ax_X_simu();
		PRESENZA_MORSA_AX_X_I = (DP_OSCILLATORE && INS_RILMOR_AX_X_O) || !INS_RILMOR_AX_X_O || TRASC_MORSE_AX_X_INS_I;

		visiera_bassa_simu();
		visiera_alta_simu();

	}
	else if(SIMULATORE_SU_PC)
	{

		R[R_0] = 123456;


		/* Modifiche per simulatore grafico SIMON ************* inizio */
		
		if ( (R[R_SIMON_START]>0.5) && !M00)
		{
			R[R_START] = 1.0; 
			R[R_ISOMG_UPDATED] = 1.0; 
			//R[R_SIMON_START] = 0.0;    // Viene resettata in central.c
			R[R_DRILL_START] = 1.0; 
		}

		/* Modifiche per simulatore grafico SIMON ************* fine */



		if (PON)
		{
			R[R_SEL] = (float) 1;
		}


		R[R_SIM_AUX] = 1;

		//Elimino per ora l'allarme di utensile sconosciuto
		R[R_UTSCON] = 0;
		UTSCON = 0;

		//*************** MACCHINA A STATI PER LA PARTENZA DEL SIMULATORE *****************

		if(PON)
		{
			STATE_SIMU_MACHINE = START_SIMU_IDLE;
		}

		switch(STATE_SIMU_MACHINE)
		{

		case START_SIMU_IDLE:
			AUX_INSER_I = 1;	//	(RITAUXINS<=0);							// (2001,02)
			SEL_AUTO_I = (RITSELAUTO<=0);		// (2001,11)
			SEL_MANU_I = !SEL_AUTO_I;								// (2001,12)

			if(!RP_PON || (R[R_START] < 0.5))
			{
				RITAUXINS = 200;
				RITSELAUTO = 100;
				RITSTCYCLE1 = 100;
			}
			else if(RITAUXINS > 0)
				RITAUXINS --;

			if(RP_PON && (RITAUXINS<=0)) 
				STATE_SIMU_MACHINE = START_SIMU_AUXON;
			break;

		case START_SIMU_AUXON:
			SEL_AUTO_I = (RITSELAUTO<=0);
			SEL_MANU_I = !SEL_AUTO_I;
			AUX_INSER_I = 1;

			if(AUX_INSER_I && (RITSELAUTO>0) ) 
				RITSELAUTO --;

			if(AUX_INSER_I && (RITSELAUTO<=0))
				STATE_SIMU_MACHINE = START_SIMU_AUTO;
			break;

		case START_SIMU_AUTO:
			AUX_INSER_I = 1;
			SEL_AUTO_I = (RITSELAUTO<=0);
			SEL_MANU_I = !SEL_AUTO_I;

			if(SEL_AUTO_I && (RITSTCYCLE1>0))
				RITSTCYCLE1--;


			if(SEL_AUTO_I && (RITSTCYCLE1<=0))
			{
				STATE_SIMU_MACHINE = START_SIMU_CYCLE;
			}
			break;

		case START_SIMU_CYCLE:
			AUX_INSER_I = (RITAUXINS<=0);
			SEL_AUTO_I = (RITSELAUTO<=0) || (R[R_DOUBLE] > 0.5);
			SEL_MANU_I = !SEL_AUTO_I;

			if (!RP_AUXON || !RP_AUTO || RESET_MC || (R[R_START]>1.5) )   // (R470>1) permette di cambiar il ciclo da eseguire
			{
				RITSTCYCLE2 = 100;
				R[R_4040] +=1;

				if(R[R_4040] > 9999) R[R_4040] = 0;

				if((R[R_START]>1.5) && ( (R[R_DRILL_START]>0.5) || (R[R_SIMON_START]>0.5) )   )  // Serve per riparire dopo M00
					R[R_START] = 1.0;
			}
			else if (RITSTCYCLE2 > 0)
			{
				RITSTCYCLE2--;
				R[R_4041] += 1;

				if(R[R_4041] > 9999) R[R_4041] = 0;
			}

			if(DP_M00)
			{
				R[R_START] = 2.0;
			}

			// Costruisco la derivata positiva di M00
			DP_M00 = 0;
			if(M00 && !APP_M00_OLD)
				DP_M00 = 1;

			APP_M00_OLD = M00;

			R[R_DRILL_START]  = (RITSTCYCLE2>5) && (RITSTCYCLE2<20) && !CICLO_ON;
			

			if(R[R_SEND_RESET] > 0.5)  R[R_4034] += 1;
			if(R[R_CLOSE_CYCLE] > 0.5) R[R_4035] += 1;

			if(R[R_4034] > 9999) R[R_4034] = 0;
			if(R[R_4035] > 9999) R[R_4035] = 0;

			if((R[R_START]<0.5) )
			{
				STATE_SIMU_MACHINE = START_SIMU_DELAY;
			}

			break;

		case START_SIMU_DELAY:
			RITAUXINS = 200;
			RITSELAUTO = 100;
			RITSTCYCLE1 = 100;
			RITSTCYCLE2 = 0;
			STATE_SIMU_MACHINE = START_SIMU_IDLE;
			break;

		}

		//***************************************************************************************

		ALIM_PRES_I = 1;
		NO_EMERG_I  = 1;
		//AUX_INSER_I         = (RITAUXINS == 0);

		ARIA_PRES_I		= 1;
		TERM_GEN_I		= 1;
		ARIA_PRES_I		= 1;
		LOAD_INVERTEROK_I   = 1;
		VEL_INVERTEROK_I    = 1;
		INV_NONBLOC_I		= 1;
		MEM_INPUT_MAND_FERMO = 1;
		OUT_MAC_ABIL_I		= 1;
		UOMO_MORTO_I        = 1;

		TERM_GEN_I			= 1;
		//SEL_MANU_I          = (O_JOG || SIMULATORE_ON) && !SEL_AUTO_I;
		//SEL_AUTO_I          = (RITAUXINS == 0);
		TEMP_OK_I			= 1;

		CENTRALINA_OK_I		= 1;
		FLUSSOSTATO_OK_I	= 1;
		TERM_FRIGO_OK_I     = 1;
		TERM_TRASP_OK_I		= 1;

		TERM_ASP_OK_I		= 1;


		MARPOSS_LOWBA_I		= 1;
		LIV_LUB_NO_BASSO_I	= 1;
		LIV_LUB_NO_ALTO_I	= 1;
		RIPARO_POST_SX_CH_I	= 1;
		RIPARO_POST_DX_CH_I	= 1;

		ALIM_MM_OK_I		= 1;

		GANCIO_MAG_NOINS_I      = 1;

		//******* FORZA POSIZIONI MORSE ALL'ACCENSIONE ******
		// inizializza posizione morse
		if ((!RP_PON && !MORSE_MOTORIZZATE) || (MORSE_MOTORIZZATE && ALMENO_UN_ASSE_MORSA_NON_RIFERITO))
		{
			if(CONF_MORSA_10) R[R_POS_ATTUALE_M10] = 1000;
			else             R[R_POS_ATTUALE_M10] = 0;

			if(CONF_MORSA_11) R[R_POS_ATTUALE_M11] = 1400;
			else             R[R_POS_ATTUALE_M11] = 0;

			if(CONF_MORSA_12) R[R_POS_ATTUALE_M12] = 1800;
			else             R[R_POS_ATTUALE_M12] = 0;


			if(CONF_MORSA_13) R[R_POS_ATTUALE_M13] = 2200;
			else             R[R_POS_ATTUALE_M13] = 0;

			if(CONF_MORSA_14) R[R_POS_ATTUALE_M14] = 2600;
			else             R[R_POS_ATTUALE_M14] = 0;

			if(CONF_MORSA_15) R[R_POS_ATTUALE_M15] = 3000;
			else             R[R_POS_ATTUALE_M15] = 0;

		}

		// In simulazione forzo a zero il controllo posizione morse
		CONF_POS_MORSE = 0;


		//******* FINE FORZATURA PRESENZA MICRO MORSA IN RICERCA MORSE MOTORIZZATE ******


		// Pulsanti simulati con il programma Funzioni manuali
		/*
		PLS_A_I = (R[R_SIM_PLS_A] == 1) || (R[R_AIUTA_PLS] == 7);
		PLS_B_I = (R[R_SIM_PLS_B] == 1) || (R[R_AIUTA_PLS] == 8);


		AUX_INSER_I			= (R[R_SIM_AUX] == 1);
		PLS_START_CYCLE_I	= (R[R_SIM_START] == 1);
		SEL_AUTO_I			= (R[R_SIM_AUTO] == 2);	    //STRINGA_SIMU = SEL_MANU_I && PLS_START_CYCLE_I;
		SEL_MANU_I			= !SEL_AUTO_I;
		*/

		// Simulo l'ingresso di utensile presente
		TOOL_PRES_SUP_I = TOOL_PRES_INF_I = UT0_ACT;

		tavola_simu();

		battuta_sx1_simu();
		battuta_dx4_simu();

		mandrino_simu();

		// Alta pressione regolata a SX e a DX
		//Simulazione alta pressione zona SX
		if(CONF_MORSA_10 || CONF_MORSA_11 || CONF_MORSA_12 || CONF_MORSA_13 || CONF_MORSA_14 || CONF_MORSA_15 )
		{
			PRESS_MORSE_HP_I = 1;
		}

	    riparo_simu();
		////OUT_MAC_ABIL_I   = ( (FTL_APPO_RIPARO_CH_INP && !CONF_VIS_ALTA) || RIP_ANT_CH_SICUR_I) ;

		rilev_morse_ax_X_simu();

		trasc_ax_X_simu();
		PRESENZA_MORSA_AX_X_I = (DP_OSCILLATORE && INS_RILMOR_AX_X_O) || !INS_RILMOR_AX_X_O || TRASC_MORSE_AX_X_INS_I;

		visiera_bassa_simu();
		visiera_alta_simu();
	}

}
