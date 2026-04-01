//----------------------------------------------------------------------------
// TITOLO      : eventi_industria_4_0.c
// DESCRIZIONE : Collegamento macchina a rete di fornitura - Industria 4.0
// AUTORI      : Formuso Daniele
//----------------------------------------------------------------------------
#include "all.inc"


void eventi_industria_4_0()
{
	if(R[R_ENABLE_EVENTI_IND_4_0])
	{
		if(PON)
		{
			APP_ORE_INIBIZ_EV_01 = M_ORE_INIBIZ_EV_01;
			APP_ORE_INIBIZ_EV_02 = M_ORE_INIBIZ_EV_02;
		}

		// Appoggio variabili R eventi
		VAR1_EVENTI_DWORD = (unsigned long) R[R_VAR_EVENTI_01];
		VAR2_EVENTI_DWORD = (unsigned long) R[R_VAR_EVENTI_02];
		VAR3_EVENTI_DWORD = (unsigned long) R[R_VAR_EVENTI_03];
		VAR4_EVENTI_DWORD = (unsigned long) R[R_VAR_EVENTI_04];
		VAR5_EVENTI_DWORD = (unsigned long) R[R_VAR_EVENTI_05];
		
		// Appoggio variabili R accknoledge eventi
		VAR1_ACK_EVENTI_DWORD = (unsigned long) R[R_VAR_ACK_01];
		VAR2_ACK_EVENTI_DWORD = (unsigned long) R[R_VAR_ACK_02];
		VAR3_ACK_EVENTI_DWORD = (unsigned long) R[R_VAR_ACK_03];
		VAR4_ACK_EVENTI_DWORD = (unsigned long) R[R_VAR_ACK_04];
		VAR5_ACK_EVENTI_DWORD = (unsigned long) R[R_VAR_ACK_05];

		//**************************************************************************
		//PASSAGGIO PARAMETRI EVENTO_01 in input alla funzione generica di gestione:
		// Evento_01: livello serbatoio1 lubrica basso
		//**************************************************************************
		NUM_EVENTO_GENERICO = 1;
		
		EVENTO_ASSOCIATO_01 = RP_PON && LIV_LUB_NOT_BASSO_FAL && (CONFMAC_ORE_INIBIZ_EV_01 > 0.0);  // livello serbatoio1 lubrica basso
		EVENTO_ASSOCIATO_GENERICO =  EVENTO_ASSOCIATO_01;

		ACK_EVENTO_GENERICO_EMESSO = ACK_EVENTO_01_EMESSO;
		INIBIZIONE_EVENTO_GENERICO = INIBIZIONE_EVENTO_01;
		DN_ACK_EV_GENERICO_EMESSO = DN_ACK_EV_01_EMESSO;
		OLD_ACK_EV_GENERICO_EMESSO = OLD_ACK_EV_01_EMESSO;
		ATTIVA_TIMER_EV_GENERICO = ATTIVA_TIMER_EV_01;

		APP_ORE_INIBIZ_EV_GENERICO = APP_ORE_INIBIZ_EV_01;
		CONFMAC_ORE_INIBIZ_EV_GENERICO = CONFMAC_ORE_INIBIZ_EV_01;
		
		gestione_eventi_standard(NUM_EVENTO_GENERICO);
		
		ACK_EVENTO_01_EMESSO = ACK_EVENTO_GENERICO_EMESSO;
		INIBIZIONE_EVENTO_01 = INIBIZIONE_EVENTO_GENERICO;
		DN_ACK_EV_01_EMESSO = DN_ACK_EV_GENERICO_EMESSO;
		OLD_ACK_EV_01_EMESSO = OLD_ACK_EV_GENERICO_EMESSO;
		ATTIVA_TIMER_EV_01 = ATTIVA_TIMER_EV_GENERICO;

		APP_ORE_INIBIZ_EV_01 = APP_ORE_INIBIZ_EV_GENERICO;
		
		//**************************************************************************
		//PASSAGGIO PARAMETRI EVENTO_02 in input alla funzione generica di gestione:
		// Evento_02: livello serbatoio2 lubrica basso
		//**************************************************************************
		NUM_EVENTO_GENERICO = 2;

		EVENTO_ASSOCIATO_02 = FALSE && (CONFMAC_ORE_INIBIZ_EV_02 > 0.0);  // livello serbatoio2 lubrica basso
		EVENTO_ASSOCIATO_GENERICO =  EVENTO_ASSOCIATO_02;

		ACK_EVENTO_GENERICO_EMESSO = ACK_EVENTO_02_EMESSO;
		INIBIZIONE_EVENTO_GENERICO = INIBIZIONE_EVENTO_02;
		DN_ACK_EV_GENERICO_EMESSO = DN_ACK_EV_02_EMESSO;
		OLD_ACK_EV_GENERICO_EMESSO = OLD_ACK_EV_02_EMESSO;
		ATTIVA_TIMER_EV_GENERICO = ATTIVA_TIMER_EV_02;

		APP_ORE_INIBIZ_EV_GENERICO = APP_ORE_INIBIZ_EV_02;
		CONFMAC_ORE_INIBIZ_EV_GENERICO = CONFMAC_ORE_INIBIZ_EV_02;
		
		gestione_eventi_standard(NUM_EVENTO_GENERICO);
		
		ACK_EVENTO_02_EMESSO = ACK_EVENTO_GENERICO_EMESSO;
		INIBIZIONE_EVENTO_02 = INIBIZIONE_EVENTO_GENERICO;
		DN_ACK_EV_02_EMESSO = DN_ACK_EV_GENERICO_EMESSO;
		OLD_ACK_EV_02_EMESSO = OLD_ACK_EV_GENERICO_EMESSO;
		ATTIVA_TIMER_EV_02 = ATTIVA_TIMER_EV_GENERICO;

		APP_ORE_INIBIZ_EV_02 = APP_ORE_INIBIZ_EV_GENERICO;		
		


		//*****************************************************
		// AGGIORNAMENTO VARIABILI: al termine della funzione
		//*****************************************************
		// Aggiornamento aree retentive per inibizione eventi
		M_ORE_INIBIZ_EV_01 = APP_ORE_INIBIZ_EV_01;
		M_ORE_INIBIZ_EV_02 = APP_ORE_INIBIZ_EV_02;

		// Reset eventi su acknoledge del Drill
		VAR1_EVENTI_DWORD = (VAR1_EVENTI_DWORD & (~VAR1_ACK_EVENTI_DWORD) );  // Operatore AND bit a bit con il complemento a 1 del secondo
		VAR2_EVENTI_DWORD = (VAR2_EVENTI_DWORD & (~VAR2_ACK_EVENTI_DWORD) );  // Operatore AND bit a bit con il complemento a 1 del secondo
		VAR3_EVENTI_DWORD = (VAR3_EVENTI_DWORD & (~VAR3_ACK_EVENTI_DWORD) );  // Operatore AND bit a bit con il complemento a 1 del secondo
		VAR4_EVENTI_DWORD = (VAR4_EVENTI_DWORD & (~VAR4_ACK_EVENTI_DWORD) );  // Operatore AND bit a bit con il complemento a 1 del secondo
		VAR5_EVENTI_DWORD = (VAR5_EVENTI_DWORD & (~VAR5_ACK_EVENTI_DWORD) );  // Operatore AND bit a bit con il complemento a 1 del secondo

		// Aggiorna variabili R degli eventi
		R[R_VAR_EVENTI_01] = (double) VAR1_EVENTI_DWORD;
		R[R_VAR_EVENTI_02] = (double) VAR2_EVENTI_DWORD;
		R[R_VAR_EVENTI_03] = (double) VAR3_EVENTI_DWORD;
		R[R_VAR_EVENTI_04] = (double) VAR4_EVENTI_DWORD;
		R[R_VAR_EVENTI_05] = (double) VAR5_EVENTI_DWORD;
	}

}
		