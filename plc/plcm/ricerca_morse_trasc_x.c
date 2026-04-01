
/*
        --------------------------------------------------------------
        TITOLO:         ricerca_morse fatta da asse X
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione ricerca morse se in pos. sconosciuta
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    ricerca_morse_trasc_x(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:      
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:     
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 6.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           10-12-2003
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"

void    ricerca_morse_trasc_x(void)
{

if (CONF_RIC_MORSE && CONF_TRASC_MORSE_AX_X)
{

/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
        }


/*************** RESET ALLARMI RICERCA MORSE ***************/
if (RESET_ALL || RESET_MC)
        {
        }

if (RESET_MC)
        {
        CONT_MORSE_FAL = 0;
		Mr_MC(245);
        Mr_MC(246);
        }


//	MorsaNum	R_PC	R_CNC		

//	MORSA_01	R540	R650
//	MORSA_02	R541	R651
//	-------------------------
//	MORSA_03	R542	R652
//	MORSA_04	R543	R653
//	MORSA_05	R544	R654
//	MORSA_06	R545	R655	SX
//	------------------------------
//	MORSA_07	R546	R656	DX
//	MORSA_08	R547	R657
//	MORSA_09	R548	R658
//	MORSA_10	R549	R659
//	-------------------------
//	MORSA_11	R550	R660
//	MORSA_12	R551	R661


/**** CICLO RICERCA MORSE ****/
if (!Mg_MC(245))
        {	
		NUM_MORSA_CHECK = (int)R[R_NUM_MORSE];		// A56.word		R532
		Ofs_Morse = 0;		
		if(!CONF_MORSA_10)  Ofs_Morse++;		//A59.word  Determino numero morse da saltare xkè mancanti a sx 
		if(!CONF_MORSA_11)  Ofs_Morse++;
		if(!CONF_MORSA_12)  Ofs_Morse++;
        }



/**** Morsa trovata : memorizza la posizione ****/
if (Mg_MC(245) && (R[R_POS_MORSA] != (float) 0))
{
	R_FINDPOSMORSA	= R_POS_ATTUALE_M10  + (NUM_MORSA_CHECK-1) + Ofs_Morse; // 650 + (12>>1) -1 + (0>>6)	A57.word
	R_OFFSET_MORSA	= R_OFFSET_X_MORSA_4 + (NUM_MORSA_CHECK-1) + Ofs_Morse; // 800 + (12>>1) -1 + (0>>6)	A58.word
	
	// Evito che vada a sovrascrivere variabili che non c'entrano
	if (R_FINDPOSMORSA>=R_POS_ATTUALE_M10)
			{
			R[R_FINDPOSMORSA] = R[R_POS_ATTUALE_X]+R[R_OFFSET_MORSA];
			}

	R[R_POS_MORSA] = (float)0;
	NUM_MORSA_CHECK--;
}


/**** ALLARME MORSE CONTATE NON CORRETTAMENTE ****/
if (Mg_MC(246) && (NUM_MORSA_CHECK != 0))
		{
		CONT_MORSE_FAL  = 1;

        if (CONF_ZIMMER_MORSA_10)	R[R_POS_ATTUALE_M10] = (float)32000;
        if (CONF_ZIMMER_MORSA_11)	R[R_POS_ATTUALE_M11] = (float)32000;
        if (CONF_ZIMMER_MORSA_12)	R[R_POS_ATTUALE_M12] = (float)32000;
		
		if (CONF_ZIMMER_MORSA_13)	R[R_POS_ATTUALE_M13] = (float)32000;
        if (CONF_ZIMMER_MORSA_14)	R[R_POS_ATTUALE_M14] = (float)32000;
        if (CONF_ZIMMER_MORSA_15)	R[R_POS_ATTUALE_M15] = (float)32000;
		}

if (CONT_MORSE_FAL)
        allarm (CONT_MORSE_AL);



/**** Se in manuale aggancio una morsa per muoverla, esegui la ricerca di nuovo ****/
////if (MANO &&	SBLOC_MORSA_10_O)  R[R_POS_ATTUALE_M10]	= (float)32000;
////if (MANO &&	SBLOC_MORSA_11_O)  R[R_POS_ATTUALE_M11]	= (float)32000;
////if (MANO &&	SBLOC_MORSA_12_O)  R[R_POS_ATTUALE_M12]	= (float)32000;
////
////if (MANO &&	SBLOC_MORSA_13_O)  R[R_POS_ATTUALE_M13]	= (float)32000;
////if (MANO &&	SBLOC_MORSA_14_O)  R[R_POS_ATTUALE_M14]	= (float)32000;
////if (MANO &&	SBLOC_MORSA_15_O)  R[R_POS_ATTUALE_M15]	= (float)32000;

/**** Se in manuale aggancio una morsa per muoverla, esegui la ricerca di nuovo ****/
// Il micro di presenza morse in manuale non è schiacciato perché è montato su cilindro, quindi si devono mettere
// le morse a posizione sconosciuta anche con micro morse non schiacciato
if (MANO && TRASC_MORSE_AX_X_INS_O && !TRASC_MORSE_AX_X_DIS_I && (CONF_RILEV_MORSE_AX_X || PRESENZA_MORSA_AX_X_I))
{
	if(CONF_MORSA_10) R[R_POS_ATTUALE_M10] = (float) 32000;
	if(CONF_MORSA_11) R[R_POS_ATTUALE_M11] = (float) 32000;
	if(CONF_MORSA_12) R[R_POS_ATTUALE_M12] = (float) 32000;
	if(CONF_MORSA_13) R[R_POS_ATTUALE_M13] = (float) 32000;
	if(CONF_MORSA_14) R[R_POS_ATTUALE_M14] = (float) 32000;
	if(CONF_MORSA_15) R[R_POS_ATTUALE_M15] = (float) 32000;
}

/**** FINE CICLO RICERCA MORSE ****/
if (Mg_MC(246))
        {
        Mr_MC(245);
        Mr_MC(246);
		}

}	// if (CONF_RIC_MORSE && CONF_TRASC_MORSE_AX_X)

else
{
// L'allarme CONT_MORSE_FAL non va resettato perchè è usato da entrambe le versioni
Mr_MC(245);
Mr_MC(246);
}


}	// void    ricerca_morse_trasc_ax_x








