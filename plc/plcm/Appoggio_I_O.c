/*
        --------------------------------------------------------------
        TITOLO:         APPOGGIO_I_O
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione appoggio input-output
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void appoggio_in(void)
                        void appoggio_out(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:       
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:      
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CS4 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           28-09-2021
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Borsari Guido
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/


#include        "all.inc"


void appoggio_in(void)
{
   /* Appoggio ingressi */

   if(Aris[R_NUM_SK_MORS_IN_1]>0.5)  MI_1_WORD1 = MI_1W1;
   if(Aris[R_NUM_SK_MORS_IN_1]>1.5)  MI_1_WORD2 = MI_1W2;
   if(Aris[R_NUM_SK_MORS_IN_1]>2.5)  MI_1_WORD3 = MI_1W3;
   if(Aris[R_NUM_SK_MORS_IN_1]>3.5)  MI_1_WORD4 = MI_1W4;
   if(Aris[R_NUM_SK_MORS_IN_1]>4.5)  MI_1_WORD5 = MI_1W5;
   //if(Aris[R_NUM_SK_MORS_IN_1]>5.5)  MI_1_WORD6 = MI_1W6;
   //if(Aris[R_NUM_SK_MORS_IN_1]>6.5)  MI_1_WORD7 = MI_1W7;

   if(Aris[R_NUM_SK_MORS_IN_2]>0.5)  MI_2_WORD1 = MI_2W1;
   if(Aris[R_NUM_SK_MORS_IN_2]>1.5)  MI_2_WORD2 = MI_2W2;
   if(Aris[R_NUM_SK_MORS_IN_2]>2.5)  MI_2_WORD3 = MI_2W3;
   if(Aris[R_NUM_SK_MORS_IN_2]>3.5)  MI_2_WORD4 = MI_2W4;
   if(Aris[R_NUM_SK_MORS_IN_2]>4.5)  MI_2_WORD5 = MI_2W5;
   //if(Aris[R_NUM_SK_MORS_IN_2]>5.5)  MI_2_WORD6 = MI_2W6;
   //if(Aris[R_NUM_SK_MORS_IN_2]>6.5)  MI_2_WORD7 = MI_2W7;

}


void appoggio_out(void)
{
   /* Appoggio uscite */

   if(Aris[R_NUM_SK_MORS_OUT_1]>0.5)  MO_1_WORD1 = MO_1W1;
   if(Aris[R_NUM_SK_MORS_OUT_1]>1.5)  MO_1_WORD2 = MO_1W2;
   if(Aris[R_NUM_SK_MORS_OUT_1]>2.5)  MO_1_WORD3 = MO_1W3;
   if(Aris[R_NUM_SK_MORS_OUT_1]>3.5)  MO_1_WORD4 = MO_1W4;
   //if(Aris[R_NUM_SK_MORS_OUT_1]>4.5)  MO_1_WORD5 = MO_1W5;
   //if(Aris[R_NUM_SK_MORS_OUT_1]>5.5)  MO_1_WORD6 = MO_1W6;
   //if(Aris[R_NUM_SK_MORS_OUT_1]>6.5)  MO_1_WORD7 = MO_1W7;
   //if(Aris[R_NUM_SK_MORS_OUT_1]>7.5)  MO_1_WORD8 = MO_1W8;
   //if(Aris[R_NUM_SK_MORS_OUT_1]>8.5)  MO_1_WORD9 = MO_1W9;

   if(Aris[R_NUM_SK_MORS_OUT_2]>0.5)  MO_2_WORD1 = MO_2W1;
   if(Aris[R_NUM_SK_MORS_OUT_2]>1.5)  MO_2_WORD2 = MO_2W2;
   if(Aris[R_NUM_SK_MORS_OUT_2]>2.5)  MO_2_WORD3 = MO_2W3;
   if(Aris[R_NUM_SK_MORS_OUT_2]>3.5)  MO_2_WORD4 = MO_2W4;
   //if(Aris[R_NUM_SK_MORS_OUT_2]>4.5)  MO_2_WORD5 = MO_2W5;
   //if(Aris[R_NUM_SK_MORS_OUT_2]>5.5)  MO_2_WORD6 = MO_2W6;
   //if(Aris[R_NUM_SK_MORS_OUT_2]>6.5)  MO_2_WORD7 = MO_2W7;
   //if(Aris[R_NUM_SK_MORS_OUT_2]>7.5)  MO_2_WORD8 = MO_2W8;
   //if(Aris[R_NUM_SK_MORS_OUT_2]>8.5)  MO_2_WORD9 = MO_2W9;
   
   if(Aris[R_NUM_SK_MORS_OUT_6]>0.5)  MO_6_WORD1  = MO_6W1;

}

