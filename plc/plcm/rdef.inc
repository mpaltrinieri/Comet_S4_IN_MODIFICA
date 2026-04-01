#ifndef R_INC_INCLUDED
#define R_INC_INCLUDED
/*

		---------------------------------------------
		TITOLO:         RDEF.INC
		---------------------------------------------
		MACCHINA:       EMMEGI COMET S4
		---------------------------------------------
		RELEASE:        CS4 0.0
		---------------------------------------------
		DATA:           22-01-2007
		---------------------------------------------
		AUTORE:         Soffritti Riccardo
		---------------------------------------------
		DESCRIZIONE:    Definizione parametri R
		---------------------------------------------
*/

extern double *R;
extern double *RR;

extern double *R_CH1;
extern double *RR_CH1;

extern double *R_CH2;
extern double *RR_CH2;

extern double *R_CH3;
extern double *RR_CH3;

// Parametri di conteggio tempo ciclo 
#define   R_0                    0  // Usato per simulatore 

#define   R_CYCLE_TIMESX         1  // Ultimo tempo di lavoro a SX 
#define   R_CYCLE_TIMEDX         2  // Ultimo tempo di lavoro a DX 

#define   R_VERSIONE_PLC         3  // Versione S/W PLC 
#define   R_VERSIONE_CNC         4  // Versione S/W CNC 
#define   R_VERSIONE_OSCNC       5  // Versione S/W sistema operativo CNC 

#define   R_NUMERO_RANDOM        8  // Time-X Morse : numero (200-550) generato casualmente 

#define   R_TYPE_HD_OS           9  // Versione supporto-sistema operativo Windows


// Parametri memorizzazione distanze micro-marca 
#define   R_DISTANZA_MICRO_X    10 // Distanza micro-marca asse X 
#define   R_DISTANZA_MICRO_Y    11 // Distanza micro-marca asse Y 
#define   R_DISTANZA_MICRO_Z    12 // Distanza micro-marca asse Z 
#define   R_DISTANZA_MICRO_A    13 // Distanza micro-marca asse A 
#define   R_DISTANZA_MICRO_W    14 // Distanza micro-marca asse W (ininfluente) 
////#define   R_DISTANZA_MICRO_P    15 // Distanza micro-marca asse P 
////#define   R_DISTANZA_MICRO_H    16 // Distanza micro-marca asse H 

// Parametri con il valore  della Micromarca iniziale degli assi : modificabile da CONFMAC 
#define   R_MICROMARCA_INI_X    20 // Valore iniziale micromarca di X (mm) 
#define   R_MICROMARCA_INI_Y    21 // Valore iniziale micromarca di Y (mm)  
#define   R_MICROMARCA_INI_Z    22 // Valore iniziale micromarca di Z (mm) 
#define   R_MICROMARCA_INI_A    23 // Valore iniziale micromarca di A (mm) 
////#define   R_MICROMARCA_INI_P    24 // Valore iniziale micromarca di P (mm) 
////#define   R_MICROMARCA_INI_H    25 // Valore iniziale micromarca di H (mm) 

#define   R_TOLL_MICROMAR_ASSI  29 // Tolleranza d'errore in % prima di generare l'allarme sugli assi 

// Differenza d'errore 
#define   R_DIFF_MICROMARCA_INI_X    30 // Differenza Misurata iniziale micromarca di X (mm) 
#define   R_DIFF_MICROMARCA_INI_Y    31 // Differenza Misurata iniziale micromarca di Y (mm)  
#define   R_DIFF_MICROMARCA_INI_Z    32 // Differenza Misurata iniziale micromarca di Z (mm) 
#define   R_DIFF_MICROMARCA_INI_A    33 // Differenza Misurata iniziale micromarca di A (mm) 
////#define   R_DIFF_MICROMARCA_INI_P    34 // Differenza Misurata iniziale micromarca di P (mm) 
////#define   R_DIFF_MICROMARCA_INI_H    35 // Differenza Misurata iniziale micromarca di H (mm) 

// Valore tollerato d'errore 
#define   R_PERC_TOLL_MICROMARCA_INI_X    36 // Percentuale d'errore tollerato in micromarca di X (mm) 
#define   R_PERC_TOLL_MICROMARCA_INI_Y    37 // Percentuale d'errore tollerato in micromarca di Y (mm)  
#define   R_PERC_TOLL_MICROMARCA_INI_Z    38 // Percentuale d'errore tollerato in micromarca di Z (mm) 
#define   R_PERC_TOLL_MICROMARCA_INI_A    39 // Percentuale d'errore tollerato in micromarca di A (mm) 
////#define   R_PERC_TOLL_MICROMARCA_INI_P    40 // Percentuale d'errore tollerato in micromarca di P (mm) 
////#define   R_PERC_TOLL_MICROMARCA_INI_H    41 // Percentuale d'errore tollerato in micromarca di H (mm) 


// Parametri permanenti di debug 
#define   R_DEBUG_ASSI          45 // Variabile R per debug assi_standard 
#define   R_DEBUG_COMPONENTI    46 // Variabile R per debug uscite_standard 
#define   R_DEBUG_UTENSILI		47 // Variabile R per debug utensili_standard 
#define   R_DEBUG_CICLO_ISO		48 // Parametro utilizzato per blocchi debug in ISO 
								   // =100 blocca con M00 dopo controlli cico WAIT_PH.CS4 in multipezzo 
								   // =101 blocca con M00 nei controlli dentro Rip_sx_x.CS4 
								   // =102 blocca con M00 nei controlli dentro Rip_dx_x.CS4 

#define   R_DEBUG_VELOC_CANOPEN	49 // Variabile R per VISUALIZZAZIONE velocità assi CANOPEN 

//#define   R_SPOSTA_ASSE_P       60  // Appoggio Sposta Asse P fuori ingombro 
//#define   R_SPOSTA_ASSE_H       61  // Appoggio Sposta Asse H fuori ingombro 

#define   R_ASSE_W_G91_SPOST    65  // W: spostamento in G91/G885/G887: spostamento relativo max che può compiere l'asse
#define   R_ASSE_W_G91_VEL      66  // W: spostamento in G91/G885/G887: velocità dello spostamento relativo
#define   R_ASSE_W_G91_TIPO_INT 67  // W: spostamento in G91/G885/G887: tipo di interruzione movimento:  1=G885(ritorna su micro)  2=G887(rilascia micro)

#define   R_APPO_POS_ASSE_W     68  // Appoggio Posizione ASSE W per controllo HOLD 

#define   R_ZERO_ASSI_SIM_X		70 // Zero simulato attivo dell'asse 0 
#define   R_ZERO_ASSI_SIM_Y		71 // Zero simulato attivo dell'asse 1 
#define   R_ZERO_ASSI_SIM_Z     72 // Zero simulato attivo dell'asse 2 
#define   R_ZERO_ASSI_SIM_B     73 // Zero simulato attivo dell'asse 3 
#define   R_ZERO_ASSI_SIM_C     74 // Zero simulato attivo dell'asse 4 
#define   R_ZERO_ASSI_SIM_W     75 // Zero simulato attivo dell'asse 5 
////#define   R_ZERO_ASSI_SIM_P		76 // Zero simulato attivo dell'asse 6 
////#define   R_ZERO_ASSI_SIM_H     77 // Zero simulato attivo dell'asse 7 
#define   R_ZERO_ASSI_SIM_AX8   78 // Zero simulato attivo dell'asse 8 
#define   R_ZERO_ASSI_SIM_AX9   79 // Zero simulato attivo dell'asse 9 
#define   R_ZERO_ASSI_SIM_AX10  80 // Zero simulato attivo dell'asse 10 
#define   R_ZERO_ASSI_SIM_AX11  81 // Zero simulato attivo dell'asse 11 


#define   R_ZERO_ASSI_SIM_V1    82 // Zero simulato attivo dell'asse 12 
#define   R_ZERO_ASSI_SIM_V2    83 // Zero simulato attivo dell'asse 13 
#define   R_ZERO_ASSI_SIM_V3    84 // Zero simulato attivo dell'asse 14 
#define   R_ZERO_ASSI_SIM_V4    85 // Zero simulato attivo dell'asse 15 
#define   R_ZERO_ASSI_SIM_V5    86 // Zero simulato attivo dell'asse 16 
#define   R_ZERO_ASSI_SIM_V6    87 // Zero simulato attivo dell'asse 17 
#define   R_ZERO_ASSI_SIM_V7    88 // Zero simulato attivo dell'asse 18 
#define   R_ZERO_ASSI_SIM_V8    89 // Zero simulato attivo dell'asse 19 
#define   R_ZERO_ASSI_SIM_V9    90 // Zero simulato attivo dell'asse 20 
#define   R_ZERO_ASSI_SIM_V10   91 // Zero simulato attivo dell'asse 21 
#define   R_ZERO_ASSI_SIM_V11   92 // Zero simulato attivo dell'asse 22 
#define   R_ZERO_ASSI_SIM_V12   93 // Zero simulato attivo dell'asse 23 


#define   R_TIPO_CN             98 // Tipo CN: 0=Spartaco;  1=Costantino; 3=Costantino 8.0

#define   R_TYPE_MACHINE        99 /* Tipo macchina:
											 0    = non definita
											 101  = Quadra Num -> Isac 
											 102  = Quadra2 Isac
											 103  = Quadra L1
											 104  = Quadra PVC V1
											 105  = Quadra PVC V2
											 106  = Quadra L2F
											 
											 201  = Planet
											 
											 301  = Satellite XT Statica
											 302  = Satellite XT Dinamica

											 311  = Satellite XT Evo Statica
											 312  = Satellite XT Evo Dinamica
											 
											 401  = Satellite XL

											 411  = Satellite XL Evo Statica
											 412  = Satellite XL Evo Dinamica
											 
											 501  = Diamant Statica
											 502  = Diamant Dinamica

											 511  = Diamant EVO Statica
											 512  = Diamant EVO Dinamica

											 601  = Comet Isola
											 602  = Comet E/M
											 603  = Comet E/P
											 
											 701  = Kelt
											 702  = Kelt2
											 
											 801  = Index
											 
											 901  = Comet T6 Morse Motorizzate
											 902  = Comet T6 H&P
											 903  = Comet T6 Base (statica)
											 904  = Comet T5 Morse Motorizzate
											 905  = Comet T5 H&P
											 906  = Comet T5 Base (statica)
											 907  = Comet T4 Morse Motorizzate
											 908  = Comet T4 Base
											 909  = Comet T3 Morse Motorizzate
											 910  = Comet T3 Base
											 
											 1001 = Phantomatic X6 H&P
											 1002 = Phantomatic X6 Statico
											 1003 = Phantomatic X6 Multipezzo
											 
											 1101 = Phantomatic X4
											 
											 1201 = Phantomatic M4
											 1202 = Phantomatic M3
											 1203 = TKE 938
											 
											 1301 = Phantomatic T3Star
											 1302 = Phantomatic T3S
											 1303 = Phantomatic T3A
											 1304 = Phantomatic T3
											 
											 1401 = Micromatic Star
											 1402 = Micromatic
											 
											 1501 = Phantomatic Isola T4Star
											 1502 = Phantomatic Isola T4A
											 
											 1601 = Phantomatic Isola T4
											 1602 = Phantomatic Isola T3
											 
											 1701 = Phantomatic 3400
											 1702 = Phantomatic 2400
											 
											 1801 = SuperVCut
											 
											 1901 = Vegamatic
											 1902 = Vegamatic Pusher T
											 1903 = Vegamatic Pusher T Automatica
											 
											 2001 = Fusion 4H
											 2002 = Fusion 4H EVO
											 2003 = Fusion Lite
											 2004 = Fusion 4HDS
											 
											 2101 = Trimmer 2A
											 2102 = Trimmer 4A
											 2103 = Trimmer 2A EVO
											 2104 = Trimmer 4A EVO
											 2105 = Trimmer Lite
											 
											 2201 = Qmatic 1
											 2202 = QMatic 2 

											 2301 = Phantomatic T5

											 3001 = Comet X4
											 3002 = Comet X4 Morse Motorizzate
											 
											 3101 = Comet X6 H&P
											 3102 = Comet X6 Statica
											 3103 = Comet X6 Morse Motorizzate

											 3201 = Comet R6 Morse Motorizzate
											 3202 = Comet R6 H&P
											 3203 = Comet R6 Statica

											 3211 = Comet R4 Morse Motorizzate
											 3210 = Comet R4 Base
											 
											 3301 = Comet S6 Morse Motorizzate
											 3302 = Comet S6 H&P
											 3303 = Comet S6 Statica

											 3311 = Comet S4 Morse Motorizzate
											 3310 = Comet S4 Base
											 */



// ---------------------------------------------------------------------------------
// ----------- ATTENZIONE AL PARAMETRO R111 Usato da ISAC nel riferimento ----------
// ---------------------------------------------------------------------------------


//*********************************************************************************
//********************* Parametri Comunicazione PC Nuova mappatura ****************
//*********************************************************************************

////#define   R_POSCARICO_AX_P_P1	120 // Quota_P per carico con battuta_P del pezzo 1 SX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_P_P2	121 // Quota_P per carico con battuta_P del pezzo 2 SX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_P_P3	122 // Quota_P per carico con battuta_P del pezzo 3 SX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_P_P4	123 // Quota_P per carico con battuta_P del pezzo 4 SX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_P_P5	124 // Quota_P per carico con battuta_P del pezzo 5 SX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_P_P6	125 // Quota_P per carico con battuta_P del pezzo 6 SX  (-1 se fissa, -2 se non usata)
////
////#define   R_POSCARICO_AX_H_P6	126 // Quota_H per carico con battuta_H del pezzo 6 DX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_H_P5	127 // Quota_H per carico con battuta_H del pezzo 5 DX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_H_P4	128 // Quota_H per carico con battuta_H del pezzo 4 DX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_H_P3	129 // Quota_H per carico con battuta_H del pezzo 3 DX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_H_P2	130 // Quota_H per carico con battuta_H del pezzo 2 DX  (-1 se fissa, -2 se non usata)
////#define   R_POSCARICO_AX_H_P1	131 // Quota_H per carico con battuta_H del pezzo 1 DX  (-1 se fissa, -2 se non usata)
////
////#define   R_NUM_PEZZI_CAR_SX	135 // Numero pezzi da caricare a SX
////#define   R_NUM_PEZZI_CAR_DX	136 // Numero pezzi da caricare a DX

////#define   R_APPOGGIO_PEZZI_SX	137 // Gestione a Bit - Indicazione se l'asse P Appoggia contro la testa/coda del pezzo
////									// Bit0 : pezzo 1 - ininfluente sempre su battuta fissa
////									// Bit1 : pezzo 2 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit2 : pezzo 3 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit3 : pezzo 4 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit4 : pezzo 5 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit5 : pezzo 6 - 0=appoggiato in testa 1=appoggiato in coda
////
////#define   R_APPOGGIO_PEZZI_DX	138 // Gestione a Bit - Indicazione se l'asse H Appoggia contro la testa/coda del pezzo
////									// Bit0 : pezzo 1 - ininfluente sempre su battuta fissa
////									// Bit1 : pezzo 2 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit2 : pezzo 3 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit3 : pezzo 4 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit4 : pezzo 5 - 0=appoggiato in testa 1=appoggiato in coda
////									// Bit5 : pezzo 6 - 0=appoggiato in testa 1=appoggiato in coda


////#define   R_GRUPPO_MORSE_AX_P1  140 // Morse associate in chiusura sul pezzo n.1 (SX) legato alla battuta mossa dall'asse P
////#define   R_GRUPPO_MORSE_AX_P2  141 // Morse associate in chiusura sul pezzo n.2 (SX) legato alla battuta mossa dall'asse P
////#define   R_GRUPPO_MORSE_AX_P3  142 // Morse associate in chiusura sul pezzo n.3 (SX) legato alla battuta mossa dall'asse P
////#define   R_GRUPPO_MORSE_AX_P4  143 // Morse associate in chiusura sul pezzo n.4 (SX) legato alla battuta mossa dall'asse P
////#define   R_GRUPPO_MORSE_AX_P5  144 // Morse associate in chiusura sul pezzo n.5 (SX) legato alla battuta mossa dall'asse P
////#define   R_GRUPPO_MORSE_AX_P6  145 // Morse associate in chiusura sul pezzo n.6 (SX) legato alla battuta mossa dall'asse P
////
////#define   R_GRUPPO_MORSE_AX_H6  146 // Morse associate in chiusura sul pezzo n.6 (DX) legato alla battuta mossa dall'asse H
////#define   R_GRUPPO_MORSE_AX_H5  147 // Morse associate in chiusura sul pezzo n.5 (DX) legato alla battuta mossa dall'asse H
////#define   R_GRUPPO_MORSE_AX_H4  148 // Morse associate in chiusura sul pezzo n.4 (DX) legato alla battuta mossa dall'asse H
////#define   R_GRUPPO_MORSE_AX_H3  149 // Morse associate in chiusura sul pezzo n.3 (DX) legato alla battuta mossa dall'asse H
////#define   R_GRUPPO_MORSE_AX_H2  150 // Morse associate in chiusura sul pezzo n.2 (DX) legato alla battuta mossa dall'asse H
////#define   R_GRUPPO_MORSE_AX_H1  151 // Morse associate in chiusura sul pezzo n.1 (DX) legato alla battuta mossa dall'asse H


#define   R_F_F_SPINDLE		   189    /* FEED FORWARD Spindle */


//*********************************************************************************
//************************* Parametri Definizione Lavorazioni *********************
//*********************************************************************************


#define   R200                 200  // lunghezza pezzo 
#define   R201                 201  // larghezza pezzo 
#define   R202                 202  // altezza pezzo 
#define   R203                 203  // faccia da lavorare 
#define   R_TESTINA_SU_MAND    204  // 0=utensile verticale, 1=testina montata


#define   R210                 210  // posizione lavorazione in X 
#define   R211                 211  // posizione lavorazione in Y 
#define   R212                 212  // posizione lavorazione in Z 
#define   R213                 213  // angolo asse A lavorazione
#define   R214                 214  // angolo asse C lavorazione

#define   R215                 215  /* Usato da POS_AXES.SAT: ipotenusa generata da C */
#define   R216                 216  /* Usato da POS_AXES.SAT: angolo generato asse A */
#define   R217                 217  /* Usato da POS_AXES.SAT: ipotenusa generata asse A */
#define   R218                 218  /* Usato da POS_AXES.SAT: raggio generato da asse A */
#define   R219                 219  /* Usato da POS_AXES.SAT: angolo generato asse C */


#define   R220                 220  // quota di posizionamento asse X 
#define   R221                 221  // quota di posizionamento asse Y 
#define   R222                 222  // quota di posizionamento asse Z 
#define   R223                 223  // quota di posizionamento asse A
#define   R224                 224  // quota di posizionamento asse C

#define   R230                 230  /* proiezione su asse Y del disimpegno di Camplus dal centro figura (in base all'angolo asse A, calcolata analogam alla proiezione di R619) */

#define   R240                 240  // quota di fuori ingombro per asse Z 

#define   R241                 241  // 0 = rotazione oraria mandrino; 1 = rotazione antioraria 
									// 0 = maschiatura destrorsa; 1 = maschiatura sinistrorsa 

#define   R242                 242  // n° giri mandrino 

#define   R250                 250  // 0=piano/ut.diversi 
									// 1=scavalca morse 
									// 2=vai in disimpegno 
									// 3=nessun spostamento in Z 

#define   R251                 251  // quota asse Z per scavalcamento morse 

#define   R_XOUT               252  // quota asse X ottimizzata per fuori ingombro 
#define   R_YOUT               253  // quota asse Y ottimizzata per fuori ingombro 
#define   R_ZOUT               254  // quota asse Z ottimizzata per fuori ingombro 

#define   R_ZOUT_CALCOLATO     255  // quota asse Z calcolata : visualizzata per controlli
#define   R_ZOUT_TESTINA       256  // quota asse Z ottimizzata per fuori ingombro con testina
#define   R_ZOUT_TEST_CALC     257  // quota asse Z ottimizzata per fuori ingombro con testina : solo visualizzata per controlli 

#define   R_LASTFACE           260  // Ultima faccia lavorata : solo per ricalcoli testina 

#define   R_265                265  /* usato in CALCXYZ */
#define   R_266                266  /* usato in CALCXYZ */
#define   R_267                267  /* usato in CALCXYZ */
#define   R_268                268  /* usato in CALCXYZ */
#define   R_269                269  /* usato in CALCXYZ */

//**********************************************************************
//**************** Parametri correzioni pezzi da tastatore  ************
//**********************************************************************
#define   R_CORR_PEZZO01_X     270    // Parametro correzione pezzo 
#define   R_CORR_PEZZO01_Y     271    // Parametro correzione pezzo 
#define   R_CORR_PEZZO01_Z     272    // Parametro correzione pezzo 
#define   R_CORR_PEZZO02_X     273    // Parametro correzione pezzo 
#define   R_CORR_PEZZO02_Y     274    // Parametro correzione pezzo 
#define   R_CORR_PEZZO02_Z     275    // Parametro correzione pezzo 
#define   R_CORR_PEZZO03_X     276    // Parametro correzione pezzo 
#define   R_CORR_PEZZO03_Y     277    // Parametro correzione pezzo 
#define   R_CORR_PEZZO03_Z     278    // Parametro correzione pezzo 
#define   R_CORR_PEZZO04_X     279    // Parametro correzione pezzo 
#define   R_CORR_PEZZO04_Y     280    // Parametro correzione pezzo 
#define   R_CORR_PEZZO04_Z     281    // Parametro correzione pezzo 
#define   R_CORR_PEZZO05_X     282    // Parametro correzione pezzo 
#define   R_CORR_PEZZO05_Y     283    // Parametro correzione pezzo 
#define   R_CORR_PEZZO05_Z     284    // Parametro correzione pezzo 
#define   R_CORR_PEZZO06_X     285    // Parametro correzione pezzo 
#define   R_CORR_PEZZO06_Y     286    // Parametro correzione pezzo 
#define   R_CORR_PEZZO06_Z     287    // Parametro correzione pezzo 
#define   R_CORR_PEZZO07_X     288    // Parametro correzione pezzo 
#define   R_CORR_PEZZO07_Y     289    // Parametro correzione pezzo 
#define   R_CORR_PEZZO07_Z     290    // Parametro correzione pezzo 
#define   R_CORR_PEZZO08_X     291    // Parametro correzione pezzo 
#define   R_CORR_PEZZO08_Y     292    // Parametro correzione pezzo 
#define   R_CORR_PEZZO08_Z     293    // Parametro correzione pezzo 
#define   R_CORR_PEZZO09_X     294    // Parametro correzione pezzo 
#define   R_CORR_PEZZO09_Y     295    // Parametro correzione pezzo 
#define   R_CORR_PEZZO09_Z     296    // Parametro correzione pezzo 
#define   R_CORR_PEZZO10_X     297    // Parametro correzione pezzo 
#define   R_CORR_PEZZO10_Y     298    // Parametro correzione pezzo 
#define   R_CORR_PEZZO10_Z     299    // Parametro correzione pezzo 



//***********************************************************************************
//******************* Parametri di definizione figure da eseguire *******************
//***********************************************************************************

#define   R300                 300  // diametro foro 
                                    // lunghezza tasca 
                                    // lunghezza asola 
                                    // lunghezza testa di morto 
                                    // lunghezza scarico 
                                    // lunghezza trilatero 
                                    // raggio interno arco 
                                    // lunghezza intestatura lama 
                                    // diametro foro da maschiare 
#define   R301                 301  // nø eliche foro 
                                    // larghezza tasca 
                                    // larghezza asola 
                                    // diametro maggiore testa di morto 
                                    // larghezza scarico 
                                    // larghezza trilatero 
                                    // angolo estensione arco 
                                    // larghezza intestatura lama 
#define   R302                 302  // raggio raccordo tasca 
                                    // diametro minore testa di morto 
                                    // raggio raccordo trilatero 
                                    // larghezza arco 
#define   R309                 309  // angolo rotazione figura 
#define   R310                 310  // velocità di sfondamento utensile (mm/min) 
#define   R311                 311  // velocità di lavorazione utensile (mm/min) 
#define   R320                 320  // 0=normale 1=svuotamento 
#define   R321                 321  // 0=normale 1=elicoidale 
#define   R322                 322  // 0=orario  1=antiorario 
#define   R323                 323  // 0=normale 1=veloce 
#define   R324                 324  // Numero di passate per sfondamento multiplo 
#define   R330                 330  // quota di fuori ingombro per asse Z 
#define   R331                 331  // quota di fuori approccio per asse Z 
#define   R332                 332  // quota di fuori fine lavoro per asse Z 

#define   R333                 333  // quota di fuori ingombro per asse Y 
#define   R334                 334  // quota di fuori approccio per asse Y 
#define   R_QUOTA_SCAV_LATER_Y 335  // per Testina : quota di scavalcamento laterale profilo a testina orientata.

//	Tastatura su 3punti:               TASTATURA:                       | LAVORAZIONE:
#define   R_ID_GRUPPO_TAST     336  // Indice Gruppo tastate (1->79)	| Indice Gruppo tastate (1->79)
#define   R_ID_TAST            337  // Indice Tastata (1->3)			| 0=Traslazione  1=RotoTraslazione
#define   R_ANGOLO_TAST        338  // Angolo al vertice delle 3 tastate (interno al profilo)

/* Gestione modulo CAMPlus per tastatura */
#define   R_ID_TAST_X          340  // Indice per correzione coord.X; valori da 1 a 99 
#define   R_ID_TAST_Y          341  // Indice per correzione coord.Y; valori da 1 a 99
#define   R_ID_TAST_Z          342  // Indice per correzione coord.Z; valori da 1 a 99
#define   R_MAX_TAST           343  // Ampiezza tastatura(configurabile da Drill) 

//**********************************************************************
//****************** Altri dati di Gestione Assi  **********************
//**********************************************************************

#define   R_FCPOS_X			   345	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_X			   346	 // Quota di finecorsa negativo dell'asse

#define   R_FCPOS_Y			   347	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_Y			   348	 // Quota di finecorsa negativo dell'asse

#define   R_FCPOS_Z			   349	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_Z			   350	 // Quota di finecorsa negativo dell'asse

#define   R_FCPOS_A			   351	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_A			   352	 // Quota di finecorsa negativo dell'asse

#define   R_FCPOS_C			   353	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_C			   354	 // Quota di finecorsa negativo dell'asse

// -----------------------------------------------------------------------------
////#define   R_FCPOS_M07		   355	 // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_M07		   356	 // Quota di finecorsa negativo dell'asse
////#define   R_FCPOS_M08		   357	 // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_M08		   358	 // Quota di finecorsa negativo dell'asse
////#define   R_FCPOS_M09		   359	 // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_M09		   360	 // Quota di finecorsa negativo dell'asse
#define   R_FCPOS_M10		   361	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_M10		   362	 // Quota di finecorsa negativo dell'asse
#define   R_FCPOS_M11		   363	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_M11		   364	 // Quota di finecorsa negativo dell'asse
#define   R_FCPOS_M12		   365	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_M12		   366	 // Quota di finecorsa negativo dell'asse
// -----------------------------------------------------------------------------
#define   R_FCPOS_M13		   367	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_M13		   368	 // Quota di finecorsa negativo dell'asse
#define   R_FCPOS_M14		   369	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_M14		   370	 // Quota di finecorsa negativo dell'asse
#define   R_FCPOS_M15		   371	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_M15		   372	 // Quota di finecorsa negativo dell'asse
////#define   R_FCPOS_M16		   373	 // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_M16		   374	 // Quota di finecorsa negativo dell'asse
////#define   R_FCPOS_M17		   375	 // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_M17		   376	 // Quota di finecorsa negativo dell'asse
////#define   R_FCPOS_M18		   377	 // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_M18		   378	 // Quota di finecorsa negativo dell'asse
// -----------------------------------------------------------------------------

////#define   R_FCPOS_P			   379   // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_P			   380	 // Quota di finecorsa negativo dell'asse
////#define   R_FCPOS_H			   381	 // Quota di finecorsa positivo dell'asse
////#define   R_FCNEG_H			   382	 // Quota di finecorsa negativo dell'asse



////#define   R_PRIMO_POS_PEND	   383    // Primo posizionamento in pendolare eseguito : evita movimenti inutili 

#define   R_MORSE_RIPOS_GIRO1  384    // Appoggio da calcolo PLC : morse da chiudere al primo giro 
#define   R_MORSE_RIPOS_GIRO2  385    // Appoggio da calcolo PLC : morse da chiudere al secondo giro 

#define   R_NUMERO_BATTUTE	   386    // Calcolo il numero di battute presenti : serve anche per l'iso 
////#define   R_NUMERO_BATTUTE_SX  387    // Calcolo il numero di battute SX presenti : serve anche per l'iso 
////#define   R_NUMERO_BATTUTE_DX  388    // Calcolo il numero di battute SX presenti : serve anche per l'iso 

////#define   R_RIP_MOV			   389	  // Flag necessità ripetizione movimento interrotto 

////#define   R_ECCEZIONE_MULTI_SX 390	  // Flag eccezione partenza multiprocesso SX 
////#define   R_ECCEZIONE_MULTI_DX 391	  // Flag eccezione partenza multiprocesso DX 

#define   R_FCPOS_W			   392	 // Quota di finecorsa positivo dell'asse
#define   R_FCNEG_W			   393	 // Quota di finecorsa negativo dell'asse

#define   R_ORE_LAVORATE       398    /* numero ore lavorate senza aver ancor effettuato l'ingrassaggio automatico */
#define   R_CICLI_INGR_NOK     399    /* Numero di volte che l'ingrassaggio automatico ha fallito */

//**********************************************************************
//***************** Parametri usati in modo immediato ******************
//**********************************************************************
//******** Non usare i parametri R400-R404 : riservati alla MOVMORS.CS4 

#define   R_IMM_0              400    // Parametro di utilizzo immediato 
#define   R_IMM_1              401    // Parametro di utilizzo immediato 
#define   R_IMM_2              402    // Parametro di utilizzo immediato 
#define   R_IMM_3              403    // Parametro di utilizzo immediato 
#define   R_IMM_4              404    // Parametro di utilizzo immediato 
#define   R_IMM_5              405    // Parametro di utilizzo immediato 
#define   R_IMM_6              406    // Parametro di utilizzo immediato 
#define   R_IMM_7              407    // Parametro di utilizzo immediato 
#define   R_IMM_8              408    // Parametro di utilizzo immediato 
#define   R_IMM_9              409    // Parametro di utilizzo immediato 
#define   R_IMM_10             410    // Parametro di utilizzo immediato 
#define   R_IMM_11             411    // Parametro di utilizzo immediato 
#define   R_IMM_12             412    // Parametro di utilizzo immediato 
#define   R_IMM_13             413    // Parametro di utilizzo immediato 
#define   R_IMM_14             414    // Parametro di utilizzo immediato 
#define   R_IMM_15             415    // Parametro di utilizzo immediato 
#define   R_IMM_16             416    // Parametro di utilizzo immediato 
#define   R_IMM_17             417    // Parametro di utilizzo immediato 
#define   R_IMM_18             418    // Parametro di utilizzo immediato 
#define   R_IMM_19             419    // Parametro di utilizzo immediato 

// Codici di ALLARME. Impostati da PLC e letti da PC 
#define   ALARM_FIRST_R        420  // Prima R riservata per lista allarmi
#define   R_ALL_0              420  // Codice allarme 1 da visualizzare 
#define   R_ALL_1              421  // Codice allarme 2 da visualizzare 
#define   R_ALL_2              422  // Codice allarme 3 da visualizzare 
#define   R_ALL_3              423  // Codice allarme 4 da visualizzare 
#define   R_ALL_4              424  // Codice allarme 5 da visualizzare 
#define   R_ALL_5              425  // Codice allarme 6 da visualizzare 
#define   R_ALL_6              426  // Codice allarme 7 da visualizzare 
#define   R_ALL_7              427  // Codice allarme 8 da visualizzare 
#define   R_ALL_8              428  // Codice allarme 9 da visualizzare 
#define   R_ALL_9              429  // Codice allarme 10 da visualizzare 
#define   ALARM_LAST_R         429  // Ultima R riservata per lista allarmi


// Codici dei MESSAGGI. Impostati da PLC e letti da PC 
#define   MESSAGE_FIRST_R      430  // Prima R riservata per lista messaggi
#define   R_MES_0              430  // Codice messaggio 1 da visualizzare 
#define   R_MES_1              431  // Codice messaggio 2 da visualizzare 
#define   R_MES_2              432  // Codice messaggio 3 da visualizzare 
#define   R_MES_3              433  // Codice messaggio 4 da visualizzare 
#define   R_MES_4              434  // Codice messaggio 5 da visualizzare 
#define   MESSAGE_LAST_R       434  // Ultima R riservata per lista messaggi


// ----------------- Simulazione F.C. Zero ------------------ 
#define   R_FC0_X			   435    // FC0 dell'asse indicato 
#define   R_FC0_Y			   436    // FC0 dell'asse indicato 
#define   R_FC0_Z			   437    // FC0 dell'asse indicato 
#define   R_FC0_A			   438    // FC0 dell'asse indicato 
#define   R_FC0_W			   439    // FC0 dell'asse indicato 


// Parametri correzioni con Sonda 
#define   R_CORR_PROBEX        440    // Correzione da Probe in X 
#define   R_CORR_PROBEY        441    // Correzione da Probe in Y 
#define   R_CORR_PROBEZ        442    // Correzione da Probe in Z 
#define   R_APP_TESTPROBE      443    // Appoggio test probe 




// Parametri di stato macchina. Impostati da PLC e letti da PC 
#define   R_STATUS             450  // Stato macchina
                                    // 0   = Automatico
                                    // 1   = Manuale
                                    // 255 = Stato indefinito 

#define   R_HOLD               451  // Stato HOLD.
                                    // 0   = Ok
                                    // 1   = Hold
                                    // L'indicazione di HOLD viene tolta solo
                                    // dopo che e' stato dato START 

#define   R_CYCLE              452  // CICLO
                                    // 0   = No ciclo
                                    // 1   = Ciclo in corso
                                    // Durante lo stato di HOLD il "ciclo"
                                    // viene tolto 

#define   R_RIFERIM            453  // Flag Assi Riferiti
                                    // 0   = Assi non Riferiti
                                    // 1   = Assi Riferiti 

#define   R_NO_EXIT            454  // Flag Inibizione Uscita da Blade e
                                    // WINDOWS
                                    // 0   = Uscita consentita
                                    // 1   = Uscita Inibita 

#define   R_APPSEL             455  // Appoggio selezione funzione manuale da PC 
#define   R_FUNZESEG_A         456  // Funzione A eseguita 
#define   R_FUNZESEG_B         457  // Funzione B eseguita 

#define   R_CONTAORE           458  // Flag per conteggio tempo di utilizzo macchina 

#define   R_SIMU               459  // Modo simulatore 

#define   R_STOP_PROG		   460  // Il Plc lo setta quando l'operatore interrompe
									// l'esecuzione del programma.
									// Il PC resetta R_START e visualizza "message box" 
////#define   R_MACHINE_SX         461  // Macchina a SX e diaframma chiuso per start ciclo pendolare 
////#define   R_MACHINE_DX         462  // Macchina a DX e diaframma chiuso per start ciclo pendolare 
#define   R_ROT_PIECE          463  // Rotazione pezzo in corso (1=sx, 2=dx) 
#define   R_PROG_RUNNING       464  // Programma in corso (a 0 può essere caricato in memoria il programma successivo) 

#define   R_PROG_FINITO		   465  // Programma finito, copia di M02 per il PC (che la resetta) 

#define   R_TIME_MANUT_TESTINA 466  // Abilita conteggio tempo per manutenzione testina
#define   R_LAMP_ALLARMI       467  // Spia allarmi presenti da visualizzare in Drill
#define   R_LAMP_AUX           468  // Lampada ausiliari per Drill
#define   R_LAMP_START         469  // Lampada start per Drill

// Parametri di stato macchina. Impostati da PC e letti da PLC 
#define   R_START              470  // Abilitazione start ciclo
                                    // 0   = Start inibito
                                    // 1   = Start abilitato 
#define   R_INIB_MOV           471  // Inibizione movimenti manuali
                                    // 0   = Movimenti abilitati
                                    // 1   = Movimenti disabilitati 
#define   R_SEL                472  // Selezione funzione manuale da PC 
#define   R_CK_START           473  // Controllo sicurezza start 

#define   R_DRILL_AUX          474  /* Pulsante inserzione ausiliari da drill */
#define   R_BUTTON_A           475  /* Pulsante A    (ricevuto da Drill se manca l'Mgpilot) */
#define   R_BUTTON_B           476  /* Pulsante B    (ricevuto da Drill se manca l'Mgpilot) */
#define   R_POTENZIOMETRO      477  /* Potenziometro (ricevuto da Drill se manca l'Mgpilot) */
#define   R_DRILL_HOLD         478  /* Pulsante HOLD (ricevuto da Drill) */
#define   R_DRILL_START        479  /* Pulsante richiesta start da drill */

// Parametri con cui il PC richiede che il PLC compia un'azione. Vengono
// settati dal PC e resettati dal PLC non appena l'azione e' stata compiuta
// o non ha piu' senso 
#define   R_SEND_START         480  // Richiesta di uno START CICLO
                                    // Il PLC deve resettarla dopo aver inviato
                                    // uno START o nel caso ci sia uno stato di
                                    // HOLD o RESET 

#define   R_SEND_RESET         481  // Richiesta di un RESET
                                    // Il PLC deve resettarla dopo aver inviato
                                    // un RESET 

#define   R_ATTESA_CONFERMA    482  // Attesa Conferma Operatore.
									// Il PLC deve resettarlo ogni volta che
									// l'operatore esegue un'operazione di
									// conferma su una qualunque delle 2 zone 

////#define   R_POSMOR_SX          483  // Attesa posizionamento morse e battute a SX in pendolare
////									// Il PLC deve resettarlo a posizionamento avvenuto 
////
////#define   R_CARPEZ_SX          484  // Attesa caricamento pezzo a SX in pendolare
////									// Il PLC deve resettarlo a caricamento avvenuto 
////
////#define   R_POSMOR_DX          485  // Attesa posizionamento morse e battute a DX in pendolare
////									// Il PLC deve resettarlo a posizionamento avvenuto 
////
////#define   R_CARPEZ_DX          486  // Attesa caricamento pezzo a DX in pendolare
////									// Il PLC deve resettarlo a caricamento avvenuto 
////
////#define   R_SCARPEZ_SX         487  // Attesa scaricamento pezzo a SX in pendolare
////									// Il PLC deve resettarlo a scarico avvenuto 
////
////#define   R_SCARPEZ_DX         488  // Attesa scaricamento pezzo a DX in pendolare
////									// Il PLC deve resettarlo a scarico avvenuto 

#define   R_CLOSE_CYCLE        489  // Comando da PC di fine lista
									// Il PLC deve resettarlo a scarico avvenuto 

#define   R_RESET_ALL          490  // Richiesta reset allarmi 

#define   R_ERGO_SEND_START    493  // Richiesta di uno START CICLO in modo ERGONOMICO
                                    // Il PLC deve resettarla dopo aver inviato
                                    // uno START o nel caso ci sia uno stato di
                                    // HOLD o RESET 

#define   R_APPO_SENSO_ROT     495  // Appoggio Senso di Rotazione Mandrino per guadagno tempo M03/M04 
#define   R_APPO_VEL_ROT	   496  // Appoggio Velocità di Rotazione Mandrino per guadagno tempo M03/M04 


//*********************************************************************************
//**************************** Parametri inviati da PC ****************************
//*********************************************************************************
//******************************** Da R500 a R599 *********************************
//*********************************************************************************

#define   R_FREQ_LUBRICA       500  // Frequenza lubrificazione lubrica (valore di Hdrill/Camplus)

#define   R_MAX_HEIGHT         501  // Max altezza profilo o morse 

#define   R_USA_REFSPEC        502  // Richiesta di utilizzo refrigerante speciale: Vortex

#define   R_SPESS_DISCO        503  // lunghezza tagliente utensile in uso 

#define   R_TIPO_LUBRICA	   504  // Lubriche attive:
									// Bit 0 = lubrica n.1 (sx)         (testina:successiva in senso orario)
									// Bit 1 = lubrica n.2 (anteriore)  (testina:successiva in senso orario)
									// Bit 2 = lubrica n.3 (dx)         (testina:successiva in senso orario)
									// Bit 3 = lubrica n.4 (posteriore) (testina:successiva in senso orario)
									// Bit 4 = lubrica n.5/6 (centrali)

#define   R_END_SX		       505  // Causale di fine lavoro ZONA sx 
									// 0 = apertura morse 
									// 1 = attesa carico pezzo 
									// 2 = attesa scarico pezzo 
									// 3 = solo attesa CONFERMA carico pezzo 
                                    // 5 = scarico pezzi finiti della barra


#define   R_CECKMORS_OPER      506  // Controllo morse da operatore 

#define   R_LENGTH_NEXTOOL     507  // Lunghezza utensile successivo 
#define   R_RADIUS_NEXTOOL     508  // Raggio utensile successivo 

#define   R_GESTMORS_OPER      509  // Gestione morse da operatore 

////#define   R_POS_MORS_SX_DX     510  // 0=posiziona morse a SX e DX (Comet_T6/5 solo asse X)
////									// 1=posiziona morse a SX      (   "         "     "  )
////									// 2=posiziona morse a DX      (   "         "     "  )

#define   R_FORZA_CHECKMORS    512  // Forza controllo morse da scelta operatore 

#define   R_ERGONOMICO		   513  // Modalità ergonomico rapida attiva 
#define   R_ERGO_PLS_PREMUTO   514  // Memoria Pulsante Premuto in Ergonomico 

#define   R_END_DX             515  // Causale di fine lavoro ZONA dx 
									// 0 = apertura morse 
									// 1 = attesa carico pezzo 
									// 2 = attesa scarico pezzo 
									// 3 = solo attesa CONFERMA carico pezzo 
                                    // 5 = scarico pezzi finiti della barra

#define   R_USA_REF_SERB2      516  // (PREDISPOSTO) Richiesta di utilizzo refrigerante speciale: secondo serbatoio lubrica

#define   R_CONFERMA_DIRETTA   517  // Permette di far partire il ciclo in Ergonomico con la pressione istantanea per carichi oltremisura o rotazione pezzi 


////#define   R_ASP_CONF_BATT_P    518 // Attender conferma di scarico pezzo prima di abbassare la battuta dell'asse P (zona SX)
////#define   R_ASP_CONF_BATT_H    519 // Attender conferma di scarico pezzo prima di abbassare la battuta dell'asse H (zona DX)

#define   R_NO_AP_MORSE        520  /* 1 => Non aprire le morse a inizio e fine ciclo (parametro profilo) */

////#define   R_RIPOS_MORSE_SX     521 // Riposizionamento Morse a SX in pendolare (1= su pezzi non separati, 2= dopo tagli di separazione)
////#define   R_RIPOS_MORSE_DX     522 // Riposizionamento Morse a DX in pendolare (1= su pezzi non separati, 2= dopo tagli di separazione)

									
#define   R_INTERAX_MORSE_SX   523  // Interasse morse 
////#define   R_INTERAX_MORSE_DX   524  // Interasse morse 									

////#define   R_NUM_MORSE_SX	   525  // Numero morse SX
////#define   R_NUM_MORSE_DX	   526  // Numero morse DX

////#define   R_ZONA_LAVORO		   527	// Indica la zona dove si sta per lavorare 
////									// 0=multipezzo(zona non imp.) 
////									// 1=pendolare a sx 
////									// 2=pendolare a dx 

#define   R_HDRILL_GRUPPO_MORSE_SX1   528  // Morse associate in chiusura alla battuta SX1 da Hdrill
//// #define   R_HDRILL_GRUPPO_MORSE_SX2   529  // Morse associate in chiusura alla battuta SX2 da Hdrill
//// #define   R_HDRILL_GRUPPO_MORSE_DX3   530  // Morse associate in chiusura alla battuta DX3 da Hdrill
#define   R_HDRILL_GRUPPO_MORSE_DX4   531  // Morse associate in chiusura alla battuta DX4 da Hdrill

#define   R_NUM_MORSE          532  // Numero morse 

#define   R_RIPOS_MORSE_MULTI  533  // Riposizionamento Morse con Pezzo sopra in multipezzo (1= su pezzi non separati, 2= dopo tagli di separazione) 


#define   R_ROTAZ_MULTI		   534  // Rotazione in multipezzo (evita l'apertura morse) 


#define   R_POS_TAVOLA_SX		535	// Posizione fisica della tavola:  0=macchina  1=operatore  2=non usata in single(quando zona sx non usata)
//#define   R_POS_TAVOLA_DX		536	// Posizione fisica della tavola:  0=macchina  1=operatore  2=non usata in single(quando zona dx non usata)

#define   R_SELECT_MARPOSS		537  // Selezione Marposs: 1=X, 2=Y, 3=Z 
#define   R_CORREZ_MARPOSS		538  // Abilitazione correzione marposs 
#define   R_NUM_PEZZO			539  // Numero pezzo da correggere (max 10) 


// -----------------------------------------------------------------------------
////#define   R_POSMORS1_PC        540    // Posizione morsa 07 da PC 
////#define   R_POSMORS2_PC        541    // Posizione morsa 08 da PC 
////#define   R_POSMORS3_PC        542    // Posizione morsa 09 da PC 
// -----------------------------------------------------------------------------
#define   R_POSMORS4_PC        543    // Posizione morsa 10 da PC (opz)
#define   R_POSMORS5_PC        544    // Posizione morsa 11 da PC 
#define   R_POSMORS6_PC        545    // Posizione morsa 12 da PC 
#define   R_POSMORS7_PC        546    // Posizione morsa 13 da PC 
#define   R_POSMORS8_PC        547    // Posizione morsa 14 da PC 
#define   R_POSMORS9_PC        548    // Posizione morsa 15 da PC (opz)
// -----------------------------------------------------------------------------
////#define   R_POSMORS10_PC       549    // Posizione morsa 16 da PC 
////#define   R_POSMORS11_PC       550    // Posizione morsa 17 da PC 
////#define   R_POSMORS12_PC       551    // Posizione morsa 18 da PC 
// -----------------------------------------------------------------------------



#define   R_SPOSTA_BATTUTE_SX  552    // Bit 0 : Sposta la battuta esterna SX1 (è in ingombro col posmorse) 
									  // Bit 1 : Sposta la battuta interna SX2 (è in ingombro col posmorse) 

#define   R_SPOSTA_BATTUTE_DX  553    // Bit 0 : Sposta la battuta esterna DX4 (è in ingombro col posmorse) 
									  // Bit 1 : Sposta la battuta interna DX3 (è in ingombro col posmorse) 



#define   R_DIM_TOOL           554  // Dimensione tool per uscita da pezzo 


#define   R_MIN_SX_ZONA_MORSE  555  // Posizione Minima raggiungibile dalle morse a SX (Minimo)  
#define   R_MAX_SX_ZONA_MORSE  556  // Posizione Massima raggiungibile dalle morse a SX (Massimo) 

////#define   R_MIN_DX_ZONA_MORSE  557  // Posizione Minima raggiungibile dalle morse a DX (Minimo)  
////#define   R_MAX_DX_ZONA_MORSE  558  // Posizione Massima raggiungibile dalle morse a DX (Massimo) 

#define   R_SOLBAT_OPER		   559  // Sollevamento battute da operatore per oltre misura 


#define   R_CAUSALE_CARICO     560  // Causale per il programma WAIT (ATTUALM. NON USATO)	
									// 0 = carico a sinistra			
                                    // 1 = carico a destra				
									// 2 = ininfluente,fermati dove è	

#define   R_POSBAT_VERT_SX1    561  // Posizione battuta SX per carico pezzo (0=bassa, 1=alta)

////#define   R_POSBAT_VERT_SX2    562  // Posizione battuta SX per carico pezzo (0=bassa, 1=alta)
////#define   R_POSBAT_ORIZ_SX1    563  // Posizione battuta SX per carico pezzo (0=esterna/indietro, 1=interna/avanti)
////#define   R_POSBAT_ORIZ_SX2    564  // Posizione battuta SX per carico pezzo (0=esterna/indietro, 1=interna/avanti)
////#define   R_POSBAT_VERT_DX3    565  // Posizione battuta DX per carico pezzo (0=bassa, 1=alta)

#define   R_POSBAT_VERT_DX4    566  // Posizione battuta DX per carico pezzo (0=bassa, 1=alta)

////#define   R_POSBAT_ORIZ_DX3    567  // Posizione battuta DX per carico pezzo (0=esterna/indietro, 1=interna/avanti)
////#define   R_POSBAT_ORIZ_DX4    568  // Posizione battuta DX per carico pezzo (0=esterna/indietro, 1=interna/avanti)

#define   R_DOUBLE             569 // Ciclo di tipo Double (1= ciclo pendolare dinamico e statico)

#define   R_OFF_TRASC_MOR_X    570 // Offset trascinamento morse, distanza tra asse X e trascinatore
#define   R_SOSTA_TAGLIO       571 // Abilitazione sosta da Drill dopo taglio per separazione
#define   R_TRASP_USE          572 // Uso trasportatore trucioli: 0=continuo; 1=intermittente; 2=fermo

#define   R_CKTOOL_ABIL        574 // Abilitazione Verifica integrita utensile (prima del deposito utensile)

#define   R_CKT_RIL_DIM_TOOL   575 // Abilitazione Rilievo dimensioni utensile (dopo eventuale prelievo utensile)
                                   // 1 = Abilitazione Rilievo lunghezza utensile 
                                   // 2 = Abilitazione Rilievo lunghezza e raggio utensile

#define   R_CKT_RIL_RAD_TOOL   576 // Abilitazione Rilievo raggio utensile (dopo eventuale prelievo utensile)
                                   // 1 = Abilitazione Rilievo di 1 raggio utensile
                                   // 2 = Abilitazione Rilievo di 2 raggi  utensile
                                   // 3 = Abilitazione Rilievo di 3 raggi  utensile

#define   R_WORK_COMPOUND      585 // Lavorazione ruotata su assi A e C (fuori dal sistema facce)
#define   R_CICLO_PLC          586 // Durata del ciclo PLC (letto da nciplc()), appoggio per debug

// (R_XMAX_AREASX < R_XMIN_AREADX)  Sulle prime Comet T6 i valori erano invertiti

////#define   R_XMAX_AREASX        588 // (X max camme SX assente; quota X max fino alla quale è assente fisicamente la camme INFERIORE, di SX)
////                                   // (verificar che a questa quota X vi siano almeno 10mm di luce tra mandrino ed diaframma )
////
////#define   R_XMIN_AREADX        589 // (X min camme DX assente; quota X min fino alla quale è assente fisicamente la camme SUPERIORE, di DX)
////                                   // (verificar che a questa quota X vi siano almeno 10mm di luce tra mandrino ed diaframma )


//******************************* Parametri riservati al PC ***************************
#define   R_CONT_PEZZI         590  // Contapezzi 
#define   R_TIPO_ISO		   591  // Gestito dal drill 
#define   R_SHOW_TIME          592  // Richiesta visualizzazione tempi 
#define   R_NUM_PEZZI          593  // Numero pezzi da eseguire 
#define   R_PARAMETRO_PC_4     594  // Parametro 4 dedicato a PC 
#define   R_APPOGGIO_CICLO	   595  // Indica il tipo di appoggio richiesto dal ciclo in esecuzione, 0 o 180 
#define   R_PARAMETRO_PC_6     596  // Parametro 6 dedicato a PC 
#define   R_PARAMETRO_PC_7     597  // Parametro 7 dedicato a PC 
#define   R_PARAMETRO_PC_8     598  // Parametro 8 dedicato a PC 
#define   R_RND_ISOCODE        599    // Codice casuale del programma ISO 




//*********************************************************************************
//******************************** Parametri Macchina *****************************
//*********************************************************************************
//******************************** Da R600 a R699 *********************************
//*********************************************************************************
#define   R_POS_ATTUALE_X      600    // Posizione attuale asse X 
#define   R_POS_ATTUALE_Y      601    // Posizione attuale asse Y 
#define   R_POS_ATTUALE_Z      602    // Posizione attuale asse Z 
#define   R_POS_ATTUALE_A      603    // Posizione attuale asse A 
#define   R_POS_ATTUALE_C      604    // Posizione attuale asse C 
#define   R_POS_ATTUALE_W      605    // Posizione attuale asse W 

////#define   R_POS_ATTUALE_P      606    // Posizione attuale asse P 
////#define   R_POS_ATTUALE_H      607    // Posizione attuale asse H 

////#define   R_QUOTA_P            608    // Quota asse P in G53 
////#define   R_QUOTA_H            609    // Quota asse H in G53 

#define   R_ACT_TOOL           610    // Utensile attivo su mandrino 
#define   R_NEXT_TOOL          611    // Utensile chiamato su mandrino 
#define   R_FUT_TOOL           612    /* Utensile Futuro richiesto su mandrino */
#define   R_NEXT_TESTINA       613    /* Testina successiva richiesta su mandrino */

#define   R_UTSCON             618    // Utensile sconosciuto su mandrino 
#define   R_LNG_TOOL           619    // Lunghezza utensile attivo su mandrino 
#define   R_RAD_TOOL           620    // Raggio utensile attivo su mandrino 
#define   R_ROTAZ_ON           621    // Rotazione piani attiva 

#define   R_TENTATIVI_POSMORSE 622   // Numero di tentativi di posizionamento : al terzo allarme 

#define   R_FCX_CHANGED        623   // FC asse X cambiati: 1=FC-; 2=FC+ per il pendolare 

#define   R_QUOTA_A            624    // Quota asse A in G53 (V6003/3)
#define   R_QUOTA_C            625    // Quota asse C in G53 (V6003/4)

#define   R_QUOTA_X            626    // Quota asse X in G53 (V6003/0)
#define   R_QUOTA_Y            627    // Quota asse Y in G53 (V6003/1)
#define   R_QUOTA_Z            628    // Quota asse Z in G53 (V6003/2)

#define   R_X_LAV              629    // Quota X inizio lavorazione 
#define   R_Y_LAV              630    // Quota Y inizio lavorazione 

#define   R_COUNT_TIMESX       631    // Parametro di conteggio tempo SX 
////#define   R_COUNT_TIMEDX       632    // Parametro di conteggio tempo DX 

#define   R_X_PROVV            633    // Quota provvisoria X inizio lavorazione 
#define   R_Y_PROVV            634    // Quota provvisoria Y inizio lavorazione 

#define   R_MORSE_NON_RIFERITE 635    // Almeno un asse morsa non riferito : esegui il set con l'azzeramento iniziale 

////#define   R_MORSE_DA_CH_SX	   636    // Cumulativo morse usate SX e da chiudere nel ciclo ROTAZIONE 
////#define   R_MORSE_DA_CH_DX	   637    // Cumulativo morse usate DX e da chiudere nel ciclo ROTAZIONE 

#define   R_MEM_OPENALLSX      638	  // Memoria morse da aprire 
////#define   R_MEM_OPENALLDX      639	  // Memoria morse da aprire DX 

#define   R_PLS_PREMUTO        640    // Pulsante premuto : A=1 B=2 
#define   R_STATO_MANMORSE     641    // Stato per segnalazione luminosa MANMORSE 

#define   R_MULTISX_ACTIVE     642    // Multiprocesso SX attivo 
#define   R_MULTIDX_ACTIVE     643    // Multiprocesso DX attivo 

#define   R_STATO_TAVOLA	   644    // Stato Reale Tavola : 
									  // 1=Tavola indietro
									  // 2=Tavola avanti (verso operatore)

#define   R_STATO_MAGUT		   645    // Stato Reale Magazzino    : 0=indietro, 1=avanti 
#define   R_STATO_TRASCMORSE   646    // Stato Reale Trascinatore : 0=indietro, 1=avanti 
////#define   R_STATO_DIAFRAMMA	   647    // Stato Reale Diaframma	  : 0=non inserito   , 1=inserito   

////#define   R_ZONA_MACCHINA      648	  // Posizione Asse X (zona in cui è) 
//									  // 0 : Asse X in centro 
//									  // 1 : Asse X in zona SX 
//									  // 2 : Asse X in zona DX 
//									  // 3 : Asse X in zona sconosciuta, entrambi i sensori non premono le camme (teoricam.impossib.)

#define   R_MASCRIG_ACT		   649    // Maschiatura rigida attiva 

// -----------------------------------------------------------------------------
////#define   R_POS_ATTUALE_M07    650    // Posizione attuale asse M07/Morsa n.07
////#define   R_POS_ATTUALE_M08    651    // Posizione attuale asse M08/Morsa n.08
////#define   R_POS_ATTUALE_M09    652    // Posizione attuale asse M09/Morsa n.09
// -----------------------------------------------------------------------------
#define   R_POS_ATTUALE_M10    653    // Posizione attuale asse M10/Morsa n.10
#define   R_POS_ATTUALE_M11    654    // Posizione attuale asse M11/Morsa n.11
#define   R_POS_ATTUALE_M12    655    // Posizione attuale asse M12/Morsa n.12
#define   R_POS_ATTUALE_M13    656    // Posizione attuale asse M13/Morsa n.13
#define   R_POS_ATTUALE_M14    657    // Posizione attuale asse M14/Morsa n.14
#define   R_POS_ATTUALE_M15    658    // Posizione attuale asse M15/Morsa n.15
// -----------------------------------------------------------------------------
////#define   R_POS_ATTUALE_M16    659    // Posizione attuale asse M16/Morsa n.16 
////#define   R_POS_ATTUALE_M17    660    // Posizione attuale asse M17/Morsa n.17 
////#define   R_POS_ATTUALE_M18    661    // Posizione attuale asse M18/Morsa n.18 
// -----------------------------------------------------------------------------


#define R_MICRODIZERO_ASSI	 662	// Configurazione Micro di zero degli assi
									// Bit00=000001 = Micro di Zero Asse X
									// Bit01=000002 = Micro di Zero Asse Y
									// Bit02=000004 = Micro di Zero Asse Z
									// Bit03=000008 = Micro di Zero Asse A
									// Bit04=000010 = Micro di Zero Asse W
									// Bit05=000020 = Micro di Zero Asse P
									// Bit06=000040 = Micro di Zero Asse H
									// Bit07=000080 = 
									// Bit08=000100 = 
									// Bit09=000200 = 
									// Bit10=000400 = 
									// Bit11=000800 = 
									// Bit12=001000 = 
									// Bit13=002000 = 
									// Bit14=004000 = 
									// Bit15=008000 = 
									// Bit16=010000 = 
									// Bit17=020000 = 
									// Bit18=040000 = 
									// Bit19=080000 = 
									// Bit20=100000 = 
									// Bit21=200000 = 
									// Bit22=400000 = 
									// ------------------------
									// Bit23 = Non utilizzabile
									// Bit24 = Non utilizzabile
									// Bit25 = Non utilizzabile
									// Bit26 = Non utilizzabile
									// Bit27 = Non utilizzabile
									// Bit28 = Non utilizzabile
									// Bit29 = Non utilizzabile
									// Bit30 = Non utilizzabile
									// Bit31 = Non utilizzabile

////#define   R_MORSE_IN_ZONA_ERR  663    // =1 Morse motorizzate di SX in Zona DX in pendolare, =2 Morse motorizzate di DX in Zona SX in pendolare
////#define   R_POS_MORSX          664    // ASSE P: Posizione morsa SX sotto controllo posizione 
////#define   R_ERR_POS_MORSX      665    // ASSE P: Errore posizione morsa SX sotto controllo posizione 
////
////#define   R_POS_MORDX          666    // ASSE H: Posizione morsa DX sotto controllo posizione 
////#define   R_ERR_POS_MORDX      667    // ASSE H: Errore posizione morsa DX sotto controllo posizione 

#define   R_CONF_OP_ERGO_MULTI 668	  // Multipezzo modo Ergonomico : numero di carichi effettuati (fino a num. max battute) 
////#define   R_CONF_OP_ERGO_PSX   669	  // Pendolare modo Ergonomico : numero di carichi effettuati ZONA SX (fino a num. max battute) 
////#define   R_CONF_OP_ERGO_PDX   670	  // Pendolare modo Ergonomico : numero di carichi effettuati ZONA DX (fino a num. max battute) 

////#define   R_PEZZO_IN_CARICO_P  671	  // Pezzo in carico con asse P (0=nessuno,1-6=numero pezzo) 
////#define   R_PEZZO_IN_CARICO_H  672	  // Pezzo in carico con asse H (0=nessuno,1-6=numero pezzo) 

////#define   R_ASSI_PH_PRESENTI   673    // Appoggio Assi P/H presenti per facile controllo 
#define   R_MORSE_MOTORIZZATE  674    // Appoggio Morse Motorizzate presenti per facile controllo


////#define   R_ZONA_SX_PRONTA     675  // Zona SX già pronta : ottimizzo movimenti 
////#define   R_ZONA_DX_PRONTA     676  // Zona DX già pronta : ottimizzo movimenti 


#define   R_MORSE_DA_CHIUDERE  678    // Cumulativo morse da chiudere nel ciclo ergonomico/rotazione 

#define   R_POS_MORSA          679    // Posizione morsa sotto controllo posizione 
#define   R_MORSE_TROVATE      680    // Numero di morse trovate
#define   R_ERR_POS_MORSA      681    // Errore posizione morsa sotto controllo posizione con asse X

#define   R_MORSA_CONTROLLATA  682	  // SOLO TRASC.: Morsa controllata 


#define   R_APPO_TAV           683    // Appoggio per calcolo Tavola da muovere in POS_AXES 

#define   R_PICCO_CORR	       684    // Picco Corrente Mandrino 
#define   R_PICCO_SPEED		   685    // Picco Velocita' Mandrino 
#define   R_CORR_SPINDLE       686    // Corrente Mandrino 
#define   R_SPEED_SPINDLE      687    // Velocita' Mandrino 
#define   R_CNC_CONT		   688	  // CNC in modo continuo

#define   R_APP_POS_A          689    // Appoggio posizione lavorazione in A

#define   R_APP_POSX           690    // Appoggio posizione lavorazione in X 
#define   R_APP_POSY           691    // Appoggio posizione lavorazione in Y 
#define   R_APP_POSZ           692    // Appoggio posizione lavorazione in Z 

#define   R_COLLAUDO		   693    // Per collaudo operatori : con password di utilizzo 
									  // Pwd = 3172  abilita i funzionamenti veloci 
									  // Pwd = 7123  bypass extracorsa
									  // Pwd = 18116 abilita lo sbloccaggio utensile 
									  // Pwd = 31247 elimina tutti gli altri 


#define   R_RAPP_RID_TEST	   694    // Appoggio rapporto riduzione testina per funzionamento in ISO 

#define   R_VALORE_ERRATO      695    // Controllo valori oltre quelli previsti : errore segnalato 
									  // 20000 : errore in POSAXES.CS4 controlla R203 
									  // 20001 : errore in CAMBMAN.CS4 controlla R6100 
									  // 20002 : errore in CAMBIOUT.CS4 controlla R611 
									  // 20003 : errore in POSMORS.CS4 controlla l'ISOMG del PC 
									  // 20004 : errore in CAMBIOUT.CS4 controlla R648 e la pos.delle cammes di zona 
									  // 20005 : errore in WAIT.CS4 : In pendolare chiamo la WAIT solo per aprire tutte le morse 
									  // 20006 : errore in WAIT_PH.CS4 : Impossibile collisione di X sia con P che con H 
									  // 20007 : errore in CAMBIOUT.CS4: controlla R648 in Pendolare Camme di zona non corrette per mov.tavola 
									  // 20008 : errore in CAMBIOUT.CS4: controlla R648 in Pendolare Camme di zona non corrette per mov.tavola 


#define   R_TESTA_ALLARMI      696    // TEST Allarmi attivo in simulazione : non ricopio gli ingressi 

#define   R_Z_LAV              697    // Quota Z inizio lavorazione 

#define   R_DEBUG_PLC		   698	  // Indica il debug attivo nelle varA 380-391: vedi nel codice PLC 
									  // 100: visualizza la configurazione NODI INPUT 
									  // 200: visualizza la configurazione NODI OUTPUT 
									  // 300: visualizza la configurazione NODI AD 
									  // 400: visualizza la configurazione NODI DA 

#define   R_APP_POSC           699    // Appoggio posizione lavorazione in C


//**************************************************************************************
//***************************** Configurazione Macchina ********************************
//**************************************************************************************
//*********************************** Confmac.CS4 **************************************
//**************************************************************************************

// Venditti: valore max delle aree R= 8.388.607 (float)  ==> 23 bit utilizzabili => (dal bit0 al bit22 !!!)   

// 33222222222211111111110000000000 
// 10987654321098765432109876543210

// 00000000000000000000000000000000=00|000000|        0  SI
// 00000000000000000000000000000001=00|000001|        1  SI
// 00000000000000000000000000000010=01|000002|        2  SI
// 00000000000000000000000000000100=02|000004|        4  SI
// 00000000000000000000000000001000=03|000008|        8  SI
// 00000000000000000000000000010000=04|000010|       16  SI

// 00000000000100000000000000000000=20|100000|  1048576  SI
// 00000000001000000000000000000000=21|200000|  2097152  SI
// 00000000010000000000000000000000=22|400000|  4194304  SI
// 00000000100000000000000000000000=23|800000|  8388608  NO

// 33222222222211111111110000000000 
// 10987654321098765432109876543210



#define R_CONFMAC1 700	// Configurazione Macchina Generale n.1
						// Bit00=000001 = Asse X presente
						// Bit01=000002 = Asse Y presente
						// Bit02=000004 = Asse Z presente
						// Bit03=000008 = Asse A presente
						// Bit04=000010 = Asse C presente
						// Bit05=000020 = occupato su CR6
						// Bit06=000040 = occupato su CR6
						// Bit07=000080 = occupato su CR6
						// Bit08=000100 = Asse A su CH2 - morsa n.10 presente
						// Bit09=000200 = Asse B su CH2 - morsa n.11 presente
						// Bit10=000400 = Asse C su CH2 - morsa n.12 presente
						// Bit11=000800 = Asse U su CH2 - morsa n.13 presente
						// Bit12=001000 = Asse V su CH2 - morsa n.14 presente
						// Bit13=002000 = Asse P su CH2 - morsa n.15 presente
						// Bit14=004000 = occupato su CR6
						// Bit15=008000 = occupato su CR6
						// Bit16=010000 = occupato su CR6
						// Bit17=020000 = occupato su CR6
						// Bit18=040000 = occupato su CR6
						// Bit19=080000 = NON UTILIZZARE - PHANTOMATIC X6
						// Bit20=100000 = Asse W presente
						// Bit21=200000 = Assi Morse disabilitati in lavoro
						// Bit22=400000 = Azionamenti digitali SCHNEIDER passo/passo (0=RTA; 1=SCHNEIDER) 
						// ------------------------
						// Bit23 = Non utilizzabile
						// Bit24 = Non utilizzabile
						// Bit25 = Non utilizzabile
						// Bit26 = Non utilizzabile
						// Bit27 = Non utilizzabile
						// Bit28 = Non utilizzabile
						// Bit29 = Non utilizzabile
						// Bit30 = Non utilizzabile
						// Bit31 = Non utilizzabile


#define R_CONFMAC2 701	// Configurazione Macchina Generale n.2
						// Bit00=000001 = Riparo Anteriore presente
						// Bit01=000002 = occupato su CR6
						// Bit02=000004 = Visiera bassa presente
						// Bit03=000008 = occupato su CR6
						// Bit04=000010 = Visiera alta presente
						// Bit05=000020 = occupato su CR6
						// Bit06=000040 = Battuta SX/1 presente (cilindro verticale)
						// Bit07=000080 = Battuta DX/4 presente (cilindro verticale)
						// Bit08=000100 = Versione macchina RC (Riduzione costi)
						// Bit09=000200 = Ciclo di ricerca morse abilitato
						// Bit10=000400 = Controllo posizione morse abilitato
						// Bit11=000800 = Funzionamento in multipezzo abilitato
						// Bit12=001000 = Funzionamento macchina da plancia esterna
						// Bit13=002000 = Funzionamento macchina da plancia esterna e CNC
						// Bit14=004000 = Calcolo tempo ciclo inserito
						// Bit15=008000 = Maschiatura rigida abilitata
						// Bit16=010000 = Azionamenti digitali Mechatrolink  (solo COMET T6)
						// Bit17=020000 = Allarme su movimento assi X-Y-Z
						// Bit18=040000 = Funzionamento ISO abilitato
						// Bit19=080000 = Time X Abilitato
						// Bit20=100000 = Trasportatore trucioli presente
						// Bit21=200000 = Tavola Presente
						// Bit22=400000 = occupato su CR6
						// Bit23=800000 = occupato su CR6
						// ------------------------
						// Bit24 = Non utilizzabile
						// Bit25 = Non utilizzabile
						// Bit26 = Non utilizzabile
						// Bit27 = Non utilizzabile
						// Bit28 = Non utilizzabile
						// Bit29 = Non utilizzabile
						// Bit30 = Non utilizzabile
						// Bit31 = Non utilizzabile


#define R_CONFMAC3 702	// Configurazione Macchina Generale n.3
						// Bit00=000001 = occupato su CR6
						// Bit01=000002 = occupato su CR6
						// Bit02=000004 = occupato su CR6
						// Bit03=000008 = Morsa 10 Presente (apertura/chiusura)
						// Bit04=000010 = Morsa 11 Presente (apertura/chiusura)
						// Bit05=000020 = Morsa 12 Presente (apertura/chiusura)
						// Bit06=000040 = Morsa 13 Presente (apertura/chiusura)
						// Bit07=000080 = Morsa 14 Presente (apertura/chiusura)
						// Bit08=000100 = Morsa 15 Presente (apertura/chiusura)
						// Bit09=000200 = occupato su CR6
						// Bit10=000400 = occupato su CR6
						// Bit11=000800 = occupato su CR6
						// Bit12=001000 = occupato su CR6
						// Bit13=002000 = occupato su CR6
						// Bit14=004000 = Pulsantiera Emmegi Pilot Presente
						// Bit15=008000 = occupato su CR6
						// Bit16=010000 = occupato su CR6
						// Bit17=020000 = Aspirazione Fumi presente 
						// Bit18=040000 = Trascinatore Morse Asse X Presente
						// Bit19=080000 = occupato su CR6
						// Bit20=100000 = Cilindro micro presenza morse asse X presente
						// Bit21=200000 = occupato su CR6
						// Bit22=400000 = Free
						// ------------------------
						// Bit23 = Non utilizzabile
						// Bit24 = Non utilizzabile
						// Bit25 = Non utilizzabile
						// Bit26 = Non utilizzabile
						// Bit27 = Non utilizzabile
						// Bit28 = Non utilizzabile
						// Bit29 = Non utilizzabile
						// Bit30 = Non utilizzabile
						// Bit31 = Non utilizzabile




#define R_MANDRINO 703	// Configurazione Mandrino
						// Bit00=000001 = Mandrino presente
						// Bit01=000002 = Micro mandrino in rotazione presente
						// Bit02=000004 = Refrigerante lubrica presente
						// Bit03=000008 = Livello Lubrica basso presente
						// Bit04=000010 = Livello Lubrica alto presente
						// Bit05=000020 = Flussostato centralina raffreddamento presente
						// Bit06=000040 = Refrigerante speciale (Vortex) presente
						// Bit07=000080 = Sensore Vibrazioni presente nel mandrino
						// Bit08=000100 = Inverter tipo A1000
						// Bit09=000200 = Inverter tipo Delta MS300
						// Bit10=000400 = Teleruttore Scambiatore di calore mandrino
						// Bit11=000800 = 
						// Bit12=001000 = 
						// Bit13=002000 = 
						// Bit14=004000 = 
						// Bit15=008000 = 
						// Bit16=010000 = 
						// Bit17=020000 = 
						// Bit18=040000 = 
						// Bit19=080000 = 
						// Bit20=100000 = 
						// Bit21=200000 = 
						// Bit22=400000 = 
						// ------------------------
						// Bit23 = Non utilizzabile
						// Bit24 = Non utilizzabile
						// Bit25 = Non utilizzabile
						// Bit26 = Non utilizzabile
						// Bit27 = Non utilizzabile
						// Bit28 = Non utilizzabile
						// Bit29 = Non utilizzabile
						// Bit30 = Non utilizzabile
						// Bit31 = Non utilizzabile

#define R_MAGAZZINO 704	// Configurazione Magazzino
						// Bit00=000001 = Magazzino utensili 10 posti presente
						// Bit01=000002 = Gancio magazzino utensili presente
						// Bit02=000004 = Magazzino utensili 12 posti presente
						// Bit03=000008 = 
						// Bit04=000010 = 
						// Bit05=000020 = 
						// Bit06=000040 = 
						// Bit07=000080 = 
						// Bit08=000100 = 
						// Bit09=000200 = 
						// Bit10=000400 = 
						// Bit11=000800 = 
						// Bit12=001000 = 
						// Bit13=002000 = 
						// Bit14=004000 = 
						// Bit15=008000 = 
						// Bit16=010000 = 
						// Bit17=020000 = 
						// Bit18=040000 = 
						// Bit19=080000 = 
						// Bit20=100000 = 
						// Bit21=200000 = 
						// Bit22=400000 = 
						// ------------------------
						// Bit23 = Non utilizzabile
						// Bit24 = Non utilizzabile
						// Bit25 = Non utilizzabile
						// Bit26 = Non utilizzabile
						// Bit27 = Non utilizzabile
						// Bit28 = Non utilizzabile
						// Bit29 = Non utilizzabile
						// Bit30 = Non utilizzabile
						// Bit31 = Non utilizzabile


#define R_SERVIZIO 705	// Configurazione Parametri di servizio 
						// Bit00=000001 = NON Eseguire riferimento Morse
						// Bit01=000002 = Uscita magazzino durante rif.asse W per visualizzazione
						// Bit02=000004 = (SOLO CR6 per ora) Battuta SX/1 presente (cilindro orizzontale)
						// Bit03=000008 = (SOLO CR6 per ora) Battuta DX/4 presente (cilindro orizzontale)
						// Bit04=000010 = occupato su CR6
						// Bit05=000020 = Visualizza Programma MGPilot
						// Bit06=000040 = Abilita i test per debuggare i BUG ISAC
						// Bit07=000080 = Abilita l'esecuzione della SR di DEBUG per visualizzazione
						// Bit08=000100 = Abilita l'uscita da DRILL senza premere l'emergenza
						// Bit09=000200 = Abilita il Reset Allarmi anche con Tasto F4 della MGPILOT
						// Bit10=000400 = Abilita la scrittura di Variable.txt appena prima di sbloccar assi Canopen
						// Bit11=000800 = Pulsantiera Emmegi Pilot di tipo 2  (con override mandrino)
						// Bit12=001000 = Riparo laterale SX presente
						// Bit13=002000 = Riparo laterale DX presente
						// Bit14=004000 = Riparo Posteriore SX presente
						// Bit15=008000 = Riparo Posteriore DX presente
						// Bit16=010000 = occupato su CR6
						// Bit17=020000 = occupato su CR6
						// Bit18=040000 = 
						// Bit19=080000 = 
						// Bit20=100000 = 
						// Bit21=200000 = 
						// Bit22=400000 = 
						// ------------------------
						// Bit23 = Non utilizzabile
						// Bit24 = Non utilizzabile
						// Bit25 = Non utilizzabile
						// Bit26 = Non utilizzabile
						// Bit27 = Non utilizzabile
						// Bit28 = Non utilizzabile
						// Bit29 = Non utilizzabile
						// Bit30 = Non utilizzabile
						// Bit31 = Non utilizzabile

#define R_ASSI_PH 706	// Configurazione Parametri Versioni con assi PH posizionatori
						// Bit00=000001 = occupato su CR6
						// Bit01=000002 = occupato su CR6
						// Bit02=000004 = occupato su CR6
						// Bit03=000008 = occupato su CR6
						// Bit04=000010 = occupato su CR6
						// Bit05=000020 = occupato su CR6
						// Bit06=000040 = occupato su CR6
						// Bit07=000080 = Morsa 10 Zimmer Sbloccaggio (senza asse) presente
						// Bit08=000100 = Morsa 11 Zimmer Sbloccaggio (senza asse) presente
						// Bit09=000200 = Morsa 12 Zimmer Sbloccaggio (senza asse) presente
						// Bit10=000400 = Morsa 13 Zimmer Sbloccaggio (senza asse) presente
						// Bit11=000800 = Morsa 14 Zimmer Sbloccaggio (senza asse) presente
						// Bit12=001000 = Morsa 15 Zimmer Sbloccaggio (senza asse) presente
						// Bit13=002000 = occupato su CR6
						// Bit14=004000 = occupato su CR6
						// Bit15=008000 = occupato su CR6
						// Bit16=010000 = occupato su CR6
						// Bit17=020000 = 
						// Bit18=040000 = 
						// Bit19=080000 = 
						// Bit20=100000 = 
						// Bit21=200000 = 
						// Bit22=400000 = 
						// ------------------------
						// Bit23 = Non utilizzabile
						// Bit24 = Non utilizzabile
						// Bit25 = Non utilizzabile
						// Bit26 = Non utilizzabile
						// Bit27 = Non utilizzabile
						// Bit28 = Non utilizzabile
						// Bit29 = Non utilizzabile
						// Bit30 = Non utilizzabile
						// Bit31 = Non utilizzabile


////#define   R_COMET_LITE   707  // Comet T6 Lite

////#define   R_MORSE_SX           708  // Numero di morse zona SX 
////#define   R_MORSE_DX           709  // Numero di morse zona DX

#define   R_SPACE_FREE         710  // Spazio lasciato tra ingombro pezzo e punta mandrino
#define   R_VEL_CAMBUT         711  // Velocità Lenta di cambio utensili 
#define   R_FASTACCX           712  // Accelerazione veloce asse X 
#define   R_FASTACCY           713  // Accelerazione veloce asse Y 
#define   R_FASTACCZ           714  // Accelerazione veloce asse Z 
#define   R_SLOWACCXYZ         715  // Accelerazione lenta assi X Y Z 
#define   R_MEDIACCXYZ         716  // Accelerazione media assi X Y Z 
#define   R_NTAU_ALL           717  // Numero TAU dopo i quali allarme 
#define   R_VEL_RITORNO_RIF_AC 718  // (Default :1000) Asse A e C : Velocità di ritorno a 90° A o 360° C in riferimento 

#define   R_Y_LENTO_MAGUT			719 // Movimento lento in Y in entrata dentro le pinze magazzino 

#define   R_W_MAX_MAGUT				720 // Movimento veloce asse W in contemporanea nel magazzino 
#define   R_VELFAST_POSMORSE		721 // Velocità veloce per posizionamento morse motorizzate 
#define   R_KEYPAD_DA_PLC           722 // Keypad per Mgpilot lanciato da PLC

#define   R_TOLL_MORSE				724 // (Default:0.5) Tolleranza per cui una morsa è considerata da non spostare 
// #define   R_POS_Y_OLTRE_MAGUT		725 // (Default:Y=-150) Pos.Y sicura fuori dal magazzino per trasc.morse e Y fuori ingombro in ciclo 

#define   R_VEL_VELOCE_FINDMOR_X	726	// Velocità Ricerca Morse : Asse X in ricerca libera 
#define   R_VEL_ABB_MICRO_FINDMOR_X	727	// Velocità Ricerca Morse : Asse X abbandona micro - scendi su camme 
#define   R_VEL_RIT_MICRO_FINDMOR_X	728	// Velocità Ricerca Morse : Asse X ricerca micro - ritorno su camme 

#define   R_FUORI_PINZE_Y_MAGUT		730 // Asse Y : Offset di entrata lenta nelle pinze del magazzino (mm) (solo COMET T6)
#define   R_USCITA_Y_MAGUT			731 // Asse Y : Offset di uscita da pos.magaz. per evitare le morse (mm) (solo COMET T6) 
#define   R_ALZA_PINZE_Z_MAGUT		732 // Asse Z : Alzata in magazzino per staccare dall'utensile dopo il dep.prel. (mm) (solo COMET T6) 
#define   R_ALZA_SICURO_Z_MAGUT		733 // Asse Z : Alza Z per ovviare a collisioni e uscire dalle pinze dopo il prelievo (mm) (solo COMET T6) 
#define   R_ENTRA_LENTO_Z_MAGUT		734 // Asse Z : Entrata lenta dentro le pinze nel prelievo (mm) (solo COMET T6) 

#define   R_ENDU_MORSE		   735  // Endurance : 1 => abilita il movimento morse della quota di R736 
#define   R_MOV_MORSE		   736  // Endurance : Quota di scostamento morse in mm verso dx 
#define   R_ENDURANCE          737  // Ciclo di endurance abilitato (1=normale, 2=fiera) 
#define   R_WAIT_ENDU		   738  // (Default:6sec) Endurance : tempo di attesa ripari bassi 
#define   R_AGG_TIME	       739  // Parametro per aggiustamento calcolo tempo ciclo in simulato
#define   R_X_SU_DIAFRAMMA     740  // Posizione in X del diaframma
////#define   R_RALLENTAMENTO_X    741  // Quota finale in mm che l'asse X fa in lento nella corsa massima 
////#define   R_TEMP_WAIT_SBLOCUT  742	// (Default:1.2 sec) Tempo d'attesa sbloccaggio utensile su mandrino in manuale 
#define   R_ALL_CAMMES_ZONA_X  743  // (Default:50) Quota verso l'interno/esterno sulla pos.delle cammes di zona oltre le quali scatta l'allarme 
#define   R_X_SPOST_DIAFRAMMA  744  // Tolleranza e Spostamento da pos. Diaframma per evitare il crash nel cambioutensile immediato a sx e dx 
#define   R_POS_ROTSICURA_Y	   745  // (Default Y=50) Pos.Y sicura alla quale si può ruotare il mandrino (0-180°) evitando crash con il magazzino 
#define   R_WAIT_MOR_CH_RIPOS  746  // (Default:1.0 sec) Temporizzo l'attesa chiusura sicura fra morse in riposizionamento 
#define   R_TENTATIVI_POS_MOR  747  // (Default:3) Numero di tentativi di posizionamento morse oltre i quali viene generato un allarme 

#define   R_DEFINE_CURVE_S     748  // Definizione curve ad S: 2=standard; 16=curve ad S

#define   R_VEL_VELOCE_FINDMOR_PH		749 // (Default:15000)Velocità Ricerca Morse : Assi PH in ricerca libera 
#define   R_VEL_ABB_MICRO_FINDMOR_PH	750	// (Default:10000)Velocità Ricerca Morse : Assi PH abbandona micro - scendi su camme 
#define   R_VEL_RIT_MICRO_FINDMOR_PH	751	// (Default:500)  Velocità Ricerca Morse : Assi PH ricerca micro - ritorno su camme 

#define   R_ACCSLOW_POSMOR_PH  752  // (Default:2000)  Assi PH - Accelerazione bassa per pos. morse con morsa
#define   R_ACCFAST_POSMOR_PH  753  // (Default:8000)  Assi PH - Accelerazione alta  per pos. morse senza morsa
#define   R_VEL_MORSA_TRASC_PH 754  // (Default:30000) Assi PH - Velocita bassa      per pos. morse con morsa 
#define   R_VELFAST_POSMOR_PH  755  // (Default:40000) Assi PH - Velocita alta       per pos. morse senza morsa 

#define   R_ACCSLOW_POSMOR_X   756  // (Default:2000)  Asse X - Accelerazione bassa per pos. morse con morsa
#define   R_ACCFAST_POSMOR_X   757  // (Default:8000)  Asse X - Accelerazione alta  per pos. morse senza morsa
#define   R_VEL_MORSA_TRASC_X  758  // (Default:30000) Asse X - Velocita bassa      per pos. morse con morsa 
#define   R_VELFAST_POSMOR_X   759  // (Default:80000) Asse X - Velocita alta       per pos. morse senza morsa 

#define   R_OFFSET_X           760  // offset asse X 
#define   R_OFFSET_Y           761  // offset asse Y 
#define   R_OFFSET_Z           762  // offset asse Z 

#define   R_OFFSET_Y_MAND      763  // offset Y mandrino 
#define   R_OFFSET_Z_MAND	   764  // offset Z mandrino 
#define   R_OFFSET_X_MAND      765  // Offset X mandrino 

#define   R_DELTAPOS_MORSE			767 // Delta max posizionamento morse per controllo 
#define   R_TOOLMAXLENGHT			768 // (Default:135) Lunghezza Massima Utensile (genera allarme) 
#define   R_QUOTA_A_INF_COLLISIONE	769 // (Default:45) Quota asse A oltre la quale genera l'allarme per ut.troppo lungo 


////// -----------------------------------------------------------------------------
////#define   R_OFFSET_MORSA_1		770 // Assi P/V1  (vers.PH/MM) - Distanza fra camme e centro morsa 1 
////#define   R_OFFSET_MORSA_2		771 // Assi P/V2  (vers.PH/MM) - Distanza fra camme e centro morsa 2 
////#define   R_OFFSET_MORSA_3		772 // Assi P/V3  (vers.PH/MM) - Distanza fra camme e centro morsa 3 
////#define   R_OFFSET_MORSA_4		773 // Assi P/V4  (vers.PH/MM) - Distanza fra camme e centro morsa 4 
////#define   R_OFFSET_MORSA_5		774 // Assi P/V5  (vers.PH/MM) - Distanza fra camme e centro morsa 5 
////#define   R_OFFSET_MORSA_6		775 // Assi P/V6  (vers.PH/MM) - Distanza fra camme e centro morsa 6 
////#define   R_OFFSET_MORSA_7		776 // Assi H/V7  (vers.PH/MM) - Distanza fra camme e centro morsa 7
////#define   R_OFFSET_MORSA_8		777 // Assi H/V8  (vers.PH/MM) - Distanza fra camme e centro morsa 8
////#define   R_OFFSET_MORSA_9		778 // Assi H/V9  (vers.PH/MM) - Distanza fra camme e centro morsa 9
////#define   R_OFFSET_MORSA_10		779 // Assi H/V10 (vers.PH/MM) - Distanza fra camme e centro morsa 10
////#define   R_OFFSET_MORSA_11		780 // Assi H/V11 (vers.PH/MM) - Distanza fra camme e centro morsa 11
////#define   R_OFFSET_MORSA_12		781 // Assi H/V12 (vers.PH/MM) - Distanza fra camme e centro morsa 12
////// -----------------------------------------------------------------------------

////#define   R_COST_V4056_SLAVE	782 // Costante V4056/num.asse dello slave per ottenere quota imposta delle morse 
////									// Varia se variano le tarature delle morse 
////									// Da cercare per ogni asse morse nei par.R R0-->R11 dello slave 

////#define   R_ABIL_ATT_CONF_DISC_BATT	784  // Abilitaz Attesa conferma di scarico pezzo prima della discesa battute degli assi P/H se quote di carico diverse da precedenti

////#define   R_P_SICURA			785  // (Default:2500) Posizione asse P sicura non collisione con Asse X per contemporaneità 
////#define   R_H_SICURA			786  // (Default:5000) Posizione asse H sicura non collisione con Asse X per contemporaneità 

#define   R_JERK_MIDACC         787  /* Jerk per MIDACC con curve cubiche */
#define   R_JERK_SLOWACC        788  /* Jerk per SLOWACC con curve cubiche */
#define   R_JERK_IN_SEMIAUTO    789  /* Jerk per FASTACC con curve cubiche in semiautomatico */
#define   R_TOLL		 		790 // (Default 0.1) Tolleranza nella discriminazione di quota raggiunta assi 

#define   R_RIT_SFRENO1			791 // (10)RICH_ABIL			>>>>	Sbloccaggio Zimmer
#define   R_RIT_IBLM1			792 // (40)Sbloccaggio Zimmer	>>>>	Start IBLM
#define   R_RIT_IBLM2			793 // (15)Fine RICH_ABIL		>>>>	Fine IBLM
#define   R_RIT_SFRENO2			794 // (15)Fine IBLM			>>>>>	Bloccaggio Zimmer
#define   R_RIT_DISABI_M		795 // (80)Bloccaggio Zimmer	>>>>	Fine Abilitazione (Mechatrolink)
#define   R_RIT_DISABI_C		796 // (2) Bloccaggio Zimmer	>>>>	Fine Abilitazione (CanOpen)
#define   R_RIT_O_MOV_CAN		797 // (80) Ritardo nella caduta di O_MOV x gli assi Canopen
#define   R_DELTA_POS			798 // (Default 0.5) Delta di movimento per definire l'asse in moto 

#define   R_ELIMINA_ALLARMI		799	// Eliminatore Allarmi : Solo per Tecnici Emmegisoft 
									// Bit 0 : Elimina allarme su controllo Pos.Morse inviate da PC 		
									// Bit 1 : Elimina allarme su controllo Pos.Battute inviate da PC 
									// Bit 2-15	: Liberi 	

// -------------------------------------------------------------------------
////#define   R_OFFSET_X_MORSA_1	800 // Asse X (vers.PH/X) - Distanza fra camme e centro morsa 1 
////#define   R_OFFSET_X_MORSA_2	801 // Asse X (vers.PH/X) - Distanza fra camme e centro morsa 2 
////#define   R_OFFSET_X_MORSA_3	802 // Asse X (vers.PH/X) - Distanza fra camme e centro morsa 3 
// -------------------------------------------------------------------------
#define   R_OFFSET_X_MORSA_4	803 // Asse X (vers.X) - Distanza fra camme e centro morsa 10 
#define   R_OFFSET_X_MORSA_5	804 // Asse X (vers.X) - Distanza fra camme e centro morsa 11 
#define   R_OFFSET_X_MORSA_6	805 // Asse X (vers.X) - Distanza fra camme e centro morsa 12 
#define   R_OFFSET_X_MORSA_7	806 // Asse X (vers.X) - Distanza fra camme e centro morsa 13 	
#define   R_OFFSET_X_MORSA_8	807 // Asse X (vers.X) - Distanza fra camme e centro morsa 14 	
#define   R_OFFSET_X_MORSA_9	808 // Asse X (vers.X) - Distanza fra camme e centro morsa 15 	
// -------------------------------------------------------------------------
////#define   R_OFFSET_X_MORSA_10	809 // Asse X (vers.PH/X) - Distanza fra camme e centro morsa 10	
////#define   R_OFFSET_X_MORSA_11	810 // Asse X (vers.PH/X) - Distanza fra camme e centro morsa 11	
////#define   R_OFFSET_X_MORSA_12	811 // Asse X (vers.PH/X) - Distanza fra camme e centro morsa 12	
// -------------------------------------------------------------------------

////#define   R_OFFS_DIFF_P_LATCH	817 // Differenza nel rilevamento quote morse fra LATCH asse P e BASIOCAN | Difference in clamp position reading by LATCH P axes or BASIOCAN
////#define   R_OFFS_DIFF_H_LATCH	818 // Differenza nel rilevamento quote morse fra LATCH asse H e BASIOCAN | Difference in clamp position reading by LATCH H axes or BASIOCAN

#define   R_OFFSET_MANDR_A_C    819 // Offset Mandrino: distanza tra centri rotazione A e C
#define   R_VERS_SCH_EL         820 // Versione schema elettrico: 0=> sch.el. fino a D2001952-03 (V6.5); 1=>sch.el. da ??? (V7.2 Costantino)

#define   R_ABIL_CORR_ASSE_A    821 // Abilita le correzioni su asse A
#define   R_ABIL_CORR_ASSE_X    822 // Abilita le correzioni su asse X
////#define   R_ABIL_CORR_ASSE_P    823 // Abilita le correzioni su asse P
////#define   R_ABIL_CORR_ASSE_H    824 // Abilita le correzioni su asse H
#define   R_ABIL_CORR_ASSE_C    825 // Abilita le correzioni su asse C
#define   R_ABIL_CORR_ASSE_Y    826 // (solo su CR6) Abilita le correzioni su asse Y
#define   R_ABIL_CORR_ASSE_Z    827 // (solo su CR6) Abilita le correzioni su asse Z


//**********************************************************************
//***************** Parametri usati in modo immediato ******************
//**********************************************************************

#define   R_IMM2_0              830    // Parametro di utilizzo immediato 
#define   R_IMM2_1              831    // Parametro di utilizzo immediato 
#define   R_IMM2_2              832    // Parametro di utilizzo immediato 
#define   R_IMM2_3              833    // Parametro di utilizzo immediato 
#define   R_IMM2_4              834    // Parametro di utilizzo immediato 
#define   R_IMM2_5              835    // Parametro di utilizzo immediato 
#define   R_IMM2_6              836    // Parametro di utilizzo immediato 
#define   R_IMM2_7              837    // Parametro di utilizzo immediato 
#define   R_IMM2_8              838    // Parametro di utilizzo immediato 
#define   R_IMM2_9              839    // Parametro di utilizzo immediato 
#define   R_IMM2_10             840    // Parametro di utilizzo immediato 
#define   R_IMM2_11             841    // Parametro di utilizzo immediato 
#define   R_IMM2_12             842    // Parametro di utilizzo immediato 
#define   R_IMM2_13             843    // Parametro di utilizzo immediato 
#define   R_IMM2_14             844    // Parametro di utilizzo immediato 
#define   R_IMM2_15             845    // Parametro di utilizzo immediato 
#define   R_IMM2_16             846    // Parametro di utilizzo immediato 
#define   R_IMM2_17             847    // Parametro di utilizzo immediato 
#define   R_IMM2_18             848    // Parametro di utilizzo immediato 
#define   R_IMM2_19             849    // Parametro di utilizzo immediato 


//***************** Posizioni in cui son state trovate le Morse *********************

////#define   R_POSTROVATA_MORSA_1	850 // Posizione fisica trovata Morsa 1
////#define   R_POSTROVATA_MORSA_2	851 // Posizione fisica trovata Morsa 2
////#define   R_POSTROVATA_MORSA_3	852 // Posizione fisica trovata Morsa 3
////
////#define   R_POSTROVATA_MORSA_4	853 // Posizione fisica trovata Morsa 4
////#define   R_POSTROVATA_MORSA_5	854 // Posizione fisica trovata Morsa 5
////#define   R_POSTROVATA_MORSA_6	855 // Posizione fisica trovata Morsa 6
////#define   R_POSTROVATA_MORSA_7	856 // Posizione fisica trovata Morsa 7
////#define   R_POSTROVATA_MORSA_8	857 // Posizione fisica trovata Morsa 8
////#define   R_POSTROVATA_MORSA_9	858 // Posizione fisica trovata Morsa 9
////
////#define   R_POSTROVATA_MORSA_10	859 // Posizione fisica trovata Morsa 10
////#define   R_POSTROVATA_MORSA_11	860 // Posizione fisica trovata Morsa 11
////#define   R_POSTROVATA_MORSA_12	861 // Posizione fisica trovata Morsa 12


//********************** Variabili R assi morse motorizzate *********************
////#define   R_CNC1_TARGET_M07		870 // Quota da raggiungere (M07/Morsa n.07)
////#define   R_CNC1_TARGET_M08		871 // Quota da raggiungere (M08/Morsa n.08)
////#define   R_CNC1_TARGET_M09		872 // Quota da raggiungere (M09/Morsa n.09)
#define   R_CNC1_TARGET_M10		873 // Quota da raggiungere (M10/Morsa n.10)
#define   R_CNC1_TARGET_M11		874 // Quota da raggiungere (M11/Morsa n.11)
#define   R_CNC1_TARGET_M12		875 // Quota da raggiungere (M12/Morsa n.12)
#define   R_CNC1_TARGET_M13		876 // Quota da raggiungere (M13/Morsa n.13)
#define   R_CNC1_TARGET_M14		877 // Quota da raggiungere (M14/Morsa n.14)
#define   R_CNC1_TARGET_M15		878 // Quota da raggiungere (M15/Morsa n.15)
////#define   R_CNC1_TARGET_M16		879 // Quota da raggiungere (M16/Morsa n.16)
////#define   R_CNC1_TARGET_M17		880 // Quota da raggiungere (M17/Morsa n.17)
////#define   R_CNC1_TARGET_M18		881 // Quota da raggiungere (M18/Morsa n.18)

#define   R_CNC1_VEL			885 // Pos_AX1/2: Velocità di tutte le morse

#define   R_CNC1_TIPO_MOV		887 // Pos_AX1/2: TipoMovimento: 85=RicercaMicro 87=AbbandonaMicro 90=Movim.Assoluto 91=Movim.Increm.
#define   R_CNC1_FLAG			888 // Pos_AX1/2: Flag: 1=H10; 2=H31; 3=H32; 4=NoWaitAX; 5=UguagliaSpostam1; 6=UguagliaSpostam1; 7=H16;


//-- Battuta di precisione (configurazione) ------------------------------------/
#define   R_BATT_PRECISIONE     890  /* Battuta di precisione presente */
#define   R_BATT_PREC_COLL      891  /* Allarmi Battuta di precisione disabilitati (solo per collaudo) */
#define   R_ZERO_BATT_PREC      892  /* Battuta di precisione: Quota asse U con battuta a riposo in posizione centrale (settare in modo che asseB=100 con battuta a riposo) */
#define   R_MAX_CORR_BATT_PREC  893  /* Battuta di precisione: max correzione ammissibile, oltre genera allarme di Pezzo appoggiato male alla battuta di riferimento */
#define   R_TOLL_BATT_PREC      894  /* Battuta di precisione: Tolleranza sulla Quota in posizione di riposo centrale e nell'allarme di pezzo non trovato */
#define   R_FC_BATT_IN_MIS      895  /* Finecorsa battuta di precisione in misura presente */

#define   R_WRITE_CONFTIME      896  /* Abilita la scrittura del file CONFTIME.CS4 */

#define   R_MARPOSS             900  /* Marposs presente */
#define   R_MARPOSS_FEED        901  /* Velocita Marposs */
#define   R_OFFSET_MARPOSS      902  /* Offset marposs laterale */
#define   R_MARPOSS_FEED2       903  /* Velocita Marposs (alta) */
#define   R_OFFSET_MARPOSS_PT   904  /* Offset marposs di punta */
#define   R_AB_MODULO_TAST      905  /* Abilitazione gestione modulo di tastatura CAMPlus */

//************************ Parametri R di test **********************

#define   R_TASTCNC					950 // R_TASTCNC
#define   R_APPTASTO_S				951 // 


#define   R_INGRASS_PATT       952  // Ingrassaggio automatico pattini presente (1=controllo sul ciclo; 2=controllo ogni pompata; 3=nessun controllo sul ciclo; -1=messaggio disabilitato) 
#define   R_INGRASS_INTERVALLO 953  // Ingrassaggio automatico: Ore di lavoro macchina prima dell'attivazione 
#define   R_NUM_CICLI_INGRASS  954  // Ingrassaggio automatico: Numero pompate di ingrassaggio 
#define   R_POMPA_ON           955  // Tempo pompa ingrassaggio ON 
#define   R_POMPA_OFF          956  // Tempo pompa ingrassaggio OFF 
#define   R_INGRASS_OFF_IF_OK  957  // Arresto ciclo ingrassaggio se Ok 
#define   R_NUM_POMP_DOPO_OK   958  // Numero di pompate aggiuntive dopo OK 




//*********************************************************************************
//********************* Posizioni TARGET degli ASSI  ******************************
//*********************************************************************************

#define   R_POS_TARGET_X  		960 // Posizione target asse
#define   R_POS_TARGET_Y  		961 // Posizione target asse
#define   R_POS_TARGET_Z	  	962 // Posizione target asse
#define   R_POS_TARGET_A  		963 // Posizione target asse
#define   R_POS_TARGET_C  		964 // Posizione target asse
#define   R_POS_TARGET_W  		965 // Posizione target asse

#define   R_POS_TARGET_M07		966 // Posizione target asse
#define   R_POS_TARGET_M08		967 // Posizione target asse
#define   R_POS_TARGET_M09		968 // Posizione target asse
#define   R_POS_TARGET_M10		969 // Posizione target asse
#define   R_POS_TARGET_M11		970 // Posizione target asse
#define   R_POS_TARGET_M12		971 // Posizione target asse
#define   R_POS_TARGET_M13		972 // Posizione target asse
#define   R_POS_TARGET_M14		973 // Posizione target asse
#define   R_POS_TARGET_M15		974 // Posizione target asse
#define   R_POS_TARGET_M16		975 // Posizione target asse
#define   R_POS_TARGET_M17		976 // Posizione target asse
#define   R_POS_TARGET_M18		977 // Posizione target asse

#define   R_POS_TARGET_P  		978 // Posizione target asse 
#define   R_POS_TARGET_H  		979 // Posizione target asse 




//*********************************************************************************
//***************** Parametri per programmazione ISO/Simulazione ******************
//*********************************************************************************

//Debug temporizzatori simu
#define   R_SIMU_NTIMERSIMU    985
#define   R_SIMU_MAXTSIMU      986
#define   R_SIMU_RPCONTTSIMU   987
#define   R_SIMU_RNCONTTSIMU   988
#define   R_SIMU_INGRTSIMU     989
#define   R_SIMU_RPTSIMU       990
#define   R_SIMU_RNTSIMU       991

//Debug temporizzatori supplementari
#define   R_SIMU_NTIMERSUPPL   992
#define   R_SIMU_MAXTSUPPL     993
#define   R_SIMU_RPCONTTSUPPL  994
#define   R_SIMU_RNCONTTSUPPL  995
#define   R_SIMU_INGRTSUPPL    996
#define   R_SIMU_RPTSUPPL      997
#define   R_SIMU_RNTSUPPL      998


// R1000 ^//////////////////////////////////////////////////////////////////////////////////////////

// **************************************************************************************
// ***** Aree R retentive (NB!!) ********************************************************
// **************************************************************************************

#define   R_1000              1000  // A disposizione per programmazione ISO 
#define   R_1001              1001  // A disposizione per programmazione ISO 
#define   R_1002              1002  // A disposizione per programmazione ISO 
#define   R_1003              1003  // A disposizione per programmazione ISO 
#define   R_1004              1004  // A disposizione per programmazione ISO 
#define   R_1005              1005  // A disposizione per programmazione ISO 
#define   R_1006              1006  // A disposizione per programmazione ISO 
#define   R_1007              1007  // A disposizione per programmazione ISO 
#define   R_1008              1008  // A disposizione per programmazione ISO 
#define   R_1009              1009  // A disposizione per programmazione ISO 
#define   R_1010              1010  // A disposizione per programmazione ISO 
#define   R_1011              1011  // A disposizione per programmazione ISO 
#define   R_1012              1012  // A disposizione per programmazione ISO 
#define   R_1013              1013  // A disposizione per programmazione ISO 
#define   R_1014              1014  // A disposizione per programmazione ISO 
#define   R_1015              1015  // A disposizione per programmazione ISO 
#define   R_1016              1016  // A disposizione per programmazione ISO 
#define   R_1017              1017  // A disposizione per programmazione ISO 
#define   R_1018              1018  // A disposizione per programmazione ISO 
#define   R_1019              1019  // A disposizione per programmazione ISO 


///////////////////////////////////////////////////////////////////////////////////////////////////
// *** (R1040-R1099) INIZIO R RISERVATE PER UTILIZZI COMUNI A TUTTI I PROGETTI COSTANTINO *********
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
// *** (R1040-R1099) FINE R RISERVATE PER UTILIZZI COMUNI A TUTTI I PROGETTI COSTANTINO ***********
///////////////////////////////////////////////////////////////////////////////////////////////////

// Parametri di gestione morse 
// Un parR per ogni morsa in modo da evitare anche problemi di sovrapposizione tra le varie morse per il look-ahead senza inserir altri SNGCNT

// Parametri di richiesta Apertura morse 
#define   R_RIC_AP_MORS_01          1101  // 
#define   R_RIC_AP_MORS_02          1102  // 
#define   R_RIC_AP_MORS_03          1103  // 
#define   R_RIC_AP_MORS_04          1104  // 
#define   R_RIC_AP_MORS_05          1105  // 
#define   R_RIC_AP_MORS_06          1106  // 
#define   R_RIC_AP_MORS_07          1107  // 
#define   R_RIC_AP_MORS_08          1108  // 
#define   R_RIC_AP_MORS_09          1109  // 
#define   R_RIC_AP_MORS_10          1110  // 
#define   R_RIC_AP_MORS_11          1111  // 
#define   R_RIC_AP_MORS_12          1112  // 

#define   R_RIC_AP_MORS_13          1113  // 
#define   R_RIC_AP_MORS_14          1114  // 
#define   R_RIC_AP_MORS_15          1115  // 
#define   R_RIC_AP_MORS_16          1116  // 
#define   R_RIC_AP_MORS_17          1117  // 
#define   R_RIC_AP_MORS_18          1118  // 
#define   R_RIC_AP_MORS_19          1119  // 
#define   R_RIC_AP_MORS_20          1120  // 
#define   R_RIC_AP_MORS_21          1121  // 
#define   R_RIC_AP_MORS_22          1122  // 
#define   R_RIC_AP_MORS_23          1123  // 
#define   R_RIC_AP_MORS_24          1124  //

#define   R_RIC_AP_MORS_TOT         1140  // 
#define   R_RIC_AP_MORS_SX          1141  // 
#define   R_RIC_AP_MORS_DX          1142  // 

///////////////////////////////////////////////////////////////////////////////////////////////////
// Variabili per MOVPIECE scritte da CAMAELON in programmazione ISO DRILL-CAMAELON
#define   R_MORSA_MASTER_CAMAELON    1146  //Numero morsa master richiesta da CAMAELON
#define   R_INDEX1_MOVPIECE_CAMAELON 1147  //Indici morse CAMAELON dalla 1 alla 12 sul pezzo in movpiece
#define   R_INDEX2_MOVPIECE_CAMAELON 1148  //Indici morse CAMAELON dalla 13 alla 24 sul pezzo in movpiece

// Posizione morse richieste da CAMAELON in programmazione ISO DRILL-CAMAELON
#define   R_POS_MORSA01_CAMAELON    1151  //Posizione morsa 1 richiesta da Camaelon
#define   R_POS_MORSA02_CAMAELON    1152  //Posizione morsa 2 richiesta da Camaelon
#define   R_POS_MORSA03_CAMAELON    1153  //Posizione morsa 3 richiesta da Camaelon
#define   R_POS_MORSA04_CAMAELON    1154  //Posizione morsa 4 richiesta da Camaelon
#define   R_POS_MORSA05_CAMAELON    1155  //Posizione morsa 5 richiesta da Camaelon
#define   R_POS_MORSA06_CAMAELON    1156  //Posizione morsa 6 richiesta da Camaelon
#define   R_POS_MORSA07_CAMAELON    1157  //Posizione morsa 7 richiesta da Camaelon
#define   R_POS_MORSA08_CAMAELON    1158  //Posizione morsa 8 richiesta da Camaelon
#define   R_POS_MORSA09_CAMAELON    1159  //Posizione morsa 9 richiesta da Camaelon
#define   R_POS_MORSA10_CAMAELON    1160  //Posizione morsa 10 richiesta da Camaelon
#define   R_POS_MORSA11_CAMAELON    1161  //Posizione morsa 11 richiesta da Camaelon
#define   R_POS_MORSA12_CAMAELON    1162  //Posizione morsa 12 richiesta da Camaelon

#define   R_POS_MORSA13_CAMAELON    1163  //Posizione morsa 13 richiesta da Camaelon
#define   R_POS_MORSA14_CAMAELON    1164  //Posizione morsa 14 richiesta da Camaelon
#define   R_POS_MORSA15_CAMAELON    1165  //Posizione morsa 15 richiesta da Camaelon
#define   R_POS_MORSA16_CAMAELON    1166  //Posizione morsa 16 richiesta da Camaelon
#define   R_POS_MORSA17_CAMAELON    1167  //Posizione morsa 17 richiesta da Camaelon
#define   R_POS_MORSA18_CAMAELON    1168  //Posizione morsa 18 richiesta da Camaelon
#define   R_POS_MORSA19_CAMAELON    1169  //Posizione morsa 19 richiesta da Camaelon
#define   R_POS_MORSA20_CAMAELON    1170  //Posizione morsa 20 richiesta da Camaelon
#define   R_POS_MORSA21_CAMAELON    1171  //Posizione morsa 21 richiesta da Camaelon
#define   R_POS_MORSA22_CAMAELON    1172  //Posizione morsa 22 richiesta da Camaelon
#define   R_POS_MORSA23_CAMAELON    1173  //Posizione morsa 23 richiesta da Camaelon
#define   R_POS_MORSA24_CAMAELON    1174  //Posizione morsa 24 richiesta da Camaelon

///////////////////////////////////////////////////////////////////////////////////////////////////

// Parametri di richiesta Chiusura morse 
#define   R_RIC_CH_MORS_01          1201  // 
#define   R_RIC_CH_MORS_02          1202  // 
#define   R_RIC_CH_MORS_03          1203  // 
#define   R_RIC_CH_MORS_04          1204  // 
#define   R_RIC_CH_MORS_05          1205  // 
#define   R_RIC_CH_MORS_06          1206  // 
#define   R_RIC_CH_MORS_07          1207  // 
#define   R_RIC_CH_MORS_08          1208  // 
#define   R_RIC_CH_MORS_09          1209  // 
#define   R_RIC_CH_MORS_10          1210  // 
#define   R_RIC_CH_MORS_11          1211  // 
#define   R_RIC_CH_MORS_12          1212  //

#define   R_RIC_CH_MORS_13          1213  // 
#define   R_RIC_CH_MORS_14          1214  // 
#define   R_RIC_CH_MORS_15          1215  // 
#define   R_RIC_CH_MORS_16          1216  // 
#define   R_RIC_CH_MORS_17          1217  // 
#define   R_RIC_CH_MORS_18          1218  // 
#define   R_RIC_CH_MORS_19          1219  // 
#define   R_RIC_CH_MORS_20          1220  // 
#define   R_RIC_CH_MORS_21          1221  // 
#define   R_RIC_CH_MORS_22          1222  // 
#define   R_RIC_CH_MORS_23          1223  // 
#define   R_RIC_CH_MORS_24          1224  // 

#define   R_RIC_CH_MORS_TOT         1240  // 
#define   R_RIC_CH_MORS_SX          1241  // 
#define   R_RIC_CH_MORS_DX          1242  // 

// Parametri di richiesta Chiusura morse in alta forza
#define   R_RIC_CH_AF_MORS_01       1261  // 
#define   R_RIC_CH_AF_MORS_02       1262  // 
#define   R_RIC_CH_AF_MORS_03       1263  // 
#define   R_RIC_CH_AF_MORS_04       1264  // 
#define   R_RIC_CH_AF_MORS_05       1265  // 
#define   R_RIC_CH_AF_MORS_06       1266  // 
#define   R_RIC_CH_AF_MORS_07       1267  // 
#define   R_RIC_CH_AF_MORS_08       1268  // 
#define   R_RIC_CH_AF_MORS_09       1269  // 
#define   R_RIC_CH_AF_MORS_10       1270  // 
#define   R_RIC_CH_AF_MORS_11       1271  // 
#define   R_RIC_CH_AF_MORS_12       1272  //

#define   R_RIC_CH_AF_MORS_13       1273  // 
#define   R_RIC_CH_AF_MORS_14       1274  // 
#define   R_RIC_CH_AF_MORS_15       1275  // 
#define   R_RIC_CH_AF_MORS_16       1276  // 
#define   R_RIC_CH_AF_MORS_17       1277  // 
#define   R_RIC_CH_AF_MORS_18       1278  // 
#define   R_RIC_CH_AF_MORS_19       1279  // 
#define   R_RIC_CH_AF_MORS_20       1280  // 
#define   R_RIC_CH_AF_MORS_21       1281  // 
#define   R_RIC_CH_AF_MORS_22       1282  // 
#define   R_RIC_CH_AF_MORS_23       1283  // 
#define   R_RIC_CH_AF_MORS_24       1284  // 

#define   R_RIC_CH_AF_MORS_TOT      1290  // 
#define   R_RIC_CH_AF_MORS_SX       1291  // 
#define   R_RIC_CH_AF_MORS_DX       1292  // 

// Parametri di richiesta libera servo su asse morsa
#define   R_RIC_LSR_MORS_01         1301  // 
#define   R_RIC_LSR_MORS_02         1302  // 
#define   R_RIC_LSR_MORS_03         1303  // 
#define   R_RIC_LSR_MORS_04         1304  // 
#define   R_RIC_LSR_MORS_05         1305  // 
#define   R_RIC_LSR_MORS_06         1306  // 
#define   R_RIC_LSR_MORS_07         1307  // 
#define   R_RIC_LSR_MORS_08         1308  // 
#define   R_RIC_LSR_MORS_09         1309  // 
#define   R_RIC_LSR_MORS_10         1310  // 
#define   R_RIC_LSR_MORS_11         1311  // 
#define   R_RIC_LSR_MORS_12         1312  //

#define   R_RIC_LSR_MORS_13         1313  // 
#define   R_RIC_LSR_MORS_14         1314  // 
#define   R_RIC_LSR_MORS_15         1315  // 
#define   R_RIC_LSR_MORS_16         1316  // 
#define   R_RIC_LSR_MORS_17         1317  // 
#define   R_RIC_LSR_MORS_18         1318  // 
#define   R_RIC_LSR_MORS_19         1319  // 
#define   R_RIC_LSR_MORS_20         1320  // 
#define   R_RIC_LSR_MORS_21         1321  // 
#define   R_RIC_LSR_MORS_22         1322  // 
#define   R_RIC_LSR_MORS_23         1323  // 
#define   R_RIC_LSR_MORS_24         1324  // 

// Parametri di richiesta disattiva libera servo su asse morsa
#define   R_RIC_DIS_LSR_MORS_01     1341  // 
#define   R_RIC_DIS_LSR_MORS_02     1342  // 
#define   R_RIC_DIS_LSR_MORS_03     1343  // 
#define   R_RIC_DIS_LSR_MORS_04     1344  // 
#define   R_RIC_DIS_LSR_MORS_05     1345  // 
#define   R_RIC_DIS_LSR_MORS_06     1346  // 
#define   R_RIC_DIS_LSR_MORS_07     1347  // 
#define   R_RIC_DIS_LSR_MORS_08     1348  // 
#define   R_RIC_DIS_LSR_MORS_09     1349  // 
#define   R_RIC_DIS_LSR_MORS_10     1350  // 
#define   R_RIC_DIS_LSR_MORS_11     1351  // 
#define   R_RIC_DIS_LSR_MORS_12     1352  //

#define   R_RIC_DIS_LSR_MORS_13     1353  // 
#define   R_RIC_DIS_LSR_MORS_14     1354  // 
#define   R_RIC_DIS_LSR_MORS_15     1355  // 
#define   R_RIC_DIS_LSR_MORS_16     1356  // 
#define   R_RIC_DIS_LSR_MORS_17     1357  // 
#define   R_RIC_DIS_LSR_MORS_18     1358  // 
#define   R_RIC_DIS_LSR_MORS_19     1359  // 
#define   R_RIC_DIS_LSR_MORS_20     1360  // 
#define   R_RIC_DIS_LSR_MORS_21     1361  // 
#define   R_RIC_DIS_LSR_MORS_22     1362  // 
#define   R_RIC_DIS_LSR_MORS_23     1363  // 
#define   R_RIC_DIS_LSR_MORS_24     1364  // 

// Parametri di richiesta disattivazione Chiusura morse in alta forza
#define   R_RIC_DIS_AF_MORS_01      1461  // 
#define   R_RIC_DIS_AF_MORS_02      1462  // 
#define   R_RIC_DIS_AF_MORS_03      1463  // 
#define   R_RIC_DIS_AF_MORS_04      1464  // 
#define   R_RIC_DIS_AF_MORS_05      1465  // 
#define   R_RIC_DIS_AF_MORS_06      1466  // 
#define   R_RIC_DIS_AF_MORS_07      1467  // 
#define   R_RIC_DIS_AF_MORS_08      1468  // 
#define   R_RIC_DIS_AF_MORS_09      1469  // 
#define   R_RIC_DIS_AF_MORS_10      1470  // 
#define   R_RIC_DIS_AF_MORS_11      1471  // 
#define   R_RIC_DIS_AF_MORS_12      1472  //

#define   R_RIC_DIS_AF_MORS_13      1473  // 
#define   R_RIC_DIS_AF_MORS_14      1474  // 
#define   R_RIC_DIS_AF_MORS_15      1475  // 
#define   R_RIC_DIS_AF_MORS_16      1476  // 
#define   R_RIC_DIS_AF_MORS_17      1477  // 
#define   R_RIC_DIS_AF_MORS_18      1478  // 
#define   R_RIC_DIS_AF_MORS_19      1479  // 
#define   R_RIC_DIS_AF_MORS_20      1480  // 
#define   R_RIC_DIS_AF_MORS_21      1481  // 
#define   R_RIC_DIS_AF_MORS_22      1482  // 
#define   R_RIC_DIS_AF_MORS_23      1483  // 
#define   R_RIC_DIS_AF_MORS_24      1484  // 

#define   R_RIC_DIS_AF_MORS_TOT     1490  // 
#define   R_RIC_DIS_AF_MORS_SX      1491  // 
#define   R_RIC_DIS_AF_MORS_DX      1492  // 

///////////////////////////////////////////////////////////////////////////////////////////////////

// Variabili errori di posizionamento morse alla fine della MOVPIECE.SXT in programmazione DRILL_CAMAELON
#define   R_ERR_POSM01_MOVPIECE_CAM 1541  /* Errore residuo posizione morsa 01 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM02_MOVPIECE_CAM 1542  /* Errore residuo posizione morsa 02 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM03_MOVPIECE_CAM 1543  /* Errore residuo posizione morsa 03 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM04_MOVPIECE_CAM 1544  /* Errore residuo posizione morsa 04 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM05_MOVPIECE_CAM 1545  /* Errore residuo posizione morsa 05 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM06_MOVPIECE_CAM 1546  /* Errore residuo posizione morsa 06 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM07_MOVPIECE_CAM 1547  /* Errore residuo posizione morsa 07 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM08_MOVPIECE_CAM 1548  /* Errore residuo posizione morsa 08 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM09_MOVPIECE_CAM 1549  /* Errore residuo posizione morsa 09 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM10_MOVPIECE_CAM 1550  /* Errore residuo posizione morsa 10 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM11_MOVPIECE_CAM 1551  /* Errore residuo posizione morsa 11 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM12_MOVPIECE_CAM 1552  /* Errore residuo posizione morsa 12 a fine MOVPIECE.CS4 per CAMAELON */

#define   R_ERR_POSM13_MOVPIECE_CAM 1553  /* Errore residuo posizione morsa 13 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM14_MOVPIECE_CAM 1554  /* Errore residuo posizione morsa 14 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM15_MOVPIECE_CAM 1555  /* Errore residuo posizione morsa 15 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM16_MOVPIECE_CAM 1556  /* Errore residuo posizione morsa 16 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM17_MOVPIECE_CAM 1557  /* Errore residuo posizione morsa 17 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM18_MOVPIECE_CAM 1558  /* Errore residuo posizione morsa 18 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM19_MOVPIECE_CAM 1559  /* Errore residuo posizione morsa 19 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM20_MOVPIECE_CAM 1560  /* Errore residuo posizione morsa 20 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM21_MOVPIECE_CAM 1561  /* Errore residuo posizione morsa 21 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM22_MOVPIECE_CAM 1562  /* Errore residuo posizione morsa 22 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM23_MOVPIECE_CAM 1563  /* Errore residuo posizione morsa 23 a fine MOVPIECE.CS4 per CAMAELON */
#define   R_ERR_POSM24_MOVPIECE_CAM 1564  /* Errore residuo posizione morsa 24 a fine MOVPIECE.CS4 per CAMAELON */

// Variabili in cui sono salvati gli errori di posizionamento morse alla fine della MOVPIECE.SXT
#define   R_ERR_POSMORSA01_MOVPIECE 1571  /* Errore residuo posizione morsa 01 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA02_MOVPIECE 1572  /* Errore residuo posizione morsa 02 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA03_MOVPIECE 1573  /* Errore residuo posizione morsa 03 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA04_MOVPIECE 1574  /* Errore residuo posizione morsa 04 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA05_MOVPIECE 1575  /* Errore residuo posizione morsa 05 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA06_MOVPIECE 1576  /* Errore residuo posizione morsa 06 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA07_MOVPIECE 1577  /* Errore residuo posizione morsa 07 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA08_MOVPIECE 1578  /* Errore residuo posizione morsa 08 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA09_MOVPIECE 1579  /* Errore residuo posizione morsa 09 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA10_MOVPIECE 1580  /* Errore residuo posizione morsa 10 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA11_MOVPIECE 1581  /* Errore residuo posizione morsa 11 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA12_MOVPIECE 1582  /* Errore residuo posizione morsa 12 a fine MOVPIECE.CS4 */

#define   R_ERR_POSMORSA13_MOVPIECE 1583  /* Errore residuo posizione morsa 13 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA14_MOVPIECE 1584  /* Errore residuo posizione morsa 14 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA15_MOVPIECE 1585  /* Errore residuo posizione morsa 15 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA16_MOVPIECE 1586  /* Errore residuo posizione morsa 16 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA17_MOVPIECE 1587  /* Errore residuo posizione morsa 17 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA18_MOVPIECE 1588  /* Errore residuo posizione morsa 18 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA19_MOVPIECE 1589  /* Errore residuo posizione morsa 19 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA20_MOVPIECE 1590  /* Errore residuo posizione morsa 20 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA21_MOVPIECE 1591  /* Errore residuo posizione morsa 21 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA22_MOVPIECE 1592  /* Errore residuo posizione morsa 22 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA23_MOVPIECE 1593  /* Errore residuo posizione morsa 23 a fine MOVPIECE.CS4 */
#define   R_ERR_POSMORSA24_MOVPIECE 1594  /* Errore residuo posizione morsa 24 a fine MOVPIECE.CS4 */

/* Parametri di conteggio durata dei movimenti pneumatici per TimeX */
#define   R_CH_RIPARO_ANTE         1900  /* Parametro per conteggio movimento */
#define   R_AP_RIPARO_ANTE         1901  /* Parametro per conteggio movimento */

#define   R_AVA_TAVOLA_OR          1904  /* Parametro per conteggio movimento */
#define   R_IND_TAVOLA_OR          1905  /* Parametro per conteggio movimento */

#define   R_AVA_BATMOBSX1_OR       1908  /* Parametro per conteggio movimento */
#define   R_IND_BATMOBSX1_OR       1909  /* Parametro per conteggio movimento */
#define   R_AVA_BATMOBSX2_OR       1910  /* Parametro per conteggio movimento */
#define   R_IND_BATMOBSX2_OR       1911  /* Parametro per conteggio movimento */
#define   R_AVA_BATMOBDX3_OR       1912  /* Parametro per conteggio movimento */
#define   R_IND_BATMOBDX3_OR       1913  /* Parametro per conteggio movimento */
#define   R_AVA_BATMOBDX4_OR       1914  /* Parametro per conteggio movimento */
#define   R_IND_BATMOBDX4_OR       1915  /* Parametro per conteggio movimento */
#define   R_SAL_BARCAR_SX1         1916  /* Parametro per conteggio movimento */
#define   R_DIS_BARCAR_SX1         1917  /* Parametro per conteggio movimento */
#define   R_SAL_BARCAR_SX2         1918  /* Parametro per conteggio movimento */
#define   R_DIS_BARCAR_SX2         1919  /* Parametro per conteggio movimento */
#define   R_SAL_BARCAR_DX3         1920  /* Parametro per conteggio movimento */
#define   R_DIS_BARCAR_DX3         1921  /* Parametro per conteggio movimento */
#define   R_SAL_BARCAR_DX4         1922  /* Parametro per conteggio movimento */
#define   R_DIS_BARCAR_DX4         1923  /* Parametro per conteggio movimento */
#define   R_AVA_MAG_UT             1924  /* Parametro per conteggio movimento */
#define   R_IND_MAG_UT             1925  /* Parametro per conteggio movimento */
#define   R_HIGH_PRESS_SX_UP       1926  /* Parametro per conteggio movimento */
#define   R_HIGH_PRESS_SX_DOWN     1927  /* Parametro per conteggio movimento */
#define   R_HIGH_PRESS_DX_UP       1928  /* Parametro per conteggio movimento */
#define   R_HIGH_PRESS_DX_DOWN     1929  /* Parametro per conteggio movimento */

#define   R_AP_RIP_MAG_UT          1932  /* Parametro per conteggio movimento */
#define   R_CH_RIP_MAG_UT          1933  /* Parametro per conteggio movimento */
#define   R_SBLOC_UT               1934  /* Parametro per conteggio movimento */
#define   R_BLOCC_UT               1935  /* Parametro per conteggio movimento */

#define   R_INS_TRASC_X_MORSE      1944  /* Parametro per conteggio movimento */
#define   R_DIS_TRASC_X_MORSE      1945  /* Parametro per conteggio movimento */
#define   R_VISIERA_BASSA_AVA      1946  /* Parametro per conteggio movimento */
#define   R_VISIERA_BASSA_IND      1947  /* Parametro per conteggio movimento */
#define   R_VIS_RIP_SAL            1950  /* Parametro per conteggio movimento */
#define   R_VIS_RIP_DIS            1951  /* Parametro per conteggio movimento */
#define   R_INS_RILMOR_AX_X        1954  /* Parametro per conteggio movimento */
#define   R_DIS_RILMOR_AX_X        1955  /* Parametro per conteggio movimento */

// AREE R RISERVATE PER SIMULATORE SIMON: da R1960 a R1999
#define   R_SIMU_TAV_AVA          1960     // Appoggio ingresso simulato tavola avanti per SIMON

#define   R_SIMU_BATTUTA_SX_INS   1962     // Appoggio ingresso simulato battuta SX inserita per SIMON
#define   R_SIMU_BATTUTA_DX_INS   1963     // Appoggio ingresso simulato battuta DX inserita per SIMON



#define   R_SIMU_STATUS_VAR       1999     // Variabile usata internamente dal software SIMON
// R2000 ^//////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
// ****** AREE R a disposizione della programmazione ISO ******
// da R2000 a R2099 sono a disposizione cliente per programmazione ISO (non usare!!!!!)
///////////////////////////////////////////////////////////////////////////////////////////////////

//-- Battuta di precisione: parametri di appoggio delle correzioni ------------/
#define   R_CORR_BATT_X01          2101  /* Parametro correzione lunghezza pezzo X01 */
#define   R_CORR_BATT_X02          2102  /* Parametro correzione lunghezza pezzo X02 */
#define   R_CORR_BATT_X03          2103  /* Parametro correzione lunghezza pezzo X03 */
#define   R_CORR_BATT_X04          2104  /* Parametro correzione lunghezza pezzo X04 */
#define   R_CORR_BATT_X05          2105  /* Parametro correzione lunghezza pezzo X05 */
#define   R_CORR_BATT_X06          2106  /* Parametro correzione lunghezza pezzo X06 */
#define   R_CORR_BATT_X07          2107  /* Parametro correzione lunghezza pezzo X07 */
#define   R_CORR_BATT_X08          2108  /* Parametro correzione lunghezza pezzo X08 */
#define   R_CORR_BATT_X09          2109  /* Parametro correzione lunghezza pezzo X09 */
#define   R_CORR_BATT_X10          2110  /* Parametro correzione lunghezza pezzo X10 */
#define   R_CORR_BATT_X11          2111  /* Parametro correzione lunghezza pezzo X11 */
#define   R_CORR_BATT_X12          2112  /* Parametro correzione lunghezza pezzo X12 */
#define   R_CORR_BATT_X13          2113  /* Parametro correzione lunghezza pezzo X13 */
#define   R_CORR_BATT_X14          2114  /* Parametro correzione lunghezza pezzo X14 */
#define   R_CORR_BATT_X15          2115  /* Parametro correzione lunghezza pezzo X15 */
#define   R_CORR_BATT_X16          2116  /* Parametro correzione lunghezza pezzo X16 */
#define   R_CORR_BATT_X17          2117  /* Parametro correzione lunghezza pezzo X17 */
#define   R_CORR_BATT_X18          2118  /* Parametro correzione lunghezza pezzo X18 */
#define   R_CORR_BATT_X19          2119  /* Parametro correzione lunghezza pezzo X19 */
#define   R_CORR_BATT_X20          2120  /* Parametro correzione lunghezza pezzo X20 */

//-- Battuta di precisione:  Parametri di ingresso della CK_LUNG -----------/
#define   R_POS_X_TAST             2150  /* Posizione X teorica tastatura (assoluta) */
#define   R_AMPIEZZA_TAST          2151  /* Ampiezza tastatura (totale e centrata rispetto alla posizione) */
#define   R_VEL_TAST               2152  /* Velocità tastatura (mm/min) */
#define   R_DIR_TAST               2153  /* Direzione tastatura (0:negativa  1:positiva) */
#define   R_OFFSET_TAST            2154  /* Offset battuta (offset positivo - offset negativo) */
#define   R_INDEX_TAST             2155  /* Indice per memorizzazione correzione coordinata X (valori da 1 a 20) */

#define   R_CORR_BATT_PREC         2160  /* Appoggio valore correzione X */

//***** VARIABILI PER SIMULAZIONE CON SIMON **********
#define   R_SIMON_OVFEED           2170  /* Simulatore Simon: Valore di override di lavoro */
#define   R_SIMON_OVRAP            2171  /* Simulatore Simon: Valore di override di rapido */
#define   R_SIMON_START            2173  /* Simulatore Simon: Start */

//***** ERRORI DI INSEGUIMENTO ASSI MORSE **********************
#define   R_INSEGUIMENTO_M01       2301  /* Errore di inseguimento morsa 01 */
#define   R_INSEGUIMENTO_M02       2302  /* Errore di inseguimento morsa 02 */
#define   R_INSEGUIMENTO_M03       2303  /* Errore di inseguimento morsa 03 */
#define   R_INSEGUIMENTO_M04       2304  /* Errore di inseguimento morsa 04 */
#define   R_INSEGUIMENTO_M05       2305  /* Errore di inseguimento morsa 05 */
#define   R_INSEGUIMENTO_M06       2306  /* Errore di inseguimento morsa 06 */
#define   R_INSEGUIMENTO_M07       2307  /* Errore di inseguimento morsa 07 */
#define   R_INSEGUIMENTO_M08       2308  /* Errore di inseguimento morsa 08 */
#define   R_INSEGUIMENTO_M09       2309  /* Errore di inseguimento morsa 09 */

#define   R_INSEGUIMENTO_M10       2310  /* Errore di inseguimento morsa 10 */
#define   R_INSEGUIMENTO_M11       2311  /* Errore di inseguimento morsa 11 */
#define   R_INSEGUIMENTO_M12       2312  /* Errore di inseguimento morsa 12 */

#define   R_INSEGUIMENTO_M13       2313  /* Errore di inseguimento morsa 13 */
#define   R_INSEGUIMENTO_M14       2314  /* Errore di inseguimento morsa 14 */
#define   R_INSEGUIMENTO_M15       2315  /* Errore di inseguimento morsa 15 */

#define   R_INSEGUIMENTO_M16       2316  /* Errore di inseguimento morsa 16 */
#define   R_INSEGUIMENTO_M17       2317  /* Errore di inseguimento morsa 17 */
#define   R_INSEGUIMENTO_M18       2318  /* Errore di inseguimento morsa 18 */
#define   R_INSEGUIMENTO_M19       2319  /* Errore di inseguimento morsa 19 */
#define   R_INSEGUIMENTO_M20       2320  /* Errore di inseguimento morsa 20 */
#define   R_INSEGUIMENTO_M21       2321  /* Errore di inseguimento morsa 21 */
#define   R_INSEGUIMENTO_M22       2322  /* Errore di inseguimento morsa 22 */
#define   R_INSEGUIMENTO_M23       2323  /* Errore di inseguimento morsa 23 */
#define   R_INSEGUIMENTO_M24       2324  /* Errore di inseguimento morsa 24 */

#define   R_RIC_ABIL_MORSA_01      2331  /* Forza abilitazione asse morsa 01 */
#define   R_RIC_ABIL_MORSA_02      2332  /* Forza abilitazione asse morsa 02 */
#define   R_RIC_ABIL_MORSA_03      2333  /* Forza abilitazione asse morsa 03 */
#define   R_RIC_ABIL_MORSA_04      2334  /* Forza abilitazione asse morsa 04 */
#define   R_RIC_ABIL_MORSA_05      2335  /* Forza abilitazione asse morsa 05 */
#define   R_RIC_ABIL_MORSA_06      2336  /* Forza abilitazione asse morsa 06 */
#define   R_RIC_ABIL_MORSA_07      2337  /* Forza abilitazione asse morsa 07 */
#define   R_RIC_ABIL_MORSA_08      2338  /* Forza abilitazione asse morsa 08 */
#define   R_RIC_ABIL_MORSA_09      2339  /* Forza abilitazione asse morsa 09 */

#define   R_RIC_ABIL_MORSA_10      2340  /* Forza abilitazione asse morsa 10 */
#define   R_RIC_ABIL_MORSA_11      2341  /* Forza abilitazione asse morsa 11 */
#define   R_RIC_ABIL_MORSA_12      2342  /* Forza abilitazione asse morsa 12 */

#define   R_RIC_ABIL_MORSA_13      2343  /* Forza abilitazione asse morsa 13 */
#define   R_RIC_ABIL_MORSA_14      2344  /* Forza abilitazione asse morsa 14 */
#define   R_RIC_ABIL_MORSA_15      2345  /* Forza abilitazione asse morsa 15 */

#define   R_RIC_ABIL_MORSA_16      2346  /* Forza abilitazione asse morsa 16 */
#define   R_RIC_ABIL_MORSA_17      2347  /* Forza abilitazione asse morsa 17 */
#define   R_RIC_ABIL_MORSA_18      2348  /* Forza abilitazione asse morsa 18 */
#define   R_RIC_ABIL_MORSA_19      2349  /* Forza abilitazione asse morsa 19 */
#define   R_RIC_ABIL_MORSA_20      2350  /* Forza abilitazione asse morsa 20 */
#define   R_RIC_ABIL_MORSA_21      2351  /* Forza abilitazione asse morsa 21 */
#define   R_RIC_ABIL_MORSA_22      2352  /* Forza abilitazione asse morsa 22 */
#define   R_RIC_ABIL_MORSA_23      2353  /* Forza abilitazione asse morsa 23 */
#define   R_RIC_ABIL_MORSA_24      2354  /* Forza abilitazione asse morsa 24 */

#define   R_OSK_START_SX           2672    // Richiesta Start ciclo SX (pulsante in HDRILL)
#define   R_OSK_START_DX           2673    // Richiesta Start ciclo DX (pulsante in HDRILL)
#define   R_LAMP_ZONA1             2674    // Lampada associata al pulsante HDrill di conferma zona 1
#define   R_LAMP_ZONA2             2675    // Lampada associata al pulsante HDrill di conferma zona 2

#define   R_LAMP_ZONA1_HDRILL      2681    // Lampada associata al pulsante HDrill di conferma zona 1:
                                           // =0 Lampada spenta
                                           // =1 Lampada accesa fissa
                                           // =2 Lampada lampeggiante a bassa frequenza (conferma di carico)
                                           // =3 Lampada lampeggiante ad alta frequenza (conferma di scarico)
#define   R_LAMP_ZONA2_HDRILL      2682    // Lampada associata al pulsante HDrill di conferma zona 1:
                                           // =0 Lampada spenta
                                           // =1 Lampada accesa fissa
                                           // =2 Lampada lampeggiante a bassa frequenza (conferma di carico)
                                           // =3 Lampada lampeggiante ad alta frequenza (conferma di scarico)

///////////////////////////////////////////////////////////////////////////////////////////////////
// *** (R2900-R2999) INIZIO R RISERVATE PER UTILIZZI COMUNI A TUTTI I PROGETTI COSTANTINO *********
///////////////////////////////////////////////////////////////////////////////////////////////////

#define   R_DRILL_OPZ_MACCHINA1     2910
#define   R_DRILL_OPZ_MACCHINA2     2911

#define   R_APP_VEL_MANDR           2920  /* Appoggio velocità richiesta per il mandrino in giri al minuto */
#define   R_VIS_VEL_ROT_MANDR       2921  /* Visualizza velocità di rotazione mandrino */


// ************* CONTATORI SU BRIDGE ************** INIZIO ******************


#define   R_CNT_COMMAND             2930  /* Comando per contatori da 5 a 16 compresi
                                             10= set R_CNT_VALUE nel contatore R_CNT_INDEX 
                                           */

#define   R_CNT_INDEX               2931  /* Indice dei contatori, può assumere i valori 1-16 (per Drill da 5-16) */
#define   R_CNT_VALUE               2932  /* Valore del contatore da aggiornare */
#define   R_CNT_RESULT              2933  /* Esito del comando 
                                             1     = comando in corso
                                             2     = comando terminato con successo
                                             -1    = comando terminato con errori
                                           */

#define   R_CNT_CNTR_WORD           2935  /* Mappatura tipo contatori */
#define   R_ACT_TOOL_OLD            2936  /* Utensile attivo su mandrino */


#define   R_CONTAORE_START          2940  /* Contenuto del contatore 1 */

#define   R_CONTAORE_1              2940  /* Contenuto del contatore 1 */
#define   R_CONTAORE_2              2941  /* Contenuto del contatore 2 */
#define   R_CONTAORE_3              2942  /* Contenuto del contatore 3 */
#define   R_CONTAORE_4              2943  /* Contenuto del contatore 4 */
#define   R_CONTAORE_5              2944  /* Contenuto del contatore 5 */
#define   R_CONTAORE_6              2945  /* Contenuto del contatore 6 */
#define   R_CONTAORE_7              2946  /* Contenuto del contatore 7 */
#define   R_CONTAORE_8              2947  /* Contenuto del contatore 8 */
#define   R_CONTAORE_9              2948  /* Contenuto del contatore 9 */
#define   R_CONTAORE_10             2949  /* Contenuto del contatore 10 */
#define   R_CONTAORE_11             2950  /* Contenuto del contatore 11 */
#define   R_CONTAORE_12             2951  /* Contenuto del contatore 12 */
#define   R_CONTAORE_13             2952  /* Contenuto del contatore 13 */
#define   R_CONTAORE_14             2953  /* Contenuto del contatore 14 */
#define   R_CONTAORE_15             2954  /* Contenuto del contatore 15 */
#define   R_CONTAORE_16             2955  /* Contenuto del contatore 16 */

// ************* CONTATORI SU BRIDGE ************** FINE ******************


// ************* VARIABILI RISERVATE AD HDRILL ****************************
#define   R_PARAMETRO_PC_10         2960  // Parametro 10 dedicato a PC
#define   R_PARAMETRO_PC_11         2961  // Parametro 11 dedicato a PC
#define   R_PARAMETRO_PC_12         2962  // Parametro 12 dedicato a PC
#define   R_PARAMETRO_PC_13         2963  // Parametro 13 dedicato a PC
#define   R_PARAMETRO_PC_14         2964  // Parametro 14 dedicato a PC
#define   R_PARAMETRO_PC_15         2965  // Parametro 15 dedicato a PC
#define   R_PARAMETRO_PC_16         2966  // Parametro 16 dedicato a PC
#define   R_PARAMETRO_PC_17         2967  // Parametro 17 dedicato a PC
#define   R_PARAMETRO_PC_18         2968  // Parametro 18 dedicato a PC
#define   R_PARAMETRO_PC_19         2969  // Parametro 19 dedicato a PC


#define R_VAR_EVENTI_01             2981  // Variabile_01 EVENTI (da PLC a DRILL-HDRILL)
                                          // Bit00=000001 = EVENTO_01: livello serbatoio1 lubrica basso
                                          // Bit01=000002 = EVENTO_02: livello serbatoio2 lubrica basso
                                          // Bit02=000004 = EVENTO_03:
                                          // Bit03=000008 = EVENTO_04:
                                          // Bit04=000010 = EVENTO_05:
                                          // Bit05=000020 = EVENTO_06:
                                          // Bit06=000040 = EVENTO_07:
                                          // Bit07=000080 = EVENTO_08:
                                          // Bit08=000100 = EVENTO_09:
                                          // Bit09=000200 = EVENTO_10:
                                          // Bit10=000400 = EVENTO_11:
                                          // Bit11=000800 = EVENTO_12:
                                          // Bit12=001000 = EVENTO_13:
                                          // Bit13=002000 = EVENTO_12:
                                          // Bit14=004000 = EVENTO_15:
                                          // Bit15=008000 = EVENTO_16:
                                          // Bit16=010000 = EVENTO_17:
                                          // Bit17=020000 = EVENTO_18:
                                          // Bit18=040000 = EVENTO_19:
                                          // Bit19=080000 = EVENTO_20:

#define R_VAR_EVENTI_02             2982  // Variabile_02 EVENTI (da PLC a DRILL-HDRILL)
                                          // Bit00=000001 = EVENTO_21:
                                          // Bit01=000002 = EVENTO_22:
                                          // Bit02=000004 = EVENTO_23:
                                          // Bit03=000008 = EVENTO_24:
                                          // Bit04=000010 = EVENTO_25:
                                          // Bit05=000020 = EVENTO_26:
                                          // Bit06=000040 = EVENTO_27:
                                          // Bit07=000080 = EVENTO_28:
                                          // Bit08=000100 = EVENTO_29:
                                          // Bit09=000200 = EVENTO_30:
                                          // Bit10=000400 = EVENTO_31:
                                          // Bit11=000800 = EVENTO_32:
                                          // Bit12=001000 = EVENTO_33:
                                          // Bit13=002000 = EVENTO_32:
                                          // Bit14=004000 = EVENTO_35:
                                          // Bit15=008000 = EVENTO_36:
                                          // Bit16=010000 = EVENTO_37:
                                          // Bit17=020000 = EVENTO_38:
                                          // Bit18=040000 = EVENTO_39:
                                          // Bit19=080000 = EVENTO_40:

#define R_VAR_EVENTI_03             2983  // Variabile_03 EVENTI (da PLC a DRILL-HDRILL)
                                          // Bit00=000001 = EVENTO_41:
                                          // Bit01=000002 = EVENTO_42:
                                          // Bit02=000004 = EVENTO_43:
                                          // Bit03=000008 = EVENTO_44:
                                          // Bit04=000010 = EVENTO_45:
                                          // Bit05=000020 = EVENTO_46:
                                          // Bit06=000040 = EVENTO_47:
                                          // Bit07=000080 = EVENTO_48:
                                          // Bit08=000100 = EVENTO_49:
                                          // Bit09=000200 = EVENTO_50:
                                          // Bit10=000400 = EVENTO_51:
                                          // Bit11=000800 = EVENTO_52:
                                          // Bit12=001000 = EVENTO_53:
                                          // Bit13=002000 = EVENTO_52:
                                          // Bit14=004000 = EVENTO_55:
                                          // Bit15=008000 = EVENTO_56:
                                          // Bit16=010000 = EVENTO_57:
                                          // Bit17=020000 = EVENTO_58:
                                          // Bit18=040000 = EVENTO_59:
                                          // Bit19=080000 = EVENTO_60:

#define R_VAR_EVENTI_04             2984  // Variabile_04 EVENTI (da PLC a DRILL-HDRILL)
                                          // Bit00=000001 = EVENTO_61:
                                          // Bit01=000002 = EVENTO_62:
                                          // Bit02=000004 = EVENTO_63:
                                          // Bit03=000008 = EVENTO_64:
                                          // Bit04=000010 = EVENTO_65:
                                          // Bit05=000020 = EVENTO_66:
                                          // Bit06=000040 = EVENTO_67:
                                          // Bit07=000080 = EVENTO_68:
                                          // Bit08=000100 = EVENTO_69:
                                          // Bit09=000200 = EVENTO_70:
                                          // Bit10=000400 = EVENTO_71:
                                          // Bit11=000800 = EVENTO_72:
                                          // Bit12=001000 = EVENTO_73:
                                          // Bit13=002000 = EVENTO_72:
                                          // Bit14=004000 = EVENTO_75:
                                          // Bit15=008000 = EVENTO_76:
                                          // Bit16=010000 = EVENTO_77:
                                          // Bit17=020000 = EVENTO_78:
                                          // Bit18=040000 = EVENTO_79:
                                          // Bit19=080000 = EVENTO_80:

#define R_VAR_EVENTI_05             2985  // Variabile_05 EVENTI (da PLC a DRILL-HDRILL)
                                          // Bit00=000001 = EVENTO_81:
                                          // Bit01=000002 = EVENTO_82:
                                          // Bit02=000004 = EVENTO_83:
                                          // Bit03=000008 = EVENTO_84:
                                          // Bit04=000010 = EVENTO_85:
                                          // Bit05=000020 = EVENTO_86:
                                          // Bit06=000040 = EVENTO_87:
                                          // Bit07=000080 = EVENTO_88:
                                          // Bit08=000100 = EVENTO_89:
                                          // Bit09=000200 = EVENTO_90:
                                          // Bit10=000400 = EVENTO_91:
                                          // Bit11=000800 = EVENTO_92:
                                          // Bit12=001000 = EVENTO_93:
                                          // Bit13=002000 = EVENTO_92:
                                          // Bit14=004000 = EVENTO_95:
                                          // Bit15=008000 = EVENTO_96:
                                          // Bit16=010000 = EVENTO_97:
                                          // Bit17=020000 = EVENTO_98:
                                          // Bit18=040000 = EVENTO_99:
                                          // Bit19=080000 = EVENTO_100:

#define R_VAR_ACK_01                2986  // Variabile_01 ACKNOLEDGE EVENTI (da DRILL-HDRILL a PLC)
                                          // Bit00=000001 = ACK_EVENTO_01: livello serbatoio1 lubrica basso
                                          // Bit01=000002 = ACK_EVENTO_02: livello serbatoio2 lubrica basso
                                          // Bit02=000004 = ACK_EVENTO_03:
                                          // Bit03=000008 = ACK_EVENTO_04:
                                          // Bit04=000010 = ACK_EVENTO_05:
                                          // Bit05=000020 = ACK_EVENTO_06:
                                          // Bit06=000040 = ACK_EVENTO_07:
                                          // Bit07=000080 = ACK_EVENTO_08:
                                          // Bit08=000100 = ACK_EVENTO_09:
                                          // Bit09=000200 = ACK_EVENTO_10:
                                          // Bit10=000400 = ACK_EVENTO_11:
                                          // Bit11=000800 = ACK_EVENTO_12:
                                          // Bit12=001000 = ACK_EVENTO_13:
                                          // Bit13=002000 = ACK_EVENTO_12:
                                          // Bit14=004000 = ACK_EVENTO_15:
                                          // Bit15=008000 = ACK_EVENTO_16:
                                          // Bit16=010000 = ACK_EVENTO_17:
                                          // Bit17=020000 = ACK_EVENTO_18:
                                          // Bit18=040000 = ACK_EVENTO_19:
                                          // Bit19=080000 = ACK_EVENTO_20:

#define R_VAR_ACK_02                2987  // Variabile_02 ACKNOLEDGE EVENTI (da DRILL-HDRILL a PLC)
                                          // Bit00=000001 = ACK_EVENTO_21:
                                          // Bit01=000002 = ACK_EVENTO_22:
                                          // Bit02=000004 = ACK_EVENTO_23:
                                          // Bit03=000008 = ACK_EVENTO_24:
                                          // Bit04=000010 = ACK_EVENTO_25:
                                          // Bit05=000020 = ACK_EVENTO_26:
                                          // Bit06=000040 = ACK_EVENTO_27:
                                          // Bit07=000080 = ACK_EVENTO_28:
                                          // Bit08=000100 = ACK_EVENTO_29:
                                          // Bit09=000200 = ACK_EVENTO_30:
                                          // Bit10=000400 = ACK_EVENTO_31:
                                          // Bit11=000800 = ACK_EVENTO_32:
                                          // Bit12=001000 = ACK_EVENTO_33:
                                          // Bit13=002000 = ACK_EVENTO_32:
                                          // Bit14=004000 = ACK_EVENTO_35:
                                          // Bit15=008000 = ACK_EVENTO_36:
                                          // Bit16=010000 = ACK_EVENTO_37:
                                          // Bit17=020000 = ACK_EVENTO_38:
                                          // Bit18=040000 = ACK_EVENTO_39:
                                          // Bit19=080000 = ACK_EVENTO_40:

#define R_VAR_ACK_03                2988  // Variabile_03 ACKNOLEDGE EVENTI (da DRILL-HDRILL a PLC)
                                          // Bit00=000001 = ACK_EVENTO_41:
                                          // Bit01=000002 = ACK_EVENTO_42:
                                          // Bit02=000004 = ACK_EVENTO_43:
                                          // Bit03=000008 = ACK_EVENTO_44:
                                          // Bit04=000010 = ACK_EVENTO_45:
                                          // Bit05=000020 = ACK_EVENTO_46:
                                          // Bit06=000040 = ACK_EVENTO_47:
                                          // Bit07=000080 = ACK_EVENTO_48:
                                          // Bit08=000100 = ACK_EVENTO_49:
                                          // Bit09=000200 = ACK_EVENTO_50:
                                          // Bit10=000400 = ACK_EVENTO_51:
                                          // Bit11=000800 = ACK_EVENTO_52:
                                          // Bit12=001000 = ACK_EVENTO_53:
                                          // Bit13=002000 = ACK_EVENTO_52:
                                          // Bit14=004000 = ACK_EVENTO_55:
                                          // Bit15=008000 = ACK_EVENTO_56:
                                          // Bit16=010000 = ACK_EVENTO_57:
                                          // Bit17=020000 = ACK_EVENTO_58:
                                          // Bit18=040000 = ACK_EVENTO_59:
                                          // Bit19=080000 = ACK_EVENTO_60:

#define R_VAR_ACK_04                2989  // Variabile_04 ACKNOLEDGE EVENTI (da DRILL-HDRILL a PLC)
                                          // Bit00=000001 = ACK_EVENTO_61:
                                          // Bit01=000002 = ACK_EVENTO_62:
                                          // Bit02=000004 = ACK_EVENTO_63:
                                          // Bit03=000008 = ACK_EVENTO_64:
                                          // Bit04=000010 = ACK_EVENTO_65:
                                          // Bit05=000020 = ACK_EVENTO_66:
                                          // Bit06=000040 = ACK_EVENTO_67:
                                          // Bit07=000080 = ACK_EVENTO_68:
                                          // Bit08=000100 = ACK_EVENTO_69:
                                          // Bit09=000200 = ACK_EVENTO_70:
                                          // Bit10=000400 = ACK_EVENTO_71:
                                          // Bit11=000800 = ACK_EVENTO_72:
                                          // Bit12=001000 = ACK_EVENTO_73:
                                          // Bit13=002000 = ACK_EVENTO_72:
                                          // Bit14=004000 = ACK_EVENTO_75:
                                          // Bit15=008000 = ACK_EVENTO_76:
                                          // Bit16=010000 = ACK_EVENTO_77:
                                          // Bit17=020000 = ACK_EVENTO_78:
                                          // Bit18=040000 = ACK_EVENTO_79:
                                          // Bit19=080000 = ACK_EVENTO_80:

#define R_VAR_ACK_05                2990  // Variabile_05 ACKNOLEDGE EVENTI (da DRILL-HDRILL a PLC)
                                          // Bit00=000001 = ACK_EVENTO_81:
                                          // Bit01=000002 = ACK_EVENTO_82:
                                          // Bit02=000004 = ACK_EVENTO_83:
                                          // Bit03=000008 = ACK_EVENTO_84:
                                          // Bit04=000010 = ACK_EVENTO_85:
                                          // Bit05=000020 = ACK_EVENTO_86:
                                          // Bit06=000040 = ACK_EVENTO_87:
                                          // Bit07=000080 = ACK_EVENTO_88:
                                          // Bit08=000100 = ACK_EVENTO_89:
                                          // Bit09=000200 = ACK_EVENTO_90:
                                          // Bit10=000400 = ACK_EVENTO_91:
                                          // Bit11=000800 = ACK_EVENTO_92:
                                          // Bit12=001000 = ACK_EVENTO_93:
                                          // Bit13=002000 = ACK_EVENTO_92:
                                          // Bit14=004000 = ACK_EVENTO_95:
                                          // Bit15=008000 = ACK_EVENTO_96:
                                          // Bit16=010000 = ACK_EVENTO_97:
                                          // Bit17=020000 = ACK_EVENTO_98:
                                          // Bit18=040000 = ACK_EVENTO_99:
                                          // Bit19=080000 = ACK_EVENTO_100:

///////////////////////////////////////////////////////////////////////////////////////////////////
// *** (R2900-R2999) FINE R RISERVATE PER UTILIZZI COMUNI A TUTTI I PROGETTI COSTANTINO ***********
///////////////////////////////////////////////////////////////////////////////////////////////////


// R3000 ^//////////////////////////////////////////////////////////////////////////////////////////
/* Gestione modulo CAMPlus per tastatura */
#define   R_APP_CORR_X         3044    // Appoggio valore correzione X per visualizzazione (Marposs)
#define   R_APP_CORR_Y         3045    // Appoggio valore correzione Y per visualizzazione (Marposs)
#define   R_APP_CORR_Z         3046    // Appoggio valore correzione Z per visualizzazione (Marposs)

#define   R_APP_INDEX_X        3047    // Appoggio indice correzione X
#define   R_APP_INDEX_Y        3048    // Appoggio indice correzione Y
#define   R_APP_INDEX_Z        3049    // Appoggio indice correzione Z

//	Tastatura su 3punti:        
#define   R_APP_CORR2_A        3084    // Appoggio valore correzione2 A per visualizzazione
#define   R_APP_CORR2_Y        3085    // Appoggio valore correzione2 Y per visualizzazione
#define   R_APP_CORR2_Z        3086    // Appoggio valore correzione2 Z per visualizzazione
#define   R_APP_CORR3_A        3087    // Appoggio valore correzione3 A per visualizzazione

#define   R_APP_OFFSET_MARPOSS_PT  3090  // APPOGGIO Offset marposs di punta, caricato solo se 29.SAT richiama POS_AXES.SAT



//***************************************************************************************
//***** VARIABILI RISERVATE PER LA TASTATURA OBLIQUA E COMPOSTA (da 3100 a 3199)
//***************************************************************************************

#define   R_ID1_TAST_OBLIQUA            3100    // Indice 1 per tastatura obliqua: valori da 1 a 500 (indica dove salvare i valori della tastatura)

#define   R_ID1_TAST_X_OBLIQUA          3101    // Indice per X per applicazione tastatura obliqua 1 alla lavorazione: valore da 1 a 500
#define   R_ID1_TAST_Y_OBLIQUA          3102    // Indice per Y per applicazione tastatura obliqua 1 alla lavorazione: valori da 1 a 500
#define   R_ID1_TAST_Z_OBLIQUA          3103    // Indice per Z per applicazione tastatura obliqua 1 alla lavorazione: valori da 1 a 500

#define   R_ID2_TAST_X_OBLIQUA          3104    // Indice per X per applicazione tastatura obliqua 2 alla lavorazione: valori da 1 a 500
#define   R_ID2_TAST_Y_OBLIQUA          3105    // Indice per Y per applicazione tastatura obliqua 2 alla lavorazione: valori da 1 a 500
#define   R_ID2_TAST_Z_OBLIQUA          3106    // Indice per Z per applicazione tastatura obliqua 2 alla lavorazione: valori da 1 a 500

#define   R_TAST_OBLIQUA_COMPOSTA       3110    // Indice 2 per tastatura obliqua per applicazione tastatura composta alla lavorazione: valori da 1 a 500 (da settare sempre a 0 se non è composta)


#define   R_APP_VALUE_TAST1_OBL_B       3111    // Appoggio per salvare angolo di tastatura 1 obliqua asse B
#define   R_APP_VALUE_TAST1_OBL_C       3112    // Appoggio per salvare angolo di tastatura 1 obliqua asse C
#define   R_APP_VALUE_TAST1_OBL_X       3113    // Appoggio per salvare quota teorica assoluta di tastatura 1 obliqua asse X
#define   R_APP_VALUE_TAST1_OBL_Y       3114    // Appoggio per salvare quota teorica assoluta di tastatura 1 obliqua asse Y
#define   R_APP_VALUE_TAST1_OBL_Z       3115    // Appoggio per salvare quota teorica assoluta di tastatura 1 obliqua asse Z
#define   R_APP_CORR_TAST1_OBL_X        3116    // Appoggio per salvare valore della correzione di tastatura 1 obliqua asse X
#define   R_APP_CORR_TAST1_OBL_Y        3117    // Appoggio per salvare valore della correzione di tastatura 1 obliqua asse Y
#define   R_APP_CORR_TAST1_OBL_Z        3118    // Appoggio per salvare valore della correzione di tastatura 1 obliqua asse Z

#define   R_INDEX_TAST1_OBL_B           3121    // Appoggio indice per salvare angolo di tastatura 1 asse B
#define   R_INDEX_TAST1_OBL_C           3122    // Appoggio indice per salvare angolo di tastatura 1 asse C
#define   R_INDEX_TAST1_OBL_X           3123    // Appoggio indice per salvare quota teorica assoluta di tastatura 1 asse X
#define   R_INDEX_TAST1_OBL_Y           3124    // Appoggio indice per salvare quota teorica assoluta di tastatura 1 asse Y
#define   R_INDEX_TAST1_OBL_Z           3125    // Appoggio indice per salvare quota teorica assoluta di tastatura 1 asse Z
#define   R_INDEX_CORR_TAST1_OBL_X      3126    // Appoggio indice per salvare valore della correzione di tastatura 1 asse X
#define   R_INDEX_CORR_TAST1_OBL_Y      3127    // Appoggio indice per salvare valore della correzione di tastatura 1 asse Y
#define   R_INDEX_CORR_TAST1_OBL_Z      3128    // Appoggio indice per salvare valore della correzione di tastatura 1 asse Z

#define   R_APP_VALUE_TAST2_OBL_B       3131    // Appoggio per salvare angolo di tastatura 2 obliqua asse B
#define   R_APP_VALUE_TAST2_OBL_C       3132    // Appoggio per salvare angolo di tastatura 2 obliqua asse C
#define   R_APP_VALUE_TAST2_OBL_X       3133    // Appoggio per salvare quota teorica assoluta di tastatura 2 obliqua asse X
#define   R_APP_VALUE_TAST2_OBL_Y       3134    // Appoggio per salvare quota teorica assoluta di tastatura 2 obliqua asse Y
#define   R_APP_VALUE_TAST2_OBL_Z       3135    // Appoggio per salvare quota teorica assoluta di tastatura 2 obliqua asse Z
#define   R_APP_CORR_TAST2_OBL_X        3136    // Appoggio per salvare valore della correzione di tastatura 2 obliqua asse X
#define   R_APP_CORR_TAST2_OBL_Y        3137    // Appoggio per salvare valore della correzione di tastatura 2 obliqua asse Y
#define   R_APP_CORR_TAST2_OBL_Z        3138    // Appoggio per salvare valore della correzione di tastatura 2 obliqua asse Z

#define   R_INDEX_TAST2_OBL_B           3141    // Appoggio indice per salvare angolo di tastatura 2 asse B
#define   R_INDEX_TAST2_OBL_C           3142    // Appoggio indice per salvare angolo di tastatura 2 asse C
#define   R_INDEX_TAST2_OBL_X           3143    // Appoggio indice per salvare quota teorica assoluta di tastatura 2 asse X
#define   R_INDEX_TAST2_OBL_Y           3144    // Appoggio indice per salvare quota teorica assoluta di tastatura 2 asse Y
#define   R_INDEX_TAST2_OBL_Z           3145    // Appoggio indice per salvare quota teorica assoluta di tastatura 2 asse Z
#define   R_INDEX_CORR_TAST2_OBL_X      3146    // Appoggio indice per salvare valore della correzione di tastatura 2 asse X
#define   R_INDEX_CORR_TAST2_OBL_Y      3147    // Appoggio indice per salvare valore della correzione di tastatura 2 asse Y
#define   R_INDEX_CORR_TAST2_OBL_Z      3148    // Appoggio indice per salvare valore della correzione di tastatura 2 asse Z

#define   R_APP_CORR_MEDIA_TAST_OBL_X   3151    // Appoggio per salvare valore della correzione di tastatura singola o media tra due oblique asse X
#define   R_APP_CORR_MEDIA_TAST_OBL_Y   3152    // Appoggio per salvare valore della correzione di tastatura singola o media tra due oblique asse Y
#define   R_APP_CORR_MEDIA_TAST_OBL_Z   3153    // Appoggio per salvare valore della correzione di tastatura singola o media tra due oblique asse Z

#define   R_COORD_X_TEOR_VERT_TAST_CMP  3155    // Coordinata X del vertice teorico di una tastatura composta
#define   R_COORD_Y_TEOR_VERT_TAST_CMP  3156    // Coordinata Y del vertice teorico di una tastatura composta
#define   R_COORD_Z_TEOR_VERT_TAST_CMP  3157    // Coordinata Z del vertice teorico di una tastatura composta

#define   R_COORD_X_REAL_VERT_TAST_CMP  3158    // Coordinata X del vertice reale di una tastatura composta
#define   R_COORD_Y_REAL_VERT_TAST_CMP  3159    // Coordinata Y del vertice reale di una tastatura composta
#define   R_COORD_Z_REAL_VERT_TAST_CMP  3160    // Coordinata Z del vertice reale di una tastatura composta

#define   R_DELTA_X_VERT_TAST_CMP       3161    // Delta X del vertice identificato con la tastatura composta (R_COORD_X_REAL_VERT_TAST_CMP - R_COORD_X_TEOR_VERT_TAST_CMP)
#define   R_DELTA_Y_VERT_TAST_CMP       3162    // Delta Y del vertice identificato con la tastatura composta (R_COORD_Y_REAL_VERT_TAST_CMP - R_COORD_Y_TEOR_VERT_TAST_CMP)
#define   R_DELTA_Z_VERT_TAST_CMP       3163    // Delta Z del vertice identificato con la tastatura composta (R_COORD_Z_REAL_VERT_TAST_CMP - R_COORD_Z_TEOR_VERT_TAST_CMP)

#define   R3164                         3164    // Appoggio calcolo traslazione X dovuta a Offset mandrino e lunghezza utensile in tastatura obliqua
#define   R3165                         3165    // Appoggio calcolo traslazione Y dovuta a Offset mandrino e lunghezza utensile in tastatura obliqua
#define   R3166                         3166    // Appoggio calcolo traslazione Z dovuta a Offset mandrino e lunghezza utensile in tastatura obliqua

#define   R3167                         3167    // Appoggio angolo di rotazione ANR intorno a X: usato per tastatura obliqua
#define   R3168                         3168    // Appoggio angolo di rotazione AN2 intorno a Y: usato per tastatura obliqua
#define   R3169                         3169    // Appoggio angolo di rotazione AN3 intorno a Z: usato per tastatura obliqua

#define   R3171                         3171    // Appoggio del punto teorico di tastatura in X nel sistema ruotato e traslato
#define   R3172                         3172    // Appoggio del punto teorico di tastatura in Y nel sistema ruotato e traslato
#define   R3173                         3173    // Appoggio del punto teorico di tastatura in Z nel sistema ruotato e traslato

#define   R_TAST_OBLIQUA3_COMPOSTA      3180    // Indice 3 per tastatura obliqua per applicazione tastatura composta alla lavorazione: valori da 1 a 500 (da settare sempre a 0 se non è composta)

#define   R_APP_VALUE_TAST3_OBL_B       3181    // Appoggio per salvare angolo di tastatura 3 obliqua asse B
#define   R_APP_VALUE_TAST3_OBL_C       3182    // Appoggio per salvare angolo di tastatura 3 obliqua asse C
#define   R_APP_VALUE_TAST3_OBL_X       3183    // Appoggio per salvare quota teorica assoluta di tastatura 3 obliqua asse X
#define   R_APP_VALUE_TAST3_OBL_Y       3184    // Appoggio per salvare quota teorica assoluta di tastatura 3 obliqua asse Y
#define   R_APP_VALUE_TAST3_OBL_Z       3185    // Appoggio per salvare quota teorica assoluta di tastatura 3 obliqua asse Z
#define   R_APP_CORR_TAST3_OBL_X        3186    // Appoggio per salvare valore della correzione di tastatura 3 obliqua asse X
#define   R_APP_CORR_TAST3_OBL_Y        3187    // Appoggio per salvare valore della correzione di tastatura 3 obliqua asse Y
#define   R_APP_CORR_TAST3_OBL_Z        3188    // Appoggio per salvare valore della correzione di tastatura 3 obliqua asse Z

#define   R_INDEX_TAST3_OBL_B           3191    // Appoggio indice per salvare angolo di tastatura 3 asse B
#define   R_INDEX_TAST3_OBL_C           3192    // Appoggio indice per salvare angolo di tastatura 3 asse C
#define   R_INDEX_TAST3_OBL_X           3193    // Appoggio indice per salvare quota teorica assoluta di tastatura 3 asse X
#define   R_INDEX_TAST3_OBL_Y           3194    // Appoggio indice per salvare quota teorica assoluta di tastatura 3 asse Y
#define   R_INDEX_TAST3_OBL_Z           3195    // Appoggio indice per salvare quota teorica assoluta di tastatura 3 asse Z
#define   R_INDEX_CORR_TAST3_OBL_X      3196    // Appoggio indice per salvare valore della correzione di tastatura 3 asse X
#define   R_INDEX_CORR_TAST3_OBL_Y      3197    // Appoggio indice per salvare valore della correzione di tastatura 3 asse Y
#define   R_INDEX_CORR_TAST3_OBL_Z      3198    // Appoggio indice per salvare valore della correzione di tastatura 3 asse Z

//***************************************************************************************
//***** FINE VARIABILI RISERVATE PER LA TASTATURA OBLIQUA E COMPOSTA (da 3100 a 3199)
//***************************************************************************************


// VARIABILI PER FIGURA 8.SXT (TAGLIO PROFILO CON LAMA)
#define   R3400                3400    // velocità di taglio                (traslazione assi in mm/min)
#define   R3401                3401    // velocità di rotazione della lama  (n° giri mandrino/min)
#define   R3402                3402    // velocità di taglio del 4° vertice (traslazione assi in mm/min)

#define   R3403                3403    // quota B
#define   R3404                3404    // quota C

#define   R3410                3410    // vertice1: quota X
#define   R3411                3411    // vertice1: quota Y
#define   R3412                3412    // vertice1: quota Z

#define   R3413                3413    // vertice2: quota X
#define   R3414                3414    // vertice2: quota Y
#define   R3415                3415    // vertice2: quota Z

#define   R3416                3416    // vertice3: quota X
#define   R3417                3417    // vertice3: quota Y
#define   R3418                3418    // vertice3: quota Z

#define   R3419                3419    // vertice4: quota X
#define   R3420                3420    // vertice4: quota Y
#define   R3421                3421    // vertice4: quota Z

/* Gestione modulo CAMPlus per tastatura */
#define   R_TIPO_TAST          3499    // = 0 correzione con una tastatura; = 1 correzione con la media di due tastature
#define   R_ID2_TAST_X         3500    // Indice per correzione 2 coordinata X; valori da 1 a 99
#define   R_ID2_TAST_Y         3501    // Indice per correzione 2 coordinata Y; valori da 1 a 99
#define   R_ID2_TAST_Z         3502    // Indice per correzione 2 coordinata Z; valori da 1 a 99

#define   R_APP2_CORR_X        3504    // Appoggio valore correzione 2 X per visualizzazione (Marposs)
#define   R_APP2_CORR_Y        3505    // Appoggio valore correzione 2 Y per visualizzazione (Marposs)
#define   R_APP2_CORR_Z        3506    // Appoggio valore correzione 2 Z per visualizzazione (Marposs)

#define   R_APP2_INDEX_X       3507    // Appoggio indice correzione 2 X
#define   R_APP2_INDEX_Y       3508    // Appoggio indice correzione 2 Y
#define   R_APP2_INDEX_Z       3509    // Appoggio indice correzione 2 Z

#define   R_APP_VALMEDIO_X     3510    // Appoggio correzione valore medio X per visualizzazione (Marposs)
#define   R_APP_VALMEDIO_Y     3511    // Appoggio correzione valore medio Y per visualizzazione (Marposs)
#define   R_APP_VALMEDIO_Z     3512    // Appoggio correzione valore medio Z per visualizzazione (Marposs)

//*************** VARIABILI DI DEBUG PER MULTICANALE *******************
#define   R_TEST3910           3910    // TEST: usata in central()
#define   R_TEST3911           3911    // TEST: usata in central()
#define   R_TEST3912           3912    // TEST: usata in central()
#define   R_TEST3913           3913    // TEST: usata in central()

#define   R_TEST3920           3920    // TEST: usata in central()
#define   R_TEST3921           3921    // TEST: usata in central()
#define   R_TEST3922           3922    // TEST: usata in central()
#define   R_TEST3923           3923    // TEST: usata in central()
#define   R_TEST3924           3924    // TEST: usata in central()
#define   R_TEST3925           3925    // TEST: usata in central()
#define   R_TEST3926           3926    // TEST: usata in central()
#define   R_TEST3927           3927    // TEST: usata in central()
#define   R_TEST3928           3928    // TEST: usata in central()
#define   R_TEST3929           3929    // TEST: usata in central()
#define   R_TEST3930           3930    // TEST: usata in central()
#define   R_TEST3931           3931    // TEST: usata in central()
#define   R_TEST3932           3932    // TEST: usata in central()

#define   R_TEST3940           3940     //usato ISO conta chiamate a SYNCNC.QUA CH0 la stesso R per gli altri canali

#define   R3950                3950     //pausa di verifica quote (aggiunta da Comet S6) 
#define   R3951                3951     //pausa di verifica quote (aggiunta da Comet S6) 
#define   R3952                3952     //pausa di verifica quote (aggiunta da Comet S6) 


// R4000 ^//////////////////////////////////////////////////////////////////////////////////////////

/* ----------------- Definite solo per simulazione con funzioni manuali e con TIMEX ------------------ */
#define   R_SIM_PLS_A		   4000    /* Simula pressione pulsante A */
#define   R_SIM_PLS_B		   4001    /* Simula pressione pulsante B */

#define   R_AIUTA_PLS		   4002   /* Aiuta pressione continua PLS in simulazione */

#define   R_SIM_AUX			   4003   /* Word Simulazione Partenza sequena automatica */
#define   R_SIM_START		   4004   /* Word Simulazione Partenza sequena automatica */
#define   R_SIM_AUTO		   4005   /* Word Simulazione Partenza sequena automatica */
#define   R_SIM_HOLD		   4006   /* Word Simulazione Partenza sequena automatica */
#define   R_SIM_RESET		   4007   /* Word Simulazione Partenza sequena automatica */

#define   R_FC0_P			   4010   /* FC0 dell'asse indicato */
#define   R_FC0_H			   4011   /* FC0 dell'asse indicato */

#define   R_4020               4020   /* Variabile di debug simulatore */
#define   R_4021               4021   /* Variabile di debug simulatore */
#define   R_4022               4022   /* Variabile di debug simulatore */
#define   R_4023               4023   /* Variabile di debug simulatore */
#define   R_4024               4024   /* Variabile di debug simulatore */
#define   R_4025               4025   /* Variabile di debug simulatore */
#define   R_4026               4026   /* Variabile di debug simulatore */
#define   R_4027               4027   /* Variabile di debug simulatore */
#define   R_4028               4028   /* Variabile di debug simulatore */
#define   R_4029               4029   /* Variabile di debug simulatore */
#define   R_4030               4030   /* Variabile di debug simulatore */
#define   R_4031               4031   /* Variabile di debug simulatore */
#define   R_4032               4032   /* Variabile di debug simulatore */
#define   R_4033               4033   /* Variabile di debug simulatore */
#define   R_4034               4034   /* Variabile di debug simulatore */
#define   R_4035               4035   /* Variabile di debug simulatore */
#define   R_4036               4036   /* Variabile di debug simulatore */
#define   R_4037               4037   /* Variabile di debug simulatore */
#define   R_4038               4038   /* Variabile di debug simulatore */
#define   R_4039               4039   /* Variabile di debug simulatore */
#define   R_4040               4040   /* Variabile di debug simulatore */
#define   R_4041               4041   /* Variabile di debug simulatore */
#define   R_4042               4042   /* Variabile di debug simulatore */
#define   R_4043               4043   /* Variabile di debug simulatore */
#define   R_4044               4044   /* Variabile di debug simulatore */
#define   R_4045               4045   /* Variabile di debug simulatore */
#define   R_4046               4046   /* Variabile di debug simulatore */
#define   R_4047               4047   /* Variabile di debug simulatore */
#define   R_4048               4048   /* Variabile di debug simulatore */
#define   R_4049               4049   /* Variabile di debug simulatore */
#define   R_4050               4050   /* Variabile di debug simulatore */
#define   R_4051               4051   /* Variabile di debug simulatore */
#define   R_4052               4052   /* Variabile di debug simulatore */
#define   R_4053               4053   /* Variabile di debug simulatore */
#define   R_4054               4054   /* Variabile di debug simulatore */

//#define   R_4055               4055   /* Variabile di debug simulatore */
//#define   R_4056               4056   /* Variabile di debug simulatore */
//#define   R_4057               4057   /* Variabile di debug simulatore */
//#define   R_4058               4058   /* Variabile di debug simulatore */
//#define   R_4059               4059   /* Variabile di debug simulatore */
//#define   R_4060               4060   /* Variabile di debug simulatore */


#define   R4100                4100   // 
#define   R4101                4101   // 
#define   R4102                4102   // 
#define   R4103                4103   // 

#define   R4105                4105   // 

#define   R4109                4109   // 
#define   R4110                4110   // 
#define   R4111                4111   // 
#define   R4112                4112   // 
#define   R4113                4113   // 
#define   R4114                4114   // 
#define   R4115                4115   // 
////#define   R4116                4116   // 
////#define   R4117                4117   // 
////#define   R4118                4118   // 
////#define   R4119                4119   // 
////#define   R4120                4120   // 
////#define   R4121                4121   // 
////#define   R4122                4122   // 

#define   R4130                4130   // 
#define   R4131                4131   // 
#define   R4132                4132   // 
#define   R4133                4133   // 
#define   R4134                4134   // 
#define   R4135                4135   // 
#define   R4136                4136   // 
#define   R4137                4137   // 
#define   R4138                4138   // 
#define   R4139                4139   // 
#define   R4140                4140   // 
#define   R4141                4141   // 
#define   R4142                4142   // 

#define   R4150                4150   // contatore di: FEEDHOLD_MAND
#define   R4151                4151   // contatore di: !(VEL_INVERTEROK_I)
#define   R4152                4152   // contatore di: !(RP_START_INV)

#define   R4200                4200   // _TEST_AX.CS4
#define   R4201                4201   // "
#define   R4202                4202   // "
#define   R4203                4203   // "
#define   R4204                4204   // "
#define   R4205                4205   // "
#define   R4206                4206   // "
#define   R4207                4207   // "
#define   R4208                4208   // "
#define   R4209                4209   // "
#define   R4210                4210   // "
#define   R4211                4211   // "
#define   R4212                4212   // "
// R4200 - R4240  _TEST_AX.CS4

// R4250 - R4261  RIFMORSE.CS4

// R4270 - R4299 UTILIZZABILI IN MODO IMMEDIATO PER CICLI ISO DI DEBUG VARI


#define   R4300                4300   // test: ad assi riferiti esegue sempre rif morse e disabilita rif altri assi

#define   R4302                4302   // test: disabilita rif di tutti gli assi se tutti riferiti

#define   R4305                4305   // contatore cambi utensile
#define   R4310                4310   // test cambiout: pausa
#define   R4311                4311   // test cambiout: ut 1
#define   R4312                4312   // test cambiout: ut 2

#define   R4320                4320   // test: ripete rif morse all'infinito
#define   R4321                4321   // test: pausa in rif morse per verifica err inseg

#define   R_TEST_DISAB_AX      4330   // test: abilita forzatura disabilitaz assi

#define   R_FORZA_AB_X         4331   // test: (manuale) forza abilitaz. asse X
#define   R_FORZA_AB_Y         4332   // test: (manuale) forza abilitaz. asse Y
#define   R_FORZA_AB_Z         4333   // test: (manuale) forza abilitaz. asse Z
#define   R_FORZA_AB_A         4334   // test: (manuale) forza abilitaz. asse A
#define   R_FORZA_AB_C         4335   // test: (manuale) forza abilitaz. asse C
#define   R_FORZA_AB_W         4336   // test: (manuale) forza abilitaz. asse W

#define   R4350                4350   // test:
#define   R4351                4351   // test:

#define   R4360                4360   // Usata in Z_RTCP.CS4
#define   R4361                4361   // Usata in Z_RTCP.CS4
#define   R4362                4362   // Usata in Z_RTCP.CS4
#define   R4363                4363   // Usata in Z_RTCP.CS4

#define   R4401                4401   // Usata in CAM_ORG.CS4
#define   R4402                4402   // Usata in CAM_ORG.CS4
#define   R4403                4403   // Usata in CAM_ORG.CS4
#define   R4404                4404   // Usata in CAM_ORG.CS4
#define   R4405                4405   // Usata in CAM_ORG.CS4
#define   R4406                4406   // Usata in CAM_ORG.CS4
#define   R4407                4407   // Usata in CAM_ORG.CS4
#define   R4408                4408   // Usata in CAM_ORG.CS4

#define   R4410                4410   // Usata per debug shared_Mem_MC

#define   R4411                4411   // CAM_ORG.CS4 : traslazione assoluta dell'origine X (aggiunta da COMET S6)
#define   R4412                4412   // CAM_ORG.CS4 : traslazione assoluta dell'origine Y (aggiunta da COMET S6)
#define   R4413                4413   // CAM_ORG.CS4 : traslazione assoluta dell'origine Z (aggiunta da COMET S6)

#define   R4421                4421   // contatore di debug 
#define   R4422                4422   // contatore di debug 


#define   R4450                4450   // contatore di debug 
#define   R4451                4451   // "
#define   R4452                4452   // "
#define   R4453                4453   // "

#define   ALARM_OPCUA_FIRST_R  4470   // Prima R riservata per lista allarmi per visualizzazione su client OPCUA 
#define   R_ALL_OPCUA_0        4470   // Codice allarme 1 per visualizzazione su client OPCUA 
#define   R_ALL_OPCUA_1        4471   // Codice allarme 2 per visualizzazione su client OPCUA 
#define   R_ALL_OPCUA_2        4472   // Codice allarme 3 per visualizzazione su client OPCUA 
#define   R_ALL_OPCUA_3        4473   // Codice allarme 4 per visualizzazione su client OPCUA 
#define   R_ALL_OPCUA_4        4474   // Codice allarme 5 per visualizzazione su client OPCUA  
#define   ALARM_OPCUA_LAST_R   4474   // Ultima R riservata per lista allarmi per visualizzazione su client OPCUA 

///////////////////////////////////////////////////////////////////////////////////////////////////
// ****** AREE R riservate per utilizzo immediato nei part program ******
// da R4500 a R4599 usare solo per utilizzo imediato dentro ai part program
///////////////////////////////////////////////////////////////////////////////////////////////////
#define   R_IMM_4500           4500    // Parametro di utilizzo immediato
#define   R_IMM_4501           4501    // Parametro di utilizzo immediato
#define   R_IMM_4502           4502    // Parametro di utilizzo immediato
#define   R_IMM_4503           4503    // Parametro di utilizzo immediato
#define   R_IMM_4504           4504    // Parametro di utilizzo immediato
#define   R_IMM_4505           4505    // Parametro di utilizzo immediato
#define   R_IMM_4506           4506    // Parametro di utilizzo immediato
#define   R_IMM_4507           4507    // Parametro di utilizzo immediato
#define   R_IMM_4508           4508    // Parametro di utilizzo immediato
#define   R_IMM_4509           4509    // Parametro di utilizzo immediato
#define   R_IMM_4510           4510    // Parametro di utilizzo immediato
#define   R_IMM_4511           4511    // Parametro di utilizzo immediato
#define   R_IMM_4512           4512    // Parametro di utilizzo immediato
#define   R_IMM_4513           4513    // Parametro di utilizzo immediato
#define   R_IMM_4514           4514    // Parametro di utilizzo immediato
#define   R_IMM_4515           4515    // Parametro di utilizzo immediato
#define   R_IMM_4516           4516    // Parametro di utilizzo immediato
#define   R_IMM_4517           4517    // Parametro di utilizzo immediato
#define   R_IMM_4518           4518    // Parametro di utilizzo immediato
#define   R_IMM_4519           4519    // Parametro di utilizzo immediato
#define   R_IMM_4520           4520    // Parametro di utilizzo immediato
#define   R_IMM_4521           4521    // Parametro di utilizzo immediato
#define   R_IMM_4522           4522    // Parametro di utilizzo immediato
#define   R_IMM_4523           4523    // Parametro di utilizzo immediato
#define   R_IMM_4524           4524    // Parametro di utilizzo immediato
#define   R_IMM_4525           4525    // Parametro di utilizzo immediato
#define   R_IMM_4526           4526    // Parametro di utilizzo immediato
#define   R_IMM_4527           4527    // Parametro di utilizzo immediato
#define   R_IMM_4528           4528    // Parametro di utilizzo immediato
#define   R_IMM_4529           4529    // Parametro di utilizzo immediato
#define   R_IMM_4530           4530    // Parametro di utilizzo immediato
#define   R_IMM_4531           4531    // Parametro di utilizzo immediato
#define   R_IMM_4532           4532    // Parametro di utilizzo immediato
#define   R_IMM_4533           4533    // Parametro di utilizzo immediato
#define   R_IMM_4534           4534    // Parametro di utilizzo immediato
#define   R_IMM_4535           4535    // Parametro di utilizzo immediato
#define   R_IMM_4536           4536    // Parametro di utilizzo immediato
#define   R_IMM_4537           4537    // Parametro di utilizzo immediato
#define   R_IMM_4538           4538    // Parametro di utilizzo immediato
#define   R_IMM_4539           4539    // Parametro di utilizzo immediato
#define   R_IMM_4540           4540    // Parametro di utilizzo immediato
#define   R_IMM_4541           4541    // Parametro di utilizzo immediato
#define   R_IMM_4542           4542    // Parametro di utilizzo immediato
#define   R_IMM_4543           4543    // Parametro di utilizzo immediato
#define   R_IMM_4544           4544    // Parametro di utilizzo immediato
#define   R_IMM_4545           4545    // Parametro di utilizzo immediato
#define   R_IMM_4546           4546    // Parametro di utilizzo immediato
#define   R_IMM_4547           4547    // Parametro di utilizzo immediato
#define   R_IMM_4548           4548    // Parametro di utilizzo immediato
#define   R_IMM_4549           4549    // Parametro di utilizzo immediato
#define   R_IMM_4550           4550    // Parametro di utilizzo immediato
#define   R_IMM_4551           4551    // Parametro di utilizzo immediato
#define   R_IMM_4552           4552    // Parametro di utilizzo immediato
#define   R_IMM_4553           4553    // Parametro di utilizzo immediato
#define   R_IMM_4554           4554    // Parametro di utilizzo immediato
#define   R_IMM_4555           4555    // Parametro di utilizzo immediato
#define   R_IMM_4556           4556    // Parametro di utilizzo immediato
#define   R_IMM_4557           4557    // Parametro di utilizzo immediato
#define   R_IMM_4558           4558    // Parametro di utilizzo immediato
#define   R_IMM_4559           4559    // Parametro di utilizzo immediato
#define   R_IMM_4560           4560    // Parametro di utilizzo immediato
#define   R_IMM_4561           4561    // Parametro di utilizzo immediato
#define   R_IMM_4562           4562    // Parametro di utilizzo immediato
#define   R_IMM_4563           4563    // Parametro di utilizzo immediato
#define   R_IMM_4564           4564    // Parametro di utilizzo immediato
#define   R_IMM_4565           4565    // Parametro di utilizzo immediato
#define   R_IMM_4566           4566    // Parametro di utilizzo immediato
#define   R_IMM_4567           4567    // Parametro di utilizzo immediato
#define   R_IMM_4568           4568    // Parametro di utilizzo immediato
#define   R_IMM_4569           4569    // Parametro di utilizzo immediato
#define   R_IMM_4580           4580    // Parametro di utilizzo immediato
#define   R_IMM_4581           4581    // Parametro di utilizzo immediato
#define   R_IMM_4582           4582    // Parametro di utilizzo immediato
#define   R_IMM_4583           4583    // Parametro di utilizzo immediato
#define   R_IMM_4584           4584    // Parametro di utilizzo immediato
#define   R_IMM_4585           4585    // Parametro di utilizzo immediato
#define   R_IMM_4586           4586    // Parametro di utilizzo immediato
#define   R_IMM_4587           4587    // Parametro di utilizzo immediato
#define   R_IMM_4588           4588    // Parametro di utilizzo immediato
#define   R_IMM_4589           4589    // Parametro di utilizzo immediato
#define   R_IMM_4590           4590    // Parametro di utilizzo immediato
#define   R_IMM_4591           4591    // Parametro di utilizzo immediato
#define   R_IMM_4592           4592    // Parametro di utilizzo immediato
#define   R_IMM_4593           4593    // Parametro di utilizzo immediato
#define   R_IMM_4594           4594    // Parametro di utilizzo immediato
#define   R_IMM_4595           4595    // Parametro di utilizzo immediato
#define   R_IMM_4596           4596    // Parametro di utilizzo immediato
#define   R_IMM_4597           4597    // Parametro di utilizzo immediato
#define   R_IMM_4598           4598    // Parametro di utilizzo immediato
#define   R_IMM_4599           4599    // Parametro di utilizzo immediato

//**************** LETTURA SDO PER CORRENTE E TENSIONE SU MORSE MOTORIZZATE *****************

#define   R_ACTUAL_CURRENT_M07        4707 // Corrente attuale letta dalla morsa M07
#define   R_ACTUAL_CURRENT_M08        4708 // Corrente attuale letta dalla morsa M08
#define   R_ACTUAL_CURRENT_M09        4709 // Corrente attuale letta dalla morsa M09
#define   R_ACTUAL_CURRENT_M10        4710 // Corrente attuale letta dalla morsa M10
#define   R_ACTUAL_CURRENT_M11        4711 // Corrente attuale letta dalla morsa M11
#define   R_ACTUAL_CURRENT_M12        4712 // Corrente attuale letta dalla morsa M12
#define   R_ACTUAL_CURRENT_M13        4713 // Corrente attuale letta dalla morsa M13
#define   R_ACTUAL_CURRENT_M14        4714 // Corrente attuale letta dalla morsa M14
#define   R_ACTUAL_CURRENT_M15        4715 // Corrente attuale letta dalla morsa M15
#define   R_ACTUAL_CURRENT_M16        4716 // Corrente attuale letta dalla morsa M16
#define   R_ACTUAL_CURRENT_M17        4717 // Corrente attuale letta dalla morsa M17
#define   R_ACTUAL_CURRENT_M18        4718 // Corrente attuale letta dalla morsa M18

#define   R_ACTUAL_VOLT_M07           4737 // Tensione attuale letta dalla morsa M07
#define   R_ACTUAL_VOLT_M08           4738 // Tensione attuale letta dalla morsa M08
#define   R_ACTUAL_VOLT_M09           4739 // Tensione attuale letta dalla morsa M09
#define   R_ACTUAL_VOLT_M10           4740 // Tensione attuale letta dalla morsa M10
#define   R_ACTUAL_VOLT_M11           4741 // Tensione attuale letta dalla morsa M11
#define   R_ACTUAL_VOLT_M12           4742 // Tensione attuale letta dalla morsa M12
#define   R_ACTUAL_VOLT_M13           4743 // Tensione attuale letta dalla morsa M13
#define   R_ACTUAL_VOLT_M14           4744 // Tensione attuale letta dalla morsa M14
#define   R_ACTUAL_VOLT_M15           4745 // Tensione attuale letta dalla morsa M15
#define   R_ACTUAL_VOLT_M16           4746 // Tensione attuale letta dalla morsa M16
#define   R_ACTUAL_VOLT_M17           4747 // Tensione attuale letta dalla morsa M17
#define   R_ACTUAL_VOLT_M18           4748 // Tensione attuale letta dalla morsa M18

#define   R_PARAM_MAX_CURRENT_M07     4767 // Paramentro corrente massima nell'azionamento morsa M07
#define   R_PARAM_MAX_CURRENT_M08     4768 // Paramentro corrente massima nell'azionamento morsa M08
#define   R_PARAM_MAX_CURRENT_M09     4769 // Paramentro corrente massima nell'azionamento morsa M09
#define   R_PARAM_MAX_CURRENT_M10     4770 // Paramentro corrente massima nell'azionamento morsa M10
#define   R_PARAM_MAX_CURRENT_M11     4771 // Paramentro corrente massima nell'azionamento morsa M11
#define   R_PARAM_MAX_CURRENT_M12     4772 // Paramentro corrente massima nell'azionamento morsa M12
#define   R_PARAM_MAX_CURRENT_M13     4773 // Paramentro corrente massima nell'azionamento morsa M13
#define   R_PARAM_MAX_CURRENT_M14     4774 // Paramentro corrente massima nell'azionamento morsa M14
#define   R_PARAM_MAX_CURRENT_M15     4775 // Paramentro corrente massima nell'azionamento morsa M15
#define   R_PARAM_MAX_CURRENT_M16     4776 // Paramentro corrente massima nell'azionamento morsa M16
#define   R_PARAM_MAX_CURRENT_M17     4777 // Paramentro corrente massima nell'azionamento morsa M17
#define   R_PARAM_MAX_CURRENT_M18     4778 // Paramentro corrente massima nell'azionamento morsa M18

#define   R_MIN_CURRENT_M07           4813 // Valore minimo della corrente morsa  M07
#define   R_MAX_CURRENT_M07           4814 // Valore massimo della corrente morsa M07
#define   R_MIN_CURRENT_M08           4815 // Valore minimo della corrente morsa  M08
#define   R_MAX_CURRENT_M08           4816 // Valore massimo della corrente morsa M08
#define   R_MIN_CURRENT_M09           4817 // Valore minimo della corrente morsa  M09
#define   R_MAX_CURRENT_M09           4818 // Valore massimo della corrente morsa M09
#define   R_MIN_CURRENT_M10           4819 // Valore minimo della corrente morsa  M10
#define   R_MAX_CURRENT_M10           4820 // Valore massimo della corrente morsa M10
#define   R_MIN_CURRENT_M11           4821 // Valore minimo della corrente morsa  M11
#define   R_MAX_CURRENT_M11           4822 // Valore massimo della corrente morsa M11
#define   R_MIN_CURRENT_M12           4823 // Valore minimo della corrente morsa  M12
#define   R_MAX_CURRENT_M12           4824 // Valore massimo della corrente morsa M12
#define   R_MIN_CURRENT_M13           4825 // Valore minimo della corrente morsa  M13
#define   R_MAX_CURRENT_M13           4826 // Valore massimo della corrente morsa M13
#define   R_MIN_CURRENT_M14           4827 // Valore minimo della corrente morsa  M14
#define   R_MAX_CURRENT_M14           4828 // Valore massimo della corrente morsa M14
#define   R_MIN_CURRENT_M15           4829 // Valore minimo della corrente morsa  M15
#define   R_MAX_CURRENT_M15           4830 // Valore massimo della corrente morsa M15
#define   R_MIN_CURRENT_M16           4831 // Valore minimo della corrente morsa  M16
#define   R_MAX_CURRENT_M16           4832 // Valore massimo della corrente morsa M16
#define   R_MIN_CURRENT_M17           4833 // Valore minimo della corrente morsa  M17
#define   R_MAX_CURRENT_M17           4834 // Valore massimo della corrente morsa M17
#define   R_MIN_CURRENT_M18           4835 // Valore minimo della corrente morsa  M18
#define   R_MAX_CURRENT_M18           4836 // Valore massimo della corrente morsa M18

#define   R_MIN_VOLT_M07              4863 // Valore minimo della tensione morsa  M07
#define   R_MAX_VOLT_M07              4864 // Valore massimo della tensione morsa M07
#define   R_MIN_VOLT_M08              4865 // Valore minimo della tensione morsa  M08
#define   R_MAX_VOLT_M08              4866 // Valore massimo della tensione morsa M08
#define   R_MIN_VOLT_M09              4867 // Valore minimo della tensione morsa  M09
#define   R_MAX_VOLT_M09              4868 // Valore massimo della tensione morsa M09
#define   R_MIN_VOLT_M10              4869 // Valore minimo della tensione morsa  M10
#define   R_MAX_VOLT_M10              4870 // Valore massimo della tensione morsa M10
#define   R_MIN_VOLT_M11              4871 // Valore minimo della tensione morsa  M11
#define   R_MAX_VOLT_M11              4872 // Valore massimo della tensione morsa M11
#define   R_MIN_VOLT_M12              4873 // Valore minimo della tensione morsa  M12
#define   R_MAX_VOLT_M12              4874 // Valore massimo della tensione morsa M12
#define   R_MIN_VOLT_M13              4875 // Valore minimo della tensione morsa  M13
#define   R_MAX_VOLT_M13              4876 // Valore massimo della tensione morsa M13
#define   R_MIN_VOLT_M14              4877 // Valore minimo della tensione morsa  M14
#define   R_MAX_VOLT_M14              4878 // Valore massimo della tensione morsa M14
#define   R_MIN_VOLT_M15              4879 // Valore minimo della tensione morsa  M15
#define   R_MAX_VOLT_M15              4880 // Valore massimo della tensione morsa M15
#define   R_MIN_VOLT_M16              4881 // Valore minimo della tensione morsa  M16
#define   R_MAX_VOLT_M16              4882 // Valore massimo della tensione morsa M16
#define   R_MIN_VOLT_M17              4883 // Valore minimo della tensione morsa  M17
#define   R_MAX_VOLT_M17              4884 // Valore massimo della tensione morsa M17
#define   R_MIN_VOLT_M18              4885 // Valore minimo della tensione morsa  M18
#define   R_MAX_VOLT_M18              4886 // Valore massimo della tensione morsa M18

#define   R_OUTPUT_PWR_M07            4907 // Valore potenza in uscita morsa M07
#define   R_OUTPUT_PWR_M08            4908 // Valore potenza in uscita morsa M08
#define   R_OUTPUT_PWR_M09            4909 // Valore potenza in uscita morsa M09
#define   R_OUTPUT_PWR_M10            4910 // Valore potenza in uscita morsa M10
#define   R_OUTPUT_PWR_M11            4911 // Valore potenza in uscita morsa M11
#define   R_OUTPUT_PWR_M12            4912 // Valore potenza in uscita morsa M12
#define   R_OUTPUT_PWR_M13            4913 // Valore potenza in uscita morsa M13
#define   R_OUTPUT_PWR_M14            4914 // Valore potenza in uscita morsa M14
#define   R_OUTPUT_PWR_M15            4915 // Valore potenza in uscita morsa M15
#define   R_OUTPUT_PWR_M16            4916 // Valore potenza in uscita morsa M16
#define   R_OUTPUT_PWR_M17            4917 // Valore potenza in uscita morsa M17
#define   R_OUTPUT_PWR_M18            4918 // Valore potenza in uscita morsa M18

#define   R_COUNTER_FILTRO_M07        4937 // Contatore intervento filtro su posizione richiesta morsa M07
#define   R_COUNTER_FILTRO_M08        4938 // Contatore intervento filtro su posizione richiesta morsa M08
#define   R_COUNTER_FILTRO_M09        4939 // Contatore intervento filtro su posizione richiesta morsa M09
#define   R_COUNTER_FILTRO_M10        4940 // Contatore intervento filtro su posizione richiesta morsa M10
#define   R_COUNTER_FILTRO_M11        4941 // Contatore intervento filtro su posizione richiesta morsa M11
#define   R_COUNTER_FILTRO_M12        4942 // Contatore intervento filtro su posizione richiesta morsa M12
#define   R_COUNTER_FILTRO_M13        4943 // Contatore intervento filtro su posizione richiesta morsa M13
#define   R_COUNTER_FILTRO_M14        4944 // Contatore intervento filtro su posizione richiesta morsa M14
#define   R_COUNTER_FILTRO_M15        4945 // Contatore intervento filtro su posizione richiesta morsa M15
#define   R_COUNTER_FILTRO_M16        4946 // Contatore intervento filtro su posizione richiesta morsa M16
#define   R_COUNTER_FILTRO_M17        4947 // Contatore intervento filtro su posizione richiesta morsa M17
#define   R_COUNTER_FILTRO_M18        4948 // Contatore intervento filtro su posizione richiesta morsa M18

// R5000 ^//////////////////////////////////////////////////////////////////////////////////////////

// aree R 5000 della gestione iso sono usate solo in Spartaco
#define   R_LUNGH_STRUCT_SPINDLE      5000 // Lunghezza struttura mandrino (ingombro massimo)
#define   R_LARGH_STRUCT_SPINDLE      5001 // Larghezza parte bassa struttura mandrino sino al centro utensile
#define   R_NEXT_POS_ASSE_A           5002 // Posizione asse A prossima lavorazione
#define   R_NEXT_POS_ASSE_C           5003 // Posizione asse C prossima lavorazione
#define   R_NEXT_POS_ASSE_X           5004 // Posizione asse X prossima lavorazione
#define   R_NEXT_POS_ASSE_Y           5005 // Posizione asse Y prossima lavorazione
#define   R_NEXT_POS_ASSE_Z           5006 // Posizione asse Z prossima lavorazione
#define   R_NEXT_R330                 5007 // Quota di approccio R330 della prossima lavorazione


#define   R_OFFSET_Y_TESTINA          5015 // Offset Y testina 
#define   R_OFFSET_Z_TESTINA          5016 // Offset Z testina
#define   R_ANGOLO_UT_SU_TEST         5017 // Angolo utensile montato su testina
                                           // =0 per utensile A testina orientata per testa coda (utensile A lavora su faccia 4)
                                           // =180 per utensile B testina orientata per testa coda (utensile B lavora su faccia 5)
                                           // =90 per utensile B testina orientata per fronte-retro (utensile B lavora su faccia 2, faccia anteriore)
                                           // =270 per utensile A testina orientata per fronte-retro (utensile A lavora su faccia 3, faccia posteriore)

#define   R_GEST_AVA_TOOL_ROTTO       5920 // Gestione utensili avanzata: utensile rotto
#define   R_VER_TOOL_1_16             5921 // Lista utensili in uso da T1 a T16 nell'isomg in gestione utensili avanzata
#define   R_VER_TOOL_17_32            5922 // Lista utensili in uso da T17 a T32 nell'isomg in gestione utensili avanzata (usata solo su Satellite XT EVO)

#define   R_MORSE_1_12_ASSOCIATE      5923 // Array morse associate al pezzo da spostare (dalla 1 alla 12)
#define   R_MORSE_13_24_ASSOCIATE     5924 // Array morse associate al pezzo da spostare (dalla 13 alla 24)

#define   R_OFFSET_POS_PEZZO          5925 // (solo CometR) Delta di spostamento pezzo
#define   R_MORSA_MASTER              5926 // (solo CometR) Numero morsa che comanda (master)
#define   R_MM_SCOST_X_LAMA           5927 // (solo CometR) mm di scostamento in X della lama

#define   R_FINE_RIPOS_MORSE_MOT_PEND 5928 // Ciclo di riposizionamento morse motorizzate in pendolare dopo tagli di separazione attivo
#define   R_NUM_MORSA_MOT_IN_RIP      5929 // Numero morsa motorizzata in riposionamento dopo tagli di separazione

#define   R_ISO_DRILL_CAMAELON_CN01   5930 // Variabile 01 usata da Drill in programmazione ISO DRILL-CAMAELON
#define   R_ISO_DRILL_CAMAELON_CN02   5931 // Variabile 02 usata da Drill in programmazione ISO DRILL-CAMAELON
#define   R_ISO_DRILL_CAMAELON_CN03   5932 // Variabile 03 usata da Drill in programmazione ISO DRILL-CAMAELON
#define   R_ISO_DRILL_CAMAELON_CN04   5933 // Variabile 04 usata da Drill in programmazione ISO DRILL-CAMAELON
#define   R_ISO_DRILL_CAMAELON_CN05   5934 // Variabile 05 usata da Drill in programmazione ISO DRILL-CAMAELON
#define   R_ISO_DRILL_CAMAELON_CN06   5935 // Variabile 06 usata da Drill in programmazione ISO DRILL-CAMAELON
#define   R_ISO_DRILL_CAMAELON_CN07   5936 // Variabile 07 usata da Drill in programmazione ISO DRILL-CAMAELON

#define   R_AUTOFEED_PEZZO_LIBERO     5940 // Ciclo in autofeed a pezzo libero
#define   R_MORSE_1_12_DA_OPEN_AF     5941 // Array delle morse da aprire (dalla 1 alla 12) in autofeed dopo taglio
#define   R_MORSE_13_24_DA_OPEN_AF    5942 // Array delle morse da aprire (dalla 13 alla 24) in autofeed dopo taglio

#define   R_APPR_RAGGIO_RACC          5957 // =0 esegue l'approccio tangenziale sul lato lungo, =1 esegue l'approccio tangenziale sul raggio raccordo

#define   R_POS_BATT_SX1_REQ          5958 /* Posizione richiesta da Hdrill per la battuta SX1 (su R4/S4/R6/S6 la battuta SX diventa fissa, senza sensore)
                                              0= battuta SX1 non usata, 
                                              1= posizione battuta SX1 esterna (X1L), 
                                              2= posizione battuta SX1 intermedia (X2L), 
                                              3= posizione battuta SX1 interna (X3L) */

#define   R_POS_BATT_DX4_REQ          5959 /* Posizione richiesta da Hdrill per la battuta DX4 (su S4 e S6 la battuta DX per ora resta a 4 posizioni, in futuro diventerà fissa, senza sensore)
                                              0= battuta DX4 non usata, 
                                              1= posizione battuta DX4 esterna (X1R), 
                                              2= posizione battuta DX4 intermedia (X2R), 
                                              3= posizione battuta DX4 intermedia (X3R),
                                              4= posizione battuta DX4 interna (X4R) */

#define   R_ISO_DRILL_CAMAELON        5960 //ISO nuova gestione Drill-Camaelon
#define   R_NUM_BARR_IN_USO           5961 //Numero barriera attualmente in uso (per ISO Drill-Camaelon)

#define   R_NUM_MASTCLAMP_LAV         5965 // Numero morsa master dopo MOVPIECE.SXT (per applicare correzione in X alla lavorazione)

#define   R_MODO_ACC_SHAPE_3D         5980 // Modo accelerazione in shape 3D: usata in RTCP_PAR_ON
#define   R_PERC_LAV_IN_HDRILL        5981 // Valore percentuale delle lavorazioni eseguite in HDRILL

#define   R_TIPO_ISO_MANUTENZ         5982 // 0: ciclo normale;  1: Carico autom. ut.;  2: Scarico autom. ut.;  3: Rilievo dimensioni utensile;  4: Rilievo dimensione pezzo Y (macro TAST_LARGHEZZA.***);  5: Rilievo dimensione pezzo Z (macro TAST_ALTEZZA.***)

// R6000 ^//////////////////////////////////////////////////////////////////////////////////////////

#define     R_ASSE_X                  6010 // appoggio Asse X presente 
#define     R_ASSE_Y                  6011 // appoggio Asse Y presente 
#define     R_ASSE_Z                  6012 // appoggio Asse Z presente 
#define     R_ASSE_A                  6013 // appoggio Asse A presente 
#define     R_ASSE_C                  6014 // appoggio Asse C presente 
#define     R_ASSE_W                  6015 // appoggio Asse W presente 

//#define     R_QUOTA_REALE_X           6020 // 
//
//#define     R_QUOTA_REALE_OLD_X       6021 // 

#define     R_6029                    6029 // flag: 1=> correzioni assi già attive ,  0=> correzioni assi da fare     
////#define     R_6030                    6030 // flag: 1=> asse X portato a SX da GOTOSX,  2=> asse X portato a DX da GOTODX.

#define     R_6031                    6031 // Quota minima  tra R_XMAX_AREASX e quella che porta il mandrino fuori ingombro diaframma (R740-R744)
#define     R_6032                    6032 // Quota massima tra R_XMAX_AREADX e quella che porta il mandrino fuori ingombro diaframma (R740+R744)

#define     R_DIST_MAGUT_CARTER_SX    6033 // Distanza tra carter SX e mag.ut (mosso dagli assi W/X)

#define     R_6034                    6034 // Usata in CAMBIOUT.CS4

////#define     R_DIST_P_X                6035 // distanza tra assi P X
////#define     R_DIST_X_H                6036 // distanza tra assi X H
#define     R_6838                    6838 // (Solo CometR) Usata in 8.CR4 e SCOST_PEZZO.CR4 su macchina dinamica (scostamento pezzo eseguito, serve per far tornare indietro il pezzo)
////#define     R_NO_HOLD_X_DA_PH         6039 // Disabilita hold su asse X da assi P e H durante il riferimento
#define     R_INSEGUIMENTO_X          6040 // Errore inseguimento asse X

#define	    R_ABI_VOL			      6041 // Se =1 abilita gestione volantini
#define     R_ASSE_ATTIVO_VOL	      6042 // Numero asse attivo sui volantini
#define     R_VELOCE_VOL		      6043 // Se =0 incrementi volantini = millesimi, se =1 decimi
#define     R_READ_ACC_ASSI_VOL       6044 // Appoggio per lettura accelerazione assi volantino
#define     R_WRITE_ACC_ASSI_VOL      6045 // Appoggio per scrittura accelerazione assi volantino

#define     R_ASSI_CNC1_RIF           6051 // Assi cnc master riferiti
#define     R_ASSI_CNC2_RIF           6052 // Assi cnc slave  riferiti

#define     R_MACCHINA_IN_SEMIAUTO    6053 // Appoggio input macchina in semiautomatico

#define     R_MEM_DIM_TOOL            6054 // Memoria Dimensione ut. da depositare per CAMBIOUT (quando è in esecuzione CAMBIOUT è già impostata la dimensione ut. successivo)

#define     R_TOT_CICLI_PRESS_MANDR   6055 // Pressurizzazione mandrino: Durata impostata in confmac, trasformata in cicli plc
#define     R_NUM_CICLI_PRESS_MANDR   6056 // Pressurizzazione mandrino: Durata impostata in confmac, trasformata in cicli plc

#define     R_CKTOOL_ESEGUITO            6057   // 1: memoria di verifica integrita utensile INIZIATA/ESEGUITA
                                                // 2: memoria di rilievo  lunghezza utensile INIZIATO/ESEGUITO

#define     R_UT_NOK                     6058   // Utensile rotto PLC > CNC > Hdrill

#define     R_TEST_MORSE_BF              6060   // Abilita test simulazione richieste ap/ch morse in automatico da selettori o da multiprocesso

#define     R_MORSA_DA_CH_AUT_S_NN       6061   // AUTOMATICO: TEST: Attivazione PLCM di CHIUSURA_IN_BASSA_FORZA morse_SX, da selettori
#define     R_MORSA_DA_AP_AUT_S_NN       6062   // AUTOMATICO: TEST: Attivazione PLCM di APERTURA_IN_ALTA_FORZA morse_SX, da selettori

#define     R_Apri_in_AF_Morsa_NN        6063   // AUTOMATICO: TEST: Attivazione PLCM di APERTURA_IN_ALTA_FORZA morse_SX, DA MULTIPROCESSO
#define     R_Chiudi_in_BF_Morsa_NN      6064   // AUTOMATICO: TEST: Attivazione PLCM di CHIUSURA_IN_BASSA_FORZA morse_SX, DA MULTIPROCESSO
#define     R_Chiudi_in_AF_Morsa_NN      6065   // AUTOMATICO: TEST: Attivazione PLCM di CHIUSURA_IN_ALTA_FORZA morse_SX, DA MULTIPROCESSO
#define     R_Disat_chius_in_AF_Morsa_NN 6066   // AUTOMATICO: TEST: Attivazione PLCM di Disattiva_chiusura_in_alta_forza morse_SX, DA MULTIPROCESSO

#define     R6070                        6070   // Usata in ZMIN_SP.CS4
#define     R6071                        6071   // Usata in ZMIN_SP.CS4
#define     R6072                        6072   // Usata in ZMIN_SP.CS4
#define     R6073                        6073   // Usata in ZMIN_SP.CS4
#define     R6074                        6074   // Usata in ZMIN_SP.CS4
#define     R6075                        6075   // Usata in ZMIN_SP.CS4
#define     R6076                        6076   // Usata in ZMIN_SP.CS4

#define     R6080                        6080   // Usata in ZMIN_SP.CS4
#define     R6081                        6081   // Usata in ZMIN_SP.CS4
#define     R6082                        6082   // Usata in ZMIN_SP.CS4
#define     R6083                        6083   // Usata in ZMIN_SP.CS4
#define     R6084                        6084   // Usata in ZMIN_SP.CS4
#define     R6085                        6085   // Usata in ZMIN_SP.CS4

#define     R6087                        6087   // Usata in Z_RTCP.CS4
#define     R6088                        6088   // Usata in Z_RTCP.CS4

#define     R6090                        6090   // Usata in ZMIN_SP.CS4 e in EXIT_MAN.CS4
#define     R_DIAG_OFFSET_SPINDLE_TOOL   6091   // Diagonale calcolata usando gli offset mandrino e lunghezza utensile

#define     R_MARPOSS_TOUCH	             6092   // Tastatore in battuta
#define     R_PROBE_ACTIVE               6093   // Tastatura Marposs in corso
#define     R_PROBE_ERROR                6094   // Errore Marposs durante tastatura

#define     R_POS_TOUCH_PROBE_AX_X       6095   // Quota asse X al momento del touch rispetto all'origine attiva
#define     R_POS_TOUCH_PROBE_AX_Y       6096   // Quota asse Y al momento del touch rispetto all'origine attiva
#define     R_POS_TOUCH_PROBE_AX_Z       6097   // Quota asse Z al momento del touch rispetto all'origine attiva

#define     R_CAMB_MAN                   6100   // Cambio utensili in magazzino assistito

#define     R_VAL_X_IN_TOUCH_LATCH       6101   // Usata inMarposs.c per debug
#define     R_VAL_Y_IN_TOUCH_LATCH       6102   // Usata inMarposs.c per debug
#define     R_VAL_Z_IN_TOUCH_LATCH       6103   // Usata inMarposs.c per debug

#define     R_APP_MORSA_INPOS_SIMU       6110   // Appoggio indice var R posizione reale morse per la simulazione Simon

#define     R_APP_XYA_IN_POS            6114   // Appoggio assi X,Y,A già posizionati alle quote di inizio lavorazione

#define     R_Z_SCAVALCA_MORSE           6116   // Appoggio quota calcolata di Z scavalcamento morse in centro di rotazione struttura mandrino

#define     R_DEBUG_NUM_MATRICOLA        6119   // Variabile di debug numero di matricola macchina

#define     R_DIST1_AX_X           6120 // 
#define     R_DIST1_AX_Y           6121 // 
#define     R_DIST1_AX_Z           6122 // 
#define     R_DIST1_AX_A           6123 //
#define     R_DIST1_AX_C           6124 //
#define     R_DIST1_AX_W           6125 // 

#define     R_DIST2_AX_X           6130 // 
#define     R_DIST2_AX_Y           6131 // 
#define     R_DIST2_AX_Z           6132 // 
#define     R_DIST2_AX_A           6133 // 
#define     R_DIST2_AX_C           6134 //
#define     R_DIST2_AX_W           6135 // 

//-- Battuta di precisione (operative) --------------------------------------/
#define   R_BATT_PREC_DIS          6146  /* Battuta di precisione disinserita */
#define   R_BATT_PREC_PREMUTA      6147  /* Battuta di precisione premuta */
#define   R_POS_BATT_PREC          6148  /* Quota attuale battuta di precisione */


// contatori movimenti assi morse
////#define   R_MORSA_07_MOSSA_CNT     6151  // 
////#define   R_MORSA_08_MOSSA_CNT     6152  // 
////#define   R_MORSA_09_MOSSA_CNT     6153  // 
#define   R_MORSA_10_MOSSA_CNT     6154  // 
#define   R_MORSA_11_MOSSA_CNT     6155  // 
#define   R_MORSA_12_MOSSA_CNT     6156  // 
#define   R_MORSA_13_MOSSA_CNT     6157  // 
#define   R_MORSA_14_MOSSA_CNT     6158  // 
#define   R_MORSA_15_MOSSA_CNT     6159  // 
////#define   R_MORSA_16_MOSSA_CNT     6160  // 
////#define   R_MORSA_17_MOSSA_CNT     6161  // 
////#define   R_MORSA_18_MOSSA_CNT     6162  // 


#define   R_VIS_APPOVFED           6170  // Visualizza APPOVFED
#define   R_VIS_APPOVSPE           6171  // Visualizza APPOVSPE
#define   R_VIS_OVFED              6172  // Visualizza OVFED   
#define   R_VIS_OVRAP              6173  // Visualizza OVRAP   
#define   R_VIS_OVSPE              6174  // Visualizza OVSPE   

// ****************************************************************************************************************************************
#define   R_CONT_DISA_DA_PP_X      6180  // Asse X : Contatore diassociazione da PP SH_OFF_n.CS4    (R non condivisa, gestita solo da plc)
#define   R_CONT_DISA_DA_PP_W      6181  // Asse W : Contatore diassociazione da PP SH_OFF_n.CS4    (R non condivisa, gestita solo da plc)
////#define   R_CONT_DISA_DA_PP_P      6182  // Asse P : Contatore diassociazione da PP SH_OFF_n.CS4    (R non condivisa, gestita solo da plc)
////#define   R_CONT_DISA_DA_PP_H      6183  // Asse H : Contatore diassociazione da PP SH_OFF_n.CS4    (R non condivisa, gestita solo da plc)

// 6185 occupato su cr4
// 6186 occupato su cr4
#define   R_CONT_ASSO_DA_PP_X      6190  // Asse X : Contatore associazione   da PP SH_ON_n.CS4   (R non condivisa, gestita solo da plc)
#define   R_CONT_ASSO_DA_PP_W      6191  // Asse W : Contatore associazione   da PP SH_ON_n.CS4   (R non condivisa, gestita solo da plc)
////#define   R_CONT_ASSO_DA_PP_P      6192  // Asse P : Contatore associazione   da PP SH_ON_n.CS4   (R non condivisa, gestita solo da plc)
////#define   R_CONT_ASSO_DA_PP_H      6193  // Asse H : Contatore associazione   da PP SH_ON_n.CS4   (R non condivisa, gestita solo da plc)
// ****************************************************************************************************************************************


//-- Variabili di diverso utilizzo ------------------------------------------/
#define   R_CONT_CKMOV_W           6204 // Contatore usato in CKMOV_W (riposizionamenti attuali)
#define   R6205                    6205 // Contatore usato in CKMOV_W  (riposizionamenti totali da avvio CN)
#define   R_MORSE_CH_IN_BP         6206 // Appoggio morse chuse in bassa pressione
#define   R_MORSE_CH_IN_HP         6207 // Appoggio morse chuse in alta pressione
#define   R_QUOTA_W                6208 // Quota asse W in G53
#define   R_RIP_MOV2               6210 // 
#define   R_LIBERA_M07_M18         6211 // 

#define   R_SCAR_PEZZI_MULTI_ESEG  6213 // Scarico pezzi in multipezzo eseguito (causale di WAIT con R505=5)
//#define   R_SCAR_PEZZI_SX_ESEG     6214 // (SOLO R6) Scarico pezzi in pendolare SX eseguito (causale di WAIT_P_SX con R505=5)
//#define   R_SCAR_PEZZI_DX_ESEG     6215 // (SOLO R6) Scarico pezzi in pendolare DX eseguito (causale di WAIT_P_DX con R505=5)

#define   R_DIST_X_ABS             6226 // Distanza da percorrere dall'asse X (caricata dal PLC) valore assoluto, senza segno
#define   R_DIST_Y_ABS             6227 // Distanza da percorrere dall'asse Y (caricata dal PLC) valore assoluto, senza segno
#define   R_DIST_Z_ABS             6228 // Distanza da percorrere dall'asse Z (caricata dal PLC) valore assoluto, senza segno

#define   R_LUBRICA_FREQ_CAMPLUS   6231 // Lubrica: freq da camplus, variabile, impostabile in base alle necessità di lubrificazione del pezzo da lavorare
#define   R_LUBRICA_DUTY_CYCLE     6232 // Lubrica: duty cycle calcolato nel plc
#define   R_LUBRICA_PERIODO        6233 // Lubrica: periodo, durata di ogni ciclo di lubrificazione (tempo pompa ON + tempo pompa OFF)
#define   R_LUBRICA_TEMPO_ON       6234 // Lubrica: tempo pompa ON 
#define   R_LUBRICA_TEMPO_OF       6235 // Lubrica: tempo pompa OFF
#define   R_LUBRICA_DUTY_COEFF_ANG 6236 // Lubrica: coeff. angolare della retta del duty cycle

#define   R_MEM_DIR_ROT            6241  // MEMORIA DIREZIONE ROTAZIONE: 0 = rotazione oraria mandrino; 1 = rotazione antioraria 

		#define   R_COLLAUDO_03            6243 // 1 = pausa di debug in CKTOOL.CR6
		#define   R_COLLAUDO_04            6244 // simula ingresso presetter in cktool.c
		//#define   R_COLLAUDO_05            6245 // 
		//#define   R_COLLAUDO_06            6246 // 
		//#define   R_COLLAUDO_07            6247 // 
		//#define   R_COLLAUDO_08            6248 // 
		//#define   R_COLLAUDO_09            6249 // 

#define     R_CONT_RES_ABIL_AX_X         6251   // Asse X : Contatore Reset abilitazione da PLC   (R non condivisa, gestita solo da plc)
#define     R_CONT_RES_ABIL_AX_Y         6252   // Asse Y : Contatore Reset abilitazione da PLC   (R non condivisa, gestita solo da plc)
#define     R_CONT_RES_ABIL_AX_Z         6253   // Asse Z : Contatore Reset abilitazione da PLC   (R non condivisa, gestita solo da plc)
#define     R_CONT_RES_ABIL_AX_A         6254   // Asse A : Contatore Reset abilitazione da PLC   (R non condivisa, gestita solo da plc)
#define     R_CONT_RES_ABIL_AX_C         6255   // Asse C : Contatore Reset abilitazione da PLC   (R non condivisa, gestita solo da plc)
#define     R_CONT_RES_ABIL_AX_W         6256   // Asse W : Contatore Reset abilitazione da PLC   (R non condivisa, gestita solo da plc)



#define     R_APP_QUOTA_A_IN_POSAXES     6260   // Appoggio quota asse A usata in POS_AXES.CS4
#define     R_APP_PROIEZ_Y_TESTINA       6261   // Appoggio proiezione in Y della parte bassa della struttura testina
#define     R_APP_QUOTA_SCAV_LATER_Y     6262   // Appoggio quota di scavalcamento laterale profilo con testina rispetto origine attiva (usata in POS_AXES.CS4)
#define     R_APP_R330                   6263   // Appoggio quota di fuori ingombro per asse Z rispetto origine attiva (usata in POS_AXES.CS4)

#define     R_APP_QUOTA_LAV_Y_SCAV_LATER 6265   // Memoria quota Y di lavorazione per calcolo dello scavalcamento laterale testina
#define     R_APP_ZOUT_TESTINA           6267   // Appoggio quota asse Z ottimizzata per fuori ingombro con testina
#define     R_LUNG_MAND_UT               6268   // Appoggio lunghezza mandrino+lungh. utensile (per utensile diretto), invece per testina lunghezza mandrino+dimensione testina

///////////////////////////////////////////////////////////////////////////////////////////////////
// Inizio Lettura parametri Ethercat degli assi 

#define R_VOLT_BATTERIA_ACT_ASSE_X     6300 // Livello attuale batteria encoder asse X
#define R_VOLT_BATTERIA_ACT_ASSE_Y     6301 // Livello attuale batteria encoder asse Y
#define R_VOLT_BATTERIA_ACT_ASSE_Z     6302 // Livello attuale batteria encoder asse Z
#define R_VOLT_BATTERIA_ACT_ASSE_A     6303 // Livello attuale batteria encoder asse A
#define R_VOLT_BATTERIA_ACT_ASSE_W     6304 // Livello attuale batteria encoder asse W

#define R_PERCENT_LOAD_ASSE_X          6310 // Percentuale di carico asse X
#define R_PERCENT_LOAD_ASSE_Y          6311 // Percentuale di carico asse Y
#define R_PERCENT_LOAD_ASSE_Z          6312 // Percentuale di carico asse Z
#define R_PERCENT_LOAD_ASSE_A          6313 // Percentuale di carico asse A
#define R_PERCENT_LOAD_ASSE_W          6314 // Percentuale di carico asse W

#define R_MAX_PERCENT_LOAD_ASSE_X      6320 // Percentuale di carico massima asse X
#define R_MAX_PERCENT_LOAD_ASSE_Y      6321 // Percentuale di carico massima asse Y
#define R_MAX_PERCENT_LOAD_ASSE_Z      6322 // Percentuale di carico massima asse Z
#define R_MAX_PERCENT_LOAD_ASSE_A      6323 // Percentuale di carico massima asse A
#define R_MAX_PERCENT_LOAD_ASSE_W      6324 // Percentuale di carico massima asse W

#define R_PEAK_LOAD_ASSE_X             6330 // Picco di carico asse X
#define R_PEAK_LOAD_ASSE_Y             6331 // Picco di carico asse Y
#define R_PEAK_LOAD_ASSE_Z             6332 // Picco di carico asse Z
#define R_PEAK_LOAD_ASSE_A             6333 // Picco di carico asse A
#define R_PEAK_LOAD_ASSE_W             6334 // Picco di carico asse W

#define R_VERS_FIRMW_ASSE_X            6340 // Versione firmware Azionamento Delta asse X
#define R_VERS_FIRMW_ASSE_Y            6341 // Versione firmware Azionamento Delta asse Y
#define R_VERS_FIRMW_ASSE_Z            6342 // Versione firmware Azionamento Delta asse Z
#define R_VERS_FIRMW_ASSE_A            6343 // Versione firmware Azionamento Delta asse A
#define R_VERS_FIRMW_ASSE_W            6344 // Versione firmware Azionamento Delta asse W

// Fine Lettura parametri Ethercat degli assi 
///////////////////////////////////////////////////////////////////////////////////////////////////


#define R_6360                         6360 // 1:     Scarico utensile assistito dal magazzino tramite mandrino
                                            // 21/22: Carico  utensile assistito nel magazzino tramite mandrino

#define R_6361                         6361 // Utensile da caricare/scaricare nel/dal magazzino tramite mandrino

// PREDISPOSTO:
	#define R_CONT_RES_ABIL_M07            6370 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M08            6371 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M09            6372 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M10            6373 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M11            6374 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M12            6375 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M13            6376 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M14            6377 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M15            6378 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M16            6379 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M17            6380 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)
	#define R_CONT_RES_ABIL_M18            6381 // Contatore Reset abilitazione asse da PLC   (R non condivisa, gestita solo da plc)


// Input macro CALC_TCP.SXT
#define     R_6450                 6450 // Posizione Centro Rotazione Testa asse X
#define     R_6451                 6451 // Posizione Centro Rotazione Testa asse Y
#define     R_6452                 6452 // Posizione Centro Rotazione Testa asse Z
#define     R_6453                 6453 // Posizione Centro Rotazione Testa asse A
#define     R_6454                 6454 // Posizione Centro Rotazione Testa asse C

// Output macro CALC_TCP.SXT
#define     R_6456                 6456 // Posizione TCP asse X
#define     R_6457                 6457 // Posizione TCP asse Y
#define     R_6458                 6458 // Posizione TCP asse Z
#define     R_6459                 6459 // Posizione TCP asse A
#define     R_6460                 6460 // Posizione TCP asse C

// Parametri interni CALC_TCP.SXT
#define     R_6465                 6465 // Parametro interno
#define     R_6466                 6466 // Parametro interno
#define     R_6467                 6467 // Parametro interno
#define     R_6468                 6468 // Parametro interno
#define     R_6469                 6469 // Parametro interno

///////////// Parametri R per creare report ///////////////////////////////////////////////////////
#define     R_REPORT_01            6471 // Parametro per report 01
#define     R_REPORT_02            6472 // Parametro per report 02
#define     R_REPORT_03            6473 // Parametro per report 03
#define     R_REPORT_04            6474 // Parametro per report 04
#define     R_REPORT_05            6475 // Parametro per report 05
#define     R_REPORT_06            6476 // Parametro per report 06
#define     R_REPORT_07            6477 // Parametro per report 07
#define     R_REPORT_08            6478 // Parametro per report 08
#define     R_REPORT_09            6479 // Parametro per report 09
#define     R_REPORT_10            6480 // Parametro per report 10
///////////// Fine Paremetri R per creare report //////////////////////////////////////////////////

#define   R_CAMBIOUT_Y             6490  // Quota asse Y per cambio utensili 
#define   R_CAMBIOUT_Z             6491  // Quota asse Z per cambio utensili 
#define   R_CAMBIOUT_A             6492  // Quota asse A per cambio utensili 
#define   R_CAMBIOUT_C             6493  // Quota asse C per cambio utensili
#define   R_CAMBIOUT_W1            6494  // Quota asse W di verifica presenza utensile
#define   R_CAMBIOUT_W2            6495  // Quota asse W per cambio utensili


#define   R_NUM_TOT_UT_MAG         6500  // (12.5) Numero TOTALE utensili del magazzino  (piu soglia di 0.5 per agevolare verifiche)
#define   R_NUM_UT_MAG_INF         6501  // ( 6.5) Numero utensili della fila inferiore del magazzino (piu soglia di 0.5 per agevolare verifiche)


#define   R_PLC_GRUPPO_MORSE_SX1   6528  // Morse associate in chiusura alla battuta SX1 dal PLC
//// #define   R_PLC_GRUPPO_MORSE_SX2   6529  // Morse associate in chiusura alla battuta SX2 dal PLC
//// #define   R_PLC_GRUPPO_MORSE_DX3   6530  // Morse associate in chiusura alla battuta DX3 dal PLC
#define   R_PLC_GRUPPO_MORSE_DX4   6531  // Morse associate in chiusura alla battuta DX4 dal PLC

#define   R6695                        6695 // PREVISTO: APPOGGIO valore errore segnalato 

// predisposizione per eventuale aggiunta dell'opzione ISO
//-- Lettura chiavi Hardware (HardLock) --------------------------------------
#define R_HARDLOCK_ISO                 6799 // Chiave Hardlock ISO presente (letta da Drill)
#define R_OPT_SW_PRESENTI_1	           6800 // Opzioni software presenti (a bit)
#define R_OPT_SW_PRESENTI_2	           6801 // Opzioni software presenti (a bit)
#define R_COM_HEARTBEAT                6802 // Il PLC controlla che questo valore sia diverso da 0,
                                            // quindi lo resetta. Se rimane fisso a 0 per troppo tempo
                                            // il PLC va in allarme.
#define R_CONT_HEARTBEAT               6803 // Contatore, si incrementa quando  R_COM_HEARTBEAT==0 


#define   R6810                        6810 // Usata in mandrino.c: conta quanto tempo rimane a 1   VEL_INVERTEROK_I dopo caduta di START_INVERTER_O
#define   R6811                        6811 // Usata in mandrino.c: conta quanto tempo dura impulso VEL_INVERTEROK_I dopo caduta di START_INVERTER_O

#define   R_APP_POS_BATT_SX1           6812 // Appoggio micro posizione battuta SX1
#define   R_APP_POS_BATT_DX4           6813 // Appoggio micro posizione battuta DX4

#define   R_APP_RIP_CHIUSO             6814 // Appoggio dello stato chiuso del riparo per il CN
#define   R_MEM_APP_RIP_CHIUSO         6815 // Memoria appoggio dello stato chiuso del riparo per il CN

#define   R_6835                       6835 // Contatore riposizionamenti pezzo in MOVPIECE.CS4
#define   R_6836                       6836 // Usata in MOVPIECE.CS4 su macchina dinamica (appoggio posizione morsa master prima di muovere il pezzo)
#define   R_6837                       6837 // Usata in MOVPIECE.CS4 su macchina dinamica (appoggio posizione morsa master dopo aver mosso il pezzo)
#define   R_6838                       6838 // (solo CometR) Usata in 8.CS4 e SCOST_PEZZO.CS4 su macchina dinamica (scostamento pezzo eseguito, serve per far tornare indietro il pezzo)

#define   R_POS_MORSE_ISO_ACT          6840 // Posizionamento morse in ISO attivo
#define   R_CORR_X_MASTCLAMP           6841 // (solo CometR) Valore correzione in X da applicare alla lavorazione (errore morsa master)
#define   R_ERR_POS_MASTCLAMP          6842 // (solo CometR) Errore di posizionamento della morsa master

//*********************** INIZIO VARIABILI DI GESTIONE DEL MULTICHANNEL ***********************************
#define   R_DISABIL_LSR_PRIMO_STEP     6851 // (solo CometR) Non fare libera servo, è il primo step di riposizionamento
#define   R_WAIT_LSR_CH0_DA_CH2        6852 // (solo CometR) Attesa fine libera servo sul CH0 settata dal CH2
////#define   R_WAIT_LSR_CH0_DA_CH3    6853 // (solo CometR) Attesa fine libera servo sul CH0 settata dal CH3

////#define   R_WAIT_CH2_DA_CH3            6855 // Sincronizza il CH2 con il CH3 settandola a 4 (settandola a 2 libera il CH2 da attesa lanciata da CH3)
////#define   R_WAIT_CH3_DA_CH2            6856 // Sincronizza il CH3 con il CH2 settandola a 8 (settandola a 4 libera il CH3 da attesa lanciata da CH2)

#define   R_FILT_SYNC0_MC              6862 // Sincronizzazione livello 0, per esempio: (1+2+4+8) sincronizzazione di tutti e 4 i canali assieme
#define   R_FILT_SYNC1_MC              6863 // Sincronizzazione livello 1, per esempio: (1+2+4+8) sincronizzazione di tutti e 4 i canali assieme
#define   R_FILT_FHOLD_MC_SH           6864 // Filtro associato ad una funzione M che agisce sul FHOLD dei singoli canali (valido solo per quelle funzioni M che lo prevedono) 
											// per esempio: con (1+2+4+8) la funzione M mette in FHOLD tutti i canali; 
#define   R_FILT_SYNC1_TO_0_MC         6865 // Sincronizzazione livello 1, filtro dei canali di livello 0 da sincronizzare dopo la sincronizzazione di livello 1, per esempio: (1+2+4+8) sincronizzazione di tutti e 4 i canali assieme

#define   R_WAIT_CH1_DA_CH0            6866 // Sincronizza il CH1 con il CH0 settandola a 2 (settandola a 2 libera il CH1 da attesa lanciata da CH0)
#define   R_WAIT_CH2_DA_CH0            6867 // Sincronizza il CH2 con il CH0 settandola a 4 (settandola a 4 libera il CH2 da attesa lanciata da CH0)
////#define   R_WAIT_CH3_DA_CH0            6868 // Sincronizza il CH3 con il CH0 settandola a 8 (settandola a 8 libera il CH3 da attesa lanciata da CH0)

#define   R_WAIT_CH0_DA_CH1            6869 // Sincronizza il CH0 con il CH1 settandola a 2 (settandola a 2 libera il CH0 da attesa lanciata da CH1)
#define   R_WAIT_CH0_DA_CH2            6870 // Sincronizza il CH0 con il CH2 settandola a 4 (settandola a 4 libera il CH0 da attesa lanciata da CH2)
////#define   R_WAIT_CH0_DA_CH3            6871 // Sincronizza il CH0 con il CH3 settandola a 8 (settandola a 8 libera il CH0 da attesa lanciata da CH3)


//Serie di variabili che indicano a quale canale l'asse è attualmente attribuito (gestito dal PLC)
////#define   R_CH_X_ON                    6873 // Canale attribuito all'asse X può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)
////#define   R_CH_P_ON                    6874 // Canale attribuito all'asse P può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)
////#define   R_CH_H_ON                    6875 // Canale attribuito all'asse H può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)
#define   R_CH_W_ON                    6876 // Canale attribuito all'asse W può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)

//Serie di variabili che indicano se l'asse è stato liberato e quale canale lo ha liberato (gestito dal PLC)
////#define   R_CH_X_OFF                   6881 // Canale che ha liberato l'asse X può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)
////#define   R_CH_P_OFF                   6882 // Canale che ha liberato l'asse P può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)
////#define   R_CH_H_OFF                   6883 // Canale che ha liberato l'asse H può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)
#define   R_CH_W_OFF                   6884 // Canale che ha liberato l'asse W può assumere i valori 0,1,2,3,999 a seconda del canale a cui è al momento attribuito (999=nessuno)

#define   R_ENABLE_NEW_ISO             6898 // 1=Drill abilitato alla generazione nuovi ISO, 0=Drill non abilitato alla generazione nuovi ISO

#define   R_FORCE_START                6899 // 1=forza la condizione di abilitazione start ciclo

#define   R_CODICE_CASUALE_ISO_CH0     6900 // Codice Casuale ISO CH0
#define   R_CODICE_CASUALE_ISO_CH1     6901 // Codice Casuale ISO CH1
#define   R_CODICE_CASUALE_ISO_CH2     6902 // Codice Casuale ISO CH2
////#define   R_CODICE_CASUALE_ISO_CH3     6903 // Codice Casuale ISO CH3

#define   R_ISO_STARTED_CH0            6904 // 1=CH0 ISO in esecuzione, 0=CH0 ISO non in esecuzione
#define   R_ISO_STARTED_CH1            6905 // 1=CH1 ISO in esecuzione, 0=CH1 ISO non in esecuzione
#define   R_ISO_STARTED_CH2            6906 // 1=CH2 ISO in esecuzione, 0=CH2 ISO non in esecuzione
////#define   R_ISO_STARTED_CH3            6907 // 1=CH3 ISO in esecuzione, 0=CH3 ISO non in esecuzione

#define   R_COMET_R_MC                 6914 // 1=Comet R MC                 

#define   R_ISOMG_UPDATED              6915 // 1=Nuovi ISOMG disponibili, 

#define   R_ENABLE_NEW_ISO2            6916 

#define   R_EMERG_PREMUTA              6924 // Appoggio emergenza premuta per HDRILL, la legge, lancia reset verso il CN e dopo la resetta
#define   R_ENABLE_CK_ISOCODE          6925 // Abilita il check del random isocode per HDRILL

#define   R_RESET_IN_CORSO             6926 // Reset in corso: appoggio per HDRILL

#define   R_CH_REQ                     6927 // Canale che richiede lo scambio assi

#define   R_SYNC_LEVEL_REQ             6928 // Livello di sincronizzazione 0;1

#define   R_CONT_NO_SH                 6929 // Contatore salto sharing per assi già attribuiti come richiesto

////#define   R_NEXT_SH_X                  6933 // Canale asse X richiesto
////#define   R_NEXT_SH_P                  6934 // Canale asse P richiesto
////#define   R_NEXT_SH_H                  6935 // Canale asse H richiesto
#define   R_NEXT_SH_W                  6936 // Canale asse W richiesto

////#define   R_SH_OFF_X                   6937 // Flag asse X da liberare
////#define   R_SH_OFF_P                   6938 // Flag asse P da liberare
////#define   R_SH_OFF_H                   6939 // Flag asse H da liberare
#define   R_SH_OFF_W                   6940 // Flag asse W da liberare

////#define   R_SH_ON_X                    6941 // Flag asse X da acquisire
////#define   R_SH_ON_P                    6942 // Flag asse P da acquisire
////#define   R_SH_ON_H                    6943 // Flag asse H da acquisire
#define   R_SH_ON_W                    6944 // Flag asse W da acquisire

////#define   R_MORSE_IN_POSIZIONE_SX      6946 // Appoggio morse a SX tutte in posizione
////#define   R_MORSE_IN_POSIZIONE_DX      6947 // Appoggio morse a DX tutte in posizione

#define   R_MODO_RIFMANO               6948 // 0=riferimento assi multicanale; 1=riferimento assi uno alla volta

#define   R_INDICE_ASSE_RIFMANO        6949 // Indice dell'asse da riferire

#define   R_FINE_ISO                   6950 // Settato a 1 in RIFAUTO e a 0 in FINEALL indica che ISO non è mai passato per FINEALL e non è terminato

#define   R_MORSE_MUOVI_GIRO_1_ZONA_SX 6951 // Appoggio per uso lato CN
#define   R_MORSE_MUOVI_GIRO_2_ZONA_SX 6952 // Appoggio per uso lato CN
#define   R_MORSE_MUOVI_GIRO_1_ZONA_DX 6953 // Appoggio per uso lato CN
#define   R_MORSE_MUOVI_GIRO_2_ZONA_DX 6954 // Appoggio per uso lato CN

////#define   R_MORSA_CONTROLLATA_P        6955 // Morsa sotto controllo posizione da asse P
////#define   R_MORSA_CONTROLLATA_H        6956 // SOLO TRASC.: Morsa controllata

#define   R_MORSE_CONTROLLATE_SX       6957 // Appoggio indici morse controllate a SX
#define   R_MORSE_CONTROLLATE_DX       6958 // Appoggio indici morse controllate a DX

#define   R_PRIMO_GIRO_SX              6961 // Appoggio flag primo giro di posizionamento morse a SX
#define   R_SECONDO_GIRO_SX            6962 // Appoggio flag secondo giro di posizionamento morse a SX

#define   R_PRIMO_GIRO_DX              6963 // Appoggio flag primo giro di posizionamento morse a DX
#define   R_SECONDO_GIRO_DX            6964 // Appoggio flag secondo giro di posizionamento morse a DX

////#define   R_ASSE_X_ASSEGN_CH2_CH3      6966 // Assegna l'asse X al canale 2 ol al canale 3 (movimento morse con P e H in multipezzo)

#define   R_APP_MORSE_SU_PEZZO_SX      6967 // Appoggio indici morse su pezzo a SX, in riposizionamento vogliamo richiudere solo quelle sul pezzo 
#define   R_APP_MORSE_SU_PEZZO_DX      6968 // Appoggio indici morse su pezzo a DX, in riposizionamento vogliamo richiudere solo quelle sul pezzo 

#define   R_CAUSALE_ISO_MC_CH0         6970 // Causale ISO multichannel (scritta da CH0 e usata dagli altri canali)
#define   R_CAUSALE_ISO_MC_CH1         6971 // Causale ISO multichannel (scritta da CH1 e usata dagli altri canali)
#define   R_CAUSALE_ISO_MC_CH2         6972 // Causale ISO multichannel (scritta da CH2 e usata dagli altri canali)
////#define   R_CAUSALE_ISO_MC_CH3         6973 // Causale ISO multichannel (scritta da CH3 e usata dagli altri canali)

//*********************** FINE VARIABILI DI GESTIONE DEL MULTICHANNEL ***********************************

// R7000 ^//////////////////////////////////////////////////////////////////////////////////////////

////#define   R_DIST_ANTICOLL_H_X      7006 // (solo S6,R6) Distanza minima di non collisione tra asse H e asse X (in jog manuali)
////#define   R_DIST_ANTICOLL_P_X      7007 // (solo S6,R6) Distanza minima di non collisione tra asse P e asse X (in jog manuali) 

#define   R_QUOTA_ZMAX_GANCIO          7008 // Quota massima Z per sollevamento magazzino
#define   R_QUOTA_ZMIN_GANCIO          7009 // Quota minima Z per sollevamento magazzino

#define   R_QUOTA_Y_MIN_NO_COLL_RIP    7010 // Quota Y minima  di non collisione tra utensile e riparo anteriore
#define   R_QUOTA_A_MAX_NO_COLL_RIP    7011 // Quota A massima di non collisione tra utensile e riparo anteriore

////#define   R_OFFSET_X_MAND_CX4      7012 // (occupato su CX4, definita per necessita di Hdrill)
////#define   R_quota_Wmax_no_ing_P    7013 // (occupato su CR6 CS6)

////#define   R_ABIL_VER_COLLIS_BATT   7014 // (occupato su CR6 CS6)

////#define   R_ABIL_AP_MORSE_DI_ZONA  7015 // (occupato su CR6 CS6)

#define   R_FORZ_CH_MORSE_LIBERE       7016 // 1=> Forzatura chiusura morse non associate ad alcuna battuta | 1=> Forcing closing of vices not associated at any stop

#define   R_LUBRICA_TIPO_GESTIONE      7017 // Lubrica: tipo gestione:
                                            // 0: (old) la freq. impostata in Camplus varia il tempo in cui la pompa è OFF e la frequenza di lubrificazione (il tempo di pompa ON è fisso a 0,3s)
                                            // 1: (new) la freq. impostata in Camplus varia il duty cycle, la % di tempo in cui la pompa è ON. Mentre la frequenza di lubrificazione resta costante (f=R7018)

#define   R_LUBRICA_FREQ_CONFMAC       7018 // Lubrica: (considerata se R7017=1) frequenza fissa dei cicli di lubrificazione da confmac (30 cicli/min  =>  T=2sec) occorre mantenere bassi i cicli di attivazioni al minuto per allungare la vita dell’impianto di lubrificazione

#define   R_GEST_DIS_ATT_ABIL          7020 // 1 = Gestione Disattivazione/Riattivazione Abilitazione assi pilotata dai PP SH_OFF_.. SH_ON_..
                                            // 2 = Reset da PLC dell'abilitazione degli assi che rimangono disabilitati

#define   R_LUBRICA_DUTY_CYCLE_MIN     7021 // Lubrica: (considerata se R7017=1) duty cycle minimo,  attivo se R_FREQ_LUBRICA=1
#define   R_LUBRICA_DUTY_CYCLE_MAX     7022 // Lubrica: (considerata se R7017=1) duty cycle massimo, attivo se R_FREQ_LUBRICA=119

#define   R_SIMULAZ_INVERTER           7028 // (PREDISPOSTO PER SVILUPPO FUTURO)  (999) Simulazione segnali inverter per collaudo macchina senza inverter

#define   R_TIPO_MODULO_SIC            7029 // Tipo modulo di sicurezza:  0:PILZ  1:PIZZATO

#define   R_NUM_SK_MORS_IN_1           7031 // Numero schede della morsettiera MI_1_ degli ingressi
#define   R_NUM_SK_MORS_IN_2           7032 // Numero schede della morsettiera MI_2_ degli ingressi

#define   R_NUM_SK_MORS_OUT_1          7041 // Numero schede della morsettiera MO_1_ delle uscite
#define   R_NUM_SK_MORS_OUT_2          7042 // Numero schede della morsettiera MO_2_ delle uscite
#define   R_NUM_SK_MORS_OUT_6          7046 // Numero schede della morsettiera MO_6_ delle uscite

#define   R_PRESS_MAND_TIME            7051 // Pressurizzazione mandrino: Durata (sec) | Spindle pressurization: duration (sec)
#define   R_PRESS_MAND_PSW             7052 // Pressurizzazione mandrino: PSW          | Spindle pressurization: PSW

#define   R7055                        7055 // OCCUPATO SU CX4

#define R_ABIL_LETTURA_STATO_ASSE_X    7060 // Abilita lettura dello stato dell'asse X (lettura oggetti ethercat da azionamenti Delta)
#define R_ABIL_LETTURA_STATO_ASSE_Y    7061 // Abilita lettura dello stato dell'asse Y (lettura oggetti ethercat da azionamenti Delta)
#define R_ABIL_LETTURA_STATO_ASSE_Z    7062 // Abilita lettura dello stato dell'asse Z (lettura oggetti ethercat da azionamenti Delta)
#define R_ABIL_LETTURA_STATO_ASSE_A    7063 // Abilita lettura dello stato dell'asse A (lettura oggetti ethercat da azionamenti Delta)
#define R_ABIL_LETTURA_STATO_ASSE_W    7064 // Abilita lettura dello stato dell'asse W (lettura oggetti ethercat da azionamenti Delta)
#define R_NCICLI_DELAY_READ_OBJECT     7067 // Numero cicli plc dopo cui ripete lettura degli oggetti ethercat degli assi
// 7069 (occupato su CR6)

#define   R_PRIMA_MORSA_A_SX           7071 // numero della prima morsa presente (a SX)
#define   R_ULTIMA_MORSA_A_DX          7072 // numero del'ultima  morsa presente (a DX)

#define   R_QUOTA_Y_FUOING_MAG_2       7179  // Quota asse Ymax appena fuori ingombro magazzino utensili, per HOLD asse Y (= Ymax Hdrill)  (con utensile max: 190mm)

#define   R_VELCAMBUT_YZ               7180  // Velocità bassa di YZ per le operazioni di cambio utensile
#define   R_POS_MIN_X_CAMB_UT          7181  // Posizione minima asse X per eseguire il cambio utensile

#define   R_QUOTA_Y_FUOING_MAG         7182  // Quota asse Y fuori ingombro magazzino utensili per operazioni di cambioutensile
#define   R_QUOTA_Y_FUOING_INF_MAG     7183  // Quota asse Y fuori ingombro fila inferiore magazzino utensili per operazioni di cambioutensile

#define   R_QUOTA_Z_FUOING_INF_MAG     7184  // Quota asse Z fuori ingombro fila inferiore magazzino utensili
#define   R_DELTA_LENTO_VEL_Y          7185  // mm di spostamento Y in velocità lenta per cambio utensile
#define   R_DELTA_LENTO_VEL_Z          7186  // mm di spostamento Z in velocità lenta per cambio utensile
#define   R_Y_OUT_W_MOV                7187  // mm di fuori ingombro asse Y rispetto al movimento dell'asse W
#define   R_Wmax_no_ing_carter_sx      7188  // Quota W max fino alla quale il magazzino non è in ingombro col carter laterale SX della macchina (quando X=min)

#define   R_QUOTA_X_CAMBMAN            7189  // (attualmente CS6) Quota asse X che porta il magazzino utensili davanti al riparo posteriore

#define   R_CAMBUT_S58_Y               7190  // Quota asse Y  per prel./dep. utensili
#define   R_CAMBUT_S58_Z               7191  // Quota asse Z  per prel./dep. utensili
#define   R_CAMBUT_S58_A               7192  // Quota asse A  per prel./dep. utensili
#define   R_CAMBUT_S58_C               7193  // Quota asse C  per prel./dep. utensili
#define   R_CAMBUT_S58_PRES_W_INF      7194  // Quota asse W  di verifica presenza utensile (fila inferiore)
#define   R_CAMBUT_S58_PRES_W_SUP      7195  // Quota asse W  di verifica presenza utensile (fila superiore)
#define   R_CAMBUT_S58_W_INF           7196  // Quota asse W  per prel./dep. utensili (fila inferiore)
#define   R_CAMBUT_S58_W_SUP           7197  // Quota asse W  per prel./dep. utensili (fila superiore)

//************************************************************************************
//****************************** Posizioni in Magazzino ******************************
//************************************************************************************

//******************* Quote di prelievo e deposito Utensile n.1 **********************
#define   R_UT1_S58_Y                  7200  // Quota asse Y per prel./dep. utensile 1 
#define   R_UT1_S58_Z                  7201  // Quota asse Z per prel./dep. utensile 1 
#define   R_UT1_S58_A                  7202  // Quota asse A per prel./dep. utensile 1 
#define   R_UT1_S58_C                  7203  // Quota asse C per prel./dep. utensile 1 
#define   R_UT1_S58_W1                 7204  // Quota asse W di verifica presenza utensile 1 
#define   R_UT1_S58_W2                 7205  // Quota asse W per prel./dep. utensile 1 

//******************* Quote di prelievo e deposito Utensile n.2 **********************
#define   R_UT2_S58_Y                  7206  // Quota asse Y per prel./dep. utensile 2 
#define   R_UT2_S58_Z                  7207  // Quota asse Z per prel./dep. utensile 2 
#define   R_UT2_S58_A                  7208  // Quota asse A per prel./dep. utensile 2 
#define   R_UT2_S58_C                  7209  // Quota asse C per prel./dep. utensile 2 
#define   R_UT2_S58_W1                 7210  // Quota asse W di verifica presenza utensile 2 
#define   R_UT2_S58_W2                 7211  // Quota asse W per prel./dep. utensile 2 

//******************* Quote di prelievo e deposito Utensile n.3 **********************
#define   R_UT3_S58_Y                  7212  // Quota asse Y per prel./dep. utensile 3 
#define   R_UT3_S58_Z                  7213  // Quota asse Z per prel./dep. utensile 3 
#define   R_UT3_S58_A                  7214  // Quota asse A per prel./dep. utensile 3 
#define   R_UT3_S58_C                  7215  // Quota asse C per prel./dep. utensile 3 
#define   R_UT3_S58_W1                 7216  // Quota asse W di verifica presenza utensile 3 
#define   R_UT3_S58_W2                 7217  // Quota asse W per prel./dep. utensile 3 

//******************* Quote di prelievo e deposito Utensile n.4 **********************
#define   R_UT4_S58_Y                  7218  // Quota asse Y per prel./dep. utensile 4 
#define   R_UT4_S58_Z                  7219  // Quota asse Z per prel./dep. utensile 4 
#define   R_UT4_S58_A                  7220  // Quota asse A per prel./dep. utensile 4 
#define   R_UT4_S58_C                  7221  // Quota asse C per prel./dep. utensile 4 
#define   R_UT4_S58_W1                 7222  // Quota asse W di verifica presenza utensile 4 
#define   R_UT4_S58_W2                 7223  // Quota asse W per prel./dep. utensile 4 

//******************* Quote di prelievo e deposito Utensile n.5 **********************
#define   R_UT5_S58_Y                  7224  // Quota asse Y per prel./dep. utensile 5 
#define   R_UT5_S58_Z                  7225  // Quota asse Z per prel./dep. utensile 5 
#define   R_UT5_S58_A                  7226  // Quota asse A per prel./dep. utensile 5 
#define   R_UT5_S58_C                  7227  // Quota asse C per prel./dep. utensile 5 
#define   R_UT5_S58_W1                 7228  // Quota asse W di verifica presenza utensile 5 
#define   R_UT5_S58_W2                 7229  // Quota asse W per prel./dep. utensile 5 

//******************* Quote di prelievo e deposito Utensile n.6 **********************
#define   R_UT6_S58_Y                  7230  // Quota asse Y per prel./dep. utensile 6 
#define   R_UT6_S58_Z                  7231  // Quota asse Z per prel./dep. utensile 6 
#define   R_UT6_S58_A                  7232  // Quota asse A per prel./dep. utensile 6 
#define   R_UT6_S58_C                  7233  // Quota asse C per prel./dep. utensile 6 
#define   R_UT6_S58_W1                 7234  // Quota asse W di verifica presenza utensile 6 
#define   R_UT6_S58_W2                 7235  // Quota asse W per prel./dep. utensile 6 

//******************* Quote di prelievo e deposito Utensile n.7 **********************
#define   R_UT7_S58_Y                  7236  // Quota asse Y per prel./dep. utensile 7 
#define   R_UT7_S58_Z                  7237  // Quota asse Z per prel./dep. utensile 7 
#define   R_UT7_S58_A                  7238  // Quota asse A per prel./dep. utensile 7 
#define   R_UT7_S58_C                  7239  // Quota asse C per prel./dep. utensile 7 
#define   R_UT7_S58_W1                 7240  // Quota asse W di verifica presenza utensile 7 
#define   R_UT7_S58_W2                 7241  // Quota asse W per prel./dep. utensile 7 

//******************* Quote di prelievo e deposito Utensile n.8 **********************
#define   R_UT8_S58_Y                  7242  // Quota asse Y per prel./dep. utensile 8 
#define   R_UT8_S58_Z                  7243  // Quota asse Z per prel./dep. utensile 8 
#define   R_UT8_S58_A                  7244  // Quota asse A per prel./dep. utensile 8 
#define   R_UT8_S58_C                  7245  // Quota asse C per prel./dep. utensile 8 
#define   R_UT8_S58_W1                 7246  // Quota asse W di verifica presenza utensile 8 
#define   R_UT8_S58_W2                 7247  // Quota asse W per prel./dep. utensile 8 

//******************* Quote di prelievo e deposito Utensile n.9 **********************
#define   R_UT9_S58_Y                  7248  // Quota asse Y per prel./dep. utensile 9 
#define   R_UT9_S58_Z                  7249  // Quota asse Z per prel./dep. utensile 9 
#define   R_UT9_S58_A                  7250  // Quota asse A per prel./dep. utensile 9 
#define   R_UT9_S58_C                  7251  // Quota asse C per prel./dep. utensile 9 
#define   R_UT9_S58_W1                 7252  // Quota asse W di verifica presenza utensile 9 
#define   R_UT9_S58_W2                 7253  // Quota asse W per prel./dep. utensile 9 

//******************* Quote di prelievo e deposito Utensile n.10 **********************
#define   R_UT10_S58_Y                 7254  // Quota asse Y per prel./dep. utensile 10
#define   R_UT10_S58_Z                 7255  // Quota asse Z per prel./dep. utensile 10
#define   R_UT10_S58_A                 7256  // Quota asse A per prel./dep. utensile 10
#define   R_UT10_S58_C                 7257  // Quota asse C per prel./dep. utensile 10
#define   R_UT10_S58_W1                7258  // Quota asse W di verifica presenza utensile 10 
#define   R_UT10_S58_W2                7259  // Quota asse W per prel./dep. utensile 10 

//******************* Quote di prelievo e deposito Utensile n.11 **********************
#define   R_UT11_S58_Y                 7260  // Quota asse Y per prel./dep. utensile 11
#define   R_UT11_S58_Z                 7261  // Quota asse Z per prel./dep. utensile 11
#define   R_UT11_S58_A                 7262  // Quota asse A per prel./dep. utensile 11
#define   R_UT11_S58_C                 7263  // Quota asse C per prel./dep. utensile 11
#define   R_UT11_S58_W1                7264  // Quota asse W di verifica presenza utensile 11 
#define   R_UT11_S58_W2                7265  // Quota asse W per prel./dep. utensile 11 

//******************* Quote di prelievo e deposito Utensile n.12 **********************
#define   R_UT12_S58_Y                 7266  // Quota asse Y per prel./dep. utensile 12
#define   R_UT12_S58_Z                 7267  // Quota asse Z per prel./dep. utensile 12
#define   R_UT12_S58_A                 7268  // Quota asse A per prel./dep. utensile 12
#define   R_UT12_S58_C                 7269  // Quota asse C per prel./dep. utensile 12
#define   R_UT12_S58_W1                7270  // Quota asse W di verifica presenza utensile 12 
#define   R_UT12_S58_W2                7271  // Quota asse W per prel./dep. utensile 12 


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NB: I PARAMETRI R COMPRESI TRA 7475 E 7599 SONO ATTUALMENTE LIBERI NEI PROGETTI DELLE MACCHINE GESTITE DA HDRILL  (20/09/2022)
//     INIZIO DEFINIZIONI PER FUNZIONI COMUNI A TUTTE LE MACCHINE GESTITE DA HDRILL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


// *** Presetter per verifica integrita e lunghezza utensili (INIZIO) ***

#define   R_CKTOOL_TYPE                7509 // 0 = Presetter di tipo meccanico | 0 = Mechanical presetter
                                            // 1 = Presetter di tipo laser     | 1 = Laser presetter

#define   R_CKTOOL_PRES                7510 // 1 = Dispositivo di verifica integrità utensile presente
                                            // 2 = Dispositivo di verifica integrità e rilievo dimensioni utensile presente

#define   R_CKT_QUOTA_VER_UT_Y         7511 // Quota asse Y per verifica integrità utensile
#define   R_CKT_QUOTA_VER_UT_Z         7512 // Quota asse Z verifica integrità utensile
#define   R_CKT_QUOTA_VER_UT_A         7513 // Quota asse A verifica integrità utensile

#define   R_CKT_QUOTA_VER_UT_W         7515 // Quota asse W verifica integrità utensile

#define   R_CKT_OFS_START              7516 // mm di distanza dal presetter dove inizia  il movimento Y di verifica integrita o rilievo lunghezza
#define   R_CKT_OFS_END                7517 // mm oltre il presetter        dove termina il movimento Y di verifica integrita o rilievo lunghezza

#define   R7518                        7518 // Velocità media dell'asse Y per verifica utensile
#define   R7519                        7519 // Velocità alta  dell'asse Y per verifica utensile
#define   R7520                        7520 // Velocità bassa dell'asse Y per verifica utensile

#define   R_CKT_OFS_LUNG               7521 // Offset da sommare alla lunghezza utensile rilevata per determinare quella reale

#define   R_CKT_QUOTA_Y_MIN            7522 // Quota Y min che evita collisione tra morse e culo mandrino a qualsiasi Z (con B0 e C90) | 

#define   R_CKT_NR_PINZA               7523 // Numero posizione del magazzino utensili in cui è installato il presetter (attualmente nr=6)

#define   R_CKT_OFS_RAD                7524 // Offset da sommare al raggio utensile rilevato per determinare quello reale

#define   R_CKT_VEL_MANDR              7525 // Velocità di rotazione mandrino (per presetter laser)

// *** Presetter per verifica integrita e lunghezza utensili (FINE) ***



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NB: I PARAMETRI R COMPRESI TRA 7475 E 7599 SONO ATTUALMENTE LIBERI NEI PROGETTI DELLE MACCHINE GESTITE DA HDRILL  (20/09/2022)
//     FINE DEFINIZIONI PER FUNZIONI COMUNI A TUTTE LE MACCHINE GESTITE DA HDRILL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define R_VEL_LATCH_FINDMOR_PH		   7879 // Velocità Ricerca Morse : Assi PH con ingressi latch
#define R_INPUT_LATCH_PROBE            7880 // Abilita input latch per tastatore Renishaw
////#define R_INPUT_LATCH_AX_P             7881 // Abilita input latch per ricerca morse con asse P
////#define R_INPUT_LATCH_AX_H             7882 // Abilita input latch per ricerca morse con asse H
#define R_ENAB_DISAB_FILTRI            7883 // =1 Gestione abilitazione/disabilitazione filtri assi da PLC attiva per X,Y,Z
                                            // =2 Gestione abilitazione/disabilitazione filtri assi da PLC attiva per X,Y,Z,A
#define R_CICLI_PLC_MAX_RIP_ANT        7884 // Numero massimo di cicli plc di movimento riparo anteriore per check velocità

#define R_VEL_MAX_RIP_ANT              7886 // Numero massimo di transizioni input check velocità lato SX-DX riparo anteriore

#define R_LED_RIPARI                   7887 // Led ripari e mandrino presenti
#define R_ABIL_AP_CH_RIPARI            7888 // =0 Abilita sempre AP/CH ripari anteriori, = 1 Abilita AP/CH ripari anteriori da posizione sicura assi A,C e Y
#define R_TOLL_SPOST_PEZZO             7889 // Tolleranza per spostamento pezzo in MOVPIECE.SXT
#define R_MAX_OVRAP_SEMIAUTO           7890 // Semiautomatico: Max percentuale override per movimenti in rapido (movimenti in G0)
#define R_TOLL_CALC_DRILL              7892 // Tolleranza nei calcoli posizioni di lavorazione per Drill

#define R_DISAB_RIPARI_FIERA           7893 // Disabilita apertura dei ripari in fiera
////#define R_ABIL_ALLARM_CAMME_ZONA       7894 // 0= Abilita allarme camme zona sempre, 1= Abilita allarme camme zona solo in pendolare
#define R_VOLANTINO_PRES               7895 // Volantino presente
#define R_ACC_ASSI_VOL_XYAC            7896 // Accelerazione assi X,Y,A,C con volantino
#define R_ACC_ASSI_VOL_Z               7897 // Accelerazione asse Z con volantino

#define R_BATTUTE_MOBMAN_PRES          7898 // Battute esterne mobili manualmente presenti  | External manually movable stops present
                                            // 1: battuta fissa a SX e mobile a DX          | 1: fixed stop on the left and mobile on the right

#define R_ABIL_GEST_AVA_TOOL           7899 // Gestione utensili avanzata abilitata

#define R_MGPILOT_NODE_DI              7900 // Numero nodo Mgpilot come nodo DI
#define R_MGPILOT_NODE_DO              7901 // Numero nodo Mgpilot come nodo DO
#define R_MGPILOT_NODE_AI              7902 // Numero nodo Mgpilot come nodo AI
#define R_MGPILOT_NODE_ENC             7903 // Numero nodo Mgpilot come nodo ENCODER

#define R_SOGLIA_FUGA_GANTRY           7905 // Soglia di fuga assi agganciati in gantry
#define R_K_GANTRY_MASTER_SLAVE        7906 // Guadagno gantry: usato per compensare lo scostamento tra master e slave
#define R_APRI_MORSE_SLAVE_MOVPIECE    7907 // Apri le morse slave durante la MOVPIECE.CS4

// #define R_INGR_RIPARI_RIDOND_PRES      7911 //(solo macchine pendolari) Ingressi ridondanti di ripari anteriori aperti-chiusi presenti (NON USATO)

#define R_POS_MAX_MORSE_SX_FUNZMAN     7912 // Posizione massima morse SX con funzione manuale di riposizionamento in zona SX
#define R_POS_MIN_MORSE_DX_FUNZMAN     7913 // Posizione minima morse DX con funzione manuale di riposizionamento in zona DX

#define R_FC_AX_ABSOLUTE_TOLL_LIN      7914 // Tolleranza per allarme di asse in oltrecorsa (asse lineare) [mm]
#define R_FC_AX_ABSOLUTE_TOLL_ROT      7915 // Tolleranza per allarme di asse in oltrecorsa (asse angolare) [gradi]

#define R_BORDO_SENSIBILE_PRES         7916 // Bordo sensibile presente sul riparo anteriore | Sensitive edge present on the front guard

#define R_BORDO_SENSIBILE_PSW          7917 // (Password) Abilitazione APERTURA AUTOMATICA del riparo anteriore pneumatico se bordo sensibile premuto
                                            // (Password) Enabling of the AUTOMATIC OPENING of the pneumatic front guard if the sensitive edge is pressed
                                            // APERTURA AUTOMATICA ATTIVABILE SOLO SE IL BORDO SENSIBILE INTERROMPE TRAMITE RELE LA EV DI CHIUSURA RIPARO
                                            // AUTOMATIC OPENING CAN BE ACTIVATED ONLY IF THE SENSITIVE EDGE CUTS THE GUARD CLOSING SOLENOID VALVE VIA A RELAY

#define R_GEST_SPEGN_ASPIR             7918 // = 0 Spegnimento aspiratore con ritardo su CICLO_ON a zero
                                            // = 1 Spegnimento aspiratore con ritardo su CICLO_ON a zero o riparo anteriore non chiuso

// ************* CONTATORI SU BRIDGE ************** INIZIO ******************

#define R_CNT_BRIDGE                   7920 /* Contatori su bridge 0=non presenti, 1=presenti */
#define R_DELAY_REOPEN                 7921 /* Ritardo dopo la chiusura prima di riprovare a riaprire il canale [msec] */
#define R_DELAY_POLLING_CONT           7922 /* Periodo aggiornamento contatori [msec] */
////#define R_CNT_MM_INDEX                 7923 /* Indice della memoria M per il test di verginità */
#define R_CNT_BRIDGE_TYPE              7924  /* Tipo di contatore 0=standard, */
#define R_CNT_BRIDGE_CONTROL_WORD      7925  /* Mappatura contatori b0=0 a step, b0=1 contatore a tempo per 16 bit */
#define R_CNT_BRIDGE_SAVE_FILE_TEST    7926 /* 1=Abilita la versione di test del salvataggio log file */

// ************* CONTATORI SU BRIDGE ************** FINE ******************

#define   R_NCICLI_DELAY_READ_SDO      7930 // Numero cicli plc dopo cui ripete lettura SDO dai Minimotor

//#define   R_ABIL_READ_SDO_M07          7937 // Abilita lettura corrente e tensione morsa M14
//#define   R_ABIL_READ_SDO_M08          7938 // Abilita lettura corrente e tensione morsa M08
//#define   R_ABIL_READ_SDO_M09          7939 // Abilita lettura corrente e tensione morsa M09
#define   R_ABIL_READ_SDO_M10          7940 // Abilita lettura corrente e tensione morsa M10
#define   R_ABIL_READ_SDO_M11          7941 // Abilita lettura corrente e tensione morsa M11
#define   R_ABIL_READ_SDO_M12          7942 // Abilita lettura corrente e tensione morsa M12
#define   R_ABIL_READ_SDO_M13          7943 // Abilita lettura corrente e tensione morsa M13
#define   R_ABIL_READ_SDO_M14          7944 // Abilita lettura corrente e tensione morsa M14
#define   R_ABIL_READ_SDO_M15          7945 // Abilita lettura corrente e tensione morsa M15
//#define   R_ABIL_READ_SDO_M16          7946 // Abilita lettura corrente e tensione morsa M16
//#define   R_ABIL_READ_SDO_M17          7947 // Abilita lettura corrente e tensione morsa M17
//#define   R_ABIL_READ_SDO_M18          7948 // Abilita lettura corrente e tensione morsa M18

#define   R_ABIL_LSR_MORSE_DA_PLC      7950 // (solo CometR)  =0 forza temporanea abilitazione morse per azzerare l'errore di inseguimento

#define   R_CICLI_LSR_MORSE            7951 // (solo CometR)  Numero cicli plc durante cui l'asse morse viene tenuto in libera servo
#define   R_ABIL_CORR_X_LAV            7965 // (solo CometR) Abilita le correzioni delle lavorazioni dopo MOVPIECE.CS4 con errore della morsa master

#define   R_SPEED_VERT4_FIG7           7987 // Velocità vertice 4 (tratto di uscita) della figura 7.CS4 
#define   R_DISAB_RESET_AREE_TAST      7988 // =0 Abilita il reset delle aree A di tastatura, =1 Disabilita reset delle aree A di tastatura nel nuovo ISOMG
#define   R_ENABLE_SCAV_MORSE_OTT      7989 // Abilita scavalcamento morse ottimizzato (serve versione HDRILL che anticipa R330 della lavorazione successiva)
#define   R_ENABLE_EVENTI_IND_4_0      7990 // Abilita eventi industia 4.0 per collegamento a rete di fornitura
#define   R_SIMUX_OFFLINE              7991 // =0 per la macchina, =1 simulatore SIMUX OFFLINE
#define   R_JERK_G184ACC               7992 // Jerk per G184ACC con curve cubiche durante la maschiatura rigida

// R8000 ^//////////////////////////////////////////////////////////////////////////////////////////

#define   R_TIMEOUT_MSG                8010 // Timeout dopo cui vengono esposti i warning

//*****************************************************************************************************
//****** VARIABILI RISERVATE PER SIMUX: da 12000 a 12999 **********************************************
//*****************************************************************************************************

#define   R12005                       12005 // appoggio Riferimento Y tavola

#define   R_SIMUX_Y_TAVOLA_INDIETRO    12007 // Riferimento Y di tavola indietro
#define   R_SIMUX_Y_TAVOLA_AVANTI      12008 // Riferimento Y di tavola avanti
#define   R_SIMUX_Y_TAVOLA_CENTRO      12009 // Riferimento Y di tavola centro   (occupato, presente su altre macchine)

#define   R_SIMUX_MORSA_10_PRESSORE    12060 // Posizione pressore morsa 10
#define   R_SIMUX_MORSA_11_PRESSORE    12061 // Posizione pressore morsa 11
#define   R_SIMUX_MORSA_12_PRESSORE    12062 // Posizione pressore morsa 12
#define   R_SIMUX_MORSA_13_PRESSORE    12063 // Posizione pressore morsa 13
#define   R_SIMUX_MORSA_14_PRESSORE    12064 // Posizione pressore morsa 14
#define   R_SIMUX_MORSA_15_PRESSORE    12065 // Posizione pressore morsa 15

#define   R_SIMUX_X_PEZZO_01           12101 // Riferimento pezzo 01
#define   R_SIMUX_X_PEZZO_02           12102 // Riferimento pezzo 02
#define   R_SIMUX_X_PEZZO_03           12103 // Riferimento pezzo 03
#define   R_SIMUX_X_PEZZO_04           12104 // Riferimento pezzo 04
#define   R_SIMUX_X_PEZZO_05           12105 // Riferimento pezzo 05
#define   R_SIMUX_X_PEZZO_06           12106 // Riferimento pezzo 06
#define   R_SIMUX_X_PEZZO_07           12107 // Riferimento pezzo 07
#define   R_SIMUX_X_PEZZO_08           12108 // Riferimento pezzo 08
#define   R_SIMUX_X_PEZZO_09           12109 // Riferimento pezzo 09
#define   R_SIMUX_X_PEZZO_10           12110 // Riferimento pezzo 10

//*****************************************************************************************************

//********* VARIABILI RISERVATE PER COMUNICAZIONE DA HDRILL A PLC MACCHINA PER OPCUA (da R13000-13099) **********************
#define   R_TIPO_TOOL_HDRILL_TO_PLC_1  13000 // Tipo utensile su mandrino 1 passato da DRILL/HDILL a plc macchina
#define   R_STATO_MACCH_HDRILL_TO_PLC  13001 // Stato macchina passato da HDRILL a plcm macchina (alla fine non lo passa DRILL/HDRILL, ricostruito da PLC-CNC)
#define   R_TIPO_TOOL_HDRILL_TO_PLC_2  13002 // Tipo utensile su mandrino 2 passato da DRILL/HDILL a plc macchina (la VEGAMILL EVO ha un secondo mandrino)

#define   R_MATRICOLA_MACCHINA_01      13003 // Matricola macchina: variabile 01 (meno significativa)
#define   R_MATRICOLA_MACCHINA_02      13004 // Matricola macchina: variabile 02 (più significativa)
#define   R_ASSORBIMENTO_MANDR         13005 // Assorbimento mandrino
#define   R_HEALTH_CANOPEN             13006 // Contatore errori in trasmissione e ricezioe su canbus
#define   R_HEALTH_ETHERCAT            13007 // Contatore pacchetti persi e pacchetti reinviati

#define   R_VERSIONE_VPLC_01           13009 // Versione VPLC: scritta da Drill, HDrill, BHDrill verso il plc macchina: variabile 01 (meno significativa)
#define   R_VERSIONE_VPLC_02           13010 // Versione VPLC: scritta da Drill, HDrill, BHDrill verso il plc macchina: variabile 02 (più significativa)
#define   R_ENDURANCE_OPCUA            13011 // 1=Endurance macchina attivo per OPCUA

//********* R13099 FINE VARIABILI RISERVATE PER COMUNICAZIONE DA HDRILL A PLC MACCHINA PER OPCUA ****************************

#define   R_TOLL_POS_READY             13198 // mm di Tolleranza per considerare gli assi arrivati in posizione
#define   R_INDEX_M_LASER              13199 // Indice della funzione ausiliaria FATM di comunicazione con l'applicativo del laser

// DA 13200 A 13399 RISERVATE ROBOT ***************  INIZIO *************************************************


// DA 13200 A 13399 RISERVATE ROBOT ***************  FINE   *************************************************

#endif // R_INC_INCLUDED
