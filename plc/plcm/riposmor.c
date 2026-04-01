/*
        --------------------------------------------------------------
        TITOLO:         Riposmor.c
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Controllo Calcoli Riposizionamento Morse
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void	riposmor (void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:		CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:			05-10-2007
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/




#include        "all.inc"

void    riposmor (void)

{


/************ Calcoli semplificati sia in multipezzo che in pendolare ***********/

/************ Sempre abilitato con le morse automatiche *********/
if (MORSE_MOTORIZZATE)

{

/******* RESET ALLARMI ********/
if (RESET_MC)
		{
		Mr_MC(200);
		}

// Copia delle variabili di riposizionamento morse motorizzate dopo tagli di separazione dal CH0 ai CH2:
Aris_CH2[R_FINE_RIPOS_MORSE_MOT_PEND] = R[R_FINE_RIPOS_MORSE_MOT_PEND];

Aris_CH2[R_NUM_MORSA_MOT_IN_RIP] = R[R_NUM_MORSA_MOT_IN_RIP];

// Sequenza di calcolo dei movimenti
if (Mg_MC(200))
{

// Controllo se le morse sono a SX1 e si muovono o sono già in posizione
MORSA_10_SX1_INPOS	= CONF_ASSE_M10	&& MORSA10_A_SX1 && MORSA_10_IN_POSIZIONE;
MORSA_11_SX1_INPOS	= CONF_ASSE_M11	&& MORSA11_A_SX1 && MORSA_11_IN_POSIZIONE;
MORSA_12_SX1_INPOS	= CONF_ASSE_M12	&& MORSA12_A_SX1 && MORSA_12_IN_POSIZIONE;
MORSA_13_SX1_INPOS	= CONF_ASSE_M13	&& MORSA13_A_SX1 && MORSA_13_IN_POSIZIONE;
MORSA_14_SX1_INPOS	= CONF_ASSE_M14	&& MORSA14_A_SX1 && MORSA_14_IN_POSIZIONE;
MORSA_15_SX1_INPOS	= CONF_ASSE_M15	&& MORSA15_A_SX1 && MORSA_15_IN_POSIZIONE;

////// Controllo se le morse sono a SX2 e si muovono o sono già in posizione
////MORSA_10_SX2_INPOS	= CONF_ASSE_M10	&& MORSA10_A_SX2 && MORSA_10_IN_POSIZIONE;
////MORSA_11_SX2_INPOS	= CONF_ASSE_M11	&& MORSA11_A_SX2 && MORSA_11_IN_POSIZIONE;
////MORSA_12_SX2_INPOS	= CONF_ASSE_M12	&& MORSA12_A_SX2 && MORSA_12_IN_POSIZIONE;
////MORSA_13_SX2_INPOS	= CONF_ASSE_M13	&& MORSA13_A_SX2 && MORSA_13_IN_POSIZIONE;
////MORSA_14_SX2_INPOS	= CONF_ASSE_M14	&& MORSA14_A_SX2 && MORSA_14_IN_POSIZIONE;
////MORSA_15_SX2_INPOS	= CONF_ASSE_M15	&& MORSA15_A_SX2 && MORSA_15_IN_POSIZIONE;
////
////// Controllo se le morse sono a DX3 e si muovono o sono già in posizione
////MORSA_10_DX3_INPOS	= CONF_ASSE_M10	&& MORSA10_A_DX3 && MORSA_10_IN_POSIZIONE;
////MORSA_11_DX3_INPOS	= CONF_ASSE_M11	&& MORSA11_A_DX3 && MORSA_11_IN_POSIZIONE;
////MORSA_12_DX3_INPOS	= CONF_ASSE_M12	&& MORSA12_A_DX3 && MORSA_12_IN_POSIZIONE;
////MORSA_13_DX3_INPOS	= CONF_ASSE_M13	&& MORSA13_A_DX3 && MORSA_13_IN_POSIZIONE;
////MORSA_14_DX3_INPOS	= CONF_ASSE_M14	&& MORSA14_A_DX3 && MORSA_14_IN_POSIZIONE;
////MORSA_15_DX3_INPOS	= CONF_ASSE_M15	&& MORSA15_A_DX3 && MORSA_15_IN_POSIZIONE;

// Controllo se le morse sono a DX4 e si muovono o sono già in posizione
MORSA_10_DX4_INPOS	= CONF_ASSE_M10	&& MORSA10_A_DX4 && MORSA_10_IN_POSIZIONE;
MORSA_11_DX4_INPOS	= CONF_ASSE_M11	&& MORSA11_A_DX4 && MORSA_11_IN_POSIZIONE;
MORSA_12_DX4_INPOS	= CONF_ASSE_M12	&& MORSA12_A_DX4 && MORSA_12_IN_POSIZIONE;
MORSA_13_DX4_INPOS	= CONF_ASSE_M13	&& MORSA13_A_DX4 && MORSA_13_IN_POSIZIONE;
MORSA_14_DX4_INPOS	= CONF_ASSE_M14	&& MORSA14_A_DX4 && MORSA_14_IN_POSIZIONE;
MORSA_15_DX4_INPOS	= CONF_ASSE_M15	&& MORSA15_A_DX4 && MORSA_15_IN_POSIZIONE;

BATTUTA_SX1_USATA = CONF_BATTUTA_SX1 && (APP_GRUPPO_MORSE_SX1>0);
BATTUTA_DX4_USATA = CONF_BATTUTA_DX4 && (APP_GRUPPO_MORSE_DX4>0);

// Azzero le variabili che tengono in memoria le morse aperte/chiuse nei giri
MORSE_MUOVI_GIRO_1_DA_SX1 = 0;
MORSE_MUOVI_GIRO_2_DA_SX1 = 0;
MORSE_MUOVI_GIRO_1_DA_SX2 = 0;
MORSE_MUOVI_GIRO_2_DA_SX2 = 0;
MORSE_MUOVI_GIRO_1_DA_DX3 = 0;
MORSE_MUOVI_GIRO_2_DA_DX3 = 0;
MORSE_MUOVI_GIRO_1_DA_DX4 = 0;
MORSE_MUOVI_GIRO_2_DA_DX4 = 0;


// Reset variabili morse associate alle battute (flag delle morse non assegnate che comunque associamo alle battute):
MORSE_07_18_ASS_SX1 = 0;
MORSE_07_18_ASS_SX2 = 0;
MORSE_07_18_ASS_DX3 = 0;
MORSE_07_18_ASS_DX4 = 0;

// Calcoli battute di appartenza fatte nella gestione morse (es:MORSA7_A_SX1,MORSA13_A_DX3,etc...)

// Gestione Morse non associate SX

		MORSA10_NON_ASSOCIATA = (!MORSA10_A_SX1 && !MORSA10_A_DX4);
		MORSA11_NON_ASSOCIATA = (!MORSA11_A_SX1 && !MORSA11_A_DX4);
		MORSA12_NON_ASSOCIATA = (!MORSA12_A_SX1 && !MORSA12_A_DX4);

		// Abilitazione Movimento morse non associate a nessuna barriera
			if (MORSA10_NON_ASSOCIATA && CONF_ASSE_M10)	
			{
			if (APP_GRUPPO_MORSE_SX1) MORSA10_ASS_SX1=1;		
			else if (APP_GRUPPO_MORSE_DX4) MORSA10_ASS_DX4=1;
			}
			if (MORSA11_NON_ASSOCIATA && CONF_ASSE_M11)	
			{
			if (APP_GRUPPO_MORSE_SX1) MORSA11_ASS_SX1=1;
			else if (APP_GRUPPO_MORSE_DX4) MORSA11_ASS_DX4=1;
			}
			if (MORSA12_NON_ASSOCIATA && CONF_ASSE_M12)	
			{
			if (APP_GRUPPO_MORSE_SX1) MORSA12_ASS_SX1=1;
			else if (APP_GRUPPO_MORSE_DX4) MORSA12_ASS_DX4=1;
			}

// Gestione Morse non associate DX

		MORSA13_NON_ASSOCIATA = (!MORSA13_A_SX1 && !MORSA13_A_DX4 );
		MORSA14_NON_ASSOCIATA = (!MORSA14_A_SX1 && !MORSA14_A_DX4 );
		MORSA15_NON_ASSOCIATA = (!MORSA15_A_SX1 && !MORSA15_A_DX4 );

		// Abilitazione Movimento morse non associate a nessuna barriera
			if (MORSA13_NON_ASSOCIATA && CONF_ASSE_M13)
			{
			if (APP_GRUPPO_MORSE_DX4) MORSA13_ASS_DX4=1;
			else if (APP_GRUPPO_MORSE_SX1) MORSA13_ASS_SX1=1;
			}
			if (MORSA14_NON_ASSOCIATA && CONF_ASSE_M14)	
			{
			if (APP_GRUPPO_MORSE_DX4) MORSA14_ASS_DX4=1;
			else if (APP_GRUPPO_MORSE_SX1) MORSA14_ASS_SX1=1;
			}
			if (MORSA15_NON_ASSOCIATA && CONF_ASSE_M15)	
			{
			if (APP_GRUPPO_MORSE_DX4) MORSA15_ASS_DX4=1;
			else if (APP_GRUPPO_MORSE_SX1) MORSA15_ASS_SX1=1;
			}


// --------------------------------------------------------------------------------------
// ------------------------------- Controlli ZONA SX1 -----------------------------------
// --------------------------------------------------------------------------------------
// La battuta SX1 è usata, vediamo come muovere le morse nel suo gruppo
if (BATTUTA_SX1_USATA && Mg_MC(200) )
	{
	// Appoggio per semplicità di lettura su un bit il cumulativo della Word
	ALMENO_UNA_MORSA_FERMA_SX1 = (MORSE_FERME_SX1_INPOS > 0);
				
	// Condizione migliore : una morsa resta ferma
	if (ALMENO_UNA_MORSA_FERMA_SX1)
		{
		// Verifico le morse presenti, assegnate alla battuta e che SI MUOVONO
		if ((MORSA10_A_SX1 || MORSA10_ASS_SX1) && !MORSA_10_IN_POSIZIONE) MORSA10_MUOVI_SX1_GIRO_1 = 1;
		if ((MORSA11_A_SX1 || MORSA11_ASS_SX1) && !MORSA_11_IN_POSIZIONE) MORSA11_MUOVI_SX1_GIRO_1 = 1;
		if ((MORSA12_A_SX1 || MORSA12_ASS_SX1) && !MORSA_12_IN_POSIZIONE) MORSA12_MUOVI_SX1_GIRO_1 = 1;
		if ((MORSA13_A_SX1 || MORSA13_ASS_SX1) && !MORSA_13_IN_POSIZIONE) MORSA13_MUOVI_SX1_GIRO_1 = 1;
		if ((MORSA14_A_SX1 || MORSA14_ASS_SX1) && !MORSA_14_IN_POSIZIONE) MORSA14_MUOVI_SX1_GIRO_1 = 1;
		if ((MORSA15_A_SX1 || MORSA15_ASS_SX1) && !MORSA_15_IN_POSIZIONE) MORSA15_MUOVI_SX1_GIRO_1 = 1;
			
		// Se almeno una morsa è ferma, c'è solo un giro
		MORSE_MUOVI_GIRO_2_DA_SX1 = 0;

		}

	else // Condizione peggiore : nessuna morsa resta ferma

		{
		// Controllo dove va la prima morsa (SX/DX)
		// ATTENZIONE : ALMENO UNA FRA LE MORSE 10-11 è sempre presente

		// Prima Morsa esistente (morsa_10) va a SX : si muove per prima
		if (MORSA10_A_SX1 && (R[R_POSMORS4_PC] < (R[R_POS_ATTUALE_M10]-R[R_TOLL_MORSE]))) 
			{
			if (MORSA10_A_SX1                   ) MORSA10_MUOVI_SX1_GIRO_1 = 1;
			if (MORSA11_A_SX1 || MORSA11_ASS_SX1) MORSA11_MUOVI_SX1_GIRO_2 = 1;
			}
		// Prima Morsa esistente (morsa_10) va a DX : si muove per ultima
		if (MORSA10_A_SX1 && (R[R_POSMORS4_PC] > (R[R_POS_ATTUALE_M10]+R[R_TOLL_MORSE]))) 
			{
			if (MORSA10_A_SX1                   ) MORSA10_MUOVI_SX1_GIRO_2 = 1;
			if (MORSA11_A_SX1 || MORSA11_ASS_SX1) MORSA11_MUOVI_SX1_GIRO_1 = 1;
			}	

		// Prima Morsa esistente (morsa_11) va a SX : si muove per prima
		if (!MORSA10_A_SX1 && MORSA11_A_SX1 && (R[R_POSMORS5_PC] < (R[R_POS_ATTUALE_M11]-R[R_TOLL_MORSE]))) 
			{
			if (MORSA11_A_SX1) MORSA11_MUOVI_SX1_GIRO_1 = 1;
			}
		// Prima Morsa esistente (morsa_11) va a DX : si muove per ultima
		if (!MORSA10_A_SX1 && MORSA11_A_SX1 && (R[R_POSMORS5_PC] > (R[R_POS_ATTUALE_M11]+R[R_TOLL_MORSE]))) 
			{
			if (MORSA11_A_SX1) MORSA11_MUOVI_SX1_GIRO_2 = 1;
			}

		// La prima morsa va a SX e si APRE subito, quindi le altre, se presenti si APRONO al 2°giro
		if (MORSA10_MUOVI_SX1_GIRO_1 || (MORSA11_MUOVI_SX1_GIRO_1 && !MORSA10_A_SX1))
			{
			// Le morse 10-11 sono assegnate prima dato che possono sempre essere quelle di testa
			if (MORSA12_A_SX1 || MORSA12_ASS_SX1)	MORSA12_MUOVI_SX1_GIRO_2 = 1;
			if (MORSA13_A_SX1 || MORSA13_ASS_SX1)	MORSA13_MUOVI_SX1_GIRO_2 = 1;
			if (MORSA14_A_SX1 || MORSA14_ASS_SX1)	MORSA14_MUOVI_SX1_GIRO_2 = 1;
			if (MORSA15_A_SX1 || MORSA15_ASS_SX1)	MORSA15_MUOVI_SX1_GIRO_2 = 1;
			}

		// La prima morsa va a DX e si APRE dopo, quindi le altre, se presenti si chiudono nel  2°giro
		if (MORSA10_MUOVI_SX1_GIRO_2 || (MORSA11_MUOVI_SX1_GIRO_2 && !MORSA10_A_SX1))
			{
			// Le morse 10-11 sono assegnate prima dato che possono sempre essere quelle di testa
			if (MORSA12_A_SX1 || MORSA12_ASS_SX1)	MORSA12_MUOVI_SX1_GIRO_1 = 1;
			if (MORSA13_A_SX1 || MORSA13_ASS_SX1 )	MORSA13_MUOVI_SX1_GIRO_1 = 1;
			if (MORSA14_A_SX1 || MORSA14_ASS_SX1 )	MORSA14_MUOVI_SX1_GIRO_1 = 1;
			if (MORSA15_A_SX1 || MORSA15_ASS_SX1 )	MORSA15_MUOVI_SX1_GIRO_1 = 1;
			}


		} // Fine condizione peggiore : nessuna morsa resta ferma

	}	// Fine Sequenza BATTUTA_SX1_USATA


// --------------------------------------------------------------------------------------
// ------------------------------- Controlli ZONA DX4 -----------------------------------
// --------------------------------------------------------------------------------------
// La battuta DX4 è usata, vediamo come muovere le morse nel suo gruppo
if (BATTUTA_DX4_USATA && Mg_MC(200))
	{
	// Appoggio per semplicità di lettura su un bit il cumulativo della Word
	ALMENO_UNA_MORSA_FERMA_DX4 = (MORSE_FERME_DX4_INPOS > 0);
				
	// Condizione migliore : una morsa resta ferma
	if (ALMENO_UNA_MORSA_FERMA_DX4)
		{
		// Verifico le morse presenti, assegnate alla battuta e che che SI MUOVONO
		if ((MORSA10_A_DX4 || MORSA10_ASS_DX4) && !MORSA_10_IN_POSIZIONE) MORSA10_MUOVI_DX4_GIRO_1 = 1;
		if ((MORSA11_A_DX4 || MORSA11_ASS_DX4) && !MORSA_11_IN_POSIZIONE) MORSA11_MUOVI_DX4_GIRO_1 = 1;
		if ((MORSA12_A_DX4 || MORSA12_ASS_DX4) && !MORSA_12_IN_POSIZIONE) MORSA12_MUOVI_DX4_GIRO_1 = 1;
		if ((MORSA13_A_DX4 || MORSA13_ASS_DX4) && !MORSA_13_IN_POSIZIONE) MORSA13_MUOVI_DX4_GIRO_1 = 1;
		if ((MORSA14_A_DX4 || MORSA14_ASS_DX4) && !MORSA_14_IN_POSIZIONE) MORSA14_MUOVI_DX4_GIRO_1 = 1;
		if ((MORSA15_A_DX4 || MORSA15_ASS_DX4) && !MORSA_15_IN_POSIZIONE) MORSA15_MUOVI_DX4_GIRO_1 = 1;
			
		// Se almeno una morsa è ferma, c'è solo un giro
		MORSE_MUOVI_GIRO_2_DA_DX4 = 0;

		}

	else // Condizione peggiore : nessuna morsa resta ferma

		{
		// Controllo dove va l' ultima morsa (SX/DX)
		// ATTENZIONE : ALMENO UNA FRA LE MORSE 15-14 è sempre presente

		// Ultima Morsa esistente va a DX : si muove per prima
		if (MORSA15_A_DX4 && (R[R_POSMORS9_PC] > (R[R_POS_ATTUALE_M15]+R[R_TOLL_MORSE]))) 
			{
			if (MORSA14_A_DX4                   ) MORSA14_MUOVI_DX4_GIRO_2 = 1;
			if (MORSA15_A_DX4 || MORSA15_ASS_DX4) MORSA15_MUOVI_DX4_GIRO_1 = 1;
			}
		// Ultima Morsa esistente va a SX : si muove per ultima
		if (MORSA15_A_DX4 && (R[R_POSMORS9_PC] < (R[R_POS_ATTUALE_M15]-R[R_TOLL_MORSE]))) 
			{
			if (MORSA15_A_DX4                   ) MORSA15_MUOVI_DX4_GIRO_2 = 1;
			if (MORSA14_A_DX4 || MORSA14_ASS_DX4) MORSA14_MUOVI_DX4_GIRO_1 = 1;
			}

		// Ultima Morsa esistente va a DX : si muove per prima
		if (!MORSA15_A_DX4 && MORSA14_A_DX4 && (R[R_POSMORS8_PC] > (R[R_POS_ATTUALE_M14]+R[R_TOLL_MORSE]))) 
			{
			if (MORSA14_A_DX4) MORSA14_MUOVI_DX4_GIRO_1 = 1;
			}
		// Ultima Morsa esistente va a SX : si muove per ultima
		if (!MORSA15_A_DX4 && MORSA14_A_DX4 && (R[R_POSMORS8_PC] < (R[R_POS_ATTUALE_M14]-R[R_TOLL_MORSE]))) 
			{
			if (MORSA14_A_DX4) MORSA14_MUOVI_DX4_GIRO_2 = 1;
			}

		// La Ultima morsa va a DX e si APRE subito, quindi le altre, se presenti si muovono al  2°giro
		if (MORSA15_MUOVI_DX4_GIRO_1 || (MORSA14_MUOVI_DX4_GIRO_1 && !MORSA15_A_DX4))
			{
			// Le morse 15-14 sono assegnate prima dato che possono sempre essere quella di testa
			if (MORSA10_A_DX4 || MORSA10_ASS_DX4) MORSA10_MUOVI_DX4_GIRO_2 = 1;
			if (MORSA11_A_DX4 || MORSA11_ASS_DX4) MORSA11_MUOVI_DX4_GIRO_2 = 1;
			if (MORSA12_A_DX4 || MORSA12_ASS_DX4) MORSA12_MUOVI_DX4_GIRO_2 = 1;
			if (MORSA13_A_DX4 || MORSA13_ASS_DX4) MORSA13_MUOVI_DX4_GIRO_2 = 1;
			}

		// La Ultima morsa va a SX e si apre dopo, quindi le altre, se presenti si muovono nel  1°giro
		if (MORSA15_MUOVI_DX4_GIRO_2 || (MORSA14_MUOVI_DX4_GIRO_2 && !MORSA15_A_DX4) )
			{
			// Le morse 15-14 sono assegnate prima dato che possono sempre essere quella di testa
			if (MORSA10_A_DX4 || MORSA10_ASS_DX4) MORSA10_MUOVI_DX4_GIRO_1 = 1;
			if (MORSA11_A_DX4 || MORSA11_ASS_DX4) MORSA11_MUOVI_DX4_GIRO_1 = 1;
			if (MORSA12_A_DX4 || MORSA12_ASS_DX4) MORSA12_MUOVI_DX4_GIRO_1 = 1;
			if (MORSA13_A_DX4 || MORSA13_ASS_DX4) MORSA13_MUOVI_DX4_GIRO_1 = 1;
			}

		} // Fine condizione peggiore : nessuna morsa resta ferma


	}	// Fine Sequenza BATTUTA_DX4_USATA



// Se c'è una morsa non assegnata a nessuna battuta va comunque mossa subito per sicurezza
// Ovviamente al secondo giro non le muovo
MORSA10_NON_ASSEGNATA_MUOVI = Mg_MC(200) && CONF_ASSE_M10 && !MORSA10_A_SX1 && !MORSA10_A_SX2 && !MORSA10_A_DX3 && !MORSA10_A_DX4;
MORSA11_NON_ASSEGNATA_MUOVI = Mg_MC(200) && CONF_ASSE_M11 && !MORSA11_A_SX1 && !MORSA11_A_SX2 && !MORSA11_A_DX3 && !MORSA11_A_DX4;
MORSA12_NON_ASSEGNATA_MUOVI = Mg_MC(200) && CONF_ASSE_M12 && !MORSA12_A_SX1 && !MORSA12_A_SX2 && !MORSA12_A_DX3 && !MORSA12_A_DX4;

MORSA13_NON_ASSEGNATA_MUOVI = Mg_MC(200) && CONF_ASSE_M13 && !MORSA13_A_SX1 && !MORSA13_A_SX2 && !MORSA13_A_DX3 && !MORSA13_A_DX4;
MORSA14_NON_ASSEGNATA_MUOVI = Mg_MC(200) && CONF_ASSE_M14 && !MORSA14_A_SX1 && !MORSA14_A_SX2 && !MORSA14_A_DX3 && !MORSA14_A_DX4;
MORSA15_NON_ASSEGNATA_MUOVI = Mg_MC(200) && CONF_ASSE_M15 && !MORSA15_A_SX1 && !MORSA15_A_SX2 && !MORSA15_A_DX3 && !MORSA15_A_DX4;


// Appoggi per gestione elegante riposizionamento in pendolare 
// Inserisco anche le morse non assegnate : se in pendolare quelle dell'altra zona restano a ZERO
MORSE_MUOVI_GIRO_1_ZONA_SX = MORSE_MUOVI_GIRO_1_DA_SX1;
MORSE_MUOVI_GIRO_2_ZONA_SX = MORSE_MUOVI_GIRO_2_DA_SX1;

// Appoggio per utilizzo lato CN
Aris_CH2[R_MORSE_MUOVI_GIRO_1_ZONA_SX] = R[R_MORSE_MUOVI_GIRO_1_ZONA_SX] = (float) MORSE_MUOVI_GIRO_1_ZONA_SX;
Aris_CH2[R_MORSE_MUOVI_GIRO_2_ZONA_SX] = R[R_MORSE_MUOVI_GIRO_2_ZONA_SX] = (float) MORSE_MUOVI_GIRO_2_ZONA_SX;

MORSE_MUOVI_GIRO_1_ZONA_DX = MORSE_MUOVI_GIRO_1_DA_DX4;
MORSE_MUOVI_GIRO_2_ZONA_DX = MORSE_MUOVI_GIRO_2_DA_DX4;

// Appoggio per utilizzo lato CN
Aris_CH2[R_MORSE_MUOVI_GIRO_1_ZONA_DX] = R[R_MORSE_MUOVI_GIRO_1_ZONA_DX] = (float) MORSE_MUOVI_GIRO_1_ZONA_DX;
Aris_CH2[R_MORSE_MUOVI_GIRO_2_ZONA_DX] = R[R_MORSE_MUOVI_GIRO_2_ZONA_DX] = (float) MORSE_MUOVI_GIRO_2_ZONA_DX;

// Appoggio i calcoli per aprire e chiudere le morse negli eventuali due giri di posizionamento
R[R_MORSE_RIPOS_GIRO1] =(float)(MORSE_MUOVI_GIRO_1_DA_SX1 |
								MORSE_MUOVI_GIRO_1_DA_DX4);
		
R[R_MORSE_RIPOS_GIRO2] =(float)(MORSE_MUOVI_GIRO_2_DA_SX1 |
								MORSE_MUOVI_GIRO_2_DA_DX4);

// Resetto tutti i bit che attivano il calcolo del riposizionamento
Mr_MC(200);

}		// Fine Sequenza di calcolo dei movimenti




}

else
        {
		// Resetta tutte le variabili coinvolte nel riposizionamento
		MORSE_MUOVI_GIRO_1_DA_SX1 = 0;
		MORSE_MUOVI_GIRO_2_DA_SX1 = 0;
		MORSE_MUOVI_GIRO_1_DA_DX4 = 0;
		MORSE_MUOVI_GIRO_2_DA_DX4 = 0;

		Mr_MC(200);
		}



}
