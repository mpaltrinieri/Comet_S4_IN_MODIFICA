/*
        --------------------------------------------------------------
        TITOLO:         CHECK_BATTUTE
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Check posizione battute
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    check_battute (void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CS4 0.100
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           05-12-2018
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

void check_battute (void)
{
	if(R[R_BATTUTE_MOBMAN_PRES]>0.5)
	{
		if(PON)
		{
		}
		

		// ------------------------------------------------------------------------------------

		//APPOGGIO POSIZIONI RICHIESTE DA HDRILL PER LA BATTUTA DX4
		rich_BATTUTA_DX4_POS1 = ( (R[R_POS_BATT_DX4_REQ]>0.5) && (R[R_POS_BATT_DX4_REQ]<1.5) );   // Richiesta Posizione di riferimento X1R (posizione esterna)
		rich_BATTUTA_DX4_POS2 = ( (R[R_POS_BATT_DX4_REQ]>1.5) && (R[R_POS_BATT_DX4_REQ]<2.5) );   // Richiesta Posizione di riferimento X2R (posizione intermedia)
		rich_BATTUTA_DX4_POS3 = ( (R[R_POS_BATT_DX4_REQ]>2.5) && (R[R_POS_BATT_DX4_REQ]<3.5) );   // Richiesta Posizione di riferimento X3R (posizione intermedia)
		rich_BATTUTA_DX4_POS4 = ( (R[R_POS_BATT_DX4_REQ]>3.5) && (R[R_POS_BATT_DX4_REQ]<4.5) );   // Richiesta Posizione di riferimento X4R (posizione interna)
		rich_BATTUTA_DX4_POS0 = ( (R[R_POS_BATT_DX4_REQ]<0.5)                                );   // Richiesta Posizione di riferimento X0R (nessuna)
		
		// ------------------------------------------------------------------------------------

		//***** SIMULAZIONE INGRESSI DI POSIZIONAMENTO BATTUTE *****
		if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
		{
			// battuta di SX sempre stata fissa.   BATTUTA_SX_POS1_I = 1;

			if(rich_BATTUTA_DX4_POS4) 
			{
				BATTUTA_DX_POS1_I = 0;
				BATTUTA_DX_POS2_I = 0;
				BATTUTA_DX_POS3_I = 0;
				BATTUTA_DX_POS4_I = 1;
			} 
			else if(rich_BATTUTA_DX4_POS3) 
			{
				BATTUTA_DX_POS1_I = 0;
				BATTUTA_DX_POS2_I = 0;
				BATTUTA_DX_POS3_I = 1;
				BATTUTA_DX_POS4_I = 0;
			} 
			else if(rich_BATTUTA_DX4_POS2) 
			{
				BATTUTA_DX_POS1_I = 0;
				BATTUTA_DX_POS2_I = 1;
				BATTUTA_DX_POS3_I = 0;
				BATTUTA_DX_POS4_I = 0;
			}
			else if(rich_BATTUTA_DX4_POS1) 
			{
				BATTUTA_DX_POS1_I = 1;
				BATTUTA_DX_POS2_I = 0;
				BATTUTA_DX_POS3_I = 0;
				BATTUTA_DX_POS4_I = 0;
			}
			else
			{
				BATTUTA_DX_POS1_I = 1;
				BATTUTA_DX_POS2_I = 0;
				BATTUTA_DX_POS3_I = 0;
				BATTUTA_DX_POS4_I = 0;
			}
		}

		// ------------------------------------------------------------------------------------
		
		//APPOGGIO SENSORE DI POSIZIONE_1 DELLA BATTUTA SX1  (battuta di SX sempre stata fissa su CometS4, mai esistito ingresso  BATTUTA_SX_POS1_I)
		app_BATTUTA_SX1_POS1 = 1;

		//*** APPOGGIO SU R DELLA POSIZIONE DELLA BATTUTA SX1 ***
		if(app_BATTUTA_SX1_POS1)       R[R_APP_POS_BATT_SX1] = 1;
		else                           R[R_APP_POS_BATT_SX1] = 0;

		// Copia variabile da CH0 a CH2
		Aris_CH2[R_APP_POS_BATT_SX1] = R[R_APP_POS_BATT_SX1];
		Aris_CH2[R_POS_BATT_SX1_REQ] = R[R_POS_BATT_SX1_REQ];
		
		// ------------------------------------------------------------------------------------

		//APPOGGIO STATO SENSORI DI POSIZIONE DELLA BATTUTA DX4
		app_BATTUTA_DX4_POS1 = ( BATTUTA_DX_POS1_I && !BATTUTA_DX_POS2_I && !BATTUTA_DX_POS3_I && !BATTUTA_DX_POS4_I);   // Posizione di riferimento X1R (la più esterna)
		app_BATTUTA_DX4_POS2 = (!BATTUTA_DX_POS1_I &&  BATTUTA_DX_POS2_I && !BATTUTA_DX_POS3_I && !BATTUTA_DX_POS4_I);   // Posizione di riferimento X2R (   posizione intermedia)
		app_BATTUTA_DX4_POS3 = (!BATTUTA_DX_POS1_I && !BATTUTA_DX_POS2_I &&  BATTUTA_DX_POS3_I && !BATTUTA_DX_POS4_I);   // Posizione di riferimento X3R (   posizione intermedia)
		app_BATTUTA_DX4_POS4 = (!BATTUTA_DX_POS1_I && !BATTUTA_DX_POS2_I && !BATTUTA_DX_POS3_I &&  BATTUTA_DX_POS4_I);   // Posizione di riferimento X4R (la posizione interna)


		//*** APPOGGIO SU R DELLE POSIZIONI DELLA BATTUTA DX4 ***
		if     (app_BATTUTA_DX4_POS1)  R[R_APP_POS_BATT_DX4] = 1;       // Posizione di riferimento X1R (posizione esterna)
		else if(app_BATTUTA_DX4_POS2)  R[R_APP_POS_BATT_DX4] = 2;       // Posizione di riferimento X2R (posizione intermedia)
		else if(app_BATTUTA_DX4_POS3)  R[R_APP_POS_BATT_DX4] = 3;       // Posizione di riferimento X3R (posizione intermedia)
		else if(app_BATTUTA_DX4_POS4)  R[R_APP_POS_BATT_DX4] = 4;       // Posizione di riferimento X4R (posizione interna)
		else                           R[R_APP_POS_BATT_DX4] = 0;       // Posizione sconosciuta

		// Copia variabile da CH0 a CH2
		Aris_CH2[R_APP_POS_BATT_DX4] = R[R_APP_POS_BATT_DX4];
		Aris_CH2[R_POS_BATT_DX4_REQ] = R[R_POS_BATT_DX4_REQ];

		// ------------------------------------------------------------------------------------

		//***** Flag di verifica posizioni reali rispetto a quelle richieste da Hdrill. Utilizzabili nelle conferme di carico pezzo *****

		// Battuta SX1 in posizione corretta, richiesta da Hdrill
		BAT_SX1_MOB_IN_POS_OK = (R[R_POS_BATT_SX1_REQ] < 1.5) && app_BATTUTA_SX1_POS1;

		// Battuta DX4 in posizione corretta, richiesta da Hdrill
		BAT_DX4_MOB_IN_POS_OK = (
			rich_BATTUTA_DX4_POS4 && app_BATTUTA_DX4_POS4  || 
			rich_BATTUTA_DX4_POS3 && app_BATTUTA_DX4_POS3  || 
			rich_BATTUTA_DX4_POS2 && app_BATTUTA_DX4_POS2  ||  
			rich_BATTUTA_DX4_POS1 && app_BATTUTA_DX4_POS1  ||
			rich_BATTUTA_DX4_POS0 && app_BATTUTA_DX4_POS1
		);

		// Battute SX1 e DX4 in posizione corretta, richiesta da Hdrill
		BAT_SX1_DX4_MOB_IN_POS_OK = BAT_SX1_MOB_IN_POS_OK && BAT_DX4_MOB_IN_POS_OK;

		// ------------------------------------------------------------------------------------


		// RESET ALLARMI
		if(RESET_MC || RESET_ALL)
		{
			BATT_SX1_NOPOS_X1L_FAL = 0;
			
			BATT_DX4_NOPOS_X4R_FAL = 0;
			BATT_DX4_NOPOS_X3R_FAL = 0;
			BATT_DX4_NOPOS_X2R_FAL = 0;
			BATT_DX4_NOPOS_X1R_FAL = 0;
			
			BATT_DX4_DISFC_FAL = 0;
		}
		
		
		// Disfunzione finecorsa battuta DX4
		if(BATTUTA_DX_POS1_I && BATTUTA_DX_POS2_I ||
		   BATTUTA_DX_POS1_I && BATTUTA_DX_POS3_I ||
		   BATTUTA_DX_POS2_I && BATTUTA_DX_POS3_I 
		   )
		   BATT_DX4_DISFC_FAL = 1;
		
		
		// ------------------------------------------------------------------------------------
		// ***** GESTIONE NEL MULTIPEZZO ******
		// ------------------------------------------------------------------------------------
		
		// Check posizione battute SX1 DX4 in multipezzo
		if( BAT_SX1_DX4_MOB_IN_POS_OK && 
		    !BATT_SX1_NOPOS_X1L_FAL && !BATT_DX4_NOPOS_X1R_FAL && !BATT_DX4_NOPOS_X2R_FAL && !BATT_DX4_NOPOS_X3R_FAL && !BATT_DX4_NOPOS_X4R_FAL
		)
		{
		  Mr_MC(303);
		}

		// ***** CONDIZIONE DI CARICO IN CORSO NEL MULTIPEZZO da aggiungere nella condizione per dare allarme di check battute:      
		//       M81 && (R[R_END_SX] == 1)
		
		if(Mg_MC(303) || (Mg_MC(81) && (R[R_END_SX] == 1)) )
		{
			if(!app_BATTUTA_SX1_POS1) BATT_SX1_NOPOS_X1L_FAL = 1;

			if( rich_BATTUTA_DX4_POS4 && !app_BATTUTA_DX4_POS4 )  BATT_DX4_NOPOS_X4R_FAL = 1;
			if( rich_BATTUTA_DX4_POS3 && !app_BATTUTA_DX4_POS3 )  BATT_DX4_NOPOS_X3R_FAL = 1;
			if( rich_BATTUTA_DX4_POS2 && !app_BATTUTA_DX4_POS2 )  BATT_DX4_NOPOS_X2R_FAL = 1;
			if( rich_BATTUTA_DX4_POS1 && !app_BATTUTA_DX4_POS1 )  BATT_DX4_NOPOS_X1R_FAL = 1;
			
			// se battuta non usata forziamo l'operatore a posizionare la battuta in posizione esterna
			if( rich_BATTUTA_DX4_POS0 && !app_BATTUTA_DX4_POS1 )  BATT_DX4_NOPOS_X1R_FAL = 1;
		}

		// ------------------------------------------------------------------------------------

	}
	else
	{
		Mr_MC(303);
		
		BATT_SX1_NOPOS_X1L_FAL = 0;
			
		BATT_DX4_NOPOS_X4R_FAL = 0;
		BATT_DX4_NOPOS_X3R_FAL = 0;
		BATT_DX4_NOPOS_X2R_FAL = 0;
		BATT_DX4_NOPOS_X1R_FAL = 0;
			
		BATT_DX4_DISFC_FAL = 0;	

		BAT_SX1_DX4_MOB_IN_POS_OK = 1;
		BAT_SX1_MOB_IN_POS_OK = 1;
		BAT_DX4_MOB_IN_POS_OK = 1;
	}
}