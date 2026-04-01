/*
        --------------------------------------------------------------   
        TITOLO:         Shared_Mem_MC
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione sincronizzazione esecuzione ISO fra 4
						canali CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    void Syn_0_MC(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        QUA 7.2 COSTANTINO MULTICANALE
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           20-20-2017
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Medici Stefano
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

/*
Il meccanismo di sincronizzazione di n canali si basa su una matrice di contatori nxn condivisa da tutti i canali,
si ottiene questo utilizzazno variabili PLC che sono comuni a tutti i canali. 

Quando il canale i-esimo incontra la $M350 esso si blocca (FATM), incrementa il proprio contatore 
(quello in posizione i,i) e copia i contatori di ciascun canale (quelli in posizione j,j con j<>i) incrementati di uno 
ed attende il verificarsi della condizione di sblocco che avviene quando i contatori dei rispettivi altri canali 
coincidono con quelli attesi. 

Per esempio di seguito la condizione di sblocco di tutti e 4 i canali con la sequenza CH1, CH0, CH1

                     *                      *       *                   !  *  
|0 |0 |0 |0 |    |0 |1 |0 |0 |    |0 |1 |0 |1 |    |1 |1 |0 |1 |    |1 |1 |2 |1 |
|0 |0 |0 |0 | -> |0 |1 |0 |0 |    |0 |1 |0 |2 |    |2 |1 |0 |2 |    |2 |1 |2 |2 |
|0 |0 |0 |0 |    |0 |1 |0 |0 |    |0 |1 |0 |1 |    |1 |1 |0 |1 |    |1 |1 |1 |1 |
|0 |0 |0 |0 |    |0 |1 |0 |0 |    |0 |1 |0 |1 |    |2 |1 |0 |1 |    |2 |1 |2 |1 |

In un unico passo di PLC si sbloccano tutti i CNC:

          !       !                      !                           F  F  F  F
|1 |2 |2 |1 |    |1 |2 |2 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    
|2 |2 |2 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    
|1 |2 |1 |1 |    |1 |2 |1 |2 |    |2 |2 |1 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    
|2 |2 |2 |1 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    |2 |2 |2 |2 |    

* = $M350 condizione di blocco
! = condizione di sblocco verificata
F = FATM rilasciato ovvero sblocco del CNC

È possibile definire un filtro per ciascun canale che identifica solo alcuni dei canali da sincronizzare 
fra quelli possibili. 

Nel caso particolare in cui si voglia sempre la sincronizzazione di tutti i canali allora il filtro sarà 
fatto di tutti uni (R6862 = 1+2+4), in questo caso la distanza fra i contatori è sempre < 2 ed è quindi 
possibile eseguire un controllo di consistenza. Tale soluzione è quella utilizzata per la Quadra.

Utilizzo dei filtri per la sincronizzazione di 4 canali CNC. 

La regola è che il canale CNC blocca se stesso ed attende i canali indicati nel proprio filtro per sbloccarsi,  
di seguito alcuni esempi

ISO CH0         | ISO CH1        | ISO CH2        | 
  (0)           |  (1)           |  (2)           |
---------------------------------------------------
                |                |                |
R[6862]=1+2+4   |R[6862]=1+2+4   |R[6862]=1+2+4   |Sincronizzazione CH0, CH1, CH2
$M350           |$M350           |$M350           |
                |                |                |
R[6862]=1+2     |R[6862]=1+2     |R[6862]=    0   |Sincronizzazione CH0, CH1
$M350           |$M350           |$M350           |
                |                |                |
R[6862]=1+  4   |R[6862]=  0     |R[6862]=1+  4   |Sincronizzazione CH0,      CH2
$M350           |$M350           |$M350           |
                |                |                |
R[6862]=0       |R[6862]=  2+4   |R[6862]=  2+4   |Sincronizzazione      CH1, CH2     
$M350           |$M350           |$M350           |
                |                |                |
		 
Per il PLC:
(0) =  (int)        R[R_FILT_SYNC0_MC] =        R[6862]
(1)	=  (int) Aris_CH1[R_FILT_SYNC0_MC] = Aris_CH1[6862]
(2)	=  (int) Aris_CH2[R_FILT_SYNC0_MC] = Aris_CH2[6862]
*/


#include        "all.inc"


#define SynNChannel				3
#define Syn_MOD_count			100

int		Syn_0_Filt_Arr [SynNChannel];				//Filtro per sincronizzare solo alcuni canali 1+2+4+8 = il CNC si sblocca quando tutti i canali hanno ricevuto la M350
int		Syn_0_Cont_Arr [SynNChannel][SynNChannel];	//Matrice 4x4 dei contatori delle richieste di M350

int		Syn_0_Done [SynNChannel]; 
int		Syn_0_Done_old [SynNChannel]; 

int		Syn_0_Execute [SynNChannel];

int		Syn_0_Busy [SynNChannel];

int    Syn_0_MReq_old [SynNChannel];



void Syn_0_CNC_MC(int myChannel, unsigned short MReq);


void Syn_0_MC_RESET_1_all(void)
{
	int i=0;
	int j=0;

	//Default: sincronizzazione di tutti i canali
	//R[R_FILT_SYNC0_MC] = Aris_CH1[R_FILT_SYNC0_MC] = Aris_CH2[R_FILT_SYNC0_MC] = nFiltSync;
	//for (i=0; i<SynNChannel; i++) {nFiltSync += sh; sh <<= 1;}

	//Azzera i contatori dei CNC da sincronizzare
	for (i=0; i<SynNChannel; i++)
	{
		Syn_0_Done [i]		= 0; 
		Syn_0_Done_old [i]	= 0; 
		Syn_0_Execute [i]	= 0;
		Syn_0_Busy [i]		= 0;
		Syn_0_MReq_old [i]	= 0;
		for (j=0; j<SynNChannel; j++) Syn_0_Cont_Arr [i][j] = 0;
	}

	R[R_FILT_SYNC0_MC] = R[R_FILT_SYNC1_TO_0_MC];
	Aris_CH1[R_FILT_SYNC0_MC] = Aris_CH1[R_FILT_SYNC1_TO_0_MC];
	Aris_CH2[R_FILT_SYNC0_MC] = Aris_CH2[R_FILT_SYNC1_TO_0_MC];
}


void Syn_0_MC_RESET_all(void)
{
	int i=0;
	int j=0;
	int nFiltSync = 0;
	int sh = 1;

	for (i=0; i<SynNChannel; i++) {nFiltSync += sh; sh <<= 1;}

	//Default: sincronizzazione di tutti i canali
	R[R_FILT_SYNC0_MC] = Aris_CH1[R_FILT_SYNC0_MC] = Aris_CH2[R_FILT_SYNC0_MC] = (double) nFiltSync;

	//Azzera i contatori dei CNC da sincronizzare
	for (i=0; i<SynNChannel; i++)
	{
		Syn_0_Done [i]		= 0; 
		Syn_0_Done_old [i]	= 0; 
		Syn_0_Execute [i]	= 0;
		Syn_0_Busy [i]		= 0;
		Syn_0_MReq_old [i]	= 0;
		for (j=0; j<SynNChannel; j++) Syn_0_Cont_Arr [i][j] = 0;
	}
}



void Syn_0_MC(void)
{
	int i = 0;
	int cont_loop = 0;
	int doLoop = 0;


	if (RESET_MC) 
	{
		Syn_0_MC_RESET_all();
		return;
	}

	Syn_0_Filt_Arr [0] =  (int) R[R_FILT_SYNC0_MC];
	Syn_0_Filt_Arr [1] =  (int) Aris_CH1[R_FILT_SYNC0_MC];
	Syn_0_Filt_Arr [2] =  (int) Aris_CH2[R_FILT_SYNC0_MC];


	//Se il filtro è 0 annulla il sincronismo e da immediatamente il FATM
	if (!Syn_0_Filt_Arr [0]) M350 = 0;
	if (!Syn_0_Filt_Arr [1]) M_CH1_350 = 0;
	if (!Syn_0_Filt_Arr [2]) M_CH2_350 = 0;

	//Se il CNC è  già bloccato non esegue il primo controllo, in questo modo i CNC non bloccati possono incrementare i contatori

	for (i=0; i<SynNChannel; i++)
	{
		if (Syn_0_Busy [i]) Syn_0_Execute[i] = 0;
		else Syn_0_Execute[i] = 1;
	}

	do 
	{
		//Verifica e incremento contatori
		Syn_0_CNC_MC (0, (unsigned short) M350);  
		Syn_0_CNC_MC (1, (unsigned short) M_CH1_350);  
		Syn_0_CNC_MC (2, (unsigned short) M_CH2_350);  

		//Sblocco del CNC
		if (Syn_0_Done [0]) M350 = 0;
		if (Syn_0_Done [1]) M_CH1_350 = 0;
		if (Syn_0_Done [2]) M_CH2_350 = 0;

		Syn_0_MReq_old [0] = M350;
		Syn_0_MReq_old [1] = M_CH1_350;
		Syn_0_MReq_old [2] = M_CH2_350;

		//Al secondo giro esegue sempre il controllo per tutti i CNC
		for (i=0; i<SynNChannel; i++) Syn_0_Execute[i] = 1;

		//Se almeno un canale si è sbloccato
		if ((Syn_0_Done [0] && !Syn_0_Done_old [0]) ||
			(Syn_0_Done [1] && !Syn_0_Done_old [1]) ||
			(Syn_0_Done [2] && !Syn_0_Done_old [2]) ||
			!cont_loop)
			doLoop = 1;
		else 
			doLoop = 0;

		cont_loop++;

		for (i=0; i<SynNChannel; i++) Syn_0_Done_old [i] = Syn_0_Done [i]; 

	}
	while (doLoop);

	SYN_0_0_0 = (short int) Syn_0_Cont_Arr [0][0];
	SYN_0_0_1 = (short int) Syn_0_Cont_Arr [0][1];
	SYN_0_0_2 = (short int) Syn_0_Cont_Arr [0][2];

	SYN_0_1_0 = (short int) Syn_0_Cont_Arr [1][0];
	SYN_0_1_1 = (short int) Syn_0_Cont_Arr [1][1];
	SYN_0_1_2 = (short int) Syn_0_Cont_Arr [1][2];

	SYN_0_2_0 = (short int) Syn_0_Cont_Arr [2][0];
	SYN_0_2_1 = (short int) Syn_0_Cont_Arr [2][1];
	SYN_0_2_2 = (short int) Syn_0_Cont_Arr [2][2];

	SYN_0_3_0 = (short int) Syn_0_Cont_Arr [3][0];
	SYN_0_3_1 = (short int) Syn_0_Cont_Arr [3][1];
	SYN_0_3_2 = (short int) Syn_0_Cont_Arr [3][2];
}


void Syn_0_CNC_MC(int myChannel, unsigned short MReq)
{
	int flag = 1;
	int ok = 1;
	int doSync = 0;

	int i = 0;
	int j = 0;

	Syn_0_Busy [myChannel] = MReq;

	if (!MReq) return;

	//Se arriva una nuova richiesta di sincronizzazione
	if (MReq && !Syn_0_MReq_old [myChannel])
	{
		Syn_0_Done [myChannel] = 0;
		for (i=0; i<SynNChannel; i++)
			//Incrementa di uno i contatori dei CNC di myChannel
			Syn_0_Cont_Arr[myChannel][i] = (Syn_0_Cont_Arr[i][i]+1) % Syn_MOD_count;
	}

	//Se non è richiesto il controllo per la condizione di avvenuta sincronizzazione esce
	if (!Syn_0_Execute [myChannel]) return;

	ok = 1;
	flag = 1;

	for (i=0; (i<SynNChannel) && ok; i++)
	{
		//Flag che indica se il canale myChannel si deve sincronizzare con il canale i-esimo
		doSync = Syn_0_Filt_Arr[myChannel] & flag;		
		if ((i != myChannel) && (doSync))		
		{
			//Se il contatore di myChannel è diverso dal contatore del canale i-esimo allora rimane bloccato
			if (Syn_0_Cont_Arr[myChannel][i] != Syn_0_Cont_Arr[i][i]) 
				ok = 0;	
		}
		flag = flag << 1;
	}

	//Se è verificata la condizione di sblocco del canale myChannel
	if (ok)
	{
		//Sblocco eseguito
		Syn_0_Done [myChannel] = 1;
		//Se è appena stato eseguito lo sblocco 
		if (Syn_0_Done [myChannel] && (!Syn_0_Done_old [myChannel]))
		{
			//incremento il contatore di myChannel
			Syn_0_Cont_Arr[myChannel][myChannel] = (Syn_0_Cont_Arr[myChannel][myChannel] + 1) % Syn_MOD_count;
			for (i=0; i<SynNChannel; i++)
				//setto i contatori degli altri canali come il contatore del canale myChannel che ho appena incrementato 
				Syn_0_Cont_Arr[myChannel][i] = Syn_0_Cont_Arr[myChannel][myChannel];
		}
	}
}


int distance_MOD (int a, int b)
{
	int aPlus, bPlus;
	int res1, res2, res3;
	int dist;
	
	aPlus = a + Syn_MOD_count;
	bPlus = b + Syn_MOD_count;

	res1 = (abs(a-b)) % Syn_MOD_count;
	res2 = (abs(aPlus-b)) % Syn_MOD_count;
	res3 = (abs(a-bPlus)) % Syn_MOD_count;

	if (res1<=res2) dist = res1;
	else dist = res2;

	if (res3<dist) dist = res3;

	return dist;
}
