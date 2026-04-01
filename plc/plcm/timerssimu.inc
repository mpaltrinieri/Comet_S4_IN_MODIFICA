#ifndef TIMERSSIMU_INC_INCLUDED
#define TIMERSSIMU_INC_INCLUDED

/*----------------------------------------------------------------------------------------*/
/*                               TIMER per SIMULAZIONE									  */
/*----------------------------------------------------------------------------------------*/
extern void timersSimu_pon	(void);
extern void timersSimu		(void);
extern void tSD				(int nTimer, unsigned char ingr);

extern double tauCNC;
extern double tauPLC;


/*****************************************************************************************/
/******************* Inserire il numero massimo di temporizzatori ************************/
/****************** Se non sono dichiarati i sinonimi non cambia nulla *******************/
/*****************************************************************************************/
#define N_TIMERS_SIMU				101

extern unsigned int  maxTSimu    [N_TIMERS_SIMU]; //limite contatore
extern unsigned char ingrTSimu   [N_TIMERS_SIMU]; //ingresso
extern unsigned char RP_TSimu    [N_TIMERS_SIMU]; //segnale ritardato positivo
extern unsigned char RN_TSimu    [N_TIMERS_SIMU]; //segnale ritardato negativo


/*****************************************************************************************/
/********** Inserire da quì tutti i temporizzatori per simulazione con TIME-X ************/
/*****************************************************************************************/

#define TSD_0						0  // Lasciare libero
#define TSD_1 						1  // 
#define TSD_2 						2  // 
#define TSD_3 						3  // 
#define TSD_4 						4  // 
#define TSD_5 						5  // 
#define TSD_6 						6  // 
#define TSD_7 						7  // 
#define TSD_8 						8  // 
#define TSD_9 						9  // 
#define TSD_10						10 // 
#define TSD_11						11 // 
#define TSD_12						12 // 
#define TSD_13						13 // 
#define TSD_14						14 // 
#define TSD_15						15 // 
#define TSD_16						16 // 
#define TSD_17						17 // 
#define TSD_18						18 // 
#define TSD_19						19 // 
#define TSD_20						20 // 
#define TSD_21						21 // 
#define TSD_22						22 // 
#define TSD_23						23 // 
#define TSD_24						24 // 
#define TSD_25						25 // 
#define TSD_26						26 // 
#define TSD_27						27 // 
#define TSD_28						28 // 
#define TSD_29						29 // 
#define TSD_30						30 // 
#define TSD_31						31 // 
#define TSD_32						32 // 
#define TSD_33						33 // 
#define TSD_34						34 // 
#define TSD_35						35 // 
#define TSD_36						36 // 
#define TSD_37						37 // 
#define TSD_38						38 // 
#define TSD_39						39 // 
#define TSD_40						40 // 
#define TSD_41						41 // 
#define TSD_42						42 // 
#define TSD_43						43 // 
#define TSD_44						44 // 
#define TSD_45    					45 // 
#define TSD_46    					46 // 
#define TSD_47    					47 // 
#define TSD_48    					48 // 
#define TSD_49    					49 // 
#define TSD_50    					50 // 
#define TSD_51    					51 // 
#define TSD_52    					52 // 
#define TSD_53    					53 // 
#define TSD_54    					54 // 
#define TSD_55						55 //
#define TSD_56						56 //
#define TSD_57						57 //
#define TSD_58						58 //
#define TSD_59						59 //
#define TSD_60						60 //
#define TSD_61						61 //
#define TSD_62						62 //
#define TSD_63						63 //
#define TSD_64						64 //
#define TSD_65						65 //
#define TSD_66						66 //
#define TSD_67						67 //
#define TSD_68						68 //
#define TSD_69						69 //
#define TSD_70						70 //
#define TSD_71						71 //
#define TSD_72						72 //
#define TSD_73						73 //
#define TSD_74						74 //
#define TSD_75						75 //
#define TSD_76						76 //
#define TSD_77						77 //
#define TSD_78						78 //
#define TSD_79						79 //
#define TSD_80						80 //
#define TSD_81						81 //
#define TSD_82						82 //
#define TSD_83						83 //
#define TSD_84						84 //
#define TSD_85						85 //
#define TSD_86						86 //
#define TSD_87						87 //
#define TSD_88						88 //
#define TSD_89						89 //
#define TSD_90						90 //
#define TSD_91						91 //
#define TSD_92						92 //
#define TSD_93						93 //
#define TSD_94						94 //
#define TSD_95						95 //
#define TSD_96						96 //
#define TSD_97						97 //
#define TSD_98						98 //
#define TSD_99						99 //
#define TSD_100						100 //

#endif // TIMERSSIMU_INC_INCLUDED
