#ifndef CONFMAC_INC_INCLUDED
#define CONFMAC_INC_INCLUDED
/*

        ---------------------------------------------
        TITOLO:         CONF_MAC.INC
        ---------------------------------------------
        MACCHINA:       EMMEGI COMET T5/T6
        ---------------------------------------------
        RELEASE:        CT6 0.0
        ---------------------------------------------
        DATA:           30-08-2000
        ---------------------------------------------
        AUTORE:         Soffritti Riccardo
        ---------------------------------------------
        DESCRIZIONE:    Definizione configurazioni varie
        ---------------------------------------------

*/

/* #define SIMU	*/              /* Esecuzione prog. PLC in simulazione */
#define MAXOV_FE         120    /* Max valore per override assi */
#define MINOV_FE           0    /* Min valore per override assi */

#define MAXOV_SP         100    /* Max valore per override mandrino */
#define MINOV_SP          50    /* Min valore per override mandrino*/

#define MININC             1    /* Incremento per override */

#define MAX_CONT_R    999999    /* Max valore per contatori */

#if defined (SIMUCN)
#define SIMULATORE_SU_CN	1	//		SIMULATORE SU CNC REALE MA SENZA NULLA COLLEGATO (assi, can, I/O..) (ANALOGO A TIMEX SU PC)
#else
#define SIMULATORE_SU_CN	0	//		SIMULATORE SU CNC REALE MA SENZA NULLA COLLEGATO (assi, can, I/O..) (ANALOGO A TIMEX SU PC)
#endif

#if defined(SIMUPC)
#define SIMULATORE_SU_PC	1	//		SIMULATORE SU PC (TIMEX SU PC)
#else
#define SIMULATORE_SU_PC	0	//		SIMULATORE SU PC (TIMEX SU PC)
#endif


#define TRACE_DEBUG_5 0
#define TRACE_DEBUG_6 0

#define SIMU2              1    // Simulatore su CN con Mgpilot

#define PSW_collaudo  1010
#define PSW_shoowroom 6328

#define PSW_AP_AUT_RIP     2929 // Password per apertura automatica riparo anteriore


// **************************************************************************************************************************************************

// Il messaggio di emergency dell'azionamento di batteria encoder scarica è: 7305-0061 (su 0x603F e 0x2001) che genera allarme CNC 2911
#define DELTA_ALL_BATT_SCARICA_GR       29445      // 0x603F =  0x7305 -> 29445  Codice Delta dell'allarme di livello batteria basso: gruppo dell'allarme
#define DELTA_ALL_BATT_SCARICA_NU          97      // 0x2001 =  0x0061 ->    97  Codice Delta dell'allarme di livello batteria basso: numero dell'allarme

#define DELTA_ALL_BATT_QUOTA_PERSA_GR   29445      // 0x603F =  0x7305 -> 29445  Codice Delta dell'allarme di livello batteria basso e posizione assoluta persa: gruppo dell'allarme
#define DELTA_ALL_BATT_QUOTA_PERSA_NU      96      // 0x2001 =  0x0060 ->    96  Codice Delta dell'allarme di livello batteria basso e posizione assoluta persa: numero dell'allarme

#define DELTA_MT_OVERFLOW_GR            29445      // 0x603F =  0x7305 -> 29445  Codice Delta dell'allarme di overflow sui giri massimi del multiturn dell'encoder assoluto: gruppo dell'allarme
#define DELTA_MT_OVERFLOW_NU               98      // 0x2001 =  0x0062 ->    98  Codice Delta dell'allarme di overflow sui giri massimi del multiturn dell'encoder assoluto: numero dell'allarme

#define DELTA_POS_ENCODER_PERSA_GR      29445      // 0x603F =  0x7305 -> 29445  Codice Delta dell'allarme di posizione assoluta encoder persa: gruppo dell allarme
#define DELTA_POS_ENCODER_PERSA_NU        106      // 0x2001 =  0x006A ->   106  Codice Delta dell'allarme di posizione assoluta encoder persa: numero dell'allarme

#define DELTA_CLEAR_ENCODER_ERR_GR      29445      // 0x603F =  0x7305 -> 29445  Codice Delta dell'allarme di funzione di reset encoder assoluto non riuscita: gruppo dell'allarme
#define DELTA_CLEAR_ENCODER_ERR_NU        112      // 0x2001 =  0x0070 ->   112  Codice Delta dell'allarme di funzione di reset encoder assoluto non riuscita: numero dell'allarme

#define DELTA_UNDER_VOLTAGE_GR          12576      // 0x603F =  0x3120 -> 12576  Codice Delta dell'allarme di tensone DC del circuito principale più bassa del valore standard: gruppo dell'allarme
#define DELTA_UNDER_VOLTAGE_NU              3      // 0x2001 =  0x0003 ->     3  Codice Delta dell'allarme di tensone DC del circuito principale più bassa del valore standard: numero dell'allarme

#define DELTA_MOTORE_SENZA_FASE_GR      12592      // 0x603F =  0x3130 -> 12592  Codice Delta dell'allarme di mancanza di una fase in ingresso: gruppo dell'allarme
#define DELTA_MOTORE_SENZA_FASE_NU         34      // 0x2001 =  0x0022 ->    34  Codice Delta dell'allarme di mancanza di una fase in ingresso: numero dell'allarme

#define DELTA_OVERSHOOT_SPEED_GR        33792      // 0x603F =  0x8400 -> 33792  Codice Delta dell'allarme di velocità del motore in overshoot rispetto al valore massimo di targa: gruppo dell'allarme
#define DELTA_OVERSHOOT_SPEED_NU           71      // 0x2001 =  0x0047 ->    71  Codice Delta dell'allarme di velocità del motore in overshoot rispetto al valore massimo di targa: numero dell'allarme

#define DELTA_PRE_OVERLOAD_GR           12849      // 0x603F =  0x3231 -> 12849  Codice Delta del messaggio di preallarme di motore in sovraccarico: gruppo dell'allarme
#define DELTA_PRE_OVERLOAD_NU              35      // 0x2001 =  0x0023 ->    35  Codice Delta del messaggio di preallarme di motore in sovraccarico: numero dell'allarme

#define RW_ETH_TIMEOUT                    150      // Timeout per funzioni di lettura-scrittura oggetti via Ethercat      

#define IND_ETHERCAT_X               "Ethercat|1002"
#define IND_ETHERCAT_Y               "Ethercat|1003"
#define IND_ETHERCAT_Z               "Ethercat|1004"
#define IND_ETHERCAT_A               "Ethercat|1005"
#define IND_ETHERCAT_W               "Ethercat|1006"

#define VERS_MIN_FIRMW_DELTA         1643.8534     // Versione minima firmware per la lettura degli SDO

// **************************************************************************************************************************************************

#endif // CONFMAC_INC_INCLUDED
