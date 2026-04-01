//----------------------------------------------------------------------------
// TITOLO      : eventi_industria_4_0.c
// DESCRIZIONE : Collegamento macchina a rete di fornitura - Industria 4.0
// AUTORI      : Formuso Daniele
//----------------------------------------------------------------------------
#include "all.inc"

extern double tauPLC;

void gestione_eventi_standard(unsigned long Num_evento)
{
		// Definizione Evento_GENERICO: condizione che scatena l'emissione dell'evento (da PLC --> DRILL)
		if(EVENTO_ASSOCIATO_GENERICO && !ACK_EVENTO_GENERICO_EMESSO && !INIBIZIONE_EVENTO_GENERICO)  
		{
			if(Num_evento <= 20)                              VAR1_EVENTI_DWORD = (VAR1_EVENTI_DWORD | (1<<((Num_evento)-1))    );
			else if((Num_evento > 20) && (Num_evento <= 40))  VAR2_EVENTI_DWORD = (VAR2_EVENTI_DWORD | (1<<((Num_evento%20)-1)) );
			else if((Num_evento > 40) && (Num_evento <= 60))  VAR3_EVENTI_DWORD = (VAR3_EVENTI_DWORD | (1<<((Num_evento%40)-1)) );
			else if((Num_evento > 60) && (Num_evento <= 80))  VAR4_EVENTI_DWORD = (VAR4_EVENTI_DWORD | (1<<((Num_evento%60)-1)) );
			else if((Num_evento > 80) && (Num_evento <= 100)) VAR5_EVENTI_DWORD = (VAR5_EVENTI_DWORD | (1<<((Num_evento%80)-1)) );
		}
		
		// Acknoledge Evento_GENERICO: livello serbatoio1 lubrica basso (da DRILL --> PLC)
		if(ACK_EVENTO_GENERICO_EMESSO || APP_ORE_INIBIZ_EV_GENERICO)
			INIBIZIONE_EVENTO_GENERICO = 1;
		
		
		// Set Timer per mascherare Evento_GENERICO
		DN_ACK_EV_GENERICO_EMESSO = 0;
		if(!ACK_EVENTO_GENERICO_EMESSO && OLD_ACK_EV_GENERICO_EMESSO)
			DN_ACK_EV_GENERICO_EMESSO = 1;
		OLD_ACK_EV_GENERICO_EMESSO = ACK_EVENTO_GENERICO_EMESSO;

		if(DN_ACK_EV_GENERICO_EMESSO || APP_ORE_INIBIZ_EV_GENERICO) 
			ATTIVA_TIMER_EV_GENERICO = 1;

		// Conteggio ore inibizione Evento_GENERICO
		if(ATTIVA_TIMER_EV_GENERICO)
			APP_ORE_INIBIZ_EV_GENERICO = APP_ORE_INIBIZ_EV_GENERICO + (float) ( tauPLC / 60000 / 60);  //ore

		if(APP_ORE_INIBIZ_EV_GENERICO >= CONFMAC_ORE_INIBIZ_EV_GENERICO) //CONFMAC_ORE_INIBIZ_EV_GENERICO è un'area A a float in CONFMAC
		{
			ATTIVA_TIMER_EV_GENERICO = 0;
			APP_ORE_INIBIZ_EV_GENERICO = 0;
			INIBIZIONE_EVENTO_GENERICO = 0;
		}
}
		