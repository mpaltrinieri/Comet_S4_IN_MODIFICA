/*
        --------------------------------------------------------------
        TITOLO:         COUNT
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione conteggio movimento
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    count(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          OUT                uscita start conteggio
                        IN                 Ingresso stop conteggio
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         COUNT              Appoggio conteggio
                        MEMCOUNT           Memorizzazione conteggio
                        MEM                Memorizzazione effettuata
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CS4 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           13-05-2020
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Pecchi Andrea
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include "all.inc"
#include "conftime.inc"

extern StructElemFile ELEM_FILE[MAX_NUM_STRUCT_ARRAY];


void count   (int *_OUT, int *_IN, int *_COUNT, int *_MEMCOUNT, int *_MEM, int NUM_PARAMETRO, char *COMMENTO)

{

if (AUTO_CICLOMAN && !ASSI_NORIF_FMS && CICLO_ON)
        {
        /* Caricamento valori all'accensione */
        if (PON)
                {
                *_COUNT = (int)0;
                *_MEM = (int)0;
                *_MEMCOUNT = (int)R[NUM_PARAMETRO];
                }

        /* Azzeramento contatore */
        if ((*_OUT == (int)0) && ((*_COUNT != (int)0) || (*_MEM != (int)0)))
                {
                *_COUNT = (int)0;
                *_MEM = (int)0;
                }
        /* Incremento contatore */
        if ((*_OUT == (int)1) && (*_IN == (int)0))
                {
                *_COUNT = *_COUNT + (int)1;
                }
        /* Memorizzazione contatore */
        if ((*_OUT == (int)1) && (*_IN == (int)1) && (*_MEM == (int)0))
                {
                *_MEM = (int)1;
                if (*_MEMCOUNT == (int)0)
                        {
                        *_MEMCOUNT = *_COUNT;
                        R[NUM_PARAMETRO] = (float)*_MEMCOUNT;
                        }
                else
                        {
                        *_MEMCOUNT = (int)((*_MEMCOUNT + (*_COUNT/10) + 1) / 1.1);
                        R[NUM_PARAMETRO] = (float)*_MEMCOUNT;
                        }
                }
        }

//Salvo nella struttura i valori da scrivere successivamente nel file alla derivata negativa di ausiliari inseriti
if(DN_AUXON && (R[R_WRITE_CONFTIME] >= 0.5))
{
	if(INDEX_ELEM_CONFTIME < MAX_NUM_STRUCT_ARRAY) //controllo che non vada a scrivere fuori dai limiti dell'array
	{
		ELEM_FILE[INDEX_ELEM_CONFTIME].NUM_VAR_R = NUM_PARAMETRO;
		ELEM_FILE[INDEX_ELEM_CONFTIME].VAL_VAR_R = R[NUM_PARAMETRO];
		ELEM_FILE[INDEX_ELEM_CONFTIME].COMMENTO = COMMENTO;
	}

	INDEX_ELEM_CONFTIME++; //incrementa indice elementi da salvare su struttura e successivamente da scrivere sul file
}

}
