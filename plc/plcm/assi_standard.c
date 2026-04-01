/*   
        --------------------------------------------------------------
        TITOLO:         Gestione assi
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione comune di tutti gli assi 
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    gestione_assi(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          DRIVE*_OK_I       Drive asse * ok
                        O_MCR(ASSE_AXGEN)          Micro zero asse *
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
        RELEASE:        DIA 1.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           01-12-2005
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Borsari G.- Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

//@ gestire nel modo nuovo: (  OVFRE )


#include        "all.inc"

extern int COM_AVANTI		[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int COM_INDIETRO		[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ARR_AVANTI		[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ARR_INDIETRO		[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ASSE_NORIF		[MAX_NUM_CHANNEL][ASSE_NULLO];
extern int ASSE_CANOPEN		[MAX_NUM_CHANNEL][ASSE_NULLO];

int RIT_O_MOV_AXGEN			[MAX_NUM_CHANNEL][ASSE_NULLO];
int MEM_I_ANN				[MAX_NUM_CHANNEL][ASSE_NULLO];	// Memoria di I_ANN_AXGEN

extern short ASSE_AXGEN;
extern short NUM_CHANNEL_AXGEN;
extern short NUM_CHANNEL_PROPR_AXGEN;
extern short NUM_ASSE_AXGEN_IN_CHANNEL_PROPR;
extern int RIT_DISABI_AXGEN, RIT_SFRENO1_AXGEN, RIT_SFRENO2_AXGEN, RIT_IBLM1_AXGEN, RIT_IBLM2_AXGEN;
extern int TIME_AXGEN, FUNZ_MAN_INC_AXGEN, FUNZ_MAN_JOG_AXGEN;
extern int TIMEOUT_DRIVE_AXGEN_NOK, TERM_AXGEN_NOK_FAL, FCZERO_INIZ_AXGEN, FCZERO_FINE_AXGEN, TIME_ARR_AXGEN;
extern float POS_ATTUALE_AXGEN, POS_OLD_AXGEN, POS_TARGET_AXGEN, DIST_AXGEN;
extern float INSEGUIMENTO_AXGEN;
extern float QUOTA_FCPOS_AXGEN, QUOTA_FCNEG_AXGEN, QUOTA_G53_AXGEN;


int VET_COM_AVA_K1[ASSE_NULLO][MAX_NUM_CHANNEL] = {0};
int VET_COM_IND_K1[ASSE_NULLO][MAX_NUM_CHANNEL] = {0};
int VET_MEM_AVA_K1[ASSE_NULLO][MAX_NUM_CHANNEL] = {0};
int VET_MEM_IND_K1[ASSE_NULLO][MAX_NUM_CHANNEL] = {0};
int VET_APP_INC1_K1[ASSE_NULLO][MAX_NUM_CHANNEL] = {0};
int VET_APP_INC2_K1[ASSE_NULLO][MAX_NUM_CHANNEL] = {0};
int VET_AB_K1[ASSE_NULLO][MAX_NUM_CHANNEL] = {0};


int DO_PWR_K1;
int COM_AVA_K1, COM_IND_K1, MEM_AVA_K1, MEM_IND_K1, APP_INC1_K1, APP_INC2_K1, AB_K1;
float DIST_K1, QUOTA_G58_K1, QUOTA_G59_K1, QUOTA_G54_K1;
long SEL_AX_K1;
BOOL COND_AVA_EXC, COND_IND_EXC;
BOOL QUOTA_RAGG_AXGEN;
unsigned short OVFRE_AXGEN; 

extern STASSI STATO_ASSI;

float POS_DESTINAZIONE;
float QUOTA_IN_G53;

void    assi_standard(void)
{
	//goto salta;	// 


	/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
	if (PON)
	{
	}

	if ((ASSE_AXGEN < NUM_ASSI) && (NUM_CHANNEL_AXGEN < MAX_NUM_CHANNEL))
	{

		// Il segnale DRIVE_AXGEN_OK arriva solo dagli azionamenti Yaskawa(mechatrolink) o Schneider(freq/segno), non dagli assi canopen (RTA o Schneider)

		if (ASSE_AXGEN_CANOPEN)
		{	// assi canopen (passo passo) Rta o Schneider
			if (!CONF_SCHNEIDER_PP)
				DRIVE_AXGEN_OK = 1;		// RTA
			else
				DRIVE_AXGEN_OK = 1;		// SCHNEIDER
		}
		else
		{	// assi Ethercat (azionamenti DELTA)
			if(NUM_CHANNEL_AXGEN == 0)
				DRIVE_AXGEN_OK = !DO_MCKO_CH0(ASSE_AXGEN);
			else if(NUM_CHANNEL_AXGEN == 1)
				DRIVE_AXGEN_OK = !DO_MCKO_CH1(ASSE_AXGEN);
			else if(NUM_CHANNEL_AXGEN == 2)
				DRIVE_AXGEN_OK = !DO_MCKO_CH2(ASSE_AXGEN);
		}


		if(NUM_CHANNEL_AXGEN == 0)
		{
			if (!DO_PWR_CH0(ASSE_AXGEN))	TIME_AXGEN = 50;
			else if (TIME_AXGEN > 0)		TIME_AXGEN--;
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			if (!DO_PWR_CH1(ASSE_AXGEN))	TIME_AXGEN = 50;
			else if (TIME_AXGEN > 0)		TIME_AXGEN--;
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			if (!DO_PWR_CH2(ASSE_AXGEN))	TIME_AXGEN = 50;
			else if (TIME_AXGEN > 0)		TIME_AXGEN--;
		}


		// Il segnale DO_PWR_K1 arriva solo dagli azionamenti Yaskawa(mechatrolink) o Schneider(freq/segno) o Ethercat, non dagli assi canopen (RTA o Schneider)

		if (ASSE_AXGEN_CANOPEN)
		{	// assi canopen (passo passo) Rta o Schneider
			if (!CONF_SCHNEIDER_PP)
				DO_PWR_K1 = RP_OUTMAC_ABIL;		// RTA
			else
				DO_PWR_K1 = RP_OUTMAC_ABIL;		// SCHNEIDER LMD   TODO: verificare se arriva segnale DO_PWR !!
		}
		else
		{	// assi Ethercat (azionamenti DELTA)
			if(NUM_CHANNEL_AXGEN == 0)
			{
				DO_PWR_K1 = DO_PWR_CH0(ASSE_AXGEN) && (TIME_AXGEN <= 0);
			}
			else if(NUM_CHANNEL_AXGEN == 1)
			{
				DO_PWR_K1 = DO_PWR_CH1(ASSE_AXGEN) && (TIME_AXGEN <= 0);
			}
			else if(NUM_CHANNEL_AXGEN == 2)
			{
				DO_PWR_K1 = DO_PWR_CH2(ASSE_AXGEN) && (TIME_AXGEN <= 0);
			}
		}


		/***************************************************************/
		/**************** ESECUZIONE PROGRAMMA SIMULATO ****************/
		/***************************************************************/

		if(SIMULATORE_SU_PC /*|| SIMULATORE_SU_CN*/)
		{
			DRIVE_AXGEN_OK = 1;
			DO_PWR_K1 = 1;           
		}

		// Gestione SW extracorsa assi
		if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
		{
			EXC_POS_AXGEN = !ASSE_AXGEN_NO_EXC_POS && AXGEN_MICRO_SU_FC_POS;	// Extracorsa positivo asse
			EXC_NEG_AXGEN = !ASSE_AXGEN_NO_EXC_NEG && AXGEN_MICRO_SU_FC_NEG;	// Extracorsa negativo asse
		}
		else
		{
			EXC_POS_AXGEN = (!ASSE_AXGEN_NO_EXC_POS && AXGEN_MICRO_SU_FC_POS) ||                // Extracorsa positivo asse (eventuali micro su assi incrementali)
							(!ASSE_AXGEN_NORIF && EXC_POS_SOFT_AXGEN && !GEST_OPERATORE_MAN);   // Gestione per assi assoluti la cui quota indicata è oltre il finecorsa: da resettare solo con gestione manuale operatore
			EXC_NEG_AXGEN = (!ASSE_AXGEN_NO_EXC_NEG && AXGEN_MICRO_SU_FC_NEG) ||                // Extracorsa negativo asse
							(!ASSE_AXGEN_NORIF && EXC_NEG_SOFT_AXGEN && !GEST_OPERATORE_MAN);   // Gestione per assi assoluti la cui quota indicata è oltre il finecorsa: da resettare solo con gestione manuale operatore
		}
		// Cumulativo negato EXTRACORSA NON ATTIVO per semplice gestione
		ASSE_AXGEN_NO_EXC_GEN = ASSE_AXGEN_NO_EXC_NEG && ASSE_AXGEN_NO_EXC_POS;


		//******* ALLARMI ASSE ***************************************************************
		if (RESET_ALL || RESET_MC)
		{
			DRIVE_AXGEN_NOK_FAL = 0;
			EXC_POS_AXGEN_FAL = 0;
			EXC_NEG_AXGEN_FAL = 0;
		}


		// **** Se viene attivata la memoria di bypass extracorsa - muovo liberamente
		if (BYPASS_EXTRACORSA)
		{
			EXC_POS_AXGEN_FAL = 0;
			EXC_NEG_AXGEN_FAL = 0;
		}


		// ASSE in extracorsa positivo
		if (EXC_POS_AXGEN && MACCHINA_PRONTA &&
			!(MANO && FUNZ_MAN_JOG_AXGEN && COMANDO_A ) && !BYPASS_EXTRACORSA)
			EXC_POS_AXGEN_FAL = 1;

		// ASSE in extracorsa negativo
		if (EXC_NEG_AXGEN &&  MACCHINA_PRONTA &&
			!(MANO && FUNZ_MAN_JOG_AXGEN && COMANDO_B) && !BYPASS_EXTRACORSA)
			EXC_NEG_AXGEN_FAL = 1;

		// Funz.man. di un altro asse attiva *************************************************
		FUNZ_MAN_JOG_ALTRI_AX = ( !FUNZ_MAN_JOG_AXGEN && 
			(FUNZ_MAN07 || FUNZ_MAN10 || FUNZ_MAN11 || FUNZ_MAN12 || FUNZ_MAN13 || FUNZ_MAN14 ||
			 FUNZ_MAN54 || FUNZ_MAN55 || FUNZ_MAN56 || FUNZ_MAN57 || FUNZ_MAN58 || FUNZ_MAN59 ));

		// Reset allarme Extracorsa se riferisce gli assi, muove l'asse in direzione opposta o muove altri assi
		if (MANO && ( (FUNZ_MAN_JOG_AXGEN && COMANDO_B /*&& GEST_OPERATORE_MAN*/) || (FUNZ_MAN_JOG_ALTRI_AX && (COMANDO_A || COMANDO_B)) ) )
			EXC_NEG_AXGEN_FAL = 0;

		if (MANO && ( (FUNZ_MAN_JOG_AXGEN && COMANDO_A /*&& GEST_OPERATORE_MAN*/) || (FUNZ_MAN_JOG_ALTRI_AX && (COMANDO_A || COMANDO_B)) ) )
			EXC_POS_AXGEN_FAL = 0;


		//**** MOVIMENTAZIONE INCREMENTALE ASSE **********************************************
		COM_AVA_K1	=	VET_COM_AVA_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN];
		COM_IND_K1	=	VET_COM_IND_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN];
		MEM_AVA_K1	=	VET_MEM_AVA_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN];
		MEM_IND_K1	=	VET_MEM_IND_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN];
		APP_INC1_K1	=	VET_APP_INC1_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN];
		APP_INC2_K1	=	VET_APP_INC2_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN];
		AB_K1		=	VET_AB_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN];

		// Comando JOG INC
		if(NUM_CHANNEL_AXGEN == 0)
		{
			jog_inc(ASSE_AXGEN, FUNZ_MAN_INC_AXGEN, COMANDO_A, COMANDO_B, RP_COMANDO_A, RP_COMANDO_B, ASSE_AXGEN_NO_EXC_GEN, &COM_AVA_K1, &COM_IND_K1, &MEM_AVA_K1, &MEM_IND_K1, &APP_INC1_K1, &APP_INC2_K1, &AB_K1);
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			jog_inc_MC(&CNCCTRL_CH1, &CNCSTATUS_CH1, &CNPLCHANDLE_CH1, ASSE_AXGEN, FUNZ_MAN_INC_AXGEN, COMANDO_A, COMANDO_B, RP_COMANDO_A, RP_COMANDO_B, ASSE_AXGEN_NO_EXC_GEN, &COM_AVA_K1, &COM_IND_K1, &MEM_AVA_K1, &MEM_IND_K1, &APP_INC1_K1, &APP_INC2_K1, &AB_K1);
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			jog_inc_MC(&CNCCTRL_CH2, &CNCSTATUS_CH2, &CNPLCHANDLE_CH2, ASSE_AXGEN, FUNZ_MAN_INC_AXGEN, COMANDO_A, COMANDO_B, RP_COMANDO_A, RP_COMANDO_B, ASSE_AXGEN_NO_EXC_GEN, &COM_AVA_K1, &COM_IND_K1, &MEM_AVA_K1, &MEM_IND_K1, &APP_INC1_K1, &APP_INC2_K1, &AB_K1);
		}		

		if (APP_INC2_K1)
		{
			COM_AVANTI_AXGEN	= COM_AVA_K1 && CONS_AVA_AXGEN;
			COM_INDIETRO_AXGEN	= COM_IND_K1 && CONS_IND_AXGEN;
			MEM_AVANTI_AXGEN	= MEM_AVA_K1;
			MEM_INDIETRO_AXGEN	= MEM_IND_K1;
			APP_INC2_K1			= 0;
		}


		VET_COM_AVA_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN]		=	COM_AVA_K1;
		VET_COM_IND_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN]		=	COM_IND_K1;
		VET_MEM_AVA_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN]		=	MEM_AVA_K1;
		VET_MEM_IND_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN]		=	MEM_IND_K1;
		VET_APP_INC1_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN]		=	APP_INC1_K1;
		VET_APP_INC2_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN]		=	APP_INC2_K1;
		VET_AB_K1[ASSE_AXGEN][NUM_CHANNEL_AXGEN]			=	AB_K1;


		// *********************** LETTURA QUOTA ASSE ********************************
		// La parte remmata è una predisp.futura (non testata) per ulteriori informazioni sull'asse


		//0 = QR (quota reale)
		//1 = QP (quota programmata)
		//2 = QE (quota errore)
		//3 = QD (distanza da percorrere)
		// Quota asse attuale
		if(NUM_CHANNEL_PROPR_AXGEN == 0)
		{
			lquote(1, &STATO_ASSI, (1L << (NUM_ASSE_AXGEN_IN_CHANNEL_PROPR)) );
			POS_ATTUALE_AXGEN = (float)STATO_ASSI.quota[NUM_ASSE_AXGEN_IN_CHANNEL_PROPR];

			read_var(VL_FLOT, 6003, -1, NUM_ASSE_AXGEN_IN_CHANNEL_PROPR, &QUOTA_IN_G53);
			// Quota asse in G53, assoluta
			QUOTA_G53_AXGEN = QUOTA_IN_G53;

			read_var(VL_FLOT, 2001, -1, NUM_ASSE_AXGEN_IN_CHANNEL_PROPR, &POS_DESTINAZIONE);
			// Quota destinazione
			POS_TARGET_AXGEN =  POS_DESTINAZIONE;			// Appoggio su variabile esterna

			lquote(2, &STATO_ASSI, (1L << (NUM_ASSE_AXGEN_IN_CHANNEL_PROPR)) );		// 2 = errore di inseguimento
			// Errore di inseguimento 
			INSEGUIMENTO_AXGEN = (float)STATO_ASSI.quota[NUM_ASSE_AXGEN_IN_CHANNEL_PROPR];
		}
		else if(NUM_CHANNEL_PROPR_AXGEN == 1)
		{
			lquote_MC(CNCSTATUS_CH1, AXSTATUS_CH1, 1, &STATO_ASSI, (1L << (NUM_ASSE_AXGEN_IN_CHANNEL_PROPR)));
			POS_ATTUALE_AXGEN = (float)STATO_ASSI.quota[NUM_ASSE_AXGEN_IN_CHANNEL_PROPR];

			read_var_MC(&CNCSTATUS_CH1, VL_FLOT, 6003, -1, NUM_ASSE_AXGEN_IN_CHANNEL_PROPR, &QUOTA_IN_G53);
			// Quota asse in G53, assoluta
			QUOTA_G53_AXGEN = QUOTA_IN_G53;

			read_var_MC(&CNCSTATUS_CH1, VL_FLOT, 2001, -1, NUM_ASSE_AXGEN_IN_CHANNEL_PROPR, &POS_DESTINAZIONE);
			// Quota destinazione
			POS_TARGET_AXGEN =  POS_DESTINAZIONE;			// Appoggio su variabile esterna

			lquote_MC(CNCSTATUS_CH1, AXSTATUS_CH1, 2, &STATO_ASSI, (1L << (NUM_ASSE_AXGEN_IN_CHANNEL_PROPR)) );		// 2 = errore di inseguimento
			// Errore di inseguimento 
			INSEGUIMENTO_AXGEN = (float)STATO_ASSI.quota[NUM_ASSE_AXGEN_IN_CHANNEL_PROPR];
		}
		else if(NUM_CHANNEL_PROPR_AXGEN == 2)
		{
			lquote_MC(CNCSTATUS_CH2, AXSTATUS_CH2, 1, &STATO_ASSI, (1L << (NUM_ASSE_AXGEN_IN_CHANNEL_PROPR)));
			POS_ATTUALE_AXGEN = (float)STATO_ASSI.quota[NUM_ASSE_AXGEN_IN_CHANNEL_PROPR];

			read_var_MC(&CNCSTATUS_CH2, VL_FLOT, 6003, -1, NUM_ASSE_AXGEN_IN_CHANNEL_PROPR, &QUOTA_IN_G53);
			// Quota asse in G53, assoluta
			QUOTA_G53_AXGEN = QUOTA_IN_G53;

			read_var_MC(&CNCSTATUS_CH2, VL_FLOT, 2001, -1, NUM_ASSE_AXGEN_IN_CHANNEL_PROPR, &POS_DESTINAZIONE);
			// Quota destinazione
			POS_TARGET_AXGEN =  POS_DESTINAZIONE;			// Appoggio su variabile esterna

			lquote_MC(CNCSTATUS_CH2, AXSTATUS_CH2, 2, &STATO_ASSI, (1L << (NUM_ASSE_AXGEN_IN_CHANNEL_PROPR)) );		// 2 = errore di inseguimento
			// Errore di inseguimento 
			INSEGUIMENTO_AXGEN = (float)STATO_ASSI.quota[NUM_ASSE_AXGEN_IN_CHANNEL_PROPR];
		}
		

		//lquote ( 3, &STATO_ASSI, (1L << (ASSE_AXGEN)) );		// 3 = distanza da percorrere
		//DIST_AXGEN =  (float)STATO_ASSI.quota[ASSE_AXGEN];	// valido per spostamenti da part program e multiprocesso
		//QUOTA_RAGG_AXGEN = (fabs(DIST_AXGEN) < R[R_TOLL]);

		// *********************** LETTURA DISTANZA DA PERCORRERE DELL'ASSE ********************************
		if(NUM_CHANNEL_AXGEN == 0)
		{
			lquote(3, &STATO_ASSI, (1L << (ASSE_AXGEN)) );          
			DIST_AXGEN = (float)(STATO_ASSI.quota[ASSE_AXGEN]);									// 3 = distanza da percorrere
			//QUOTA_RAGG_AXGEN = (fabs(DIST_AXGEN) < R[R_TOLL]);
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			lquote_MC( CNCSTATUS_CH1, AXSTATUS_CH1, 3, &STATO_ASSI, (1L << (ASSE_AXGEN)) );		// 3 = distanza da percorrere
			DIST_AXGEN = (float)(STATO_ASSI.quota[ASSE_AXGEN]);
			//QUOTA_RAGG_AXGEN = (fabs(DIST_AXGEN) < R[R_TOLL]);
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			lquote_MC( CNCSTATUS_CH2, AXSTATUS_CH2, 3, &STATO_ASSI, (1L << (ASSE_AXGEN)) );		// 3 = distanza da percorrere
			DIST_AXGEN = (float)(STATO_ASSI.quota[ASSE_AXGEN]);
			//QUOTA_RAGG_AXGEN = (fabs(DIST_AXGEN) < R[R_TOLL]);
		}

		// Gestione segnale asse in movimento *************************************************************
		// (Temporaneo fino alla corretta gestione di O_JPOS e O_JNEG dell'Isac)
		if(NUM_CHANNEL_AXGEN == 0)
		{
			O_MOV_AXGEN = (unsigned short)O_MOV_CH0(ASSE_AXGEN);
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			O_MOV_AXGEN = (unsigned short)O_MOV_CH1(ASSE_AXGEN);
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			O_MOV_AXGEN = (unsigned short)O_MOV_CH2(ASSE_AXGEN);
		}


		ASSE_AXGEN_IN_MOV = ( (fabs(POS_ATTUALE_AXGEN - POS_OLD_AXGEN)) > Delta_Pos);
		POS_OLD_AXGEN = POS_ATTUALE_AXGEN;

		// (Se asse Mec, indipendente, in hold: O_MOV rimarrebbe a 1)
		if (!ASSE_AXGEN_CANOPEN && I_HLD_AXGEN)
			O_MOV_AXGEN = O_MOV_AXGEN && ASSE_AXGEN_IN_MOV;


		// (O_MOV cadrebbe subito se si annulla il movimento di un asse Canopen)
		if (ASSE_AXGEN_CANOPEN)
		{
			if (I_ANN_AXGEN) MEM_I_ANN[NUM_CHANNEL_AXGEN][ASSE_AXGEN] = 1;		//I_ANN_AXGEN blocca jog assi canopen che a volte non si fermerebbero prima d'aver raggiunto la quota finale(20000) impostata dal cnc

			if (O_MOV_AXGEN) RIT_O_MOV_AXGEN[NUM_CHANNEL_AXGEN][ASSE_AXGEN] = (int)R[R_RIT_O_MOV_CAN]; //80 necessario agli assi Canopen x fermarsi
			else 
			{
				if (RIT_O_MOV_AXGEN[NUM_CHANNEL_AXGEN][ASSE_AXGEN] > 0)
				{
					RIT_O_MOV_AXGEN[NUM_CHANNEL_AXGEN][ASSE_AXGEN]--;
					//if (MEM_I_ANN[NUM_CHANNEL_AXGEN][ASSE_AXGEN)	RIT_O_MOV_AXGEN[NUM_CHANNEL_AXGEN][ASSE_AXGEN--;
					//else						RIT_O_MOV_AXGEN[NUM_CHANNEL_AXGEN][ASSE_AXGEN = 0;
				}
				else MEM_I_ANN[NUM_CHANNEL_AXGEN][ASSE_AXGEN]=0;
			}
			O_MOV2_AXGEN = RIT_O_MOV_AXGEN[NUM_CHANNEL_AXGEN][ASSE_AXGEN]>0;
		}
		else 
			O_MOV2_AXGEN = O_MOV_AXGEN;


		// Determino O_JPOS/O_JNEG *******************************************************************************
		// (Temporaneo fino alla corretta gestione di O_JPOS e O_JNEG dell'Isac per assi indipendenti)

		if(NUM_CHANNEL_AXGEN == 0)
		{
			if(ASSE_AXGEN_CANOPEN)
			{
				O_JPOS_AXGEN = ( O_MOV2_AXGEN && !O_IND_CH0(ASSE_AXGEN) || O_JPOS_CH0 ) && !O_JNEG_AXGEN;
				O_JNEG_AXGEN = ( O_MOV2_AXGEN &&  O_IND_CH0(ASSE_AXGEN) || O_JNEG_CH0 ) && !O_JPOS_AXGEN;
			}
			else
			{
				O_JPOS_AXGEN =  O_JPOS_CH0;		// Valido solo x Assi CNC
				O_JNEG_AXGEN =  O_JNEG_CH0;		// Valido solo x Assi CNC
			}
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			if(ASSE_AXGEN_CANOPEN)
			{
				O_JPOS_AXGEN = ( O_MOV2_AXGEN && !O_IND_CH1(ASSE_AXGEN) || O_JPOS_CH1 ) && !O_JNEG_AXGEN;
				O_JNEG_AXGEN = ( O_MOV2_AXGEN &&  O_IND_CH1(ASSE_AXGEN) || O_JNEG_CH1 ) && !O_JPOS_AXGEN;
			}
			else
			{
				O_JPOS_AXGEN =  O_JPOS_CH1;		// Valido solo x Assi CNC
				O_JNEG_AXGEN =  O_JNEG_CH1;		// Valido solo x Assi CNC
			}
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			if(ASSE_AXGEN_CANOPEN)
			{
				O_JPOS_AXGEN = ( O_MOV2_AXGEN && !O_IND_CH2(ASSE_AXGEN) || O_JPOS_CH2 ) && !O_JNEG_AXGEN;
				O_JNEG_AXGEN = ( O_MOV2_AXGEN &&  O_IND_CH2(ASSE_AXGEN) || O_JNEG_CH2 ) && !O_JPOS_AXGEN;
			}
			else
			{
				O_JPOS_AXGEN =  O_JPOS_CH2;		// Valido solo x Assi CNC
				O_JNEG_AXGEN =  O_JNEG_CH2;		// Valido solo x Assi CNC
			}
		}
			
		O_JPOS2_AXGEN = O_JPOS_AXGEN;
		O_JNEG2_AXGEN = O_JNEG_AXGEN;


		// Flag movimenti assi in corso
		MEM_JPOS_AXGEN = MEM_JPOS_AXGEN || O_JPOS_AXGEN;
		MEM_JNEG_AXGEN = MEM_JNEG_AXGEN || O_JNEG_AXGEN;


		// Condiz. per movimentare asse in extracorsa ****************************************

		COND_AVA_EXC = !EXC_POS_AXGEN_FAL && ( (FCZERO_INIZ_AXGEN &&  ASSE_AXGEN_SU_FC_ZERO) || (FCZERO_FINE_AXGEN && !ASSE_AXGEN_SU_FC_ZERO) );
		COND_IND_EXC = !EXC_NEG_AXGEN_FAL && ( (FCZERO_INIZ_AXGEN && !ASSE_AXGEN_SU_FC_ZERO) || (FCZERO_FINE_AXGEN &&  ASSE_AXGEN_SU_FC_ZERO) );


		//****** MOVIMENTAZIONE ASSE IN JOG **************************************************
		if (MANO && FUNZ_MAN_JOG_AXGEN && !MEM_AVANTI_AXGEN && !MEM_INDIETRO_AXGEN)
		{
			if ( COMANDO_B && CONS_AVA_AXGEN && (ASSE_AXGEN_NO_EXC_GEN || COND_AVA_EXC) )
			{
				COM_AVANTI_AXGEN = 1;        /* Comanda avanti asse */
				MEM_AVANTI_AXGEN = 1;
			}

			if ( COMANDO_A && CONS_IND_AXGEN && (ASSE_AXGEN_NO_EXC_GEN || COND_IND_EXC) )
			{
				COM_INDIETRO_AXGEN = 1;      /* Comanda indietro asse */
				MEM_INDIETRO_AXGEN = 1;
			}
		}

		if (MANO && MEM_AVANTI_AXGEN && (!COMANDO_B || !CONS_AVA_AXGEN) )
		{
			ARR_AVANTI_AXGEN = 1;
			COM_AVANTI_AXGEN = 0;
		}

		if (MANO && MEM_INDIETRO_AXGEN && (!COMANDO_A || !CONS_IND_AXGEN) )
		{
			ARR_INDIETRO_AXGEN = 1;
			COM_INDIETRO_AXGEN = 0;
		}


		if (O_JPOS_AXGEN)
			COM_AVANTI_AXGEN = 0;
		if (O_JNEG_AXGEN)
			COM_INDIETRO_AXGEN = 0;

		if (!O_MOV_AXGEN && !O_JPOS_AXGEN && ARR_AVANTI_AXGEN)
		{
			ARR_AVANTI_AXGEN = 0;
			MEM_AVANTI_AXGEN = 0;
		}

		if (!O_MOV_AXGEN && !O_JNEG_AXGEN && ARR_INDIETRO_AXGEN)
		{
			ARR_INDIETRO_AXGEN = 0;
			MEM_INDIETRO_AXGEN = 0;
		}

		if (!COMANDO_B && !COMANDO_A && !O_JPOS_AXGEN && !O_JNEG_AXGEN && !O_MOV_AXGEN)
		{
			ARR_AVANTI_AXGEN =   0;
			MEM_AVANTI_AXGEN =   0;
			ARR_INDIETRO_AXGEN = 0;
			MEM_INDIETRO_AXGEN = 0;
			COM_AVANTI_AXGEN =   0; 
			COM_INDIETRO_AXGEN = 0; 
		}


		//****** GESTIONE ABILITAZIONE (ASSE BLOCCABILE) ************************************

		// Condizioni valide solo in simulazione
		if(SIMULATORE_SU_PC)
			COND_SIMU_AXGEN = SIMULATORE_ON;
		else
			COND_SIMU_AXGEN = 0;


		// Flag di movimento in corso e out peric. (ritardate,reali) ancora presenti
		if(
			(NUM_CHANNEL_AXGEN == 0) && 
			(
				(ASSE_AXGEN==AX_X_CH0) || 
				(ASSE_AXGEN==AX_Y_CH0) || 
				(ASSE_AXGEN==AX_Z_CH0) || 
				(ASSE_AXGEN==AX_A_CH0) || 
				(ASSE_AXGEN==AX_C_CH0) || 
				(ASSE_AXGEN==AX_W_CH0)
			)
		)
			O_MOV2_OUT_RIT_AXGEN = O_MOV2_AXGEN && RIPARI_CHIUSI_RIT;

		else if(
			(NUM_CHANNEL_AXGEN == 1) && 
			(ASSE_AXGEN==AX_W_CH1) 
		)
			O_MOV2_OUT_RIT_AXGEN = O_MOV2_AXGEN && RIPARI_CHIUSI_RIT;

		else if(
			(NUM_CHANNEL_AXGEN == 2) && (
				(ASSE_AXGEN==AX_M10_CH2) || 
				(ASSE_AXGEN==AX_M11_CH2) || 
				(ASSE_AXGEN==AX_M12_CH2) || 
				(ASSE_AXGEN==AX_M13_CH2) || 
				(ASSE_AXGEN==AX_M14_CH2) || 
				(ASSE_AXGEN==AX_M15_CH2) 
			)
		)
			O_MOV2_OUT_RIT_AXGEN = O_MOV2_AXGEN && RIPARI_CHIUSI_RIT && (RP_TSuppl[TS_RIT_ALIM_MM_OK]);			// cr6 TS_RIT_ALIM_MM_SX_OK



		// Condizioni di Sicurezza : quando posso muovere l'asse
		if(NUM_CHANNEL_AXGEN == 0)
		{
			COND_SICUR_AXGEN = 
				DRIVE_AXGEN_OK && DO_PWR_K1 && ABAX_CH0(ASSE_AXGEN) && CONS_ABIL_HW_AXGEN && 
				(COND_RIPARI_AXGEN || O_MOV2_OUT_RIT_AXGEN);


			O_BLM_AXGEN = (unsigned short)(O_BLM_CH0(ASSE_AXGEN));
			O_AGY_AXGEN = (unsigned short) (O_AGY_CH0(ASSE_AXGEN));
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			COND_SICUR_AXGEN = 
				DRIVE_AXGEN_OK && DO_PWR_K1 && ABAX_CH1(ASSE_AXGEN) && CONS_ABIL_HW_AXGEN && 
				(COND_RIPARI_AXGEN || O_MOV2_OUT_RIT_AXGEN);


			O_BLM_AXGEN = (unsigned short)(O_BLM_CH1(ASSE_AXGEN));
			O_AGY_AXGEN = (unsigned short) (O_AGY_CH1(ASSE_AXGEN));
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			COND_SICUR_AXGEN = 
				DRIVE_AXGEN_OK && DO_PWR_K1 && ABAX_CH2(ASSE_AXGEN) && CONS_ABIL_HW_AXGEN && 
				(COND_RIPARI_AXGEN || O_MOV2_OUT_RIT_AXGEN);


			O_BLM_AXGEN = (unsigned short)(O_BLM_CH2(ASSE_AXGEN));
			O_AGY_AXGEN = (unsigned short) (O_AGY_CH2(ASSE_AXGEN));
		}


		// Condizioni manuali per movimentare l'asse : solo se deve muoversi, o deve almeno mantener la posizione in un ciclo manuale
		ABIL_MANO_AXGEN = MANO && (AB_K1 || FUNZ_M_AXGEN || !O_BLM_AXGEN || O_MOV2_AXGEN || ABIL_MANO_DA_CORR_AXGEN || FORZA_ABIL_AXGEN || (CICLOMAN && COND_RIPARI_AXGEN)); 


		// Condizioni automatiche per movimentare l'asse MORSA o comunque un asse non alimentato sempre
		if (AXGEN_BLOCCATO_IN_LAV)
		{
			// Aggiunto la condizione esterna di abilitazione al movimento (per le morse sullo slave) 
			// Il segnale OBLM_Ethernet va a 0 in ritardo rispetto al manuale
			// In manuale OBLM=0, l'asse parte
			// In automatico non va a 0 l'OBLM per far partire l'asse, ma va a 0 dopo (solo per gli assi slave ethernet)

			ABIL_AUTO_AXGEN = !MANO && (FUNZ_M_AXGEN || !O_BLM_AXGEN || O_AGY_AXGEN || O_MOV2_AXGEN);
		}
		else
		{
			// Condizioni automatiche per movimentare l'asse NON MORSA - sempre abilitato
			// Mantengo la funzione M per il riferimento assi

			ABIL_AUTO_AXGEN = !MANO && (COND_RIPARI_AXGEN || O_MOV2_AXGEN || FUNZ_M_AXGEN);

		}


		// Richiesta abilitazione dell'asse					
		RICH_ABIL_AXGEN = (COND_SIMU_AXGEN || ((ABIL_MANO_AXGEN || ABIL_AUTO_AXGEN) && COND_SICUR_AXGEN)) && !Disab_AXGEN; 



		// ------------------------- Temporizzazioni --------------------------------

		// (RICH_ABIL+DO_SON)	>>>>	Sbloccaggio Zimmer
		// SFRENA_K1_AXGEN: Inizia dopo un po di RICH_ABIL=1, termina quando RICH_ABIL=0

		if (!COND_SFRENO_AXGEN)			RIT_SFRENO1_AXGEN = (int)R[R_RIT_SFRENO1];		//R791=10

		else if (RIT_SFRENO1_AXGEN > 0)	RIT_SFRENO1_AXGEN--;

		SFRENA_K1_AXGEN = (RIT_SFRENO1_AXGEN==0); 



		// Sbloccaggio Zimmer	>>>>	Start IBLM
		// IBLM1_K1: Inizia dopo un po di SFRENA_K1_AXGEN=1, termina quando RICH_ABIL=0

		if (!SFRENA_K1_AXGEN)			RIT_IBLM1_AXGEN = (int)R[R_RIT_IBLM1];		//R792=40

		else if (RIT_IBLM1_AXGEN > 0)	RIT_IBLM1_AXGEN--;

		IBLM1_K1 = (RIT_IBLM1_AXGEN == 0);


		// ---------------------------------------------------


		// Fine RICH_ABIL		>>>>	Fine IBLM
		// IBLM2_K1: Inizia quando IBLM1_K1=1, termina dopo un po di RICH_ABIL=0

		if (IBLM1_K1)			RIT_IBLM2_AXGEN = (int)R[R_RIT_IBLM2];					//R793=15

		else if (RIT_IBLM2_AXGEN > 0)	RIT_IBLM2_AXGEN--;

		IBLM2_K1 = (RIT_IBLM2_AXGEN > 0);

		// Fine IBLM		>>>>>	Bloccaggio Zimmer
		// SFRENA_AXGEN: Inizia dopo un po di RICH_ABIL=1, termina dopo un po di IBLM2_K1=0

		if (SFRENA_K1_AXGEN || IBLM2_K1)	RIT_SFRENO2_AXGEN = (int)R[R_RIT_SFRENO2];	//R794=15;

		else if (RIT_SFRENO2_AXGEN > 0)	RIT_SFRENO2_AXGEN--;

		SFRENA_AXGEN = (RIT_SFRENO2_AXGEN > 0);

		// Bloccaggio Zimmer	>>>>	Fine Abilitazione
		// ABIL_AXGEN: Inizia quando RICH_ABIL_AXGEN=1, termina dopo un po di SFRENA_AXGEN=0

		if (!ASSE_AXGEN_CANOPEN && (RICH_ABIL_AXGEN || SFRENA_AXGEN))  RIT_DISABI_AXGEN=(int)R[R_RIT_DISABI_M];		//R795=80
		if ( ASSE_AXGEN_CANOPEN && (RICH_ABIL_AXGEN || SFRENA_AXGEN))  RIT_DISABI_AXGEN=(int)R[R_RIT_DISABI_C];		//R796=80
		else if (RIT_DISABI_AXGEN > 0)	RIT_DISABI_AXGEN--;

		ABIL_AXGEN = (RIT_DISABI_AXGEN > 0);

		//Nonostante manchi zimmer su assi canopen, gli serve cmq 1 ritardo simile ai mechatr. 
		//nella disabilitazione quando si interrompe ciclo con I_ANN e !AUTO_FOT_OK

		// ***********************************************************************************
		I_BLM_AXGEN = (!IBLM2_K1 || I_HLD_AXGEN || !COND_RIPARI_AXGEN);	// se (I_BLM_AXGEN == 0)  l'asse puo muoversi

		if(NUM_CHANNEL_AXGEN == 0)
		{
			DI_SERVON_CH0(ASSE_AXGEN) = ABIL_AXGEN;
			I_BLM_CH0(ASSE_AXGEN) = I_BLM_AXGEN;		// Richiesta sbloccaggio sw dell'asse
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			DI_SERVON_CH1(ASSE_AXGEN) = ABIL_AXGEN;
			I_BLM_CH1(ASSE_AXGEN) = I_BLM_AXGEN;		// Richiesta sbloccaggio sw dell'asse
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			DI_SERVON_CH2(ASSE_AXGEN) = ABIL_AXGEN;
			I_BLM_CH2(ASSE_AXGEN) = I_BLM_AXGEN;		// Richiesta sbloccaggio sw dell'asse
		}

		FRENO_AXGEN  = RICH_ABIL_AXGEN;				// Attualmente non utilizzato

		// ***********************************************************************************

		if (ASSE_AXGEN_CANOPEN)
		{	// assi canopen (passo passo) Rta o Schneider: attualmente nulla da fare
			if (!CONF_SCHNEIDER_PP)
			{/* RTA */ }
			else
			{/* SCHNEIDER */ }
		}
		else
		{	// assi Ethercat (azionamenti DELTA)
		}

		// ***********************************************************************************

		if (O_MOV_AXGEN && !ABIL_AXGEN)			// DEBUG: tiene traccia di cadute dell'abilitazione durante movim. assi
		{
			if((ASSE_AXGEN==AX_W_CH0) || (ASSE_AXGEN==AX_W_CH1))	TEST_000++;		// (1700)
			if(ASSE_AXGEN==AX_M10_CH2)	TEST_004++;		// (1704)
			if(ASSE_AXGEN==AX_M11_CH2)	TEST_005++;		// (1705)
			if(ASSE_AXGEN==AX_M12_CH2)	TEST_006++;		// (1706)
			if(ASSE_AXGEN==AX_M13_CH2)	TEST_007++;		// (1707)
			if(ASSE_AXGEN==AX_M14_CH2)	TEST_008++;		// (1708)
			if(ASSE_AXGEN==AX_M15_CH2)	TEST_009++;		// (1709)
		}

		if (!I_BLM_AXGEN && !ABIL_AXGEN)		// DEBUG: tiene traccia di cadute dell'abilitazione asse mentre IBLM abilita movimento
		{
			if((ASSE_AXGEN==AX_W_CH0) || (ASSE_AXGEN==AX_W_CH1))	TEST_060++;		// (2000)
			if(ASSE_AXGEN==AX_M10_CH2)	TEST_064++;		// (2004)
			if(ASSE_AXGEN==AX_M11_CH2)	TEST_065++;		// (2005)
			if(ASSE_AXGEN==AX_M12_CH2)	TEST_066++;		// (2006)
			if(ASSE_AXGEN==AX_M13_CH2)	TEST_067++;		// (2007)
			if(ASSE_AXGEN==AX_M14_CH2)	TEST_068++;		// (2008)
			if(ASSE_AXGEN==AX_M15_CH2)	TEST_069++;		// (2009)
		}

		// ***********************************************************************************


		// blocca movim assi canopen che a volte non si fermerebbero prima d'aver raggiunto la quota finale(20000) impostata dal cnc
		I_ANN_AXGEN = (ASSE_AXGEN_CANOPEN && MANO && !AUTO_CICLOMAN && (ARR_AVANTI_AXGEN || ARR_INDIETRO_AXGEN)) ||
			(I_ANN_AXGEN && (O_MOV_AXGEN || O_MOV2_AXGEN));

		if(NUM_CHANNEL_AXGEN == 0)
		{
			/* Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito */
			I_EME_CH0(ASSE_AXGEN) = I_EME_AXGEN;

			if(ASSE_AXGEN_CANOPEN)
			{
				/* Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì */
				I_ANN_CH0(ASSE_AXGEN) = 0;			// attualmente non funziona bene per gli LMD!!!!

				/* Hold asse indipendente */
				if(O_MOV2_AXGEN) 
					I_HLD_CH0(ASSE_AXGEN) = (I_HLD_AXGEN || I_ANN_AXGEN); // Hold asse indipendente 
				else 
					I_HLD_CH0(ASSE_AXGEN) = 0;
			}
			else
			{
				/* Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì */
				I_ANN_CH0(ASSE_AXGEN) = I_ANN_AXGEN;

				/* Hold asse indipendente */
				I_HLD_CH0(ASSE_AXGEN) = I_HLD_AXGEN;
			}

			/* Richiesta di libera servo : per azzerare l'errore di inseguimento (Non usare) */
			I_LSR_CH0(ASSE_AXGEN) = I_LSR_AXGEN && !I_BLC_CH0;

			/* Non fare blocco e allarme su cn (Non usare) */
			I_NAL_CH0(ASSE_AXGEN) = 0;
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			/* Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito */
			I_EME_CH1(ASSE_AXGEN) = I_EME_AXGEN;

			if(ASSE_AXGEN_CANOPEN)
			{
				/* Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì */
				I_ANN_CH1(ASSE_AXGEN) = 0;			// attualmente non funziona bene per gli LMD!!!!

				/* Hold asse indipendente */
				if(O_MOV2_AXGEN) 
					I_HLD_CH1(ASSE_AXGEN) = (I_HLD_AXGEN || I_ANN_AXGEN); // Hold asse indipendente 
				else 
					I_HLD_CH1(ASSE_AXGEN) = 0;
			}
			else
			{
				/* Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì */
				I_ANN_CH1(ASSE_AXGEN) = I_ANN_AXGEN;

				/* Hold asse indipendente */
				I_HLD_CH1(ASSE_AXGEN) = I_HLD_AXGEN;
			}

			/* Richiesta di libera servo : per azzerare l'errore di inseguimento (Non usare) */
			I_LSR_CH1(ASSE_AXGEN) = I_LSR_AXGEN && !I_BLC_CH1;

			/* Non fare blocco e allarme su cn (Non usare) */
			I_NAL_CH1(ASSE_AXGEN) = 0;
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			/* Richiesta emergenza asse : frena senza rampa, in modo diretto, rende asse non riferito */
			I_EME_CH2(ASSE_AXGEN) = I_EME_AXGEN;

			if(ASSE_AXGEN_CANOPEN)
			{
				/* Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì */
				I_ANN_CH2(ASSE_AXGEN) = 0;			// attualmente non funziona bene per gli LMD!!!!

				/* Hold asse indipendente */
				if(O_MOV2_AXGEN) 
					I_HLD_CH2(ASSE_AXGEN) = (I_HLD_AXGEN || I_ANN_AXGEN); // Hold asse indipendente 
				else 
					I_HLD_CH2(ASSE_AXGEN) = 0;
			}
			else
			{
				/* Annulla richiesta di movimento in corso senza allarme, il movimento finisce lì */
				I_ANN_CH2(ASSE_AXGEN) = I_ANN_AXGEN;

				/* Hold asse indipendente */
				I_HLD_CH2(ASSE_AXGEN) = I_HLD_AXGEN;
			}

			/* Richiesta di libera servo : per azzerare l'errore di inseguimento (Non usare) */
			I_LSR_CH2(ASSE_AXGEN) = I_LSR_AXGEN && !I_BLC_CH2;

			/* Non fare blocco e allarme su cn (Non usare) */
			I_NAL_CH2(ASSE_AXGEN) = 0;
		}

		// ***********************************************************************************


		/******* ASSE NON RIFERITO ********/
		if(NUM_CHANNEL_AXGEN == 0)
		{
			ASSE_AXGEN_NORIF = !O_SEE_CH0(ASSE_AXGEN);
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			ASSE_AXGEN_NORIF = !O_SEE_CH1(ASSE_AXGEN);
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			ASSE_AXGEN_NORIF = !O_SEE_CH2(ASSE_AXGEN);
		}

		/******* ANOMALIA AZIONAMENTO ASSE *******/
		if (RP_AUXON && TIMEOUT_DRIVE_AXGEN_NOK && !TERM_AXGEN_NOK_FAL)
			DRIVE_AXGEN_NOK_FAL = 1;

		// Flag anomalie azionamenti assi
		MEM_DRIVE_AXGEN_NOK_FAL = MEM_DRIVE_AXGEN_NOK_FAL || DRIVE_AXGEN_NOK_FAL;


		/**** override assi indipendenti ****/
		OVFRE_AXGEN = (unsigned short)OVFED_CH0;

		// Limitazione override minimo e massimo per assi CANOPEN (deve essere >0 e =<100)
		if (ASSE_AXGEN_CANOPEN)		
		{
			if(OVFRE_AXGEN < 20)    OVFRE_AXGEN = 20;
			if(OVFRE_AXGEN > 100)   OVFRE_AXGEN = 100;
			//if(CICLO_MANMORSE)      OVFRE_AXGEN = 80;   // Velocità fissa anche da pot. per movmorse tutte a SX/DX
		}

		if (ASSE_AXGEN_CANOPEN)		R[R_DEBUG_VELOC_CANOPEN] = OVFRE_AXGEN;

		// Override asse indipendente	
		if(NUM_CHANNEL_AXGEN == 0)
		{
			OVFRE_CH0(ASSE_AXGEN) = OVFRE_AXGEN;
		}
		else if(NUM_CHANNEL_AXGEN == 1)
		{
			OVFRE_CH1(ASSE_AXGEN) = OVFRE_AXGEN;
		}
		else if(NUM_CHANNEL_AXGEN == 2)
		{
			OVFRE_CH2(ASSE_AXGEN) = OVFRE_AXGEN;
		}


		// Aggiornamento vettori gestione assi **********************************************

		COM_AVANTI[NUM_CHANNEL_AXGEN][ASSE_AXGEN]	=	COM_AVANTI_AXGEN;
		COM_INDIETRO[NUM_CHANNEL_AXGEN][ASSE_AXGEN]	=	COM_INDIETRO_AXGEN;
		ARR_AVANTI[NUM_CHANNEL_AXGEN][ASSE_AXGEN]	=	ARR_AVANTI_AXGEN;
		ARR_INDIETRO[NUM_CHANNEL_AXGEN][ASSE_AXGEN]	=	ARR_INDIETRO_AXGEN;

		ASSE_NORIF[NUM_CHANNEL_AXGEN][ASSE_AXGEN]	=	ASSE_AXGEN_NORIF;
		ASSE_CANOPEN[NUM_CHANNEL_AXGEN][ASSE_AXGEN]	=	ASSE_AXGEN_CANOPEN;


		/**** Controllo posizione per verifiche su allarmi e ciclo ****/
		ASSE_AXGEN_SU_FCPOS = (POS_ATTUALE_AXGEN>(QUOTA_FCPOS_AXGEN-0.3))	&& !ASSE_AXGEN_NORIF;
		ASSE_AXGEN_SU_FCNEG	= (POS_ATTUALE_AXGEN<(QUOTA_FCNEG_AXGEN+0.3))   && !ASSE_AXGEN_NORIF;


		/**************** FUNZIONE ESEGUITA ***************************/
		ASSE_AXGEN_FUNES_B = 
			((COMANDO_B && O_JPOS_AXGEN && P_OSCILLATORE) || ASSE_AXGEN_SU_FCPOS)
			&& (FUNZ_MAN_JOG_AXGEN || FUNZ_MAN_INC_AXGEN);

		ASSE_AXGEN_FUNES_A = 
			((COMANDO_A && O_JNEG_AXGEN && P_OSCILLATORE) || ASSE_AXGEN_SU_FCNEG)
			&& (FUNZ_MAN_JOG_AXGEN || FUNZ_MAN_INC_AXGEN);



	}//NUM_ASSI

	//salta:;	// 

}


