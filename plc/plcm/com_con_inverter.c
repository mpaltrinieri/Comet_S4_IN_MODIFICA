/*
        --------------------------------------------------------------
        TITOLO:         COMUNICAZIONE INVERTER
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione flags da comunicazione RS485 con inverter
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    com_con_inverter(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:           
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CR4 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           05-07-2022
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"


void com_con_inverter_INPUT(void)
{

	//**** NEL CONFMAC.*** è impostata la variabile:
	//*************************************************************************************
	//********* VARIABILI DI IMPOSTAZIONE COMUNICAZIONE CON PLC IEC: PER GLI INVERTER ****+
	//*************************************************************************************
	//F_A19880=0003    {INVERTER 0: AA BB         --> AA=canale, BB=indice asse nel canale
	//F_A19882=01101   {INVERTER 0:       TT C MM -->                                      TT=tecnologia, C=porta COM, MM=indirizzo MODBUS
	// Tecnologia TT=01  --->  sta per inverter Delta (lettura stato e invio comandi dal PLC IEC)
	// Tecnologia TT=02  --->  sta per inverter Yaskawa A1000, V1000 (solo lettura stato)
	// Tecnologia TT=03  --->  sta per inverter Yaskawa A1000, V1000  (lettura stato e invio comandi dal PLC IEC)

	if(PON)
	{
		INVERTER_0_TECNOLOGIA = (((unsigned int) AF_INVERTER_0_COM01_MODBUS / 1000) % 100);


		if( INVERTER_0_TECNOLOGIA == 1 )  // Impostata tecnologia TT=01
		{
			GESTIONE_INVERTER_DELTA = 1;  // --->  inverter DELTA (lettura stato e invio comandi)
			GESTIONE_INVERTER_A1000 = 0;
			GESTIONE_INVERTER_V1000 = 0;
		}
		else if( INVERTER_0_TECNOLOGIA == 2 )  // Impostata tecnologia TT=02
		{
			GESTIONE_INVERTER_DELTA = 0;
			GESTIONE_INVERTER_A1000 = 1;  // --->  inverter YASKAWA A1000 (solo lettura stato)
			GESTIONE_INVERTER_V1000 = 0;
		}
		else if( INVERTER_0_TECNOLOGIA == 3 )  // Impostata tecnologia TT=03
		{
			GESTIONE_INVERTER_DELTA = 0;
			GESTIONE_INVERTER_A1000 = 0;
			GESTIONE_INVERTER_V1000 = 1;   // --->  inverter YASKAWA V1000 o A1000 (lettura stato e invio comandi)
		}
		else
		{
			GESTIONE_INVERTER_DELTA = 0;
			GESTIONE_INVERTER_A1000 = 0;
			GESTIONE_INVERTER_V1000 = 0;
		}

		// Abilita l'errore di comunicazione con inverter. Se il plc iec non riesce più a comunicare con inverter passerà
		// codice di errore 9999 in AF_INVERTER_0_CODE_ERROR. IL plc macchina deve settare un allarme INVERTER_0_COM_ERROR_FAL:
		// - se tramite la COM dell'inverter viene solo letto lo stato allora l'allarme viene dato solo una volta dopo l'accensione,
		//   dopo si consente di resettarlo e non potrà più ricomparire fino alla prossima riaccensione della macchina
		// - se tramite la COM l'inverter viene anche comandato allora l'allarme si ripresenterà se la comunicazione continuerà a mancare
		ENABLE_INVERTER_0_COM_ERROR = 1;
	}

	// Definisco timer per ritardo positivo su ENABLE_INVERTER_0_COM_ERROR, evitiamo di prendere dei falsi allarmi di comunicazione su COM
	// quando il CN è appena andato in start
	tS(TS_RIT_ENABLE_INVERTER_0_COM_ERROR, (unsigned char) ENABLE_INVERTER_0_COM_ERROR);


	if(RESET_ALL || RESET_MC)
	{
		INVERTER_0_COM_ERROR_FAL = 0;
	}


	if(GESTIONE_INVERTER_DELTA)  // abilitazione comunicazione inverter --> plc iec --> plc
	{
		// INGRESSI PLC: da INVERTER-->PLC
		DW_INVERTER_0_OUTPUT = (unsigned long) AF_INVERTER_0_OUTPUT;
		// FREQUENZA MASSIMA IMPOSTATA SU INVERTER: da INVERTER-->PLC
		FL_INVERTER_0_FREQ_MAX = (float) AF_INVERTER_0_MAX_FREQ;
		// CODICE DI ERRORE: da INVERTER-->PLC
		FL_INVERTER_0_CODE_ERROR = (float) AF_INVERTER_0_CODE_ERROR;

		if( RP_TSuppl[TS_RIT_ENABLE_INVERTER_0_COM_ERROR] && ((FL_INVERTER_0_CODE_ERROR > 9998.9) && (FL_INVERTER_0_CODE_ERROR < 9999.1))  )
			INVERTER_0_COM_ERROR_FAL = 1;

		//******* L'inverter DELTA MS300 espone la percentuale di coppia rispetto alla coppia nominale, per esporre il valore in N*m occorre
        //******* inserire in CONFMAC.PHN il valore della coppia nominale del mandrino. Poiché la macchina può avere due mandrini di diverso tipo
        //******* (con e senza encoder), occorre definire due campi di coppia nominale per ogni inverter gestito in Voilap connect
		if(CONF_MASK_RIGIDA)
			AF_APP_TORQUE_INVERTER_0 = AF_NOM_TORQUE1_INVERTER_0;  // Passa al plc iec il valore della coppia del mandrino con encoder
		else
			AF_APP_TORQUE_INVERTER_0 = AF_NOM_TORQUE2_INVERTER_0;  // Passa al plc iec il valore della coppia del mandrino senza encoder

		// Assorbimento mandrino espresso come percentuale della corrente nominale mandrino: il valore viene passato dal PLC IEC al PLC macchina
		APP_PERC_CORRENTE_INVERTER_0 = AF_PERC_CORRENTE_INVERTER_0;

		APP_PERC_CORRENTE_INVERTER_0 = (int) (APP_PERC_CORRENTE_INVERTER_0 * 100+0.5) / 100.0f; // cast a due cifre decimali

		R[R_ASSORBIMENTO_MANDR] = (double) APP_PERC_CORRENTE_INVERTER_0;

	}
	else if(GESTIONE_INVERTER_A1000)
	{
		INVERTER_0_INV_NOIN_BLOCCO = INV_NONBLOC_I;
		INVERTER_0_INV_NO_OVERLOAD = LOAD_INVERTEROK_I;
		INVERTER_0_INV_VEL_OK = VEL_INVERTEROK_I;
		INVERTER_0_INV_MANDR_FERMO = MANDRINO_FERMO_I;

		// CODICE DI ERRORE: da INVERTER-->PLC (AGGIUNTO SOLO PER DEBUG)
		FL_INVERTER_0_CODE_ERROR = (float) AF_INVERTER_0_CODE_ERROR;
		INVERTER_0_INV_MANDR_FERMO_DA_RS485 = (((unsigned long) AF_INVERTER_0_OUTPUT & (0x08)) >> 3);

		if( RP_TSuppl[TS_RIT_ENABLE_INVERTER_0_COM_ERROR] && ((FL_INVERTER_0_CODE_ERROR > 9998.9) && (FL_INVERTER_0_CODE_ERROR < 9999.1))  )
		{
			ENABLE_INVERTER_0_COM_ERROR = 0;    // disabilita allarme di comunicazione COM, l'allarme potrà ricomparire solo dopo il prossimo restart
			INVERTER_0_COM_ERROR_FAL = 1;
		}

		//******* L'inverter A1000 espone la percentuale di coppia rispetto alla coppia nominale, per esporre il valore in N*m occorre
        //******* inserire in CONFMAC.PHN il valore della coppia nominale del mandrino. Poiché la macchina può avere due mandrini di diverso tipo
        //******* (con e senza encoder), occorre definire due campi di coppia nominale per ogni inverter gestito in Voilap connect
		if(CONF_MASK_RIGIDA)
			AF_APP_TORQUE_INVERTER_0 = AF_NOM_TORQUE1_INVERTER_0;  // Passa al plc iec il valore della coppia del mandrino con encoder
		else
			AF_APP_TORQUE_INVERTER_0 = AF_NOM_TORQUE2_INVERTER_0;  // Passa al plc iec il valore della coppia del mandrino senza encoder

		// Assorbimento mandrino espresso come percentuale della corrente nominale mandrino: il valore viene passato dal PLC IEC al PLC macchina
		APP_PERC_CORRENTE_INVERTER_0 = AF_PERC_CORRENTE_INVERTER_0;

		APP_PERC_CORRENTE_INVERTER_0 = (int) (APP_PERC_CORRENTE_INVERTER_0 * 100+0.5) / 100.0f; // cast a due cifre decimali

		R[R_ASSORBIMENTO_MANDR] = (double) APP_PERC_CORRENTE_INVERTER_0;

	}
	else if(GESTIONE_INVERTER_V1000)  // abilitazione comunicazione inverter --> plc iec --> plc
	{
		// INGRESSI PLC: da INVERTER-->PLC
		DW_INVERTER_0_OUTPUT = (unsigned long) AF_INVERTER_0_OUTPUT;
		// FREQUENZA MASSIMA IMPOSTATA SU INVERTER: da INVERTER-->PLC
		FL_INVERTER_0_FREQ_MAX = (float) AF_INVERTER_0_MAX_FREQ;
		// CODICE DI ERRORE: da INVERTER-->PLC
		FL_INVERTER_0_CODE_ERROR = (float) AF_INVERTER_0_CODE_ERROR;

		if( RP_TSuppl[TS_RIT_ENABLE_INVERTER_0_COM_ERROR] && ((FL_INVERTER_0_CODE_ERROR > 9998.9) && (FL_INVERTER_0_CODE_ERROR < 9999.1))  )
			INVERTER_0_COM_ERROR_FAL = 1;
	}
	else
	{
		INVERTER_0_INV_NOIN_BLOCCO = INV_NONBLOC_I;
		INVERTER_0_INV_NO_OVERLOAD = LOAD_INVERTEROK_I;
		INVERTER_0_INV_VEL_OK = VEL_INVERTEROK_I;
		INVERTER_0_INV_MANDR_FERMO = MANDRINO_FERMO_I;
	}
}

void com_con_inverter_OUTPUT(void)
{
	if(GESTIONE_INVERTER_DELTA)  // abilitazione comunicazione plc --> plc iec --> inverter
	{
		// FREQUENZA TARGET: da PLC-->INVERTER
		AF_INVERTER_0_TARGET_FREQ = (float) FL_INVERTER_0_FREQ_TARGET;

		// USCITE PLC:
		START_INVERTER_O = INVERTER_0_START_INV_FW;

		// USCITE PLC: da PLC-->INVERTER
		AF_INVERTER_0_INPUT = (float) DW_INVERTER_0_INPUT;

		// Velocità massima di rotazione mandrino da tarature
		if(RP_PON && !READ_SETTING_ASSE_Q_ESEG)
		{
			read_var (VL_FLOT, 4054, -1, AX_Q_CH0, &APP_VEL_MAX_ASSE_Q);              /* V4054/6 = velocita' massima (gradi/ciclo assi) asse Q in taratura */
			// ((APP_VEL_MAX_ASSE_Q / CICLO_ASSI) * 60) --> sono gradi al minuto
			VEL_MAX_ASSE_Q = ((APP_VEL_MAX_ASSE_Q / CICLO_ASSI) * 60) / 360;          // VEL_MAX_ASSE_Q = velocità massima asse Q espressa in rpm
			READ_SETTING_ASSE_Q_ESEG = 1;
		}

		// Appoggio speed mandrino da passare al plc iec
		read_var (VL_FLOT, 6058, -1, AX_Q_CH0, &APP_SPEED_ASSE_Q);                 /* V4058/6 = velocita' attuale (giri/ciclo assi) asse mandrino */
		VEL_ACT_ASSE_Q = (APP_SPEED_ASSE_Q / CICLO_ASSI) * 60;                     // VEL_ACT_ASSE_Q = speed attuale mandrino espressa in rpm

		// AGGIUNGO FILTRO SU VELOCITA' DI ROTAZIONE: in modo random il valore esposto diventa di milioni di rpm probabilmente dovuto a 
		//                                            disturbi su encoder mandrino in fase di decelerazione, in particolare con la lama
		// Aggiorno il valore da esporre della velocità attuale solo se entro la massima velocità di taratura + 2000 rpm di tolleranza
		if(ABS(VEL_ACT_ASSE_Q) <= (VEL_MAX_ASSE_Q+2000.0))
			AF_INVERTER_0_SPEED = VEL_ACT_ASSE_Q;   // AF_INVERTER_0_SPEED = variabile in cui appoggio la speed mandrino per il plc iec
	}
	else if(GESTIONE_INVERTER_A1000)
	{
		// USCITE PLC: da PLC-->INVERTER
		START_INVERTER_O = INVERTER_0_START_INV_FW;  // presente solo lo start inverter, non usato lo start inverter reverse
		RESET_INVERTER_O = INVERTER_0_RESET_INVERTER;
		MASC_RIGID_O = INVERTER_0_MASCH_RIGIDA;
		ACC_INV_AB_O = INVERTER_0_INCLUS_RAMPE;

		// USCITE PLC: da PLC-->INVERTER (necessario passare la word perché al plc iec serve almeno il reset)
		AF_INVERTER_0_INPUT = (float) DW_INVERTER_0_INPUT;

		// Velocità massima di rotazione mandrino da tarature
		if(RP_PON && !READ_SETTING_ASSE_Q_ESEG)
		{
			read_var (VL_FLOT, 4054, -1, AX_Q_CH0, &APP_VEL_MAX_ASSE_Q);              /* V4054/6 = velocita' massima (gradi/ciclo assi) asse Q in taratura */
			// ((APP_VEL_MAX_ASSE_Q / CICLO_ASSI) * 60) --> sono gradi al minuto
			VEL_MAX_ASSE_Q = ((APP_VEL_MAX_ASSE_Q / CICLO_ASSI) * 60) / 360;          // VEL_MAX_ASSE_Q = velocità massima asse Q espressa in rpm
			READ_SETTING_ASSE_Q_ESEG = 1;
		}

		// Appoggio speed mandrino da passare al plc iec
		read_var (VL_FLOT, 6058, -1, AX_Q_CH0, &APP_SPEED_ASSE_Q);                 /* V4058/6 = velocita' attuale (giri/ciclo assi) asse mandrino */
		VEL_ACT_ASSE_Q = (APP_SPEED_ASSE_Q / CICLO_ASSI) * 60;                     // VEL_ACT_ASSE_Q = speed attuale mandrino espressa in rpm

		// AGGIUNGO FILTRO SU VELOCITA' DI ROTAZIONE: in modo random il valore esposto diventa di milioni di rpm probabilmente dovuto a 
		//                                            disturbi su encoder mandrino in fase di decelerazione, in particolare con la lama
		// Aggiorno il valore da esporre della velocità attuale solo se entro la massima velocità di taratura + 2000 rpm di tolleranza
		if(ABS(VEL_ACT_ASSE_Q) <= (VEL_MAX_ASSE_Q+2000.0))
			AF_INVERTER_0_SPEED = VEL_ACT_ASSE_Q;   // AF_INVERTER_0_SPEED = variabile in cui appoggio la speed mandrino per il plc iec
	}
	else if(GESTIONE_INVERTER_V1000)
	{
		// FREQUENZA TARGET: da PLC-->INVERTER
		AF_INVERTER_0_TARGET_FREQ = (float) FL_INVERTER_0_FREQ_TARGET;
		
		// USCITE PLC:
		START_INVERTER_O = INVERTER_0_START_INV_FW;

		// USCITE PLC: da PLC-->INVERTER
		AF_INVERTER_0_INPUT = (float) DW_INVERTER_0_INPUT;
	}
	else
	{
		// USCITE PLC: da PLC-->INVERTER
		START_INVERTER_O = INVERTER_0_START_INV_FW;  // presente solo lo start inverter, non usato lo start inverter reverse
		RESET_INVERTER_O = INVERTER_0_RESET_INVERTER;
		MASC_RIGID_O = INVERTER_0_MASCH_RIGIDA;
		ACC_INV_AB_O = INVERTER_0_INCLUS_RAMPE;
	}
}
