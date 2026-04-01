//----------------------------------------------------------------------------
// TITOLO      : funzman.c
// DESCRIZIONE : Creazione flags funzioni manuali
// AUTORI      : Mattia Grandi
//----------------------------------------------------------------------------
#include "all.inc"

void funzman(void)
{
    const int wordSize = sizeof(FUNZ_MAN_FIRST_WORD);
    const int bitInWord = 8*wordSize;
    const int bufLen = (&FUNZ_MAN_LAST_WORD - &FUNZ_MAN_FIRST_WORD + 1);
    const int minFunzMan = 0;
    const int maxFunzMan = minFunzMan + bufLen*bitInWord - 1;

    // Reset di tutti i flag delle funzioni manuali
    memset(&FUNZ_MAN_FIRST_WORD, 0, bufLen*wordSize);
	
	// Set del flag indicato dal codice della funzione manuale
	if (!COMANDO_A && !COMANDO_B)
        APP_CODE_FUNZMAN = !CONF_MGPILOT ? (short)R[R_SEL] : MGPILOT_SEL;

	// L'indice deve essere compreso fra i limiti ammessi     
	if (!IN_RANGE(APP_CODE_FUNZMAN, minFunzMan, maxFunzMan))
        APP_CODE_FUNZMAN = minFunzMan;
	
	// Appoggio funzione manuale da PLC 
	R[R_APPSEL] = (float)APP_CODE_FUNZMAN;
	
    (&FUNZ_MAN_FIRST_WORD)[(APP_CODE_FUNZMAN - minFunzMan) / bitInWord] = (1u << ((APP_CODE_FUNZMAN - minFunzMan) % bitInWord));

    // Comandi manuali
	//Gestione pulsantiera MGPILOT inserita in central per problemi 
	//sincronizzazione dei timer sui comandi A e B
    //if (!CONF_MGPILOT) {
    //    COMANDO_A = FTB(R[R_BUTTON_A]);
    //    COMANDO_B = FTB(R[R_BUTTON_B]);
    //} else {
    //    COMANDO_A = MGPILOT_A;
    //    COMANDO_B = MGPILOT_B;
    //}
}
