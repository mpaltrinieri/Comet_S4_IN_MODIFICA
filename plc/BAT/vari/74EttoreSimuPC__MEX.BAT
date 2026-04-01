@ECHO OFF

REM  COPIA DI ALLARMI, MESSAGGI E DESCRIZIONI I/O DI SIOMAG/HMI SULLA MACCHINA CONNESSA VIA RETE  (IN "Y:\isac\exe\").

REM  LINGUE DRILL/MG_PILOT:
REM  1) PULIRE EVENTUALMENTE DA STRINGHE NON NECESSARIE  C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\CNC.MSG 
REM  2) COPIAR MANUALMENTE CNC.MSG DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\"   A  "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\"
REM  3) COPIAR LA CARTELLA LINGUE DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE"         A  "C:\isac\LINGUE"  (DELLA MACCHINA)
REM  4) COPIAR *.*                DA "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\LINGUE\I\*.*"   A  "D:\isac\Msg\"  (DELLA MACCHINA)  (Poi sarà fatto da Language_Setup)


REM COPIA IN MACCHINA ///////////////////////////////////////////////////////////////////////////////////////////////

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuPC\plcres.dll"   "X:\plc\plc\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\iodescr.xml"    "Y:\isac\usertar\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsen.dll"       "Y:\isac\exe\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsfr.dll"       "Y:\isac\exe\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsit.dll"       "Y:\isac\exe\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rssp.dll"       "Y:\isac\exe\"

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuPC\plcres.dll"   "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\iodescr.xml"    "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsen.dll"       "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsfr.dll"       "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsit.dll"       "Y:\_DLL\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rssp.dll"       "Y:\_DLL\"


REM COPIA SU CHIAVE USB ///////////////////////////////////////////////////////////////////////////////////////////////

REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuPC\plcres.dll"   "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\iodescr.xml"    "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsen.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsfr.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsit.dll"       "G:\_______XXX\"
REM copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rssp.dll"       "G:\_______XXX\"


REM COPIA SU C:\        ///////////////////////////////////////////////////////////////////////////////////////////////

rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\resdll\74EttoreSimuPC\plcres.dll"   "C:\plc\plc\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\iodescr.xml"    "C:\isac\usertar\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsen.dll"       "C:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsfr.dll"       "C:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rsit.dll"       "C:\isac\exe\"
rem copy "C:\Prodotti\Progetti Cnc 7_0\Comet_S4\PLC\plcm\74EttoreSimuPC\rssp.dll"       "C:\isac\exe\"

REM ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

REM PAUSE
