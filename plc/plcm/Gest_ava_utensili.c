/*
        --------------------------------------------------------------
        TITOLO:         Gest_ava_utensili.c
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione avanzata utensili, flag utensile rotto
		                e gestione alias
		--------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    gest_ava_utensili (void)
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
        DATA:           15-03-2017
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Daniele Formuso
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------
*/


#include "all.inc"

#define IDLE_NEXT_TOOL        0   // Stato inattivo
#define INIT_NEXT_TOOL       10   // Stato start macchina a stati
#define CHECK_NEXT_TOOL      20   // Satato verifica utensile successivo
#define FAMILY_NEXT_TOOL     30   // Stato di caricamento parametri di tutti gli alias utensile non utilizzabile
#define ALIAS_NEXT_TOOL      40   // Stato di scelta dell'utensile alias
#define ALARM_NEXT_TOOL      50   // Stato di allarme per mancanza di utensili alias
#define OK_NEXT_TOOL         60   // Stato finale di utensile ok o sostituito con alias

#define IDLE_VER_TOOL         0   // Stato inattivo
#define INIT_VER_TOOL        10   // Stato start macchina a stati
#define APP_LISTA_VER_TOOL   20   // Stato appoggio lista utensili isomg
#define CHECK_VER_TOOL       30   // Stato di verifica stato utensili e alias della lista dell'isomg
#define ALARM_VER_TOOL       40   // Stato di allarme per mancanza di utensili alias di utensili rotti
#define TOOL_OK_VER_TOOL     50   // Stato finale di termine verifica ok (no utensili rotti o alias presenti)

#define IDLE_CHECK_TOOL        0  // Stato inattivo
#define TOOL_ROTTO_CHECK_TOOL 10  // Stato start macchina a stati
#define WAIT_DRILL_CHECK_TOOL 20  // Satato verifica utensile successivo
#define END_CHECK_TOOL        30  // Stato di caricamento parametri di tutti gli alias utensile non utilizzabile


//*** STRUTTURA DI APPOGGIO DELLE INFORMAZIONI UTENSILI SCRITTE DA DRILL
GEST_AVA_TOOL_DRILL_CNC_STRUCT App_GestAvaToolDrillToCnc[60];
PGEST_AVA_TOOL_DRILL_CNC_STRUCT PApp_GestAvaToolDrillToCnc;
PGEST_AVA_TOOL_DRILL_CNC_STRUCT P_GestAvaToolDrillToCnc;

//*** STRUTTURA CHE USO PER CONTENERE GLI ALIAS DI UN UTENSILE NON UTILIZZABILE
GEST_AVA_TOOL_DRILL_CNC_STRUCT alias_next_tool[60];

long OLD_DRILL_ALIVE_VALUE;  //appoggio old value dell'alive di Drill

long APP1_TOOL_IN_USE;        //appoggio lista utensili nell'isomg
long APP1_TOOL_IN_USE_ROTTO;  //appoggio lista utensili rotti senza alias


void gest_ava_utensili(void)
{
if(R[R_ABIL_GEST_AVA_TOOL]>0.5)
{
	int i, j;
	
	if(PON)
	{
		memset(&GestAvaToolDrillToCnc, 0, sizeof(GestAvaToolDrillToCnc));
		memset(&GestAvaToolCncToDrill, 0, sizeof(GestAvaToolCncToDrill));
		memset(&App_GestAvaToolDrillToCnc, 0, sizeof(App_GestAvaToolDrillToCnc));
		memset(&alias_next_tool, 0, sizeof(alias_next_tool));
		AliveCncToDrill = 0;  //Inizializzazione variabile di alive

		CASE_NEXT_TOOL = IDLE_NEXT_TOOL;
		CASE_VER_TOOL = IDLE_VER_TOOL;
		CASE_CHECK_TOOL = IDLE_CHECK_TOOL;

		if      (CONF_MAGUT_10POSTI)  NUM_UTENSILI_MAGAZZINO = 10;  // magazzino utensili + lama
		else if (CONF_MAGUT_12POSTI)  NUM_UTENSILI_MAGAZZINO = 12;  // magazzino utensili + lama
	}
	
	// Appoggio utensile attuale, successivo e futuro
	ACTUAL_TOOL = (int) R[R_ACT_TOOL];
	NEXT_TOOL = (int) R[R_NEXT_TOOL];
	FUTUR_TOOL = 0;		// nelle Comet RS non è gestito l'utensile futuro, a differenza delle sat xt,xte,xle: (int) R[R_FUT_TOOL];
	
	//Reset flag di appoggio e stato macchina a stati
	if(RESET_MC)
	{
		CASE_NEXT_TOOL = IDLE_NEXT_TOOL;
		CASE_VER_TOOL = IDLE_VER_TOOL;
		CASE_CHECK_TOOL = IDLE_CHECK_TOOL;
	}

	//Reset allarmi
	if(RESET_ALL || RESET_MC)
	{
		NOT_ALIVE_DRILL_FAL = 0;
	}

	P_GestAvaToolDrillToCnc = &GestAvaToolDrillToCnc[0];  //inizializzo il puntatore con indirizzo della struttura del Drill
	PApp_GestAvaToolDrillToCnc = &App_GestAvaToolDrillToCnc[0]; //inizializzo il puntatore con indirizzo della struttura di appoggio

	// Alive da Drill per gestione utensili avanzata
	tS(TS_ALIVE_DRILL, (unsigned char) SET_TIMEOUT_ALIVE_DRILL);

	if((AliveDrillToCnc == OLD_DRILL_ALIVE_VALUE) && CICLO_ON)
		SET_TIMEOUT_ALIVE_DRILL = 1;
	else
		SET_TIMEOUT_ALIVE_DRILL = 0;

	// GESTISCI ALLARME DI ALIVE
	if(RP_TSuppl[TS_ALIVE_DRILL])
		NOT_ALIVE_DRILL_FAL = 1;

	// Lancio M di lettura parametri utensili avanzati: da lanciare a inizio cambio utensili (tenere conto anche del caso delle funzioni T in ISO)
	// Costruisco la derivata positiva della M di lettura parametri utensili
	DP_M251 = 0;
	if(Mg_MC(251) && !APP_M251)
		DP_M251 = 1;
	APP_M251 = Mg_MC(251);

	if (DP_M251) 
	{
		CASE_NEXT_TOOL = INIT_NEXT_TOOL;  //start macchina a stati di verifica utensile successivo
	}
	
	switch (CASE_NEXT_TOOL)
	{
		case IDLE_NEXT_TOOL: //Stato di inattività
			NumToolNonUtilizzabile = 0;
			R[R_GEST_AVA_TOOL_ROTTO] = 0;  //reset iniziale
		break;

		case INIT_NEXT_TOOL: //copia in locale struttura scritta da Drill
			for(i=0; i<NUM_UTENSILI_MAGAZZINO; i++)
				PApp_GestAvaToolDrillToCnc[i] = P_GestAvaToolDrillToCnc[i]; //Copio la struttura scritta da Drill sulla struttura locale
			CASE_NEXT_TOOL = CHECK_NEXT_TOOL;
		break;
		
		case CHECK_NEXT_TOOL: //verifica stato utensile successivo
		//Del next tool devo leggere se è utilizzabile:
		// SI -> vai avanti e resetti la M251
		if(!App_GestAvaToolDrillToCnc[NEXT_TOOL-1].NonUtilizzabile) 
			CASE_NEXT_TOOL = OK_NEXT_TOOL;
		
		// NO -> leggi la famiglia di appartenenza, cerchi tutti gli utensili in magazzino della stessa famiglia, ne selezioni uno (ad esempio scelgo il primo 
		//       della famiglia utilizzabile che trovo , dando priorità all'utensile futuro se appartiene alla stessa famiglia), 
		//       carichi i parametri del nuovo utensile scelto
		if(App_GestAvaToolDrillToCnc[NEXT_TOOL-1].NonUtilizzabile)
		{
			if(!App_GestAvaToolDrillToCnc[NEXT_TOOL-1].Famiglia) //se la famiglia è zero, allora vuol dire che non ci sono alias
			{
				//Gestisci allarme: utensile R611 oppure T*** morto e non ci sono alias disponibili
				R[R_GEST_AVA_TOOL_ROTTO] = R[R_NEXT_TOOL];
				NumToolNonUtilizzabile = (int) R[R_NEXT_TOOL];
				CASE_NEXT_TOOL = ALARM_NEXT_TOOL;
			}
			else
			{
				memset(&alias_next_tool, 0, sizeof(alias_next_tool));  //resetto l'array di strutture prima di usarlo
				CASE_NEXT_TOOL = FAMILY_NEXT_TOOL;  //ricerca tutti gli utensili della stessa famiglia utilizzabili (non rotti)
			}
		}
		break;
		
		case FAMILY_NEXT_TOOL: // carica nella struttura alias_next_tool gli utensili non rotti appartenenti alla stessa famiglia del next tool
		    j=0;
			//// Diamo priorità come alias all'utensile futuro
			////if( (FUTUR_TOOL >= 1) && 
			////    (App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].Famiglia == App_GestAvaToolDrillToCnc[NEXT_TOOL-1].Famiglia) &&
			////	!App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].NonUtilizzabile )
			////{
			////	alias_next_tool[0].PosInStock = App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].PosInStock;
			////	alias_next_tool[0].Famiglia = App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].Famiglia;
			////	alias_next_tool[0].Lunghezza = App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].Lunghezza;	
			////	alias_next_tool[0].Raggio = App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].Raggio;
			////	alias_next_tool[0].DimTool = App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].DimTool;
			////	alias_next_tool[0].NumLubrica = App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].NumLubrica;
			////	alias_next_tool[0].NonUtilizzabile = App_GestAvaToolDrillToCnc[FUTUR_TOOL-1].NonUtilizzabile;
			////}
			////else
			{
				for (i=0; i<NUM_UTENSILI_MAGAZZINO; i++)
				{
					if(i==(NEXT_TOOL-1)) continue;
					if( (App_GestAvaToolDrillToCnc[i].Famiglia == App_GestAvaToolDrillToCnc[NEXT_TOOL-1].Famiglia) &&
						!App_GestAvaToolDrillToCnc[i].NonUtilizzabile )
						{
							alias_next_tool[j].PosInStock = App_GestAvaToolDrillToCnc[i].PosInStock;
							alias_next_tool[j].Famiglia = App_GestAvaToolDrillToCnc[i].Famiglia;
							alias_next_tool[j].Lunghezza = App_GestAvaToolDrillToCnc[i].Lunghezza;	
							alias_next_tool[j].Raggio = App_GestAvaToolDrillToCnc[i].Raggio;
							alias_next_tool[j].DimTool = App_GestAvaToolDrillToCnc[i].DimTool;
							alias_next_tool[j].NumLubrica = App_GestAvaToolDrillToCnc[i].NumLubrica;
							alias_next_tool[j].NonUtilizzabile = App_GestAvaToolDrillToCnc[i].NonUtilizzabile;
							j++;
						}
				}
			}
						
			CASE_NEXT_TOOL = ALIAS_NEXT_TOOL;
			
		break;
		
		case ALIAS_NEXT_TOOL:  //nell'array degli alias del next tool scelgo il primo (posizione 0 nell'array) se esiste, altrimenti devi dare allarme
			if(alias_next_tool[0].PosInStock>=1) //se esiste un utensile della famiglia utilizzabile
			{
				R[R_NEXT_TOOL] = (double) alias_next_tool[0].PosInStock;
				R[R_LENGTH_NEXTOOL] = (double) alias_next_tool[0].Lunghezza;
				//R[R_RADIUS_NEXTOOL] = (double) alias_next_tool[0].Raggio;  //come raggio teniamo quello dell'utensile originale richiesto 
				R[R_DIM_TOOL] = (double) alias_next_tool[0].DimTool;
				R[R_TIPO_LUBRICA] = (double) alias_next_tool[0].NumLubrica;
				CASE_NEXT_TOOL = OK_NEXT_TOOL;
			}
			else
			{
				//Gestisci allarme: utensile R611 oppure T*** morto e non ci sono alias disponibili
				R[R_GEST_AVA_TOOL_ROTTO] = R[R_NEXT_TOOL];
				NumToolNonUtilizzabile = (int) R[R_NEXT_TOOL];
				CASE_NEXT_TOOL = ALARM_NEXT_TOOL;
			}

		break;
		
		case ALARM_NEXT_TOOL: //Next tool KO e non ha alias utilizzabili
			//Gestisci allarme: utensile R611 oppure T*** morto e non ci sono alias disponibili
			NumToolNonUtilizzabile = (int) R[R_NEXT_TOOL];
			Mr_MC(251);
			if(RESET_MC)
			{
				R[R_GEST_AVA_TOOL_ROTTO] = 0;
				Mr_MC(250);
				CASE_NEXT_TOOL = OK_NEXT_TOOL;
			}
		break;
		
		case OK_NEXT_TOOL: //Next tool OK o next tool sostituito con alias
			Mr_MC(251);
			NumToolNonUtilizzabile = 0;
			CASE_NEXT_TOOL = IDLE_NEXT_TOOL;
		break;
				
		default:
		break;
	}
		//***** Parametri scritti dal DRILL->CNC per il prossimo utensile
		// GestAvaToolDrillToCnc[NEXT_TOOL-1].PosInStock;
		// GestAvaToolDrillToCnc[NEXT_TOOL-1].Famiglia;
		// GestAvaToolDrillToCnc[NEXT_TOOL-1].Lunghezza;	
		// GestAvaToolDrillToCnc[NEXT_TOOL-1].Raggio;
		// GestAvaToolDrillToCnc[NEXT_TOOL-1].DimTool;
		// GestAvaToolDrillToCnc[NEXT_TOOL-1].NumLubrica;
		// GestAvaToolDrillToCnc[NEXT_TOOL-1].NonUtilizzabile;
		
		
		//***** Parametri scritti dal DRILL->CNC per utensile futuro
		//if(FUTUR_TOOL >= 1)
		//{
		//	GestAvaToolDrillToCnc[FUTUR_TOOL-1].PosInStock;
		//	GestAvaToolDrillToCnc[FUTUR_TOOL-1].Famiglia;
		//	GestAvaToolDrillToCnc[FUTUR_TOOL-1].Lunghezza;	
		//	GestAvaToolDrillToCnc[FUTUR_TOOL-1].Raggio;
		//	GestAvaToolDrillToCnc[FUTUR_TOOL-1].DimTool;
		//	GestAvaToolDrillToCnc[FUTUR_TOOL-1].NumLubrica;
		//	GestAvaToolDrillToCnc[FUTUR_TOOL-1].NonUtilizzabile;
		//}	

    // Reset allarme utensile rotto e senza alias
	if(RESET_MC)
	{
		TOOL_01_MORTO_FAL = 0;   //utensile 01 morto e senza alias
		TOOL_02_MORTO_FAL = 0;   //utensile 02 morto e senza alias
		TOOL_03_MORTO_FAL = 0;   //utensile 03 morto e senza alias
		TOOL_04_MORTO_FAL = 0;   //utensile 04 morto e senza alias
		TOOL_05_MORTO_FAL = 0;   //utensile 05 morto e senza alias
		TOOL_06_MORTO_FAL = 0;   //utensile 06 morto e senza alias
		TOOL_07_MORTO_FAL = 0;   //utensile 07 morto e senza alias
		TOOL_08_MORTO_FAL = 0;   //utensile 08 morto e senza alias
		TOOL_09_MORTO_FAL = 0;   //utensile 09 morto e senza alias
		TOOL_10_MORTO_FAL = 0;   //utensile 10 morto e senza alias
		TOOL_11_MORTO_FAL = 0;   //utensile 11 morto e senza alias
		TOOL_12_MORTO_FAL = 0;   //utensile 12 morto e senza alias
	}

	// Allarme utensile morto e senza alias disponibili
	if((R[R_GEST_AVA_TOOL_ROTTO] > 0.5) && Mg_MC(250))
	{
		switch ((int) R[R_GEST_AVA_TOOL_ROTTO])
		{
			case 1:
				TOOL_01_MORTO_FAL = 1;
			break;
			
			case 2:
				TOOL_02_MORTO_FAL = 1;
			break;
			
			case 3:
				TOOL_03_MORTO_FAL = 1;
			break;
			
			case 4:
				TOOL_04_MORTO_FAL = 1;
			break;
			
			case 5:
				TOOL_05_MORTO_FAL = 1;
			break;
			
			case 6:
				TOOL_06_MORTO_FAL = 1;
			break;
			
			case 7:
				TOOL_07_MORTO_FAL = 1;
			break;
			
			case 8:
				TOOL_08_MORTO_FAL = 1;
			break;
			
			case 9:
				TOOL_09_MORTO_FAL = 1;
			break;
			
			case 10:
				TOOL_10_MORTO_FAL = 1;
			break;

			case 11:
				TOOL_11_MORTO_FAL = 1;
			break;
			
			case 12:
				TOOL_12_MORTO_FAL = 1;
			break;
			
			default:
			break;			
		}
	}

	//******** CHECK LISTA UTENSILI IN USO NELL'ISOMG *******************
	// Lancio M di verifica utensili a inizio ripetizioni dell'ISOMG
	// Costruisco la derivata positiva della M di verifica lista utensili (inserisci M252 in FATM)
	DP_M252 = 0;
	if(Mg_MC(252) && !APP_M252)
		DP_M252 = 1;
	APP_M252 = Mg_MC(252);

	if (DP_M252) 
	{
		CASE_VER_TOOL = INIT_VER_TOOL;  //start macchina a stati di verifica lista utensili usati nell'isomg
	}
	
	switch (CASE_VER_TOOL)
	{
		case IDLE_VER_TOOL: //Stato di inattività
			APP_INDEX_USE_TOOL_1_16 = 0;   // Reset iniziale word utensili da usare da T1 a T16

			APP_INDEX_TOOL_ROTTO_1_16 = 0;   // Reset iniziale word utensili da usare rotti da T1 a T16

			APP1_TOOL_IN_USE = 0;
			APP1_TOOL_IN_USE_ROTTO = 0;
			
		break;
		
		case INIT_VER_TOOL: //start macchina a stati
			for(i=0; i<NUM_UTENSILI_MAGAZZINO; i++)
				PApp_GestAvaToolDrillToCnc[i] = P_GestAvaToolDrillToCnc[i]; //Copio la struttura scritta da Drill sulla struttura locale

			APP_INDEX_USE_TOOL_1_16 = (short int) R[R_VER_TOOL_1_16];    //lettura utensili da usare da T1 a T16
			
			CASE_VER_TOOL = APP_LISTA_VER_TOOL;
		break;
		
		case APP_LISTA_VER_TOOL:
			APP1_TOOL_IN_USE =  (long) ( APP_INDEX_USE_TOOL_1_16 & 0xFFFF ); //utensili da T1 a T32
			
			CASE_VER_TOOL = CHECK_VER_TOOL;								 
		break;
		
		case CHECK_VER_TOOL: //verifica se utensili usati nell'isomg sono rotti e senza alias
			
			i=0;
			while(APP1_TOOL_IN_USE) //per gli utensili da T1 a T32
			{
				if(APP1_TOOL_IN_USE & 1ul) //se utensile da usare nell'isomg
				{
					if(App_GestAvaToolDrillToCnc[i].NonUtilizzabile)
					{
						if(!App_GestAvaToolDrillToCnc[i].Famiglia)   //famiglia=0 vuol dire che non ha alias
						{
							APP1_TOOL_IN_USE_ROTTO = (APP1_TOOL_IN_USE_ROTTO | (1ul<<i)); //utensile rotto e non ha alias
						}
						else if(App_GestAvaToolDrillToCnc[i].Famiglia)
						{
							APP1_TOOL_IN_USE_ROTTO = (APP1_TOOL_IN_USE_ROTTO | (1ul<<i));  //inizializzo l'utensile come rotto
							for (j=0; j<NUM_UTENSILI_MAGAZZINO; j++)
							{
								if(j==i) continue;
								if((App_GestAvaToolDrillToCnc[j].Famiglia == App_GestAvaToolDrillToCnc[i].Famiglia) &&
								   !App_GestAvaToolDrillToCnc[j].NonUtilizzabile)
								{
									APP1_TOOL_IN_USE_ROTTO = (APP1_TOOL_IN_USE_ROTTO & (~(1ul<<i)));  //se trovo un alias utilizzabile resetto l'inizializzazione di utensile rotto
									break;  //se trovo un alias utilizzabile esce dal loop
								}
							}
						}
					}
					
					i++;
					APP1_TOOL_IN_USE = (APP1_TOOL_IN_USE>>1ul);						
				}
				else
				{
					i++;
					APP1_TOOL_IN_USE = (APP1_TOOL_IN_USE>>1ul);
				}
			}
			
			APP_INDEX_TOOL_ROTTO_1_16 = (short int) (APP1_TOOL_IN_USE_ROTTO & 0xFFFF);          // word utensili da usare rotti da T1 a T16			

			if(APP_INDEX_TOOL_ROTTO_1_16)
				CASE_VER_TOOL = ALARM_VER_TOOL;
			else
				CASE_VER_TOOL = TOOL_OK_VER_TOOL;
			
		break;
        
		case ALARM_VER_TOOL:
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<0))  TOOL_01_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<1))  TOOL_02_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<2))  TOOL_03_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<3))  TOOL_04_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<4))  TOOL_05_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<5))  TOOL_06_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<6))  TOOL_07_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<7))  TOOL_08_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<8))  TOOL_09_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<9))  TOOL_10_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<10)) TOOL_11_MORTO_FAL = 1;
			if(APP_INDEX_TOOL_ROTTO_1_16 & (1<<11)) TOOL_12_MORTO_FAL = 1;
		break;
		
		case TOOL_OK_VER_TOOL:
			Mr_MC(252);
			CASE_VER_TOOL = IDLE_VER_TOOL;
		break;
					
		default:
		break;
	}
	//******** FINE CHECK LISTA UTENSILI IN USO NELL'ISOMG **************


	//***** Parametro scritto dal CNC->DRILL per utensile attuale	
	// Lancio scrittura parametri utensili avanzati: ToolInLavoro da mantenere a 1 durante la lavorazione con l'utensile
	// Per scrivere questo parametro utilizzo INVERTER_0_START_INV_FW
	if(INVERTER_0_START_INV_FW && O_LAV_CH0 && (ACTUAL_TOOL>=1))
	{
		GestAvaToolCncToDrill[ACTUAL_TOOL-1].ToolInLavoro = 1;
	}
	else if((!INVERTER_0_START_INV_FW || !O_LAV_CH0) && (ACTUAL_TOOL>=1)) 
	{
		GestAvaToolCncToDrill[ACTUAL_TOOL-1].ToolInLavoro = 0;
	}
	
	//********** Scrivo informazione utensile rotto a fine check tool *********
	switch (CASE_CHECK_TOOL)
	{
		case IDLE_CHECK_TOOL: //Stato di inattività
			if(R[R_UT_NOK] > 0.5) //Se utensile sotto check tool è rotto
				CASE_CHECK_TOOL = TOOL_ROTTO_CHECK_TOOL;
		break;

		case TOOL_ROTTO_CHECK_TOOL: //Stato set flag tool rotto
			//***** Parametro scritto dal CNC->DRILL per utensile attuale
			GestAvaToolCncToDrill[ACTUAL_TOOL-1].ToolRotto = 1;

			CASE_CHECK_TOOL = WAIT_DRILL_CHECK_TOOL;
		break;

		case WAIT_DRILL_CHECK_TOOL: //Stato attesa risposta del Drill
			//***** Aspetta che Drill aggiorni l'informazione di utensile non utilizzabile
			if(GestAvaToolDrillToCnc[ACTUAL_TOOL-1].NonUtilizzabile)
			{
				GestAvaToolCncToDrill[ACTUAL_TOOL-1].ToolRotto = 0;
				CASE_CHECK_TOOL = END_CHECK_TOOL;
			}

		break;

		case END_CHECK_TOOL: //Stato di fine macchina a stati
            if(SIMULATORE_SU_CN || SIMULATORE_SU_PC)
			{
				R[R_UT_NOK] = (double) 0; //reset R utensile rotto
				Mr_MC(249);  // reset attesa sincronizzazione con Drill, scrittura info utensile non utilizzabile
			
				CASE_CHECK_TOOL = IDLE_CHECK_TOOL;
			}
			else
			{
				if(Mg_MC(249))
				{
					R[R_UT_NOK] = (double) 0; //reset R utensile rotto
					Mr_MC(249);  // reset attesa sincronizzazione con Drill, scrittura info utensile non utilizzabile

					CASE_CHECK_TOOL = IDLE_CHECK_TOOL;
				}
			}
		break;

		default:
		break;
	}

	//******* Alive da Drill per gestione utensili avanzata: appoggio valore ********
	OLD_DRILL_ALIVE_VALUE = AliveDrillToCnc;

	//********* Alive da CN per Drill ********
	if(AliveCncToDrill<99999)
		AliveCncToDrill += 1;
	else
		AliveCncToDrill = 0;
}
else
	{
		Mr_MC(249);
		Mr_MC(250);
		Mr_MC(251);
		Mr_MC(252);
		NOT_ALIVE_DRILL_FAL = 0;
		TOOL_01_MORTO_FAL = 0;
		TOOL_02_MORTO_FAL = 0;
		TOOL_03_MORTO_FAL = 0;
		TOOL_04_MORTO_FAL = 0;
		TOOL_05_MORTO_FAL = 0;
		TOOL_06_MORTO_FAL = 0;
		TOOL_07_MORTO_FAL = 0;
		TOOL_08_MORTO_FAL = 0;
		TOOL_09_MORTO_FAL = 0;
		TOOL_10_MORTO_FAL = 0;
		TOOL_11_MORTO_FAL = 0;
		TOOL_12_MORTO_FAL = 0;
	}
}