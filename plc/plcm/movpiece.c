/*

        --------------------------------------------------------------
        TITOLO          REPORT
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    EMMEGI COMET S58
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void crea_report(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           04-12-2017
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include "all.inc"

void movpiece(PPLCMAIN_LOCVARS locvars)
{
#define MAX_GANTRY_SLAVE		15
	CNCPLC_AXIS_STATUS slave_axes [MAX_GANTRY_SLAVE + 1];  // il limite massimo è sempre 1 master+15 slave
	USHORT slave_ChAxIndex [MAX_GANTRY_SLAVE + 1];
	DOUBLE gantry_ratio [MAX_GANTRY_SLAVE + 1];
	RTPLC_BIT Done_inGear = RTPLC_FALSE;
	RTPLC_BIT Done_GearOut = RTPLC_FALSE;
	RTPLC_BIT Error_GearOut = RTPLC_FALSE;
	RTPLC_BIT Error_GearIn = RTPLC_FALSE;
	SHORT ErrorID_GearIn = 0;
	SHORT ErrorID_GearOut = 0;

	if(MORSE_MOTORIZZATE)
	{
		unsigned int APP_INDICI_AX_SLAVE_M10_M12 = 0;
		unsigned int APP_INDICI_AX_SLAVE_M13_M15 = 0;
		int i = 0, j = 0, k = 0;
		double RAPP_GANTRY_SLAVE_CH2_AX0=0.0;	// Rapporto gantry slave AX1 su CH2
		double RAPP_GANTRY_SLAVE_CH2_AX1=0.0;	// Rapporto gantry slave AX2 su CH2
		double RAPP_GANTRY_SLAVE_CH2_AX2=0.0;	// Rapporto gantry slave AX3 su CH2
		double RAPP_GANTRY_SLAVE_CH2_AX3=0.0;	// Rapporto gantry slave AX4 su CH2
		double RAPP_GANTRY_SLAVE_CH2_AX4=0.0;	// Rapporto gantry slave AX5 su CH2
		double RAPP_GANTRY_SLAVE_CH2_AX5=0.0;	// Rapporto gantry slave AX6 su CH2


		double SOGLIA_FUGA_GANTRY = 0.0;
		double K_GANTRY_MASTER_SLAVE = 0.0;

		if(RESET_MC)
		{
			MORSE_NO_AGG_GANTRY_FAL = 0;
			MORSE_NO_SGAN_GANTRY_FAL = 0;
		}

		if(Mg_MC(106))
		{
			// M108 = aggancio assi in gantry
			// M109 = sganca assi in gantry
			// R5926 = R[R_MORSA_MASTER] = numero della morsa master
			// R5923 = R[R_MORSE_1_12_ASSOCIATE] = Array morse associate al pezzo da spostare (morse dalla 1 alla 12)
			// R5924 = R[R_MORSE_13_24_ASSOCIATE] = Array morse associate al pezzo da spostare (morse dalla 13 alla 24)
			// Sulla Macchina ci sono le morse
			// Morsa10 --> CH2  Ax=0
			// Morsa11 --> CH2  Ax=1
			// Morsa12 --> CH2  Ax=2
			// Morsa13 --> CH2  Ax=3
			// Morsa14 --> CH2  Ax=4
			// Morsa15 --> CH2  Ax=5


			// L'asse 0 è la morsa 10 quindi l'indice dell'asse master è dato dalla morsa master-10
			INDEX_CH_MASTER = 2;
			INDEX_AX_MASTER = (  ((unsigned int) R[R_MORSA_MASTER]) - 10 );

			// Appoggio indici morse sul pezzo considerando solo i primi 12 bit
			APP_INDICI_AX_SLAVE_M10_M12 = ((unsigned int) R[R_MORSE_1_12_ASSOCIATE]) & 0xFFF;  // prendo i 12 bit meno significativi
			APP_INDICI_AX_SLAVE_M13_M15 = ((unsigned int) R[R_MORSE_13_24_ASSOCIATE]) & 0xFFF; // prendo i 12 bit meno significativi

			// Calcolo gli indici degli assi corrispondenti alle morse sul pezzo
			INDEX_AX_SLAVE_CH2 = 0;

			// Le morse sulla macchina partono da M10 che è l'asse zero quindi APP_INDICI_AX_SLAVE_M10_M12 va shiftato a DX di 10-1 posizioni
			// mentre la morsa M13 è l'asse 3 quindi APP_INDICI_AX_SLAVE_M13_M15 va shiftato verso destra di 3 posizioni 
			INDEX_AX_SLAVE_CH2 = (APP_INDICI_AX_SLAVE_M10_M12 >> (10-1)) | (APP_INDICI_AX_SLAVE_M13_M15 << 3);
			

			//if (Start_FB_GearIn) {
			//	rtplctrace (2, "INDEX_AX_SLAVE_CH2=0x%X APP_INDICI_AX_SLAVE_M10_M12=0x%X",
			//		INDEX_AX_SLAVE_CH2, APP_INDICI_AX_SLAVE_M10_M12);
			//}

			APP_AX_IN_GANTRY_CH2 = INDEX_AX_SLAVE_CH2;  // Appoggio gli indici degli assi del CH2 da agganciare in gantry (morsa master e morse slave)


			INDEX_AX_SLAVE_CH2 = INDEX_AX_SLAVE_CH2 &  (~(1<<INDEX_AX_MASTER));  // elimino la morsa master dagli indici delle morse slave


			//if (Start_FB_GearIn) {
			//	rtplctrace (2, "INDEX_AX_SLAVE_CH2=0x%X ", INDEX_AX_SLAVE_CH2);
			//}

			//if(INDEX_AX_SLAVE_CH2 & (1<<0)) RAPP_GANTRY_SLAVE_CH2_AX0 = R[R_RAPP_GANTRY_SLAVE_CH2_AX0];
			//if(INDEX_AX_SLAVE_CH2 & (1<<1)) RAPP_GANTRY_SLAVE_CH2_AX1 = R[R_RAPP_GANTRY_SLAVE_CH2_AX1];
			//if(INDEX_AX_SLAVE_CH2 & (1<<2)) RAPP_GANTRY_SLAVE_CH2_AX2 = R[R_RAPP_GANTRY_SLAVE_CH2_AX2];
			//if(INDEX_AX_SLAVE_CH2 & (1<<3)) RAPP_GANTRY_SLAVE_CH2_AX3 = R[R_RAPP_GANTRY_SLAVE_CH2_AX3];
			//if(INDEX_AX_SLAVE_CH2 & (1<<4)) RAPP_GANTRY_SLAVE_CH2_AX4 = R[R_RAPP_GANTRY_SLAVE_CH2_AX4];
			//if(INDEX_AX_SLAVE_CH2 & (1<<5)) RAPP_GANTRY_SLAVE_CH2_AX5 = R[R_RAPP_GANTRY_SLAVE_CH2_AX5];

			SOGLIA_FUGA_GANTRY = R[R_SOGLIA_FUGA_GANTRY];

			K_GANTRY_MASTER_SLAVE = R[R_K_GANTRY_MASTER_SLAVE];

		}

		// Costruisco array degli assi slave da passare alle Function block Omcnc_GearIn e Omcnc_GearOut
		j=0;
		for(i=AX_M10_CH2; (i<=AX_M15_CH2) && (i<MAX_GANTRY_SLAVE); i++)
		{
			if(INDEX_AX_SLAVE_CH2 & (1<<i))
			{
				slave_axes[j] = AXSTATUS_CH2[i];
				slave_ChAxIndex[j] = i | (CHANNEL_CH2 << 8);  //la parte bassa contiene l'indice di questo asse slave nel suo canale, la parte alta contiene l'indice del canale di questo asse slave
				gantry_ratio[j] = 1.0;
				j++;
			}
		}

		slave_ChAxIndex[j] = 0xFFFF;  //nel primo elemento che non va usato inserire sempre 0xFFFF

		//*********** AGGANCIO MORSE IN GANTRY *************
		DP_M108 = 0;
		DN_M108 = 0;

		if(Mg_MC(108) && !APP_M108)
			DP_M108 = 1;

		if(!Mg_MC(108) && APP_M108)
			DN_M108 = 1;

		APP_M108 = Mg_MC(108);

		if(DP_M108) Start_FB_GearIn = RTPLC_TRUE;
		if(DN_M108) Start_FB_GearIn = RTPLC_FALSE;


		//if (Start_FB_GearIn) {
		//	rtplctrace (2, "Omcnc_GearIn INDEX_CH_MASTER=%d INDEX_AX_MASTER=%d [0]=0x%X [1]=0x%X [2]=0x%X [3]=0x%X [4]=0x%X [5]=0x%X [6]=0x%X k=%f s=%f",
		//		INDEX_CH_MASTER, INDEX_AX_MASTER, slave_ChAxIndex[0], slave_ChAxIndex[1], slave_ChAxIndex[2], slave_ChAxIndex[3], slave_ChAxIndex[4], slave_ChAxIndex[5],slave_ChAxIndex[6],
		//		K_GANTRY_MASTER_SLAVE, SOGLIA_FUGA_GANTRY);
		//	rtplctrace (2, "            [0]=%f [1]=%f [2]=%f [3]=%f [4]=f%f [5]=%f [6]=%f",
		//		gantry_ratio[0], gantry_ratio[1], gantry_ratio[2], gantry_ratio[3], gantry_ratio[4], gantry_ratio[5],gantry_ratio[6]);
		//}

		if((INDEX_CH_MASTER == 2) && INDEX_AX_SLAVE_CH2)  // se è presente almeno una morsa slave deve fare l'aggancio
		{
			Omcnc_GearIn (&locvars->fbGearIn_ch2, (RTPLC_BIT) Start_FB_GearIn, &CNCSTATUS_CH2, &AXSTATUS_CH2[INDEX_AX_MASTER], INDEX_AX_MASTER,
				slave_axes, slave_ChAxIndex, K_GANTRY_MASTER_SLAVE, SOGLIA_FUGA_GANTRY, gantry_ratio, 0,
				&Done_inGear, NULL, &Error_GearIn, &ErrorID_GearIn);
		}

		if(Done_inGear || (!INDEX_AX_SLAVE_CH2) ) {
			//rtplctrace (2, "Omcnc_GearIn INDEX_CH_MASTER=%d INDEX_AX_MASTER=%d Done", INDEX_CH_MASTER, INDEX_AX_MASTER);
			Mr_MC(108);
		}

		if(Error_GearIn)
		{
			//rtplctrace (1, "Omcnc_GearIn INDEX_CH_MASTER=%d INDEX_AX_MASTER=%d Error %d", INDEX_CH_MASTER, INDEX_AX_MASTER, ErrorID_GearIn);
			Mr_MC(108);
			MORSE_NO_AGG_GANTRY_FAL = 1;
			ERRORE_ID_NOAGG = ErrorID_GearIn;
		}

		// Verifico se gli assi che volevo agganciare in gantry risultano agganciati:
		//APP_AX_IN_GANTRY_CH2  // Appoggio gli indici degli assi del CH2 da agganciare in gantry

		INDEX_AX_IN_GANTRY_CH2 = 0;  // Indici degli assi del CH2 agganciati in gantry
		for(k=AX_M10_CH2; k<=AX_M15_CH2; k++)
		{
			if(APP_AX_IN_GANTRY_CH2 & (1<<k))
			{
				if(AXSTATUS_CH2[k].statusFlags.AGY) INDEX_AX_IN_GANTRY_CH2 = (INDEX_AX_IN_GANTRY_CH2 | (1<<k));
			}
		}

		// Se gli assi richiesti in aggancio gantry risultano agganciati resetta la M105
		if( Mg_MC(105) && (   (INDEX_AX_IN_GANTRY_CH2 == APP_AX_IN_GANTRY_CH2) || (!INDEX_AX_IN_GANTRY_CH2)  )  )
		{
			Mr_MC(105);
		}


		//*********** SGANCIO MORSE IN GANTRY *************

		if((INDEX_CH_MASTER == 2) && (AXSTATUS_CH2[INDEX_AX_MASTER].statusFlags.AGY)) 
			ASSI_AGG_ATTIVI = 1;
		else 
			ASSI_AGG_ATTIVI = 0;

		if((INDEX_CH_MASTER == 2) && (AXSTATUS_CH2[INDEX_AX_MASTER].statusFlags.AGY) && 
			!(AXSTATUS_CH2[INDEX_AX_MASTER].statusFlags.MOV)) 
			ASSE_MASTER_FERMO = 1;
		else 
			ASSE_MASTER_FERMO = 0;

		DP_M109 = 0;
		DN_M109 = 0;

		if(Mg_MC(109) && !APP_M109)
			DP_M109 = 1;

		if(!Mg_MC(109) && APP_M109)
			DN_M109 = 1;

		APP_M109 = Mg_MC(109);

		if(DP_M109 && ASSI_AGG_ATTIVI) Start_FB_GearOut = RTPLC_TRUE;
		if(DP_M109 && !ASSI_AGG_ATTIVI) Mr_MC(109);

		if(DN_M109) Start_FB_GearOut = RTPLC_FALSE;

		DP_RESET_GEAROUT = 0;
		if( (ASSI_AGG_ATTIVI && ASSE_MASTER_FERMO && RESET_MC) && !APP_RESET_GEAROUT)
			DP_RESET_GEAROUT = 1;

		APP_RESET_GEAROUT = ASSI_AGG_ATTIVI && ASSE_MASTER_FERMO && RESET_MC;

		if(DP_RESET_GEAROUT) Start_FB_GearOut_da_RESET = RTPLC_TRUE;

		//if (Start_FB_GearOut || Start_FB_GearOut_da_RESET) {
		//	rtplctrace (2, "Omcnc_GearOut INDEX_CH_MASTER=%d INDEX_AX_MASTER=%d [0]=0x%X [1]=0x%X [2]=0x%X [3]=0x%X [4]=0x%X [5]=0x%X [6]=0x%X",
		//		INDEX_CH_MASTER, INDEX_AX_MASTER, slave_ChAxIndex[0], slave_ChAxIndex[1], slave_ChAxIndex[2], slave_ChAxIndex[3], slave_ChAxIndex[4], slave_ChAxIndex[5],slave_ChAxIndex[6]);
		//}

		if(INDEX_CH_MASTER == 2)
		{
			Omcnc_GearOut (&locvars->fbGearOut_ch2, (RTPLC_BIT) (Start_FB_GearOut || Start_FB_GearOut_da_RESET), &CNCSTATUS_CH2, INDEX_AX_MASTER, slave_ChAxIndex,
				&Done_GearOut, NULL, &Error_GearOut, &ErrorID_GearOut);
		}


		if(Done_GearOut)
		{
			//rtplctrace (2, "Omcnc_GearOut INDEX_CH_MASTER=%d INDEX_AX_MASTER=%d Done", INDEX_CH_MASTER, INDEX_AX_MASTER);
			Mr_MC(109);
			Start_FB_GearOut_da_RESET = RTPLC_FALSE;
		}

		if(Error_GearOut)
		{
			//rtplctrace (1, "Omcnc_GearOut INDEX_CH_MASTER=%d INDEX_AX_MASTER=%d Error %d", INDEX_CH_MASTER, INDEX_AX_MASTER, ErrorID_GearOut);
			Mr_MC(109);
			MORSE_NO_SGAN_GANTRY_FAL = 1;
			ERRORE_ID_NOSGAN = ErrorID_GearOut;
		}


		if(Mg_MC(107))
		{
			Mr_MC(106);
			Mr_MC(107);
		}
	}
	else
	{
		MORSE_NO_AGG_GANTRY_FAL = 0;
		MORSE_NO_SGAN_GANTRY_FAL = 0;
		Mr_MC(105);
		Mr_MC(106);
		Mr_MC(107);
		Mr_MC(108);
		Mr_MC(109);
	}
}