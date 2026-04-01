#ifndef ASSI_INC_INCLUDED
#define ASSI_INC_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : assi.inc
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Corrispondenza nome <-> posizione asse in macchina
//----------------------------------------------------------------------------


// Definizione corrispondenza nome <-> posizione asse in macchina
// 0  - 11 : Assi del CNC MASTER
// 12 - 23 : Assi del CNC SLAVE1 
//
// NB: Eventuali variazioni vanno riportate anche nei seg. files:
// CONFMAC.CS4 Inizializzazione Multiprocesso
// comcnc.c    Gestione input veloce assi del CNC1

#define		ASSE_NULLO		12	//  Numero asse associato agli assi non presenti in readconf.c
#define		NUM_ASSI		12	//  Numero massimo assi : OCCHIO AI BLOKKI @
#define		MAX_NUM_CHANNEL 3   //  Numero massimo di canali

// -------------------------- Definizione degli assi MASTER   ---------------------------
//			ASSE	CH		Descrizione		Indirizzo	Num.AxDig	Tipo
// --------------------------------------------------------------------------------------

// abilitazione gestione freno dall'azionamento: P2-18 = 0x2212 = 0x108 = 264 (NA)

//******* ASSI DEL CHANNEL 0 *******                    
#define		AX_X_CH0	0	//	Asse X			1002					Ethercat / Delta
#define		AX_Y_CH0	1	//	Asse Y			1003					Ethercat / Delta
#define		AX_Z_CH0	2	//	Asse Z			1004	P2-18=264		Ethercat / Delta

#define		AX_A_CH0	3	//	Asse A			1005	P2-18=264		Ethercat / Delta
#define		AX_C_CH0	4	//	Asse C			/						Ethercat / Delta
#define		AX_W_CH0	5	//	Asse W			1006	P2-18=264		Ethercat / Delta  (proprietario il CHANNEL 1)

#define		AX_Q_CH0	6	//	Mandrino								Analogico
#define     AX_U_CH0	7   //  Banda magnetica battuta di precisione   Analogico


//******* ASSI DEL CHANNEL 1 ***********************************************************
#define		AX_W_CH1	0	//	Asse W			1006			 		Ethercat / Delta


// ( opriobcm01									1007			>>	1020		I/O Ethercat )
// ( opriocom00													>>	1021		com Ethercat )


//******* ASSI DEL CHANNEL 2 ***********************************************************

// ( gx-jc06(in,x2,x3)							1008			>>	1030		Switch Ethercat

#define		AX_M12_CH2	2	//	Asse M12 morsa n.12 1009 (C)	>>	1031		Ethercat / Minimotor
#define		AX_M13_CH2	3	//	Asse M13 morsa n.13	1010 (U)	>>	1032	 	Ethercat / Minimotor

// ( gx-jc06(x4,x5,x6)							1011			>>	1033		Switch Ethercat

#define		AX_M11_CH2	1	//	Asse M11 morsa n.11 1012 (B)	>>	1034		Ethercat / Minimotor
#define		AX_M14_CH2	4	//	Asse M14 morsa n.14	1013 (V)	>>	1035	 	Ethercat / Minimotor

// gx-jc06(in,x2,x3)							1014			>>	1036		(opz.) Switch Ethercat 

#define		AX_M10_CH2	0	//	Asse M10 morsa n.10 1015 (A)	>>	1037		(opz.) Ethercat / Minimotor
#define		AX_M15_CH2	5	//	Asse M15 morsa n.15	1016 (P)	>>	1038	 	(opz.) Ethercat / Minimotor



//************* NUMERO CANALE **********************************************************
#define     CHANNEL_CH0 0   // Canale 0
#define     CHANNEL_CH1 1   // Canale 1
#define     CHANNEL_CH2 2   // Canale 2


// Funzioni per abilitazione correzione assi
RTPLC_STATUS setCorrezione(USHORT channel, USHORT axis,BOOL reset, BOOL set);

// Funzioni per lettura / scrittura parametri asse da PLC
typedef struct {
    USHORT channel;
    USHORT axis;
    OMCNCAXISCOMMANDCODE command;
    OMCNC_AXISCOMMAND_PARAM param;
    double *outValue;
} CmdAxisStruct;

RTPLC_STATUS getParam(CmdAxisStruct* s, BOOL fbReset);
RTPLC_STATUS setParam(CmdAxisStruct* s, BOOL fbReset);

void getJerk(USHORT channel, USHORT axis, double *jerkValue, CmdAxisStruct* s);
void setJerk(USHORT channel, USHORT axis, double  jerkValue, CmdAxisStruct* s);

void getEncRatio(USHORT channel, USHORT axis, double *ratioValue, CmdAxisStruct* s);
void setEncRatio(USHORT channel, USHORT axis, double  ratioValue, CmdAxisStruct* s);
    
void getFeedForward(USHORT channel, USHORT axis, double *feedForward, CmdAxisStruct* s);
void setFeedForward(USHORT channel, USHORT axis, double  feedForward, CmdAxisStruct* s);

void setAxisCorrection(USHORT channel, USHORT axis, BOOL enable, CmdAxisStruct* s);
void setAxisFilter(USHORT channel, USHORT axis, double enable_disable, CmdAxisStruct* s);

// Funzioni aggiunte per la lettura / scrittura del kp

RTPLC_STATUS getParam_X(USHORT num_AX, double *kpSpazio);
RTPLC_STATUS setParam_X(USHORT num_AX, double kpSpazio);
void getKpSpazio_X(USHORT channel, USHORT axis, double *kpSpazio, CmdAxisStruct* s);
void setKpSpazio_X(USHORT channel, USHORT axis, double kpSpazio, CmdAxisStruct* s);

RTPLC_STATUS getParam_Y(USHORT num_AX, double *kpSpazio);
RTPLC_STATUS setParam_Y(USHORT num_AX, double kpSpazio);
void getKpSpazio_Y(USHORT channel, USHORT axis, double *kpSpazio, CmdAxisStruct* s);
void setKpSpazio_Y(USHORT channel, USHORT axis, double kpSpazio, CmdAxisStruct* s);

RTPLC_STATUS getParam_Z(USHORT num_AX, double *kpSpazio);
RTPLC_STATUS setParam_Z(USHORT num_AX, double kpSpazio);
void getKpSpazio_Z(USHORT channel, USHORT axis, double *kpSpazio, CmdAxisStruct* s);
void setKpSpazio_Z(USHORT channel, USHORT axis, double kpSpazio, CmdAxisStruct* s);

#endif // ASSI_INC_INCLUDED
