/*
        --------------------------------------------------------------   
        TITOLO:         Shared_Mem_MC
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione sincronizzazione esecuzione ISO fra 4
						canali CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    void Syn_1_MC(void)
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

#include        "all.inc"


#define SynNChannel				3
#define Syn_MOD_count			100

int		Syn_1_Filt_Arr [SynNChannel];				//Filtro per sincronizzare solo alcuni canali 1+2+4+8 = il CNC si sblocca quando tutti i canali hanno ricevuto la M3000
int		Syn_1_Cont_Arr [SynNChannel][SynNChannel];	//Matrice 4x4 dei contatori delle richieste di M3000

int		Syn_1_Done [SynNChannel]; 
int		Syn_1_Done_old [SynNChannel]; 

int		Syn_1_Execute [SynNChannel];

int		Syn_1_Busy [SynNChannel];

int    Syn_1_MReq_old [SynNChannel];



void Syn_1_CNC_MC(int myChannel, unsigned short MReq);


void Syn_1_MC_RESET_all(void)
{
	int i=0;
	int j=0;
	int nFiltSync = 0;
	int sh = 1;

	for (i=0; i<SynNChannel; i++) {nFiltSync += sh; sh <<= 1;}

	//Default: sincronizzazione di tutti i canali
	R[R_FILT_SYNC1_MC] = Aris_CH1[R_FILT_SYNC1_MC] = Aris_CH2[R_FILT_SYNC1_MC] = (double) nFiltSync;
	R[R_FILT_SYNC1_TO_0_MC] = Aris_CH1[R_FILT_SYNC1_TO_0_MC] = Aris_CH2[R_FILT_SYNC1_TO_0_MC] = (double) nFiltSync;

	//Azzera i contatori dei CNC da sincronizzare
	for (i=0; i<SynNChannel; i++)
	{
		Syn_1_Done [i]		= 0; 
		Syn_1_Done_old [i]	= 0; 
		Syn_1_Execute [i]	= 0;
		Syn_1_Busy [i]		= 0;
		Syn_1_MReq_old [i]	= 0;
		for (j=0; j<SynNChannel; j++) Syn_1_Cont_Arr [i][j] = 0;
	}
}


void Syn_1_MC(void)
{
	int i = 0;
	int cont_loop = 0;
	int doLoop = 0;
	int unlock = 0;

	if (RESET_MC) 
	{
		Syn_1_MC_RESET_all();
		return;
	}
	
	Syn_1_Filt_Arr [0] =  (int) R[R_FILT_SYNC1_MC];
	Syn_1_Filt_Arr [1] =  (int) Aris_CH1[R_FILT_SYNC1_MC];
	Syn_1_Filt_Arr [2] =  (int) Aris_CH2[R_FILT_SYNC1_MC];

	//Se il filtro è 0 annulla il sincronismo e da immediatamente il FATM
	if (!Syn_1_Filt_Arr [0]) M351 = 0;
	if (!Syn_1_Filt_Arr [1]) M_CH1_351 = 0;
	if (!Syn_1_Filt_Arr [2]) M_CH2_351 = 0;

	//Se il CNC è  già bloccato non esegue il primo controllo, in questo modo i CNC non bloccati possono incrementare i contatori

	for (i=0; i<SynNChannel; i++)
	{
		if (Syn_1_Busy [i]) Syn_1_Execute[i] = 0;
		else Syn_1_Execute[i] = 1;
	}

	do 
	{
		//Verifica e incremento contatori
		Syn_1_CNC_MC (0, (unsigned short) M351);  
		Syn_1_CNC_MC (1, (unsigned short) M_CH1_351);  
		Syn_1_CNC_MC (2, (unsigned short) M_CH2_351);  

		//Sblocco del CNC
		if (Syn_1_Done [0]) M351 = 0;
		if (Syn_1_Done [1]) M_CH1_351 = 0;
		if (Syn_1_Done [2]) M_CH2_351 = 0;

		Syn_1_MReq_old [0] = M351;
		Syn_1_MReq_old [1] = M_CH1_351;
		Syn_1_MReq_old [2] = M_CH2_351;

		//Al secondo giro esegue sempre il controllo per tutti i CNC
		for (i=0; i<SynNChannel; i++) Syn_1_Execute[i] = 1;

		unlock = (Syn_1_Done [0] && !Syn_1_Done_old [0]) ||
			(Syn_1_Done [1] && !Syn_1_Done_old [1]) ||
			(Syn_1_Done [2] && !Syn_1_Done_old [2]);
		
		//Se almeno un canale si è sbloccato
		if (unlock || !cont_loop)
			doLoop = 1;
		else 
			doLoop = 0;

		cont_loop++;

		for (i=0; i<SynNChannel; i++) Syn_1_Done_old [i] = Syn_1_Done [i]; 

	}
	while (doLoop);

	SYN_1_0_0 = (short int) Syn_1_Cont_Arr [0][0];
	SYN_1_0_1 = (short int) Syn_1_Cont_Arr [0][1];
	SYN_1_0_2 = (short int) Syn_1_Cont_Arr [0][2];

	SYN_1_1_0 = (short int) Syn_1_Cont_Arr [1][0];
	SYN_1_1_1 = (short int) Syn_1_Cont_Arr [1][1];
	SYN_1_1_2 = (short int) Syn_1_Cont_Arr [1][2];

	SYN_1_2_0 = (short int) Syn_1_Cont_Arr [2][0];
	SYN_1_2_1 = (short int) Syn_1_Cont_Arr [2][1];
	SYN_1_2_2 = (short int) Syn_1_Cont_Arr [2][2];

	SYN_1_3_0 = (short int) Syn_1_Cont_Arr [3][0];
	SYN_1_3_1 = (short int) Syn_1_Cont_Arr [3][1];
	SYN_1_3_2 = (short int) Syn_1_Cont_Arr [3][2];

	//Reset sincronismo livello 0
	if (Syn_1_Done [0] &&  Syn_1_Done [1] && Syn_1_Done [2]) Syn_0_MC_RESET_1_all ();

}


void Syn_1_CNC_MC(int myChannel, unsigned short MReq)
{
	int flag = 1;
	int ok = 1;
	int doSync = 0;

	int i = 0;
	int j = 0;

	Syn_1_Busy [myChannel] = MReq;

	if (!MReq) return;

	//Se arriva una nuova richiesta di sincronizzazione
	if (MReq && !Syn_1_MReq_old [myChannel])
	{
		Syn_1_Done [myChannel] = 0;
		for (i=0; i<SynNChannel; i++)
			//Incrementa di uno i contatori dei CNC di myChannel
			Syn_1_Cont_Arr[myChannel][i] = (Syn_1_Cont_Arr[i][i]+1) % Syn_MOD_count;
	}

	//Se non è richiesto il controllo per la condizione di avvenuta sincronizzazione esce
	if (!Syn_1_Execute [myChannel]) return;

	ok = 1;
	flag = 1;

	for (i=0; (i<SynNChannel) && ok; i++)
	{
		//Flag che indica se il canale myChannel si deve sincronizzare con il canale i-esimo
		doSync = Syn_1_Filt_Arr[myChannel] & flag;		
		if ((i != myChannel) && (doSync))		
		{
			//Se il contatore di myChannel è diverso dal contatore del canale i-esimo allora rimane bloccato
			if (Syn_1_Cont_Arr[myChannel][i] != Syn_1_Cont_Arr[i][i]) 
				ok = 0;	
		}
		flag = flag << 1;
	}

	//Se è verificata la condizione di sblocco del canale myChannel
	if (ok)
	{
		//Sblocco eseguito
		Syn_1_Done [myChannel] = 1;
		//Se è appena stato eseguito lo sblocco 
		if (Syn_1_Done [myChannel] && (!Syn_1_Done_old [myChannel]))
		{
			//incremento il contatore di myChannel
			Syn_1_Cont_Arr[myChannel][myChannel] = (Syn_1_Cont_Arr[myChannel][myChannel] + 1) % Syn_MOD_count;
			for (i=0; i<SynNChannel; i++)
				//setto i contatori degli altri canali come il contatore del canale myChannel che ho appena incrementato 
				Syn_1_Cont_Arr[myChannel][i] = Syn_1_Cont_Arr[myChannel][myChannel];
		}
	}
}


