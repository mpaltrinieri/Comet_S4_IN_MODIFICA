/*
        --------------------------------------------------------------
        TITOLO:         CHECK_POSIZ_MORSE
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Verifica congruita' quote morse
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    check_posiz_morse(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CS4 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           11-06-2021
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Daniele Formuso
        --------------------------------------------------------------

*/

#include        "all.inc"


void check_posiz_morse(void)
{
//****************************************************************************************************************************
//***** VOGLIAMO CONTROLLARE LA POSIZIONE DI OGNI ASSE MORSA RISPETTO ALLA MORSA PRECEDENTE E ALLA SUCCESSIVA
//***** QUALCHE MINIMOTOR HA MANIFESTATO DIFETTOSITA' NELLA BATTERIA TAMPONE, QUINDI NON HA MANTENUTO LA QUOTA ENCODER
//***** DOPO LO SPEGNIMENTO DELLA MACCHINA. CONTROLLIAMO LE POSIZIONI RECIPROCHE DELLE MORSE SU OGNI RIFASSI.CS4 IN AUTOMATICO
//****************************************************************************************************************************

	if(MORSE_MOTORIZZATE && !SIMULATORE_SU_CN && !SIMULATORE_SU_PC)
	{
		if(RESET_MC)
			POSIZ_MORSE_NOT_OK_FAL = 0;
		
		// Facciamo il controllo solo in automatico, se lo facessimo anche in manuale complicheremmo 
		// il lavoro dei collaudatori a macchina appena accesa in cui sicuramente non c'è congruità tra le posizioni morse
		if(Mg_MC(228))
		{
			if(CONF_ASSE_M10)
			{
				if ( CONF_ASSE_M11 && (R[R_POS_ATTUALE_M10] > (R[R_POS_ATTUALE_M11]-(R[R_INTERAX_MORSE_SX]-10))) )
					POSIZ_MORSE_NOT_OK_FAL = 1;
			}

			if(CONF_ASSE_M11)
			{
				if ( CONF_ASSE_M10 && (R[R_POS_ATTUALE_M11] < (R[R_POS_ATTUALE_M10]+(R[R_INTERAX_MORSE_SX]-10))) ||
				     CONF_ASSE_M12 && (R[R_POS_ATTUALE_M11] > (R[R_POS_ATTUALE_M12]-(R[R_INTERAX_MORSE_SX]-10))) )
					POSIZ_MORSE_NOT_OK_FAL = 1;
			}

			if(CONF_ASSE_M12)
			{
				if ( CONF_ASSE_M11 && (R[R_POS_ATTUALE_M12] < (R[R_POS_ATTUALE_M11]+(R[R_INTERAX_MORSE_SX]-10))) ||
				     CONF_ASSE_M13 && (R[R_POS_ATTUALE_M12] > (R[R_POS_ATTUALE_M13]-(R[R_INTERAX_MORSE_SX]-10))) )
					POSIZ_MORSE_NOT_OK_FAL = 1;
			}

			if(CONF_ASSE_M13)
			{
				if ( CONF_ASSE_M12 && (R[R_POS_ATTUALE_M13] < (R[R_POS_ATTUALE_M12]+(R[R_INTERAX_MORSE_SX]-10))) ||
				     CONF_ASSE_M14 && (R[R_POS_ATTUALE_M13] > (R[R_POS_ATTUALE_M14]-(R[R_INTERAX_MORSE_SX]-10))) )
					POSIZ_MORSE_NOT_OK_FAL = 1;
			}

			if(CONF_ASSE_M14)
			{
				if ( CONF_ASSE_M13 && (R[R_POS_ATTUALE_M14] < (R[R_POS_ATTUALE_M13]+(R[R_INTERAX_MORSE_SX]-10))) ||
				     CONF_ASSE_M15 && (R[R_POS_ATTUALE_M14] > (R[R_POS_ATTUALE_M15]-(R[R_INTERAX_MORSE_SX]-10))) )
					POSIZ_MORSE_NOT_OK_FAL = 1;
			}

			if(CONF_ASSE_M15)
			{
				if ( CONF_ASSE_M14 && (R[R_POS_ATTUALE_M15] < (R[R_POS_ATTUALE_M14]+(R[R_INTERAX_MORSE_SX]-10))) )
					POSIZ_MORSE_NOT_OK_FAL = 1;
			}
	
			Mr_MC(228);
		}
		
	}
	else
	{
		Mr_MC(228);
		POSIZ_MORSE_NOT_OK_FAL = 0;
	}
}
