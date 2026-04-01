//----------------------------------------------------------------------------
// TITOLO      : plc.c
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Routine principale gestione macchina
//----------------------------------------------------------------------------

#include "all.inc"

//-- Programma macchina ------------------------------------------------------
//----------------------------------------------------------------------------


void plc(PPLCMAIN_LOCVARS locvars)
{
// goto salta_plc;	//@


// **************************************************************************************************************************
// *************** GESTIONE UPS: in caso di assenza alimentazione , comandiamo lo shutdown dopo un certo tempo **************
// **************************************************************************************************************************
//////tS(TS_RIT_INPUT_UPS, (unsigned char) UPS_ALIM_MACCH_I);     // UPS_ALIM_MACCH_I = contatto che chiude l'UPS quando interviene 
//////
//////if(RP_TSuppl[TS_RIT_INPUT_UPS] && !SHUTDOWN_WIN_ESEG)       // Il comando di shutdown deve essere dato una sola volta
//////{
//////
//////	RTPLC_VARIANT StringCommand;
//////	CHAR stringa[] = "shutdown -s -t 10 -c \"Save your job, machine being shut down\"";  // -t 10 indica che tra 10 secondi sarà eseguito lo shutdown
//////	StringCommand.vt = RTPLC_FORMAT_STRING;
//////	StringCommand.value.string.size = _strlen(stringa);
//////	StringCommand.value.string.sz = stringa;
//////	SendExternString(12345, &StringCommand );
//////
//////	SHUTDOWN_WIN_ESEG = 1;
//////}
// **************************************************************************************************************************
// *************** FINE GESTIONE UPS: in caso di assenza alimentazione , comandiamo lo shutdown dopo un certo tempo *********
// **************************************************************************************************************************


/**** DEFINIZIONE VERSIONE PLC ****/
Aris[R_VERSIONE_PLC] = (float)150.800;

/**** Tutti i CNC CT4 e CT6 sono di tipo M ****/

BITON	= 1;
BITOFF	= 0;


if (PON)
	{
	timersSuppl_pon	();
	timersSimu_pon	();
	//timersCrono_pon();
	lotime (T_MEM_INVERTER_KO, 300.0f);  // ritardo apertura ripari dopo anomalia inverter (300 sec)

	#ifdef ETTORE_RELEASE
		{
			Aris[R_TIPO_CN] = 1;
		}
	#endif	
	}


//****** GESTIONE CAMBIO PARAMETRI: solo per il sistema costantino ******************
#if defined(ETTORE_RELEASE)
if (!RESET_MC) {
    UPDATEPARAM_ENUM sts;
    sts = UpdateParamGetStatus ();    // chiedo se c’e’ un cambio di tarature al volo
    if (sts == upRequest) {
        sts = UpdateParamAck (RTPLC_TRUE);    // do sempre l'ACK TRUE al cambio dei parametri , e quindi il cambio delle tarature viene fatto
    }
}
#endif
//*********************FINE GESTIONE CAMBIO PARAMETRI ******************


/*----------- Ragiono in logica positiva sui ripari --------------*/
//***** Appoggio ripari chiusi per modulo di sicurezza PILZ ******
APPO_RIPARO_CH_PILZ	= (RIP_ANT_CH_SICUR_I || !CONF_VIS_ALTA) && (APPO_RIPARO_CH_INP || !CONF_RIPARO_ANT);

APPO_RIPARO_CH	= (VISIERA_IND_I || !CONF_VIS_BASSA) && (RIP_ANT_CH_SICUR_I || !CONF_VIS_ALTA) && (APPO_RIPARO_CH_INP || !CONF_RIPARO_ANT);

Aris_CH1[R_APP_RIP_CHIUSO] = Aris_CH2[R_APP_RIP_CHIUSO] = R[R_APP_RIP_CHIUSO] = (float) APPO_RIPARO_CH;  //appoggio su area R per utilizzo lato CN

APPO_TUN_RIP_LAT_SX_CH = (!SPORT_LAT_SX_AP_I || !CONF_RIP_LAT_SX);  // se riparo chiuso: micro non premuto, ingresso_plc=0 (contatto N.O.)
APPO_TUN_RIP_LAT_DX_CH = (!SPORT_LAT_DX_AP_I || !CONF_RIP_LAT_DX);  // se riparo chiuso: micro non premuto, ingresso_plc=0 (contatto N.O.)

timersSuppl	();
timersSimu	();

// Debug segnali PC ************************************************

if (TEST_015 > 30000)		TEST_015 = 0;
if (TEST_016 > 30000)		TEST_016 = 0;
if (TEST_017 > 30000)		TEST_017 = 0;
if (TEST_018 > 30000)		TEST_018 = 0;
if (TEST_019 > 30000)		TEST_019 = 0;
if (TEST_020 > 30000)		TEST_020 = 0;
if (TEST_021 > 30000)		TEST_021 = 0;
if (TEST_022 > 30000)		TEST_022 = 0;
if (TEST_023 > 30000)		TEST_023 = 0;
if (TEST_024 > 30000)		TEST_024 = 0;
if (TEST_025 > 30000)		TEST_025 = 0;
if (TEST_026 > 30000)		TEST_026 = 0;

if (R[R_SEND_START])		TEST_015++;	// (1715)
if (R[R_SEND_RESET])		TEST_016++;	// (1716)
if (R[R_ATTESA_CONFERMA])	TEST_017++;	// (1717)

if (R[R_CLOSE_CYCLE])		TEST_024++;	// (1724)
if (R[R_RESET_ALL])			TEST_025++;	// (1725)
if (R[R_ERGO_SEND_START])	TEST_026++;	// (1726)


// *****************************************************************

modulo_sicurezza();

shared_Mem_MC();

res_mes();

readconf();

allarmi_ethercat_assi();

funz_m();

funz_m_CH1();

funz_m_CH2();

Syn_0_MC();

Syn_1_MC();

// Lasciare la chiamata a Gruppo_FRL_connect prima di central per corretta sincronizzazione con l'allarme di pressione aria insufficiente
Gruppo_FRL_connect();

central();

check_battute();

axparams();

code_all();

funzman	();

aspiratori();

attivita_periodiche();

assi();

battuta_precisione();

cambut();

check_morse_aut();

check_morse_trasc_x();

check_posiz_morse();

cktool();

com_OPCUA_con_laser();

testhlock();

// dati_utensile();          // dati_utensile(): commentato perché gestisce i parametri utensili in ISO usando TTReader_1.exe  (NON PIU' USATO)

enable_disable_filtri();

eventi_industria_4_0();

debug();

gest_ava_utensili();

gestione_morse();

led_ripari();

lubrica();

marposs(locvars);

mandrino();

mgpilot();

movpiece(locvars);

time_cal();  //non spostare: anticipato rispetto a multipezzo() per problema calcolo tempo ciclo in simulato

multipezzo();

read_SDO_minimotor();

OPCUA_dati();
Oil_level();    // livellostato iolink nel serbatoio

riparo();

riposmor();

ricerca_morse_aut();

ricerca_morse_trasc_x();

uscite();

street_m();

time_out();
	
utensili();

volantino();

com_cnc();

contatori_bridge();


//@@	if(R[R_TEST3926] > 0.5)
//@	{
//@		rtplctrace(1,_T("g_Handle[0] = %d"), g_Handle[0]);
//@		rtplctrace(1,_T("g_Handle[1] = %d"), g_Handle[1]);
//@		R[R_TEST3926] = 0;
//@	}


/************************* MICRO VELOCI ************************/

//Micro veloce X per riferimento asse o ricerca morse 
if ((Mg_MC(110) || Mg_MC(152) || Mg_MC(245)) && CONF_RIC_MORSE)
{
	/* Ricerca morse attiva : il micro di presenza morse è quello veloce reindirizzato */
	if (CONF_ASSE_X) SetMiVel(AX_X_CH0,1,35);		// PRESENZA_MORSA_AX_X_I
}
else
{
}

//Micro veloce Y per rilievo lunghezza utensile.		Ingresso:  PRESETTER_UT_I          MI_1_69  /*MI_2_69 Presetter, Verifica integrita utensili */
if ( (R[R_CKTOOL_PRES]>1.5) && (Mg_MC(21)) )
{
	if (CONF_ASSE_Y) SetMiVel(AX_Y_CH0,1,69);		// 
	if (CONF_ASSE_W) SetMiVel_MC(&CNCSTATUS_CH1,AXCTRL_CH1,AX_W_CH1,1,69);	
}


// Eventuale futuro Riferimento assi Slave
// PLC_ETHERNET_MICRO_HOME_SIGNAL(PLC_ETHERNET_O_ID_SLAVE1, WORD_FC0_ASSI_SLAVE);


/**** PARTE COMUNE ****/
if (!CICLO_ON)
	M02 = 0;    /*Reset di M02 che deve avvenire a fine loop*/

if (!CICLO_ON_CH1)
	M_CH1_02 = 0;    /*Reset di M02 che deve avvenire a fine loop*/

if (!CICLO_ON_CH2)
	M_CH2_02 = 0;    /*Reset di M02 che deve avvenire a fine loop*/

crea_report();  //creazione file di report
conftime();     //scrittura del file CONFTIME.CS4 (lasciare come ultima chiamata)


// salta_plc:;		// @

	//-- Reset Pulsante di start da Drill ----	
	R[R_DRILL_START] = 0.0;

	R[R_SIMON_START] = (float) 0.0;

	if(SIMULATORE_SU_PC)
		R[R_DRILL_HOLD] = 0.0;

// abil_Isac_CH2_AX_P_0_02 = (unsigned short)(AXCTRL_CH2[1].ctrlFlags.SERVON);	// visualizzazione variabile CNC di abilitazione asse 

appoggio_out ();

} // fine plc



//-- Temporizzatori ----------------------------------------------------------
//----------------------------------------------------------------------------
void templc()
{ 

appoggio_in ();


// Nuova versione Reduction Cost: Appoggio di eventuali ingressi inesistenti o di nuovi dispositivi opzionali


// Vibrazioni e temperatura OK nel mandrino (OPT) (1: ok) (0: deve interrompere start inverter)
MANDRINO_VIBR_TEMP_OK = (MANDRINO_VIBR_TEMP_OK_I) || (!MANDRINO_VIBR_TEMP_PRES);	


		///**************************************************************
        ///*************** ESECUZIONE PROGRAMMA SIMULATO ****************
        ///**************************************************************


 		if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
		{
			SIMULATORE_ON = 1;
			R[R_SIMU]     = 1;
			NO_EXIT_SIMU  = 0;
			simulazione ();
		}

		if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
		{
			SIMULATORE_ON = 0;
			R[R_SIMU] = 0;
			NO_EXIT_SIMU = 1;                     /* Flag per uscita da WINDOWS in simulato */
			
			// Reset funzioni M relativi a cicli di posizionamento morse con X che sono usate solo in simulazione per il software SIMON
			Mr_MC(364);
			Mr_MC(365);
		}


// Appoggio ingresso presetter e sua simulazione
if (R[R_CKTOOL_PRES] > 0.5)
{

	if (SIMULATORE_SU_CN || SIMULATORE_SU_PC || (R[R_COLLAUDO_04]==1010) )
	{
		if( R[R_CKTOOL_ABIL]>0.5      && (Mg_MC(10)) )  { PRESETTER_UT_I = PRESETTER_UT_INGR = ( (R[R_QUOTA_Y]) > ( R[R_CKT_QUOTA_VER_UT_Y] - R[R_OFFSET_Z_MAND] - R[R_LNG_TOOL] ) ) ; }
		if( R[R_CKT_RIL_DIM_TOOL]>0.5 && (Mg_MC(21)) )  { PRESETTER_UT_I = PRESETTER_UT_INGR = ( (R[R_QUOTA_Y]) > ( R[R_CKT_QUOTA_VER_UT_Y] - R[R_OFFSET_Z_MAND] - 160           ) ) ; }
	}
	else
	{
		PRESETTER_UT_INGR = !(PRESETTER_UT_I);		// Ingresso N.C.
	}

	I_ANN_Y_DA_PRESETTER = PRESETTER_UT_INGR && ( (Mg_MC(10)) || (Mg_MC(21)) );

}
else
{
	I_ANN_Y_DA_PRESETTER = 0;
}

// Appoggi ingressi Uscite movimenti pericolosi abilitate:
APP_OUT_MAC_ABIL = OUT_MAC_ABIL_I;


P_AUXON = AUX_INSER_I || ((R[R_SIM_AUX] == 1) && SIMULATORE_ON);	/* Ritardo inserzione ausiliari */

P_PON = PON || P_PON;   						/* Ritardo PLC ON */
P_RIT_PON = RP_PON;								/* Derivata Ritardo PLC ON */

PON_dn = mem_PON && !PON;						/* Derivata negativa di PLC ON (attualmente serve per attivare pressurizzazione mandrino) */
mem_PON = PON;

												
P_PRES_ARIA = APP_INPUT_ARIA_PRES;             /* Ritardo presenza aria */
P_MANU = SEL_MANU_I;                           /* Macchina in manuale */
P_AUTO = (SEL_AUTO_I || SEL_SEMIAUTO_I);       /* Macchina in automatico */

P_COMANDO_A = COMANDO_A;                       /* Ritardo comando indietro */
P_COMANDO_B = COMANDO_B;                       /* Ritardo comando avanti */
P_NVM_CH0 = NVM_CH0;                                   /* Strobe nuova funzione M */

// Memorizzazione anomalia inverter, serve per inibire temporaneamente l'apertura ripari (pilotaggio timer analogo a DRIVEM_NOK_FAL)
COND_INVERTER_KO = !(INVERTER_0_INV_NOIN_BLOCCO) && (RP_AUXON) && (ALIM_PRES_I) && CONF_MANDRINO;
P_MEM_INVERTER_KO = COND_INVERTER_KO;
MEM_INVERTER_KO = (P_MEM_INVERTER_KO) || (RN_MEM_INVERTER_KO);

P_START_CYCLE = ( (R[R_DRILL_START]>0.5) || MGPILOT_START || (AUTO && REQ_CICLO_ON) );    // Pilotaggio start ciclo in singolo/multipezzo


P_AUX_OSCILL = !RP_OSCILLATORE;                /* Aux oscillatore 1 Hz */
P_OSCILLATORE = RP_AUX_OSCILL;                 /* Oscilatore 1 HZ */

P_IMPRST_INV = INVERTER_0_RESET_INVERTER;      /* Impulso reset allarmi inverter */

P_LUBRICA_ON = AUX1_LUBRICA_ON && !RP_LUBRICA_OFF; /* Tempo impulso di lubrificazione lubrica */
P_LUBRICA_OFF = RP_LUBRICA_ON;                     /* Aux tempo impulso lubrificazione lubrica */

P_UT_AGGAN = UT_AGGAN_I;					   /* Ritardo utensile agganciato */
P_UT_SGANC = UT_SGANC_I;                       /* Ritardo utensile sganciato */
P_AUXPREA = INVERTER_0_INV_NO_OVERLOAD;        /* Ritardo mandrino in sovraccarico */

P_OUTMAC_ABIL = OUT_MAC_ABIL_I;                /* Ritardo uscite pericolose abilitate (ritardate) */

P_VEL_0 = MEM_VEL0;                            /* Ritardo velocita' mandrino a 0 */

P_STOP_INV = !INVERTER_0_START_INV_FW;         /* Ritardo caduta start inverter */

P_START_INV = INVERTER_0_START_INV_FW && !INVERS_ROT_MAND;  /* Ritardo start inverter */

P_START2_INV = INVERTER_0_START_INV_FW;        /* Ritardo che mantiene attivo il Teleruttore dello Scambiatore di calore mandrino (frigo) per 2 minuti dopo fine start inverter */

P_SCAMB_CAL_MANDR = SCAMB_CAL_MANDR_O;         // Ritardo dopo l'attivazione dello Scambiatore di calore mandrino (frigo) che abilita allarme flussostato

P_MANDR_DISALIM = (!ALIM_MANDR_O && MANDRINO_FERMO); // Caduta alimentazione mandrino e mandrino fermo

P_IMP_SBL_RITENUTA = DP_RIT_STOP_INV ||        /* Impulso sblocco ritenuta teleruttore elettromandrino */
               DP_MANU || DP_AUTO || 
			   DP_RIT_PON || DP_AUXON || 
			   DP_MANDRINO_FERMO || DP_OUTMAC_ABIL || DP_MANDR_DISALIM;


P_CONDIZ_AX_OK = ALIM_PRES_I && AUX_INSER_I && RP_OUTMAC_ABIL && CENTRALINA_OK_I && TERM_GEN_I;

P_ALIM_PRES = ALIM_PRES_I;                     /* Ritardo alimentazioni presenti */

				
P_RIP_CH = CENTRALINA_OK_I && (APPO_RIPARO_CH || UOMO_MORTO_I || !CONF_RIPARO_ANT);	// Ripari chiusi e abilitati

P_START_STRINGA	= MANO && ( (R[R_DRILL_START]>0.5) || MGPILOT_START) && COLLAUDO_ON;	/* Start stringa in manuale per collaudo */
P_FRONTE_STRINGA = RP_START_STRINGA;					/* Fronte per comando stringa dopo temporizzazione */

P_LIV_LUB_NOT_BASSO = !LIV_LUB_NO_BASSO_I;     /* Temporizzo Livello Lubrica Normale basso */
P_LIV_LUB_NOT_ALTO = !LIV_LUB_NO_ALTO_I;       /* Temporizzo Livello Lubrica Normale alto */

P_BORDO_SENSIB_OK = BORDO_SENSIB_OK_I;         /* filtro sul segnale impulsivo */

P_START_MARPOSS = START_MARPOSS;               /* Ritardo start Marposs */

P_POT_ZERO = (POTENZIOMETRO < 3);			/* Ritardo prima di considerare il potenziometro a Zero */

P_STARTASP = CICLO_ON && (APPO_RIPARO_CH || (R[R_GEST_SPEGN_ASPIR]<0.5));	/* Partenza Aspiratore SX e DX */

P_CKTOOL = (Mg_MC(12) || Mg_MC(13));  /* Ritardo verifica integrità utensili */

//Micro Morse Asse X
P_RIL_MORSE_X = (Mg_MC(110) || Mg_MC(152) || Mg_MC(245)) && PRESENZA_MORSA_AX_X_I;	/* Derivata di salita micro rilevamento morse */

// Presetter utensili
P_PRESETTER = I_ANN_Y_DA_PRESETTER;

P_MICRO_MORSA_ASSENTE_X = !PRESENZA_MORSA_AX_X_I;	/* Ritardo per controllo allarme assenza micro */

P_NVT_CH0 = NVT_CH0;                                /* Strobe nuova funzione T */

P_VOL_ON = (MANO && FUNZ_MAN_VOL && OUT_MAC_ABIL_I && UOMO_MORTO_I && !STROBE_SEL_ASSE_VOL);  /* Volantini attivi solo dopo un pò che le condizioni sono presenti */

P_FRONTE_ALLARMI = ALLARMI_PRES;			/* Fronte sugli allarmi presenti */


P_START_SX = PLS_CONFERMA_ZONASX_I;         /* Impulso zona SX pronta */
P_START_DX = PLS_CONFERMA_ZONADX_I;         /* Impulso zona DX pronta */


P_AUX_OSCFAST = !RP_OSCFAST;                   /* Aux oscillatore 0.5 Hz per Lampeggio Veloce */
P_OSCFAST = RP_AUX_OSCFAST;                    /* Oscilatore 0.5 HZ per Lampeggio Veloce  */

P_TRASC_INSERITO_X = TRASC_MORSE_AX_X_INS_I;	/* Trascinatore inserito per allarmi sul micro */

P_PRESSIONE_PLS_START_CYCLE = ( (R[R_DRILL_START]>0.5) || MGPILOT_START); /* Pressione SOLO del PLS Start Ciclo */

P_LAMP_PER_MESS = LAMP_PER_MESS;			// Temporizzo la durata del breve lampeggio per i messaggi (vedo solo il blink)

P_MEM_MASCRIG = MEM_MASCRIG;					// Ritardo su memoria maschiatura rigida

P_I_BLC_CH0 = I_BLC_CH0;                                /* I_BLC */
P_I_BLC_CH1 = I_BLC_CH1;                                /* I_BLC */
P_I_BLC_CH2 = I_BLC_CH2;                                /* I_BLC */
	
P_LIVGRASS_NOK = !INGRASS_LIV_OK_I && !RESET_ALL
                 && !RESET_MC;                    /* Ritardo livello grasso basso */
P_INGRASS_OFF = START_INGRASS && !RP_INGRASS_ON; /* Aux tempo impulso lubrificazione INGRASSAGGIO AUTOMATICO */
P_INGRASS_ON =  START_INGRASS && RP_INGRASS_OFF; /* Tempo impulso di lubrificazione  INGRASSAGGIO AUTOMATICO */

// Temporizzazione impulso di reset per i dispositivi (assi ed inverter)
P_IMP_RESET = (RESET_MC || RESET_ALL) || (P_IMP_RESET && !RP_IMP_RESET);


/********** Inserisci le condizioni di TEMPORIZZAZIONE dei TIMER SUPPLEMENTARI ************/
// Sono per il controllo degli allarmi

	tS(TS_ALL_RIPARO_AP				, (unsigned char)(AP_RIP_ANT_O));
	tS(TS_ALL_RIPARO_CH				, (unsigned char)(CH_RIP_ANT_O));
	
	tS(TS_TAVOLA_AVA				, (unsigned char)(TAVOLA_AVA_O));
	tS(TS_TAVOLA_IND				, (unsigned char)(TAVOLA_IND_O));

	tS(TS_CENTRALINA_OK				, (unsigned char)(CENTRALINA_OK_I));
	
	tS(TS_TIMEOUT_BATTUTA_SX1_ALT			, (unsigned char)(BATTUTA_SX_ALT_O));
	tS(TS_TIMEOUT_BATTUTA_SX1_BAS			, (unsigned char)(!BATTUTA_SX_ALT_O));
	tS(TS_TIMEOUT_BATTUTA_DX4_ALT			, (unsigned char)(BATTUTA_DX_ALT_O));
	tS(TS_TIMEOUT_BATTUTA_DX4_BAS			, (unsigned char)(!BATTUTA_DX_ALT_O));
	
	tS(TS_TIMEOUT_SBLOC_UT					, (unsigned char)(SBLOC_UT_O));
	tS(TS_TIMEOUT_BLOCC_UT					, (unsigned char)(!SBLOC_UT_O));
	
	tS(TS_FORZA_ALTA_PRESS_MAN		, (unsigned char)((COLLAUDO_ON && FUNZ_MAN00 && COMANDO_B && (RICHIESTA_SEL_MORSE_SX_CH || RICHIESTA_SEL_MORSE_DX_CH) )));  // Ritardo per Forza l'alta pressione in manuale : DEBUG
	
	tS(TS_BAS_PRESSIONE_MORSE		, (unsigned char) ( (!CH_MORSA_10_HP_O || !CONF_MORSA_10) && 
								                        (!CH_MORSA_11_HP_O || !CONF_MORSA_11) && 
								                        (!CH_MORSA_12_HP_O || !CONF_MORSA_12) &&
														(!CH_MORSA_13_HP_O || !CONF_MORSA_13) && 
	                                                    (!CH_MORSA_14_HP_O || !CONF_MORSA_14) && 
								                        (!CH_MORSA_15_HP_O || !CONF_MORSA_15))  );

	tS(TS_PRESS_TAV_AVA			, (unsigned char)(TAVOLA_AVA_I));
	tS(TS_PRESS_TAV_IND			, (unsigned char)(TAVOLA_IND_I));

	
////old	tS(TS_MAN_FERMO					, (unsigned char)((MEM_INPUT_MAND_FERMO || !OUT_MAC_ABIL_I || RP_STOP_INV)));	// Ritardo Mandrino Fermo
	tS(TS_MAN_FERMO					, (unsigned char)((MEM_INPUT_MAND_FERMO || SET_MAN_FERMO && !INVERTER_0_START_INV_FW) /*|| !OUT_MAC_ABIL_I*/ || RP_STOP_INV) );	// Ritardo Mandrino Fermo

	tS(TS_RIT_MANDR_FERMO			, (unsigned char)(RIT_MANDR_FERMO));	// Ritardo Mandrino Fermo a basse velocita

	tS(TS_RIP_AUTO_NO_CH			, (unsigned char)((!AUTO_RIP_CH)));	// NON auto e ripari chiusi
		
	
	tS(TS_ALL_TAV_AVA			, (unsigned char)(!TAVOLA_AVA_I && APP_INPUT_ARIA_PRES));	// Condizione d'allarme temporizzata per tavola SX avanti
	tS(TS_ALL_TAV_IND			, (unsigned char)(!TAVOLA_IND_I && APP_INPUT_ARIA_PRES));	// Condizione d'allarme temporizzata per tavola SX indietro

	tS(TS_ALL_DISFC_TAV			, (unsigned char)(TAVOLA_AVA_I && TAVOLA_IND_I));	// Condizione d'allarme temporizzata per disfunzione Tavola SX


	tS(TS_DRIVE_X_IN_ALLARME, (unsigned char)(!DRIVE_X_OK));	// Drive Asse X in allarme 
	tS(TS_DRIVE_Y_IN_ALLARME, (unsigned char)(!DRIVE_Y_OK));	// Drive Asse Y in allarme 
	tS(TS_DRIVE_Z_IN_ALLARME, (unsigned char)(!DRIVE_Z_OK));	// Drive Asse Z in allarme 
	tS(TS_DRIVE_A_IN_ALLARME, (unsigned char)(!DRIVE_A_OK));	// Drive Asse A in allarme 
	tS(TS_DRIVE_C_IN_ALLARME, (unsigned char)(!DRIVE_C_OK));	// Drive Asse C in allarme 
	tS(TS_DRIVE_W_IN_ALLARME, (unsigned char)(!DRIVE_W_OK));	// Drive Asse W in allarme 


	tS(TS_ALL_CENTRALINA, (unsigned char)(!CENTRALINA_OK_I && APPO_RIPARO_CH_PILZ && APPO_TUN_RIP_LAT_SX_CH && APPO_TUN_RIP_LAT_DX_CH));	// Temporizzo Allarme Centralina non attiva con riparo chiuso SX

	tS(TS_ALIM_MM_NOT_OK, (unsigned char) (OUT_MAC_ABIL_I && !ALIM_MM_OK_I) );  // Temporizzo allarme alimentatore morse motorizzate non ok

	tS(TS_RIT_ALIM_MM_OK, (unsigned char) ALIM_MM_OK_I);  // Temporizza ritardo alimentatori morse OK

	tS(TS_PRESS_MORSE_CH, (unsigned char) PRESS_MORSE_HP_I);	// Temporizzo segnale di alta pressione morse
	
	tS(TS_MANO,	(unsigned char)(MANO)); // Ritardo su macchina multicanale in manuale

	tS(TS_COND_ASINCRO_CNC_MAN,	(unsigned char)(COND_ASINCRO_CNC_MAN));	// Temporizza segnale di CNC in stati diversi da tutti in MAN
	tS(TS_COND_ASINCRO_CNC_AUT,	(unsigned char)(COND_ASINCRO_CNC_AUT));	// Temporizza segnale di CNC in stati diversi da tutti in AUT
	

	// Appoggio per chiarezza le condizioni possibili di controllo per il corto sul cavo 
	CONDIZIONI_CORTO =	PLS_CONFERMA_ZONASX_I	||
						PLS_CONFERMA_ZONADX_I	||
						SEL_SBLOC_MORSE_SX_I	||
						SEL_BLOCC_MORSE_SX_I	||
						SEL_SBLOC_MORSE_DX_I	||
						SEL_BLOCC_MORSE_DX_I;

	// Sono segnali su un selettore instabile a ritorno 0 :  non possono mai essere insieme
	CORTO_DIRETTO = SEL_SBLOC_MORSE_SX_I && SEL_BLOCC_MORSE_SX_I || 
					SEL_SBLOC_MORSE_DX_I && SEL_BLOCC_MORSE_DX_I;


	tS(TS_COND_POSSIBILE_CORTO, (unsigned char)(CONDIZIONI_CORTO));	// Condizioni possibili per il corto dei cavi

	tS(TS_RILMOR_AX_X_INS,(unsigned char)(INS_RILMOR_AX_X_O));   // Temporizzo EV per condizione d'allarme micro morse asse X non inserito
	tS(TS_RILMOR_AX_X_DIS,(unsigned char)(!INS_RILMOR_AX_X_O));  // Temporizzo EV per condizione d'allarme micro morse asse X non disinserito

	tS(TS_FATM_CH0,			(unsigned char)(AUTO && CICLO_ON && !FATM_CH0 && !I_FHOLD_CH0 && !Mg_MC(157) && !Mg_MC(162) && !Mg_MC(163) && !Mg_MC(81)));
	
	tS(TS_TRASC_MORSE_AX_X_INS,	(unsigned char)(TRASC_MORSE_AX_X_INS_O));	// Temporizzo condizione d'allarme Trascinatore Morse Asse X non inserita 
	tS(TS_TRASC_MORSE_AX_X_DIS,	(unsigned char)(!TRASC_MORSE_AX_X_INS_O));	// Temporizzo condizione d'allarme Trascinatore Morse Asse X non disinserita 

	tS(TS_SBLOCCAGGIO_MORSA_10, (unsigned char)(SBLOC_MORSA_10_O));	    // Temporizzo Sbloccaggio morse : per non partire con la morsa mezza bloccata (non c'è l'input)
	tS(TS_SBLOCCAGGIO_MORSA_11, (unsigned char)(SBLOC_MORSA_11_O));
	tS(TS_SBLOCCAGGIO_MORSA_12, (unsigned char)(SBLOC_MORSA_12_O));					
	tS(TS_SBLOCCAGGIO_MORSA_13, (unsigned char)(SBLOC_MORSA_13_O));
	tS(TS_SBLOCCAGGIO_MORSA_14, (unsigned char)(SBLOC_MORSA_14_O));
	tS(TS_SBLOCCAGGIO_MORSA_15, (unsigned char)(SBLOC_MORSA_15_O));

	tS(TS_SOLO_MESS_PRESENTI, (unsigned char)(SOLO_MESS_PRESENTI && AUTO_CICLOMAN && CICLO_ON && !RP_LAMP_PER_MESS));	// Temporizzo dopo quanto inizio a segnalare i messaggi in auto 

	tS(TS_ALT_PRESS_MORSA10 , (unsigned char) (CH_MORSA_10_HP_O  && APP_OUT_MAC_ABIL) );
	tS(TS_ALT_PRESS_MORSA11 , (unsigned char) (CH_MORSA_11_HP_O  && APP_OUT_MAC_ABIL) );
	tS(TS_ALT_PRESS_MORSA12 , (unsigned char) (CH_MORSA_12_HP_O  && APP_OUT_MAC_ABIL) );
	tS(TS_ALT_PRESS_MORSA13 , (unsigned char) (CH_MORSA_13_HP_O  && APP_OUT_MAC_ABIL) );
	tS(TS_ALT_PRESS_MORSA14 , (unsigned char) (CH_MORSA_14_HP_O  && APP_OUT_MAC_ABIL) );
	tS(TS_ALT_PRESS_MORSA15 , (unsigned char) (CH_MORSA_15_HP_O  && APP_OUT_MAC_ABIL) );

	tS(TS_RIPARO_CH, (unsigned char) APPO_RIPARO_CH_INP);
	tS(TS_RIPARO_AP, (unsigned char) APPO_RIPARO_AP_INP);

	tS(TS_TIMEOUT_VIS_AVA, (unsigned char) !VISIERA_IND_O);
	tS(TS_TIMEOUT_VIS_IND, (unsigned char) VISIERA_IND_O);
	tS(TS_TIMEOUT_VIS_SAL, (unsigned char) (VIS_RIP_SAL_O && (APPO_RIPARO_CH_INP || !CONF_RIPARO_ANT) ) );
	tS(TS_TIMEOUT_VIS_DIS, (unsigned char) VIS_RIP_DIS_O);
	
	tS(TS_VIS_RIP_DIS, (unsigned char) VIS_RIP_DIS_O);


	tS(TS_RIT_VISIERA_IND, (unsigned char) VISIERA_IND_I);
	tS(TS_RIT_VISIERA_AVA, (unsigned char) VISIERA_AVA_I);
	

/************************** FINE ingressi dei TIMER SUPPLEMENTARI **************************/
	
/* Necessario per WINDOWS NT */
//@@	AggSePlc(act[0].dword, act[1].dword, act[2].dword);		ELIMINATO!!

}
