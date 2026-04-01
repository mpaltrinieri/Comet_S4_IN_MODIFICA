/*
        --------------------------------------------------------------
        TITOLO:         MC_IO
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione segnali interscambio PLC - Drill per MC
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    mc_io(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        QUA 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           15-12-2017
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Medici Stefano
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"

void sendStartCNC_CH1(void)
{
	if (REQ_LOAD_ISO_CH1) 
	{
		switch (LOAD_ISO_STATE_CH1)
		{
		case 0:
			if (!O_CNT_CH1)
			{
				if (!SendCnc_MC (&CNCSTATUS_CH1, CTASTO, S_SNCNT, 0)) LOAD_ISO_STATE_CH1++;					 
				else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH1 = 90;}
			}
			//else {LOAD_ISO_STATE_CH1++; LOAD_ISO_STATE_CH1++;LOAD_ISO_STATE_CH1++; LOAD_ISO_STATE_CH1++;}	
			else {LOAD_ISO_STATE_CH1++; LOAD_ISO_STATE_CH1++;}	
			break;
		case 1:
			TSTCMDCNC_MC_RET_CH1 = TstCmdCnc_MC (&CNCSTATUS_CH1);
			//if (!TSTCMDCNC_MC_RET_CH1)  {LOAD_ISO_STATE_CH1++;LOAD_ISO_STATE_CH1++;LOAD_ISO_STATE_CH1++;}					 
			if (!TSTCMDCNC_MC_RET_CH1)  {LOAD_ISO_STATE_CH1++;}
			else if ((TSTCMDCNC_MC_RET_CH1 == E_NOINVP)) 
			{
				if (RP_TSuppl[TS_LOAD_ISO_CH1]) {LOAD_ISO_TIMEOUT_FAL = 1; LOAD_ISO_STATE_CH1 = 80;}
			}
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH1 = 91;}
			break;
		case 2:
			if (!SendCnc_MC (&CNCSTATUS_CH1, CTASTO, S_F2, 0)) LOAD_ISO_STATE_CH1++;					 
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH1 = 92;}
			break;
		case 3:
			TSTCMDCNC_MC_RET_CH1 = TstCmdCnc_MC (&CNCSTATUS_CH1);
			if (!TSTCMDCNC_MC_RET_CH1)  LOAD_ISO_STATE_CH1++;					 
			else if ((TSTCMDCNC_MC_RET_CH1 == E_NOINVP)) 
			{
				if (RP_TSuppl[TS_LOAD_ISO_CH1]) {LOAD_ISO_TIMEOUT_FAL = 1; LOAD_ISO_STATE_CH1 = 81;}
			}
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH1 = 93;}
			break;
		case 4:
			if (!SendCnc_MC (&CNCSTATUS_CH1, CSPP, 0, "ISOMG_CH1.CS4")) LOAD_ISO_STATE_CH1++;					 
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH1 = 94;}
			break;
		case 5:
			TSTCMDCNC_MC_RET_CH1 = TstCmdCnc_MC (&CNCSTATUS_CH1);
			if (!TSTCMDCNC_MC_RET_CH1) 
			{
				//Termina ciclo selezione ISO CH1
				REQ_LOAD_ISO_CH1 = 0;
				//Richiesta start CH1
				ISO_LOAD_CH1 = 1;
				LOAD_ISO_STATE_CH1 = 0;
			}
			else if ((TSTCMDCNC_MC_RET_CH1 == E_NOINVP)) 
			{
				if (RP_TSuppl[TS_LOAD_ISO_CH1]) {LOAD_ISO_TIMEOUT_FAL = 1; LOAD_ISO_STATE_CH1 = 82;}
			}
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH1 = 95;} //Allarme esecuzione comando
			break;

		case 80:
		case 81:
		case 82:
			LOAD_ISO_TIMEOUT_FAL = 1;
			break;

		case 90:
		case 91:
		case 92:
		case 93:
		case 94:
		case 95:
			LOAD_ISO_FAL = 1;
			break;

		}
	}
}

void sendStartCNC_CH2(void)
{
	if (REQ_LOAD_ISO_CH2) 
	{
		switch (LOAD_ISO_STATE_CH2)
		{
		case 0:
			if (!O_CNT_CH2)
			{
				if (!SendCnc_MC (&CNCSTATUS_CH2, CTASTO, S_SNCNT, 0)) LOAD_ISO_STATE_CH2++;
				else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH2 = 90;}
			}
			//else {LOAD_ISO_STATE_CH2++; LOAD_ISO_STATE_CH2++;LOAD_ISO_STATE_CH2++; LOAD_ISO_STATE_CH2++;}	
			else {LOAD_ISO_STATE_CH2++; LOAD_ISO_STATE_CH2++;}
			break;
		case 1:
			TSTCMDCNC_MC_RET_CH2 = TstCmdCnc_MC (&CNCSTATUS_CH2);
			//if (!TSTCMDCNC_MC_RET_CH2)  {LOAD_ISO_STATE_CH2++;LOAD_ISO_STATE_CH2++;LOAD_ISO_STATE_CH2++;}
			if (!TSTCMDCNC_MC_RET_CH2)  {LOAD_ISO_STATE_CH2++;}
			else if ((TSTCMDCNC_MC_RET_CH2 == E_NOINVP)) 
			{
				if (RP_TSuppl[TS_LOAD_ISO_CH2]) {LOAD_ISO_TIMEOUT_FAL = 1; LOAD_ISO_STATE_CH2 = 80;}
			}
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH2 = 91;}
			break;
		case 2:
			if (!SendCnc_MC (&CNCSTATUS_CH2, CTASTO, S_F2, 0)) LOAD_ISO_STATE_CH2++;					 
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH2 = 92;}
			break;
		case 3:
			TSTCMDCNC_MC_RET_CH2 = TstCmdCnc_MC (&CNCSTATUS_CH2);
			if (!TSTCMDCNC_MC_RET_CH2)  LOAD_ISO_STATE_CH2++;					 
			else if ((TSTCMDCNC_MC_RET_CH2 == E_NOINVP)) 
			{
				if (RP_TSuppl[TS_LOAD_ISO_CH2]) {LOAD_ISO_TIMEOUT_FAL = 1; LOAD_ISO_STATE_CH2 = 81;}
			}
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH2 = 93;}
			break;
		case 4:
			if (!SendCnc_MC (&CNCSTATUS_CH2, CSPP, 0, "ISOMG_CH2.CS4")) LOAD_ISO_STATE_CH2++;					 
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH2 = 94;}
			break;
		case 5:
			TSTCMDCNC_MC_RET_CH2 = TstCmdCnc_MC (&CNCSTATUS_CH2);
			if (!TSTCMDCNC_MC_RET_CH2) 
			{
				//Termina ciclo selezione ISO CH2
				REQ_LOAD_ISO_CH2 = 0;
				//Richiesta start CH2
				ISO_LOAD_CH2 = 1;
				LOAD_ISO_STATE_CH2 = 0;
			}
			else if ((TSTCMDCNC_MC_RET_CH2 == E_NOINVP)) 
			{
				if (RP_TSuppl[TS_LOAD_ISO_CH2]) {LOAD_ISO_TIMEOUT_FAL = 1; LOAD_ISO_STATE_CH2 = 82;}
			}
			else {LOAD_ISO_FAL = 1; LOAD_ISO_STATE_CH2 = 95;} //Allarme esecuzione comando
			break;

		case 80:
		case 81:
		case 82:
			LOAD_ISO_TIMEOUT_FAL = 1;
			break;

		case 90:
		case 91:
		case 92:
		case 93:
		case 94:
		case 95:
			LOAD_ISO_FAL = 1;
			break;

		}
	}
}

