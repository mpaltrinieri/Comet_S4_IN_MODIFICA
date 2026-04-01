@ECHO OFF

REM  COPIA DI ALLARMI, MESSAGGI E DESCRIZIONI I/O DI SIOMAG/HMI SULLA MACCHINA CONNESSA VIA RETE  (IN "Y:\isac\exe\").

REM  LINGUE DRILL/MG_PILOT:
REM  1) PULIRE EVENTUALMENTE DA STRINGHE NON NECESSARIE  C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\CNC.MSG 
REM  2) COPIAR MANUALMENTE CNC.MSG DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\"   A  "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\"
REM  3) COPIAR LA CARTELLA LINGUE DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE"         A  "C:\isac\LINGUE"  (DELLA MACCHINA)
REM  4) COPIAR *.*                DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\*.*"   A  "D:\isac\Msg\"  (DELLA MACCHINA)  (Poi sarà fatto da Language_Setup)

REM  All'avvio il CNC copia plcres.dll da C:\plc\plc\ a "D:\isac\exe\resdll"  (solo se non trova un file con questo nome in D:\isac\exe\resdll)
REM  se si cancella C:\plc\plc\plcres.dll  il CNC cancella anche  D:\isac\exe\resdll\plcres.dll

REM COPIA IN MACCHINA ///////////////////////////////////////////////////////////////////////////////////////////////

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuCN\plcres.dll"   "X:\plc\plc\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuCN\plcres.dll"   "Y:\isac\exe\resdll\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\iodescr.xml"    "Y:\isac\usertar\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsen.dll"       "Y:\isac\exe\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsfr.dll"       "Y:\isac\exe\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsit.dll"       "Y:\isac\exe\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rssp.dll"       "Y:\isac\exe\"


REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuCN\plcres.dll"   "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\iodescr.xml"    "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsen.dll"       "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsfr.dll"       "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsit.dll"       "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rssp.dll"       "Y:\_DLL\"


REM COPIA SU CHIAVE USB ///////////////////////////////////////////////////////////////////////////////////////////////

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuCN\plcres.dll"   "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\iodescr.xml"    "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsen.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsfr.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rsit.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuCN\rssp.dll"       "G:\_______XXX\"

REM PAUSE

REM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
