#ifndef CARICAFMAN_H_INCLUDED
#define CARICAFMAN_H_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : caricafman.h
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Gestione caricamento funzioni manuali da file su MGPilot
//----------------------------------------------------------------------------

#include <rtplc.h>
#include "mgpilot.h"


// Configurazione
#define FMAN_MANMESS_FILE_NAME  "%base%\\msg\\MANMESS.MSG"       // Nome del file contenente le funzioni manuali
#define FMAN_MANCNTX_FILE_NAME  "%base%\\msg\\MANCNTX.MSG"       // Nome del file contenente i menù contestuali
#define FMAN_CNCMSG_FILE_NAME   "%base%\\msg\\CNC.MSG"           // Nome del file con allarmi e messaggi per pilot
#define FMAN_SELREM_FILE_NAME   "%base%\\lav\\lav\\REM_CTRL.MSG" // Nome del file contenente le funzioni manuali di REMCTRL.MSG da escludere

#define FMAN_SEPARATOR          "\r\n"  // Separatore fra i record delle funzioni manuali
#define FMAN_ERRORONPARSE       (FALSE) // Emetti un errore se non è possibile interpretare una funzione manuale

// Configurazione parsing di <FILE_NAME_MANMESS>
#define MANMSG_DESC_TRIMEND     (TRUE)  // Elimina gli spazi alla fine della descrizione della funzione manuale
#define MANMSG_DESC_ENDSPACE    (TRUE)  // Inserisce uno spazio al termine della stringa di descrizione della funzione manuale

// Definizione Tipi
typedef enum {
    PILOT_STATUS_NONE = 0,
    PILOT_STATUS_START = 1,
    PILOT_STATUS_MGPILOT = 100,
    PILOT_STATUS_REMCTRL = 200,
} PilotStatusEnum;

typedef struct {
	RTPLC_CHARSTRING alarmsStr[ALARM_LAST_AL-ALARM_FIRST_AL+1][MGPILOT_MAX_F23_ROW_LEN+1];
	RTPLC_CHARSTRING messagesStr[MESSAGE_LAST_MS-MESSAGE_FIRST_MS+1][MGPILOT_MAX_F23_ROW_LEN+1];
} CNC_MESSAGE_TABLE;

// Export funzioni
extern RTPLC_STATUS loadMGPilot(BOOL reset);
extern RTPLC_STATUS loadCncMsg(BOOL reset);
extern RTPLC_STATUS writeRemCtrl(BOOL reset);
extern RTPLC_STATUS updateF2F3(BOOL reset);

#endif // CARICAFMAN_H_INCLUDED
