/*
        --------------------------------------------------------------
        TITOLO:         READCONF
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Lettura configurazione macchina da CONFMAC.CS4
						Set parametri assi da assi.inc
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    readconf(void)
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
        DATA:           10-08-2005
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------

*/

#include        "all.inc"



void    readconf(void)

{

	if (PON) // Tutto attivo 
	{

		//------------------- Lettura parametro configurazione macchina WORD N.1 -------------------
		CONFMAC1_DWORD =		(long)R[R_CONFMAC1];		// 

		if(TRACE_DEBUG_6) rtplctrace(1,_T("readconf_2a R[R_CONFMAC1]=%f.3"),R[R_CONFMAC1]);
		if(TRACE_DEBUG_6) rtplctrace(1,_T("readconf_2b CONFMAC1_DWORD=%d"),CONFMAC1_DWORD);


		//--------------------- Lettura parametro configurazione macchina WORD N.2 ------------------
		CONFMAC2_DWORD =		(long)R[R_CONFMAC2];		// 

		//--------------------- Lettura parametro configurazione macchina WORD N.2 ------------------
		CONFMAC3_DWORD =		(long)R[R_CONFMAC3];		// 

		//------------------------ Lettura parametro configurazione mandrino ----------------------
		CONF_MANDRINO_DWORD =	(long)R[R_MANDRINO];		// 

		//--------------------- Lettura parametro configurazione magazzino ---------------------
		CONF_MAGAZZINO_DWORD =	    (long)R[R_MAGAZZINO];		// 

		//--------------------- Lettura parametro configurazione SERVIZIO ---------------------
		CONF_SERVIZIO_DWORD =	(long)R[R_SERVIZIO];		// 

		//--------------------- Lettura parametro configurazione Assi P H ---------------------
		CONF_ASSI_PH_DWORD =	(long)R[R_ASSI_PH];			// 


		/**** Morse motorizzate presenti ****/
		MORSE_MOTORIZZATE = 
			CONF_ASSE_M10	|| 
			CONF_ASSE_M11	|| 
			CONF_ASSE_M12	|| 
			CONF_ASSE_M13	|| 
			CONF_ASSE_M14	|| 
			CONF_ASSE_M15;


		ASSE_M10_PRES = CONF_ASSE_M10;
		ASSE_M11_PRES = CONF_ASSE_M11;
		ASSE_M12_PRES = CONF_ASSE_M12;
		ASSE_M13_PRES = CONF_ASSE_M13;
		ASSE_M14_PRES = CONF_ASSE_M14;
		ASSE_M15_PRES = CONF_ASSE_M15;

		// Appoggio parametri R per semplice DEBUG
		R[R_MORSE_MOTORIZZATE]	= (float) (MORSE_MOTORIZZATE);

		R[R_ASSE_X]	= (float)(CONF_ASSE_X);		// 
		R[R_ASSE_Y]	= (float)(CONF_ASSE_Y);		// 
		R[R_ASSE_Z]	= (float)(CONF_ASSE_Z);		// 
		R[R_ASSE_A]	= (float)(CONF_ASSE_A);		// 
		R[R_ASSE_C]	= (float)(CONF_ASSE_C);		// 
		R[R_ASSE_W]	= (float)(CONF_ASSE_W);		// 


	} // Dentro quì esegue solo al Pon

}

