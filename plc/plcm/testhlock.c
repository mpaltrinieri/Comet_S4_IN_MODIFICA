//@@TODO verificare intera routine se si aggiungerà l'opzione ISO

//----------------------------------------------------------------------------
// TITOLO      : teskhlock.c
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Comunicazione con chiave hardware
//----------------------------------------------------------------------------

#include "all.inc"


void testhlock(void)
{
    // Legge le variabili R degli opzionali e valorizza i flag opportuni nelle variabili A
    HARDLOCK_OPT_WORD1 = (unsigned short)R[R_OPT_SW_PRESENTI_1] & 0xFFFF;
    HARDLOCK_OPT_WORD2 = (unsigned short)R[R_OPT_SW_PRESENTI_2] & 0xFFFF;
	HARDLOCK_OPT_ISO = FTB(R[R_HARDLOCK_ISO]) || ((SIMULATORE_SU_CN || SIMULATORE_SU_PC) && CONF_FUNZ_ISO_ABIL); // Opzione iso gestita da Drill
	// (SIMULATORE_SU_CN && CONF_FUNZ_ISO_ABIL: serve per prove Drill
}
