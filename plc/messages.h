#ifndef MESSAGES_H_INCLUDED
#define MESSAGES_H_INCLUDED
//*******************************************************************
//
// TITOLO:      messages.mc
//
// DATA:        marted� 10 marzo 2026
//
// DESCRIZIONE: Generato automaticamente da inc2all.js
//
//*******************************************************************
//                                                                   
//  NOTE: comments in the .mc file must use both ; and //.           
//                                                                   
//  Status values are 32 bit values layed out as follows:            
//                                                                   
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1                     
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 
//  +---+-+-------------------------+-------------------------------+
//  |Sev|C|       Facility          |               Code            |
//  +---+-+-------------------------+-------------------------------+
//                                                                   
//  where                                                            
//                                                                   
//      Sev - is the severity code                                   
//                                                                   
//          00 - Success                                             
//          01 - Informational                                       
//          10 - Warning                                             
//          11 - Error                                               
//                                                                   
//      C - is the Customer code flag                                
//                                                                   
//      Facility - is the facility code                              
//                                                                   
//      Code - is the facility's status code                         
//                                                                   
//*******************************************************************
                                                                     
//-- Allarmi macchina --------------------------------------------------------
//----------------------------------------------------------------------------
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_PLC                     0x120


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: ALARM_FIRST_AL
//
// MessageText:
//
//  Primo allarme da non usare
//
#define ALARM_FIRST_AL                   ((DWORD)0xC1204C90L)

//
// MessageId: DRIVE_X_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE X - Anomalia azionamento asse X
//
#define DRIVE_X_NOK_AL                   ((DWORD)0xC1204C91L)

//
// MessageId: DRIVE_Y_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE Y - Anomalia azionamento asse Y
//
#define DRIVE_Y_NOK_AL                   ((DWORD)0xC1204C92L)

//
// MessageId: DRIVE_Z_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE Z - Anomalia azionamento asse Z
//
#define DRIVE_Z_NOK_AL                   ((DWORD)0xC1204C93L)

//
// MessageId: DRIVE_A_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE B - Anomalia azionamento asse B
//
#define DRIVE_A_NOK_AL                   ((DWORD)0xC1204C94L)

//
// MessageId: DRIVE_C_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE C - Anomalia azionamento asse C
//
#define DRIVE_C_NOK_AL                   ((DWORD)0xC1204C95L)

//
// MessageId: DRIVE_W_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE W - Anomalia azionamento asse W
//
#define DRIVE_W_NOK_AL                   ((DWORD)0xC1204C96L)

//
// MessageId: DRIVE_ALIM_AL
//
// MessageText:
//
//  ALLARME GENERALE - Assenza alimentazione agli azionamenti degli assi
//
#define DRIVE_ALIM_AL                    ((DWORD)0xC1204C99L)

//
// MessageId: CNT_ERROR_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Allarme lettura scrittura contatori
//
#define CNT_ERROR_AL                     ((DWORD)0xC1204C9FL)

//
// MessageId: DRIVE_M10_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA M10 - Anomalia azionamento asse Morsa M10
//
#define DRIVE_M10_NOK_AL                 ((DWORD)0xC1204CA3L)

//
// MessageId: DRIVE_M11_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA M11 - Anomalia azionamento asse Morsa M11
//
#define DRIVE_M11_NOK_AL                 ((DWORD)0xC1204CA4L)

//
// MessageId: DRIVE_M12_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA M12 - Anomalia azionamento asse Morsa M12
//
#define DRIVE_M12_NOK_AL                 ((DWORD)0xC1204CA5L)

//
// MessageId: DRIVE_M13_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA M13 - Anomalia azionamento asse Morsa M13
//
#define DRIVE_M13_NOK_AL                 ((DWORD)0xC1204CA6L)

//
// MessageId: DRIVE_M14_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA M14 - Anomalia azionamento asse Morsa M14
//
#define DRIVE_M14_NOK_AL                 ((DWORD)0xC1204CA7L)

//
// MessageId: DRIVE_M15_NOK_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA M15 - Anomalia azionamento asse Morsa M15
//
#define DRIVE_M15_NOK_AL                 ((DWORD)0xC1204CA8L)

//
// MessageId: ALIM_NOPRES_AL
//
// MessageText:
//
//  ALLARME GENERALE - Alimentazioni non presenti
//
#define ALIM_NOPRES_AL                   ((DWORD)0xC1204CB0L)

//
// MessageId: EMERGENZA_AL
//
// MessageText:
//
//  ALLARME GENERALE - Emergenza premuta
//
#define EMERGENZA_AL                     ((DWORD)0xC1204CB1L)

//
// MessageId: AUX_NOINS_AL
//
// MessageText:
//
//  ALLARME GENERALE - Ausiliari non inseriti
//
#define AUX_NOINS_AL                     ((DWORD)0xC1204CB2L)

//
// MessageId: ARIA_NOPRES_AL
//
// MessageText:
//
//  ALLARME GENERALE - Pressione aria insufficiente
//
#define ARIA_NOPRES_AL                   ((DWORD)0xC1204CB3L)

//
// MessageId: TEMP_NOK_AL
//
// MessageText:
//
//  ALLARME GENERALE - Temperatura armadio non ok
//
#define TEMP_NOK_AL                      ((DWORD)0xC1204CB4L)

//
// MessageId: TERMICI_NOK_AL
//
// MessageText:
//
//  ALLARME GENERALE - Termici scattati
//
#define TERMICI_NOK_AL                   ((DWORD)0xC1204CB5L)

//
// MessageId: TERM_TRASP_AL
//
// MessageText:
//
//  ALLARME TRASP.TRUCIOLI - Termico trasportatore scattato
//
#define TERM_TRASP_AL                    ((DWORD)0xC1204CB7L)

//
// MessageId: TERM_ASP_AL
//
// MessageText:
//
//  ALLARME ASPIRATORE - Termico aspiratore scattato
//
#define TERM_ASP_AL                      ((DWORD)0xC1204CB8L)

//
// MessageId: CNC_AL
//
// MessageText:
//
//  ALLARME GENERALE - CNC in allarme
//
#define CNC_AL                           ((DWORD)0xC1204CBAL)

//
// MessageId: CNC1_AL
//
// MessageText:
//
//  ALLARME GENERALE - CNC1 in allarme
//
#define CNC1_AL                          ((DWORD)0xC1204CBBL)

//
// MessageId: CNC2_AL
//
// MessageText:
//
//  ALLARME GENERALE - CNC2 in allarme
//
#define CNC2_AL                          ((DWORD)0xC1204CBCL)

//
// MessageId: COND_ASINCRO_CNC_MAN_AL
//
// MessageText:
//
//  ALLARME GENERALE - CNC0, CNC1, CNC2 non tutti in manuale
//
#define COND_ASINCRO_CNC_MAN_AL          ((DWORD)0xC1204CBEL)

//
// MessageId: COND_ASINCRO_CNC_AUT_AL
//
// MessageText:
//
//  ALLARME GENERALE - CNC0, CNC1, CNC2 non tutti in automatico
//
#define COND_ASINCRO_CNC_AUT_AL          ((DWORD)0xC1204CBFL)

//
// MessageId: DRIVEM_NOK_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Anomalia inverter mandrino
//
#define DRIVEM_NOK_AL                    ((DWORD)0xC1204CC0L)

//
// MessageId: DRIVEM_PREA_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Inverter mandrino in sovraccarico
//
#define DRIVEM_PREA_AL                   ((DWORD)0xC1204CC1L)

//
// MessageId: MANDRINO_FERMO_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Mandrino non in rotazione
//
#define MANDRINO_FERMO_AL                ((DWORD)0xC1204CC2L)

//
// MessageId: MANDRINO_HOLD_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Velocita' non a regime
//
#define MANDRINO_HOLD_AL                 ((DWORD)0xC1204CC3L)

//
// MessageId: UT_NOSBL_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Time out sbloccaggio utensile
//
#define UT_NOSBL_AL                      ((DWORD)0xC1204CC4L)

//
// MessageId: UT_NOBLO_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Time out bloccaggio utensile
//
#define UT_NOBLO_AL                      ((DWORD)0xC1204CC5L)

//
// MessageId: UT_DISFC_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Disfunzione F.C bloccaggio utensile
//
#define UT_DISFC_AL                      ((DWORD)0xC1204CC6L)

//
// MessageId: UT_NOAGG_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Utensile non agganciato correttamente
//
#define UT_NOAGG_AL                      ((DWORD)0xC1204CC7L)

//
// MessageId: UTSCON_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Utensile sconosciuto su mandrino
//
#define UTSCON_AL                        ((DWORD)0xC1204CC8L)

//
// MessageId: TERM_FRIGO_NOK_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Termico Centralina di Raffreddamento Mandrino scattato
//
#define TERM_FRIGO_NOK_AL                ((DWORD)0xC1204CC9L)

//
// MessageId: FLUSSOSTATO_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Flussostato Centralina di Raffreddamento Mandrino in allarme
//
#define FLUSSOSTATO_AL                   ((DWORD)0xC1204CCAL)

//
// MessageId: MANDRINO_VIBR_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Vibrazioni eccessive sul mandrino
//
#define MANDRINO_VIBR_AL                 ((DWORD)0xC1204CCEL)

//
// MessageId: MANDRINO_TEMP_AL
//
// MessageText:
//
//  ALLARME MANDRINO - Temperatura eccessiva sul mandrino
//
#define MANDRINO_TEMP_AL                 ((DWORD)0xC1204CCFL)

//
// MessageId: EXC_POS_X_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse X in Extracorsa Positivo
//
#define EXC_POS_X_AL                     ((DWORD)0xC1204CD0L)

//
// MessageId: EXC_NEG_X_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse X in Extracorsa Negativo
//
#define EXC_NEG_X_AL                     ((DWORD)0xC1204CD1L)

//
// MessageId: EXC_POS_Y_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse Y in Extracorsa Positivo
//
#define EXC_POS_Y_AL                     ((DWORD)0xC1204CD2L)

//
// MessageId: EXC_NEG_Y_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse Y in Extracorsa Negativo
//
#define EXC_NEG_Y_AL                     ((DWORD)0xC1204CD3L)

//
// MessageId: EXC_POS_Z_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse Z in Extracorsa Positivo
//
#define EXC_POS_Z_AL                     ((DWORD)0xC1204CD4L)

//
// MessageId: EXC_NEG_Z_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse Z in Extracorsa Negativo
//
#define EXC_NEG_Z_AL                     ((DWORD)0xC1204CD5L)

//
// MessageId: EXC_POS_A_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse A in Extracorsa Positivo
//
#define EXC_POS_A_AL                     ((DWORD)0xC1204CD6L)

//
// MessageId: EXC_NEG_A_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse A in Extracorsa Negativo
//
#define EXC_NEG_A_AL                     ((DWORD)0xC1204CD7L)

//
// MessageId: EXC_POS_C_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse C in Extracorsa Positivo
//
#define EXC_POS_C_AL                     ((DWORD)0xC1204CD8L)

//
// MessageId: EXC_NEG_C_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse C in Extracorsa Negativo
//
#define EXC_NEG_C_AL                     ((DWORD)0xC1204CD9L)

//
// MessageId: EXC_POS_P_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse P in Extracorsa Positivo
//
#define EXC_POS_P_AL                     ((DWORD)0xC1204CDAL)

//
// MessageId: EXC_NEG_P_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse P in Extracorsa Negativo
//
#define EXC_NEG_P_AL                     ((DWORD)0xC1204CDBL)

//
// MessageId: EXC_POS_H_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse H in Extracorsa Positivo
//
#define EXC_POS_H_AL                     ((DWORD)0xC1204CDCL)

//
// MessageId: EXC_NEG_H_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse H in Extracorsa Negativo
//
#define EXC_NEG_H_AL                     ((DWORD)0xC1204CDDL)

//
// MessageId: EXC_POS_W_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse W in Extracorsa Positivo
//
#define EXC_POS_W_AL                     ((DWORD)0xC1204CDEL)

//
// MessageId: EXC_NEG_W_AL
//
// MessageText:
//
//  ALLARMI ASSI - Asse W in Extracorsa Negativo
//
#define EXC_NEG_W_AL                     ((DWORD)0xC1204CDFL)

//
// MessageId: UT1_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 1
//
#define UT1_PRES_AL                      ((DWORD)0xC1204CE0L)

//
// MessageId: UT1_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 1
//
#define UT1_NOPRES_AL                    ((DWORD)0xC1204CE1L)

//
// MessageId: UT2_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 2
//
#define UT2_PRES_AL                      ((DWORD)0xC1204CE2L)

//
// MessageId: UT2_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 2
//
#define UT2_NOPRES_AL                    ((DWORD)0xC1204CE3L)

//
// MessageId: UT3_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 3
//
#define UT3_PRES_AL                      ((DWORD)0xC1204CE4L)

//
// MessageId: UT3_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 3
//
#define UT3_NOPRES_AL                    ((DWORD)0xC1204CE5L)

//
// MessageId: UT4_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 4
//
#define UT4_PRES_AL                      ((DWORD)0xC1204CE6L)

//
// MessageId: UT4_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 4
//
#define UT4_NOPRES_AL                    ((DWORD)0xC1204CE7L)

//
// MessageId: UT5_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 5
//
#define UT5_PRES_AL                      ((DWORD)0xC1204CE8L)

//
// MessageId: UT5_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 5
//
#define UT5_NOPRES_AL                    ((DWORD)0xC1204CE9L)

//
// MessageId: UT6_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 6
//
#define UT6_PRES_AL                      ((DWORD)0xC1204CEAL)

//
// MessageId: UT6_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 6
//
#define UT6_NOPRES_AL                    ((DWORD)0xC1204CEBL)

//
// MessageId: UT7_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 7
//
#define UT7_PRES_AL                      ((DWORD)0xC1204CECL)

//
// MessageId: UT7_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 7
//
#define UT7_NOPRES_AL                    ((DWORD)0xC1204CEDL)

//
// MessageId: UT8_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 8
//
#define UT8_PRES_AL                      ((DWORD)0xC1204CEEL)

//
// MessageId: UT8_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 8
//
#define UT8_NOPRES_AL                    ((DWORD)0xC1204CEFL)

//
// MessageId: UT9_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 9
//
#define UT9_PRES_AL                      ((DWORD)0xC1204CF0L)

//
// MessageId: UT9_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 9
//
#define UT9_NOPRES_AL                    ((DWORD)0xC1204CF1L)

//
// MessageId: UT10_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 10
//
#define UT10_PRES_AL                     ((DWORD)0xC1204CF2L)

//
// MessageId: UT10_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 10
//
#define UT10_NOPRES_AL                   ((DWORD)0xC1204CF3L)

//
// MessageId: UT11_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 11
//
#define UT11_PRES_AL                     ((DWORD)0xC1204CF4L)

//
// MessageId: UT11_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 11
//
#define UT11_NOPRES_AL                   ((DWORD)0xC1204CF5L)

//
// MessageId: UT12_PRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 12
//
#define UT12_PRES_AL                     ((DWORD)0xC1204CF6L)

//
// MessageId: UT12_NOPRES_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 12
//
#define UT12_NOPRES_AL                   ((DWORD)0xC1204CF7L)

//
// MessageId: GANCIO_MAG_NODIS_AL
//
// MessageText:
//
//  ALLARME MAGAZZINO UTENSILI - Gancio magazzino utensile non disinserito
//
#define GANCIO_MAG_NODIS_AL              ((DWORD)0xC1204CF8L)

//
// MessageId: MANDR_COLL_MAG_AL
//
// MessageText:
//
//  ALLARME MAGAZZINO UTENSILI - Ciclo iniziato con mandrino in potenziale collisione con magazzino
//
#define MANDR_COLL_MAG_AL                ((DWORD)0xC1204CF9L)

//
// MessageId: GANCIO_MAG_NOFUOING_AL
//
// MessageText:
//
//  ALLARME MAGAZZINO UTENSILI - Gancio magazzino utensile non fuori ingombro
//
#define GANCIO_MAG_NOFUOING_AL           ((DWORD)0xC1204CFAL)

//
// MessageId: BAS_PRESSIONE_AL
//
// MessageText:
//
//  ALLARME MORSE - Alta Pressione attiva senza comando
//
#define BAS_PRESSIONE_AL                 ((DWORD)0xC1204CFBL)

//
// MessageId: COLL_RIPARI_Y_A_AL
//
// MessageText:
//
//  ALLARMI ASSI - Potenziale collisione fra utensile e ripari anteriori
//
#define COLL_RIPARI_Y_A_AL               ((DWORD)0xC1204CFCL)

//
// MessageId: POS_MORSA_10_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 10 non in posizione corretta
//
#define POS_MORSA_10_AL                  ((DWORD)0xC1204D03L)

//
// MessageId: POS_MORSA_11_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 11 non in posizione corretta
//
#define POS_MORSA_11_AL                  ((DWORD)0xC1204D04L)

//
// MessageId: POS_MORSA_12_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 12 non in posizione corretta
//
#define POS_MORSA_12_AL                  ((DWORD)0xC1204D05L)

//
// MessageId: POS_MORSA_13_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 13 non in posizione corretta
//
#define POS_MORSA_13_AL                  ((DWORD)0xC1204D06L)

//
// MessageId: POS_MORSA_14_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 14 non in posizione corretta
//
#define POS_MORSA_14_AL                  ((DWORD)0xC1204D07L)

//
// MessageId: POS_MORSA_15_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 15 non in posizione corretta
//
#define POS_MORSA_15_AL                  ((DWORD)0xC1204D08L)

//
// MessageId: CONT_MORSE_AL
//
// MessageText:
//
//  ALLARME MORSE - Conteggio morse errato
//
#define CONT_MORSE_AL                    ((DWORD)0xC1204D0CL)

//
// MessageId: POSMORSE_DA_PC_AL
//
// MessageText:
//
//  ALLARME MORSE - Errore pos. Morse da PC: valori fuori range
//
#define POSMORSE_DA_PC_AL                ((DWORD)0xC1204D0DL)

//
// MessageId: MOD_SIC_ALL_01_AL
//
// MessageText:
//
//  PREDISPOSTO: ALLARME MODULO SICUREZZA - Modulo di sicurezza in anomalia, controlla la word A2843
//
#define MOD_SIC_ALL_01_AL                ((DWORD)0xC1204D0FL)

//
// MessageId: ALIM_MM_NOT_OK_AL
//
// MessageText:
//
//  ALLARME MORSE - Alimentatore morse motorizzate in zona non OK
//
#define ALIM_MM_NOT_OK_AL                ((DWORD)0xC1204D18L)

//
// MessageId: INS_BATT_PREC_AL
//
// MessageText:
//
//  ALLARME BATTUTA DI PRECISIONE - Battuta non inserita
//
#define INS_BATT_PREC_AL                 ((DWORD)0xC1204D1AL)

//
// MessageId: DIS_BATT_PREC_AL
//
// MessageText:
//
//  ALLARME BATTUTA DI PRECISIONE - Battuta non disinserita
//
#define DIS_BATT_PREC_AL                 ((DWORD)0xC1204D1BL)

//
// MessageId: BATT_PREC_QUOTA0_AL
//
// MessageText:
//
//  ALLARME BATTUTA DI PRECISIONE - Errore posizione a riposo della battuta
//
#define BATT_PREC_QUOTA0_AL              ((DWORD)0xC1204D1CL)

//
// MessageId: INDICE_TAST_AL
//
// MessageText:
//
//  ALLARME BATTUTA DI PRECISIONE - Errore indice di tastatura
//
#define INDICE_TAST_AL                   ((DWORD)0xC1204D1DL)

//
// MessageId: PEZZO_NON_TROV_AL
//
// MessageText:
//
//  ALLARME BATTUTA DI PRECISIONE - Pezzo non trovato
//
#define PEZZO_NON_TROV_AL                ((DWORD)0xC1204D1EL)

//
// MessageId: POSIZIONE_PEZZO_AL
//
// MessageText:
//
//  ALLARME DI POSIZIONAMENTO - Pezzo appoggiato male alla battuta di riferimento
//
#define POSIZIONE_PEZZO_AL               ((DWORD)0xC1204D1FL)

//
// MessageId: BATT_DX4_NOPOS_X4R_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta DX4 non in posizione X4R
//
#define BATT_DX4_NOPOS_X4R_AL            ((DWORD)0xC1204D2AL)

//
// MessageId: BATT_DX4_DISFC_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Disfunzione Finecorsa Battuta DX4
//
#define BATT_DX4_DISFC_AL                ((DWORD)0xC1204D2BL)

//
// MessageId: BATT_SX1_NOPOS_X1L_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta SX1 non in posizione X1L
//
#define BATT_SX1_NOPOS_X1L_AL            ((DWORD)0xC1204D2CL)

//
// MessageId: BATT_DX4_NOPOS_X3R_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta DX4 non in posizione X3R
//
#define BATT_DX4_NOPOS_X3R_AL            ((DWORD)0xC1204D2DL)

//
// MessageId: BATT_DX4_NOPOS_X2R_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta DX4 non in posizione X2R
//
#define BATT_DX4_NOPOS_X2R_AL            ((DWORD)0xC1204D2EL)

//
// MessageId: BATT_DX4_NOPOS_X1R_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta DX4 non in posizione X1R
//
#define BATT_DX4_NOPOS_X1R_AL            ((DWORD)0xC1204D2FL)

//
// MessageId: BATTUTA_SX1_ALT_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta SX1 non alta
//
#define BATTUTA_SX1_ALT_AL               ((DWORD)0xC1204D30L)

//
// MessageId: BATTUTA_SX1_BAS_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta SX1 non bassa
//
#define BATTUTA_SX1_BAS_AL               ((DWORD)0xC1204D31L)

//
// MessageId: BATTUTA_DX4_ALT_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta DX4 non alta
//
#define BATTUTA_DX4_ALT_AL               ((DWORD)0xC1204D36L)

//
// MessageId: BATTUTA_DX4_BAS_AL
//
// MessageText:
//
//  ALLARME BATTUTE - Battuta DX4 non bassa
//
#define BATTUTA_DX4_BAS_AL               ((DWORD)0xC1204D37L)

//
// MessageId: TAVOLA_AVA_A_AL
//
// MessageText:
//
//  ALLARME TAVOLA - Tavola non avanti : controlla il sensore
//
#define TAVOLA_AVA_A_AL                  ((DWORD)0xC1204D40L)

//
// MessageId: TAVOLA_AVA_B_AL
//
// MessageText:
//
//  ALLARME TAVOLA - Tavola non avanti : controlla la EV
//
#define TAVOLA_AVA_B_AL                  ((DWORD)0xC1204D41L)

//
// MessageId: TAVOLA_IND_A_AL
//
// MessageText:
//
//  ALLARME TAVOLA - Tavola non indietro : controlla il sensore
//
#define TAVOLA_IND_A_AL                  ((DWORD)0xC1204D42L)

//
// MessageId: TAVOLA_IND_B_AL
//
// MessageText:
//
//  ALLARME TAVOLA - Tavola non indietro : controlla la EV
//
#define TAVOLA_IND_B_AL                  ((DWORD)0xC1204D43L)

//
// MessageId: TAVOLA_DISFC_AL
//
// MessageText:
//
//  ALLARME TAVOLA - Disfunzione Finecorsa Tavola
//
#define TAVOLA_DISFC_AL                  ((DWORD)0xC1204D44L)

//
// MessageId: LIV_LUB_NOT_BASSO_AL
//
// MessageText:
//
//  ALLARME LUBRICA - Livello lubrica normale basso
//
#define LIV_LUB_NOT_BASSO_AL             ((DWORD)0xC1204D56L)

//
// MessageId: LIV_LUB_NOT_ALTO_AL
//
// MessageText:
//
//  ALLARME LUBRICA - Livello lubrica normale alto
//
#define LIV_LUB_NOT_ALTO_AL              ((DWORD)0xC1204D57L)

//
// MessageId: MARPOSS_TOUCH_AL
//
// MessageText:
//
//  ALLARME TASTATORE MARPOSS - Tastatore già in battuta ad inizio tastata
//
#define MARPOSS_TOUCH_AL                 ((DWORD)0xC1204D58L)

//
// MessageId: MARPOSS_NOTOUCH_AL
//
// MessageText:
//
//  ALLARME TASTATORE MARPOSS - Pezzo non rilevato da tastatore
//
#define MARPOSS_NOTOUCH_AL               ((DWORD)0xC1204D59L)

//
// MessageId: MARPOSS_INDEX_AL
//
// MessageText:
//
//  ALLARME TASTATORE MARPOSS - Errore indice tastatore
//
#define MARPOSS_INDEX_AL                 ((DWORD)0xC1204D5AL)

//
// MessageId: MARPOSS_ERROR_AL
//
// MessageText:
//
//  ALLARME TASTATORE MARPOSS - Tastatore Marposs in errore
//
#define MARPOSS_ERROR_AL                 ((DWORD)0xC1204D5BL)

//
// MessageId: MARPOSS_LOWBA_AL
//
// MessageText:
//
//  ALLARME TASTATORE MARPOSS - Batteria scarica tastatore Marposs
//
#define MARPOSS_LOWBA_AL                 ((DWORD)0xC1204D5CL)

//
// MessageId: MARPOSS_ST_TOUCH_AL
//
// MessageText:
//
//  ALLARME TASTATORE MARPOSS - Tastatore ancor in battuta dopo fine tastata
//
#define MARPOSS_ST_TOUCH_AL              ((DWORD)0xC1204D5DL)

//
// MessageId: CORREZ_TOO_BIG_AL
//
// MessageText:
//
//  ALLARME TASTATORE MARPOSS - Correzioni troppo grandi: verificare il tastatore
//
#define CORREZ_TOO_BIG_AL                ((DWORD)0xC1204D5EL)

//
// MessageId: INGRASS_LIV_AL
//
// MessageText:
//
//  ALLARME INGRASSAGGIO GUIDE - Livello grasso basso
//
#define INGRASS_LIV_AL                   ((DWORD)0xC1204D64L)

//
// MessageId: INGRASS_EV_AL
//
// MessageText:
//
//  ALLARME INGRASSAGGIO GUIDE - Anomalia pompa/elettrovalvola
//
#define INGRASS_EV_AL                    ((DWORD)0xC1204D65L)

//
// MessageId: INGRASS_ORE_AL
//
// MessageText:
//
//  ALLARME INGRASSAGGIO GUIDE - Mancata esecuzione per troppe ore lavorative
//
#define INGRASS_ORE_AL                   ((DWORD)0xC1204D66L)

//
// MessageId: SINGOL_POMP_AL
//
// MessageText:
//
//  ALLARME INGRASSAGGIO GUIDE - Mancata commutazione sensore sulla singola pompata
//
#define SINGOL_POMP_AL                   ((DWORD)0xC1204D67L)

//
// MessageId: PATHCONF_TXT_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - File di configurazione utensili PATH_CONF.TXT non trovato
//
#define PATHCONF_TXT_AL                  ((DWORD)0xC1204D70L)

//
// MessageId: CONFIG_PAR_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Errore in apertura / lettura file CONFIG.PAR
//
#define CONFIG_PAR_AL                    ((DWORD)0xC1204D71L)

//
// MessageId: TOOLS_TXT_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Errore in apertura / lettura file TOOLS.TXT
//
#define TOOLS_TXT_AL                     ((DWORD)0xC1204D72L)

//
// MessageId: HEADS_TXT_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Errore in apertura / lettura file HEADS.TXT
//
#define HEADS_TXT_AL                     ((DWORD)0xC1204D73L)

//
// MessageId: CHIAMATA_UT_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Utensile non trovato, errato o nullo
//
#define CHIAMATA_UT_AL                   ((DWORD)0xC1204D74L)

//
// MessageId: PARAM_PAR_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Errore in apertura / lettura file PARAM.PAR
//
#define PARAM_PAR_AL                     ((DWORD)0xC1204D75L)

//
// MessageId: HEARTBEAT_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Errore di comunicazione con SW Hardlock
//
#define HEARTBEAT_AL                     ((DWORD)0xC1204D76L)

//
// MessageId: VARIABLE_OPEN_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Apertura File Errata : Variable.txt
//
#define VARIABLE_OPEN_AL                 ((DWORD)0xC1204D77L)

//
// MessageId: VARIABLE_CLOSE_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Chiusura File Errata : Variable.txt
//
#define VARIABLE_CLOSE_AL                ((DWORD)0xC1204D78L)

//
// MessageId: DRIVE_MISSING_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Allarme manca driver
//
#define DRIVE_MISSING_AL                 ((DWORD)0xC1204D79L)

//
// MessageId: CONF_NOK_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Configurazione macchina sbagliata
//
#define CONF_NOK_AL                      ((DWORD)0xC1204D7AL)

//
// MessageId: VALORE_ERRATO_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Valore oltre soglie in controlli Routine ISO CNC
//
#define VALORE_ERRATO_AL                 ((DWORD)0xC1204D7BL)

//
// MessageId: TAB_UT_NON_CAR_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Tabella Utensili non caricata (eseguire M209)
//
#define TAB_UT_NON_CAR_AL                ((DWORD)0xC1204D7CL)

//
// MessageId: MOV_XYZ_AL
//
// MessageText:
//
//  ALLARME SOFTWARE - Allarme movimento assi X - Y - Z
//
#define MOV_XYZ_AL                       ((DWORD)0xC1204D7DL)

//
// MessageId: MORSA_10_NONPOS_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 10 non in posizione
//
#define MORSA_10_NONPOS_AL               ((DWORD)0xC1204D83L)

//
// MessageId: MORSA_11_NONPOS_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 11 non in posizione
//
#define MORSA_11_NONPOS_AL               ((DWORD)0xC1204D84L)

//
// MessageId: MORSA_12_NONPOS_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 12 non in posizione
//
#define MORSA_12_NONPOS_AL               ((DWORD)0xC1204D85L)

//
// MessageId: MORSA_13_NONPOS_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 13 non in posizione
//
#define MORSA_13_NONPOS_AL               ((DWORD)0xC1204D86L)

//
// MessageId: MORSA_14_NONPOS_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 14 non in posizione
//
#define MORSA_14_NONPOS_AL               ((DWORD)0xC1204D87L)

//
// MessageId: MORSA_15_NONPOS_AL
//
// MessageText:
//
//  ALLARME MORSE - Morsa 15 non in posizione
//
#define MORSA_15_NONPOS_AL               ((DWORD)0xC1204D88L)

//
// MessageId: MORSA_MICRO_X_PERSO_AL
//
// MessageText:
//
//  ALLARME MORSE - Micro morsa perso durante posizionamento
//
#define MORSA_MICRO_X_PERSO_AL           ((DWORD)0xC1204D8CL)

//
// MessageId: MORSA_MICRO_X_NON_TROVATO_AL
//
// MessageText:
//
//  ALLARME MORSE - Micro morsa Asse X non trovato in controllo posizione
//
#define MORSA_MICRO_X_NON_TROVATO_AL     ((DWORD)0xC1204D8DL)

//
// MessageId: LOAD_ISO_AL
//
// MessageText:
//
//  ALLARME GENERALE - Errore caricamento ISOMG in memoria
//
#define LOAD_ISO_AL                      ((DWORD)0xC1204D90L)

//
// MessageId: LOAD_ISO_TIMEOUT_AL
//
// MessageText:
//
//  ALLARME GENERALE - Timeout caricamento ISOMG in memoria
//
#define LOAD_ISO_TIMEOUT_AL              ((DWORD)0xC1204D91L)

//
// MessageId: COMUNIC_CAN_AL
//
// MessageText:
//
//  ALLARME CAN OPEN - Comunicazione CanOpen in anomalia
//
#define COMUNIC_CAN_AL                   ((DWORD)0xC1204D94L)

//
// MessageId: TUN_RIP_LAT_SX_CH_AL
//
// MessageText:
//
//  ALLARME RIPARI - Riparo laterale o tunnel SX non chiuso
//
#define TUN_RIP_LAT_SX_CH_AL             ((DWORD)0xC1204D9EL)

//
// MessageId: TUN_RIP_LAT_DX_CH_AL
//
// MessageText:
//
//  ALLARME RIPARI - Riparo laterale o tunnel DX non chiuso
//
#define TUN_RIP_LAT_DX_CH_AL             ((DWORD)0xC1204D9FL)

//
// MessageId: RIPARO_CH_A_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Riparo anteriore non chiuso : controlla il sensore
//
#define RIPARO_CH_A_AL                   ((DWORD)0xC1204DA0L)

//
// MessageId: RIPARO_CH_B_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Riparo anteriore non chiuso : controlla la EV
//
#define RIPARO_CH_B_AL                   ((DWORD)0xC1204DA1L)

//
// MessageId: RIPARO_AP_A_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Riparo anteriore non aperto : controlla il sensore
//
#define RIPARO_AP_A_AL                   ((DWORD)0xC1204DA2L)

//
// MessageId: RIPARO_AP_B_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Riparo anteriore non aperto : controlla la EV
//
#define RIPARO_AP_B_AL                   ((DWORD)0xC1204DA3L)

//
// MessageId: RIPARO_DISFC_AL
//
// MessageText:
//
//  ALLARME RIPARI - Disfunzione finecorsa riparo anteriore
//
#define RIPARO_DISFC_AL                  ((DWORD)0xC1204DA4L)

//
// MessageId: RIPARO_POST_SX_CH_AL
//
// MessageText:
//
//  ALLARME RIPARI - Riparo posteriore SX non Chiuso
//
#define RIPARO_POST_SX_CH_AL             ((DWORD)0xC1204DAAL)

//
// MessageId: RIPARO_POST_DX_CH_AL
//
// MessageText:
//
//  ALLARME RIPARI - Riparo posteriore DX non Chiuso
//
#define RIPARO_POST_DX_CH_AL             ((DWORD)0xC1204DABL)

//
// MessageId: CENTRALINA_AL
//
// MessageText:
//
//  ALLARME RIPARI - Centralina di sicurezza non attiva con riparo chiuso
//
#define CENTRALINA_AL                    ((DWORD)0xC1204DAEL)

//
// MessageId: BORDO_SENSIB_PREM_AL
//
// MessageText:
//
//  ALLARME RIPARI - Bordo sensibile ripari intervenuto
//
#define BORDO_SENSIB_PREM_AL             ((DWORD)0xC1204DBAL)

//
// MessageId: TRASC_MORSE_AX_X_INS_A_AL
//
// MessageText:
//
//  ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non inserito: controlla il sensore
//
#define TRASC_MORSE_AX_X_INS_A_AL        ((DWORD)0xC1204DD0L)

//
// MessageId: TRASC_MORSE_AX_X_INS_B_AL
//
// MessageText:
//
//  ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non inserito: controlla la EV
//
#define TRASC_MORSE_AX_X_INS_B_AL        ((DWORD)0xC1204DD1L)

//
// MessageId: TRASC_MORSE_AX_X_DIS_A_AL
//
// MessageText:
//
//  ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non disinserito: controlla il sensore
//
#define TRASC_MORSE_AX_X_DIS_A_AL        ((DWORD)0xC1204DD2L)

//
// MessageId: TRASC_MORSE_AX_X_DIS_B_AL
//
// MessageText:
//
//  ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non disinserito: controlla la EV
//
#define TRASC_MORSE_AX_X_DIS_B_AL        ((DWORD)0xC1204DD3L)

//
// MessageId: TRASC_MORSE_AX_X_DISFC_AL
//
// MessageText:
//
//  ALLARME TRASCINATORE MORSE - Disfunzione Finecorsa Trasc.Morse Asse X
//
#define TRASC_MORSE_AX_X_DISFC_AL        ((DWORD)0xC1204DD4L)

//
// MessageId: RILMOR_AX_X_INS_AL
//
// MessageText:
//
//  ALLARME RILEVAMENTO MORSE - Time out inserzione rilevamento morse
//
#define RILMOR_AX_X_INS_AL               ((DWORD)0xC1204DE6L)

//
// MessageId: RILMOR_AX_X_DIS_AL
//
// MessageText:
//
//  ALLARME RILEVAMENTO MORSE - Time out disinserzione rilevamento morse
//
#define RILMOR_AX_X_DIS_AL               ((DWORD)0xC1204DE7L)

//
// MessageId: ALT_PRESS_MORSA10_AL
//
// MessageText:
//
//  ALLARME MORSE - Alta pressione non attiva su morsa 10
//
#define ALT_PRESS_MORSA10_AL             ((DWORD)0xC1204E03L)

//
// MessageId: ALT_PRESS_MORSA11_AL
//
// MessageText:
//
//  ALLARME MORSE - Alta pressione non attiva su morsa 11
//
#define ALT_PRESS_MORSA11_AL             ((DWORD)0xC1204E04L)

//
// MessageId: ALT_PRESS_MORSA12_AL
//
// MessageText:
//
//  ALLARME MORSE - Alta pressione non attiva su morsa 12
//
#define ALT_PRESS_MORSA12_AL             ((DWORD)0xC1204E05L)

//
// MessageId: ALT_PRESS_MORSA13_AL
//
// MessageText:
//
//  ALLARME MORSE - Alta pressione non attiva su morsa 13
//
#define ALT_PRESS_MORSA13_AL             ((DWORD)0xC1204E06L)

//
// MessageId: ALT_PRESS_MORSA14_AL
//
// MessageText:
//
//  ALLARME MORSE - Alta pressione non attiva su morsa 14
//
#define ALT_PRESS_MORSA14_AL             ((DWORD)0xC1204E07L)

//
// MessageId: ALT_PRESS_MORSA15_AL
//
// MessageText:
//
//  ALLARME MORSE - Alta pressione non attiva su morsa 15
//
#define ALT_PRESS_MORSA15_AL             ((DWORD)0xC1204E08L)

//
// MessageId: VIS_BASSA_NOAVA_A_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera bassa non aperta (avanzamento) : controlla il sensore
//
#define VIS_BASSA_NOAVA_A_AL             ((DWORD)0xC1204E10L)

//
// MessageId: VIS_BASSA_NOAVA_B_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera bassa non aperta (avanzamento) : controlla la EV
//
#define VIS_BASSA_NOAVA_B_AL             ((DWORD)0xC1204E11L)

//
// MessageId: VIS_BASSA_NOIND_A_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera bassa non chiusa (arretramento) : controlla il sensore
//
#define VIS_BASSA_NOIND_A_AL             ((DWORD)0xC1204E12L)

//
// MessageId: VIS_BASSA_NOIND_B_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera bassa non chiusa (arretramento) : controlla la EV
//
#define VIS_BASSA_NOIND_B_AL             ((DWORD)0xC1204E13L)

//
// MessageId: VIS_BASSA_DISFC_AL
//
// MessageText:
//
//  ALLARME RIPARI - Disfunzione finecorsa visiera bassa
//
#define VIS_BASSA_DISFC_AL               ((DWORD)0xC1204E14L)

//
// MessageId: VIS_RIP_NODIS_A_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera alta non aperta (discesa) : controlla il sensore
//
#define VIS_RIP_NODIS_A_AL               ((DWORD)0xC1204E1AL)

//
// MessageId: VIS_RIP_NODIS_B_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera alta non aperta (discesa) : controlla la EV
//
#define VIS_RIP_NODIS_B_AL               ((DWORD)0xC1204E1BL)

//
// MessageId: VIS_RIP_NOSAL_A_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera alta non chiusa (salita) : controlla il sensore
//
#define VIS_RIP_NOSAL_A_AL               ((DWORD)0xC1204E1CL)

//
// MessageId: VIS_RIP_NOSAL_B_AL
//
// MessageText:
//
//  ALLARME RIPARI - Time Out Visiera alta non chiusa (salita) : controlla la EV
//
#define VIS_RIP_NOSAL_B_AL               ((DWORD)0xC1204E1DL)

//
// MessageId: TOOL_01_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T1 rotto
//
#define TOOL_01_MORTO_AL                 ((DWORD)0xC1204E22L)

//
// MessageId: TOOL_02_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T2 rotto
//
#define TOOL_02_MORTO_AL                 ((DWORD)0xC1204E23L)

//
// MessageId: TOOL_03_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T3 rotto
//
#define TOOL_03_MORTO_AL                 ((DWORD)0xC1204E24L)

//
// MessageId: TOOL_04_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T4 rotto
//
#define TOOL_04_MORTO_AL                 ((DWORD)0xC1204E25L)

//
// MessageId: TOOL_05_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T5 rotto
//
#define TOOL_05_MORTO_AL                 ((DWORD)0xC1204E26L)

//
// MessageId: TOOL_06_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T6 rotto
//
#define TOOL_06_MORTO_AL                 ((DWORD)0xC1204E27L)

//
// MessageId: TOOL_07_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T7 rotto
//
#define TOOL_07_MORTO_AL                 ((DWORD)0xC1204E28L)

//
// MessageId: TOOL_08_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T8 rotto
//
#define TOOL_08_MORTO_AL                 ((DWORD)0xC1204E29L)

//
// MessageId: TOOL_09_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T9 rotto
//
#define TOOL_09_MORTO_AL                 ((DWORD)0xC1204E2AL)

//
// MessageId: TOOL_10_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T10 rotto
//
#define TOOL_10_MORTO_AL                 ((DWORD)0xC1204E2BL)

//
// MessageId: TOOL_11_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T11 rotto
//
#define TOOL_11_MORTO_AL                 ((DWORD)0xC1204E2CL)

//
// MessageId: TOOL_12_MORTO_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Utensile T12 rotto
//
#define TOOL_12_MORTO_AL                 ((DWORD)0xC1204E2DL)

//
// MessageId: NOT_ALIVE_DRILL_AL
//
// MessageText:
//
//  ALLARME UTENSILI - Drill not alive
//
#define NOT_ALIVE_DRILL_AL               ((DWORD)0xC1204E2EL)

//
// MessageId: MORSE_NO_AGG_GANTRY_AL
//
// MessageText:
//
//  ALLARME GANTRY - Morse non agganciate in gantry
//
#define MORSE_NO_AGG_GANTRY_AL           ((DWORD)0xC1204E30L)

//
// MessageId: MORSE_NO_SGAN_GANTRY_AL
//
// MessageText:
//
//  ALLARME GANTRY - Morse non sganciate in gantry
//
#define MORSE_NO_SGAN_GANTRY_AL          ((DWORD)0xC1204E31L)

//
// MessageId: POSIZ_MORSE_NOT_OK_AL
//
// MessageText:
//
//  ALLARME ASSI MORSE - Posizioni assi morse non congruenti (posizioni encoder perse)
//
#define POSIZ_MORSE_NOT_OK_AL            ((DWORD)0xC1204E32L)

//
// MessageId: ERR_UT_IN_MEM_AL
//
// MessageText:
//
//  ALLARME CAMBIO UTENSILI - Incongruenza tra utensile teoricamente presente e sensore di presenza utensile
//
#define ERR_UT_IN_MEM_AL                 ((DWORD)0xC1204E33L)

//
// MessageId: TOOL_NOK_AL
//
// MessageText:
//
//  ALLARME CONTROLLO UTENSILE - Utensile rotto
//
#define TOOL_NOK_AL                      ((DWORD)0xC1204E34L)

//
// MessageId: CKTOOL_NOK_AL
//
// MessageText:
//
//  ALLARME CONTROLLO UTENSILE - Dispositivo verifica integrità utensile non funzionante
//
#define CKTOOL_NOK_AL                    ((DWORD)0xC1204E35L)

//
// MessageId: EXC_POS_M10_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M10 in extracorsa positivo
//
#define EXC_POS_M10_AL                   ((DWORD)0xC1204E46L)

//
// MessageId: EXC_NEG_M10_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M10 in extracorsa negativo
//
#define EXC_NEG_M10_AL                   ((DWORD)0xC1204E47L)

//
// MessageId: EXC_POS_M11_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M11 in extracorsa positivo
//
#define EXC_POS_M11_AL                   ((DWORD)0xC1204E48L)

//
// MessageId: EXC_NEG_M11_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M11 in extracorsa negativo
//
#define EXC_NEG_M11_AL                   ((DWORD)0xC1204E49L)

//
// MessageId: EXC_POS_M12_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M12 in extracorsa positivo
//
#define EXC_POS_M12_AL                   ((DWORD)0xC1204E4AL)

//
// MessageId: EXC_NEG_M12_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M12 in extracorsa negativo
//
#define EXC_NEG_M12_AL                   ((DWORD)0xC1204E4BL)

//
// MessageId: EXC_POS_M13_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M13 in extracorsa positivo
//
#define EXC_POS_M13_AL                   ((DWORD)0xC1204E4CL)

//
// MessageId: EXC_NEG_M13_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M13 in extracorsa negativo
//
#define EXC_NEG_M13_AL                   ((DWORD)0xC1204E4DL)

//
// MessageId: EXC_POS_M14_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M14 in extracorsa positivo
//
#define EXC_POS_M14_AL                   ((DWORD)0xC1204E4EL)

//
// MessageId: EXC_NEG_M14_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M14 in extracorsa negativo
//
#define EXC_NEG_M14_AL                   ((DWORD)0xC1204E4FL)

//
// MessageId: EXC_POS_M15_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M15 in extracorsa positivo
//
#define EXC_POS_M15_AL                   ((DWORD)0xC1204E50L)

//
// MessageId: EXC_NEG_M15_AL
//
// MessageText:
//
//  ALLARME ASSE MORSA - Asse Morsa M15 in extracorsa negativo
//
#define EXC_NEG_M15_AL                   ((DWORD)0xC1204E51L)

//
// MessageId: INIT_ERROR_AL
//
// MessageText:
//
//  ALLARME CONFIGURAZIONE - Errore inizializzazione variabili PLC
//
#define INIT_ERROR_AL                    ((DWORD)0xC1204E6BL)

//
// MessageId: CONFMAC_ERROR_AL
//
// MessageText:
//
//  ALLARME CONFIGURAZIONE - Errore lettura confmac
//
#define CONFMAC_ERROR_AL                 ((DWORD)0xC1204E6CL)

//
// MessageId: MGPILOT_ERROR_AL
//
// MessageText:
//
//  ALLARME CONFIGURAZIONE - Errore caricamento funzioni manuali (MGPilot)
//
#define MGPILOT_ERROR_AL                 ((DWORD)0xC1204E6DL)

//
// MessageId: REMCTRL_ERROR_AL
//
// MessageText:
//
//  ALLARME CONFIGURAZIONE - Errore caricamento funzioni manuali (REM_CTRL)
//
#define REMCTRL_ERROR_AL                 ((DWORD)0xC1204E6EL)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - Livello Batteria encoder basso
//
#define BATTERIA_LOWLEVEL_ASSE_X_AL      ((DWORD)0xC1204E70L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - Livello Batteria encoder basso
//
#define BATTERIA_LOWLEVEL_ASSE_Y_AL      ((DWORD)0xC1204E71L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - Livello Batteria encoder basso
//
#define BATTERIA_LOWLEVEL_ASSE_Z_AL      ((DWORD)0xC1204E72L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - Livello Batteria encoder basso
//
#define BATTERIA_LOWLEVEL_ASSE_A_AL      ((DWORD)0xC1204E73L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - Livello Batteria encoder basso
//
#define BATTERIA_LOWLEVEL_ASSE_W_AL      ((DWORD)0xC1204E74L)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - Livello Batteria encoder basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_X_AL    ((DWORD)0xC1204E77L)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - Livello Batteria encoder basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_Y_AL    ((DWORD)0xC1204E78L)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - Livello Batteria encoder basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_Z_AL    ((DWORD)0xC1204E79L)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - Livello Batteria encoder basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_A_AL    ((DWORD)0xC1204E7AL)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - Livello Batteria encoder basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_W_AL    ((DWORD)0xC1204E7BL)

//
// MessageId: MT_OVERFLOW_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - Overflow sui giri massimi del multiturn dell'encoder assoluto
//
#define MT_OVERFLOW_ASSE_X_AL            ((DWORD)0xC1204E80L)

//
// MessageId: MT_OVERFLOW_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - Overflow sui giri massimi del multiturn dell'encoder assoluto
//
#define MT_OVERFLOW_ASSE_Y_AL            ((DWORD)0xC1204E81L)

//
// MessageId: MT_OVERFLOW_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - Overflow sui giri massimi del multiturn dell'encoder assoluto
//
#define MT_OVERFLOW_ASSE_Z_AL            ((DWORD)0xC1204E82L)

//
// MessageId: MT_OVERFLOW_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - Overflow sui giri massimi del multiturn dell'encoder assoluto
//
#define MT_OVERFLOW_ASSE_A_AL            ((DWORD)0xC1204E83L)

//
// MessageId: MT_OVERFLOW_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - Overflow sui giri massimi del multiturn dell'encoder assoluto
//
#define MT_OVERFLOW_ASSE_W_AL            ((DWORD)0xC1204E84L)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - Posizione assoluta encoder non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_X_AL     ((DWORD)0xC1204E87L)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - Posizione assoluta encoder non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_Y_AL     ((DWORD)0xC1204E88L)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - Posizione assoluta encoder non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_Z_AL     ((DWORD)0xC1204E89L)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - Posizione assoluta encoder non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_A_AL     ((DWORD)0xC1204E8AL)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - Posizione assoluta encoder non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_W_AL     ((DWORD)0xC1204E8BL)

//
// MessageId: CLEAR_ENCODER_ERROR_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - Funzione di reset encoder assoluto non riuscita
//
#define CLEAR_ENCODER_ERROR_ASSE_X_AL    ((DWORD)0xC1204E90L)

//
// MessageId: CLEAR_ENCODER_ERROR_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - Funzione di reset encoder assoluto non riuscita
//
#define CLEAR_ENCODER_ERROR_ASSE_Y_AL    ((DWORD)0xC1204E91L)

//
// MessageId: CLEAR_ENCODER_ERROR_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - Funzione di reset encoder assoluto non riuscita
//
#define CLEAR_ENCODER_ERROR_ASSE_Z_AL    ((DWORD)0xC1204E92L)

//
// MessageId: CLEAR_ENCODER_ERROR_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - Funzione di reset encoder assoluto non riuscita
//
#define CLEAR_ENCODER_ERROR_ASSE_A_AL    ((DWORD)0xC1204E93L)

//
// MessageId: CLEAR_ENCODER_ERROR_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - Funzione di reset encoder assoluto non riuscita
//
#define CLEAR_ENCODER_ERROR_ASSE_W_AL    ((DWORD)0xC1204E94L)

//
// MessageId: UNDER_VOLTAGE_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - La tensione DC del circuito principale è più bassa del valore standard
//
#define UNDER_VOLTAGE_ASSE_X_AL          ((DWORD)0xC1204E97L)

//
// MessageId: UNDER_VOLTAGE_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - La tensione DC del circuito principale è più bassa del valore standard
//
#define UNDER_VOLTAGE_ASSE_Y_AL          ((DWORD)0xC1204E98L)

//
// MessageId: UNDER_VOLTAGE_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - La tensione DC del circuito principale è più bassa del valore standard
//
#define UNDER_VOLTAGE_ASSE_Z_AL          ((DWORD)0xC1204E99L)

//
// MessageId: UNDER_VOLTAGE_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - La tensione DC del circuito principale è più bassa del valore standard
//
#define UNDER_VOLTAGE_ASSE_A_AL          ((DWORD)0xC1204E9AL)

//
// MessageId: UNDER_VOLTAGE_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - La tensione DC del circuito principale è più bassa del valore standard
//
#define UNDER_VOLTAGE_ASSE_W_AL          ((DWORD)0xC1204E9BL)

//
// MessageId: MOTORE_SENZA_FASE_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - Mancanza di una fase in ingresso
//
#define MOTORE_SENZA_FASE_ASSE_X_AL      ((DWORD)0xC1204EA0L)

//
// MessageId: MOTORE_SENZA_FASE_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - Mancanza di una fase in ingresso
//
#define MOTORE_SENZA_FASE_ASSE_Y_AL      ((DWORD)0xC1204EA1L)

//
// MessageId: MOTORE_SENZA_FASE_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - Mancanza di una fase in ingresso
//
#define MOTORE_SENZA_FASE_ASSE_Z_AL      ((DWORD)0xC1204EA2L)

//
// MessageId: MOTORE_SENZA_FASE_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - Mancanza di una fase in ingresso
//
#define MOTORE_SENZA_FASE_ASSE_A_AL      ((DWORD)0xC1204EA3L)

//
// MessageId: MOTORE_SENZA_FASE_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - Mancanza di una fase in ingresso
//
#define MOTORE_SENZA_FASE_ASSE_W_AL      ((DWORD)0xC1204EA4L)

//
// MessageId: OVERSHOOT_SPEED_ASSE_X_AL
//
// MessageText:
//
//  ALLARME ASSE X - La velocità del motore è in overshoot rispetto al valore massimo di targa
//
#define OVERSHOOT_SPEED_ASSE_X_AL        ((DWORD)0xC1204EA7L)

//
// MessageId: OVERSHOOT_SPEED_ASSE_Y_AL
//
// MessageText:
//
//  ALLARME ASSE Y - La velocità del motore è in overshoot rispetto al valore massimo di targa
//
#define OVERSHOOT_SPEED_ASSE_Y_AL        ((DWORD)0xC1204EA8L)

//
// MessageId: OVERSHOOT_SPEED_ASSE_Z_AL
//
// MessageText:
//
//  ALLARME ASSE Z - La velocità del motore è in overshoot rispetto al valore massimo di targa
//
#define OVERSHOOT_SPEED_ASSE_Z_AL        ((DWORD)0xC1204EA9L)

//
// MessageId: OVERSHOOT_SPEED_ASSE_A_AL
//
// MessageText:
//
//  ALLARME ASSE A - La velocità del motore è in overshoot rispetto al valore massimo di targa
//
#define OVERSHOOT_SPEED_ASSE_A_AL        ((DWORD)0xC1204EAAL)

//
// MessageId: OVERSHOOT_SPEED_ASSE_W_AL
//
// MessageText:
//
//  ALLARME ASSE W - La velocità del motore è in overshoot rispetto al valore massimo di targa
//
#define OVERSHOOT_SPEED_ASSE_W_AL        ((DWORD)0xC1204EABL)

//
// MessageId: PLC_IEC_NOT_ALIVE_AL
//
// MessageText:
//
//  ALLARME PLC IEC - PLC IEC timeout di not alive
//
#define PLC_IEC_NOT_ALIVE_AL             ((DWORD)0xC1204EB0L)

//
// MessageId: INVERTER_0_COM_ERROR_AL
//
// MessageText:
//
//  ALLARME PLC IEC - Errore di comunicazione COM con inverter 0
//
#define INVERTER_0_COM_ERROR_AL          ((DWORD)0xC1204EB1L)

//
// MessageId: ASSE_0_COM_ERROR_AL
//
// MessageText:
//
//  ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse X
//
#define ASSE_0_COM_ERROR_AL              ((DWORD)0xC1204EC0L)

//
// MessageId: ASSE_1_COM_ERROR_AL
//
// MessageText:
//
//  ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse Y
//
#define ASSE_1_COM_ERROR_AL              ((DWORD)0xC1204EC1L)

//
// MessageId: ASSE_2_COM_ERROR_AL
//
// MessageText:
//
//  ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse Z
//
#define ASSE_2_COM_ERROR_AL              ((DWORD)0xC1204EC2L)

//
// MessageId: ASSE_3_COM_ERROR_AL
//
// MessageText:
//
//  ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse A
//
#define ASSE_3_COM_ERROR_AL              ((DWORD)0xC1204EC3L)

//
// MessageId: ASSE_4_COM_ERROR_AL
//
// MessageText:
//
//  ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse W
//
#define ASSE_4_COM_ERROR_AL              ((DWORD)0xC1204EC4L)

//
// MessageId: ALARM_LAST_AL
//
// MessageText:
//
//  Ultimo allarme disponibile
//
#define ALARM_LAST_AL                    ((DWORD)0xC1204F0FL)

//-- Messaggi macchina -------------------------------------------------------
//----------------------------------------------------------------------------
//
// MessageId: MESSAGE_FIRST_MS
//
// MessageText:
//
//  Primo messaggio da non usare
//
#define MESSAGE_FIRST_MS                 ((DWORD)0x81204F10L)

//
// MessageId: ASSI_NORIF_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Assi non riferiti
//
#define ASSI_NORIF_MS                    ((DWORD)0x81204F11L)

//
// MessageId: PC_HOLD_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Macchina in HOLD
//
#define PC_HOLD_MS                       ((DWORD)0x81204F12L)

//
// MessageId: UTSCON_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Utensile sconosciuto su mandrino
//
#define UTSCON_MS                        ((DWORD)0x81204F13L)

//
// MessageId: POT_ZERO_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Potenziometro a Zero in Ciclo Automatico
//
#define POT_ZERO_MS                      ((DWORD)0x81204F14L)

//
// MessageId: MAGUT_HOLD_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Macchina in HOLD da Magazzino
//
#define MAGUT_HOLD_MS                    ((DWORD)0x81204F15L)

//
// MessageId: MORSE_SX_HOLD_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Macchina in HOLD da Morse Zona SX
//
#define MORSE_SX_HOLD_MS                 ((DWORD)0x81204F16L)

//
// MessageId: MORSE_DX_HOLD_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Macchina in HOLD da Morse Zona DX
//
#define MORSE_DX_HOLD_MS                 ((DWORD)0x81204F17L)

//
// MessageId: FEEDHOLD_MAND_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Macchina in HOLD da Mandrino
//
#define FEEDHOLD_MAND_MS                 ((DWORD)0x81204F18L)

//
// MessageId: RIPARI_HOLD_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Macchina in HOLD da Ripari
//
#define RIPARI_HOLD_MS                   ((DWORD)0x81204F19L)

//
// MessageId: COLL_MAGUT_CARTER_SX_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Magazzino in potenziale collisione con carter laterale SX della macchina
//
#define COLL_MAGUT_CARTER_SX_MS          ((DWORD)0x81204F1AL)

//
// MessageId: MAN_COLL_MAG_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Mandrino in potenziale collisione con magazzino
//
#define MAN_COLL_MAG_MS                  ((DWORD)0x81204F1BL)

//
// MessageId: FATM_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Blocco Esecuzioni FATM Attivo
//
#define FATM_MS                          ((DWORD)0x81204F1CL)

//
// MessageId: HOLD_AP_CH_RIPARI_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Hold apertura / chiusura ripari anteriori da posizione assi Y, A, C
//
#define HOLD_AP_CH_RIPARI_MS             ((DWORD)0x81204F1DL)

//
// MessageId: POSSIBILE_CORTO_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Attenzione : Possibile corto sugli ingressi non ritentivi
//
#define POSSIBILE_CORTO_MS               ((DWORD)0x81204F1EL)

//
// MessageId: COLL_RIPARI_Y_A_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Potenziale collisione fra utensile e riparo anteriore
//
#define COLL_RIPARI_Y_A_MS               ((DWORD)0x81204F1FL)

//
// MessageId: SBLOC_UT_RIP_AP_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Sbloc. Ut. diretto possibile solo con ripari bassi
//
#define SBLOC_UT_RIP_AP_MS               ((DWORD)0x81204F20L)

//
// MessageId: INGRASS_DISAB_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Ingrassaggio Automatico disabilitato
//
#define INGRASS_DISAB_MS                 ((DWORD)0x81204F29L)

//
// MessageId: NO_OUT_MAC_ABIL_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Assenza uscite pericolose con centralina di sicurezza ok
//
#define NO_OUT_MAC_ABIL_MS               ((DWORD)0x81204F2BL)

//
// MessageId: CNT_BRIDGE_STATE_INFO_INIT_DONE_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Inizializzazione password Bridge fatta, riavviare
//
#define CNT_BRIDGE_STATE_INFO_INIT_DONE_MS ((DWORD)0x81204F2EL)

//
// MessageId: CONTATORI_BRIDGE_SAVE_FILE_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Errore scrittura file contatori
//
#define CONTATORI_BRIDGE_SAVE_FILE_MS    ((DWORD)0x81204F2FL)

//
// MessageId: MGPILOT_ERROR_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Errore caricamento funzioni manuali (MGPilot)
//
#define MGPILOT_ERROR_MS                 ((DWORD)0x81204F5DL)

//
// MessageId: REMCTRL_ERROR_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Errore caricamento funzioni manuali (REM_CTRL)
//
#define REMCTRL_ERROR_MS                 ((DWORD)0x81204F5EL)

//
// MessageId: PRE_OVERLOAD_ASSE_X_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Motore asse X in preallarme da sovraccarico
//
#define PRE_OVERLOAD_ASSE_X_MS           ((DWORD)0x81204F60L)

//
// MessageId: PRE_OVERLOAD_ASSE_Y_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Motore asse Y in preallarme da sovraccarico
//
#define PRE_OVERLOAD_ASSE_Y_MS           ((DWORD)0x81204F61L)

//
// MessageId: PRE_OVERLOAD_ASSE_Z_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Motore asse Z in preallarme da sovraccarico
//
#define PRE_OVERLOAD_ASSE_Z_MS           ((DWORD)0x81204F62L)

//
// MessageId: PRE_OVERLOAD_ASSE_A_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Motore asse A in preallarme da sovraccarico
//
#define PRE_OVERLOAD_ASSE_A_MS           ((DWORD)0x81204F63L)

//
// MessageId: PRE_OVERLOAD_ASSE_W_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Motore asse W in preallarme da sovraccarico
//
#define PRE_OVERLOAD_ASSE_W_MS           ((DWORD)0x81204F64L)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_X_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse X basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_X_MS    ((DWORD)0x81204F68L)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_Y_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse Y basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_Y_MS    ((DWORD)0x81204F69L)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_Z_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse Z basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_Z_MS    ((DWORD)0x81204F6AL)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_A_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse A basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_A_MS    ((DWORD)0x81204F6BL)

//
// MessageId: QUOTA_ENCODER_PERSA_ASSE_W_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse W basso e posizione assoluta persa
//
#define QUOTA_ENCODER_PERSA_ASSE_W_MS    ((DWORD)0x81204F6CL)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_X_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse X basso
//
#define BATTERIA_LOWLEVEL_ASSE_X_MS      ((DWORD)0x81204F70L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_Y_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse Y basso
//
#define BATTERIA_LOWLEVEL_ASSE_Y_MS      ((DWORD)0x81204F71L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_Z_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse Z basso
//
#define BATTERIA_LOWLEVEL_ASSE_Z_MS      ((DWORD)0x81204F72L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_A_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse A basso
//
#define BATTERIA_LOWLEVEL_ASSE_A_MS      ((DWORD)0x81204F73L)

//
// MessageId: BATTERIA_LOWLEVEL_ASSE_W_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Livello Batteria encoder asse W basso
//
#define BATTERIA_LOWLEVEL_ASSE_W_MS      ((DWORD)0x81204F74L)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_X_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Posizione assoluta encoder asse X non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_X_MS     ((DWORD)0x81204F78L)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_Y_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Posizione assoluta encoder asse Y non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_Y_MS     ((DWORD)0x81204F79L)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_Z_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Posizione assoluta encoder asse Z non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_Z_MS     ((DWORD)0x81204F7AL)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_A_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Posizione assoluta encoder asse A non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_A_MS     ((DWORD)0x81204F7BL)

//
// MessageId: POS_ENCODER_NOINIT_ASSE_W_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Posizione assoluta encoder asse W non inizializzata
//
#define POS_ENCODER_NOINIT_ASSE_W_MS     ((DWORD)0x81204F7CL)

//
// MessageId: MT_OVERFLOW_ASSE_X_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse X
//
#define MT_OVERFLOW_ASSE_X_MS            ((DWORD)0x81204F80L)

//
// MessageId: MT_OVERFLOW_ASSE_Y_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse Y
//
#define MT_OVERFLOW_ASSE_Y_MS            ((DWORD)0x81204F81L)

//
// MessageId: MT_OVERFLOW_ASSE_Z_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse Z
//
#define MT_OVERFLOW_ASSE_Z_MS            ((DWORD)0x81204F82L)

//
// MessageId: MT_OVERFLOW_ASSE_A_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse A
//
#define MT_OVERFLOW_ASSE_A_MS            ((DWORD)0x81204F83L)

//
// MessageId: MT_OVERFLOW_ASSE_W_MS
//
// MessageText:
//
//  MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse W
//
#define MT_OVERFLOW_ASSE_W_MS            ((DWORD)0x81204F84L)

//
// MessageId: MESSAGE_LAST_MS
//
// MessageText:
//
//  Ultimo messaggio disponibile
//
#define MESSAGE_LAST_MS                  ((DWORD)0x81204FBFL)

#endif // MESSAGES_H_INCLUDED
