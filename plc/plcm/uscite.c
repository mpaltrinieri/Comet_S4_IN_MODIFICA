/*
        --------------------------------------------------------------
        TITOLO:         Uscite
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Uscite Pneumatiche
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void	uscite(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:		CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:			28-09-2006
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

int AVA_TAVOLA_OR, TAVOLA_OR_AVA, TAVOLA_OR_AVA_COUNT, TAVOLA_OR_AVA_MEMCOUNT, TAVOLA_OR_AVA_MEM;
char AVA_TAVOLA_OR_COMMENTO[80] = "{Tempo avanzamento tavola}";
int IND_TAVOLA_OR, TAVOLA_OR_IND, TAVOLA_OR_IND_COUNT, TAVOLA_OR_IND_MEMCOUNT, TAVOLA_OR_IND_MEM;
char IND_TAVOLA_OR_COMMENTO[80] = "{Tempo arretramento tavola}";

int INS_BARCAR_SX1, BARCAR_SX1_INS, BARCAR_SX1_INS_COUNT, BARCAR_SX1_INS_MEMCOUNT, BARCAR_SX1_INS_MEM;
char INS_BARCAR_SX1_COMMENTO[80] = "{Tempo salita barriera carico SX1}";
int DIS_BARCAR_SX1, BARCAR_SX1_DIS, BARCAR_SX1_DIS_COUNT, BARCAR_SX1_DIS_MEMCOUNT, BARCAR_SX1_DIS_MEM;
char DIS_BARCAR_SX1_COMMENTO[80] = "{Tempo abbassamento barriera carico SX1}";

int INS_BARCAR_DX4, BARCAR_DX4_INS, BARCAR_DX4_INS_COUNT, BARCAR_DX4_INS_MEMCOUNT, BARCAR_DX4_INS_MEM;
char INS_BARCAR_DX4_COMMENTO[80] = "{Tempo salita barriera carico DX4}";
int DIS_BARCAR_DX4, BARCAR_DX4_DIS, BARCAR_DX4_DIS_COUNT, BARCAR_DX4_DIS_MEMCOUNT, BARCAR_DX4_DIS_MEM;
char DIS_BARCAR_DX4_COMMENTO[80] = "{Tempo abbassamento barriera carico DX4}";

int UP_HIGH_PRES_MORSE, HIGH_PRES_MORSE_UP, HIGH_PRES_MORSE_UP_COUNT, HIGH_PRES_MORSE_UP_MEMCOUNT, HIGH_PRES_MORSE_UP_MEM;
char UP_HIGH_PRES_MORSE_COMMENTO[80] = "{Tempo raggiungimento alta pressione morse}";
int DOWN_HIGH_PRES_MORSE, HIGH_PRES_MORSE_DOWN, HIGH_PRES_MORSE_DOWN_COUNT, HIGH_PRES_MORSE_DOWN_MEMCOUNT, HIGH_PRES_MORSE_DOWN_MEM;
char DOWN_HIGH_PRES_MORSE_COMMENTO[80] = "{Tempo caduta alta pressione morse}";

int INS_RILMOR, RILMOR_INS, INS_RILMOR_COUNT, INS_RILMOR_MEMCOUNT, INS_RILMOR_MEM;
char INS_RILMOR_COMMENTO[80] = "{Tempo inserimento micro rilevatore morse}";
int DIS_RILMOR, RILMOR_DIS, DIS_RILMOR_COUNT, DIS_RILMOR_MEMCOUNT, DIS_RILMOR_MEM;
char DIS_RILMOR_COMMENTO[80] = "{Tempo disinserimento micro rilevatore morse}";

int INS_TRASC_X_MORSE, TRASC_X_MORSE_INS, TRASC_X_MORSE_INS_COUNT, TRASC_X_MORSE_INS_MEMCOUNT, TRASC_X_MORSE_INS_MEM;
char INS_TRASC_X_MORSE_COMMENTO[80] = "{Tempo inserimento trascinatore morse asse X}";
int DIS_TRASC_X_MORSE, TRASC_X_MORSE_DIS, TRASC_X_MORSE_DIS_COUNT, TRASC_X_MORSE_DIS_MEMCOUNT, TRASC_X_MORSE_DIS_MEM;
char DIS_TRASC_X_MORSE_COMMENTO[80] = "{Tempo disinserimento trascinatore morse asse X}";

int INS_TRASC_P_MORSE, TRASC_P_MORSE_INS, TRASC_P_MORSE_INS_COUNT, TRASC_P_MORSE_INS_MEMCOUNT, TRASC_P_MORSE_INS_MEM;
char INS_TRASC_P_MORSE_COMMENTO[80] = "{Tempo inserimento trascinatore morse asse P}";
int DIS_TRASC_P_MORSE, TRASC_P_MORSE_DIS, TRASC_P_MORSE_DIS_COUNT, TRASC_P_MORSE_DIS_MEMCOUNT, TRASC_P_MORSE_DIS_MEM;
char DIS_TRASC_P_MORSE_COMMENTO[80] = "{Tempo disinserimento trascinatore morse asse P}";

int INS_TRASC_H_MORSE, TRASC_H_MORSE_INS, TRASC_H_MORSE_INS_COUNT, TRASC_H_MORSE_INS_MEMCOUNT, TRASC_H_MORSE_INS_MEM;
char INS_TRASC_H_MORSE_COMMENTO[80] = "{Tempo inserimento trascinatore morse asse H}";
int DIS_TRASC_H_MORSE, TRASC_H_MORSE_DIS, TRASC_H_MORSE_DIS_COUNT, TRASC_H_MORSE_DIS_MEMCOUNT, TRASC_H_MORSE_DIS_MEM;
char DIS_TRASC_H_MORSE_COMMENTO[80] = "{Tempo disinserimento trascinatore morse asse H}";

int AVA_VISIERA_BASSA, VISIERA_BASSA_AVA, VISIERA_BASSA_AVA_COUNT, VISIERA_BASSA_AVA_MEMCOUNT, VISIERA_BASSA_AVA_MEM;
char AVA_VISIERA_BASSA_COMMENTO[80] = "{Tempo spostamento avanti visiera}";
int IND_VISIERA_BASSA, VISIERA_BASSA_IND, VISIERA_BASSA_IND_COUNT, VISIERA_BASSA_IND_MEMCOUNT, VISIERA_BASSA_IND_MEM;
char IND_VISIERA_BASSA_COMMENTO[80] = "{Tempo spostamento indietro visiera}";

int SAL_VIS_RIP, VIS_RIP_SAL, VIS_RIP_SAL_COUNT, VIS_RIP_SAL_MEMCOUNT, VIS_RIP_SAL_MEM;
char SAL_VIS_RIP_COMMENTO[80] = "{Tempo di chiusura visiera alta}";
int DIS_VIS_RIP, VIS_RIP_DIS, VIS_RIP_DIS_COUNT, VIS_RIP_DIS_MEMCOUNT, VIS_RIP_DIS_MEM;
char DIS_VIS_RIP_COMMENTO[80] = "{Tempo di apertura visiera alta}";


void    uscite(void)

{

//*******************************************************************************
//***************** Inizializzazione Temporizzatori *****************************
//*******************************************************************************
if (PON)
        {
		}

/***************** RESET ALLARMI Uscite ***********************/
if (RESET_ALL || RESET_MC)
        {
		}


//******************************************************************************
//**************************** Componente 1 ************************************
//******************************************************************************
//************************* PORTELLONE RIPARO SX *******************************
//************************** Salita / Discesa **********************************
//******************************************************************************

// Componente eliminato

//******************************************************************************
//**************************** Componente 2 ************************************
//******************************************************************************
//************************* PORTELLONE RIPARO DX *******************************
//************************** Salita / Discesa **********************************
//******************************************************************************

// Componente eliminato

//******************************************************************************
//**************************** Componente 3 ************************************
//******************************************************************************
//******************************* TAVOLA    ************************************
//************************** Avanti / Indietro *********************************
//******************************************************************************

COMP_PRES				= CONF_TAVOLA_PRES;
FUNZ_MANUALE			= (FUNZ_MAN64 || FUNZ_MAN66);
MAN_1					= (FUNZ_MAN64 || FUNZ_MAN66) && COMANDO_B;
MAN_2					= (FUNZ_MAN64 || FUNZ_MAN66) && COMANDO_A;
M_1						= Mg_MC(91) || PLCMg_MC(91) || Mg_MC(168);
M_2						= Mg_MC(90) || PLCMg_MC(90);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA && CENTRALINA_OK_I && CENTRALINA_RP;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA && CENTRALINA_OK_I && CENTRALINA_RP;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 1;


OUTPUT_1				= TAVOLA_AVA_O;
OUTPUT_2				= TAVOLA_IND_O;
INPUT_1					= RP_TSuppl[TS_PRESS_TAV_AVA];		// Segnale temporizzato : è un pressostato
INPUT_2					= RP_TSuppl[TS_PRESS_TAV_IND];

COND_ALL_1				= RP_TSuppl[TS_ALL_TAV_AVA];	// Condizione anomala nel movimento 1
COND_ALL_2				= RP_TSuppl[TS_ALL_TAV_IND];	// Condizione anomala nel movimento 2
COND_DISF				= RP_TSuppl[TS_ALL_DISFC_TAV];	// Condizione temporizzata per la disfunzione
TIMEOUT_ALL_1			= RP_TSuppl[TS_TAVOLA_AVA];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= RP_TSuppl[TS_TAVOLA_IND];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= BITON;		

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= TAVOLA_AVA_A_FAL;
OUTPUT_1B_FAL			= TAVOLA_AVA_B_FAL;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= TAVOLA_IND_A_FAL;
OUTPUT_2B_FAL			= TAVOLA_IND_B_FAL;
DISFUNZIONE_FAL			= TAVOLA_DISFC_FAL;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_3;
uscite_standard ();
COMPONENTE_3			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	TAVOLA_AVA_O =		OUTPUT_1;
	TAVOLA_IND_O =		OUTPUT_2;
}
if (!M_1)
{
	Mr_MC(91);
	PLCMr_MC(91);
	Mr_MC(168);
}
if (!M_2)
{
	Mr_MC(90);
	PLCMr_MC(90);
}

//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
TAVOLA_AVA_A_FAL =	OUTPUT_1A_FAL;
TAVOLA_AVA_B_FAL =	OUTPUT_1B_FAL;

//DIS_£_FAL =	OUTPUT_2_FAL;
TAVOLA_IND_A_FAL =	OUTPUT_2A_FAL;
TAVOLA_IND_B_FAL =	OUTPUT_2B_FAL;


TAVOLA_DISFC_FAL =	DISFUNZIONE_FAL;

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{
	AVA_TAVOLA_OR = (int) TAVOLA_AVA_O; TAVOLA_OR_AVA = (int) TAVOLA_AVA_I;
	count (&AVA_TAVOLA_OR, &TAVOLA_OR_AVA, &TAVOLA_OR_AVA_COUNT, &TAVOLA_OR_AVA_MEMCOUNT, &TAVOLA_OR_AVA_MEM, R_AVA_TAVOLA_OR, AVA_TAVOLA_OR_COMMENTO);

	IND_TAVOLA_OR = (int) TAVOLA_IND_O; TAVOLA_OR_IND = (int) TAVOLA_IND_I;
	count (&IND_TAVOLA_OR, &TAVOLA_OR_IND, &TAVOLA_OR_IND_COUNT, &TAVOLA_OR_IND_MEMCOUNT, &TAVOLA_OR_IND_MEM, R_IND_TAVOLA_OR, IND_TAVOLA_OR_COMMENTO);
}

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 3) 
			{	
			goto saltauscite;
			}	



//******************************************************************************
//**************************** Componente 4 ************************************
//******************************************************************************
//******************************* TAVOLA DX ************************************
//************************** Avanti / Indietro *********************************
//******************************************************************************

// *********** ELIMINATO **************	


//******************************************************************************
//**************************** Componente 5 ************************************
//******************************************************************************
//***************************** BATTUTA SX1 *************************************
//************************** Avanti / Indietro *********************************
//******************************************************************************

// *********** ELIMINATO **************

//******************************************************************************
//**************************** Componente 6 ************************************
//******************************************************************************
//***************************** BATTUTA SX2 *************************************
//************************** Avanti / Indietro *********************************
//******************************************************************************

// *********** ELIMINATO **************

//******************************************************************************
//**************************** Componente 7 ************************************
//******************************************************************************
//***************************** BATTUTA DX3 *************************************
//************************** Avanti / Indietro *********************************
//******************************************************************************

// *********** ELIMINATO **************

//******************************************************************************
//**************************** Componente 8 ************************************
//******************************************************************************
//***************************** BATTUTA DX4 *************************************
//************************** Avanti / Indietro *********************************
//******************************************************************************

// *********** ELIMINATO **************

//******************************************************************************
//**************************** Componente 9 ************************************
//******************************************************************************
//***************************** BATTUTA SX1 *************************************
//**************************** Alto / Basso ************************************
//******************************************************************************

COMP_PRES				= CONF_BATTUTA_SX1;
FUNZ_MANUALE			= FUNZ_MAN48;
MAN_1					= FUNZ_MAN48 && COMANDO_B;
MAN_2					= FUNZ_MAN48 && COMANDO_A;
M_1						= Mg_MC(116) || PLCMg_MC(116);
M_2						= Mg_MC(117) || PLCMg_MC(117);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				= BATTUTA_SX_ALT_O;
OUTPUT_2				= !BATTUTA_SX_ALT_O;
INPUT_1					= !BATTUTA_SX_BAS_I;
INPUT_2					= BATTUTA_SX_BAS_I;

COND_ALL_1				= BATTUTA_SX_BAS_I;		// Condizione anomala nel movimento 1
COND_ALL_2				= !BATTUTA_SX_BAS_I;		// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_TIMEOUT_BATTUTA_SX1_ALT];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= RP_TSuppl[TS_TIMEOUT_BATTUTA_SX1_BAS];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= BATTUTA_SX1_ALT_FAL;		// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= BATTUTA_SX1_BAS_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_9;
uscite_standard ();
COMPONENTE_9			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	BATTUTA_SX_ALT_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}
if (!M_1)
{
	Mr_MC(116);
	PLCMr_MC(116);
}
if (!M_2)
{
	Mr_MC(117);
	PLCMr_MC(117);
}

//**** Messaggi e Allarmi ***********************************************************
BATTUTA_SX1_ALT_FAL =	OUTPUT_1_FAL;
//BATTUTA_SX1_ALT_A_FAL =	OUTPUT_1A_FAL;
//BATTUTA_SX1_ALT_B_FAL =	OUTPUT_1B_FAL;

BATTUTA_SX1_BAS_FAL =	OUTPUT_2_FAL;
//BATTUTA_SX1_BAS_A_FAL =	OUTPUT_2A_FAL;
//BATTUTA_SX1_BAS_B_FAL =	OUTPUT_2B_FAL;


//BAT_SX1_ALTBAS_DISFC_FAL =	DISFUNZIONE_FAL;

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{	
    INS_BARCAR_SX1 = (int) BATTUTA_SX_ALT_O; BARCAR_SX1_INS = (int) !BATTUTA_SX_BAS_I;
    count (&INS_BARCAR_SX1, &BARCAR_SX1_INS, &BARCAR_SX1_INS_COUNT, &BARCAR_SX1_INS_MEMCOUNT, &BARCAR_SX1_INS_MEM, R_SAL_BARCAR_SX1, INS_BARCAR_SX1_COMMENTO);
    DIS_BARCAR_SX1 = (int) !BATTUTA_SX_ALT_O; BARCAR_SX1_DIS = (int) BATTUTA_SX_BAS_I;
    count (&DIS_BARCAR_SX1, &BARCAR_SX1_DIS, &BARCAR_SX1_DIS_COUNT, &BARCAR_SX1_DIS_MEMCOUNT, &BARCAR_SX1_DIS_MEM, R_DIS_BARCAR_SX1, DIS_BARCAR_SX1_COMMENTO);
}

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 9) 
			{	
			goto saltauscite;
			}	
 

//******************************************************************************
//**************************** Componente 10 ************************************
//******************************************************************************
//***************************** BATTUTA SX2 *************************************
//**************************** Alto / Basso ************************************
//******************************************************************************

// *********** ELIMINATO **************

//******************************************************************************
//**************************** Componente 11 ************************************
//******************************************************************************
//***************************** BATTUTA DX3 *************************************
//**************************** Alto / Basso ************************************
//******************************************************************************

// *********** ELIMINATO **************

//******************************************************************************
//**************************** Componente 12 ************************************
//******************************************************************************
//***************************** BATTUTA DX4 *************************************
//**************************** Alto / Basso ************************************
//******************************************************************************

COMP_PRES				= CONF_BATTUTA_DX4;
FUNZ_MANUALE			= FUNZ_MAN49;
MAN_1					= FUNZ_MAN49 && COMANDO_B;
MAN_2					= FUNZ_MAN49 && COMANDO_A;
M_1						= Mg_MC(122) || PLCMg_MC(122);
M_2						= Mg_MC(123) || PLCMg_MC(123);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= BATTUTA_DX_ALT_O;
OUTPUT_2				= !BATTUTA_DX_ALT_O;
INPUT_1					= !BATTUTA_DX_BAS_I;
INPUT_2					= BATTUTA_DX_BAS_I;

COND_ALL_1				= BATTUTA_DX_BAS_I;		// Condizione anomala nel movimento 1
COND_ALL_2				= !BATTUTA_DX_BAS_I;	// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_TIMEOUT_BATTUTA_DX4_ALT];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= RP_TSuppl[TS_TIMEOUT_BATTUTA_DX4_BAS];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= BATTUTA_DX4_ALT_FAL;		// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= BATTUTA_DX4_BAS_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_12;
uscite_standard ();
COMPONENTE_12			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	BATTUTA_DX_ALT_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}
if (!M_1)
{
	Mr_MC(122);
	PLCMr_MC(122);
}
if (!M_2)
{
	Mr_MC(123);
	PLCMr_MC(123);
}

//**** Messaggi e Allarmi ***********************************************************
BATTUTA_DX4_ALT_FAL =	OUTPUT_1_FAL;
//BATTUTA_DX4_ALT_A_FAL =	OUTPUT_1A_FAL;
//BATTUTA_DX4_ALT_B_FAL =	OUTPUT_1B_FAL;

BATTUTA_DX4_BAS_FAL =	OUTPUT_2_FAL;
//BATTUTA_DX4_BAS_A_FAL =	OUTPUT_2A_FAL;
//BATTUTA_DX4_BAS_B_FAL =	OUTPUT_2B_FAL;

//BAT_DX4_ALTBAS_DISFC_FAL =	DISFUNZIONE_FAL;

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{	
    INS_BARCAR_DX4 = (int) BATTUTA_DX_ALT_O; BARCAR_DX4_INS = (int) !BATTUTA_DX_BAS_I;
    count (&INS_BARCAR_DX4, &BARCAR_DX4_INS, &BARCAR_DX4_INS_COUNT, &BARCAR_DX4_INS_MEMCOUNT, &BARCAR_DX4_INS_MEM, R_SAL_BARCAR_DX4, INS_BARCAR_DX4_COMMENTO);
    DIS_BARCAR_DX4 = (int) !BATTUTA_DX_ALT_O; BARCAR_DX4_DIS = (int) BATTUTA_DX_BAS_I;
    count (&DIS_BARCAR_DX4, &BARCAR_DX4_DIS, &BARCAR_DX4_DIS_COUNT, &BARCAR_DX4_DIS_MEMCOUNT, &BARCAR_DX4_DIS_MEM, R_DIS_BARCAR_DX4, DIS_BARCAR_DX4_COMMENTO);
}

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 12) 
			{	
			goto saltauscite;
			}	
 



//******************************************************************************
//**************************** Componente 13 ***********************************
//******************************************************************************
//********************** Magazzino Porta Utensili ******************************
//************************** Avanti / Indietro *********************************
//******************************************************************************

//**************** ELIMINATO ******************************

//******************************************************************************
//**************************** Componente 14 ***********************************
//******************************************************************************
//****************************** MORSA_7 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 15 ***********************************
//******************************************************************************
//****************************** MORSA_8 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

//**************** ELIMINATO ******************************


 

//******************************************************************************
//**************************** Componente 16 ***********************************
//******************************************************************************
//****************************** MORSA_9 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

//**************** ELIMINATO ******************************



//******************************************************************************
//**************************** Componente 17 ***********************************
//******************************************************************************
//****************************** MORSA_10 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_10;
FUNZ_MANUALE			= FUNZ_MAN37;
MAN_1					= F_M_CH_MORSA_10;
MAN_2					= F_M_AP_MORSA_10;
M_1						= Mg_MC(134) || PLCMg_MC(134);
M_2						= Mg_MC(234) || PLCMg_MC(234);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA && !(CH_MORSA_10_HP_O);	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				= CH_MORSA_10_FLAG;
OUTPUT_2				= AP_MORSA_10_O;
INPUT_1					= CH_MORSA_10_FLAG && !AP_MORSA_10_O;	// Appena cambia di stato è ok
INPUT_2					= AP_MORSA_10_O;

COND_ALL_1				= 0;				// L'allarme è collettivo sull'alta pressione
COND_ALL_2				= 0;				// L'allarme è collettivo sull'alta pressione
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_ALL_2			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// Nessun Allarme singolo per le morse 
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_17;
uscite_standard ();
COMPONENTE_17			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_10_FLAG =		OUTPUT_1;

	AP_MORSA_10_O =		OUTPUT_2;
}
if (!M_1)
{
	Mr_MC(134);
	PLCMr_MC(134);
}
if (!M_2)
{
	Mr_MC(234);
	PLCMr_MC(234);
}

//**** Messaggi e Allarmi ***********************************************************
	// Nessun Allarme singolo per le morse 

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 17) 
			{	
			goto saltauscite;
			}	


 

//******************************************************************************
//**************************** Componente 18 ***********************************
//******************************************************************************
//****************************** MORSA_11 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_11;
FUNZ_MANUALE			= FUNZ_MAN38;
MAN_1					= F_M_CH_MORSA_11;
MAN_2					= F_M_AP_MORSA_11;
M_1						= Mg_MC(135) || PLCMg_MC(135);
M_2						= Mg_MC(235) || PLCMg_MC(235);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA && !(CH_MORSA_11_HP_O);	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				= CH_MORSA_11_FLAG;
OUTPUT_2				= AP_MORSA_11_O;
INPUT_1					= CH_MORSA_11_FLAG && !AP_MORSA_11_O;	// Appena cambia di stato è ok
INPUT_2					= AP_MORSA_11_O;

COND_ALL_1				= 0;				// L'allarme è collettivo sull'alta pressione
COND_ALL_2				= 0;				// L'allarme è collettivo sull'alta pressione
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_ALL_2			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// Nessun Allarme singolo per le morse 
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_18;
uscite_standard ();
COMPONENTE_18			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_11_FLAG =		OUTPUT_1;

	AP_MORSA_11_O =		OUTPUT_2;
}
if (!M_1)
{
	Mr_MC(135);
	PLCMr_MC(135);
}
if (!M_2)
{
	Mr_MC(235);
	PLCMr_MC(235);
}

//**** Messaggi e Allarmi ***********************************************************
	// Nessun Allarme singolo per le morse 

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 18) 
			{	
			goto saltauscite;
			}	


 

//******************************************************************************
//**************************** Componente 19 ***********************************
//******************************************************************************
//****************************** MORSA_12 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_12;
FUNZ_MANUALE			= FUNZ_MAN39;
MAN_1					= F_M_CH_MORSA_12;
MAN_2					= F_M_AP_MORSA_12;
M_1						= Mg_MC(136) || PLCMg_MC(136);
M_2						= Mg_MC(236) || PLCMg_MC(236);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA && !(CH_MORSA_12_HP_O);	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				= CH_MORSA_12_FLAG;
OUTPUT_2				= AP_MORSA_12_O;
INPUT_1					= CH_MORSA_12_FLAG && !AP_MORSA_12_O;	// Appena cambia di stato è ok
INPUT_2					= AP_MORSA_12_O;

COND_ALL_1				= 0;				// L'allarme è collettivo sull'alta pressione
COND_ALL_2				= 0;				// L'allarme è collettivo sull'alta pressione
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_ALL_2			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// Nessun Allarme singolo per le morse 
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_19;
uscite_standard ();
COMPONENTE_19			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_12_FLAG =		OUTPUT_1;

	AP_MORSA_12_O =		OUTPUT_2;
}
if (!M_1)
{
	Mr_MC(136);
	PLCMr_MC(136);
}
if (!M_2)
{
	Mr_MC(236);
	PLCMr_MC(236);
}

//**** Messaggi e Allarmi ***********************************************************
	// Nessun Allarme singolo per le morse 

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 19) 
			{	
			goto saltauscite;
			}	

 

//******************************************************************************
//**************************** Componente 20 ***********************************
//******************************************************************************
//****************************** MORSA_13 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_13;
FUNZ_MANUALE			= FUNZ_MAN40;
MAN_1					= F_M_CH_MORSA_13;
MAN_2					= F_M_AP_MORSA_13;
M_1						= Mg_MC(137) || PLCMg_MC(137);
M_2						= Mg_MC(237) || PLCMg_MC(237);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA && !(CH_MORSA_13_HP_O);	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				= CH_MORSA_13_FLAG;
OUTPUT_2				= AP_MORSA_13_O;
INPUT_1					= CH_MORSA_13_FLAG && !AP_MORSA_13_O;	// Appena cambia di stato è ok
INPUT_2					= AP_MORSA_13_O;

COND_ALL_1				= 0;				// L'allarme è collettivo sull'alta pressione
COND_ALL_2				= 0;				// L'allarme è collettivo sull'alta pressione
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_ALL_2			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// Nessun Allarme singolo per le morse 
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_20;
uscite_standard ();
COMPONENTE_20			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_13_FLAG =		OUTPUT_1;

	AP_MORSA_13_O =		OUTPUT_2;
}
if (!M_1)
{
	Mr_MC(137);
	PLCMr_MC(137);
}
if (!M_2)
{
	Mr_MC(237);
	PLCMr_MC(237);
}

//**** Messaggi e Allarmi ***********************************************************
	// Nessun Allarme singolo per le morse 

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 20) 
			{	
			goto saltauscite;
			}	


 

//******************************************************************************
//**************************** Componente 21 ***********************************
//******************************************************************************
//****************************** MORSA_14 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_14;
FUNZ_MANUALE			= FUNZ_MAN41;
MAN_1					= F_M_CH_MORSA_14;
MAN_2					= F_M_AP_MORSA_14;
M_1						= Mg_MC(138) || PLCMg_MC(138);
M_2						= Mg_MC(238) || PLCMg_MC(238);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA && !(CH_MORSA_14_HP_O);	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				= CH_MORSA_14_FLAG;
OUTPUT_2				= AP_MORSA_14_O;
INPUT_1					= CH_MORSA_14_FLAG && !AP_MORSA_14_O;	// Appena cambia di stato è ok
INPUT_2					= AP_MORSA_14_O;

COND_ALL_1				= 0;				// L'allarme è collettivo sull'alta pressione
COND_ALL_2				= 0;				// L'allarme è collettivo sull'alta pressione
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_ALL_2			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// Nessun Allarme singolo per le morse 
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_21;
uscite_standard ();
COMPONENTE_21			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_14_FLAG =		OUTPUT_1;

	AP_MORSA_14_O =		OUTPUT_2;
}
if (!M_1)
{
	Mr_MC(138);
	PLCMr_MC(138);
}
if (!M_2)
{
	Mr_MC(238);
	PLCMr_MC(238);
}

//**** Messaggi e Allarmi ***********************************************************
	// Nessun Allarme singolo per le morse 

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 21) 
			{	
			goto saltauscite;
			}	


 

//******************************************************************************
//**************************** Componente 22 ***********************************
//******************************************************************************
//****************************** MORSA_15 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_15;
FUNZ_MANUALE			= FUNZ_MAN42;
MAN_1					= F_M_CH_MORSA_15;
MAN_2					= F_M_AP_MORSA_15;
M_1						= Mg_MC(139) || PLCMg_MC(139);
M_2						= Mg_MC(239) || PLCMg_MC(239);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA && !(CH_MORSA_15_HP_O);	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				= CH_MORSA_15_FLAG;
OUTPUT_2				= AP_MORSA_15_O;
INPUT_1					= CH_MORSA_15_FLAG && !AP_MORSA_15_O;	// Appena cambia di stato è ok
INPUT_2					= AP_MORSA_15_O;

COND_ALL_1				= 0;				// L'allarme è collettivo sull'alta pressione
COND_ALL_2				= 0;				// L'allarme è collettivo sull'alta pressione
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_ALL_2			= 0;				// L'allarme è collettivo sull'alta pressione
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// Nessun Allarme singolo per le morse 
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_22;
uscite_standard ();
COMPONENTE_22			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_15_FLAG =		OUTPUT_1;

	AP_MORSA_15_O =		OUTPUT_2;
}
if (!M_1)
{
	Mr_MC(139);
	PLCMr_MC(139);
}
if (!M_2)
{
	Mr_MC(239);
	PLCMr_MC(239);
}

//**** Messaggi e Allarmi ***********************************************************
	// Nessun Allarme singolo per le morse 

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 22) 
			{	
			goto saltauscite;
			}	


 

//******************************************************************************
//**************************** Componente 23 ***********************************
//******************************************************************************
//****************************** MORSA_16 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

//**************** ELIMINATO ******************************



//******************************************************************************
//**************************** Componente 24 ***********************************
//******************************************************************************
//****************************** MORSA_17 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

//**************** ELIMINATO ******************************



//******************************************************************************
//**************************** Componente 25 ***********************************
//******************************************************************************
//****************************** MORSA_18 ***************************************
//*************************** Apri / Chiudi ************************************
//******************************************************************************

//**************** ELIMINATO ******************************


// Chiusura morse SX in bassa forza
CH_MORSE_SX_O = CH_MORSA_10_FLAG || CH_MORSA_11_FLAG || CH_MORSA_12_FLAG;

// Chiusura morse DX in bassa forza
CH_MORSE_DX_O = CH_MORSA_13_FLAG || CH_MORSA_14_FLAG || CH_MORSA_15_FLAG;


// Temporizzo caduta segnale di alta pressione morse
PRESS_MORSE_CH_RN = RN_TSuppl[TS_PRESS_MORSE_CH];


// Reset allarmi di alta pressione ancora attiva.  
// Attualmente l'allarme non serve perchè il pressostato di alta pressione morse (PRESS_MORSE_HP_I) è a monte delle EV di ap/ch morse, 
// quindi deve sempre rilevare l'alta pressione attiva, non solo dopo TS_BAS_PRESSIONE_SX
if(RESET_ALL || RESET_MC) 
	{
	BAS_PRESSIONE_FAL = 0;
	}


//******************************************************************************
//**************************** Componente 26 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 7 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 27 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 8 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 28 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 9 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

//**************** ELIMINATO ******************************



//******************************************************************************
//**************************** Componente 29 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 10 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_10;

FUNZ_MANUALE			= 0;
MAN_1					=  RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
MAN_2					= !RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
M_1						= Mg_MC(274) || PLCMg_MC(274);	// attiva chiusura in alta forza morsa
M_2						= Mg_MC(294) || PLCMg_MC(294);  // disattiva chiusura in alta forza morsa
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN && ( (CH_MORSE_SX_O && !AP_MORSA_10_O) || (R[R_GESTMORS_OPER]>0.5) );	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;		// Anche a riparo basso per ergonomico - Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				=   CH_MORSA_10_HP_O;
OUTPUT_2				= !(CH_MORSA_10_HP_O);
INPUT_1					=   CH_MORSA_10_HP_O && PRESS_MORSE_HP_I;		// Con le morse chiuse va a 1
INPUT_2					= !(CH_MORSA_10_HP_O);

COND_ALL_1				= (CH_MORSA_10_HP_O) && ( (AP_MORSA_10_O) || (!PRESS_MORSE_CH_RN && APP_OUT_MAC_ABIL && APP_INPUT_ARIA_PRES) ) ;  // Condizione che attiva l'allarme di ASSENZA  alta pressione su questa morsa
COND_ALL_2				= 0;                                                                                 // Condizione che attiva l'allarme di PRESENZA alta pressione su questa morsa  (Alta pressione ancora attiva)
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_ALT_PRESS_MORSA10];  // Ritardo dopo il quale puo attivarsi l'allarme di ASSENZA  alta pressione su questa morsa
TIMEOUT_ALL_2			= 0;                                            // Ritardo dopo il quale puo attivarsi l'allarme di PRESENZA alta pressione su questa morsa	 (Alta pressione ancora attiva)
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= ALT_PRESS_MORSA10_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0; // eliminato: BAS_PRESSIONE_FAL;	  // Allarme comune per l'alta pressione ancora attiva	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_29;
uscite_standard ();
COMPONENTE_29			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_10_HP_O = OUTPUT_1;

}
if (!M_1)
{
	Mr_MC(274);
	PLCMr_MC(274);
}
if (!M_2)
{
	Mr_MC(294);
	PLCMr_MC(294);
}

ALT_PRESS_MORSA10_FAL	= OUTPUT_1_FAL;
////BAS_PRESSIONE_FAL	= OUTPUT_2_FAL;


if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{	
    UP_HIGH_PRES_MORSE = (int) (CH_MORSA_10_HP_O || CH_MORSA_11_HP_O || CH_MORSA_12_HP_O || CH_MORSA_13_HP_O || CH_MORSA_14_HP_O || CH_MORSA_15_HP_O); 
	HIGH_PRES_MORSE_UP = (int) PRESS_MORSE_HP_I;
    count (&UP_HIGH_PRES_MORSE, &HIGH_PRES_MORSE_UP, &HIGH_PRES_MORSE_UP_COUNT, &HIGH_PRES_MORSE_UP_MEMCOUNT, &HIGH_PRES_MORSE_UP_MEM, R_HIGH_PRESS_SX_UP, UP_HIGH_PRES_MORSE_COMMENTO);
    
	DOWN_HIGH_PRES_MORSE = (int) (!CH_MORSA_10_HP_O && !CH_MORSA_11_HP_O && !CH_MORSA_12_HP_O && !CH_MORSA_13_HP_O && !CH_MORSA_14_HP_O && !CH_MORSA_15_HP_O);
	HIGH_PRES_MORSE_DOWN = (int) !PRESS_MORSE_HP_I;
    count (&DOWN_HIGH_PRES_MORSE, &HIGH_PRES_MORSE_DOWN, &HIGH_PRES_MORSE_DOWN_COUNT, &HIGH_PRES_MORSE_DOWN_MEMCOUNT, &HIGH_PRES_MORSE_DOWN_MEM, R_HIGH_PRESS_SX_DOWN, DOWN_HIGH_PRES_MORSE_COMMENTO);
}


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 29) 
			{	
			goto saltauscite;
			}


//******************************************************************************
//**************************** Componente 30 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 11 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_11;

FUNZ_MANUALE			= 0;
MAN_1					=  RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
MAN_2					= !RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
M_1						= Mg_MC(275) || PLCMg_MC(275);	// attiva chiusura in alta forza morsa
M_2						= Mg_MC(295) || PLCMg_MC(295);  // disattiva chiusura in alta forza morsa
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN && ( (CH_MORSE_SX_O && !AP_MORSA_11_O) || (R[R_GESTMORS_OPER]>0.5) );	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;		// Anche a riparo basso per ergonomico - Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				=   CH_MORSA_11_HP_O;
OUTPUT_2				= !(CH_MORSA_11_HP_O);
INPUT_1					=   CH_MORSA_11_HP_O && PRESS_MORSE_HP_I;		// Con le morse chiuse va a 1
INPUT_2					= !(CH_MORSA_11_HP_O);

COND_ALL_1				= (CH_MORSA_11_HP_O) && ( (AP_MORSA_11_O) || (!PRESS_MORSE_CH_RN && APP_OUT_MAC_ABIL && APP_INPUT_ARIA_PRES) ) ;  // Condizione che attiva l'allarme di ASSENZA  alta pressione su questa morsa
COND_ALL_2				= 0;                                                                                 // Condizione che attiva l'allarme di PRESENZA alta pressione su questa morsa  (Alta pressione ancora attiva)
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_ALT_PRESS_MORSA11];  // Ritardo dopo il quale puo attivarsi l'allarme di ASSENZA  alta pressione su questa morsa
TIMEOUT_ALL_2			= 0;                                            // Ritardo dopo il quale puo attivarsi l'allarme di PRESENZA alta pressione su questa morsa	 (Alta pressione ancora attiva)
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= ALT_PRESS_MORSA11_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0; // eliminato: BAS_PRESSIONE_FAL;	  // Allarme comune per l'alta pressione ancora attiva	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_30;
uscite_standard ();
COMPONENTE_30			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_11_HP_O = OUTPUT_1;

}
if (!M_1)
{
	Mr_MC(275);
	PLCMr_MC(275);
}
if (!M_2)
{
	Mr_MC(295);
	PLCMr_MC(295);
}

ALT_PRESS_MORSA11_FAL	= OUTPUT_1_FAL;
////BAS_PRESSIONE_FAL	= OUTPUT_2_FAL;

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 30) 
			{	
			goto saltauscite;
			}


//******************************************************************************
//**************************** Componente 31 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 12 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_12;

FUNZ_MANUALE			= 0;
MAN_1					=  RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
MAN_2					= !RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
M_1						= Mg_MC(276) || PLCMg_MC(276);	// attiva chiusura in alta forza morsa
M_2						= Mg_MC(296) || PLCMg_MC(296);  // disattiva chiusura in alta forza morsa
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN && ( (CH_MORSE_SX_O && !AP_MORSA_12_O) || (R[R_GESTMORS_OPER]>0.5) );	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;		// Anche a riparo basso per ergonomico - Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				=   CH_MORSA_12_HP_O;
OUTPUT_2				= !(CH_MORSA_12_HP_O);
INPUT_1					=   CH_MORSA_12_HP_O && PRESS_MORSE_HP_I;		// Con le morse chiuse va a 1
INPUT_2					= !(CH_MORSA_12_HP_O);

COND_ALL_1				= (CH_MORSA_12_HP_O) && ( (AP_MORSA_12_O) || (!PRESS_MORSE_CH_RN && APP_OUT_MAC_ABIL && APP_INPUT_ARIA_PRES) ) ;  // Condizione che attiva l'allarme di ASSENZA  alta pressione su questa morsa
COND_ALL_2				= 0;                                                                                 // Condizione che attiva l'allarme di PRESENZA alta pressione su questa morsa  (Alta pressione ancora attiva)
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_ALT_PRESS_MORSA12];  // Ritardo dopo il quale puo attivarsi l'allarme di ASSENZA  alta pressione su questa morsa
TIMEOUT_ALL_2			= 0;                                            // Ritardo dopo il quale puo attivarsi l'allarme di PRESENZA alta pressione su questa morsa	 (Alta pressione ancora attiva)
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= ALT_PRESS_MORSA12_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0; // eliminato: BAS_PRESSIONE_FAL;	  // Allarme comune per l'alta pressione ancora attiva	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_31;
uscite_standard ();
COMPONENTE_31			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_12_HP_O = OUTPUT_1;

}
if (!M_1)
{
	Mr_MC(276);
	PLCMr_MC(276);
}
if (!M_2)
{
	Mr_MC(296);
	PLCMr_MC(296);
}

ALT_PRESS_MORSA12_FAL	= OUTPUT_1_FAL;
////BAS_PRESSIONE_FAL	= OUTPUT_2_FAL;

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 31) 
			{	
			goto saltauscite;
			}




//******************************************************************************
//**************************** Componente 32 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 13 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_13;

FUNZ_MANUALE			= 0;
MAN_1					=  RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
MAN_2					= !RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
M_1						= Mg_MC(277) || PLCMg_MC(277);	// attiva chiusura in alta forza morsa
M_2						= Mg_MC(297) || PLCMg_MC(297);  // disattiva chiusura in alta forza morsa
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN && ( (CH_MORSE_DX_O && !AP_MORSA_13_O) || (R[R_GESTMORS_OPER]>0.5) );	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;		// Anche a riparo basso per ergonomico - Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				=   CH_MORSA_13_HP_O;
OUTPUT_2				= !(CH_MORSA_13_HP_O);
INPUT_1					=   CH_MORSA_13_HP_O && PRESS_MORSE_HP_I;		// Con le morse chiuse va a 1
INPUT_2					= !(CH_MORSA_13_HP_O);

COND_ALL_1				= (CH_MORSA_13_HP_O) && ( (AP_MORSA_13_O) || (!PRESS_MORSE_CH_RN && APP_OUT_MAC_ABIL && APP_INPUT_ARIA_PRES) ) ;  // Condizione che attiva l'allarme di ASSENZA  alta pressione su questa morsa
COND_ALL_2				= 0;                                                                                 // Condizione che attiva l'allarme di PRESENZA alta pressione su questa morsa  (Alta pressione ancora attiva)
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_ALT_PRESS_MORSA13];  // Ritardo dopo il quale puo attivarsi l'allarme di ASSENZA  alta pressione su questa morsa
TIMEOUT_ALL_2			= 0;                                            // Ritardo dopo il quale puo attivarsi l'allarme di PRESENZA alta pressione su questa morsa	 (Alta pressione ancora attiva)
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= ALT_PRESS_MORSA13_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0; // eliminato: BAS_PRESSIONE_FAL;	  // Allarme comune per l'alta pressione ancora attiva	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_32;
uscite_standard ();
COMPONENTE_32			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_13_HP_O = OUTPUT_1;

}
if (!M_1)
{
	Mr_MC(277);
	PLCMr_MC(277);
}
if (!M_2)
{
	Mr_MC(297);
	PLCMr_MC(297);
}

ALT_PRESS_MORSA13_FAL	= OUTPUT_1_FAL;
////BAS_PRESSIONE_FAL	= OUTPUT_2_FAL;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 32) 
			{	
			goto saltauscite;
			}


//******************************************************************************
//**************************** Componente 33 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 14 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_14;

FUNZ_MANUALE			= 0;
MAN_1					=  RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
MAN_2					= !RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
M_1						= Mg_MC(278) || PLCMg_MC(278);	// attiva chiusura in alta forza morsa
M_2						= Mg_MC(298) || PLCMg_MC(298);  // disattiva chiusura in alta forza morsa
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN && ( (CH_MORSE_DX_O && !AP_MORSA_14_O) || (R[R_GESTMORS_OPER]>0.5) );	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;		// Anche a riparo basso per ergonomico - Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				=   CH_MORSA_14_HP_O;
OUTPUT_2				= !(CH_MORSA_14_HP_O);
INPUT_1					=   CH_MORSA_14_HP_O && PRESS_MORSE_HP_I;		// Con le morse chiuse va a 1
INPUT_2					= !(CH_MORSA_14_HP_O);

COND_ALL_1				= (CH_MORSA_14_HP_O) && ( (AP_MORSA_14_O) || (!PRESS_MORSE_CH_RN && APP_OUT_MAC_ABIL && APP_INPUT_ARIA_PRES) ) ;  // Condizione che attiva l'allarme di ASSENZA  alta pressione su questa morsa
COND_ALL_2				= 0;                                                                                 // Condizione che attiva l'allarme di PRESENZA alta pressione su questa morsa  (Alta pressione ancora attiva)
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_ALT_PRESS_MORSA14];  // Ritardo dopo il quale puo attivarsi l'allarme di ASSENZA  alta pressione su questa morsa
TIMEOUT_ALL_2			= 0;                                            // Ritardo dopo il quale puo attivarsi l'allarme di PRESENZA alta pressione su questa morsa	 (Alta pressione ancora attiva)
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= ALT_PRESS_MORSA14_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0; // eliminato: BAS_PRESSIONE_FAL;	  // Allarme comune per l'alta pressione ancora attiva	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_33;
uscite_standard ();
COMPONENTE_33			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_14_HP_O = OUTPUT_1;

}
if (!M_1)
{
	Mr_MC(278);
	PLCMr_MC(278);
}
if (!M_2)
{
	Mr_MC(298);
	PLCMr_MC(298);
}

ALT_PRESS_MORSA14_FAL	= OUTPUT_1_FAL;
////BAS_PRESSIONE_FAL	= OUTPUT_2_FAL;

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 33) 
			{	
			goto saltauscite;
			}


//******************************************************************************
//**************************** Componente 34 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 15 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

COMP_PRES				= CONF_MORSA_15;

FUNZ_MANUALE			= 0;
MAN_1					=  RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
MAN_2					= !RP_TSuppl[TS_FORZA_ALTA_PRESS_MAN];
M_1						= Mg_MC(279) || PLCMg_MC(279);	// attiva chiusura in alta forza morsa
M_2						= Mg_MC(299) || PLCMg_MC(299);  // disattiva chiusura in alta forza morsa
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN && ( (CH_MORSE_DX_O && !AP_MORSA_15_O) || (R[R_GESTMORS_OPER]>0.5) );	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;		// Anche a riparo basso per ergonomico - Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;

OUTPUT_1				=   CH_MORSA_15_HP_O;
OUTPUT_2				= !(CH_MORSA_15_HP_O);
INPUT_1					=   CH_MORSA_15_HP_O && PRESS_MORSE_HP_I;		// Con le morse chiuse va a 1
INPUT_2					= !(CH_MORSA_15_HP_O);

COND_ALL_1				= (CH_MORSA_15_HP_O) && ( (AP_MORSA_15_O) || (!PRESS_MORSE_CH_RN && APP_OUT_MAC_ABIL && APP_INPUT_ARIA_PRES) ) ;  // Condizione che attiva l'allarme di ASSENZA  alta pressione su questa morsa
COND_ALL_2				= 0;                                                                                 // Condizione che attiva l'allarme di PRESENZA alta pressione su questa morsa  (Alta pressione ancora attiva)
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_ALT_PRESS_MORSA15];  // Ritardo dopo il quale puo attivarsi l'allarme di ASSENZA  alta pressione su questa morsa
TIMEOUT_ALL_2			= 0;                                            // Ritardo dopo il quale puo attivarsi l'allarme di PRESENZA alta pressione su questa morsa	 (Alta pressione ancora attiva)
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= ALT_PRESS_MORSA15_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0; // eliminato: BAS_PRESSIONE_FAL;	  // Allarme comune per l'alta pressione ancora attiva	
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_34;
uscite_standard ();
COMPONENTE_34			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	CH_MORSA_15_HP_O = OUTPUT_1;

}
if (!M_1)
{
	Mr_MC(279);
	PLCMr_MC(279);
}
if (!M_2)
{
	Mr_MC(299);
	PLCMr_MC(299);
}

ALT_PRESS_MORSA15_FAL	= OUTPUT_1_FAL;
////BAS_PRESSIONE_FAL	= OUTPUT_2_FAL;

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 34) 
			{	
			goto saltauscite;
			}




//******************************************************************************
//**************************** Componente 35 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 16 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

//**************** ELIMINATO ******************************


			
//******************************************************************************
//**************************** Componente 36 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 17 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 37 ***********************************
//******************************************************************************
//************************* EV Alta Pressione Morsa 18 **************************
//***************************** OFF / ON ***************************************
//******************************************************************************

//**************** ELIMINATO ******************************



//******************************************************************************
//**************************** Componente 38 ***********************************
//******************************************************************************
//************************* DIAFRAMMA CENTRALE *********************************
//************************* movimento SX / DX **********************************
//******************************************************************************

//****** ELIMINATO ********


//******************************************************************************
//**************************** Componente 39 ***********************************
//******************************************************************************
//******************** Trasportatori Trucioli SX e DX **************************
//**************************** OFF / ON  ***************************************
//******************************************************************************

// AVANTI TRASPORTATORE TRUCIOLO
if(PON)
{
	CONT_TRASP = (short) 12000;
}

if (R[R_TRASP_USE] == 0)	// 0=continuo
	GEST_TRASP = 1; 

if (R[R_TRASP_USE] == 1)	// 1=intermittente
{
	if (CONT_TRASP<=0) CONT_TRASP = 12000;
	if (CONT_TRASP>0)  CONT_TRASP--;
	GEST_TRASP = (CONT_TRASP>6000); 
}
else
	CONT_TRASP = 12000;

if (R[R_TRASP_USE] == 2)	// 2=fermo
	GEST_TRASP = 0; 

COMP_PRES				= CONF_TRASP;
FUNZ_MANUALE			= FUNZ_MAN83;
MAN_1					= FUNZ_MAN83 && COMANDO_B;
MAN_2					= FUNZ_MAN83 && COMANDO_A; 
M_1						= Mg_MC(101) || PLCMg_MC(101);
M_2						= Mg_MC(102) || PLCMg_MC(102) || RESET_MC;
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 0;			// Azzero l'uscita nel passaggio AUTO->MAN
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN_RIT && ( (GEST_TRASP && CICLO_ON) || MANO);	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= ABILITAZIONI_AUTO_MAN_RIT;						// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= AVA_TRASP_O;
OUTPUT_2				= 0;
INPUT_1					= AVA_TRASP_O;
INPUT_2					= !AVA_TRASP_O;

COND_ALL_1				= 0;					// Condizione anomala nel movimento 1
COND_ALL_2				= 0;					// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_39;
uscite_standard ();
COMPONENTE_39			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	// Le due uscite sono identiche
	// L'allarme è solo il termico che è gestito separatamente insieme agli altri termici
	AVA_TRASP_O =		OUTPUT_1;

	// OUTPUT_2 NON presente
}
if (!M_1)
	{
	Mr_MC(101);
	PLCMr_MC(101);
	}
if (!M_2)
	{
	Mr_MC(102);
	PLCMr_MC(102);
	}

//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
//DIS_£_FAL =	OUTPUT_2_FAL;
// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 39) 
			{	
			goto saltauscite;
			}	



//******************************************************************************
//**************************** Componente 40 ***********************************
//******************************************************************************
//******************** Rilevatore morse su ASSE X ****************************
//*********************** Inserito / Disinserito *******************************
//******************************************************************************

COMP_PRES				= CONF_RILEV_MORSE_AX_X;
FUNZ_MANUALE			= FUNZ_MAN47;
MAN_1					= FUNZ_MAN47 && COMANDO_B;
MAN_2					= FUNZ_MAN47 && COMANDO_A;
M_1						= Mg_MC(56) || PLCMg_MC(56);
M_2						= Mg_MC(57) || PLCMg_MC(57);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= INS_RILMOR_AX_X_O;
OUTPUT_2				= !INS_RILMOR_AX_X_O;
INPUT_1					= !PRESENZA_MORSA_AX_X_I || ((Mg_MC(110) || Mg_MC(112) || Mg_MC(152) || Mg_MC(245)) && PRESENZA_MORSA_AX_X_I);
INPUT_2					= PRESENZA_MORSA_AX_X_I;

COND_ALL_1				= !(Mg_MC(110) || Mg_MC(112) || Mg_MC(152) || Mg_MC(245)) && PRESENZA_MORSA_AX_X_I;		// Condizione anomala nel movimento 1 (deve essere verificato se non siamo in ciclo di ricerca morse)
COND_ALL_2				= !PRESENZA_MORSA_AX_X_I;		// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_RILMOR_AX_X_INS]; // Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= RP_TSuppl[TS_RILMOR_AX_X_DIS]; // Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= RILMOR_AX_X_INS_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= RILMOR_AX_X_DIS_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_40;
uscite_standard ();
COMPONENTE_40			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	INS_RILMOR_AX_X_O =	OUTPUT_1;
	//TRASC_MORSE_AX_X_DIS_O =	OUTPUT_2;
} 
if (!M_1)
{
	Mr_MC(56);
	PLCMr_MC(56);
}
if (!M_2)
{
	Mr_MC(57);
	PLCMr_MC(57);
}

//**** Messaggi e Allarmi ***********************************************************
RILMOR_AX_X_INS_FAL =	OUTPUT_1_FAL;
//RILMOR_AX_X_INS_A_FAL =	OUTPUT_1A_FAL;
//RILMOR_AX_X_INS_B_FAL =	OUTPUT_1B_FAL;

RILMOR_AX_X_DIS_FAL =	OUTPUT_2_FAL;
//RILMOR_AX_X_DIS_A_FAL =	OUTPUT_2A_FAL;
//RILMOR_AX_X_DIS_B_FAL =	OUTPUT_2B_FAL;


//RILMOR_AX_X_DISFC_FAL =	DISFUNZIONE_FAL;

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;

if(!SIMULATORE_SU_CN && !SIMULATORE_SU_PC)
{

	INS_RILMOR = (int) INS_RILMOR_AX_X_O; RILMOR_INS = (int) !PRESENZA_MORSA_AX_X_I;
	count (&INS_RILMOR, &RILMOR_INS, &INS_RILMOR_COUNT, &INS_RILMOR_MEMCOUNT, &INS_RILMOR_MEM, R_INS_RILMOR_AX_X, INS_RILMOR_COMMENTO);

	DIS_RILMOR = (int) !INS_RILMOR_AX_X_O; RILMOR_DIS = (int) PRESENZA_MORSA_AX_X_I;
	count (&DIS_RILMOR, &RILMOR_DIS, &DIS_RILMOR_COUNT, &DIS_RILMOR_MEMCOUNT, &DIS_RILMOR_MEM, R_DIS_RILMOR_AX_X, DIS_RILMOR_COMMENTO);

}

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 40) 
			{	
			goto saltauscite;
			}



//******************************************************************************
//**************************** Componente 41 ***********************************
//******************************************************************************
//************************** BATTUTA su ASSE P *********************************
//*********************** Inserita / Disinserita *******************************
//******************************************************************************

//****** ELIMINATO ********


//******************************************************************************
//**************************** Componente 42 ***********************************
//******************************************************************************
//************************** BATTUTA su ASSE H *********************************
//*********************** Inserita / Disinserita *******************************
//******************************************************************************

//****** ELIMINATO ********


//******************************************************************************
//**************************** Componente 43 ***********************************
//******************************************************************************
//******************** Trascinatore morse su ASSE P ****************************
//*********************** Inserita / Disinserita *******************************
//******************************************************************************

//****** ELIMINATO ********
 

//******************************************************************************
//**************************** Componente 44 ***********************************
//******************************************************************************
//******************** Trascinatore morse su ASSE H ****************************
//*********************** Inserita / Disinserita *******************************
//******************************************************************************

//****** ELIMINATO ********
 




//******************************************************************************
//**************************** Componente 45 ***********************************
//******************************************************************************
//******************** Trascinatore morse su ASSE X ****************************
//*********************** Inserita / Disinserita *******************************
//******************************************************************************

COMP_PRES				= CONF_TRASC_MORSE_AX_X;
FUNZ_MANUALE			= FUNZ_MAN69;
MAN_1					= FUNZ_MAN69 && COMANDO_B;
MAN_2					= FUNZ_MAN69 && COMANDO_A;
M_1						= Mg_MC(201) || PLCMg_MC(201);
M_2						= Mg_MC(202) || PLCMg_MC(202);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= MACCHINA_PRONTA;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 1;


OUTPUT_1				= TRASC_MORSE_AX_X_INS_O;
OUTPUT_2				= !TRASC_MORSE_AX_X_INS_O;
INPUT_1					= RP_TRASC_INSERITO_X && PRESENZA_MORSA_AX_X_I; // verifica che trascinatore sia effettivamente sulla morsa prima di iniziar a muover asse X
INPUT_2					= TRASC_MORSE_AX_X_DIS_I;

COND_ALL_1				= !TRASC_MORSE_AX_X_INS_I;		// Condizione anomala nel movimento 1
COND_ALL_2				= !TRASC_MORSE_AX_X_DIS_I;		// Condizione anomala nel movimento 2
COND_DISF				= INPUT_1 && INPUT_2;
TIMEOUT_ALL_1			= RP_TSuppl[TS_TRASC_MORSE_AX_X_INS]; // Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= RP_TSuppl[TS_TRASC_MORSE_AX_X_DIS]; // Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= BITON;

OUTPUT_1_FAL			= 0;							// INS_£_FAL;
OUTPUT_1A_FAL			= TRASC_MORSE_AX_X_INS_A_FAL;
OUTPUT_1B_FAL			= TRASC_MORSE_AX_X_INS_B_FAL;
OUTPUT_2_FAL			= 0;
OUTPUT_2A_FAL			= TRASC_MORSE_AX_X_DIS_A_FAL;
OUTPUT_2B_FAL			= TRASC_MORSE_AX_X_DIS_B_FAL;
DISFUNZIONE_FAL			= TRASC_MORSE_AX_X_DISFC_FAL;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_45;
uscite_standard ();
COMPONENTE_45			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	TRASC_MORSE_AX_X_INS_O =	OUTPUT_1;
	//TRASC_MORSE_AX_X_DIS_O =	OUTPUT_2;
} 
if (!M_1)
{
	Mr_MC(201);
	PLCMr_MC(201);
}
if (!M_2)
{
	Mr_MC(202);
	PLCMr_MC(202);
}

//**** Messaggi e Allarmi ***********************************************************
//TRASC_MORSE_AX_X_INS_FAL =	OUTPUT_1_FAL;
TRASC_MORSE_AX_X_INS_A_FAL =	OUTPUT_1A_FAL;
TRASC_MORSE_AX_X_INS_B_FAL =	OUTPUT_1B_FAL;

//TRASC_MORSE_AX_X_DIS_FAL =	OUTPUT_2_FAL;
TRASC_MORSE_AX_X_DIS_A_FAL =	OUTPUT_2A_FAL;
TRASC_MORSE_AX_X_DIS_B_FAL =	OUTPUT_2B_FAL;


TRASC_MORSE_AX_X_DISFC_FAL =	DISFUNZIONE_FAL;

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{	
    INS_TRASC_X_MORSE = (int) TRASC_MORSE_AX_X_INS_O; TRASC_X_MORSE_INS = (int) TRASC_MORSE_AX_X_INS_I;
    count (&INS_TRASC_X_MORSE, &TRASC_X_MORSE_INS, &TRASC_X_MORSE_INS_COUNT, &TRASC_X_MORSE_INS_MEMCOUNT, &TRASC_X_MORSE_INS_MEM, R_INS_TRASC_X_MORSE, INS_TRASC_X_MORSE_COMMENTO);
    DIS_TRASC_X_MORSE = (int) !TRASC_MORSE_AX_X_INS_O; TRASC_X_MORSE_DIS = (int) TRASC_MORSE_AX_X_DIS_I;
    count (&DIS_TRASC_X_MORSE, &TRASC_X_MORSE_DIS, &TRASC_X_MORSE_DIS_COUNT, &TRASC_X_MORSE_DIS_MEMCOUNT, &TRASC_X_MORSE_DIS_MEM, R_DIS_TRASC_X_MORSE, DIS_TRASC_X_MORSE_COMMENTO);
}

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 45) 
			{	
			goto saltauscite;
			}	
 



//******************************************************************************
//**************************** Componente 46 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 07 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

//**************** ELIMINATO ******************************	


//******************************************************************************
//**************************** Componente 47 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 08 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 48 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 09 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 49 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 10 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

COMP_PRES				= CONF_ZIMMER_MORSA_10;
FUNZ_MANUALE			= FUNZ_MAN54;
MAN_1					= FUNZ_MAN54 && COMANDO_B;
MAN_2					= FUNZ_MAN54 && (COMANDO_A || !COMANDO_B); 
M_1						= Mg_MC(324) || PLCMg_MC(324);
M_2						= Mg_MC(337) || PLCMg_MC(337);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= SBLOC_MORSA_10_O;
OUTPUT_2				= !SBLOC_MORSA_10_O;
INPUT_1					= RP_TSuppl[TS_SBLOCCAGGIO_MORSA_10];
INPUT_2					= !SBLOC_MORSA_10_O;

COND_ALL_1				= 0;					// Condizione anomala nel movimento 1
COND_ALL_2				= 0;					// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_49;
uscite_standard ();
COMPONENTE_49			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	SBLOC_MORSA_10_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}

if (!M_1)
{
	Mr_MC(324);
	PLCMr_MC(324);
}
if (!M_2)
{
	Mr_MC(337);
	PLCMr_MC(337);
}

//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
//DIS_£_FAL =	OUTPUT_2_FAL;
// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 49) 
			{	
			goto saltauscite;
			}	





//******************************************************************************
//**************************** Componente 50 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 11 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

COMP_PRES				= CONF_ZIMMER_MORSA_11;
FUNZ_MANUALE			= FUNZ_MAN55;
MAN_1					= FUNZ_MAN55 && COMANDO_B;
MAN_2					= FUNZ_MAN55 && (COMANDO_A || !COMANDO_B); 
M_1						= Mg_MC(325) || PLCMg_MC(325);
M_2						= Mg_MC(338) || PLCMg_MC(338);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= SBLOC_MORSA_11_O;
OUTPUT_2				= !SBLOC_MORSA_11_O;
INPUT_1					= RP_TSuppl[TS_SBLOCCAGGIO_MORSA_11];
INPUT_2					= !SBLOC_MORSA_11_O;

COND_ALL_1				= 0;					// Condizione anomala nel movimento 1
COND_ALL_2				= 0;					// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_50;
uscite_standard ();
COMPONENTE_50			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	SBLOC_MORSA_11_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}

if (!M_1)
{
	Mr_MC(325);
	PLCMr_MC(325);
}
if (!M_2)
{
	Mr_MC(338);
	PLCMr_MC(338);
}

//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
//DIS_£_FAL =	OUTPUT_2_FAL;
// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 50) 
			{	
			goto saltauscite;
			}	




//******************************************************************************
//**************************** Componente 51 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 12 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

COMP_PRES				= CONF_ZIMMER_MORSA_12;
FUNZ_MANUALE			= FUNZ_MAN56;
MAN_1					= FUNZ_MAN56 && COMANDO_B;
MAN_2					= FUNZ_MAN56 && (COMANDO_A || !COMANDO_B); 
M_1						= Mg_MC(326) || PLCMg_MC(326);
M_2						= Mg_MC(339) || PLCMg_MC(339);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= SBLOC_MORSA_12_O;
OUTPUT_2				= !SBLOC_MORSA_12_O;
INPUT_1					= RP_TSuppl[TS_SBLOCCAGGIO_MORSA_12];
INPUT_2					= !SBLOC_MORSA_12_O;

COND_ALL_1				= 0;					// Condizione anomala nel movimento 1
COND_ALL_2				= 0;					// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_51;
uscite_standard ();
COMPONENTE_51			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	SBLOC_MORSA_12_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}

if (!M_1)
{
	Mr_MC(326);
	PLCMr_MC(326);
}
if (!M_2)
{
	Mr_MC(339);
	PLCMr_MC(339);
}

//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
//DIS_£_FAL =	OUTPUT_2_FAL;
// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 51) 
			{	
			goto saltauscite;
			}	






//******************************************************************************
//**************************** Componente 52 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 13 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

COMP_PRES				= CONF_ZIMMER_MORSA_13;
FUNZ_MANUALE			= FUNZ_MAN57;
MAN_1					= FUNZ_MAN57 && COMANDO_B;
MAN_2					= FUNZ_MAN57 && (COMANDO_A || !COMANDO_B); 
M_1						= Mg_MC(327) || PLCMg_MC(327);
M_2						= Mg_MC(340) || PLCMg_MC(340);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= SBLOC_MORSA_13_O;
OUTPUT_2				= !SBLOC_MORSA_13_O;
INPUT_1					= RP_TSuppl[TS_SBLOCCAGGIO_MORSA_13];
INPUT_2					= !SBLOC_MORSA_13_O;

COND_ALL_1				= 0;					// Condizione anomala nel movimento 1
COND_ALL_2				= 0;					// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_52;
uscite_standard ();
COMPONENTE_52			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	SBLOC_MORSA_13_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}

if (!M_1)
{
	Mr_MC(327);
	PLCMr_MC(327);
}
if (!M_2)
{
	Mr_MC(340);
	PLCMr_MC(340);
}


//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
//DIS_£_FAL =	OUTPUT_2_FAL;
// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 52) 
			{	
			goto saltauscite;
			}	




//******************************************************************************
//**************************** Componente 53 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 14 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

COMP_PRES				= CONF_ZIMMER_MORSA_14;
FUNZ_MANUALE			= FUNZ_MAN58;
MAN_1					= FUNZ_MAN58 && COMANDO_B;
MAN_2					= FUNZ_MAN58 && (COMANDO_A || !COMANDO_B); 
M_1						= Mg_MC(328) || PLCMg_MC(328);
M_2						= Mg_MC(341) || PLCMg_MC(341);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= SBLOC_MORSA_14_O;
OUTPUT_2				= !SBLOC_MORSA_14_O;
INPUT_1					= RP_TSuppl[TS_SBLOCCAGGIO_MORSA_14];
INPUT_2					= !SBLOC_MORSA_14_O;

COND_ALL_1				= 0;					// Condizione anomala nel movimento 1
COND_ALL_2				= 0;					// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_53;
uscite_standard ();
COMPONENTE_53			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	SBLOC_MORSA_14_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}
if (!M_1)
{
	Mr_MC(328);
	PLCMr_MC(328);
}
if (!M_2)
{
	Mr_MC(341);
	PLCMr_MC(341);
}


//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
//DIS_£_FAL =	OUTPUT_2_FAL;
// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 53) 
			{	
			goto saltauscite;
			}	




//******************************************************************************
//**************************** Componente 54 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 15 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

COMP_PRES				= CONF_ZIMMER_MORSA_15;
FUNZ_MANUALE			= FUNZ_MAN59;
MAN_1					= FUNZ_MAN59 && COMANDO_B;
MAN_2					= FUNZ_MAN59 && (COMANDO_A || !COMANDO_B); 
M_1						= Mg_MC(329) || PLCMg_MC(329);
M_2						= Mg_MC(342) || PLCMg_MC(342);
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 1
COND_MACCHINA_2			= ABILITAZIONI_AUTO_MAN_RIT;	// Condizione x eseguire il movimento 2
DIAGNOSTICA_2_IN		= 0;


OUTPUT_1				= SBLOC_MORSA_15_O;
OUTPUT_2				= !SBLOC_MORSA_15_O;
INPUT_1					= RP_TSuppl[TS_SBLOCCAGGIO_MORSA_15];
INPUT_2					= !SBLOC_MORSA_15_O;

COND_ALL_1				= 0;					// Condizione anomala nel movimento 1
COND_ALL_2				= 0;					// Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= 0;					// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= 0;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= 0;
OUTPUT_1B_FAL			= 0;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= 0;
OUTPUT_2B_FAL			= 0;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_54;
uscite_standard ();
COMPONENTE_54			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	SBLOC_MORSA_15_O =		OUTPUT_1;
	// OUTPUT_2 NON presente
}

if (!M_1)
{
	Mr_MC(329);
	PLCMr_MC(329);
}
if (!M_2)
{
	Mr_MC(342);
	PLCMr_MC(342);
}



//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
//DIS_£_FAL =	OUTPUT_2_FAL;
// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;


// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 54) 
			{	
			goto saltauscite;
			}	


//******************************************************************************
//**************************** Componente 55 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 16 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 56 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 17 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

//**************** ELIMINATO ******************************


//******************************************************************************
//**************************** Componente 57 ***********************************
//******************************************************************************
//************************** Zimmer Morsa 18 (senza asse) **********************
//**************************** Sblocca/Blocca **********************************
//******************************************************************************

//**************** ELIMINATO ******************************	



//******************************************************************************
//**************************** Componente 58 ***********************************
//******************************************************************************
//**************************** VISIERA BASSA  **********************************
//************************* movimento AVA / IND ********************************
//******************************************************************************

if(R[R_DISAB_RIPARI_FIERA]>0.5)  //Disabilita apertura riparo in automatico
{
	Mr_MC(310);
	PLCMr_MC(310);
	Mr_MC(311);
	PLCMr_MC(311);
}

//**** Ritardo su ingressi per considerare eseguito il movimento ***** 
APP_RIT_VISIERA_IND = RP_TSuppl[TS_RIT_VISIERA_IND];
APP_RIT_VISIERA_AVA = RP_TSuppl[TS_RIT_VISIERA_AVA];

COMP_PRES				= CONF_VIS_BASSA;   
FUNZ_MANUALE			= FUNZ_MAN100;
MAN_1					= ( (FUNZ_MAN100 || FUNZ_MAN02) && COMANDO_AUX_B )   && !AP_RIPARO_DA_BORDO_PREM;
MAN_2					= ( (FUNZ_MAN100 || FUNZ_MAN02) && COMANDO_AUX_A )   ||  AP_RIPARO_DA_BORDO_PREM;
M_1						= ( Mg_MC(311) || PLCMg_MC(311) || FORZA_RIPARI_CH ) && !AP_RIPARO_DA_BORDO_PREM;
M_2						= ( Mg_MC(310) || PLCMg_MC(310) || FORZA_RIPARI_AP ) ||  AP_RIPARO_DA_BORDO_PREM;
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 2; // 2=> l'uscita rimane a 1 anche se cade l'ingresso, altrimenti si resetterebbe l'autoritenuta e la visiera si sposterebbe con rischio per un eventuale operatore che vi stia facendo manutenzione (data la presenza di un EV monostabile)
COND_MACCHINA_1			= COND_CH_VIS_BAS;    // VISIERA BASSA: Condizione x eseguire il movimento 1 (chiusura)
COND_MACCHINA_2			= COND_AP_VIS_BAS;    // VISIERA BASSA: Condizione x eseguire il movimento 2 (apertura)
DIAGNOSTICA_2_IN		= 1;

OUTPUT_1				= VISIERA_IND_O;      // Arretramento Visiera bassa (chiusura visiera oriz.)
OUTPUT_2				= !VISIERA_IND_O;     // Avanzamento  Visiera bassa (apertura visiera oriz.)
INPUT_1					= APP_RIT_VISIERA_IND;
INPUT_2					= APP_RIT_VISIERA_AVA;

COND_ALL_1				= !VISIERA_IND_I;	// Condizione anomala nel movimento 1
COND_ALL_2				= !VISIERA_AVA_I;	// Condizione anomala nel movimento 2
COND_DISF				= INPUT_1 && INPUT_2;
TIMEOUT_ALL_1			= RP_TSuppl[TS_TIMEOUT_VIS_IND];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= RP_TSuppl[TS_TIMEOUT_VIS_AVA];	// Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= BITON;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= VIS_BASSA_NOIND_A_FAL;
OUTPUT_1B_FAL			= VIS_BASSA_NOIND_B_FAL;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= VIS_BASSA_NOAVA_A_FAL;
OUTPUT_2B_FAL			= VIS_BASSA_NOAVA_B_FAL;
DISFUNZIONE_FAL			= VIS_BASSA_DISFC_FAL;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_58;
uscite_standard ();
COMPONENTE_58			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	VISIERA_IND_O =		OUTPUT_1; // Arretramento Visiera bassa (chiusura visiera oriz.)
	//VISIERA_AVA_O =	OUTPUT_2; // il movimento di avanzamento è stato eliminato (ora è monostabile)
}
else	// se si disattiva la visiera orizzontale, ma è presente fisicamente, occorre tenerla fuori ingombro dal riparo
{
	VISIERA_IND_O = BITOFF;
	//VISIERA_AVA_O = BITON;
}

if (!M_1)
{
	Mr_MC(311);
	PLCMr_MC(311);
}
if (!M_2)
{
	Mr_MC(310);
	PLCMr_MC(310);
}

//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
VIS_BASSA_NOIND_A_FAL =	OUTPUT_1A_FAL;
VIS_BASSA_NOIND_B_FAL =	OUTPUT_1B_FAL;

//DIS_£_FAL =	OUTPUT_2_FAL;
VIS_BASSA_NOAVA_A_FAL =	OUTPUT_2A_FAL;
VIS_BASSA_NOAVA_B_FAL =	OUTPUT_2B_FAL;

VIS_BASSA_DISFC_FAL =	DISFUNZIONE_FAL;

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{
	AVA_VISIERA_BASSA = (int) !VISIERA_IND_O; VISIERA_BASSA_AVA = (int) VISIERA_AVA_I;
	count (&AVA_VISIERA_BASSA, &VISIERA_BASSA_AVA, &VISIERA_BASSA_AVA_COUNT, &VISIERA_BASSA_AVA_MEMCOUNT, &VISIERA_BASSA_AVA_MEM, R_VISIERA_BASSA_AVA, AVA_VISIERA_BASSA_COMMENTO);

	IND_VISIERA_BASSA = (int) VISIERA_IND_O; VISIERA_BASSA_IND = (int) VISIERA_IND_I;
	count (&IND_VISIERA_BASSA, &VISIERA_BASSA_IND, &VISIERA_BASSA_IND_COUNT, &VISIERA_BASSA_IND_MEMCOUNT, &VISIERA_BASSA_IND_MEM, R_VISIERA_BASSA_IND, IND_VISIERA_BASSA_COMMENTO);
}

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 58) 
			{	
			goto saltauscite;
			}	

			

//******************************************************************************
//**************************** Componente 59 ***********************************
//******************************************************************************
//**************************** VISIERA BASSA DX ********************************
//************************* movimento AVA / IND ********************************
//******************************************************************************

//**************** ELIMINATO ******************************	



//******************************************************************************
//**************************** Componente 60 ***********************************
//******************************************************************************
//**************************** VISIERA ALTA SX *********************************
//************************* movimento SAL / DIS ********************************
//******************************************************************************

if(R[R_DISAB_RIPARI_FIERA]>0.5)  //Disabilita apertura riparo in automatico
{
	Mr_MC(312);
	PLCMr_MC(312);
	Mr_MC(313);
	PLCMr_MC(313);
}

COMP_PRES				= CONF_VIS_ALTA;   
FUNZ_MANUALE			= FUNZ_MAN101;
MAN_1					= ( (FUNZ_MAN101 || FUNZ_MAN02) && COMANDO_AUX_B )   && !AP_RIPARO_DA_BORDO_PREM;
MAN_2					= ( (FUNZ_MAN101 || FUNZ_MAN02) && COMANDO_AUX_A )   ||  AP_RIPARO_DA_BORDO_PREM;
M_1						= ( Mg_MC(313) || PLCMg_MC(313) || FORZA_RIPARI_CH ) && !AP_RIPARO_DA_BORDO_PREM;
M_2						= ( Mg_MC(312) || PLCMg_MC(312) || FORZA_RIPARI_AP ) ||  AP_RIPARO_DA_BORDO_PREM;
M_0						= 0;

RESET_CONDAUTO			= RESET_MC;
AUTORITENUTA			= 1;
COND_MACCHINA_1			= COND_CH_VIS_ALT;      // VISIERA ALTA: Condizione x eseguire il movimento 1 (chiusura)
COND_MACCHINA_2			= COND_AP_VIS_ALT;      // VISIERA ALTA: Condizione x eseguire il movimento 2 (apertura)
DIAGNOSTICA_2_IN		= 1;

OUTPUT_1				= VIS_RIP_SAL_O;		// Salita visiera riparo  (chiusura visiera vertic.) 
OUTPUT_2				= VIS_RIP_DIS_O;		// Discesa visiera riparo (apertura visiera vertic.) 
INPUT_1					= RIP_ANT_CH_SICUR_I;
INPUT_2					= RP_TSuppl[TS_VIS_RIP_DIS];

COND_ALL_1				= !RIP_ANT_CH_SICUR_I && (APPO_RIPARO_CH_INP || !CONF_RIPARO_ANT);  // Condizione anomala nel movimento 1
COND_ALL_2				= RIP_ANT_CH_SICUR_I;                                               // Condizione anomala nel movimento 2
COND_DISF				= 0;
TIMEOUT_ALL_1			= RP_TSuppl[TS_TIMEOUT_VIS_SAL];  // Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_ALL_2			= RP_TSuppl[TS_TIMEOUT_VIS_DIS];  // Tempo dopo il quale verifica l'assenza della condizione anomala
TIMEOUT_DISF			= BITON;

OUTPUT_1_FAL			= 0;	// INS_£_FAL;
OUTPUT_1A_FAL			= VIS_RIP_NOSAL_A_FAL;
OUTPUT_1B_FAL			= VIS_RIP_NOSAL_B_FAL;
OUTPUT_2_FAL			= 0;	// DIS_£_FAL;
OUTPUT_2A_FAL			= VIS_RIP_NODIS_A_FAL;
OUTPUT_2B_FAL			= VIS_RIP_NODIS_B_FAL;
DISFUNZIONE_FAL			= 0;

//**** Elaborazione comune *****************************************************
COMPONENTE_WORD			= COMPONENTE_60;
uscite_standard ();
COMPONENTE_60			= COMPONENTE_WORD;

//**** Gestione uscite e funzioni "M" ***********************************************
if (COMP_PRES)
{
	VIS_RIP_SAL_O =		OUTPUT_1;  // Sollevamento visiera riparo (chisura visiera)
	VIS_RIP_DIS_O =		OUTPUT_2;  // Discesa visiera riparo (apertura visiera)
}
if (!M_1)
{
	Mr_MC(313);
	PLCMr_MC(313);
}
if (!M_2)
{
	Mr_MC(312);
	PLCMr_MC(312);
}

//**** Messaggi e Allarmi ***********************************************************
//INS_£_FAL =	OUTPUT_1_FAL;
VIS_RIP_NOSAL_A_FAL =	OUTPUT_1A_FAL;
VIS_RIP_NOSAL_B_FAL =	OUTPUT_1B_FAL;

//DIS_£_FAL =	OUTPUT_2_FAL;
VIS_RIP_NODIS_A_FAL =	OUTPUT_2A_FAL;
VIS_RIP_NODIS_B_FAL =	OUTPUT_2B_FAL;

//VIS_RIP_SX_DISFC_FAL =	DISFUNZIONE_FAL;

// Hold Componente per mancanza condizioni di funzionamento 
//HOLD_£_FMS = HOLD_COMPONENTE;

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{
	SAL_VIS_RIP = (int) VIS_RIP_SAL_O; VIS_RIP_SAL = (int) RIP_ANT_CH_SICUR_I;
	count (&SAL_VIS_RIP, &VIS_RIP_SAL, &VIS_RIP_SAL_COUNT, &VIS_RIP_SAL_MEMCOUNT, &VIS_RIP_SAL_MEM, R_VIS_RIP_SAL, SAL_VIS_RIP_COMMENTO);

	DIS_VIS_RIP = (int) VIS_RIP_DIS_O; VIS_RIP_DIS = (int) !RIP_ANT_CH_SICUR_I;
	count (&DIS_VIS_RIP, &VIS_RIP_DIS, &VIS_RIP_DIS_COUNT, &VIS_RIP_DIS_MEMCOUNT, &VIS_RIP_DIS_MEM, R_VIS_RIP_DIS, DIS_VIS_RIP_COMMENTO);
}

// Serve per debuggare di volta in volta il componenete selezionato dal par.R
if  (R[R_DEBUG_COMPONENTI] == (float) 60) 
			{	
			goto saltauscite;
			}	



//******************************************************************************
//**************************** Componente 61 ***********************************
//******************************************************************************
//**************************** VISIERA ALTA DX *********************************
//************************* movimento SAL / DIS ********************************
//******************************************************************************

//**************** ELIMINATO ******************************	


//////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// Fine Uscite ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////




saltauscite:;


} // ENDOUT *********************************************************************

