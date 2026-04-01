/*
        --------------------------------------------------------------
        TITOLO:         Checkmor
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione verifica posizione morse
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    check_morse_trasc_x(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:     
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:    
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 3.200
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           04-12-2002
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

void    check_morse_trasc_x(void)

{


// Se ci sono le morse motorizzate tutti i conti li faccio nell'altra SR
// Se anche il trascinatore X non è presente non cambia nulla
if (CONF_POS_MORSE && !MORSE_MOTORIZZATE)

{

/**** INIZIALIZZAZIONE TEMPORIZZATORI e Caricamento posizione morse da memoria permanente ****/
if (PON)
        {
		// Ovvio alla prima accensione che vengano caricati tutti 0 : sono valori possibili
		if ( (POSMORS_10 == 0) && CONF_ZIMMER_MORSA_10) POSMORS_10 = 32000;
		if ( (POSMORS_11 == 0) && CONF_ZIMMER_MORSA_11) POSMORS_11 = 32000;
		if ( (POSMORS_12 == 0) && CONF_ZIMMER_MORSA_12) POSMORS_12 = 32000;
		if ( (POSMORS_13 == 0) && CONF_ZIMMER_MORSA_13) POSMORS_13 = 32000;
		if ( (POSMORS_14 == 0) && CONF_ZIMMER_MORSA_14) POSMORS_14 = 32000;
		if ( (POSMORS_15 == 0) && CONF_ZIMMER_MORSA_15) POSMORS_15 = 32000;

		
        R[R_POS_ATTUALE_M10] = POSMORS_10;
        R[R_POS_ATTUALE_M11] = POSMORS_11;
        R[R_POS_ATTUALE_M12] = POSMORS_12;
        R[R_POS_ATTUALE_M13] = POSMORS_13;
        R[R_POS_ATTUALE_M14] = POSMORS_14;
        R[R_POS_ATTUALE_M15] = POSMORS_15;
		}


/**** RESET ALLARMI ****/
if (RESET_MC)
        {
        MORSA_MICRO_X_PERSO_FAL		= 0;
        MORSA_MICRO_X_NON_TROVATO_FAL = 0;

        R[R_POS_MORSA] =   0;

        MORSA_10_NONPOS_FAL = 0;
        MORSA_11_NONPOS_FAL = 0;
        MORSA_12_NONPOS_FAL = 0;

        MORSA_13_NONPOS_FAL	= 0;
        MORSA_14_NONPOS_FAL	= 0;
        MORSA_15_NONPOS_FAL	= 0;

		Mr_MC(110);
        Mr_MC(111);

		}

/**** SALVATAGGIO POSIZIONE MORSE ****/
POSMORS_10 = (float)R[R_POS_ATTUALE_M10];
POSMORS_11 = (float)R[R_POS_ATTUALE_M11];
POSMORS_12 = (float)R[R_POS_ATTUALE_M12];
POSMORS_13 = (float)R[R_POS_ATTUALE_M13];
POSMORS_14 = (float)R[R_POS_ATTUALE_M14];
POSMORS_15 = (float)R[R_POS_ATTUALE_M15];


/* Verifica posizionamento reale morse rispetto a quello richiesto dal DRILL */

MORSA_10_IN_POSIZIONE =	((R[R_POSMORS4_PC] > (R[R_POS_ATTUALE_M10]-R[R_TOLL_MORSE])) && 
						 (R[R_POSMORS4_PC] < (R[R_POS_ATTUALE_M10]+R[R_TOLL_MORSE]))) ||
						!CONF_MORSA_10;

MORSA_11_IN_POSIZIONE =	((R[R_POSMORS5_PC] > (R[R_POS_ATTUALE_M11]-R[R_TOLL_MORSE])) && 
						 (R[R_POSMORS5_PC] < (R[R_POS_ATTUALE_M11]+R[R_TOLL_MORSE]))) ||
						!CONF_MORSA_11;

MORSA_12_IN_POSIZIONE =	((R[R_POSMORS6_PC] > (R[R_POS_ATTUALE_M12]-R[R_TOLL_MORSE])) && 
						 (R[R_POSMORS6_PC] < (R[R_POS_ATTUALE_M12]+R[R_TOLL_MORSE]))) ||
						!CONF_MORSA_12;

MORSA_13_IN_POSIZIONE =	((R[R_POSMORS7_PC] > (R[R_POS_ATTUALE_M13]-R[R_TOLL_MORSE])) && 
						 (R[R_POSMORS7_PC] < (R[R_POS_ATTUALE_M13]+R[R_TOLL_MORSE]))) ||
						!CONF_MORSA_13;

MORSA_14_IN_POSIZIONE =	((R[R_POSMORS8_PC] > (R[R_POS_ATTUALE_M14]-R[R_TOLL_MORSE])) && 
						 (R[R_POSMORS8_PC] < (R[R_POS_ATTUALE_M14]+R[R_TOLL_MORSE]))) ||
						!CONF_MORSA_14;

MORSA_15_IN_POSIZIONE =	((R[R_POSMORS9_PC] > (R[R_POS_ATTUALE_M15]-R[R_TOLL_MORSE])) && 
						 (R[R_POSMORS9_PC] < (R[R_POS_ATTUALE_M15]+R[R_TOLL_MORSE]))) ||
						!CONF_MORSA_15;



/**** RESET DI M110 ****/
if (Mg_MC(111))
        {
        Mr_MC(110);
        Mr_MC(111);
        }



/**** Reset di M112 : ciclo di posizionamento con trascinatore in corso ****/
if (Mg_MC(113) || !AUTO || RESET_MC)
		{
		Mr_MC(112);
		Mr_MC(113);
		}


/**** Allarme micro morsa non trovato ****/
if (AUTO_CICLOMAN && Mg_MC(112) && RP_TRASC_INSERITO_X && RP_MICRO_MORSA_ASSENTE_X)
			MORSA_MICRO_X_PERSO_FAL = 1;


/**** VERIFICA ERRORE DI POSIZIONAMENTO MORSA ****/
	if (Mg_MC(110) && (R[R_POS_MORSA] != 0))
        {
		
		POS_CORRETTA =	(R[R_ERR_POS_MORSA] < R[R_DELTAPOS_MORSE]) && 
						(R[R_ERR_POS_MORSA] > -R[R_DELTAPOS_MORSE]);

		// Posizione Corretta : resetta il valore e riprendi
		if (POS_CORRETTA)	R[R_POS_MORSA] =   0;
            
		// Posizione NON corretta : identifica l'allarme sulla morsa

		if ((R[R_MORSA_CONTROLLATA]==4) && !POS_CORRETTA) MORSA_10_NONPOS_FAL = 1;
		if ((R[R_MORSA_CONTROLLATA]==5) && !POS_CORRETTA) MORSA_11_NONPOS_FAL = 1;
		if ((R[R_MORSA_CONTROLLATA]==6) && !POS_CORRETTA) MORSA_12_NONPOS_FAL = 1;

		if ((R[R_MORSA_CONTROLLATA]==7) && !POS_CORRETTA) MORSA_13_NONPOS_FAL = 1;
		if ((R[R_MORSA_CONTROLLATA]==8) && !POS_CORRETTA) MORSA_14_NONPOS_FAL = 1;
		if ((R[R_MORSA_CONTROLLATA]==9) && !POS_CORRETTA) MORSA_15_NONPOS_FAL = 1;

        }


/* Allarme sulla morsa : memorizza l'errore con il 32000 per il ciclo dopo */
if (MORSA_10_NONPOS_FAL)	R[R_POS_ATTUALE_M10] = (float)32000;
if (MORSA_11_NONPOS_FAL)	R[R_POS_ATTUALE_M11] = (float)32000;
if (MORSA_12_NONPOS_FAL)	R[R_POS_ATTUALE_M12] = (float)32000;

if (MORSA_13_NONPOS_FAL)	R[R_POS_ATTUALE_M13] = (float)32000;
if (MORSA_14_NONPOS_FAL)	R[R_POS_ATTUALE_M14] = (float)32000;
if (MORSA_15_NONPOS_FAL)	R[R_POS_ATTUALE_M15] = (float)32000;
        

/* Cnc in allarme durante controllo morse : probabile allarme di micro non trovato */
if (Mg_MC(110) && (CNC_FAL || CNC1_FAL || CNC2_FAL) && !PRESENZA_MORSA_AX_X_I)
        MORSA_MICRO_X_NON_TROVATO_FAL = 1;


/* Memorizzazione dell'allarme per il ciclo successivo */
if (MORSA_MICRO_X_NON_TROVATO_FAL || MORSA_MICRO_X_PERSO_FAL)
        {
        if (R[R_MORSA_CONTROLLATA]==4)  R[R_POS_ATTUALE_M10] = (float)32000;
        if (R[R_MORSA_CONTROLLATA]==5)  R[R_POS_ATTUALE_M11] = (float)32000;
        if (R[R_MORSA_CONTROLLATA]==6)  R[R_POS_ATTUALE_M12] = (float)32000;
		
		if (R[R_MORSA_CONTROLLATA]==7)	R[R_POS_ATTUALE_M13] = (float)32000;
        if (R[R_MORSA_CONTROLLATA]==8)  R[R_POS_ATTUALE_M14] = (float)32000;
		if (R[R_MORSA_CONTROLLATA]==9)  R[R_POS_ATTUALE_M15] = (float)32000;
		}


}		
		
else
        {
		MORSA_10_NONPOS_FAL = 0;
		MORSA_11_NONPOS_FAL = 0;
		MORSA_12_NONPOS_FAL = 0;
		MORSA_13_NONPOS_FAL = 0;
        MORSA_14_NONPOS_FAL = 0;
        MORSA_15_NONPOS_FAL = 0;

		MORSA_MICRO_X_PERSO_FAL	= 0;
		
		Mr_MC(110);
		Mr_MC(111);
		}


}

