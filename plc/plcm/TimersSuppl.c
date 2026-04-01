/* 
        --------------------------------------------------------------
        TITOLO:         TimersSuppl.c
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Timers supplementari
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void timersSuppl_pon(void)
        				void tS(int nTimer, unsigned char ingr)
						void timersSuppl(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          N_TIMERS_SUPPL = numero di timer supplementari
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
        RELEASE:        001.000
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           08.2006
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Medici Stefano
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

/*
Esempi:

#define N_TIMERS_SUPPL        128

________________________________________________
Esempio di utilizzo:

Inizializzazione:
maxTSuppl [TS_TIMEOUT_RIP_NOBL] = 1000.0; {1000 msec
(questa parte è automatizzata se si utilizza il confmac.xxx con gestione dei timer)

Settaggio:
tS(TS_TIMEOUT_RIP_NOBL, (unsigned char) BLOC_RIPARI);

Uscita:
if (RP_TSuppl [TS_TIMEOUT_RIP_NOBL] && !RIP_CHIUSI_I && AUTO && RP_AUXON) 
{}

Conteggio:
void  plc (void)
{
	...
	timersSuppl();
}
*/

#include        "all.inc"

unsigned int  maxTSuppl    [N_TIMERS_SUPPL]; //limite contatore
unsigned char ingrTSuppl   [N_TIMERS_SUPPL]; //ingresso
unsigned char RP_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato positivo
unsigned char RN_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato negativo
unsigned char DP_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato positivo
unsigned char DN_TSuppl    [N_TIMERS_SUPPL]; //segnale ritardato negativo

unsigned int RP_contTSuppl [N_TIMERS_SUPPL]; //contatori
unsigned int RN_contTSuppl [N_TIMERS_SUPPL]; //contatori

void timersSuppl_pon(void)
{
	int           nTimer          = 0;
	unsigned int  *pmaxTSuppl     = maxTSuppl;
	unsigned int  *pRP_contTSuppl = RP_contTSuppl;
	unsigned int  *pRN_contTSuppl = RN_contTSuppl;
	unsigned char *pRP_TSuppl     = RP_TSuppl;
	unsigned char *pRN_TSuppl     = RN_TSuppl;
	unsigned char *pDP_TSuppl     = DP_TSuppl;
	unsigned char *pDN_TSuppl     = DN_TSuppl;
	
	for (nTimer=0;nTimer<N_TIMERS_SUPPL;nTimer++,pmaxTSuppl++,pRP_contTSuppl++,pRN_contTSuppl++,pRP_TSuppl++,pRN_TSuppl++,pDP_TSuppl++,pDN_TSuppl++)
	{
		*pRP_contTSuppl = 0;
		*pRN_contTSuppl = 0;		
		*pRP_TSuppl     = 0;
		*pRN_TSuppl     = 0;
		*pDP_TSuppl     = 0;
		*pDN_TSuppl     = 0;
		*pmaxTSuppl = ncicplc ((double)(*pmaxTSuppl/1000.0));
		if(nTimer == (N_TIMERS_SUPPL-1)) rtplctrace2(1,_T("Timer Supplementari"));
	}
}

void tS(int nTimer, unsigned char ingr)
{
	DP_TSuppl[nTimer] = ingr && !ingrTSuppl[nTimer];
	DN_TSuppl[nTimer] = !ingr && ingrTSuppl[nTimer];
	
	ingrTSuppl[nTimer] = ingr;
	
	if (ingr) 
	{
		RN_contTSuppl[nTimer] = maxTSuppl[nTimer];
		RN_TSuppl[nTimer]     = 1;
		if (!maxTSuppl[nTimer]) 
			RP_TSuppl[nTimer] = 1;
	}
	else      
	{	
		RP_contTSuppl[nTimer] = maxTSuppl[nTimer];
		RP_TSuppl[nTimer]     = 0;
		if (!maxTSuppl[nTimer]) 
			RN_TSuppl[nTimer] = 0;
	}
}

void timersSuppl(void)
{
	int           nTimer          = 0;
	unsigned int  *pmaxTSuppl     = maxTSuppl;
	unsigned int  *pRP_contTSuppl = RP_contTSuppl;
	unsigned int  *pRN_contTSuppl = RN_contTSuppl;
	unsigned char *pingrTSuppl    = ingrTSuppl;
	unsigned char *pRP_TSuppl     = RP_TSuppl;
	unsigned char *pRN_TSuppl     = RN_TSuppl;
	
// Debug copiato dai TSIMU
	R[R_SIMU_MAXTSUPPL] = (float)maxTSuppl[(int) R[R_SIMU_NTIMERSUPPL]];
	R[R_SIMU_RPCONTTSUPPL] = (float)RP_contTSuppl[(int) R[R_SIMU_NTIMERSUPPL]];
	R[R_SIMU_RNCONTTSUPPL] = (float)RN_contTSuppl[(int) R[R_SIMU_NTIMERSUPPL]];
	R[R_SIMU_INGRTSUPPL] = (float)ingrTSuppl[(int) R[R_SIMU_NTIMERSUPPL]];
	R[R_SIMU_RPTSUPPL] = (float)RP_TSuppl[(int) R[R_SIMU_NTIMERSUPPL]];
	R[R_SIMU_RNTSUPPL] = (float)RN_TSuppl[(int) R[R_SIMU_NTIMERSUPPL]];
	
	
	for (nTimer=0;nTimer<N_TIMERS_SUPPL;nTimer++,pmaxTSuppl++,pRP_contTSuppl++,pRN_contTSuppl++,pingrTSuppl++,pRP_TSuppl++,pRN_TSuppl++)
	{
		if (*pingrTSuppl) //ingresso
		{
			//se vero
			if (*pRP_contTSuppl) //testa se ritardo terminato
			{
				//se ancora da terninare
				(*pRP_contTSuppl)--; //decrementa il contatore	
				*pRP_TSuppl = 0;     //setta l'uscita a 0 perchè il ritardo deve ancora terminare
			}
			else *pRP_TSuppl = 1;    //setta l'uscita a 1 perchè il ritardo è già terminato
			*pRN_contTSuppl = *pmaxTSuppl;     //con ingresso vero resetto il timer per il RN
		}
		else
		{
			//se falso
			if (*pRN_contTSuppl) //testa se ritardo terminato
			{
				//se ancora da terninare
				(*pRN_contTSuppl)--; //decrementa il contatore	
				*pRN_TSuppl = 1;     //setta l'uscita a 1 perchè il ritardo deve ancora terminare
			}
			else *pRN_TSuppl = 0;    //setta l'uscita a 0 perchè il ritardo è già terminato
			*pRP_contTSuppl = *pmaxTSuppl;     //con ingresso false resetto il timer per il RP
		}	
	}
}
