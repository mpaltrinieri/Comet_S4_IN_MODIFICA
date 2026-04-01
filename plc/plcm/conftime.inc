#ifndef CONFTIME_INC_INCLUDED
#define CONFTIME_INC_INCLUDED

/*

        ---------------------------------------------
        TITOLO:         CONFTIME.INC
        ---------------------------------------------
        MACCHINA:       COMET T5/T6
        ---------------------------------------------
        CLIENTE:
        ---------------------------------------------
        AUTORE:         Formuso Daniele
        ---------------------------------------------
        DESCRIZIONE:    Elementi per CONFTIME
        ---------------------------------------------

*/

typedef struct{
    unsigned int NUM_VAR_R;   //numero variabile R
	double VAL_VAR_R;         //valore variabile R
	char *COMMENTO;  //commento della Riga
} StructElemFile;

#define MAX_NUM_STRUCT_ARRAY  100
#define MAX_BUFFER_RIGA       255

#endif // CONFTIME_INC_INCLUDED
