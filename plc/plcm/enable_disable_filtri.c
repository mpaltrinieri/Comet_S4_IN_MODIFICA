//----------------------------------------------------------------------------
// TITOLO      : enable_disable_filtri.c
// AUTORE      : Daniele Formuso
// DESCRIZIONE : Funzioni di supporto per caricamento / lettura parametri assi
//----------------------------------------------------------------------------
#include "all.inc"



void enable_disable_filtri(void) 
{
	static RTPLC_STATUS status = 0;
	static CmdAxisStruct s = {0};
	RTPLC_STATUS fbResult = FB_EXIT_FAILURE;
	static double enable_disable = 1;

	if( R[R_ENAB_DISAB_FILTRI] > 0.5 )
	{
		//if (fbReset) {
		//    FB_RESET();
		//    status = 0;
		//    FB_EXIT(FB_EXIT_SUCCESS);
		//}

		APP_G184_IN_CORSO = G184_CH0;   //Appoggio G184_CH0 in corso per visualizzazione

		// Derivata positiva della M di Disattivazione filtri su assi X,Y,Z:
		DP_M_DIS_FILTRI = Mg_MC(255) && !MEM_M_DIS_FILTRI;
		MEM_M_DIS_FILTRI = Mg_MC(255);

		// Derivata positiva della M di Attivazione filtri su assi X,Y,Z:
		DP_M_ATT_FILTRI = Mg_MC(256) && !MEM_M_ATT_FILTRI;
		MEM_M_ATT_FILTRI = Mg_MC(256);

		//Derivata negativa di RESET_MC in corso:
		DN_O_RESET = 0;
		DN_O_RESET = !RESET_MC && MEM_O_RESET;

		MEM_O_RESET = RESET_MC;

		if(DP_M_DIS_FILTRI)                {ENABLE_FILTRI_XYZA = 0; DISABLE_FILTRI_XYZA = 1; status = 0;}

		if(DP_M_ATT_FILTRI || DN_O_RESET)  {ENABLE_FILTRI_XYZA = 1; DISABLE_FILTRI_XYZA = 0; status = 0;}


		switch (status) 
		{
		case 0:
			if (DISABLE_FILTRI_XYZA) {
				rtplctrace4(1,_T("Inizio maschiatura rigida: inizio disabilitazione filtri" ));
				enable_disable = -1;  //disabilita filtri
				if(!O_MOV_X && !O_MOV_Y && !O_MOV_Z)
				{
					CONT_ABIL_DISABIL_X = 0;
					CONT_ABIL_DISABIL_Y = 0;
					CONT_ABIL_DISABIL_Z = 0;
					CONT_ABIL_DISABIL_A = 0;
					status = 10;
				}
			} 
			else if(ENABLE_FILTRI_XYZA){
				rtplctrace4(1,_T("Fine maschiatura rigida: inizio abilitazione filtri" ));
				enable_disable = 1;  //abilita filtri
				if(!O_MOV_X && !O_MOV_Y && !O_MOV_Z)
				{
					CONT_ABIL_DISABIL_X = 0;
					CONT_ABIL_DISABIL_Y = 0;
					CONT_ABIL_DISABIL_Z = 0;
					CONT_ABIL_DISABIL_A = 0;
					status = 10;
				}
			} 
			break;

		// ASSE X /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case 10:
			{
				setAxisFilter(0, AX_X_CH0, enable_disable, &s);
				rtplctrace4(1,_T("Richiesta abilitazione / disabilitazione %f filtro su asse X" ), enable_disable);
				status = 20;
			} 
			break;			

		case 20:
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
			if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 40;
			} else {
				rtplctrace4(1,_T("Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 30;
			}
			break;

		case 30:
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
			if (FB_SUCCESS(fbResult)) {
				rtplctrace4(1,_T("Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 110;
			} else if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 40;
			}
			break;

		case 40: //Stato di errore su abilitazione / disabilitazione filtro su asse X
			{
				CONT_ABIL_DISABIL_X++;  //incrementa il numero di tentativi di abilitare / disabilitare filtri su asse X 
				rtplctrace4(1,_T("Errore abilitazione / disabilitazione filtro su asse X "));
				if(CONT_ABIL_DISABIL_X < 3) // tenta 3 volte di abilitare / disabilitare filtri
				{
					status = 10;
					//Mr_MC(255);  Mr_MC(256);
				}
				else
				{
					status = 110;
				}
			}
			break;

		// ASSE Y /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case 110:
			{
				setAxisFilter(0, AX_Y_CH0, enable_disable, &s);
				rtplctrace4(1,_T("Richiesta abilitazione / disabilitazione %f filtro su asse Y" ), enable_disable);
				status = 120;
			} 
			break;			

		case 120:
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
			if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 140;
			} else {
				rtplctrace4(1,_T("Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 130;
			}
			break;

		case 130:
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
			if (FB_SUCCESS(fbResult)) {
				rtplctrace4(1,_T("Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 210;
			} else if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 140;
			}
			break;	

		case 140: //Stato di errore su abilitazione / disabilitazione filtro su asse Y
			{
				CONT_ABIL_DISABIL_Y++;  //incrementa il numero di tentativi di abilitare / disabilitare filtri su asse Y
				rtplctrace4(1,_T("Errore abilitazione / disabilitazione filtro su asse Y "));
                if(CONT_ABIL_DISABIL_Y < 3) // tenta 3 volte di abilitare / disabilitare filtri
				{
					status = 110;
					//Mr_MC(255);  Mr_MC(256);
				}
				else
				{
					status = 210;
				}
			}

		// ASSE Z /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case 210:
			{
				setAxisFilter(0, AX_Z_CH0, enable_disable, &s);
				rtplctrace4(1,_T("Richiesta abilitazione / disabilitazione %f filtro su asse Z" ), enable_disable);
				status = 220;
			} 
			break;			

		case 220:
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
			if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 240;
			} else {
				rtplctrace4(1,_T("Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 230;
			}
			break;

		case 230:
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
			if (FB_SUCCESS(fbResult)) {
				rtplctrace4(1,_T("Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);

				if(R[R_ENAB_DISAB_FILTRI] > 1.5) //abilta la gestione abilitazione/disabilitazione filtri da plc anche per asse A
					status = 410;
				else
					status = 900;

			} else if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 240;
			}
			break;

		case 240: //Stato di errore su abilitazione / disabilitazione filtro su asse Z
			{
				CONT_ABIL_DISABIL_Z++;  //incrementa il numero di tentativi di abilitare / disabilitare filtri su asse Z
				rtplctrace4(1,_T("Errore abilitazione / disabilitazione filtro su asse Z "));
                if(CONT_ABIL_DISABIL_Z < 3) // tenta 3 volte di abilitare / disabilitare filtri
				{
					status = 210;
					//Mr_MC(255);  Mr_MC(256);
				}
				else if (R[R_ENAB_DISAB_FILTRI] > 1.5) //abilta la gestione abilitazione/disabilitazione filtri da plc anche per asse A
				{
					status = 410;  //proseguo comunque per non bloccare la macchina in FATM
				}
				else
				{
					status = 900;  //termino comunque per non bloccare la macchina in FATM
				}
			}

		// ASSE A /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		case 410:
			{
				setAxisFilter(0, AX_A_CH0, enable_disable, &s);
				rtplctrace4(1,_T("Richiesta abilitazione / disabilitazione %f filtro su asse A" ), enable_disable);
				status = 420;
			} 
		break;			

		case 420:
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
			if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 440;
			} else {
				rtplctrace4(1,_T("Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 430;
			}
		break;

		case 430:
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
			if (FB_SUCCESS(fbResult)) {
				rtplctrace4(1,_T("Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)"), 
					s.command, s.channel, s.axis,
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 510;
			} else if (FB_FAILURE(fbResult)) {
				rtplctrace4(1,_T("Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)"), 
					RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
					s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
				status = 440;
			}
		break;

		case 440: //Stato di errore su abilitazione / disabilitazione filtro su asse A
			{
				CONT_ABIL_DISABIL_A++;  //incrementa il numero di tentativi di abilitare / disabilitare filtri su asse A
				rtplctrace4(1,_T("Errore abilitazione / disabilitazione filtro su asse A "));
				if(CONT_ABIL_DISABIL_A < 3) // tenta 3 volte di abilitare / disabilitare filtri
				{
					status = 410;
					//Mr_MC(255);  Mr_MC(256);
				}
				else
				{
					status = 510;  //proseguo comunque per non bloccare la macchina in FATM
				}
			}
		break;

		// FINE /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case 900:  //disabilitazione / abilitazione filtri terminata con successo
			{
				DISABLE_FILTRI_XYZA = 0;
				ENABLE_FILTRI_XYZA = 0;
				Mr_MC(255);  
				Mr_MC(256);
				status = 0;
			}
			break;

		default:
			{
				DISABLE_FILTRI_XYZA = 0;
				ENABLE_FILTRI_XYZA = 0;
				Mr_MC(255);
				Mr_MC(256);
				status = 0;
			}
			break;
		}
	} //if( R[R_ENAB_DISAB_FILTRI] > 0.5 )
	else
	{
		Mr_MC(255);
		Mr_MC(256);
	}
}


void setAxisFilter(USHORT channel, USHORT axis, double enable_disable, CmdAxisStruct* s) {
	s->channel = channel;
	s->axis = axis;
	s->command = OMCNC_CMD_PUTPARAM;
	s->param.param[0] = 0x08005009;        //axppcAxisFilter???  devono ancora implementarlo!!!
	s->param.param[1] = enable_disable;
}