;#ifndef MESSAGES_H_INCLUDED
;#define MESSAGES_H_INCLUDED
;//*******************************************************************
;//
;// TITOLO:      messages.mc
;//
;// DATA:        mercoled� 1 aprile 2026
;//
;// DESCRIZIONE: Generato automaticamente da inc2all.js
;//
;//*******************************************************************
;//                                                                   
;//  NOTE: comments in the .mc file must use both ; and //.           
;//                                                                   
;//  Status values are 32 bit values layed out as follows:            
;//                                                                   
;//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1                     
;//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 
;//  +---+-+-------------------------+-------------------------------+
;//  |Sev|C|       Facility          |               Code            |
;//  +---+-+-------------------------+-------------------------------+
;//                                                                   
;//  where                                                            
;//                                                                   
;//      Sev - is the severity code                                   
;//                                                                   
;//          00 - Success                                             
;//          01 - Informational                                       
;//          10 - Warning                                             
;//          11 - Error                                               
;//                                                                   
;//      C - is the Customer code flag                                
;//                                                                   
;//      Facility - is the facility code                              
;//                                                                   
;//      Code - is the facility's status code                         
;//                                                                   
;//*******************************************************************
;                                                                     
MessageIdTypedef=DWORD

SeverityNames = (
    Success       = 0x0:STATUS_SEVERITY_SUCCESS
    Informational = 0x1:STATUS_SEVERITY_INFORMATIONAL
    Warning       = 0x2:STATUS_SEVERITY_WARNING
    Error         = 0x3:STATUS_SEVERITY_ERROR
)

LanguageNames = (
    Italian = 0x0410:it
    English = 0x0409:en
)

FacilityNames = (
    System = 0x0
    Plc    = 0x120:FACILITY_PLC
)


;//-- Allarmi macchina --------------------------------------------------------
;//----------------------------------------------------------------------------
MessageId=19600 Facility=Plc Severity=Error SymbolicName=ALARM_FIRST_AL
Language=Italian
Primo allarme da non usare
.

Language=English
Primo allarme da non usare
.

MessageId=19601 Facility=Plc Severity=Error SymbolicName=DRIVE_X_NOK_AL
Language=Italian
ALLARME ASSE X - Anomalia azionamento asse X
.

Language=English
ALLARME ASSE X - Anomalia azionamento asse X
.

MessageId=19602 Facility=Plc Severity=Error SymbolicName=DRIVE_Y_NOK_AL
Language=Italian
ALLARME ASSE Y - Anomalia azionamento asse Y
.

Language=English
ALLARME ASSE Y - Anomalia azionamento asse Y
.

MessageId=19603 Facility=Plc Severity=Error SymbolicName=DRIVE_Z_NOK_AL
Language=Italian
ALLARME ASSE Z - Anomalia azionamento asse Z
.

Language=English
ALLARME ASSE Z - Anomalia azionamento asse Z
.

MessageId=19604 Facility=Plc Severity=Error SymbolicName=DRIVE_A_NOK_AL
Language=Italian
ALLARME ASSE B - Anomalia azionamento asse B
.

Language=English
ALLARME ASSE B - Anomalia azionamento asse B
.

MessageId=19605 Facility=Plc Severity=Error SymbolicName=DRIVE_C_NOK_AL
Language=Italian
ALLARME ASSE C - Anomalia azionamento asse C
.

Language=English
ALLARME ASSE C - Anomalia azionamento asse C
.

MessageId=19606 Facility=Plc Severity=Error SymbolicName=DRIVE_W_NOK_AL
Language=Italian
ALLARME ASSE W - Anomalia azionamento asse W
.

Language=English
ALLARME ASSE W - Anomalia azionamento asse W
.

MessageId=19609 Facility=Plc Severity=Error SymbolicName=DRIVE_ALIM_AL
Language=Italian
ALLARME GENERALE - Assenza alimentazione agli azionamenti degli assi
.

Language=English
ALLARME GENERALE - Assenza alimentazione agli azionamenti degli assi
.

MessageId=19615 Facility=Plc Severity=Error SymbolicName=CNT_ERROR_AL
Language=Italian
ALLARME SOFTWARE - Allarme lettura scrittura contatori
.

Language=English
ALLARME SOFTWARE - Allarme lettura scrittura contatori
.

MessageId=19619 Facility=Plc Severity=Error SymbolicName=DRIVE_M10_NOK_AL
Language=Italian
ALLARME ASSE MORSA M10 - Anomalia azionamento asse Morsa M10
.

Language=English
ALLARME ASSE MORSA M10 - Anomalia azionamento asse Morsa M10
.

MessageId=19620 Facility=Plc Severity=Error SymbolicName=DRIVE_M11_NOK_AL
Language=Italian
ALLARME ASSE MORSA M11 - Anomalia azionamento asse Morsa M11
.

Language=English
ALLARME ASSE MORSA M11 - Anomalia azionamento asse Morsa M11
.

MessageId=19621 Facility=Plc Severity=Error SymbolicName=DRIVE_M12_NOK_AL
Language=Italian
ALLARME ASSE MORSA M12 - Anomalia azionamento asse Morsa M12
.

Language=English
ALLARME ASSE MORSA M12 - Anomalia azionamento asse Morsa M12
.

MessageId=19622 Facility=Plc Severity=Error SymbolicName=DRIVE_M13_NOK_AL
Language=Italian
ALLARME ASSE MORSA M13 - Anomalia azionamento asse Morsa M13
.

Language=English
ALLARME ASSE MORSA M13 - Anomalia azionamento asse Morsa M13
.

MessageId=19623 Facility=Plc Severity=Error SymbolicName=DRIVE_M14_NOK_AL
Language=Italian
ALLARME ASSE MORSA M14 - Anomalia azionamento asse Morsa M14
.

Language=English
ALLARME ASSE MORSA M14 - Anomalia azionamento asse Morsa M14
.

MessageId=19624 Facility=Plc Severity=Error SymbolicName=DRIVE_M15_NOK_AL
Language=Italian
ALLARME ASSE MORSA M15 - Anomalia azionamento asse Morsa M15
.

Language=English
ALLARME ASSE MORSA M15 - Anomalia azionamento asse Morsa M15
.

MessageId=19632 Facility=Plc Severity=Error SymbolicName=ALIM_NOPRES_AL
Language=Italian
ALLARME GENERALE - Alimentazioni non presenti
.

Language=English
ALLARME GENERALE - Alimentazioni non presenti
.

MessageId=19633 Facility=Plc Severity=Error SymbolicName=EMERGENZA_AL
Language=Italian
ALLARME GENERALE - Emergenza premuta
.

Language=English
ALLARME GENERALE - Emergenza premuta
.

MessageId=19634 Facility=Plc Severity=Error SymbolicName=AUX_NOINS_AL
Language=Italian
ALLARME GENERALE - Ausiliari non inseriti
.

Language=English
ALLARME GENERALE - Ausiliari non inseriti
.

MessageId=19635 Facility=Plc Severity=Error SymbolicName=ARIA_NOPRES_AL
Language=Italian
ALLARME GENERALE - Pressione aria insufficiente
.

Language=English
ALLARME GENERALE - Pressione aria insufficiente
.

MessageId=19636 Facility=Plc Severity=Error SymbolicName=TEMP_NOK_AL
Language=Italian
ALLARME GENERALE - Temperatura armadio non ok
.

Language=English
ALLARME GENERALE - Temperatura armadio non ok
.

MessageId=19637 Facility=Plc Severity=Error SymbolicName=TERMICI_NOK_AL
Language=Italian
ALLARME GENERALE - Termici scattati
.

Language=English
ALLARME GENERALE - Termici scattati
.

MessageId=19639 Facility=Plc Severity=Error SymbolicName=TERM_TRASP_AL
Language=Italian
ALLARME TRASP.TRUCIOLI - Termico trasportatore scattato
.

Language=English
ALLARME TRASP.TRUCIOLI - Termico trasportatore scattato
.

MessageId=19640 Facility=Plc Severity=Error SymbolicName=TERM_ASP_AL
Language=Italian
ALLARME ASPIRATORE - Termico aspiratore scattato
.

Language=English
ALLARME ASPIRATORE - Termico aspiratore scattato
.

MessageId=19642 Facility=Plc Severity=Error SymbolicName=CNC_AL
Language=Italian
ALLARME GENERALE - CNC in allarme
.

Language=English
ALLARME GENERALE - CNC in allarme
.

MessageId=19643 Facility=Plc Severity=Error SymbolicName=CNC1_AL
Language=Italian
ALLARME GENERALE - CNC1 in allarme
.

Language=English
ALLARME GENERALE - CNC1 in allarme
.

MessageId=19644 Facility=Plc Severity=Error SymbolicName=CNC2_AL
Language=Italian
ALLARME GENERALE - CNC2 in allarme
.

Language=English
ALLARME GENERALE - CNC2 in allarme
.

MessageId=19646 Facility=Plc Severity=Error SymbolicName=COND_ASINCRO_CNC_MAN_AL
Language=Italian
ALLARME GENERALE - CNC0, CNC1, CNC2 non tutti in manuale
.

Language=English
ALLARME GENERALE - CNC0, CNC1, CNC2 non tutti in manuale
.

MessageId=19647 Facility=Plc Severity=Error SymbolicName=COND_ASINCRO_CNC_AUT_AL
Language=Italian
ALLARME GENERALE - CNC0, CNC1, CNC2 non tutti in automatico
.

Language=English
ALLARME GENERALE - CNC0, CNC1, CNC2 non tutti in automatico
.

MessageId=19648 Facility=Plc Severity=Error SymbolicName=DRIVEM_NOK_AL
Language=Italian
ALLARME MANDRINO - Anomalia inverter mandrino
.

Language=English
ALLARME MANDRINO - Anomalia inverter mandrino
.

MessageId=19649 Facility=Plc Severity=Error SymbolicName=DRIVEM_PREA_AL
Language=Italian
ALLARME MANDRINO - Inverter mandrino in sovraccarico
.

Language=English
ALLARME MANDRINO - Inverter mandrino in sovraccarico
.

MessageId=19650 Facility=Plc Severity=Error SymbolicName=MANDRINO_FERMO_AL
Language=Italian
ALLARME MANDRINO - Mandrino non in rotazione
.

Language=English
ALLARME MANDRINO - Mandrino non in rotazione
.

MessageId=19651 Facility=Plc Severity=Error SymbolicName=MANDRINO_HOLD_AL
Language=Italian
ALLARME MANDRINO - Velocita' non a regime
.

Language=English
ALLARME MANDRINO - Velocita' non a regime
.

MessageId=19652 Facility=Plc Severity=Error SymbolicName=UT_NOSBL_AL
Language=Italian
ALLARME MANDRINO - Time out sbloccaggio utensile
.

Language=English
ALLARME MANDRINO - Time out sbloccaggio utensile
.

MessageId=19653 Facility=Plc Severity=Error SymbolicName=UT_NOBLO_AL
Language=Italian
ALLARME MANDRINO - Time out bloccaggio utensile
.

Language=English
ALLARME MANDRINO - Time out bloccaggio utensile
.

MessageId=19654 Facility=Plc Severity=Error SymbolicName=UT_DISFC_AL
Language=Italian
ALLARME MANDRINO - Disfunzione F.C bloccaggio utensile
.

Language=English
ALLARME MANDRINO - Disfunzione F.C bloccaggio utensile
.

MessageId=19655 Facility=Plc Severity=Error SymbolicName=UT_NOAGG_AL
Language=Italian
ALLARME MANDRINO - Utensile non agganciato correttamente
.

Language=English
ALLARME MANDRINO - Utensile non agganciato correttamente
.

MessageId=19656 Facility=Plc Severity=Error SymbolicName=UTSCON_AL
Language=Italian
ALLARME MANDRINO - Utensile sconosciuto su mandrino
.

Language=English
ALLARME MANDRINO - Utensile sconosciuto su mandrino
.

MessageId=19657 Facility=Plc Severity=Error SymbolicName=TERM_FRIGO_NOK_AL
Language=Italian
ALLARME MANDRINO - Termico Centralina di Raffreddamento Mandrino scattato
.

Language=English
ALLARME MANDRINO - Termico Centralina di Raffreddamento Mandrino scattato
.

MessageId=19658 Facility=Plc Severity=Error SymbolicName=FLUSSOSTATO_AL
Language=Italian
ALLARME MANDRINO - Flussostato Centralina di Raffreddamento Mandrino in allarme
.

Language=English
ALLARME MANDRINO - Flussostato Centralina di Raffreddamento Mandrino in allarme
.

MessageId=19662 Facility=Plc Severity=Error SymbolicName=MANDRINO_VIBR_AL
Language=Italian
ALLARME MANDRINO - Vibrazioni eccessive sul mandrino
.

Language=English
ALLARME MANDRINO - Vibrazioni eccessive sul mandrino
.

MessageId=19663 Facility=Plc Severity=Error SymbolicName=MANDRINO_TEMP_AL
Language=Italian
ALLARME MANDRINO - Temperatura eccessiva sul mandrino
.

Language=English
ALLARME MANDRINO - Temperatura eccessiva sul mandrino
.

MessageId=19664 Facility=Plc Severity=Error SymbolicName=EXC_POS_X_AL
Language=Italian
ALLARMI ASSI - Asse X in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse X in Extracorsa Positivo
.

MessageId=19665 Facility=Plc Severity=Error SymbolicName=EXC_NEG_X_AL
Language=Italian
ALLARMI ASSI - Asse X in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse X in Extracorsa Negativo
.

MessageId=19666 Facility=Plc Severity=Error SymbolicName=EXC_POS_Y_AL
Language=Italian
ALLARMI ASSI - Asse Y in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse Y in Extracorsa Positivo
.

MessageId=19667 Facility=Plc Severity=Error SymbolicName=EXC_NEG_Y_AL
Language=Italian
ALLARMI ASSI - Asse Y in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse Y in Extracorsa Negativo
.

MessageId=19668 Facility=Plc Severity=Error SymbolicName=EXC_POS_Z_AL
Language=Italian
ALLARMI ASSI - Asse Z in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse Z in Extracorsa Positivo
.

MessageId=19669 Facility=Plc Severity=Error SymbolicName=EXC_NEG_Z_AL
Language=Italian
ALLARMI ASSI - Asse Z in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse Z in Extracorsa Negativo
.

MessageId=19670 Facility=Plc Severity=Error SymbolicName=EXC_POS_A_AL
Language=Italian
ALLARMI ASSI - Asse A in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse A in Extracorsa Positivo
.

MessageId=19671 Facility=Plc Severity=Error SymbolicName=EXC_NEG_A_AL
Language=Italian
ALLARMI ASSI - Asse A in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse A in Extracorsa Negativo
.

MessageId=19672 Facility=Plc Severity=Error SymbolicName=EXC_POS_C_AL
Language=Italian
ALLARMI ASSI - Asse C in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse C in Extracorsa Positivo
.

MessageId=19673 Facility=Plc Severity=Error SymbolicName=EXC_NEG_C_AL
Language=Italian
ALLARMI ASSI - Asse C in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse C in Extracorsa Negativo
.

MessageId=19674 Facility=Plc Severity=Error SymbolicName=EXC_POS_P_AL
Language=Italian
ALLARMI ASSI - Asse P in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse P in Extracorsa Positivo
.

MessageId=19675 Facility=Plc Severity=Error SymbolicName=EXC_NEG_P_AL
Language=Italian
ALLARMI ASSI - Asse P in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse P in Extracorsa Negativo
.

MessageId=19676 Facility=Plc Severity=Error SymbolicName=EXC_POS_H_AL
Language=Italian
ALLARMI ASSI - Asse H in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse H in Extracorsa Positivo
.

MessageId=19677 Facility=Plc Severity=Error SymbolicName=EXC_NEG_H_AL
Language=Italian
ALLARMI ASSI - Asse H in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse H in Extracorsa Negativo
.

MessageId=19678 Facility=Plc Severity=Error SymbolicName=EXC_POS_W_AL
Language=Italian
ALLARMI ASSI - Asse W in Extracorsa Positivo
.

Language=English
ALLARMI ASSI - Asse W in Extracorsa Positivo
.

MessageId=19679 Facility=Plc Severity=Error SymbolicName=EXC_NEG_W_AL
Language=Italian
ALLARMI ASSI - Asse W in Extracorsa Negativo
.

Language=English
ALLARMI ASSI - Asse W in Extracorsa Negativo
.

MessageId=19680 Facility=Plc Severity=Error SymbolicName=UT1_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 1
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 1
.

MessageId=19681 Facility=Plc Severity=Error SymbolicName=UT1_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 1
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 1
.

MessageId=19682 Facility=Plc Severity=Error SymbolicName=UT2_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 2
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 2
.

MessageId=19683 Facility=Plc Severity=Error SymbolicName=UT2_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 2
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 2
.

MessageId=19684 Facility=Plc Severity=Error SymbolicName=UT3_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 3
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 3
.

MessageId=19685 Facility=Plc Severity=Error SymbolicName=UT3_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 3
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 3
.

MessageId=19686 Facility=Plc Severity=Error SymbolicName=UT4_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 4
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 4
.

MessageId=19687 Facility=Plc Severity=Error SymbolicName=UT4_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 4
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 4
.

MessageId=19688 Facility=Plc Severity=Error SymbolicName=UT5_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 5
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 5
.

MessageId=19689 Facility=Plc Severity=Error SymbolicName=UT5_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 5
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 5
.

MessageId=19690 Facility=Plc Severity=Error SymbolicName=UT6_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 6
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 6
.

MessageId=19691 Facility=Plc Severity=Error SymbolicName=UT6_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 6
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 6
.

MessageId=19692 Facility=Plc Severity=Error SymbolicName=UT7_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 7
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 7
.

MessageId=19693 Facility=Plc Severity=Error SymbolicName=UT7_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 7
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 7
.

MessageId=19694 Facility=Plc Severity=Error SymbolicName=UT8_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 8
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 8
.

MessageId=19695 Facility=Plc Severity=Error SymbolicName=UT8_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 8
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 8
.

MessageId=19696 Facility=Plc Severity=Error SymbolicName=UT9_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 9
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 9
.

MessageId=19697 Facility=Plc Severity=Error SymbolicName=UT9_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 9
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 9
.

MessageId=19698 Facility=Plc Severity=Error SymbolicName=UT10_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 10
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 10
.

MessageId=19699 Facility=Plc Severity=Error SymbolicName=UT10_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 10
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 10
.

MessageId=19700 Facility=Plc Severity=Error SymbolicName=UT11_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 11
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 11
.

MessageId=19701 Facility=Plc Severity=Error SymbolicName=UT11_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 11
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 11
.

MessageId=19702 Facility=Plc Severity=Error SymbolicName=UT12_PRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 12
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile depositare utensile 12
.

MessageId=19703 Facility=Plc Severity=Error SymbolicName=UT12_NOPRES_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 12
.

Language=English
ALLARME CAMBIO UTENSILI - Impossibile prelevare utensile 12
.

MessageId=19704 Facility=Plc Severity=Error SymbolicName=GANCIO_MAG_NODIS_AL
Language=Italian
ALLARME MAGAZZINO UTENSILI - Gancio magazzino utensile non disinserito
.

Language=English
ALLARME MAGAZZINO UTENSILI - Gancio magazzino utensile non disinserito
.

MessageId=19705 Facility=Plc Severity=Error SymbolicName=MANDR_COLL_MAG_AL
Language=Italian
ALLARME MAGAZZINO UTENSILI - Ciclo iniziato con mandrino in potenziale collisione con magazzino
.

Language=English
ALLARME MAGAZZINO UTENSILI - Ciclo iniziato con mandrino in potenziale collisione con magazzino
.

MessageId=19706 Facility=Plc Severity=Error SymbolicName=GANCIO_MAG_NOFUOING_AL
Language=Italian
ALLARME MAGAZZINO UTENSILI - Gancio magazzino utensile non fuori ingombro
.

Language=English
ALLARME MAGAZZINO UTENSILI - Gancio magazzino utensile non fuori ingombro
.

MessageId=19707 Facility=Plc Severity=Error SymbolicName=BAS_PRESSIONE_AL
Language=Italian
ALLARME MORSE - Alta Pressione attiva senza comando
.

Language=English
ALLARME MORSE - Alta Pressione attiva senza comando
.

MessageId=19708 Facility=Plc Severity=Error SymbolicName=COLL_RIPARI_Y_A_AL
Language=Italian
ALLARMI ASSI - Potenziale collisione fra utensile e ripari anteriori
.

Language=English
ALLARMI ASSI - Potenziale collisione fra utensile e ripari anteriori
.

MessageId=19715 Facility=Plc Severity=Error SymbolicName=POS_MORSA_10_AL
Language=Italian
ALLARME MORSE - Morsa 10 non in posizione corretta
.

Language=English
ALLARME MORSE - Morsa 10 non in posizione corretta
.

MessageId=19716 Facility=Plc Severity=Error SymbolicName=POS_MORSA_11_AL
Language=Italian
ALLARME MORSE - Morsa 11 non in posizione corretta
.

Language=English
ALLARME MORSE - Morsa 11 non in posizione corretta
.

MessageId=19717 Facility=Plc Severity=Error SymbolicName=POS_MORSA_12_AL
Language=Italian
ALLARME MORSE - Morsa 12 non in posizione corretta
.

Language=English
ALLARME MORSE - Morsa 12 non in posizione corretta
.

MessageId=19718 Facility=Plc Severity=Error SymbolicName=POS_MORSA_13_AL
Language=Italian
ALLARME MORSE - Morsa 13 non in posizione corretta
.

Language=English
ALLARME MORSE - Morsa 13 non in posizione corretta
.

MessageId=19719 Facility=Plc Severity=Error SymbolicName=POS_MORSA_14_AL
Language=Italian
ALLARME MORSE - Morsa 14 non in posizione corretta
.

Language=English
ALLARME MORSE - Morsa 14 non in posizione corretta
.

MessageId=19720 Facility=Plc Severity=Error SymbolicName=POS_MORSA_15_AL
Language=Italian
ALLARME MORSE - Morsa 15 non in posizione corretta
.

Language=English
ALLARME MORSE - Morsa 15 non in posizione corretta
.

MessageId=19724 Facility=Plc Severity=Error SymbolicName=CONT_MORSE_AL
Language=Italian
ALLARME MORSE - Conteggio morse errato
.

Language=English
ALLARME MORSE - Conteggio morse errato
.

MessageId=19725 Facility=Plc Severity=Error SymbolicName=POSMORSE_DA_PC_AL
Language=Italian
ALLARME MORSE - Errore pos. Morse da PC: valori fuori range
.

Language=English
ALLARME MORSE - Errore pos. Morse da PC: valori fuori range
.

MessageId=19727 Facility=Plc Severity=Error SymbolicName=MOD_SIC_ALL_01_AL
Language=Italian
PREDISPOSTO: ALLARME MODULO SICUREZZA - Modulo di sicurezza in anomalia, controlla la word A2843
.

Language=English
PREDISPOSTO: ALLARME MODULO SICUREZZA - Modulo di sicurezza in anomalia, controlla la word A2843
.

MessageId=19736 Facility=Plc Severity=Error SymbolicName=ALIM_MM_NOT_OK_AL
Language=Italian
ALLARME MORSE - Alimentatore morse motorizzate in zona non OK
.

Language=English
ALLARME MORSE - Alimentatore morse motorizzate in zona non OK
.

MessageId=19738 Facility=Plc Severity=Error SymbolicName=INS_BATT_PREC_AL
Language=Italian
ALLARME BATTUTA DI PRECISIONE - Battuta non inserita
.

Language=English
ALLARME BATTUTA DI PRECISIONE - Battuta non inserita
.

MessageId=19739 Facility=Plc Severity=Error SymbolicName=DIS_BATT_PREC_AL
Language=Italian
ALLARME BATTUTA DI PRECISIONE - Battuta non disinserita
.

Language=English
ALLARME BATTUTA DI PRECISIONE - Battuta non disinserita
.

MessageId=19740 Facility=Plc Severity=Error SymbolicName=BATT_PREC_QUOTA0_AL
Language=Italian
ALLARME BATTUTA DI PRECISIONE - Errore posizione a riposo della battuta
.

Language=English
ALLARME BATTUTA DI PRECISIONE - Errore posizione a riposo della battuta
.

MessageId=19741 Facility=Plc Severity=Error SymbolicName=INDICE_TAST_AL
Language=Italian
ALLARME BATTUTA DI PRECISIONE - Errore indice di tastatura
.

Language=English
ALLARME BATTUTA DI PRECISIONE - Errore indice di tastatura
.

MessageId=19742 Facility=Plc Severity=Error SymbolicName=PEZZO_NON_TROV_AL
Language=Italian
ALLARME BATTUTA DI PRECISIONE - Pezzo non trovato
.

Language=English
ALLARME BATTUTA DI PRECISIONE - Pezzo non trovato
.

MessageId=19743 Facility=Plc Severity=Error SymbolicName=POSIZIONE_PEZZO_AL
Language=Italian
ALLARME DI POSIZIONAMENTO - Pezzo appoggiato male alla battuta di riferimento
.

Language=English
ALLARME DI POSIZIONAMENTO - Pezzo appoggiato male alla battuta di riferimento
.

MessageId=19754 Facility=Plc Severity=Error SymbolicName=BATT_DX4_NOPOS_X4R_AL
Language=Italian
ALLARME BATTUTE - Battuta DX4 non in posizione X4R
.

Language=English
ALLARME BATTUTE - Battuta DX4 non in posizione X4R
.

MessageId=19755 Facility=Plc Severity=Error SymbolicName=BATT_DX4_DISFC_AL
Language=Italian
ALLARME BATTUTE - Disfunzione Finecorsa Battuta DX4
.

Language=English
ALLARME BATTUTE - Disfunzione Finecorsa Battuta DX4
.

MessageId=19756 Facility=Plc Severity=Error SymbolicName=BATT_SX1_NOPOS_X1L_AL
Language=Italian
ALLARME BATTUTE - Battuta SX1 non in posizione X1L
.

Language=English
ALLARME BATTUTE - Battuta SX1 non in posizione X1L
.

MessageId=19757 Facility=Plc Severity=Error SymbolicName=BATT_DX4_NOPOS_X3R_AL
Language=Italian
ALLARME BATTUTE - Battuta DX4 non in posizione X3R
.

Language=English
ALLARME BATTUTE - Battuta DX4 non in posizione X3R
.

MessageId=19758 Facility=Plc Severity=Error SymbolicName=BATT_DX4_NOPOS_X2R_AL
Language=Italian
ALLARME BATTUTE - Battuta DX4 non in posizione X2R
.

Language=English
ALLARME BATTUTE - Battuta DX4 non in posizione X2R
.

MessageId=19759 Facility=Plc Severity=Error SymbolicName=BATT_DX4_NOPOS_X1R_AL
Language=Italian
ALLARME BATTUTE - Battuta DX4 non in posizione X1R
.

Language=English
ALLARME BATTUTE - Battuta DX4 non in posizione X1R
.

MessageId=19760 Facility=Plc Severity=Error SymbolicName=BATTUTA_SX1_ALT_AL
Language=Italian
ALLARME BATTUTE - Battuta SX1 non alta
.

Language=English
ALLARME BATTUTE - Battuta SX1 non alta
.

MessageId=19761 Facility=Plc Severity=Error SymbolicName=BATTUTA_SX1_BAS_AL
Language=Italian
ALLARME BATTUTE - Battuta SX1 non bassa
.

Language=English
ALLARME BATTUTE - Battuta SX1 non bassa
.

MessageId=19766 Facility=Plc Severity=Error SymbolicName=BATTUTA_DX4_ALT_AL
Language=Italian
ALLARME BATTUTE - Battuta DX4 non alta
.

Language=English
ALLARME BATTUTE - Battuta DX4 non alta
.

MessageId=19767 Facility=Plc Severity=Error SymbolicName=BATTUTA_DX4_BAS_AL
Language=Italian
ALLARME BATTUTE - Battuta DX4 non bassa
.

Language=English
ALLARME BATTUTE - Battuta DX4 non bassa
.

MessageId=19776 Facility=Plc Severity=Error SymbolicName=TAVOLA_AVA_A_AL
Language=Italian
ALLARME TAVOLA - Tavola non avanti : controlla il sensore
.

Language=English
ALLARME TAVOLA - Tavola non avanti : controlla il sensore
.

MessageId=19777 Facility=Plc Severity=Error SymbolicName=TAVOLA_AVA_B_AL
Language=Italian
ALLARME TAVOLA - Tavola non avanti : controlla la EV
.

Language=English
ALLARME TAVOLA - Tavola non avanti : controlla la EV
.

MessageId=19778 Facility=Plc Severity=Error SymbolicName=TAVOLA_IND_A_AL
Language=Italian
ALLARME TAVOLA - Tavola non indietro : controlla il sensore
.

Language=English
ALLARME TAVOLA - Tavola non indietro : controlla il sensore
.

MessageId=19779 Facility=Plc Severity=Error SymbolicName=TAVOLA_IND_B_AL
Language=Italian
ALLARME TAVOLA - Tavola non indietro : controlla la EV
.

Language=English
ALLARME TAVOLA - Tavola non indietro : controlla la EV
.

MessageId=19780 Facility=Plc Severity=Error SymbolicName=TAVOLA_DISFC_AL
Language=Italian
ALLARME TAVOLA - Disfunzione Finecorsa Tavola
.

Language=English
ALLARME TAVOLA - Disfunzione Finecorsa Tavola
.

MessageId=19798 Facility=Plc Severity=Error SymbolicName=LIV_LUB_NOT_BASSO_AL
Language=Italian
ALLARME LUBRICA - Livello lubrica normale basso
.

Language=English
ALLARME LUBRICA - Livello lubrica normale basso
.

MessageId=19799 Facility=Plc Severity=Error SymbolicName=LIV_LUB_NOT_ALTO_AL
Language=Italian
ALLARME LUBRICA - Livello lubrica normale alto
.

Language=English
ALLARME LUBRICA - Livello lubrica normale alto
.

MessageId=19800 Facility=Plc Severity=Error SymbolicName=MARPOSS_TOUCH_AL
Language=Italian
ALLARME TASTATORE MARPOSS - Tastatore già in battuta ad inizio tastata
.

Language=English
ALLARME TASTATORE MARPOSS - Tastatore già in battuta ad inizio tastata
.

MessageId=19801 Facility=Plc Severity=Error SymbolicName=MARPOSS_NOTOUCH_AL
Language=Italian
ALLARME TASTATORE MARPOSS - Pezzo non rilevato da tastatore
.

Language=English
ALLARME TASTATORE MARPOSS - Pezzo non rilevato da tastatore
.

MessageId=19802 Facility=Plc Severity=Error SymbolicName=MARPOSS_INDEX_AL
Language=Italian
ALLARME TASTATORE MARPOSS - Errore indice tastatore
.

Language=English
ALLARME TASTATORE MARPOSS - Errore indice tastatore
.

MessageId=19803 Facility=Plc Severity=Error SymbolicName=MARPOSS_ERROR_AL
Language=Italian
ALLARME TASTATORE MARPOSS - Tastatore Marposs in errore
.

Language=English
ALLARME TASTATORE MARPOSS - Tastatore Marposs in errore
.

MessageId=19804 Facility=Plc Severity=Error SymbolicName=MARPOSS_LOWBA_AL
Language=Italian
ALLARME TASTATORE MARPOSS - Batteria scarica tastatore Marposs
.

Language=English
ALLARME TASTATORE MARPOSS - Batteria scarica tastatore Marposs
.

MessageId=19805 Facility=Plc Severity=Error SymbolicName=MARPOSS_ST_TOUCH_AL
Language=Italian
ALLARME TASTATORE MARPOSS - Tastatore ancor in battuta dopo fine tastata
.

Language=English
ALLARME TASTATORE MARPOSS - Tastatore ancor in battuta dopo fine tastata
.

MessageId=19806 Facility=Plc Severity=Error SymbolicName=CORREZ_TOO_BIG_AL
Language=Italian
ALLARME TASTATORE MARPOSS - Correzioni troppo grandi: verificare il tastatore
.

Language=English
ALLARME TASTATORE MARPOSS - Correzioni troppo grandi: verificare il tastatore
.

MessageId=19812 Facility=Plc Severity=Error SymbolicName=INGRASS_LIV_AL
Language=Italian
ALLARME INGRASSAGGIO GUIDE - Livello grasso basso
.

Language=English
ALLARME INGRASSAGGIO GUIDE - Livello grasso basso
.

MessageId=19813 Facility=Plc Severity=Error SymbolicName=INGRASS_EV_AL
Language=Italian
ALLARME INGRASSAGGIO GUIDE - Anomalia pompa/elettrovalvola
.

Language=English
ALLARME INGRASSAGGIO GUIDE - Anomalia pompa/elettrovalvola
.

MessageId=19814 Facility=Plc Severity=Error SymbolicName=INGRASS_ORE_AL
Language=Italian
ALLARME INGRASSAGGIO GUIDE - Mancata esecuzione per troppe ore lavorative
.

Language=English
ALLARME INGRASSAGGIO GUIDE - Mancata esecuzione per troppe ore lavorative
.

MessageId=19815 Facility=Plc Severity=Error SymbolicName=SINGOL_POMP_AL
Language=Italian
ALLARME INGRASSAGGIO GUIDE - Mancata commutazione sensore sulla singola pompata
.

Language=English
ALLARME INGRASSAGGIO GUIDE - Mancata commutazione sensore sulla singola pompata
.

MessageId=19824 Facility=Plc Severity=Error SymbolicName=PATHCONF_TXT_AL
Language=Italian
ALLARME SOFTWARE - File di configurazione utensili PATH_CONF.TXT non trovato
.

Language=English
ALLARME SOFTWARE - File di configurazione utensili PATH_CONF.TXT non trovato
.

MessageId=19825 Facility=Plc Severity=Error SymbolicName=CONFIG_PAR_AL
Language=Italian
ALLARME SOFTWARE - Errore in apertura / lettura file CONFIG.PAR
.

Language=English
ALLARME SOFTWARE - Errore in apertura / lettura file CONFIG.PAR
.

MessageId=19826 Facility=Plc Severity=Error SymbolicName=TOOLS_TXT_AL
Language=Italian
ALLARME SOFTWARE - Errore in apertura / lettura file TOOLS.TXT
.

Language=English
ALLARME SOFTWARE - Errore in apertura / lettura file TOOLS.TXT
.

MessageId=19827 Facility=Plc Severity=Error SymbolicName=HEADS_TXT_AL
Language=Italian
ALLARME SOFTWARE - Errore in apertura / lettura file HEADS.TXT
.

Language=English
ALLARME SOFTWARE - Errore in apertura / lettura file HEADS.TXT
.

MessageId=19828 Facility=Plc Severity=Error SymbolicName=CHIAMATA_UT_AL
Language=Italian
ALLARME SOFTWARE - Utensile non trovato, errato o nullo
.

Language=English
ALLARME SOFTWARE - Utensile non trovato, errato o nullo
.

MessageId=19829 Facility=Plc Severity=Error SymbolicName=PARAM_PAR_AL
Language=Italian
ALLARME SOFTWARE - Errore in apertura / lettura file PARAM.PAR
.

Language=English
ALLARME SOFTWARE - Errore in apertura / lettura file PARAM.PAR
.

MessageId=19830 Facility=Plc Severity=Error SymbolicName=HEARTBEAT_AL
Language=Italian
ALLARME SOFTWARE - Errore di comunicazione con SW Hardlock
.

Language=English
ALLARME SOFTWARE - Errore di comunicazione con SW Hardlock
.

MessageId=19831 Facility=Plc Severity=Error SymbolicName=VARIABLE_OPEN_AL
Language=Italian
ALLARME SOFTWARE - Apertura File Errata : Variable.txt
.

Language=English
ALLARME SOFTWARE - Apertura File Errata : Variable.txt
.

MessageId=19832 Facility=Plc Severity=Error SymbolicName=VARIABLE_CLOSE_AL
Language=Italian
ALLARME SOFTWARE - Chiusura File Errata : Variable.txt
.

Language=English
ALLARME SOFTWARE - Chiusura File Errata : Variable.txt
.

MessageId=19833 Facility=Plc Severity=Error SymbolicName=DRIVE_MISSING_AL
Language=Italian
ALLARME SOFTWARE - Allarme manca driver
.

Language=English
ALLARME SOFTWARE - Allarme manca driver
.

MessageId=19834 Facility=Plc Severity=Error SymbolicName=CONF_NOK_AL
Language=Italian
ALLARME SOFTWARE - Configurazione macchina sbagliata
.

Language=English
ALLARME SOFTWARE - Configurazione macchina sbagliata
.

MessageId=19835 Facility=Plc Severity=Error SymbolicName=VALORE_ERRATO_AL
Language=Italian
ALLARME SOFTWARE - Valore oltre soglie in controlli Routine ISO CNC
.

Language=English
ALLARME SOFTWARE - Valore oltre soglie in controlli Routine ISO CNC
.

MessageId=19836 Facility=Plc Severity=Error SymbolicName=TAB_UT_NON_CAR_AL
Language=Italian
ALLARME SOFTWARE - Tabella Utensili non caricata (eseguire M209)
.

Language=English
ALLARME SOFTWARE - Tabella Utensili non caricata (eseguire M209)
.

MessageId=19837 Facility=Plc Severity=Error SymbolicName=MOV_XYZ_AL
Language=Italian
ALLARME SOFTWARE - Allarme movimento assi X - Y - Z
.

Language=English
ALLARME SOFTWARE - Allarme movimento assi X - Y - Z
.

MessageId=19843 Facility=Plc Severity=Error SymbolicName=MORSA_10_NONPOS_AL
Language=Italian
ALLARME MORSE - Morsa 10 non in posizione
.

Language=English
ALLARME MORSE - Morsa 10 non in posizione
.

MessageId=19844 Facility=Plc Severity=Error SymbolicName=MORSA_11_NONPOS_AL
Language=Italian
ALLARME MORSE - Morsa 11 non in posizione
.

Language=English
ALLARME MORSE - Morsa 11 non in posizione
.

MessageId=19845 Facility=Plc Severity=Error SymbolicName=MORSA_12_NONPOS_AL
Language=Italian
ALLARME MORSE - Morsa 12 non in posizione
.

Language=English
ALLARME MORSE - Morsa 12 non in posizione
.

MessageId=19846 Facility=Plc Severity=Error SymbolicName=MORSA_13_NONPOS_AL
Language=Italian
ALLARME MORSE - Morsa 13 non in posizione
.

Language=English
ALLARME MORSE - Morsa 13 non in posizione
.

MessageId=19847 Facility=Plc Severity=Error SymbolicName=MORSA_14_NONPOS_AL
Language=Italian
ALLARME MORSE - Morsa 14 non in posizione
.

Language=English
ALLARME MORSE - Morsa 14 non in posizione
.

MessageId=19848 Facility=Plc Severity=Error SymbolicName=MORSA_15_NONPOS_AL
Language=Italian
ALLARME MORSE - Morsa 15 non in posizione
.

Language=English
ALLARME MORSE - Morsa 15 non in posizione
.

MessageId=19852 Facility=Plc Severity=Error SymbolicName=MORSA_MICRO_X_PERSO_AL
Language=Italian
ALLARME MORSE - Micro morsa perso durante posizionamento
.

Language=English
ALLARME MORSE - Micro morsa perso durante posizionamento
.

MessageId=19853 Facility=Plc Severity=Error SymbolicName=MORSA_MICRO_X_NON_TROVATO_AL
Language=Italian
ALLARME MORSE - Micro morsa Asse X non trovato in controllo posizione
.

Language=English
ALLARME MORSE - Micro morsa Asse X non trovato in controllo posizione
.

MessageId=19856 Facility=Plc Severity=Error SymbolicName=LOAD_ISO_AL
Language=Italian
ALLARME GENERALE - Errore caricamento ISOMG in memoria
.

Language=English
ALLARME GENERALE - Errore caricamento ISOMG in memoria
.

MessageId=19857 Facility=Plc Severity=Error SymbolicName=LOAD_ISO_TIMEOUT_AL
Language=Italian
ALLARME GENERALE - Timeout caricamento ISOMG in memoria
.

Language=English
ALLARME GENERALE - Timeout caricamento ISOMG in memoria
.

MessageId=19860 Facility=Plc Severity=Error SymbolicName=COMUNIC_CAN_AL
Language=Italian
ALLARME CAN OPEN - Comunicazione CanOpen in anomalia
.

Language=English
ALLARME CAN OPEN - Comunicazione CanOpen in anomalia
.

MessageId=19870 Facility=Plc Severity=Error SymbolicName=TUN_RIP_LAT_SX_CH_AL
Language=Italian
ALLARME RIPARI - Riparo laterale o tunnel SX non chiuso
.

Language=English
ALLARME RIPARI - Riparo laterale o tunnel SX non chiuso
.

MessageId=19871 Facility=Plc Severity=Error SymbolicName=TUN_RIP_LAT_DX_CH_AL
Language=Italian
ALLARME RIPARI - Riparo laterale o tunnel DX non chiuso
.

Language=English
ALLARME RIPARI - Riparo laterale o tunnel DX non chiuso
.

MessageId=19872 Facility=Plc Severity=Error SymbolicName=RIPARO_CH_A_AL
Language=Italian
ALLARME RIPARI - Time Out Riparo anteriore non chiuso : controlla il sensore
.

Language=English
ALLARME RIPARI - Time Out Riparo anteriore non chiuso : controlla il sensore
.

MessageId=19873 Facility=Plc Severity=Error SymbolicName=RIPARO_CH_B_AL
Language=Italian
ALLARME RIPARI - Time Out Riparo anteriore non chiuso : controlla la EV
.

Language=English
ALLARME RIPARI - Time Out Riparo anteriore non chiuso : controlla la EV
.

MessageId=19874 Facility=Plc Severity=Error SymbolicName=RIPARO_AP_A_AL
Language=Italian
ALLARME RIPARI - Time Out Riparo anteriore non aperto : controlla il sensore
.

Language=English
ALLARME RIPARI - Time Out Riparo anteriore non aperto : controlla il sensore
.

MessageId=19875 Facility=Plc Severity=Error SymbolicName=RIPARO_AP_B_AL
Language=Italian
ALLARME RIPARI - Time Out Riparo anteriore non aperto : controlla la EV
.

Language=English
ALLARME RIPARI - Time Out Riparo anteriore non aperto : controlla la EV
.

MessageId=19876 Facility=Plc Severity=Error SymbolicName=RIPARO_DISFC_AL
Language=Italian
ALLARME RIPARI - Disfunzione finecorsa riparo anteriore
.

Language=English
ALLARME RIPARI - Disfunzione finecorsa riparo anteriore
.

MessageId=19882 Facility=Plc Severity=Error SymbolicName=RIPARO_POST_SX_CH_AL
Language=Italian
ALLARME RIPARI - Riparo posteriore SX non Chiuso
.

Language=English
ALLARME RIPARI - Riparo posteriore SX non Chiuso
.

MessageId=19883 Facility=Plc Severity=Error SymbolicName=RIPARO_POST_DX_CH_AL
Language=Italian
ALLARME RIPARI - Riparo posteriore DX non Chiuso
.

Language=English
ALLARME RIPARI - Riparo posteriore DX non Chiuso
.

MessageId=19886 Facility=Plc Severity=Error SymbolicName=CENTRALINA_AL
Language=Italian
ALLARME RIPARI - Centralina di sicurezza non attiva con riparo chiuso
.

Language=English
ALLARME RIPARI - Centralina di sicurezza non attiva con riparo chiuso
.

MessageId=19898 Facility=Plc Severity=Error SymbolicName=BORDO_SENSIB_PREM_AL
Language=Italian
ALLARME RIPARI - Bordo sensibile ripari intervenuto
.

Language=English
ALLARME RIPARI - Bordo sensibile ripari intervenuto
.

MessageId=19920 Facility=Plc Severity=Error SymbolicName=TRASC_MORSE_AX_X_INS_A_AL
Language=Italian
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non inserito: controlla il sensore
.

Language=English
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non inserito: controlla il sensore
.

MessageId=19921 Facility=Plc Severity=Error SymbolicName=TRASC_MORSE_AX_X_INS_B_AL
Language=Italian
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non inserito: controlla la EV
.

Language=English
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non inserito: controlla la EV
.

MessageId=19922 Facility=Plc Severity=Error SymbolicName=TRASC_MORSE_AX_X_DIS_A_AL
Language=Italian
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non disinserito: controlla il sensore
.

Language=English
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non disinserito: controlla il sensore
.

MessageId=19923 Facility=Plc Severity=Error SymbolicName=TRASC_MORSE_AX_X_DIS_B_AL
Language=Italian
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non disinserito: controlla la EV
.

Language=English
ALLARME TRASCINATORE MORSE - Trasc.Morse Asse X non disinserito: controlla la EV
.

MessageId=19924 Facility=Plc Severity=Error SymbolicName=TRASC_MORSE_AX_X_DISFC_AL
Language=Italian
ALLARME TRASCINATORE MORSE - Disfunzione Finecorsa Trasc.Morse Asse X
.

Language=English
ALLARME TRASCINATORE MORSE - Disfunzione Finecorsa Trasc.Morse Asse X
.

MessageId=19942 Facility=Plc Severity=Error SymbolicName=RILMOR_AX_X_INS_AL
Language=Italian
ALLARME RILEVAMENTO MORSE - Time out inserzione rilevamento morse
.

Language=English
ALLARME RILEVAMENTO MORSE - Time out inserzione rilevamento morse
.

MessageId=19943 Facility=Plc Severity=Error SymbolicName=RILMOR_AX_X_DIS_AL
Language=Italian
ALLARME RILEVAMENTO MORSE - Time out disinserzione rilevamento morse
.

Language=English
ALLARME RILEVAMENTO MORSE - Time out disinserzione rilevamento morse
.

MessageId=19971 Facility=Plc Severity=Error SymbolicName=ALT_PRESS_MORSA10_AL
Language=Italian
ALLARME MORSE - Alta pressione non attiva su morsa 10
.

Language=English
ALLARME MORSE - Alta pressione non attiva su morsa 10
.

MessageId=19972 Facility=Plc Severity=Error SymbolicName=ALT_PRESS_MORSA11_AL
Language=Italian
ALLARME MORSE - Alta pressione non attiva su morsa 11
.

Language=English
ALLARME MORSE - Alta pressione non attiva su morsa 11
.

MessageId=19973 Facility=Plc Severity=Error SymbolicName=ALT_PRESS_MORSA12_AL
Language=Italian
ALLARME MORSE - Alta pressione non attiva su morsa 12
.

Language=English
ALLARME MORSE - Alta pressione non attiva su morsa 12
.

MessageId=19974 Facility=Plc Severity=Error SymbolicName=ALT_PRESS_MORSA13_AL
Language=Italian
ALLARME MORSE - Alta pressione non attiva su morsa 13
.

Language=English
ALLARME MORSE - Alta pressione non attiva su morsa 13
.

MessageId=19975 Facility=Plc Severity=Error SymbolicName=ALT_PRESS_MORSA14_AL
Language=Italian
ALLARME MORSE - Alta pressione non attiva su morsa 14
.

Language=English
ALLARME MORSE - Alta pressione non attiva su morsa 14
.

MessageId=19976 Facility=Plc Severity=Error SymbolicName=ALT_PRESS_MORSA15_AL
Language=Italian
ALLARME MORSE - Alta pressione non attiva su morsa 15
.

Language=English
ALLARME MORSE - Alta pressione non attiva su morsa 15
.

MessageId=19984 Facility=Plc Severity=Error SymbolicName=VIS_BASSA_NOAVA_A_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera bassa non aperta (avanzamento) : controlla il sensore
.

Language=English
ALLARME RIPARI - Time Out Visiera bassa non aperta (avanzamento) : controlla il sensore
.

MessageId=19985 Facility=Plc Severity=Error SymbolicName=VIS_BASSA_NOAVA_B_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera bassa non aperta (avanzamento) : controlla la EV
.

Language=English
ALLARME RIPARI - Time Out Visiera bassa non aperta (avanzamento) : controlla la EV
.

MessageId=19986 Facility=Plc Severity=Error SymbolicName=VIS_BASSA_NOIND_A_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera bassa non chiusa (arretramento) : controlla il sensore
.

Language=English
ALLARME RIPARI - Time Out Visiera bassa non chiusa (arretramento) : controlla il sensore
.

MessageId=19987 Facility=Plc Severity=Error SymbolicName=VIS_BASSA_NOIND_B_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera bassa non chiusa (arretramento) : controlla la EV
.

Language=English
ALLARME RIPARI - Time Out Visiera bassa non chiusa (arretramento) : controlla la EV
.

MessageId=19988 Facility=Plc Severity=Error SymbolicName=VIS_BASSA_DISFC_AL
Language=Italian
ALLARME RIPARI - Disfunzione finecorsa visiera bassa
.

Language=English
ALLARME RIPARI - Disfunzione finecorsa visiera bassa
.

MessageId=19994 Facility=Plc Severity=Error SymbolicName=VIS_RIP_NODIS_A_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera alta non aperta (discesa) : controlla il sensore
.

Language=English
ALLARME RIPARI - Time Out Visiera alta non aperta (discesa) : controlla il sensore
.

MessageId=19995 Facility=Plc Severity=Error SymbolicName=VIS_RIP_NODIS_B_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera alta non aperta (discesa) : controlla la EV
.

Language=English
ALLARME RIPARI - Time Out Visiera alta non aperta (discesa) : controlla la EV
.

MessageId=19996 Facility=Plc Severity=Error SymbolicName=VIS_RIP_NOSAL_A_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera alta non chiusa (salita) : controlla il sensore
.

Language=English
ALLARME RIPARI - Time Out Visiera alta non chiusa (salita) : controlla il sensore
.

MessageId=19997 Facility=Plc Severity=Error SymbolicName=VIS_RIP_NOSAL_B_AL
Language=Italian
ALLARME RIPARI - Time Out Visiera alta non chiusa (salita) : controlla la EV
.

Language=English
ALLARME RIPARI - Time Out Visiera alta non chiusa (salita) : controlla la EV
.

MessageId=20002 Facility=Plc Severity=Error SymbolicName=TOOL_01_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T1 rotto
.

Language=English
ALLARME UTENSILI - Utensile T1 rotto
.

MessageId=20003 Facility=Plc Severity=Error SymbolicName=TOOL_02_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T2 rotto
.

Language=English
ALLARME UTENSILI - Utensile T2 rotto
.

MessageId=20004 Facility=Plc Severity=Error SymbolicName=TOOL_03_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T3 rotto
.

Language=English
ALLARME UTENSILI - Utensile T3 rotto
.

MessageId=20005 Facility=Plc Severity=Error SymbolicName=TOOL_04_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T4 rotto
.

Language=English
ALLARME UTENSILI - Utensile T4 rotto
.

MessageId=20006 Facility=Plc Severity=Error SymbolicName=TOOL_05_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T5 rotto
.

Language=English
ALLARME UTENSILI - Utensile T5 rotto
.

MessageId=20007 Facility=Plc Severity=Error SymbolicName=TOOL_06_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T6 rotto
.

Language=English
ALLARME UTENSILI - Utensile T6 rotto
.

MessageId=20008 Facility=Plc Severity=Error SymbolicName=TOOL_07_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T7 rotto
.

Language=English
ALLARME UTENSILI - Utensile T7 rotto
.

MessageId=20009 Facility=Plc Severity=Error SymbolicName=TOOL_08_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T8 rotto
.

Language=English
ALLARME UTENSILI - Utensile T8 rotto
.

MessageId=20010 Facility=Plc Severity=Error SymbolicName=TOOL_09_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T9 rotto
.

Language=English
ALLARME UTENSILI - Utensile T9 rotto
.

MessageId=20011 Facility=Plc Severity=Error SymbolicName=TOOL_10_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T10 rotto
.

Language=English
ALLARME UTENSILI - Utensile T10 rotto
.

MessageId=20012 Facility=Plc Severity=Error SymbolicName=TOOL_11_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T11 rotto
.

Language=English
ALLARME UTENSILI - Utensile T11 rotto
.

MessageId=20013 Facility=Plc Severity=Error SymbolicName=TOOL_12_MORTO_AL
Language=Italian
ALLARME UTENSILI - Utensile T12 rotto
.

Language=English
ALLARME UTENSILI - Utensile T12 rotto
.

MessageId=20014 Facility=Plc Severity=Error SymbolicName=NOT_ALIVE_DRILL_AL
Language=Italian
ALLARME UTENSILI - Drill not alive
.

Language=English
ALLARME UTENSILI - Drill not alive
.

MessageId=20016 Facility=Plc Severity=Error SymbolicName=MORSE_NO_AGG_GANTRY_AL
Language=Italian
ALLARME GANTRY - Morse non agganciate in gantry
.

Language=English
ALLARME GANTRY - Morse non agganciate in gantry
.

MessageId=20017 Facility=Plc Severity=Error SymbolicName=MORSE_NO_SGAN_GANTRY_AL
Language=Italian
ALLARME GANTRY - Morse non sganciate in gantry
.

Language=English
ALLARME GANTRY - Morse non sganciate in gantry
.

MessageId=20018 Facility=Plc Severity=Error SymbolicName=POSIZ_MORSE_NOT_OK_AL
Language=Italian
ALLARME ASSI MORSE - Posizioni assi morse non congruenti (posizioni encoder perse)
.

Language=English
ALLARME ASSI MORSE - Posizioni assi morse non congruenti (posizioni encoder perse)
.

MessageId=20019 Facility=Plc Severity=Error SymbolicName=ERR_UT_IN_MEM_AL
Language=Italian
ALLARME CAMBIO UTENSILI - Incongruenza tra utensile teoricamente presente e sensore di presenza utensile
.

Language=English
ALLARME CAMBIO UTENSILI - Incongruenza tra utensile teoricamente presente e sensore di presenza utensile
.

MessageId=20020 Facility=Plc Severity=Error SymbolicName=TOOL_NOK_AL
Language=Italian
ALLARME CONTROLLO UTENSILE - Utensile rotto
.

Language=English
ALLARME CONTROLLO UTENSILE - Utensile rotto
.

MessageId=20021 Facility=Plc Severity=Error SymbolicName=CKTOOL_NOK_AL
Language=Italian
ALLARME CONTROLLO UTENSILE - Dispositivo verifica integrità utensile non funzionante
.

Language=English
ALLARME CONTROLLO UTENSILE - Dispositivo verifica integrità utensile non funzionante
.

MessageId=20038 Facility=Plc Severity=Error SymbolicName=EXC_POS_M10_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M10 in extracorsa positivo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M10 in extracorsa positivo
.

MessageId=20039 Facility=Plc Severity=Error SymbolicName=EXC_NEG_M10_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M10 in extracorsa negativo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M10 in extracorsa negativo
.

MessageId=20040 Facility=Plc Severity=Error SymbolicName=EXC_POS_M11_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M11 in extracorsa positivo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M11 in extracorsa positivo
.

MessageId=20041 Facility=Plc Severity=Error SymbolicName=EXC_NEG_M11_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M11 in extracorsa negativo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M11 in extracorsa negativo
.

MessageId=20042 Facility=Plc Severity=Error SymbolicName=EXC_POS_M12_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M12 in extracorsa positivo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M12 in extracorsa positivo
.

MessageId=20043 Facility=Plc Severity=Error SymbolicName=EXC_NEG_M12_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M12 in extracorsa negativo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M12 in extracorsa negativo
.

MessageId=20044 Facility=Plc Severity=Error SymbolicName=EXC_POS_M13_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M13 in extracorsa positivo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M13 in extracorsa positivo
.

MessageId=20045 Facility=Plc Severity=Error SymbolicName=EXC_NEG_M13_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M13 in extracorsa negativo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M13 in extracorsa negativo
.

MessageId=20046 Facility=Plc Severity=Error SymbolicName=EXC_POS_M14_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M14 in extracorsa positivo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M14 in extracorsa positivo
.

MessageId=20047 Facility=Plc Severity=Error SymbolicName=EXC_NEG_M14_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M14 in extracorsa negativo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M14 in extracorsa negativo
.

MessageId=20048 Facility=Plc Severity=Error SymbolicName=EXC_POS_M15_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M15 in extracorsa positivo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M15 in extracorsa positivo
.

MessageId=20049 Facility=Plc Severity=Error SymbolicName=EXC_NEG_M15_AL
Language=Italian
ALLARME ASSE MORSA - Asse Morsa M15 in extracorsa negativo
.

Language=English
ALLARME ASSE MORSA - Asse Morsa M15 in extracorsa negativo
.

MessageId=20075 Facility=Plc Severity=Error SymbolicName=INIT_ERROR_AL
Language=Italian
ALLARME CONFIGURAZIONE - Errore inizializzazione variabili PLC
.

Language=English
ALLARME CONFIGURAZIONE - Errore inizializzazione variabili PLC
.

MessageId=20076 Facility=Plc Severity=Error SymbolicName=CONFMAC_ERROR_AL
Language=Italian
ALLARME CONFIGURAZIONE - Errore lettura confmac
.

Language=English
ALLARME CONFIGURAZIONE - Errore lettura confmac
.

MessageId=20077 Facility=Plc Severity=Error SymbolicName=MGPILOT_ERROR_AL
Language=Italian
ALLARME CONFIGURAZIONE - Errore caricamento funzioni manuali (MGPilot)
.

Language=English
ALLARME CONFIGURAZIONE - Errore caricamento funzioni manuali (MGPilot)
.

MessageId=20078 Facility=Plc Severity=Error SymbolicName=REMCTRL_ERROR_AL
Language=Italian
ALLARME CONFIGURAZIONE - Errore caricamento funzioni manuali (REM_CTRL)
.

Language=English
ALLARME CONFIGURAZIONE - Errore caricamento funzioni manuali (REM_CTRL)
.

MessageId=20080 Facility=Plc Severity=Error SymbolicName=BATTERIA_LOWLEVEL_ASSE_X_AL
Language=Italian
ALLARME ASSE X - Livello Batteria encoder basso
.

Language=English
ALLARME ASSE X - Livello Batteria encoder basso
.

MessageId=20081 Facility=Plc Severity=Error SymbolicName=BATTERIA_LOWLEVEL_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - Livello Batteria encoder basso
.

Language=English
ALLARME ASSE Y - Livello Batteria encoder basso
.

MessageId=20082 Facility=Plc Severity=Error SymbolicName=BATTERIA_LOWLEVEL_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - Livello Batteria encoder basso
.

Language=English
ALLARME ASSE Z - Livello Batteria encoder basso
.

MessageId=20083 Facility=Plc Severity=Error SymbolicName=BATTERIA_LOWLEVEL_ASSE_A_AL
Language=Italian
ALLARME ASSE A - Livello Batteria encoder basso
.

Language=English
ALLARME ASSE A - Livello Batteria encoder basso
.

MessageId=20084 Facility=Plc Severity=Error SymbolicName=BATTERIA_LOWLEVEL_ASSE_W_AL
Language=Italian
ALLARME ASSE W - Livello Batteria encoder basso
.

Language=English
ALLARME ASSE W - Livello Batteria encoder basso
.

MessageId=20087 Facility=Plc Severity=Error SymbolicName=QUOTA_ENCODER_PERSA_ASSE_X_AL
Language=Italian
ALLARME ASSE X - Livello Batteria encoder basso e posizione assoluta persa
.

Language=English
ALLARME ASSE X - Livello Batteria encoder basso e posizione assoluta persa
.

MessageId=20088 Facility=Plc Severity=Error SymbolicName=QUOTA_ENCODER_PERSA_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - Livello Batteria encoder basso e posizione assoluta persa
.

Language=English
ALLARME ASSE Y - Livello Batteria encoder basso e posizione assoluta persa
.

MessageId=20089 Facility=Plc Severity=Error SymbolicName=QUOTA_ENCODER_PERSA_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - Livello Batteria encoder basso e posizione assoluta persa
.

Language=English
ALLARME ASSE Z - Livello Batteria encoder basso e posizione assoluta persa
.

MessageId=20090 Facility=Plc Severity=Error SymbolicName=QUOTA_ENCODER_PERSA_ASSE_A_AL
Language=Italian
ALLARME ASSE A - Livello Batteria encoder basso e posizione assoluta persa
.

Language=English
ALLARME ASSE A - Livello Batteria encoder basso e posizione assoluta persa
.

MessageId=20091 Facility=Plc Severity=Error SymbolicName=QUOTA_ENCODER_PERSA_ASSE_W_AL
Language=Italian
ALLARME ASSE W - Livello Batteria encoder basso e posizione assoluta persa
.

Language=English
ALLARME ASSE W - Livello Batteria encoder basso e posizione assoluta persa
.

MessageId=20096 Facility=Plc Severity=Error SymbolicName=MT_OVERFLOW_ASSE_X_AL
Language=Italian
ALLARME ASSE X - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

Language=English
ALLARME ASSE X - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

MessageId=20097 Facility=Plc Severity=Error SymbolicName=MT_OVERFLOW_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

Language=English
ALLARME ASSE Y - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

MessageId=20098 Facility=Plc Severity=Error SymbolicName=MT_OVERFLOW_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

Language=English
ALLARME ASSE Z - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

MessageId=20099 Facility=Plc Severity=Error SymbolicName=MT_OVERFLOW_ASSE_A_AL
Language=Italian
ALLARME ASSE A - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

Language=English
ALLARME ASSE A - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

MessageId=20100 Facility=Plc Severity=Error SymbolicName=MT_OVERFLOW_ASSE_W_AL
Language=Italian
ALLARME ASSE W - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

Language=English
ALLARME ASSE W - Overflow sui giri massimi del multiturn dell'encoder assoluto
.

MessageId=20103 Facility=Plc Severity=Error SymbolicName=POS_ENCODER_NOINIT_ASSE_X_AL
Language=Italian
ALLARME ASSE X - Posizione assoluta encoder non inizializzata
.

Language=English
ALLARME ASSE X - Posizione assoluta encoder non inizializzata
.

MessageId=20104 Facility=Plc Severity=Error SymbolicName=POS_ENCODER_NOINIT_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - Posizione assoluta encoder non inizializzata
.

Language=English
ALLARME ASSE Y - Posizione assoluta encoder non inizializzata
.

MessageId=20105 Facility=Plc Severity=Error SymbolicName=POS_ENCODER_NOINIT_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - Posizione assoluta encoder non inizializzata
.

Language=English
ALLARME ASSE Z - Posizione assoluta encoder non inizializzata
.

MessageId=20106 Facility=Plc Severity=Error SymbolicName=POS_ENCODER_NOINIT_ASSE_A_AL
Language=Italian
ALLARME ASSE A - Posizione assoluta encoder non inizializzata
.

Language=English
ALLARME ASSE A - Posizione assoluta encoder non inizializzata
.

MessageId=20107 Facility=Plc Severity=Error SymbolicName=POS_ENCODER_NOINIT_ASSE_W_AL
Language=Italian
ALLARME ASSE W - Posizione assoluta encoder non inizializzata
.

Language=English
ALLARME ASSE W - Posizione assoluta encoder non inizializzata
.

MessageId=20112 Facility=Plc Severity=Error SymbolicName=CLEAR_ENCODER_ERROR_ASSE_X_AL
Language=Italian
ALLARME ASSE X - Funzione di reset encoder assoluto non riuscita
.

Language=English
ALLARME ASSE X - Funzione di reset encoder assoluto non riuscita
.

MessageId=20113 Facility=Plc Severity=Error SymbolicName=CLEAR_ENCODER_ERROR_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - Funzione di reset encoder assoluto non riuscita
.

Language=English
ALLARME ASSE Y - Funzione di reset encoder assoluto non riuscita
.

MessageId=20114 Facility=Plc Severity=Error SymbolicName=CLEAR_ENCODER_ERROR_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - Funzione di reset encoder assoluto non riuscita
.

Language=English
ALLARME ASSE Z - Funzione di reset encoder assoluto non riuscita
.

MessageId=20115 Facility=Plc Severity=Error SymbolicName=CLEAR_ENCODER_ERROR_ASSE_A_AL
Language=Italian
ALLARME ASSE A - Funzione di reset encoder assoluto non riuscita
.

Language=English
ALLARME ASSE A - Funzione di reset encoder assoluto non riuscita
.

MessageId=20116 Facility=Plc Severity=Error SymbolicName=CLEAR_ENCODER_ERROR_ASSE_W_AL
Language=Italian
ALLARME ASSE W - Funzione di reset encoder assoluto non riuscita
.

Language=English
ALLARME ASSE W - Funzione di reset encoder assoluto non riuscita
.

MessageId=20119 Facility=Plc Severity=Error SymbolicName=UNDER_VOLTAGE_ASSE_X_AL
Language=Italian
ALLARME ASSE X - La tensione DC del circuito principale è più bassa del valore standard
.

Language=English
ALLARME ASSE X - La tensione DC del circuito principale è più bassa del valore standard
.

MessageId=20120 Facility=Plc Severity=Error SymbolicName=UNDER_VOLTAGE_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - La tensione DC del circuito principale è più bassa del valore standard
.

Language=English
ALLARME ASSE Y - La tensione DC del circuito principale è più bassa del valore standard
.

MessageId=20121 Facility=Plc Severity=Error SymbolicName=UNDER_VOLTAGE_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - La tensione DC del circuito principale è più bassa del valore standard
.

Language=English
ALLARME ASSE Z - La tensione DC del circuito principale è più bassa del valore standard
.

MessageId=20122 Facility=Plc Severity=Error SymbolicName=UNDER_VOLTAGE_ASSE_A_AL
Language=Italian
ALLARME ASSE A - La tensione DC del circuito principale è più bassa del valore standard
.

Language=English
ALLARME ASSE A - La tensione DC del circuito principale è più bassa del valore standard
.

MessageId=20123 Facility=Plc Severity=Error SymbolicName=UNDER_VOLTAGE_ASSE_W_AL
Language=Italian
ALLARME ASSE W - La tensione DC del circuito principale è più bassa del valore standard
.

Language=English
ALLARME ASSE W - La tensione DC del circuito principale è più bassa del valore standard
.

MessageId=20128 Facility=Plc Severity=Error SymbolicName=MOTORE_SENZA_FASE_ASSE_X_AL
Language=Italian
ALLARME ASSE X - Mancanza di una fase in ingresso
.

Language=English
ALLARME ASSE X - Mancanza di una fase in ingresso
.

MessageId=20129 Facility=Plc Severity=Error SymbolicName=MOTORE_SENZA_FASE_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - Mancanza di una fase in ingresso
.

Language=English
ALLARME ASSE Y - Mancanza di una fase in ingresso
.

MessageId=20130 Facility=Plc Severity=Error SymbolicName=MOTORE_SENZA_FASE_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - Mancanza di una fase in ingresso
.

Language=English
ALLARME ASSE Z - Mancanza di una fase in ingresso
.

MessageId=20131 Facility=Plc Severity=Error SymbolicName=MOTORE_SENZA_FASE_ASSE_A_AL
Language=Italian
ALLARME ASSE A - Mancanza di una fase in ingresso
.

Language=English
ALLARME ASSE A - Mancanza di una fase in ingresso
.

MessageId=20132 Facility=Plc Severity=Error SymbolicName=MOTORE_SENZA_FASE_ASSE_W_AL
Language=Italian
ALLARME ASSE W - Mancanza di una fase in ingresso
.

Language=English
ALLARME ASSE W - Mancanza di una fase in ingresso
.

MessageId=20135 Facility=Plc Severity=Error SymbolicName=OVERSHOOT_SPEED_ASSE_X_AL
Language=Italian
ALLARME ASSE X - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

Language=English
ALLARME ASSE X - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

MessageId=20136 Facility=Plc Severity=Error SymbolicName=OVERSHOOT_SPEED_ASSE_Y_AL
Language=Italian
ALLARME ASSE Y - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

Language=English
ALLARME ASSE Y - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

MessageId=20137 Facility=Plc Severity=Error SymbolicName=OVERSHOOT_SPEED_ASSE_Z_AL
Language=Italian
ALLARME ASSE Z - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

Language=English
ALLARME ASSE Z - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

MessageId=20138 Facility=Plc Severity=Error SymbolicName=OVERSHOOT_SPEED_ASSE_A_AL
Language=Italian
ALLARME ASSE A - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

Language=English
ALLARME ASSE A - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

MessageId=20139 Facility=Plc Severity=Error SymbolicName=OVERSHOOT_SPEED_ASSE_W_AL
Language=Italian
ALLARME ASSE W - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

Language=English
ALLARME ASSE W - La velocità del motore è in overshoot rispetto al valore massimo di targa
.

MessageId=20144 Facility=Plc Severity=Error SymbolicName=PLC_IEC_NOT_ALIVE_AL
Language=Italian
ALLARME PLC IEC - PLC IEC timeout di not alive
.

Language=English
ALLARME PLC IEC - PLC IEC timeout di not alive
.

MessageId=20145 Facility=Plc Severity=Error SymbolicName=INVERTER_0_COM_ERROR_AL
Language=Italian
ALLARME PLC IEC - Errore di comunicazione COM con inverter 0
.

Language=English
ALLARME PLC IEC - Errore di comunicazione COM con inverter 0
.

MessageId=20160 Facility=Plc Severity=Error SymbolicName=ASSE_0_COM_ERROR_AL
Language=Italian
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse X
.

Language=English
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse X
.

MessageId=20161 Facility=Plc Severity=Error SymbolicName=ASSE_1_COM_ERROR_AL
Language=Italian
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse Y
.

Language=English
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse Y
.

MessageId=20162 Facility=Plc Severity=Error SymbolicName=ASSE_2_COM_ERROR_AL
Language=Italian
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse Z
.

Language=English
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse Z
.

MessageId=20163 Facility=Plc Severity=Error SymbolicName=ASSE_3_COM_ERROR_AL
Language=Italian
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse A
.

Language=English
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse A
.

MessageId=20164 Facility=Plc Severity=Error SymbolicName=ASSE_4_COM_ERROR_AL
Language=Italian
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse W
.

Language=English
ALLARME PLC IEC - Errore di comunicazione COM con azionamento asse W
.

MessageId=20239 Facility=Plc Severity=Error SymbolicName=ALARM_LAST_AL
Language=Italian
Ultimo allarme disponibile
.

Language=English
Ultimo allarme disponibile
.



;//-- Messaggi macchina -------------------------------------------------------
;//----------------------------------------------------------------------------
MessageId=20240 Facility=Plc Severity=Warning SymbolicName=MESSAGE_FIRST_MS
Language=Italian
Primo messaggio da non usare
.

Language=English
Primo messaggio da non usare
.

MessageId=20241 Facility=Plc Severity=Warning SymbolicName=ASSI_NORIF_MS
Language=Italian
MESSAGGIO OPERATORE - Assi non riferiti
.

Language=English
MESSAGGIO OPERATORE - Assi non riferiti
.

MessageId=20242 Facility=Plc Severity=Warning SymbolicName=PC_HOLD_MS
Language=Italian
MESSAGGIO OPERATORE - Macchina in HOLD
.

Language=English
MESSAGGIO OPERATORE - Macchina in HOLD
.

MessageId=20243 Facility=Plc Severity=Warning SymbolicName=UTSCON_MS
Language=Italian
MESSAGGIO OPERATORE - Utensile sconosciuto su mandrino
.

Language=English
MESSAGGIO OPERATORE - Utensile sconosciuto su mandrino
.

MessageId=20244 Facility=Plc Severity=Warning SymbolicName=POT_ZERO_MS
Language=Italian
MESSAGGIO OPERATORE - Potenziometro a Zero in Ciclo Automatico
.

Language=English
MESSAGGIO OPERATORE - Potenziometro a Zero in Ciclo Automatico
.

MessageId=20245 Facility=Plc Severity=Warning SymbolicName=MAGUT_HOLD_MS
Language=Italian
MESSAGGIO OPERATORE - Macchina in HOLD da Magazzino
.

Language=English
MESSAGGIO OPERATORE - Macchina in HOLD da Magazzino
.

MessageId=20246 Facility=Plc Severity=Warning SymbolicName=MORSE_SX_HOLD_MS
Language=Italian
MESSAGGIO OPERATORE - Macchina in HOLD da Morse Zona SX
.

Language=English
MESSAGGIO OPERATORE - Macchina in HOLD da Morse Zona SX
.

MessageId=20247 Facility=Plc Severity=Warning SymbolicName=MORSE_DX_HOLD_MS
Language=Italian
MESSAGGIO OPERATORE - Macchina in HOLD da Morse Zona DX
.

Language=English
MESSAGGIO OPERATORE - Macchina in HOLD da Morse Zona DX
.

MessageId=20248 Facility=Plc Severity=Warning SymbolicName=FEEDHOLD_MAND_MS
Language=Italian
MESSAGGIO OPERATORE - Macchina in HOLD da Mandrino
.

Language=English
MESSAGGIO OPERATORE - Macchina in HOLD da Mandrino
.

MessageId=20249 Facility=Plc Severity=Warning SymbolicName=RIPARI_HOLD_MS
Language=Italian
MESSAGGIO OPERATORE - Macchina in HOLD da Ripari
.

Language=English
MESSAGGIO OPERATORE - Macchina in HOLD da Ripari
.

MessageId=20250 Facility=Plc Severity=Warning SymbolicName=COLL_MAGUT_CARTER_SX_MS
Language=Italian
MESSAGGIO OPERATORE - Magazzino in potenziale collisione con carter laterale SX della macchina
.

Language=English
MESSAGGIO OPERATORE - Magazzino in potenziale collisione con carter laterale SX della macchina
.

MessageId=20251 Facility=Plc Severity=Warning SymbolicName=MAN_COLL_MAG_MS
Language=Italian
MESSAGGIO OPERATORE - Mandrino in potenziale collisione con magazzino
.

Language=English
MESSAGGIO OPERATORE - Mandrino in potenziale collisione con magazzino
.

MessageId=20252 Facility=Plc Severity=Warning SymbolicName=FATM_MS
Language=Italian
MESSAGGIO OPERATORE - Blocco Esecuzioni FATM Attivo
.

Language=English
MESSAGGIO OPERATORE - Blocco Esecuzioni FATM Attivo
.

MessageId=20253 Facility=Plc Severity=Warning SymbolicName=HOLD_AP_CH_RIPARI_MS
Language=Italian
MESSAGGIO OPERATORE - Hold apertura / chiusura ripari anteriori da posizione assi Y, A, C
.

Language=English
MESSAGGIO OPERATORE - Hold apertura / chiusura ripari anteriori da posizione assi Y, A, C
.

MessageId=20254 Facility=Plc Severity=Warning SymbolicName=POSSIBILE_CORTO_MS
Language=Italian
MESSAGGIO OPERATORE - Attenzione : Possibile corto sugli ingressi non ritentivi
.

Language=English
MESSAGGIO OPERATORE - Attenzione : Possibile corto sugli ingressi non ritentivi
.

MessageId=20255 Facility=Plc Severity=Warning SymbolicName=COLL_RIPARI_Y_A_MS
Language=Italian
MESSAGGIO OPERATORE - Potenziale collisione fra utensile e riparo anteriore
.

Language=English
MESSAGGIO OPERATORE - Potenziale collisione fra utensile e riparo anteriore
.

MessageId=20256 Facility=Plc Severity=Warning SymbolicName=SBLOC_UT_RIP_AP_MS
Language=Italian
MESSAGGIO OPERATORE - Sbloc. Ut. diretto possibile solo con ripari bassi
.

Language=English
MESSAGGIO OPERATORE - Sbloc. Ut. diretto possibile solo con ripari bassi
.

MessageId=20265 Facility=Plc Severity=Warning SymbolicName=INGRASS_DISAB_MS
Language=Italian
MESSAGGIO OPERATORE - Ingrassaggio Automatico disabilitato
.

Language=English
MESSAGGIO OPERATORE - Ingrassaggio Automatico disabilitato
.

MessageId=20267 Facility=Plc Severity=Warning SymbolicName=NO_OUT_MAC_ABIL_MS
Language=Italian
MESSAGGIO OPERATORE - Assenza uscite pericolose con centralina di sicurezza ok
.

Language=English
MESSAGGIO OPERATORE - Assenza uscite pericolose con centralina di sicurezza ok
.

MessageId=20270 Facility=Plc Severity=Warning SymbolicName=CNT_BRIDGE_STATE_INFO_INIT_DONE_MS
Language=Italian
MESSAGGIO OPERATORE - Inizializzazione password Bridge fatta, riavviare
.

Language=English
MESSAGGIO OPERATORE - Inizializzazione password Bridge fatta, riavviare
.

MessageId=20271 Facility=Plc Severity=Warning SymbolicName=CONTATORI_BRIDGE_SAVE_FILE_MS
Language=Italian
MESSAGGIO OPERATORE - Errore scrittura file contatori
.

Language=English
MESSAGGIO OPERATORE - Errore scrittura file contatori
.

MessageId=20317 Facility=Plc Severity=Warning SymbolicName=MGPILOT_ERROR_MS
Language=Italian
MESSAGGIO OPERATORE - Errore caricamento funzioni manuali (MGPilot)
.

Language=English
MESSAGGIO OPERATORE - Errore caricamento funzioni manuali (MGPilot)
.

MessageId=20318 Facility=Plc Severity=Warning SymbolicName=REMCTRL_ERROR_MS
Language=Italian
MESSAGGIO OPERATORE - Errore caricamento funzioni manuali (REM_CTRL)
.

Language=English
MESSAGGIO OPERATORE - Errore caricamento funzioni manuali (REM_CTRL)
.

MessageId=20320 Facility=Plc Severity=Warning SymbolicName=PRE_OVERLOAD_ASSE_X_MS
Language=Italian
MESSAGGIO OPERATORE - Motore asse X in preallarme da sovraccarico
.

Language=English
MESSAGGIO OPERATORE - Motore asse X in preallarme da sovraccarico
.

MessageId=20321 Facility=Plc Severity=Warning SymbolicName=PRE_OVERLOAD_ASSE_Y_MS
Language=Italian
MESSAGGIO OPERATORE - Motore asse Y in preallarme da sovraccarico
.

Language=English
MESSAGGIO OPERATORE - Motore asse Y in preallarme da sovraccarico
.

MessageId=20322 Facility=Plc Severity=Warning SymbolicName=PRE_OVERLOAD_ASSE_Z_MS
Language=Italian
MESSAGGIO OPERATORE - Motore asse Z in preallarme da sovraccarico
.

Language=English
MESSAGGIO OPERATORE - Motore asse Z in preallarme da sovraccarico
.

MessageId=20323 Facility=Plc Severity=Warning SymbolicName=PRE_OVERLOAD_ASSE_A_MS
Language=Italian
MESSAGGIO OPERATORE - Motore asse A in preallarme da sovraccarico
.

Language=English
MESSAGGIO OPERATORE - Motore asse A in preallarme da sovraccarico
.

MessageId=20324 Facility=Plc Severity=Warning SymbolicName=PRE_OVERLOAD_ASSE_W_MS
Language=Italian
MESSAGGIO OPERATORE - Motore asse W in preallarme da sovraccarico
.

Language=English
MESSAGGIO OPERATORE - Motore asse W in preallarme da sovraccarico
.

MessageId=20328 Facility=Plc Severity=Warning SymbolicName=QUOTA_ENCODER_PERSA_ASSE_X_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse X basso e posizione assoluta persa
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse X basso e posizione assoluta persa
.

MessageId=20329 Facility=Plc Severity=Warning SymbolicName=QUOTA_ENCODER_PERSA_ASSE_Y_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse Y basso e posizione assoluta persa
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse Y basso e posizione assoluta persa
.

MessageId=20330 Facility=Plc Severity=Warning SymbolicName=QUOTA_ENCODER_PERSA_ASSE_Z_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse Z basso e posizione assoluta persa
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse Z basso e posizione assoluta persa
.

MessageId=20331 Facility=Plc Severity=Warning SymbolicName=QUOTA_ENCODER_PERSA_ASSE_A_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse A basso e posizione assoluta persa
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse A basso e posizione assoluta persa
.

MessageId=20332 Facility=Plc Severity=Warning SymbolicName=QUOTA_ENCODER_PERSA_ASSE_W_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse W basso e posizione assoluta persa
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse W basso e posizione assoluta persa
.

MessageId=20336 Facility=Plc Severity=Warning SymbolicName=BATTERIA_LOWLEVEL_ASSE_X_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse X basso
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse X basso
.

MessageId=20337 Facility=Plc Severity=Warning SymbolicName=BATTERIA_LOWLEVEL_ASSE_Y_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse Y basso
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse Y basso
.

MessageId=20338 Facility=Plc Severity=Warning SymbolicName=BATTERIA_LOWLEVEL_ASSE_Z_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse Z basso
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse Z basso
.

MessageId=20339 Facility=Plc Severity=Warning SymbolicName=BATTERIA_LOWLEVEL_ASSE_A_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse A basso
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse A basso
.

MessageId=20340 Facility=Plc Severity=Warning SymbolicName=BATTERIA_LOWLEVEL_ASSE_W_MS
Language=Italian
MESSAGGIO OPERATORE - Livello Batteria encoder asse W basso
.

Language=English
MESSAGGIO OPERATORE - Livello Batteria encoder asse W basso
.

MessageId=20344 Facility=Plc Severity=Warning SymbolicName=POS_ENCODER_NOINIT_ASSE_X_MS
Language=Italian
MESSAGGIO OPERATORE - Posizione assoluta encoder asse X non inizializzata
.

Language=English
MESSAGGIO OPERATORE - Posizione assoluta encoder asse X non inizializzata
.

MessageId=20345 Facility=Plc Severity=Warning SymbolicName=POS_ENCODER_NOINIT_ASSE_Y_MS
Language=Italian
MESSAGGIO OPERATORE - Posizione assoluta encoder asse Y non inizializzata
.

Language=English
MESSAGGIO OPERATORE - Posizione assoluta encoder asse Y non inizializzata
.

MessageId=20346 Facility=Plc Severity=Warning SymbolicName=POS_ENCODER_NOINIT_ASSE_Z_MS
Language=Italian
MESSAGGIO OPERATORE - Posizione assoluta encoder asse Z non inizializzata
.

Language=English
MESSAGGIO OPERATORE - Posizione assoluta encoder asse Z non inizializzata
.

MessageId=20347 Facility=Plc Severity=Warning SymbolicName=POS_ENCODER_NOINIT_ASSE_A_MS
Language=Italian
MESSAGGIO OPERATORE - Posizione assoluta encoder asse A non inizializzata
.

Language=English
MESSAGGIO OPERATORE - Posizione assoluta encoder asse A non inizializzata
.

MessageId=20348 Facility=Plc Severity=Warning SymbolicName=POS_ENCODER_NOINIT_ASSE_W_MS
Language=Italian
MESSAGGIO OPERATORE - Posizione assoluta encoder asse W non inizializzata
.

Language=English
MESSAGGIO OPERATORE - Posizione assoluta encoder asse W non inizializzata
.

MessageId=20352 Facility=Plc Severity=Warning SymbolicName=MT_OVERFLOW_ASSE_X_MS
Language=Italian
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse X
.

Language=English
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse X
.

MessageId=20353 Facility=Plc Severity=Warning SymbolicName=MT_OVERFLOW_ASSE_Y_MS
Language=Italian
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse Y
.

Language=English
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse Y
.

MessageId=20354 Facility=Plc Severity=Warning SymbolicName=MT_OVERFLOW_ASSE_Z_MS
Language=Italian
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse Z
.

Language=English
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse Z
.

MessageId=20355 Facility=Plc Severity=Warning SymbolicName=MT_OVERFLOW_ASSE_A_MS
Language=Italian
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse A
.

Language=English
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse A
.

MessageId=20356 Facility=Plc Severity=Warning SymbolicName=MT_OVERFLOW_ASSE_W_MS
Language=Italian
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse W
.

Language=English
MESSAGGIO OPERATORE - Overflow sui giri massimi del multiturn dell'encoder assoluto asse W
.

MessageId=20415 Facility=Plc Severity=Warning SymbolicName=MESSAGE_LAST_MS
Language=Italian
Ultimo messaggio disponibile
.

Language=English
Ultimo messaggio disponibile
.

;#endif // MESSAGES_H_INCLUDED
