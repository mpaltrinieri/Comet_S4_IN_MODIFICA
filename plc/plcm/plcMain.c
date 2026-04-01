#define _INTERNAL_GENERATION

#include "all.inc"

BOOL initPlcArea(BOOL reset, LPVOID data, PPLCMAIN_LOCVARS locvars);


/*
The plcTimer routine
*/
void RTPLC_ROUTINE stub_plcMain(LPVOID data, PPLCMAIN_LOCVARS locvars) 
{
    RTPLC_STATUS fbResult = RTPLC_STATUS_OK;

    //if (waitDebugger) return;
	if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
	{
		//if (p_dplc_v3) SIMULATORE_ON = 1;
	}

   iomap(locvars, TRUE);

    switch (plcStatus) {
        case 0:
            ACTIVATE_WD_ON_RESET(RTPLC_TRUE); // Caduta contatto aux al reset del Framework
            NEXT_STATUS(plcStatus, "Attivato contatto aux su reset framework");
            locvars->pilotStatus = PILOT_STATUS_NONE; // Reset macchina a stati funzioni manuali

        case 1:
            initPlcArea(TRUE, data, locvars);
            NEXT_STATUS(plcStatus, "");
        case 2:
            if (initPlcArea(FALSE, data, locvars)) {
                NEXT_STATUS(plcStatus, "Inizializzazione aree di memoria avvenuta con successo");
            } else {
                INIT_ERROR_FAL = 1;
                ERROR_STATUS(plcStatus, "Errore durante l'inizializzazione delle aree di memoria");
            }
            break;

        case W322RTPLC_STATUS(2):
            if (INIT_ERROR_FAL)
                allarm(INIT_ERROR_AL);
            break;

        case 3:
            processConfmac(TRUE);
            NEXT_STATUS(plcStatus, "Inizio lettura confmac.");
        case 4:
            fbResult = processConfmac(FALSE);
            if (FB_FAILURE(fbResult)) 
			{
                CONFMAC_ERROR_FAL = 1;
                ERROR_STATUS(plcStatus, "Errore durante la lettura del confmac");
            } 
			else if (FB_SUCCESS(fbResult)) 
			{
                NEXT_STATUS(plcStatus, "Lettura confmac terminata con successo");
            }
            break;

        case W322RTPLC_STATUS(4):
            if (CONFMAC_ERROR_FAL)
                allarm(CONFMAC_ERROR_AL);
            break;

        case 5:
            PON = TRUE; // Inizio pon
            NEXT_STATUS(plcStatus, "Inizializzo il PLC");
        case 6: // Ciclo plc

			templc();	 // Routine temporizzati
            cnctempor(); // Gestione temporizzatori come in v6.5

			///warning cncReady corrisponde a IO_EXE che e` tirato su al pon dal plc
			if (!CNCSTATUS.cncReady && (!pon_CH0)) return;
			if (!CNCSTATUS_CH1.cncReady && (!pon_CH1)) return;
			if (!CNCSTATUS_CH2.cncReady && (!pon_CH2)) return;

            plc(locvars);		 // Routine principale PLC

	        // Aggiornamento della coda dei messaggi
            rec_code[rec_queuetop] = 0;
            rec_queuetop++;
            if (rec_queuetop > rec_queuebottom) { // Scodata tutta la coda dei messaggi
                rec_queuetop = 0;
                rec_queuebottom = 0;
            }
            if (PON) {
                locvars->pilotStatus = PILOT_STATUS_START; // Carico le funzioni manuali

                pio->exe = IO_EXE; // Abilitazione uscite fisiche

				pio_v2_CH1->exe = IO_EXE;
				pio_v2_CH2->exe = IO_EXE;

                PON = FALSE;       // Fine pon
                LOG_MSG2(1, "Fine ciclo di PON ed attivazione uscite");
            }
            set_io_exe();      // Plc in esecuzione
        break;

        default:
            break;
    }

    switch (locvars->pilotStatus) 
	{
        case PILOT_STATUS_NONE:
            MGPILOT_ERROR_FAL = 0;
            MGPILOT_ERROR_FMS = 0;

            REMCTRL_ERROR_FAL = 0;
            REMCTRL_ERROR_FMS = 0;
            break;

        case PILOT_STATUS_START:
            if (CONF_MGPILOT) {
                MGPILOT_ERROR_FMS = 1;
                JUMP_STATUS(locvars->pilotStatus, PILOT_STATUS_MGPILOT, "Trovata configurazione per MGPilot");
            } else {
				if(!SIMULATORE_ON)
				{
                REMCTRL_ERROR_FMS = 1;
				}
                JUMP_STATUS(locvars->pilotStatus, PILOT_STATUS_REMCTRL, "Trovata configurazione per REM_CTRL");
            }
            break;

        case PILOT_STATUS_MGPILOT: // Caricamento funzioni manuali nel pilot (reset)
            loadMGPilot(TRUE);
            loadCncMsg(TRUE);
            NEXT_STATUS(locvars->pilotStatus, "Inizio lettura funzioni manuali");
        case PILOT_STATUS_MGPILOT+1: // Caricamento funzioni manuali nel pilot
        case PILOT_STATUS_MGPILOT+3:
            fbResult = loadMGPilot(FALSE);
            if (FB_FAILURE(fbResult)) {
                MGPILOT_ERROR_FAL = 1;
                ERROR_STATUS(locvars->pilotStatus, "Errore durante il caricamento delle funzioni manuali");
            } else if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(locvars->pilotStatus, "Caricamento funzioni manuali terminato con successo");
            }
            if (locvars->pilotStatus == (PILOT_STATUS_MGPILOT+3)) break;
        case PILOT_STATUS_MGPILOT+2: // Caricamento allarmi e messaggi pilot
            MGPILOT_ERROR_FMS = 0;
			REMCTRL_ERROR_FMS = 0;
            break; //TODO: test emissioni allarmi / messaggi
            fbResult = loadCncMsg(FALSE);
            if (FB_FAILURE(fbResult)) {
                MGPILOT_ERROR_FAL = 1;
                ERROR_STATUS(locvars->pilotStatus, "Errore durante il caricamento della lista degli allarmi e messaggi");
            } else if (FB_SUCCESS(fbResult)) {
                JUMP_STATUS(locvars->pilotStatus, locvars->pilotStatus+2, "Caricamento lista allarmi e messaggi terminato con successo");
            }
            break;
        case PILOT_STATUS_MGPILOT+4:
            updateF2F3(TRUE);
            NEXT_STATUS(locvars->pilotStatus, "");
        case PILOT_STATUS_MGPILOT+5: // Aggiornamento stato pilot
            fbResult = updateF2F3(FALSE);
            if (FB_FAILURE(fbResult))
                ERROR_STATUS(locvars->pilotStatus, "Errore aggiornamento menu F2 ed F3 pilot");
            break;
        case W322RTPLC_STATUS(PILOT_STATUS_MGPILOT+1):
        case W322RTPLC_STATUS(PILOT_STATUS_MGPILOT+2):
        case W322RTPLC_STATUS(PILOT_STATUS_MGPILOT+3):
            MGPILOT_ERROR_FAL = !AUTO;
            MGPILOT_ERROR_FMS = AUTO;
            break;
        case W322RTPLC_STATUS(PILOT_STATUS_MGPILOT+5):
            break;

        case PILOT_STATUS_REMCTRL: // Scrittura REM_CTRL (reset)
            writeRemCtrl(TRUE);
            NEXT_STATUS(locvars->pilotStatus, "Inizio aggiornamento REM_CTRL");
        case PILOT_STATUS_REMCTRL+1: // Scrittura REM_CTRL
            fbResult = writeRemCtrl(FALSE);
            if (FB_FAILURE(fbResult)) {
                REMCTRL_ERROR_FAL = 1;
                ERROR_STATUS(locvars->pilotStatus, "Errore durante l'aggiornamento del REM_CTRL");
            } else if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(locvars->pilotStatus, "Aggiornamento REM_CTRL terminato con successo");
            }
            break;
        case PILOT_STATUS_REMCTRL+2:
            break;
        case W322RTPLC_STATUS(PILOT_STATUS_REMCTRL+1):
            REMCTRL_ERROR_FAL = !AUTO;
            REMCTRL_ERROR_FMS = AUTO;
            break;

        default:
            break;
    }

    iomap(locvars, FALSE);
}

void RTPLC_ROUTINE plcMain(LPVOID data) {
  PULONG pt = (PULONG)data;
  PPLCMAIN_LOCVARS pstruct = (PPLCMAIN_LOCVARS)(pt + 1);
  stub_plcMain((LPVOID)(*pt), pstruct);
}


// Inizializzazioni
BOOL initPlcArea(BOOL reset, LPVOID data, PPLCMAIN_LOCVARS locvars)
{
    BOOL result = TRUE;

    FB_ENTER();

    if (reset) {
        FB_RESET();

        Aris = NULL;
        R = NULL;
        Acus = NULL;
        RR = NULL;
        p_m = NULL;
        p_dplc_v3 = NULL;
        ppckey = NULL;
        pn_xout = NULL;
        pn_xin = NULL;
        pn_arec_v2 = NULL;
        pn_ared_v2 = NULL;
        pn_sarec = NULL;
        pn_key = NULL;
        pio_v2 = NULL;
        pdiag = NULL;
        pn_visplc_v2 = NULL;
        psin = NULL;
        pcnf_v2 = NULL;
        paretplc_v2 = NULL;
        pn_dmand = NULL;
        //memset(g_pointerDataMem, 0, sizeof(g_pointerDataMem));
        //memset(&g_header, 0, sizeof(g_header));
        //memset(g_Handle, 0, sizeof(g_Handle));

		//Ch1
        Aris_CH1 = NULL;
        R_CH1 = NULL;
		Acus_CH1 = NULL;
        RR_CH1 = NULL;
		p_m_CH1 = NULL;
        p_dplc_v3_CH1 = NULL;

        ppckey_CH1 = NULL;
        pn_xout_CH1 = NULL;
        pn_xin_CH1 = NULL;
        pn_arec_v2_CH1 = NULL;
        pn_ared_v2_CH1 = NULL;
        pn_sarec_CH1 = NULL;
        pn_key_CH1 = NULL;
        pio_v2_CH1 = NULL;
        pdiag_CH1 = NULL;
        pn_visplc_v2_CH1 = NULL;
        psin_CH1 = NULL;
        pcnf_v2_CH1 = NULL;
        paretplc_v2_CH1 = NULL;
        pn_dmand_CH1 = NULL;


		//Ch2
        Aris_CH2 = NULL;
        R_CH2 = NULL;
        Acus_CH2 = NULL;
        RR_CH2 = NULL;
		p_m_CH2 = NULL;
        p_dplc_v3_CH2 = NULL;

        ppckey_CH2 = NULL;
        pn_xout_CH2 = NULL;
        pn_xin_CH2 = NULL;
        pn_arec_v2_CH2 = NULL;
        pn_ared_v2_CH2 = NULL;
        pn_sarec_CH2 = NULL;
        pn_key_CH2 = NULL;
        pio_v2_CH2 = NULL;
        pdiag_CH2 = NULL;
        pn_visplc_v2_CH2 = NULL;
        psin_CH2 = NULL;
        pcnf_v2_CH2 = NULL;
        paretplc_v2_CH2 = NULL;
        pn_dmand_CH2 = NULL;

        FB_EXIT(FB_EXIT_SUCCESS);
    }


    // Aree R
    if (!Aris) Aris = (double*)GetDatiCnc(ARERRE);
    if (!Aris) result = FALSE;
	
    if (!R) R = &CNC_AREA_R(0);
    if (!R) result = FALSE;

    // Aree cancelletto
    if (!Acus) Acus = (double*)GetDatiCnc(ARECANC);
    if (!Acus) result = FALSE;

    // Aree retentive
    if (!p_m) p_m = (DATI*)p_ms;
    if (!p_m) result = FALSE;

    // Tenporizzatori, aree A ed aree B
    if (!p_dplc_v3) p_dplc_v3 = (PCNCPLC_DATA)GetDatiPlc(INTERNAL_PLCAREA);
    if (!p_dplc_v3) result = FALSE;

    // Aree tasti
    if (!ppckey) ppckey = (PCKEY*)GetDatiCnc(AREA_PCKEY);
    if (!ppckey) result = FALSE;

    // Uscite assi
    if (!pn_xout) pn_xout = (N_XOUT*)GetDatiCnc(AREA_N_XOUT);
    if (!pn_xout) result = FALSE;

    // Ingressi assi
    if (!pn_xin) pn_xin = (N_XIN*)GetDatiCnc(AREA_N_XIN);
    if (!pn_xin) result = FALSE;

    // Aree C
    if (!pn_arec_v2) pn_arec_v2 = (N_AREC_V3*)GetDatiCnc(AREA_N_AREC_V3);
    if (!pn_arec_v2) result = FALSE;

    // Aree D
    if (!pn_ared_v2) pn_ared_v2 = (N_ARED_V3*)GetDatiCnc(AREA_N_ARED_V3);
    if (!pn_ared_v2) result = FALSE;

    if (!pn_sarec) pn_sarec = (N_SAREC*)GetDatiCnc(AREA_N_SAREC);
    if (!pn_sarec) result = FALSE;

    if (!pn_key) pn_key = (N_KEY*)GetDatiCnc(AREA_N_KEY);
    if (!pn_key) result = FALSE;

    // Struttura I/O vari
    if (!pio_v2) pio_v2 = (IO_V3*)GetDatiCnc(AREA_IO_V3);
    if (!pio_v2) result = FALSE;

    if (!pdiag) pdiag = (DIAG*)GetDatiCnc(AREA_DIAG);
    if (!pdiag) result = FALSE;

    if (!pn_visplc_v2) pn_visplc_v2 = (N_VISPLC_V2*)GetDatiCnc(AREA_N_VISPLC_V2);
    if (!pn_visplc_v2) result = FALSE;

    // Strutture sincronismo
    if (!psin) psin = (SIN*)GetDatiCnc(AREA_SIN);
    if (!psin) result = FALSE;

    // Struttura configurazione
    if (!pcnf_v2) pcnf_v2 = (CNF_V2*)GetDatiCnc(AREA_CNF_V2);
    if (!pcnf_v2) result = FALSE;

    // Aree C ed R retentive
    if (!paretplc_v2) {
        paretplc_v2 = (ARETPLC_V4*)GetDatiCnc(AREA_ARETPLC_V4);
        RR = &CNC_AREA_RRET(0);    
    }
    if (!paretplc_v2) result = FALSE;

    // Taratura mandrino
    if (!pn_dmand) pn_dmand = (N_DMAND_V3*)GetDatiCnc(AREA_N_DMAND_V3);
    if (!pn_dmand) result = FALSE;

    //if (!g_header.singleHeader[0]) g_header.singleHeader[0] = (PSCHECMD_SINGLE_HEADER)GianoSharedAreaMaster.sharedmem;
    //if (!g_header.singleHeader[0]) result = FALSE;

    //if (!g_pointerDataMem[0]) g_pointerDataMem[0] = (PPLC_IO_DATA2)((PUCHAR)GianoSharedAreaMaster.sharedmem + sizeof(SCHECMD_SINGLE_HEADER));
    //if (!g_pointerDataMem[0]) result = FALSE;

    //if (!g_header.singleHeader[1]) g_header.singleHeader[1] = (PSCHECMD_SINGLE_HEADER)GianoSharedAreaSlave0.sharedmem;
    //if (!g_header.singleHeader[1]) result = FALSE;

    //if (!g_pointerDataMem[1]) g_pointerDataMem[1] = (PPLC_IO_DATA2)((PUCHAR)GianoSharedAreaSlave0.sharedmem + sizeof(SCHECMD_SINGLE_HEADER));
    //if (!g_pointerDataMem[1]) result = FALSE;

    //if (!g_header.singleHeader[2]) g_header.singleHeader[2] = (PSCHECMD_SINGLE_HEADER)GianoSharedAreaSlave1.sharedmem;
    //if (!g_header.singleHeader[2]) result = FALSE;

    //if (!g_pointerDataMem[2]) g_pointerDataMem[2] = (PPLC_IO_DATA2)((PUCHAR)GianoSharedAreaSlave1.sharedmem + sizeof(SCHECMD_SINGLE_HEADER));
    //if (!g_pointerDataMem[2]) result = FALSE;

    //if (!g_header.singleHeader[3]) g_header.singleHeader[3] = (PSCHECMD_SINGLE_HEADER)GianoSharedAreaSlave2.sharedmem;
    //if (!g_header.singleHeader[3]) result = FALSE;

    //if (!g_pointerDataMem[3]) g_pointerDataMem[3] = (PPLC_IO_DATA2)((PUCHAR)GianoSharedAreaSlave2.sharedmem + sizeof(SCHECMD_SINGLE_HEADER));
    //if (!g_pointerDataMem[3]) result = FALSE;

    //if (!g_header.singleHeader[4]) g_header.singleHeader[4] = (PSCHECMD_SINGLE_HEADER)GianoSharedAreaSlave3.sharedmem;
    //if (!g_header.singleHeader[4]) result = FALSE;

    //if (!g_pointerDataMem[4]) g_pointerDataMem[4] = (PPLC_IO_DATA2)((PUCHAR)GianoSharedAreaSlave3.sharedmem + sizeof(SCHECMD_SINGLE_HEADER));
    //if (!g_pointerDataMem[4]) result = FALSE;

    //memset(g_OffSetArea, 0, sizeof(g_OffSetArea)); 

    //// Aree condivise
    //if (!initSharedMem()) result = FALSE;

#if defined(GIANO_DEFINED) || defined(GIANO_DEFINED_71)
    //if (ScheCmd2_plcInit(NULL, 1, 0, 0)) result = FALSE // Gestione MMI
    if (ScheCmd2_plcInit(NULL, 0, 0, 0)) result = FALSE; // Gestione PLC
#endif

    // Inizializzazione prima istanza multiprocesso 
#if defined(GIANO_DEFINED) || defined(GIANO_DEFINED_71)
    {short exitcode = 0; 
    if (!g_Handle[0])
//old   g_Handle[0] = ScheCmd2_init(AREACAN, 610, 5, 380, 0, 0, 0, 0, &exitcode);
        g_Handle[0] = ScheCmd2_init(AREACAN, 610, 5,  25, 0, 0, 0, 0, &exitcode);
    if (exitcode || !g_Handle[0]) {
        g_Handle[0] = NULL;
        //tolto come quadra@: result = FALSE; 
			LOG_MSG2(1, "exitcode || !g_Handle[0]");
    }}
#endif

    // Inizializzazione seconda istanza multiprocesso 
#if defined(GIANO_DEFINED) || defined(GIANO_DEFINED_71)
    {short exitcode = 0; 
    if (!g_Handle[1])
//old   g_Handle[1] = ScheCmd2_init(AREACAN, 710, 6, 380, 0, 0, 0, 0, &exitcode);
        g_Handle[1] = ScheCmd2_init(AREACAN, 710, 6,  25, 0, 0, 0, 0, &exitcode);
    if (exitcode || !g_Handle[1]) {
        g_Handle[1] = NULL;
        //tolto come quadra@: result = FALSE; 
			LOG_MSG2(1, "exitcode || !g_Handle[1]");
    }}
#endif

    // Reset aree assi
    memset(AXSTATUS, 0, sizeof(AXSTATUS));
    memset(AXCTRL, 0, sizeof(AXCTRL));
    memset(&CNCSTATUS, 0, sizeof(CNCSTATUS));
    memset(&CNCCTRL, 0, sizeof(CNCCTRL));
    memset(&CNPLCHANDLE, 0, sizeof(CNPLCHANDLE));
    memset(DIGITALIN, 0, sizeof(DIGITALIN));
    memset(DIGITALOUT, 0, sizeof(DIGITALOUT));
    memset(ANALOGIN, 0, sizeof(ANALOGIN));
    memset(ANALOGOUT, 0, sizeof(ANALOGOUT));


	//Ch1

    if (!Aris_CH1) Aris_CH1 = (double *) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), ARERRE);
    if (!Aris_CH1) result = FALSE;

	if(!R_CH1) R_CH1 = &CNC_AREA_R_CH1(0);
	if(!R_CH1) result = FALSE; 

	if (!Acus_CH1) Acus_CH1 = (double*)GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), ARECANC);
    if (!Acus_CH1) result = FALSE;

	if (!p_m_CH1) p_m_CH1 = (DATI *) p_ms_CH1;
    if (!p_m_CH1) result = FALSE;

	if (!p_dplc_v3_CH1) p_dplc_v3_CH1 = (PCNCPLC_DATA) GetDatiPlc_MC (&(locvars->CNCSTATUS_l_CH1), INTERNAL_PLCAREA);
	if (!p_dplc_v3_CH1) result = FALSE;
	
	if (!ppckey_CH1) ppckey_CH1 = (PCKEY*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_PCKEY);
    if (!ppckey_CH1) result = FALSE;

	if (!pn_xout_CH1) pn_xout_CH1 = (N_XOUT*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_XOUT);
    if (!pn_xout_CH1) result = FALSE;

	if (!pn_xin_CH1) pn_xin_CH1 = (N_XIN*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_XIN);
    if (!pn_xin_CH1) result = FALSE;

	if (!pn_arec_v2_CH1) pn_arec_v2_CH1 = (N_AREC_V3*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_AREC_V3);
    if (!pn_arec_v2_CH1) result = FALSE;

	if (!pn_ared_v2_CH1) pn_ared_v2_CH1 = (N_ARED_V3*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_ARED_V3);
    if (!pn_ared_v2_CH1) result = FALSE;

	if (!pn_sarec_CH1) pn_sarec_CH1 = (N_SAREC*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_SAREC);
    if (!pn_sarec_CH1) result = FALSE;

	if (!pn_key_CH1) pn_key_CH1 = (N_KEY*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_KEY);
    if (!pn_key_CH1) result = FALSE;

	if (!pio_v2_CH1) pio_v2_CH1 = (IO_V3*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_IO_V3);
    if (!pio_v2_CH1) result = FALSE;

	if (!pdiag_CH1) pdiag_CH1 = (DIAG*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_DIAG);
    if (!pdiag_CH1) result = FALSE;

	if (!pn_visplc_v2_CH1) pn_visplc_v2_CH1 = (N_VISPLC_V2 *) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_VISPLC_V2);
    if (!pn_visplc_v2_CH1) result = FALSE;

	if (!psin_CH1) psin_CH1 = (SIN*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_SIN);
    if (!psin_CH1) result = FALSE;

	if (!pcnf_v2_CH1) pcnf_v2_CH1 = (CNF_V2*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_CNF_V2);
    if (!pcnf_v2_CH1) result = FALSE;

    if (!paretplc_v2_CH1) {
        paretplc_v2_CH1 = (ARETPLC_V4*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_ARETPLC_V4);
        RR_CH1 = &CNC_AREA_RRET_CH1(0);	
    }
    if (!paretplc_v2_CH1) result = FALSE;

	if (!pn_dmand_CH1) pn_dmand_CH1 = (N_DMAND_V3 *) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH1), AREA_N_DMAND_V3);
    if (!pn_dmand_CH1) result = FALSE;

    // Reset aree assi
    memset(AXSTATUS_CH1, 0, sizeof(AXSTATUS_CH1));
	memset(AXCTRL_CH1, 0, sizeof(AXCTRL_CH1));
	memset(&CNCSTATUS_CH1, 0, sizeof(CNCSTATUS_CH1));
	memset(&CNCCTRL_CH1, 0, sizeof(CNCCTRL_CH1));
	memset(&CNPLCHANDLE_CH1, 0, sizeof(CNPLCHANDLE_CH1));


	//Ch2

	if (!Aris_CH2) Aris_CH2 = (double *) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), ARERRE);
    if (!Aris_CH2) result = FALSE;

	if(!R_CH2) R_CH2 = &CNC_AREA_R_CH2(0);
	if(!R_CH2) result = FALSE; 

	if (!Acus_CH2) Acus_CH2  = (double*)GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), ARECANC);
    if (!Acus_CH2) result = FALSE;

	if (!p_m_CH2) p_m_CH2 = (DATI *) p_ms_CH2;
    if (!p_m_CH2) result = FALSE;

	if (!p_dplc_v3_CH2) p_dplc_v3_CH2 = (PCNCPLC_DATA) GetDatiPlc_MC (&(locvars->CNCSTATUS_l_CH2), INTERNAL_PLCAREA);
	if (!p_dplc_v3_CH2) result = FALSE;

	if (!ppckey_CH2) ppckey_CH2 = (PCKEY*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_PCKEY);
    if (!ppckey_CH2) result = FALSE;

	if (!pn_xout_CH2) pn_xout_CH2 = (N_XOUT*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_XOUT);
    if (!pn_xout_CH2) result = FALSE;

	if (!pn_xin_CH2) pn_xin_CH2 = (N_XIN*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_XIN);
    if (!pn_xin_CH2) result = FALSE;

	if (!pn_arec_v2_CH2) pn_arec_v2_CH2 = (N_AREC_V3*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_AREC_V3);
    if (!pn_arec_v2_CH2) result = FALSE;

	if (!pn_ared_v2_CH2) pn_ared_v2_CH2 = (N_ARED_V3*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_ARED_V3);
    if (!pn_ared_v2_CH2) result = FALSE;

	if (!pn_sarec_CH2) pn_sarec_CH2 = (N_SAREC*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_SAREC);
    if (!pn_sarec_CH2) result = FALSE;

	if (!pn_key_CH2) pn_key_CH2 = (N_KEY*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_KEY);
    if (!pn_key_CH2) result = FALSE;

	if (!pio_v2_CH2) pio_v2_CH2 = (IO_V3*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_IO_V3);
    if (!pio_v2_CH2) result = FALSE;

	if (!pdiag_CH2) pdiag_CH2 = (DIAG*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_DIAG);
    if (!pdiag_CH2) result = FALSE;

	if (!pn_visplc_v2_CH2) pn_visplc_v2_CH2 = (N_VISPLC_V2 *) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_VISPLC_V2);
    if (!pn_visplc_v2_CH2) result = FALSE;

	if (!psin_CH2) psin_CH2 = (SIN*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_SIN);
    if (!psin_CH2) result = FALSE;

	if (!pcnf_v2_CH2) pcnf_v2_CH2 = (CNF_V2*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_CNF_V2);
    if (!pcnf_v2_CH2) result = FALSE;

    if (!paretplc_v2_CH2) {
        paretplc_v2_CH2 = (ARETPLC_V4*) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_ARETPLC_V4);
        RR_CH2 = &CNC_AREA_RRET_CH2(0);	
    }
    if (!paretplc_v2_CH2) result = FALSE;

	if (!pn_dmand_CH2) pn_dmand_CH2 = (N_DMAND_V3 *) GetDatiCnc_MC (&(locvars->CNCSTATUS_l_CH2), AREA_N_DMAND_V3);
    if (!pn_dmand_CH2) result = FALSE;

    // Reset aree assi
    memset(AXSTATUS_CH2, 0, sizeof(AXSTATUS_CH2));
	memset(AXCTRL_CH2, 0, sizeof(AXCTRL_CH2));
	memset(&CNCSTATUS_CH2, 0, sizeof(CNCSTATUS_CH2));
	memset(&CNCCTRL_CH2, 0, sizeof(CNCCTRL_CH2));
	memset(&CNPLCHANDLE_CH2, 0, sizeof(CNPLCHANDLE_CH2));

    return result;
}


// Copia strutture locali su variabili globali e viceversa
void iomap(PPLCMAIN_LOCVARS locvars, BOOL direction)
{
    if (direction) {
        // Copia delle strutture da locali a globali
        memcpy(AXSTATUS, locvars->AXSTATUS, sizeof(CNCPLC_AXIS_STATUS)*min(CONFCN.n_ax, ARRAY_SIZE(AXSTATUS)));
        memcpy(AXCTRL, locvars->AXCTRL, sizeof(CNCPLC_AXIS_CTRL)*min(CONFCN.n_ax, ARRAY_SIZE(AXCTRL)));
        memcpy(&CNCSTATUS, &locvars->CNCSTATUS, sizeof(CNPLC_CNCSTATUS));
        memcpy(&CNCCTRL, &locvars->CNCCTRL, sizeof(CNPLC_CNCCTRL));
        memcpy(&CNPLCHANDLE, &locvars->CNPLCHANDLE, sizeof(CNPLC_HANDLE));

		//ch1
		memcpy (AXSTATUS_CH1, locvars->AXSTATUS_l_CH1, sizeof(CNCPLC_AXIS_STATUS)* (min(CONFCN_CH1.n_ax, ARRAY_SIZE (AXSTATUS))));
		memcpy (AXCTRL_CH1, locvars->AXCTRL_l_CH1, sizeof(CNCPLC_AXIS_CTRL)* (min(CONFCN_CH1.n_ax, ARRAY_SIZE (AXCTRL))));
		memcpy (&CNCSTATUS_CH1, &locvars->CNCSTATUS_l_CH1, sizeof(CNPLC_CNCSTATUS));
		memcpy (&CNCCTRL_CH1, &locvars->CNCCTRL_l_CH1, sizeof(CNPLC_CNCCTRL));
		memcpy (&CNPLCHANDLE_CH1, &locvars->CNPLCHANDLE_l_CH1, sizeof(CNPLC_HANDLE));

		//ch2
		memcpy (AXSTATUS_CH2, locvars->AXSTATUS_l_CH2, sizeof(CNCPLC_AXIS_STATUS)* (min(CONFCN_CH2.n_ax, ARRAY_SIZE (AXSTATUS))));
		memcpy (AXCTRL_CH2, locvars->AXCTRL_l_CH2, sizeof(CNCPLC_AXIS_CTRL)* (min(CONFCN_CH2.n_ax, ARRAY_SIZE (AXCTRL))));
		memcpy (&CNCSTATUS_CH2, &locvars->CNCSTATUS_l_CH2, sizeof(CNPLC_CNCSTATUS));
		memcpy (&CNCCTRL_CH2, &locvars->CNCCTRL_l_CH2, sizeof(CNPLC_CNCCTRL));
		memcpy (&CNPLCHANDLE_CH2, &locvars->CNPLCHANDLE_l_CH2, sizeof(CNPLC_HANDLE));

         // Scheda 1
        DIGITALIN[0][0] = locvars->DIGITALIN_00_00;
        DIGITALIN[0][1] = locvars->DIGITALIN_00_01;
        DIGITALIN[0][2] = locvars->DIGITALIN_00_02;
        DIGITALIN[0][3] = locvars->DIGITALIN_00_03;
        DIGITALIN[0][4] = locvars->DIGITALIN_00_04;
        DIGITALIN[0][5] = locvars->DIGITALIN_00_05;
        DIGITALIN[0][6] = locvars->DIGITALIN_00_06;
        DIGITALIN[0][7] = locvars->DIGITALIN_00_07;
        DIGITALIN[0][8] = locvars->DIGITALIN_00_08;
        DIGITALIN[0][9] = locvars->DIGITALIN_00_09;
        DIGITALIN[0][10] = locvars->DIGITALIN_00_10;
        DIGITALIN[0][11] = locvars->DIGITALIN_00_11;
        DIGITALIN[0][12] = locvars->DIGITALIN_00_12;
        DIGITALIN[0][13] = locvars->DIGITALIN_00_13;
        DIGITALIN[0][14] = locvars->DIGITALIN_00_14;
        DIGITALIN[0][15] = locvars->DIGITALIN_00_15;
        DIGITALIN[0][16] = locvars->DIGITALIN_00_16;
        DIGITALIN[0][17] = locvars->DIGITALIN_00_17;
        //DIGITALOUT[0][0] = locvars->DIGITALOUT_00_00;
        //DIGITALOUT[0][1] = locvars->DIGITALOUT_00_01;
        //DIGITALOUT[0][2] = locvars->DIGITALOUT_00_02;
        //DIGITALOUT[0][3] = locvars->DIGITALOUT_00_03;
        //DIGITALOUT[0][4] = locvars->DIGITALOUT_00_04;
        //DIGITALOUT[0][5] = locvars->DIGITALOUT_00_05;
        //DIGITALOUT[0][6] = locvars->DIGITALOUT_00_06;
        //DIGITALOUT[0][7] = locvars->DIGITALOUT_00_07;
        //DIGITALOUT[0][8] = locvars->DIGITALOUT_00_08;
        //DIGITALOUT[0][9] = locvars->DIGITALOUT_00_09;
        //DIGITALOUT[0][10] = locvars->DIGITALOUT_00_10;
        //DIGITALOUT[0][11] = locvars->DIGITALOUT_00_11;
        //DIGITALOUT[0][12] = locvars->DIGITALOUT_00_12;
        //DIGITALOUT[0][13] = locvars->DIGITALOUT_00_13;
        //DIGITALOUT[0][14] = locvars->DIGITALOUT_00_14;
        //DIGITALOUT[0][15] = locvars->DIGITALOUT_00_15;
        //DIGITALOUT[0][16] = locvars->DIGITALOUT_00_16;
        //DIGITALOUT[0][17] = locvars->DIGITALOUT_00_17;
        ANALOGIN[0][0] = locvars->ANALOGIN_00_00;
        ANALOGIN[0][1] = locvars->ANALOGIN_00_01;
        ANALOGIN[0][2] = locvars->ANALOGIN_00_02;
        ANALOGIN[0][3] = locvars->ANALOGIN_00_03;
        ANALOGIN[0][4] = locvars->ANALOGIN_00_04;
        ANALOGIN[0][5] = locvars->ANALOGIN_00_05;
        ANALOGIN[0][6] = locvars->ANALOGIN_00_06;
        ANALOGIN[0][7] = locvars->ANALOGIN_00_07;
        ANALOGIN[0][8] = locvars->ANALOGIN_00_08;
        ANALOGIN[0][9] = locvars->ANALOGIN_00_09;
        ANALOGIN[0][10] = locvars->ANALOGIN_00_10;
		ANALOGIN[0][11] = locvars->ANALOGIN_00_11;
        //ANALOGOUT[0][0] = locvars->ANALOGOUT_00_00;
		//ANALOGOUT[0][1] = locvars->ANALOGOUT_00_01;
        //ANALOGOUT[0][2] = locvars->ANALOGOUT_00_02;
		//ANALOGOUT[0][3] = locvars->ANALOGOUT_00_03;
        //ANALOGOUT[0][4] = locvars->ANALOGOUT_00_04;
		//ANALOGOUT[0][5] = locvars->ANALOGOUT_00_05;
		ENCODERIN[0][0] = locvars->ENCODERIN_00_00;

        // Scheda 2
        //DIGITALIN[1][0] = locvars->DIGITALIN_01_00;
        //DIGITALIN[1][1] = locvars->DIGITALIN_01_01;
        //DIGITALIN[1][2] = locvars->DIGITALIN_01_02;
        //DIGITALOUT[1][0] = locvars->DIGITALOUT_01_00;
        //DIGITALOUT[1][1] = locvars->DIGITALOUT_01_01;
        //DIGITALOUT[1][2] = locvars->DIGITALOUT_01_02;
        //ANALOGIN[1][0] = locvars->ANALOGIN_01_00;
        //ANALOGIN[1][1] = locvars->ANALOGIN_01_01;
        //ANALOGOUT[1][0] = locvars->ANALOGOUT_01_00;

        // Scheda 3
        //DIGITALIN[2][0] = locvars->DIGITALIN_02_00;
        //DIGITALIN[2][1] = locvars->DIGITALIN_02_01;
        //DIGITALIN[2][2] = locvars->DIGITALIN_02_02;
        //DIGITALOUT[2][0] = locvars->DIGITALOUT_02_00;
        //DIGITALOUT[2][1] = locvars->DIGITALOUT_02_01;
        //DIGITALOUT[2][2] = locvars->DIGITALOUT_02_02;
        //ANALOGIN[2][0] = locvars->ANALOGIN_02_00;
        //ANALOGIN[2][1] = locvars->ANALOGIN_02_01;
        //ANALOGOUT[2][0] = locvars->ANALOGOUT_02_00;

        // Scheda 4
        //DIGITALIN[3][0] = locvars->DIGITALIN_03_00;
        //DIGITALIN[3][1] = locvars->DIGITALIN_03_01;
        //DIGITALIN[3][2] = locvars->DIGITALIN_03_02;
        //DIGITALOUT[3][0] = locvars->DIGITALOUT_03_00;
        //DIGITALOUT[3][1] = locvars->DIGITALOUT_03_01;
        //DIGITALOUT[3][2] = locvars->DIGITALOUT_03_02;
        //ANALOGIN[3][0] = locvars->ANALOGIN_03_00;
        //ANALOGIN[3][1] = locvars->ANALOGIN_03_01;
		//ANALOGOUT[3][0] = locvars->ANALOGOUT_03_00;

        // Scheda 5 (MGPILOT)
        DIGITALIN[4][0] = locvars->DIGITALIN_04_00;
        DIGITALIN[4][1] = locvars->DIGITALIN_04_01;
        DIGITALIN[4][2] = locvars->DIGITALIN_04_02;
        //DIGITALOUT[4][0] = locvars->DIGITALOUT_04_00;
        //DIGITALOUT[4][1] = locvars->DIGITALOUT_04_01;
        //DIGITALOUT[4][2] = locvars->DIGITALOUT_04_02;
        ANALOGIN[4][0] = locvars->ANALOGIN_04_00;
        ANALOGIN[4][1] = locvars->ANALOGIN_04_01;

        // Scheda 6 (Ethercat 1022: dispositivi gruppo FRL in IOlink)
        DIGITALIN[5][0]  = locvars->DIGITALIN_05_00;
        DIGITALIN[5][1]  = locvars->DIGITALIN_05_01;
        DIGITALIN[5][2]  = locvars->DIGITALIN_05_02;
        DIGITALIN[5][3]  = locvars->DIGITALIN_05_03;
        DIGITALIN[5][4]  = locvars->DIGITALIN_05_04;
        DIGITALIN[5][5]  = locvars->DIGITALIN_05_05;
        DIGITALIN[5][6]  = locvars->DIGITALIN_05_06;
        DIGITALIN[5][7]  = locvars->DIGITALIN_05_07;
        DIGITALIN[5][8]  = locvars->DIGITALIN_05_08;
        DIGITALIN[5][9]  = locvars->DIGITALIN_05_09;
        DIGITALIN[5][10] = locvars->DIGITALIN_05_10;
        DIGITALIN[5][11] = locvars->DIGITALIN_05_11;

		highresClk = locvars->highresClk;
    } else {
        // Copia delle strutture da globali a locali 
        memcpy(locvars->AXCTRL, AXCTRL, sizeof(CNCPLC_AXIS_CTRL)*min(CONFCN.n_ax, ARRAY_SIZE(AXCTRL)));
        memcpy(&locvars->CNCCTRL, &CNCCTRL, sizeof(CNPLC_CNCCTRL));
        memcpy(&locvars->CNPLCHANDLE, &CNPLCHANDLE, sizeof(CNPLC_HANDLE));

		//ch1
		memcpy (locvars->AXCTRL_l_CH1, AXCTRL_CH1, sizeof(CNCPLC_AXIS_CTRL)* (min(CONFCN_CH1.n_ax, ARRAY_SIZE (AXCTRL))));
		memcpy (&locvars->CNCCTRL_l_CH1, &CNCCTRL_CH1, sizeof(CNPLC_CNCCTRL));
		memcpy (&locvars->CNPLCHANDLE_l_CH1, &CNPLCHANDLE_CH1, sizeof(CNPLC_HANDLE));

		////ch2
		memcpy (locvars->AXCTRL_l_CH2, AXCTRL_CH2, sizeof(CNCPLC_AXIS_CTRL)* (min(CONFCN_CH2.n_ax, ARRAY_SIZE (AXCTRL))));
		memcpy (&locvars->CNCCTRL_l_CH2, &CNCCTRL_CH2, sizeof(CNPLC_CNCCTRL));
		memcpy (&locvars->CNPLCHANDLE_l_CH2, &CNPLCHANDLE_CH2, sizeof(CNPLC_HANDLE));


        // Scheda 1
        //locvars->DIGITALIN_00_00 = DIGITALIN[0][0];
        //locvars->DIGITALIN_00_01 = DIGITALIN[0][1];
        //locvars->DIGITALIN_00_02 = DIGITALIN[0][2];
        //locvars->DIGITALIN_00_03 = DIGITALIN[0][3];
        //locvars->DIGITALIN_00_04 = DIGITALIN[0][4];
        //locvars->DIGITALIN_00_05 = DIGITALIN[0][5];
        //locvars->DIGITALIN_00_06 = DIGITALIN[0][6];
        //locvars->DIGITALIN_00_07 = DIGITALIN[0][7];
        //locvars->DIGITALIN_00_08 = DIGITALIN[0][8];
        //locvars->DIGITALIN_00_09 = DIGITALIN[0][9];
        //locvars->DIGITALIN_00_10 = DIGITALIN[0][10];
        //locvars->DIGITALIN_00_11 = DIGITALIN[0][11];
        //locvars->DIGITALIN_00_12 = DIGITALIN[0][12];
        //locvars->DIGITALIN_00_13 = DIGITALIN[0][13];
        //locvars->DIGITALIN_00_14 = DIGITALIN[0][14];
        //locvars->DIGITALIN_00_15 = DIGITALIN[0][15];
        //locvars->DIGITALIN_00_16 = DIGITALIN[0][16];
        //locvars->DIGITALIN_00_17 = DIGITALIN[0][17];
        locvars->DIGITALOUT_00_00 = DIGITALOUT[0][0];
        locvars->DIGITALOUT_00_01 = DIGITALOUT[0][1];
        locvars->DIGITALOUT_00_02 = DIGITALOUT[0][2];
        locvars->DIGITALOUT_00_03 = DIGITALOUT[0][3];
        locvars->DIGITALOUT_00_04 = DIGITALOUT[0][4];
        locvars->DIGITALOUT_00_05 = DIGITALOUT[0][5];
        locvars->DIGITALOUT_00_06 = DIGITALOUT[0][6];
        locvars->DIGITALOUT_00_07 = DIGITALOUT[0][7];
        locvars->DIGITALOUT_00_08 = DIGITALOUT[0][8];
        locvars->DIGITALOUT_00_09 = DIGITALOUT[0][9];
        locvars->DIGITALOUT_00_10 = DIGITALOUT[0][10];
        locvars->DIGITALOUT_00_11 = DIGITALOUT[0][11];
        locvars->DIGITALOUT_00_12 = DIGITALOUT[0][12];
        locvars->DIGITALOUT_00_13 = DIGITALOUT[0][13];
        locvars->DIGITALOUT_00_14 = DIGITALOUT[0][14];
        locvars->DIGITALOUT_00_15 = DIGITALOUT[0][15];
        locvars->DIGITALOUT_00_16 = DIGITALOUT[0][16];
        locvars->DIGITALOUT_00_17 = DIGITALOUT[0][17];
        //locvars->ANALOGIN_00_00 = ANALOGIN[0][0];
        //locvars->ANALOGIN_00_01 = ANALOGIN[0][1];
        //locvars->ANALOGIN_00_02 = ANALOGIN[0][2];
        //locvars->ANALOGIN_00_03 = ANALOGIN[0][3];
        //locvars->ANALOGIN_00_04 = ANALOGIN[0][4];
        //locvars->ANALOGIN_00_05 = ANALOGIN[0][5];
        //locvars->ANALOGIN_00_06 = ANALOGIN[0][6];
        //locvars->ANALOGIN_00_07 = ANALOGIN[0][7];
        //locvars->ANALOGIN_00_08 = ANALOGIN[0][8];
        //locvars->ANALOGIN_00_09 = ANALOGIN[0][9];
        //locvars->ANALOGIN_00_10 = ANALOGIN[0][10];
		//locvars->ANALOGIN_00_11 = ANALOGIN[0][11];
        locvars->ANALOGOUT_00_00 = ANALOGOUT[0][0];
		locvars->ANALOGOUT_00_01 = ANALOGOUT[0][1];
        locvars->ANALOGOUT_00_02 = ANALOGOUT[0][2];
		locvars->ANALOGOUT_00_03 = ANALOGOUT[0][3];
        locvars->ANALOGOUT_00_04 = ANALOGOUT[0][4];
		locvars->ANALOGOUT_00_05 = ANALOGOUT[0][5];
        //locvars->ENCODERIN_00_00 = ENCODERIN[0][0];

        // Scheda 2
        //locvars->DIGITALIN_01_00 = DIGITALIN[1][0];
        //locvars->DIGITALIN_01_01 = DIGITALIN[1][1];
        //locvars->DIGITALIN_01_02 = DIGITALIN[1][2];
        //locvars->DIGITALOUT_01_00 = DIGITALOUT[1][0];
        //locvars->DIGITALOUT_01_01 = DIGITALOUT[1][1];
        //locvars->DIGITALOUT_01_02 = DIGITALOUT[1][2];
        //locvars->ANALOGIN_01_00 = ANALOGIN[1][0];
        //locvars->ANALOGIN_01_01 = ANALOGIN[1][1];
        //locvars->ANALOGOUT_01_00 = ANALOGOUT[1][0];

        // Scheda 3
        //locvars->DIGITALIN_02_00 = DIGITALIN[2][0];
        //locvars->DIGITALIN_02_01 = DIGITALIN[2][1];
        //locvars->DIGITALIN_02_02 = DIGITALIN[2][2];
        //locvars->DIGITALOUT_02_00 = DIGITALOUT[2][0];
        //locvars->DIGITALOUT_02_01 = DIGITALOUT[2][1];
        //locvars->DIGITALOUT_02_02 = DIGITALOUT[2][2];
        //locvars->ANALOGIN_02_00 = ANALOGIN[2][0];
        //locvars->ANALOGIN_02_01 = ANALOGIN[2][1];
        //locvars->ANALOGOUT_02_00 = ANALOGOUT[2][0];

        // Scheda 4
        //locvars->DIGITALIN_03_00 = DIGITALIN[3][0];
        //locvars->DIGITALIN_03_01 = DIGITALIN[3][1];
        //locvars->DIGITALIN_03_02 = DIGITALIN[3][2];
		//locvars->DIGITALOUT_03_00 = DIGITALOUT[3][0];
		//locvars->DIGITALOUT_03_01 = DIGITALOUT[3][1];
		//locvars->DIGITALOUT_03_02 = DIGITALOUT[3][2];
        //locvars->ANALOGIN_03_00 = ANALOGIN[3][0];
        //locvars->ANALOGIN_03_01 = ANALOGIN[3][1];
		//locvars->ANALOGOUT_03_00 = ANALOGOUT[3][0];

        // Scheda 5 (MGPILOT)
        //locvars->DIGITALIN_04_00 = DIGITALIN[4][0];
        //locvars->DIGITALIN_04_01 = DIGITALIN[4][1];
        //locvars->DIGITALIN_04_02 = DIGITALIN[4][2];
        locvars->DIGITALOUT_04_00 = DIGITALOUT[4][0];
        locvars->DIGITALOUT_04_01 = DIGITALOUT[4][1];
        //locvars->ANALOGIN_04_00 = ANALOGIN[4][0];
        //locvars->ANALOGIN_04_01 = ANALOGIN[4][1];

        // Scheda 6 (Ethercat 1022: dispositivi gruppo FRL in IOlink)
        //locvars->DIGITALIN_05_00 = DIGITALIN[5][0]; 
        //locvars->DIGITALIN_05_01 = DIGITALIN[5][1]; 
        //locvars->DIGITALIN_05_02 = DIGITALIN[5][2]; 
        //locvars->DIGITALIN_05_03 = DIGITALIN[5][3]; 
        //locvars->DIGITALIN_05_04 = DIGITALIN[5][4]; 
        //locvars->DIGITALIN_05_05 = DIGITALIN[5][5]; 
        //locvars->DIGITALIN_05_06 = DIGITALIN[5][6]; 
        //locvars->DIGITALIN_05_07 = DIGITALIN[5][7]; 
        //locvars->DIGITALIN_05_08 = DIGITALIN[5][8]; 
        //locvars->DIGITALIN_05_09 = DIGITALIN[5][9]; 
        //locvars->DIGITALIN_05_10 = DIGITALIN[5][10];
        //locvars->DIGITALIN_05_11 = DIGITALIN[5][11];

		// Scheda 7 (BRIDGE CON CONTAORE SOFTWARE)
		locvars->DIGITALOUT_05_00 = DIGITALOUT[5][0];
    }
}
