@ECHO OFF

rem comando:	"$(SolutionDir)\BAT\EttoreSimuCN__MEX.BAT"

REM  COPIA DI ALLARMI, MESSAGGI E DESCRIZIONI I/O DI SIOMAG/HMI SULLA MACCHINA CONNESSA VIA RETE  (IN "Y:\isac\exe\").

REM  LINGUE DRILL/MG_PILOT:
REM  1) PULIRE EVENTUALMENTE DA STRINGHE NON NECESSARIE  C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\CNC.MSG 
REM  2) COPIAR MANUALMENTE CNC.MSG DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\"   A  "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\"
REM  3) COPIAR LA CARTELLA LINGUE DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE"         A  "C:\isac\LINGUE"  (DELLA MACCHINA)
REM  4) COPIAR *.*                DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\*.*"   A  "D:\isac\Msg\"  (DELLA MACCHINA)  (Poi sarà fatto da Language_Setup)


REM COPIA IN MACCHINA ///////////////////////////////////////////////////////////////////////////////////////////////

rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\EttoreSimuCN\plcres.dll"   "X:\plc\plc\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\iodescr.xml"    "Y:\isac\usertar\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsen.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsfr.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsit.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rssp.dll"       "Y:\isac\exe\"
rem 
rem 
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\EttoreSimuCN\plcres.dll"   "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\iodescr.xml"    "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsen.dll"       "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsfr.dll"       "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsit.dll"       "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rssp.dll"       "Y:\_DLL\"


REM COPIA SU CHIAVE USB ///////////////////////////////////////////////////////////////////////////////////////////////

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\EttoreSimuCN\plcres.dll"   "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\iodescr.xml"    "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsen.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsfr.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rsit.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreSimuCN\rssp.dll"       "G:\_______XXX\"

REM PAUSE

REM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
