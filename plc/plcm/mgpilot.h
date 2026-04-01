#ifndef MGPILOT_H_INCLUDED
#define MGPILOT_H_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : mgpilot.h
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Costanti e configurazione mgpilot
//----------------------------------------------------------------------------

// Configurazione MGPilot
#define MGPILOT_ADDRESS         (63)      // Indirizzo CAN MGPilot
#define MGPILOT_CAN_TIMEOUT     (150)     // Timeout per le chiamate omcan da / verso l'MGPilot

#define MGPILOT_MAX_F1_ROW_LEN  (40)      // Massima lunghezza riga menù F1
#define MGPILOT_MAX_F1_ROWS     (200)     // Massimo numero di righe nel menu F1
#define MGPILOT_MAX_CTX_ROW_LEN (21)      // Massima lunghezza menu contestuale
#define MGPILOT_MAX_CTX_ROWS    (10)      // Massimo numero di righe contestuali
#define MGPILOT_MAX_F23_ROW_LEN (140)     // Massima lunghezza riga menù F2 ed F3
#define MGPILOT_MAX_F23_ROWS    (10)      // Massimo numero di righe nei menù F2 ed F3

// Export variabili
extern unsigned char MGPILOT_NODE_DI;               // Numero nodo ingressi MGPilot
extern unsigned char MGPILOT_NODE_DO;               // Numero nodo uscite MGPilot
extern unsigned char MGPILOT_NODE_AI;               // Numero nodo AD MGPilot
extern unsigned char MGPILOT_NODE_ENC;              // Numero nodo encoder MGPilot

// Export funzioni
extern void mgpilot(void);

#endif // MGPILOT_H_INCLUDED
