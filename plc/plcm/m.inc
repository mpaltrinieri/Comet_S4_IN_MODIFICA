#ifndef M_INC_INCLUDED
#define M_INC_INCLUDED
/*

        ---------------------------------------------
        TITOLO:         M.INC
        ---------------------------------------------
        MACCHINA:       EMMEGI PHANTOMATIC
        ---------------------------------------------
        RELEASE:        CT6 0.0
        ---------------------------------------------
        DATA:           30-08-2000
        ---------------------------------------------
        AUTORE:         Soffritti Riccardo
        ---------------------------------------------
        DESCRIZIONE:    Definizione aree "M"
        ---------------------------------------------

*/


#define MM_DRILL_OPZ_MACCHINA1  MM0.word
#define MM_DRILL_OPZ_MACCHINA2  MM1.word

#define MM_CNT_MM_INDEX			MM2.word //Test verginità Bridge per contatori

/**********************************************************************/
/************************ ATTENZIONE !!!! *****************************/
/******* Aree M : la 5 e la 6 sono utilizzate per ScheCmd2_init ********/
/**********************************************************************/
/**********************************************************************/

#define M_MULTI_SXDX       MM8.word     /* Definito in #523 (CONFMAC.CMT) Puntatore comandi eseguiti multiprocesso in corso */


#define POSMORS_7          F_MM10       /* Memoria posizione morsa 7  */
#define POSMORS_8          F_MM12       /* Memoria posizione morsa 8  */
#define POSMORS_9          F_MM14       /* Memoria posizione morsa 9  */
#define POSMORS_10         F_MM16       /* Memoria posizione morsa 10 */
#define POSMORS_11         F_MM18       /* Memoria posizione morsa 11 */
#define POSMORS_12         F_MM20       /* Memoria posizione morsa 12 */
#define POSMORS_13         F_MM22       /* Memoria posizione morsa 13 */
#define POSMORS_14         F_MM24       /* Memoria posizione morsa 14 */
#define POSMORS_15         F_MM28       /* Memoria posizione morsa 15 */
#define POSMORS_16         F_MM30       /* Memoria posizione morsa 16 */
#define POSMORS_17         F_MM32       /* Memoria posizione morsa 17 */
#define POSMORS_18         F_MM34       /* Memoria posizione morsa 18 */



// ----------------- Lascia libere : riparti da F_MM26 per CT6 ------------------



#define M_ORE_LAVORATE     F_MM40        /* numero ore lavorate senza aver ancor effettuato l'ingrassaggio automatico */
#define M_CICLI_INGR_NOK   F_MM42        /* numero di volte in cui l'ingrassaggio ha fallito */


#define WAIT               MM46.word    /* Tempo di attesa per INTP3 */

#define UTSCON             MM48.bit._00  /* Memoria utensile sconosciuto per spegnimento */
#define ROTAZ_ON           MM48.bit._01  /* Memoria rotazione on */

#define APPOVFED           MM49.ubyte.l  /* Appoggio commutatore override feed */
#define APPOVSPE           MM49.ubyte.h  /* Appoggio commutatore override speed */

#define APPOVRAP           MM50.ubyte.l  /* Appoggio commutatore override feed in rapido (movmenti in G0)*/


/* Descrizione dei simbolici :
TIMEOUTxx     : variabile di conteggio per ritardo
NC_TIMEOUTxx  : ritardo espresso in numero di tempi ciclo
P_TIMEOUTxx   : segnale pilota
RP_TIMEOUTxx  : ritardo positivo
*/

#define  TIMEOUT_01									   MM51.word
#define  NC_TIMEOUT_01										 100
#define  P_TIMEOUT_01									(BITOFF)
#define  RP_TIMEOUT_01					           MM230.bit._00

#define  TIMEOUT_02									   MM52.word
#define  NC_TIMEOUT_02										 100
#define  P_TIMEOUT_02									(BITOFF)
#define  RP_TIMEOUT_02					           MM230.bit._01

#define  TIMEOUT_03									   MM53.word
#define  NC_TIMEOUT_03										 100
#define  P_TIMEOUT_03									(BITOFF)
#define  RP_TIMEOUT_03					           MM230.bit._02 

#define  TIMEOUT_04									   MM54.word
#define  NC_TIMEOUT_04										 100
#define  P_TIMEOUT_04									(BITOFF)
#define  RP_TIMEOUT_04					           MM230.bit._03 

#define  TIMEOUT_05									   MM55.word
#define  NC_TIMEOUT_05										 100
#define  P_TIMEOUT_05									(BITOFF)
#define  RP_TIMEOUT_05					           MM230.bit._04

#define  TIMEOUT_06									   MM56.word
#define  NC_TIMEOUT_06 										 100
#define  P_TIMEOUT_06									(BITOFF)
#define  RP_TIMEOUT_06					           MM230.bit._05

#define  TIMEOUT_07									   MM57.word
#define  NC_TIMEOUT_07										 100
#define  P_TIMEOUT_07									(BITOFF)
#define  RP_TIMEOUT_07					           MM230.bit._06

#define  TIMEOUT_08									   MM58.word
#define  NC_TIMEOUT_08										 100
#define  P_TIMEOUT_08									(BITOFF)
#define  RP_TIMEOUT_08					           MM230.bit._07

#define  TIMEOUT_09									   MM59.word
#define  NC_TIMEOUT_09										 100
#define  P_TIMEOUT_09									(BITOFF)
#define  RP_TIMEOUT_09					           MM230.bit._08

#define  TIMEOUT_10									   MM60.word
#define  NC_TIMEOUT_10										 100
#define  P_TIMEOUT_10									(BITOFF)
#define  RP_TIMEOUT_10					           MM230.bit._09

#define  TIMEOUT_11									   MM61.word
#define  NC_TIMEOUT_11										 100
#define  P_TIMEOUT_11									(BITOFF)
#define  RP_TIMEOUT_11					           MM230.bit._10

#define  TIMEOUT_12									   MM62.word
#define  NC_TIMEOUT_12										 100
#define  P_TIMEOUT_12									(BITOFF)
#define  RP_TIMEOUT_12					           MM230.bit._11

#define  TIMEOUT_13									   MM63.word
#define  NC_TIMEOUT_13										 500
#define  P_TIMEOUT_13									(BITOFF)
#define  RP_TIMEOUT_13					           MM230.bit._12 

#define  TIMEOUT_14									   MM64.word
#define  NC_TIMEOUT_14										 500
#define  P_TIMEOUT_14									(BITOFF)
#define  RP_TIMEOUT_14					           MM230.bit._13 

#define  TIMEOUT_15									   MM65.word
#define  NC_TIMEOUT_15										 500
#define  P_TIMEOUT_15									(BITOFF)
#define  RP_TIMEOUT_15					           MM230.bit._14

#define  TIMEOUT_16									   MM66.word
#define  NC_TIMEOUT_16										 500
#define  P_TIMEOUT_16									(BITOFF)
#define  RP_TIMEOUT_16					           MM230.bit._15

#define  TIMEOUT_17									   MM67.word
#define  NC_TIMEOUT_17										 500
#define  P_TIMEOUT_17									(BITOFF)
#define  RP_TIMEOUT_17					           MM231.bit._00

#define  TIMEOUT_18									   MM68.word
#define  NC_TIMEOUT_18										 500
#define  P_TIMEOUT_18									(BITOFF)
#define  RP_TIMEOUT_18					           MM231.bit._01

#define  TIMEOUT_19									   MM69.word
#define  NC_TIMEOUT_19										 500
#define  P_TIMEOUT_19									(BITOFF)
#define  RP_TIMEOUT_19					           MM231.bit._02

#define  TIMEOUT_20									   MM70.word
#define  NC_TIMEOUT_20										 500
#define  P_TIMEOUT_20									(BITOFF)
#define  RP_TIMEOUT_20					           MM231.bit._03



#define  TIMEOUT_21									   MM71.word
#define  NC_TIMEOUT_21										 900
#define  P_TIMEOUT_21									(SBLOC_UT_O)
#define  RP_TIMEOUT_21					           MM231.bit._04

#define  TIMEOUT_22									   MM72.word
#define  NC_TIMEOUT_22										 375
#define  P_TIMEOUT_22									(!(SBLOC_UT_O))
#define  RP_TIMEOUT_22					           MM231.bit._05

#define  TIMEOUT_23									   MM73.word
#define  NC_TIMEOUT_23										 100
#define  P_TIMEOUT_23									(INVERTER_0_START_INV_FW && !INVERS_ROT_MAND)
#define  RP_TIMEOUT_23					           MM231.bit._06 

#define  TIMEOUT_24									   MM74.word
#define  NC_TIMEOUT_24										1000
#define  P_TIMEOUT_24						(FEEDHOLD_MAND && (INVERTER_0_START_INV_FW) && (RP_START_INV))
#define  RP_TIMEOUT_24					           MM231.bit._07 

#define  TIMEOUT_25									   MM75.word
#define  NC_TIMEOUT_25										 500
#define  P_TIMEOUT_25									(BITOFF)
#define  RP_TIMEOUT_25					           MM231.bit._08

#define  TIMEOUT_26									   MM76.word
#define  NC_TIMEOUT_26										 500
#define  P_TIMEOUT_26									(BITOFF)
#define  RP_TIMEOUT_26					           MM231.bit._09

#define  TIMEOUT_27									   MM77.word
#define  NC_TIMEOUT_27										 500
#define  P_TIMEOUT_27									(BITOFF)
#define  RP_TIMEOUT_27					           MM231.bit._10

#define  TIMEOUT_28									   MM78.word
#define  NC_TIMEOUT_28										 500
#define  P_TIMEOUT_28									(BITOFF)
#define  RP_TIMEOUT_28					           MM231.bit._11

#define  TIMEOUT_29									   MM79.word
#define  NC_TIMEOUT_29										 500
#define  P_TIMEOUT_29									(BITOFF)
#define  RP_TIMEOUT_29					           MM231.bit._12

#define  TIMEOUT_30									   MM80.word
#define  NC_TIMEOUT_30										 500
#define  P_TIMEOUT_30									(BITOFF)
#define  RP_TIMEOUT_30					           MM231.bit._13




#define  TIMEOUT_31									   MM81.word
#define  NC_TIMEOUT_31										 100
#define  P_TIMEOUT_31									(BITOFF)
#define  RP_TIMEOUT_31					           MM231.bit._14

#define  TIMEOUT_32									   MM82.word
#define  NC_TIMEOUT_32										 100
#define  P_TIMEOUT_32									(BITOFF)
#define  RP_TIMEOUT_32					           MM231.bit._15

#define  TIMEOUT_33									   MM83.word
#define  NC_TIMEOUT_33										  50
#define  P_TIMEOUT_33									(BITOFF)
#define  RP_TIMEOUT_33					           MM232.bit._00 

#define  TIMEOUT_34									   MM84.word
#define  NC_TIMEOUT_34										1000
#define  P_TIMEOUT_34									(BITOFF)
#define  RP_TIMEOUT_34					           MM232.bit._01 

#define  TIMEOUT_35									   MM85.word
#define  NC_TIMEOUT_35										 500
#define  P_TIMEOUT_35									(BITOFF)
#define  RP_TIMEOUT_35					           MM232.bit._02

#define  TIMEOUT_36									   MM86.word
#define  NC_TIMEOUT_36										 500
#define  P_TIMEOUT_36									(BITOFF)
#define  RP_TIMEOUT_36					           MM232.bit._03

#define  TIMEOUT_37									   MM87.word
#define  NC_TIMEOUT_37										 500
#define  P_TIMEOUT_37									(BITOFF)
#define  RP_TIMEOUT_37					           MM232.bit._04

#define  TIMEOUT_38									   MM88.word
#define  NC_TIMEOUT_38										 500
#define  P_TIMEOUT_38									(BITOFF)
#define  RP_TIMEOUT_38					           MM232.bit._05

#define  TIMEOUT_39									   MM89.word
#define  NC_TIMEOUT_39										 500
#define  P_TIMEOUT_39									(BITOFF)
#define  RP_TIMEOUT_39					           MM232.bit._06

#define  TIMEOUT_40									   MM90.word
#define  NC_TIMEOUT_40										 500
#define  P_TIMEOUT_40									(BITOFF)
#define  RP_TIMEOUT_40					           MM232.bit._07




/*-------------------- DEFINIZIONE VARIABILI PER FUNZIONAMENTO IN SIMULATO ----------------*/
#define TIMESBLOCCUT1      MM150.word
#define TIMESBLOCCUT2      MM151.word
#define TIMETAV1           MM152.word
#define TIMETAV2           MM153.word

#define TIMEBATTSX11       MM164.word
#define TIMEBATTSX12       MM165.word
#define TIMEBATTDX41       MM166.word
#define TIMEBATTDX42       MM167.word

#define TIMEVISBAS1        MM170.word
#define TIMEVISBAS2        MM171.word
#define TIMEVISALTA1       MM172.word
#define TIMEVISALTA2       MM173.word
#define TIMERIPANT1        MM178.word
#define TIMERIPANT2        MM179.word


#define TIMETRASCMORAXX1   MM189.word
#define TIMETRASCMORAXX2   MM190.word

#define TIMERILMORAXX1     MM195.word
#define TIMERILMORAXX2     MM196.word

#define TIMEMOVASSIXYZ	   MM201.word
#define TIMEHOLDJOG		   MM202.word
#define TIMEMARPOSS1       MM203.word

//----------------------------------------------------------------------------
// ATTENZIONE !!!!
// Aree M da 246 a 254 Occupate dal software ISAC
//-----------------------------------------------------------------------------
//#define	SEQVOL		MM246.word		/* Sequenz. Gestione volantini */
//#define	OVRAP		MM247.ubyte.l	/* Commutatore override rapido */
//#define	OVFED	    MM247.ubyte.h	/* Commutatore override feed */
//#define	OVSPE	    MM248.ubyte.l	/* Commutatore override speed */
//#define	AXEJOGM	    MM248.byte.h	/* Commutatore selezione assi */
//#define	firstax 	M249.word		/* Primo asse da visualizzare in quote */
//#define	FIRSTAX 	MM249.word		/* Primo asse da visualizzare in quote */ // Per visualizzazione Sin. II
// riservate per macchine particolari : v. tenona
//#define	spazjog		D_MM250		/* Spazio per JOG (micron) */
//#define	SPAZIOJOG	D_MM250		/* Spazio per JOG (micron) */ // Per visualizzazione Sin. II
//#define	veljog		F_MM252		/* Valore Feed in jog [mm/tau] */
//#define	VELJOG		F_MM252		/* Valore Feed in jog [mm/tau] */ // Per visualizzazione Sin. II
//#define	velaut		F_MM254		/* Valore Feed in autoamtico [mm/tau] */
//#define	VELAUT		F_MM254		/* Valore Feed in automatico [mm/tau] */ // Per visualizzazione Sin. II

// Aree M a float da F_MM300 sino a F_MM498 da lasciare libere per i 100 eventi industria 4.0
#define M_ORE_INIBIZ_EV_01 F_MM300
#define M_ORE_INIBIZ_EV_02 F_MM302

#endif // M_INC_INCLUDED
