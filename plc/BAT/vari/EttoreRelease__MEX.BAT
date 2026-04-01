@ECHO OFF

rem comando:	"$(SolutionDir)\BAT\EttoreRelease__MEX.BAT"

REM  COPIA DI ALLARMI, MESSAGGI E DESCRIZIONI I/O DI SIOMAG/HMI SULLA MACCHINA CONNESSA VIA RETE  (IN "Y:\isac\exe\").

REM  LINGUE DRILL/MG_PILOT:
REM  1) PULIRE EVENTUALMENTE DA STRINGHE NON NECESSARIE  C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\CNC.MSG 
REM  2) COPIAR MANUALMENTE CNC.MSG DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\"   A  "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\"
REM  3) COPIAR LA CARTELLA LINGUE DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE"         A  "C:\isac\LINGUE"  (DELLA MACCHINA)
REM  4) COPIAR *.*                DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\*.*"   A  "D:\isac\Msg\"  (DELLA MACCHINA)  (Poi sarà fatto da Language_Setup)

REM  All'avvio il CNC copia plcres.dll da C:\plc\plc\ a "D:\isac\exe\resdll"  (solo se non trova un file con questo nome in D:\isac\exe\resdll)
REM  se si cancella C:\plc\plc\plcres.dll  il CNC cancella anche  D:\isac\exe\resdll\plcres.dll

REM COPIA IN MACCHINA ///////////////////////////////////////////////////////////////////////////////////////////////

rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\EttoreRelease\plcres.dll"     "X:\plc\plc\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\EttoreRelease\plcres.dll"     "Y:\isac\exe\resdll\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsen.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsfr.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsit.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rssp.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\iodescr.xml"    "Y:\isac\usertar\"
rem 
rem 
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\EttoreRelease\plcres.dll"   "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\iodescr.xml"    "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsen.dll"       "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsfr.dll"       "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsit.dll"       "Y:\_DLL\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rssp.dll"       "Y:\_DLL\"


REM COPIA SU CHIAVE USB ///////////////////////////////////////////////////////////////////////////////////////////////

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\EttoreRelease\plcres.dll"   "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\iodescr.xml"    "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsen.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsfr.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rsit.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\EttoreRelease\rssp.dll"       "G:\_______XXX\"


REM COPIA DA CHIAVE USB A MACCHINA ///////////////////////////////////////////////////////////////////////////////////////////////

rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\resdll\EttoreRelease\plcres.dll"   "C:\plc\plc\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\resdll\EttoreRelease\plcres.dll"   "D:\isac\exe\resdll\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rsen.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rsfr.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rsit.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rssp.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\iodescr.xml"    "D:\isac\usertar\"

rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\resdll\EttoreRelease\plcres.dll"   "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rsen.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rsfr.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rsit.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\rssp.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\EttoreRelease\iodescr.xml"    "D:\_DLL\"

rem PAUSE

REM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
