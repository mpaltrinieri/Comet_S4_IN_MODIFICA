/*
        --------------------------------------------------------------
        TITOLO:         RIPARO
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione riparo macchina
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    riparo(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          APPO_RIPARO_AP_INP = riparo anteriore aperto
		                APPO_RIPARO_CH_INP = riparo anteriore chiuso
						CENTRALINA_OK_I = ripari chiusi (disp. di sicurezza)
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:       
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        PHN 2.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           06-03-2001
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Pecchi Andrea
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"


int CH_RIPARO_ANTE, RIPARO_ANTE_CH, RIPARO_ANTE_CH_COUNT, RIPARO_ANTE_CH_MEMCOUNT, RIPARO_ANTE_CH_MEM;
char CH_RIPARO_ANTE_COMMENTO[80] = "{Tempo chiusura riparo anteriore}";
int AP_RIPARO_ANTE, RIPARO_ANTE_AP, RIPARO_ANTE_AP_COUNT, RIPARO_ANTE_AP_MEMCOUNT, RIPARO_ANTE_AP_MEM;
char AP_RIPARO_ANTE_COMMENTO[80] = "{Tempo apertura riparo anteriore}";



void riparo(void)
{

	APP_BORDO_SENSIB_OK = RN_BORDO_SENSIB_OK;		// filtro di BORDO_SENSIB_OK_I  (impulsivo)

	DEBUG_RIP_ANT = COLLAUDO_ON_1;

	
	//***** BORDO SENSIBILE *****
	if(R[R_BORDO_SENSIBILE_PRES]>0.5)
	{
		// Reset allarme bordo sensibile intervenuto
		if( APP_BORDO_SENSIB_OK && (DP_AUXON || RESET_MC) )
		{
			BORDO_SENSIB_PREM_FAL = 0;
		}

		// Reset memoria allarme (possibile aggiunger altre condizioni prima di resettare la memoria che impedisce di chiuder il riparo)
		if(!BORDO_SENSIB_PREM_FAL)
		{
			MEM_BORDO_SENSIB_PREM = 0;
		}

		// BORDO_SENSIB_OK_I impulsivo.
		// se viene premuto il bordo sensibile, il PILZ deve mantener BORDO_SENSIB_OK_I=0 fino a riattivaz ausiliari !!!
		// cmq manteniamo memorizzato l'evento per sicurezza, per mantener disattiva CH_RIP_ANT_O

		// Allarme bordo sensibile intervenuto
		if(!APP_BORDO_SENSIB_OK)
		{
			BORDO_SENSIB_PREM_FAL = 1;
			MEM_BORDO_SENSIB_PREM = 1;
		}

		// Abilitazione apertura automatica riparo anteriore da password in Confmac
		AB_AP_AUT_RIP_ANT = VERSIONE_MAC_RC && ( ( R[R_BORDO_SENSIBILE_PSW]>(PSW_AP_AUT_RIP-0.2) ) && ( R[R_BORDO_SENSIBILE_PSW]<(PSW_AP_AUT_RIP+0.2) ) );

		// Apertura automatica riparo se premuto il bordo sensibile. Fattibile solo in macchine con ripari pneumatici e bordo sensibile che taglia via HW la EV di chiusura riparo.
		AP_RIPARO_DA_BORDO_PREM = (!APP_BORDO_SENSIB_OK || MEM_BORDO_SENSIB_PREM) && MANDRINO_FERMO && !MEM_INVERTER_KO && AB_AP_AUT_RIP_ANT && (RP_PON);

	}
	else
	{
		BORDO_SENSIB_PREM_FAL = 0;
		MEM_BORDO_SENSIB_PREM = 0;
		AP_RIPARO_DA_BORDO_PREM = 0;
	}


	// Non devo consentire l'apertura / chiusura riparo anteriore per ingombro tra mandrino e visiera superiore 
	// in base alla posizione degli assi Y, A  (sia in manuale che in automatico)
	CONS_AP_CH_RIPARI_DA_ASSI = !COLL_RIPARI_Y_A || (R[R_ABIL_AP_CH_RIPARI] < 0.5);


	// Condizioni comuni per apertura riparo anteriore e visiere (non eliminare NO_EMERG_I e non aggiungere AUX_INSER_I)
	CONDIZ_COM_AP_RIP_VIS = (NO_EMERG_I) && (ALIM_PRES_I) && MANDRINO_FERMO && !MEM_INVERTER_KO && (CONS_AP_CH_RIPARI_DA_ASSI || AP_RIPARO_DA_BORDO_PREM);
	
	// Consenso apertura riparo anteriore 
	CON_AP_RIPARO = CONDIZ_COM_AP_RIP_VIS && (APP_RIT_VISIERA_AVA || !CONF_VIS_BASSA);          /*|| DEBUG_RIP_ANT*/
	
	// VISIERA ALTA: Condizione x eseguire il movimento 2 (apertura)
	COND_AP_VIS_ALT = CONDIZ_COM_AP_RIP_VIS;  
	
	// VISIERA BASSA: Condizione x eseguire il movimento 2 (apertura)
	COND_AP_VIS_BAS = CONDIZ_COM_AP_RIP_VIS;                   



	// Condizioni comuni per chiusura riparo anteriore e visiere 
	CONDIZ_COM_CH_RIP_VIS = MACCHINA_PRONTA && CONS_AP_CH_RIPARI_DA_ASSI && !MEM_BORDO_SENSIB_PREM && !AP_RIPARO_DA_BORDO_PREM;

	// Consenso chiusura riparo anteriore 
	CON_CH_RIPARO = CONDIZ_COM_CH_RIP_VIS;

	// VISIERA ALTA: Condizione x eseguire il movimento 1 (chiusura)
	COND_CH_VIS_ALT = CONDIZ_COM_CH_RIP_VIS;                              

	// VISIERA BASSA: Condizione x eseguire il movimento 1 (chiusura)
	COND_CH_VIS_BAS = CONDIZ_COM_CH_RIP_VIS && (APPO_RIPARO_CH_INP || !CONF_RIPARO_ANT);    



	/**** Forzatura Apertura Riparo e Visiere durante Hold ****/
	FORZA_RIPARI_AP = (COMANDO_AUX_A || COMANDO_A) && FUNZ_MAN02 && !CICLO_ON && M_HOLD && AUTO && CONDIZ_COM_AP_RIP_VIS;

	/**** Forzatura Chiusura Riparo e Visiere durante Hold  (chiusura permessa solo dopo apertura) ****/
	FORZA_RIPARI_CH = (COMANDO_AUX_B || COMANDO_B) && FUNZ_MAN02 && !CICLO_ON && M_HOLD && AUTO && CONDIZ_COM_CH_RIP_VIS && (RIPARO_CH_A_FAL || RIPARO_CH_B_FAL);



	if (CONF_RIPARO_ANT)	// RIPARO ANTERIORE PRESENTE
	{
	// Disabilitazione apertura/chiusura automatica riparo
		if(R[R_DISAB_RIPARI_FIERA]>0.5)  //Disabilita apertura riparo in automatico
		{
			Mr_MC(60);
			PLCMr_MC(60);
			Mr_MC(61);
			PLCMr_MC(61);
		}

		//Appoggi funz.M di richiesta ap/ch riparo anteriore
		RICH_AP_RIP_ANT = ( Mg_MC(60) || PLCMg_MC(60) );
		RICH_CH_RIP_ANT = ( Mg_MC(61) || PLCMg_MC(61) );
		
		// Ritardo comando di apertura riparo anteriore SX (per consentire eventuale aspirazione fumi)
		tS(TS_RICH_AP_RIP_ANT, (unsigned char)RICH_AP_RIP_ANT);
		RIT_RICH_AP_RIP_ANT =  (RP_TSuppl[TS_RICH_AP_RIP_ANT]);
		
		//Comandi di ap/ch riparo anteriore SX
		COM_AP_RIP_ANT = RICH_AP_RIP_ANT && !RICH_CH_RIP_ANT && RIT_RICH_AP_RIP_ANT;		// orig: ( Mg_MC(60) || PLCMg_MC(60) )
		COM_CH_RIP_ANT = RICH_CH_RIP_ANT && !RICH_AP_RIP_ANT;								// orig: ( Mg_MC(61) || PLCMg_MC(61) )


		// appoggio ingressi riparo anteriore chiuso/aperto 
		if(!SIMULATORE_SU_CN && !SIMULATORE_SU_CN)
		{
			APPO_RIPARO_CH_INP = (RIP_ANT_CH_SX_I || RIP_ANT_CH_DX_I);
			APPO_RIPARO_AP_INP = (RIP_ANT_AP_SX_I || RIP_ANT_AP_DX_I);
		}
		else
		{
			// In simualzione APPO_RIPARO_CH_INP e APPO_RIPARO_AP_INP vengono scritti in riparo_simu()
		}

		// filtri su appoggio ingressi riparo anteriore chiuso/aperto 
		FTL_APPO_RIPARO_CH_INP = RP_TSuppl[TS_RIPARO_CH] || (FTL_APPO_RIPARO_CH_INP && RN_TSuppl[TS_RIPARO_CH]);
		FTL_APPO_RIPARO_AP_INP = RP_TSuppl[TS_RIPARO_AP] || (FTL_APPO_RIPARO_AP_INP && RN_TSuppl[TS_RIPARO_AP]);	
		

		/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
		if (PON)
        {
        }

		if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
		{
			AP_RIPARO_ANTE = (int) AP_RIP_ANT_O; RIPARO_ANTE_AP = (int) FTL_APPO_RIPARO_AP_INP;
			count (&AP_RIPARO_ANTE, &RIPARO_ANTE_AP, &RIPARO_ANTE_AP_COUNT, &RIPARO_ANTE_AP_MEMCOUNT, &RIPARO_ANTE_AP_MEM, R_AP_RIPARO_ANTE, AP_RIPARO_ANTE_COMMENTO);

			CH_RIPARO_ANTE = (int) CH_RIP_ANT_O; RIPARO_ANTE_CH = (int) FTL_APPO_RIPARO_CH_INP;
			count (&CH_RIPARO_ANTE, &RIPARO_ANTE_CH, &RIPARO_ANTE_CH_COUNT, &RIPARO_ANTE_CH_MEMCOUNT, &RIPARO_ANTE_CH_MEM, R_CH_RIPARO_ANTE, CH_RIPARO_ANTE_COMMENTO);
		}
		
		
		/**** MEMORIA RIPARO ANTERIORE CHIUSO ****/
		if (COM_CH_RIP_ANT && FTL_APPO_RIPARO_CH_INP) 
			MEM_RIPARO_CH = 1;
		if (COM_AP_RIP_ANT || RESET_MC || MANO)
			MEM_RIPARO_CH = 0;


		/*************** RESET ALLARMI RIPARO ANTERIORE ***************/
		if (RESET_ALL || RESET_MC)
        {
			RIPARO_CH_A_FAL = 0;
			RIPARO_CH_B_FAL = 0;
			
			RIPARO_AP_A_FAL = 0;
			RIPARO_AP_B_FAL = 0;
			
			RIPARO_DISFC_FAL = 0;
        }


		/*************** APERTURA RIPARO ANTERIORE *****************/
		
		/* Ausiliario comando apertura riparo anteriore */
		AUX_AP_RIPARO = 
			CON_AP_RIPARO && 
			(
				AP_RIPARO_DA_BORDO_PREM ||
				( AUTO_CICLOMAN && ( COM_AP_RIP_ANT || FORZA_RIPARI_AP ) ) || 
				( MANO && FUNZ_MAN02 && (COMANDO_AUX_A || COMANDO_A) ) ||
				( AP_RIP_ANT_O && FTL_APPO_RIPARO_AP_INP && !AUX_CH_RIPARO )
			);
		
		/* Comando apertura riparo anteriore */
		AP_RIP_ANT_O =  AUX_AP_RIPARO && !AUX_CH_RIPARO && !(CH_RIP_ANT_O);
		AP_RIP_ANT2_O = AUX_AP_RIPARO && !AUX_CH_RIPARO && !(CH_RIP_ANT_O);
		
		/* Time out apertura riparo anteriore */
		if (RP_TSuppl[TS_ALL_RIPARO_AP] && !FTL_APPO_RIPARO_AP_INP && NO_EMERG_I && !DEBUG_RIP_ANT)
		{
			if(!RP_TSuppl[TS_RIPARO_CH])
				RIPARO_AP_A_FAL = 1; // Time Out Riparo anteriore non aperto : controlla il sensore
			if(RP_TSuppl[TS_RIPARO_CH]) 
				RIPARO_AP_B_FAL = 1; // Time Out Riparo anteriore non aperto : controlla la EV
		}
		
		/* Reset funzione ausiliaria "M" */
		if (FTL_APPO_RIPARO_AP_INP)
		{
			Mr_MC(60);
			PLCMr_MC(60);
		}
		
		/*************** CHIUSURA RIPARO ANTERIORE *****************/
		
		/* Ausiliario comando chiusura riparo anteriore */
		AUX_CH_RIPARO = 
			CON_CH_RIPARO && 
			(
				( AUTO_CICLOMAN && ( COM_CH_RIP_ANT || FORZA_RIPARI_CH ) ) || 
				( MANO && FUNZ_MAN02 && (COMANDO_AUX_B || COMANDO_B) ) ||
				( CH_RIP_ANT_O && FTL_APPO_RIPARO_CH_INP && !AUX_AP_RIPARO )
			);
		
		/* Comando chiusura riparo anteriore */
		CH_RIP_ANT_O = AUX_CH_RIPARO && !AUX_AP_RIPARO && !(AP_RIP_ANT_O);
		
		/* Time out chiusura riparo anteriore */
		if ((RP_TSuppl[TS_ALL_RIPARO_CH] || MEM_RIPARO_CH) && !FTL_APPO_RIPARO_CH_INP && AUX_INSER_I && !DEBUG_RIP_ANT)
		{
			if(!RP_TSuppl[TS_RIPARO_AP])
				RIPARO_CH_A_FAL = 1; // Time Out Riparo anteriore non chiuso : controlla il sensore
			if(RP_TSuppl[TS_RIPARO_AP]) 
				RIPARO_CH_B_FAL = 1; // Time Out Riparo anteriore non chiuso : controlla la EV
		}

		
		/* Reset funzione ausiliaria "M" */
		if (FTL_APPO_RIPARO_CH_INP)
		{			
			Mr_MC(61);
			PLCMr_MC(61);
		}
		
		
		/**************** DISFUNZIONE F.C. RIPARO ANTERIORE ****************/
		if (FTL_APPO_RIPARO_CH_INP && FTL_APPO_RIPARO_AP_INP && !COLLAUDO_ON)
			RIPARO_DISFC_FAL = 1;
		
		
		/**************** FUNZIONE ESEGUITA ***************************/
		RIPARO_FUNES_A = (AP_RIP_ANT_O && P_OSCILLATORE || FTL_APPO_RIPARO_AP_INP) && FUNZ_MAN02;
		RIPARO_FUNES_B = (CH_RIP_ANT_O && P_OSCILLATORE || FTL_APPO_RIPARO_CH_INP) && FUNZ_MAN02; 
	
	}
	else
	{
		FTL_APPO_RIPARO_CH_INP = 1;
		FTL_APPO_RIPARO_AP_INP = 1;

		RIPARO_CH_A_FAL = 0;
		RIPARO_CH_B_FAL = 0;	
		RIPARO_AP_A_FAL = 0;
		RIPARO_AP_B_FAL = 0;
		RIPARO_DISFC_FAL = 0;
		
		Mr_MC(60);
		PLCMr_MC(60);
		Mr_MC(61);
		PLCMr_MC(61);

		RIPARO_FUNES_B = 0;
		RIPARO_FUNES_A = 0;
	}

}
