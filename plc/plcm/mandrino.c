/*
        --------------------------------------------------------------
        TITOLO:         MANDRINO
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione mandrino
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    mandrino(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:           LOAD_INVEROK_I   Inverter non in sovraccarico
                         VEL_INVERTEROK_I Velocit… inverter Ok
                         INV_NONBLOC_I    Inverter non in blocco
                         UT_AGGAN_I       Utensile mandrino agganciato
                         UT_SGANC_I       Utensile mandrino sganciato
                         VEL_MANDR_I      Segnale velocit… mandrino
                         R[R_ACT_TOOL]    Utensile attivo su mandrino
                         MANDRINO_FERMO_I | INVERTER_0_INV_MANDR_FERMO  Mandrino fermo (da inverter: M3) (valido solo se presente encoder mandrino)
                         MANDRINO_VIBR_TEMP_OK   Appoggio segnale di Vibrazioni e temperatura OK nel mandrino (0: interrompe start inverter)
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         START_INVERTER_O | INVERTER_0_START_INV_FW    Start inverter mandrino
                        RESET_INVERTER_O | INVERTER_0_RESET_INVERTER  Reset inverter mandrino
                        ALIM_MANDR_O                                  Alimentazione motore mandrino
                        SBLOC_UT_O                                    Sbloccaggio utensile su mandrino
                        MASC_RIGID_O     | INVERTER_0_MASCH_RIGIDA
                        ACC_INV_AB_O     | INVERTER_0_INCLUS_RAMPE;

                        DRIVEM_NOK_AL     All. inverter mandrino non ok
                        DRIVEM_NOK_FAL    Flag inverter mandrino non ok
                        DRIVEM_PREA_AL    All. inverter mandrino in preallarme
                        DRIVEM_PREA_FAL   Flag inverter mandrino in preallarme
                        MANDRINO_HOLD_AL  All. velocita' mandrino non a regime
                        MANDRINO_HOLD_FAL Flag velocita' mandrino non a regime
                        UT_NOSBL_AL       All. time out utensile mandrino non sbloccato
                        UT_NOSBL_FAL      Flag time out utensile mandrino non sbloccato
                        UT_NOBLO_AL       All. time out utensile mandrino non bloccato
                        UT_NOBLO_FAL      Flag time out utensile mandrino non bloccato
                        UT_DISFC_AL       All. disfunzione F.C.bloccaggio utensile
                        UT_DISFC_FAL      Flag disfunzione F.C.bloccaggio utensile
        --------------------------------------------------------------
        --------------------------------------------------------------

        NUOVI FLAG DEL PLC IEC:
                        INV_NONBLOC_I        >> INVERTER_0_INV_NOIN_BLOCCO
                        LOAD_INVERTEROK_I    >> INVERTER_0_INV_NO_OVERLOAD 
                        VEL_INVERTEROK_I     >> INVERTER_0_INV_VEL_OK
                        MANDRINO_FERMO_I     >> INVERTER_0_INV_MANDR_FERMO
                        
                        START_INVERTER_O     >> INVERTER_0_START_INV_FW    
                        RESET_INVERTER_O     >> INVERTER_0_RESET_INVERTER  
                        MASC_RIGID_O         >> INVERTER_0_MASCH_RIGIDA    
                        ACC_INV_AB_O         >> INVERTER_0_INCLUS_RAMPE    

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

void com_con_inverter_INPUT(void);   // Input per PLC --> output dell'inverter
void com_con_inverter_OUTPUT(void);  // Output per PLC --> input per inverter

CONF_CN CONFIGURAZIONE_CNN;
float  TAUN;
float  VEL_MAX;
double RIF_MANDR;
double appdouble;
int    TIME_MEM_MASCRIG;


int SBLOC_UT, UT_SBLOC, SBLOC_UT_COUNT, SBLOC_UT_MEMCOUNT, SBLOC_UT_MEM;
char SBLOC_UT_COMMENTO[80] = "{Tempo sbloccaggio utensile}";
int BLOCC_UT, UT_BLOCC, BLOCC_UT_COUNT, BLOCC_UT_MEMCOUNT, BLOCC_UT_MEM;
char BLOCC_UT_COMMENTO[80] = "{Tempo bloccaggio utensile}";




void    mandrino(void)

{

if (CONF_MANDRINO)
{

/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
		// Temporizzatore mandrino fermo caricato esternamente nel timerssuppl.inc
        
        // Tutti i Timer trasferiti in CONFMAC
        
        
        
            MEM_MANDRINO_FERMO = 1;

			GetConfCn (&CONFIGURAZIONE_CNN);
		    TAUN = (float)CONFIGURAZIONE_CNN.tau;
			read_var (VL_FLOT, 4054, -1, AX_Q_CH0, &VEL_MAX);
			appdouble =(double)(((double)VEL_MAX * 60) / ((double)TAUN * 360));
			VEL_MAX = (float)(appdouble);
		
        }

//ESECUZIONE PROGRAMMA SIMULATO
if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
{
   INV_NONBLOC_I   = 1;
   //R[R_MAND_ROTAZ] = 0;
   VEL_MANDR_I = (INVERTER_0_START_INV_FW && P_OSCILLATORE); 
	
   if(!INVERTER_0_START_INV_FW) MANDRINO_FERMO_I = 1;
   else MANDRINO_FERMO_I = 0;
}

//*****************************************************************
//****** LETTURA INPUT PLC (OUTPUT DELL'INVERTER) DA PLC IEC ******
//*****************************************************************
com_con_inverter_INPUT();

// Modifica il feed forward del mandrino per aggancio in velocità o in posizione
if (MEM_MAN_AGG_AVV && !O_AVV_CH0 (AX_Q_CH0)) {
    REQ_FF_SPINDLE_R = 1;
    REQ_FF_SPINDLE_100 = 0;
} else if (!MEM_MAN_AGG_AVV && O_AVV_CH0 (AX_Q_CH0)) {
    REQ_FF_SPINDLE_R = 0;
    REQ_FF_SPINDLE_100 = 1;
}
MEM_MAN_AGG_AVV = O_AVV_CH0 (AX_Q_CH0) ? 1 : 0;

/**** GESTIONE SPEED E DIREZIONE PER INVERTER MANDRINO ****/
			read_var (VL_FLOT, 6058, -1, AX_Q_CH0, &RIF_MANDR);
			appdouble = (double)((double)RIF_MANDR * 60 / (double)TAUN);
			appdouble = (double)((appdouble / (double)VEL_MAX) * 32766);
			if ( appdouble > 32766 )
				appdouble = 32766;
			if ( appdouble < -32766 )
				appdouble = -32766;
			RIF_MANDR = appdouble;

			APP_RIF_MANDRINO = (int)RIF_MANDR; // Appoggio per visualizzazione


/************ APPOGGIO VELOCITA DI ROTAZIONE MANDRINO PER VISUALIZZAZIONE ************/

R[R_APP_VEL_MANDR] = (float) O_TDS_CH0 ;

if(INVERTER_0_START_INV_FW)
{
      R[R_VIS_VEL_ROT_MANDR] = ((double) (APPOVSPE/100.0)) * R[R_APP_VEL_MANDR];
}
else
{
      R[R_VIS_VEL_ROT_MANDR] = (double) 0;
}



/*************** RESET ALLARMI MANDRINO ***************/
if (RESET_ALL || RESET_MC)
	{
	DRIVEM_NOK_FAL =      0;
	DRIVEM_PREA_FAL =     0;
	MANDRINO_FERMO_FAL =  0;
	MANDRINO_HOLD_FAL =   0;
	UT_NOSBL_FAL =        0;
	UT_NOBLO_FAL =        0;
	UT_DISFC_FAL =        0;
	UT_NOAGG_FAL =        0;
	
	FLUSSOSTATO_FAL =     0;
	TERM_FRIGO_NOK_FAL =  0;

	MANDRINO_VIBR_FAL =   0;
	MANDRINO_TEMP_FAL =   0;
	}

//****** Appoggio su flag del ritardo negativo di utensile agganciato per consensi vari ******
tS(TS_TOOL_AGGAN, (unsigned char) UT_AGGAN_I); 

TOOL_AGGANCIATO = RN_TSuppl[TS_TOOL_AGGAN];

//***** MASC_RIGID_O collegato su S5, ACC_INV_AB_O collegato su S6
// MASC_RIGID_O definisce il TIPO MOTORE: 0=mot.1 (anello chiuso); 1=mot.2 (anello aperto) (S5)
INVERTER_0_MASCH_RIGIDA = !CONF_MASK_RIGIDA;

// Inclusione rampe inverter (S6)
INVERTER_0_INCLUS_RAMPE = !APP_M19 && !G184_CH0;


// MASCHIATURA RIGIDA IN ANELLO CHIUSO
if (Mg_MC(226) && AUTO_CICLOMAN)
{
	MEM_MASCRIG = 1;
	Mr_MC(226);
}
if (Mg_MC(227) || RESET_MC && MEM_MASCRIG)
{
	MEM_MASCRIG = 0;
	Mr_MC(227);
	SET_MAN_FERMO = 1;
}
if(MANDRINO_FERMO)
	SET_MAN_FERMO = 0;
	
PROL_MEM_MASCRIG = 0;
if (MEM_MASCRIG)
        TIME_MEM_MASCRIG = 200;
else
        {
        if (TIME_MEM_MASCRIG > 0)
                {
                TIME_MEM_MASCRIG--;
                PROL_MEM_MASCRIG = 1;
                }
        }


R[R_MASCRIG_ACT] = (float)MEM_MASCRIG;


// GESTIONE I_BLC
	// HMI: [HOLD] (rosso)
	// HMI > view > variable > CometS4 > All > CNCCTRL_CH1 > BLC 
	// HMI > view > variable > CometS4 > All > CNCCTRL_CH1 > BLCAX
I_BLC_CH0  =  ( (PC_HOLD) ? (RTPLC_TRUE) : (RTPLC_FALSE) );
if (DN_I_BLC_CH0)
		NO_I_BLC_CH0 = 1;
if (!O_BLC_CH0)
		NO_I_BLC_CH0 = 0;

I_BLC_CH1  = ( (PC_HOLD) ? (RTPLC_TRUE) : (RTPLC_FALSE) );
if (DN_I_BLC_CH1)
		NO_I_BLC_CH1 = 1;
if (!O_BLC_CH1)
		NO_I_BLC_CH1 = 0;

I_BLC_CH2  = ( (PC_HOLD) ? (RTPLC_TRUE) : (RTPLC_FALSE) );
if (DN_I_BLC_CH2)
		NO_I_BLC_CH2 = 1;
if (!O_BLC_CH2)
		NO_I_BLC_CH2 = 0;


// Visualizzazioni segnali Isac
VIS_I_BLC_CH0 = I_BLC_CH0 ;
VIS_O_BLC_CH0 = O_BLC_CH0 ;



/**** INIBIZIONE HOLD MANDRINO PER MASCHIATURA RIGIDA ****/
if (G184_CH0  || Mg_MC(53))
        NO_HOLD_MAND = 1;

/******* Appoggio M19 ******/
if (M19)
{
	APP_M19 = 1;
	M19=0;
}
if (M03 || M04 || RESET_MC)
	APP_M19 = 0;

/**** RICHIESTA ROTAZIONE MANDRINO ****/
if ((M03 || M04 || Mg_MC(53)) && AUTO_CICLOMAN)
        {
        if (Mg_MC(53))
                MEM_M53 = 1;
        M03 = 0;
        M04 = 0;
        Mr_MC(53);
        AUX_ROTMAN = 1;
        }

if (M05 || RESET_MC || (NVS_CH0  && (O_TDS_CH0  == 0)))
        {
        NO_HOLD_MAND = 0;
        if (MANDRINO_FERMO || MEM_MASCRIG)
                M05 = 0;
        AUX_ROTMAN = 0;
        MEM_M53 = 0;
        }


/**** Memorizzo condizione di Input Mandrino Fermo ****/
////if ((INVERTER_0_INV_VEL_OK || SET_MAN_FERMO) && !INVERTER_0_START_INV_FW)
////					MEM_INPUT_MAND_FERMO = 1;
////if (INVERTER_0_START_INV_FW)
////					MEM_INPUT_MAND_FERMO = 0;


			// ******** Conteggio durata impulso di VELOCITA INVERTER OK allo stop del mandrino	********
			DN_START_INV = 0;
			if(!INVERTER_0_START_INV_FW && !APP_START_INV)
				DN_START_INV = 1;
			APP_START_INV = !INVERTER_0_START_INV_FW;

			if(DN_START_INV && INVERTER_0_INV_VEL_OK)
				ENABLE_COUNT_STARTINV = 1;

			if(ENABLE_COUNT_STARTINV)
				COUNTER_STARTINV += 1;  //conto quanto tempo rimane a 1 VEL_INVERTEROK_I quando va a zero START_INVERTER_O 
			else
				R[R6810] = (double) (COUNTER_STARTINV * (tauPLC/1000.0)); // appoggio tempo a 1 VEL_INVERTEROK_I quando va a zero START_INVERTER_O

			// Individuo impulso a 1 dell'ingresso di VEL_INVERTEROK_I dopo che va a zero START_INVERTER_O
			DP_VEL_INV_OK = 0;
			if(INVERTER_0_INV_VEL_OK && !APP_VEL_INV_OK)
				DP_VEL_INV_OK = 1;

			DN_VEL_INV_OK = 0;
			if(!INVERTER_0_INV_VEL_OK && APP_VEL_INV_OK)
				DN_VEL_INV_OK = 1;
			APP_VEL_INV_OK = INVERTER_0_INV_VEL_OK;

			/**** Memorizzo condizione di Input Mandrino Fermo ****/
			if(DP_VEL_INV_OK && !INVERTER_0_START_INV_FW)
			{
				MEM_INPUT_MAND_FERMO = 1;
				RIT_MANDR_FERMO = 0;
			}
			if(DN_VEL_INV_OK && !INVERTER_0_START_INV_FW)
				MEM_INPUT_MAND_FERMO = 0;

			if(MEM_INPUT_MAND_FERMO)
				COUNTER_PULSE_VELINV_OK += 1; //conteggio durata impulso VEL_INVERTEROK_I dopo che va a zero START_INVERTER_O
			else
				R[R6811] = (double) (COUNTER_PULSE_VELINV_OK * (tauPLC/1000.0)); // appoggio durata impulso VEL_INVERTEROK_I dopo che va a zero START_INVERTER_O

			if(DN_VEL_INV_OK && ENABLE_COUNT_STARTINV)
			{
				RIT_MANDR_FERMO = 1;  //serve a considerare il mandrino fermo alle basse velocità, l'inverter non da l'impulso di velocità inverter ok
				ENABLE_COUNT_STARTINV = 0;
			}

			if(INVERTER_0_START_INV_FW)
			{
				MEM_INPUT_MAND_FERMO = 0;
				COUNTER_PULSE_VELINV_OK = 0;
				COUNTER_STARTINV = 0;
				RIT_MANDR_FERMO = 0;
			}

			//*******************************************************************************************


/**** MANDRINO FERMO ****/
if (CONF_MICRO_ROTAZ_MAND)
		{
        if (!SBLOC_UT_O || !MANDRINO_FERMO || INVERTER_0_START_INV_FW)
		    MEM_VEL = VEL_MANDR_I;        
		MEM_VEL0 = 1;
		if (RP_TSuppl[TS_MAN_FERMO] || RP_TSuppl[TS_RIT_MANDR_FERMO])
		{
				MEM_MANDRINO_FERMO = 1;
				RIT_MANDR_FERMO = 0;
		}
			if (MEM_VEL != VEL_PREC)
				{
				VEL_PREC = MEM_VEL;
				MEM_VEL0 = 0;
				if (INVERTER_0_START_INV_FW)
						MEM_MANDRINO_FERMO = 0;
				}
		}


if (!CONF_MICRO_ROTAZ_MAND)
		{
		if (RP_TSuppl[TS_MAN_FERMO] || RP_TSuppl[TS_RIT_MANDR_FERMO])
		{
				MEM_MANDRINO_FERMO = 1;
				RIT_MANDR_FERMO = 0;
		}
		MEM_VEL0 = 1;
		if (INVERTER_0_START_INV_FW)
				MEM_MANDRINO_FERMO = 0;
		}


// il sensore di velocità del mandrino cambia stato durante l'apertura manuale dello sblocco utensili
if(!CONF_MASK_RIGIDA)
	MANDRINO_FERMO = MEM_MANDRINO_FERMO && RP_VEL_0;
else
	MANDRINO_FERMO = INVERTER_0_INV_MANDR_FERMO && RP_VEL_0;


// Abilitazione conteggio tempo manutenzione testina:
R[R_TIME_MANUT_TESTINA] = (float) (AUTO && !MANDRINO_FERMO && R[R_TESTINA_SU_MAND]==1);


/**** CONSENSO ROTAZIONE MANDRINO ****/
CONS_ROTMAN =	UT_AGGAN_I && !SBLOC_UT_O && !M_HOLD && OUT_MAC_ABIL_I && MANDRINO_VIBR_TEMP_OK &&
				RP_AUXON && (!PC_HOLD || O_MOV_CH0(AX_X_CH0) || O_MOV_CH0(AX_Y_CH0) || O_MOV_CH0(AX_Z_CH0) || O_MOV_CH0(AX_A_CH0) || O_MOV_CH0(AX_C_CH0));

//***** Ritardo su uscita alimentazione motore mandrino per start inverter *****
tS(TS_RIT_ALIM_MANDR, (unsigned char) ALIM_MANDR_O);

/**** START INVERTER MANDRINO ****/
INVERTER_0_START_INV_FW = (RP_TSuppl[TS_RIT_ALIM_MANDR]) && (AUX_ROTMAN || RP_MEM_MASCRIG) && CONS_ROTMAN;

/**** ALIMENTAZIONE MOTORE MANDRINO ****/
// Funziona con le uscite pericolose abilitate
// ALIM_MANDR_O = RP_OUTMAC_ABIL;

ALIM_MANDR_O = ((AUX_ROTMAN || MEM_MASCRIG || PROL_MEM_MASCRIG) && CONS_ROTMAN) ||
               (ALIM_MANDR_O && !MANDRINO_FERMO && !DRIVEM_NOK_FAL);

//***** Abilitazione logica asse mandrino *******
DI_SERVON_CH0(AX_Q_CH0) = INVERTER_0_START_INV_FW;

// Derivata positiva mandrino fermo (una sola volta dopo uno start inverter)
DP_MANDRINO_FERMO = 0;
if (DP_START_INV)	
	MEM_MAN_AVVIATO = 1; 
if (MEM_MAN_AVVIATO)
	{
	if (MANDRINO_FERMO && !MEM_MANDRINO_FERMO2)
		{
		DP_MANDRINO_FERMO = 1;
		MEM_MAN_AVVIATO = 0;
		}
	}
MEM_MANDRINO_FERMO2 = MANDRINO_FERMO;

// Fronte di salita del segnale di mandrino non in start, ritardato (30sec dopo caduta start inverter)
DP_RIT_STOP_INV = 0;
if (RP_STOP_INV && !APP_RP_STOP_INV)
	DP_RIT_STOP_INV = 1;
APP_RP_STOP_INV = RP_STOP_INV;


// Sblocco ritenzione teleruttore mandrino che rimane attivato in assenza di tensione
SBL_RIT_MANDRINO_O = RN_IMP_SBL_RITENUTA && !ALIM_MANDR_O;


/**** ALLARMI INVERTER ****/

/* Allarme inverter in blocco */
if (RP_AUXON && !INVERTER_0_INV_NOIN_BLOCCO && ALIM_PRES_I)
        DRIVEM_NOK_FAL = 1;

/* Allarme inverter in sovraccarico */
if (RP_AUXON && !RN_AUXPREA && INVERTER_0_START_INV_FW && !DRIVEM_NOK_FAL && ALIM_PRES_I)
		{
		if (!DRIVEM_PREA_FAL)
			{
			R[R_PICCO_CORR] = R[R_CORR_SPINDLE];
			R[R_PICCO_SPEED]= R[R_SPEED_SPINDLE];
			}
		DRIVEM_PREA_FAL = 1;
		}


// Allarme resettato : posso cancellare il picco
if (!DRIVEM_PREA_FAL && (RESET_ALL || RESET_MC) )
			{
			R[R_PICCO_CORR] = (float) 0;
			R[R_PICCO_SPEED]= (float) 0;
			}


// Inversione rotazione mandrino
INVERS_ROT_MAND = INVERTER_0_START_INV_FW && ( fabs(R[R241]-R[R_MEM_DIR_ROT])>0.5 );

// memoria senso di rotazione mandrino
R[R_MEM_DIR_ROT] = R[R241];

APP_RP_TIMEOUT_23 = RP_TIMEOUT_23 && !INVERS_ROT_MAND;     // App. Ritardo dopo [start inverter o eventuale inversione rotazione] (0,4 sec) (disabilita Allarme mandrino non in rotazione)
APP_RP_START_INV =  RP_START_INV  && !INVERS_ROT_MAND;     // App. Ritardo dopo [start inverter o eventuale inversione rotazione] (4   sec) (attiva FEEDHOLD_MAND PER VELOCITA' NON A REGIME IN G01)

if(INVERS_ROT_MAND)                                            DISAB_ALL_MND_FRM = 1;
if(RESET_MC || !INVERTER_0_START_INV_FW || APP_RP_START_INV )  DISAB_ALL_MND_FRM = 0;


/* Allarme mandrino non in rotazione */
//old 1:  if (RP_TIMEOUT_23 && MEM_MANDRINO_FERMO && !MEM_M53 && !MEM_MASCRIG  && CONF_MICRO_ROTAZ_MAND)
//old 2:  if (RP_TIMEOUT_23 && INVERTER_0_INV_MANDR_FERMO && MEM_MANDRINO_FERMO && !MEM_M53 && !MEM_MASCRIG && !PROL_MEM_MASCRIG && CONF_MICRO_ROTAZ_MAND)
if (	
		( (INVERTER_0_INV_MANDR_FERMO && CONF_MASK_RIGIDA) || (MEM_MANDRINO_FERMO && CONF_MICRO_ROTAZ_MAND) ) && 
		APP_RP_TIMEOUT_23 && !MEM_M53 && !MEM_MASCRIG && !PROL_MEM_MASCRIG && !DISAB_ALL_MND_FRM
)
        MANDRINO_FERMO_FAL = 1;


/* Allarme velocita' non a regime */
if (RP_TIMEOUT_24 && INVERTER_0_START_INV_FW)
        MANDRINO_HOLD_FAL = 1;


// Vibrazioni OK sul mandrino - Info dal mandrino tramite scheda di comunicazione Isac RS485  E5009156  OPRIOCOM0
RS485_MANDRINO_VIBR_OK = 0;

// Temperatura OK sul mandrino - Info dal mandrino tramite scheda di comunicazione Isac RS485  E5009156  OPRIOCOM0
RS485_MANDRINO_TEMP_OK = 0;

/* Allarme Vibrazioni eccessive sul mandrino */
if (!MANDRINO_VIBR_TEMP_OK && !RS485_MANDRINO_VIBR_OK)
	MANDRINO_VIBR_FAL = 1;

/* Allarme Temperatura eccessiva sul mandrino */
if (!MANDRINO_VIBR_TEMP_OK && !RS485_MANDRINO_TEMP_OK)
	MANDRINO_TEMP_FAL = 1;


/**** RESET ALLARMI PER INVERTER ****/
if (RESET_MC || RESET_ALL)
		INVERTER_0_RESET_INVERTER = 1;

if (RP_IMPRST_INV)
        INVERTER_0_RESET_INVERTER = 0;

/**** CICLO ROTAZIONE MANDRINO ****/
CICLO_ROTMAN =	MANO && FUNZ_MAN15 && (COMANDO_A || COMANDO_B) && 
				(CONS_ROTMAN || CICLO_ROTMAN);

CICLO_VOLROT = MANO && CONS_ROTMAN && ABIL_MANDRINO && UOMO_MORTO_I;		

if (CICLO_ROTMAN || CICLO_VOLROT)
        ROTMAN_REQ = 1;
if (RESET_MC)
        ROTMAN_REQ = 0;


/**** FEED HOLD PER VELOCITA' NON A REGIME IN G01 ****/
FEEDHOLD_MAND = AUX_ROTMAN && (!(INVERTER_0_INV_VEL_OK) || !(RP_START_INV)) && O_LAV_CH0  && !NO_HOLD_MAND;


// DIAGNOSTICA FEED HOLD PER VELOCITA' NON A REGIME IN G01
if( FEEDHOLD_MAND       )       R[R4150]++;    if( RESET_ALL || RESET_MC || (R[R4150]>99999) ) R[R4150] = 0;
if( !(INVERTER_0_INV_VEL_OK) )  R[R4151]++;    if( RESET_ALL || RESET_MC || (R[R4151]>99999) ) R[R4151] = 0;
if( !(RP_START_INV)     )       R[R4152]++;    if( RESET_ALL || RESET_MC || (R[R4152]>99999) ) R[R4152] = 0;


/******************************************************************************/
/*********************** GESTIONE SBLOCCAGGIO UTENSILE ************************/
/******************************************************************************/

if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
{

	SBLOC_UT = (int)SBLOC_UT_O; UT_SBLOC = (int)UT_SGANC_I;
	count (&SBLOC_UT, &UT_SBLOC, &SBLOC_UT_COUNT, &SBLOC_UT_MEMCOUNT, &SBLOC_UT_MEM, R_SBLOC_UT, SBLOC_UT_COMMENTO);

	BLOCC_UT = (int)!SBLOC_UT_O; UT_BLOCC = (int)UT_AGGAN_I;
	count (&BLOCC_UT, &UT_BLOCC, &BLOCC_UT_COUNT, &BLOCC_UT_MEMCOUNT, &BLOCC_UT_MEM, R_BLOCC_UT, BLOCC_UT_COMMENTO);

}


/**** MEMORIA SBLOCCAGGIO UTENSILE ****/
if(!SBLOC_UT_CAR_SCAR_AUT)
{
	if ( Mg_MC(50) )
			MEM_SBLOC_UT = 1;
	if ( Mg_MC(51) || RESET_MC )
			MEM_SBLOC_UT = 0;
}
else
{
	MEM_SBLOC_UT = COMANDO_AUX_B;
}


/****************** SBLOCCAGGIO UTENSILE *******************/
/* Consenso sbloccaggio utensile */
// Permetto il cambio solo con assi riferiti o in manuale ad assi non riferiti (quindi ad occhio) 
// Consenso diverso se CT6 e asse A rotativo con sbloccaggio a spinta dall'altro o 
// se classico con sbloccaggio utensile da comando direttoù

CONS_SBLOCUT = MANDRINO_FERMO && !INVERTER_0_START_INV_FW && AUX_INSER_I ;

MAN_SBLOCCA_UT = CONS_SBLOCUT && 
                 MANO && FTL_APPO_RIPARO_AP_INP && FUNZ_MAN20 && COMANDO_B;

/* Messaggio per operatore : sbloccaggio utensile diretto possibile solo con ripari bassi */
SBLOC_UT_RIP_AP_FMS = MANO && FUNZ_MAN20  && COMANDO_B && (!FTL_APPO_RIPARO_AP_INP);


/* Ausiliario sbloccaggio utensile */
AUX_SBLOCUT = ((	AUTO_CICLOMAN && MEM_SBLOC_UT || 
					MAN_SBLOCCA_UT && MANO)
					&& CONS_SBLOCUT)
					|| (SBLOC_UT_O && !AUX_BLOCCUT);


/* Sbloccaggio utensile */
SBLOC_UT_O = AUX_SBLOCUT && !AUX_BLOCCUT;

/* Time out sbloccaggio utensile */
if (MACCHINA_PRONTA && RP_TIMEOUT_21 && !RN_UT_SGANC)
        UT_NOSBL_FAL = 1;

/* Reset funzione ausiliaria "M" */
if (UT_SGANC_I)
        Mr_MC(50);


/****************** BLOCCAGGIO UTENSILE *******************/
/* Consenso bloccaggio utensile */
CONS_BLOCCUT = 1;

/* Ausiliario bloccaggio utensile */
AUX_BLOCCUT = ((	AUTO_CICLOMAN && !MEM_SBLOC_UT ||
					!AUTO_CICLOMAN && !MAN_SBLOCCA_UT)
					 && CONS_BLOCCUT)
					|| (AUX_BLOCCUT && RN_UT_AGGAN && !AUX_SBLOCUT);


/* Time out bloccaggio utensile */
if (MACCHINA_PRONTA && RP_TIMEOUT_22 && !RN_UT_AGGAN && (R[R_ACT_TOOL] != 0) && !DISAB_ALL_UT_CAR_SCAR && 
	!UTSCON_ACT && !GEST_OPERATORE_MAN)
        UT_NOBLO_FAL = 1;

/* Reset funzione ausiliaria "M" */
if ( UT_AGGAN_I || ( ((R[R_ACT_TOOL] == 0) || UTSCON_ACT) && AUX_BLOCCUT) )
        Mr_MC(51);

/**************** DISFUNZIONE F.C. BLOCCAGGIO UTENSILE ****************/
if (RP_UT_AGGAN && RP_UT_SGANC && !GEST_OPERATORE_MAN)
        UT_DISFC_FAL = 1;


/**** ALLARME UTENSILE NON AGGANCIATO CORRETTAMENTE  ****/
/**** Disabilitato, servirebbe un ulteriore sensore che non c'è ****/
if	(BITOFF && AUTO && RP_UT_AGGAN && !UT0_ACT && !UTSCON_ACT)
        UT_NOAGG_FAL = 1;


// Gestione Teleruttore dello Scambiatore di calore mandrino ON (frigo)
SCAMB_CAL_MANDR_O = (RN_START2_INV);

/**** ALLARME FLUSSASTATO CENTRALINA NON OK ****/
if ( !(FLUSSOSTATO_OK_I) && CONF_FLUSSOSTATO && ( !CONF_TELERUTTORE_FRIGO || (RP_SCAMB_CAL_MANDR) ) )
		FLUSSOSTATO_FAL = 1;


/**** ALLARME TERMICO CENTRALINA DI RAFFREDDAMENTO ****/
if (CONF_FLUSSOSTATO && !TERM_FRIGO_OK_I)
		TERM_FRIGO_NOK_FAL = 1;



/**************** FUNZIONE ESEGUITA ***************************/
MANDRINO_FUNES_B = ((Mg_MC(71) && P_OSCILLATORE) || (INVERTER_0_INV_VEL_OK && INVERTER_0_START_INV_FW)) 
					&& FUNZ_MAN15 && COMANDO_B;

MANDRINO_FUNES_A = ((Mg_MC(71) && P_OSCILLATORE) || (INVERTER_0_INV_VEL_OK && INVERTER_0_START_INV_FW)) 
					&& FUNZ_MAN15 && COMANDO_A;

/**************** FUNZIONE ESEGUITA ***************************/
UT_SGANCIO_FUNES_B =	( (SBLOC_UT_O && P_OSCILLATORE) || UT_SGANC_I) 
						&& FUNZ_MAN20;

UT_SGANCIO_FUNES_A =	( UT_AGGAN_I || !SBLOC_UT_O)
						&& FUNZ_MAN20;

//*****************************************************************
//****** SCRITTURA OUTPUT PLC (INPUT DELL'INVERTER) PER PLC IEC ***
//*****************************************************************
com_con_inverter_OUTPUT();

}

else
        {
		DRIVEM_NOK_FAL		= 0;
        DRIVEM_PREA_FAL		= 0;
        MANDRINO_FERMO_FAL	= 0;
        MANDRINO_HOLD_FAL	= 0;
        UT_NOSBL_FAL		= 0;
        UT_NOBLO_FAL		= 0;
        UT_DISFC_FAL		= 0;
        UT_NOAGG_FAL		= 0;
        FEEDHOLD_MAND		= 0;

		FLUSSOSTATO_FAL		= 0;
		TERM_FRIGO_NOK_FAL  = 0;
        }



}







