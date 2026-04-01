/*
        --------------------------------------------------------------
        TITOLO:         uscite_standard
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gest. uscita.stand.: componente con due uscite
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    gestione_uscite(void)
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
        DATA:			13-09-2005
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo - Borsari Guido
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------


*/


#include        "all.inc"

void    uscite_standard(void)

{

if (COMP_PRES)
{

/**** RESET ALLARMI ****/
if (RESET_ALL || RESET_MC)
        {
        OUTPUT_1_FAL =		0;
        OUTPUT_1A_FAL =		0;
        OUTPUT_1B_FAL =		0;
        OUTPUT_2_FAL =		0;
        OUTPUT_2A_FAL =		0;
        OUTPUT_2B_FAL =		0;
		DISFUNZIONE_FAL	=	0;
		}

/******************************************************************************/
/*************** Componente generico con 2 uscite e 2 ingressi ****************/
/******************************************************************************/

/***** CONSENSO FUNZIONAMENTO : Condizioni di sicurezza *****/
CON_OUTPUT_1 = COND_MACCHINA_1 && (AUTORITENUTA && !AUX_2 || !AUTORITENUTA && !OUTPUT_2) ;
CON_OUTPUT_2 = COND_MACCHINA_2 && (AUTORITENUTA && !AUX_1 || !AUTORITENUTA && !OUTPUT_1) ;


//************** ALLARMI ********************************************************

// Allarme Uscita 1 *************************************************************

if ( !DIAGNOSTICA_2_IN && (TIMEOUT_ALL_1 && COND_ALL_1) )
        OUTPUT_1_FAL = 1;	// Solo 1 input presente, diagnostica standard

if ( DIAGNOSTICA_2_IN && (TIMEOUT_ALL_1 && COND_ALL_1 && !INPUT_2) )
        OUTPUT_1A_FAL = 1;	// Probabile movim. effettuato e sensore input1 rotto

if ( DIAGNOSTICA_2_IN && (TIMEOUT_ALL_1 && COND_ALL_1 && INPUT_2) )
        OUTPUT_1B_FAL = 1;	// Probabile movim. non effettuato ed EV1 rotta


// Allarme Uscita 2 *************************************************************

if ( !DIAGNOSTICA_2_IN && (TIMEOUT_ALL_2 && COND_ALL_2) )
        OUTPUT_2_FAL = 1;	// Solo 1 input presente, diagnostica standard

if ( DIAGNOSTICA_2_IN && (TIMEOUT_ALL_2 && COND_ALL_2 && !INPUT_1) )
        OUTPUT_2A_FAL = 1;	// Probabile movim. effettuato e sensore input2 rotto

if ( DIAGNOSTICA_2_IN && (TIMEOUT_ALL_2 && COND_ALL_2 && INPUT_1) )
        OUTPUT_2B_FAL = 1;	// Probabile movim. non effettuato ed EV2 rotta


// Allarme finecorsa contemporanei **********************************************
if (TIMEOUT_DISF && COND_DISF)
        DISFUNZIONE_FAL = 1;


/* Blocchi sulle uscite dovuti mancanza consensi o ad allarmi */
ALLAUT_OUTPUT_1	= !CON_OUTPUT_1 || DISFUNZIONE_FAL;
ALLMAN_OUTPUT_1	= !CON_OUTPUT_1;	
ALLAUT_OUTPUT_2	= !CON_OUTPUT_2 || DISFUNZIONE_FAL;
ALLMAN_OUTPUT_2	= !CON_OUTPUT_2; 


/************** CONDIZIONI MANUALI **************/
// eliminato COND_MACCHINA_1/2 per analogia a AUT_OUTPUT_1 e per chiarezza, tanto è ridondante: se COND_MACCHINA_1=0 -> CON_OUTPUT_1=0 -> ALLMAN_OUTPUT_1=1 -> AUX_1=0 
MAN_OUTPUT_1 = MANO && MAN_1/* && COND_MACCHINA_1*/;	
MAN_OUTPUT_2 = MANO && MAN_2/* && COND_MACCHINA_2*/;


/**** Reset Funzioni M ****/      
if (INPUT_1 && AUT_OUTPUT_1 || !AUTO_CICLOMAN)			M_1=0;
if (INPUT_2 && AUT_OUTPUT_2 || !AUTO_CICLOMAN)			M_2=0;

if ((!AUT_OUTPUT_1 && !AUT_OUTPUT_2) || !AUTO_CICLOMAN)	M_0=0;


/************** CONDIZIONI AUTOMATICHE **************/
AUT_OUTPUT_1 = (M_1 || AUT_OUTPUT_1) && AUTO_CICLOMAN && !RESET_CONDAUTO && !M_2 && !M_0;
AUT_OUTPUT_2 = (M_2 || AUT_OUTPUT_2) && AUTO_CICLOMAN && !RESET_CONDAUTO && !M_1 && !M_0;

/* Hold ASSI */
HOLD_COMPONENTE = OUTPUT_1_FAL || OUTPUT_1A_FAL || OUTPUT_1B_FAL ||
				  OUTPUT_2_FAL || OUTPUT_2A_FAL || OUTPUT_2B_FAL ||
				  DISFUNZIONE_FAL;


/************** USCITE **************/
// Alcune uscite le comando con l'autoaggancio sull'arrivo dell'ingresso
// Altre uscite sono dirette senza autoaggancio


// aux delle out validi in tutte le condizioni
AUX_1 = (MAN_OUTPUT_1 && !ALLMAN_OUTPUT_1)||
        (AUT_OUTPUT_1 && !ALLAUT_OUTPUT_1);

AUX_2 = (MAN_OUTPUT_2 && !ALLMAN_OUTPUT_2)||
        (AUT_OUTPUT_2 && !ALLAUT_OUTPUT_2);


// Nel passaggio Auto-->Man l'uscita cade e viene messa a 0
if (AUTORITENUTA == 0)
	{
	OUTPUT_1 = AUX_1 && !AUX_2;
	OUTPUT_2 = AUX_2 && !AUX_1;
	}
// Nel passaggio Auto-->Man l'uscita resta a 1
if (AUTORITENUTA == 1)
	{
	OUTPUT_1 = (AUX_1 || OUTPUT_1 && INPUT_1) && !AUX_2;
	OUTPUT_2 = (AUX_2 || OUTPUT_2 && INPUT_2) && !AUX_1;
	}
// Con autoritenuta = 2 : Nel passaggio Auto-->Man l'uscita resta a 1, anche se cade l'ingresso.
if (AUTORITENUTA == 2)
	{
	OUTPUT_1 = (AUX_1 || OUTPUT_1) && !AUX_2;
	OUTPUT_2 = (AUX_2 || OUTPUT_2) && !AUX_1;
	}

// Con autoritenuta = 3 : come la precedente(2) ma in piu l'autoritenuta si resetta se cadono le condizioni elettriche o pneumatiche, in modo che al loro ritorno non si generi un movimento imprevisto con EV monostabili
if (AUTORITENUTA == 3)
	{
	OUTPUT_1 = ( AUX_1 || (OUTPUT_1 && RN_PRES_ARIA && MACCHINA_PRONTA) ) && !AUX_2;
	OUTPUT_2 = ( AUX_2 || (OUTPUT_2 && RN_PRES_ARIA && MACCHINA_PRONTA) ) && !AUX_1;
	}


/**************** FUNZIONE ESEGUITA ***************************/
/* Per definizione il PLS.B esegue il movimento di primo cambio stato */
COMPONENTE_FUNES_B = FUNZ_MANUALE && (INPUT_1 || P_OSCILLATORE && OUTPUT_1);
COMPONENTE_FUNES_A = FUNZ_MANUALE && (INPUT_2 || P_OSCILLATORE && OUTPUT_2);

}

else
        {
        OUTPUT_1_FAL =		 0;
        OUTPUT_1A_FAL =		 0;
        OUTPUT_1B_FAL =		 0;
        OUTPUT_2_FAL =		 0;
        OUTPUT_2A_FAL =		 0;
        OUTPUT_2B_FAL =		 0;
		DISFUNZIONE_FAL =	 0;
		COMPONENTE_FUNES_A = 0;
		COMPONENTE_FUNES_B = 0;
        M_1				=	 0;	// Evita di dover condizionare i comandi CNC alla presenza del componente
        M_2				=	 0;	// Evita di dover condizionare i comandi CNC alla presenza del componente
        }


}



