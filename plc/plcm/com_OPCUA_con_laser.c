/*
        --------------------------------------------------------------
        TITOLO:         ACQUISIZIONE AUTOMATICA CON LASER
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Acquisizione automatica con laser
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    com_OPCUA_con_laser(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:         SI SCAMBIANO VARIABILI SU SERVER OPCUA
                       StepOver
                       AckMeasurementFinish
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:        SI SCAMBIANO VARIABILI SU SERVER OPCUA
                       PositionReadY
                       CmdResetStepOver
                       MeasurementFinish
                       ActualPositionX
                       ActualPositionX
                       ActualPositionX     
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        XTE 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"

void com_OPCUA_con_laser(void)
{
	if(R[R_INDEX_M_LASER]>0.5)
	{
		//STRUTTURA DATI DI INPUT (Input per il CN, output per l'applicativo del laser)
		//t_laser_input_shared
		//   StepOver              INT  --> Variabile di Intput
		//   AckMeasurementFinish  INT  --> Variabile di Intput

		//STRUTTURA DATI DI OUTPUT (Output per il CN, input per l'applicativo del laser)
		//t_laser_output_shared
		//   PositionReady       INT  --> Variabile di Output
		//   CmdResetStepOver    INT  --> Variabile di Output
		//   MeasurementFinish   INT  --> Variabile di Output
		//   MachineInAutomatic  INT  --> Variabile di Output
		//   ActualPositionX     REAL  --> Posizione attuale asse X
		//   ActualPositionY     REAL  --> Posizione attuale asse Y
		//   ActualPositionZ     REAL  --> Posizione attuale asse Z

		// Reset delle variabili scritte dal CN se si passa in manuale (aggiungere una info di macchina in automatico verso l'applicativo
		// per considerare validi i flag scritti dal CN ???)

		if(!AUTO)
		{
			variabili_globali.t_laser_output_shared.PositionReady = 0;
			variabili_globali.t_laser_output_shared.CmdResetStepOver = 0;
			variabili_globali.t_laser_output_shared.MeasurementFinish = 0;
			variabili_globali.t_laser_output_shared.MachineInAutomatic = 0;
		}
		else
		{
			variabili_globali.t_laser_output_shared.MachineInAutomatic = 1;
		}

		// R13199 = contiene l'indice della funzione ausiliaria FATM sui cui si ferma ad ogni passo l'esecuzione del part-program di acquisizione delle correzioni laser
		// R13199 fissata in CONFMAC.XTE a 150 --> M150 è la funzione FATM di sincronizzazione tra il CN e l'applicativo del laser
		DP_M150 = 0;
		if(Mg_MC(150) && !APP_M150)
			DP_M150 = 1;
		APP_M150 = Mg_MC(150);

		////if(DP_M150)
		////{
		////	// Il CN indica all'applicativo che gli assi hanno terminato lo step --> può fare l'acquisizione 
		////	variabili_globali.t_laser_output_shared.PositionReady = 1;
		////}

		if(M150 && !(variabili_globali.t_laser_output_shared.PositionReady))
		{
			// Il CN indica all'applicativo che gli assi hanno quasi terminato lo step --> può fare l'acquisizione appena 
			if(  (R[R_DIST_X_ABS]<=R[R_TOLL_POS_READY]) && (R[R_DIST_Y_ABS]<=R[R_TOLL_POS_READY]) && (R[R_DIST_Z_ABS]<=R[R_TOLL_POS_READY]) )
			   variabili_globali.t_laser_output_shared.PositionReady = 1;
		}

		// Il CN espone sempre verso l'applicativo le quote assolute degli assi X, Y, Z
		variabili_globali.t_laser_output_shared.ActualPositionX = (float) R[R_QUOTA_X];
		variabili_globali.t_laser_output_shared.ActualPositionY = (float) R[R_QUOTA_Y];
		variabili_globali.t_laser_output_shared.ActualPositionZ = (float) R[R_QUOTA_Z];

		// Quando l'applicativo ha fatto l'acquisizione indica al CN di andare allo step successivo scrivendo StepOver=1, il CN indica all'applicativo
		// di aver recepito e chiede di resettare StepOver scrivendo CmdResetStepOver=1
		if( variabili_globali.t_laser_input_shared.StepOver && variabili_globali.t_laser_output_shared.PositionReady )
			variabili_globali.t_laser_output_shared.CmdResetStepOver = 1;
		if( !variabili_globali.t_laser_input_shared.StepOver && variabili_globali.t_laser_output_shared.CmdResetStepOver && variabili_globali.t_laser_output_shared.PositionReady)
		{
			variabili_globali.t_laser_output_shared.PositionReady = 0;
			variabili_globali.t_laser_output_shared.CmdResetStepOver = 0;
			Mr_MC(150);  // Reset delle funzione M150 ausiliaria FATM
		}

		// Il CN indica all'applicativo che il part-program ha raggiunto la fine
		DP_M02 = 0;
		if(M02 && !APP_M02)
			DP_M02 = 1;
		APP_M02 = M02;

		if(DP_M02)
			variabili_globali.t_laser_output_shared.MeasurementFinish = 1;
		if(variabili_globali.t_laser_input_shared.AckMeasurementFinish && variabili_globali.t_laser_output_shared.MeasurementFinish)
			variabili_globali.t_laser_output_shared.MeasurementFinish = 0;
	}

}
