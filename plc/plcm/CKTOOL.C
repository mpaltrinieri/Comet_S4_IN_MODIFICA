/*
        --------------------------------------------------------------
        TITOLO:         CKTOOL.C
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione controllo integrità utensili
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void cktool(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          PRESETTER_UT_INGR         Utensile Ok

		M10  (10)  - Verifica utensile in corso
		M11  (11)  - Fine verifica utensile

		M12  (12)  - Verifica dispositivo integrità utensile
		M13  (13)  - Verifica integrità utensile
		M14  (14)  - Abilita allarme utensile rotto (FATM)

		M21  (21)  - Rilievo dimensioni utensile in corso
		M22  (22)  - Fine rilievo dimensioni utensile

        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         TOOL_NOK_AL       All. utensile rotto
                        TOOL_NOK_FAL      Flag utensile rotto
                        CKTOOL_NOK_AL     All. dispositivo verifica utensili guasto
                        CKTOOL_NOK_FAL    Flag dispositivo verifica utensili guasto
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CS4 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           05-08-2019
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include   "all.inc"

void cktool(void)
{
	Aris_CH2[R_COLLAUDO_03] =      Aris_CH1[R_COLLAUDO_03] =      R[R_COLLAUDO_03];

	Aris_CH2[R_CKTOOL_PRES] =      Aris_CH1[R_CKTOOL_PRES] =      R[R_CKTOOL_PRES];
	Aris_CH2[R_CKTOOL_ABIL] =      Aris_CH1[R_CKTOOL_ABIL] =      R[R_CKTOOL_ABIL];
	Aris_CH2[R_CKT_RIL_DIM_TOOL] = Aris_CH1[R_CKT_RIL_DIM_TOOL] = R[R_CKT_RIL_DIM_TOOL];
	Aris_CH2[R_CKT_RIL_RAD_TOOL] = Aris_CH1[R_CKT_RIL_RAD_TOOL] = R[R_CKT_RIL_RAD_TOOL];

	Aris_CH2[R_GEST_AVA_TOOL_ROTTO] =  Aris_CH1[R_GEST_AVA_TOOL_ROTTO] =  R[R_GEST_AVA_TOOL_ROTTO];
	
	Aris_CH2[R_CKTOOL_ESEGUITO] =      Aris_CH1[R_CKTOOL_ESEGUITO] =      R[R_CKTOOL_ESEGUITO];
	Aris_CH2[R_UT_NOK] =               Aris_CH1[R_UT_NOK] =               R[R_UT_NOK];


//	Aris_CH2[@] =      Aris_CH1[@] =      R[@];


	if (R[R_CKTOOL_PRES] > 0.5)
	{

		// INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE 
		if (PON)
		{
		}

		//
		// ESECUZIONE PROGRAMMA SIMULATO 
		//


		// RESET ALLARMI VERIFICA UTENSILE 
		if (RESET_ALL || RESET_MC)
		{
			TOOL_NOK_FAL = 0;
			CKTOOL_NOK_FAL = 0;
			Mr_MC(14);               // aggiunto per rendere resettabile l'allarme di utensile rotto
			if(R[R_ABIL_GEST_AVA_TOOL]<0.5) 
				R[R_UT_NOK] = (float) 0.0;    // aggiunto per rendere resettabile l'allarme di utensile rotto
		}

		// Reset variabili
		if (RESET_MC)
		{
			R[R_UT_NOK] = (float) 0.0;
			Mr_MC(10);
			Mr_MC(11);
			Mr_MC(12);
			Mr_MC(13);

			Mr_MC(21);
			Mr_MC(22);
		}

		// FINE CICLO VERIFICA INTEGRITA' UTENSILE 
		if (Mg_MC(11))
		{
			Mr_MC(10);
			Mr_MC(11);
		}

		// FINE CICLO RILIEVO DIMENSIONI UTENSILE 
		if (Mg_MC(22))
		{
			Mr_MC(21);
			Mr_MC(22);
		}

		// Dispositivo OK
		if (Mg_MC(12) && !PRESETTER_UT_INGR)
			Mr_MC(12);

		// Dispositivo KO, verifica integrità utensile guasto 
		if (Mg_MC(12) && RP_CKTOOL && PRESETTER_UT_INGR)
			CKTOOL_NOK_FAL = 1;

		// Utensile OK
		if (Mg_MC(13) && PRESETTER_UT_INGR)
		{
			Mr_MC(13);
			R[R_UT_NOK] = (float) 0.0;
		}

		// Utensile KO 
		if (Mg_MC(13) && RP_CKTOOL && !(PRESETTER_UT_INGR))
		{
			Mr_MC(13);
			R[R_UT_NOK] = (float) 1.0;
		}

		// allarme utensile KO
		if ((R[R_UT_NOK] > 0.5) && Mg_MC(14))  //aggiunta M14 per abilitare allarme ut. rotto solo dopo che il mandrino è fuori dal magazzino
			TOOL_NOK_FAL = 1;

	}
	else
	{
		TOOL_NOK_FAL = 0;
		CKTOOL_NOK_FAL = 0;
		R[R_UT_NOK] = (float) 0.0;
		Mr_MC(10);
		Mr_MC(11);
		Mr_MC(12);
		Mr_MC(13);
		Mr_MC(14);
		Mr_MC(21);
		Mr_MC(22);
	}

}
