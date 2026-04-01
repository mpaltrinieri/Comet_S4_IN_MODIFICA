/*
        --------------------------------------------------------------
        TITOLO:         utensili_standard
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gest. utensili.stand.
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    utensili_standard(void)
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
        DATA:           16-10-2006        
		--------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------


*/


#include        "all.inc"

void    utensili_standard(void)
{


if (UT_ESISTENTE)
{

/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
        }



/*************** RESET ALLARMI MAGAZZINO UTENSILI ***************/
if (RESET_ALL || RESET_MC)
        {
        UT_PRES_FAL   = 0;
        UT_NOPRES_FAL = 0;
        }

/* Reset assoluto per evitare errori */
if (RESET_MC)
        {
        Mr_MC(78);
		Mr_MC(79); 
        Mr_MC(77);
		Mr_MC(76);
        }

/**** CODIFICA UTENSILE SU MANDRINO ****/
UT_ACT = (R[R_ACT_TOOL] == NUMERO_UT);


/**** CODIFICA UTENSILE RICHIESTO ****/
UT_NEXT = (R[R_NEXT_TOOL] == NUMERO_UT);




/**** CARICAMENTO "T" PER CICLO PRELIEVO IN MANUALE ****/
if (CICLO_PREL)
    R[R_NEXT_TOOL] = (float)NUMERO_UT;

// Punto ai parametri R del confmac che contengono le quote mappate del magazzino
// Parametri Magazzino dalla R7190 in poi
OFFSET_R = 7200+( (NUMERO_UT-1)*6 );


/**** CARICAMENTO QUOTE DI CAMBIO UTENSILI ****/
/* Caricamento quote di prelievo/deposito utensile  */
if ( ((UT_ACT || CICLO_DEP)		&& Mg_MC(78)) || 
	 ((UT_NEXT || CICLO_PREL)	&& Mg_MC(79)) )
		{
		R[R_CAMBIOUT_Y]		=	R[OFFSET_R];
		R[R_CAMBIOUT_Z]		=	R[OFFSET_R+1];
		R[R_CAMBIOUT_A]		=	R[OFFSET_R+2];
		R[R_CAMBIOUT_C]		=	R[OFFSET_R+3];
		R[R_CAMBIOUT_W1]	=	R[OFFSET_R+4];
		R[R_CAMBIOUT_W2]	=	R[OFFSET_R+5];
		Mr_MC(78);
		Mr_MC(79);	
		}


/**** Asse W in posizione di verifica presenza utensile ****/
ASSE_W_SU_UT =	( R[R_POS_ATTUALE_W] > (R[OFFSET_R+4]-0.3) )&&
				( R[R_POS_ATTUALE_W] < (R[OFFSET_R+4]+0.3) );

/**** L'utensile richiesto o attuale è presente in magazzino ? ****/

if ( NUMERO_UT > (R[R_NUM_UT_MAG_INF]) )  
	UT_PRESENTE = ASSE_W_SU_UT && TOOL_PRES_SUP_I;		// fila superiore
else
	UT_PRESENTE = ASSE_W_SU_UT && TOOL_PRES_INF_I;		// fila inferiore


/**** CICLO DEPOSITO UTENSILE ****/
CONDIZIONI_DEP = UT_ACT && !UTSCON_ACT;

CONS_CICLO_DEP = CONS_INIZIO_DEP_PRE && CONDIZIONI_DEP || Mg_MC(72);

CICLO_DEP = MANO && FUNZ_MAN_UT && COMANDO_A && CONS_CICLO_DEP;


/* Allarme utensile impossibile da depositare */
if (UT_ACT && Mg_MC(76) && AUTO_CICLOMAN && (!CONDIZIONI_DEP || UT_PRESENTE))
        UT_PRES_FAL = 1;


/* Reset funzione M di verifica possibilità di deposito */
if (UT_ACT && CONDIZIONI_DEP && !UT_PRES_FAL)  
        Mr_MC(76);


/* Ciclo deposito eseguito */
if (Mg_MC(73))
		{
        Mr_MC(72);
        Mr_MC(73);
        }


/**** CICLO PRELIEVO UTENSILE ****/
CONDIZIONI_PRE =	MANDRINO_SENZA_UT && 
					(UT0_ACT || UTSCON_ACT) ;
					//&& UT_PRESENTE; 

CONS_CICLO_PREL =	CONS_INIZIO_DEP_PRE && CONDIZIONI_PRE || Mg_MC(74);

CICLO_PREL = MANO && FUNZ_MAN_UT && COMANDO_B && CONS_CICLO_PREL;

/* Allarme utensile impossibile da prelevare */
if (UT_NEXT && Mg_MC(77) && AUTO_CICLOMAN && (!CONDIZIONI_PRE || !UT_PRESENTE) )
        UT_NOPRES_FAL = 1;

/* Reset funzione M di verifica possibilità di prelievo */
if (UT_NEXT && CONDIZIONI_PRE && !UT_NOPRES_FAL)
        Mr_MC(77);

/* Ciclo prelievo eseguito */
if (Mg_MC(75) && UT_ACT)
        {
        Mr_MC(74);
        Mr_MC(75);
		//UT_PRESENTE = 0;
        }

/**************** FUNZIONE ESEGUITA ***************************/
UT_FUNES_B = ((Mg_MC(74) && UT_NEXT && P_OSCILLATORE || UT_ACT && !UTSCON_ACT) && FUNZ_MAN_UT);
UT_FUNES_A = ((Mg_MC(72) && UT_ACT && P_OSCILLATORE || UT_PRESENTE) && FUNZ_MAN_UT);

}

else
        {
        UT_PRES_FAL   = 0;
        UT_NOPRES_FAL = 0;
		UT_FUNES_B = 0;
		UT_FUNES_A = 0;
		CICLO_PREL = 0;
		CICLO_DEP = 0;
		UT_ACT = 0;
		UT_NEXT = 0;
		}


}
