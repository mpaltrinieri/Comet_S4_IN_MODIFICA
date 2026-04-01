/*
        --------------------------------------------------------------
        TITOLO:         JOG_INC
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione movimento incrementale asse
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    jog_inc(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          NUMERO_ASSE			Numero asse CNC da muovere
                        FUNZ_MAN			Funzione manuale per muovere asse
						COM_A				Comando A
						COM_B				Comando B
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           14-01-2002
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Pecchi Andrea
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

short SELJOG_APP;

void jog_inc_MC(PCNPLC_CNCCTRL cnctrl, PCNPLC_CNCSTATUS cncstatus, PCNPLC_HANDLE cnplchandle, short NUMERO_ASSE, int FUNZ_MAN, int COM_A, int COM_B, int RP_COM_A, int RP_COM_B, int NO_OVERT, int *COM_AVA, int *COM_IND, int *MEM_AVA, int *MEM_IND, int *APP_INC1, int *APP_INC2, int *AB_ASSE)

{

	// Reset appoggi
	if (!COM_A && !COM_B)
	{
		*APP_INC1 = 0;
		*COM_AVA = 0;
		*COM_IND = 0;
		*MEM_AVA = 0;
		*MEM_IND = 0;
	}


	// Abilitazione asse 
	*AB_ASSE = MANO && FUNZ_MAN && (COM_A || COM_B);


	/******* MOVIMENTAZIONE ASSI IN JOG *******/ 
	if (MANO && FUNZ_MAN && !*MEM_AVA && !*MEM_IND && !*APP_INC1)
	{
		if (COM_A && RP_COM_A && NO_OVERT)
		{
			if (!*APP_INC1)
			{
				if (OVFED_CH0 >= 90)
					//SELJOG_APP = SelJog3(NUMERO_ASSE, 1, 1000); // Seleziona spostamento 1 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 1000);
				if ((OVFED_CH0 < 90) && (OVFED_CH0>=60))
					//SELJOG_APP = SelJog3(NUMERO_ASSE, 1,  100); // Seleziona spostamento 0,1 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 100);
				if ((OVFED_CH0 < 60) && (OVFED_CH0>=30))
					//SELJOG_APP = SelJog3(NUMERO_ASSE, 1,   10); // Seleziona spostamento 0,01 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 10);
				if ((OVFED_CH0 < 30) && (OVFED_CH0>=1))
					//SELJOG_APP = SelJog3(NUMERO_ASSE, 1,    1); // Seleziona spostamento 0,01 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 1);

				if (SELJOG_APP == 0)
				{
					*COM_IND = 1;        // Comanda avanti asse
					*MEM_IND = 1;
					*APP_INC1 = 1;
					*APP_INC2 = 1;
					SELJOG = 0;
				}
			}	
		}

		if (COM_B && RP_COM_B && NO_OVERT)
		{
			if (!*APP_INC1)
			{
				if (OVFED_CH0 >= 90)
					// Seleziona spostamento 1 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 1000);
				if ((OVFED_CH0 < 90) && (OVFED_CH0>=60))
					// Seleziona spostamento 0.1 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 100);
				if ((OVFED_CH0 < 60) && (OVFED_CH0>=30))
					// Seleziona spostamento 0.01 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 10);
				if ((OVFED_CH0 < 30) && (OVFED_CH0>=1))
					// Seleziona spostamento 0.001 mm
					SELJOG_APP = SelJog_MC(cnctrl,cncstatus,cnplchandle,NUMERO_ASSE, 1, 1);

				if (SELJOG_APP == 0)
				{
					*COM_AVA = 1;        // Comanda indietro asse
					*MEM_AVA = 1;
					*APP_INC1 = 1;
					*APP_INC2 = 1;
					SELJOG = 0;
				}
			}
		}
	}


}

void jog_inc(short NUMERO_ASSE, int FUNZ_MAN, int COM_A, int COM_B, int RP_COM_A, int RP_COM_B, int NO_OVERT, int *COM_AVA, int *COM_IND, int *MEM_AVA, int *MEM_IND, int *APP_INC1, int *APP_INC2, int *AB_ASSE)
{

	// Reset appoggi
	if (!COM_A && !COM_B)
	{
		*APP_INC1 = 0;
		*COM_AVA = 0;
		*COM_IND = 0;
		*MEM_AVA = 0;
		*MEM_IND = 0;
	}


	// Abilitazione asse 
	*AB_ASSE = MANO && FUNZ_MAN && (COM_A || COM_B);


	/******* MOVIMENTAZIONE ASSI IN JOG *******/
	if (MANO && FUNZ_MAN && !*MEM_AVA && !*MEM_IND && !*APP_INC1)
	{
		if (COM_A && RP_COM_A && NO_OVERT)
		{
			if (!*APP_INC1)
			{
				if (OVFED_CH0 >= 90)
					SELJOG_APP = SelJog(NUMERO_ASSE, 1, 1000); /* Seleziona spostamento 1 mm */
				if ((OVFED_CH0 < 90) && (OVFED_CH0>=60))
					SELJOG_APP = SelJog(NUMERO_ASSE, 1,  100); /* Seleziona spostamento 0,1 mm */
				if ((OVFED_CH0 < 60) && (OVFED_CH0>=30))
					SELJOG_APP = SelJog(NUMERO_ASSE, 1,   10); /* Seleziona spostamento 0,01 mm */
				if ((OVFED_CH0 < 30) && (OVFED_CH0>=1))
					SELJOG_APP = SelJog(NUMERO_ASSE, 1,    1); /* Seleziona spostamento 0,001 mm */

				if (SELJOG_APP == 0)
				{
					*COM_IND = 1;        /* Comanda indietro asse */
					*MEM_IND = 1;
					*APP_INC1 = 1;
					*APP_INC2 = 1;
					SELJOG = 0;
				}
			}	
		}

		if (COM_B && RP_COM_B && NO_OVERT)
		{
			if (!*APP_INC1)
			{
				if (OVFED_CH0 >= 90)
					SELJOG_APP = SelJog(NUMERO_ASSE, 1, 1000); /* Seleziona spostamento 1 mm */
				if ((OVFED_CH0 < 90) && (OVFED_CH0>=60))
					SELJOG_APP = SelJog(NUMERO_ASSE, 1,  100); /* Seleziona spostamento 0,1 mm */
				if ((OVFED_CH0 < 60) && (OVFED_CH0>=30))
					SELJOG_APP = SelJog(NUMERO_ASSE, 1,   10); /* Seleziona spostamento 0,01 mm */
				if ((OVFED_CH0 < 30) && (OVFED_CH0>=1))
					SELJOG_APP = SelJog(NUMERO_ASSE, 1,    1); /* Seleziona spostamento 0,001 mm */

				if (SELJOG_APP == 0)
				{
					*COM_AVA = 1;        /* Comanda avanti asse */
					*MEM_AVA = 1;
					*APP_INC1 = 1;
					*APP_INC2 = 1;
					SELJOG = 0;
				}
			}
		}
	}


}
