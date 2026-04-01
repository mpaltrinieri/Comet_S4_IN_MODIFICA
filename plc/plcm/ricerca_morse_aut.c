
/*
        --------------------------------------------------------------
        TITOLO:         ricerca_morse_aut
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione ricerca morse se in pos. sconosciuta
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    ricerca_morse(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:      
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:     
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.1
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

int NUM_MORSE_PRESENTI;

void    ricerca_morse_aut(void)

{

if (CONF_RIC_MORSE && !CONF_TRASC_MORSE_AX_X)
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
		Mr_MC(152);
        Mr_MC(153);
	    }

		
// Conto con un INT e appoggio diretto dentro alla variabile R
NUM_MORSE_PRESENTI = 0;

if (CONF_MORSA_10) NUM_MORSE_PRESENTI++;
if (CONF_MORSA_11) NUM_MORSE_PRESENTI++;
if (CONF_MORSA_12) NUM_MORSE_PRESENTI++;		
if (CONF_MORSA_13) NUM_MORSE_PRESENTI++;
if (CONF_MORSA_14) NUM_MORSE_PRESENTI++;
if (CONF_MORSA_15) NUM_MORSE_PRESENTI++;


// Con il CT6 mi serve saperlo prima 
// Assegno alla var R il numero di morse presenti per il riferimento
if (MANO)
	R[R_NUM_MORSE]= (float) NUM_MORSE_PRESENTI;


/**** FINE CICLO RICERCA MORSE ****/
if (Mg_MC(153))
        {
		/**** ALLARME MORSE CONTATE NON CORRETTAMENTE ****/
		if (R[R_MORSE_TROVATE]!=R[R_NUM_MORSE])
				{
				CONT_MORSE_FAL  = 1;
				OBBLIGA_RIFERIMENTO = 1;		// Sriferisci gli assi
				}	
		Mr_MC(152);
		Mr_MC(153);
		}

}

else
        {
		// L'allarme CONT_MORSE_FAL non va resettato perchè è usato da entrambe le versioni
		Mr_MC(152);
        Mr_MC(153);
		}

}










