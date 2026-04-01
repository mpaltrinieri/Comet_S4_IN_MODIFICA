#ifndef IO_INC_INCLUDED
#define IO_INC_INCLUDED
#include "io_ext.inc"

/*

        ---------------------------------------------
        TITOLO:         I_O.INC
        ---------------------------------------------
        MACCHINA:       EMMEGI COMET S4
        ---------------------------------------------
        RELEASE:        1.0
        ---------------------------------------------
        DATA:           04-04-2022
        ---------------------------------------------
        AUTORE:         G.Borsari
        ---------------------------------------------
        DESCRIZIONE:    Definizione I/O PLC
        ---------------------------------------------

*/

/*********************************************************************************/
/****************************** DEFINIZIONE INGRESSI PLC *************************/
/*********************************************************************************/
/* Le ultime lettere della definizione dell'ingresso ne definiscono il tipo:
    _I  = bit
    _IB = byte
    _IW = word

                                        *               *               *           *                   *                   *               *               *                       
====================================================================================================================================================================================================
                                        Morsettiera     Nodo_Siom_Dig   Indir_Fis   Dimens_Siom_Dig     Dimens_Siom_Anl     Nodo_Siom_Anl   NodoENC IndENC  DimENC  TipoNodo        
                                        [MI]    [MO]    [I]     [O]                 DI      DO          AI(AD)  AO(DA)      [I]     [O]                                                             
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
SCHEDA1: DEBUG      (80i 64o)           1       1       0       0       1           5       4           /       /           /       /       /       /       /       DEBUG (SCHEDA VIRTUALE)                        
--------------------------------------------------------------------------------------------------------/-------/-----------/-------/-------/-------/-------/---------------------------------------
SCHEDA2: ETHERCAT   (80i 64o)           2       2       1       1       2           5       4           /       /           /       /       /       /       /       ETHERCAT ISAC          
--------------------------------------------------------------------------------------------------------/-------/-----------/-------/-------/-------/-------/---------------------------------------
SCHEDA3: DEBUG      (48i 48o)           3       3       2       2       3           3       2           /       /           /       /       /       /       /       DEBUG             
--------------------------------------------------------------------------------------------------------/-------/-----------/-------/-------/-------/-------/---------------------------------------
SCHEDA4: DEBUG      (48i 48o)           4       4       3       3       4           3       2           /       /           /       /       /       /       /       DEBUG             
--------------------------------------------------------------------------------------------------------/-------/-----------/-------/-------/-------/-----------------------------------------------
SCHEDA5: MGPILOT:                       /       /       4       4       63          3       2           /       /           /       /       /       /       1       ETHERCAT      
--------------------------------------------------------------------------------------------------------/-------/-----------/-------/-------/-------/-----------------------------------------------
SCHEDA6: BRIDGE:    ( 0i 16o)           /       /       /       /       /           0       1           /       /           /       /       /       /       /       
====================================================================================================================================================================================================

*/


/**********************************************/
/********* SCHEDA2 REALE INGRESSI     *********/
/**********************************************/

// --------------------------------------------------------------------------------------
// word DI 1

#define ALIM_PRES_I               MI_2_1    //MI_2_1  Alimentazioni presenti
#define NO_EMERG_I                MI_2_2    //MI_2_2  Macchina non in emergenza
#define AUX_INSER_I               MI_2_3    //MI_2_3  Ausiliari inseriti
#define ARIA_PRES_I               MI_2_4    //MI_2_4  Pressostato aria presente
#define TERM_GEN_I                MI_2_5    //MI_2_5  Termici Generici non scattati
#define SEL_MANU_I                MI_2_6    //MI_2_6  Macchina in manuale
#define SEL_SEMIAUTO_I            MI_2_7    //MI_2_7  Macchina in semiautomatico
#define SEL_AUTO_I                MI_2_8    //MI_2_8  Macchina in automatico

#define PLS_CONFERMA_ZONASX_I     MI_2_9    //MI_2_9  PLS di conferma zona SX
#define SEL_SBLOC_MORSE_SX_I      MI_2_10   //MI_2_10 Selettore sbloccaggio morse SX
#define SEL_BLOCC_MORSE_SX_I      MI_2_11   //MI_2_11 Selettore bloccaggio morse SX
#define SEL_SBLOC_MORSE_DX_I      MI_2_12   //MI_2_12 Selettore sbloccaggio morse DX
#define SEL_BLOCC_MORSE_DX_I      MI_2_13   //MI_2_13 Selettore bloccaggio morse DX
#define PLS_CONFERMA_ZONADX_I     MI_2_14   //MI_2_14 PLS di conferma zona DX
#define LIV_LUB_NO_BASSO_I        MI_2_15   //MI_2_15 Livello lubrica non basso
#define LIV_LUB_NO_ALTO_I         MI_2_16   //MI_2_16 Livello lubrica non alto

// --------------------------------------------------------------------------------------
// word DI 2

#define UOMO_MORTO_I              MI_2_17   //MI_2_17 Pulsante uomo morto premuto
#define CENTRALINA_OK_I           MI_2_18   //MI_2_18 Centralina di sicurezza OK (immediato)
#define OUT_MAC_ABIL_I            MI_2_19   //MI_2_19 Uscite movimenti pericolosi abilitate (ritardato)
#define VEL_MANDR_I               MI_2_20   //MI_2_20 S3: mandrino in rotazione
#define UT_SGANC_I                MI_2_21   //MI_2_21 S2: mandrino sganciato (pinza fuori)
#define UT_AGGAN_I                MI_2_22   //MI_2_22 S1:  mandrino agganciato (pinza dentro)
#define TERM_FRIGO_OK_I           MI_2_23   //MI_2_23 Termico OK raffredd. Mandrino
#define FLUSSOSTATO_OK_I          MI_2_24   //MI_2_24 Flussostato su centralina di raffreddamento OK

#define VEL_INVERTEROK_I          MI_2_25   //MI_2_25 Velocita inverter ok
#define INV_NONBLOC_I             MI_2_26   //MI_2_26 Inverter non in blocco
#define MANDRINO_FERMO_I          MI_2_27   //MI_2_27 Mandrino fermo (reale solo con encoder)
#define LOAD_INVERTEROK_I         MI_2_28   //MI_2_28 Inverter non in sovraccarico
#define TOOL_PRES_SUP_I           MI_2_29   //MI_2_29 Fotocellula presenza utensile linea superiore
#define TOOL_PRES_INF_I           MI_2_30   //MI_2_30 Fotocellula presenza utensile linea inferiore
#define GANCIO_MAG_NODIS_I        MI_2_31   //MI_2_31 Gancio magazzino non disinserito (NC)
#define GANCIO_MAG_NOINS_I        MI_2_32   //MI_2_32 Gancio magazzino non inserito (NC)

// --------------------------------------------------------------------------------------
// word DI 3

#define TRASC_MORSE_AX_X_INS_I    MI_2_33   //MI_2_33 Sensore Magnetico Trascinatore Morse Asse X Inserito (non Comet R4i/S4i)
#define TRASC_MORSE_AX_X_DIS_I    MI_2_34   //MI_2_34 Sensore Magnetico Trascinatore Morse Asse X Disinserito (non Comet R4i/S4i)
#define PRESENZA_MORSA_AX_X_I     MI_2_35   //MI_2_35 Micro Presenza Morsa su Asse X (non Comet R4i/S4i)
#define TAVOLA_AVA_I              MI_2_36   //MI_2_36 Pressostato Tavola Avanti
#define TAVOLA_IND_I              MI_2_37   //MI_2_37 Pressostato Tavola Indietro
#define PRESS_MORSE_HP_I          MI_2_38   //MI_2_38 Pressostato alta pressione morse presente
#define BATTUTA_SX_BAS_I          MI_2_39   //MI_2_39 Battuta zona SX bassa
#define BATTUTA_DX_BAS_I          MI_2_40   //MI_2_40 Battuta zona DX bassa

#define RIP_ANT_AP_SX_I           MI_2_41   //MI_2_41 Riparo anteriore aperto (cilindro SX)
#define RIP_ANT_AP_DX_I           MI_2_42   //MI_2_42 Riparo anteriore aperto (cilindro DX)
#define RIP_ANT_CH_SX_I           MI_2_43   //MI_2_43 Riparo anteriore chiuso (cilindro SX)
#define RIP_ANT_CH_DX_I           MI_2_44   //MI_2_44 Riparo anteriore chiuso (cilindro DX)
#define RIP_ANT_CH_SICUR_I        MI_2_45   //MI_2_45 Riparo anteriore alto e Visiera vert.alta (RFID)
#define TEMP_OK_I                 MI_2_46   //MI_2_46 Temperatura armadio ok
#define VISIERA_AVA_I             MI_2_47   //MI_2_47 Visiera avanti (visiera aperta)
#define VISIERA_IND_I             MI_2_48   //MI_2_48 Visiera indietro (visiera chiusa)

// --------------------------------------------------------------------------------------
// word DI 4

#define RIPARO_POST_SX_CH_I       MI_2_49   //MI_2_49 Riparo Posteriore SX Chiuso (RFID)
#define RIPARO_POST_DX_CH_I       MI_2_50   //MI_2_50 Riparo Posteriore DX Chiuso (RFID) (OPT)
#define SPORT_LAT_SX_AP_I         MI_2_51   //MI_2_51 Sportello laterale SX aperto (0:chiuso)
#define SPORT_LAT_DX_AP_I         MI_2_52   //MI_2_52 Sportello laterale DX aperto (0:chiuso)
#define BATTUTA_DX_POS4_I         MI_2_53   //MI_2_53 Battuta DX in posizione 4 (micro induttivo)
#define BATTUTA_DX_POS1_I         MI_2_54   //MI_2_54 Battuta DX in posizione 1 (micro induttivo)
#define BATTUTA_DX_POS2_I         MI_2_55   //MI_2_55 Battuta DX in posizione 2 (micro induttivo)
#define BATTUTA_DX_POS3_I         MI_2_56   //MI_2_56 Battuta DX in posizione 3 (micro induttivo)

#define BATT_PREC_RIP_I           MI_2_57   //MI_2_57 Paletta battuta di precisione a riposo (OPT) 
#define BATT_PREC_MIS_I           MI_2_58   //MI_2_58 Paletta battuta di precisione in posizione di misura (OPT)
#define INGRASS_LIV_OK_I          MI_2_59   //MI_2_59 Livello grasso ok per l'ingrassaggio automatico pattini (OPT)
#define INGRASS_ATTIVO_I          MI_2_60   //MI_2_60 Ingrassaggio automatico pattini avvenuto correttamente (OPT)
#define TERM_ASP_OK_I             MI_2_61   //MI_2_61 Termico aspiratore interno non scattato (OPT)
#define TERM_TRASP_OK_I           MI_2_62   //MI_2_62 Termico nastro trasportatore ok (OPT)
#define ALIM_MM_OK_I              MI_2_63   //MI_2_63 Alimentatori morse motorizzate OK
#define BORDO_SENSIB_OK_I         MI_2_64   //MI_2_64 Bordo sensibile del riparo anteriore OK (OPT)

// --------------------------------------------------------------------------------------
// word DI 5

#define MARPOSS_TOUCH_I           MI_2_65   //MI_2_65 Tastatore in battuta (OPT)
#define MARPOSS_LOWBA_I           MI_2_66   //MI_2_66 Tastatore low battery (OPT)
#define MARPOSS_NOERR_I           MI_2_67   //MI_2_67 Tastatore non in errore (OPT)
#define MANDRINO_VIBR_TEMP_OK_I   MI_2_68   //MI_2_68 Vibrazioni e temperatura OK nel mandrino (OPT) (0: interrompe start inverter)
#define PRESETTER_UT_I            MI_2_69   //MI_2_69 Presetter, Verifica integrita utensili (OPT)
#define FREE_MI_2_70              MI_2_70   //MI_2_70 Free
#define FREE_MI_2_71              MI_2_71   //MI_2_71 Free
#define FREE_MI_2_72              MI_2_72   //MI_2_72 Free

#define FREE_MI_2_73              MI_2_73   //MI_2_73 Free
#define FREE_MI_2_74              MI_2_74   //MI_2_74 Free
#define FREE_MI_2_75              MI_2_75   //MI_2_75 Free
#define FREE_MI_2_76              MI_2_76   //MI_2_76 Free
#define FREE_MI_2_77              MI_2_77   //MI_2_77 Free
#define FREE_MI_2_78              MI_2_78   //MI_2_78 Free
#define FREE_MI_2_79              MI_2_79   //MI_2_79 Free
#define FREE_MI_2_80              MI_2_80   //MI_2_80 Free

// --------------------------------------------------------------------------------------


/*********************************************************************************/
/****************************** DEFINIZIONE USCITE PLC ***************************/
/*********************************************************************************/
/* Le ultime lettere della definizione dell'ingresso ne definiscono il tipo:
    _O  = bit
    _OB = byte
    _OW = word
*/


/**********************************************/
/********** SCHEDA2 REALE USCITE     **********/
/**********************************************/

// --------------------------------------------------------------------------------------
// word DO 1

// 24USC COMUNE 24VDC USCITE FISSE 
#define NOEMER_PLC_O              MO_2_1    //MO_2_1  Non emergenza da PLC
#define AUX_INSER_O               MO_2_2    //MO_2_2  Inserzione ausiliari (usare uscita a relè)
#define FREE_MO_2_3               MO_2_3    //MO_2_3  Free
#define LAMP_ZONA_SX_O            MO_2_4    //MO_2_4  Lampada di stato

// 24USC COMUNE 24VDC USCITE FISSE 
#define MASC_RIGID_O              MO_2_5    //MO_2_5  Maschiatura Rigida (S5)
#define ACC_INV_AB_O              MO_2_6    //MO_2_6  Inclusione rampe inverter (S6) 
#define RESET_INVERTER_O          MO_2_7    //MO_2_7  Reset allarmi inverter
#define SBL_RIT_MANDRINO_O        MO_2_8    //MO_2_8  Sblocco ritenuta teleruttore mandrino

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define SBLOC_UT_O                MO_2_9    //MO_2_9  Sbloccaggio utensile
#define VISIERA_IND_O             MO_2_10   //MO_2_10 Arretramento Visiera (chiusura visiera oriz.)
#define BATTUTA_SX_ALT_O          MO_2_11   //MO_2_11 EV Battuta SX alta
#define BATTUTA_DX_ALT_O          MO_2_12   //MO_2_12 EV Battuta DX alta

// 24PMC COMUNE 24VDC USCITE PERICOLOSE_MANDRINO
#define ALIM_MANDR_O              MO_2_13   //MO_2_13 Alimentazione motore mandrino
#define START_INVERTER_O          MO_2_14   //MO_2_14 Start inverter
#define CH_MORSA_10_HP_O          MO_2_15   //MO_2_15 EV Chiudi Morsa 10 in alta forza (OPT)
#define CH_MORSA_11_HP_O          MO_2_16   //MO_2_16 EV Chiudi Morsa 11 in alta forza

// --------------------------------------------------------------------------------------
// word DO 2

// 24PMC COMUNE 24VDC USCITE PERICOLOSE_MANDRINO
#define CH_MORSA_12_HP_O          MO_2_17   //MO_2_17 EV Chiudi Morsa 12 in alta forza
#define CH_MORSA_13_HP_O          MO_2_18   //MO_2_18 EV Chiudi Morsa 13 in alta forza
#define CH_MORSA_14_HP_O          MO_2_19   //MO_2_19 EV Chiudi Morsa 14 in alta forza
#define CH_MORSA_15_HP_O          MO_2_20   //MO_2_20 EV Chiudi Morsa 15 in alta forza (OPT)

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define AP_MORSA_10_O             MO_2_21   //MO_2_21 EV Apri Morsa 10 in alta forza (OPT)
#define AP_MORSA_11_O             MO_2_22   //MO_2_22 EV Apri Morsa 11 in alta forza
#define AP_MORSA_12_O             MO_2_23   //MO_2_23 EV Apri Morsa 12 in alta forza
#define AP_MORSA_13_O             MO_2_24   //MO_2_24 EV Apri Morsa 13 in alta forza

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define AP_MORSA_14_O             MO_2_25   //MO_2_25 EV Apri Morsa 14 in alta forza
#define AP_MORSA_15_O             MO_2_26   //MO_2_26 EV Apri Morsa 15 in alta forza (OPT)
#define CH_MORSE_SX_O             MO_2_27   //MO_2_27 EV Chiusura morse a SX in bassa forza
#define CH_MORSE_DX_O             MO_2_28   //MO_2_28 EV Chiusura morse a DX in bassa forza

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define CH_RIP_ANT_O              MO_2_29   //MO_2_29 Chiusura Riparo Anteriore
#define AP_RIP_ANT_O              MO_2_30   //MO_2_30 Apertura Riparo Anteriore
#define VIS_RIP_SAL_O             MO_2_31   //MO_2_31 Sollevamento visiera riparo (chiusura visiera vertic.) 
#define VIS_RIP_DIS_O             MO_2_32   //MO_2_32 Discesa visiera riparo (apertura visiera vertic.) 

// --------------------------------------------------------------------------------------
// word DO 3

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define LUBRICA_1_O               MO_2_33   //MO_2_33 Ugello 1 di lubrificazione
#define LUBRICA_2_O               MO_2_34   //MO_2_34 Ugello 2 di lubrificazione
#define LUBRICA_3_O               MO_2_35   //MO_2_35 Ugello 3 di lubrificazione (OPZ: solo Comet S)
#define LUBRICA_4_O               MO_2_36   //MO_2_36 Ugello 4 di lubrificazione (OPZ: solo Comet S)

// 24USC COMUNE 24VDC USCITE FISSE
#define LED_SPINDLE_O             MO_2_37   //MO_2_37 Led spindle
#define LED_RIPARO_R_O            MO_2_38   //MO_2_38 Led riparo ( R )
#define LED_RIPARO_G_O            MO_2_39   //MO_2_39 Led riparo ( G )
#define LED_RIPARO_B_O            MO_2_40   //MO_2_40 Led riparo ( B )

// 24DC4 COMUNE 24VDC USCITE PERICOLOSE_ASSI
#define TRASC_MORSE_AX_X_INS_O    MO_2_41   //MO_2_41 Inserzione e soffiaggio Trascinatore Morse su asse X (non Comet R4i/S4i)
#define INS_RILMOR_AX_X_O         MO_2_42   //MO_2_42 Inserzione rilevatore morse su asse X (non Comet R4i/S4i)
#define TAVOLA_AVA_O              MO_2_43   //MO_2_43 EV Tavola avanti
#define TAVOLA_IND_O              MO_2_44   //MO_2_44 EV Tavola indietro

// 24DC4 COMUNE 24VDC USCITE PERICOLOSE_ASSI
#define AVA_TRASP_O               MO_2_45   //MO_2_45 Motore Nastro trasportatore (OPT)
#define ASPIRATORE_O              MO_2_46   //MO_2_46 Motore Aspiratore (OPT)
#define INS_BATT_PREC_O           MO_2_47   //MO_2_47 Inserzione,  Discesa battuta di precisione (OPT)
#define DIS_BATT_PREC_O           MO_2_48   //MO_2_48 Disinserzione,Salita battuta di precisione (OPT)

// --------------------------------------------------------------------------------------
// word DO 4

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define SBLOC_MORSA_11_O          MO_2_49   //MO_2_49 Zimmer di sbloccaggio morsa 11  (Comet R4i/S4i)
#define SBLOC_MORSA_12_O          MO_2_50   //MO_2_50 Zimmer di sbloccaggio morsa 12  (Comet R4i/S4i)
#define SBLOC_MORSA_13_O          MO_2_51   //MO_2_51 Zimmer di sbloccaggio morsa 13  (Comet R4i/S4i)
#define SBLOC_MORSA_14_O          MO_2_52   //MO_2_52 Zimmer di sbloccaggio morsa 14  (Comet R4i/S4i)

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define SBLOC_MORSA_10_O          MO_2_53   //MO_2_53 Zimmer di sbloccaggio morsa 10 (Comet R4i/S4i) (OPT)
#define SBLOC_MORSA_15_O          MO_2_54   //MO_2_54 Zimmer di sbloccaggio morsa 15 (Comet R4i/S4i) (OPT)
#define LUBRICA_SPEC_O            MO_2_55   //MO_2_55 Lubrica speciale / Vortex (OPT)
#define INGRASSAGGIO_AUTO_O       MO_2_56   //MO_2_56 Ingrassaggio automatico pattini-viti (OPT) 

// 24USC COMUNE 24VDC USCITE FISSE
#define START_MARPOSS_O           MO_2_57   //MO_2_57 Start lettura Marposs (OPT)
#define PRESSURIZ_MAND_O          MO_2_58   //MO_2_58 EV pressurizzazione mandrino (OPT)
#define FREE_MO_2_59              MO_2_59   //MO_2_59 Free
#define FREE_MO_2_60              MO_2_60   //MO_2_60 Free

// 24DC6 COMUNE 24VDC USCITE NON_PERICOLOSE (AUSILIARI)
#define ABIL_AP_RIP_ANT_O         MO_2_61   //MO_2_61 EV abilitazione apertura Riparo Anteriore (OPT)
#define FREE_MO_2_62              MO_2_62   //MO_2_62 Free
#define FREE_MO_2_63              MO_2_63   //MO_2_63 Free
#define FREE_MO_2_64              MO_2_64   //MO_2_64 Free

// --------------------------------------------------------------------------------------

#endif
