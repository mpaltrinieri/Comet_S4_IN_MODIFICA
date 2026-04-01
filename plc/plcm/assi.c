/* 

*************************************************************************************************************************************************************************************************
NB: FILE MODIFICATO IN MODO CHE I VARI ASSI SIANO VERIFICABILI FACILMENTE RICERCANDO (CON F3) FLAG ANALOGHI PRESENTI NEI VARI ASSI, 
EFFETTUARE EVENTUALI MODIFICHE SENZA ALTERARE QUESTA POSSIBILITA'
*************************************************************************************************************************************************************************************************

        --------------------------------------------------------------
        TITOLO:         ASSI
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione Assi in modo standard
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    assi(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          DRIVE*_OK_I      Drive asse * ok
                        O_MCR(*)         Micro zero asse *
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         ABIL_*_O          Abilitazione drive asse *

                        DRIVE*_NOK_AL     All. drive asse * non ok
                        DRIVE*_NOK_FAL    Flag drive asse * non ok
							ASSE*_NORIF       Asse * non riferito
                        COM_AVANTI_*      Comando avanti asse *
                        COM_INDIETRO_*    Comando indietro asse *
                        ASSE*_IN_ALLARME  Asse * in allarme
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           01/12/2005-----------------------------
        --------------------------------------------------------------
        AUTORI:         Borsari G.
        ---------------------------------
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"

int COM_AVANTI		[MAX_NUM_CHANNEL][ASSE_NULLO] = {0};
int COM_INDIETRO	[MAX_NUM_CHANNEL][ASSE_NULLO] = {0};
int ARR_AVANTI		[MAX_NUM_CHANNEL][ASSE_NULLO] = {0};
int ARR_INDIETRO	[MAX_NUM_CHANNEL][ASSE_NULLO] = {0};
int ASSE_NORIF		[MAX_NUM_CHANNEL][ASSE_NULLO] = {0};
int ASSE_CANOPEN	[MAX_NUM_CHANNEL][ASSE_NULLO] = {0};


/******************* Variabili d'utilizzo **********************/
extern BOOL COND_AVA_EXC, COND_IND_EXC;
extern int DO_PWR_K1;

STASSI STATO_ASSI;

short ASSE_AXGEN;
short NUM_CHANNEL_AXGEN;       //numero canale a cui appartiene l'asse al momento
short NUM_CHANNEL_PROPR_AXGEN; //numero canale proprietario dell'asse
short NUM_ASSE_AXGEN_IN_CHANNEL_PROPR; //numero asse generico nel canale proprietario dell'asse
int RIT_DISABI_AXGEN, RIT_SFRENO1_AXGEN, RIT_SFRENO2_AXGEN, RIT_IBLM1_AXGEN, RIT_IBLM2_AXGEN;
int TIME_AXGEN, FUNZ_MAN_INC_AXGEN, FUNZ_MAN_JOG_AXGEN;
int TIMEOUT_DRIVE_AXGEN_NOK, TERM_AXGEN_NOK_FAL;
int FCZERO_INIZ_AXGEN, FCZERO_FINE_AXGEN;

int TIME_ARR_AXGEN;

float POS_ATTUALE_AXGEN, QUOTA_FCPOS_AXGEN, QUOTA_FCNEG_AXGEN, POS_TARGET_AXGEN, DIST_AXGEN;

float POS_OLD_AXGEN, QUOTA_G53_AXGEN;
float INSEGUIMENTO_AXGEN;


int TIME_X, TIME_Y, TIME_Z, TIME_A, TIME_C, TIME_W;
int TIME_M10, TIME_M11, TIME_M12, TIME_M13, TIME_M14, TIME_M15;

int RIT_SFRENO1_X,	RIT_SFRENO1_Y,	RIT_SFRENO1_Z,	RIT_SFRENO1_A,	RIT_SFRENO1_C,	RIT_SFRENO1_W;
int RIT_SFRENO1_M10, RIT_SFRENO1_M11, RIT_SFRENO1_M12, RIT_SFRENO1_M13, RIT_SFRENO1_M14, RIT_SFRENO1_M15;

int RIT_SFRENO2_X,	RIT_SFRENO2_Y,	RIT_SFRENO2_Z,	RIT_SFRENO2_A,	RIT_SFRENO2_C,	RIT_SFRENO2_W;
int RIT_SFRENO2_M10, RIT_SFRENO2_M11, RIT_SFRENO2_M12, RIT_SFRENO2_M13, RIT_SFRENO2_M14, RIT_SFRENO2_M15;

int RIT_DISABI_X,	RIT_DISABI_Y,	RIT_DISABI_Z,	RIT_DISABI_A,	RIT_DISABI_C,	RIT_DISABI_W;
int RIT_DISABI_M10,	RIT_DISABI_M11, RIT_DISABI_M12, RIT_DISABI_M13,	RIT_DISABI_M14,	RIT_DISABI_M15;

int RIT_IBLM1_X,	RIT_IBLM1_Y,	RIT_IBLM1_Z,	RIT_IBLM1_A,	RIT_IBLM1_C,	RIT_IBLM1_W;
int RIT_IBLM1_M10,	RIT_IBLM1_M11,  RIT_IBLM1_M12,  RIT_IBLM1_M13,	RIT_IBLM1_M14,	RIT_IBLM1_M15;

int RIT_IBLM2_X,	RIT_IBLM2_Y,	RIT_IBLM2_Z,	RIT_IBLM2_A,	RIT_IBLM2_C,	RIT_IBLM2_W;
int RIT_IBLM2_M10,	RIT_IBLM2_M11,	RIT_IBLM2_M12,	RIT_IBLM2_M13,	RIT_IBLM2_M14,	RIT_IBLM2_M15;

int TIME_ARR_X,		TIME_ARR_Y,		TIME_ARR_Z,		TIME_ARR_A,		TIME_ARR_C,		TIME_ARR_W;
int	TIME_ARR_M10,	TIME_ARR_M11,	TIME_ARR_M12,	TIME_ARR_M13,	TIME_ARR_M14,	TIME_ARR_M15;

/***************************************************************/



void assi(void)
{

int Ind1 = 0;
int Ind2 = 0;

// goto saltaassi;	// 


// RESET ALLARMI DRIVE NON ABILITATI ///////////
if (RESET_ALL || RESET_MC)
{
}

// PER GLI ASSI CONDIVISI: 
// come richisto da Stefano Giusti e realizzato sul PLC della prima macchina (CS6) in cui si è risolto il problema degli assi condivisi comandati mentre non eran temporaneamente associati ad alcun canale,
// anche il PLC della CS4 non invia comandi agli assi quando non son piu associati a nessun canale,
// non continua ad inviargli comandi sull'ultimo canale a cui erano associati, 
// quindi non serve inizializzare e aggiornare memorie degli ultimi canali che han gestito questi assi.


if(RESET_MC)
{
	    RIC_LSR_MORS_10 =     RIC_LSR_MORS_11 =     RIC_LSR_MORS_12 =     RIC_LSR_MORS_13 =     RIC_LSR_MORS_14 =     RIC_LSR_MORS_15 = 0;
	RIC_DIS_LSR_MORS_10 = RIC_DIS_LSR_MORS_11 = RIC_DIS_LSR_MORS_12 = RIC_DIS_LSR_MORS_13 = RIC_DIS_LSR_MORS_14 = RIC_DIS_LSR_MORS_15 = 0;

	FORZA_ABIL_MORSA_10 = FORZA_ABIL_MORSA_11 = FORZA_ABIL_MORSA_12 = FORZA_ABIL_MORSA_13 = FORZA_ABIL_MORSA_14 = FORZA_ABIL_MORSA_15 = 0;
}


// Dichiarazione dei timer di ritardo per il reset delle funzioni ausiliarie di forzatura abilitazione morse:
tS(TS_RIT_ABIL_MORSE_M210, (unsigned char) Mg_MC(210) );	// M210 Forza abilitazione delle morse del CH2 nella MOVPIECE

// Reset funzioni ausiliarie di forzatura abilitazione morse
	
if( (RP_TSuppl[TS_RIT_ABIL_MORSE_M210]) ||
	(
	( (FORZA_ABIL_MORSA_10 && (ABS(R[R_INSEGUIMENTO_M10])<0.1)) ||  !FORZA_ABIL_MORSA_10 || !CONF_ASSE_M10) &&
	( (FORZA_ABIL_MORSA_11 && (ABS(R[R_INSEGUIMENTO_M11])<0.1)) ||  !FORZA_ABIL_MORSA_11 || !CONF_ASSE_M11) &&
	( (FORZA_ABIL_MORSA_12 && (ABS(R[R_INSEGUIMENTO_M12])<0.1)) ||  !FORZA_ABIL_MORSA_12 || !CONF_ASSE_M12) &&
	
	( (FORZA_ABIL_MORSA_13 && (ABS(R[R_INSEGUIMENTO_M13])<0.1)) ||  !FORZA_ABIL_MORSA_13 || !CONF_ASSE_M13) &&
	( (FORZA_ABIL_MORSA_14 && (ABS(R[R_INSEGUIMENTO_M14])<0.1)) ||  !FORZA_ABIL_MORSA_14 || !CONF_ASSE_M14) &&
	( (FORZA_ABIL_MORSA_15 && (ABS(R[R_INSEGUIMENTO_M15])<0.1)) ||  !FORZA_ABIL_MORSA_15 || !CONF_ASSE_M15) 
	)  )
	Mr_MC(210);

// Azzeramento vettori gestione assi ************************************************
for(Ind1=0;Ind1<MAX_NUM_CHANNEL;Ind1++)
{
	for (Ind2=0;Ind2<ASSE_NULLO;Ind2++)
	{
		COM_AVANTI[Ind1][Ind2] = 0;
		COM_INDIETRO[Ind1][Ind2] = 0;
		ARR_AVANTI[Ind1][Ind2] = 0;
		ARR_INDIETRO[Ind1][Ind2] = 0;
		ASSE_NORIF[Ind1][Ind2] = 0;
		ASSE_CANOPEN[Ind1][Ind2] = 0;
	}
}


MEM_JPOS_AXGEN = 0;				// Reset iniziale Flag assi in mov. (non spostare questa riga)
MEM_JNEG_AXGEN = 0;				// Reset iniziale Flag assi in mov. (non spostare questa riga)
MEM_DRIVE_AXGEN_NOK_FAL = 0;	// Reset iniziale Flag anomalie azion. assi (non spostare questa riga)


// Gestione sbloccaggio assi CanOpen ************************************************


// Caricamento valori Target assi del CNC Slave
R[R_POS_TARGET_M10] =	R[R_CNC1_TARGET_M10];
R[R_POS_TARGET_M11] =	R[R_CNC1_TARGET_M11];
R[R_POS_TARGET_M12] =	R[R_CNC1_TARGET_M12];
R[R_POS_TARGET_M13] =	R[R_CNC1_TARGET_M13];
R[R_POS_TARGET_M14] =	R[R_CNC1_TARGET_M14];
R[R_POS_TARGET_M15] =	R[R_CNC1_TARGET_M15];



QuotaRaggiunta_X = ( (R[R_POS_ATTUALE_X] > (R[R_POS_TARGET_X]-R[R_TOLL])) && 
				     (R[R_POS_ATTUALE_X] < (R[R_POS_TARGET_X]+R[R_TOLL])) || !CONF_ASSE_X);

QuotaRaggiunta_Y = ( (R[R_POS_ATTUALE_Y] > (R[R_POS_TARGET_Y]-R[R_TOLL])) && 
				     (R[R_POS_ATTUALE_Y] < (R[R_POS_TARGET_Y]+R[R_TOLL])) || !CONF_ASSE_Y);

QuotaRaggiunta_Z = ( (R[R_POS_ATTUALE_Z] > (R[R_POS_TARGET_Z]-R[R_TOLL])) && 
				     (R[R_POS_ATTUALE_Z] < (R[R_POS_TARGET_Z]+R[R_TOLL])) || !CONF_ASSE_Z);

QuotaRaggiunta_A = ( (R[R_POS_ATTUALE_A] > (R[R_POS_TARGET_A]-R[R_TOLL])) && 
				     (R[R_POS_ATTUALE_A] < (R[R_POS_TARGET_A]+R[R_TOLL])) || !CONF_ASSE_A);

QuotaRaggiunta_C = ( (R[R_POS_ATTUALE_C] > (R[R_POS_TARGET_C]-R[R_TOLL])) && 
				     (R[R_POS_ATTUALE_C] < (R[R_POS_TARGET_C]+R[R_TOLL])) || !CONF_ASSE_C);

QuotaRaggiunta_W = ( (R[R_POS_ATTUALE_W] > (R[R_POS_TARGET_W]-R[R_TOLL])) && 
				     (R[R_POS_ATTUALE_W] < (R[R_POS_TARGET_W]+R[R_TOLL])) || !CONF_ASSE_W);


QuotaRaggiunta_M10 = ( (R[R_POS_ATTUALE_M10] > (R[R_POS_TARGET_M10]-R[R_TOLL])) && 
					   (R[R_POS_ATTUALE_M10] < (R[R_POS_TARGET_M10]+R[R_TOLL])) || !CONF_ASSE_M10);

QuotaRaggiunta_M11 = ( (R[R_POS_ATTUALE_M11] > (R[R_POS_TARGET_M11]-R[R_TOLL])) && 
					   (R[R_POS_ATTUALE_M11] < (R[R_POS_TARGET_M11]+R[R_TOLL])) || !CONF_ASSE_M11);

QuotaRaggiunta_M12 = ( (R[R_POS_ATTUALE_M12] > (R[R_POS_TARGET_M12]-R[R_TOLL])) && 
					  (R[R_POS_ATTUALE_M12] < (R[R_POS_TARGET_M12]+R[R_TOLL])) || !CONF_ASSE_M12);

QuotaRaggiunta_M13 = ( (R[R_POS_ATTUALE_M13] > (R[R_POS_TARGET_M13]-R[R_TOLL])) && 
					   (R[R_POS_ATTUALE_M13] < (R[R_POS_TARGET_M13]+R[R_TOLL])) || !CONF_ASSE_M13);

QuotaRaggiunta_M14 = ( (R[R_POS_ATTUALE_M14] > (R[R_POS_TARGET_M14]-R[R_TOLL])) && 
					   (R[R_POS_ATTUALE_M14] < (R[R_POS_TARGET_M14]+R[R_TOLL])) || !CONF_ASSE_M14);

QuotaRaggiunta_M15 = ( (R[R_POS_ATTUALE_M15] > (R[R_POS_TARGET_M15]-R[R_TOLL])) && 
					   (R[R_POS_ATTUALE_M15] < (R[R_POS_TARGET_M15]+R[R_TOLL])) || !CONF_ASSE_M15);


/** Tutti gli assi morse V1-V12 sono in posizione **/

QuoteRaggiunte = (
				  QuotaRaggiunta_M10 && 
				  QuotaRaggiunta_M11 && 
				  QuotaRaggiunta_M12 &&
				  QuotaRaggiunta_M13 && 
				  QuotaRaggiunta_M14 && 
				  QuotaRaggiunta_M15
				 );


QuoteRaggiunte_SX = (
				  QuotaRaggiunta_M10 && 
				  QuotaRaggiunta_M11 && 
				  QuotaRaggiunta_M12
				 );


QuoteRaggiunte_DX = (
				  QuotaRaggiunta_M13 && 
				  QuotaRaggiunta_M14 && 
				  QuotaRaggiunta_M15
				 );


/////////////////////////////////////////////////////////////////////////////////////
// Verifica caduta O_MOT con quote errate degli assi slave lmd 

if (O_MOT_M10 && !MEM_O_MOT_M10)  R[R_MORSA_10_MOSSA_CNT] += 1;    if(RESET_ALL) R[R_MORSA_10_MOSSA_CNT] = 0;
if (O_MOT_M11 && !MEM_O_MOT_M11)  R[R_MORSA_11_MOSSA_CNT] += 1;    if(RESET_ALL) R[R_MORSA_11_MOSSA_CNT] = 0;
if (O_MOT_M12 && !MEM_O_MOT_M12)  R[R_MORSA_12_MOSSA_CNT] += 1;    if(RESET_ALL) R[R_MORSA_12_MOSSA_CNT] = 0;
if (O_MOT_M13 && !MEM_O_MOT_M13)  R[R_MORSA_13_MOSSA_CNT] += 1;    if(RESET_ALL) R[R_MORSA_13_MOSSA_CNT] = 0;
if (O_MOT_M14 && !MEM_O_MOT_M14)  R[R_MORSA_14_MOSSA_CNT] += 1;    if(RESET_ALL) R[R_MORSA_14_MOSSA_CNT] = 0;
if (O_MOT_M15 && !MEM_O_MOT_M15)  R[R_MORSA_15_MOSSA_CNT] += 1;    if(RESET_ALL) R[R_MORSA_15_MOSSA_CNT] = 0;

QuotaErrata_M10 = ( ( fabs(R[R_POS_ATTUALE_M10]  - R[R_POS_TARGET_M10] ) ) > R[R_TOLL] ) && CONF_ASSE_M10;
QuotaErrata_M11 = ( ( fabs(R[R_POS_ATTUALE_M11]  - R[R_POS_TARGET_M11] ) ) > R[R_TOLL] ) && CONF_ASSE_M11;
QuotaErrata_M12 = ( ( fabs(R[R_POS_ATTUALE_M12]  - R[R_POS_TARGET_M12] ) ) > R[R_TOLL] ) && CONF_ASSE_M12;
QuotaErrata_M13 = ( ( fabs(R[R_POS_ATTUALE_M13]  - R[R_POS_TARGET_M13] ) ) > R[R_TOLL] ) && CONF_ASSE_M13;
QuotaErrata_M14 = ( ( fabs(R[R_POS_ATTUALE_M14]  - R[R_POS_TARGET_M14] ) ) > R[R_TOLL] ) && CONF_ASSE_M14;
QuotaErrata_M15 = ( ( fabs(R[R_POS_ATTUALE_M15]  - R[R_POS_TARGET_M15] ) ) > R[R_TOLL] ) && CONF_ASSE_M15;


// Assi morse fermi in posizioni errate (bit della word: MORSE_FERME_ERR)
MORSA_10_FERMA_ERR = CONF_ASSE_M10 && QuotaErrata_M10 && MEM_O_MOT_M10 && !O_MOT_M10;
MORSA_11_FERMA_ERR = CONF_ASSE_M11 && QuotaErrata_M11 && MEM_O_MOT_M11 && !O_MOT_M11;
MORSA_12_FERMA_ERR = CONF_ASSE_M12 && QuotaErrata_M12 && MEM_O_MOT_M12 && !O_MOT_M12;
MORSA_13_FERMA_ERR = CONF_ASSE_M13 && QuotaErrata_M13 && MEM_O_MOT_M13 && !O_MOT_M13;
MORSA_14_FERMA_ERR = CONF_ASSE_M14 && QuotaErrata_M14 && MEM_O_MOT_M14 && !O_MOT_M14;
MORSA_15_FERMA_ERR = CONF_ASSE_M15 && QuotaErrata_M15 && MEM_O_MOT_M15 && !O_MOT_M15;

if (MORSA_10_FERMA_ERR) MORSA_10_FERMA_CNT += 1;  if(RESET_ALL) MORSA_10_FERMA_CNT = 0;
if (MORSA_11_FERMA_ERR) MORSA_11_FERMA_CNT += 1;  if(RESET_ALL) MORSA_11_FERMA_CNT = 0;
if (MORSA_12_FERMA_ERR) MORSA_12_FERMA_CNT += 1;  if(RESET_ALL) MORSA_12_FERMA_CNT = 0;
if (MORSA_13_FERMA_ERR) MORSA_13_FERMA_CNT += 1;  if(RESET_ALL) MORSA_13_FERMA_CNT = 0;
if (MORSA_14_FERMA_ERR) MORSA_14_FERMA_CNT += 1;  if(RESET_ALL) MORSA_14_FERMA_CNT = 0;
if (MORSA_15_FERMA_ERR) MORSA_15_FERMA_CNT += 1;  if(RESET_ALL) MORSA_15_FERMA_CNT = 0;


MEM_O_MOT_M10 = O_MOT_M10;
MEM_O_MOT_M11 = O_MOT_M11;
MEM_O_MOT_M12 = O_MOT_M12;
MEM_O_MOT_M13 = O_MOT_M13;
MEM_O_MOT_M14 = O_MOT_M14;
MEM_O_MOT_M15 = O_MOT_M15;


if (CONF_ASSE_M10) O_LSR_M10 = ( (unsigned short)O_LSR_CH2(AX_M10_CH2) );
if (CONF_ASSE_M11) O_LSR_M11 = ( (unsigned short)O_LSR_CH2(AX_M11_CH2) );
if (CONF_ASSE_M12) O_LSR_M12 = ( (unsigned short)O_LSR_CH2(AX_M12_CH2) );
if (CONF_ASSE_M13) O_LSR_M13 = ( (unsigned short)O_LSR_CH2(AX_M13_CH2) );
if (CONF_ASSE_M14) O_LSR_M14 = ( (unsigned short)O_LSR_CH2(AX_M14_CH2) );
if (CONF_ASSE_M15) O_LSR_M15 = ( (unsigned short)O_LSR_CH2(AX_M15_CH2) );


if (CONF_ASSE_M10) O_AGG_M10 = ( (unsigned short)O_AGG_CH2(AX_M10_CH2) );
if (CONF_ASSE_M11) O_AGG_M11 = ( (unsigned short)O_AGG_CH2(AX_M11_CH2) );
if (CONF_ASSE_M12) O_AGG_M12 = ( (unsigned short)O_AGG_CH2(AX_M12_CH2) );
if (CONF_ASSE_M13) O_AGG_M13 = ( (unsigned short)O_AGG_CH2(AX_M13_CH2) );
if (CONF_ASSE_M14) O_AGG_M14 = ( (unsigned short)O_AGG_CH2(AX_M14_CH2) );
if (CONF_ASSE_M15) O_AGG_M15 = ( (unsigned short)O_AGG_CH2(AX_M15_CH2) );



/////////////////////////////////////////////////////////////////////////////////////




// Appoggio segnale per I_ANN assi CANOPEN ZONA SX e DX - e zona comune
APPOGGIO_I_ANN_COM	= !NO_EMERG_I;


// Resetto attesa ripristino per JOG o allarme 
if (!M_HOLD && !ALLARMI_PRES || RESET_MC)
		{
		Mr_MC(100);
		}


// Almeno un drive in allarme per gestione allarmi
ALMENO_UN_DRIVE_IN_ALLARME =	DRIVE_X_NOK_FAL		||
								DRIVE_Y_NOK_FAL		||
								DRIVE_Z_NOK_FAL		||
								DRIVE_A_NOK_FAL		||
								DRIVE_C_NOK_FAL		||
								DRIVE_W_NOK_FAL		||
								DRIVE_M10_NOK_FAL	||
								DRIVE_M11_NOK_FAL	||
								DRIVE_M12_NOK_FAL	||
								DRIVE_M13_NOK_FAL	||
								DRIVE_M14_NOK_FAL	||
								DRIVE_M15_NOK_FAL;
								



// VERIFICA ASSOCIAZIONI / DISASSOCIAZIONI ASSI AI/DAI CANALI (DIAGNOSTICA SEMPRE ATTIVA) ////////////////////////////////////////////////////////////

	// VERIFICA DISASSOCIAZIONE ASSI DAI CANALI (SH_OFF_N.CS4)
	if (Mg_MC(353))   { rilascio_AX_W = 1; }
	
	if(rilascio_AX_W && !mem_rilascio_AX_W) {R[R_CONT_DISA_DA_PP_W]++;}   if( (R[R_CONT_DISA_DA_PP_W]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) {R[R_CONT_DISA_DA_PP_W] = 0;}
	
	mem_rilascio_AX_W = rilascio_AX_W;


	// VERIFICA ASSOCIAZIONE ASSI AI CANALI (SH_ON_N.CS4)
	if (Mg_MC(357))   { rilascio_AX_W = 0; }
	
	if(!rilascio_AX_W && mem_rilascio_AX_W) {R[R_CONT_ASSO_DA_PP_W]++;}   if( (R[R_CONT_ASSO_DA_PP_W]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) {R[R_CONT_ASSO_DA_PP_W] = 0;}
	
	mem_rilascio_AX_W = rilascio_AX_W;

// DISABILITAZIONE ASSI PER CAMBIO CH ////////////////////////////////////////////////////////////////////////////////

if ( (R[R_GEST_DIS_ATT_ABIL]<0.5) || RESET_MC )						// R_GEST_DIS_ATT_ABIL = 0
{
	// Reset Disattivazione Abilitazione assi 
	Disab_AX_X = 0;
	Disab_AX_Y = 0;
	Disab_AX_Z = 0;
	Disab_AX_A = 0;
	Disab_AX_W = 0;
	Disab_AX_C = 0;

	// Reset M di Disattivazione Abilitazione assi
	Mr_MC(353);	
	
	// Reset M di Riattivazione Abilitazione assi
	Mr_MC(357);	
}

if ( (R[R_GEST_DIS_ATT_ABIL]>0.5) && (R[R_GEST_DIS_ATT_ABIL]<1.5) )		// R_GEST_DIS_ATT_ABIL = 1		(Gestione suggerita da A.Denardis)
{
	// Disattivazione Abilitazione assi all'inizio di SH_OFF_n.CS4
	if (Mg_MC(353))   { Disab_AX_W = 1; }

	// Riattivazione Abilitazione assi alla fine di SH_OFF_n.CS4
	if (Mg_MC(357))   { Disab_AX_W = 0; }
		
	// Reset M di Disattivazione Abilitazione assi
	if(!ABIL_W && !DO_SON_W)  {Mr_MC(353);}	

	// Reset M di Riattivazione Abilitazione assi
	Mr_MC(357);	
}

if ( (R[R_GEST_DIS_ATT_ABIL]>1.5) && (R[R_GEST_DIS_ATT_ABIL]<2.5) )		// R_GEST_DIS_ATT_ABIL = 2
{
	// if ritardo_di(rich_abil_plc && !asse_abil && !o_mov_asse)   Disab_AX_X = 1;
	// if ritardo_di_3sec_di(Disab_AX_X)                           Disab_AX_X = 0;

		// #define TS_ALL_RIPARO_SX_AP			1  // Temporizza Riparo Anteriore SX Apertura
		// TS1  = 10000  {Timeout Allarme Riparo Anteriore SX Apertura  | Front LH Guard Opening Alarm Timeout
		// tS(TS_ALL_RIPARO_SX_AP			, (unsigned char)(START_INV_RIPARO_SX_O));
		// if (RP_TSuppl[TS_ALL_RIPARO_SX_AP] && !RP_TSuppl[TS_RIPARO_SX_AP] && AUX_INSER_I)

	cond_START_RES_ABIL_AX_X = (ABIL_X && !DO_SON_X && !O_MOV_X && !rp_STOP_RES_ABIL_AX_X);
	cond_START_RES_ABIL_AX_Y = (ABIL_Y && !DO_SON_Y && !O_MOV_Y && !rp_STOP_RES_ABIL_AX_Y);
	cond_START_RES_ABIL_AX_Z = (ABIL_Z && !DO_SON_Z && !O_MOV_Z && !rp_STOP_RES_ABIL_AX_Z);
	cond_START_RES_ABIL_AX_A = (ABIL_A && !DO_SON_A && !O_MOV_A && !rp_STOP_RES_ABIL_AX_A);
	cond_START_RES_ABIL_AX_W = (ABIL_W && !DO_SON_W && !O_MOV_W && !rp_STOP_RES_ABIL_AX_W);
	cond_START_RES_ABIL_AX_C = (ABIL_C && !DO_SON_C && !O_MOV_C && !rp_STOP_RES_ABIL_AX_C);


	tS(TS_START_RES_ABIL_AX_X, (unsigned char)(cond_START_RES_ABIL_AX_X));
	tS(TS_START_RES_ABIL_AX_Y, (unsigned char)(cond_START_RES_ABIL_AX_Y));
	tS(TS_START_RES_ABIL_AX_Z, (unsigned char)(cond_START_RES_ABIL_AX_Z));
	tS(TS_START_RES_ABIL_AX_A, (unsigned char)(cond_START_RES_ABIL_AX_A));
	tS(TS_START_RES_ABIL_AX_W, (unsigned char)(cond_START_RES_ABIL_AX_W));
	tS(TS_START_RES_ABIL_AX_C, (unsigned char)(cond_START_RES_ABIL_AX_C));


	rp_START_RES_ABIL_AX_X = RP_TSuppl[TS_START_RES_ABIL_AX_X];
	rp_START_RES_ABIL_AX_Y = RP_TSuppl[TS_START_RES_ABIL_AX_Y];
	rp_START_RES_ABIL_AX_Z = RP_TSuppl[TS_START_RES_ABIL_AX_Z];
	rp_START_RES_ABIL_AX_A = RP_TSuppl[TS_START_RES_ABIL_AX_A];
	rp_START_RES_ABIL_AX_W = RP_TSuppl[TS_START_RES_ABIL_AX_W];
	rp_START_RES_ABIL_AX_C = RP_TSuppl[TS_START_RES_ABIL_AX_C];


	tS(TS_STOP_RES_ABIL_AX_X, (unsigned char)(rp_START_RES_ABIL_AX_X));
	tS(TS_STOP_RES_ABIL_AX_Y, (unsigned char)(rp_START_RES_ABIL_AX_Y));
	tS(TS_STOP_RES_ABIL_AX_Z, (unsigned char)(rp_START_RES_ABIL_AX_Z));
	tS(TS_STOP_RES_ABIL_AX_A, (unsigned char)(rp_START_RES_ABIL_AX_A));
	tS(TS_STOP_RES_ABIL_AX_W, (unsigned char)(rp_START_RES_ABIL_AX_W));
	tS(TS_STOP_RES_ABIL_AX_C, (unsigned char)(rp_START_RES_ABIL_AX_C));


	rp_STOP_RES_ABIL_AX_X = RP_TSuppl[TS_STOP_RES_ABIL_AX_X];
	rp_STOP_RES_ABIL_AX_Y = RP_TSuppl[TS_STOP_RES_ABIL_AX_Y];
	rp_STOP_RES_ABIL_AX_Z = RP_TSuppl[TS_STOP_RES_ABIL_AX_Z];
	rp_STOP_RES_ABIL_AX_A = RP_TSuppl[TS_STOP_RES_ABIL_AX_A];
	rp_STOP_RES_ABIL_AX_W = RP_TSuppl[TS_STOP_RES_ABIL_AX_W];
	rp_STOP_RES_ABIL_AX_C = RP_TSuppl[TS_STOP_RES_ABIL_AX_C];


	if(rp_START_RES_ABIL_AX_X && !mem_rp_START_RES_ABIL_AX_X) R[R_CONT_RES_ABIL_AX_X]++;   if( (R[R_CONT_RES_ABIL_AX_X]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) R[R_CONT_RES_ABIL_AX_X] = 0;
	if(rp_START_RES_ABIL_AX_Y && !mem_rp_START_RES_ABIL_AX_Y) R[R_CONT_RES_ABIL_AX_Y]++;   if( (R[R_CONT_RES_ABIL_AX_Y]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) R[R_CONT_RES_ABIL_AX_Y] = 0;
	if(rp_START_RES_ABIL_AX_Z && !mem_rp_START_RES_ABIL_AX_Z) R[R_CONT_RES_ABIL_AX_Z]++;   if( (R[R_CONT_RES_ABIL_AX_Z]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) R[R_CONT_RES_ABIL_AX_Z] = 0;
	if(rp_START_RES_ABIL_AX_A && !mem_rp_START_RES_ABIL_AX_A) R[R_CONT_RES_ABIL_AX_A]++;   if( (R[R_CONT_RES_ABIL_AX_A]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) R[R_CONT_RES_ABIL_AX_A] = 0;
	if(rp_START_RES_ABIL_AX_W && !mem_rp_START_RES_ABIL_AX_W) R[R_CONT_RES_ABIL_AX_W]++;   if( (R[R_CONT_RES_ABIL_AX_W]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) R[R_CONT_RES_ABIL_AX_W] = 0;
	if(rp_START_RES_ABIL_AX_C && !mem_rp_START_RES_ABIL_AX_C) R[R_CONT_RES_ABIL_AX_C]++;   if( (R[R_CONT_RES_ABIL_AX_C]>32000) || (MGPILOT_F2 && MGPILOT_F3) ) R[R_CONT_RES_ABIL_AX_C] = 0;


	mem_rp_START_RES_ABIL_AX_X = rp_START_RES_ABIL_AX_X;
	mem_rp_START_RES_ABIL_AX_Y = rp_START_RES_ABIL_AX_Y;
	mem_rp_START_RES_ABIL_AX_Z = rp_START_RES_ABIL_AX_Z;
	mem_rp_START_RES_ABIL_AX_A = rp_START_RES_ABIL_AX_A;
	mem_rp_START_RES_ABIL_AX_W = rp_START_RES_ABIL_AX_W;
	mem_rp_START_RES_ABIL_AX_C = rp_START_RES_ABIL_AX_C;


	Disab_AX_X = rp_START_RES_ABIL_AX_X;
	Disab_AX_Y = rp_START_RES_ABIL_AX_Y;
	Disab_AX_Z = rp_START_RES_ABIL_AX_Z;
	Disab_AX_A = rp_START_RES_ABIL_AX_A;
	Disab_AX_W = rp_START_RES_ABIL_AX_W;
	Disab_AX_C = rp_START_RES_ABIL_AX_C;
	
	//////////////////////////////////////////////
	

	// Reset M di Disattivazione Abilitazione assi
	Mr_MC(353);	
	
	// Reset M di Riattivazione Abilitazione assi
	Mr_MC(357);	
}


// VERIFICHE VARIE ////////////////////////////////////////////////////////////////////////////////

// Prevenzione collisione tra utensile (ut. lungo>180 o lama) e visiera del riparo anteriore.
//FUNZ_MAN11+B : JOG+ ASSE Y
//FUNZ_MAN13+A : JOG- ASSE A
COLL_RIPARI_Y_A = CONF_VIS_ALTA &&
(
	( R[R_QUOTA_Y] < R[R_QUOTA_Y_MIN_NO_COLL_RIP] ) &&
	( R[R_QUOTA_A] > R[R_QUOTA_A_MAX_NO_COLL_RIP] ) &&
	( !COLLAUDO_ON && !ASSE_Y_NORIF && !ASSE_A_NORIF ) && 
	( !GEST_OPERATORE_MAN || ( !(MANO && FUNZ_MAN11 && COMANDO_B) && !(MANO && FUNZ_MAN13 && COMANDO_A) ) )
);

// Messaggio di potenziale collisione tra visiera del riparo anteriore e utensile
COLL_RIPARI_Y_A_FMS = COLL_RIPARI_Y_A;


// Distanza tra carter SX e mag.ut (mosso dagli assi W/X)
R[R_DIST_MAGUT_CARTER_SX] = (R[R_QUOTA_X]-R[R_FCNEG_X]) - (R[R_POS_ATTUALE_W]-R[R_Wmax_no_ing_carter_sx]);

//Magazzino in potenziale collisione con carter laterale SX della macchina
COLL_MAGUT_CARTER_SX_FMS = (R[R_Wmax_no_ing_carter_sx]>0.5) &&
	( ASSE_X_NORIF || ASSE_W_NORIF || ( (fabs(R[R_DIST_MAGUT_CARTER_SX])) < 20 ) ) && 
	MANO && !COLLAUDO_ON /*&& !GEST_OPERATORE_MAN*/;


//******************************************************************************
//******************************** Asse X **************************************
//******************************************************************************

if (!CONF_ASSE_X)
	{
	DRIVE_X_NOK_FAL = 0;
	ASSE_X_NORIF = 0;
	ABIL_X = 0;
	ASSE_X_FUNES_B = 0;
	ASSE_X_FUNES_A = 0;
	//
	}
else
	{
//  IN *************************************************************************
	
	ASSE_AXGEN = AX_X_CH0;
	NUM_CHANNEL_AXGEN = CHANNEL_CH0;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH0;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_X_CH0;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;
	ASSE_AXGEN_NO_EXC_POS	= 1;                    // Eventuale micro di asse non in extracorsa positivo
	ASSE_AXGEN_NO_EXC_NEG	= 1;                    // Eventuale micro di asse non in extracorsa negativo

	AXGEN_MICRO_SU_FC_POS	= 0;                    // Eventuale micro di zero posizionato verso il finecorsa positivo
	AXGEN_MICRO_SU_FC_NEG	= 0;                    // Eventuale micro di zero posizionato verso il finecorsa negativo

	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= 0;					// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_QUOTA_X] > (R[R_FCPOS_X]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_QUOTA_X] < (R[R_FCNEG_X]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme
	
	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN10;			// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN90;			// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || Mg_MC(72) || Mg_MC(74) || Mg_MC(114) || Mg_MC(10) || Mg_MC(21);	// Funz M abilitaz assi durante riferimento e cambio ut.

	DO_SON_X =  (unsigned short)(DO_SON_CH0(AX_X_CH0));
	DO_BRK_X =  (unsigned short)(DO_BRK_CH0(AX_X_CH0));
	DO_MCKO_X = (unsigned short)(DO_MCKO_CH0(AX_X_CH0));
	O_MOT_X =   (unsigned short)(O_MOT_CH0(AX_X_CH0));
	O_MOV_X =   (unsigned short)(O_MOV_CH0(AX_X_CH0));
	O_IND_X =   (unsigned short)(O_IND_CH0(AX_X_CH0));
	O_BLM_X =   (unsigned short)(O_BLM_CH0(AX_X_CH0));
	I_ABAX_X =  (unsigned short)(ABAX_CH0(AX_X_CH0));
	O_AGY_X = (unsigned short) (O_AGY_CH0(AX_X_CH0));

	TIMEOUT_DRIVE_AXGEN_NOK	= RP_TSuppl[TS_DRIVE_X_IN_ALLARME];	// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_X];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_X];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_X;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_X;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_X;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_X;
	CONS_AVA_AXGEN			= 1;                           // Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= !COLL_MAGUT_CARTER_SX_FMS;   // Consenso fisico di blocchi meccanici 

	COND_SIMU_AXGEN			= COND_SIMU_X;				 // Solo visualizzati
	ABIL_AUTO_AXGEN			= ABIL_AUTO_X;
	ABIL_MANO_AXGEN			= ABIL_MANO_X;
    CONS_ABIL_HW_AXGEN      = ALIM_PRES_I;
	COND_SICUR_AXGEN		= SICUREZZE_X;	
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_RIT && CENTRALINA_OK_I;

	MEM_AVANTI_AXGEN		= MEM_AVANTI_X;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_X;
	FRENO_AXGEN				= FRENO_X;
	
	RICH_ABIL_AXGEN			= RICH_ABIL_X;
	ABIL_AXGEN				= ABIL_X;
	PROL_ABIL_AXGEN			= PROL_ABIL_X;
    COND_SFRENO_AXGEN       = RICH_ABIL_X && DO_SON_X && !DO_BRK_X;
	TIME_AXGEN				= TIME_X;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_X;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_X;
	RIT_DISABI_AXGEN		= RIT_DISABI_X;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_X;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_X;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_X_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_X_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_X_FAL;

	I_EME_AXGEN				= BITOFF;													// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= ( (Mg_MC(110) || Mg_MC(152) || Mg_MC(245)) && (DP_RIL_MORSE_X || I_ANN_CH0(AX_X_CH0) && O_MOV_CH0(AX_X_CH0)) ) ;	// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH0;												// Hold asse indipendente
	I_LSR_AXGEN				= BITOFF;													// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_X;
	Disab_AXGEN				= Disab_AX_X || ( MGPILOT_F2 && (R[R_TEST_DISAB_AX]>0.5) );
	FORZA_ABIL_AXGEN        = (R[R_FORZA_AB_X]>0.5);           // Test: forziamo abilitazione in manuale per analisi dei disturbi elettrici

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_X_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_X_OK				= DRIVE_AXGEN_OK;
	DO_PWR_X				= DO_PWR_K1;

    CONS_ABIL_HW_X          = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_X			= COM_AVANTI_AXGEN;
	COM_INDIETRO_X			= COM_INDIETRO_AXGEN;
	ARR_AVANTI_X			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_X			= ARR_INDIETRO_AXGEN;

	R[R_POS_ATTUALE_X]		= POS_ATTUALE_AXGEN;
	R[R_POS_TARGET_X]		= POS_TARGET_AXGEN;
	R[R_QUOTA_X]			= QUOTA_G53_AXGEN;
	R[R_INSEGUIMENTO_X]		= INSEGUIMENTO_AXGEN;		// Non serve per questo asse
	R[R_DIST1_AX_X]			= DIST_AXGEN;

	ASSE_X_FUNES_A			= ASSE_AXGEN_FUNES_A;
	ASSE_X_FUNES_B			= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_X			= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_X_SU_FCPOS			= ASSE_AXGEN_SU_FCPOS;
	ASSE_X_SU_FCNEG			= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_X				= COND_SIMU_AXGEN;
	ABIL_AUTO_X				= ABIL_AUTO_AXGEN;		
	ABIL_MANO_X				= ABIL_MANO_AXGEN;		
	SICUREZZE_X				= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_X		= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_X			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_X			= MEM_INDIETRO_AXGEN;
	FRENO_X					= FRENO_AXGEN;
	RICH_ABIL_X				= RICH_ABIL_AXGEN;
	ABIL_X					= ABIL_AXGEN;
	PROL_ABIL_X				= PROL_ABIL_AXGEN;
    COND_SFRENO_X           = COND_SFRENO_AXGEN;
	TIME_X					= TIME_AXGEN;
	RIT_SFRENO1_X			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_X			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_X			= RIT_DISABI_AXGEN;
	RIT_IBLM1_X				= RIT_IBLM1_AXGEN;
	RIT_IBLM2_X				= RIT_IBLM2_AXGEN;

	I_EME_X					= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_X					= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_X					= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_X				= TIME_ARR_AXGEN;
	X_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	 // asse fermo in lavoro, non abilitato
	
	SFRENA_K1_X  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_X  			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_X  			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_X					= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_X  				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_X					= I_LSR_AXGEN;		// per visualizzazione
	X_O_MOV					= O_MOV_AXGEN;		// per visualizzazione
	X_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_X				= FUNZ_M_AXGEN;		// per visualizzazione	

	EXC_POS_X_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_X_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_X_NOK_FAL			= DRIVE_AXGEN_NOK_FAL;

	//
	R[R_DIST_X_ABS]			= fabs(R[R_DIST1_AX_X]);

	}
	
	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 1) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//******************************** Asse Y **************************************
//******************************************************************************

if (!CONF_ASSE_Y)
	{
	DRIVE_Y_NOK_FAL = 0;
	ASSE_Y_NORIF = 0;
	ABIL_Y = 0;
	ASSE_Y_FUNES_B = 0;
	ASSE_Y_FUNES_A = 0;
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_Y_CH0;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH0;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH0;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_Y_CH0;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;
	ASSE_AXGEN_NO_EXC_POS	= 1;
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 0;
	AXGEN_MICRO_SU_FC_NEG	= 0;
	
	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= 0;					// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= ((R[R_ABIL_CORR_ASSE_Y] > 0.5) && (!O_BLM_X || O_MOV_X || !O_BLM_Z || O_MOV_Z)); // forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_QUOTA_Y] > (R[R_FCPOS_Y]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_QUOTA_Y] < (R[R_FCNEG_Y]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN11;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN91;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || Mg_MC(72) || Mg_MC(74) || Mg_MC(114) || Mg_MC(10) || Mg_MC(21);	// Funz M abilitaz assi durante riferimento e cambio ut.

	DO_SON_Y =  (unsigned short)(DO_SON_CH0(AX_Y_CH0));
	DO_BRK_Y =  (unsigned short)(DO_BRK_CH0(AX_Y_CH0));
	DO_MCKO_Y = (unsigned short)(DO_MCKO_CH0(AX_Y_CH0));
	O_MOT_Y =   (unsigned short)(O_MOT_CH0(AX_Y_CH0));
	O_MOV_Y =   (unsigned short)(O_MOV_CH0(AX_Y_CH0));
	O_IND_Y =   (unsigned short)(O_IND_CH0(AX_Y_CH0));
	O_BLM_Y =   (unsigned short)(O_BLM_CH0(AX_Y_CH0));
	I_ABAX_Y =  (unsigned short)(ABAX_CH0(AX_Y_CH0));
	O_AGY_Y = (unsigned short) (O_AGY_CH0(AX_Y_CH0));

	TIMEOUT_DRIVE_AXGEN_NOK	= RP_TSuppl[TS_DRIVE_Y_IN_ALLARME];	// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_Y];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_Y];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_Y;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_Y;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_Y;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_Y;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_Y;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_Y;
	ABIL_MANO_AXGEN			= ABIL_MANO_Y;
	CONS_ABIL_HW_AXGEN      = ALIM_PRES_I;
	COND_SICUR_AXGEN		= SICUREZZE_Y;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_RIT && CENTRALINA_OK_I;

	MEM_AVANTI_AXGEN		= MEM_AVANTI_Y;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_Y;
	FRENO_AXGEN				= FRENO_Y;
	
	RICH_ABIL_AXGEN			= RICH_ABIL_Y;
	ABIL_AXGEN				= ABIL_Y;
	PROL_ABIL_AXGEN			= PROL_ABIL_Y;
    COND_SFRENO_AXGEN       = RICH_ABIL_Y && DO_SON_Y && !DO_BRK_Y;
	TIME_AXGEN				= TIME_Y;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_Y;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_Y;
	RIT_DISABI_AXGEN		= RIT_DISABI_Y;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_Y;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_Y;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_Y_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_Y_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_Y_FAL;

	I_EME_AXGEN				= BITOFF;				// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= ( DP_PRESETTER || ( I_ANN_CH0(AX_Y_CH0) && O_MOV_CH0(AX_Y_CH0) ) );  // Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH0;			// Hold asse indipendente
	I_LSR_AXGEN				= BITOFF;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_Y;
	Disab_AXGEN				= Disab_AX_Y || ( MGPILOT_F2 && (R[R_TEST_DISAB_AX]>0.5) );
	FORZA_ABIL_AXGEN        = (R[R_FORZA_AB_Y]>0.5);           // Test: forziamo abilitazione in manuale per analisi dei disturbi elettrici

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_Y_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_Y_OK				= DRIVE_AXGEN_OK;
	DO_PWR_Y				= DO_PWR_K1;

    CONS_ABIL_HW_Y          = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_Y			= COM_AVANTI_AXGEN;
	COM_INDIETRO_Y			= COM_INDIETRO_AXGEN;
	ARR_AVANTI_Y			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_Y			= ARR_INDIETRO_AXGEN;

	R[R_POS_ATTUALE_Y]		= POS_ATTUALE_AXGEN;
	R[R_POS_TARGET_Y]		= POS_TARGET_AXGEN;
	R[R_QUOTA_Y]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_Y]		= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	R[R_DIST1_AX_Y]			= DIST_AXGEN;

	ASSE_Y_FUNES_A			= ASSE_AXGEN_FUNES_A;
	ASSE_Y_FUNES_B			= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_Y			= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_Y_SU_FCPOS			= ASSE_AXGEN_SU_FCPOS;
	ASSE_Y_SU_FCNEG			= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_Y				= COND_SIMU_AXGEN;
	ABIL_AUTO_Y				= ABIL_AUTO_AXGEN;		
	ABIL_MANO_Y				= ABIL_MANO_AXGEN;		
	SICUREZZE_Y				= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_Y		= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_Y			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_Y			= MEM_INDIETRO_AXGEN;
	FRENO_Y					= FRENO_AXGEN;
	RICH_ABIL_Y				= RICH_ABIL_AXGEN;
	ABIL_Y					= ABIL_AXGEN;
	PROL_ABIL_Y				= PROL_ABIL_AXGEN;
    COND_SFRENO_Y           = COND_SFRENO_AXGEN;
	TIME_Y					= TIME_AXGEN;
	RIT_SFRENO1_Y			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_Y			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_Y			= RIT_DISABI_AXGEN;
	RIT_IBLM1_Y				= RIT_IBLM1_AXGEN;
	RIT_IBLM2_Y				= RIT_IBLM2_AXGEN;

	I_EME_Y					= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_Y					= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_Y					= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_Y				= TIME_ARR_AXGEN;
	Y_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_Y 			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_Y  			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_Y  			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_Y					= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_Y  				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_Y					= I_LSR_AXGEN;		// per visualizzazione
	Y_O_MOV					= O_MOV_AXGEN;		// per visualizzazione
	Y_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_Y				= FUNZ_M_AXGEN;		// per visualizzazione	

	EXC_POS_Y_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_Y_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_Y_NOK_FAL			= DRIVE_AXGEN_NOK_FAL;

	//
	R[R_DIST_Y_ABS]			= fabs(R[R_DIST1_AX_Y]);

	}

	// HOLD/VARIE EVENTUALI ********************************************************

	// Mandrino in potenziale ingombro (in Y) col magazzino 
	if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
		MANDR_COLL_MAG = 0;
	else
		{
		if(AUTO_CICLOMAN)  MANDR_COLL_MAG = !ASSE_Y_NORIF && (R[R_QUOTA_Y]>(R[R_QUOTA_Y_FUOING_MAG_2]+1 ))   && !( Mg_MC(72) || Mg_MC(74) || Mg_MC(10) || Mg_MC(21) ) && !(MANO && FUNZ_MAN11 && COMANDO_A);
		else               MANDR_COLL_MAG = !ASSE_Y_NORIF && (R[R_QUOTA_Y]>(R[R_QUOTA_Y_FUOING_MAG_2]+1-20)) && !( Mg_MC(72) || Mg_MC(74) || Mg_MC(10) || Mg_MC(21) ) && !(MANO && FUNZ_MAN11 && COMANDO_A);	// (R[R_QUOTA_Y_FUOING_MAG_2]-20)  genera Hold 20mm prima per considerare spazio d'arresto di circa 15mm
		}
	
	// HOLD da Y per ingombro tra mandrino e mag.ut.
	Y_HOLD_DA_MAG_TOOL = (MANO && MANDR_COLL_MAG && !O_BLM_Y && FUNZ_MAN11 && COMANDO_B && !GEST_OPERATORE_MAN) ||
	                     (AUTO && MANDR_COLL_MAG && !O_BLM_Y && !O_IND_Y && !( Mg_MC(72) || Mg_MC(74) || Mg_MC(64) || Mg_MC(10) || Mg_MC(21) ) );

	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 2) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//******************************** Asse Z **************************************
//******************************************************************************

if (!CONF_ASSE_Z)
	{
	DRIVE_Z_NOK_FAL = 0;
	ASSE_Z_NORIF = 0;
	ABIL_Z = 0;
	ASSE_Z_FUNES_B = 0;
	ASSE_Z_FUNES_A = 0;
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_Z_CH0;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH0;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH0;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_Z_CH0;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;
	ASSE_AXGEN_NO_EXC_POS	= 1;
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 0;
	AXGEN_MICRO_SU_FC_NEG	= 0;

	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= 0;					// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= ((R[R_ABIL_CORR_ASSE_Z] > 0.5) && (!O_BLM_X || O_MOV_X || !O_BLM_Y || O_MOV_Y)); // forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_QUOTA_Z] > (R[R_FCPOS_Z]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_QUOTA_Z] < (R[R_FCNEG_Z]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN12;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN92;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || Mg_MC(72) || Mg_MC(74) || Mg_MC(114) || Mg_MC(10) || Mg_MC(21);	// Funz M abilitaz assi durante riferimento e cambio ut.

	DO_SON_Z =  (unsigned short)(DO_SON_CH0(AX_Z_CH0));
	DO_BRK_Z =  (unsigned short)(DO_BRK_CH0(AX_Z_CH0));
	DO_MCKO_Z = (unsigned short)(DO_MCKO_CH0(AX_Z_CH0));
	O_MOT_Z =   (unsigned short)(O_MOT_CH0(AX_Z_CH0));
	O_MOV_Z =   (unsigned short)(O_MOV_CH0(AX_Z_CH0));
	O_IND_Z =   (unsigned short)(O_IND_CH0(AX_Z_CH0));
	O_BLM_Z =   (unsigned short)(O_BLM_CH0(AX_Z_CH0));
	I_ABAX_Z =  (unsigned short)(ABAX_CH0(AX_Z_CH0));
	O_AGY_Z = (unsigned short) (O_AGY_CH0(AX_Z_CH0));

	TIMEOUT_DRIVE_AXGEN_NOK	= RP_TSuppl[TS_DRIVE_Z_IN_ALLARME];	// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_Z];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_Z];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_Z;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_Z;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_Z;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_Z;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_Z;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_Z;
	ABIL_MANO_AXGEN			= ABIL_MANO_Z;
	CONS_ABIL_HW_AXGEN      = ALIM_PRES_I;
	COND_SICUR_AXGEN		= SICUREZZE_Z;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_RIT && CENTRALINA_OK_I && (NO_EMERG_I || O_MOT_Z); // Modifica per caduta asse alla pressione pulsante emergenza

	MEM_AVANTI_AXGEN		= MEM_AVANTI_Z;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_Z;
	FRENO_AXGEN				= FRENO_Z;
	
	RICH_ABIL_AXGEN			= RICH_ABIL_Z;
	ABIL_AXGEN				= ABIL_Z;
	PROL_ABIL_AXGEN			= PROL_ABIL_Z;
    COND_SFRENO_AXGEN       = RICH_ABIL_Z && DO_SON_Z && !DO_BRK_Z;
	TIME_AXGEN				= TIME_Z;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_Z;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_Z;
	RIT_DISABI_AXGEN		= RIT_DISABI_Z;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_Z;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_Z;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_Z_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_Z_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_Z_FAL;

	I_EME_AXGEN				= BITOFF;			// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= BITOFF;			// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH0;		// Hold asse indipendente
	I_LSR_AXGEN				= BITOFF;			// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_Z;
	Disab_AXGEN				= Disab_AX_Z || ( MGPILOT_F2 && (R[R_TEST_DISAB_AX]>0.5) );
	FORZA_ABIL_AXGEN        = (R[R_FORZA_AB_Z]>0.5);           // Test: forziamo abilitazione in manuale per analisi dei disturbi elettrici

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_Z_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_Z_OK				= DRIVE_AXGEN_OK;
	DO_PWR_Z				= DO_PWR_K1;

	CONS_ABIL_HW_Z          = CONS_ABIL_HW_AXGEN;
    COM_AVANTI_Z			= COM_AVANTI_AXGEN;
	COM_INDIETRO_Z			= COM_INDIETRO_AXGEN;
	ARR_AVANTI_Z			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_Z			= ARR_INDIETRO_AXGEN;

	R[R_POS_ATTUALE_Z]		= POS_ATTUALE_AXGEN;
	R[R_POS_TARGET_Z]		= POS_TARGET_AXGEN;
	R[R_QUOTA_Z]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_Z]		= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	R[R_DIST1_AX_Z]			= DIST_AXGEN;

	ASSE_Z_FUNES_A			= ASSE_AXGEN_FUNES_A;
	ASSE_Z_FUNES_B			= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_Z			= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_Z_SU_FCPOS			= ASSE_AXGEN_SU_FCPOS;
	ASSE_Z_SU_FCNEG			= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_Z				= COND_SIMU_AXGEN;
	ABIL_AUTO_Z				= ABIL_AUTO_AXGEN;		
	ABIL_MANO_Z				= ABIL_MANO_AXGEN;		
	SICUREZZE_Z				= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_Z		= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_Z			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_Z			= MEM_INDIETRO_AXGEN;
	FRENO_Z					= FRENO_AXGEN;
	RICH_ABIL_Z				= RICH_ABIL_AXGEN;
	ABIL_Z					= ABIL_AXGEN;
	PROL_ABIL_Z				= PROL_ABIL_AXGEN;
    COND_SFRENO_Z           = COND_SFRENO_AXGEN;
	TIME_Z					= TIME_AXGEN;
	RIT_SFRENO1_Z			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_Z			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_Z			= RIT_DISABI_AXGEN;
	RIT_IBLM1_Z				= RIT_IBLM1_AXGEN;
	RIT_IBLM2_Z				= RIT_IBLM2_AXGEN;

	I_EME_Z					= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_Z					= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_Z					= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_Z				= TIME_ARR_AXGEN;
	Z_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
			
	SFRENA_K1_Z  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_Z  			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_Z  			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_Z					= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_Z  				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_Z					= I_LSR_AXGEN;		// per visualizzazione
	Z_O_MOV					= O_MOV_AXGEN;		// per visualizzazione
	Z_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_Z				= FUNZ_M_AXGEN;		// per visualizzazione	
	
	EXC_POS_Z_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_Z_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_Z_NOK_FAL			= DRIVE_AXGEN_NOK_FAL;

	//SFRENO_Z_O				= SFRENA_Z;   // Il freno elettrico lo facciamo gestire direttamente all'azionamento

	R[R_DIST_Z_ABS]			= fabs(R[R_DIST1_AX_Z]);
	}

	// HOLD/VARIE EVENTUALI ********************************************************

	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 3) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//******************************** Asse A **************************************
//******************************************************************************

if (!CONF_ASSE_A)
	{
	DRIVE_A_NOK_FAL = 0;
	ASSE_A_NORIF = 0;
	ABIL_A = 0;
	ASSE_A_FUNES_B = 0;
	ASSE_A_FUNES_A = 0;
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_A_CH0;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH0;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH0;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_A_CH0;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;
	ASSE_AXGEN_NO_EXC_POS	= 1;
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 0;
	AXGEN_MICRO_SU_FC_NEG	= 0;
	
	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= 0;					// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_QUOTA_A] > (R[R_FCPOS_A]+R[R_FC_AX_ABSOLUTE_TOLL_ROT]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_QUOTA_A] < (R[R_FCNEG_A]-R[R_FC_AX_ABSOLUTE_TOLL_ROT]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN13;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN93;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || Mg_MC(72) || Mg_MC(74) || Mg_MC(114) || Mg_MC(10) || Mg_MC(21);	// Funz M abilitaz assi durante riferimento e cambio ut.

	DO_SON_A =  (unsigned short)(DO_SON_CH0(AX_A_CH0));
	DO_BRK_A =  (unsigned short)(DO_BRK_CH0(AX_A_CH0));
	DO_MCKO_A = (unsigned short)(DO_MCKO_CH0(AX_A_CH0));
	O_MOT_A =   (unsigned short)(O_MOT_CH0(AX_A_CH0));
	O_MOV_A =   (unsigned short)(O_MOV_CH0(AX_A_CH0));
	O_IND_A =   (unsigned short)(O_IND_CH0(AX_A_CH0));
	O_BLM_A =   (unsigned short)(O_BLM_CH0(AX_A_CH0));
	I_ABAX_A =  (unsigned short)(ABAX_CH0(AX_A_CH0));
	O_AGY_A = (unsigned short) (O_AGY_CH0(AX_A_CH0));

	TIMEOUT_DRIVE_AXGEN_NOK	= RP_TSuppl[TS_DRIVE_A_IN_ALLARME];	// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_A];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_A];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_A;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_A;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_A;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_A;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_A;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_A;
	ABIL_MANO_AXGEN			= ABIL_MANO_A;
	CONS_ABIL_HW_AXGEN      = ALIM_PRES_I;
	COND_SICUR_AXGEN		= SICUREZZE_A;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_RIT && CENTRALINA_OK_I;

	MEM_AVANTI_AXGEN		= MEM_AVANTI_A;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_A;
	FRENO_AXGEN				= FRENO_A;
	
	RICH_ABIL_AXGEN			= RICH_ABIL_A;
	ABIL_AXGEN				= ABIL_A;
	PROL_ABIL_AXGEN			= PROL_ABIL_A;
    COND_SFRENO_AXGEN       = RICH_ABIL_A && DO_SON_A && !DO_BRK_A;
	TIME_AXGEN				= TIME_A;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_A;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_A;
	RIT_DISABI_AXGEN		= RIT_DISABI_A;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_A;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_A;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_A_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_A_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_A_FAL;

	I_EME_AXGEN				= BITOFF;				// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= BITOFF;				// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH0;			// Hold asse indipendente
	I_LSR_AXGEN				= BITOFF;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_A;
	Disab_AXGEN				= Disab_AX_A || ( MGPILOT_F2 && (R[R_TEST_DISAB_AX]>0.5) );
	FORZA_ABIL_AXGEN        = (R[R_FORZA_AB_A]>0.5);           // Test: forziamo abilitazione in manuale per analisi dei disturbi elettrici

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_A_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_A_OK				= DRIVE_AXGEN_OK;
	DO_PWR_A				= DO_PWR_K1;

    CONS_ABIL_HW_A          = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_A			= COM_AVANTI_AXGEN;
	COM_INDIETRO_A			= COM_INDIETRO_AXGEN;
	ARR_AVANTI_A			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_A			= ARR_INDIETRO_AXGEN;

	R[R_POS_ATTUALE_A]		= POS_ATTUALE_AXGEN;
	R[R_POS_TARGET_A]		= POS_TARGET_AXGEN;
	R[R_QUOTA_A]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_A]		= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	R[R_DIST1_AX_A]			= DIST_AXGEN;

	ASSE_A_FUNES_A			= ASSE_AXGEN_FUNES_A;
	ASSE_A_FUNES_B			= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_A			= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_A_SU_FCPOS			= ASSE_AXGEN_SU_FCPOS;
	ASSE_A_SU_FCNEG			= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_A				= COND_SIMU_AXGEN;
	ABIL_AUTO_A				= ABIL_AUTO_AXGEN;		
	ABIL_MANO_A				= ABIL_MANO_AXGEN;		
	SICUREZZE_A				= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_A		= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_A			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_A			= MEM_INDIETRO_AXGEN;
	FRENO_A					= FRENO_AXGEN;
	RICH_ABIL_A				= RICH_ABIL_AXGEN;
	ABIL_A					= ABIL_AXGEN;
	PROL_ABIL_A				= PROL_ABIL_AXGEN;
    COND_SFRENO_A           = COND_SFRENO_AXGEN;
	TIME_A					= TIME_AXGEN;
	RIT_SFRENO1_A			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_A			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_A			= RIT_DISABI_AXGEN;
	RIT_IBLM1_A				= RIT_IBLM1_AXGEN;
	RIT_IBLM2_A				= RIT_IBLM2_AXGEN;

	I_EME_A					= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_A					= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_A					= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_A				= TIME_ARR_AXGEN;
	A_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_A 			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_A  			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_A  			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_A					= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_A  				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_A					= I_LSR_AXGEN;		// per visualizzazione
	A_O_MOV					= O_MOV_AXGEN;		// per visualizzazione
	A_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_A				= FUNZ_M_AXGEN;		// per visualizzazione	

	EXC_POS_A_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_A_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_A_NOK_FAL			= DRIVE_AXGEN_NOK_FAL;

	//

	}

	// HOLD/VARIE EVENTUALI ********************************************************

	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 4) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//


//******************************************************************************
//******************************** Asse C **************************************
//******************************************************************************

if (!CONF_ASSE_C)
	{
	DRIVE_C_NOK_FAL = 0;
	ASSE_C_NORIF = 0;
	ABIL_C = 0;
	ASSE_C_FUNES_B = 0;
	ASSE_C_FUNES_A = 0;
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_C_CH0;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH0;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH0;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_C_CH0;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;
	ASSE_AXGEN_NO_EXC_POS	= 1;
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 0;
	AXGEN_MICRO_SU_FC_NEG	= 0;

	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= 0;					// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_QUOTA_C] > (R[R_FCPOS_C]+R[R_FC_AX_ABSOLUTE_TOLL_ROT]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_QUOTA_C] < (R[R_FCNEG_C]-R[R_FC_AX_ABSOLUTE_TOLL_ROT]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN14;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN94;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || Mg_MC(72) || Mg_MC(74) || Mg_MC(114) || Mg_MC(10) || Mg_MC(21);	// Funz M abilitaz assi durante riferimento e cambio ut.

	DO_SON_C =  (unsigned short)(DO_SON_CH0(AX_C_CH0));
	DO_BRK_C =  (unsigned short)(DO_BRK_CH0(AX_C_CH0));
	DO_MCKO_C = (unsigned short)(DO_MCKO_CH0(AX_C_CH0));
	O_MOT_C =   (unsigned short)(O_MOT_CH0(AX_C_CH0));
	O_MOV_C =   (unsigned short)(O_MOV_CH0(AX_C_CH0));
	O_IND_C =   (unsigned short)(O_IND_CH0(AX_C_CH0));
	O_BLM_C =   (unsigned short)(O_BLM_CH0(AX_C_CH0));
	I_ABAX_C =  (unsigned short)(ABAX_CH0(AX_C_CH0));
	O_AGY_C = (unsigned short) (O_AGY_CH0(AX_C_CH0));

	TIMEOUT_DRIVE_AXGEN_NOK	= RP_TSuppl[TS_DRIVE_C_IN_ALLARME];	// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_C];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_C];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_C;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_C;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_C;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_C;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_C;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_C;
	ABIL_MANO_AXGEN			= ABIL_MANO_C;
	CONS_ABIL_HW_AXGEN      = ALIM_PRES_I;
	COND_SICUR_AXGEN		= SICUREZZE_C;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_RIT && CENTRALINA_OK_I;

	MEM_AVANTI_AXGEN		= MEM_AVANTI_C;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_C;
	FRENO_AXGEN				= FRENO_C;
	
	RICH_ABIL_AXGEN			= RICH_ABIL_C;
	ABIL_AXGEN				= ABIL_C;
	PROL_ABIL_AXGEN			= PROL_ABIL_C;
    COND_SFRENO_AXGEN       = RICH_ABIL_C && DO_SON_C && !DO_BRK_C;
	TIME_AXGEN				= TIME_C;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_C;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_C;
	RIT_DISABI_AXGEN		= RIT_DISABI_C;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_C;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_C;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_C_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_C_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_C_FAL;

	I_EME_AXGEN				= BITOFF;					// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= BITOFF;					// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH0;				// Hold asse indipendente
	I_LSR_AXGEN				= BITOFF;					// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_C;
	Disab_AXGEN				= Disab_AX_C || ( MGPILOT_F2 && (R[R_TEST_DISAB_AX]>0.5) );
	FORZA_ABIL_AXGEN        = (R[R_FORZA_AB_C]>0.5);           // Test: forziamo abilitazione in manuale per analisi dei disturbi elettrici

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_C_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_C_OK				= DRIVE_AXGEN_OK;
	DO_PWR_C				= DO_PWR_K1;

	CONS_ABIL_HW_C          = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_C			= COM_AVANTI_AXGEN;
	COM_INDIETRO_C			= COM_INDIETRO_AXGEN;
	ARR_AVANTI_C			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_C			= ARR_INDIETRO_AXGEN;

	R[R_POS_ATTUALE_C]		= POS_ATTUALE_AXGEN;
	R[R_POS_TARGET_C]		= POS_TARGET_AXGEN;
	R[R_QUOTA_C]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_C]		= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	R[R_DIST1_AX_C]			= DIST_AXGEN;
	
	ASSE_C_FUNES_A			= ASSE_AXGEN_FUNES_A;
	ASSE_C_FUNES_B			= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_C			= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_C_SU_FCPOS			= ASSE_AXGEN_SU_FCPOS;
	ASSE_C_SU_FCNEG			= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_C				= COND_SIMU_AXGEN;
	ABIL_AUTO_C				= ABIL_AUTO_AXGEN;		
	ABIL_MANO_C				= ABIL_MANO_AXGEN;		
	SICUREZZE_C				= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_C		= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_C			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_C			= MEM_INDIETRO_AXGEN;
	FRENO_C					= FRENO_AXGEN;
	RICH_ABIL_C				= RICH_ABIL_AXGEN;
	ABIL_C					= ABIL_AXGEN;
	PROL_ABIL_C				= PROL_ABIL_AXGEN;
    COND_SFRENO_C           = COND_SFRENO_AXGEN;
	TIME_C					= TIME_AXGEN;
	RIT_SFRENO1_C			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_C			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_C			= RIT_DISABI_AXGEN;
	RIT_IBLM1_C				= RIT_IBLM1_AXGEN;
	RIT_IBLM2_C				= RIT_IBLM2_AXGEN;

	I_EME_C					= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_C					= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_C					= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_C				= TIME_ARR_AXGEN;
	C_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_C  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_C  			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_C  			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_C					= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_C  				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_C					= I_LSR_AXGEN;		// per visualizzazione
	C_O_MOV					= O_MOV_AXGEN;		// per visualizzazione
	C_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_C				= FUNZ_M_AXGEN;		// per visualizzazione	

	EXC_POS_C_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_C_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_C_NOK_FAL			= DRIVE_AXGEN_NOK_FAL;

	//
	
	}

	// HOLD/VARIE EVENTUALI ********************************************************
	
	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 5) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//******************************** Asse W **************************************
//******************************************************************************

if (!CONF_ASSE_W)
	{
	DRIVE_W_NOK_FAL = 0;
	ASSE_W_NORIF = 0;
	ABIL_W = 0;
	ASSE_W_FUNES_B = 0;
	ASSE_W_FUNES_A = 0;
	}
else
	{
//  IN *************************************************************************
	if(AX_W_CH_ON == CHANNEL_CH1)
	{
		ASSE_AXGEN	= AX_W_CH1;
		NUM_CHANNEL_AXGEN = CHANNEL_CH1;
	}
	else if(AX_W_CH_ON == CHANNEL_CH0)  // Canale proprietario
	{
		ASSE_AXGEN	= AX_W_CH0;
		NUM_CHANNEL_AXGEN = CHANNEL_CH0;
	}
	else
	{
		ASSE_AXGEN = 999;
		NUM_CHANNEL_AXGEN = 999;
	}

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH0;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_W_CH0;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;
	ASSE_AXGEN_NO_EXC_POS	= 1;
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 1;
	AXGEN_MICRO_SU_FC_NEG	= 1;

	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= 0;					// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_POS_ATTUALE_W] > (R[R_FCPOS_W]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_POS_ATTUALE_W] < (R[R_FCNEG_W]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN07;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN95;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || Mg_MC(72) || Mg_MC(74) || Mg_MC(114) || Mg_MC(10) || Mg_MC(21);	// Funz M abilitaz assi durante riferimento e cambio ut.

	if(AX_W_CH_ON == 1)
	{
		DO_SON_W =  (unsigned short)(DO_SON_CH1(AX_W_CH1));
		DO_BRK_W =  (unsigned short)(DO_BRK_CH1(AX_W_CH1));
		DO_MCKO_W = (unsigned short)(DO_MCKO_CH1(AX_W_CH1));
		O_MOT_W =   (unsigned short)(O_MOT_CH1(AX_W_CH1));
		O_MOV_W =   (unsigned short)(O_MOV_CH1(AX_W_CH1));
		O_IND_W =   (unsigned short)(O_IND_CH1(AX_W_CH1));
		O_BLM_W =   (unsigned short)(O_BLM_CH1(AX_W_CH1));
		I_ABAX_W =  (unsigned short)(ABAX_CH1(AX_W_CH1));
		O_AGY_W = (unsigned short) (O_AGY_CH1(AX_W_CH1));
	}
	else if(AX_W_CH_ON == 0)
	{
		DO_SON_W =  (unsigned short)(DO_SON_CH0(AX_W_CH0));
		DO_BRK_W =  (unsigned short)(DO_BRK_CH0(AX_W_CH0));
		DO_MCKO_W = (unsigned short)(DO_MCKO_CH0(AX_W_CH0));
		O_MOT_W =   (unsigned short)(O_MOT_CH0(AX_W_CH0));
		O_MOV_W =   (unsigned short)(O_MOV_CH0(AX_W_CH0));
		O_IND_W =   (unsigned short)(O_IND_CH0(AX_W_CH0));
		O_BLM_W =   (unsigned short)(O_BLM_CH0(AX_W_CH0));
		I_ABAX_W =  (unsigned short)(ABAX_CH0(AX_W_CH0));
		O_AGY_W = (unsigned short) (O_AGY_CH0(AX_W_CH0));
	}

	TIMEOUT_DRIVE_AXGEN_NOK	= RP_TSuppl[TS_DRIVE_W_IN_ALLARME];	// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_W];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_W];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_W;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_W;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_W;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_W;
	CONS_AVA_AXGEN			= !COLL_MAGUT_CARTER_SX_FMS;   // Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;                           // Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_W;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_W;
	ABIL_MANO_AXGEN			= ABIL_MANO_W;
    CONS_ABIL_HW_AXGEN      = 1;
	COND_SICUR_AXGEN		= SICUREZZE_W;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_RIT && CENTRALINA_OK_I;

	MEM_AVANTI_AXGEN		= MEM_AVANTI_W;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_W;
	FRENO_AXGEN				= FRENO_W;

	RICH_ABIL_AXGEN			= RICH_ABIL_W;
	ABIL_AXGEN				= ABIL_W;
	PROL_ABIL_AXGEN			= PROL_ABIL_W;
    COND_SFRENO_AXGEN       = RICH_ABIL_W && DO_SON_W && !DO_BRK_W;
	TIME_AXGEN				= TIME_W;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_W;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_W;
	RIT_DISABI_AXGEN		= RIT_DISABI_W;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_W;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_W;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_W_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_W_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_W_FAL;

	I_EME_AXGEN				= BITOFF;													// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= BITOFF;													// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	
	if(AX_W_CH_ON == 1)
		I_HLD_AXGEN			= I_FHOLD_CH1;												// Hold asse indipendente
	else if(AX_W_CH_ON == 0)
		I_HLD_AXGEN			= I_FHOLD_CH0;												// Hold asse indipendente
	
	I_LSR_AXGEN				= BITOFF;													// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_W;
	Disab_AXGEN				= Disab_AX_W || ( MGPILOT_F2 && (R[R_TEST_DISAB_AX]>0.5) );
	FORZA_ABIL_AXGEN        = (R[R_FORZA_AB_W]>0.5);           // Test: forziamo abilitazione in manuale per analisi dei disturbi elettrici

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_W_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_W_OK				= DRIVE_AXGEN_OK;
	DO_PWR_W				= DO_PWR_K1;

	CONS_ABIL_HW_W          = CONS_ABIL_HW_AXGEN;
    COM_AVANTI_W			= COM_AVANTI_AXGEN;
	COM_INDIETRO_W			= COM_INDIETRO_AXGEN;
	ARR_AVANTI_W			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_W			= ARR_INDIETRO_AXGEN;

	R[R_POS_ATTUALE_W]		= POS_ATTUALE_AXGEN;
	R[R_POS_TARGET_W]		= POS_TARGET_AXGEN;
	R[R_QUOTA_W]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_W]		= INSEGUIMENTO_AXGEN;	// Non serve per questo asse
	R[R_DIST1_AX_W]			= DIST_AXGEN;

	ASSE_W_FUNES_A			= ASSE_AXGEN_FUNES_A;
	ASSE_W_FUNES_B			= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_W			= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_W_SU_FCPOS			= ASSE_AXGEN_SU_FCPOS;
	ASSE_W_SU_FCNEG			= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_W				= COND_SIMU_AXGEN;
	ABIL_AUTO_W				= ABIL_AUTO_AXGEN;		
	ABIL_MANO_W				= ABIL_MANO_AXGEN;		
	SICUREZZE_W				= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_W		= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_W			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_W			= MEM_INDIETRO_AXGEN;
	FRENO_W					= FRENO_AXGEN;
	RICH_ABIL_W				= RICH_ABIL_AXGEN;
	ABIL_W					= ABIL_AXGEN;
	PROL_ABIL_W				= PROL_ABIL_AXGEN;
    COND_SFRENO_W           = COND_SFRENO_AXGEN;
	TIME_W					= TIME_AXGEN;
	RIT_SFRENO1_W			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_W			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_W			= RIT_DISABI_AXGEN;
	RIT_IBLM1_W				= RIT_IBLM1_AXGEN;
	RIT_IBLM2_W				= RIT_IBLM2_AXGEN;

	I_EME_W					= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_W					= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_W					= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_W				= TIME_ARR_AXGEN;
	W_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_W  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_W  			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_W  			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_W					= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_W  				= SFRENA_AXGEN;		// Visualizza SFRENA
	
	I_LSR_W					= I_LSR_AXGEN;		// per visualizzazione
	W_O_MOV					= O_MOV_AXGEN;		// per visualizzazione
	W_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_W				= FUNZ_M_AXGEN;		// per visualizzazione	

	//
	//
	EXC_POS_W_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_W_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_W_NOK_FAL			= DRIVE_AXGEN_NOK_FAL;

	//

	}

	// HOLD/VARIE EVENTUALI ********************************************************


	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 6) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//******************************** Asse P **************************************
//******************************************************************************

//******************* ELIMINATO



//******************************************************************************
//******************************** Asse H **************************************
//******************************************************************************

//******************* ELIMINATO


//******************************************************************************
//*********************** Asse Morsa M07               *************************
//******************************************************************************

//******************* ELIMINATO


//******************************************************************************
//*********************** Asse Morsa M08               *************************
//******************************************************************************

//******************* ELIMINATO


//******************************************************************************
//*********************** Asse Morsa M09                ************************
//******************************************************************************

//******************* ELIMINATO


//******************************************************************************
//*********************** Asse Morsa M10 (A per Siomag) ************************
//******************************************************************************

if (!CONF_ASSE_M10)
	{
	DRIVE_M10_NOK_FAL = 0;
	ASSE_M10_NORIF = 0;
	ABIL_M10 = 0;
	ASSE_M10_FUNES_B = 0;
	ASSE_M10_FUNES_A = 0;
	//
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_M10_CH2;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH2;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH2;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_M10_CH2;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;				// NON c'è micro di zero è comune per tutte le morse
	ASSE_AXGEN_NO_EXC_POS	= 1;				// NON ci sono extracorsa
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 1;
	AXGEN_MICRO_SU_FC_NEG	= 1;

	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= CONF_MORSE_NOTENABLED;	// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_POS_ATTUALE_M10] > (R[R_FCPOS_M10]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_POS_ATTUALE_M10] < (R[R_FCNEG_M10]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN54;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN74;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || FORZA_ABIL_MORSA_10;				// Funz M abilitaz assi durante riferimento e basta

	DO_SON_M10 =  (unsigned short)(DO_SON_CH2(AX_M10_CH2));
	DO_BRK_M10 =  (unsigned short)(DO_BRK_CH2(AX_M10_CH2));
	DO_MCKO_M10 = (unsigned short)(DO_MCKO_CH2(AX_M10_CH2));
	O_MOT_M10 =   (unsigned short)(O_MOT_CH2(AX_M10_CH2));
	O_MOV_M10 =   (unsigned short)(O_MOV_CH2(AX_M10_CH2));
	O_IND_M10 =   (unsigned short)(O_IND_CH2(AX_M10_CH2));
	O_BLM_M10 =   (unsigned short)(O_BLM_CH2(AX_M10_CH2));
	I_ABAX_M10 =  (unsigned short)(ABAX_CH2(AX_M10_CH2));
	O_AGY_M10 = (unsigned short) (O_AGY_CH2(AX_M10_CH2));

	APP_I_LSR_AX_M10 = (O_LSR_CH2(AX_M10_CH2) || RIC_LSR_MORS_10 ) && AUTO_CICLOMAN && !RIC_DIS_LSR_MORS_10 && !RESET_MC;

	if(O_LSR_CH2(AX_M10_CH2))
	{
		RIC_LSR_MORS_10 = 0;
	}
	if(O_AGG_CH2(AX_M10_CH2))
	{
		RIC_DIS_LSR_MORS_10 = 0;
	}

	TIMEOUT_DRIVE_AXGEN_NOK	= 0;				// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_M10];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_M10];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_M10;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_M10;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_M10;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_M10;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_M10;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_M10;
	ABIL_MANO_AXGEN			= ABIL_MANO_M10;
    CONS_ABIL_HW_AXGEN      = 1;
	COND_SICUR_AXGEN		= SICUREZZE_M10;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_IMM && CENTRALINA_OK_I && RP_TSuppl[TS_RIT_ALIM_MM_OK];

	MEM_AVANTI_AXGEN		= MEM_AVANTI_M10;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_M10;
	FRENO_AXGEN				= FRENO_M10;

	RICH_ABIL_AXGEN			= RICH_ABIL_M10;
	ABIL_AXGEN				= ABIL_M10;
	PROL_ABIL_AXGEN			= PROL_ABIL_M10;
    COND_SFRENO_AXGEN       = RICH_ABIL_M10 && DO_SON_M10 && !DO_BRK_M10;
	TIME_AXGEN				= TIME_M10;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_M10;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_M10;
	RIT_DISABI_AXGEN		= RIT_DISABI_M10;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_M10;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_M10;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_M10_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_M10_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_M10_FAL;

	I_EME_AXGEN				= BITOFF;						// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= APPOGGIO_I_ANN_COM;			// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH2 || M_HOLD || !RIPARI_CHIUSI_IMM || !(RP_TSuppl[TS_RIT_ALIM_MM_OK]);	// Hold asse indipendente
	I_LSR_AXGEN				= APP_I_LSR_AX_M10;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_M10;
	Disab_AXGEN				= BITOFF;
	FORZA_ABIL_AXGEN        = BITOFF;

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_M10_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_M10_OK			= DRIVE_AXGEN_OK;
	DO_PWR_M10				= DO_PWR_K1;

	CONS_ABIL_HW_M10        = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_M10			= COM_AVANTI_AXGEN;
	COM_INDIETRO_M10		= COM_INDIETRO_AXGEN;
	ARR_AVANTI_M10			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_M10		= ARR_INDIETRO_AXGEN;

	if( (!SIMULATORE_SU_PC && !SIMULATORE_SU_CN) || !ASSE_AXGEN_NORIF) R[R_POS_ATTUALE_M10] = POS_ATTUALE_AXGEN;
//	R[R_POS_TARGET_M10]		= POS_TARGET_AXGEN;
//	R[R_QUOTA_M10]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_M10]	= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	
	ASSE_M10_FUNES_A		= ASSE_AXGEN_FUNES_A;
	ASSE_M10_FUNES_B		= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_M10		= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_M10_SU_FCPOS		= ASSE_AXGEN_SU_FCPOS;
	ASSE_M10_SU_FCNEG		= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_M10			= COND_SIMU_AXGEN;
	ABIL_AUTO_M10			= ABIL_AUTO_AXGEN;		
	ABIL_MANO_M10			= ABIL_MANO_AXGEN;		
	SICUREZZE_M10			= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_M10	= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_M10			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_M10		= MEM_INDIETRO_AXGEN;
	FRENO_M10				= FRENO_AXGEN;
	RICH_ABIL_M10			= RICH_ABIL_AXGEN;
	ABIL_M10				= ABIL_AXGEN;
	PROL_ABIL_M10			= PROL_ABIL_AXGEN;
    COND_SFRENO_M10         = COND_SFRENO_AXGEN;
	TIME_M10				= TIME_AXGEN;
	RIT_SFRENO1_M10			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_M10			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_M10			= RIT_DISABI_AXGEN;
	RIT_IBLM1_M10			= RIT_IBLM1_AXGEN;
	RIT_IBLM2_M10			= RIT_IBLM2_AXGEN;

	I_EME_M10				= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_M10				= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_M10				= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_M10			= TIME_ARR_AXGEN;
	M10_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_M10  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_M10 			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_M10 			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_M10				= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_M10 				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_M10				= I_LSR_AXGEN;		// per visualizzazione
	M10_O_MOV				= O_MOV_AXGEN;		// per visualizzazione
	M10_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_M10				= FUNZ_M_AXGEN;		// per visualizzazione	

	//
	//
	//

	SBLOC_MORSA_10_O		= (SFRENA_M10 /*|| O_LSR_CH2(AX_M10_CH2)*/);   // Gestione sbloccaggio pneumatico asse

	EXC_POS_M10_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_M10_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_M10_NOK_FAL		= DRIVE_AXGEN_NOK_FAL;

	}

	// HOLD/VARIE EVENTUALI ********************************************************



	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 15) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

// Scritta per gestire il BUG dell'asse non riferito
if (CONF_SALTA_BUG_ISAC)
			{
			ASSE_M10_NORIF = ASSE_M11_NORIF;
			}			




//******************************************************************************
//*********************** Asse Morsa M11 (B per Siomag) ************************
//******************************************************************************

if (!CONF_ASSE_M11)
	{
	DRIVE_M11_NOK_FAL = 0;
	ASSE_M11_NORIF = 0;
	ABIL_M11 = 0;
	ASSE_M11_FUNES_B = 0;
	ASSE_M11_FUNES_A = 0;
	//
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_M11_CH2;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH2;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH2;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_M11_CH2;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;				// NON c'è micro di zero è comune per tutte le morse
	ASSE_AXGEN_NO_EXC_POS	= 1;				// NON ci sono extracorsa
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 1;
	AXGEN_MICRO_SU_FC_NEG	= 1;
	
	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= CONF_MORSE_NOTENABLED;	// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_POS_ATTUALE_M11] > (R[R_FCPOS_M11]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_POS_ATTUALE_M11] < (R[R_FCNEG_M11]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN55;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN75;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || FORZA_ABIL_MORSA_11;				// Funz M abilitaz assi durante riferimento e basta

	DO_SON_M11 =  (unsigned short)(DO_SON_CH2(AX_M11_CH2));
	DO_BRK_M11 =  (unsigned short)(DO_BRK_CH2(AX_M11_CH2));
	DO_MCKO_M11 = (unsigned short)(DO_MCKO_CH2(AX_M11_CH2));
	O_MOT_M11 =   (unsigned short)(O_MOT_CH2(AX_M11_CH2));
	O_MOV_M11 =   (unsigned short)(O_MOV_CH2(AX_M11_CH2));
	O_IND_M11 =   (unsigned short)(O_IND_CH2(AX_M11_CH2));
	O_BLM_M11 =   (unsigned short)(O_BLM_CH2(AX_M11_CH2));
	I_ABAX_M11 =  (unsigned short)(ABAX_CH2(AX_M11_CH2));
	O_AGY_M11 = (unsigned short) (O_AGY_CH2(AX_M11_CH2));

	APP_I_LSR_AX_M11 = (O_LSR_CH2(AX_M11_CH2) || RIC_LSR_MORS_11 ) && AUTO_CICLOMAN && !RIC_DIS_LSR_MORS_11 && !RESET_MC;

	if(O_LSR_CH2(AX_M11_CH2))
	{
		RIC_LSR_MORS_11 = 0;
	}
	if(O_AGG_CH2(AX_M11_CH2))
	{
		RIC_DIS_LSR_MORS_11 = 0;
	}
	
	TIMEOUT_DRIVE_AXGEN_NOK	= 0;				// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_M11];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_M11];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_M11;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_M11;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_M11;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_M11;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_M11;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_M11;
	ABIL_MANO_AXGEN			= ABIL_MANO_M11;
    CONS_ABIL_HW_AXGEN      = 1;
	COND_SICUR_AXGEN		= SICUREZZE_M11;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_IMM && CENTRALINA_OK_I && RP_TSuppl[TS_RIT_ALIM_MM_OK];

	MEM_AVANTI_AXGEN		= MEM_AVANTI_M11;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_M11;
	FRENO_AXGEN				= FRENO_M11;
	
	RICH_ABIL_AXGEN			= RICH_ABIL_M11;
	ABIL_AXGEN				= ABIL_M11;
	PROL_ABIL_AXGEN			= PROL_ABIL_M11;
    COND_SFRENO_AXGEN       = RICH_ABIL_M11 && DO_SON_M11 && !DO_BRK_M11;
	TIME_AXGEN				= TIME_M11;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_M11;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_M11;
	RIT_DISABI_AXGEN		= RIT_DISABI_M11;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_M11;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_M11;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_M11_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_M11_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_M11_FAL;

	I_EME_AXGEN				= BITOFF;						// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= APPOGGIO_I_ANN_COM;			// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH2 || M_HOLD || !RIPARI_CHIUSI_IMM || !(RP_TSuppl[TS_RIT_ALIM_MM_OK]);	// Hold asse indipendente
	I_LSR_AXGEN				= APP_I_LSR_AX_M11;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_M11;
	Disab_AXGEN				= BITOFF;
	FORZA_ABIL_AXGEN        = BITOFF;

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_M11_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_M11_OK			= DRIVE_AXGEN_OK;
	DO_PWR_M11				= DO_PWR_K1;

	CONS_ABIL_HW_M11        = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_M11			= COM_AVANTI_AXGEN;
	COM_INDIETRO_M11		= COM_INDIETRO_AXGEN;
	ARR_AVANTI_M11			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_M11		= ARR_INDIETRO_AXGEN;

	if( (!SIMULATORE_SU_PC && !SIMULATORE_SU_CN) || !ASSE_AXGEN_NORIF) R[R_POS_ATTUALE_M11] = POS_ATTUALE_AXGEN;
//	R[R_POS_TARGET_M11]		= POS_TARGET_AXGEN;
//	R[R_QUOTA_M11]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_M11]	= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	
	ASSE_M11_FUNES_A		= ASSE_AXGEN_FUNES_A;
	ASSE_M11_FUNES_B		= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_M11		= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_M11_SU_FCPOS		= ASSE_AXGEN_SU_FCPOS;
	ASSE_M11_SU_FCNEG		= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_M11			= COND_SIMU_AXGEN;
	ABIL_AUTO_M11			= ABIL_AUTO_AXGEN;		
	ABIL_MANO_M11			= ABIL_MANO_AXGEN;		
	SICUREZZE_M11			= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_M11	= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_M11			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_M11		= MEM_INDIETRO_AXGEN;
	FRENO_M11				= FRENO_AXGEN;
	RICH_ABIL_M11			= RICH_ABIL_AXGEN;
	ABIL_M11				= ABIL_AXGEN;
	PROL_ABIL_M11			= PROL_ABIL_AXGEN;
    COND_SFRENO_M11         = COND_SFRENO_AXGEN;
	TIME_M11				= TIME_AXGEN;
	RIT_SFRENO1_M11			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_M11			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_M11			= RIT_DISABI_AXGEN;
	RIT_IBLM1_M11			= RIT_IBLM1_AXGEN;
	RIT_IBLM2_M11			= RIT_IBLM2_AXGEN;

	I_EME_M11				= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_M11				= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_M11				= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_M11			= TIME_ARR_AXGEN;
	M11_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_M11  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_M11 			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_M11 			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_M11				= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_M11 				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_M11				= I_LSR_AXGEN;		// per visualizzazione
	M11_O_MOV				= O_MOV_AXGEN;		// per visualizzazione
	M11_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_M11				= FUNZ_M_AXGEN;		// per visualizzazione	

	//
	//
	//

	SBLOC_MORSA_11_O		= (SFRENA_M11 /*|| O_LSR_CH2(AX_M11_CH2)*/);   // Gestione sbloccaggio pneumatico asse	

	EXC_POS_M11_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_M11_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_M11_NOK_FAL		= DRIVE_AXGEN_NOK_FAL;
	
	}

	// HOLD/VARIE EVENTUALI ********************************************************



	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 16) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//*********************** Asse Morsa M12 (C per Siomag) ************************
//******************************************************************************

if (!CONF_ASSE_M12)
	{
	DRIVE_M12_NOK_FAL = 0;
	ASSE_M12_NORIF = 0;
	ABIL_M12 = 0;
	ASSE_M12_FUNES_B = 0;
	ASSE_M12_FUNES_A = 0;
	//
	//
	}
else
	{
//  IN *************************************************************************


	ASSE_AXGEN = AX_M12_CH2;
	NUM_CHANNEL_AXGEN = CHANNEL_CH2;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH2;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_M12_CH2;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;				// NON c'è micro di zero è comune per tutte le morse
	ASSE_AXGEN_NO_EXC_POS	= 1;				// NON ci sono extracorsa
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 1;
	AXGEN_MICRO_SU_FC_NEG	= 1;
	
	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= CONF_MORSE_NOTENABLED;	// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_POS_ATTUALE_M12] > (R[R_FCPOS_M12]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_POS_ATTUALE_M12] < (R[R_FCNEG_M12]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN56;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN76;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || FORZA_ABIL_MORSA_12;				// Funz M abilitaz assi durante riferimento e basta

	DO_SON_M12 =  (unsigned short)(DO_SON_CH2(AX_M12_CH2));
	DO_BRK_M12 =  (unsigned short)(DO_BRK_CH2(AX_M12_CH2));
	DO_MCKO_M12 = (unsigned short)(DO_MCKO_CH2(AX_M12_CH2));
	O_MOT_M12 =   (unsigned short)(O_MOT_CH2(AX_M12_CH2));
	O_MOV_M12 =   (unsigned short)(O_MOV_CH2(AX_M12_CH2));
	O_IND_M12 =   (unsigned short)(O_IND_CH2(AX_M12_CH2));
	O_BLM_M12 =   (unsigned short)(O_BLM_CH2(AX_M12_CH2));
	I_ABAX_M12 =  (unsigned short)(ABAX_CH2(AX_M12_CH2));
	O_AGY_M12 = (unsigned short) (O_AGY_CH2(AX_M12_CH2));

	APP_I_LSR_AX_M12 = (O_LSR_CH2(AX_M12_CH2) || RIC_LSR_MORS_12 ) && AUTO_CICLOMAN && !RIC_DIS_LSR_MORS_12 && !RESET_MC;

	if(O_LSR_CH2(AX_M12_CH2))
	{
		RIC_LSR_MORS_12 = 0;
	}
	if(O_AGG_CH2(AX_M12_CH2))
	{
		RIC_DIS_LSR_MORS_12 = 0;
	}

	TIMEOUT_DRIVE_AXGEN_NOK	= 0;				// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_M12];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_M12];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_M12;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_M12;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_M12;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_M12;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_M12;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_M12;
	ABIL_MANO_AXGEN			= ABIL_MANO_M12;
    CONS_ABIL_HW_AXGEN      = 1;
	COND_SICUR_AXGEN		= SICUREZZE_M12;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_IMM && CENTRALINA_OK_I && RP_TSuppl[TS_RIT_ALIM_MM_OK];

	MEM_AVANTI_AXGEN		= MEM_AVANTI_M12;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_M12;
	FRENO_AXGEN				= FRENO_M12;

	RICH_ABIL_AXGEN			= RICH_ABIL_M12;
	ABIL_AXGEN				= ABIL_M12;
	PROL_ABIL_AXGEN			= PROL_ABIL_M12;
    COND_SFRENO_AXGEN       = RICH_ABIL_M12 && DO_SON_M12 && !DO_BRK_M12;
	TIME_AXGEN				= TIME_M12;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_M12;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_M12;
	RIT_DISABI_AXGEN		= RIT_DISABI_M12;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_M12;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_M12;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_M12_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_M12_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_M12_FAL;

	I_EME_AXGEN				= BITOFF;						// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= APPOGGIO_I_ANN_COM;			// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH2 || M_HOLD || !RIPARI_CHIUSI_IMM || !(RP_TSuppl[TS_RIT_ALIM_MM_OK]);	// Hold asse indipendente
	I_LSR_AXGEN				= APP_I_LSR_AX_M12;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_M12;
	Disab_AXGEN				= BITOFF;
	FORZA_ABIL_AXGEN        = BITOFF;

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_M12_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_M12_OK			= DRIVE_AXGEN_OK;
	DO_PWR_M12				= DO_PWR_K1;

	CONS_ABIL_HW_M12        = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_M12			= COM_AVANTI_AXGEN;
	COM_INDIETRO_M12		= COM_INDIETRO_AXGEN;
	ARR_AVANTI_M12			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_M12		= ARR_INDIETRO_AXGEN;

	if( (!SIMULATORE_SU_PC && !SIMULATORE_SU_CN) || !ASSE_AXGEN_NORIF) R[R_POS_ATTUALE_M12] = POS_ATTUALE_AXGEN;
//	R[R_POS_TARGET_M12]		= POS_TARGET_AXGEN;
//	R[R_QUOTA_M12]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_M12]	= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	
	ASSE_M12_FUNES_A		= ASSE_AXGEN_FUNES_A;
	ASSE_M12_FUNES_B		= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_M12		= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_M12_SU_FCPOS		= ASSE_AXGEN_SU_FCPOS;
	ASSE_M12_SU_FCNEG		= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_M12			= COND_SIMU_AXGEN;
	ABIL_AUTO_M12			= ABIL_AUTO_AXGEN;		
	ABIL_MANO_M12			= ABIL_MANO_AXGEN;		
	SICUREZZE_M12			= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_M12	= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_M12			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_M12		= MEM_INDIETRO_AXGEN;
	FRENO_M12				= FRENO_AXGEN;
	RICH_ABIL_M12			= RICH_ABIL_AXGEN;
	ABIL_M12				= ABIL_AXGEN;
	PROL_ABIL_M12			= PROL_ABIL_AXGEN;
    COND_SFRENO_M12         = COND_SFRENO_AXGEN;
	TIME_M12				= TIME_AXGEN;
	RIT_SFRENO1_M12			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_M12			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_M12			= RIT_DISABI_AXGEN;
	RIT_IBLM1_M12			= RIT_IBLM1_AXGEN;
	RIT_IBLM2_M12			= RIT_IBLM2_AXGEN;

	I_EME_M12				= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_M12				= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_M12				= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_M12			= TIME_ARR_AXGEN;
	M12_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_M12  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_M12 			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_M12 			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_M12				= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_M12 				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_M12				= I_LSR_AXGEN;		// per visualizzazione
	M12_O_MOV				= O_MOV_AXGEN;		// per visualizzazione
	M12_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_M12				= FUNZ_M_AXGEN;		// per visualizzazione	

	//
	//
	//

	SBLOC_MORSA_12_O		= (SFRENA_M12 /*|| O_LSR_CH2(AX_M12_CH2)*/);   // Gestione sbloccaggio pneumatico asse

	EXC_POS_M12_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_M12_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_M12_NOK_FAL		= DRIVE_AXGEN_NOK_FAL;

	}

	// HOLD/VARIE EVENTUALI ********************************************************

	

	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 17) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//*********************** Asse Morsa M13 (U per Siomag) ************************
//******************************************************************************

if (!CONF_ASSE_M13)
	{
	DRIVE_M13_NOK_FAL = 0;
	ASSE_M13_NORIF = 0;
	ABIL_M13 = 0;
	ASSE_M13_FUNES_B = 0;
	ASSE_M13_FUNES_A = 0;
	//
	//
	}
else
	{
//  IN *************************************************************************

	ASSE_AXGEN = AX_M13_CH2;
	NUM_CHANNEL_AXGEN = CHANNEL_CH2;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH2;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_M13_CH2;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;				// NON c'è micro di zero è comune per tutte le morse
	ASSE_AXGEN_NO_EXC_POS	= 1;				// NON ci sono extracorsa
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 1;
	AXGEN_MICRO_SU_FC_NEG	= 1;
	
	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= CONF_MORSE_NOTENABLED;	// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_POS_ATTUALE_M13] > (R[R_FCPOS_M13]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_POS_ATTUALE_M13] < (R[R_FCNEG_M13]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN57;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN77;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || FORZA_ABIL_MORSA_13;				// Funz M abilitaz assi durante riferimento e basta

	DO_SON_M13 =  (unsigned short)(DO_SON_CH2(AX_M13_CH2));
	DO_BRK_M13 =  (unsigned short)(DO_BRK_CH2(AX_M13_CH2));
	DO_MCKO_M13 = (unsigned short)(DO_MCKO_CH2(AX_M13_CH2));
	O_MOT_M13 =   (unsigned short)(O_MOT_CH2(AX_M13_CH2));
	O_MOV_M13 =   (unsigned short)(O_MOV_CH2(AX_M13_CH2));
	O_IND_M13 =   (unsigned short)(O_IND_CH2(AX_M13_CH2));
	O_BLM_M13 =   (unsigned short)(O_BLM_CH2(AX_M13_CH2));
	I_ABAX_M13 =  (unsigned short)(ABAX_CH2(AX_M13_CH2));
	O_AGY_M13 = (unsigned short) (O_AGY_CH2(AX_M13_CH2));

	APP_I_LSR_AX_M13 = (O_LSR_CH2(AX_M13_CH2) || RIC_LSR_MORS_13 ) && AUTO_CICLOMAN && !RIC_DIS_LSR_MORS_13 && !RESET_MC;

	if(O_LSR_CH2(AX_M13_CH2))
	{
		RIC_LSR_MORS_13 = 0;
	}
	if(O_AGG_CH2(AX_M13_CH2))
	{
		RIC_DIS_LSR_MORS_13 = 0;
	}

	TIMEOUT_DRIVE_AXGEN_NOK	= 0;				// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_M13];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_M13];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_M13;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_M13;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_M13;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_M13;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_M13;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_M13;
	ABIL_MANO_AXGEN			= ABIL_MANO_M13;
    CONS_ABIL_HW_AXGEN      = 1;
	COND_SICUR_AXGEN		= SICUREZZE_M13;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_IMM && CENTRALINA_OK_I && RP_TSuppl[TS_RIT_ALIM_MM_OK];

	MEM_AVANTI_AXGEN		= MEM_AVANTI_M13;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_M13;
	FRENO_AXGEN				= FRENO_M13;
	
	RICH_ABIL_AXGEN			= RICH_ABIL_M13;
	ABIL_AXGEN				= ABIL_M13;
	PROL_ABIL_AXGEN			= PROL_ABIL_M13;
    COND_SFRENO_AXGEN       = RICH_ABIL_M13 && DO_SON_M13 && !DO_BRK_M13;
	TIME_AXGEN				= TIME_M13;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_M13;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_M13;
	RIT_DISABI_AXGEN		= RIT_DISABI_M13;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_M13;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_M13;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_M13_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_M13_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_M13_FAL;

	I_EME_AXGEN				= BITOFF;						// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= APPOGGIO_I_ANN_COM;			// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH2 || M_HOLD || !RIPARI_CHIUSI_IMM || !(RP_TSuppl[TS_RIT_ALIM_MM_OK]);	// Hold asse indipendente
	I_LSR_AXGEN				= APP_I_LSR_AX_M13;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_M13;
	Disab_AXGEN				= BITOFF;
	FORZA_ABIL_AXGEN        = BITOFF;

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_M13_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_M13_OK			= DRIVE_AXGEN_OK;
	DO_PWR_M13				= DO_PWR_K1;

	CONS_ABIL_HW_M13        = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_M13			= COM_AVANTI_AXGEN;
	COM_INDIETRO_M13		= COM_INDIETRO_AXGEN;
	ARR_AVANTI_M13			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_M13		= ARR_INDIETRO_AXGEN;

	if( (!SIMULATORE_SU_PC && !SIMULATORE_SU_CN) || !ASSE_AXGEN_NORIF) R[R_POS_ATTUALE_M13] = POS_ATTUALE_AXGEN;
//	R[R_POS_TARGET_M13]		= POS_TARGET_AXGEN;
//	R[R_QUOTA_M13]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_M13]	= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	
	ASSE_M13_FUNES_A		= ASSE_AXGEN_FUNES_A;
	ASSE_M13_FUNES_B		= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_M13		= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_M13_SU_FCPOS		= ASSE_AXGEN_SU_FCPOS;
	ASSE_M13_SU_FCNEG		= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_M13			= COND_SIMU_AXGEN;
	ABIL_AUTO_M13			= ABIL_AUTO_AXGEN;		
	ABIL_MANO_M13			= ABIL_MANO_AXGEN;		
	SICUREZZE_M13			= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_M13	= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_M13			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_M13		= MEM_INDIETRO_AXGEN;
	FRENO_M13				= FRENO_AXGEN;
	RICH_ABIL_M13			= RICH_ABIL_AXGEN;
	ABIL_M13				= ABIL_AXGEN;
	PROL_ABIL_M13			= PROL_ABIL_AXGEN;
    COND_SFRENO_M13         = COND_SFRENO_AXGEN;
	TIME_M13				= TIME_AXGEN;
	RIT_SFRENO1_M13			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_M13			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_M13			= RIT_DISABI_AXGEN;
	RIT_IBLM1_M13			= RIT_IBLM1_AXGEN;
	RIT_IBLM2_M13			= RIT_IBLM2_AXGEN;

	I_EME_M13				= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_M13				= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_M13				= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_M13			= TIME_ARR_AXGEN;
	M13_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_M13  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_M13 			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_M13 			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_M13				= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_M13 				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_M13				= I_LSR_AXGEN;		// per visualizzazione
	M13_O_MOV				= O_MOV_AXGEN;		// per visualizzazione
	M13_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_M13				= FUNZ_M_AXGEN;		// per visualizzazione	

	//
	//
	//

	SBLOC_MORSA_13_O		= (SFRENA_M13 /*|| O_LSR_CH2(AX_M13_CH2)*/);   // Gestione sbloccaggio pneumatico asse

	EXC_POS_M13_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_M13_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_M13_NOK_FAL		= DRIVE_AXGEN_NOK_FAL;

	}

	// HOLD/VARIE EVENTUALI ********************************************************

	

	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 18) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

// Scritta per gestire il BUG dell'asse non riferito
if (CONF_SALTA_BUG_ISAC)
			{
			ASSE_M13_NORIF = ASSE_M11_NORIF;
			}			




//******************************************************************************
//*********************** Asse Morsa M14 (V per Siomag) ************************
//******************************************************************************

if (!CONF_ASSE_M14)
	{
	DRIVE_M14_NOK_FAL = 0;
	ASSE_M14_NORIF = 0;
	ABIL_M14 = 0;
	ASSE_M14_FUNES_B = 0;
	ASSE_M14_FUNES_A = 0;
	//
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_M14_CH2;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH2;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH2;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_M14_CH2;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;				// NON c'è micro di zero è comune per tutte le morse
	ASSE_AXGEN_NO_EXC_POS	= 1;				// NON ci sono extracorsa
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 1;
	AXGEN_MICRO_SU_FC_NEG	= 1;
	
	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= CONF_MORSE_NOTENABLED;	// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_POS_ATTUALE_M14] > (R[R_FCPOS_M14]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_POS_ATTUALE_M14] < (R[R_FCNEG_M14]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN58;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN78;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || FORZA_ABIL_MORSA_14;				// Funz M abilitaz assi durante riferimento e basta

	DO_SON_M14 =  (unsigned short)(DO_SON_CH2(AX_M14_CH2));
	DO_BRK_M14 =  (unsigned short)(DO_BRK_CH2(AX_M14_CH2));
	DO_MCKO_M14 = (unsigned short)(DO_MCKO_CH2(AX_M14_CH2));
	O_MOT_M14 =   (unsigned short)(O_MOT_CH2(AX_M14_CH2));
	O_MOV_M14 =   (unsigned short)(O_MOV_CH2(AX_M14_CH2));
	O_IND_M14 =   (unsigned short)(O_IND_CH2(AX_M14_CH2));
	O_BLM_M14 =   (unsigned short)(O_BLM_CH2(AX_M14_CH2));
	I_ABAX_M14 =  (unsigned short)(ABAX_CH2(AX_M14_CH2));
	O_AGY_M14 = (unsigned short) (O_AGY_CH2(AX_M14_CH2));

	APP_I_LSR_AX_M14 = (O_LSR_CH2(AX_M14_CH2) || RIC_LSR_MORS_14 ) && AUTO_CICLOMAN && !RIC_DIS_LSR_MORS_14 && !RESET_MC;

	if(O_LSR_CH2(AX_M14_CH2))
	{
		RIC_LSR_MORS_14 = 0;
	}
	if(O_AGG_CH2(AX_M14_CH2))
	{
		RIC_DIS_LSR_MORS_14 = 0;
	}

	TIMEOUT_DRIVE_AXGEN_NOK	= 0;				// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_M14];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_M14];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_M14;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_M14;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_M14;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_M14;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_M14;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_M14;
	ABIL_MANO_AXGEN			= ABIL_MANO_M14;
    CONS_ABIL_HW_AXGEN      = 1;
	COND_SICUR_AXGEN		= SICUREZZE_M14;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_IMM && CENTRALINA_OK_I && RP_TSuppl[TS_RIT_ALIM_MM_OK];

	MEM_AVANTI_AXGEN		= MEM_AVANTI_M14;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_M14;
	FRENO_AXGEN				= FRENO_M14;

	RICH_ABIL_AXGEN			= RICH_ABIL_M14;
	ABIL_AXGEN				= ABIL_M14;
	PROL_ABIL_AXGEN			= PROL_ABIL_M14;
    COND_SFRENO_AXGEN       = RICH_ABIL_M14 && DO_SON_M14 && !DO_BRK_M14;
	TIME_AXGEN				= TIME_M14;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_M14;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_M14;
	RIT_DISABI_AXGEN		= RIT_DISABI_M14;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_M14;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_M14;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_M14_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_M14_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_M14_FAL;

	I_EME_AXGEN				= BITOFF;						// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= APPOGGIO_I_ANN_COM;			// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH2 || M_HOLD || !RIPARI_CHIUSI_IMM || !(RP_TSuppl[TS_RIT_ALIM_MM_OK]);	// Hold asse indipendente
	I_LSR_AXGEN				= APP_I_LSR_AX_M14;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_M14;
	Disab_AXGEN				= BITOFF;
	FORZA_ABIL_AXGEN        = BITOFF;

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_M14_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_M14_OK			= DRIVE_AXGEN_OK;
	DO_PWR_M14				= DO_PWR_K1;

	CONS_ABIL_HW_M14        = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_M14			= COM_AVANTI_AXGEN;
	COM_INDIETRO_M14		= COM_INDIETRO_AXGEN;
	ARR_AVANTI_M14			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_M14		= ARR_INDIETRO_AXGEN;

	if( (!SIMULATORE_SU_PC && !SIMULATORE_SU_CN) || !ASSE_AXGEN_NORIF) R[R_POS_ATTUALE_M14] = POS_ATTUALE_AXGEN;
//	R[R_POS_TARGET_M14]		= POS_TARGET_AXGEN;
//	R[R_QUOTA_M14]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_M14]	= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	
	ASSE_M14_FUNES_A		= ASSE_AXGEN_FUNES_A;
	ASSE_M14_FUNES_B		= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_M14		= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_M14_SU_FCPOS		= ASSE_AXGEN_SU_FCPOS;
	ASSE_M14_SU_FCNEG		= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_M14			= COND_SIMU_AXGEN;
	ABIL_AUTO_M14			= ABIL_AUTO_AXGEN;		
	ABIL_MANO_M14			= ABIL_MANO_AXGEN;		
	SICUREZZE_M14			= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_M14	= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_M14			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_M14		= MEM_INDIETRO_AXGEN;
	FRENO_M14				= FRENO_AXGEN;
	RICH_ABIL_M14			= RICH_ABIL_AXGEN;
	ABIL_M14				= ABIL_AXGEN;
	PROL_ABIL_M14			= PROL_ABIL_AXGEN;
    COND_SFRENO_M14          = COND_SFRENO_AXGEN;
	TIME_M14				= TIME_AXGEN;
	RIT_SFRENO1_M14			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_M14			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_M14			= RIT_DISABI_AXGEN;
	RIT_IBLM1_M14			= RIT_IBLM1_AXGEN;
	RIT_IBLM2_M14			= RIT_IBLM2_AXGEN;

	I_EME_M14				= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_M14				= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_M14				= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_M14			= TIME_ARR_AXGEN;
	M14_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato
	
	SFRENA_K1_M14  			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_M14 			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_M14 			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_M14				= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_M14 				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_M14				= I_LSR_AXGEN;		// per visualizzazione
	M14_O_MOV				= O_MOV_AXGEN;		// per visualizzazione
	M14_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_M14				= FUNZ_M_AXGEN;		// per visualizzazione	

	//
	//
	//

	SBLOC_MORSA_14_O		= (SFRENA_M14 /*|| O_LSR_CH2(AX_M14_CH2)*/);   // Gestione sbloccaggio pneumatico asse

	EXC_POS_M14_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_M14_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_M14_NOK_FAL		= DRIVE_AXGEN_NOK_FAL;

	}

	// HOLD/VARIE EVENTUALI ********************************************************

	

	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 19) 
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//*********************** Asse Morsa M15 (P per Siomag) ************************
//******************************************************************************

if (!CONF_ASSE_M15)
	{
	DRIVE_M15_NOK_FAL = 0;
	ASSE_M15_NORIF = 0;
	ABIL_M15 = 0;
	ASSE_M15_FUNES_B = 0;
	ASSE_M15_FUNES_A = 0;
	//
	//
	}
else
	{
//  IN *************************************************************************
	ASSE_AXGEN				= AX_M15_CH2;
	NUM_CHANNEL_AXGEN		= CHANNEL_CH2;

	if (NUM_CHANNEL_AXGEN < 998) 
	{
	NUM_CHANNEL_PROPR_AXGEN = CHANNEL_CH2;
	NUM_ASSE_AXGEN_IN_CHANNEL_PROPR = AX_M15_CH2;
	ASSE_AXGEN_CANOPEN		= 0;
	ASSE_AXGEN_SU_FC_ZERO	= 0;				// NON c'è micro di zero è comune per tutte le morse
	ASSE_AXGEN_NO_EXC_POS	= 1;				// NON ci sono extracorsa
	ASSE_AXGEN_NO_EXC_NEG	= 1;

	AXGEN_MICRO_SU_FC_POS	= 1;
	AXGEN_MICRO_SU_FC_NEG	= 1;
	
	FCZERO_INIZ_AXGEN		= 1;					// abilita jog+ su FC0
	FCZERO_FINE_AXGEN		= 1;					// abilita jog- su FC0
	AXGEN_BLOCCATO_IN_LAV	= CONF_MORSE_NOTENABLED;	// asse fermo in lavoro, non abilitato

	ABIL_MANO_DA_CORR_AXGEN	= 0;					// forza abilitazione asse in manuale per correzioni volumetriche

	EXC_POS_SOFT_AXGEN = (R[R_POS_ATTUALE_M15] > (R[R_FCPOS_M15]+R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa positivo per allarme
	EXC_NEG_SOFT_AXGEN = (R[R_POS_ATTUALE_M15] < (R[R_FCNEG_M15]-R[R_FC_AX_ABSOLUTE_TOLL_LIN]));  //Asse assoluto in oltrecorsa negativo per allarme

	FUNZ_MAN_JOG_AXGEN		= FUNZ_MAN59;		// Funzione manuale che esegue il comando JOG
	FUNZ_MAN_INC_AXGEN		= FUNZ_MAN79;		// Funzione manuale che esegue il comando INC
	FUNZ_M_AXGEN			= Mg_MC(64) || FORZA_ABIL_MORSA_15;				// Funz M abilitaz assi durante riferimento e basta

	DO_SON_M15 =  (unsigned short)(DO_SON_CH2(AX_M15_CH2));
	DO_BRK_M15 =  (unsigned short)(DO_BRK_CH2(AX_M15_CH2));
	DO_MCKO_M15 = (unsigned short)(DO_MCKO_CH2(AX_M15_CH2));
	O_MOT_M15 =   (unsigned short)(O_MOT_CH2(AX_M15_CH2));
	O_MOV_M15 =   (unsigned short)(O_MOV_CH2(AX_M15_CH2));
	O_IND_M15 =   (unsigned short)(O_IND_CH2(AX_M15_CH2));
	O_BLM_M15 =   (unsigned short)(O_BLM_CH2(AX_M15_CH2));
	I_ABAX_M15 =  (unsigned short)(ABAX_CH2(AX_M15_CH2));
	O_AGY_M15 = (unsigned short) (O_AGY_CH2(AX_M15_CH2));

	APP_I_LSR_AX_M15 = (O_LSR_CH2(AX_M15_CH2) || RIC_LSR_MORS_15 ) && AUTO_CICLOMAN && !RIC_DIS_LSR_MORS_15 && !RESET_MC;

	if(O_LSR_CH2(AX_M15_CH2))
	{
		RIC_LSR_MORS_15 = 0;
	}
	if(O_AGG_CH2(AX_M15_CH2))
	{
		RIC_DIS_LSR_MORS_15 = 0;
	}

	TIMEOUT_DRIVE_AXGEN_NOK	= 0;				// Timer su cui appoggiare il Negato di DRIVE_OK
	QUOTA_FCPOS_AXGEN		= (float) R[R_FCPOS_M15];
	QUOTA_FCNEG_AXGEN		= (float) R[R_FCNEG_M15];
	TERM_AXGEN_NOK_FAL		= TERMICI_NOK_FAL;	// Termico generale di assi e azionamenti

	COM_AVANTI_AXGEN		= COM_AVANTI_M15;
	COM_INDIETRO_AXGEN		= COM_INDIETRO_M15;
	ARR_AVANTI_AXGEN		= ARR_AVANTI_M15;
	ARR_INDIETRO_AXGEN		= ARR_INDIETRO_M15;
	CONS_AVA_AXGEN			= 1;					// Consenso fisico di blocchi meccanici 
	CONS_IND_AXGEN			= 1;					// Consenso fisico di blocchi meccanici

	COND_SIMU_AXGEN			= COND_SIMU_M15;
	ABIL_AUTO_AXGEN			= ABIL_AUTO_M15;
	ABIL_MANO_AXGEN			= ABIL_MANO_M15;
    CONS_ABIL_HW_AXGEN      = 1;
	COND_SICUR_AXGEN		= SICUREZZE_M15;
	COND_RIPARI_AXGEN		= RIPARI_CHIUSI_IMM && CENTRALINA_OK_I && RP_TSuppl[TS_RIT_ALIM_MM_OK];

	MEM_AVANTI_AXGEN		= MEM_AVANTI_M15;
	MEM_INDIETRO_AXGEN		= MEM_INDIETRO_M15;
	FRENO_AXGEN				= FRENO_M15;

	RICH_ABIL_AXGEN			= RICH_ABIL_M15;
	ABIL_AXGEN				= ABIL_M15;
	PROL_ABIL_AXGEN			= PROL_ABIL_M15;
    COND_SFRENO_AXGEN       = RICH_ABIL_M15 && DO_SON_M15 && !DO_BRK_M15;
	TIME_AXGEN				= TIME_M15;
	RIT_SFRENO1_AXGEN		= RIT_SFRENO1_M15;
	RIT_SFRENO2_AXGEN		= RIT_SFRENO2_M15;
	RIT_DISABI_AXGEN		= RIT_DISABI_M15;
	RIT_IBLM1_AXGEN			= RIT_IBLM1_M15;
	RIT_IBLM2_AXGEN			= RIT_IBLM2_M15;

	DRIVE_AXGEN_NOK_FAL		= DRIVE_M15_NOK_FAL;
	EXC_POS_AXGEN_FAL		= EXC_POS_M15_FAL;
	EXC_NEG_AXGEN_FAL		= EXC_NEG_M15_FAL;

	I_EME_AXGEN				= BITOFF;						// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_AXGEN				= APPOGGIO_I_ANN_COM;			// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_AXGEN				= I_FHOLD_CH2 || M_HOLD || !RIPARI_CHIUSI_IMM || !(RP_TSuppl[TS_RIT_ALIM_MM_OK]);	// Hold asse indipendente
	I_LSR_AXGEN				= APP_I_LSR_AX_M15;				// Richiesta libera servo
	TIME_ARR_AXGEN			= TIME_ARR_M15;
	Disab_AXGEN				= BITOFF;
	FORZA_ABIL_AXGEN        = BITOFF;

//  ELABORAZIONE ***************************************************************
	assi_standard ();

//  OUT ************************************************************************
	ASSE_M15_NORIF			= ASSE_AXGEN_NORIF;	// ASSE NON RIFERITO
	DRIVE_M15_OK			= DRIVE_AXGEN_OK;
	DO_PWR_M15				= DO_PWR_K1;

	CONS_ABIL_HW_M15        = CONS_ABIL_HW_AXGEN;
	COM_AVANTI_M15			= COM_AVANTI_AXGEN;
	COM_INDIETRO_M15		= COM_INDIETRO_AXGEN;
	ARR_AVANTI_M15			= ARR_AVANTI_AXGEN;
	ARR_INDIETRO_M15		= ARR_INDIETRO_AXGEN;

	if( (!SIMULATORE_SU_PC && !SIMULATORE_SU_CN) || !ASSE_AXGEN_NORIF) R[R_POS_ATTUALE_M15] = POS_ATTUALE_AXGEN;
//	R[R_POS_TARGET_M15]		= POS_TARGET_AXGEN;
//	R[R_QUOTA_M15]			= QUOTA_G53_AXGEN;
//	R[R_INSEGUIMENTO_M15]	= INSEGUIMENTO_AXGEN		// Non serve per questo asse
	
	ASSE_M15_FUNES_A		= ASSE_AXGEN_FUNES_A;
	ASSE_M15_FUNES_B		= ASSE_AXGEN_FUNES_B;

	MICRO_DI_ZERO_M15		= ASSE_AXGEN_SU_FC_ZERO;

	ASSE_M15_SU_FCPOS		= ASSE_AXGEN_SU_FCPOS;
	ASSE_M15_SU_FCNEG		= ASSE_AXGEN_SU_FCNEG;

	COND_SIMU_M15			= COND_SIMU_AXGEN;
	ABIL_AUTO_M15			= ABIL_AUTO_AXGEN;		
	ABIL_MANO_M15			= ABIL_MANO_AXGEN;		
	SICUREZZE_M15			= COND_SICUR_AXGEN;		
	COND_RIPARI_ASSE_M15	= COND_RIPARI_AXGEN;	// Solo per visualizzazione

	MEM_AVANTI_M15			= MEM_AVANTI_AXGEN;
	MEM_INDIETRO_M15		= MEM_INDIETRO_AXGEN;
	FRENO_M15				= FRENO_AXGEN;
	RICH_ABIL_M15			= RICH_ABIL_AXGEN;
	ABIL_M15				= ABIL_AXGEN;
	PROL_ABIL_M15			= PROL_ABIL_AXGEN;
    COND_SFRENO_M15         = COND_SFRENO_AXGEN;
	TIME_M15				= TIME_AXGEN;
	RIT_SFRENO1_M15			= RIT_SFRENO1_AXGEN;
	RIT_SFRENO2_M15			= RIT_SFRENO2_AXGEN;
	RIT_DISABI_M15			= RIT_DISABI_AXGEN;
	RIT_IBLM1_M15			= RIT_IBLM1_AXGEN;
	RIT_IBLM2_M15			= RIT_IBLM2_AXGEN;

	I_EME_M15				= I_EME_AXGEN;		// Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito
	I_ANN_M15				= I_ANN_AXGEN;		// Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì
	I_HLD_M15				= I_HLD_AXGEN;		// Hold asse indipendente
	TIME_ARR_M15			= TIME_ARR_AXGEN;
	M15_BLOCCATO_IN_LAV		= AXGEN_BLOCCATO_IN_LAV;	// asse fermo in lavoro, non abilitato

	SFRENA_K1_M15			= SFRENA_K1_AXGEN;	// Visualizza Inizio sfreno asse 
	IBLM1_K1_M15			= IBLM1_K1;			// Visualizza Inizio Consenso I_BLM 
	IBLM2_K1_M15			= IBLM2_K1;			// Visualizza Fine   Consenso I_BLM 
	I_BLM_M15				= I_BLM_AXGEN;		// per visualizzazione
	SFRENA_M15 				= SFRENA_AXGEN;		// Visualizza SFRENA

	I_LSR_M15				= I_LSR_AXGEN;		// per visualizzazione
	M15_O_MOV				= O_MOV_AXGEN;		// per visualizzazione
	M15_O_MOV2				= O_MOV2_AXGEN;		// per visualizzazione
	FUNZ_M_M15				= FUNZ_M_AXGEN;		// per visualizzazione	

	//
	//
	//

	SBLOC_MORSA_15_O		= (SFRENA_M15 /*|| O_LSR_CH2(AX_M15_CH2)*/);   // Gestione sbloccaggio pneumatico asse

	EXC_POS_M15_FAL			= EXC_POS_AXGEN_FAL;
	EXC_NEG_M15_FAL			= EXC_NEG_AXGEN_FAL;
	DRIVE_M15_NOK_FAL		= DRIVE_AXGEN_NOK_FAL;

	}

	// HOLD/VARIE EVENTUALI ********************************************************

	

	}//CONF_ASSE


// Serve per debuggare di volta in volta l'asse selezionato dal par.R
if  (R[R_DEBUG_ASSI] == (float) 20)
			{	
			APPO_POS_ATTUALE_AXGEN	= (int) POS_ATTUALE_AXGEN;
			APPO_QUOTA_FCPOS_AXGEN	= (int)	QUOTA_FCPOS_AXGEN;
			APPO_QUOTA_FCNEG_AXGEN	= (int) QUOTA_FCNEG_AXGEN;
			APPO_DIST_AXGEN			= (int) DIST_AXGEN;
			goto saltaassi;
			}	

	//
	//
	//
	//
	//




//******************************************************************************
//*********************** Asse Morsa M16               *************************
//******************************************************************************

//******************* ELIMINATO


//******************************************************************************
//*********************** Asse Morsa M17               *************************
//******************************************************************************

//******************* ELIMINATO


//******************************************************************************
//*********************** Asse Morsa M18                ************************
//******************************************************************************

//******************* ELIMINATO


//******************************************************************************

 // Se è l'ultima istruzione prima della graffa finale serve il ;
saltaassi:;

// Appoggi dei segnali di assi morse motorizzate in movimento
O_MOT_AX_MM =  O_MOT_M10  || O_MOT_M11  || O_MOT_M12  || O_MOT_M13  || O_MOT_M14  || O_MOT_M15;

O_MOV_AX_MM =  M10_O_MOV  || M11_O_MOV  || M12_O_MOV  || M13_O_MOV  || M14_O_MOV  || M15_O_MOV;

O_MOV2_AX_MM = M10_O_MOV2 || M11_O_MOV2 || M12_O_MOV2 || M13_O_MOV2 || M14_O_MOV2 || M15_O_MOV2;



// Verifica stato abilitazione asse per il CNC Isac (da Comet S6)
// abil_Isac_CH2_AX_P_0_01 = (unsigned short)(AXCTRL_CH2[1].ctrlFlags.SERVON);

}//assi ==============================================================================



