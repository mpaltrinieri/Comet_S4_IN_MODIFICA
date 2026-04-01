/*
        --------------------------------------------------------------   
        TITOLO:         Shared_Mem_MC
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione memoria condivisa fra più canali CNC
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    shared_Mem_MC()
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CS4  COSTANTINO MULTICANALE
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


#define nChannel 4

// Array delle aree R che devono essere copiate dal canale 0 sugli altri canali
int R_list [] = {

	R_SIMU,
	R_ENDURANCE,

	R_POS_ATTUALE_X,
	R_QUOTA_X,

	//R_CAUSALE_ISO_MC_CH0,
	//R_CAUSALE_ISO_MC_CH1,
	//R_CAUSALE_ISO_MC_CH2,

	R_ATTESA_CONFERMA,

	R_WAIT_CH1_DA_CH0,
	R_WAIT_CH2_DA_CH0,

	R_WAIT_CH0_DA_CH1,
	R_WAIT_CH0_DA_CH2,


	R_6360,
	R_6361,

	R_COLLAUDO_03,
	R_COLLAUDO_04,

	R_CAMBIOUT_Y, 
	R_CAMBIOUT_Z, 
	R_CAMBIOUT_A, 
	R_CAMBIOUT_C, 
	R_CAMBIOUT_W1,
	R_CAMBIOUT_W2,

	R_NUM_TOT_UT_MAG,
	R_NUM_UT_MAG_INF,

	R_ACT_TOOL,
	R_NEXT_TOOL,
	R_LNG_TOOL,
	R_RAD_TOOL,

	R_ASSE_W_G91_SPOST,
	R_ASSE_W_G91_VEL,
	R_ASSE_W_G91_TIPO_INT,

	R_APPO_POS_ASSE_W,

	R_STATUS,

	R_MORSE_MOTORIZZATE,
	
	R_ROT_PIECE,
	
	R_GESTMORS_OPER,
	R_END_SX,
	R_END_DX,
	
	R_NO_AP_MORSE,

	R_INTERAX_MORSE_SX,
	////R_INTERAX_MORSE_DX,
	////R_NUM_MORSE_SX,
	////R_NUM_MORSE_DX,
	
	R_HDRILL_GRUPPO_MORSE_SX1,
	////R_HDRILL_GRUPPO_MORSE_SX2,
	////R_HDRILL_GRUPPO_MORSE_DX3,
	R_HDRILL_GRUPPO_MORSE_DX4,

	R_PLC_GRUPPO_MORSE_SX1,
	//// R_PLC_GRUPPO_MORSE_SX2,
	//// R_PLC_GRUPPO_MORSE_DX3,
	R_PLC_GRUPPO_MORSE_DX4,

	R_NUM_MORSE,
	R_RIPOS_MORSE_MULTI,
	
	R_POSMORS4_PC,
	R_POSMORS5_PC,
	R_POSMORS6_PC,
	R_POSMORS7_PC,
	R_POSMORS8_PC,
	R_POSMORS9_PC,

	R_CNC1_TARGET_M10,
	R_CNC1_TARGET_M11,
	R_CNC1_TARGET_M12,
	R_CNC1_TARGET_M13,
	R_CNC1_TARGET_M14,
	R_CNC1_TARGET_M15,

	R_POSBAT_VERT_SX1,
	R_POSBAT_VERT_DX4,
	
	////R_XMAX_AREASX,
	////R_XMIN_AREADX,
	
	R_POS_ATTUALE_M10,
	R_POS_ATTUALE_M11,
	R_POS_ATTUALE_M12,
	R_POS_ATTUALE_M13,
	R_POS_ATTUALE_M14,
	R_POS_ATTUALE_M15,

	R_MORSE_CONTROLLATE_SX,
	R_MORSE_CONTROLLATE_DX,


	R_FCNEG_M10,
	R_FCNEG_M11,
	R_FCNEG_M12,
	R_FCNEG_M13,
	R_FCNEG_M14,
	R_FCNEG_M15,

	R_FCPOS_M10,
	R_FCPOS_M11,
	R_FCPOS_M12,
	R_FCPOS_M13,
	R_FCPOS_M14,
	R_FCPOS_M15,

	R_INSEGUIMENTO_M10,
	R_INSEGUIMENTO_M11,
	R_INSEGUIMENTO_M12,
	R_INSEGUIMENTO_M13,
	R_INSEGUIMENTO_M14,
	R_INSEGUIMENTO_M15,

	R3950,	//pausa di verifica 
	R3951,	//pausa di verifica 
	R3952,	//pausa di verifica 

};



#define NRShared (sizeof(R_list)/sizeof(int))

double R_old[NRShared][nChannel];


void sh_Mem_MC(int iList);

//Quando una R di un canale subisce una variazione, questa viene copiata in tutti i canali
//la priorità, in caso di contemporaneità, è in ordine di canale (ch0 piu prioritario di ch1 ecc..) 
void sh_Mem_MC(int iList)
{
	int rNum = R_list[iList];
	double R_CH0_loc = R[rNum];
	double R_CH1_loc = Aris_CH1[rNum];
	double R_CH2_loc = Aris_CH2[rNum];


	double chosed =  R[rNum];
	int doit = 0;

	if      (R_CH0_loc != R_old[iList][0])	{doit = 1; chosed = R_CH0_loc;}
	else if (R_CH1_loc != R_old[iList][1])	{doit = 1; chosed = R_CH1_loc;}
	else if (R_CH2_loc != R_old[iList][2])	{doit = 1; chosed = R_CH2_loc;}

	if (doit) { R[rNum] = Aris_CH1[rNum] = Aris_CH2[rNum] = R_old[iList][0] = R_old[iList][1] = R_old[iList][2] = chosed; }
}

void shared_Mem_MC(void)
{
	int i=0;


	//if (PON)
	//{
	//	for (i=0; i<NRShared; i++)
	//		{
	//			R_old[i][0] = R[R_list[i]];
	//			R_old[i][1] = Aris_CH1[R_list[i]];
	//			R_old[i][2] = Aris_CH2[R_list[i]];
	//		}
	//	return;
	//}


	R[R4410] = NRShared;

	for (i=0; i<NRShared; i++) 
		sh_Mem_MC(i);
}
