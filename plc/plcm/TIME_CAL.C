/*
        --------------------------------------------------------------
        TITOLO:         TIME_CAL
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Calcolo tempo ciclo pezzo
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    time_cal(void)
		--------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          R[R_COUNT_TIME]     Abilit.cont.tempo
                        CICLO_ON            Ciclo in corso
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         R[R_CYCLE_TIME]     Cont.tempo di lavoro
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           30-08-2000
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Pecchi Andrea
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

CONF_CN CONFIGURAZIONE_CN;
float TAU;
int   TAUPC;
long  N_CICLI;
double APPTIME;
double APPTIMESX;
double APPTIMEDX;
long  N_CICLISX;
long  N_CICLIDX;
double tauPLC;

void    time_cal(void)
{

	if (CONF_CALC_TIME)
	{

		/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
		if (PON)
		{
			GetConfCn (&CONFIGURAZIONE_CN);
			TAU   = CONFIGURAZIONE_CN.tau*500;
			TAUPC = CONFIGURAZIONE_CN.taupc;

			tauPLC = (double)( (int)(  ( (1.0 / ncicplc (1.0)) * 1000) + 0.5) );
			R[R_CICLO_PLC] = tauPLC;  //visualizzazione per debug 

			read_var (VL_FLOT, 4065, -1, -1, &CICLO_ASSI);      /* V4065 = durata del ciclo assi in secondi */
		}

		/************************ Tempo Ciclo in MULTIPEZZO **************************/

		if (R[R_DOUBLE]==0)
		{
			/**** CALCOLO TEMPO CICLO DI LAVORO IN SIMULAZIONE ****/
			if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
			{
				if (R[R_COUNT_TIMESX])
				{
					if (CICLO_ON)
					{
						N_CICLI = N_CICLI + 1;
						R[R_CYCLE_TIMESX] = (float)((N_CICLI * tauPLC / 60000) * R[R_AGG_TIME]);
					}
				}
				else
					N_CICLI = 0;
			}


			/**** CALCOLO TEMPO CICLO DI LAVORO IN MODALITA' NORMALE****/
			if(!SIMULATORE_SU_PC && !SIMULATORE_SU_CN)
			{
				if (R[R_COUNT_TIMESX])
				{
					if (CICLO_ON)
					{
						N_CICLI = N_CICLI + 1;
						R[R_CYCLE_TIMESX] = (float)N_CICLI * tauPLC / 60000;
					}
				}
				else
					N_CICLI = 0;
			}
		}

	}
}
