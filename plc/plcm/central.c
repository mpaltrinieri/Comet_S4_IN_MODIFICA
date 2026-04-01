/*
        --------------------------------------------------------------
        TITOLO:         CENTRAL
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione centralizzati macchina
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    central(void)
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
        DATA:           30-08-2000
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

int TIME_PENDOLARE_ON;

int TIMECONT_CH0, TIMECONT_CH1, TIMECONT_CH2;	

int TIMEENDPROGRAM;

int testMan = 0;
int testAut = 0;

void    central(void)

{

/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
        lotime (T_IMP_RESET, 1.0f);  // Impulso di reset dei dispositivi
		
		// GLI ALTRI TIMER SONO TUTTI CARICATI DAL CONFMAC 
    
		R[R_SEL] = (float) 1;				/* All'accensione i comandi manuali vanno sul riferimento assi */
		
		// Parametri per DEBUG : messi al valore dell'asse/componente/utensile ne visualizzano lo stato dentro la SR generica
		R[R_DEBUG_ASSI]			= 100;      
		R[R_DEBUG_COMPONENTI]	= 100;
		R[R_DEBUG_UTENSILI]		= 100;

		// Lettura dei parametri Drill da memorie retentive
		R[R_DRILL_OPZ_MACCHINA1] = MM_DRILL_OPZ_MACCHINA1;
		R[R_DRILL_OPZ_MACCHINA2] = MM_DRILL_OPZ_MACCHINA2;
		}

// Aggiornamento memorie retentive dei parametri Drill
MM_DRILL_OPZ_MACCHINA1 = (int)(R[R_DRILL_OPZ_MACCHINA1]);
MM_DRILL_OPZ_MACCHINA2 = (int)(R[R_DRILL_OPZ_MACCHINA2]);


//-- Inserzione ausiliari ----
P_AUX_INSER = ( (R[R_DRILL_AUX]>0.5) && !RN_AUX_INSER ) || ( CONF_MGPILOT && MGPILOT_F1 && MGPILOT_F4 ) ;
AUX_INSER_O = P_AUX_INSER || RN_AUX_INSER;
R[R_LAMP_AUX] = AUX_INSER_I || AUX_INSER_O && P_OSCILLATORE || LAMP_TEST;
R[R_DRILL_AUX] = 0.0;


/***************** DIAGNOSTICA GENERALE ************************/

/* Bit di collaudo attivo : operazioni veloci abilitate */
COLLAUDO_ON = (R[R_COLLAUDO]==(float)3172);

COLLAUDO_ON_1 = ( (R[R_COLLAUDO]>1001.5) && (R[R_COLLAUDO]<1002.5) );	// 1002 Debug riparo anteriore. Attenzione: permette di non considerare i sensori relativi, analogo a forzare direttamente le uscite

/* Identifica condizione per bloccare tutti gli allarmi con R di Collaudo*/
ELIMINA_TUTTI_ALL	= (R[R_COLLAUDO]==(float)31247);

/* Attivo il bypass extracorsa */
if (R[R_COLLAUDO]==(float)7123)
				{
				// solo se siamo in manuale
				if (MANO) 
					{
					BYPASS_EXTRACORSA	= 1;
					}
					
				R[R_COLLAUDO]=(float)0;
				}


/* Disattivo il bypass extracorsa e resetto le eccezioni che fanno partire il multiprocesso */
if (RESET_MC)
				{
				BYPASS_EXTRACORSA = 0;
				R[R_POS_MORSE_ISO_ACT] = 0;  // Reset Posizionamento morse in ISO attivo
				}


// Appoggio la condizione di macchina con morse Mosse solo da ASSE X
MAC_VERSIONE_X = !MORSE_MOTORIZZATE;


/* Appoggio pressione tasti A-B per istruzioni ISO */
// Quattro combinazioni
if (!COMANDO_A	&& !COMANDO_B)	R[R_PLS_PREMUTO] = 0;
if (COMANDO_A	&& !COMANDO_B)	R[R_PLS_PREMUTO] = 1;
if (!COMANDO_A	&&  COMANDO_B)	R[R_PLS_PREMUTO] = 2;
if (COMANDO_A	&&  COMANDO_B)	R[R_PLS_PREMUTO] = 3;


/* Appoggio pressione tasti A-B per istruzioni ISO */
// Quattro combinazioni
// 0 non è un valore significativo
if (TAVOLA_IND_I)	R[R_STATO_TAVOLA] = 1;
if (TAVOLA_AVA_I)	R[R_STATO_TAVOLA] = 2;

// La condizione di sicurezza è la 0							
if (TRASC_MORSE_AX_X_DIS_I && !TRASC_MORSE_AX_X_INS_I) 
	R[R_STATO_TRASCMORSE]=0;	// disinserito
else	
	R[R_STATO_TRASCMORSE]=1;	// inserito

	
// Sposto le battute solo se sono in ingombro
APPO_SPOSTA_BATTUTE_SX = ( (int)(R[R_SPOSTA_BATTUTE_SX]+0.2) );
APPO_SPOSTA_BATTUTE_DX = ( (int)(R[R_SPOSTA_BATTUTE_DX]+0.2) );



/***************** RESET ALLARMI GENERALI ***********************/
if (RESET_ALL || RESET_MC)
        {
        ALIM_NOPRES_FAL =          0;
        EMERGENZA_FAL =            0;

        ARIA_NOPRES_FAL =          0;
        AUX_NOINS_FAL =            0;
        TEMP_NOK_FAL =             0;
        TERMICI_NOK_FAL =          0;

		ALIM_MM_NOT_OK_FAL =	   0;

        CNC_FAL =                  0;
		CNC1_FAL =                 0;
		CNC2_FAL =                 0;
        
        CONF_NOK_FAL =             0;

        RIPARO_POST_SX_CH_FAL =    0;
        RIPARO_POST_DX_CH_FAL =    0;

		TUN_RIP_LAT_SX_CH_FAL =    0;
		TUN_RIP_LAT_DX_CH_FAL =    0;

		GANCIO_MAG_NODIS_FAL =     0;
		GANCIO_MAG_NOFUOING_FAL =  0;

		MANDR_COLL_MAG_FAL =       0;

        CENTRALINA_FAL =           0;

        TERM_TRASP_FAL =           0;
        DRIVE_ALIM_FAL =           0;

		PLC_IEC_NOT_ALIVE_FAL =    0;
        }

if (RESET_MC)
        {
		VALORE_ERRATO_FAL =        0;
		R[R_VALORE_ERRATO] =       0;
		MOV_XYZ_FAL =              0;

		////COMUNIC_CAN_FAL		= 0;	Attualmente occorre riavviare il CNC per ristabilire la comunicazione Can coi disp quindi allarme non resettabile
		// @ mappa anche gli allarmi suoi parenti e portalo fuori da questa sr

		}



/******* Allarme assenza alimentazione agli azionamenti degli assi *******/

RIT_CONDIZ_AX_OK = RP_CONDIZ_AX_OK;

if	(
		RIT_CONDIZ_AX_OK && 
		(
			( !DO_PWR_X && DRIVE_X_OK && CONF_ASSE_X ) ||
			( !DO_PWR_Y && DRIVE_Y_OK && CONF_ASSE_Y ) ||
			( !DO_PWR_Z && DRIVE_Z_OK && CONF_ASSE_Z ) ||
			( !DO_PWR_A && DRIVE_A_OK && CONF_ASSE_A ) ||
			( !DO_PWR_C && DRIVE_C_OK && CONF_ASSE_C ) ||
			( !DO_PWR_W && DRIVE_W_OK && CONF_ASSE_W ) 
		) 
	)
	DRIVE_ALIM_FAL = 1;
if (DRIVE_ALIM_FAL)
        allarm (DRIVE_ALIM_AL);



/**** Allarme alimentazioni non presenti ****/
ALIM_NOPRES_FAL =	(AUTO && (!ALIM_PRES_I || ALIM_NOPRES_FAL)) ||
					(MANO && !ALIM_PRES_I);


/**** Allarme macchina in emergenza ****/
EMERGENZA_FAL = (AUTO && (!NO_EMERG_I && TEMP_OK_I && TERM_GEN_I && ALIM_PRES_I || EMERGENZA_FAL)) ||
				(MANO && !NO_EMERG_I && TEMP_OK_I && TERM_GEN_I && ALIM_PRES_I);



/**** Allarme assi in oltrecorsa ****/


// -------------------------- Inserire allarmi singoli


// Appoggio nessun extracorsa attivo
NESSUN_EXTRACORSA = 1;

/**** Allarme ausiliari non inseriti ( tolta NOEMER_PLC_O)****/
AUX_NOINS_FAL =	
	(AUTO && (!AUX_INSER_I && NO_EMERG_I && TERM_GEN_I && NESSUN_EXTRACORSA || AUX_NOINS_FAL)) ||
	(MANO && !AUX_INSER_I && NO_EMERG_I && TERM_GEN_I && NESSUN_EXTRACORSA);


/**** Allarme mancanza aria ****/
ARIA_NOPRES_FAL =
	(AUTO && (!APP_INPUT_ARIA_PRES && !RN_PRES_ARIA && ALIM_PRES_I || ARIA_NOPRES_FAL)) ||
	(MANO && !APP_INPUT_ARIA_PRES && !RN_PRES_ARIA && ALIM_PRES_I);



/**** Allarme temperatura armadio non ok ****/
if (!TEMP_OK_I && ALIM_PRES_I)
        TEMP_NOK_FAL = 1;


/**** Allarme termici scattati ****/
if (!TERM_GEN_I && ALIM_PRES_I)
        TERMICI_NOK_FAL = 1;

/***** Allarme alimentatori morse motorizzate in zona non OK *****/
if(MORSE_MOTORIZZATE && RP_TSuppl[TS_ALIM_MM_NOT_OK])
		ALIM_MM_NOT_OK_FAL = 1;

// ***** ALLARME GANCIO MAGAZZINO NON DISINSERITO *****
GANCIO_MAG_NODIS_FAL = CONF_GANCIO_MAGAZZINO && !GANCIO_MAG_NOINS_I && GANCIO_MAG_NODIS_I &&
	                   !(  GEST_OPERATORE_MAN || 
					       ( MANO && ( (FUNZ_MAN12 || FUNZ_MAN92) && COMANDO_B ) && (R[R_QUOTA_Z]<(R[R_QUOTA_ZMAX_GANCIO]-10)) ) ||    
						   ( MANO &&  ( (FUNZ_MAN12 || FUNZ_MAN92) && COMANDO_A ) && (R[R_QUOTA_Z]>(R[R_QUOTA_ZMIN_GANCIO]+10)) )
						 );

// ***** Allarme gancio magazzino non fuori ingombro (deve comparire anche semplicemente se l'ingresso GANCIO_MAG_NOINS_I trilla a seguito delle 
// ***** vibrazioni durante il ciclo di lavoro macchina)
if(CONF_GANCIO_MAGAZZINO && !GANCIO_MAG_NOINS_I && !GANCIO_MAG_NODIS_I)
	GANCIO_MAG_NOFUOING_FAL = 1;

/**** Allarme Centralina ****/
if (CONF_RIPARO_ANT && RP_TSuppl[TS_ALL_CENTRALINA] && RIPARI_POST_CHIUSI && CICLO_ON)
        CENTRALINA_FAL = 1;


/**** Termico Trasportatore Trucioli SX o DX scattato ****/
if (CONF_TRASP && !TERM_TRASP_OK_I && ALIM_PRES_I)
		TERM_TRASP_FAL = 1;



/**** Ripari Posteriori Non Chiusi ****/
/*Controllo i tentativi di movimento non SOLO sugli assi : anche se  loro rimarranno sempre in blocco con tutti i ripari */
TENTATIVO_MOVIMENTO = (FUNZ_MAN01 || 
					   FUNZ_MAN06 || 
					   FUNZ_MAN10 || 
					   FUNZ_MAN11 || 
					   FUNZ_MAN12 || 
					   FUNZ_MAN13 || 
					   FUNZ_MAN14 || 
					   FUNZ_MAN15 || 
					   FUNZ_MAN19 ||
					   FUNZ_MAN21 || 
					   FUNZ_MAN22 || 
					   FUNZ_MAN23 || 
					   FUNZ_MAN24 || 
					   FUNZ_MAN25 || 
					   FUNZ_MAN26 || 
					   FUNZ_MAN27 || 
					   FUNZ_MAN28 || 
					   FUNZ_MAN29 ||
					   FUNZ_MAN30 ||
					   FUNZ_MAN31 ||
					   FUNZ_MAN32 ||
					   FUNZ_MAN54 || 
					   FUNZ_MAN55 || 
					   FUNZ_MAN56 || 
					   FUNZ_MAN57 || 
					   FUNZ_MAN58 || 
					   FUNZ_MAN59 || 
					   
					   FUNZ_MAN64 ||
 
					   FUNZ_MAN74 || 
					   FUNZ_MAN75 || 
					   FUNZ_MAN76 || 
					   FUNZ_MAN77 || 
					   FUNZ_MAN78 || 
					   FUNZ_MAN79 || 
					   FUNZ_MAN80 || 
					   FUNZ_MAN81 || 
					   FUNZ_MAN82 || 
					   FUNZ_MAN90 || 
					   FUNZ_MAN91 || 
					   FUNZ_MAN92 || 
					   FUNZ_MAN93 || 
					   FUNZ_MAN94)		&&
					   
					   (COMANDO_A || COMANDO_B);


/*Riparo posteriore SX Non Chiuso*/
if (CONF_RIP_POST_SX && MACCHINA_PRONTA && !RIPARO_POST_SX_CH_I && AUTO)		
			RIPARO_POST_SX_CH_FAL = 1;

/*Riparo posteriore DX Non Chiuso*/
if (CONF_RIP_POST_DX && MACCHINA_PRONTA && !RIPARO_POST_DX_CH_I && AUTO)
			RIPARO_POST_DX_CH_FAL = 1;

/*Riparo laterale e tunnel SX Non Chiuso*/
if (MACCHINA_PRONTA && !APPO_TUN_RIP_LAT_SX_CH && AUTO)		
			TUN_RIP_LAT_SX_CH_FAL = 1;

/*Riparo laterale e tunnel SX Non Chiuso*/
if (MACCHINA_PRONTA && !APPO_TUN_RIP_LAT_DX_CH && AUTO)
			TUN_RIP_LAT_DX_CH_FAL = 1;

/* Controlli per allarmi confmac */
ALMENO_UNA_MORSA_CON_ZIMMER = 
					CONF_ZIMMER_MORSA_10 ||
					CONF_ZIMMER_MORSA_11 ||
					CONF_ZIMMER_MORSA_12 ||
					CONF_ZIMMER_MORSA_13 ||
					CONF_ZIMMER_MORSA_14 ||
					CONF_ZIMMER_MORSA_15;



/**** Allarme Configurazione CONFMAC errata ****/
/* Bit condizioni singole errori nel confmac */
ERR_CONFMAC_0	=	(SIMULATORE_ON && !CONF_CALC_TIME);			// In simulazione serve la funzione di calcolo tempi
ERR_CONFMAC_1	=	(CONF_MAGUT_10POSTI && CONF_MAGUT_12POSTI) || (!CONF_MAGUT_10POSTI && !CONF_MAGUT_12POSTI);
ERR_CONFMAC_2	=	BITOFF;
ERR_CONFMAC_3	=	BITOFF;
ERR_CONFMAC_4	=	BITOFF;
ERR_CONFMAC_5	=	BITOFF;
ERR_CONFMAC_6	=	BITOFF;
ERR_CONFMAC_7	=	BITOFF;
ERR_CONFMAC_8	=	BITOFF;
ERR_CONFMAC_9	=	BITOFF;
ERR_CONFMAC_10	=	BITOFF;
ERR_CONFMAC_11	=	BITOFF;
ERR_CONFMAC_12	=	BITOFF;
ERR_CONFMAC_13	=	BITOFF;
ERR_CONFMAC_14	=	BITOFF;
ERR_CONFMAC_15	=	BITOFF;

/* Controllo Word con condizioni per allarme CONFMAC errato */
if (WORD_ERR_CONFMAC != 0)
			CONF_NOK_FAL = 1;


if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{
	/**** Allarme per valore oltre soglie (generiche) previste da PC ****/
	if (R[R_VALORE_ERRATO] != (float)0)
		VALORE_ERRATO_FAL = 1;
}


/**** Allarme movimento assi X-Y-Z ****/
if (!(O_MOV_CH0(AX_X_CH0) && O_MOV_CH0(AX_Y_CH0) && O_MOV_CH0(AX_Z_CH0)))	// 0 1 1 -> reset
    TIMEMOVASSIXYZ = 50;
else
{
    if (TIMEMOVASSIXYZ > 0)
		TIMEMOVASSIXYZ--;
}
if (CONF_ALLMOV_XYZ && (TIMEMOVASSIXYZ == 0))
			MOV_XYZ_FAL = 1;


// Se Mgpilot presente gestisce appoggi funzioni
if (CONF_MGPILOT)
{
	COMANDO_A = MACCHINA_PRONTA && (RIPARI_CHIUSI_RIT || UOMO_MORTO_I) && MGPILOT_A && !COMANDO_B;
	COMANDO_B = MACCHINA_PRONTA && (RIPARI_CHIUSI_RIT || UOMO_MORTO_I) && MGPILOT_B && !COMANDO_A;

	COMANDO_AUX_A = MACCHINA_PRONTA && MGPILOT_A && !COMANDO_AUX_B;
	COMANDO_AUX_B = MACCHINA_PRONTA && MGPILOT_B && !COMANDO_AUX_A;

	// Da aggiungere la seguente parte per la gestione dei led della MGPilot
	// in central.c dopo l'aggiornamento di  R[R_FUNZESEG_A] ed R[R_FUNZESEG_B]		
	LAMP_ESEG_A = MANO && (R[R_FUNZESEG_A] == (float) 1);
	LAMP_ESEG_B = MANO && (R[R_FUNZESEG_B] == (float) 1);
	LAMP_CYCLE  = LAMP_CYCLE_APP;
}
else
{
	// Pulsanti A/B da DRILL
	COMANDO_A = MACCHINA_PRONTA && FTB(R[R_BUTTON_A]) && !COMANDO_B;
	COMANDO_B = MACCHINA_PRONTA && FTB(R[R_BUTTON_B]) && !COMANDO_A;

	COMANDO_AUX_A = COMANDO_A;
	COMANDO_AUX_B = COMANDO_B;
}


/**** Assi morse non riferiti ****/
ALMENO_UN_ASSE_MORSA_NON_RIFERITO = 	 
				ASSE_M10_NORIF && CONF_ASSE_M10	|| 
				ASSE_M11_NORIF && CONF_ASSE_M11	|| 
				ASSE_M12_NORIF && CONF_ASSE_M12	|| 
				ASSE_M13_NORIF && CONF_ASSE_M13	|| 
				ASSE_M14_NORIF && CONF_ASSE_M14	|| 
				ASSE_M15_NORIF && CONF_ASSE_M15;

/*** Passo il controllo a un par.R, il CNC riesegue nel caso l'azzeramento totale assi */
if (ALMENO_UN_ASSE_MORSA_NON_RIFERITO)
				R[R_MORSE_NON_RIFERITE] = 1;
			else
				R[R_MORSE_NON_RIFERITE] = 0;


/**** Assi non riferiti ****/
if (Mg_MC(65))
	Mr_MC(18);	// Reset M18 ad assi riferiti prima di reset M65

if (ASSE_X_NORIF && CONF_ASSE_X			||	 
	ASSE_Y_NORIF && CONF_ASSE_Y			||	 
	ASSE_Z_NORIF && CONF_ASSE_Z			||
	ASSE_A_NORIF && CONF_ASSE_A			||	 
	ASSE_C_NORIF && CONF_ASSE_C			||	 
	ASSE_W_NORIF && CONF_ASSE_W			||
	ALMENO_UN_ASSE_MORSA_NON_RIFERITO	||
	OBBLIGA_RIFERIMENTO					||
	Mg_MC(64))
        ASSI_NORIF_FMS = 1;

if (!ASSE_X_NORIF &&
	!ASSE_Y_NORIF &&  
	!ASSE_Z_NORIF && 
	!ASSE_A_NORIF && 
	!ASSE_C_NORIF && 
	!ASSE_W_NORIF &&
	
	!ASSE_M10_NORIF &&
	!ASSE_M11_NORIF &&
	!ASSE_M12_NORIF &&
	!ASSE_M13_NORIF &&
	!ASSE_M14_NORIF &&
	!ASSE_M15_NORIF &&
	
	Mg_MC(65))
        {
        ASSI_NORIF_FMS = 0;
		OBBLIGA_RIFERIMENTO = 0;
        Mr_MC(64);        /* Abilitazione assi durante riferimento */
        Mr_MC(65);        /* Conferma assi riferiti */
        }


ASSI_CNC1_NORIF_X = ASSE_X_NORIF;
ASSI_CNC1_NORIF_Y = ASSE_Y_NORIF;
ASSI_CNC1_NORIF_Z = ASSE_Z_NORIF;
ASSI_CNC1_NORIF_A = ASSE_A_NORIF;
ASSI_CNC1_NORIF_C = ASSE_C_NORIF;
ASSI_CNC1_NORIF_W = ASSE_W_NORIF;

R[R_ASSI_CNC1_RIF] = !(ASSI_CNC1_NORIF > 0);


ASSI_CNC2_NORIF_M10 = ASSE_M10_NORIF;
ASSI_CNC2_NORIF_M11 = ASSE_M11_NORIF;
ASSI_CNC2_NORIF_M12 = ASSE_M12_NORIF;
ASSI_CNC2_NORIF_M13 = ASSE_M13_NORIF;
ASSI_CNC2_NORIF_M14 = ASSE_M14_NORIF;
ASSI_CNC2_NORIF_M15 = ASSE_M15_NORIF;

R[R_ASSI_CNC2_RIF] = !(ASSI_CNC2_NORIF > 0);


/**** Macchina in HOLD ****/
PC_HOLD_FMS = PC_HOLD && !ALLARMI_PRES;

/**** Messaggio Potenziometro a Zero in Ciclo Automatico e nei CICLI MANUALI ****/
POTENZIOMETRO = (int) OVFED_CH0;
POT_ZERO_FMS = ( (AUTO_CICLOMAN && MANO) || (AUTO && CICLO_ON)) && RP_POT_ZERO;


/**** Messaggio di anomalia : Possibile corto su ingressi ritentivi ****/
if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{
	POSSIBILE_CORTO_FMS	= MACCHINA_PRONTA && (RP_TSuppl[TS_COND_POSSIBILE_CORTO] || CORTO_DIRETTO); 
}

// Messaggi di mancanza uscite pericolose con centralina OK   (CENTRALINA_OK_I)
// (agevolano la diagnostica degli allarmi DRIVE_X_ABIL_FAL, DRIVE_Y_ABIL_FAL, DRIVE_Z_ABIL_FAL, DRIVE_A_ABIL_FAL...)
CENTRALINA_RP = RP_TSuppl[TS_CENTRALINA_OK];		// Ritardo CENTRALINA_OK_I

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{
	NO_OUT_MAC_ABIL_FMS = !OUT_MAC_ABIL_I && RP_AUXON && CENTRALINA_RP;
}

/**** Macchina in HOLD : singole condizioni per visualizzazione ****/
// Hold dal magazzino (è in ingombro con il resto)
// Inserita anche la cammes 
if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
	MAGUT_HOLD = 0;
else
	MAGUT_HOLD = !ASSE_W_SU_FCNEG && !Mg_MC(72) && !Mg_MC(74) && !Mg_MC(10) && !Mg_MC(21) && (R[R_QUOTA_X]<R[R_POS_MIN_X_CAMB_UT]-1) && !(MANO && FUNZ_MAN07 && COMANDO_A) && !GEST_OPERATORE_MAN;

MAGUT_HOLD_FMS = MAGUT_HOLD;

/**** Messaggio di mandrino in potenziale collisione con magazzino ****/
MAN_COLL_MAG_FMS = MANDR_COLL_MAG;
if (MAN_COLL_MAG_FMS)
        attenz (MAN_COLL_MAG_MS);

if(SIMULATORE_SU_CN || SIMULATORE_SU_PC)
{
	Mr_MC(20);
}
// Verifica mandrino fuori ingombro magazzino
if (!MANDR_COLL_MAG)
	Mr_MC(20);

// Allarme ciclo iniziato con mandrini in potenziale collisione con magazzini
if (Mg_MC(20) && MANDR_COLL_MAG)
	MANDR_COLL_MAG_FAL = 1;
if	(MANDR_COLL_MAG_FAL)
		allarm (MANDR_COLL_MAG_AL);


// HOLD DA MORSE : non usato per ora
MORSE_SX_HOLD_FMS = MORSE_SX_HOLD = BITOFF;
MORSE_DX_HOLD_FMS = MORSE_DX_HOLD = BITOFF;


// HOLD DA MANDRINO : appoggiato
FEEDHOLD_MAND_FMS = FEEDHOLD_MAND;


// Appoggio nessun drive in allarme
NESSUN_DRIVE_IN_ALLARME = 
			(DRIVE_X_OK || !CONF_ASSE_X) && 
			(DRIVE_Y_OK || !CONF_ASSE_Y) && 
			(DRIVE_Z_OK || !CONF_ASSE_Z) && 
			(DRIVE_A_OK || !CONF_ASSE_A) && 
			(DRIVE_C_OK || !CONF_ASSE_C) && 
			
			(DRIVE_W_OK || !CONF_ASSE_W) && 
			
			(DRIVE_M10_OK || !CONF_ASSE_M10) && 
			(DRIVE_M11_OK || !CONF_ASSE_M11) && 
			(DRIVE_M12_OK || !CONF_ASSE_M12) && 
			(DRIVE_M13_OK || !CONF_ASSE_M13) && 
			(DRIVE_M14_OK || !CONF_ASSE_M14) && 
			(DRIVE_M15_OK || !CONF_ASSE_M15); 

// Reset Aree di memoria della Tastatura
if ( (R[R_DISAB_RESET_AREE_TAST]<0.5) && Mg_MC(69) )
{
	int I;
	short int *Punt;

	// Reset Aree A comprese tra A400 e A999   Utilizzate dal modulo di tastatura
	// Reset Aree A comprese tra A1000 e A2047 Utilizzate nel CNC per la Tastatura su 3 punti
	for (I=400;I<=2047;I++)
	{
		Punt = (&A0.word) + I;
		*Punt = 0;
	}

	// Reset delle aree A della tastatura obliqua
	memset(&TAST_OBLIQUA_FIRST_FLOAT, 0, (&TAST_OBLIQUA_LAST_FLOAT - &TAST_OBLIQUA_FIRST_FLOAT + 1)*sizeof(TAST_OBLIQUA_FIRST_FLOAT));

	Mr_MC(69);
}
else if( (R[R_DISAB_RESET_AREE_TAST]>0.5) && Mg_MC(69) )
{
	Mr_MC(69);
}


// **** INIZIO GESTIONE PRESSURIZZAZIONE MANDRINO ****

	// Pressurizzazione mandrino: modo collaudatore
	Press_mod_Collaudatore = ( ( fabs( Aris[R_PRESS_MAND_PSW] - (double)(PSW_collaudo) ) ) < 0.2 );

	// Pressurizzazione mandrino: modo shoowroom
	Press_mod_Shooroom =     ( ( fabs( Aris[R_PRESS_MAND_PSW] - (double)(PSW_shoowroom) ) ) < 0.2 );

	if(PON_dn)
	{
		// Reset iniziale della password collaudatore (non può permanere dopo il riavvio del FW per sicurezza)
		if (Press_mod_Collaudatore)
		{
			Press_mod_Collaudatore = 0;
			Aris[R_PRESS_MAND_PSW] = -1;
		}

		// Modalita Shoowroom: tempo pressurizzazione mandrino: 30 sec
		if(Press_mod_Shooroom)  R[R_PRESS_MAND_TIME] = 30;			

		// Tempo minimo in modo cliente: 10 minuti
		if(!Press_mod_Shooroom && (R[R_PRESS_MAND_TIME]<600))  R[R_PRESS_MAND_TIME] = 600;
										
		// Caricamento timer pressurizzazione mandrino
		R[R_NUM_CICLI_PRESS_MANDR] = R[R_TOT_CICLI_PRESS_MANDR] = (int)( (R[R_PRESS_MAND_TIME]) * 1000 / 4 );
	}

	// Modalita collaudatore
	// (dopo fine PON è gia stata eventualmente resettata la password collaudatore se salvata in confmac)
	if (P_PON && !PON && !PON_dn && Press_mod_Collaudatore)	
	{
		Press_mod_Collaudatore = 0;
		R[R_PRESS_MAND_PSW] = -2;
		R[R_PRESS_MAND_TIME] = 10;                                      // tempo pressurizzazione mandrino: 10 sec
		R[R_NUM_CICLI_PRESS_MANDR] = R[R_TOT_CICLI_PRESS_MANDR] = ( (R[R_PRESS_MAND_TIME]) * 1000 / 4 );
	}

	// Cumulativo ripari chiusi, per pressurizzazione mandrino 
	Ripari_Chiusi = APPO_RIPARO_CH && APPO_TUN_RIP_LAT_SX_CH && APPO_TUN_RIP_LAT_DX_CH && RIPARI_POST_CHIUSI ;

	// Assi in movimento in manuale, per pressurizzazione mandrino 
	Assi_in_movim = (O_JPOS_CH0 || O_JNEG_CH0 || O_JPOS_CH1 || O_JNEG_CH1 || O_JPOS_CH2 || O_JNEG_CH2 || O_JPOS_CH3 || O_JNEG_CH3 || Assi_M_in_Mov || Assi_S_in_Mov);

	// Abilitazione pressurizzazione mandrino  (indicazioni di Francesco Lolli)
	if ( (DP_RIT_PON) || AUTO_CICLOMAN || !Ripari_Chiusi || Assi_in_movim )  Abil_Press_Mand = 1;
	else                                                                     Abil_Press_Mand = 0;

	// Pilotaggio timer pressurizzazione mandrino
	// !Press_mod_Collaudatore => volendo evitare eventuali anomalie isac occorre spostar dopo la parte precedente che resetta Press_mod_Collaudatore 
	// !Press_mod_Collaudatore => evito eventuali anomalie isac attendendo che sia gia stato eventualm. reimpostato il timer prima di pilotarlo
	if (Abil_Press_Mand && P_PON && !PON && !PON_dn /*&& !Press_mod_Collaudatore*/)
	{
		R[R_NUM_CICLI_PRESS_MANDR] = R[R_TOT_CICLI_PRESS_MANDR];
	}
	else if (R[R_NUM_CICLI_PRESS_MANDR]>0.5)
	{
		R[R_NUM_CICLI_PRESS_MANDR]--;
	}

	// Pilotaggio uscita pressurizzazione mandrino
	PRESSURIZ_MAND_O = (R[R_NUM_CICLI_PRESS_MANDR]>0.5);

// **** FINE GESTIONE PRESSURIZZAZIONE MANDRINO ****


//Cumulativo ripari posteriori chiusi
RIPARI_POST_CHIUSI = (RIPARO_POST_SX_CH_I || !CONF_RIP_POST_SX) && 
                     (RIPARO_POST_DX_CH_I || !CONF_RIP_POST_DX);

// Hold dai ripari anteriori
RIPARI_HOLD_FMS = MANO && !RP_RIP_CH && RIPARI_POST_CHIUSI && AUX_INSER_I && NESSUN_DRIVE_IN_ALLARME;

// Hold apertura / chiusura ripari da posizione assi Y, A, C
HOLD_AP_CH_RIPARI_FMS = (MANO && (FUNZ_MAN02 || FUNZ_MAN100 || FUNZ_MAN101) && !CONS_AP_CH_RIPARI_DA_ASSI ) ||
						 AUTO && !CONS_AP_CH_RIPARI_DA_ASSI;

/**** Messaggio HOLD da FATM in Ciclo Automatico : solo per segnalare i blocchi****/
FATM_FMS = RP_TSuppl[TS_FATM_CH0];


/* Hold magazzino aperto quando non deve -----------------------<<<<<<<<<<<<<<<<<<<<<<<<<<*/
// Integrare 


/*************************** Programma in corso ***************************/
/**** Temporizzazione reset programma : evita sovrapposizioni software ****/
if (CICLO_ON)
	R[R_PROG_RUNNING] = 1;
if (M02 || RESET_MC)
	END_PROGRAM = 1;

if (!END_PROGRAM)
TIMEENDPROGRAM = 50;
else
	{
     if (TIMEENDPROGRAM > 0)
             TIMEENDPROGRAM--;
    }
if (END_PROGRAM && (TIMEENDPROGRAM == 0))
{
	R[R_PROG_RUNNING] = 0;
	END_PROGRAM = 0;
}


/**************************************************************************************/
/*************************** Identificazione stati Macchina ***************************/
/**************************************************************************************/

/************************************************************************/
/* Macchina in funzionamento singolo */
/************************************************************************/
CICLO_MULTI  = CICLO_ON && (R[R_DOUBLE]==0);


/**** Operazioni manuali libere abilitate ****/
if (MANO && ( (FUNZ_MAN99 && COMANDO_B) || COLLAUDO_ON) )
        GEST_OPERATORE_MAN = 1;
if (AUTO || RESET_MC || (FUNZ_MAN99 && COMANDO_A))
        GEST_OPERATORE_MAN = 0;


/**************** Fine Gestione PLC Master *****************/

/**** MACCHINA IN MANUALE ****/
MANO_MC = O_JOG_CH0 && O_JOG_CH1 && O_JOG_CH2;
MANO = SEL_MANU_I && MANO_MC;

/**** MACCHINA IN AUTOMATICO ****/
AUTO_MC = O_AUT_CH0 && O_AUT_CH1 && O_AUT_CH2;
AUTO = !(SEL_MANU_I) && AUTO_MC;						// Sostituito "(SEL_AUTO_I || SEL_SEMIAUTO_I)" con "!SEL_MANU_I" per non resettare CICLO_ON passando da automatico a semiautomatico

RESET_MC = O_RESET_CH0 || O_RESET_CH1 || O_RESET_CH2;

/**** Allarme CNC MASTER in allarme ****/
if (O_ALLAR_CH0 && ALIM_PRES_I) CNC_FAL = 1;
if (O_ALLAR_CH1 && ALIM_PRES_I) CNC1_FAL = 1;
if (O_ALLAR_CH2 && ALIM_PRES_I) CNC2_FAL = 1;

//*** CONTEMPORANEITA' DI STATO DEI CNC

//CNC non tutti in modalità manuale 
if (O_JOG_CH0) testMan += 1;
if (O_JOG_CH1) testMan += 2;
if (O_JOG_CH2) testMan += 4;

COND_ASINCRO_CNC_MAN = (RP_PON &&
	!RESET_MC &&
	(testMan >= 1) &&
	(testMan <= 14) &&
	!SEL_AUTO_I && !SEL_SEMIAUTO_I);

if (RP_TSuppl[TS_COND_ASINCRO_CNC_MAN]) COND_ASINCRO_CNC_MAN_FAL = 1;
if (RESET_ALL || RESET_MC) COND_ASINCRO_CNC_MAN_FAL = 0;

//CNC non tutti in modalità automatica
if (O_AUT_CH0) testAut += 1;
if (O_AUT_CH1) testAut += 2;
if (O_AUT_CH2) testAut += 4;

COND_ASINCRO_CNC_AUT = (RP_PON &&
	(testAut >= 1) &&
	(testAut <= 14) &&
	!RESET_MC &&
	!SEL_MANU_I);

if (RP_TSuppl[TS_COND_ASINCRO_CNC_AUT]) COND_ASINCRO_CNC_AUT_FAL = 1;
if (RESET_ALL || RESET_MC) COND_ASINCRO_CNC_AUT_FAL = 0;


/**** Condizioni minime attivate ****/
MACCHINA_PRONTA = ALIM_PRES_I && NO_EMERG_I && AUX_INSER_I;

// **** Ritardo di (0.2s) su Ripari chiusi e (1.0s) su uscite abilitate (immediate e ritardate) in manuale e automatico
RIPARI_CHIUSI_IMM	= RP_RIP_CH && RP_OUTMAC_ABIL;

// Ritardo di (1,5s) su Uscite pericolose abilitate (ritardate)
RIPARI_CHIUSI_RIT	= RP_OUTMAC_ABIL;	

/**** Macchina in automatico e Ripari chiusi SX e DX ****/
AUTO_RIP_CH	= AUTO_CICLOMAN && RIPARI_CHIUSI_IMM;
AUTO_RIP_CH_RIT = AUTO_CICLOMAN && RIPARI_CHIUSI_RIT;


/**** Condizioni di moto Generali : auto con ripari chiusi o manuale e linea attiva ****/
ABILITAZIONI_AUTO_MAN = AUTO_RIP_CH || MANO && MACCHINA_PRONTA;
ABILITAZIONI_AUTO_MAN_RIT = AUTO_RIP_CH_RIT || MANO && MACCHINA_PRONTA;


/**** CICLO MANUALE IN ESECUZIONE ****/
CICLOMAN = ( MANO && (STRINGA || RIFMANO || AXSHARED_DEFAULT_MANUAL_REQ || CICLO_ROTMAN ||CICLO_VOLROT || CICLO_PRELUT || CICLO_DEPUT || CICLO_CAMBUT_MAN || CICLO_POSRIP) );

/**** MACCHINA IN AUTO O CICLO MANUALE IN ESECUZIONE ****/
AUTO_CICLOMAN = AUTO || CICLOMAN;


/**** GESTIONE ABIL./DISABIL. POTENZIOMETRI ASSI MANDRINO ****/
if (Mg_MC(49))
        {
        DIS_POT = 1;
        Mr_MC(49);
        }
if (Mg_MC(48) || RESET_MC)
        {
        DIS_POT = 0;
        Mr_MC(48);
        }

/**** GESTIONE HOLD PER MACCHINA ****/

// Nella CT6 per togliere l'HOLD servono anche i pls separati
if ( ((DP_START_CYCLE || MGPILOT_START || (R[R_DRILL_START]>0.5) || (R[R_SIMON_START]>0.5) ) && !ALLARMI_PRES) || RESET_MC || !AUTO_CICLOMAN)
				M_HOLD = 0;

/**** Nella Comet T5/6 è ancora presente il fungo nero di HOLD sul pulpito ****/
if (MGPILOT_HOLD || (R[R_DRILL_HOLD]>0.5) || ALLARMI_PRES && AUTO)
{
	M_HOLD = 1;
	R[R_DRILL_HOLD] = (float) 0.0;
}


/**** GESTIONE HOLD PER PC ****/
if (DP_START_CYCLE || MGPILOT_START  || (R[R_DRILL_START]>0.5) || (R[R_SIMON_START]>0.5) || RESET_MC || MANO)
{
        PC_HOLD = 0;
}
if (M_HOLD && !Mg_MC(81) || ALLARMI_PRES)
        PC_HOLD = 1;

/**** RIFERIMENTO ASSI ****/
RIFMANO = MANO && FUNZ_MAN01 && COMANDO_B;

if (RIFMANO && DP_COMANDO_B)
        RIFMANO_REQ = 1;
if (Mg_MC(64) || RESET_MC)
        RIFMANO_REQ = 0;

//Richiesta assi condivisi assegnati ai canali di default
AXSHARED_DEFAULT_MANUAL_REQ = MANO && FUNZ_MAN160 && COMANDO_B;

//Richiesta attiva su comando manuale o dopo un reset con CNC in modo manuale
if (AXSHARED_DEFAULT_MANUAL_REQ && DP_COMANDO_B)
	AXSHARED_DEFAULT_REQ = 1;
if (RESET_MC)
	AXSHARED_DEFAULT_REQ = 0;

//Flag che indica che può essere eseguito il programma di assegnazione degli assi condivisi ai canali di default
if (RESET_MC) 
	AXSHARED_DEFAULT_RESET = 1;

//Richiesta attiva dopo un reset con CNC in modo manuale
if (!LEASED_DEFAULT && AXSHARED_DEFAULT_RESET && RP_TSuppl[TS_MANO] && !RESET_MC)  
	{AXSHARED_DEFAULT_RESET_REQ = 1; AXSHARED_DEFAULT_RESET = 0;}
	
if (LEASED_DEFAULT)
	{AXSHARED_DEFAULT_RESET_REQ = 0; AXSHARED_DEFAULT_RESET = 0;}

/**** Gestione Posizione di riposo ****/
CICLO_POSRIP = MANO && FUNZ_MAN06 && COMANDO_B;


if (CICLO_POSRIP && DP_COMANDO_B && !Mg_MC(247))
        POSRIP_REQ = 1;

if (Mg_MC(247) || RESET_MC)
		{
        POSRIP_REQ = 0;
		AXIS_RIPOSO = 0;
		}

if (!FUNZ_MAN06 || RESET_MC)	
		{
		Mr_MC(247);
		Mr_MC(248);
		}

if (Mg_MC(248))
        {
        AXIS_RIPOSO = 1;
        Mr_MC(247);
        Mr_MC(248);
        }
		


/**** ESECUZIONE COMANDI IN STRINGA ****/
STRINGA = MANO && FUNZ_MAN05 && COMANDO_B;

/**** START CICLO PER COMANDI IN STRINGA : attiva abilitazione per collaudo ****/
START_STRINGA = STRINGA && DP_COMANDO_B || DP_FRONTE_STRINGA;


// Appoggi segnali di assi MASTER in movimento
if(!CONF_ASSE_X) Asse_M_in_Mov_X_CH0 = Asse_M_in_Mot_X_CH0 =  0;
if(!CONF_ASSE_Y) Asse_M_in_Mov_Y_CH0 = Asse_M_in_Mot_Y_CH0 = 0;
if(!CONF_ASSE_Z) Asse_M_in_Mov_Z_CH0 = Asse_M_in_Mot_Z_CH0 = 0;
if(!CONF_ASSE_A) Asse_M_in_Mov_B_CH0 = Asse_M_in_Mot_B_CH0 = 0;
if(!CONF_ASSE_C) Asse_M_in_Mov_C_CH0 = Asse_M_in_Mot_C_CH0 = 0;
if(!CONF_ASSE_W) Asse_M_in_Mov_W_CH0 = Asse_M_in_Mot_W_CH0 = Asse_M_in_Mov_W_CH1 = Asse_M_in_Mot_W_CH1 = 0;

if(CONF_ASSE_X) Asse_M_in_Mov_X_CH0 = ((unsigned short)(O_MOV_CH0(AX_X_CH0)));
if(CONF_ASSE_Y) Asse_M_in_Mov_Y_CH0 = ((unsigned short)(O_MOV_CH0(AX_Y_CH0)));
if(CONF_ASSE_Z) Asse_M_in_Mov_Z_CH0 = ((unsigned short)(O_MOV_CH0(AX_Z_CH0)));
if(CONF_ASSE_A) Asse_M_in_Mov_B_CH0 = ((unsigned short)(O_MOV_CH0(AX_A_CH0)));
if(CONF_ASSE_C) Asse_M_in_Mov_C_CH0 = ((unsigned short)(O_MOV_CH0(AX_C_CH0)));
if(CONF_ASSE_W) Asse_M_in_Mov_W_CH0 = ((unsigned short)(O_MOV_CH0(AX_W_CH0)));
if(CONF_ASSE_W) Asse_M_in_Mov_W_CH1 = ((unsigned short)(O_MOV_CH1(AX_W_CH1)));

if(CONF_ASSE_X) Asse_M_in_Mot_X_CH0 = ((unsigned short)(O_MOT_CH0(AX_X_CH0)));
if(CONF_ASSE_Y) Asse_M_in_Mot_Y_CH0 = ((unsigned short)(O_MOT_CH0(AX_Y_CH0)));
if(CONF_ASSE_Z) Asse_M_in_Mot_Z_CH0 = ((unsigned short)(O_MOT_CH0(AX_Z_CH0)));
if(CONF_ASSE_A) Asse_M_in_Mot_B_CH0 = ((unsigned short)(O_MOT_CH0(AX_A_CH0)));
if(CONF_ASSE_C) Asse_M_in_Mot_C_CH0 = ((unsigned short)(O_MOT_CH0(AX_C_CH0)));
if(CONF_ASSE_W) Asse_M_in_Mot_W_CH0 = ((unsigned short)(O_MOT_CH0(AX_W_CH0)));
if(CONF_ASSE_W) Asse_M_in_Mot_W_CH1 = ((unsigned short)(O_MOT_CH1(AX_W_CH1)));


// Appoggi segnali di assi MORSE in movimento
if(!CONF_ASSE_M10) Asse_S_in_Mov_M10 = Asse_S_in_Mot_M10 = 0;
if(!CONF_ASSE_M11) Asse_S_in_Mov_M11 = Asse_S_in_Mot_M11 = 0;
if(!CONF_ASSE_M12) Asse_S_in_Mov_M12 = Asse_S_in_Mot_M12 = 0;
if(!CONF_ASSE_M13) Asse_S_in_Mov_M13 = Asse_S_in_Mot_M13 = 0;
if(!CONF_ASSE_M14) Asse_S_in_Mov_M14 = Asse_S_in_Mot_M14 = 0;
if(!CONF_ASSE_M15) Asse_S_in_Mov_M15 = Asse_S_in_Mot_M15 = 0;

if(CONF_ASSE_M10)  Asse_S_in_Mov_M10 = ((unsigned short)(O_MOV_CH2(AX_M10_CH2)));
if(CONF_ASSE_M11)  Asse_S_in_Mov_M11 = ((unsigned short)(O_MOV_CH2(AX_M11_CH2)));
if(CONF_ASSE_M12)  Asse_S_in_Mov_M12 = ((unsigned short)(O_MOV_CH2(AX_M12_CH2)));
if(CONF_ASSE_M13)  Asse_S_in_Mov_M13 = ((unsigned short)(O_MOV_CH2(AX_M13_CH2)));
if(CONF_ASSE_M14)  Asse_S_in_Mov_M14 = ((unsigned short)(O_MOV_CH2(AX_M14_CH2)));
if(CONF_ASSE_M15)  Asse_S_in_Mov_M15 = ((unsigned short)(O_MOV_CH2(AX_M15_CH2)));

if(CONF_ASSE_M10)  Asse_S_in_Mot_M10 = ((unsigned short)(O_MOV_CH2(AX_M10_CH2)));
if(CONF_ASSE_M11)  Asse_S_in_Mot_M11 = ((unsigned short)(O_MOV_CH2(AX_M11_CH2)));
if(CONF_ASSE_M12)  Asse_S_in_Mot_M12 = ((unsigned short)(O_MOV_CH2(AX_M12_CH2)));
if(CONF_ASSE_M13)  Asse_S_in_Mot_M13 = ((unsigned short)(O_MOV_CH2(AX_M13_CH2)));
if(CONF_ASSE_M14)  Asse_S_in_Mot_M14 = ((unsigned short)(O_MOV_CH2(AX_M14_CH2)));
if(CONF_ASSE_M15)  Asse_S_in_Mot_M15 = ((unsigned short)(O_MOV_CH2(AX_M15_CH2)));



/**** GESTIONE ARRESTO MOVIMENTI INCONTROLLATI ****/
if(!CONF_PLANCIA_CNC)
{
	JOG_HOLD = MANO && !COMANDO_A && !COMANDO_B && (O_JPOS_CH0 || O_JNEG_CH0 || O_JPOS_CH1 || O_JNEG_CH1 ||
		O_JPOS_CH2 || O_JNEG_CH2 || Assi_M_in_Mov || Assi_S_in_Mov);
}
else
{
	JOG_HOLD = 0;
}

if (!JOG_HOLD)            TIMEHOLDJOG = 100;
else if (TIMEHOLDJOG > 0) TIMEHOLDJOG--;

if (JOG_HOLD && (TIMEHOLDJOG <= 0))
	RICH_RESET_JOG = 1;
if (RESET_MC)
	RICH_RESET_JOG = 0;

/**** RICHIESTA DI RESET ****/
if ((MANO && FUNZ_MAN05 && DN_COMANDO_B && !CICLO_ROTMAN && !CICLO_VOLROT) 
	|| 	RICH_RESET_JOG || DP_MANU || DN_MANU || DP_AUXON || (RP_PON && !RESET_IN)
    || (MANO && !RIFMANO && (Mg_MC(64) || RIFMANO_REQ)) 
	|| (MANO && !AXSHARED_DEFAULT_MANUAL_REQ && AXSHARED_DEFAULT_REQ)
	|| (MANO && !CICLO_ROTMAN && !CICLO_VOLROT && (Mg_MC(71) || ROTMAN_REQ))
	//|| (MANO && !CICLO_MANMORSE && (Mg_MC(98) || MANMORSE_REQ))
	|| (MANO && !CICLO_POSRIP && (Mg_MC(247) || POSRIP_REQ)) 
	|| (MANO && !CICLO_DEPUT && (Mg_MC(72) || CICLO_DEPUT_REQ))
    || (MANO && !CICLO_PRELUT && (Mg_MC(74) || CICLO_PRELUT_REQ))
	|| (MANO && !CICLO_CAMBUT_MAN && (Mg_MC(114) || CICLO_CAMBUT_REQ)) 
	|| (Mg_MC(18) && M_HOLD)
	) 
		{
   		RICH_RESET_JOG = 0; // azzeram immediato della richiesta RICH_RESET_JOG x evitar che il mancato reset dello slave rigeneri reset su master
        
		RESET_IN = 1;		// reset iniziale eseguito

		RICH_RESET = 1;

        }
     
if (RESET_MC)	RICH_RESET = 0;


/**** NON EMERGENZA DA PLC ****/
NOEMER_PLC_O = !ALIM_NOPRES_FAL && !TEMP_NOK_FAL;
              

/**** TEST LAMPADE ****/
LAMP_TEST = MANO && FUNZ_MAN00 && (COMANDO_A || COMANDO_B);


/**** GESTIONE LAMPADA ALLARMI PRESENTI ****/
LAMP_ALLARMI = (ALLARMI_PRES && P_OSCILLATORE) || LAMP_TEST /*|| LAMP_PER_MESS*/;

/***** LAMPADA ALLARMI IN DRILL *****/
R[R_LAMP_ALLARMI] = (float) LAMP_ALLARMI;


//DEBUG  ************************************************************
if (TEST_027 > 30000)		TEST_027 = 0;
if (TEST_028 > 30000)		TEST_028 = 0;
if (ALLARMI_PRES)	TEST_027++;	// (1727)
if (LAMP_PER_MESS)	TEST_028++;	// (1728)




/**** GESTIONE LAMPADA START CICLO ****/
LAMP_CYCLE_APP = 
	(AUTO && (R[R_START]==1) && !CICLO_ON && !R[R_ERGO_PLS_PREMUTO] && !ALLARMI_PRES && P_OSCILLATORE) ||
	(AUTO && (R[R_START]==1) && !CICLO_ON && R[R_ERGO_PLS_PREMUTO] && !ALLARMI_PRES && P_OSCFAST) ||
	(AUTO && CICLO_ON && !Mg_MC(81)) ||
	(AUTO && CICLO_ON && Mg_MC(81) && P_OSCILLATORE) ||
	(AUTO && CICLO_ON && Mg_MC(81) && (R[R_CONF_OP_ERGO_MULTI]==4) ) ||	// in ergonomico faccio capire che è stata accetta la conferma lunga di start ciclo
     LAMP_TEST;

/***** LAMPADA START CICLO IN DRILL *****/
R[R_LAMP_START] = (float) LAMP_CYCLE_APP;

/***** USCITA CONTAORE *****/
// CONTAORE_O = CICLO_ON;

// Appoggio condizione morse da chiudere per lampeggio
APPO_MORSE_SX_LAMP = (APP_GRUPPO_MORSE_SX1 || APP_GRUPPO_MORSE_SX2);

// Appoggio condizione morse da chiudere per lampeggio
APPO_MORSE_DX_LAMP = (APP_GRUPPO_MORSE_DX3 || APP_GRUPPO_MORSE_DX4);


/**** GESTIONE LAMPADA ZONA SX PRONTA AL LAVORO ****/
/* In single è associata alla battuta */
LAMP_ZONA_SX_O = 
	(AUTO && CICLO_ON && CAR_MULTI_IN_CORSO && P_OSCILLATORE && (APPO_MORSE_SX_LAMP || APPO_MORSE_DX_LAMP) )
	|| (AUTO && CICLO_ON && SCA_MULTI_IN_CORSO && P_OSCFAST && (APPO_MORSE_SX_LAMP || APPO_MORSE_DX_LAMP) )
	|| ZONA_OK_LAV && !SCA_MULTI_IN_CORSO // !SCA_MULTI_IN_CORSO aggiunto per l'autofeed
	|| LAMP_TEST;


/**** GESTIONE FUNZIONE ESEGUITA B ****/
R[R_FUNZESEG_B] = (float)
				(ASSE_X_FUNES_B || ASSE_Y_FUNES_B || ASSE_Z_FUNES_B ||
				 ASSE_A_FUNES_B || ASSE_C_FUNES_B || ASSE_W_FUNES_B ||
                 BATTUTA_PREC_FUNES_B ||
				 INGRASS_FUNES_B ||

				 ASSE_M10_FUNES_B ||
				 ASSE_M11_FUNES_B ||
				 ASSE_M12_FUNES_B ||
				 ASSE_M13_FUNES_B ||
				 ASSE_M14_FUNES_B ||
				 ASSE_M15_FUNES_B ||

				 MANDRINO_FUNES_B	|| 
				 UT_SGANCIO_FUNES_B	||	
				 
				 CENTRAL_FUNES_B || 
				 LUBRICA_FUNES_B || 
				 REFSPEC_FUNES_B || 
				 				 			 
				 COMPONENTE_3_FUNES_B ||
				 
				 COMPONENTE_9_FUNES_B ||
				 COMPONENTE_12_FUNES_B ||

				 COMPONENTE_17_FUNES_B ||
				 COMPONENTE_18_FUNES_B ||
				 COMPONENTE_19_FUNES_B ||
				 COMPONENTE_20_FUNES_B ||
				 COMPONENTE_21_FUNES_B ||
				 COMPONENTE_22_FUNES_B ||

				 COMPONENTE_39_FUNES_B ||
				 COMPONENTE_40_FUNES_B ||

				 COMPONENTE_45_FUNES_B ||

				 COMPONENTE_49_FUNES_B ||
				 COMPONENTE_50_FUNES_B ||
				 COMPONENTE_51_FUNES_B ||
				 COMPONENTE_52_FUNES_B ||
				 COMPONENTE_53_FUNES_B || 
				 COMPONENTE_54_FUNES_B ||

				 COMPONENTE_58_FUNES_B ||
				 COMPONENTE_60_FUNES_B ||

				 CH_TUTTE_MORSE_FUNES_B ||

				 CICLO_CAMBUT_FUNES_B ||
				 (GEST_OPERATORE_MAN && FUNZ_MAN99)		||
			
				 UT1_FUNES_B ||
				 UT2_FUNES_B ||
				 UT3_FUNES_B ||
				 UT4_FUNES_B ||
				 UT5_FUNES_B ||
				 UT6_FUNES_B ||
				 UT7_FUNES_B ||
				 UT8_FUNES_B ||
				 UT9_FUNES_B ||
				 UT10_FUNES_B ||
				 UT11_FUNES_B ||
				 UT12_FUNES_B ||
				 
 				 ASP_FUNES_B ||
				 RIPARO_FUNES_B ||
				 VOLANT_FUNES_B ||
				 LAMP_TEST);

/**** GESTIONE FUNZIONE ESEGUITA A ****/
R[R_FUNZESEG_A] = (float)
				(ASSE_X_FUNES_A || ASSE_Y_FUNES_A || ASSE_Z_FUNES_A ||
				 ASSE_A_FUNES_A || ASSE_C_FUNES_A || ASSE_W_FUNES_A ||
                 BATTUTA_PREC_FUNES_A ||

				 ASSE_M10_FUNES_A ||
				 ASSE_M11_FUNES_A ||
				 ASSE_M12_FUNES_A ||
				 ASSE_M13_FUNES_A ||
				 ASSE_M14_FUNES_A ||
				 ASSE_M15_FUNES_A ||

                 MANDRINO_FUNES_A	|| 
				 UT_SGANCIO_FUNES_A	||	
				 
				 COMPONENTE_3_FUNES_A ||
				 
				 COMPONENTE_9_FUNES_A ||
				 COMPONENTE_12_FUNES_A ||

				 COMPONENTE_17_FUNES_A ||
				 COMPONENTE_18_FUNES_A ||
				 COMPONENTE_19_FUNES_A ||
				 COMPONENTE_20_FUNES_A ||
				 COMPONENTE_21_FUNES_A ||
				 COMPONENTE_22_FUNES_A ||

				 COMPONENTE_39_FUNES_A ||
				 COMPONENTE_40_FUNES_A ||

				 COMPONENTE_45_FUNES_A ||

				 COMPONENTE_49_FUNES_A ||
				 COMPONENTE_50_FUNES_A ||
				 COMPONENTE_51_FUNES_A ||
				 COMPONENTE_52_FUNES_A ||
				 COMPONENTE_53_FUNES_A || 
				 COMPONENTE_54_FUNES_A ||

				 COMPONENTE_58_FUNES_A ||
				 COMPONENTE_60_FUNES_A ||
				 			 
				 AP_TUTTE_MORSE_FUNES_A ||

				 CICLO_CAMBUT_FUNES_A ||
				 UT1_FUNES_A || 
				 UT2_FUNES_A || 
				 UT3_FUNES_A || 
				 UT4_FUNES_A || 
				 UT5_FUNES_A || 
				 UT6_FUNES_A || 
				 UT7_FUNES_A || 
				 UT8_FUNES_A || 
				 UT9_FUNES_A ||
				 UT10_FUNES_A ||
				 UT11_FUNES_A ||
				 UT12_FUNES_A ||
				 
				 ASP_FUNES_A ||
				 RIPARO_FUNES_A ||
				 VOLANT_FUNES_B ||
				 LAMP_TEST );




/************** GESTIONE SCAMBIO INFORMAZIONI CON PC ***********************/

/**** GESTIONE RICHIESTA START CICLO DA PC ****/
if (!AUTO || M_HOLD || RESET_MC)
        R[R_SEND_START] = 0.0;

if (R[R_SEND_START] > 0.5)
        {
        REQ_CICLO_ON = 1;
        R[R_SEND_START] = 0.0;
        }


// Reset richiesta partenza ciclo
if (Mg_MC(198) || RESET_MC)
		{
        REQ_CICLO_ON = 0;
		Mr_MC(198);
		}


// Reset memoria ciclo in corso
if (M02 || RESET_MC || !AUTO)
		{
        Mr_MC(195);
		}

//Copia di variabili da CH0 a CH1 e a CH2
Aris_CH1[R_W_MAX_MAGUT] = R[R_W_MAX_MAGUT];
Aris_CH2[R_VELFAST_POSMORSE] = R[R_VELFAST_POSMORSE];

Aris_CH2[R_MORSE_1_12_ASSOCIATE] = R[R_MORSE_1_12_ASSOCIATE];
Aris_CH2[R_MORSE_13_24_ASSOCIATE] = R[R_MORSE_13_24_ASSOCIATE];
Aris_CH2[R_OFFSET_POS_PEZZO] = R[R_OFFSET_POS_PEZZO];
Aris_CH2[R_MORSA_MASTER] = R[R_MORSA_MASTER];

//Temporizzatori timeout caricamento ISO in memoria
tS(TS_LOAD_ISO_CH1, (unsigned char) REQ_LOAD_ISO_CH1);
tS(TS_LOAD_ISO_CH2, (unsigned char) REQ_LOAD_ISO_CH2);

//Start abilitato da Drill
if (AUTO && (R[R_START] == 1) && DP_START_CYCLE && (R[R_ISOMG_UPDATED] == 1)) 
{
	R[R_TEST3932] += 1; 
	REQ_SEND_START_CH0_mem = REQ_SEND_START_CH1_mem = REQ_SEND_START_CH2_mem = 1;
	// Devo comandare il caricamento in memoria e dopo lo start dell'ISOMG dei vari canali
	R[R_ISOMG_UPDATED] = (float) 0;
}

//Se reset 
if (RESET_MC)
{
	LOAD_ISO_STATE_CH1 = 0;
	LOAD_ISO_STATE_CH2 = 0;

	LOAD_ISO_FAL = 0;
	LOAD_ISO_TIMEOUT_FAL = 0;

	REQ_SEND_START_CH0_mem = REQ_SEND_START_CH1_mem = REQ_SEND_START_CH2_mem = 0;
	REQ_LOAD_ISO_CH0 = REQ_LOAD_ISO_CH1 = REQ_LOAD_ISO_CH2 = 0;

	ISO_LOAD_CH0 = ISO_LOAD_CH1 = ISO_LOAD_CH2 = 0;

	ISOMG_CH1_ACTIVE = 0;
	ISOMG_CH2_ACTIVE = 0;

	R[R_ISOMG_UPDATED] = (float) 0;
	R[R_ENABLE_CK_ISOCODE] = (float) 0;

}	

//Richiesto lo start di un nuovo ISOMG ma che è ancora stato lanciato e caricato in memoria
COND_START_SU_CH1 = REQ_SEND_START_CH1_mem && !ISOMG_CH1_ACTIVE;
COND_START_SU_CH2 = REQ_SEND_START_CH2_mem && !ISOMG_CH2_ACTIVE;

// L' ISOMG del canale 0 viene caricato in memoria dal DRILL
if (AUTO && REQ_SEND_START_CH0_mem && !O_INIZ_CH0 && !REQ_LOAD_ISO_CH0 && !ISO_LOAD_CH0) {REQ_LOAD_ISO_CH0 = 1; ISO_LOAD_CH0 = 1;}
if (AUTO && COND_START_SU_CH1 && !O_INIZ_CH1 && !REQ_LOAD_ISO_CH1 && !ISO_LOAD_CH1) {REQ_LOAD_ISO_CH1 = 1; ISO_LOAD_CH1 = 0;}
if (AUTO && COND_START_SU_CH2 && !O_INIZ_CH2 && !REQ_LOAD_ISO_CH2 && !ISO_LOAD_CH2) {REQ_LOAD_ISO_CH2 = 1; ISO_LOAD_CH2 = 0;}

//Richiesto lo start di un nuovo ISOMG ma che non è ancora stato lanciato ma è già stato caricato in memoria
if (AUTO && !O_INIZ_CH0 && REQ_SEND_START_CH0_mem && ISO_LOAD_CH0) {REQ_CICLO_ON_CH0 = 1; REQ_SEND_START_CH0_mem = 0;}
if (AUTO && !O_INIZ_CH1 && REQ_SEND_START_CH1_mem && ISO_LOAD_CH1) {REQ_CICLO_ON_CH1 = 1; REQ_SEND_START_CH1_mem = 0;}
if (AUTO && !O_INIZ_CH2 && REQ_SEND_START_CH2_mem && ISO_LOAD_CH2) {REQ_CICLO_ON_CH2 = 1; REQ_SEND_START_CH2_mem = 0;}


//Se in manuale o in automatico e ISOMG in esecuzione
if (MANO || (AUTO && O_INIZ_CH0 && ISO_LOAD_CH0)) {ISO_LOAD_CH0 = 0; REQ_LOAD_ISO_CH0 = 0;}
if (MANO || (AUTO && O_INIZ_CH1 && ISO_LOAD_CH1)) {ISO_LOAD_CH1 = 0;}
if (MANO || (AUTO && O_INIZ_CH2 && ISO_LOAD_CH2)) {ISO_LOAD_CH2 = 0;}

if (O_ESEC_CH0 || RESET_MC)
	REQ_SEND_START_CH0 = REQ_CICLO_ON_CH0 = 0;

if (O_ESEC_CH1 || RESET_MC)
	REQ_SEND_START_CH1 = REQ_CICLO_ON_CH1 = 0;

if (O_ESEC_CH2 || RESET_MC)
	REQ_SEND_START_CH2 = REQ_CICLO_ON_CH2 = 0;


// Gestione selezione ISO da eseguire CH1 - CH2
if (!RESET_MC)
{
	sendStartCNC_CH1();
	sendStartCNC_CH2();
}


// Reset flag di ISOMG ATTIVO attivo con le M02 del canale corrispondente
if(M_CH1_02)
	ISOMG_CH1_ACTIVE = 0;

if(M_CH2_02)
	ISOMG_CH2_ACTIVE = 0;
	
// Reset causale ISO multichannel (scritta da CH0 e usata dagli altri canali)
if(!AUTO || (!ISOMG_CH1_ACTIVE && !ISOMG_CH2_ACTIVE))
	R[R_CAUSALE_ISO_MC_CH0] = (float) 0;

// Copia delle variabili causale ISO multichannel sui vari canali:
Aris_CH2[R_CAUSALE_ISO_MC_CH0] = Aris_CH1[R_CAUSALE_ISO_MC_CH0] = R[R_CAUSALE_ISO_MC_CH0];
R[R_CAUSALE_ISO_MC_CH1] = Aris_CH1[R_CAUSALE_ISO_MC_CH1]; // Questa copia solo per facilità di debug: visualizzo sul CH0
R[R_CAUSALE_ISO_MC_CH2] = Aris_CH2[R_CAUSALE_ISO_MC_CH2]; // Questa copia solo per facilità di debug: visualizzo sul CH0


/**** GESTIONE CICLO IN CORSO ****/
if(	(DP_START_CYCLE || REQ_CICLO_ON || REQ_CICLO_ON_CH0) && AUTO && (R[R_START] > 0.5) )
{
	M00 = 0;
	CICLO_ON = 1;
}

// GESTIONE CICLO IN CORSO CH1
if (  ( (DP_START_CYCLE || REQ_CICLO_ON_CH1) && AUTO && (R[R_START] > 0.5) ) || 
	REQ_CICLO_ON_CH1 && AUTO_CICLOMAN )
{
	CICLO_ON_CH1 = 1;
	ISOMG_CH1_ACTIVE = 1;
	M_CH1_00 = 0;
}
// GESTIONE CICLO IN CORSO CH2
if ( (DP_START_CYCLE || REQ_CICLO_ON_CH2) && AUTO && (R[R_START] > 0.5) )
{
	CICLO_ON_CH2 = 1;
	ISOMG_CH2_ACTIVE = 1;
	M_CH2_00 = 0;
}


// Reset ciclo in corso
if (M_HOLD || RESET_MC || (M02 && !SINGOLO_ON) || !AUTO || ALLARMI_PRES || (M00 && !O_ESEC_CH0))
{
	CICLO_ON = 0;
	//M00 = 0;
}

if (M_HOLD || RESET_MC || M_CH1_02 || !AUTO || ALLARMI_PRES || (M_CH1_00 && !O_ESEC_CH1))
{
	CICLO_ON_CH1 = 0;
	//M_CH1_00 = 0;		
}

if (M_HOLD || RESET_MC || M_CH2_02 || !AUTO || ALLARMI_PRES || (M_CH2_00 && !O_ESEC_CH2))
{
	CICLO_ON_CH2 = 0;
	//M_CH2_00 = 0;		
}


//*********************************
// Reset variabili di Debug per MULTICANALE
if(R[R_TEST3910] > 30000 || RESET_ALL) R[R_TEST3910] = (float) 0;
if(R[R_TEST3911] > 30000 || RESET_ALL) R[R_TEST3911] = (float) 0;
if(R[R_TEST3912] > 30000 || RESET_ALL) R[R_TEST3912] = (float) 0;
if(R[R_TEST3913] > 30000 || RESET_ALL) R[R_TEST3913] = (float) 0;

if(DP_START_CYCLE)	R[R_TEST3910]++;
if(M02)				R[R_TEST3911]++;
if(CICLO_ON)		R[R_TEST3912]++;
if(O_ESEC_CH0)		R[R_TEST3913]++;

R[R_TEST3920] = REQ_CICLO_ON;
R[R_TEST3921] = CICLO_ON;
R[R_TEST3922] = O_ESEC_CH0;

R[R_TEST3923] = REQ_CICLO_ON_CH1;
R[R_TEST3924] = CICLO_ON_CH1;
R[R_TEST3925] = O_ESEC_CH1;

R[R_TEST3926] = REQ_CICLO_ON_CH2;
R[R_TEST3927] = CICLO_ON_CH2;
R[R_TEST3928] = O_ESEC_CH2;


//*********************************



/********************** Reset rotazione pezzo in corso ********************/
if (RESET_MC)
		R[R_ROT_PIECE] = 0;





/**** INVIO INFORMAZIONI AL PC ****/
/* Stato macchina */
if (AUTO) //|| SIMULATORE_ON)
        R[R_STATUS] = (float)0;
else if (MANO)
        R[R_STATUS] = (float)1;
else
        R[R_STATUS] = (float)255;

// Appoggio input macchina in semiautomatico
R[R_MACCHINA_IN_SEMIAUTO] = SEL_SEMIAUTO_I;

// Appoggio reset in corso per HDRILL:
R[R_RESET_IN_CORSO] = RESET_MC;

/* HOLD macchina */
R[R_HOLD] = (float)PC_HOLD;

/* Ciclo macchina */
R[R_CYCLE] = (float)(CICLO_ON || (Mg_MC(81) && !ALLARMI_PRES));

/* Conteggio tempo ciclo */
R[R_CONTAORE] = (float)CICLO_ON;

/* Assi riferiti */
R[R_RIFERIM] = Aris_CH1[R_RIFERIM] = Aris_CH2[R_RIFERIM] = (float)!ASSI_NORIF_FMS;

/* Inibizione uscita da WINDOWS */
R[R_NO_EXIT] = (float)(NO_EMERG_I && NO_EXIT_SIMU && !COLLAUDO_ON && !CONF_USCITA_DRILL);


/* Rimetti CNC CH0 in modo continuo */
if (AUTO_CICLOMAN && O_CNT_CH0)
	TIMECONT_CH0 = 100;
else
{
	if (TIMECONT_CH0 > 0)
		TIMECONT_CH0--;
}
/* Rimetti CNC CH1 in modo continuo */
if (AUTO_CICLOMAN && O_CNT_CH1)
	TIMECONT_CH1 = 100;
else
{
	if (TIMECONT_CH1 > 0)
		TIMECONT_CH1--;
}
/* Rimetti CNC CH2 in modo continuo */
if (AUTO_CICLOMAN && O_CNT_CH2)
	TIMECONT_CH2 = 100;
else
{
	if (TIMECONT_CH2 > 0)
		TIMECONT_CH2--;
}

R[R_CNC_CONT] = (float)((AUTO_CICLOMAN && O_CNT_CH0) || (TIMECONT_CH0 > 0));
Aris_CH1[R_CNC_CONT] = (float)((AUTO_CICLOMAN && O_CNT_CH1) || (TIMECONT_CH1 > 0));
Aris_CH2[R_CNC_CONT] = (float)((AUTO_CICLOMAN && O_CNT_CH2) || (TIMECONT_CH2 > 0));



/* Programma finito : resetto in  manuale */
if(!SIMULATORE_SU_CN && !SIMULATORE_SU_PC)
{
	if (!AUTO)
		R[R_PROG_FINITO] = 0;
}


/* Stop da operatore */
if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{
	if (R[R_START] == (float)1)
			PC_START = 1;
	if (R[R_START] == (float)0)
			PC_START = 0;
	if (PC_START && RESET_MC)
			R[R_STOP_PROG] = (float)1;
	if (!PC_START)
			R[R_STOP_PROG] = (float)0;
}

//********************************************************************
//***************** ALLARME SU NOT ALIVE PLC IEC *********************
//********************************************************************

tS(TS_PLC_IEC_NOT_ALIVE, (unsigned char) PLC_IEC_NOT_ALIVE);

if( (AF_INVERTER_0_COM01_MODBUS>0.5) || (AF_ASSE_0_CH_NUM_TECH01_ADDRESS>0.5) || (AF_ASSE_1_CH_NUM_TECH01_ADDRESS>0.5) || (AF_ASSE_2_CH_NUM_TECH01_ADDRESS>0.5) ||
                                        (AF_ASSE_3_CH_NUM_TECH01_ADDRESS>0.5) || (AF_ASSE_4_CH_NUM_TECH01_ADDRESS>0.5) ||
										(R[R_INDEX_M_LASER]>0.5) )
{
	if(AF_ALIVE_COM_CON_PLC_IEC != OLD_ALIVE_COM_CON_PLC_IEC)
		PLC_IEC_NOT_ALIVE = 0;
	else
		PLC_IEC_NOT_ALIVE = 1;
	
	OLD_ALIVE_COM_CON_PLC_IEC = AF_ALIVE_COM_CON_PLC_IEC;

	if(RP_TSuppl[TS_PLC_IEC_NOT_ALIVE])
		PLC_IEC_NOT_ALIVE_FAL = 1;
}



/******* FUNZIONE ESEGUITA ********/
CENTRAL_FUNES_B = (((Mg_MC(64) && P_OSCILLATORE)  || !ASSI_NORIF_FMS) && FUNZ_MAN01) ||
				  (((Mg_MC(247) && P_OSCILLATORE) || AXIS_RIPOSO) && FUNZ_MAN06) ||
                   STRINGA || LOAD_PROG;


}




