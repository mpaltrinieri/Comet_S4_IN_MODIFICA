@ECHO OFF

rem comando compilatore:	"$(SolutionDir)\BAT\74EttoreRelease__MEX.BAT"

REM  COPIA DI ALLARMI, MESSAGGI E DESCRIZIONI I/O DI SIOMAG/HMI SULLA MACCHINA CONNESSA VIA RETE  (IN "Y:\isac\exe\").

REM  LINGUE HDRILL/MG_PILOT:
REM  1) PULIRE EVENTUALMENTE DA STRINGHE NON NECESSARIE  C:\Prodotti\Progetti Cnc 7_0\Comet_S4\lingue\I\CNC.MSG 
REM  2) COPIAR LA CARTELLA LINGUE DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE"         A  "C:\isac\LINGUE"  (DELLA MACCHINA)
REM  3) COPIAR *.*                DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\*.*"   A  "D:\isac\Msg\"    (DELLA MACCHINA)
REM  4) (Poi sarà fatto da Language_Setup)

REM  All'avvio il CNC copia plcres.dll da C:\plc\plc\ a "D:\isac\exe\resdll"  (solo se non trova un file con questo nome in D:\isac\exe\resdll)
REM  se si cancella C:\plc\plc\plcres.dll  il CNC cancella anche  D:\isac\exe\resdll\plcres.dll

REM COPIA IN MACCHINA ///////////////////////////////////////////////////////////////////////////////////////////////

rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreRelease\plcres.dll"   "X:\plc\plc\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreRelease\plcres.dll"   "Y:\isac\exe\resdll\"
rem 
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsen.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsfr.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsit.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rssp.dll"       "Y:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\iodescr.xml"    "Y:\isac\usertar\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\lingue\I\CNC.MSG"                        "X:\isac\lingue\I\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\lingue\I\CNC.MSG"                        "Y:\isac\Msg\"
rem 
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreRelease\plcres.dll"   "Y:\_MEX\"
rem 
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsen.dll"       "Y:\_MEX\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsfr.dll"       "Y:\_MEX\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsit.dll"       "Y:\_MEX\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rssp.dll"       "Y:\_MEX\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\iodescr.xml"    "Y:\_MEX\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\lingue\I\CNC.MSG"                        "Y:\_MEX\"

REM COPIA SU CHIAVE USB ///////////////////////////////////////////////////////////////////////////////////////////////

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreRelease\plcres.dll"   "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\iodescr.xml"    "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsen.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsfr.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rsit.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreRelease\rssp.dll"       "G:\_______XXX\"


REM COPIA DA CHIAVE USB A MACCHINA ///////////////////////////////////////////////////////////////////////////////////////////////

rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\resdll\74EttoreRelease\plcres.dll"   "C:\plc\plc\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\resdll\74EttoreRelease\plcres.dll"   "D:\isac\exe\resdll\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rsen.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rsfr.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rsit.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rssp.dll"       "D:\isac\exe\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\iodescr.xml"    "D:\isac\usertar\"

rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\resdll\74EttoreRelease\plcres.dll"   "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rsen.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rsfr.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rsit.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\rssp.dll"       "D:\_DLL\"
rem copy "E:\Comet_S4\PROGETTO\Comet_S4\PLC\plcm\74EttoreRelease\iodescr.xml"    "D:\_DLL\"

REM PAUSE

REM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
