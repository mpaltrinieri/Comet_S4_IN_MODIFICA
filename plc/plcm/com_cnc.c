/*
        --------------------------------------------------------------
        TITOLO:         COM_CNC 
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione comunicazione PLC <--> CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    com_cnc(void)
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
        AUTORI:         Pecchi Andrea - Borsari G.
        --------------------------------------------------------------

*/

// ATTENZIONE: se si aggiungono comandi da inviare al CNC MASTER 
// occorre inserirli nella prima parte della Com_cnc relativa solo al MASTER
// e nella seconda parte relativa a MASTER+SLAVE


#include        "all.inc"

void com_cnc1(void);

short ESITO_TASTCNC_CH0 = 0;
short ESITO_TASTCNC_CH1 = 0;
short ESITO_TASTCNC_CH2 = 0;

BOOL AXESEL_MC (PCNPLC_CNCCTRL CncCtrl, UCHAR nAxe);

extern int COM_AVANTI	[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int COM_INDIETRO	[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ARR_AVANTI	[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ARR_INDIETRO	[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ASSE_NORIF	[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ASSE_CANOPEN	[MAX_NUM_CHANNEL][ASSE_NULLO];

void    com_cnc(void)
{
	//// Puntatori per la gestione standardizzata
	//short int *P_VEL_COL = 0;
	//short int *P_VEL_BAS = 0;
	//short int *P_VEL_NOR = 0;

	//// Valore intero area puntata
	//int AREA_COL = 0;
	//int AREA_BAS = 0;
	//int AREA_NOR = 0;

	//// Puntatori per ciclica ripetiva su SELJOG
	//UCHAR Ind = 0;

#ifdef _CWIN32
	short esito_CH0, esito_CH1, esito_CH2;
#endif 

	if (PON)
	{

		//Ch0
		JS_R_CH0 = 0;            // Scelte fisse per assi
		JS_L_CH0 = 0;
		JV_R_CH0 = 0;
		JV_L_CH0 = 1;

		//Risoluzione millesimale
		RS001_CH0 = 1;
		RS010_CH0 = 1;
		RS100_CH0 = 1;

		//Ch1
		JS_R_CH1 = 0;            // Scelte fisse per assi
		JS_L_CH1 = 0;
		JV_R_CH1 = 0;
		JV_L_CH1 = 1;

		//Risoluzione millesimale
		RS001_CH1 = 1;
		RS010_CH1 = 1;
		RS100_CH1 = 1;

		//Ch2
		JS_R_CH2 = 0;            // Scelte fisse per assi
		JS_L_CH2 = 0;
		JV_R_CH2 = 0;
		JV_L_CH2 = 1;

		//Risoluzione millesimale
		RS001_CH2 = 1;
		RS010_CH2 = 1;
		RS100_CH2 = 1;

		// Reset iniziale segnali comuni assi CH0
		I_BLCAX_CH0 = 0;
		I_BLC_CH0   = 0;
		I_FHOLD_CH0 = 0;

		// Reset iniziale segnali comuni assi CH1
		I_BLCAX_CH1 = 0;
		I_BLC_CH1   = 0;
		I_FHOLD_CH1 = 0;

		// Reset iniziale segnali comuni assi CH2
		I_BLCAX_CH2 = 0;
		I_BLC_CH2   = 0;
		I_FHOLD_CH2 = 0;


		R[R_ROTAZ_ON] = ROTAZ_ON;

		if(CONF_ASSE_M12)
			SELJOG = SelJog_MC(&CNCCTRL_CH2,&CNCSTATUS_CH2,&CNPLCHANDLE_CH2,AX_M12_CH2, 0, 1000);

		SELJOG = SelJog_MC(&CNCCTRL_CH1,&CNCSTATUS_CH1,&CNPLCHANDLE_CH1,AX_W_CH1, 0, 1000);

		SELJOG = SelJog(AX_X_CH0, 0, 4000);

		if (CONF_MGPILOT)
			overad3(MGPILOT_NODE_AI, 1, MAXOV_FE, 0, MININC, APPOVFED);  //necessario inizializzare overad3 al pon

	}
	

	// Tenere come visualizzazione
	APPOGGIO_PIOEXE=pio->exe;

	// Allarme comunicazione CanOpen
	if ((pio->exe != IO_EXE) && RP_PON)
		COMUNIC_CAN_FAL = 1;


	if(!SIMULATORE_SU_PC/* && !SIMULATORE_SU_CN*/)	
	{
		if (CONF_MGPILOT)
		{   
			APPOVFED = overad3(MGPILOT_NODE_AI, 1, MAXOV_FE, MINOV_FE, MININC, APPOVFED); 
		}
		else
		{	// Override assi da Drill
			APPOVFED = (unsigned char)(R[R_POTENZIOMETRO]);	  //Override assi da Drill
		}

		if(CONF_MGPILOT && CONF_MGPILOT2)
		{	// Override mandrino da potenziometro mandrino dell'MGPilot2 se presente
			APPOVSPE = overad3 (MGPILOT_NODE_AI, 2, MAXOV_SP, MINOV_SP, MININC, APPOVSPE);
		}
		else
		{	// Override mandrino fisso
			APPOVSPE = 100;
		}
	}
	else
	{
		APPOVFED = 120;
		APPOVSPE = 100;
	}

	// ****** ASSEGNAZIONE DEL CANALE ATTUALMENTE ASSOCIATO PER GLI ASSI CONDIVISI *******

	if		(O_LEASED_CH1(AX_W_CH1))	AX_W_CH_ON = CHANNEL_CH1;
	else if	(O_LEASED_CH0(AX_W_CH0))	AX_W_CH_ON = CHANNEL_CH0;
	else								AX_W_CH_ON = 999;

	R[R_CH_W_ON] = Aris_CH1[R_CH_W_ON] = Aris_CH2[R_CH_W_ON] = (double) AX_W_CH_ON;

	if      (O_LEASED_NOTUSED_CH1 (AX_W_CH1))	AX_W_CH_OFF = CHANNEL_CH1;
	else if (O_LEASED_NOTUSED_CH0 (AX_W_CH0))	AX_W_CH_OFF = CHANNEL_CH0;
	else										AX_W_CH_OFF = 999;

	R[R_CH_W_OFF] = Aris_CH1[R_CH_W_OFF] = Aris_CH2[R_CH_W_OFF] = (double) AX_W_CH_OFF;


	//Flag attivo se gli assi condivisi sono assegnati ai canali di default
	LEASED_DEFAULT = (AX_W_CH_ON == 0);

	//************************************************************************************

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<

	// ATTENZIONE AL NODO DELL'MGPILOT

	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<
	// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>><<<<<


	/* Scheduler comandi provenienti da tastiera PC */
	//Ch0
	schepro();

	//Ch1
	schepro_MC (&CNCSTATUS_CH1);

	//Ch2
	schepro_MC (&CNCSTATUS_CH2);

#ifdef _CWIN32

	//Ch0
	if (!SerPlanPlc (&esito_CH0))
	{
		gestjgo ();
		SerJogMP (-1);
	}

	//Ch1
	if (!SerPlanPlc_MC(&CNCCTRL_CH1,&CNCSTATUS_CH1,&CNPLCHANDLE_CH1,&esito_CH1))
	{
		gestjgo_MC (&CNCCTRL_CH1,&CNCSTATUS_CH1,&CNPLCHANDLE_CH1);
		SerJogMP_MC (-1,&CNCCTRL_CH1,&CNCSTATUS_CH1,&CNPLCHANDLE_CH1);
	}

	//Ch2
	if (!SerPlanPlc_MC(&CNCCTRL_CH2,&CNCSTATUS_CH2,&CNPLCHANDLE_CH2,&esito_CH2))
	{
		gestjgo_MC (&CNCCTRL_CH2,&CNCSTATUS_CH2,&CNPLCHANDLE_CH2);
		SerJogMP_MC (-1,&CNCCTRL_CH2,&CNCSTATUS_CH2,&CNPLCHANDLE_CH2);
	}

#endif

	// disabilitazione potenziometri
	if (DIS_POT) 
	{
		APPOVFED = 100;
		APPOVSPE = 100;
	}

	// Flag per limitazione OVRAP degli assi al 30% in semiautomatico e in manuale nei cicli manuali
	LIM_VEL_ASSI_1 = (SEL_SEMIAUTO_I) || (MANO && (CICLO_PRELUT || CICLO_DEPUT));

	// Limitazione OVRAP degli assi al 30% in Semiautomatico e nei cicli manuali di prelievo/deposito utensile
	if (LIM_VEL_ASSI_1 && (APPOVFED>(unsigned int)R[R_MAX_OVRAP_SEMIAUTO]) )
	{
		APPOVRAP = (unsigned int)R[R_MAX_OVRAP_SEMIAUTO];
	}
	else
	{
		APPOVRAP = APPOVFED;
	}

    //***** OVERRIDE RAPIDO E DI LAVORO PER SIMULAZIONE CON SIMON *****
	if(SIMULATORE_SU_PC && !RP_PON)
	{
		//Inizializzazione variabili del feed per SIMON
		R[R_SIMON_OVFEED] = (float) 120.0;
		R[R_SIMON_OVRAP] = (float) 120.0;
	}
	if(SIMULATORE_SU_PC)
	{
		APPOVFED = (unsigned char) R[R_SIMON_OVFEED];
		APPOVRAP = (unsigned char) R[R_SIMON_OVRAP];
	}
	// set override assi e mandrino
	OVFED_CH0 = OVFED_CH1 = OVFED_CH2 = APPOVFED;
	OVRAP_CH0 = OVRAP_CH1 = OVRAP_CH2 = APPOVRAP;
	OVSPE_CH0 = OVSPE_CH1 = OVSPE_CH2 = APPOVSPE;

	// visualizzazione override
	R[R_VIS_APPOVFED] = (float) APPOVFED;
	R[R_VIS_APPOVSPE] = (float) APPOVSPE;
	R[R_VIS_OVFED] = (float) OVFED_CH0;
	R[R_VIS_OVRAP] = (float) OVRAP_CH0;
	R[R_VIS_OVSPE] = (float) OVSPE_CH0;

	if(OVRAP_CH0 <= 100)   //gli override di tutti i canali sono uguali (OVRAP_CH0 invece di OVFED_CH0 per limitare in caso di semiautomatico)
	{
		OVFRE_CH0(AX_W_CH0) = OVRAP_CH0; //override asse indipendente (OVRAP_CH0 invece di OVFED_CH0 per limitare in caso di semiautomatico)
		OVFRE_CH1(AX_W_CH1) = OVRAP_CH0; //override asse indipendente
	}
	else
	{
		OVFRE_CH0(AX_W_CH0) = (double) 100.0; //override asse indipendente
		OVFRE_CH1(AX_W_CH1) = (double) 100.0; //override asse indipendente
	}


	if(MORSE_MOTORIZZATE)
	{
		if(OVRAP_CH0 <= 100)   //gli override di tutti i canali sono uguali
		{
			if(CONF_ASSE_M10) OVFRE_CH2(AX_M10_CH2) = OVRAP_CH0; /*override asse indipendente*/
			if(CONF_ASSE_M11) OVFRE_CH2(AX_M11_CH2) = OVRAP_CH0; /*override asse indipendente*/
			if(CONF_ASSE_M12) OVFRE_CH2(AX_M12_CH2) = OVRAP_CH0; /*override asse indipendente*/
			if(CONF_ASSE_M13) OVFRE_CH2(AX_M13_CH2) = OVRAP_CH0; /*override asse indipendente*/
			if(CONF_ASSE_M14) OVFRE_CH2(AX_M14_CH2) = OVRAP_CH0; /*override asse indipendente*/
			if(CONF_ASSE_M15) OVFRE_CH2(AX_M15_CH2) = OVRAP_CH0; /*override asse indipendente*/
		}
		else
		{
			if(CONF_ASSE_M10) OVFRE_CH2(AX_M10_CH2) = (double) 100.0; /*override asse indipendente*/
			if(CONF_ASSE_M11) OVFRE_CH2(AX_M11_CH2) = (double) 100.0; /*override asse indipendente*/
			if(CONF_ASSE_M12) OVFRE_CH2(AX_M12_CH2) = (double) 100.0; /*override asse indipendente*/
			if(CONF_ASSE_M13) OVFRE_CH2(AX_M13_CH2) = (double) 100.0; /*override asse indipendente*/
			if(CONF_ASSE_M14) OVFRE_CH2(AX_M14_CH2) = (double) 100.0; /*override asse indipendente*/
			if(CONF_ASSE_M15) OVFRE_CH2(AX_M15_CH2) = (double) 100.0; /*override asse indipendente*/
		}
	}


	//***************************************************************

	// Gestione FATGN
	FATGN_CH0 = 1;
	FATGN_CH1 = 1;
	FATGN_CH2 = 1;


	//Gestione FATS
	FATS_CH0 = 1;
	FATS_CH1 = 1;
	FATS_CH2 = 1;


	// Gestione FATM e FATT							
	FATM_CH0 = 
		!(
		PC_HOLD || ALLARMI_PRES || 

		M05 ||								// Mandrino fermo 

		M12 || M13 || M14 ||                // check tool

		M20 ||                              // Verifica mandrino fuori ingombro magazzino
		M24 || M25 || M26 || M27 ||         // Battuta di precisione

		M50 || M51 ||

		M54 ||								// attesa Scaricamento ut. dal mandrino (abilitaz. sblocco ut. con mgpilot)
		M55 ||								// attesa Caricamento  ut. sul mandrino (abilitaz. sblocco ut. con mgpilot)

		M56 || M57 ||						// Inserzione/disinserzione micro di ricerca morse
		M60 || M61 || M62 || M63 ||
		M81 ||
		M90 || M91 ||

		M76 || M77 || M78 || M79 ||
		M105 || M108 || M109 ||  //aggancio-sgancio morse in gantry
		M117 || M123 ||
		M154 || 

		M83  ||									// Copiata dal T5

		M100 ||				// Attesa movimento di ripristino Canopen

		M150 ||             // M di comunicazione con l'applicativo del laser

		M158 ||             // Controllo valori pos.morse da PC 
		M175 ||             // Attesa FATM in figura CAM_PROB.CNC

		M200 ||				// Controllo riposizionamento MORSE

		M201 || M202 ||  // Trasc.morse Asse X
		M209 ||          // carica tabella utensili in ISO

		M228 ||    // check congruità posizioni assi morse

		M249 || M250 || M251 || M252 ||
		M255 || M256 || //disattivazione / attivazione filtri su assi X,Y,Z per maschiatura rigida

		M260 || M261 || M262 || M263 || M268 || M269 ||  // Attivazione/Disattivazione correzioni assi
		M306 || M307 || M308 || M309 ||  // Attivazione/Disattivazione correzioni assi

		M274 || M275 || M276 || M277 || M278 || M279 ||  // Alta Pressione morse
	
		// M283 || // Libera servo indicizzato morse

		M294 || M295 || M296 || M297 || M298 || M299 ||  // Disattiva Alta Pressione morse

		M303 || //check posizione battute SX1 e DX4

		M310 || M311 || M312 || M313 ||

		// Bloccaggio/Sbloccaggio Morse
		M324 || M325 || M326 || M327 || M328 || M329 || 
		M337 || M338 || M339 || M340 || M341 || M342 ||
		M350 ||  //Richiesta sincronizzazione CNC livello 0
		M351 ||  //Richiesta sincronizzazione CNC livello 1
		M353 || M357  // CH0 : Disattivazione/Riattivazione Abilitazione assi
		);
					
	FATM_CH1 = 
		!(
		PC_HOLD || ALLARMI_PRES || 

		M_CH1_05 ||								// Mandrino fermo 

		M_CH1_12 || M_CH1_13 || M_CH1_14 ||                // check tool

		M_CH1_20 ||								// Verifica mandrino fuori ingombro magazzino
		M_CH1_24 || M_CH1_25 || M_CH1_26 || M_CH1_27 ||         // Battuta di precisione

		M_CH1_50 || M_CH1_51 ||
		M_CH1_56 || M_CH1_57 ||						// Inserzione/disinserzione micro di ricerca morse
		M_CH1_60 || M_CH1_61 || M_CH1_62 || M_CH1_63 ||
		M_CH1_81 || 	
		M_CH1_90 || M_CH1_91 ||

		M_CH1_76 || M_CH1_77 || M_CH1_78 || M_CH1_79 ||
		M_CH1_117 || M_CH1_123 ||
		M_CH1_154 || 

		M_CH1_83  ||									// Copiata dal T5

		M_CH1_100 ||				// Attesa movimento di ripristino Canopen

		M_CH1_158 ||            // Controllo valori pos.morse da PC 
		M_CH1_175 ||			// Attesa FATM in figura CAM_PROB.CNC

		M_CH1_200 ||			// Controllo riposizionamento MORSE

		M_CH1_201 || M_CH1_202 ||   // Trasc.morse Assi X 
		M_CH1_209 ||				// carica tabella utensili in ISO

		M_CH1_228 ||    // check congruità posizioni assi morse

		M_CH1_249 || M_CH1_250 || M_CH1_251 || M_CH1_252 ||

		M_CH1_274 || M_CH1_275 || M_CH1_276 || M_CH1_277 || M_CH1_278 || M_CH1_279 ||	// Alta Pressione morse

		M_CH1_294 || M_CH1_295 || M_CH1_296 || M_CH1_297 || M_CH1_298 || M_CH1_299 ||	// Disattiva Alta Pressione morse

		M_CH1_310 || M_CH1_311 || M_CH1_312 || M_CH1_313 ||

		// Bloccaggio/Sbloccaggio morse
		M_CH1_324 || M_CH1_325 || M_CH1_326 || M_CH1_327 || M_CH1_328 || M_CH1_329 || 
		M_CH1_337 || M_CH1_338 || M_CH1_339 || M_CH1_340 || M_CH1_341 || M_CH1_342 ||
		M_CH1_350 ||  //Richiesta sincronizzazione CNC livello 0
		M_CH1_351 ||  //Richiesta sincronizzazione CNC livello 1
		M_CH1_353 || M_CH1_357  // CH1 : Disattivazione/Riattivazione Abilitazione assi
		);

	FATM_CH2 = 
		!(
		PC_HOLD || ALLARMI_PRES || 

		M_CH2_05 ||								// Mandrino fermo 

		M_CH2_12 || M_CH2_13 || M_CH2_14 ||                // check tool
		
		M_CH2_20 ||								// Verifica mandrino fuori ingombro magazzino
		M_CH2_24 || M_CH2_25 || M_CH2_26 || M_CH2_27 ||         // Battuta di precisione

		M_CH2_50 || M_CH2_51 ||
		M_CH2_56 || M_CH2_57 ||						// Inserzione/disinserzione micro di ricerca morse
		M_CH2_60 || M_CH2_61 || M_CH2_62 || M_CH2_63 ||
		M_CH2_81 ||	
		M_CH2_90 || M_CH2_91 ||

		M_CH2_76 || M_CH2_77 || M_CH2_78 || M_CH2_79 ||
		M_CH2_105 || M_CH2_108 || M_CH2_109 ||  //aggancio-sgancio morse in gantry
		M_CH2_117 || M_CH2_123 ||
		M_CH2_154 || 

		M_CH2_83  ||									// Copiata dal T5

		M_CH2_100 ||				// Attesa movimento di ripristino Canopen

		M_CH2_158 ||            // Controllo valori pos.morse e pos.battute da PC 
		M_CH2_175 ||			// Attesa FATM in figura CAM_PROB.CNC

		M_CH2_200 ||			// Controllo riposizionamento MORSE

		M_CH2_201 || M_CH2_202 || 	// Trasc.morse Assi X
		M_CH2_209 ||				// carica tabella utensili in ISO

		M_CH2_210 ||				// Forza abilitazione assi morse

		M_CH2_228 ||    // check congruità posizioni assi morse

		M_CH2_274 || M_CH2_275 || M_CH2_276 || M_CH2_277 || M_CH2_278 || M_CH2_279 ||	// Alta Pressione morse

		// M_CH2_283 || // Libera servo indicizzato morse

		M_CH2_286  ||   //Macchina pronta al lavoro zona SX "Pend." (canale CH2)

		M_CH2_294 || M_CH2_295 || M_CH2_296 || M_CH2_297 || M_CH2_298 || M_CH2_299 ||	// Disattiva Alta Pressione morse
		
		M_CH2_310 || M_CH2_311 || M_CH2_312 || M_CH2_313 ||

		// Bloccaggio/Sbloccaggio morse
		M_CH2_324 || M_CH2_325 || M_CH2_326 || M_CH2_327 || M_CH2_328 || M_CH2_329 ||
		M_CH2_337 || M_CH2_338 || M_CH2_339 || M_CH2_340 || M_CH2_341 || M_CH2_342 ||
		M_CH2_350 ||  //Richiesta sincronizzazione CNC livello 0
		M_CH2_351 ||  //Richiesta sincronizzazione CNC livello 1
		M_CH2_353 || M_CH2_357  // CH2 : Disattivazione/Riattivazione Abilitazione assi
		);

	// Gestione FATT : nasce con la richiesta utensili solo in programmazione ISO
	FATT_CH0 = !(T01 || T02 || T03 || T04 || T05 || T06 || T07 || T08 || T09 || T10 || T11 || T12 );
	FATT_CH1 = 1;
	FATT_CH2 = 1;

	// Serve per poter toglier mandrino dal magazzino se si è interrotto movimento di cambio utensile 
	APP_I_FHOLD = (MAGUT_HOLD || ALLARMI_PRES || MANDR_COLL_MAG) && !GEST_OPERATORE_MAN;

	// Gestione FEED-HOLD assi
	I_FHOLD_CH0 = M_HOLD || FEEDHOLD_MAND || APP_I_FHOLD || Y_HOLD_DA_MAG_TOOL || JOG_HOLD;

	I_FHOLD_CH1 = I_FHOLD_CH0;
	I_FHOLD_CH2 = I_FHOLD_CH0;

	if(ELIMINA_TUTTI_ALL) I_FHOLD_CH0 = 0;


	// Visualizzazione per SIOMAG		(Ciclo prosegue quando FATM_CH0=1 e I_FHOLD_CH0=0)
	VISUALIZZA_FATM = FATM_CH0;

	// Visualizzazione per SIOMAG 
	VISUALIZZA_HOLD = I_FHOLD_CH0;

    // Appggio di emergenza premuta su area R per HDRILL
	DP_MACCH_IN_EMERG = 0;
	if(!NO_EMERG_I && !APP_MACCH_IN_EMERG)
		DP_MACCH_IN_EMERG = 1;
    APP_MACCH_IN_EMERG = !NO_EMERG_I;

	if(DP_MACCH_IN_EMERG)
	{
		R[R_EMERG_PREMUTA] = 1; // emergenza premuta per HDRILL, che manderà reset al CN e dopo resetta la variabile quando ha fatto il reset
	}
	if(NO_EMERG_I)
	{
		R[R_EMERG_PREMUTA] = 0; // reset variabile per sicurezza al rilascio della emergenza
	}

	//**** GESTIONE RICHIESTA RESET DA PC ****
	if (R[R_SEND_RESET] > 0.5)
	{
		REQ_RESET = 1;
		R[R_SEND_RESET] = (float)0;
	}

	// Richiesta reset effettuta
	if (RESET_MC) 
		REQ_RESET = 0;

    com_cnc1();

}

void com_cnc1(void)
{
	// Puntatori per la gestione standardizzata
	short int *P_VEL_COL = 0;
	short int *P_VEL_BAS = 0;
	short int *P_VEL_NOR = 0;

	// Valore intero area puntata
	int AREA_COL = 0;
	int AREA_BAS = 0;
	int AREA_NOR = 0;

	// Puntatori per ciclica ripetiva su SELJOG
	UCHAR Ind = 0;

	// Gestione tasti CN
	if (!CONF_PLANCIA && !CONF_PLANCIA_CNC)  // Funzionamento solo tastiera CNC
	{
		tastcnc(0);							//Inoltra il tasto senza filtri al ch0
		tastcnc_MC (&CNCSTATUS_CH1 , 0);	//Inoltra il tasto senza filtri al ch1
		tastcnc_MC (&CNCSTATUS_CH2 , 0);	//Inoltra il tasto senza filtri al ch2
	}

	if (CONF_PLANCIA || CONF_PLANCIA_CNC)  // Funzionamento da plancia esterna o CNC
	{

		if (CONF_PLANCIA)
		{
			acktasto();						// Svuota il buffer, non invia il tasto al CNC ch0
			acktasto_MC(&CNCSTATUS_CH1);	// Svuota il buffer, non invia il tasto al CNC ch1
			acktasto_MC(&CNCSTATUS_CH2);	// Svuota il buffer, non invia il tasto al CNC ch2

			APPTASTO_CH0 = APPTASTO_CH1 = APPTASTO_CH2 = 0;

			//Isac: La FB deve essere richiamata con lo stesso codice tasto fintanto che il risultato non è di successo.
			if ( (!COMANDO_A && !COMANDO_B) || (!NO_I_BLC_CH0 && (OK_TASTIN_M_CH0 == 206)) )
			{
				OK_TASTIN_M_CH0 = OK_TASTIN_M_CH1 = OK_TASTIN_M_CH2 = 0;
			}
		}

		//Isac: La FB deve essere richiamata con lo stesso codice tasto fintanto che il risultato non è di successo.

		if (CONF_PLANCIA_CNC)	//=0
		{
			TASTO_CH0 = tasto();					// Lettura tasto inviato da buffer CH0
			TASTO_CH1 = tasto_MC(&CNCSTATUS_CH1);	// Lettura tasto inviato da buffer CH1
			TASTO_CH2 = tasto_MC(&CNCSTATUS_CH2);	// Lettura tasto inviato da buffer CH2

			acktasto();      // Svuota il buffer
			acktasto_MC(&CNCSTATUS_CH1);	// Svuota il buffer, non invia il tasto al CNC ch1
			acktasto_MC(&CNCSTATUS_CH2);	// Svuota il buffer, non invia il tasto al CNC ch2

			if (!TASTO_CH0)		{APPTASTO_CH0 = 0; OK_TASTIN_M_CH0 = 0;}
			else				{APPTASTO_CH0 = TASTO_CH0; OK_TASTIN_M_CH0 = (unsigned short)255;}


			if (!TASTO_CH1)		{APPTASTO_CH1 = 0; OK_TASTIN_M_CH1 = 0;}
			else				{APPTASTO_CH1 = TASTO_CH1; OK_TASTIN_M_CH1 = (unsigned short)255;}


			if (!TASTO_CH2)		{APPTASTO_CH2 = 0; OK_TASTIN_M_CH2 = 0;}
			else				{APPTASTO_CH2 = TASTO_CH2; OK_TASTIN_M_CH2 = (unsigned short)255;}

		}


		if (!RN_COMANDO_A && !RN_COMANDO_B)
			OK_SEND = 1;


		//Parte il riferimento Assi
		if (RIFMANO && !Mg_MC(64) && OK_SEND)
		{
			SendCnc (6, 178, "L<RIFASSI.CS4>");  // 6 = CCMAN; 178 = S_START
			SendCnc_MC(&CNCSTATUS_CH1,6, 178, "L<RIFASSI_CH1.CS4>");
			SendCnc_MC(&CNCSTATUS_CH2,6, 178, "L<RIFASSI_CH2.CS4>");
			OK_SEND = 0;
		}

		if ((AXSHARED_DEFAULT_MANUAL_REQ || (MANO && AXSHARED_DEFAULT_RESET_REQ)) && OK_SEND)
		{
			AXSHARED_DEFAULT_RESET_REQ = AXSHARED_DEFAULT_RESET = 0;
			OK_SEND = 0;
		}

		//Lancio il ciclo di rotazione mandrino in manuale 
		if (CICLO_ROTMAN && !Mg_MC(71) && OK_SEND)
		{
			SendCnc (6, 178, "L<ROTMAN.CS4>"); // 6 = CCMAN; 178 = S_START
			OK_SEND = 0;
		}

		//Ciclo volantino in manuale
		if (CICLO_VOLROT && !Mg_MC(71) && OK_SEND)
		{
			SendCnc (6, 178, "L<VOLROT.CS4>"); // 6 = CCMAN; 178 = S_START
			OK_SEND = 0;
		}

		// Chiamata Posizione di Riposo
		if (CICLO_POSRIP && !Mg_MC(247) && OK_SEND ) 
		{
			SendCnc (6, 178, "L<POSRIP.CS4>"); // 6 = CCMAN; 178 = S_START
			SendCnc_MC(&CNCSTATUS_CH1,6, 178, "L<POSRIP_CH1.CS4>");
			SendCnc_MC(&CNCSTATUS_CH2,6, 178, "L<POSRIP_CH2.CS4>");
			OK_SEND = 0;
		}

		// Chiamata SR Cambio utensile assistito
		if (CICLO_CAMBUT_MAN && !Mg_MC(114) && OK_SEND)
		{
			SendCnc (6, 178, "L<CAMBMAN.CS4>"); // 6 = CCMAN; 178 = S_START
			SendCnc_MC(&CNCSTATUS_CH1,6, 178, "L<CAMBMAN_CH1.CS4>");
			SendCnc_MC(&CNCSTATUS_CH2,6, 178, "L<CAMBMAN_CH2.CS4>");
			OK_SEND = 0;
		}		

		// Azzero memoria utensile
		if (MANO && R[R_UTSCON] && MANDRINO_SENZA_UT && RESET_ALL && OK_SEND && GEST_OPERATORE_MAN)
		{
			SendCnc (6, 178, "L<ZERO_UT.CS4>"); // 6 = CCMAN; 178 = S_START
			OK_SEND = 0;
		}

		//Ciclo di deposito utensile in manuale
		if (CICLO_DEPUT && CONS_INIZIO_DEP_PRE && !Mg_MC(72) && OK_SEND)
		{
			SendCnc (6, 178, "L<DEPUT.CS4>"); // 6 = CCMAN; 178 = S_START 
			SendCnc_MC(&CNCSTATUS_CH1,6, 178, "L<DEPUT_CH1.CS4>");
			SendCnc_MC(&CNCSTATUS_CH2,6, 178, "L<DEPUT_CH2.CS4>");
			OK_SEND = 0;
		}

		//Ciclo di prelievo utensile in manuale
		if (CICLO_PRELUT && CONS_INIZIO_DEP_PRE && !Mg_MC(74) && OK_SEND)
		{
			SendCnc (6, 178, "L<PRELUT.CS4>"); // 6 = CCMAN; 178 = S_START
			SendCnc_MC(&CNCSTATUS_CH1,6, 178, "L<PRELUT_CH1.CS4>");
			SendCnc_MC(&CNCSTATUS_CH2,6, 178, "L<PRELUT_CH2.CS4>");
			OK_SEND = 0;
		}


		//********** INIZIO TRASMISSIONE COMANNDI CANALE 0 *************
		if ((RICH_RESET || REQ_RESET) && RP_PON && (OK_TASTIN_M_CH0 == 0))
		{
			APPTASTO_CH0 = (unsigned short)CT_RST;     // Comando reset
			OK_TASTIN_M_CH0 = 201;
		}

		if (SEL_MANU_I && !MANO && RP_PON && (OK_TASTIN_M_CH0 == 0))
		{
			APPTASTO_CH0 = (unsigned short)CT_JOG;     // Comando macchina in manuale
			OK_TASTIN_M_CH0 = 202;
		}

		if (((SEL_AUTO_I || SEL_SEMIAUTO_I) && !AUTO) && RP_PON && (OK_TASTIN_M_CH0 == 0))
		{
			APPTASTO_CH0 = (unsigned short)CT_AUT;     // Comando macchina in automatico
			OK_TASTIN_M_CH0 = 203;
		}

		//if ( ( (DP_START_CYCLE && RP_PON && (R[R_START] == 1)) || START_STRINGA || (DP_START_CYCLE && RESET_ALL)) && (OK_TASTIN_M_CH0 == 0))
		if ( ( ( ( (DP_START_CYCLE && O_INIZ_CH0) || REQ_CICLO_ON_CH0 || REQ_CICLO_ON) && CICLO_ON && !O_ESEC_CH0 && RP_PON) || START_STRINGA) && (OK_TASTIN_M_CH0 == 0) )
		{
			APPTASTO_CH0 = (unsigned short)CT_STA;
			OK_TASTIN_M_CH0 = 204;
		}

		if (LOAD_PROG && (OK_TASTIN_M_CH0 == 0))
		{
			APPTASTO_CH0 = (unsigned short)CT_SF2;
			OK_TASTIN_M_CH0 = 205;
		}

		if (NO_I_BLC_CH0 && (OK_TASTIN_M_CH0 == 0 || OK_TASTIN_M_CH0 == 206))
		{
			APPTASTO_CH0 = (unsigned short)CT_REL;
			OK_TASTIN_M_CH0 = 206;
		}

		if (O_BLC_CH0 && RESET_ALL && (OK_TASTIN_M_CH0 == 0 || OK_TASTIN_M_CH0 == 207))
		{
			APPTASTO_CH0 = (unsigned short)CT_REL;
			OK_TASTIN_M_CH0 = 207;
		}


		// Trasmissione comandi degli assi del canale 0 **********************************************************
		for (Ind=0;Ind<12;Ind++)
		{
			if ( COM_AVANTI[CHANNEL_CH0][Ind] && AXESEL_CH0(Ind) && RP_PON && SELJOG_OK && (OK_TASTIN_M_CH0==0 || OK_TASTIN_M_CH0==(10*Ind+1))) //OK_TASTIN_M_CH0==vecchio valore: permette ripetizione comando, necessario sopratutto a slave che sembra nn ricever il primo a volte
			{
				APPTASTO_CH0	= (unsigned short)CT_JPP;
				OK_TASTIN_M_CH0	= (10*Ind+1);
			}

			if ( COM_INDIETRO[CHANNEL_CH0][Ind] && AXESEL_CH0(Ind) && RP_PON && SELJOG_OK && (OK_TASTIN_M_CH0==0 || OK_TASTIN_M_CH0==(10*Ind+2)))
			{
				APPTASTO_CH0	= (unsigned short)CT_JNP;
				OK_TASTIN_M_CH0	= (10*Ind+2);
			}

			if ( ARR_AVANTI[CHANNEL_CH0][Ind] && AXESEL_CH0(Ind) && RP_PON && (OK_TASTIN_M_CH0==0 || OK_TASTIN_M_CH0==(10*Ind+3)))
			{
				APPTASTO_CH0	= (unsigned short)CT_JPR;
				OK_TASTIN_M_CH0	= (10*Ind+3);
			}

			if ( ARR_INDIETRO[CHANNEL_CH0][Ind] && AXESEL_CH0(Ind) && RP_PON && (OK_TASTIN_M_CH0==0 || OK_TASTIN_M_CH0==(10*Ind+4)))
			{
				APPTASTO_CH0	= (unsigned short)CT_JNR;
				OK_TASTIN_M_CH0	= (10*Ind+4);
			}
		}// Canale 0
		//********** FINE TRASMISSIONE COMANDI CANALE 0 ****************


		//********** INIZIO TRASMISSIONE COMANNDI CANALE 1 *************
		if ((RICH_RESET || REQ_RESET) && RP_PON && (OK_TASTIN_M_CH1 == 0))
		{
			APPTASTO_CH1 = (unsigned short)CT_RST;     /* Comando reset */
			OK_TASTIN_M_CH1 = 201;
		}

		if (SEL_MANU_I && !MANO && RP_PON && (OK_TASTIN_M_CH1 == 0))
		{
			APPTASTO_CH1 = (unsigned short)CT_JOG;     /* Comando macchina in manuale */
			OK_TASTIN_M_CH1 = 202;
		}

		if (((SEL_AUTO_I || SEL_SEMIAUTO_I) && !AUTO) && RP_PON && (OK_TASTIN_M_CH1 == 0))
		{
			APPTASTO_CH1 = (unsigned short)CT_AUT;     /* Comando macchina in automatico */
			OK_TASTIN_M_CH1 = 203;
		}

		//if ( ( (DP_START_CYCLE && RP_PON && (R[R_START] == 1)) || START_STRINGA || (DP_START_CYCLE && RESET_ALL)) && (OK_TASTIN_M_CH1 == 0))
		if ( ( ( ( (DP_START_CYCLE && O_INIZ_CH1) || REQ_CICLO_ON_CH1) && CICLO_ON_CH1 && !O_ESEC_CH1 && RP_PON) || START_STRINGA) && (OK_TASTIN_M_CH1 == 0) )
		{
			APPTASTO_CH1 = (unsigned short)CT_STA;
			OK_TASTIN_M_CH1 = 204;
		}

		if (LOAD_PROG && (OK_TASTIN_M_CH1 == 0))
		{
			APPTASTO_CH1 = (unsigned short)CT_SF2;
			OK_TASTIN_M_CH1 = 205;
		}

		if (NO_I_BLC_CH1 && (OK_TASTIN_M_CH1 == 0 || OK_TASTIN_M_CH1 == 206))
		{
			APPTASTO_CH1 = (unsigned short)CT_REL;
			OK_TASTIN_M_CH1 = 206;
		}

		if (O_BLC_CH1 && RESET_ALL && (OK_TASTIN_M_CH1 == 0 || OK_TASTIN_M_CH1 == 207))
		{
			APPTASTO_CH1 = (unsigned short)CT_REL;
			OK_TASTIN_M_CH1 = 207;
		}


		// Trasmissione comandi degli assi del canale 1 **********************************************************
		for (Ind=0;Ind<12;Ind++)
		{
			if ( COM_AVANTI[CHANNEL_CH1][Ind] && AXESEL_MC(&CNCCTRL_CH1, Ind) && RP_PON && SELJOG_OK && (OK_TASTIN_M_CH1==0 || OK_TASTIN_M_CH1==(10*Ind+1))) //OK_TASTIN_M_CH1==vecchio valore: permette ripetizione comando, necessario sopratutto a slave che sembra nn ricever il primo a volte
			{
				APPTASTO_CH1	= (unsigned short)CT_JPP;
				OK_TASTIN_M_CH1	= (10*Ind+1);
			}

			if ( COM_INDIETRO[CHANNEL_CH1][Ind] && AXESEL_MC(&CNCCTRL_CH1, Ind) && RP_PON && SELJOG_OK && (OK_TASTIN_M_CH1==0 || OK_TASTIN_M_CH1==(10*Ind+2)))
			{
				APPTASTO_CH1	= (unsigned short)CT_JNP;
				OK_TASTIN_M_CH1	= (10*Ind+2);
			}

			if ( ARR_AVANTI[CHANNEL_CH1][Ind] && AXESEL_MC(&CNCCTRL_CH1, Ind) && RP_PON && (OK_TASTIN_M_CH1==0 || OK_TASTIN_M_CH1==(10*Ind+3)))
			{
				APPTASTO_CH1	= (unsigned short)CT_JPR;
				OK_TASTIN_M_CH1	= (10*Ind+3);
			}

			if ( ARR_INDIETRO[CHANNEL_CH1][Ind] && AXESEL_MC(&CNCCTRL_CH1, Ind) && RP_PON && (OK_TASTIN_M_CH1==0 || OK_TASTIN_M_CH1==(10*Ind+4)))
			{
				APPTASTO_CH1	= (unsigned short)CT_JNR;
				OK_TASTIN_M_CH1	= (10*Ind+4);
			}
		}// Canale 1
		//********** FINE TRASMISSIONE COMANDI CANALE 1 ****************


		//********** INIZIO TRASMISSIONE COMANNDI CANALE 2 *************
		if ((RICH_RESET || REQ_RESET) && RP_PON && (OK_TASTIN_M_CH2 == 0))
		{
			APPTASTO_CH2 = (unsigned short)CT_RST;     /* Comando reset */
			OK_TASTIN_M_CH2 = 201;
		}

		if (SEL_MANU_I && !MANO && RP_PON && (OK_TASTIN_M_CH2 == 0))
		{
			APPTASTO_CH2 = (unsigned short)CT_JOG;     /* Comando macchina in manuale */
			OK_TASTIN_M_CH2 = 202;
		}

		if (((SEL_AUTO_I || SEL_SEMIAUTO_I) && !AUTO) && RP_PON && (OK_TASTIN_M_CH2 == 0))
		{
			APPTASTO_CH2 = (unsigned short)CT_AUT;     /* Comando macchina in automatico */
			OK_TASTIN_M_CH2 = 203;
		}

		//if ( ( (DP_START_CYCLE && RP_PON && (R[R_START] == 1)) || START_STRINGA || (DP_START_CYCLE && RESET_ALL)) && (OK_TASTIN_M_CH2 == 0))
		if ( ( ( ( (DP_START_CYCLE && O_INIZ_CH2) || REQ_CICLO_ON_CH2) && CICLO_ON_CH2 && !O_ESEC_CH2 && RP_PON) || START_STRINGA) && (OK_TASTIN_M_CH2 == 0) )
		{
			APPTASTO_CH2 = (unsigned short)CT_STA;
			OK_TASTIN_M_CH2 = 204;
		}

		if (LOAD_PROG && (OK_TASTIN_M_CH2 == 0))
		{
			APPTASTO_CH2 = (unsigned short)CT_SF2;
			OK_TASTIN_M_CH2 = 205;
		}

		if (NO_I_BLC_CH2 && (OK_TASTIN_M_CH2 == 0 || OK_TASTIN_M_CH2 == 206))
		{
			APPTASTO_CH2 = (unsigned short)CT_REL;
			OK_TASTIN_M_CH2 = 206;
		}

		if (O_BLC_CH2 && RESET_ALL && (OK_TASTIN_M_CH2 == 0 || OK_TASTIN_M_CH2 == 207))
		{
			APPTASTO_CH2 = (unsigned short)CT_REL;
			OK_TASTIN_M_CH2 = 207;
		}


		// Trasmissione comandi degli assi del canale 2 **********************************************************
		for (Ind=0;Ind<12;Ind++)
		{
			if ( COM_AVANTI[CHANNEL_CH2][Ind] && AXESEL_MC(&CNCCTRL_CH2, Ind) && RP_PON && SELJOG_OK && (OK_TASTIN_M_CH2==0 || OK_TASTIN_M_CH2==(10*Ind+1))) //OK_TASTIN_M_CH2==vecchio valore: permette ripetizione comando, necessario sopratutto a slave che sembra nn ricever il primo a volte
			{
				APPTASTO_CH2	= (unsigned short)CT_JPP;
				OK_TASTIN_M_CH2	= (10*Ind+1);
			}

			if ( COM_INDIETRO[CHANNEL_CH2][Ind] && AXESEL_MC(&CNCCTRL_CH2, Ind) && RP_PON && SELJOG_OK && (OK_TASTIN_M_CH2==0 || OK_TASTIN_M_CH2==(10*Ind+2)))
			{
				APPTASTO_CH2	= (unsigned short)CT_JNP;
				OK_TASTIN_M_CH2	= (10*Ind+2);
			}

			if ( ARR_AVANTI[CHANNEL_CH2][Ind] && AXESEL_MC(&CNCCTRL_CH2, Ind) && RP_PON && (OK_TASTIN_M_CH2==0 || OK_TASTIN_M_CH2==(10*Ind+3)))
			{
				APPTASTO_CH2	= (unsigned short)CT_JPR;
				OK_TASTIN_M_CH2	= (10*Ind+3);
			}

			if ( ARR_INDIETRO[CHANNEL_CH2][Ind] && AXESEL_MC(&CNCCTRL_CH2, Ind) && RP_PON && (OK_TASTIN_M_CH2==0 || OK_TASTIN_M_CH2==(10*Ind+4)))
			{
				APPTASTO_CH2	= (unsigned short)CT_JNR;
				OK_TASTIN_M_CH2	= (10*Ind+4);
			}
		}// Canale 2
		//********** FINE TRASMISSIONE COMANDI CANALE 2 ****************

		// SELJOG non attiva nessun comando
		if (!COMANDO_A && !COMANDO_B)
			SELJOG = 255;

		// =======================================================================================
		// ============================ Selezione assi e velocità ================================
		// =======================================================================================

		//*********** SELEZIONE ASSI E VELOCITA PER IL CANALE 0 *************
		for (Ind=0;Ind<12;Ind++)
		{
			if (((COM_AVANTI[CHANNEL_CH0][Ind] && DP_COMANDO_B) || (COM_INDIETRO[CHANNEL_CH0][Ind] && DP_COMANDO_A)) && (SELJOG == 255))
			{

				// Punto alle 3 word delle velocità 
				P_VEL_COL = &VEL_ASSE_X_COLLAUDO + Ind*3;
				P_VEL_BAS = &VEL_ASSE_X_COLLAUDO + Ind*3 + 1;
				P_VEL_NOR = &VEL_ASSE_X_COLLAUDO + Ind*3 + 2;

				// Appoggio su interi il valore letto
				AREA_COL = *P_VEL_COL;
				AREA_BAS = *P_VEL_BAS;
				AREA_NOR = *P_VEL_NOR;

				// Velocità da caricare
				VEL_ASSE_COLLAUDO	= AREA_COL;	
				VEL_ASSE_BASSA		= AREA_BAS;		
				VEL_ASSE_NORMALE	= AREA_NOR;


				// Carico il valore di velocità settato
				if (ASSI_NORIF_FMS && (Ind!=AX_Q_CH0) && (Ind!=AX_U_CH0))
				{ // Assi non riferiti
					if (COLLAUDO_ON)
					{
						SELJOG = SelJog(Ind, 0, (long)VEL_ASSE_COLLAUDO);		/* Seleziona asse a velocita' di collaudo */
						WP0=VEL_ASSE_COLLAUDO;
					}
					else
					{
						SELJOG = SelJog(Ind, 0, (long)VEL_ASSE_BASSA);		/* Seleziona asse a velocita' bassa */
						WP0=VEL_ASSE_BASSA;
					}
				} 
				else if ((Ind!=AX_Q_CH0) && (Ind!=AX_U_CH0))
				{ // Assi riferiti 
					SELJOG = SelJog(Ind, 0, (long)VEL_ASSE_NORMALE);		/* Seleziona asse a velocita' normale */
					WP0=VEL_ASSE_NORMALE;
				}

			} // fine "IF" x ogni asse

		} // fine ripetizioni x tutti gli assi

		//*********** SELEZIONE ASSI E VELOCITA PER IL CANALE 1 (solo asse W) *************
		if (((COM_AVANTI[CHANNEL_CH1][AX_W_CH1] && DP_COMANDO_B) || (COM_INDIETRO[CHANNEL_CH1][AX_W_CH1] && DP_COMANDO_A)) && (SELJOG == 255))
		{

			// Punto alle 3 word delle velocità 
			P_VEL_COL = &VEL_ASSE_W_COLLAUDO ;
			P_VEL_BAS = &VEL_ASSE_W_COLLAUDO + 1;
			P_VEL_NOR = &VEL_ASSE_W_COLLAUDO + 2;

			// Appoggio su interi il valore letto
			AREA_COL = *P_VEL_COL;
			AREA_BAS = *P_VEL_BAS;
			AREA_NOR = *P_VEL_NOR;

			// Velocità da caricare
			VEL_ASSE_COLLAUDO	= AREA_COL;	
			VEL_ASSE_BASSA		= AREA_BAS;		
			VEL_ASSE_NORMALE	= AREA_NOR;


			// Carico il valore di velocità settato
			if (ASSI_NORIF_FMS)
			{ // Assi non riferiti
				if (COLLAUDO_ON)
				{
					SELJOG = SelJog_MC(&CNCCTRL_CH1, &CNCSTATUS_CH1, &CNPLCHANDLE_CH1, AX_W_CH1, 0, (long)VEL_ASSE_COLLAUDO);	/* Seleziona asse a velocita' di collaudo */
					WP0=VEL_ASSE_COLLAUDO;
				}
				else
				{
					SELJOG = SelJog_MC(&CNCCTRL_CH1, &CNCSTATUS_CH1, &CNPLCHANDLE_CH1, AX_W_CH1, 0, (long)VEL_ASSE_BASSA);	/* Seleziona asse a velocita' bassa */
					WP0=VEL_ASSE_BASSA;
				}
			} 
			else
			{ // Assi riferiti 
				SELJOG = SelJog_MC(&CNCCTRL_CH1, &CNCSTATUS_CH1, &CNPLCHANDLE_CH1, AX_W_CH1, 0, (long)VEL_ASSE_NORMALE);		/* Seleziona asse a velocita' normale */
				WP0=VEL_ASSE_NORMALE;
			}

		} // fine "IF" x ogni asse

		//*********** SELEZIONE ASSI E VELOCITA PER IL CANALE 2 *************
		for (Ind=0;Ind<12;Ind++)
		{
			if (((COM_AVANTI[CHANNEL_CH2][Ind] && DP_COMANDO_B) || (COM_INDIETRO[CHANNEL_CH2][Ind] && DP_COMANDO_A)) && (SELJOG == 255))
			{

				if(MORSE_MOTORIZZATE)
				{
					// Punto alle 3 word delle velocità 
					P_VEL_COL = &VEL_ASSE_MORSE_COLLAUDO ;
					P_VEL_BAS = &VEL_ASSE_MORSE_COLLAUDO + 1;
					P_VEL_NOR = &VEL_ASSE_MORSE_COLLAUDO + 2;

					// Appoggio su interi il valore letto
					AREA_COL = *P_VEL_COL;
					AREA_BAS = *P_VEL_BAS;
					AREA_NOR = *P_VEL_NOR;

					// Velocità da caricare
					VEL_ASSE_COLLAUDO	= AREA_COL;	
					VEL_ASSE_BASSA		= AREA_BAS;		
					VEL_ASSE_NORMALE	= AREA_NOR;
				}


				// Carico il valore di velocità settato
				if (ASSI_NORIF_FMS)
				{ // Assi non riferiti
					if (COLLAUDO_ON)
					{
						SELJOG = SelJog_MC(&CNCCTRL_CH2, &CNCSTATUS_CH2, &CNPLCHANDLE_CH2, Ind, 0, (long)VEL_ASSE_COLLAUDO);	/* Seleziona asse a velocita' di collaudo */
						WP0=VEL_ASSE_COLLAUDO;
					}
					else
					{
						SELJOG = SelJog_MC(&CNCCTRL_CH2, &CNCSTATUS_CH2, &CNPLCHANDLE_CH2, Ind, 0, (long)VEL_ASSE_BASSA);		/* Seleziona asse a velocita' bassa */
						WP0=VEL_ASSE_BASSA;
					}
				} 
				else
				{ // Assi riferiti 
					SELJOG = SelJog_MC(&CNCCTRL_CH2, &CNCSTATUS_CH2, &CNPLCHANDLE_CH2, Ind, 0, (long)VEL_ASSE_NORMALE);		/* Seleziona asse a velocita' normale */
					WP0=VEL_ASSE_NORMALE;
				}

			} // fine "IF" x ogni asse

		} // fine ripetizioni x tutti gli assi


		// RITARDO SELEZIONE ASSE COMPIUTA ******************************************************
		SELJOG_OK = 0;
		if (SELJOG != 0)
			TIMESELJOG = 80;  
		else
		{
			if (TIMESELJOG > 0)
				TIMESELJOG--;
		}
		if (TIMESELJOG == 0)
			SELJOG_OK = 1;



		if (APPTASTO_CH0 != S_NULL)
		{
			ESITO_TASTCNC_CH0 = tastcnc ((unsigned char) APPTASTO_CH0);						// Invio comando a CNC ch0
			LOG_MSG2(1, "CH0 Emesso tasto (%d) risultato (%d)", APPTASTO_CH0, ESITO_TASTCNC_CH0);
			if (ESITO_TASTCNC_CH0) APPTASTO_CH0 = S_NULL;
		}


		if (APPTASTO_CH1 != S_NULL)
		{
			ESITO_TASTCNC_CH1 = tastcnc_MC(&CNCSTATUS_CH1,(unsigned char) APPTASTO_CH1);	// Invio comando a CNC ch1
			LOG_MSG2(1, "CH1 Emesso tasto (%d) risultato (%d)", APPTASTO_CH1, ESITO_TASTCNC_CH1);
			if (ESITO_TASTCNC_CH1) APPTASTO_CH1 = S_NULL;
		}

		if (APPTASTO_CH2 != S_NULL)
		{
			ESITO_TASTCNC_CH2 = tastcnc_MC(&CNCSTATUS_CH2,(unsigned char) APPTASTO_CH2);	// Invio comando a CNC ch2
			LOG_MSG2(1, "CH2 Emesso tasto (%d) risultato (%d)", APPTASTO_CH2, ESITO_TASTCNC_CH2);
			if (ESITO_TASTCNC_CH2) APPTASTO_CH2 = S_NULL;
		}
	}
}

