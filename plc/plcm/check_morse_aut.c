/*
        --------------------------------------------------------------
        TITOLO:         Check_morse_aut
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Controllo Morse Automatiche in modo standard
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void	check_morse_aut (void)
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

void    check_morse_aut (void)
{

	/************ Sempre abilitato con le morse automatiche *********/
	// new: verifiche posizionamenti morse ora disponibili in tutte le configurazioni.		old: if (MORSE_MOTORIZZATE)
	{

		/******* RESET ALLARMI ********/
		if (RESET_MC)
		{
			POS_MORSA_10_FAL = 0;
			POS_MORSA_11_FAL = 0;
			POS_MORSA_12_FAL = 0;
			POS_MORSA_13_FAL = 0;
			POS_MORSA_14_FAL = 0;
			POS_MORSA_15_FAL = 0;

			Mr_MC(154);
		}

		// Controllo se le morse sono nella posizione richiesta dal PC : appena prima del ciclo di lavoro
		if (Mg_MC(154))
		{
			POS_MORSA_10_FAL = CONF_ASSE_M10 && !MORSA_10_IN_POSIZIONE;
			POS_MORSA_11_FAL = CONF_ASSE_M11 && !MORSA_11_IN_POSIZIONE;
			POS_MORSA_12_FAL = CONF_ASSE_M12 && !MORSA_12_IN_POSIZIONE;
			POS_MORSA_13_FAL = CONF_ASSE_M13 && !MORSA_13_IN_POSIZIONE;
			POS_MORSA_14_FAL = CONF_ASSE_M14 && !MORSA_14_IN_POSIZIONE;
			POS_MORSA_15_FAL = CONF_ASSE_M15 && !MORSA_15_IN_POSIZIONE;

			if(TUTTE_LE_MORSE_IN_POSIZIONE_SX && TUTTE_LE_MORSE_IN_POSIZIONE_DX)
			{
				Mr_MC(154);
			}	
		}

	}
	//else
	//{
	//	POS_MORSA_10_FAL = 0;
	//	POS_MORSA_11_FAL = 0;
	//	POS_MORSA_12_FAL = 0;

	//	POS_MORSA_13_FAL = 0;
	//	POS_MORSA_14_FAL = 0;
	//	POS_MORSA_15_FAL = 0;

	//	Mr_MC(154);
	//}
}
