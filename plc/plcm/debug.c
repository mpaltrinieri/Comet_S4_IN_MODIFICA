/*
        --------------------------------------------------------------
        TITOLO:         DEBUG
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione Visualizzazioni per DEBUG
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    debug (void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.100
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           27-09-2007
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

void    debug (void)

{


	if (CONF_DEBUG)
	{


		// RESET ALLARMI ASPIRATORE FUMI 
		if (RESET_ALL || RESET_MC)
		{
		}

		/******* ASSE RIFERITO ********/
		if(CONF_ASSE_X) O_SEE_ASSE_X = (unsigned short) O_SEE_CH0(AX_X_CH0);
		if(CONF_ASSE_Y) O_SEE_ASSE_Y = (unsigned short) O_SEE_CH0(AX_Y_CH0);
		if(CONF_ASSE_Z) O_SEE_ASSE_Z = (unsigned short) O_SEE_CH0(AX_Z_CH0);
		if(CONF_ASSE_A) O_SEE_ASSE_A = (unsigned short) O_SEE_CH0(AX_A_CH0);
		if(CONF_ASSE_C) O_SEE_ASSE_C = (unsigned short) O_SEE_CH0(AX_C_CH0);
		if(CONF_ASSE_W) O_SEE_ASSE_W = (unsigned short) O_SEE_CH1(AX_W_CH1);


		if(CONF_ASSE_M10)	O_SEE_ASSE_M10 = (unsigned short) O_SEE_CH2(AX_M10_CH2);
		if(CONF_ASSE_M11)	O_SEE_ASSE_M11 = (unsigned short) O_SEE_CH2(AX_M11_CH2);
		if(CONF_ASSE_M12)	O_SEE_ASSE_M12 = (unsigned short) O_SEE_CH2(AX_M12_CH2);
		if(CONF_ASSE_M13)	O_SEE_ASSE_M13 = (unsigned short) O_SEE_CH2(AX_M13_CH2);
		if(CONF_ASSE_M14)	O_SEE_ASSE_M14 = (unsigned short) O_SEE_CH2(AX_M14_CH2);
		if(CONF_ASSE_M15)	O_SEE_ASSE_M15 = (unsigned short) O_SEE_CH2(AX_M15_CH2);

		if(CONF_ASSE_M10)	O_MOV_ASSE_M10 = (unsigned short) O_MOV_CH2(AX_M10_CH2);
		if(CONF_ASSE_M11)	O_MOV_ASSE_M11 = (unsigned short) O_MOV_CH2(AX_M11_CH2);
		if(CONF_ASSE_M12)	O_MOV_ASSE_M12 = (unsigned short) O_MOV_CH2(AX_M12_CH2);
		if(CONF_ASSE_M13)	O_MOV_ASSE_M13 = (unsigned short) O_MOV_CH2(AX_M13_CH2);
		if(CONF_ASSE_M14)	O_MOV_ASSE_M14 = (unsigned short) O_MOV_CH2(AX_M14_CH2);
		if(CONF_ASSE_M15)	O_MOV_ASSE_M15 = (unsigned short) O_MOV_CH2(AX_M15_CH2);

	}
	else
	{
		VISUALIZZAZIONI_1 = 0;
		VISUALIZZAZIONI_2 = 0;
		VISUALIZZAZIONI_3 = 0;
		VISUALIZZAZIONI_4 = 0;
	}


}






