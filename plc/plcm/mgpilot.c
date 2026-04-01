//----------------------------------------------------------------------------
// TITOLO      : mgpilot.c
// DESCRIZIONE : Gestione pulsantiera MGPilot
// AUTORI      : Mattia Grandi
//----------------------------------------------------------------------------
#include "all.inc"
#include "keypad.h"

//const int MGPILOT_NODE_DI = 4;    // Numero nodo ingressi MGPilot
//const int MGPILOT_NODE_DO = 4;    // Numero nodo uscite MGPilot
//const int MGPILOT_NODE_AI = 4;    // Numero nodo AD MGPilot
//const int MGPILOT_NODE_ENC = 0;   // Numero nodo encoder MGPilot

unsigned char MGPILOT_NODE_DI;    // Numero nodo ingressi MGPilot
unsigned char MGPILOT_NODE_DO;    // Numero nodo uscite MGPilot
unsigned char MGPILOT_NODE_AI;    // Numero nodo AD MGPilot
unsigned char MGPILOT_NODE_ENC;   // Numero nodo encoder MGPilot


void mgpilot()
{
	if (!CONF_MGPILOT)
        return;

	MGPILOT_NODE_DI = (unsigned char) R[R_MGPILOT_NODE_DI];
	MGPILOT_NODE_DO = (unsigned char) R[R_MGPILOT_NODE_DO];
	MGPILOT_NODE_AI = (unsigned char) R[R_MGPILOT_NODE_AI];
	MGPILOT_NODE_ENC = (unsigned char) R[R_MGPILOT_NODE_ENC];

    MGPILOT_START = KEYPAD_KEY_START(MGPILOT_NODE_DI);     // Tasto START
	MGPILOT_HOLD  = KEYPAD_KEY_HOLD(MGPILOT_NODE_DI);      // Tasto HOLD
	MGPILOT_UP    = KEYPAD_KEY_ARRHIGH(MGPILOT_NODE_DI);   // Tasto FRECCIA SU
	MGPILOT_DOWN  = KEYPAD_KEY_ARRDOWN(MGPILOT_NODE_DI);   // Tasto FRECCIA GIU
	MGPILOT_A     = KEYPAD_KEY_A(MGPILOT_NODE_DI);         // Tasto A
	MGPILOT_B     = KEYPAD_KEY_B(MGPILOT_NODE_DI);         // Tasto B
	MGPILOT_RESET = KEYPAD_KEY_RESET(MGPILOT_NODE_DI);     // Tasto RESET
	MGPILOT_F1    = KEYPAD_KEY_F1(MGPILOT_NODE_DI);        // Tasto F1
	MGPILOT_F2    = KEYPAD_KEY_F2(MGPILOT_NODE_DI);        // Tasto F2
	MGPILOT_F3    = KEYPAD_KEY_F3(MGPILOT_NODE_DI);        // Tasto F3
	MGPILOT_F4    = KEYPAD_KEY_F4(MGPILOT_NODE_DI);        // Tasto F4

	MGPILOT_CURRENT_MENU = KEYPAD_CURRENTMENU(MGPILOT_NODE_DI);
	MGPILOT_CURRENT_ITEM = KEYPAD_CURRENTITEM(MGPILOT_NODE_DI);

	// Interpretazione funzione manuale
    if ((MGPILOT_CURRENT_MENU == KEYPAD_MEN_CMD) && IN_RANGE(MGPILOT_CURRENT_ITEM-1, 0, fmanMap.fmanCount - 1)) { 
        MGPILOT_SEL = fmanMap.map[MGPILOT_CURRENT_ITEM-1];
    } else {
        MGPILOT_SEL = 0;
    }

    KEYPAD_LEDA(MGPILOT_NODE_DO, LAMP_ESEG_A);       // Led funzione A eseguita
    KEYPAD_LEDB(MGPILOT_NODE_DO, LAMP_ESEG_B);       // Led funzione A eseguita
    KEYPAD_LEDRUN(MGPILOT_NODE_DO, LAMP_CYCLE); // Led funzione ciclo in esecuzione
}
