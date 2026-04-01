/*
        --------------------------------------------------------------
        TITOLO:         MULTIPEZZO
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione funzionamento macchina in SINGOLO / MULTIPEZZO
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    MULTIPEZZO (void)
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
        DATA:           30-08-2006
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

void    multipezzo(void)

{

if (CONF_MULTIPEZZO)
{

/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
        }


/***************************************************************/
/**************** ESECUZIONE PROGRAMMA SIMULATO ****************/
/***************************************************************/
if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
{
	if ( (Mg_MC(81)) && (DELAY_SIMU_ATTESA_SING == 0) )
	{
		Mr_MC(81);  /* resetta blocco lettore attesa morse aperte/chiuse */
		R[R_ATTESA_CONFERMA] = (float)0;
	}

	//SIMULAZIONE ATTESA PER HDRILL:
	if( !(Mg_MC(81)) ) DELAY_SIMU_ATTESA_SING = 125;    // 125 cicli di plc corrispondono a 1 secondo
	else if(DELAY_SIMU_ATTESA_SING>0) DELAY_SIMU_ATTESA_SING--;
}


/**** FUNZIONAMENTO IN MULTIPEZZO : unico possibile ****/
if (Mg_MC(80) && AUTO && CICLO_MULTI)
        {
        SINGOLO_ON = 1;
        Mr_MC(80);
        }

// Azzeramento delle funzioni multipezzo
if (Mg_MC(83) && SINGOLO_ON || RESET_MC)
        {
        SINGOLO_ON = 0;
        Mr_MC(83);
        ZONA_OK_LAV = 0;
        ZONA_OK_CAR = 0;
	    }

//**************** PARTE AGGIUNTA PER PASSARE STATO MACCHINA IN WAITING PER OPCUA ************
if(Mg_MC(81))
{
	R[R_STATO_MACCH_HDRILL_TO_PLC] = MACH_STATUS_WAIT;  // macchina in stato di attesa conferma carico / scarico
}


/**** Condizioni comuni ****/
CAR_MULTI_IN_CORSO		= Mg_MC(81) && (R[R_END_SX] == 1) && BAT_SX1_DX4_MOB_IN_POS_OK;
SCA_MULTI_IN_CORSO		= Mg_MC(81) && ((R[R_END_SX] == 2) || (R[R_END_SX] == 5));


/**** CONFERMA MACCHINA PRONTA AL LAVORO ****/
/* Conferma per scarico pezzo */
/* Lo scarico è sempre fatto con l'M81 anche per la versione PH*/

if (SCA_MULTI_IN_CORSO && PRESSIONE_NORM && ((TUTTE_LE_MORSE_AP || (MORSE_NECESSARIE_AP && (R[R_END_SX] == 5)) || (R[R_GESTMORS_OPER] == 1))))
        {
        Mr_MC(81);

		R[R_ATTESA_CONFERMA] = (float)0;
		R[R_STATO_MACCH_HDRILL_TO_PLC] = MACH_STATUS_POSITIONING;  // macchina in stato di posizionamento assi
        }


// Ciclo normale : pressione sui fronti di salita
PRESSIONE_NORM = (DP_PRESSIONE_PLS_START_CYCLE || DP_START_SX || DP_START_DX);


// In multipezzo un qualsiasi pulsante di conferma è accettato
PEZZI_CARICATI_MULTI =  
		CAR_MULTI_IN_CORSO && PRESSIONE_NORM &&
		(MORSE_NECESSARIE_MULTI_CH || (R[R_GESTMORS_OPER]>0.5)) ;


/* Conferma per carico pezzo  */
if (SINGOLO_ON && PEZZI_CARICATI_MULTI)
        
		{
        Mr_MC(81);

        R[R_ATTESA_CONFERMA] = (float)0;
		R[R_STATO_MACCH_HDRILL_TO_PLC] = MACH_STATUS_POSITIONING;  // macchina in stato di posizionamento assi

		ZONA_OK_LAV = 1;
		ZONA_OK_CAR = 0;
		}


/**** Fine operazioni ****/
if (Mg_MC(85))
        {
        ZONA_OK_LAV = 0;
        ZONA_OK_CAR = 0;
        Mr_MC(85);
        }




/**** Gestione Oltremisura : alza battute solo con il selettore ****/
if (CAR_MULTI_IN_CORSO && (R[R_SOLBAT_OPER] == 1) && (R[R_POSBAT_VERT_SX1]) && SEL_SBLOC_MORSE_SX_I)
	{
	PLCM116 = 1;	// Alza a richiesta battuta SX1
	}

if (CAR_MULTI_IN_CORSO && (R[R_SOLBAT_OPER] == 1) && (R[R_POSBAT_VERT_DX4]) && SEL_SBLOC_MORSE_DX_I)
	{
	PLCM122 = 1;	// Alza a richiesta battuta DX4
	}


}

}









