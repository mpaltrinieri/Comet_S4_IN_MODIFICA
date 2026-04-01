{PROBE FOR CAMAELEON}
{R2080 = Probe movement mm}
{R2081 = Start point in X}
{R2082 = Start point in Y}
{R2083 = Start point in Z}


       {TL=R507-R508}
N1     IF (R979 == 0) RET       {modulo di tastatura CAMPlus disabilitato}
       L SNGCNT.CS4
       $M118                    {inizio ciclo tastatore}


N5     S0                   {forza velocita' di rotazione mandrino a 0}
       R6093=1                   {ciclo di tastatura attivo}

	{Calculation direction vector
	R401=(R210-R2081)
	R402=(R211-R2082)
	R403=(R212-R2083)

	R404=SQR((R401*R401) + (R402*R402) + (R403*R403))
	R405=(R401/R404)
	R406=(R402/R404)
	R407=(R403/R404)

	{Calculation of destination point
	R408=R210+(R405*R2080)
	R409=R211+(R406*R2080)
	R410=R212+(R407*R2080)   
	
	 L SLOWACC.CS4
	 
N80 $M175    {attesa spegnimento ingresso marposs in touch}
N85 G4 F0.1
N90 L SNGCNT.CS4
 	 
       IF (R459 == 0) $M178     {INIZIO verifica tastatore non premuto}

	   [TAST]
       IF (R6094 == 1) $M178     {INIZIO verifica tastatore non premuto}
       R6094=0
       IF (R459 == 0) $M177     {FINE   verifica tastatore non premuto}

       {mentre esecuz è tra N110/N120 può venir captata interruz da PLC e l'esecuz va a N150
N100   <TRU<0>:N110;N120;N150>
N110   G304 CNC                 {attesa assi fermi}
       G4 F0.1
       L SNGCNT.CS4
       R411= R600               {memorizza quota asse X}
       R412= R601               {memorizza quota asse Y}
       R413= R602               {memorizza quota asse Z}

	   
N120   G1 F=R901 X=R408 Y=R409 Z=R410 $M49

N150   IF (R459 == 0) $M179     {verifica tastatore premuto}
       IF (R459 == 1) RET       {esce se simulazione}
       G304 CNC                 {attesa assi fermi}
       G4 F0.1
       L SNGCNT.CS4
       IF(R7880>0.5) JMP [LATCH] {usa ingressi latch su azionamenti}
       R414= R600               {memorizza quota asse X}
       R415= R601               {memorizza quota asse Y}
       R416= R602               {memorizza quota asse Z}
       JMP [NO_LATCH]
       
       [LATCH]
       R414= R6095              {memorizza quota asse X}
       R415= R6096              {memorizza quota asse Y}
       R416= R6097              {memorizza quota asse Z}       
       
       [NO_LATCH]
       G0 X=R2081 Y=R2082 Z=R2083               
       L SNGCNT.CS4
       IF (R6094 == 1) [TAST]
N193   G304 CNC                 {attesa assi fermi}
N195   IF (R6092 == 1) $M176     {ALLARME TASTATORE ANCORA IN BATTUTA DOPO FINE TASTATA


N200   IF (R340 >=  1)  IF (R340 <= 99) [INDEX_OK]
       $M184                    {errore indice tastatura}

[INDEX_OK]
N300   IF (R340 > 0) [XYZ]

       [XYZ]
		R405=ABS(R405 * R902) 
		R406=ABS(R406 * R902)
		R407=ABS(R407 * R902)

{SISTEMA RUOTATO CON DRTXYZ NELLA SEQUENZA ASSI <DMX:Z;X;Y>
{-----------------------------------------------------------------------}
    { TRASFORMAZIONE DIRETTA: sbagliato, serve la trasformazione inversa
    { R4021=(COS(ANR)*COS(AN3)-SIN(AN3)*SIN(AN2)*SIN(ANR))*R405
    { R4022=(SIN(ANR)*COS(AN3)+COS(ANR)*SIN(AN2)*SIN(AN3))*R406
    { R4023=(-COS(AN2)*SIN(AN3))*R407

    { R4024=(-SIN(ANR)*COS(AN2))*R405
    { R4025=COS(ANR)*COS(AN2)*R406
    { R4026=SIN(AN2)*R407

    { R4027=(COS(ANR)*SIN(AN3)+SIN(ANR)*SIN(AN2)*COS(AN3))*R405
    { R4028=(SIN(ANR)*SIN(AN3)-COS(ANR)*SIN(AN2)*COS(AN3))*R406
    { R4029=COS(AN2)*COS(AN3)*R407

{   TRASFORMAZIONE INVERSA
R4021=(COS(ANR)*COS(AN3)-SIN(AN3)*SIN(AN2)*SIN(ANR))*R405
R4022=(SIN(ANR)*COS(AN2))*R406
R4023=(SIN(AN3)*COS(ANR)+SIN(AN2)*COS(AN3)*SIN(ANR))*R407

R4024=(SIN(ANR)*COS(AN3)+SIN(AN3)*SIN(AN2)*COS(ANR))*R405
R4025=(COS(ANR)*COS(AN2))*R406
R4026=(SIN(AN3)*SIN(ANR)-SIN(AN2)*COS(AN3)*COS(ANR))*R407

R4027=(0-COS(AN2)*SIN(AN3))*R405
R4028=SIN(AN2)*R406
R4029=(COS(AN2)*COS(AN3))*R407
{-----------------------------------------------------------------------}

R4010=R4021+R4022+R4023  {x nel sistema originario non ruotato}
R4011=R4024+R4025+R4026  {y nel sistema originario non ruotato}
R4012=R4027+R4028+R4029  {z nel sistema originario non ruotato}

R4010 = ABS(R4010)
R4011 = ABS(R4011)
R4012 = ABS(R4012)
		
       IF (R411 > 0) R3044 = R411 - ( (SQR((R414-R411)**2)) + R4010)
       IF (R411 < 0) R3044 = R411 + ( (SQR((R414-R411)**2)) + R4010)
	   IF (ABS(R411-R414) < 0.001) R3044=0 
 
       IF (R412 > 0) R3045 = R412 - ( (SQR((R415-R412)**2)) + R4011)
       IF (R412 < 0) R3045 = R412 + ( (SQR((R415-R412)**2)) + R4011)
	   IF (ABS(R412-R415) < 0.001) R3045=0

       IF (R413 > 0) R3046 = R413 - ( (SQR((R416-R413)**2)) + R4012)
       IF (R413 < 0) R3046 = R413 + ( (SQR((R416-R413)**2)) + R4012)
	   IF (ABS(R413-R416) < 0.001) R3046=0
       JMP [MEM_CORR]

[MEM_CORR]
N400   IF (R340 > 0) R3047=400+((R340-1)*2) {calcolo indice appoggio correzione asse X} 
N410   IF (R340 > 0) R3048=600+((R340-1)*2) {calcolo indice appoggio correzione asse Y} 
N420   IF (R340 > 0) R3049=800+((R340-1)*2) {calcolo indice appoggio correzione asse Z} 

N500   IF (R340 > 0) (V11006.(FTI(R3047))=R3044) {memorizza correzione asse X} 
N510   IF (R340 > 0) (V11006.(FTI(R3048))=R3045) {memorizza correzione asse Y} 
N520   IF (R340 > 0) (V11006.(FTI(R3049))=R3046) {memorizza correzione asse Z} 

N600   $M48
       L SNGCNT.CS4
       R6093=0                   {ciclo di tastatura non attivo}
       L FASTACC.CS4
       $M119 {fine ciclo tastatore}
       TL=R507
       RET
