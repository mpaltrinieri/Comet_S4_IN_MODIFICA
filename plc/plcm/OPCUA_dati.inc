#ifndef OPCUA_DATI_INC_INCLUDED
#define OPCUA_DATI_INC_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : OPCUA_State_mach.inc
// AUTORE      : Daniele Formuso
// DESCRIZIONE : Definizione funzioni PLC
//----------------------------------------------------------------------------

#define  MACH_STATUS_OFFLINE         0     // Stato sconosciuto e/o macchina spenta
#define  MACH_STATUS_BOOTING         1     // Inizializzazione in corso
#define  MACH_STATUS_ON              2     // Macchina pronta in manuale
#define  MACH_STATUS_READY           3     // Macchina pronta in automatico ma non in ciclo
#define  MACH_STATUS_ALARM           4     // Macchina in allarme, ma non in emergenza
#define  MACH_STATUS_EMERGENCY       5     // Macchina in emergenza
#define  MACH_STATUS_SETUP           6     // Azzeramento in corso
#define  MACH_STATUS_JOG             7     // Movimento manuale attivo
#define  MACH_STATUS_HOLD            8     // Macchina in pausa
#define  MACH_STATUS_WAIT            9     // Attesa operazione operatore con ciclo automatico in corso
#define  MACH_STATUS_POSITIONING    10     // Tutti i movimenti assi ad esclusione del ciclo di lavorazione
#define  MACH_STATUS_WORKING        11     // Lavorazione attiva, utensile a contatto con il pezzo
#define  MACH_STATUS_TOOL_CHANGE    12     // Cambio utensili in corso
#define  MACH_STATUS_SERVICE        13     // Macchina in manutenzione

#endif // OPCUA_DATI_INC_INCLUDED
