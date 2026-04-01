/*
        --------------------------------------------------------------
        TITOLO:         LUBRICA
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione lubrificazione a impulsi
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    lubrica(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          R[R_FREQ_LUBRICA]  Frequenza di lubr. lubrica
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         REFR_LUBRICA_O     EV refrigerante lubrica
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           30-08-2000
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo - Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include "all.inc"


void    lubrica(void)
{


if (CONF_REF_LUBRICA || CONF_REF_SPECIALE)
{

/**** INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE ****/
if (PON)
        {
        }


/********************************************************************************/ 
/********************************************************************************/
/************	                NOTA SULLE LUBRICHE              ****************/
/********************************************************************************/
/********************************************************************************/

if(RESET_ALL || RESET_MC)
{
	LIV_LUB_NOT_BASSO_FAL = 0;
	LIV_LUB_NOT_ALTO_FAL = 0;
}


// resettati i valori di lubrificazione mettendo in manuale
if(DP_MANU)
{
	R[R_FREQ_LUBRICA] = 60;
	R[R_TIPO_LUBRICA] = 15;
}

// Valide per tutte le lubriche
COND_COMUNI_LUBRICHE = (R[R_FREQ_LUBRICA] > 0.5) && !M_HOLD && AUX_INSER_I;

MAN_LUBRICA_B =  MANO && FUNZ_MAN17 && COMANDO_AUX_B;	// funz.man. lubrica intermittente
MAN_LUBRICA_A =  MANO && FUNZ_MAN17 && COMANDO_AUX_A;	// funz.man. lubrica continua (nuova funzione per spurgo tubi) 
MAN_LUBRICA_AB = MANO && FUNZ_MAN17 && (COMANDO_AUX_A || COMANDO_AUX_B);

AUT_LUBRICA = M07 && (R[R_ENDURANCE]<0.5);


/**** CALCOLO TEMPI POMPA ON/OFF ****/

R[R_LUBRICA_FREQ_CAMPLUS] = R[R_FREQ_LUBRICA];

if(R[R_LUBRICA_TIPO_GESTIONE] < 0.5)            // **** 0 : GESTIONE LUBRICA A FREQUENZA VARIABILE, FINO AL 22/11/2021 *******************
{
	if (R[R_LUBRICA_FREQ_CAMPLUS] > 120)  R[R_LUBRICA_FREQ_CAMPLUS] = (float)120;       /* Max frequenza */
	if (R[R_LUBRICA_FREQ_CAMPLUS] < 1)    R[R_LUBRICA_FREQ_CAMPLUS] = (float)1;         /* Min frequenza */

	R[R_LUBRICA_TEMPO_OF] = (float)((60 / R[R_LUBRICA_FREQ_CAMPLUS]) - 0.3);    /* Tempo pompa OFF */

	if ( (!M07 || M_HOLD) && !MAN_LUBRICA_AB )
		retrig ( T_LUBRICA_OFF, (float)(R[R_LUBRICA_TEMPO_OF]) );       /* Caricamento tempo pompa OFF */
}
else if(R[R_LUBRICA_TIPO_GESTIONE] < 1.5)       // **** 1 : GESTIONE LUBRICA A FREQUENZA FISSA E DUTY-CYCLE VARIABILE, DAL 22/11/2021 ****
{
	if (R[R_LUBRICA_FREQ_CAMPLUS] > 120)  R[R_LUBRICA_FREQ_CAMPLUS] = (float)120; // Limitazione frequenza Max
	if (R[R_LUBRICA_FREQ_CAMPLUS] < 0)    R[R_LUBRICA_FREQ_CAMPLUS] = (float)0;   // Limitazione frequenza Min

	// coeff. angolare della retta del duty cycle
	R[R_LUBRICA_DUTY_COEFF_ANG] = ( R[R_LUBRICA_DUTY_CYCLE_MAX] - R[R_LUBRICA_DUTY_CYCLE_MIN] ) / ( 119 - 1 );

	// calcolo del duty cycle
	if      (R[R_LUBRICA_FREQ_CAMPLUS] < 0.5)   R[R_LUBRICA_DUTY_CYCLE] = 0;
	else if (R[R_LUBRICA_FREQ_CAMPLUS] < 1.5)   R[R_LUBRICA_DUTY_CYCLE] = R[R_LUBRICA_DUTY_CYCLE_MIN];

	else if (R[R_LUBRICA_FREQ_CAMPLUS] < 118.5) R[R_LUBRICA_DUTY_CYCLE] = R[R_LUBRICA_DUTY_CYCLE_MIN] + ( R[R_LUBRICA_FREQ_CAMPLUS] * R[R_LUBRICA_DUTY_COEFF_ANG] );

	else if (R[R_LUBRICA_FREQ_CAMPLUS] < 119.5) R[R_LUBRICA_DUTY_CYCLE] = R[R_LUBRICA_DUTY_CYCLE_MAX];
	else                                        R[R_LUBRICA_DUTY_CYCLE] = 100;

	R[R_LUBRICA_PERIODO] = 60 / R[R_LUBRICA_FREQ_CONFMAC];

	R[R_LUBRICA_TEMPO_ON] = R[R_LUBRICA_PERIODO] * R[R_LUBRICA_DUTY_CYCLE] / 100 ;
	R[R_LUBRICA_TEMPO_OF] = R[R_LUBRICA_PERIODO] - R[R_LUBRICA_TEMPO_ON];

	if ( (!M07 || M_HOLD) && !MAN_LUBRICA_AB )
	{
		retrig ( T_LUBRICA_ON , (float)(R[R_LUBRICA_TEMPO_ON]) );    /* Caricamento tempo pompa ON  */
		retrig ( T_LUBRICA_OFF, (float)(R[R_LUBRICA_TEMPO_OF]) );    /* Caricamento tempo pompa OFF */
	}
}


/**** GESTIONE VALVOLE LUBRIFICAZIONE  ****/
// Dalla word ottengo i singoli bit 
LUBRICA_ATTIVA = (int)(R[R_TIPO_LUBRICA]+0.1);		

if(R[R_LUBRICA_TIPO_GESTIONE] < 0.5)            // **** 0 : GESTIONE LUBRICA A FREQUENZA VARIABILE, FINO AL 22/11/2021 *******************
{
	// Ausiliari di lubrificazione mandrini
	AUX1_LUBRICA_ON = (MAN_LUBRICA_AB || AUT_LUBRICA) && COND_COMUNI_LUBRICHE;
	AUX2_LUBRICA_ON = AUX1_LUBRICA_ON && ( (P_LUBRICA_ON && !RP_LUBRICA_ON) || (R[R_LUBRICA_FREQ_CAMPLUS] > 99.9) || MAN_LUBRICA_A );

	// *********************** MODIFICHE PER CONNECT ***********************
	// INFORMAZIONE SU LUBRICA ATTIVA E DUTY CYCLE ESPOSTE PER VOILAP CONNECT (SOLO PER SERBATOIO LUBRICA NORMALE)
    // I cicli di refrigerazione settano il tempo di pompa off, il tempo di pompa on è fisso a 0.3 secondi
	//Ton/(Ton+Toff)
	AF_DUTYCYCLE = (float) ( (0.3f/((float)(R[R_LUBRICA_TEMPO_OF])+0.3f) )*100.0f);
	// 0.3 è il valore fissato nella formula del retrig del timer ed indica quanto tempo rimane accesa la lubrica in un singolo ciclo di refrigerazione
	// R[R_LUBRICA_TEMPO_OF] = indica quanto tempo rimane spenta la lubrica in un ciclo di refrigerazione (dipende dalla frequenza di lubrificazione impostata)
	AF_LUBRICA_ON = (float)((MAN_LUBRICA_AB || AUT_LUBRICA) && COND_COMUNI_LUBRICHE);
	// *********************** FINE MODIFICHE PER CONNECT ***********************
}
else if(R[R_LUBRICA_TIPO_GESTIONE] < 1.5)       // **** 1 : GESTIONE LUBRICA A FREQUENZA FISSA E DUTY-CYCLE VARIABILE, DAL 22/11/2021 ****
{
	// Ausiliari di lubrificazione mandrini
	AUX1_LUBRICA_ON = (MAN_LUBRICA_AB || AUT_LUBRICA) && COND_COMUNI_LUBRICHE;
	AUX2_LUBRICA_ON = AUX1_LUBRICA_ON && ( (P_LUBRICA_ON && !RP_LUBRICA_ON) || (R[R_LUBRICA_DUTY_CYCLE] > 99.9) || MAN_LUBRICA_A );

	// *********************** MODIFICHE PER CONNECT ***********************
	// INFORMAZIONE SU LUBRICA ATTIVA E DUTY CYCLE ESPOSTE PER VOILAP CONNECT 

	//Ton/(Ton+Toff)
	AF_DUTYCYCLE = (float) ((R[R_LUBRICA_TEMPO_ON]/(R[R_LUBRICA_TEMPO_ON]+R[R_LUBRICA_TEMPO_OF]))*100.0f);
	// R[R_LUBRICA_TEMPO_ON] = indica quanto tempo rimane accesa la lubrica in un ciclo di refrigerazione
	// R[R_LUBRICA_TEMPO_OF] = indica quanto tempo rimane spenta la lubrica in un ciclo di refrigerazione
	AF_LUBRICA_ON = (float) ((MAN_LUBRICA_AB || AUT_LUBRICA) && COND_COMUNI_LUBRICHE);
	// *********************** FINE MODIFICHE PER CONNECT ***********************
}

if (CONF_REF_LUBRICA)
{
	// Pilotaggio uscita lubriche standard
	LUBRICA_1_O = LUBRICA_1_ATTIVA && AUX1_LUBRICA_ON && AUX2_LUBRICA_ON;
	LUBRICA_2_O = LUBRICA_2_ATTIVA && AUX1_LUBRICA_ON && AUX2_LUBRICA_ON;
	LUBRICA_3_O = LUBRICA_3_ATTIVA && AUX1_LUBRICA_ON && AUX2_LUBRICA_ON;
	LUBRICA_4_O = LUBRICA_4_ATTIVA && AUX1_LUBRICA_ON && AUX2_LUBRICA_ON;
}


// **** GESTIONE REFRIGERANTE SPECIALE (VORTEX) ****
if (CONF_REF_SPECIALE)
{
	MAN_REFSPEC = MANO          && !M_HOLD && AUX_INSER_I && FUNZ_MAN18 && COMANDO_AUX_B;
	AUT_REFSPEC = AUTO_CICLOMAN && !M_HOLD && AUX_INSER_I && (R[R_USA_REFSPEC]>0.5) && M07 && (R[R_ENDURANCE]<0.5);

	LUBRICA_SPEC_O = (MAN_REFSPEC || AUT_REFSPEC);
}


/* Reset funzione ausiliaria "M" */
if (M09 || M05 && !MEM_MASCRIG || M02 || RESET_MC)
        {
        M07 = 0;
		M09 = 0;
        }


if (CONF_REF_LUBRICA)
{
	/**** Allarme per operatore : Livello lubrica basso ****/
	if (CONF_LIV_LUBRICA_BASSO && RP_LIV_LUB_NOT_BASSO && !CICLO_ON && ALIM_PRES_I)
				LIV_LUB_NOT_BASSO_FAL = 1;

	/**** Allarme per operatore : Livello lubrica alto ****/
	if (CONF_LIV_LUBRICA_ALTO && RP_LIV_LUB_NOT_ALTO && !CICLO_ON && ALIM_PRES_I)
				LIV_LUB_NOT_ALTO_FAL = 1;
}


/**** GESTIONE FUNZIONE ESEGUITA ****/
LUBRICA_FUNES_A = MAN_LUBRICA_A;
LUBRICA_FUNES_B = MAN_LUBRICA_B && P_OSCILLATORE;

REFSPEC_FUNES_B = FUNZ_MAN18 && COMANDO_AUX_B && P_OSCILLATORE;

}

else
        {
		LIV_LUB_NOT_BASSO_FAL = 0;
		LIV_LUB_NOT_ALTO_FAL = 0;
        }

}
