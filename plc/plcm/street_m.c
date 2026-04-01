/*
        --------------------------------------------------------------
        TITOLO:         STREET_M
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione percorso assi
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    street_m(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          R[R_ZPIU]         Finecorsa positivo asse Z
                        R[R_YPIU]         Finecorsa positivo asse Y
                        R[R_YMENO]        Finecorsa negativo asse Y
                        R[R_SPACE_FREE]   Spazio lasciato tra ingomro pezzo e punta mandrino
        --------------------------------  ------------------------------
        --------------------------------  ------------------------------
        OUTPUT:         R[R_ZOUT]         Quota asse Z fuori ingombro
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           30-08-2000
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Pecchi Andrea
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"


void    street_m(void)


{
//////////double APP_LNG_TOOL;
//////////
//////////
///////////**** CALCOLO QUOTA DI FUORI INGOMBRO PER ASSE Z ****/
//////////if (!UT0_ACT)
//////////   {
//////////    APP_LNG_TOOL = R[R_LNG_TOOL];
//////////
//////////	if (APP_LNG_TOOL < R[R_DIM_TOOL])
//////////		APP_LNG_TOOL = R[R_DIM_TOOL];
//////////
//////////	 
//////////    R[R_ZOUT_CALCOLATO] = 
//////////		(float)sqrt
//////////		(((R[R_OFFSET_Y_MAND]+R[R_RAD_TOOL]+R[R_OFFSET_MANDR_B_C])*(R[R_OFFSET_Y_MAND]+R[R_RAD_TOOL]+R[R_OFFSET_MANDR_B_C])) + 
//////////		((R[R_OFFSET_Z_MAND]+APP_LNG_TOOL)*(R[R_OFFSET_Z_MAND]+APP_LNG_TOOL))) + 
//////////		R[R_MAX_HEIGHT] + R[R_SPACE_FREE];
//////////
//////////	if(R[R_TESTINA_SU_MAND]>0.5)  // con testina su mandrino il Drill modifica gli offset R763 ed R764 sono inclusivi degli offset della testina
//////////	{
//////////		// R[R_OFFSET_Z_TESTINA] ricorda che assume valore negativo
//////////		R[R_ZOUT_TEST_CALC] = 
//////////			(float)sqrt
//////////			(((R[R_OFFSET_Y_MAND]-R[R_OFFSET_Z_TESTINA]+R[R_LARGH_STRUCT_SPINDLE]+R[R_OFFSET_MANDR_B_C])*(R[R_OFFSET_Y_MAND]-R[R_OFFSET_Z_TESTINA]+R[R_LARGH_STRUCT_SPINDLE]+R[R_OFFSET_MANDR_B_C])) + 
//////////			((R[R_OFFSET_Z_MAND]-R[R_OFFSET_Y_TESTINA]+R[R_DIM_TOOL])*(R[R_OFFSET_Z_MAND]-R[R_OFFSET_Y_TESTINA]+R[R_DIM_TOOL]))) + 
//////////			R[R_MAX_HEIGHT] + R[R_SPACE_FREE];
//////////	}
//////////
//////////	// Appoggio calcolo diagonale offset mandrino e lunghezza,raggio utensile
//////////	R[R_DIAG_OFFSET_SPINDLE_TOOL] =
//////////		(float)sqrt
//////////		(((R[R_OFFSET_Y_MAND]+R[R_OFFSET_MANDR_B_C])*(R[R_OFFSET_Y_MAND]+R[R_OFFSET_MANDR_B_C])) + 
//////////		((R[R_OFFSET_Z_MAND]+APP_LNG_TOOL)*(R[R_OFFSET_Z_MAND]+APP_LNG_TOOL)));
//////////
//////////	/*
//////////	// Calcolo Z di uscita da testare DIRETTO Per TESTINA Eventuale Modifica
//////////	// Sarebbe un miglioramento per alzare di meno l'asse Z se il PC ci dice che l'ut. è la testina
//////////	R[R_ZOUT_CALCOLATO] = R[R_DIM_TOOL] + R[R_SPACE_FREE] + R[R_MAX_HEIGHT];
//////////	*/
//////////
//////////
//////////	// quota asse Z ottimizzata per fuori ingombro
//////////	R[R_ZOUT] = R[R_ZOUT_CALCOLATO];
//////////
//////////	// quota asse Z ottimizzata per fuori ingombro con testina
//////////	R[R_ZOUT_TESTINA] = R[R_ZOUT_TEST_CALC];
//////////
//////////	}
//////////
//////////
//////////// Limite massimo : se siamo al massimo della pos. Z ogni movimento è insicuro
//////////if (R[R_ZOUT] > R[R_FCPOS_Z])               R[R_ZOUT] = R[R_FCPOS_Z];
//////////
//////////if (R[R_ZOUT_TESTINA] > R[R_FCPOS_Z])       R[R_ZOUT_TESTINA] = R[R_FCPOS_Z];
//////////
//////////
///////////**** CALCOLO SEMPRE QUOTA DI FUORI INGOMBRO PER ASSE Y ****/
//////////////if (R[R_ZOUT_CALCOLATO] >= R[R_FCPOS_Z])
//////////        {
//////////
//////////		// Posizione per ROTAZIONE SICURA A : se occorre andar oltre Zmax e in Y sono già oltre la metà vado a Ymax oppure a Ymin
//////////		
//////////		if ( R[R_QUOTA_Y] >= ((R[R_QUOTA_Y_FUOING_MAG]+R[R_FCNEG_Y])/2) )
//////////                R[R_YOUT] = R[R_QUOTA_Y_FUOING_MAG];
//////////        else
//////////                R[R_YOUT] = R[R_FCNEG_Y];
//////////		
//////////        }
//////////

}









