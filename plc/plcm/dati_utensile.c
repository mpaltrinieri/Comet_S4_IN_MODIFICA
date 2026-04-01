/*
        --------------------------------------------------------------
        TITOLO:         Dati_utensile
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Su chiamata funzione T restituisce i dati 
		relativi all'utensile indicato secondo i parametri DRILL
		--------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    dati_utensile (void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           07-05-2018
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------
*/


#include "all.inc"

typedef enum {
	LEF_TAB_UTENSILI_ACK = 1,
	LEF_HEADS_TXT_ERROR = 10,
	LEF_PARAM_PAR_ERROR = 20,
	LEF_CONFIG_PAR_ERROR = 30,
	LEF_TOOLS_TXT_ERROR = 40,
	LEF_ISOPATH_TXT_ERROR = 400
} DatiUtensileLoadErrorFlags;

#define TAB_UTENSILI_REQ_CARICA   (ToolTabS1)
#define TAB_UTENSILI_ACK_CARICA   (ToolTabS2)


void dati_utensile(void)
{

	/**** RESET ALLARMI ****/

	if (RESET_MC || RESET_ALL) {
		PATHCONF_TXT_FAL = 0;
		CONFIG_PAR_FAL = 0;        
		TOOLS_TXT_FAL = 0;        
		HEADS_TXT_FAL = 0; 
		PARAM_PAR_FAL = 0;
	}	

	if (RESET_MC || M02) 
	{
		TAB_UTENSILI_REQ_CARICA = 0;
		TAB_UTENSILI_CARICATA = 0;
		CHIAMATA_UT_FAL	= 0;
		TAB_UT_NON_CAR_FAL = 0;
		Mr_MC(209);
		memset(&T_FIRST_WORD, 0, (&T_LAST_WORD - &T_FIRST_WORD + 1)*sizeof(T_FIRST_WORD));
	}

	if (CONF_FUNZ_ISO_ABIL) R[R_CK_START] = BTF(HARDLOCK_OPT_ISO);
	CONSENSO_CICLO_ISO = FTB(R[R_CK_START]) && CONF_FUNZ_ISO_ABIL && HARDLOCK_OPT_ISO;

	/*** RICHIESTA LETTURA TABELLE A TTreader.exe ***/
	// Inizializzazione delle aree tabella utensili, e lancio lo start di sincronizzazione
	if (Mg_MC(209) && (TAB_UTENSILI_REQ_CARICA == 0) && (TAB_UTENSILI_ACK_CARICA == 0) ) {
		int i, j = 0;

		memset(&SynoToolStruct, 0, sizeof(SynoToolStruct));

		for (i = 0; i <= ARRAY_SIZE(SynoToolStruct.magazzino); i++)
			for(j = 0; j < ARRAY_SIZE(SynoToolStruct.magazzino[i].utensile); j++)
				SynoToolStruct.magazzino[i].utensile[j].presente = -1;

		TAB_UTENSILI_REQ_CARICA = 1;	// Consenso caricamento tabella utensili
	}

	// Annullo richiesta caricamento tabella utensili
	// la funzione M alzata provoca un allarme DRIVE_MISSING_FAL
	if (!CONSENSO_CICLO_ISO) {
		TAB_UTENSILI_REQ_CARICA = 0;
		TAB_UTENSILI_CARICATA = 0;
	}

	// Il programma esterno ha terminato di caricare la tabella utensili
	if (Mg_MC(209) && (TAB_UTENSILI_REQ_CARICA == 1) && (TAB_UTENSILI_ACK_CARICA == 1) )	{
		TAB_UTENSILI_REQ_CARICA = 0;
		TAB_UTENSILI_CARICATA = 1;
		Mr_MC(209);	
	}

	if (!CONF_FUNZ_ISO_ABIL) return;


	/*** Controllo funzione T emessa ***/

	if (DP_NVT_CH0 && O_EXE_CH0 && !Mg_MC(72) && !Mg_MC(74) && !Mg_MC(209))		
	{
		const int wordSize = sizeof(T_FIRST_WORD);
		const int bitInWord = 8*wordSize;
		const int tMaxValue = (T_LAST_WORD - T_FIRST_WORD + 1) * bitInWord; 
		const TOOL_STRUCT *utensileCorrente = NULL;

		// Set funzione T corrispondente
		if (!IN_RANGE(O_T_CH0, 0, tMaxValue))
			CHIAMATA_UT_FAL = 1;

		if (!CHIAMATA_UT_FAL)
			(&T_FIRST_WORD)[O_T_CH0 / bitInWord] |= 0x1u << (O_T_CH0 % bitInWord);

		Aris_CH2[R_NEXT_TOOL] = Aris_CH1[R_NEXT_TOOL] = R[R_NEXT_TOOL] = O_T_CH0;
		//R[R_NEXT_TESTINA] = 0.0; // Testine non gestite in questa versione

		if (!TAB_UTENSILI_CARICATA)
			TAB_UT_NON_CAR_FAL = 1;

		// Verifica numero utensile nel range massimo della struttura dati
		if (!IN_RANGE(R[R_NEXT_TOOL], 0, ARRAY_SIZE(SynoToolStruct.magazzino)))
			CHIAMATA_UT_FAL = 1;

		// Verifica numero utensile nel range degli utensili disponibili
		if (!IN_RANGE(R[R_NEXT_TOOL], 0, SynoToolStruct.numeroUtensili))
			CHIAMATA_UT_FAL = 1;

		if (!CHIAMATA_UT_FAL && (O_T_CH0 > 0))
			utensileCorrente = &SynoToolStruct.magazzino[(int)R[R_NEXT_TOOL]-1].utensile[0];

		if (!utensileCorrente || utensileCorrente->presente != 1)
			CHIAMATA_UT_FAL = 1;


		if (!CHIAMATA_UT_FAL && !TAB_UT_NON_CAR_FAL)
		{ 
			// Frequenza lubrica
			if (CONF_REF_LUBRICA || CONF_REF_SPECIALE) {
				double fpart = modf(utensileCorrente->frequenzaRefrigerante, &R[R_FREQ_LUBRICA]);
				R[R_USA_REFSPEC] = BTF(fpart > 0);
			}
			// Senso rotazione mandrino
			R[R241] = utensileCorrente->versoRotazione;
			// Velocità di lavorazione
			R[R311] = (utensileCorrente->velocitaRotazioneMandrino / 100.0) * utensileCorrente->velocitaAsportazione;
			// Velocità di sfondamento
			R[R310] = utensileCorrente->velocitaSfondamento;
			// Diametro 1
			R[R_RADIUS_NEXTOOL] = utensileCorrente->diametro[0] / 2.0;
			// Lunghezza 1
			R[R_SPESS_DISCO] = utensileCorrente->lunghezza[0];
			// Lunghezza totale
			R[R_LENGTH_NEXTOOL] = utensileCorrente->lunghezzaTotale;
			// Tipo di lubrica
			R[R_TIPO_LUBRICA] = (int)utensileCorrente->numeroRefrigerante & 0x1F; //and con i primi 5 bit

			// Numero di giri mandrino
			//if (R[R_UT1A_RAPPORTO_RIDUZIONE+offset] > 0.0)
			// R[R242] = utensileCorrente->velocitaRotazioneMandrino / R[R_UT1A_RAPPORTO_RIDUZIONE+offset];
			//else
			R[R242] = utensileCorrente->velocitaRotazioneMandrino;

			// Dimensione d'ingombro
			//if (R[R_UT1A_DIM_UTENSILE+offset] > 0.0)
			//R[R_DIM_TOOL] = R[R_UT1A_DIM_UTENSILE+offset];
			//else		
			R[R_DIM_TOOL] =	R[R_LENGTH_NEXTOOL];

			// Offset mandrino
			R[R_OFFSET_X_MAND] = SynoToolStruct.offsetX;
			R[R_OFFSET_Y_MAND] = SynoToolStruct.offsetY;
			R[R_OFFSET_Z_MAND] = SynoToolStruct.offsetZ;
			R[R_OFFSET_MANDR_A_C] = SynoToolStruct.offsetAC;

			// Azzeramento chiamate utensili solo quando tabella caricata altrimenti allarme
			APP_AZZERA_CALL_TOOL = 1;
			//memset(&T_FIRST_WORD, 0, (&T_LAST_WORD - &T_FIRST_WORD + 1)*sizeof(T_FIRST_WORD)); 
			// Sulla macchina multicanale sembra necessario che la FATT duri più di un ciclo plc, pertanto il reset della T viene fatto con ritardo
		}
	}

	if(RESET_MC)
	{
		APP_AZZERA_CALL_TOOL = 0;
	}

	tS(TS_RIT_AZZERA_CALL_TOOL,(unsigned char) APP_AZZERA_CALL_TOOL);
	if(RP_TSuppl[TS_RIT_AZZERA_CALL_TOOL])
	{
		// Azzeramento chiamate utensili solo quando tabella caricata altrimenti allarme
		APP_AZZERA_CALL_TOOL = 0;
		memset(&T_FIRST_WORD, 0, (&T_LAST_WORD - &T_FIRST_WORD + 1)*sizeof(T_FIRST_WORD));
	}


	// Gestione allarmi per SIOMAG
	tS(TS_TOOLTAB_READ, (unsigned char)(Mg_MC(209) || (TAB_UTENSILI_REQ_CARICA != 0)) ); // Temporizza lettura delle tabelle utensili

	// Timeout risposta TTreader
	if (RP_TSuppl[TS_TOOLTAB_READ]) {
		switch (TAB_UTENSILI_ACK_CARICA) {

			case LEF_HEADS_TXT_ERROR:
				HEADS_TXT_FAL = 1;
				break;
			case LEF_PARAM_PAR_ERROR:
				PARAM_PAR_FAL = 1;
				break;
			case LEF_CONFIG_PAR_ERROR:
				CONFIG_PAR_FAL = 1;
				break;
			case LEF_TOOLS_TXT_ERROR:
				TOOLS_TXT_FAL = 1;
				break;
			case LEF_ISOPATH_TXT_ERROR:
				PATHCONF_TXT_FAL = 1;
				break;
			case LEF_TAB_UTENSILI_ACK:
				//Allarme chiamata utensile su errore sconosciuto
			default:
				TAB_UT_NON_CAR_FAL = 1;
				break;
		}
	}

	// Allarme chiamata utensile su errore sconosciuto
	//if(TAB_UT_NON_CAR_FAL)
	//	allarm(TAB_UT_NON_CAR_AL);

	// Allarme errore in chiamata file PATH_CONF.TXT
	//if (PATHCONF_TXT_FAL)
	//	allarm (PATHCONF_TXT_AL);

	// Allarme errore in lettura HEADS.TXT
	//if (HEADS_TXT_FAL)
	//	allarm (HEADS_TXT_AL);

	// Allarme errore in lettura PARAM.PAR
	//if (PARAM_PAR_FAL)
	//	allarm (PARAM_PAR_AL);

	// Allarme errore in lettura file CONFIG.PAR
	//if (CONFIG_PAR_FAL)
	//	allarm (CONFIG_PAR_AL);

	// Allarme errore lettura TOOLS.TXT
	//if (TOOLS_TXT_FAL)
	//	allarm (TOOLS_TXT_AL);

	// Allarme errore in chiamata utensile				
	//if (CHIAMATA_UT_FAL)
	//  allarm (CHIAMATA_UT_AL);	
}
	
