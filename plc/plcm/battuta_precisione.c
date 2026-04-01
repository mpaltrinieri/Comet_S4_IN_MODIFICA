/*
        --------------------------------------------------------------
        TITOLO:         battuta_precisione
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Battuta di precisione
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    battuta_precisione(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------


*/
#include "all.inc"


void battuta_precisione(void)
{
    if (!R[R_BATT_PRECISIONE]) {
            R[R_BATT_PREC_DIS]   = 1; // Battuta disinserita
            INS_BATT_PREC_FAL    = 0;
            DIS_BATT_PREC_FAL    = 0;
            BATTUTA_PREC_FUNES_A = 0;
            BATTUTA_PREC_FUNES_B = 0;
            Mr_MC(26)               ;
            Mr_MC(27)               ;

	        BATT_PREC_QUOTA0_FAL = 0;
	        INDICE_TAST_FAL      = 0;
	        PEZZO_NON_TROV_FAL   = 0;
	        POSIZIONE_PEZZO_FAL  = 0;

			TASTATURA_ATTIVA = 0;
            Mr_MC(24);
            Mr_MC(25);

            return;
    }

    /**** RESET ALLARMI ****/
    if (RESET_ALL || RESET_MC) {
        INS_BATT_PREC_FAL    = 0;
        DIS_BATT_PREC_FAL    = 0;
        BATT_PREC_QUOTA0_FAL = 0;
    }

    if (RESET_MC) {
		INDICE_TAST_FAL     = 0;
		PEZZO_NON_TROV_FAL  = 0;
		POSIZIONE_PEZZO_FAL = 0;

        TASTATURA_ATTIVA    = 0;
	}


	/**** Analisi presenza FC battuta di precisione in misura ****/
	if (R[R_FC_BATT_IN_MIS] > 0.5)
		FC_BATT_IN_MIS = 1;
	else
		FC_BATT_IN_MIS = 0;

    /************** Allarmi dispositivo ********************************************/
    P_ALL_BATT_PREC_NO_INS = APP_INPUT_ARIA_PRES && INS_BATT_PREC_O && (!FC_BATT_IN_MIS && BATT_PREC_RIP_I || FC_BATT_IN_MIS && !BATT_PREC_MIS_I);
    INS_BATT_PREC_FAL = INS_BATT_PREC_FAL || RP_ALL_BATT_PREC_NO_INS;

    P_ALL_BATT_PREC_NO_DIS = APP_INPUT_ARIA_PRES && DIS_BATT_PREC_O && !BATT_PREC_RIP_I;
    DIS_BATT_PREC_FAL = DIS_BATT_PREC_FAL || RP_ALL_BATT_PREC_NO_DIS;

    /**** Reset Funzioni M ****/
    P_BATT_PREC_INS = (!FC_BATT_IN_MIS && !BATT_PREC_RIP_I || FC_BATT_IN_MIS && BATT_PREC_MIS_I);
    if (RP_BATT_PREC_INS && AUT_BATTUTA_PREC_INS || !AUTO_CICLOMAN)
        Mr_MC(26);
    if (BATT_PREC_RIP_I && AUT_BATTUTA_PREC_DIS || !AUTO_CICLOMAN)
        Mr_MC(27);

    /******** Condizioni automatiche e manuali *********/
    MAN_BATTUTA_PREC_INS = MANO && FUNZ_MAN16 && COMANDO_B;
    MAN_BATTUTA_PREC_DIS = MANO && FUNZ_MAN16 && COMANDO_A;

    AUT_BATTUTA_PREC_INS = (Mg_MC(26) || AUT_BATTUTA_PREC_INS) && AUTO_CICLOMAN && !RESET_MC && !Mg_MC(27);
    AUT_BATTUTA_PREC_DIS = (Mg_MC(27) || AUT_BATTUTA_PREC_DIS) && AUTO_CICLOMAN && !RESET_MC && !Mg_MC(26);

    HOLD_BATTUTA_PREC = INS_BATT_PREC_FAL || DIS_BATT_PREC_FAL;


    /************** Uscite **************/
    // Consensi
    CON_BATTUTA_PREC_INS = ALIM_PRES_I && NO_EMERG_I && AUX_INSER_I;
    CON_BATTUTA_PREC_DIS = ALIM_PRES_I && NO_EMERG_I && AUX_INSER_I;

    // Aux delle out in tutte le condizioni
    AUX_BATTUTA_PREC_INS = (MAN_BATTUTA_PREC_INS || AUT_BATTUTA_PREC_INS) 
                        && CON_BATTUTA_PREC_INS && !AUX_BATTUTA_PREC_DIS;

    AUX_BATTUTA_PREC_DIS = (MAN_BATTUTA_PREC_DIS || AUT_BATTUTA_PREC_DIS) 
                        && CON_BATTUTA_PREC_DIS && !AUX_BATTUTA_PREC_INS;

    // Nel passaggio Auto-->Man l'uscita resta a 1; l'uscita rimane a 1 anche se cade l'ingresso
    INS_BATT_PREC_O = AUX_BATTUTA_PREC_INS || (INS_BATT_PREC_O && !AUX_BATTUTA_PREC_DIS);
    DIS_BATT_PREC_O = AUX_BATTUTA_PREC_DIS || (DIS_BATT_PREC_O && !AUX_BATTUTA_PREC_INS);


    /**************** Funzione eseguita ***************************/
    BATTUTA_PREC_FUNES_B = FUNZ_MAN16 && (RP_BATT_PREC_INS || P_OSCILLATORE && INS_BATT_PREC_O);
    BATTUTA_PREC_FUNES_A = FUNZ_MAN16 && (BATT_PREC_RIP_I || P_OSCILLATORE && DIS_BATT_PREC_O);



    /**************** Ciclica ***************************/
    I_LSR_CH0(AX_U_CH0) = 1; // libera servo (l'errore di inseguimento diventa tutto variazione di quota)

    // Appoggio stato inserzione
    R[R_BATT_PREC_DIS] = (float)BATT_PREC_RIP_I;

    // Lettura quota banda magnetica
    { STASSI bandaBattuta;
        lquote(QREALE, &bandaBattuta, (1L << (AX_U_CH0)));
	    R[R_POS_BATT_PREC] = -(bandaBattuta.quota[AX_U_CH0] - R[R_ZERO_BATT_PREC]);
    }

    // Attivazione tastatura
    TASTATURA_ATTIVA = Mg_MC(24) || TASTATURA_ATTIVA && !Mg_MC(25);
    Mr_MC(24); Mr_MC(25);

	// Verifica se battuta premuta
	BATTUTA_PREC_PREMUTA = (ABS(R[R_POS_BATT_PREC]) > R[R_TOLL_BATT_PREC]);
    R[R_BATT_PREC_PREMUTA] = (BATTUTA_PREC_PREMUTA) ? (1.0f) : (0.0f);

    // Interruzione programma da PLC
	if(!Mg_MC(118))   //se non è attiva la tastatura con il renishaw
		VERFALS_CH0 = AUTO && TASTATURA_ATTIVA && BATTUTA_PREC_PREMUTA;

    // Allarmi emessi dalla ciclica con G318
    if (BATT_PREC_QUOTA0_FAL)
        allarm(BATT_PREC_QUOTA0_AL); // Errore posizione a riposo della battuta di precisione

    if (INDICE_TAST_FAL)
        allarm(INDICE_TAST_AL); // Errore indice tastatura

    if (POSIZIONE_PEZZO_FAL)
        allarm(POSIZIONE_PEZZO_AL); // Pezzo posizionato male 

    if (PEZZO_NON_TROV_FAL)
        allarm(PEZZO_NON_TROV_AL); // Pezzo non trovato
}
