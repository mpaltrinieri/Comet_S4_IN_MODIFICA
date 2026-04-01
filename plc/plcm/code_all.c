
/*
        --------------------------------------------------------------
        TITOLO:         code_all.c
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Creazione codice allarmi e messaggi presenti
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void code_all(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          START_WORD_ALL     = indirizzo prima word di allarmi (es )
        				NUM_WORD_ALL       = numero word di allarmi
						NUM_WORD_MSG       = indirizzo prima word di messaggi
						START_WORD_MSG     = numero word di messaggi
        
        				NUM_R_ALL          = numero di variabili R di appoggio degli allarmi (es 10)
						NUM_R_MES          = numero di variabili R di appoggio dei messaggi (es 4)
						ELIMINA_TUTTI_ALL  = flag per presenza di operatore esperto
						AL_PRIMO_ALLARME   = valore numerico del primo allarme (es 19600)
						MS_PRIMO_MESSAGGIO = valore numerico del primo messaggio (es 22000)

						START_WORD_ALL - START_WORD_ALL + NUM_WORD_ALL = flag allarmi
						START_WORD_MSG - START_WORD_MSG + NUM_WORD_MSG = flag messaggi
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         R[R_ALL_0] - R[R_ALL_0+NUM_R_ALL-1]  Codice allarme da visualiz.
                        R[R_MES_0] - R[R_MES_0+NUM_R_MES-1]  Codice messaggio da visualiz.
                        ALLARMI_PRES    Allarmi macchina presenti
                        MESSAGGI_PRES   Messaggi macchina presenti
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        001.000
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           08.2004
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Medici Stefano
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

#define NUM_R_ALL       ((ALARM_LAST_R)-(ALARM_FIRST_R)+1)
#define NUM_R_MES       ((MESSAGE_LAST_R)-(MESSAGE_FIRST_R)+1)
#define NUM_WORD_ALL    (&(ALARM_LAST_WORD)-&(ALARM_FIRST_WORD)+1)
#define NUM_WORD_MSG    (&(MESSAGE_LAST_WORD)-&(MESSAGE_FIRST_WORD)+1)

#define NUM_R_ALL_OPCUA ((ALARM_OPCUA_LAST_R)-(ALARM_OPCUA_FIRST_R)+1)

int nTIMEOUT;

//ATTENZIONE SE SI AUMENTANO I MESSAGGI OCCORRE AGGIORNARE LA DIMENSIONE DI QUESTO VETTORE
int cont_msgList[16*11]; //16*NUM_WORD_MSG


void all_scroll(void);
////void all_scroll_eth(int nNodo, int start);
void msg_scroll(void);
////void msg_scroll_eth(int nNodo, int start);

void     code_all(void)
{
	int iRAll     = 0;
	int iRMsg     = 0;
	int i         = 0;
	int iRAll_OPCUA = 0;

	if (PON) 
	{
		nTIMEOUT = ncicplc ((float)(R[R_TIMEOUT_MSG]/1000.0));
	}

	// Resetta la lista degli allarmi presenti
	ALLARMI_PRES = 0;     
	for (iRAll=0; iRAll<NUM_R_ALL; iRAll++) R[R_ALL_0+iRAll] = (float)0;

	if(RESET_ALL || RESET_MC)
	{
		for (iRAll_OPCUA=0; iRAll_OPCUA<NUM_R_ALL_OPCUA; iRAll_OPCUA++) R[R_ALL_OPCUA_0+iRAll_OPCUA] = (float)0;
	}

	//Genera gli allarmi e aggiorna la lista sulle variabili R
	all_scroll();

	// Resetta la lista dei messaggi presenti
	MESSAGGI_PRES = 0;
	for (iRMsg=0; iRMsg<NUM_R_MES; iRMsg++) R[R_MES_0+iRMsg] = (float)0;

	//Genera i messaggi e aggiorna la lista sulle variabili R
	msg_scroll();

	//Eliminazione allarmi da parte dell'operatore esperto
	if (ELIMINA_TUTTI_ALL) ALLARMI_PRES = 0;	

	// Condizione di solo messaggi presenti per lampeggio
	// Alcuni messaggio non sono da segnalare perchè evidenti e ripetitivi
	SOLO_MESS_PRESENTI = MESSAGGI_PRES && !ALLARMI_PRES && !ASSI_NORIF_FMS;

	// Dopo x secondi lampeggia con fronte per segnalare il messaggio e richiamare l'attenzione 
	if (RP_TSuppl[TS_SOLO_MESS_PRESENTI])
		LAMP_PER_MESS = 1; 

	if (RP_LAMP_PER_MESS || RESET_MC || MANO)
		LAMP_PER_MESS = 0; 
}


void all_scroll(void)
{
	int iAAll     = 0;
	int contaAll  = 0;
	unsigned short *pValAll;
	unsigned short ALLARME_PRES_IN_OPCUA;
	
	pValAll = &ALARM_FIRST_WORD;
	// Spazzola tutte le word dei flag allarmi
	for (iAAll=0; iAAll<NUM_WORD_ALL; iAAll++, pValAll++)
	{
		// Se è presente un allarme nella word
		if (*pValAll)
		{
			// Spazzola tutti i bit della word dei flag allarmi
			int iBitAAll;
			unsigned short wAll = *pValAll;
			for (iBitAAll=0; iBitAAll<16; iBitAAll++, wAll >>= 1)
			{
				// Se è presente un allarme
				if (wAll & 1)
				{
					unsigned short allarmeAttuale = contaAll;
					int i = 0;
					int j = 0;
					
					// Setta il flag allarmi presenti
					ALLARMI_PRES = 1;
					
					// Accoda l'allarme nel buffer
					// Copia e shifta gli allarmi
					for (i=NUM_R_ALL-1;i;i--) R[R_ALL_0+i]=R[R_ALL_0+i-1];
					R[R_ALL_0] = (float)allarmeAttuale;

					// ************************************************
					// Accoda l'allarme nel buffer per il client OPCUA
					// Copia e shifta gli allarmi
					// ************************************************

					ALLARME_PRES_IN_OPCUA = 0;

					for (j=0;j<NUM_R_ALL_OPCUA;j++)
					{
						if( (R[R_ALL_OPCUA_0+j] == (float)allarmeAttuale) )
						{
							ALLARME_PRES_IN_OPCUA = 1;
							break;
						}
					}

					if(!ALLARME_PRES_IN_OPCUA)
					{
						for (j=0;j<NUM_R_ALL_OPCUA;j++)
						{
							if( (R[R_ALL_OPCUA_0+j] < 0.5) )
							{
								R[R_ALL_OPCUA_0+j] = (float)allarmeAttuale;
								break;
							}
						}
					}
					// ************************************************
					// ************************************************

					//Genera l'allarme
					allarm (allarmeAttuale + ALARM_FIRST_AL);
				}
				contaAll++;
			}
		}
		else contaAll += 16;
	}
}

void msg_scroll(void)
{
	int iAMsg     = 0;
	int contaMsg  = 0;
	unsigned short *pValMsg;
	
	pValMsg = &MESSAGE_FIRST_WORD;
	
	for (iAMsg=0; iAMsg<NUM_WORD_MSG; iAMsg++, pValMsg++)
	{		
		if (*pValMsg)
		{
			int iBitAMsg;
			unsigned short wMsg = *pValMsg;
			for (iBitAMsg=0; iBitAMsg<16; iBitAMsg++, wMsg >>= 1)
			{
				if (wMsg & 1)
				{
					unsigned short messaggioAttuale = contaMsg;
					int i = 0;
					
					MESSAGGI_PRES = 1;
					
					if(cont_msgList[contaMsg] > nTIMEOUT)
					{
						// Accoda il messaggio nel buffer
						for (i=NUM_R_MES-1;i;i--) R[R_MES_0+i]=R[R_MES_0+i-1];
						R[R_MES_0] = (float)messaggioAttuale;

						attenz (messaggioAttuale + MESSAGE_FIRST_MS);
					}
					else
					{
						cont_msgList[contaMsg]++;
					}
				}
				contaMsg++;			
			}
		}
		else 
		{
			int i = 0;
			for (i=0; i<16;++i)
			{
				cont_msgList[contaMsg+i] = 0;
			}
			contaMsg += 16;
		}
	}
}

////////void all_scroll_eth(int nNodo, int start)
////////{
////////	int iAAll     = 0;
////////	int contaAll  = 0;
////////	int ip        = 0;
////////	unsigned short valAll = 0;
////////	
////////	ip = start;
////////	
////////	// Spazzola tutte le word dei flag allarmi
////////	for (iAAll=0; iAAll<NUM_WORD_ALL; iAAll++, ip++)
////////	{
////////		valAll = PLC_ETHERNET_DATA_WORD(nNodo, ip);
////////		
////////		// Se è presente un allarme nella word
////////		if (valAll)
////////		{
////////			// Spazzola tutti i bit della word dei flag allarmi
////////			int iBitAAll;
////////			unsigned short wAll = valAll;
////////			for (iBitAAll=0; iBitAAll<16; iBitAAll++, wAll >>= 1)
////////			{
////////				// Se è presente un allarme
////////				if (wAll & 1)
////////				{
////////					unsigned short allarmeAttuale = contaAll;
////////					int present = 0;
////////					int iAl=0;
////////					
////////					// Setta il flag allarmi presenti
////////					ALLARMI_PRES = 1;       
////////					
////////					for (iAl=0;iAl<NUM_R_ALL;iAl++) 
////////						if(R[R_ALL_0+iAl] == ((float)allarmeAttuale)) 
////////						{
////////							present = 1;
////////							break;
////////						}
////////						
////////					//Se l'allarme non è già presente nella lista
////////					if (!present)
////////						{
////////							int i = 0;
////////							
////////							// Accoda l'allarme nel buffer
////////							for (i=NUM_R_ALL-1;i;i--) R[R_ALL_0+i]=R[R_ALL_0+i-1];
////////							R[R_ALL_0] = (float)allarmeAttuale;
////////							
////////							//Genera l'allarme
////////							allarm ((unsigned short)(allarmeAttuale + ALARM_FIRST_AL));
////////						}
////////				}
////////				contaAll++;
////////			}
////////		}
////////		else contaAll += 16;
////////	}
////////}
////////
////////void msg_scroll_eth(int nNodo, int start)
////////{
////////	int iAMsg     = 0;
////////	int contaMsg  = 0;
////////	int ip        = 0;
////////	unsigned short valMsg = 0;
////////	
////////	ip = start;
////////	
////////	for (iAMsg=0; iAMsg<NUM_WORD_MSG; iAMsg++, ip++)
////////	{		
////////		valMsg = PLC_ETHERNET_DATA_WORD(nNodo, ip);
////////		
////////		if (valMsg)
////////		{
////////			int iBitAMsg;
////////			unsigned short wMsg = valMsg;
////////			for (iBitAMsg=0; iBitAMsg<16; iBitAMsg++, wMsg >>= 1)
////////			{
////////				if (wMsg & 1)
////////				{
////////					unsigned short messaggioAttuale = contaMsg;
////////					int present = 0;
////////					int iMs=0;
////////					
////////					MESSAGGI_PRES = 1;
////////					
////////					for (iMs=0;iMs<NUM_R_MES;iMs++) 
////////						if(R[R_MES_0+iMs] == ((float)messaggioAttuale)) 
////////						{
////////							present = 1;
////////							break;
////////						}
////////						
////////					//Se il messaggio non è già presente nella lista
////////					if (!present)
////////						{					
////////							int i = 0;
////////					
////////							// Accoda il messaggio nel buffer
////////							for (i=NUM_R_MES-1;i;i--) R[R_MES_0+i]=R[R_MES_0+i-1];
////////							R[R_MES_0] = (float)messaggioAttuale;
////////
////////							attenz ((unsigned short) (messaggioAttuale +  MESSAGE_FIRST_MS));
////////						}
////////				}
////////				contaMsg++;			
////////			}
////////		}
////////		else contaMsg += 16;
////////	}
////////}
