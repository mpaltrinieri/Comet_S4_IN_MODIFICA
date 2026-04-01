/*
        --------------------------------------------------------------
        TITOLO:         CAMBUT
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione c.ut. generale
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    cambut(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          SBLOC_UT_O         Sbloccagggio utensile su mandrino
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         UTSCON_AL          All. utensile sconosciuto su mandrino
                        UTSCON_FAL         Flag utensile sconosciuto su mandrino
                        UTSCON_MS          Mess.utensile sconosciuto su mandrino
                        UTSCON_FMS         Flag utensile sconosciuto su mandrino
                        R[R_ACT_TOOL]      Utensile attivo su mandrino
                        R[R_NEXT_TOOL]     Utensile chiamato per cambio utensili
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           30-08-2000
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

void    cambut(void)

{



/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
        R[R_UTSCON] = UTSCON;
        }

/*************** RESET ALLARMI Cambio Utensili ***************/
if (RESET_ALL || RESET_MC)
        {
			ERR_UT_IN_MEM_FAL = 0;
        }

/**** LETTURA UTENSILE ATTUALE ****/
        {
        long  act_tool;
        float lng_tool;
        float rad_tool;

        read_var (VL_LONG, 4091, -1, -1, &act_tool);      /* 4091 = utensile attuale */
        read_var (VL_FLOT, 4090, -1, -1, &lng_tool);      /* 4090 = lunghezza utensile attuale */
        read_var (VL_FLOT, 4089, -1, -1, &rad_tool);      /* 4089 = raggio utensile attuale */

        R[R_ACT_TOOL] = (float)act_tool;
        R[R_LNG_TOOL] = (float)lng_tool;
        R[R_RAD_TOOL] = (float)rad_tool;
        }


// RESET Disabilitazione temporanea allarmi ut. per carico/scarico ut. atomatico
if ( Mg_MC(67) || RESET_MC )
{
	Mr_MC(66);
	Mr_MC(67);
}

// Disabilitazione temporanea allarmi ut. per carico/scarico ut. atomatico
DISAB_ALL_UT_CAR_SCAR = Mg_MC(66);


// Reset M di sbloccaggio ut. per SCARICO utensile automatico tramite mandrino:
if (P_PRESSIONE_PLS_START_CYCLE && !(UT_SGANC_I) && !(UT_AGGAN_I) )
	Mr_MC(54);

// Reset M di sbloccaggio ut. per CARICO utensile automatico tramite mandrino:
if (P_PRESSIONE_PLS_START_CYCLE && !(UT_SGANC_I) &&  (UT_AGGAN_I) )
	Mr_MC(55);

// Sbloccaggio ut. per Carico/Scarico utensile automatico tramite mandrino
SBLOC_UT_CAR_SCAR_AUT = 
	( (Mg_MC(54)) /*&& COMANDO_B*/ ) ||
	( (Mg_MC(55)) /*&& COMANDO_B*/ ) ;



/**** UTENSILE SCONOSCIUTO SU MANDRINO ****/
if ( SBLOC_UT_O && !Mg_MC(72) && !Mg_MC(74) && !DISAB_ALL_UT_CAR_SCAR )
        R[R_UTSCON] = (float)1;

if ( SBLOC_UT_O && ( Mg_MC(72) || Mg_MC(74) ||  DISAB_ALL_UT_CAR_SCAR ) )
        R[R_UTSCON] = (float)0;


UTSCON_ACT = (int)R[R_UTSCON];
UTSCON     = (int)R[R_UTSCON];

/* Messaggio utensile sconosciuto su mandrino */
UTSCON_FMS = UTSCON_ACT /*&& !AUTO*/;		// eliminato: AUTO 

/* Allarme utensile sconosciuto su mandrino  */
UTSCON_FAL = UTSCON_ACT && AUTO ;

// Incongruenza tra utensile teoricamente presente e sensore di presenza utensile (S3 - TOOL_PRES_I)
COND_ERR_UT_IN_MEM = !GEST_OPERATORE_MAN && !DISAB_ALL_UT_CAR_SCAR && !(Mg_MC(72)) && !(Mg_MC(74)) &&
(
	(!UTSCON && (R[R_ACT_TOOL] > 0.5) && !TOOL_AGGANCIATO) ||
	(!UTSCON && (R[R_ACT_TOOL] < 0.5) &&  TOOL_AGGANCIATO)
);

tS(TS_ERR_UT_IN_MEM, (unsigned char)(COND_ERR_UT_IN_MEM));

// Allarme incongruenza tra utensile teoricamente presente e sensore di presenza utensile (S3)
if (RP_TSuppl[TS_ERR_UT_IN_MEM])
	ERR_UT_IN_MEM_FAL = 1;

/*****************************************************************/
/**** Gestione sequenza assistita manuale per cambio utensili ****/
/*****************************************************************/

// Condizioni d'inizio ciclo cambio ut assistito
COND_START_CAMBUT_MAN = /*UOMO_MORTO_I &&*/ !CICLO_CAMBUT_MAN && ASSE_W_SU_FCNEG;
COND_END_CAMBUT_MAN	=   /*UOMO_MORTO_I &&*/ !CICLO_CAMBUT_MAN && ASSE_W_SU_FCPOS && ASSE_Z_SU_FCPOS && (R[R_QUOTA_Y]>(R[R_QUOTA_Y_FUOING_MAG]-2)) && (R[R_QUOTA_Y]<R[R_QUOTA_Y_FUOING_MAG]);

// Inizio ciclo cambio ut assistito
if	(MANO && FUNZ_MAN19 && 
	 ((COND_START_CAMBUT_MAN && COMANDO_B) || (COND_END_CAMBUT_MAN && COMANDO_A)))
		{	
		if (COMANDO_B) 
				{
				R[R_CAMB_MAN] = (float) 1;
				}
		
		if (COMANDO_A) 
				{
				R[R_CAMB_MAN] = (float) 2;
				}
		
		CICLO_CAMBUT_MAN = 1;
		CICLO_CAMBUT_REQ = 1;
		}

// Azzero richiesta ciclo
if (Mg_MC(114) || Mg_MC(115) || RESET_MC )
        CICLO_CAMBUT_REQ = 0;

//// Azzero memoria ciclo attivo
//if (Mg_MC(115) ||RESET_MC )
//		{
//		Mr_MC(114);
//		Mr_MC(115);
//		}	

// Interruzione o fine del ciclo di cambio ut. assistito (seconda parte)
//if	( ( Mg_MC(115) || RESET_MC || !MANO || !FUNZ_MAN19 || (!COMANDO_AUX_A && !COMANDO_AUX_B) ) && !CICLO_CAMBUT_MAN )
if	( RESET_MC )
		{
		Mr_MC(114);		// SPOSTATA QUI PER NON PERDER LA CONDIZIONE DI RICH_RESET
		Mr_MC(115);
		}

// Interruzione o fine del ciclo di cambio ut. assistito (prima parte)
if	(Mg_MC(115) || RESET_MC || !MANO || !FUNZ_MAN19 || (!COMANDO_AUX_A && !COMANDO_AUX_B) /*|| (!(UOMO_MORTO_I))*/ )
		{
		////Mr_MC(114);		// SPOSTATA SU NON PERDER LA CONDIZIONE DI RICH_RESET
		////Mr_MC(115);		// "
		CICLO_CAMBUT_MAN = 0;
		R[R_CAMB_MAN] = (float) 0;
		}


// Led funzioni manuali
CICLO_CAMBUT_FUNES_A = FUNZ_MAN19 &&
	(COND_START_CAMBUT_MAN || CICLO_CAMBUT_MAN && COMANDO_A && P_OSCILLATORE);

CICLO_CAMBUT_FUNES_B = FUNZ_MAN19 &&
	(COND_END_CAMBUT_MAN   || CICLO_CAMBUT_MAN && COMANDO_B && P_OSCILLATORE);


}


