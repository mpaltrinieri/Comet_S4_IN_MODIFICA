/*
        --------------------------------------------------------------
        TITOLO:         Gestione Morse
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione Morse in modo standard
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void	gestione morse (void)
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
        DATA:			05-10-2006
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

void    gestione_morse(void)
{

/************ Sempre abilitato *************/
if (BITON)
{

/******* RESET ALLARMI ********/
if (RESET_MC)
		{
		Mr_MC(158);

		PLCMr_MC(158);

		POSMORSE_DA_PC_FAL = 0;
		}

// Conto il numero delle morse che hanno quota zero, se ne trovo più di una sicuramente è stato fatto un reset 
// della memoria retentiva quindi le metto tutte in posizione sconosciuta 32000

if(!MORSE_MOTORIZZATE)
{
	NUM_MORSE_A_ZERO = 0;
	if(CONF_MORSA_10 && ( (R[R_POS_ATTUALE_M10] > (float) (-0.1)) && (R[R_POS_ATTUALE_M10] < (float) (0.1)) )  ) NUM_MORSE_A_ZERO++;
	if(CONF_MORSA_11 && ( (R[R_POS_ATTUALE_M11] > (float) (-0.1)) && (R[R_POS_ATTUALE_M11] < (float) (0.1)) )  ) NUM_MORSE_A_ZERO++;
	if(CONF_MORSA_12 && ( (R[R_POS_ATTUALE_M12] > (float) (-0.1)) && (R[R_POS_ATTUALE_M12] < (float) (0.1)) )  ) NUM_MORSE_A_ZERO++;
	if(CONF_MORSA_13 && ( (R[R_POS_ATTUALE_M13] > (float) (-0.1)) && (R[R_POS_ATTUALE_M13] < (float) (0.1)) )  ) NUM_MORSE_A_ZERO++;
	if(CONF_MORSA_14 && ( (R[R_POS_ATTUALE_M14] > (float) (-0.1)) && (R[R_POS_ATTUALE_M14] < (float) (0.1)) )  ) NUM_MORSE_A_ZERO++;
	if(CONF_MORSA_15 && ( (R[R_POS_ATTUALE_M15] > (float) (-0.1)) && (R[R_POS_ATTUALE_M15] < (float) (0.1)) )  ) NUM_MORSE_A_ZERO++;

	if(CONF_MORSA_10 && (NUM_MORSE_A_ZERO>1.5) ) R[R_POS_ATTUALE_M10] = (float) 32000;
	if(CONF_MORSA_11 && (NUM_MORSE_A_ZERO>1.5) ) R[R_POS_ATTUALE_M11] = (float) 32000;
	if(CONF_MORSA_12 && (NUM_MORSE_A_ZERO>1.5) ) R[R_POS_ATTUALE_M12] = (float) 32000;
	if(CONF_MORSA_13 && (NUM_MORSE_A_ZERO>1.5) ) R[R_POS_ATTUALE_M13] = (float) 32000; 
	if(CONF_MORSA_14 && (NUM_MORSE_A_ZERO>1.5) ) R[R_POS_ATTUALE_M14] = (float) 32000; 
	if(CONF_MORSA_15 && (NUM_MORSE_A_ZERO>1.5) ) R[R_POS_ATTUALE_M15] = (float) 32000; 
}


// AUTOMATICO: Reset iniziale flag di CHIUSURA/APERTURA morse_SX in bassa/alta forza da SELETTORI
MORSA_DA_CH_AUT_S_10 = MORSA_DA_AP_AUT_S_10 = 0;
MORSA_DA_CH_AUT_S_11 = MORSA_DA_AP_AUT_S_11 = 0;
MORSA_DA_CH_AUT_S_12 = MORSA_DA_AP_AUT_S_12 = 0;
MORSA_DA_CH_AUT_S_13 = MORSA_DA_AP_AUT_S_13 = 0;
MORSA_DA_CH_AUT_S_14 = MORSA_DA_AP_AUT_S_14 = 0;
MORSA_DA_CH_AUT_S_15 = MORSA_DA_AP_AUT_S_15 = 0;


/* Unica verifica morse in posizione chiamata dal DRILL */
MORSA_10_IN_POSIZIONE =	(R[R_POSMORS4_PC] >= (R[R_POS_ATTUALE_M10]-R[R_TOLL_MORSE])) && 
						(R[R_POSMORS4_PC] <= (R[R_POS_ATTUALE_M10]+R[R_TOLL_MORSE]));

MORSA_11_IN_POSIZIONE =	(R[R_POSMORS5_PC] >= (R[R_POS_ATTUALE_M11]-R[R_TOLL_MORSE])) && 
						(R[R_POSMORS5_PC] <= (R[R_POS_ATTUALE_M11]+R[R_TOLL_MORSE]));

MORSA_12_IN_POSIZIONE =	(R[R_POSMORS6_PC] >= (R[R_POS_ATTUALE_M12]-R[R_TOLL_MORSE])) && 
						(R[R_POSMORS6_PC] <= (R[R_POS_ATTUALE_M12]+R[R_TOLL_MORSE]));

MORSA_13_IN_POSIZIONE =	(R[R_POSMORS7_PC] >= (R[R_POS_ATTUALE_M13]-R[R_TOLL_MORSE])) && 
						(R[R_POSMORS7_PC] <= (R[R_POS_ATTUALE_M13]+R[R_TOLL_MORSE]));

MORSA_14_IN_POSIZIONE =	(R[R_POSMORS8_PC] >= (R[R_POS_ATTUALE_M14]-R[R_TOLL_MORSE])) && 
						(R[R_POSMORS8_PC] <= (R[R_POS_ATTUALE_M14]+R[R_TOLL_MORSE]));

MORSA_15_IN_POSIZIONE =	(R[R_POSMORS9_PC] >= (R[R_POS_ATTUALE_M15]-R[R_TOLL_MORSE])) && 
						(R[R_POSMORS9_PC] <= (R[R_POS_ATTUALE_M15]+R[R_TOLL_MORSE]));



// Controllo se tutte le morse sono in posizione
TUTTE_LE_MORSE_IN_POSIZIONE_SX =
	(MORSA_10_IN_POSIZIONE || !CONF_MORSA_10)  &&
	(MORSA_11_IN_POSIZIONE || !CONF_MORSA_11)  &&
	(MORSA_12_IN_POSIZIONE || !CONF_MORSA_12) ;

////Aris_CH2[R_MORSE_IN_POSIZIONE_SX] = R[R_MORSE_IN_POSIZIONE_SX] = (float) TUTTE_LE_MORSE_IN_POSIZIONE_SX;
		

// Controllo se tutte le morse sono in posizione
TUTTE_LE_MORSE_IN_POSIZIONE_DX =
	(MORSA_13_IN_POSIZIONE || !CONF_MORSA_13) &&
	(MORSA_14_IN_POSIZIONE || !CONF_MORSA_14) &&
	(MORSA_15_IN_POSIZIONE || !CONF_MORSA_15);

////Aris_CH2[R_MORSE_IN_POSIZIONE_DX] = R[R_MORSE_IN_POSIZIONE_DX] = (float) TUTTE_LE_MORSE_IN_POSIZIONE_DX;


/********************************************************************************/
/********** Controllare : errore pos. morse da PC : VALORE fuori RANGE **********/
/********************************************************************************/
// Il posizionamento è improprio ma vale per entrambi i cicli

// Concedo una tolleranza di 1 mm per l'errore di collisione
if (Mg_MC(158) || PLCMg_MC(158))   // Controllo posizione morse di SX
	{
	
	if	(!ELIMINA_ALLARMI_0 &&
		(
		( CONF_ASSE_M10 && ( R[R_POSMORS4_PC]<R[R_FCNEG_M10] || R[R_POSMORS4_PC]>R[R_FCPOS_M10] ) ) ||
		( CONF_ASSE_M11 && ( R[R_POSMORS5_PC]<R[R_FCNEG_M11] || R[R_POSMORS5_PC]>R[R_FCPOS_M11] ) ) ||
		( CONF_ASSE_M12 && ( R[R_POSMORS6_PC]<R[R_FCNEG_M12] || R[R_POSMORS6_PC]>R[R_FCPOS_M12] ) ) ||
		( CONF_ASSE_M13	&& ( R[R_POSMORS7_PC]<R[R_FCNEG_M13] || R[R_POSMORS7_PC]>R[R_FCPOS_M13] ) ) ||
		( CONF_ASSE_M14	&& ( R[R_POSMORS8_PC]<R[R_FCNEG_M14] || R[R_POSMORS8_PC]>R[R_FCPOS_M14] ) ) ||
		( CONF_ASSE_M15	&& ( R[R_POSMORS9_PC]<R[R_FCNEG_M15] || R[R_POSMORS9_PC]>R[R_FCPOS_M15] ) ) ||

		( CONF_MORSA_10 && ( R[R_POSMORS4_PC]<(R[R_MIN_SX_ZONA_MORSE]-1) || R[R_POSMORS4_PC]>(R[R_MAX_SX_ZONA_MORSE]+1) ) ) ||
		( CONF_MORSA_11 && ( R[R_POSMORS5_PC]<(R[R_MIN_SX_ZONA_MORSE]-1) || R[R_POSMORS5_PC]>(R[R_MAX_SX_ZONA_MORSE]+1) ) ) ||
		( CONF_MORSA_12 && ( R[R_POSMORS6_PC]<(R[R_MIN_SX_ZONA_MORSE]-1) || R[R_POSMORS6_PC]>(R[R_MAX_SX_ZONA_MORSE]+1) ) ) ||
		( CONF_MORSA_13	&& ( R[R_POSMORS7_PC]<(R[R_MIN_SX_ZONA_MORSE]-1) || R[R_POSMORS7_PC]>(R[R_MAX_SX_ZONA_MORSE]+1) ) ) ||
		( CONF_MORSA_14	&& ( R[R_POSMORS8_PC]<(R[R_MIN_SX_ZONA_MORSE]-1) || R[R_POSMORS8_PC]>(R[R_MAX_SX_ZONA_MORSE]+1) ) ) ||
		( CONF_MORSA_15	&& ( R[R_POSMORS9_PC]<(R[R_MIN_SX_ZONA_MORSE]-1) || R[R_POSMORS9_PC]>(R[R_MAX_SX_ZONA_MORSE]+1) ) )
		)
		)
		{
		POSMORSE_DA_PC_FAL = 1;
		}
	else
		{
		Mr_MC(158);		// Nessun allarme -> vai avanti : il reset lo fa l'RESET_MC
		PLCMr_MC(158);
		}

	}


// Appoggio su aree A della associazione di Hdrill delle morse alle battute fisse SX1 - DX4   (DETERMINA:  MORSA10_A_SX1..  MORSE_CONTROLLATE_A_SX  MORSA_DA_CH_AUT_S_10..  MORSA10_ASS_SX1..)
APP2_GRUPPO_MORSE_SX1 = APP_GRUPPO_MORSE_SX1 = (int)(R[R_HDRILL_GRUPPO_MORSE_SX1]+0.2);       // Appoggio della associazione di Hdrill delle Morse alla battuta SX1
APP2_GRUPPO_MORSE_DX4 = APP_GRUPPO_MORSE_DX4 = (int)(R[R_HDRILL_GRUPPO_MORSE_DX4]+0.2);       // Appoggio della associazione di Hdrill delle Morse alla battuta DX4


// EVENTUALE FORZATURA ASSOCIAZIONE MORSE-BATTUTE NON ASSOCIATE
if(R[R_FORZ_CH_MORSE_LIBERE]>0.5)
{
	// Solo battuta SX1 attiva: forzatura associazione di tutte le morse presenti alla battuta SX1 ( APP_GRUPPO_MORSE_SX1 )
	if ( APP2_GRUPPO_MORSE_SX1 && !APP2_GRUPPO_MORSE_DX4 )  
	{
		MORSA10_A_SX1 = CONF_MORSA_10;  // Morsa 10 associata alla battuta SX1
		MORSA11_A_SX1 = CONF_MORSA_11;  // Morsa 11 associata alla battuta SX1
		MORSA12_A_SX1 = CONF_MORSA_12;  // Morsa 12 associata alla battuta SX1
		MORSA13_A_SX1 = CONF_MORSA_13;  // Morsa 13 associata alla battuta SX1
		MORSA14_A_SX1 = CONF_MORSA_14;  // Morsa 14 associata alla battuta SX1
		MORSA15_A_SX1 = CONF_MORSA_15;  // Morsa 15 associata alla battuta SX1
	}

	// Solo battuta DX4 attiva: forzatura associazione di tutte le morse presenti alla battuta DX4 ( APP_GRUPPO_MORSE_DX4 )
	if (!APP2_GRUPPO_MORSE_SX1 && APP2_GRUPPO_MORSE_DX4 )  
	{
		MORSA10_A_DX4 = CONF_MORSA_10;  // Morsa 10 associata alla battuta DX4
		MORSA11_A_DX4 = CONF_MORSA_11;  // Morsa 11 associata alla battuta DX4
		MORSA12_A_DX4 = CONF_MORSA_12;  // Morsa 12 associata alla battuta DX4
		MORSA13_A_DX4 = CONF_MORSA_13;  // Morsa 13 associata alla battuta DX4
		MORSA14_A_DX4 = CONF_MORSA_14;  // Morsa 14 associata alla battuta DX4
		MORSA15_A_DX4 = CONF_MORSA_15;  // Morsa 15 associata alla battuta DX4
	}

	// Battute SX1 e DX4 attive: forzatura associazione di tutte le morse SX presenti alla battuta SX1 e di quelle DX alla DX4 ( APP_GRUPPO_MORSE_SX1  APP_GRUPPO_MORSE_DX4 )
	if ( APP2_GRUPPO_MORSE_SX1 && APP2_GRUPPO_MORSE_DX4 ) 
	{
		MORSA10_A_SX1 = CONF_MORSA_10;  // Morsa 10 associata alla battuta SX1
		MORSA11_A_SX1 = CONF_MORSA_11;  // Morsa 11 associata alla battuta SX1
		MORSA12_A_SX1 = CONF_MORSA_12;  // Morsa 12 associata alla battuta SX1
		MORSA13_A_SX1 = 0;              // Morsa 13 
		MORSA14_A_SX1 = 0;              // Morsa 14 
		MORSA15_A_SX1 = 0;              // Morsa 15 

		MORSA10_A_DX4 = 0;              // Morsa 10 
		MORSA11_A_DX4 = 0;              // Morsa 11 
		MORSA12_A_DX4 = 0;              // Morsa 12 
		MORSA13_A_DX4 = CONF_MORSA_13;  // Morsa 13 associata alla battuta DX4
		MORSA14_A_DX4 = CONF_MORSA_14;  // Morsa 14 associata alla battuta DX4
		MORSA15_A_DX4 = CONF_MORSA_15;  // Morsa 15 associata alla battuta DX4
	}
}

// Appoggio su aree R della associazione PLC/HDRILL delle morse alle battute fisse SX1 - DX4   (usato nelle macro ISO del CNC)
R[R_PLC_GRUPPO_MORSE_SX1] = APP_GRUPPO_MORSE_SX1;	// Appoggio della associazione PLC delle Morse alla battuta SX1
R[R_PLC_GRUPPO_MORSE_DX4] = APP_GRUPPO_MORSE_DX4;	// Appoggio della associazione PLC delle Morse alla battuta DX4


/*Cumulativo delle morse da Chiudere per semplicità di gestione (determina:  MORSA10_DA_CH..  TUTTE_LE_MORSE_CH ) */
MORSE_DA_CHIUDERE = APP_GRUPPO_MORSE_SX1 |
					APP_GRUPPO_MORSE_DX4;

/* Cumulativo per semplice gestione nel multiprocesso PLC */
MORSE_DA_CHIUDERE_SX = APP_GRUPPO_MORSE_SX1;

/* Cumulativo per semplice gestione nel multiprocesso PLC */	
MORSE_DA_CHIUDERE_DX = APP_GRUPPO_MORSE_DX4;


// Flag di morse_SX chiuse in bassa forza //
MORSA10_CH_IN_BP = ( (CH_MORSE_SX_O && !CH_MORSA_10_HP_O && !AP_MORSA_10_O) && CONF_MORSA_10);
MORSA11_CH_IN_BP = ( (CH_MORSE_SX_O && !CH_MORSA_11_HP_O && !AP_MORSA_11_O) && CONF_MORSA_11);
MORSA12_CH_IN_BP = ( (CH_MORSE_SX_O && !CH_MORSA_12_HP_O && !AP_MORSA_12_O) && CONF_MORSA_12);                       

MORSA13_CH_IN_BP = ( (CH_MORSE_DX_O && !CH_MORSA_13_HP_O && !AP_MORSA_13_O) && CONF_MORSA_13); 
MORSA14_CH_IN_BP = ( (CH_MORSE_DX_O && !CH_MORSA_14_HP_O && !AP_MORSA_14_O) && CONF_MORSA_14);
MORSA15_CH_IN_BP = ( (CH_MORSE_DX_O && !CH_MORSA_15_HP_O && !AP_MORSA_15_O) && CONF_MORSA_15);
// Flag di morse_DX chiuse in bassa forza //                          

Aris_CH2[R_MORSE_CH_IN_BP] = R[R_MORSE_CH_IN_BP] = (unsigned int) MORSE_CH_IN_BASSA_PRESS;  //appoggio su area R lo stato delle morse chiuse in bassa forza


// Flag di morse_SX chiuse in alta forza //
MORSA10_CH_IN_HP = ((CH_MORSE_SX_O && CH_MORSA_10_HP_O && !AP_MORSA_10_O && PRESS_MORSE_HP_I) && CONF_MORSA_10);
MORSA11_CH_IN_HP = ((CH_MORSE_SX_O && CH_MORSA_11_HP_O && !AP_MORSA_11_O && PRESS_MORSE_HP_I) && CONF_MORSA_11);
MORSA12_CH_IN_HP = ((CH_MORSE_SX_O && CH_MORSA_12_HP_O && !AP_MORSA_12_O && PRESS_MORSE_HP_I) && CONF_MORSA_12);

MORSA13_CH_IN_HP = ((CH_MORSE_DX_O && CH_MORSA_13_HP_O && !AP_MORSA_13_O && PRESS_MORSE_HP_I) && CONF_MORSA_13); 
MORSA14_CH_IN_HP = ((CH_MORSE_DX_O && CH_MORSA_14_HP_O && !AP_MORSA_14_O && PRESS_MORSE_HP_I) && CONF_MORSA_14);
MORSA15_CH_IN_HP = ((CH_MORSE_DX_O && CH_MORSA_15_HP_O && !AP_MORSA_15_O && PRESS_MORSE_HP_I) && CONF_MORSA_15);
// Flag di morse_DX chiuse in alta forza //

Aris_CH2[R_MORSE_CH_IN_HP] = R[R_MORSE_CH_IN_HP] = (unsigned int) MORSE_CH_IN_HP;  //appoggio su area R lo stato delle morse chiuse in alta forza


// Flag di morse_SX aperte (di cui non è stata attivata la chiusura in bassa o alta forza)
MORSA_10_AP = !MORSA10_CH_IN_BP && !MORSA10_CH_IN_HP;
MORSA_11_AP = !MORSA11_CH_IN_BP && !MORSA11_CH_IN_HP;
MORSA_12_AP = !MORSA12_CH_IN_BP && !MORSA12_CH_IN_HP;

MORSA_13_AP = !MORSA13_CH_IN_BP && !MORSA13_CH_IN_HP;
MORSA_14_AP = !MORSA14_CH_IN_BP && !MORSA14_CH_IN_HP;
MORSA_15_AP = !MORSA15_CH_IN_BP && !MORSA15_CH_IN_HP;
// Flag di morse_DX aperte (di cui non è stata attivata la chiusura in bassa o alta forza)



// IN CICLICA 

// Bit di gestione morse
 
ALMENO_UNA_MORSA_SX_CH = 
	CH_MORSE_SX_O && !AP_MORSA_10_O ||
	CH_MORSE_SX_O && !AP_MORSA_11_O ||
	CH_MORSE_SX_O && !AP_MORSA_12_O;

ALMENO_UNA_MORSA_DX_CH = 
	CH_MORSE_DX_O && !AP_MORSA_13_O ||
	CH_MORSE_DX_O && !AP_MORSA_14_O ||
	CH_MORSE_DX_O && !AP_MORSA_15_O;

ALMENO_UNA_MORSA_CH = ALMENO_UNA_MORSA_SX_CH || ALMENO_UNA_MORSA_DX_CH;
	

TUTTE_LE_MORSE_CH =
	((CH_MORSE_SX_O && !AP_MORSA_10_O) || !CONF_MORSA_10 || !MORSA10_DA_CH ) && 
	((CH_MORSE_SX_O && !AP_MORSA_11_O) || !CONF_MORSA_11 || !MORSA11_DA_CH ) && 
	((CH_MORSE_SX_O && !AP_MORSA_12_O) || !CONF_MORSA_12 || !MORSA12_DA_CH ) &&
	((CH_MORSE_DX_O && !AP_MORSA_13_O) || !CONF_MORSA_13 || !MORSA13_DA_CH ) && 
	((CH_MORSE_DX_O && !AP_MORSA_14_O) || !CONF_MORSA_14 || !MORSA14_DA_CH ) && 
	((CH_MORSE_DX_O && !AP_MORSA_15_O) || !CONF_MORSA_15 || !MORSA15_DA_CH ); 


ALMENO_UNA_MORSA_SX_AP = 
	AP_MORSA_10_O || 
	AP_MORSA_11_O || 
	AP_MORSA_12_O;

ALMENO_UNA_MORSA_DX_AP = 
	AP_MORSA_13_O || 
	AP_MORSA_14_O || 
	AP_MORSA_15_O;


ALMENO_UNA_MORSA_AP = ALMENO_UNA_MORSA_SX_AP || ALMENO_UNA_MORSA_DX_AP;

// AUTOFEED : Morse necessarie aperte per permettere la conferma dello scarico pezzo:
MORSE_DA_APRIRE_SX = (int) (R[R_MORSE_1_12_DA_OPEN_AF]+0.1);
MORSE_DA_APRIRE_DX = (int) (R[R_MORSE_13_24_DA_OPEN_AF]+0.1);

MORSE_NECESSARIE_SX_AP = 
	(AP_MORSA_10_O || !CONF_MORSA_10 || !MORSA10_DA_APRIRE) &&
	(AP_MORSA_11_O || !CONF_MORSA_11 || !MORSA11_DA_APRIRE) &&
	(AP_MORSA_12_O || !CONF_MORSA_12 || !MORSA12_DA_APRIRE);

MORSE_NECESSARIE_DX_AP = 
	(AP_MORSA_13_O || !CONF_MORSA_13 || !MORSA13_DA_APRIRE) &&
	(AP_MORSA_14_O || !CONF_MORSA_14 || !MORSA14_DA_APRIRE) &&
	(AP_MORSA_15_O || !CONF_MORSA_15 || !MORSA15_DA_APRIRE);


MORSE_NECESSARIE_AP = MORSE_NECESSARIE_SX_AP && MORSE_NECESSARIE_DX_AP;


TUTTE_LE_MORSE_SX_AP =
	(AP_MORSA_10_O || !CONF_MORSA_10 || !MORSA10_DA_CH)  && 
	(AP_MORSA_11_O || !CONF_MORSA_11 || !MORSA11_DA_CH)  && 
	(AP_MORSA_12_O || !CONF_MORSA_12 || !MORSA12_DA_CH)  ;

TUTTE_LE_MORSE_DX_AP =
	(AP_MORSA_13_O || !CONF_MORSA_13 || !MORSA13_DA_CH ) && 
	(AP_MORSA_14_O || !CONF_MORSA_14 || !MORSA14_DA_CH ) && 
	(AP_MORSA_15_O || !CONF_MORSA_15 || !MORSA15_DA_CH );


TUTTE_LE_MORSE_AP = TUTTE_LE_MORSE_SX_AP && TUTTE_LE_MORSE_DX_AP;

MORSE_CH_FUNZ_MAN =  
	((CH_MORSE_SX_O && !AP_MORSA_10_O) || !CONF_MORSA_10) &&  
	((CH_MORSE_SX_O && !AP_MORSA_11_O) || !CONF_MORSA_11) &&  
	((CH_MORSE_SX_O && !AP_MORSA_12_O) || !CONF_MORSA_12) &&  
	((CH_MORSE_DX_O && !AP_MORSA_13_O) || !CONF_MORSA_13) &&  
	((CH_MORSE_DX_O && !AP_MORSA_14_O) || !CONF_MORSA_14) &&  
	((CH_MORSE_DX_O && !AP_MORSA_15_O) || !CONF_MORSA_15);

MORSE_AP_FUNZ_MAN =   
	(AP_MORSA_10_O || !CONF_MORSA_10) &&  
	(AP_MORSA_11_O || !CONF_MORSA_11) &&  
	(AP_MORSA_12_O || !CONF_MORSA_12) &&  
	(AP_MORSA_13_O || !CONF_MORSA_13) &&  
	(AP_MORSA_14_O || !CONF_MORSA_14) &&  
	(AP_MORSA_15_O || !CONF_MORSA_15);


CH_TUTTE_MORSE_FUNES_B = FUNZ_MAN33 && (P_OSCILLATORE && COMANDO_B || MORSE_CH_FUNZ_MAN);

AP_TUTTE_MORSE_FUNES_A = FUNZ_MAN33 && (P_OSCILLATORE && COMANDO_A || MORSE_AP_FUNZ_MAN);


/* Verifico le morse chiuse singolarmente : in multipezzo poi le guardo insieme */
MORSE_NECESSARIE_SX_CH = 
		(!MORSA10_DA_CH || (CH_MORSE_SX_O && !AP_MORSA_10_O) || !CONF_MORSA_10) &&
		(!MORSA11_DA_CH || (CH_MORSE_SX_O && !AP_MORSA_11_O) || !CONF_MORSA_11) &&
		(!MORSA12_DA_CH || (CH_MORSE_SX_O && !AP_MORSA_12_O) || !CONF_MORSA_12);
		
MORSE_NECESSARIE_DX_CH = 
		(!MORSA13_DA_CH || (CH_MORSE_DX_O && !AP_MORSA_13_O) || !CONF_MORSA_13) &&
		(!MORSA14_DA_CH || (CH_MORSE_DX_O && !AP_MORSA_14_O) || !CONF_MORSA_14) &&
		(!MORSA15_DA_CH || (CH_MORSE_DX_O && !AP_MORSA_15_O) || !CONF_MORSA_15);


/* Le morse richieste chiuse sono state chiuse dall'operatore */
MORSE_NECESSARIE_MULTI_CH = MORSE_NECESSARIE_SX_CH && MORSE_NECESSARIE_DX_CH; 


// Operazioni in manuale - chiudo le morse anche con i selettori 
RICHIESTA_SEL_MORSE_SX_CH = 
				(SEL_BLOCC_MORSE_SX_I && !SEL_SBLOC_MORSE_SX_I);

RICHIESTA_SEL_MORSE_SX_AP = 
				(SEL_SBLOC_MORSE_SX_I && !SEL_BLOCC_MORSE_SX_I);
				
RICHIESTA_SEL_MORSE_DX_CH = 
				(SEL_BLOCC_MORSE_DX_I && !SEL_SBLOC_MORSE_DX_I);

RICHIESTA_SEL_MORSE_DX_AP = 
				(SEL_SBLOC_MORSE_DX_I && !SEL_BLOCC_MORSE_DX_I);


//----------------------- CONTROLLA MORSE LIBERE ZONA SX ------------------------

// Controllo se la morsa è controllata in questo step
MORSA_10_CONTROLLATA_SX = (MORSA10_A_SX1);
MORSA_11_CONTROLLATA_SX = (MORSA11_A_SX1);
MORSA_12_CONTROLLATA_SX = (MORSA12_A_SX1);
MORSA_13_CONTROLLATA_SX = (MORSA13_A_SX1);
MORSA_14_CONTROLLATA_SX = (MORSA14_A_SX1);
MORSA_15_CONTROLLATA_SX = (MORSA15_A_SX1);

R[R_MORSE_CONTROLLATE_SX] = (float) MORSE_CONTROLLATE_A_SX;

//----------------------- CONTROLLA MORSE LIBERE ZONA DX ------------------------

// Controllo se la morsa è controllata in questo step
MORSA_10_CONTROLLATA_DX = (MORSA10_A_DX4);
MORSA_11_CONTROLLATA_DX = (MORSA11_A_DX4);
MORSA_12_CONTROLLATA_DX = (MORSA12_A_DX4);
MORSA_13_CONTROLLATA_DX = (MORSA13_A_DX4);
MORSA_14_CONTROLLATA_DX = (MORSA14_A_DX4);
MORSA_15_CONTROLLATA_DX = (MORSA15_A_DX4);

R[R_MORSE_CONTROLLATE_DX] = (float) MORSE_CONTROLLATE_A_DX;


/*======================================================================================*/
/*================        APERTURA E CHIUSURA MORSE IN MULTIPEZZO        ===============*/
/*======================================================================================*/

/*--------------------------- Apri/Chiudi le morse SX1 con selettore ---------------------*/

/* Chiudi singole morse durante carico */
if (CAR_MULTI_IN_CORSO && SEL_BLOCC_MORSE_SX_I)
	{
	if (MORSA10_A_SX1)                MORSA_DA_CH_AUT_S_10 = 1;
	if (MORSA11_A_SX1)                MORSA_DA_CH_AUT_S_11 = 1;
	if (MORSA12_A_SX1)                MORSA_DA_CH_AUT_S_12 = 1;
	if (MORSA13_A_SX1 && SINGOLO_ON)  MORSA_DA_CH_AUT_S_13 = 1;
	if (MORSA14_A_SX1 && SINGOLO_ON)  MORSA_DA_CH_AUT_S_14 = 1;
	if (MORSA15_A_SX1 && SINGOLO_ON)  MORSA_DA_CH_AUT_S_15 = 1;
	}


/* Apri singole morse durante carico o scarico */
if ((CAR_MULTI_IN_CORSO || SCA_MULTI_IN_CORSO) && SEL_SBLOC_MORSE_SX_I)
	{
	if (MORSA10_A_SX1)                MORSA_DA_AP_AUT_S_10 = 1;
	if (MORSA11_A_SX1)                MORSA_DA_AP_AUT_S_11 = 1;
	if (MORSA12_A_SX1)                MORSA_DA_AP_AUT_S_12 = 1;
	if (MORSA13_A_SX1 && SINGOLO_ON)  MORSA_DA_AP_AUT_S_13 = 1;
	if (MORSA14_A_SX1 && SINGOLO_ON)  MORSA_DA_AP_AUT_S_14 = 1;
	if (MORSA15_A_SX1 && SINGOLO_ON)  MORSA_DA_AP_AUT_S_15 = 1;
	}


//--------------------------- Apri/Chiudi le morse DX4 con selettore ---------------------

// Chiudi singole morse durante carico 
if (CAR_MULTI_IN_CORSO && SEL_BLOCC_MORSE_DX_I)
	{
	if (MORSA10_A_DX4 && SINGOLO_ON) MORSA_DA_CH_AUT_S_10 = 1;
	if (MORSA11_A_DX4 && SINGOLO_ON) MORSA_DA_CH_AUT_S_11 = 1;
	if (MORSA12_A_DX4 && SINGOLO_ON) MORSA_DA_CH_AUT_S_12 = 1;
	if (MORSA13_A_DX4)               MORSA_DA_CH_AUT_S_13 = 1;
	if (MORSA14_A_DX4)               MORSA_DA_CH_AUT_S_14 = 1;
	if (MORSA15_A_DX4)               MORSA_DA_CH_AUT_S_15 = 1;
	}


// Apri singole morse durante carico o scarico
if ((CAR_MULTI_IN_CORSO || SCA_MULTI_IN_CORSO) && SEL_SBLOC_MORSE_DX_I)
	{
	if (MORSA10_A_DX4 && SINGOLO_ON) MORSA_DA_AP_AUT_S_10 = 1;
	if (MORSA11_A_DX4 && SINGOLO_ON) MORSA_DA_AP_AUT_S_11 = 1;
	if (MORSA12_A_DX4 && SINGOLO_ON) MORSA_DA_AP_AUT_S_12 = 1;
	if (MORSA13_A_DX4)               MORSA_DA_AP_AUT_S_13 = 1;
	if (MORSA14_A_DX4)               MORSA_DA_AP_AUT_S_14 = 1;
	if (MORSA15_A_DX4)               MORSA_DA_AP_AUT_S_15 = 1;
	}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AUTOMATICO: TEST GESTIONE APERTURA/CHIUSURA MORSE CON CHIUSURA IN BASSA FORZA, DA SELETTORI


if (!AUTO) R[R_TEST_MORSE_BF] = 0;

if ( fabs(R[R_TEST_MORSE_BF]-422601) > 0.1 )	
{	// funzionamento normale           (R4110=0)
	R[R_MORSA_DA_CH_AUT_S_NN] = 0;
	R[R_MORSA_DA_AP_AUT_S_NN] = 0;
}
else
{	// simulazione di test             (R4110=422601)
MORSA_DA_CH_AUT_S_10 = (fabs(R[R_MORSA_DA_CH_AUT_S_NN]- 4)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-21)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-23)<0.1);
MORSA_DA_CH_AUT_S_11 = (fabs(R[R_MORSA_DA_CH_AUT_S_NN]- 5)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-21)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-23)<0.1);
MORSA_DA_CH_AUT_S_12 = (fabs(R[R_MORSA_DA_CH_AUT_S_NN]- 6)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-21)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-23)<0.1);
MORSA_DA_CH_AUT_S_13 = (fabs(R[R_MORSA_DA_CH_AUT_S_NN]- 7)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-22)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-23)<0.1);
MORSA_DA_CH_AUT_S_14 = (fabs(R[R_MORSA_DA_CH_AUT_S_NN]- 8)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-22)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-23)<0.1);
MORSA_DA_CH_AUT_S_15 = (fabs(R[R_MORSA_DA_CH_AUT_S_NN]- 9)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-22)<0.1) || (fabs(R[R_MORSA_DA_CH_AUT_S_NN]-23)<0.1);

MORSA_DA_AP_AUT_S_10 = (fabs(R[R_MORSA_DA_AP_AUT_S_NN]- 4)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-21)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-23)<0.1);
MORSA_DA_AP_AUT_S_11 = (fabs(R[R_MORSA_DA_AP_AUT_S_NN]- 5)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-21)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-23)<0.1);
MORSA_DA_AP_AUT_S_12 = (fabs(R[R_MORSA_DA_AP_AUT_S_NN]- 6)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-21)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-23)<0.1);
MORSA_DA_AP_AUT_S_13 = (fabs(R[R_MORSA_DA_AP_AUT_S_NN]- 7)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-22)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-23)<0.1);
MORSA_DA_AP_AUT_S_14 = (fabs(R[R_MORSA_DA_AP_AUT_S_NN]- 8)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-22)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-23)<0.1);
MORSA_DA_AP_AUT_S_15 = (fabs(R[R_MORSA_DA_AP_AUT_S_NN]- 9)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-22)<0.1) || (fabs(R[R_MORSA_DA_AP_AUT_S_NN]-23)<0.1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Nota: In automatico occorre resettare le chiusure morse in alta forza per poter aprir le morse

// AUTOMATICO: Attivazione PLCM di CHIUSURA_IN_BASSA_FORZA morse, da selettori
if (MORSA_DA_CH_AUT_S_10 || MORSA_DA_CH_AUT_S_11 || MORSA_DA_CH_AUT_S_12 || MORSA_DA_CH_AUT_S_13 || MORSA_DA_CH_AUT_S_14 || MORSA_DA_CH_AUT_S_15)  
{
	if (MORSA_DA_CH_AUT_S_10)      {PLCMr_MC(234); PLCM134 = 1; PLCMr_MC(274); PLCM294 = 1;} else if (MORSA_10_AP) {PLCM234 = 1; PLCMr_MC(134); PLCMr_MC(274); PLCM294 = 1;}
	if (MORSA_DA_CH_AUT_S_11)      {PLCMr_MC(235); PLCM135 = 1; PLCMr_MC(275); PLCM295 = 1;} else if (MORSA_11_AP) {PLCM235 = 1; PLCMr_MC(135); PLCMr_MC(275); PLCM295 = 1;}
	if (MORSA_DA_CH_AUT_S_12)      {PLCMr_MC(236); PLCM136 = 1; PLCMr_MC(276); PLCM296 = 1;} else if (MORSA_12_AP) {PLCM236 = 1; PLCMr_MC(136); PLCMr_MC(276); PLCM296 = 1;}
	if (MORSA_DA_CH_AUT_S_13)      {PLCMr_MC(237); PLCM137 = 1; PLCMr_MC(277); PLCM297 = 1;} else if (MORSA_13_AP) {PLCM237 = 1; PLCMr_MC(137); PLCMr_MC(277); PLCM297 = 1;}
	if (MORSA_DA_CH_AUT_S_14)      {PLCMr_MC(238); PLCM138 = 1; PLCMr_MC(278); PLCM298 = 1;} else if (MORSA_14_AP) {PLCM238 = 1; PLCMr_MC(138); PLCMr_MC(278); PLCM298 = 1;}
	if (MORSA_DA_CH_AUT_S_15)      {PLCMr_MC(239); PLCM139 = 1; PLCMr_MC(279); PLCM299 = 1;} else if (MORSA_15_AP) {PLCM239 = 1; PLCMr_MC(139); PLCMr_MC(279); PLCM299 = 1;}
}

// AUTOMATICO: Attivazione PLCM di APERTURA_IN_ALTA_FORZA morse, da selettori
if (MORSA_DA_AP_AUT_S_10)    {PLCM234 = 1;  PLCMr_MC(134); PLCMr_MC(274); PLCM294 = 1;}
if (MORSA_DA_AP_AUT_S_11)    {PLCM235 = 1;  PLCMr_MC(135); PLCMr_MC(275); PLCM295 = 1;}
if (MORSA_DA_AP_AUT_S_12)    {PLCM236 = 1;  PLCMr_MC(136); PLCMr_MC(276); PLCM296 = 1;}
if (MORSA_DA_AP_AUT_S_13)    {PLCM237 = 1;  PLCMr_MC(137); PLCMr_MC(277); PLCM297 = 1;}
if (MORSA_DA_AP_AUT_S_14)    {PLCM238 = 1;  PLCMr_MC(138); PLCMr_MC(278); PLCM298 = 1;}
if (MORSA_DA_AP_AUT_S_15)    {PLCM239 = 1;  PLCMr_MC(139); PLCMr_MC(279); PLCM299 = 1;}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// AUTOMATICO: GESTIONE APERTURA/CHIUSURA MORSE CON CHIUSURA IN BASSA/ALTA FORZA, DAI MULTIPROCESSI SX DX


if ( fabs(R[R_TEST_MORSE_BF]-422601) > 0.1 )
{	// funzionamento normale           (R4110=0)
	R[R_Apri_in_AF_Morsa_NN] = 0;
	R[R_Chiudi_in_BF_Morsa_NN] = 0;
	R[R_Chiudi_in_AF_Morsa_NN] = 0;
	R[R_Disat_chius_in_AF_Morsa_NN] = 0;
}
else
{	// simulazione di test             (R4110=422601)
Apri_in_AF_Morsa_10 = (fabs(R[R_Apri_in_AF_Morsa_NN]- 4)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-23)<0.1);
Apri_in_AF_Morsa_11 = (fabs(R[R_Apri_in_AF_Morsa_NN]- 5)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-23)<0.1);
Apri_in_AF_Morsa_12 = (fabs(R[R_Apri_in_AF_Morsa_NN]- 6)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-23)<0.1);
Apri_in_AF_Morsa_13 = (fabs(R[R_Apri_in_AF_Morsa_NN]- 7)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-23)<0.1);
Apri_in_AF_Morsa_14 = (fabs(R[R_Apri_in_AF_Morsa_NN]- 8)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-23)<0.1);
Apri_in_AF_Morsa_15 = (fabs(R[R_Apri_in_AF_Morsa_NN]- 9)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Apri_in_AF_Morsa_NN]-23)<0.1);

Chiudi_in_BF_Morsa_10 = (fabs(R[R_Chiudi_in_BF_Morsa_NN]- 4)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-21)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-23)<0.1);
Chiudi_in_BF_Morsa_11 = (fabs(R[R_Chiudi_in_BF_Morsa_NN]- 5)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-21)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-23)<0.1);
Chiudi_in_BF_Morsa_12 = (fabs(R[R_Chiudi_in_BF_Morsa_NN]- 6)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-21)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-23)<0.1);
Chiudi_in_BF_Morsa_13 = (fabs(R[R_Chiudi_in_BF_Morsa_NN]- 7)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-22)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-23)<0.1);
Chiudi_in_BF_Morsa_14 = (fabs(R[R_Chiudi_in_BF_Morsa_NN]- 8)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-22)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-23)<0.1);
Chiudi_in_BF_Morsa_15 = (fabs(R[R_Chiudi_in_BF_Morsa_NN]- 9)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-22)<0.1) || (fabs(R[R_Chiudi_in_BF_Morsa_NN]-23)<0.1);

Chiudi_in_AF_Morsa_10 = (fabs(R[R_Chiudi_in_AF_Morsa_NN]- 4)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-23)<0.1);
Chiudi_in_AF_Morsa_11 = (fabs(R[R_Chiudi_in_AF_Morsa_NN]- 5)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-23)<0.1);
Chiudi_in_AF_Morsa_12 = (fabs(R[R_Chiudi_in_AF_Morsa_NN]- 6)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-23)<0.1);
Chiudi_in_AF_Morsa_13 = (fabs(R[R_Chiudi_in_AF_Morsa_NN]- 7)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-23)<0.1);
Chiudi_in_AF_Morsa_14 = (fabs(R[R_Chiudi_in_AF_Morsa_NN]- 8)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-23)<0.1);
Chiudi_in_AF_Morsa_15 = (fabs(R[R_Chiudi_in_AF_Morsa_NN]- 9)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Chiudi_in_AF_Morsa_NN]-23)<0.1);

Disat_chius_in_AF_Morsa_10 = (fabs(R[R_Disat_chius_in_AF_Morsa_NN]- 4)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-23)<0.1);
Disat_chius_in_AF_Morsa_11 = (fabs(R[R_Disat_chius_in_AF_Morsa_NN]- 5)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-23)<0.1);
Disat_chius_in_AF_Morsa_12 = (fabs(R[R_Disat_chius_in_AF_Morsa_NN]- 6)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-21)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-23)<0.1);
Disat_chius_in_AF_Morsa_13 = (fabs(R[R_Disat_chius_in_AF_Morsa_NN]- 7)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-23)<0.1);
Disat_chius_in_AF_Morsa_14 = (fabs(R[R_Disat_chius_in_AF_Morsa_NN]- 8)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-23)<0.1);
Disat_chius_in_AF_Morsa_15 = (fabs(R[R_Disat_chius_in_AF_Morsa_NN]- 9)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-22)<0.1) || (fabs(R[R_Disat_chius_in_AF_Morsa_NN]-23)<0.1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Nota: In automatico occorre resettare le chiusure morse in alta forza per poter aprir le morse
//                                                                     NEW                              NEW  
// PLC M234 Apri_in_AF_Morsa_10   PLC M134 Chiudi_in_BF_Morsa_10   PLC M274 Chiudi_in_AF_Morsa_10   PLC M294 Disat_chius_in_AF_Morsa_10    
// PLC M235 Apri_in_AF_Morsa_11   PLC M135 Chiudi_in_BF_Morsa_11   PLC M275 Chiudi_in_AF_Morsa_11   PLC M295 Disat_chius_in_AF_Morsa_11    
// PLC M236 Apri_in_AF_Morsa_12   PLC M136 Chiudi_in_BF_Morsa_12   PLC M276 Chiudi_in_AF_Morsa_12   PLC M296 Disat_chius_in_AF_Morsa_12    
// PLC M237 Apri_in_AF_Morsa_13   PLC M137 Chiudi_in_BF_Morsa_13   PLC M277 Chiudi_in_AF_Morsa_13   PLC M297 Disat_chius_in_AF_Morsa_13    
// PLC M238 Apri_in_AF_Morsa_14   PLC M138 Chiudi_in_BF_Morsa_14   PLC M278 Chiudi_in_AF_Morsa_14   PLC M298 Disat_chius_in_AF_Morsa_14    
// PLC M239 Apri_in_AF_Morsa_15   PLC M139 Chiudi_in_BF_Morsa_15   PLC M279 Chiudi_in_AF_Morsa_15   PLC M299 Disat_chius_in_AF_Morsa_15    

// DERIVATE DELLE RICHIESTE DEI MULTIPROCESSI SX DX
DP_Apri_in_AF_Morsa_10 = Apri_in_AF_Morsa_10 && !mem_Apri_in_AF_Morsa_10;           mem_Apri_in_AF_Morsa_10 = Apri_in_AF_Morsa_10;
DP_Apri_in_AF_Morsa_11 = Apri_in_AF_Morsa_11 && !mem_Apri_in_AF_Morsa_11;           mem_Apri_in_AF_Morsa_11 = Apri_in_AF_Morsa_11;
DP_Apri_in_AF_Morsa_12 = Apri_in_AF_Morsa_12 && !mem_Apri_in_AF_Morsa_12;           mem_Apri_in_AF_Morsa_12 = Apri_in_AF_Morsa_12;
DP_Apri_in_AF_Morsa_13 = Apri_in_AF_Morsa_13 && !mem_Apri_in_AF_Morsa_13;           mem_Apri_in_AF_Morsa_13 = Apri_in_AF_Morsa_13;
DP_Apri_in_AF_Morsa_14 = Apri_in_AF_Morsa_14 && !mem_Apri_in_AF_Morsa_14;           mem_Apri_in_AF_Morsa_14 = Apri_in_AF_Morsa_14;
DP_Apri_in_AF_Morsa_15 = Apri_in_AF_Morsa_15 && !mem_Apri_in_AF_Morsa_15;           mem_Apri_in_AF_Morsa_15 = Apri_in_AF_Morsa_15;

DP_Chiudi_in_BF_Morsa_10 = Chiudi_in_BF_Morsa_10 && !mem_Chiudi_in_BF_Morsa_10;     mem_Chiudi_in_BF_Morsa_10 = Chiudi_in_BF_Morsa_10;
DP_Chiudi_in_BF_Morsa_11 = Chiudi_in_BF_Morsa_11 && !mem_Chiudi_in_BF_Morsa_11;     mem_Chiudi_in_BF_Morsa_11 = Chiudi_in_BF_Morsa_11;
DP_Chiudi_in_BF_Morsa_12 = Chiudi_in_BF_Morsa_12 && !mem_Chiudi_in_BF_Morsa_12;     mem_Chiudi_in_BF_Morsa_12 = Chiudi_in_BF_Morsa_12;
DP_Chiudi_in_BF_Morsa_13 = Chiudi_in_BF_Morsa_13 && !mem_Chiudi_in_BF_Morsa_13;     mem_Chiudi_in_BF_Morsa_13 = Chiudi_in_BF_Morsa_13;
DP_Chiudi_in_BF_Morsa_14 = Chiudi_in_BF_Morsa_14 && !mem_Chiudi_in_BF_Morsa_14;     mem_Chiudi_in_BF_Morsa_14 = Chiudi_in_BF_Morsa_14;
DP_Chiudi_in_BF_Morsa_15 = Chiudi_in_BF_Morsa_15 && !mem_Chiudi_in_BF_Morsa_15;     mem_Chiudi_in_BF_Morsa_15 = Chiudi_in_BF_Morsa_15;

DP_Chiudi_in_AF_Morsa_10 = Chiudi_in_AF_Morsa_10 && !mem_Chiudi_in_AF_Morsa_10;     mem_Chiudi_in_AF_Morsa_10 = Chiudi_in_AF_Morsa_10;
DP_Chiudi_in_AF_Morsa_11 = Chiudi_in_AF_Morsa_11 && !mem_Chiudi_in_AF_Morsa_11;     mem_Chiudi_in_AF_Morsa_11 = Chiudi_in_AF_Morsa_11;
DP_Chiudi_in_AF_Morsa_12 = Chiudi_in_AF_Morsa_12 && !mem_Chiudi_in_AF_Morsa_12;     mem_Chiudi_in_AF_Morsa_12 = Chiudi_in_AF_Morsa_12;
DP_Chiudi_in_AF_Morsa_13 = Chiudi_in_AF_Morsa_13 && !mem_Chiudi_in_AF_Morsa_13;     mem_Chiudi_in_AF_Morsa_13 = Chiudi_in_AF_Morsa_13;
DP_Chiudi_in_AF_Morsa_14 = Chiudi_in_AF_Morsa_14 && !mem_Chiudi_in_AF_Morsa_14;     mem_Chiudi_in_AF_Morsa_14 = Chiudi_in_AF_Morsa_14;
DP_Chiudi_in_AF_Morsa_15 = Chiudi_in_AF_Morsa_15 && !mem_Chiudi_in_AF_Morsa_15;     mem_Chiudi_in_AF_Morsa_15 = Chiudi_in_AF_Morsa_15;

DP_Disat_chius_in_AF_Morsa_10 = Disat_chius_in_AF_Morsa_10 && !mem_Disat_chius_in_AF_Morsa_10;   mem_Disat_chius_in_AF_Morsa_10 = Disat_chius_in_AF_Morsa_10;
DP_Disat_chius_in_AF_Morsa_11 = Disat_chius_in_AF_Morsa_11 && !mem_Disat_chius_in_AF_Morsa_11;   mem_Disat_chius_in_AF_Morsa_11 = Disat_chius_in_AF_Morsa_11;
DP_Disat_chius_in_AF_Morsa_12 = Disat_chius_in_AF_Morsa_12 && !mem_Disat_chius_in_AF_Morsa_12;   mem_Disat_chius_in_AF_Morsa_12 = Disat_chius_in_AF_Morsa_12;
DP_Disat_chius_in_AF_Morsa_13 = Disat_chius_in_AF_Morsa_13 && !mem_Disat_chius_in_AF_Morsa_13;   mem_Disat_chius_in_AF_Morsa_13 = Disat_chius_in_AF_Morsa_13;
DP_Disat_chius_in_AF_Morsa_14 = Disat_chius_in_AF_Morsa_14 && !mem_Disat_chius_in_AF_Morsa_14;   mem_Disat_chius_in_AF_Morsa_14 = Disat_chius_in_AF_Morsa_14;
DP_Disat_chius_in_AF_Morsa_15 = Disat_chius_in_AF_Morsa_15 && !mem_Disat_chius_in_AF_Morsa_15;   mem_Disat_chius_in_AF_Morsa_15 = Disat_chius_in_AF_Morsa_15;


// PLCM234 Apri_in_AF_Morsa_10   PLCM134 Chiudi_in_BF_Morsa_10   PLCM274 Chiudi_in_AF_Morsa_10   PLCM294 Disat_chius_in_AF_Morsa_10    
// PLCM235 Apri_in_AF_Morsa_11   PLCM135 Chiudi_in_BF_Morsa_11   PLCM275 Chiudi_in_AF_Morsa_11   PLCM295 Disat_chius_in_AF_Morsa_11    
// PLCM236 Apri_in_AF_Morsa_12   PLCM136 Chiudi_in_BF_Morsa_12   PLCM276 Chiudi_in_AF_Morsa_12   PLCM296 Disat_chius_in_AF_Morsa_12    
// PLCM237 Apri_in_AF_Morsa_13   PLCM137 Chiudi_in_BF_Morsa_13   PLCM277 Chiudi_in_AF_Morsa_13   PLCM297 Disat_chius_in_AF_Morsa_13    
// PLCM238 Apri_in_AF_Morsa_14   PLCM138 Chiudi_in_BF_Morsa_14   PLCM278 Chiudi_in_AF_Morsa_14   PLCM298 Disat_chius_in_AF_Morsa_14    
// PLCM239 Apri_in_AF_Morsa_15   PLCM139 Chiudi_in_BF_Morsa_15   PLCM279 Chiudi_in_AF_Morsa_15   PLCM299 Disat_chius_in_AF_Morsa_15    


// AUTOMATICO: Attivazione PLCM di APERTURA_IN_ALTA_FORZA morse, DA MULTIPROCESSO
if (DP_Apri_in_AF_Morsa_10)  {PLCM234 = 1;  PLCMr_MC(134); PLCMr_MC(274); PLCM294 = 1;}
if (DP_Apri_in_AF_Morsa_11)  {PLCM235 = 1;  PLCMr_MC(135); PLCMr_MC(275); PLCM295 = 1;}
if (DP_Apri_in_AF_Morsa_12)  {PLCM236 = 1;  PLCMr_MC(136); PLCMr_MC(276); PLCM296 = 1;}
if (DP_Apri_in_AF_Morsa_13)  {PLCM237 = 1;  PLCMr_MC(137); PLCMr_MC(277); PLCM297 = 1;}
if (DP_Apri_in_AF_Morsa_14)  {PLCM238 = 1;  PLCMr_MC(138); PLCMr_MC(278); PLCM298 = 1;}
if (DP_Apri_in_AF_Morsa_15)  {PLCM239 = 1;  PLCMr_MC(139); PLCMr_MC(279); PLCM299 = 1;}

if (!PLCMg_MC(234) && !PLCMg_MC(134) && !PLCMg_MC(274) && !PLCMg_MC(294)) Apri_in_AF_Morsa_10 = 0;
if (!PLCMg_MC(235) && !PLCMg_MC(135) && !PLCMg_MC(275) && !PLCMg_MC(295)) Apri_in_AF_Morsa_11 = 0;
if (!PLCMg_MC(236) && !PLCMg_MC(136) && !PLCMg_MC(276) && !PLCMg_MC(296)) Apri_in_AF_Morsa_12 = 0;
if (!PLCMg_MC(237) && !PLCMg_MC(137) && !PLCMg_MC(277) && !PLCMg_MC(297)) Apri_in_AF_Morsa_13 = 0;
if (!PLCMg_MC(238) && !PLCMg_MC(138) && !PLCMg_MC(278) && !PLCMg_MC(298)) Apri_in_AF_Morsa_14 = 0;
if (!PLCMg_MC(239) && !PLCMg_MC(139) && !PLCMg_MC(279) && !PLCMg_MC(299)) Apri_in_AF_Morsa_15 = 0;



// AUTOMATICO: Attivazione PLCM di CHIUSURA_IN_BASSA_FORZA morse_SX, DA MULTIPROCESSO
if (DP_Chiudi_in_BF_Morsa_10 || DP_Chiudi_in_BF_Morsa_11 || DP_Chiudi_in_BF_Morsa_12 || DP_Chiudi_in_BF_Morsa_13 || DP_Chiudi_in_BF_Morsa_14 || DP_Chiudi_in_BF_Morsa_15)  
{
	if (DP_Chiudi_in_BF_Morsa_10)  {PLCMr_MC(234); PLCM134 = 1; PLCMr_MC(274); PLCM294 = 1;} else if (MORSA_10_AP) {PLCM234 = 1; PLCMr_MC(134); PLCMr_MC(274); PLCM294 = 1;}
	if (DP_Chiudi_in_BF_Morsa_11)  {PLCMr_MC(235); PLCM135 = 1; PLCMr_MC(275); PLCM295 = 1;} else if (MORSA_11_AP) {PLCM235 = 1; PLCMr_MC(135); PLCMr_MC(275); PLCM295 = 1;}
	if (DP_Chiudi_in_BF_Morsa_12)  {PLCMr_MC(236); PLCM136 = 1; PLCMr_MC(276); PLCM296 = 1;} else if (MORSA_12_AP) {PLCM236 = 1; PLCMr_MC(136); PLCMr_MC(276); PLCM296 = 1;}
	if (DP_Chiudi_in_BF_Morsa_13)  {PLCMr_MC(237); PLCM137 = 1; PLCMr_MC(277); PLCM297 = 1;} else if (MORSA_13_AP) {PLCM237 = 1; PLCMr_MC(137); PLCMr_MC(277); PLCM297 = 1;}
	if (DP_Chiudi_in_BF_Morsa_14)  {PLCMr_MC(238); PLCM138 = 1; PLCMr_MC(278); PLCM298 = 1;} else if (MORSA_14_AP) {PLCM238 = 1; PLCMr_MC(138); PLCMr_MC(278); PLCM298 = 1;}
	if (DP_Chiudi_in_BF_Morsa_15)  {PLCMr_MC(239); PLCM139 = 1; PLCMr_MC(279); PLCM299 = 1;} else if (MORSA_15_AP) {PLCM239 = 1; PLCMr_MC(139); PLCMr_MC(279); PLCM299 = 1;}
}

if (!PLCMg_MC(234) && !PLCMg_MC(134) && !PLCMg_MC(274) && !PLCMg_MC(294)) Chiudi_in_BF_Morsa_10 = 0;
if (!PLCMg_MC(235) && !PLCMg_MC(135) && !PLCMg_MC(275) && !PLCMg_MC(295)) Chiudi_in_BF_Morsa_11 = 0;
if (!PLCMg_MC(236) && !PLCMg_MC(136) && !PLCMg_MC(276) && !PLCMg_MC(296)) Chiudi_in_BF_Morsa_12 = 0;
if (!PLCMg_MC(237) && !PLCMg_MC(137) && !PLCMg_MC(277) && !PLCMg_MC(297)) Chiudi_in_BF_Morsa_13 = 0;
if (!PLCMg_MC(238) && !PLCMg_MC(138) && !PLCMg_MC(278) && !PLCMg_MC(298)) Chiudi_in_BF_Morsa_14 = 0;
if (!PLCMg_MC(239) && !PLCMg_MC(139) && !PLCMg_MC(279) && !PLCMg_MC(299)) Chiudi_in_BF_Morsa_15 = 0;


// AUTOMATICO: Attivazione PLCM di CHIUSURA_IN_ALTA_FORZA morse, DA MULTIPROCESSO
if (DP_Chiudi_in_AF_Morsa_10)  {PLCMr_MC(234); PLCM274 = 1; PLCMr_MC(294);}
if (DP_Chiudi_in_AF_Morsa_11)  {PLCMr_MC(235); PLCM275 = 1; PLCMr_MC(295);}
if (DP_Chiudi_in_AF_Morsa_12)  {PLCMr_MC(236); PLCM276 = 1; PLCMr_MC(296);}
if (DP_Chiudi_in_AF_Morsa_13)  {PLCMr_MC(237); PLCM277 = 1; PLCMr_MC(297);}
if (DP_Chiudi_in_AF_Morsa_14)  {PLCMr_MC(238); PLCM278 = 1; PLCMr_MC(298);}
if (DP_Chiudi_in_AF_Morsa_15)  {PLCMr_MC(239); PLCM279 = 1; PLCMr_MC(299);}

if (!PLCMg_MC(234) && !PLCMg_MC(274) && !PLCMg_MC(294)) Chiudi_in_AF_Morsa_10 = 0;
if (!PLCMg_MC(235) && !PLCMg_MC(275) && !PLCMg_MC(295)) Chiudi_in_AF_Morsa_11 = 0;
if (!PLCMg_MC(236) && !PLCMg_MC(276) && !PLCMg_MC(296)) Chiudi_in_AF_Morsa_12 = 0;
if (!PLCMg_MC(237) && !PLCMg_MC(277) && !PLCMg_MC(297)) Chiudi_in_AF_Morsa_13 = 0;
if (!PLCMg_MC(238) && !PLCMg_MC(278) && !PLCMg_MC(298)) Chiudi_in_AF_Morsa_14 = 0;
if (!PLCMg_MC(239) && !PLCMg_MC(279) && !PLCMg_MC(299)) Chiudi_in_AF_Morsa_15 = 0;


// AUTOMATICO: Attivazione PLCM di Disattiva_chiusura_in_alta_forza morse, DA MULTIPROCESSO
if (DP_Disat_chius_in_AF_Morsa_10)  {PLCM294 = 1;}
if (DP_Disat_chius_in_AF_Morsa_11)  {PLCM295 = 1;}
if (DP_Disat_chius_in_AF_Morsa_12)  {PLCM296 = 1;}
if (DP_Disat_chius_in_AF_Morsa_13)  {PLCM297 = 1;}
if (DP_Disat_chius_in_AF_Morsa_14)  {PLCM298 = 1;}
if (DP_Disat_chius_in_AF_Morsa_15)  {PLCM299 = 1;}

if (!PLCMg_MC(294)) Disat_chius_in_AF_Morsa_10 = 0;
if (!PLCMg_MC(295)) Disat_chius_in_AF_Morsa_11 = 0;
if (!PLCMg_MC(296)) Disat_chius_in_AF_Morsa_12 = 0;
if (!PLCMg_MC(297)) Disat_chius_in_AF_Morsa_13 = 0;
if (!PLCMg_MC(298)) Disat_chius_in_AF_Morsa_14 = 0;
if (!PLCMg_MC(299)) Disat_chius_in_AF_Morsa_15 = 0;



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MANUALE: GESTIONE APERTURA/CHIUSURA MORSE CON CHIUSURA IN BASSA FORZA, DA SELETTORI O FUNZIONI MANUALI
// Nota: In manuale non occorre resettare le chiusure morse in alta forza, dato che sono già costantemente resettate dall'assenza di TS_FORZA_ALTA_PRESS_MAN

// MANUALE: appoggio condizioni di CHIUSURA morse da funzioni manuali o selettori 
MORSA_DA_CH_MAN_10 = ((FUNZ_MAN37 || FUNZ_MAN33) && COMANDO_B) || (RICHIESTA_SEL_MORSE_SX_CH || RICHIESTA_SEL_MORSE_DX_CH);
MORSA_DA_CH_MAN_11 = ((FUNZ_MAN38 || FUNZ_MAN33) && COMANDO_B) || (RICHIESTA_SEL_MORSE_SX_CH || RICHIESTA_SEL_MORSE_DX_CH);
MORSA_DA_CH_MAN_12 = ((FUNZ_MAN39 || FUNZ_MAN33) && COMANDO_B) || (RICHIESTA_SEL_MORSE_SX_CH || RICHIESTA_SEL_MORSE_DX_CH);
MORSA_DA_CH_MAN_13 = ((FUNZ_MAN40 || FUNZ_MAN33) && COMANDO_B) || (RICHIESTA_SEL_MORSE_SX_CH || RICHIESTA_SEL_MORSE_DX_CH);
MORSA_DA_CH_MAN_14 = ((FUNZ_MAN41 || FUNZ_MAN33) && COMANDO_B) || (RICHIESTA_SEL_MORSE_SX_CH || RICHIESTA_SEL_MORSE_DX_CH);
MORSA_DA_CH_MAN_15 = ((FUNZ_MAN42 || FUNZ_MAN33) && COMANDO_B) || (RICHIESTA_SEL_MORSE_SX_CH || RICHIESTA_SEL_MORSE_DX_CH);

// MANUALE: appoggio condizioni di APERTURA morse da funzioni manuali o selettori 
MORSA_DA_AP_MAN_10 = ((FUNZ_MAN37 || FUNZ_MAN33) && COMANDO_A) || (RICHIESTA_SEL_MORSE_SX_AP || RICHIESTA_SEL_MORSE_DX_AP);
MORSA_DA_AP_MAN_11 = ((FUNZ_MAN38 || FUNZ_MAN33) && COMANDO_A) || (RICHIESTA_SEL_MORSE_SX_AP || RICHIESTA_SEL_MORSE_DX_AP);
MORSA_DA_AP_MAN_12 = ((FUNZ_MAN39 || FUNZ_MAN33) && COMANDO_A) || (RICHIESTA_SEL_MORSE_SX_AP || RICHIESTA_SEL_MORSE_DX_AP);
MORSA_DA_AP_MAN_13 = ((FUNZ_MAN40 || FUNZ_MAN33) && COMANDO_A) || (RICHIESTA_SEL_MORSE_SX_AP || RICHIESTA_SEL_MORSE_DX_AP);
MORSA_DA_AP_MAN_14 = ((FUNZ_MAN41 || FUNZ_MAN33) && COMANDO_A) || (RICHIESTA_SEL_MORSE_SX_AP || RICHIESTA_SEL_MORSE_DX_AP);
MORSA_DA_AP_MAN_15 = ((FUNZ_MAN42 || FUNZ_MAN33) && COMANDO_A) || (RICHIESTA_SEL_MORSE_SX_AP || RICHIESTA_SEL_MORSE_DX_AP);


// MANUALE: RESET Flag di APERTURA/CHIUSURA morse se funzioni manuali o selettori non attivi
if(!MORSE_DA_CH_MAN && !MORSE_DA_AP_MAN)
	{
	F_M_CH_MORSA_10 = F_M_AP_MORSA_10 = 0; 
	F_M_CH_MORSA_11 = F_M_AP_MORSA_11 = 0; 
	F_M_CH_MORSA_12 = F_M_AP_MORSA_12 = 0; 
	F_M_CH_MORSA_13 = F_M_AP_MORSA_13 = 0; 
	F_M_CH_MORSA_14 = F_M_AP_MORSA_14 = 0; 
	F_M_CH_MORSA_15 = F_M_AP_MORSA_15 = 0; 
	}

// MANUALE: Attivazione flag di CHIUSURA_IN_BASSA_FORZA morse , da funzioni manuali o selettori  
if (MORSA_DA_CH_MAN_10 || MORSA_DA_CH_MAN_11 || MORSA_DA_CH_MAN_12 || MORSA_DA_CH_MAN_13 || MORSA_DA_CH_MAN_14 || MORSA_DA_CH_MAN_15)  
{
	if (MORSA_DA_CH_MAN_10)  {F_M_CH_MORSA_10 = 1; F_M_AP_MORSA_10 = 0;} else if (MORSA_10_AP) {F_M_CH_MORSA_10 = 0; F_M_AP_MORSA_10 = 1;}
	if (MORSA_DA_CH_MAN_11)  {F_M_CH_MORSA_11 = 1; F_M_AP_MORSA_11 = 0;} else if (MORSA_11_AP) {F_M_CH_MORSA_11 = 0; F_M_AP_MORSA_11 = 1;}
	if (MORSA_DA_CH_MAN_12)  {F_M_CH_MORSA_12 = 1; F_M_AP_MORSA_12 = 0;} else if (MORSA_12_AP) {F_M_CH_MORSA_12 = 0; F_M_AP_MORSA_12 = 1;}
	if (MORSA_DA_CH_MAN_13)  {F_M_CH_MORSA_13 = 1; F_M_AP_MORSA_13 = 0;} else if (MORSA_13_AP) {F_M_CH_MORSA_13 = 0; F_M_AP_MORSA_13 = 1;}
	if (MORSA_DA_CH_MAN_14)  {F_M_CH_MORSA_14 = 1; F_M_AP_MORSA_14 = 0;} else if (MORSA_14_AP) {F_M_CH_MORSA_14 = 0; F_M_AP_MORSA_14 = 1;}
	if (MORSA_DA_CH_MAN_15)  {F_M_CH_MORSA_15 = 1; F_M_AP_MORSA_15 = 0;} else if (MORSA_15_AP) {F_M_CH_MORSA_15 = 0; F_M_AP_MORSA_15 = 1;}
}

// MANUALE: Attivazione flag di APERTURA_IN_ALTA_FORZA morse_SX, da funzioni manuali o selettori
if (MORSA_DA_AP_MAN_10)  {F_M_AP_MORSA_10 = 1;  F_M_CH_MORSA_10 = 0;}
if (MORSA_DA_AP_MAN_11)  {F_M_AP_MORSA_11 = 1;  F_M_CH_MORSA_11 = 0;}
if (MORSA_DA_AP_MAN_12)  {F_M_AP_MORSA_12 = 1;  F_M_CH_MORSA_12 = 0;}
if (MORSA_DA_AP_MAN_13)  {F_M_AP_MORSA_13 = 1;  F_M_CH_MORSA_13 = 0;}
if (MORSA_DA_AP_MAN_14)  {F_M_AP_MORSA_14 = 1;  F_M_CH_MORSA_14 = 0;}
if (MORSA_DA_AP_MAN_15)  {F_M_AP_MORSA_15 = 1;  F_M_CH_MORSA_15 = 0;}



/*-------------------------------------------------------------------------------------*/
/*---------------------- Fine operazioni d'apertura/chiusura morse --------------------*/
/*-------------------------------------------------------------------------------------*/

//ENDOUT:;

}

else
        {
		}



}
