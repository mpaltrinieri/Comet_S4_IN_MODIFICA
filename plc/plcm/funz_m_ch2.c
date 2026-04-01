/*

		--------------------------------------------------------------
        TITOLO:         FUNZ_M_CH2
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Creazione flags funzioni "M" emesse da CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    funz_m_CH2(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          NVM_CH2   : Strobe funzioni "M"
                        O_EXE_CH2 : CNC in modo esecuzione
                        O_M_CH2   : Codice funzione "M" emessa da CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         M00_CH2
                        ..           : Flags funzioni "M" emesse :
                        ..             da "A3940.bit._00" 
						..             ad "A3962.bit._15"
                        M367_CH2
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           10-10-2018
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:  Formuso Daniele
        --------------------------------------------------------------

*/


#include        "all.inc"

//Legenda:
//Get funz M, ritorna true se almeno una delle funzioni M dei canali è a true
//BOOL Mg_MC(int nFunzM)

//Get funz PLCM, ritorna true se almeno una delle funzioni PLCM dei canali è a true
//BOOL PLCMg_MC(int nFunzM)

//Reset funz M mette a 0 il flag della funzione M per tutti i canali
//void Mr_MC(int nFunzM)


void funz_m_CH2(void)
{

	const int wordSize = sizeof(M_FIRST_WORD_CH2);
	const int bufLen = (&M_LAST_WORD_CH2 - &M_FIRST_WORD_CH2 + 1);

	// Reset indicizzato di tutti i flag delle funzioni "M" su reset CNC
	if (RESET_MC)
	{
		memset(&M_FIRST_WORD_CH2, 0, bufLen*wordSize);
		DRIVE_MISSING_FAL = 0;
	}

	tS(TS_NVM_CH2,(unsigned char) NVM_CH2);   /* Strobe nuova funzione M ch1 */

	/* Set dei flag delle funzioni "M" */
	if (DP_TSuppl[TS_NVM_CH2] && O_EXE_CH2)
	{

		//if (AUTO && !SIMULATORE_ON)
		//{
		//	if (Aris_CH2[R_CK_START] == (float)0)
		//		DRIVE_MISSING_FAL = 1;
		//}

		switch (O_M_CH2)
		{
		case 0:					// M_CH2_00 - da usare per PAUSA CICLO in ISO
			M_CH2_00 = 1;
			break;

		case 1:
			break;

		case 2:
			M_CH2_02 = 1;                /* Fine programma */
			break;

		case 3:
			M_CH2_03 = 1;                /* Rotazione oraria mandrino */
			break;

		case 4:
			M_CH2_04 = 1;                /* Rotazione antioraria mandrino */
			break;

		case 5:
			M_CH2_05 = 1;                /* Arresto rotazione mandrino */
			break;

		case 6:
			M_CH2_06 = 1;                /* Cambio utensili */
			break;

		case 7:
			M_CH2_07 = 1;                /* Refrigerante lubrica */
			break;

		case 8:
			break;

		case 9:
			M_CH2_09 = 1;                /* Arresto refrigerante */
			break;

		case 10:
			M_CH2_10 = 1;      // Verifica utensile in corso
			break;

		case 11:
			M_CH2_11 = 1;      // Fine verifica utensile
			break;

		case 12:
			M_CH2_12 = 1;      // Verifica dispositivo integrità utensile
			break;

		case 13:
			M_CH2_13 = 1;      // Verifica integrità utensile
			break;

		case 14:
			M_CH2_14 = 1;      // Abilita allarme utensile rotto (FATM)
			break;

		case 15:				// RISERVATA: Gamme
			break;

		case 16:
			break;

		case 17:
			break;

		case 18:
			M_CH2_18 = 1;				// Riferimento assi CANOPEN attivo
			break;

		case 19:				// RISERVATA: ORIENTAM.MANDR.
			M_CH2_19 = 1;
			break;

		case 20:
			M_CH2_20 = 1;               // Verifica mandrino fuori ingombro magazzino
			break;

		case 21:
			M_CH2_21 = 1;         // Rilievo dimensioni utensile in corso
			break;

		case 22:
			M_CH2_22 = 1;         // Fine rilievo dimensioni utensile
			break;

		case 23:
			break;

		case 24:
			M_CH2_24 = 1; // Inzio ciclo di tastatura con battuta di precisione
			break;

		case 25:
			M_CH2_25 = 1; // Fine ciclo di tastatura con battuta di precisione
			break;

		case 26:
			M_CH2_26 = 1; // Discesa battuta di precisione
			break;

		case 27:
			M_CH2_27 = 1; // Salita battuta di precisione
			break;

		case 28:
			break;

		case 29:
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
			PLCM91_CH2 = 1;				/* Avanzamento tavola in carico, avanti verso operatore */
			PLCM60_CH2 = 1;				/* Apertura riparo anteriore */
			PLCM310_CH2 = 1;			// Apertura (avanzamento) visiera bassa
			PLCM312_CH2 = 1;			// Apertura (discesa) visiera alta
			break;

		case 47:
			break;

		case 48:
			M_CH2_48 = 1;                /* Attivazione potenziometri */
			break;

		case 49:
			M_CH2_49 = 1;                /* Disattivazione potenziometri (100%) */
			break;

		case 50:
			M_CH2_50 = 1;                /* Sbloccaggio utensile su mandrino */
			break;

		case 51:
			M_CH2_51 = 1;                /* Bloccaggio utensile su mandrino */
			break;

		case 52:
			break;

		case 53:
			M_CH2_53 = 1;                /* Rotazione mandrino per masc. rigida */
			break;

		case 54:
			break;

		case 55:				
			break;

		case 56:				// Inserzione rilevatore morse
			M_CH2_56 = 1;
			break;

		case 57:				// Disinsezione rilevatore morse
			M_CH2_57 = 1;
			break;

		case 58:				// Discesa Ripari
			M_CH2_60 = 1;				/* Apertura riparo anteriore */ 
			M_CH2_310 = 1;				// Apertura (avanzamento) visiera bassa
			M_CH2_312 = 1;				// Apertura (discesa) visiera alta
			break;

		case 59:				// Salita Ripari
			M_CH2_61 = 1;				/* Chiusura riparo anteriore */
			M_CH2_311 = 1;				// Chiusura (arretramento) visiera bassa
			M_CH2_313 = 1;				// Chiusura (salita) visiera alta
			break;

		case 60:
			M_CH2_60 = 1;				/* Apertura riparo anteriore */
			M_CH2_310 = 1;				// Apertura (avanzamento) visiera bassa
			M_CH2_312 = 1;				// Apertura (discesa) visiera alta
			M_CH2_61 = 0;				/* Reset Chiusura riparo anteriore */
			PLCM61_CH2 = 0;				/* Reset Chiusura riparo anteriore */
			M_CH2_311 = 0;				// Chiusura (arretramento) visiera bassa 
			M_CH2_313 = 0;				// Chiusura (salita) visiera alta
			PLCM311_CH2 = 0;			// Chiusura (arretramento) visiera bassa
			PLCM313_CH2 = 0;			// Chiusura (salita) visiera alta
			break;

		case 61:
			M_CH2_61 = 1;				/* Chiusura riparo anteriore */
			M_CH2_311 = 1;				// Chiusura (arretramento) visiera bassa 
			M_CH2_313 = 1;				// Chiusura (salita) visiera alta
			M_CH2_60 = 0;				// Reset Apertura riparo anteriore
			M_CH2_310 = 0;				// Reset Apertura (avanzamento) visiera bassa
			M_CH2_312 = 0;				// Reset Apertura (discesa) visiera alta
			PLCM60_CH2 = 0;				// Reset Apertura riparo anteriore
			PLCM310_CH2 = 0;			// Reset Apertura (avanzamento) visiera bassa
			PLCM312_CH2 = 0;			// Reset Apertura (discesa) visiera alta
			break;

		case 62:
			break;

		case 63:
			break;

		case 64:
			M_CH2_64 = 1;                /* Abilitazione totale assi per riferimento */
			break;

		case 65:
			M_CH2_65 = 1;                /* Conferma assi riferiti */
			break;

		case 66:
			break;

		case 67:
			break;

		case 68:
			break;

		case 69:
			M_CH2_69 = 1;				// Reset Aree memoria Tastatura
			break;

		case 70:
			break;

		case 71:
			M_CH2_71 = 1;                /* Ciclo rotazione mandrino in corso */
			break;

		case 72:
			M_CH2_72 = 1;                /* Ciclo deposito utensile in corso */
			break;

		case 73:
			M_CH2_73 = 1;                /* Ciclo deposito utensile eseguito */
			break;

		case 74:
			M_CH2_74 = 1;                /* Ciclo prelievo utensile in corso */
			break;

		case 75:
			M_CH2_75 = 1;                /* Ciclo prelievo utensile eseguito */
			break;

		case 76:
			M_CH2_76 = 1;				/* Controllo possibilità deposito utensile */
			break;

		case 77:
			M_CH2_77 = 1;				/* Controllo possibilità prelievo utensile */
			break;

		case 78:
			M_CH2_78 = 1;				/* Carica i dati del cambio utensili in deposito */
			break;

		case 79:
			M_CH2_79 = 1;				/* Carica i dati del cambio utensili in prelievo */
			break;

		case 80:
			M_CH2_80 = 1;        /* Inizio ciclo di lavoro */
			break;

		case 81:
			M_CH2_81 = 1;        /* Attesa macchina pronta al lavoro */
			break;

		case 82:
			break;

		case 83:
			M_CH2_83 = 1;        /* Fine ciclo di lavoro */
			break;

		case 84:
			break;

		case 85:
			M_CH2_85 = 1;        /* Macchina fine lavoro */
			break;

		case 86:
			break;

		case 87:
			break;

		case 88:
			break;

		case 89:
			break;

		case 90:
			M_CH2_90 = 1;		/* Ritorno tavola in lavoro, indietro verso macchina */
			break;

		case 91:
			M_CH2_91 = 1;		/* Avanzamento tavola in carico, avanti verso operatore */
			break;

		case 92:
			break;

		case 93:
			break;

		case 94:
			break;

		case 95:
			break;

		case 96:
			break;

		case 97:
			break;

		case 98:
			M_CH2_98	= 1;		/* Ciclo di Movimentazione morse in manuale */
			break;

		case 99:
			M_CH2_99	= 1;		/* Fine Ciclo di Movimentazione morse in manuale */
			break;

		case 100:		/* Attesa ripristino per movimento da rieseguire */
			M_CH2_100 = 1;
			break;

		case 101:		/* Start Trasportatore Trucioli */
			M_CH2_101 = 1;
			break;

		case 102:		/* Stop Trasportatore Trucioli */
			M_CH2_102 = 1;
			break;

		case 103:	
			break;

		case 104:
			break;

		case 105:
			M_CH2_105 = 1;      // Verifica degli assi morse agganciati in gantry (FATM)
			break;

		case 106:
			M_CH2_106 = 1;      // MOVPIECE.CS4 in corso
			break;

		case 107:
			M_CH2_107 = 1;      // MOVPIECE.CS4 terminata
			break;

		case 108:
			M_CH2_108 = 1;      // Aggancio assi morse in gantry (FATM)
			break;

		case 109:
			M_CH2_109 = 1;      // Sgancio assi morse in gantry (FATM)
			break;

		case 110:
			M_CH2_110 = 1;       /* MORSE TRASC. ASSE X : Inizio ciclo controllo pos. morse dopo posizionamento */
			break;

		case 111:
			M_CH2_111 = 1;       /* MORSE TRASC. ASSE X : Fine ciclo controllo pos. morse dopo posizionamento */
			break;

		case 112:
			M_CH2_112 = 1;		/* TRASC.MORSE : Ciclo pos.trascinamento morse in corso (serve per ovviare l'allarme magazzino aperto in ciclo) */
			break;

		case 113:
			M_CH2_113 = 1;		/* TRASC.MORSE : FINE Ciclo pos.trascinamento morse in corso (serve per ovviare l'allarme magazzino aperto in ciclo) */
			break;

		case 114:
			M_CH2_114 = 1;		/* Ciclo cambio utensili assistito in corso */
			break;

		case 115:
			M_CH2_115 = 1;		/* Fine Ciclo cambio utensili assistito */
			break;

		case 116:				
			M_CH2_116 = 1;               /* Salita Battuta di carico SX1 */
			break;

		case 117:				
			M_CH2_117 = 1;               /* Discesa Battuta di carico SX1 */
			break;

		case 118:
			M_CH2_118 = 1;              /* Inizio ciclo marposs */
			break;

		case 119:
			M_CH2_119 = 1;              /* Fine ciclo marposs */
			break;

		case 120:
			M_CH2_120 = 1;              /* Verifica entità della tastatura: se maggiore della metà della corsa di tastatura dai allarme */
			break;

		case 121:				
			break;

		case 122:
			M_CH2_122 = 1;               /* Salita Battuta di carico DX4 */
			break;

		case 123:				
			M_CH2_123 = 1;               /* Discesa Battuta di carico DX4 */
			break;

		case 124:				/* Salita Battute di carico ZONA SX */
			M_CH2_116 = 1;
			break;

		case 125:				/* Discesa Battute di carico ZONA SX */
			M_CH2_117 = 1;
			break;

		case 126:				/* Salita Battute di carico ZONA DX */
			M_CH2_122 = 1;				
			break;

		case 127:				/* Discesa Battute di carico ZONA DX */
			M_CH2_123 = 1;				
			break;

		case 128:				/* Salita Battute di carico ZONA SX E ZONA DX */
			M_CH2_116 = 1;
			M_CH2_122 = 1;				
			break;

		case 129:				/* Discesa Battute di carico ZONA SX E ZONA DX */
			M_CH2_117 = 1;
			M_CH2_123 = 1;				
			break;

		case 130:				// Chiusura tutte le morse 
			M_CH2_134 = 1; M_CH2_234 = 0;
			M_CH2_135 = 1; M_CH2_235 = 0;
			M_CH2_136 = 1; M_CH2_236 = 0;
			M_CH2_137 = 1; M_CH2_237 = 0;
			M_CH2_138 = 1; M_CH2_238 = 0;
			M_CH2_139 = 1; M_CH2_239 = 0;
			break;

		case 131:
			break;

		case 132:
			break;

		case 133:
			break;

		case 134:
			M_CH2_134 = 1; M_CH2_234 = 0;				/* Chiusura morsa 10 */
			break;

		case 135:
			M_CH2_135= 1; M_CH2_235 = 0;				/* Chiusura morsa 11 */
			break;

		case 136:
			M_CH2_136 = 1; M_CH2_236 = 0;				/* Chiusura morsa 12 */
			break;

		case 137:
			M_CH2_137 = 1; M_CH2_237 = 0;				/* Chiusura morsa 13 */
			break;

		case 138:
			M_CH2_138 = 1; M_CH2_238 = 0;				/* Chiusura morsa 14 */
			break;

		case 139:
			M_CH2_139 = 1; M_CH2_239 = 0;				/* Chiusura morsa 15 */
			break;

		case 140:
			break;

		case 141:
			break;

		case 142:
			break;

		case 143:				// Chiusura tutte le morse SX
			M_CH2_134 = 1; M_CH2_234 = 0;
			M_CH2_135 = 1; M_CH2_235 = 0;
			M_CH2_136 = 1; M_CH2_236 = 0;
			break;

		case 144:				// Chiusura tutte le morse DX
			M_CH2_137 = 1; M_CH2_237 = 0;
			M_CH2_138 = 1; M_CH2_238 = 0;
			M_CH2_139 = 1; M_CH2_239 = 0;
			break;

		case 145: //Impegnato sul CH0 per chiusura morse indicizzata (non usare)
			break;

		case 146:	
			break;

		case 147:
			break;

		case 148:
			break;

		case 149:
			break;

		case 150:                        /* Impegnata su CH0: Funzione ausiliaria di comunicazione con l'applicativo del laser (FATM) */
			break;

		case 151:
			break;

		case 152:
			M_CH2_152 = 1;               /* MORSE MOT. : Ciclo ricerca morse in corso per conteggio e posiz.*/
			break;

		case 153:
			M_CH2_153 = 1;               /* MORSE MOT. : Fine ciclo ricerca morse per conteggio e posiz.*/
			break;

		case 154:
			M_CH2_154 = 1;				/* MORSE MOT. : Controllo la posizione morse prima del lavoro */
			break;

		case 155:
			break;

		case 156:			
			break;

		case 157:
			break;

		case 158:
			M_CH2_158 = 1;		/* MORSE MOT. e TRASC : Controllo posizione morse inviata da PC attivo */
			break;

		case 159:
			break;

		case 160:
			break;

		case 161:
			break;

		case 162:
			break;

		case 163:
			break;

		case 164:
			break;

		case 165:
			break;

		case 166:                       // Occupata su CR6
			break;

		case 167:                       // Occupata su CR6
			break;

		case 168:
			M_CH2_168 = 1;               // Avanti tavola no FATM
			break;

		case 169:
			break;

		case 170:
			break;

		case 171:				
			break;

		case 172:                       // Occupata su CR6
			break;

		case 173:                       // Occupata su CR6
			break;

		case 174:
			M_CH2_174 = 1;               // Spegne il tastatore
			break;

		case 175:
			M_CH2_175 = 1;               // Attesa FATM in figura CAM_PROB.CNC (aspetta che vada a zero l'ingresso di tastatore in battuta)
			break;

		case 176:
			M_CH2_176 = 1;				// TASTATORE ANCORA IN BATTUTA DOPO FINE TASTATA
			break;

		case 177:
			M_CH2_177 = 1;				// Controllo stato tastatore: FINE tastatore non premuto
			break;

		case 178:
			M_CH2_178 = 1;				// Controllo stato tastatore: INIZIO tastatore non premuto
			break;

		case 179:
			M_CH2_179 = 1;				// Controllo stato tastatore: tastatore premuto
			break;

		case 180:	/* SUPER-OTTIMIZZAZIONE : Muovi tutte le battute insieme */
			/* Battute alte o basse */
			if (( R[R_POSBAT_VERT_SX1]) && (R[R_SOLBAT_OPER])==(float) 0) M_CH2_116 = 1;
			if (!R[R_POSBAT_VERT_SX1]) M_CH2_117 = 1;
			if (( R[R_POSBAT_VERT_DX4]) && (R[R_SOLBAT_OPER])==(float) 0) M_CH2_122 = 1;
			if (!R[R_POSBAT_VERT_DX4]) M_CH2_123 = 1;
			break;


		case 181:
			break;

		case 182:
			break;


		case 183:				/* Super contemporaneità - Ripari Aperti e battute tutte in posizione */
			M_CH2_60 = 1;
			M_CH2_310 = 1;				// Apertura (avanzamento) visiera bassa
			M_CH2_312 = 1;				// Apertura (discesa) visiera alta

			/* ----- QUESTA PARTE DEVE ESSERE COPIATA DALLA M_CH2_180 ----- */
			/* Battute alte o basse */
			if (( R[R_POSBAT_VERT_SX1]) && (R[R_SOLBAT_OPER])==(float) 0) M_CH2_116 = 1;
			if (!R[R_POSBAT_VERT_SX1]) M_CH2_117 = 1;
			if (( R[R_POSBAT_VERT_DX4]) && (R[R_SOLBAT_OPER])==(float) 0) M_CH2_122 = 1;
			if (!R[R_POSBAT_VERT_DX4]) M_CH2_123 = 1;
			break;


		case 184:
			M_CH2_184 = 1;		    // Controllo stato tastatore: errore indice tastatura
			break;

		case 185:
			break;

		case 186:
			M_CH2_61 = 1;			/* Chiusura riparo */
			M_CH2_311 = 1;			// Chiusura (arretramento) visiera bassa
			M_CH2_313 = 1;			// Chiusura (salita) visiera alta
			break;

		case 187:
			break;

		case 188:
			break;

		case 189:
			break;

		case 190:				/* Apertura ripari anteriori */        
			M_CH2_60 = 1;
			M_CH2_310 = 1;				// Apertura (avanzamento) visiera bassa
			M_CH2_312 = 1;				// Apertura (discesa) visiera alta
			break;

		case 191:				/* Chiusura ripari anteriori */
			M_CH2_61 = 1;
			M_CH2_311 = 1;				// Chiusura (arretramento) visiera bassa
			M_CH2_313 = 1;				// Chiusura (salita) visiera alta
			break;

		case 192:
			break;

		case 193:				/* Chiusura ripari anteriori, tutte le battute basse*/
			M_CH2_61 = 1;				/* Chiusura riparo anteriore */
			M_CH2_311 = 1;				// Chiusura (arretramento) visiera bassa
			M_CH2_313 = 1;				// Chiusura (salita) visiera alta
			M_CH2_117 = 1;              /* Discesa Battuta di carico SX1 */
			M_CH2_123 = 1;              /* Discesa Battuta di carico DX4 */
			break;

		case 194:
			break;

		case 195:
			M_CH2_195 = 1;				/* Ciclo attualmente in corso */
			break;

		case 196:
			M_CH2_196 = 1;				/* Start conteggio tempo ciclo SX */
			break;

		case 197:
			M_CH2_197 = 1;				/* Start conteggio tempo ciclo DX */
			break;

		case 198:
			M_CH2_198 = 1;				/* Conferma ciclo in corso */
			break;

		case 199:
			break;

		case 200:
			M_CH2_200 = 1;				/* Abilita controllo riposizionamento morse */	
			break;

		case 201:
			M_CH2_201 = 1;		// Inserimento Trascinatore Morse su asse X
			M_CH2_56 = 1;		// Avanti micro Morse su asse X     
			break;

		case 202:
			M_CH2_202 = 1;		// Disinserimento Trascinatore Morse su asse X
			break;

		case 203:
			break;

		case 204:
			break;

		case 205:
			break;

		case 206:
			break;

		case 207:
			break;

		case 208:
			break;

		case 209:
			M_CH2_209 = 1;       // Carica tabella utensili da file
			break;

		case 210:                // Forza abilitazione delle morse del CH2 nella MOVPIECE
			{
				FORZA_ABIL_MORSA_10 = (Aris_CH2[R_RIC_ABIL_MORSA_10]>0.5);
				FORZA_ABIL_MORSA_11 = (Aris_CH2[R_RIC_ABIL_MORSA_11]>0.5);
				FORZA_ABIL_MORSA_12 = (Aris_CH2[R_RIC_ABIL_MORSA_12]>0.5);
				
				FORZA_ABIL_MORSA_13 = (Aris_CH2[R_RIC_ABIL_MORSA_13]>0.5);
				FORZA_ABIL_MORSA_14 = (Aris_CH2[R_RIC_ABIL_MORSA_14]>0.5);
				FORZA_ABIL_MORSA_15 = (Aris_CH2[R_RIC_ABIL_MORSA_15]>0.5);

				Aris_CH2[R_RIC_ABIL_MORSA_10] = 0;
				Aris_CH2[R_RIC_ABIL_MORSA_11] = 0;
				Aris_CH2[R_RIC_ABIL_MORSA_12] = 0;

				Aris_CH2[R_RIC_ABIL_MORSA_13] = 0;
				Aris_CH2[R_RIC_ABIL_MORSA_14] = 0;
				Aris_CH2[R_RIC_ABIL_MORSA_15] = 0;

				M_CH2_210 = 1;
			}
			break;

		case 211:                // Reset abilitazione delle morse del CH2 nella MOVPIECE
			{
				FORZA_ABIL_MORSA_10 = 0;
				FORZA_ABIL_MORSA_11 = 0;
				FORZA_ABIL_MORSA_12 = 0;
				
				FORZA_ABIL_MORSA_13 = 0;
				FORZA_ABIL_MORSA_14 = 0;
				FORZA_ABIL_MORSA_15 = 0;
			}
			break;

		case 212:
			break;

		case 213:
			break;

		case 214:
			break;

		case 215:
			break;

		case 216:
			break;

		case 217:
			break;

		case 218:
			break;

		case 219:
			break;

		case 220:
			break;

		case 221:
			break;

		case 222:
			break;

		case 223:
			break;

		case 224:
			break;

		case 225:
			break;

		case 226:
			M_CH2_226 = 1;		// Abilita mandrino per maschiatura rigida 
			break;

		case 227:
			M_CH2_227 = 1;		// Disabilita mandrino dopo maschiatura rigida 
			break;

		case 228:
			M_CH2_228 = 1;      // Check congruità posizioni assi morse
			break;

		case 229: //Impegnato sul CH0 per apertura morse indicizzata (non usare)
			break;

		case 230:		// Apertura tutte le morse 
			M_CH2_234 = 1; M_CH2_134 = 0; M_CH2_274 = 0; 
			M_CH2_235 = 1; M_CH2_135 = 0; M_CH2_275 = 0; 
			M_CH2_236 = 1; M_CH2_136 = 0; M_CH2_276 = 0; 

			M_CH2_237 = 1; M_CH2_137 = 0; M_CH2_277 = 0; 
			M_CH2_238 = 1; M_CH2_138 = 0; M_CH2_278 = 0; 
			M_CH2_239 = 1; M_CH2_139 = 0; M_CH2_279 = 0; 
			break;

		case 231:
			break;

		case 232:
			break;

		case 233:
			break;

		case 234:
			M_CH2_234 = 1; M_CH2_134 = 0; M_CH2_274 = 0; 				/* Apertura morsa 10 */
			break;

		case 235:
			M_CH2_235 = 1; M_CH2_135 = 0; M_CH2_275 = 0; 				/* Apertura morsa 11 */
			break;

		case 236:
			M_CH2_236 = 1; M_CH2_136 = 0; M_CH2_276 = 0; 				/* Apertura morsa 12 */
			break;

		case 237:
			M_CH2_237 = 1; M_CH2_137 = 0; M_CH2_277 = 0; 				/* Apertura morsa 13 */
			break;

		case 238:
			M_CH2_238 = 1; M_CH2_138 = 0; M_CH2_278 = 0; 				/* Apertura morsa 14 */
			break;

		case 239:
			M_CH2_239 = 1; M_CH2_139 = 0; M_CH2_279 = 0; 				/* Apertura morsa 15 */
			break;

		case 240:
			break;

		case 241:
			break;

		case 242:
			break;

		case 243:			// Apertura tutte le morse SX
			M_CH2_234 = 1; M_CH2_134 = 0; M_CH2_274 = 0; 
			M_CH2_235 = 1; M_CH2_135 = 0; M_CH2_275 = 0; 
			M_CH2_236 = 1; M_CH2_136 = 0; M_CH2_276 = 0; 
			break;

		case 244:			// Apertura tutte le morse DX
			M_CH2_237 = 1; M_CH2_137 = 0; M_CH2_277 = 0; 
			M_CH2_238 = 1; M_CH2_138 = 0; M_CH2_278 = 0; 
			M_CH2_239 = 1; M_CH2_139 = 0; M_CH2_279 = 0; 
			break;

		case 245:
			M_CH2_245 = 1;       /* MORSE : Ciclo ricerca morse in corso per conteggio e posiz.*/
			break;

		case 246:
			M_CH2_246 = 1;       /* MORSE : Fine ciclo ricerca morse per conteggio e posiz.*/
			break;

		case 247:
			M_CH2_247 = 1;       /* Ciclo pos. assi a riposo */
			break;

		case 248:
			M_CH2_248 = 1;       /* Fine ciclo pos. assi a riposo */
			break;

		case 249:
			M_CH2_249 = 1;       // Attesa sincronizzazione CN/Drill, usata in CKTOOL.SXT in gestione utensili avanzata
			break;

		case 250:
			M_CH2_250 = 1;       // Abilita allarme utensile non utilizzabile (gestione utensili avanzata)
			break;

		case 251:
			M_CH2_251 = 1;       // Attesa lettura parametri gestione utensili avanzata
			break;

		case 252:
			M_CH2_252 = 1;       // Verifica lista parametri in uso nell'isomg (verifica se utensili rotti e senza alias)
			break;

		case 253:
			M_CH2_253 = 1;       // Inizio scrittura file report
			break;

		case 254:
			M_CH2_254 = 1;       // Fine scrittura file report
			break;

		case 255:
			M_CH2_255 = 1;       //Disabilita filtri su assi X,Y,Z,A prima di maschiatura rigida (FATM)
			break;

		case 256:
			M_CH2_256 = 1;       //Abilita filtri su assi X,Y,Z,A dopo maschiatura rigida (FATM)
			break;

		case 257:
                       // Occupata su CR6
			break;

		case 258:
                       // Occupata su CR6
			break;

		case 259:
			break;
			/////////////////////////////////
		case 260:
			M_CH2_260 = 1;   //Disattiva correzioni asse A
			break;

		case 261:
			M_CH2_261 = 1;   //Attiva correzioni asse A
			break;

		case 262:
			M_CH2_262 = 1;   //Disattiva correzioni asse X
			break;

		case 263:
			M_CH2_263 = 1;   //Attiva correzioni asse X
			break;

		case 264:
			break;

		case 265:
			break;

		case 266:
			break;

		case 267:
			break;

		case 268:
			M_CH2_268 = 1;   //Disattiva correzioni asse C
			break;

		case 269:
			M_CH2_269 = 1;   //Attiva correzioni asse C
			break;
			/////////////////////////////////
		case 270: //Impegnato sul CH0 per chiusura morse in alta forza indicizzata (non usare)
			break;

		case 271:
			break;

		case 272:
			break;

		case 273:
			break;

		case 274:
			M_CH2_274 = 1; M_CH2_234 = 0; M_CH2_294 = 0;    //Attiva chiusura in alta forza morsa 10
			break;

		case 275:
			M_CH2_275 = 1; M_CH2_235 = 0; M_CH2_295 = 0;    //Attiva chiusura in alta forza morsa 11
			break;

		case 276:
			M_CH2_276 = 1; M_CH2_236 = 0; M_CH2_296 = 0;    //Attiva chiusura in alta forza morsa 12
			break;

		case 277:
			M_CH2_277 = 1; M_CH2_237 = 0; M_CH2_297 = 0;    //Attiva chiusura in alta forza morsa 13
			break;

		case 278:
			M_CH2_278 = 1; M_CH2_238 = 0; M_CH2_298 = 0;    //Attiva chiusura in alta forza morsa 14
			break;

		case 279:
			M_CH2_279 = 1; M_CH2_239 = 0; M_CH2_299 = 0;    //Attiva chiusura in alta forza morsa 15
			break;

		case 280:
			break;

		case 281:
			break;

		case 282:
			break;

		case 283:              // occupata su CR6
			break;

		case 284:              // occupata su CR6
			break;

		case 285:              // occupata su CR6
			break;

		case 286:
			break;

		case 287:
			break;

		case 288:			// occupata su CR6
			break;

		case 289:
			break;

		case 290: //Impegnato sul CH0 per disattivazione chiusura morse in alta forza indicizzata (non usare)
			break;

		case 291:
			break;

		case 292:
			break;

		case 293:
			break;

		case 294:
			M_CH2_294 = 1; M_CH2_274 = 0;              //DisAttiva chiusura in alta forza morsa 10
			break;

		case 295:
			M_CH2_295 = 1; M_CH2_275 = 0;              //DisAttiva chiusura in alta forza morsa 11
			break;

		case 296:
			M_CH2_296 = 1; M_CH2_276 = 0;              //DisAttiva chiusura in alta forza morsa 12
			break;

		case 297:
			M_CH2_297 = 1; M_CH2_277 = 0;              //DisAttiva chiusura in alta forza morsa 13
			break;

		case 298:
			M_CH2_298 = 1; M_CH2_278 = 0;              //DisAttiva chiusura in alta forza morsa 14
			break;

		case 299:
			M_CH2_299 = 1; M_CH2_279 = 0;              //DisAttiva chiusura in alta forza morsa 15
			break;

		case 300:
			break;

		case 301:
			break;

		case 302:
			break;

		case 303:
			M_CH2_303 = 1;                        // FATM: check posizione battute SX1 e DX4 in multipezzo 
			break;

		case 304:
			break;

		case 305:
			break;

		case 306:
			M_CH2_306 = 1;   //Disattiva correzioni asse Y
			break;

		case 307:
			M_CH2_307 = 1;   //Attiva correzioni asse Y		
			break;

		case 308:
			M_CH2_308 = 1;   //Disattiva correzioni asse Z		
			break;

		case 309:
			M_CH2_309 = 1;   //Attiva correzioni asse Z		
			break;
			/////////////////////////////////
		case 310:
			M_CH2_310 = 1;  //Avanzamento (apertura) visiera bassa
			break;

		case 311:
			M_CH2_311 = 1;  //Arretramento (chiusura) visiera bassa
			break;

		case 312:
			M_CH2_312 = 1;  //Discesa (apertura) visiera alta
			break;

		case 313:
			M_CH2_313 = 1;  //Salita (chiusura) visiera alta
			break;

		case 314:
			break;

		case 315:
			break;

		case 316:
			break;

		case 317:
			break;

		case 318: // occupata su CR6
			break;

		case 319:
			break;
			/////////////////////////////////
		case 320:				/* Sblocca tutte gli Zimmer morse */
			M_CH2_324 = 1;
			M_CH2_325 = 1;
			M_CH2_326 = 1;
			M_CH2_327 = 1;
			M_CH2_328 = 1;
			M_CH2_329 = 1;
			break;

		case 321:
			break;

		case 322:
			break;

		case 323:
			break;

		case 324:
			M_CH2_324 = 1;				/* Sbloccaggio Zimmer morsa 10 */
			break;

		case 325:
			M_CH2_325 = 1;				/* Sbloccaggio Zimmer morsa 11 */
			break;

		case 326:
			M_CH2_326 = 1;				/* Sbloccaggio Zimmer morsa 12 */
			break;

		case 327:
			M_CH2_327 = 1;				/* Sbloccaggio Zimmer morsa 13 */
			break;

		case 328:
			M_CH2_328 = 1;				/* Sbloccaggio Zimmer morsa 14 */
			break;

		case 329:
			M_CH2_329 = 1;				/* Sbloccaggio Zimmer morsa 15 */
			break;

		case 330:
			break;

		case 331:
			break;

		case 332:
			break;

		case 333:				/* Blocca tutte gli Zimmer morse */
			M_CH2_337 = 1;
			M_CH2_338 = 1;
			M_CH2_339 = 1;
			M_CH2_340 = 1;
			M_CH2_341 = 1;
			M_CH2_342 = 1;
			break;

		case 334:
			break;

		case 335:
			break;

		case 336:
			break;

		case 337:
			M_CH2_337 = 1;				/* Bloccaggio Zimmer morsa 10 */
			break;

		case 338:
			M_CH2_338 = 1;				/* Bloccaggio Zimmer morsa 11 */
			break;

		case 339:
			M_CH2_339 = 1;				/* Bloccaggio Zimmer morsa 12 */
			break;

		case 340:
			M_CH2_340 = 1;				/* Bloccaggio Zimmer morsa 13 */
			break;

		case 341:
			M_CH2_341 = 1;				/* Bloccaggio Zimmer morsa 14 */
			break;

		case 342:
			M_CH2_342 = 1;				/* Bloccaggio Zimmer morsa 15 */
			break;

		case 343:
			break;

		case 344:
			break;

		case 345:
			break;

		case 346:
			break;

		case 347:
			break;

		case 348:			// occupata su CR6
			break;

		case 349:			// occupata su CR6
			break;

		case 350:
			M_CH2_350 = 1;          //Richiesta sincronizzazione CNC livello 0
			break;

		case 351:
			M_CH2_351 = 1;          //Richiesta sincronizzazione CNC livello 1
			break;

		case 352:
			break;

		case 353:
			M_CH2_353 = 1;          // Disattivazione Abilitazione asse W
			break;

		case 354:
			break;

		case 355:
			break;

		case 356:
			break;

		case 357:
			M_CH2_357 = 1;          // Riattivazione Abilitazione asse W
			break;

		case 358:
			break;

		case 359:
			break;

		case 360:
			break;

		case 361:
			break;

		case 362:
			break;

		case 363:
			break;

		case 364:
			M_CH2_364 = 1;          // Ciclo di posizionamento morse con asse X in simulazione (serve a scrivere la posizione morsa mentre viene mossa dall'asse X)
			break;

		case 365:
			M_CH2_365 = 1;          // Fine ciclo di posizionamento morse con asse X in simulazione
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
