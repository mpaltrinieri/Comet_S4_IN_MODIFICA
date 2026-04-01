/*
        --------------------------------------------------------------
        TITOLO:         UTENSILI
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione utensili generica
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    utensili(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:       
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:      
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 6.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           29-10-2003
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/



#include        "all.inc"

void utensili(void)
{

/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
        }


// Numero utensili magazzino
if(CONF_MAGUT_10POSTI && !CONF_MAGUT_12POSTI)  
	{
	R[R_NUM_TOT_UT_MAG] = 10.5;		// Numero TOTALE utensili del magazzino                (piu soglia di 0.5 per agevolare verifiche)
	R[R_NUM_UT_MAG_INF] = 5.5;		// Numero utensili della fila inferiore del magazzino  (piu soglia di 0.5 per agevolare verifiche)
	}
if(!CONF_MAGUT_10POSTI && CONF_MAGUT_12POSTI)  
	{
	R[R_NUM_TOT_UT_MAG] = 12.5;		// Numero TOTALE utensili del magazzino                (piu soglia di 0.5 per agevolare verifiche)
	R[R_NUM_UT_MAG_INF] = 6.5;		// Numero utensili della fila inferiore del magazzino  (piu soglia di 0.5 per agevolare verifiche)
	}


/**** CONSENSO AL PRELIEVO E DEPOSITO DA MAGAZZINO****/
//CONS_INIZIO_DEP_PRE = MAGUT_IND_I;
CONS_INIZIO_DEP_PRE = 1;

/**** CODIFICA UTENSILE SU MANDRINO ****/
UT0_ACT = R[R_ACT_TOOL] == 0;

/**** CICLO DEPOSITO UTENSILE IN MANUALE ****/
CICLO_DEPUT = 
	CICLO_DEP_UT1 || CICLO_DEP_UT2 || CICLO_DEP_UT3 || CICLO_DEP_UT4 || 
	CICLO_DEP_UT5 || CICLO_DEP_UT6 || CICLO_DEP_UT7 || CICLO_DEP_UT8 ||
	CICLO_DEP_UT9 || CICLO_DEP_UT10 || CICLO_DEP_UT11 || CICLO_DEP_UT12;

if (CICLO_DEPUT)
        CICLO_DEPUT_REQ = 1;
if (Mg_MC(72) || RESET_MC)
        CICLO_DEPUT_REQ = 0;


/**** CICLO PRELIEVO UTENSILE IN MANUALE ****/
CICLO_PRELUT = 
	CICLO_PREL_UT1 || CICLO_PREL_UT2 || CICLO_PREL_UT3 || CICLO_PREL_UT4 || 
	CICLO_PREL_UT5 || CICLO_PREL_UT6 || CICLO_PREL_UT7 || CICLO_PREL_UT8 ||
	CICLO_PREL_UT9 || CICLO_PREL_UT10 || CICLO_PREL_UT11 || CICLO_PREL_UT12;

if (CICLO_PRELUT)
        CICLO_PRELUT_REQ = 1;
if (Mg_MC(74) || RESET_MC)
        CICLO_PRELUT_REQ = 0;


/**** Bit comuni a tutti gli utensili : appoggio per maggior chiarezza ****/
MANDRINO_SENZA_UT	= !UT_AGGAN_I;
    

/******************************************************************************/
/******************************* Utensile 1 ***********************************/
/******************************************************************************/
// Utensile al posto n.1 Magazzino //

NUMERO_UT				=	1;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN21;
UT_PRES_FAL				=	UT1_PRES_FAL;
UT_NOPRES_FAL			=	UT1_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT1;

utensili_standard ();

// Bit d'uscita 
UT1_PRES_FAL			=	UT_PRES_FAL;
UT1_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT1			=	GESTIONE_UT;

 
// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 1) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 2 ***********************************/
/******************************************************************************/
// Utensile al posto n.2 Magazzino //

NUMERO_UT				=	2;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN22;
UT_PRES_FAL				=	UT2_PRES_FAL;
UT_NOPRES_FAL			=	UT2_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT2;

utensili_standard ();

// Bit d'uscita 
UT2_PRES_FAL			=	UT_PRES_FAL;
UT2_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT2			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 2) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 3 ***********************************/
/******************************************************************************/
// Utensile al posto n.3 Magazzino //

NUMERO_UT				=	3;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN23;
UT_PRES_FAL				=	UT3_PRES_FAL;
UT_NOPRES_FAL			=	UT3_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT3;

utensili_standard ();

// Bit d'uscita 
UT3_PRES_FAL			=	UT_PRES_FAL;
UT3_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT3			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 3) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 4 ***********************************/
/******************************************************************************/
// Utensile al posto n.4 Magazzino //

NUMERO_UT				=	4;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN24;
UT_PRES_FAL				=	UT4_PRES_FAL;
UT_NOPRES_FAL			=	UT4_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT4;

utensili_standard ();

// Bit d'uscita 
UT4_PRES_FAL			=	UT_PRES_FAL;
UT4_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT4			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 4) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 5 ***********************************/
/******************************************************************************/
// Utensile al posto n.5 Magazzino //

NUMERO_UT				=	5;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN25;
UT_PRES_FAL				=	UT5_PRES_FAL;
UT_NOPRES_FAL			=	UT5_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT5;

utensili_standard ();

// Bit d'uscita 
UT5_PRES_FAL			=	UT_PRES_FAL;
UT5_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT5			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 5) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 6 ***********************************/
/******************************************************************************/
// Utensile al posto n.6 Magazzino //

NUMERO_UT				=	6;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN26;
UT_PRES_FAL				=	UT6_PRES_FAL;
UT_NOPRES_FAL			=	UT6_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT6;

utensili_standard ();

// Bit d'uscita 
UT6_PRES_FAL			=	UT_PRES_FAL;
UT6_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT6			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 6) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 7 ***********************************/
/******************************************************************************/
// Utensile al posto n.7 Magazzino //

NUMERO_UT				=	7;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN27;
UT_PRES_FAL				=	UT7_PRES_FAL;
UT_NOPRES_FAL			=	UT7_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT7;

utensili_standard ();

// Bit d'uscita 
UT7_PRES_FAL			=	UT_PRES_FAL;
UT7_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT7			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 7) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 8 ***********************************/
/******************************************************************************/
// Utensile al posto n.8 Magazzino //

NUMERO_UT				=	8;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN28;
UT_PRES_FAL				=	UT8_PRES_FAL;
UT_NOPRES_FAL			=	UT8_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT8;

utensili_standard ();

// Bit d'uscita 
UT8_PRES_FAL			=	UT_PRES_FAL;
UT8_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT8			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 8) 
			{	
			goto saltautensili;
			}


/******************************************************************************/
/******************************* Utensile 9 ***********************************/
/******************************************************************************/
// Utensile al posto n.9 Magazzino //

NUMERO_UT				=	9;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN29;
UT_PRES_FAL				=	UT9_PRES_FAL;
UT_NOPRES_FAL			=	UT9_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT9;

utensili_standard ();

// Bit d'uscita 
UT9_PRES_FAL			=	UT_PRES_FAL;
UT9_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT9			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 9) 
			{	
			goto saltautensili;
			}	


/******************************************************************************/
/******************************* Utensile 10 **********************************/
/******************************************************************************/
// Utensile al posto n.10 Magazzino //

NUMERO_UT				=	10;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN30;
UT_PRES_FAL				=	UT10_PRES_FAL;
UT_NOPRES_FAL			=	UT10_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT10;

utensili_standard ();

// Bit d'uscita 
UT10_PRES_FAL			=	UT_PRES_FAL;
UT10_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT10			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 10) 
			{	
			goto saltautensili;
			}


/******************************************************************************/
/******************************* Utensile 11 **********************************/
/******************************************************************************/
// Utensile al posto n.11 Magazzino //

NUMERO_UT				=	11;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN31;
UT_PRES_FAL				=	UT11_PRES_FAL;
UT_NOPRES_FAL			=	UT11_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT11;

utensili_standard ();

// Bit d'uscita 
UT11_PRES_FAL			=	UT_PRES_FAL;
UT11_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT11			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 11) 
			{	
			goto saltautensili;
			}

			
/******************************************************************************/
/******************************* Utensile 12 **********************************/
/******************************************************************************/
// Utensile al posto n.12 Magazzino //

NUMERO_UT				=	12;
UT_ESISTENTE			=	(NUMERO_UT < R[R_NUM_TOT_UT_MAG]) && ( (R[R_CKTOOL_PRES]<0.5) || ( NUMERO_UT<(R[R_CKT_NR_PINZA]-0.5) ) || ( NUMERO_UT>(R[R_CKT_NR_PINZA]+0.5) ) );
FUNZ_MAN_UT				=	FUNZ_MAN32;
UT_PRES_FAL				=	UT12_PRES_FAL;
UT_NOPRES_FAL			=	UT12_NOPRES_FAL;

GESTIONE_UT				=	GESTIONE_UT12;

utensili_standard ();

// Bit d'uscita 
UT12_PRES_FAL			=	UT_PRES_FAL;
UT12_NOPRES_FAL			=	UT_NOPRES_FAL;

// Word con bit interni per visualizzazione e debug 
GESTIONE_UT12			=	GESTIONE_UT;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_UTENSILI] == (float) 12) 
			{	
			goto saltautensili;
			}			


// Se è l'ultima istruzione prima della graffa finale serve il ;
saltautensili:;


//ENDOUT:;

//Mg_MC(72) = Mg_MC(72);
//Mg_MC(73) = Mg_MC(73);
//
//Mg_MC(74) = Mg_MC(74);
//Mg_MC(75) = Mg_MC(75);
//
//Mg_MC(76) = Mg_MC(76);
//Mg_MC(77) = Mg_MC(77);
//
//Mg_MC(78) = Mg_MC(78);
//Mg_MC(79) = Mg_MC(79);



GESTIONE_UT1		=GESTIONE_UT1		;
UT1_ACT				=UT1_ACT			;	
UT1_NEXT			=UT1_NEXT			;
UT1_PRESENTE		=UT1_PRESENTE		;
CONS_CICLO_DEP_UT1	=CONS_CICLO_DEP_UT1	;
CICLO_DEP_UT1		=CICLO_DEP_UT1		;
CONS_CICLO_PREL_UT1	=CONS_CICLO_PREL_UT1;	
CICLO_PREL_UT1		=CICLO_PREL_UT1		;
UT1_FUNES_B			=UT1_FUNES_B		;	
UT1_FUNES_A			=UT1_FUNES_A		;	
UT1_DEPOSITATO		=UT1_DEPOSITATO		;
CONDIZIONI_DEP_UT1	=CONDIZIONI_DEP_UT1	;
CONDIZIONI_PRE_UT1	=CONDIZIONI_PRE_UT1	;

GESTIONE_UT2		=GESTIONE_UT2		;
UT2_ACT				=UT2_ACT			;	
UT2_NEXT			=UT2_NEXT			;
UT2_PRESENTE		=UT2_PRESENTE		;
CONS_CICLO_DEP_UT2	=CONS_CICLO_DEP_UT2	;
CICLO_DEP_UT2		=CICLO_DEP_UT2		;
CONS_CICLO_PREL_UT2	=CONS_CICLO_PREL_UT2;	
CICLO_PREL_UT2		=CICLO_PREL_UT2		;
UT2_FUNES_B			=UT2_FUNES_B		;	
UT2_FUNES_A			=UT2_FUNES_A		;	
UT2_DEPOSITATO		=UT2_DEPOSITATO		;
CONDIZIONI_DEP_UT2	=CONDIZIONI_DEP_UT2	;
CONDIZIONI_PRE_UT2	=CONDIZIONI_PRE_UT2	;

GESTIONE_UT3		=GESTIONE_UT3		;
UT3_ACT				=UT3_ACT			;	
UT3_NEXT			=UT3_NEXT			;
UT3_PRESENTE		=UT3_PRESENTE		;
CONS_CICLO_DEP_UT3	=CONS_CICLO_DEP_UT3	;
CICLO_DEP_UT3		=CICLO_DEP_UT3		;
CONS_CICLO_PREL_UT3	=CONS_CICLO_PREL_UT3;	
CICLO_PREL_UT3		=CICLO_PREL_UT3		;
UT3_FUNES_B			=UT3_FUNES_B		;	
UT3_FUNES_A			=UT3_FUNES_A		;	
UT3_DEPOSITATO		=UT3_DEPOSITATO		;
CONDIZIONI_DEP_UT3	=CONDIZIONI_DEP_UT3	;
CONDIZIONI_PRE_UT3	=CONDIZIONI_PRE_UT3	;

GESTIONE_UT4		=GESTIONE_UT4		;
UT4_ACT				=UT4_ACT			;	
UT4_NEXT			=UT4_NEXT			;
UT4_PRESENTE		=UT4_PRESENTE		;
CONS_CICLO_DEP_UT4	=CONS_CICLO_DEP_UT4	;
CICLO_DEP_UT4		=CICLO_DEP_UT4		;
CONS_CICLO_PREL_UT4	=CONS_CICLO_PREL_UT4;	
CICLO_PREL_UT4		=CICLO_PREL_UT4		;
UT4_FUNES_B			=UT4_FUNES_B		;	
UT4_FUNES_A			=UT4_FUNES_A		;	
UT4_DEPOSITATO		=UT4_DEPOSITATO		;
CONDIZIONI_DEP_UT4	=CONDIZIONI_DEP_UT4	;
CONDIZIONI_PRE_UT4	=CONDIZIONI_PRE_UT4	;

GESTIONE_UT5		=GESTIONE_UT5		;
UT5_ACT				=UT5_ACT			;	
UT5_NEXT			=UT5_NEXT			;
UT5_PRESENTE		=UT5_PRESENTE		;
CONS_CICLO_DEP_UT5	=CONS_CICLO_DEP_UT5	;
CICLO_DEP_UT5		=CICLO_DEP_UT5		;
CONS_CICLO_PREL_UT5	=CONS_CICLO_PREL_UT5;	
CICLO_PREL_UT5		=CICLO_PREL_UT5		;
UT5_FUNES_B			=UT5_FUNES_B		;	
UT5_FUNES_A			=UT5_FUNES_A		;	
UT5_DEPOSITATO		=UT5_DEPOSITATO		;
CONDIZIONI_DEP_UT5	=CONDIZIONI_DEP_UT5	;
CONDIZIONI_PRE_UT5	=CONDIZIONI_PRE_UT5	;

GESTIONE_UT6		=GESTIONE_UT6		;
UT6_ACT				=UT6_ACT			;	
UT6_NEXT			=UT6_NEXT			;
UT6_PRESENTE		=UT6_PRESENTE		;
CONS_CICLO_DEP_UT6	=CONS_CICLO_DEP_UT6	;
CICLO_DEP_UT6		=CICLO_DEP_UT6		;
CONS_CICLO_PREL_UT6	=CONS_CICLO_PREL_UT6;	
CICLO_PREL_UT6		=CICLO_PREL_UT6		;
UT6_FUNES_B			=UT6_FUNES_B		;	
UT6_FUNES_A			=UT6_FUNES_A		;	
UT6_DEPOSITATO		=UT6_DEPOSITATO		;
CONDIZIONI_DEP_UT6	=CONDIZIONI_DEP_UT6	;
CONDIZIONI_PRE_UT6	=CONDIZIONI_PRE_UT6	;

GESTIONE_UT7		=GESTIONE_UT7		;
UT7_ACT				=UT7_ACT			;	
UT7_NEXT			=UT7_NEXT			;
UT7_PRESENTE		=UT7_PRESENTE		;
CONS_CICLO_DEP_UT7	=CONS_CICLO_DEP_UT7	;
CICLO_DEP_UT7		=CICLO_DEP_UT7		;
CONS_CICLO_PREL_UT7	=CONS_CICLO_PREL_UT7;	
CICLO_PREL_UT7		=CICLO_PREL_UT7		;
UT7_FUNES_B			=UT7_FUNES_B		;	
UT7_FUNES_A			=UT7_FUNES_A		;	
UT7_DEPOSITATO		=UT7_DEPOSITATO		;
CONDIZIONI_DEP_UT7	=CONDIZIONI_DEP_UT7	;
CONDIZIONI_PRE_UT7	=CONDIZIONI_PRE_UT7	;

GESTIONE_UT8		=GESTIONE_UT8		;
UT8_ACT				=UT8_ACT			;	
UT8_NEXT			=UT8_NEXT			;
UT8_PRESENTE		=UT8_PRESENTE		;
CONS_CICLO_DEP_UT8	=CONS_CICLO_DEP_UT8	;
CICLO_DEP_UT8		=CICLO_DEP_UT8		;
CONS_CICLO_PREL_UT8	=CONS_CICLO_PREL_UT8;	
CICLO_PREL_UT8		=CICLO_PREL_UT8		;
UT8_FUNES_B			=UT8_FUNES_B		;	
UT8_FUNES_A			=UT8_FUNES_A		;	
UT8_DEPOSITATO		=UT8_DEPOSITATO		;
CONDIZIONI_DEP_UT8	=CONDIZIONI_DEP_UT8	;
CONDIZIONI_PRE_UT8	=CONDIZIONI_PRE_UT8	;

GESTIONE_UT9		=GESTIONE_UT9		;
UT9_ACT				=UT9_ACT			;	
UT9_NEXT			=UT9_NEXT			;
UT9_PRESENTE		=UT9_PRESENTE		;
CONS_CICLO_DEP_UT9	=CONS_CICLO_DEP_UT9	;
CICLO_DEP_UT9		=CICLO_DEP_UT9		;
CONS_CICLO_PREL_UT9	=CONS_CICLO_PREL_UT9;	
CICLO_PREL_UT9		=CICLO_PREL_UT9		;
UT9_FUNES_B			=UT9_FUNES_B		;	
UT9_FUNES_A			=UT9_FUNES_A		;	
UT9_DEPOSITATO		=UT9_DEPOSITATO		;
CONDIZIONI_DEP_UT9	=CONDIZIONI_DEP_UT9	;
CONDIZIONI_PRE_UT9	=CONDIZIONI_PRE_UT9	;

GESTIONE_UT10		=GESTIONE_UT10		;
UT10_ACT			=UT10_ACT			;	
UT10_NEXT			=UT10_NEXT			;
UT10_PRESENTE		=UT10_PRESENTE		;
CONS_CICLO_DEP_UT10	=CONS_CICLO_DEP_UT10;
CICLO_DEP_UT10		=CICLO_DEP_UT10		;
CONS_CICLO_PREL_UT10=CONS_CICLO_PREL_UT10;	
CICLO_PREL_UT10		=CICLO_PREL_UT10	;
UT10_FUNES_B		=UT10_FUNES_B		;	
UT10_FUNES_A		=UT10_FUNES_A		;	
UT10_DEPOSITATO		=UT10_DEPOSITATO	;
CONDIZIONI_DEP_UT10	=CONDIZIONI_DEP_UT10;
CONDIZIONI_PRE_UT10	=CONDIZIONI_PRE_UT10;

GESTIONE_UT11		=GESTIONE_UT11		;
UT11_ACT			=UT11_ACT			;	
UT11_NEXT			=UT11_NEXT			;
UT11_PRESENTE		=UT11_PRESENTE		;
CONS_CICLO_DEP_UT11	=CONS_CICLO_DEP_UT11;
CICLO_DEP_UT11		=CICLO_DEP_UT11		;
CONS_CICLO_PREL_UT11=CONS_CICLO_PREL_UT11;	
CICLO_PREL_UT11		=CICLO_PREL_UT11	;
UT11_FUNES_B		=UT11_FUNES_B		;	
UT11_FUNES_A		=UT11_FUNES_A		;	
UT11_DEPOSITATO		=UT11_DEPOSITATO	;
CONDIZIONI_DEP_UT11	=CONDIZIONI_DEP_UT11;
CONDIZIONI_PRE_UT11	=CONDIZIONI_PRE_UT11;

GESTIONE_UT12		=GESTIONE_UT12		;
UT12_ACT			=UT12_ACT			;	
UT12_NEXT			=UT12_NEXT			;
UT12_PRESENTE		=UT12_PRESENTE		;
CONS_CICLO_DEP_UT12	=CONS_CICLO_DEP_UT12;
CICLO_DEP_UT12		=CICLO_DEP_UT12		;
CONS_CICLO_PREL_UT12=CONS_CICLO_PREL_UT12;	
CICLO_PREL_UT12		=CICLO_PREL_UT12	;
UT12_FUNES_B		=UT12_FUNES_B		;	
UT12_FUNES_A		=UT12_FUNES_A		;	
UT12_DEPOSITATO		=UT12_DEPOSITATO	;
CONDIZIONI_DEP_UT12	=CONDIZIONI_DEP_UT12;
CONDIZIONI_PRE_UT12	=CONDIZIONI_PRE_UT12;


}
