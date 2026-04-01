/*                                                     \
        --------------------------------------------------------------
        TITOLO:         TIME_OUT
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione timer per time-out
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    time_out(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           23-05-2006
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Soffritti Riccardo
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:   
        --------------------------------------------------------------

*/
  

#include        "all.inc"


void    time_out(void)

{

/******************* Gestione TIMEOUT_01 : -------------------------- ***************/
if (!P_TIMEOUT_01)
        TIMEOUT_01 = NC_TIMEOUT_01;
else
        {
        if (TIMEOUT_01 > 0)
                TIMEOUT_01--;
        }

RP_TIMEOUT_01 = P_TIMEOUT_01 && (TIMEOUT_01 == 0);

/******************* Gestione TIMEOUT_02 : -------------------------- ***************/
if (!P_TIMEOUT_02)
        TIMEOUT_02 = NC_TIMEOUT_02;
else
        {
        if (TIMEOUT_02 > 0)
                TIMEOUT_02--;
        }

RP_TIMEOUT_02 = P_TIMEOUT_02 && (TIMEOUT_02 == 0);

/******************* Gestione TIMEOUT_03 : -------------------------- ***************/
if (!P_TIMEOUT_03)
        TIMEOUT_03 = NC_TIMEOUT_03;
else
        {
        if (TIMEOUT_03 > 0)
                TIMEOUT_03--;
        }

RP_TIMEOUT_03 = P_TIMEOUT_03 && (TIMEOUT_03 == 0);

/******************* Gestione TIMEOUT_04 : -------------------------- ***************/
if (!P_TIMEOUT_04)
        TIMEOUT_04 = NC_TIMEOUT_04;
else
        {
        if (TIMEOUT_04 > 0)
                TIMEOUT_04--;
        }

RP_TIMEOUT_04 = P_TIMEOUT_04 && (TIMEOUT_04 == 0);


/******************* Gestione TIMEOUT_05 : -------------------------- ***************/
if (!P_TIMEOUT_05)
        TIMEOUT_05 = NC_TIMEOUT_05;
else
        {
        if (TIMEOUT_05 > 0)
                TIMEOUT_05--;
        }

RP_TIMEOUT_05 = P_TIMEOUT_05 && (TIMEOUT_05 == 0);


/******************* Gestione TIMEOUT_06 : -------------------------- ***************/
if (!P_TIMEOUT_06)
        TIMEOUT_06 = NC_TIMEOUT_06;
else
        {
        if (TIMEOUT_06 > 0)
                TIMEOUT_06--;
        }

RP_TIMEOUT_06 = P_TIMEOUT_06 && (TIMEOUT_06 == 0);


/******************* Gestione TIMEOUT_07 : -------------------------- ***************/
if (!P_TIMEOUT_07)
        TIMEOUT_07 = NC_TIMEOUT_07;
else
        {
        if (TIMEOUT_07 > 0)
                TIMEOUT_07--;
        }

RP_TIMEOUT_07 = P_TIMEOUT_07 && (TIMEOUT_07 == 0);


/******************* Gestione TIMEOUT_08 : -------------------------- ***************/
if (!P_TIMEOUT_08)
        TIMEOUT_08 = NC_TIMEOUT_08;
else
        {
        if (TIMEOUT_08 > 0)
                TIMEOUT_08--;
        }

RP_TIMEOUT_08 = P_TIMEOUT_08 && (TIMEOUT_08 == 0);


/******************* Gestione TIMEOUT_09 : -------------------------- ***************/
if (!P_TIMEOUT_09)
        TIMEOUT_09 = NC_TIMEOUT_09;
else
        {
        if (TIMEOUT_09 > 0)
                TIMEOUT_09--;
        }

RP_TIMEOUT_09 = P_TIMEOUT_09 && (TIMEOUT_09 == 0);


/******************* Gestione TIMEOUT_10 : -------------------------- ***************/
if (!P_TIMEOUT_10)
        TIMEOUT_10 = NC_TIMEOUT_10;
else
        {
        if (TIMEOUT_10 > 0)
                TIMEOUT_10--;
        }

RP_TIMEOUT_10 = P_TIMEOUT_10 && (TIMEOUT_10 == 0);


/******************* Gestione TIMEOUT_11 : -------------------------- ***************/
if (!P_TIMEOUT_11)
        TIMEOUT_11 = NC_TIMEOUT_11;
else
        {
        if (TIMEOUT_11 > 0)
                TIMEOUT_11--;
        }

RP_TIMEOUT_11 = P_TIMEOUT_11 && (TIMEOUT_11 == 0);


/******************* Gestione TIMEOUT_12 : -------------------------- ***************/
if (!P_TIMEOUT_12)
        TIMEOUT_12 = NC_TIMEOUT_12;
else
        {
        if (TIMEOUT_12 > 0)
                TIMEOUT_12--;
        }

RP_TIMEOUT_12 = P_TIMEOUT_12 && (TIMEOUT_12 == 0);


/******************* Gestione TIMEOUT_13 : -------------------------- ***************/
if (!P_TIMEOUT_13)
        TIMEOUT_13 = NC_TIMEOUT_13;
else
        {
        if (TIMEOUT_13 > 0)
                TIMEOUT_13--;
        }

RP_TIMEOUT_13 = P_TIMEOUT_13 && (TIMEOUT_13 == 0);


/******************* Gestione TIMEOUT_14 : -------------------------- ***************/
if (!P_TIMEOUT_14)
        TIMEOUT_14 = NC_TIMEOUT_14;
else
        {
        if (TIMEOUT_14 > 0)
                TIMEOUT_14--;
        }

RP_TIMEOUT_14 = P_TIMEOUT_14 && (TIMEOUT_14 == 0);


/******************* Gestione TIMEOUT_15 : -------------------------- ***************/
if (!P_TIMEOUT_15)
        TIMEOUT_15 = NC_TIMEOUT_15;
else
        {
        if (TIMEOUT_15 > 0)
                TIMEOUT_15--;
        }

RP_TIMEOUT_15 = P_TIMEOUT_15 && (TIMEOUT_15 == 0);


/******************* Gestione TIMEOUT_16 : -------------------------- ***************/
if (!P_TIMEOUT_16)
        TIMEOUT_16 = NC_TIMEOUT_16;
else
        {
        if (TIMEOUT_16 > 0)
                TIMEOUT_16--;
        }

RP_TIMEOUT_16 = P_TIMEOUT_16 && (TIMEOUT_16 == 0);


/******************* Gestione TIMEOUT_17 : -------------------------- ***************/
if (!P_TIMEOUT_17)
        TIMEOUT_17 = NC_TIMEOUT_17;
else
        {
        if (TIMEOUT_17 > 0)
                TIMEOUT_17--;
        }

RP_TIMEOUT_17 = P_TIMEOUT_17 && (TIMEOUT_17 == 0);


/******************* Gestione TIMEOUT_18 : -------------------------- ***************/
if (!P_TIMEOUT_18)
        TIMEOUT_18 = NC_TIMEOUT_18;
else
        {
        if (TIMEOUT_18 > 0)
                TIMEOUT_18--;
        }

RP_TIMEOUT_18 = P_TIMEOUT_18 && (TIMEOUT_18 == 0);


/******************* Gestione TIMEOUT_19 : -------------------------- ***************/
if (!P_TIMEOUT_19)
        TIMEOUT_19 = NC_TIMEOUT_19;
else
        {
        if (TIMEOUT_19 > 0)
                TIMEOUT_19--;
        }

RP_TIMEOUT_19 = P_TIMEOUT_19 && (TIMEOUT_19 == 0);



/******************* Gestione TIMEOUT_20 : -------------------------- ***************/
if (!P_TIMEOUT_20)
        TIMEOUT_20 = NC_TIMEOUT_20;
else
        {
        if (TIMEOUT_20 > 0)
                TIMEOUT_20--;
        }

RP_TIMEOUT_20 = P_TIMEOUT_20 && (TIMEOUT_20 == 0);



/******************* Gestione TIMEOUT_21 : -------------------------- ***************/
if (!P_TIMEOUT_21)
        TIMEOUT_21 = NC_TIMEOUT_21;
else
        {
        if (TIMEOUT_21 > 0)
                TIMEOUT_21--;
        }

RP_TIMEOUT_21 = P_TIMEOUT_21 && (TIMEOUT_21 == 0);


/******************* Gestione TIMEOUT_22 : -------------------------- ***************/
if (!P_TIMEOUT_22)
        TIMEOUT_22 = NC_TIMEOUT_22;
else
        {
        if (TIMEOUT_22 > 0)
                TIMEOUT_22--;
        }

RP_TIMEOUT_22 = P_TIMEOUT_22 && (TIMEOUT_22 == 0);


/******************* Gestione TIMEOUT_23 : -------------------------- ***************/
if (!P_TIMEOUT_23)
        TIMEOUT_23 = NC_TIMEOUT_23;
else
        {
        if (TIMEOUT_23 > 0)
                TIMEOUT_23--;
        }

RP_TIMEOUT_23 = P_TIMEOUT_23 && (TIMEOUT_23 == 0);


/******************* Gestione TIMEOUT_24 : -------------------------- ***************/
if (!P_TIMEOUT_24)
        TIMEOUT_24 = NC_TIMEOUT_24;
else
        {
        if (TIMEOUT_24 > 0)
                TIMEOUT_24--;
        }

RP_TIMEOUT_24 = P_TIMEOUT_24 && (TIMEOUT_24 == 0);


/******************* Gestione TIMEOUT_25 : -------------------------- ***************/
if (!P_TIMEOUT_25)
        TIMEOUT_25 = NC_TIMEOUT_25;
else
        {
        if (TIMEOUT_25 > 0)
                TIMEOUT_25--;
        }

RP_TIMEOUT_25 = P_TIMEOUT_25 && (TIMEOUT_25 == 0);


/******************* Gestione TIMEOUT_26 : -------------------------- ***************/
if (!P_TIMEOUT_26)
        TIMEOUT_26 = NC_TIMEOUT_26;
else
        {
        if (TIMEOUT_26 > 0)
                TIMEOUT_26--;
        }

RP_TIMEOUT_26 = P_TIMEOUT_26 && (TIMEOUT_26 == 0);


/******************* Gestione TIMEOUT_27 : -------------------------- ***************/
if (!P_TIMEOUT_27)
        TIMEOUT_27 = NC_TIMEOUT_27;
else
        {
        if (TIMEOUT_27 > 0)
                TIMEOUT_27--;
        }

RP_TIMEOUT_27 = P_TIMEOUT_27 && (TIMEOUT_27 == 0);


/******************* Gestione TIMEOUT_28 : -------------------------- ***************/
if (!P_TIMEOUT_28)
        TIMEOUT_28 = NC_TIMEOUT_28;
else
        {
        if (TIMEOUT_28 > 0)
                TIMEOUT_28--;
        }

RP_TIMEOUT_28 = P_TIMEOUT_28 && (TIMEOUT_28 == 0);


/******************* Gestione TIMEOUT_29 : -------------------------- ***************/
if (!P_TIMEOUT_29)
        TIMEOUT_29 = NC_TIMEOUT_29;
else
        {
        if (TIMEOUT_29 > 0)
                TIMEOUT_29--;
        }

RP_TIMEOUT_29 = P_TIMEOUT_29 && (TIMEOUT_29 == 0);



/******************* Gestione TIMEOUT_30 : -------------------------- ***************/
if (!P_TIMEOUT_30)
        TIMEOUT_30 = NC_TIMEOUT_30;
else
        {
        if (TIMEOUT_30 > 0)
                TIMEOUT_30--;
        }

RP_TIMEOUT_30 = P_TIMEOUT_30 && (TIMEOUT_30 == 0);



/******************* Gestione TIMEOUT_31 : -------------------------- ***************/
if (!P_TIMEOUT_31)
        TIMEOUT_31 = NC_TIMEOUT_31;
else
        {
        if (TIMEOUT_31 > 0)
                TIMEOUT_31--;
        }

RP_TIMEOUT_31 = P_TIMEOUT_31 && (TIMEOUT_31 == 0);


/******************* Gestione TIMEOUT_32 : -------------------------- ***************/
if (!P_TIMEOUT_32)
        TIMEOUT_32 = NC_TIMEOUT_32;
else
        {
        if (TIMEOUT_32 > 0)
                TIMEOUT_32--;
        }

RP_TIMEOUT_32 = P_TIMEOUT_32 && (TIMEOUT_32 == 0);


/******************* Gestione TIMEOUT_33 : -------------------------- ***************/
if (!P_TIMEOUT_33)
        TIMEOUT_33 = NC_TIMEOUT_33;
else
        {
        if (TIMEOUT_33 > 0)
                TIMEOUT_33--;
        }

RP_TIMEOUT_33 = P_TIMEOUT_33 && (TIMEOUT_33 == 0);


/******************* Gestione TIMEOUT_34 : -------------------------- ***************/
if (!P_TIMEOUT_34)
        TIMEOUT_34 = NC_TIMEOUT_34;
else
        {
        if (TIMEOUT_34 > 0)
                TIMEOUT_34--;
        }

RP_TIMEOUT_34 = P_TIMEOUT_34 && (TIMEOUT_34 == 0);


/******************* Gestione TIMEOUT_35 : -------------------------- ***************/
if (!P_TIMEOUT_35)
        TIMEOUT_35 = NC_TIMEOUT_35;
else
        {
        if (TIMEOUT_35 > 0)
                TIMEOUT_35--;
        }

RP_TIMEOUT_35 = P_TIMEOUT_35 && (TIMEOUT_35 == 0);


/******************* Gestione TIMEOUT_36 : -------------------------- ***************/
if (!P_TIMEOUT_36)
        TIMEOUT_36 = NC_TIMEOUT_36;
else
        {
        if (TIMEOUT_36 > 0)
                TIMEOUT_36--;
        }

RP_TIMEOUT_36 = P_TIMEOUT_36 && (TIMEOUT_36 == 0);


/******************* Gestione TIMEOUT_37 : -------------------------- ***************/
if (!P_TIMEOUT_37)
        TIMEOUT_37 = NC_TIMEOUT_37;
else
        {
        if (TIMEOUT_37 > 0)
                TIMEOUT_37--;
        }

RP_TIMEOUT_37 = P_TIMEOUT_37 && (TIMEOUT_37 == 0);


/******************* Gestione TIMEOUT_38 : -------------------------- ***************/
if (!P_TIMEOUT_38)
        TIMEOUT_38 = NC_TIMEOUT_38;
else
        {
        if (TIMEOUT_38 > 0)
                TIMEOUT_38--;
        }

RP_TIMEOUT_38 = P_TIMEOUT_38 && (TIMEOUT_38 == 0);


/******************* Gestione TIMEOUT_39 : -------------------------- ***************/
if (!P_TIMEOUT_39)
        TIMEOUT_39 = NC_TIMEOUT_39;
else
        {
        if (TIMEOUT_39 > 0)
                TIMEOUT_39--;
        }

RP_TIMEOUT_39 = P_TIMEOUT_39 && (TIMEOUT_39 == 0);



/******************* Gestione TIMEOUT_40 : -------------------------- ***************/
if (!P_TIMEOUT_40)
        TIMEOUT_40 = NC_TIMEOUT_40;
else
        {
        if (TIMEOUT_40 > 0)
                TIMEOUT_40--;
        }

RP_TIMEOUT_40 = P_TIMEOUT_40 && (TIMEOUT_40 == 0);





}


