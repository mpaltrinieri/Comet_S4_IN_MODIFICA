#ifndef TIMERSSUPPL_INC_INCLUDED
#define TIMERSSUPPL_INC_INCLUDED

/*

        ---------------------------------------------
        TITOLO:         TIMERSSUPPL.INC
        ---------------------------------------------
        MACCHINA:       EMMEGI COMET T6
        ---------------------------------------------
        RELEASE:        CT6 0.0
        ---------------------------------------------
        DATA:           01-01-2006
        ---------------------------------------------
        AUTORE:         G.Borsari
        ---------------------------------------------
        DESCRIZIONE:    Definizione timers supplementari
        ---------------------------------------------

*/

// Central.c:	maxTSuppl[TS_XXXX] = tempo_in_1/100s;	(oppure in CONFMAC.CT4)
// templc:		tS(TS_XXXX, (unsigned char) ingresso);
//				uscita_rit = RP_TSuppl[TS_XXXX];
//				derivt_pos = DP_TSuppl[TS_XXXX];
//				uscita_rit = RN_TSuppl[TS_XXXX];
//				derivt_pos = DN_TSuppl[TS_XXXX];

/*----------------------------------------------------------------------------------------*/
/*                               TIMER SUPPLEMENTARI									  */
/*----------------------------------------------------------------------------------------*/
extern void timersSuppl_pon	(void);
extern void timersSuppl		(void);
extern void tS				(int nTimer, unsigned char ingr);

extern double tauCNC;
extern double tauPLC;


/*****************************************************************************************/
/************* Inserire il numero massimo di temporizzatori e il TAU del PLC *************/
/****************** Se non sono dichiarati i sinonimi non cambia nulla *******************/
/*****************************************************************************************/
#define N_TIMERS_SUPPL        399	/* <<<<<<<<< DA MODIFICARE PER AMPLIARE IL NUMERO DI TIMER */

extern unsigned int  maxTSuppl    [N_TIMERS_SUPPL]; //Tempo in ms
extern unsigned char ingrTSuppl   [N_TIMERS_SUPPL]; //ingresso 
extern unsigned char RP_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato positivo
extern unsigned char RN_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato negativo
extern unsigned char DP_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato positivo
extern unsigned char DN_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato negativo

// maxTSuppl[TS_XXXX] = tempo_in_1/100s;	->	Central.c
// tS(TS_XXXX, (unsigned char) ingresso);	->	Plc.c
// uscita_rit = RP_TSuppl[TS_XXXX];


/*****************************************************************************************/
/***************** Inserire da quì tutti i temporizzatori supplementari ******************/
/*****************************************************************************************/

#define TS_0						0  // Lasciare libero
#define TS_ALL_RIPARO_AP			1  // Temporizza Riparo Anteriore Apertura
#define TS_ALL_RIPARO_CH			2  // Temporizza Riparo Anteriore Chiusura
#define TS_3						3  // Temporizza Riparo Anteriore DX Apertura
#define TS_4						4  // Temporizza Riparo Anteriore DX Chiusura
#define TS_TAVOLA_AVA				5  // Temporizza Tavola Avanti
#define TS_TAVOLA_IND				6  // Temporizza Tavola Indietro
#define TS_7						7  //
#define TS_RIT_CONTAORE				8  // Ritardo prima di attivare i contaore (60sec)
#define TS_CENTRALINA_OK			9  // Temporizza ingresso CENTRALINA_OK_I

#define TS_10						10 //
#define TS_11						11 //   
#define TS_ALIM_MM_NOT_OK			12 // Temporizza condizione di alimentatori morse motorizzate not OK per allarme                     
#define TS_RIT_ALIM_MM_OK			13 // Temporizza ritardo alimentatori morse OK
#define TS_14						14 //

#define TS_RICH_AP_RIP_ANT			15 // Ritardo apertura riparo anteriore (per consentire aspirazione fumi) | Guards opening delay for fume extraction
#define TS_16						16 //                      
#define TS_TIMEOUT_BATTUTA_SX1_ALT	17 // Timeout Allarme Battuta SX1 non Alta 
#define TS_TIMEOUT_BATTUTA_SX1_BAS	18 // Timeout Allarme Battuta SX1 non Bassa

#define TS_TIMEOUT_BATTUTA_SX1_AVA	19 // (SOLO CR6 per ora) Timeout Allarme Battuta SX1 non avanti 
#define TS_TIMEOUT_BATTUTA_SX1_IND	20 // (SOLO CR6 per ora) Timeout Allarme Battuta SX1 non indietro

#define TS_TIMEOUT_BATTUTA_DX4_AVA	21 // (SOLO CR6 per ora) Timeout Allarme Battuta DX4 non avanti 
#define TS_TIMEOUT_BATTUTA_DX4_IND	22 // (SOLO CR6 per ora) Timeout Allarme Battuta DX4 non indietro

#define TS_TIMEOUT_BATTUTA_DX4_ALT	23 // Timeout Allarme Battuta DX4 non Alta  
#define TS_TIMEOUT_BATTUTA_DX4_BAS	24 // Timeout Allarme Battuta DX4 non Bassa 

#define TS_TIMEOUT_SBLOC_UT			25 // Timeout Allarme Sbloccaggio Utensile
#define TS_TIMEOUT_BLOCC_UT			26 // Timeout Allarme Bloccaggio Utensile 

#define TS_BATTUTA_SX1_ALTA			27 // (SOLO CR6 per ora) Ritardo dopo il quale si considera ALTA la battuta SX1 (dopo che BATTUTA_SX1_BAS_I=0)
#define TS_BATTUTA_DX4_ALTA			28 // (SOLO CR6 per ora) Ritardo dopo il quale si considera ALTA la battuta DX4 (dopo che BATTUTA_DX4_BAS_I=0)

#define TS_FORZA_ALTA_PRESS_MAN		29 // Temporizza Forza Alta pressione in manuale (2 pls per 5 secondi)

#define TS_BATTUTA_SX1_AVA			30 // (SOLO CR6 per ora) Ritardo dopo il quale si considera AVANTI la battuta SX1 (dopo che BATTUTA_SX1_IND_I=0)
#define TS_BATTUTA_DX4_AVA			31 // (SOLO CR6 per ora) Ritardo dopo il quale si considera AVANTI la battuta DX4 (dopo che BATTUTA_DX4_IND_I=0)

#define TS_BAS_PRESSIONE_MORSE		32 // Temporizza bassa pressione morse (alta pressione non attiva)
#define TS_33						33 // (occupato su CR6)
#define TS_PRESS_TAV_AVA			34 // Temporizzo segnale pressostato Tavola Avanti
#define TS_PRESS_TAV_IND			35 // Temporizzo segnale pressostato Tavola Indietro
#define TS_36						36 // 
#define TS_37						37 //
#define TS_MAN_FERMO				38 // Temporizzo condizione mandrino fermo
#define TS_RIP_AUTO_NO_CH			39 // Temporizzo riparo auto non chiuso

#define TS_40						40 //
#define TS_ALL_DISFC_TAV			41 // Temporizzo condizione d'allarme Disfunzione Tavola
#define TS_42						42 //

#define TS_ABIL_VERIF_SERIAL		43 // Durata abilitazione verifica segnale "serial" del modulo PIZZATO

#define TS_45						45 //
#define TS_46						46 //
#define TS_ALL_TAV_AVA				47 // Temporizzo condizione d'allarme tavola avanti
#define TS_ALL_TAV_IND				48 // Temporizzo condizione d'allarme tavola indietro
#define TS_49						49 // 

#define TS_50						50 // 
#define TS_DRIVE_X_IN_ALLARME		51 // Temporizzo Drive Asse X in allarme 
#define TS_DRIVE_Y_IN_ALLARME		52 // Temporizzo Drive Asse Y in allarme 
#define TS_DRIVE_Z_IN_ALLARME		53 // Temporizzo Drive Asse Z in allarme 
#define TS_DRIVE_A_IN_ALLARME		54 // Temporizzo Drive Asse A in allarme 
#define TS_DRIVE_C_IN_ALLARME		55 // Temporizzo Drive Asse C in allarme 
#define TS_DRIVE_W_IN_ALLARME		56 // Temporizzo Drive Asse C in allarme 

#define TS_COND_POSSIBILE_CORTO		58 // Temporizzo Condizioni di rilievo di un possibile corto
#define TS_59						59 //

#define TS_61						61 //

#define TS_66						66 //
#define TS_67						67 //
#define TS_FATM_CH0					68 // Temporizzo messaggio FATM Attivo 


#define TS_74						74 //
#define TS_75						75 //
#define TS_76						76 //
#define TS_77						77 //
#define TS_78						78 //
#define TS_79						79 //

#define TS_80						80 //
#define TS_81						81 //
#define TS_TRASC_MORSE_AX_X_INS		82 // Temporizzo condizione d'allarme Trascinatore Morse Asse X non inserita 
#define TS_TRASC_MORSE_AX_X_DIS		83 // Temporizzo condizione d'allarme Trascinatore Morse Asse X non disinserita
#define TS_84						84 // 
#define TS_85						85 // 
#define TS_86						86 // 
#define TS_SBLOCCAGGIO_MORSA_10		87 // Temporizzo Sbloccaggio Morsa Numero 10
#define TS_SBLOCCAGGIO_MORSA_11		88 // Temporizzo Sbloccaggio Morsa Numero 11
#define TS_SBLOCCAGGIO_MORSA_12		89 // Temporizzo Sbloccaggio Morsa Numero 12

#define TS_SBLOCCAGGIO_MORSA_13		90 // Temporizzo Sbloccaggio Morsa Numero 13
#define TS_SBLOCCAGGIO_MORSA_14		91 // Temporizzo Sbloccaggio Morsa Numero 14
#define TS_SBLOCCAGGIO_MORSA_15		92 // Temporizzo Sbloccaggio Morsa Numero 15
#define TS_93						93 // 
#define TS_94						94 // 
#define TS_95						95 // 
#define TS_96						96 //
#define TS_97						97 //
#define TS_SOLO_MESS_PRESENTI		98 // Temporizzo dopo quanto inizio a segnalare i messaggi in auto
#define TS_99						99 //

#define TS_100						100 //
#define TS_ALL_CENTRALINA			101 // Temporizzo Allarme Centralina non attiva con riparo chiuso
#define TS_102						102 //
#define TS_PRESS_MORSE_CH			103 // Temporizzo segnale di alta pressione morse
#define TS_104						104 // 
#define TS_105						105 //
#define TS_106						106 //
#define TS_107						107 //
#define TS_108						108 //
#define TS_RIT_MANDR_FERMO			109 // Ritardo mandrino fermo a basse velocità 

#define TS_RILMOR_AX_X_INS			112	// Temporizza allarme inserzione Rilevatore morse
#define TS_RILMOR_AX_X_DIS			113	// Temporizza allarme disinserzione Rilevatore morse
#define TS_114						114 //
#define TS_115						115 //
#define TS_RIT_ALIM_MANDR			116 // Ritardo su uscita alimentazione motore mandrino

#define TS_117						117 //
#define TS_118						118 //
#define TS_119						119 //
#define TS_ALT_PRESS_MORSA10		120 // Temporizza allarme alta pressione assente su morsa 10
#define TS_ALT_PRESS_MORSA11		121 // Temporizza allarme alta pressione assente su morsa 11
#define TS_ALT_PRESS_MORSA12		122 // Temporizza allarme alta pressione assente su morsa 12
#define TS_ALT_PRESS_MORSA13		123 // Temporizza allarme alta pressione assente su morsa 13
#define TS_ALT_PRESS_MORSA14		124 // Temporizza allarme alta pressione assente su morsa 14
#define TS_ALT_PRESS_MORSA15		125 // Temporizza allarme alta pressione assente su morsa 15
#define TS_126						126 //
#define TS_127						127 //
#define TS_128						128 //
#define TS_129						129 //

#define TS_START_RES_ABIL_AX_X		130 // Attesa abilitazione asse AX_X prima di temporaneo reset abilitazione
#define TS_START_RES_ABIL_AX_Y		131 // Attesa abilitazione asse AX_Y prima di temporaneo reset abilitazione
#define TS_START_RES_ABIL_AX_Z		132 // Attesa abilitazione asse AX_Z prima di temporaneo reset abilitazione
#define TS_START_RES_ABIL_AX_A		133 // Attesa abilitazione asse AX_A prima di temporaneo reset abilitazione
#define TS_START_RES_ABIL_AX_W		134 // Attesa abilitazione asse AX_W prima di temporaneo reset abilitazione
#define TS_START_RES_ABIL_AX_C		135 // Attesa abilitazione asse AX_C prima di temporaneo reset abilitazione (per diagnostica, asse fittizio)
#define TS_136						136 //
#define TS_137						137 //
#define TS_138						138 //
#define TS_ALIVE_DRILL				139 // Timeout alive Drill in gestione utensile avanzata

#define TS_STOP_RES_ABIL_AX_X		140 // Durata temporaneo reset abilitazione asse AX_X 
#define TS_STOP_RES_ABIL_AX_Y		141 // Durata temporaneo reset abilitazione asse AX_Y
#define TS_STOP_RES_ABIL_AX_Z		142 // Durata temporaneo reset abilitazione asse AX_Z
#define TS_STOP_RES_ABIL_AX_A		143 // Durata temporaneo reset abilitazione asse AX_A
#define TS_STOP_RES_ABIL_AX_W		144 // Durata temporaneo reset abilitazione asse AX_W
#define TS_STOP_RES_ABIL_AX_C		145 // Durata temporaneo reset abilitazione asse AX_C (per diagnostica, asse fittizio)

#define TS_TOOL_AGGAN				146 // Ritardo su ingresso utensile agganciato per consensi vari
#define TS_ERR_UT_IN_MEM			147 // Temporizza Allarme incongruenza tra utensile teoricamente presente e sensore di presenza utensile
#define TS_148						148 //
#define TS_PLC_IEC_NOT_ALIVE		149 // Temporizza timeout di comunicazione con PLC IEC

#define TS_RIPARO_CH				150 // Ritardo su ingresso (200msec)
#define TS_RIPARO_AP				151 // Ritardo su ingresso (200msec)
#define TS_152						152 //
#define TS_153						153 //
#define TS_TIMEOUT_VIS_AVA			154 // Timeout avanzamento visiera bassa
#define TS_TIMEOUT_VIS_IND			155 // Timeout arretramento visiera bassa
#define TS_TIMEOUT_VIS_SAL			156 // Timeout chiusura visiera alta
#define TS_TIMEOUT_VIS_DIS			157 // Timeout apertura visiera alta
#define TS_158						158 //
#define TS_159						159 //

#define TS_160						160 //
#define TS_161						161 //
#define TS_VIS_RIP_DIS				162 // Ritardo su uscita apertura visiera alta
#define TS_163						163 //
#define TS_RIT_VISIERA_IND			164 // Ritardo su ingresso visiera indietro
#define TS_RIT_VISIERA_AVA			165 // Ritardo su ingresso visiera avanti
#define TS_166						166 //
#define TS_167						167 //
#define TS_168						168 //
#define TS_RIT_AZZERA_CALL_TOOL		169 // Ritardo su azzeramento chiamata utensile in ISO

#define TS_TOOLTAB_READ				170	// Ritardo su segnale di lettura tabelle utensili (Funz ISO)
#define TS_171						171 //
#define TS_172						172 //
#define TS_173						173 //
#define TS_174						174 //
#define TS_175						175 //
#define TS_176						176 //
#define TS_177						177 //
#define TS_178						178 //
#define TS_179						179 //

#define TS_180						180 //
#define TS_MANO						181 // Ritardo su Multicanale in manuale
#define TS_182						182 //
#define TS_183						183 //
#define TS_COND_ASINCRO_CNC_MAN		184 // Ritardo per allarme asincronia manuale tra i CN
#define TS_COND_ASINCRO_CNC_AUT		185 // Ritardo per allarme asincronia automatico tra i CN
#define TS_NVM_CH1					186 // Ritardo su nuova Funz. M CH1
#define TS_NVM_CH2					187 // Ritardo su nuova Funz. M CH4
#define TS_188						188 //
#define TS_189						189 //

#define TS_LOAD_ISO_CH1				190 // Timeout comando caricamento ISOMG_CH1.CS4 su CH1
#define TS_LOAD_ISO_CH2				191 // Timeout comando caricamento ISOMG_CH2.CS4 su CH2
#define TS_192						192 //
#define TS_193						193 //
#define TS_194						194 //
#define TS_195						195 //
#define TS_196						196 //
#define TS_197						197 //
#define TS_198						198 //
#define TS_199						199 //

#define TS_200						200 //
#define TS_201						201 //
#define TS_202						202 //
#define TS_203						203 //
#define TS_204						204 //
#define TS_RIT_ABIL_MORSE_M210		205 // Temporizza ritardo su M210 per resettarla
#define TS_206						206 // Occupata su CR6
#define TS_207						207 // Occupata su CR6
#define TS_208						208 //
#define TS_209						209 //

#define TS_RIT_ENABLE_CODE_ALARM                210 // Ritardo di abilitazione della coda allarmi passata al plc iec
#define TS_RIT_ENABLE_INVERTER_0_COM_ERROR      211 // Ritardo per abilitazione errore di comunicazione COM con inverter 0
#define TS_RIT_ENABLE_ASSE_0_COM_ERROR          212 // Ritardo per abilitazione errore di comunicazione COM con azionamento asse X
#define TS_RIT_ENABLE_ASSE_1_COM_ERROR          213 // Ritardo per abilitazione errore di comunicazione COM con azionamento asse Y
#define TS_RIT_ENABLE_ASSE_2_COM_ERROR          214 // Ritardo per abilitazione errore di comunicazione COM con azionamento asse Z
#define TS_RIT_ENABLE_ASSE_3_COM_ERROR          215 // Ritardo per abilitazione errore di comunicazione COM con azionamento asse A
#define TS_RIT_ENABLE_ASSE_4_COM_ERROR          216 // Ritardo per abilitazione errore di comunicazione COM con azionamento asse W

#endif // TIMERSSUPPL_INC_INCLUDED
