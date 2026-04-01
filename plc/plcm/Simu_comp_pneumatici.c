
/*
        --------------------------------------------------------------
        TITOLO:         SIMULAZIONE COMPONENTI PNEUMATICI
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    RACCOLTA FUNZIONI DI SIMULAZIONE 
		                COMPONENTI PNEUMATICI
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       
        --------------------------------------------------------------
        --------------------------------------------------------------
		INPUT:		
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        COMET S58
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           19-12-2017
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------
*/

#include "all.inc"


void mandrino_simu(void)
{
	if(CONF_MANDRINO)
	{	
		if (!SBLOC_UT_O)
			TIMESBLOCCUT2 = (int) R[R_SBLOC_UT];
		else
		{
			if (TIMESBLOCCUT2 > 0)
				TIMESBLOCCUT2--;
		}
		UT_SGANC_I = SBLOC_UT_O && (TIMESBLOCCUT2 <= 0);
	
	
		if (SBLOC_UT_O)
			TIMESBLOCCUT1 = (int) R[R_BLOCC_UT];
		else
		{
			if (TIMESBLOCCUT1 > 0)
				TIMESBLOCCUT1--;
		}
		UT_AGGAN_I = !SBLOC_UT_O && (TIMESBLOCCUT1 <= 0) && !UT0_ACT;	
	}
}

void tavola_simu(void)
{
	//Simulazione tavola SX
	if(CONF_TAVOLA_PRES)
	{	
		if (!TAVOLA_AVA_O)
			TIMETAV1 = (int) R[R_AVA_TAVOLA_OR];
		else
		{
			if (TIMETAV1 > 0)
				TIMETAV1--;
		}
	
		TAVOLA_AVA_I = (TAVOLA_AVA_O && (TIMETAV1 <= 0));
		R[R_SIMU_TAV_AVA] = (float) TAVOLA_AVA_I;
	
		if (!TAVOLA_IND_O)
			TIMETAV2 = (int) R[R_IND_TAVOLA_OR];
		else
		{
			if (TIMETAV2 > 0)
				TIMETAV2--;
		}
	
		TAVOLA_IND_I = (TAVOLA_IND_O && (TIMETAV2 <= 0));
	}
}

void battuta_sx1_simu(void)
{
	//Simulazione battuta SX1 Salita/Discesa
	if (CONF_BATTUTA_SX1)
	{		
		if (!BATTUTA_SX_ALT_O)
			TIMEBATTSX11 = (int) R[R_SAL_BARCAR_SX1];
		else
		{
			if (TIMEBATTSX11 > 0)
				TIMEBATTSX11--;
		}

		R[R_SIMU_BATTUTA_SX_INS] = BATTUTA_SX_ALT_O && (TIMEBATTSX11<=0);
		
		if (BATTUTA_SX_ALT_O)
			TIMEBATTSX12 = (int) R[R_DIS_BARCAR_SX1];
		else
		{
			if (TIMEBATTSX12 > 0)
				TIMEBATTSX12--;
		}			
	
		BATTUTA_SX_BAS_I = !BATTUTA_SX_ALT_O && (TIMEBATTSX12 <= 0);
	}
}		

void battuta_dx4_simu(void)
{
	//Simulazione battuta DX4 Salita/Discesa
	if (CONF_BATTUTA_DX4)
	{		
	
		if (!BATTUTA_DX_ALT_O)
			TIMEBATTDX41 = (int) R[R_SAL_BARCAR_DX4];
		else
		{
			if (TIMEBATTDX41 > 0)
				TIMEBATTDX41--;
		}
	
		if (BATTUTA_DX_ALT_O)
			TIMEBATTDX42 = (int) R[R_DIS_BARCAR_DX4];
		else
		{
			if (TIMEBATTDX42 > 0)
				TIMEBATTDX42--;
		}
	
		BATTUTA_DX_BAS_I = !BATTUTA_DX_ALT_O && (TIMEBATTDX42 <= 0);
	}
}
		
void riparo_simu(void)
{
	//Simulazione Riparo Anteriore
	if(CONF_RIPARO_ANT)
	{
		if (!AP_RIP_ANT_O)
			TIMERIPANT1 = (int) R[R_AP_RIPARO_ANTE];
		else
		{
			if (TIMERIPANT1 > 0)
			{
				TIMERIPANT1--;

				if(TIMERIPANT1<=5)
					RIPARO_APERTO_SIMU = 1;
			}

			RIPARO_CHIUSO_SIMU = 0;
		}
		
		APPO_RIPARO_AP_INP = (AP_RIP_ANT_O && (TIMERIPANT1 <= 0)) || RIPARO_APERTO_SIMU;
		
		if (!CH_RIP_ANT_O)
			TIMERIPANT2 = (int) R[R_CH_RIPARO_ANTE];
		else
		{
			if (TIMERIPANT2 > 0)
			{
				TIMERIPANT2--;

				if(TIMERIPANT2<=5)
					RIPARO_CHIUSO_SIMU = 1;
			}
			
			RIPARO_APERTO_SIMU = 0;
		}
		
		APPO_RIPARO_CH_INP = (CH_RIP_ANT_O && (TIMERIPANT2 <= 0)) || RIPARO_CHIUSO_SIMU;
	}
}

void trasc_ax_X_simu(void)
{
	//Simulazione Trascinatore Morse asse X
	if(CONF_TRASC_MORSE_AX_X)
	{
		if (!TRASC_MORSE_AX_X_INS_O)
			TIMETRASCMORAXX1 = (int) R[R_INS_TRASC_X_MORSE];
		else
		{
			if (TIMETRASCMORAXX1 > 0)
				TIMETRASCMORAXX1--;
		}
	
		TRASC_MORSE_AX_X_INS_I = TRASC_MORSE_AX_X_INS_O && (TIMETRASCMORAXX1 <= 0);
	
		if (TRASC_MORSE_AX_X_INS_O)
			TIMETRASCMORAXX2 = (int) R[R_DIS_TRASC_X_MORSE];
		else
		{
			if (TIMETRASCMORAXX2 > 0)
				TIMETRASCMORAXX2--;
		}
		TRASC_MORSE_AX_X_DIS_I = !TRASC_MORSE_AX_X_INS_O && (TIMETRASCMORAXX2 <= 0);

	}
}

void rilev_morse_ax_X_simu(void)
{
	//Simulazione Trascinatore Morse asse X
	if(CONF_RILEV_MORSE_AX_X)
	{
		if (!INS_RILMOR_AX_X_O)
			TIMERILMORAXX1 = (int) R[R_INS_RILMOR_AX_X];
		else
		{
			if (TIMERILMORAXX1 > 0)
				TIMERILMORAXX1--;
		}
	
	
		if (INS_RILMOR_AX_X_O)
			TIMERILMORAXX2 = (int) R[R_DIS_RILMOR_AX_X];
		else
		{
			if (TIMERILMORAXX2 > 0)
				TIMERILMORAXX2--;
		}
		PRESENZA_MORSA_AX_X_I = (!INS_RILMOR_AX_X_O) && (TIMERILMORAXX2 <= 0);

	}
}

void visiera_bassa_simu(void)
{
	//Simulazione visiera bassa (componente monostabile)
	if (CONF_VIS_BASSA)
	{		
		if (VISIERA_IND_O)
			TIMEVISBAS1 = (int) R[R_VISIERA_BASSA_AVA];
		else
		{
			if (TIMEVISBAS1 > 0)
				TIMEVISBAS1--;
		}
		
		VISIERA_AVA_I = !VISIERA_IND_O && (TIMEVISBAS1 <= 0);		
	
	
		if (!VISIERA_IND_O)
			TIMEVISBAS2 = (int) R[R_VISIERA_BASSA_IND];
		else
		{
			if (TIMEVISBAS2 > 0)
				TIMEVISBAS2--;
		}
	
		VISIERA_IND_I = VISIERA_IND_O && (TIMEVISBAS2 <= 0);
	}
}


void visiera_alta_simu(void)
{
	//Simulazione visiera alta
	if (CONF_VIS_ALTA)
	{		
		if (!VIS_RIP_SAL_O)
			TIMEVISALTA1 = (int) R[R_VIS_RIP_SAL];
		else
		{
			if (TIMEVISALTA1 > 0)
				TIMEVISALTA1--;
		}
		
		RIP_ANT_CH_SICUR_I = VIS_RIP_SAL_O && (TIMEVISALTA1 <= 0);		
	
	
		if (VIS_RIP_DIS_O)
			TIMEVISALTA2 = (int) R[R_VIS_RIP_DIS];
		else
		{
			if (TIMEVISALTA2 > 0)
				TIMEVISALTA2--;
		}
	
	}
}

