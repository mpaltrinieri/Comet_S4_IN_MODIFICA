/*
        --------------------------------------------------------------
        TITOLO:         Modulo sicurezza    
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione Modulo sicurezza
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void modulo_sicurezza (void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CS4 0.000
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           21-11-2022
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Borsari Guido
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include "all.inc"

void modulo_sicurezza(void)
{

// INIZIO DIAGNOSTICA1 PIZZATO ////////////////////////////////////////////////////////////////////
if ( (R[R_TIPO_MODULO_SIC]>0.5) && (R[R_TIPO_MODULO_SIC]<1.5) )
{
	// PIZZATO_CLOCK_I           MI_2_69 Diagnostica Pizzato - Segnale "clock"
	// PIZZATO_SERIAL_I          MI_2_70 Diagnostica Pizzato - Segnale "serial"
	
	// Esecuzione: Il plc conta quante volte va a 1 il segnale "serial" (mentre il segnale clock è a 1) in un periodo di 100(?) eventi di clock.
	// Condizione: Affinche il plc veda sicuramente le variazioni dei segnali clock e serial, questi dovrebbero restare a 1 per un tempo > 10ms, e restare a 0 per un tempo > 10ms.

	// info necessarie:
	// 1)	Durata in ms della permanenza a 1 e a 0 dei segnali clock e serial: ?        
	// 2)	Numero di transizioni positive del segnale clock in ogni periodo da considerare = ?
	// 3)	Numero massimo di transizioni positive del segnale serial in ogni periodo da considerare = ?
	// 4)	Elenco allarmi da visualizzare?

	if (RESET_ALL || RESET_MC)
		{
		MEM_PIZZATO_CLOCK = 0;
		ABIL_VERIF_SERIAL = 0;
		MEM_ABIL_VERIF_SERIAL = 0;
		
		CONT_PIZZATO_CLOCK = 0;
		CONT_PIZZATO_SERIAL = 0;
		ALLARME_MOD_SIC = 0;
		// = 0;
		  MOD_SIC_ALL_01_FAL = 0;
		//MOD_SIC_ALL_02_FAL = 0;
		//MOD_SIC_ALL_03_FAL = 0;
		//MOD_SIC_ALL_04_FAL = 0;
		//MOD_SIC_ALL_05_FAL = 0;
		//MOD_SIC_ALL_06_FAL = 0;
		//MOD_SIC_ALL_07_FAL = 0;
		//MOD_SIC_ALL_08_FAL = 0;
		//MOD_SIC_ALL_09_FAL = 0;
		//MOD_SIC_ALL_10_FAL = 0;
		}

	// transiz pos. del segnale clock => abilita verifica segnale serial (se contemporaneo al segnale clock)
	if (PIZZATO_CLOCK_I && !MEM_PIZZATO_CLOCK) ABIL_VERIF_SERIAL = 1;
	if (!PIZZATO_CLOCK_I)                      ABIL_VERIF_SERIAL = 0;
	MEM_PIZZATO_CLOCK = PIZZATO_CLOCK_I;
	
	// conteggio eventi segnale clock
	if (ABIL_VERIF_SERIAL && !MEM_ABIL_VERIF_SERIAL) { CONT_PIZZATO_CLOCK++; }
	MEM_ABIL_VERIF_SERIAL = ABIL_VERIF_SERIAL;
	
	// conteggio eventi segnale serial
	if (ABIL_VERIF_SERIAL && PIZZATO_SERIAL_I) { ABIL_VERIF_SERIAL = 0;  CONT_PIZZATO_SERIAL++; }

	// fine eventuale conteggio eventi segnale serial e set flag allarme
	if (CONT_PIZZATO_CLOCK > 100) 
	{
		ALLARME_MOD_SIC = CONT_PIZZATO_SERIAL;
		CONT_PIZZATO_SERIAL =    0;
		CONT_PIZZATO_CLOCK = 0;
	}

	   if (ALLARME_MOD_SIC== 1) MOD_SIC_ALL_01_FAL = 1;
	// if (ALLARME_MOD_SIC== 2) MOD_SIC_ALL_02_FAL = 1;
	// if (ALLARME_MOD_SIC== 3) MOD_SIC_ALL_03_FAL = 1;
	// if (ALLARME_MOD_SIC== 4) MOD_SIC_ALL_04_FAL = 1;
	// if (ALLARME_MOD_SIC== 5) MOD_SIC_ALL_05_FAL = 1;
	// if (ALLARME_MOD_SIC== 6) MOD_SIC_ALL_06_FAL = 1;
	// if (ALLARME_MOD_SIC== 7) MOD_SIC_ALL_07_FAL = 1;
	// if (ALLARME_MOD_SIC== 8) MOD_SIC_ALL_08_FAL = 1;
	// if (ALLARME_MOD_SIC== 9) MOD_SIC_ALL_09_FAL = 1;
	// if (ALLARME_MOD_SIC==10) MOD_SIC_ALL_10_FAL = 1;

}
// FINE DIAGNOSTICA1 PLC-PIZZATO //////////////////////////////////////////////////////////////////



// INIZIO DIAGNOSTICA2 PIZZATO ////////////////////////////////////////////////////////////////////
if ( (R[R_TIPO_MODULO_SIC]>1.5) && (R[R_TIPO_MODULO_SIC]<2.5) )
{
	// PIZZATO_CLOCK_I           MI_2_70 Diagnostica Pizzato - Segnale "clock"
	// PIZZATO_SERIAL_I          MI_2_71 Diagnostica Pizzato - Segnale "serial"
	
	// Esecuzione: Il plc conta quante volte va a 1 il segnale "serial" (dopo che il segnale clock è andato a 1 e tornato a 0) .
	// Condizione: Affinche il plc veda sicuramente le variazioni dei segnali clock e serial, questi dovrebbero restare a 1 per un tempo > 10ms, e restare a 0 per un tempo > 10ms.

	// info necessarie:
	// 1)	Durata in ms della permanenza a 1 e a 0 dei segnali clock e serial: ?        
	// 2)	Numero di transizioni positive del segnale clock in ogni periodo da considerare = 1 ?
	// 3)	Numero massimo di transizioni positive del segnale serial in ogni periodo da considerare = ?
	// 4)	Elenco allarmi da visualizzare?

	if (RESET_ALL || RESET_MC)
		{
		MEM_PIZZATO_CLOCK = 0;
		ABIL_VERIF_SERIAL = 0;
		MEM_ABIL_VERIF_SERIAL = 0;
		ABIL_VERIF_SERIAL_RP = 0;
		MEM_PIZZATO_SERIAL = 0;
		CONT_PIZZATO_SERIAL = 0;
		ALLARME_MOD_SIC = 0;
		// = 0;
		  MOD_SIC_ALL_01_FAL = 0;
		//MOD_SIC_ALL_02_FAL = 0;
		//MOD_SIC_ALL_03_FAL = 0;
		//MOD_SIC_ALL_04_FAL = 0;
		//MOD_SIC_ALL_05_FAL = 0;
		//MOD_SIC_ALL_06_FAL = 0;
		//MOD_SIC_ALL_07_FAL = 0;
		//MOD_SIC_ALL_08_FAL = 0;
		//MOD_SIC_ALL_09_FAL = 0;
		//MOD_SIC_ALL_10_FAL = 0;
		}
	
	// transiz neg. del clock => abilita conteggio eventi di PIZZATO_SERIAL_I
	if (!(PIZZATO_CLOCK_I) && MEM_PIZZATO_CLOCK)   ABIL_VERIF_SERIAL = 1;                
	MEM_PIZZATO_CLOCK = PIZZATO_CLOCK_I;

	// timer durata abilitaz. conteggio eventi
	tS(TS_ABIL_VERIF_SERIAL, (unsigned char) ABIL_VERIF_SERIAL);                         
	ABIL_VERIF_SERIAL_RP = ABIL_VERIF_SERIAL && (RP_TSuppl[TS_ABIL_VERIF_SERIAL]);

	// transiz pos. del clock o dopo un certo ritardo => disabilita conteggio eventi di PIZZATO_SERIAL_I
	if (PIZZATO_CLOCK_I || ABIL_VERIF_SERIAL_RP)   ABIL_VERIF_SERIAL = 0;                

	// conteggio eventi segnale serial dopo un clock
	if (ABIL_VERIF_SERIAL && PIZZATO_SERIAL_I && !MEM_PIZZATO_SERIAL) { CONT_PIZZATO_SERIAL++; }   
	MEM_PIZZATO_SERIAL = PIZZATO_SERIAL_I;

	// fine eventuale conteggio eventi segnale serial e set flag allarme
	if (!ABIL_VERIF_SERIAL)
	{
		if(MEM_ABIL_VERIF_SERIAL) ALLARME_MOD_SIC = CONT_PIZZATO_SERIAL;                 // memorizzaz. allarme conteggiato 
		CONT_PIZZATO_SERIAL = 0;                                                         // reset contatore eventi "serial"
	}
	
	MEM_ABIL_VERIF_SERIAL = ABIL_VERIF_SERIAL;
	
	// visualizzazione allarmi Pizzato
	   if (ALLARME_MOD_SIC== 1) MOD_SIC_ALL_01_FAL = 1;
	// if (ALLARME_MOD_SIC== 2) MOD_SIC_ALL_02_FAL = 1;
	// if (ALLARME_MOD_SIC== 3) MOD_SIC_ALL_03_FAL = 1;
	// if (ALLARME_MOD_SIC== 4) MOD_SIC_ALL_04_FAL = 1;
	// if (ALLARME_MOD_SIC== 5) MOD_SIC_ALL_05_FAL = 1;
	// if (ALLARME_MOD_SIC== 6) MOD_SIC_ALL_06_FAL = 1;
	// if (ALLARME_MOD_SIC== 7) MOD_SIC_ALL_07_FAL = 1;
	// if (ALLARME_MOD_SIC== 8) MOD_SIC_ALL_08_FAL = 1;
	// if (ALLARME_MOD_SIC== 9) MOD_SIC_ALL_09_FAL = 1;
	// if (ALLARME_MOD_SIC==10) MOD_SIC_ALL_10_FAL = 1;

}
// FINE DIAGNOSTICA2 PLC-PIZZATO //////////////////////////////////////////////////////////////////


}
