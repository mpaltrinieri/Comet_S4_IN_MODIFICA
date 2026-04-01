/*

		--------------------------------------------------------------
        TITOLO:         FUNZ_M
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Creazione flags funzioni "M" emesse da CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    funz_m(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          NVM   : Strobe funzioni "M"
                        O_EXE : CNC in modo esecuzione
                        O_M   : Codice funzione "M" emessa da CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         M00
                        ..           : Flags funzioni "M" emesse :
                        ..             da "A7.bit._00" ad "A13.bit._15"
                        M249
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           30-08-2000
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:  Soffritti Riccardo
        --------------------------------------------------------------

*/

//Legenda:
//Get funz M, ritorna true se almeno una delle funzioni M dei canali è a true
//BOOL Mg_MC(int nFunzM)

//Get funz PLCM, ritorna true se almeno una delle funzioni PLCM dei canali è a true
//BOOL PLCMg_MC(int nFunzM)

//Reset funz M mette a 0 il flag della funzione M per tutti i canali
//void Mr_MC(int nFunzM)


#include        "all.inc"

void funz_m(void)

{

	const int wordSize = sizeof(M_FIRST_WORD);
	const int bufLen = (&M_LAST_WORD - &M_FIRST_WORD + 1);

	// Sincronizzazione con G318
	// Funzione utilizzabile lato CN uguale alle M, con sintassi G318=valore
	if (PSET_CH0 && O_EXE_CH0) 
	{
		switch (O_GN_CH0) 
		{
		case 46: // Errore posizione a riposo della battuta di precisione
			if (R[R_BATT_PRECISIONE]) 
				BATT_PREC_QUOTA0_FAL = 1;
			break;

		case 47: // Errore indice tastatura 
			if (R[R_BATT_PRECISIONE])
				INDICE_TAST_FAL = 1;
			break;

		case 54: // Pezzo posizionato male 
			if (R[R_BATT_PRECISIONE])
				POSIZIONE_PEZZO_FAL = 1;
			break;

		case 55: // Pezzo non trovato 
			if (R[R_BATT_PRECISIONE])
				PEZZO_NON_TROV_FAL = 1;
			break;
		}
	}


	// Reset indicizzato di tutti i flag delle funzioni "M" su reset CNC
	if (RESET_MC)
	{
		memset(&M_FIRST_WORD, 0, bufLen*wordSize);
		DRIVE_MISSING_FAL = 0;
	}


	/* Set dei flag delle funzioni "M" */
	if (DP_NVM_CH0 && O_EXE_CH0)
	{

		if (AUTO && !SIMULATORE_ON)
		{
			if (R[R_CK_START] == (float)0)
				DRIVE_MISSING_FAL = 1;
		}

		switch (O_M_CH0)
		{
		case 0:					// M00 - da usare per PAUSA CICLO in ISO
			M00 = 1;
			break;

		case 1:
			break;

		case 2:
			M02 = 1;                /* Fine programma */
			R[R_PROG_FINITO] = 1;	/* Copia su R per il Drill - la resetto in manuale fuori di quà */
			break;

		case 3:
			M03 = 1;                /* Rotazione oraria mandrino */
			break;

		case 4:
			M04 = 1;                /* Rotazione antioraria mandrino */
			break;

		case 5:
			M05 = 1;                /* Arresto rotazione mandrino */
			break;

		case 6:
			M06 = 1;                /* Cambio utensili */
			break;

		case 7:
			M07 = 1;                /* Refrigerante lubrica */
			break;

		case 8:
			break;

		case 9:
			M09 = 1;                /* Arresto refrigerante */
			break;

		case 10:
			M10 = 1;      // Verifica utensile in corso (xte: M 130)
			break;

		case 11:
			M11 = 1;      // Fine verifica utensile (xte: M 131)
			break;

		case 12:
			M12 = 1;      // Verifica dispositivo integrità utensile (xte: M 132)
			break;

		case 13:
			M13 = 1;      // Verifica integrità utensile (xte: M 133)
			break;

		case 14:
			M14 = 1;      // Abilita allarme utensile rotto (FATM) (xte: M 134)
			break;

		case 15:				// RISERVATA: Gamme
			break;

		case 16:
			break;

		case 17:
			break;

		case 18:
			M18 = 1;				// Riferimento assi CANOPEN attivo
			break;

		case 19:				// RISERVATA: ORIENTAM.MANDR.
			M19 = 1;
			break;

		case 20:
			M20 = 1;               // Verifica mandrino fuori ingombro magazzino
			break;

		case 21:
			M21 = 1;         // Rilievo dimensioni utensile in corso
			break;

		case 22:
			M22 = 1;         // Fine rilievo dimensioni utensile
			break;

		case 23:
			break;

		case 24:
			M24 = 1; // Inzio ciclo di tastatura con battuta di precisione
			break;

		case 25:
			M25 = 1; // Fine ciclo di tastatura con battuta di precisione
			break;

		case 26:
			M26 = 1; // Discesa, inserzione battuta di precisione
			break;

		case 27:
			M27 = 1; // Salita, disinserzione battuta di precisione
			break;

		case 28:		// INIZIO SET ASSI SLAVE
			Acus[380] = -1;
			break;

		case 29:		// FINE SET ASSI SLAVE
			if (FATM_CH0 /*&& !O_INIZ1*/)	Acus[380] = 0;
			break;

		case 30:
			break;

		case 31:		// RISERVATA: Partenza multiprocesso
			break;

		case 32:		// RISERVATA: Attesa fine multiprocesso
			break;

		case 33:		// RISERVATA: Set asse su slave1
			break;

		case 34:		// RISERVATA: Set asse su slave2
			break;

		case 35:		// RISERVATA: Set asse su slave3 (eventuale sviluppo futuro)
			break;

		case 36:		// RISERVATA: Set asse su slave4 (eventuale sviluppo futuro)
			break;

		case 37:
			break;

		case 38:
			break;

		case 39:
			break;


		case 40:		// RISERVATA: Gamma alta
			break;

		case 41:		// RISERVATA: Gamma alta
			break;

		case 42:		// RISERVATA: Gamma alta
			break;

		case 43:		// RISERVATA: Gamma alta
			break;

		case 44:		// RISERVATA: Gamma alta
			break;

		case 45:		// RISERVATA: Gamma alta
			break;

		case 46:				// scarico possibile zona SX
			PLCM91 = 1;				/* Avanzamento tavola in carico, avanti verso operatore */
			PLCM60 = 1;				/* Apertura riparo anteriore */
			PLCM310 = 1;			// Apertura (avanzamento) visiera bassa
			PLCM312 = 1;			// Apertura (discesa) visiera alta
			break;

		case 47:
			// occupata su CR6
			break;

		case 48:
			M48 = 1;                /* Attivazione potenziometri */
			break;

		case 49:
			M49 = 1;                /* Disattivazione potenziometri (100%) */
			break;

		case 50:
			M50 = 1;                /* Sbloccaggio utensile su mandrino */
			break;

		case 51:
			M51 = 1;                /* Bloccaggio utensile su mandrino */
			break;

		case 52:
			break;

		case 53:
			M53 = 1;                /* Rotazione mandrino per masc. rigida */
			break;

		case 54:
			M54 = 1;                // attesa Scaricamento ut. dal mandrino (abilitaz. sblocco ut. con mgpilot)
			break;

		case 55:				
			M55 = 1;                // attesa Caricamento ut. sul mandrino (abilitaz. sblocco ut. con mgpilot)
			break;

		case 56:				// Inserzione rilevatore morse
			M56 = 1;
			break;

		case 57:				// Disinsezione rilevatore morse
			M57 = 1;
			break;

		case 58:				// Discesa Riparo
			M60 = 1;				/* Apertura riparo anteriore */ 
			M310 = 1;				// Apertura (avanzamento) visiera bassa
			M312 = 1;				// Apertura (discesa) visiera alta
			break;

		case 59:				// Salita Riparo
			M61 = 1;				/* Chiusura riparo anteriore*/
			M311 = 1;				// Chiusura (arretramento) visiera bassa
			M313 = 1;				// Chiusura (salita) visiera alta
			break;

		case 60:
			M60 = 1;				/* Apertura riparo anteriore */
			M310 = 1;				// Apertura (avanzamento) visiera bassa
			M312 = 1;				// Apertura (discesa) visiera alta
			M61 = 0;				/* Reset Chiusura riparo anteriore  */
			PLCM61 = 0;				/* Reset Chiusura riparo anteriore */
			M311 = 0;				// Reset Chiusura (arretramento) visiera bassa
			M313 = 0;				// Reset Chiusura (salita) visiera alta
			PLCM311 = 0;			// Reset Chiusura (arretramento) visiera bassa
			PLCM313 = 0;			// Reset Chiusura (salita) visiera alta
			break;

		case 61:
			M61 = 1;				/* Chiusura riparo anteriore */
			M311 = 1;				// Chiusura (arretramento) visiera bassa
			M313 = 1;				// Chiusura (salita) visiera alta
			M60 = 0;				// Reset Apertura riparo anteriore
			M310 = 0;				// Reset Apertura (avanzamento) visiera bassa
			M312 = 0;				// Reset Apertura (discesa) visiera alta
			PLCM60 = 0;				// Reset Apertura riparo anteriore
			PLCM310 = 0;			// Reset Apertura (avanzamento) visiera bassa
			PLCM312 = 0;			// Reset Apertura (discesa) visiera alta
			break;

		case 62:
			// occupata su CR6
			break;

		case 63:
			// occupata su CR6
			break;

		case 64:
			M64 = 1;                /* Abilitazione totale assi per riferimento */
			break;

		case 65:
			M65 = 1;                /* Conferma assi riferiti */
			break;

		case 66:
			M66 = 1;                // Disabilita allarmi utensile
			break;

		case 67:
			M67 = 1;                // Abilita allarmi utensile
			break;

		case 68:
			break;

		case 69:
			M69 = 1;				// Reset Aree memoria Tastatura
			break;

		case 70:
			break;

		case 71:
			M71 = 1;                /* Ciclo rotazione mandrino in corso */
			break;

		case 72:
			M72 = 1;                /* Ciclo deposito utensile in corso */
			break;

		case 73:
			M73 = 1;                /* Ciclo deposito utensile eseguito */
			break;

		case 74:
			M74 = 1;                /* Ciclo prelievo utensile in corso */
			break;

		case 75:
			M75 = 1;                /* Ciclo prelievo utensile eseguito */
			break;

		case 76:
			M76 = 1;				/* Controllo possibilità deposito utensile */
			break;

		case 77:
			M77 = 1;				/* Controllo possibilità prelievo utensile */
			break;

		case 78:
			M78 = 1;				/* Carica i dati del cambio utensili in deposito */
			break;

		case 79:
			M79 = 1;				/* Carica i dati del cambio utensili in prelievo */
			break;

		case 80:
			M80 = 1;        /* Inizio ciclo di lavoro */
			break;

		case 81:
			M81 = 1;        /* Attesa macchina pronta al lavoro */
			break;

		case 82:
			break;

		case 83:
			M83 = 1;        /* Fine ciclo di lavoro */
			break;

		case 84:
			// occupata su CR6
			break;

		case 85:
			M85 = 1;        /* Macchina fine lavoro */
			break;

		case 86:
			// occupata su CR6
			break;

		case 87:
			// occupata su CR6
			break;

		case 88:
			// occupata su CR6
			break;

		case 89:
			// occupata su CR6
			break;

		case 90:
			M90 = 1;		/* Ritorno tavola in lavoro, indietro verso macchina */
			break;

		case 91:
			M91 = 1;		/* Avanzamento tavola in carico, avanti verso operatore */
			break;

		case 92:
			// occupata su CR6
			break;

		case 93:
			// occupata su CR6
			break;

		case 94:
			// occupata su CR6
			break;

		case 95:
			// occupata su CR6
			break;

		case 96:
			// occupata su CR6
			break;

		case 97:
			break;

		case 98:
			M98	= 1;		/* Ciclo di Movimentazione morse in manuale */
			break;

		case 99:
			M99	= 1;		/* Fine Ciclo di Movimentazione morse in manuale */
			break;

		case 100:		/* Attesa ripristino per movimento da rieseguire */
			M100 = 1;
			break;

		case 101:		/* Start Trasportatore Trucioli */
			M101 = 1;
			break;

		case 102:		/* Stop Trasportatore Trucioli */
			M102 = 1;
			break;

		case 103:	
			// occupata su CR6
			break;

		case 104:
			// occupata su CR6
			break;

		case 105:
			M105 = 1;      // Verifica degli assi morse agganciati in gantry (FATM)
			break;

		case 106:
			M106 = 1;      // MOVPIECE.CS4 in corso
			break;

		case 107:
			M107 = 1;      // MOVPIECE.CS4 terminata
			break;

		case 108:
			M108 = 1;      // Aggancio assi morse in gantry (FATM)
			break;

		case 109:
			M109 = 1;      // Sgancio assi morse in gantry (FATM)
			break;

		case 110:
			M110 = 1;       /* MORSE TRASC. ASSE X : Inizio ciclo controllo pos. morse dopo posizionamento */
			break;

		case 111:
			M111 = 1;       /* MORSE TRASC. ASSE X : Fine ciclo controllo pos. morse dopo posizionamento */
			break;

		case 112:
			M112 = 1;		/* TRASC.MORSE : Ciclo pos.trascinamento morse in corso (serve per ovviare l'allarme magazzino aperto in ciclo) */
			break;

		case 113:
			M113 = 1;		/* TRASC.MORSE : FINE Ciclo pos.trascinamento morse in corso (serve per ovviare l'allarme magazzino aperto in ciclo) */
			break;

		case 114:
			M114 = 1;		/* Ciclo cambio utensili assistito in corso */
			break;

		case 115:
			M115 = 1;		/* Fine Ciclo cambio utensili assistito */
			break;

		case 116:				
			M116 = 1;               /* Salita Battuta di carico SX1 */
			break;

		case 117:				
			M117 = 1;               /* Discesa Battuta di carico SX1 */
			break;

		case 118:
			M118 = 1;              /* Inizio ciclo marposs */
			break;

		case 119:
			M119 = 1;              /* Fine ciclo marposs */
			break;

		case 120:
			M120 = 1;              /* Verifica entità della tastatura: se maggiore della metà della corsa di tastatura dai allarme */
			break;

		case 121:				
			break;

		case 122:
			M122 = 1;               /* Salita Battuta di carico DX4 */
			break;

		case 123:				
			M123 = 1;               /* Discesa Battuta di carico DX4 */
			break;

		case 124:				/* Salita Battute di carico ZONA SX */
			M116 = 1;
			break;

		case 125:				/* Discesa Battute di carico ZONA SX */
			M117 = 1;
			break;

		case 126:				/* Salita Battute di carico ZONA DX */
			M122 = 1;				
			break;

		case 127:				/* Discesa Battute di carico ZONA DX */
			M123 = 1;				
			break;

		case 128:				/* Salita Battute di carico ZONA SX E ZONA DX */
			M116 = 1;
			M122 = 1;				
			break;

		case 129:				/* Discesa Battute di carico ZONA SX E ZONA DX */
			M117 = 1;
			M123 = 1;				
			break;

		case 130:				// Chiusura tutte le morse 
			M134 = 1; M234 = 0;
			M135 = 1; M235 = 0;
			M136 = 1; M236 = 0;
			M137 = 1; M237 = 0;
			M138 = 1; M238 = 0;
			M139 = 1; M239 = 0;
			break;

		case 131:
			// occupata su CR6
			break;

		case 132:
			// occupata su CR6
			break;

		case 133:
			// occupata su CR6
			break;

		case 134:
			M134 = 1; M234 = 0;				/* Chiusura Morsa 10 */
			break;

		case 135:
			M135= 1; M235 = 0;				/* Chiusura Morsa 11 */
			break;

		case 136:
			M136 = 1; M236 = 0;				/* Chiusura Morsa 12 */
			break;

		case 137:
			M137 = 1; M237 = 0;				/* Chiusura Morsa 13 */
			break;

		case 138:
			M138 = 1; M238 = 0;				/* Chiusura Morsa 14 */
			break;

		case 139:
			M139 = 1; M239 = 0;				/* Chiusura Morsa 15 */
			break;

		case 140:
			// occupata su CR6
			break;

		case 141:
			// occupata su CR6
			break;

		case 142:
			// occupata su CR6
			break;

		case 143:				// Chiusura tutte le morse SX
			M134 = 1; M234 = 0;
			M135 = 1; M235 = 0;
			M136 = 1; M236 = 0;
			break;

		case 144:				// Chiusura tutte le morse DX
			M137 = 1; M237 = 0;
			M138 = 1; M238 = 0;
			M139 = 1; M239 = 0;
			break;

		case 145:	// Chiusura morse indicizzata
			RIC_CH_BF_MORS_ORIZ_10 = (R[R_RIC_CH_MORS_10]>0.5) || (R[R_RIC_CH_MORS_TOT]>0.5) || ((R[R_RIC_CH_MORS_SX]>0.5) && (MORSA10_A_SX1 || MORSA10_A_SX2)) || ((R[R_RIC_CH_MORS_DX]>0.5) && (MORSA10_A_DX3 || MORSA10_A_DX4));
			RIC_CH_BF_MORS_ORIZ_11 = (R[R_RIC_CH_MORS_11]>0.5) || (R[R_RIC_CH_MORS_TOT]>0.5) || ((R[R_RIC_CH_MORS_SX]>0.5) && (MORSA11_A_SX1 || MORSA11_A_SX2)) || ((R[R_RIC_CH_MORS_DX]>0.5) && (MORSA11_A_DX3 || MORSA11_A_DX4));
			RIC_CH_BF_MORS_ORIZ_12 = (R[R_RIC_CH_MORS_12]>0.5) || (R[R_RIC_CH_MORS_TOT]>0.5) || ((R[R_RIC_CH_MORS_SX]>0.5) && (MORSA12_A_SX1 || MORSA12_A_SX2)) || ((R[R_RIC_CH_MORS_DX]>0.5) && (MORSA12_A_DX3 || MORSA12_A_DX4));

			RIC_CH_BF_MORS_ORIZ_13 = (R[R_RIC_CH_MORS_13]>0.5) || (R[R_RIC_CH_MORS_TOT]>0.5) || ((R[R_RIC_CH_MORS_SX]>0.5) && (MORSA13_A_SX1 || MORSA13_A_SX2)) || ((R[R_RIC_CH_MORS_DX]>0.5) && (MORSA13_A_DX3 || MORSA13_A_DX4));
			RIC_CH_BF_MORS_ORIZ_14 = (R[R_RIC_CH_MORS_14]>0.5) || (R[R_RIC_CH_MORS_TOT]>0.5) || ((R[R_RIC_CH_MORS_SX]>0.5) && (MORSA14_A_SX1 || MORSA14_A_SX2)) || ((R[R_RIC_CH_MORS_DX]>0.5) && (MORSA14_A_DX3 || MORSA14_A_DX4));
			RIC_CH_BF_MORS_ORIZ_15 = (R[R_RIC_CH_MORS_15]>0.5) || (R[R_RIC_CH_MORS_TOT]>0.5) || ((R[R_RIC_CH_MORS_SX]>0.5) && (MORSA15_A_SX1 || MORSA15_A_SX2)) || ((R[R_RIC_CH_MORS_DX]>0.5) && (MORSA15_A_DX3 || MORSA15_A_DX4));
					
			if(RIC_CH_BF_MORS_ORIZ_10) { M134 = 1; M234 = 0; }
			if(RIC_CH_BF_MORS_ORIZ_11) { M135 = 1; M235 = 0; }
			if(RIC_CH_BF_MORS_ORIZ_12) { M136 = 1; M236 = 0; }

			if(RIC_CH_BF_MORS_ORIZ_13) { M137 = 1; M237 = 0; }
			if(RIC_CH_BF_MORS_ORIZ_14) { M138 = 1; M238 = 0; }
			if(RIC_CH_BF_MORS_ORIZ_15) { M139 = 1; M239 = 0; }

			R[R_RIC_CH_MORS_TOT] = 0;
			R[R_RIC_CH_MORS_SX] = 0;
			R[R_RIC_CH_MORS_DX] = 0;


			R[R_RIC_CH_MORS_10] = 0;
			R[R_RIC_CH_MORS_11] = 0;
			R[R_RIC_CH_MORS_12] = 0;
			R[R_RIC_CH_MORS_13] = 0;
			R[R_RIC_CH_MORS_14] = 0;
			R[R_RIC_CH_MORS_15] = 0;

			break;

		case 146:	
			break;

		case 147:
			// occupata su CR6
			break;

		case 148:
			// occupata su CR6
			break;

		case 149:
			// occupata su CR6
			break;

		case 150:
			M150 = 1;              /* Funzione ausiliaria di comunicazione con l'applicativo del laser (FATM) */
			break;

		case 151:
			break;

		case 152:
			M152 = 1;               /* MORSE MOT. : Ciclo ricerca morse in corso per conteggio e posiz.*/
			break;

		case 153:
			M153 = 1;               /* MORSE MOT. : Fine ciclo ricerca morse per conteggio e posiz.*/
			break;

		case 154:
			M154 = 1;				/* MORSE MOT. : Controllo la posizione morse prima del lavoro */
			break;

		case 155:
			// occupata su CR6
			break;

		case 156:			
			// occupata su CR6
			break;

		case 157:
			// occupata su CR6
			break;

		case 158:
			M158 = 1;				/* MORSE MOT. e TRASC : Controllo posizione morse inviata da PC attivo */
			break;

		case 159:
			// occupata su CR6
			break;

		case 160:
			// occupata su CR6
			break;

		case 161:
			// occupata su CR6
			break;

		case 162:
			// occupata su CR6
			break;

		case 163:
			// occupata su CR6
			break;

		case 164:
			// occupata su CR6
			break;

		case 165:
			// occupata su CR6
			break;

		case 166:
			//(SOLO CR6) set in uscite.c	M166 = 1;               /* Avanti Battuta di carico SX1 */
			break;

		case 167:
			//(SOLO CR6) set in uscite.c	M167 = 1;               /* Indietro Battuta di carico SX1 */
			break;

		case 168:
			M168 = 1;               // Avanti tavola no FATM
			break;

		case 169:
			// occupata su CR6
			break;

		case 170:
			// occupata su CR6
			break;

		case 171:				
			break;

		case 172:
			//(SOLO CR6) set in uscite.c	M172 = 1;               /* Avanti Battuta di carico DX4 */
			break;

		case 173:				
			//(SOLO CR6) set in uscite.c	M173 = 1;               /* Indietro Battuta di carico DX4 */
			break;

		case 174:
			M174 = 1;               // Spegne il tastatore
			break;

		case 175:
			M175 = 1;               // Attesa FATM in figura CAM_PROB.CNC (aspetta che vada a zero l'ingresso di tastatore in battuta)
			break;

		case 176:
			M176 = 1;				// TASTATORE ANCORA IN BATTUTA DOPO FINE TASTATA
			break;

		case 177:
			M177 = 1;				// Controllo stato tastatore: FINE tastatore non premuto
			break;

		case 178:
			M178 = 1;				// Controllo stato tastatore: INIZIO tastatore non premuto
			break;

		case 179:
			M179 = 1;				// Controllo stato tastatore: tastatore premuto
			break;

		case 180:	/* SUPER-OTTIMIZZAZIONE : Muovi tutte le battute insieme */
			/* Battute alte o basse */
			if ((R[R_POSBAT_VERT_SX1]) && (R[R_SOLBAT_OPER])==(float) 0) M116=1;
			if (!R[R_POSBAT_VERT_SX1]) M117=1;
			if ((R[R_POSBAT_VERT_DX4]) && (R[R_SOLBAT_OPER])==(float) 0) M122=1;
			if (!R[R_POSBAT_VERT_DX4]) M123=1;
			break;


		case 181:
			// occupata su CR6
			break;

		case 182:
			// occupata su CR6
			break;


		case 183:				/* Super contemporaneità - Ripari Aperti e battute tutte in posizione */
			M60	= 1;
			M310 = 1;				// Apertura (avanzamento) visiera bassa
			M312 = 1;				// Apertura (discesa) visiera alta

			/* ----- QUESTA PARTE DEVE ESSERE COPIATA DALLA M180 ----- */
			/* Battute alte o basse */
			if (( R[R_POSBAT_VERT_SX1]) && (R[R_SOLBAT_OPER])==(float) 0) M116=1;
			if (!R[R_POSBAT_VERT_SX1]) M117=1;
			if (( R[R_POSBAT_VERT_DX4]) && (R[R_SOLBAT_OPER])==(float) 0) M122=1;
			if (!R[R_POSBAT_VERT_DX4]) M123=1;
			break;


		case 184:
			M184 = 1;		    // Controllo stato tastatore: errore indice tastatura
			break;

		case 185:
			break;

		case 186:
			M61	 = 1;			/* Chiusura riparo */
			M311 = 1;			// Chiusura (arretramento) visiera bassa
			M313 = 1;			// Chiusura (salita) visiera alta
			break;

		case 187:
			// occupata su CR6
			break;

		case 188:
			// occupata su CR6
			break;

		case 189:
			// occupata su CR6
			break;

		case 190:				/* Apertura ripari anteriori */        
			M60 = 1;
			M310 = 1;				// Apertura (avanzamento) visiera bassa
			M312 = 1;				// Apertura (discesa) visiera alta
			break;

		case 191:				/* Chiusura ripari anteriori */
			M61 = 1;
			M311 = 1;				// Chiusura (arretramento) visiera bassa  
			M313 = 1;				// Chiusura (salita) visiera alta
			break;

		case 192:
			break;

		case 193:				/* Chiusura ripari anteriori , tutte le battute basse*/
			M61 = 1;				/* Chiusura riparo anteriore */
			M311 = 1;				// Chiusura (arretramento) visiera bassa
			M313 = 1;				// Chiusura (salita) visiera alta
			M117 = 1;               /* Discesa Battuta di carico SX1 */
			M123 = 1;               /* Discesa Battuta di carico DX4 */
			break;

		case 194:
			break;

		case 195:
			M195 = 1;				/* Ciclo attualmente in corso */
			break;

		case 196:
			M196 = 1;				/* Start conteggio tempo ciclo SX */
			break;

		case 197:
			M197 = 1;				/* Start conteggio tempo ciclo DX */
			break;

		case 198:
			{
			M198 = 1;				/* Conferma ciclo in corso */
			R[R_ENABLE_CK_ISOCODE] = (float) 1.0;  // Abilta HDrill a fare il check del random isocode
			}
			break;

		case 199:
			break;

		case 200:
			M200 = 1;				/* Abilita controllo riposizionamento morse */	
			break;

		case 201:
			M201 = 1;		// Inserimento Trascinatore Morse su asse X
			M56 = 1;		// Avanti micro Morse su asse X     
			break;

		case 202:
			M202 = 1;		// Disinserimento Trascinatore Morse su asse X
			break;

		case 203:
			// occupata su CR6
			break;

		case 204:
			// occupata su CR6
			break;

		case 205:
			// occupata su CR6
			break;

		case 206:
			// occupata su CR6
			break;

		case 207:
			// occupata su CR6
			break;

		case 208:
			// occupata su CR6
			break;

		case 209:
			M209 = 1;       // Carica tabella utensili da file
			break;

		case 210:           // Impegnata Forza abilitazione delle morse del CH2 nella MOVEMORS
			break;

		case 211:           // Impegnata Reset abilitazione delle morse del CH2 nella MOVEMORS
			break;

		case 212:
			// occupata su CR6
			break;

		case 213:
			// occupata su CR6
			break;

		case 214:
			// occupata su CR6
			break;

		case 215:
			// occupata su CR6
			break;

		case 216:
			// occupata su CR6
			break;

		case 217:
			// occupata su CR6
			break;

		case 218:
			// occupata su CR6
			break;

		case 219:
			// occupata su CR6
			break;

		case 220:
			// occupata su CR6
			break;

		case 221:
			// occupata su CR6
			break;

		case 222:
			// occupata su CR6
			break;

		case 223:
			// occupata su CR6
			break;

		case 224:
			// occupata su CR6
			break;

		case 225:
			// occupata su CR6
			break;

		case 226:
			M226 = 1;		// Abilita mandrino per maschiatura rigida 
			break;

		case 227:
			M227 = 1;		// Disabilita mandrino dopo maschiatura rigida 
			break;

		case 228:
			M228 = 1;       // Check congruità posizioni assi morse
			break;

		case 229:	// Apertura morse indicizzata
			RIC_AP_MORS_ORIZ_10 = (R[R_RIC_AP_MORS_10]>0.5) || (R[R_RIC_AP_MORS_TOT]>0.5) || ((R[R_RIC_AP_MORS_SX]>0.5) && (MORSA10_A_SX1 || MORSA10_A_SX2)) || ((R[R_RIC_AP_MORS_DX]>0.5) && (MORSA10_A_DX3 || MORSA10_A_DX4));
			RIC_AP_MORS_ORIZ_11 = (R[R_RIC_AP_MORS_11]>0.5) || (R[R_RIC_AP_MORS_TOT]>0.5) || ((R[R_RIC_AP_MORS_SX]>0.5) && (MORSA11_A_SX1 || MORSA11_A_SX2)) || ((R[R_RIC_AP_MORS_DX]>0.5) && (MORSA11_A_DX3 || MORSA11_A_DX4));
			RIC_AP_MORS_ORIZ_12 = (R[R_RIC_AP_MORS_12]>0.5) || (R[R_RIC_AP_MORS_TOT]>0.5) || ((R[R_RIC_AP_MORS_SX]>0.5) && (MORSA12_A_SX1 || MORSA12_A_SX2)) || ((R[R_RIC_AP_MORS_DX]>0.5) && (MORSA12_A_DX3 || MORSA12_A_DX4));
			RIC_AP_MORS_ORIZ_13 = (R[R_RIC_AP_MORS_13]>0.5) || (R[R_RIC_AP_MORS_TOT]>0.5) || ((R[R_RIC_AP_MORS_SX]>0.5) && (MORSA13_A_SX1 || MORSA13_A_SX2)) || ((R[R_RIC_AP_MORS_DX]>0.5) && (MORSA13_A_DX3 || MORSA13_A_DX4));
			RIC_AP_MORS_ORIZ_14 = (R[R_RIC_AP_MORS_14]>0.5) || (R[R_RIC_AP_MORS_TOT]>0.5) || ((R[R_RIC_AP_MORS_SX]>0.5) && (MORSA14_A_SX1 || MORSA14_A_SX2)) || ((R[R_RIC_AP_MORS_DX]>0.5) && (MORSA14_A_DX3 || MORSA14_A_DX4));
			RIC_AP_MORS_ORIZ_15 = (R[R_RIC_AP_MORS_15]>0.5) || (R[R_RIC_AP_MORS_TOT]>0.5) || ((R[R_RIC_AP_MORS_SX]>0.5) && (MORSA15_A_SX1 || MORSA15_A_SX2)) || ((R[R_RIC_AP_MORS_DX]>0.5) && (MORSA15_A_DX3 || MORSA15_A_DX4));

			if(RIC_AP_MORS_ORIZ_10) { M234 = 1; M134 = 0; M274 = 0; }
			if(RIC_AP_MORS_ORIZ_11) { M235 = 1; M135 = 0; M275 = 0; }
			if(RIC_AP_MORS_ORIZ_12) { M236 = 1; M136 = 0; M276 = 0; }
			if(RIC_AP_MORS_ORIZ_13) { M237 = 1; M137 = 0; M277 = 0; }
			if(RIC_AP_MORS_ORIZ_14) { M238 = 1; M138 = 0; M278 = 0; }
			if(RIC_AP_MORS_ORIZ_15) { M239 = 1; M139 = 0; M279 = 0; }

			R[R_RIC_AP_MORS_TOT] = 0;
			R[R_RIC_AP_MORS_SX] = 0;
			R[R_RIC_AP_MORS_DX] = 0;

			R[R_RIC_AP_MORS_10] = 0;
			R[R_RIC_AP_MORS_11] = 0;
			R[R_RIC_AP_MORS_12] = 0;
			R[R_RIC_AP_MORS_13] = 0;
			R[R_RIC_AP_MORS_14] = 0;
			R[R_RIC_AP_MORS_15] = 0;
			break;

		case 230:		// Apertura tutte le morse 
			M234 = 1; M134 = 0; M274 = 0; 
			M235 = 1; M135 = 0; M275 = 0; 
			M236 = 1; M136 = 0; M276 = 0; 

			M237 = 1; M137 = 0; M277 = 0; 
			M238 = 1; M138 = 0; M278 = 0; 
			M239 = 1; M139 = 0; M279 = 0; 
			break;

		case 231:
			// occupata su CR6
			break;

		case 232:
			// occupata su CR6
			break;

		case 233:
			// occupata su CR6
			break;

		case 234:
			M234 = 1; M134 = 0; M274 = 0; 				/* Apertura Morsa 10 */
			break;

		case 235:
			M235 = 1; M135 = 0; M275 = 0; 				/* Apertura Morsa 11 */
			break;

		case 236:
			M236 = 1; M136 = 0; M276 = 0; 				/* Apertura Morsa 12 */
			break;

		case 237:
			M237 = 1; M137 = 0; M277 = 0; 				/* Apertura Morsa 13 */
			break;

		case 238:
			M238 = 1; M138 = 0; M278 = 0; 				/* Apertura Morsa 14 */
			break;

		case 239:
			M239 = 1; M139 = 0; M279 = 0; 				/* Apertura Morsa 15 */
			break;

		case 240:
			// occupata su CR6
			break;

		case 241:
			// occupata su CR6
			break;

		case 242:
			// occupata su CR6
			break;

		case 243:			// Apertura tutte le morse SX
			M234 = 1; M134 = 0; M274 = 0; 
			M235 = 1; M135 = 0; M275 = 0; 
			M236 = 1; M136 = 0; M276 = 0; 
			break;

		case 244:			// Apertura tutte le morse DX
			M237 = 1; M137 = 0; M277 = 0; 
			M238 = 1; M138 = 0; M278 = 0; 
			M239 = 1; M139 = 0; M279 = 0; 
			break;

		case 245:
			M245 = 1;       /* MORSE : Ciclo ricerca morse in corso per conteggio e posiz.*/
			break;

		case 246:
			M246 = 1;       /* MORSE : Fine ciclo ricerca morse per conteggio e posiz.*/
			break;

		case 247:
			M247 = 1;       /* Ciclo pos. assi a riposo */
			break;

		case 248:
			M248 = 1;       /* Fine ciclo pos. assi a riposo */
			break;

		case 249:
			M249 = 1;       // Attesa sincronizzazione CN/Drill, usata in CKTOOL.CS4 in gestione utensili avanzata (solo su SATELLITE XT EVO)
			break;

		case 250:
			M250 = 1;       // Abilita allarme utensile non utilizzabile (gestione utensili avanzata)
			break;

		case 251:
			M251 = 1;       // Attesa lettura parametri gestione utensili avanzata
			break;

		case 252:
			M252 = 1;       // Verifica lista parametri in uso nell'isomg (verifica se utensili rotti e senza alias)
			break;

		case 253:
			M253 = 1;       // Inizio scrittura file report 
			break;

		case 254:
			M254 = 1;       // Fine scrittura file report
			break;

		case 255:
			M255 = 1;       //Disabilita filtri su assi X,Y,Z,A prima di maschiatura rigida (FATM)
			break;

		case 256:
			M256 = 1;       //Abilita filtri su assi X,Y,Z,A dopo maschiatura rigida (FATM)
			break;

		case 257:
			// occupata su CR6
			break;

		case 258:
			// occupata su CR6
			break;

		case 259:
			break;
			/////////////////////////////////
		case 260:
			M260 = 1;   //Disattiva correzioni asse A
			break;

		case 261:
			M261 = 1;   //Attiva correzioni asse A
			break;

		case 262:
			M262 = 1;   //Disattiva correzioni asse X
			break;

		case 263:
			M263 = 1;   //Attiva correzioni asse X
			break;

		case 264:
			// occupata su CR6
			break;

		case 265:
			// occupata su CR6
			break;

		case 266:
			// occupata su CR6
			break;

		case 267:
			// occupata su CR6
			break;

		case 268:
			M268 = 1;   //Disattiva correzioni asse C
			break;

		case 269:
			M269 = 1;   //Attiva correzioni asse C
			break;
			/////////////////////////////////
		case 270:	// Chiusura morse in alta forza indicizzata
			RIC_CH_AF_MORS_ORIZ_10 = (R[R_RIC_CH_AF_MORS_10]>0.5) || (R[R_RIC_CH_AF_MORS_TOT]>0.5) || ((R[R_RIC_CH_AF_MORS_SX]>0.5) && (MORSA10_A_SX1 || MORSA10_A_SX2)) || ((R[R_RIC_CH_AF_MORS_DX]>0.5) && (MORSA10_A_DX3 || MORSA10_A_DX4));
			RIC_CH_AF_MORS_ORIZ_11 = (R[R_RIC_CH_AF_MORS_11]>0.5) || (R[R_RIC_CH_AF_MORS_TOT]>0.5) || ((R[R_RIC_CH_AF_MORS_SX]>0.5) && (MORSA11_A_SX1 || MORSA11_A_SX2)) || ((R[R_RIC_CH_AF_MORS_DX]>0.5) && (MORSA11_A_DX3 || MORSA11_A_DX4));
			RIC_CH_AF_MORS_ORIZ_12 = (R[R_RIC_CH_AF_MORS_12]>0.5) || (R[R_RIC_CH_AF_MORS_TOT]>0.5) || ((R[R_RIC_CH_AF_MORS_SX]>0.5) && (MORSA12_A_SX1 || MORSA12_A_SX2)) || ((R[R_RIC_CH_AF_MORS_DX]>0.5) && (MORSA12_A_DX3 || MORSA12_A_DX4));
			RIC_CH_AF_MORS_ORIZ_13 = (R[R_RIC_CH_AF_MORS_13]>0.5) || (R[R_RIC_CH_AF_MORS_TOT]>0.5) || ((R[R_RIC_CH_AF_MORS_SX]>0.5) && (MORSA13_A_SX1 || MORSA13_A_SX2)) || ((R[R_RIC_CH_AF_MORS_DX]>0.5) && (MORSA13_A_DX3 || MORSA13_A_DX4));
			RIC_CH_AF_MORS_ORIZ_14 = (R[R_RIC_CH_AF_MORS_14]>0.5) || (R[R_RIC_CH_AF_MORS_TOT]>0.5) || ((R[R_RIC_CH_AF_MORS_SX]>0.5) && (MORSA14_A_SX1 || MORSA14_A_SX2)) || ((R[R_RIC_CH_AF_MORS_DX]>0.5) && (MORSA14_A_DX3 || MORSA14_A_DX4));
			RIC_CH_AF_MORS_ORIZ_15 = (R[R_RIC_CH_AF_MORS_15]>0.5) || (R[R_RIC_CH_AF_MORS_TOT]>0.5) || ((R[R_RIC_CH_AF_MORS_SX]>0.5) && (MORSA15_A_SX1 || MORSA15_A_SX2)) || ((R[R_RIC_CH_AF_MORS_DX]>0.5) && (MORSA15_A_DX3 || MORSA15_A_DX4));

					
			if(RIC_CH_AF_MORS_ORIZ_10) { M274 = 1; M234 = 0; M294 = 0; }
			if(RIC_CH_AF_MORS_ORIZ_11) { M275 = 1; M235 = 0; M295 = 0; }
			if(RIC_CH_AF_MORS_ORIZ_12) { M276 = 1; M236 = 0; M296 = 0; }
			if(RIC_CH_AF_MORS_ORIZ_13) { M277 = 1; M237 = 0; M297 = 0; }
			if(RIC_CH_AF_MORS_ORIZ_14) { M278 = 1; M238 = 0; M298 = 0; }
			if(RIC_CH_AF_MORS_ORIZ_15) { M279 = 1; M239 = 0; M299 = 0; }

			R[R_RIC_CH_AF_MORS_TOT] = 0;
			R[R_RIC_CH_AF_MORS_SX] = 0;
			R[R_RIC_CH_AF_MORS_DX] = 0;

			R[R_RIC_CH_AF_MORS_10] = 0;
			R[R_RIC_CH_AF_MORS_11] = 0;
			R[R_RIC_CH_AF_MORS_12] = 0;
			R[R_RIC_CH_AF_MORS_13] = 0;
			R[R_RIC_CH_AF_MORS_14] = 0;
			R[R_RIC_CH_AF_MORS_15] = 0;
			break;

		case 271:
			// occupata su CR6
			break;

		case 272:
			// occupata su CR6
			break;

		case 273:
			// occupata su CR6
			break;

		case 274:
			M274 = 1; M234 = 0; M294 = 0;    //Attiva chiusura in alta forza morsa 10
			break;

		case 275:
			M275 = 1; M235 = 0; M295 = 0;    //Attiva chiusura in alta forza morsa 11
			break;

		case 276:
			M276 = 1; M236 = 0; M296 = 0;    //Attiva chiusura in alta forza morsa 12
			break;

		case 277:
			M277 = 1; M237 = 0; M297 = 0;    //Attiva chiusura in alta forza morsa 13
			break;

		case 278:
			M278 = 1; M238 = 0; M298 = 0;    //Attiva chiusura in alta forza morsa 14
			break;

		case 279:
			M279 = 1; M239 = 0; M299 = 0;    //Attiva chiusura in alta forza morsa 15
			break;

		case 280:
			// occupata su CR6
			break;

		case 281:
			// occupata su CR6
			break;

		case 282:
			// occupata su CR6
			break;

		case 283:              // occupata su CR4
			break;

		case 284:          // occupata su CR6
			break;

		case 285:          // occupata su CR6
			break;

		case 286:
			// occupata su CR6
			break;

		case 287:
			// occupata su CR6
			break;

		case 288:
			// occupata su CR6
			break;

		case 289:
			break;

		case 290:	// Disattivazione Chiusura morse in alta forza indicizzata
			RIC_DIS_AF_MORS_ORIZ_10 = (R[R_RIC_DIS_AF_MORS_10]>0.5) || (R[R_RIC_DIS_AF_MORS_TOT]>0.5) || ((R[R_RIC_DIS_AF_MORS_SX]>0.5) && (MORSA10_A_SX1 || MORSA10_A_SX2)) || ((R[R_RIC_DIS_AF_MORS_DX]>0.5) && (MORSA10_A_DX3 || MORSA10_A_DX4));
			RIC_DIS_AF_MORS_ORIZ_11 = (R[R_RIC_DIS_AF_MORS_11]>0.5) || (R[R_RIC_DIS_AF_MORS_TOT]>0.5) || ((R[R_RIC_DIS_AF_MORS_SX]>0.5) && (MORSA11_A_SX1 || MORSA11_A_SX2)) || ((R[R_RIC_DIS_AF_MORS_DX]>0.5) && (MORSA11_A_DX3 || MORSA11_A_DX4));
			RIC_DIS_AF_MORS_ORIZ_12 = (R[R_RIC_DIS_AF_MORS_12]>0.5) || (R[R_RIC_DIS_AF_MORS_TOT]>0.5) || ((R[R_RIC_DIS_AF_MORS_SX]>0.5) && (MORSA12_A_SX1 || MORSA12_A_SX2)) || ((R[R_RIC_DIS_AF_MORS_DX]>0.5) && (MORSA12_A_DX3 || MORSA12_A_DX4));

			RIC_DIS_AF_MORS_ORIZ_13 = (R[R_RIC_DIS_AF_MORS_13]>0.5) || (R[R_RIC_DIS_AF_MORS_TOT]>0.5) || ((R[R_RIC_DIS_AF_MORS_SX]>0.5) && (MORSA13_A_SX1 || MORSA13_A_SX2)) || ((R[R_RIC_DIS_AF_MORS_DX]>0.5) && (MORSA13_A_DX3 || MORSA13_A_DX4));
			RIC_DIS_AF_MORS_ORIZ_14 = (R[R_RIC_DIS_AF_MORS_14]>0.5) || (R[R_RIC_DIS_AF_MORS_TOT]>0.5) || ((R[R_RIC_DIS_AF_MORS_SX]>0.5) && (MORSA14_A_SX1 || MORSA14_A_SX2)) || ((R[R_RIC_DIS_AF_MORS_DX]>0.5) && (MORSA14_A_DX3 || MORSA14_A_DX4));
			RIC_DIS_AF_MORS_ORIZ_15 = (R[R_RIC_DIS_AF_MORS_15]>0.5) || (R[R_RIC_DIS_AF_MORS_TOT]>0.5) || ((R[R_RIC_DIS_AF_MORS_SX]>0.5) && (MORSA15_A_SX1 || MORSA15_A_SX2)) || ((R[R_RIC_DIS_AF_MORS_DX]>0.5) && (MORSA15_A_DX3 || MORSA15_A_DX4));
					
			if(RIC_DIS_AF_MORS_ORIZ_10) { M294 = 1; M274 = 0; }
			if(RIC_DIS_AF_MORS_ORIZ_11) { M295 = 1; M275 = 0; }
			if(RIC_DIS_AF_MORS_ORIZ_12) { M296 = 1; M276 = 0; }

			if(RIC_DIS_AF_MORS_ORIZ_13) { M297 = 1; M277 = 0; }
			if(RIC_DIS_AF_MORS_ORIZ_14) { M298 = 1; M278 = 0; }
			if(RIC_DIS_AF_MORS_ORIZ_15) { M299 = 1; M279 = 0; }

			R[R_RIC_DIS_AF_MORS_TOT] = 0;
			R[R_RIC_DIS_AF_MORS_SX] = 0;
			R[R_RIC_DIS_AF_MORS_DX] = 0;

			R[R_RIC_DIS_AF_MORS_10] = 0;
			R[R_RIC_DIS_AF_MORS_11] = 0;
			R[R_RIC_DIS_AF_MORS_12] = 0;
			R[R_RIC_DIS_AF_MORS_13] = 0;
			R[R_RIC_DIS_AF_MORS_14] = 0;
			R[R_RIC_DIS_AF_MORS_15] = 0;
			break;

		case 291:
			// occupata su CR6
			break;

		case 292:
			// occupata su CR6
			break;

		case 293:
			// occupata su CR6
			break;

		case 294:
			M294 = 1; M274 = 0;              //DisAttiva chiusura in alta forza morsa 10
			break;

		case 295:
			M295 = 1; M275 = 0;              //DisAttiva chiusura in alta forza morsa 11
			break;

		case 296:
			M296 = 1; M276 = 0;              //DisAttiva chiusura in alta forza morsa 12
			break;

		case 297:
			M297 = 1; M277 = 0;              //DisAttiva chiusura in alta forza morsa 13
			break;

		case 298:
			M298 = 1; M278 = 0;              //DisAttiva chiusura in alta forza morsa 14
			break;

		case 299:
			M299 = 1; M279 = 0;              //DisAttiva chiusura in alta forza morsa 15
			break;

		case 300:
			// occupata su CR6
			break;

		case 301:
			// occupata su CR6
			break;

		case 302:
			// occupata su CR6
			break;

		case 303:
			M303 = 1;                        // FATM: check posizione battute SX1 e DX4 in multipezzo 
			break;

		case 304:
			// occupata su CR6
			break;

		case 305:
			// occupata su CR6
			break;

		case 306:
			M306 = 1;                        //Disattiva correzioni asse Y
			break;

		case 307:
			M307 = 1;                        //Attiva correzioni asse Y		
			break;

		case 308:
			M308 = 1;                        //Disattiva correzioni asse Z		
			break;

		case 309:
			M309 = 1;                        //Attiva correzioni asse Z		
			break;
			/////////////////////////////////
		case 310:
			M310 = 1;  //Avanzamento (apertura) visiera bassa
			break;

		case 311:
			M311 = 1;  //Arretramento (chiusura) visiera bassa
			break;

		case 312:
			M312 = 1;  //Discesa (apertura) visiera alta
			break;

		case 313:
			M313 = 1;  //Salita (chiusura) visiera alta
			break;

		case 314:
			// occupata su CR6
			break;

		case 315:
			// occupata su CR6
			break;

		case 316:
			// occupata su CR6
			break;

		case 317:
			// occupata su CR6
			break;

		case 318:
			// occupata su CR6
			break;

		case 319:
			break;
			/////////////////////////////////
		case 320:				/* Sblocca tutte gli Zimmer morse */
			M324 = 1;
			M325 = 1;
			M326 = 1;
			M327 = 1;
			M328 = 1;
			M329 = 1;
			break;

		case 321:
			// occupata su CR6
			break;

		case 322:
			// occupata su CR6
			break;

		case 323:
			// occupata su CR6
			break;

		case 324:
			M324 = 1;				/* Sbloccaggio Zimmer Morsa 10 */
			break;

		case 325:
			M325 = 1;				/* Sbloccaggio Zimmer Morsa 11 */
			break;

		case 326:
			M326 = 1;				/* Sbloccaggio Zimmer Morsa 12 */
			break;

		case 327:
			M327 = 1;				/* Sbloccaggio Zimmer Morsa 13 */
			break;

		case 328:
			M328 = 1;				/* Sbloccaggio Zimmer Morsa 14 */
			break;

		case 329:
			M329 = 1;				/* Sbloccaggio Zimmer Morsa 15 */
			break;

		case 330:
			// occupata su CR6
			break;

		case 331:
			// occupata su CR6
			break;

		case 332:
			// occupata su CR6
			break;

		case 333:				/* Blocca tutte gli Zimmer morse */
			M337 = 1;
			M338 = 1;
			M339 = 1;
			M340 = 1;
			M341 = 1;
			M342 = 1;
			break;

		case 334:			
			// occupata su CR6
			break;

		case 335:
			// occupata su CR6
			break;

		case 336:
			// occupata su CR6
			break;

		case 337:
			M337 = 1;				/* Bloccaggio Zimmer Morsa 10 */
			break;

		case 338:
			M338 = 1;				/* Bloccaggio Zimmer Morsa 11 */
			break;

		case 339:
			M339 = 1;				/* Bloccaggio Zimmer Morsa 12 */
			break;

		case 340:
			M340 = 1;				/* Bloccaggio Zimmer Morsa 13 */
			break;

		case 341:
			M341 = 1;				/* Bloccaggio Zimmer Morsa 14 */
			break;

		case 342:
			M342 = 1;				/* Bloccaggio Zimmer Morsa 15 */
			break;

		case 343:
			// occupata su CR6
			break;

		case 344:
			// occupata su CR6
			break;

		case 345:
			// occupata su CR6
			break;

		case 346:
			// occupata su CR6
			break;

		case 347:
			// occupata su CR6
			break;

		case 348:			// occupata su CR6
			break;

		case 349:			// occupata su CR6
			break;

		case 350:
			M350 = 1;               //Richiesta sincronizzazione CNC livello 0
			break;

		case 351:
			M351 = 1;               //Richiesta sincronizzazione CNC livello 1
			break;

		case 352:
			// occupata su CR6
			break;

		case 353:
			M353 = 1;               // Disattivazione Abilitazione asse W
			break;

		case 354:
			// occupata su CR6
			break;

		case 355:
			// occupata su CR6
			break;

		case 356:
			// occupata su CR6
			break;

		case 357:
			M357 = 1;               // Riattivazione Abilitazione asse W
			break;

		case 358:
			// occupata su CR6
			break;

		case 359:
			// occupata su CR6
			break;

		case 360:
			// occupata su CR6
			break;

		case 361:
			// occupata su CR6
			break;

		case 362:
			// occupata su CR6
			break;

		case 363:
			// occupata su CR6
			break;

		case 364:
			M364 = 1;               // Ciclo di posizionamento morse con asse X in simulazione Simon (serve a scrivere la posizione morsa mentre viene mossa dall'asse X)
			break;

		case 365:
			M365 = 1;               // Fine ciclo di posizionamento morse con asse X in simulazione Simon
			break;

		case 366:
			break;

		case 367:
			break;

			// Nota importante (da Pierotti)
			// L'ultima funzione M configurabile è 65000 da spartaco 7.0 

		}
	}

}


//Get funz M, ritorna true se almeno una delle funzioni M dei canali è a true
BOOL Mg_MC(int nFunzM)
{
	int shift_WORD = nFunzM / 16;
	int shift_BIT  = (int) (nFunzM % 16);

	BOOL M_CH0_bool = FALSE;
	BOOL M_CH1_bool = FALSE;
	BOOL M_CH2_bool = FALSE;

	switch (shift_BIT)
	{
	case 0:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 00);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 00);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 00);
	break;
	case 1:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 01);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 01);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 01);
	break;	
	case 2:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 02);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 02);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 02);
	break;	
	case 3:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 03);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 03);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 03);
	break;	
	case 4:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 04);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 04);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 04);
	break;	
	case 5:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 05);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 05);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 05);
	break;	
	case 6:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 06);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 06);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 06);
	break;	
	case 7:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 07);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 07);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 07);
	break;	
	case 8:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 08);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 08);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 08);
	break;	
	case 9:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 09);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 09);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 09);
	break;	
	case 10:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 10);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 10);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 10);
	break;	
	case 11:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 11);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 11);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 11);
	break;	
	case 12:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 12);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 12);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 12);
	break;	
	case 13:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 13);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 13);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 13);
	break;	
	case 14:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 14);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 14);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 14);
	break;	
	case 15:
	M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 15);
	M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 15);
	M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 15);
	break;	
	}

	//BOOL M_CH0_bool = PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, shift_BIT);
	//BOOL M_CH1_bool = PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, shift_BIT);
	//BOOL M_CH2_bool = PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, shift_BIT);

	return (M_CH0_bool || M_CH1_bool  || M_CH2_bool);
}


//Reset funz M mette a 0 il flag della funzione M per tutti i canali
void Mr_MC(int nFunzM)
{
	int shift_WORD = nFunzM / 16;
	int shift_BIT  = (int) (nFunzM % 16);


	switch (shift_BIT)
	{
	case 0:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 00) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 00) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 00) = 0;
	break;
	case 1:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 01) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 01) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 01) = 0;
	break;	
	case 2:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 02) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 02) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 02) = 0;
	break;	
	case 3:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 03) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 03) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 03) = 0;
	break;	
	case 4:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 04) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 04) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 04) = 0;
	break;	
	case 5:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 05) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 05) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 05) = 0;
	break;	
	case 6:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 06) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 06) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 06) = 0;
	break;	
	case 7:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 07) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 07) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 07) = 0;
	break;	
	case 8:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 08) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 08) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 08) = 0;
	break;	
	case 9:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 09) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 09) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 09) = 0;
	break;	
	case 10:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 10) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 10) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 10) = 0;
	break;	
	case 11:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 11) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 11) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 11) = 0;
	break;	
	case 12:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 12) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 12) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 12) = 0;
	break;	
	case 13:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 13) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 13) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 13) = 0;
	break;	
	case 14:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 14) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 14) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 14) = 0;
	break;	
	case 15:
	PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, 15) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, 15) = 0;
	PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, 15) = 0;
	break;	
	}


	//PLC_A_BIT(M_FIRST_WORD_N + shift_WORD, shift_BIT) = 0;
	//PLC_A_BIT(M_FIRST_WORD_N_CH1 + shift_WORD, shift_BIT) = 0;
	//PLC_A_BIT(M_FIRST_WORD_N_CH2 + shift_WORD, shift_BIT) = 0;
}

//Get funz M, ritorna true se almeno una delle funzioni M dei canali è a true
BOOL PLCMg_MC(int nFunzM)
{
	int shift_WORD = nFunzM / 16;
	int shift_BIT  = (int) (nFunzM % 16);

	BOOL M_CH0_bool = FALSE;
	BOOL M_CH1_bool = FALSE;
	BOOL M_CH2_bool = FALSE;

	switch (shift_BIT)
	{
	case 0:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 00);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 00);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 00);
	break;
	case 1:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 01);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 01);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 01);
	break;	
	case 2:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 02);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 02);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 02);
	break;	
	case 3:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 03);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 03);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 03);
	break;	
	case 4:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 04);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 04);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 04);
	break;	
	case 5:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 05);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 05);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 05);
	break;	
	case 6:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 06);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 06);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 06);
	break;	
	case 7:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 07);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 07);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 07);
	break;	
	case 8:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 08);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 08);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 08);
	break;	
	case 9:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 09);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 09);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 09);
	break;	
	case 10:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 10);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 10);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 10);
	break;	
	case 11:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 11);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 11);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 11);
	break;	
	case 12:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 12);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 12);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 12);
	break;	
	case 13:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 13);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 13);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 13);
	break;	
	case 14:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 14);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 14);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 14);
	break;	
	case 15:
	M_CH0_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 15);
	M_CH1_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 15);
	M_CH2_bool = PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 15);
	break;	
	}

	return (M_CH0_bool || M_CH1_bool  || M_CH2_bool);
}

//Reset funz M mette a 0 il flag della funzione M per tutti i canali
void PLCMr_MC(int nFunzM)
{
	int shift_WORD = nFunzM / 16;
	int shift_BIT  = (int) (nFunzM % 16);


	switch (shift_BIT)
	{
	case 0:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 00) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 00) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 00) = 0;
	break;
	case 1:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 01) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 01) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 01) = 0;
	break;	
	case 2:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 02) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 02) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 02) = 0;
	break;	
	case 3:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 03) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 03) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 03) = 0;
	break;	
	case 4:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 04) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 04) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 04) = 0;
	break;	
	case 5:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 05) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 05) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 05) = 0;
	break;	
	case 6:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 06) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 06) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 06) = 0;
	break;	
	case 7:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 07) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 07) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 07) = 0;
	break;	
	case 8:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 08) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 08) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 08) = 0;
	break;	
	case 9:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 09) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 09) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 09) = 0;
	break;	
	case 10:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 10) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 10) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 10) = 0;
	break;	
	case 11:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 11) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 11) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 11) = 0;
	break;	
	case 12:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 12) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 12) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 12) = 0;
	break;	
	case 13:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 13) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 13) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 13) = 0;
	break;	
	case 14:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 14) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 14) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 14) = 0;
	break;	
	case 15:
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH0 + shift_WORD, 15) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH1 + shift_WORD, 15) = 0;
	PLC_A_BIT(PLCM_FIRST_WORD_N_CH2 + shift_WORD, 15) = 0;
	break;	
	}
}