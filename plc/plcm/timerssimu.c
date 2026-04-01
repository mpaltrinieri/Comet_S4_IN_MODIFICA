/* 
        --------------------------------------------------------------
        TITOLO:         TimersSimu.c
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Timers supplementari
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    timersSimu(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          maxTSimu   [N_TIMERS_SIMU]
						ingrTSimu  [N_TIMERS_SIMU]
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        FUNZ. M:        
        --------------------------------------------------------------
        --------------------------------------------------------------
        FUNZ. MANUAL:   
        --------------------------------------------------------------
        --------------------------------------------------------------
        ALLARMI:        
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        ULTM 0.0 (ULTRA MASTER)
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           11-2004
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Medici Stefano
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"

unsigned char ingrTSimu    [N_TIMERS_SIMU]; //ingresso
unsigned char RP_TSimu     [N_TIMERS_SIMU]; //segnale ritardato positivo
unsigned char RN_TSimu     [N_TIMERS_SIMU]; //segnale ritardato negativo

unsigned int  maxTSimu     [N_TIMERS_SIMU]; //limite contatore
unsigned int  RP_contTSimu [N_TIMERS_SIMU]; //contatori
unsigned int  RN_contTSimu [N_TIMERS_SIMU]; //contatori

void timersSimu_pon(void)
{
	if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
	{
		int             nTimer          = 0;
		unsigned int    *pmaxTSimu     = maxTSimu;
		unsigned int    *pRP_contTSimu = RP_contTSimu;
		unsigned int    *pRN_contTSimu = RN_contTSimu;
		unsigned char   *pRP_TSimu     = RP_TSimu;
		unsigned char   *pRN_TSimu     = RN_TSimu;

		for (nTimer=0;nTimer<N_TIMERS_SIMU;nTimer++,pmaxTSimu++,pRP_contTSimu++,pRN_contTSimu++,pRP_TSimu++,pRN_TSimu++)
		{
			*pRP_contTSimu = 0;
			*pRN_contTSimu = 0;		
			*pRP_TSimu     = 0;
			*pRN_TSimu     = 0;

			//Inizializzazione timers
			*pmaxTSimu = ncicplc ((float)(*pmaxTSimu/1000.0));

			//if (tauPLC > 0) *pmaxTSimu    = (unsigned int)(((float)(*pmaxTSimu)) / ((tauPLC))) ;
			//else            *pmaxTSimu    = (unsigned int)(((float)(*pmaxTSimu)) / ((float)T_TAU_DEFAULT));		
		}
	}
}

void tSD(int nTimer, unsigned char ingr)
{
	if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
	{
		ingrTSimu[nTimer] = ingr;

		if (ingr) 
		{
			RN_contTSimu[nTimer] = maxTSimu[nTimer];
			RN_TSimu[nTimer]     = 1;
			if (!maxTSimu[nTimer]) 
				RP_TSimu[nTimer] = 1;
		}
		else      
		{	
			RP_contTSimu[nTimer] = maxTSimu[nTimer];
			RP_TSimu[nTimer]     = 0;
			if (!maxTSimu[nTimer]) 
				RN_TSimu[nTimer] = 0;
		}
	}
}

void timersSimu(void)
{
	if(SIMULATORE_SU_PC || SIMULATORE_SU_CN)
	{
		int             nTimer          = 0;
		unsigned int    *pmaxTSimu     = maxTSimu;
		unsigned int    *pRP_contTSimu = RP_contTSimu;
		unsigned int    *pRN_contTSimu = RN_contTSimu;

		unsigned char   *pingrTSimu    = ingrTSimu;
		unsigned char   *pRP_TSimu     = RP_TSimu;
		unsigned char   *pRN_TSimu     = RN_TSimu;

		R[R_SIMU_MAXTSIMU] = (float)maxTSimu[(int) R[R_SIMU_NTIMERSIMU]];
		R[R_SIMU_RPCONTTSIMU] = (float)RP_contTSimu[(int) R[R_SIMU_NTIMERSIMU]];
		R[R_SIMU_RNCONTTSIMU] = (float)RN_contTSimu[(int) R[R_SIMU_NTIMERSIMU]];
		R[R_SIMU_INGRTSIMU] = (float)ingrTSimu[(int) R[R_SIMU_NTIMERSIMU]];
		R[R_SIMU_RPTSIMU] = (float)RP_TSimu[(int) R[R_SIMU_NTIMERSIMU]];
		R[R_SIMU_RNTSIMU] = (float)RN_TSimu[(int) R[R_SIMU_NTIMERSIMU]];

		for (nTimer=0;nTimer<N_TIMERS_SIMU;nTimer++,pmaxTSimu++,pRP_contTSimu++,pRN_contTSimu++,pingrTSimu++,pRP_TSimu++,pRN_TSimu++)
		{
			if (*pingrTSimu) //ingresso
			{
				//se vero
				if (*pRP_contTSimu) //testa se ritardo terminato
				{
					//se ancora da terninare
					(*pRP_contTSimu)--; //incrementa il contatore	
					*pRP_TSimu = 0;     //setta l'uscita a 0 perchè il ritardo deve ancora terminare
				}
				else *pRP_TSimu = 1;    //setta l'uscita a 1 perchè il ritardo è già terminato
				*pRN_contTSimu = *pmaxTSimu;     //con ingresso vero resetto il timer per il RN
			}
			else
			{
				//se falso
				if (*pRN_contTSimu) //testa se ritardo terminato
				{
					//se ancora da terninare
					(*pRN_contTSimu)--; //incrementa il contatore	
					*pRN_TSimu = 1;     //setta l'uscita a 1 perchè il ritardo deve ancora terminare
				}
				else *pRN_TSimu = 0;    //setta l'uscita a 0 perchè il ritardo è già terminato
				*pRP_contTSimu = *pmaxTSimu;     //con ingresso false resetto il timer per il RP
			}
		}
	}
}

