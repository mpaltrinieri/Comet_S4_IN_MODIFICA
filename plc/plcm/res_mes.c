//----------------------------------------------------------------------------
// TITOLO      : res_mes.c
// DESCRIZIONE : Gestione reset messaggi di diagnostica
// AUTORI      : Pecchi Andrea
//----------------------------------------------------------------------------
#include "all.inc"


BOOL MEM_RESET_ALL, OLD_MESSAGGI_PRES, OLD_ALLARMI_PRES;

void res_mes()
{
    static int TIME_RESET = 50;

    // Flag di reset allarmi
    if (R[R_RESET_ALL] < 0.5)
        TIME_RESET = 50;
    else if (TIME_RESET > 0)
        TIME_RESET--;
    else
        R[R_RESET_ALL] = 0;

    // Condizione di reset allarmi
    RESET_ALL = (R[R_RESET_ALL]>0.5) || MGPILOT_F4 && CONF_RESET_ALL_F4;

    // Reset generico messaggi, attenzioni, allarmi
	if ((RESET_ALL || RESET_MC) && !MEM_RESET_ALL) {
	    messagp(0);
	    attenz(0);
	    allarm(0);
		MEM_RESET_ALL = 1;
        LOG_MSG2(1, "Emesso reset allarmi, messaggi ed attenzioni");
	}
	if (!RESET_ALL && !RESET_MC)
		MEM_RESET_ALL = 0;

    // Reset allarmi per un ciclo in assenza di allarmi da lanciare
	if(OLD_ALLARMI_PRES && !ALLARMI_PRES)
	{
		LOG_MSG2(1, "Emesso reset allarmi old");
		allarm  (0);
	}

    OLD_ALLARMI_PRES = ALLARMI_PRES;
	//**********

    // Reset attenzioni per un ciclo in assenza di messaggi da lanciare
	if(OLD_MESSAGGI_PRES && !MESSAGGI_PRES)
		attenz(0);

    OLD_MESSAGGI_PRES = MESSAGGI_PRES;			

    // Appoggio eliminatore allarmi
    WORD_ELIMINA_ALLARMI = FTB(R[R_ELIMINA_ALLARMI]);
}
