/*
        --------------------------------------------------------------
        TITOLO:         Volantino
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Chiamate alla gestione volantino 
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    Volantino (void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:          
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:         
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           15-04-2003
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         G.Borsari
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------
*/


#include		"all.inc"

void volantino(void)
{

if((R[R_VOLANTINO_PRES]>0.5) && CONF_FUNZ_ISO_ABIL && !(SIMULATORE_SU_CN || SIMULATORE_SU_PC ))
{
#ifdef _CWIN32
	short esito_CH0;
#endif 

// Funzioni manuali abilitanti movimenti assi col volantino
FUNZ_MAN_VOL = (FUNZ_MAN181 || FUNZ_MAN182 || FUNZ_MAN183 || FUNZ_MAN184 || FUNZ_MAN185 || 
                FUNZ_MAN186 || FUNZ_MAN187 || FUNZ_MAN188 || FUNZ_MAN189 || FUNZ_MAN190 || 
                FUNZ_MAN191 || FUNZ_MAN192 || FUNZ_MAN193 || FUNZ_MAN194 || FUNZ_MAN195);


// Abilitazione mandrino col volantino
if (MANO && FUNZ_MAN180 && COMANDO_B)
		ABIL_MANDRINO = 1;

if ( AUTO || RESET_MC || (FUNZ_MAN180 && COMANDO_A) || (!FUNZ_MAN_VOL && !FUNZ_MAN180) )
		ABIL_MANDRINO = 0;


// Precedente Scelta asse 
OLD_SEL_ASSE_VOL_X = SEL_ASSE_VOL_X;
OLD_SEL_ASSE_VOL_Y = SEL_ASSE_VOL_Y;
OLD_SEL_ASSE_VOL_Z = SEL_ASSE_VOL_Z;
OLD_SEL_ASSE_VOL_A = SEL_ASSE_VOL_A;
OLD_SEL_ASSE_VOL_C = SEL_ASSE_VOL_C;

// Scelta asse
SEL_ASSE_VOL_X = (FUNZ_MAN181 || FUNZ_MAN182 || FUNZ_MAN183);
SEL_ASSE_VOL_Y = (FUNZ_MAN184 || FUNZ_MAN185 || FUNZ_MAN186);
SEL_ASSE_VOL_Z = (FUNZ_MAN187 || FUNZ_MAN188 || FUNZ_MAN189);
SEL_ASSE_VOL_A = (FUNZ_MAN190 || FUNZ_MAN191 || FUNZ_MAN192);
SEL_ASSE_VOL_C = (FUNZ_MAN193 || FUNZ_MAN194 || FUNZ_MAN195);

// Variazione selezione asse
STROBE_SEL_ASSE_VOL = (
	(SEL_ASSE_VOL_X && !OLD_SEL_ASSE_VOL_X) ||
	(SEL_ASSE_VOL_Y && !OLD_SEL_ASSE_VOL_Y) ||
	(SEL_ASSE_VOL_Z && !OLD_SEL_ASSE_VOL_Z) ||
	(SEL_ASSE_VOL_A && !OLD_SEL_ASSE_VOL_A) ||
	(SEL_ASSE_VOL_C && !OLD_SEL_ASSE_VOL_C)
);


//Selezione Asse
if      (MANO && SEL_ASSE_VOL_X)  R[R_ASSE_ATTIVO_VOL] = 0;		// Asse X attivo 
else if (MANO && SEL_ASSE_VOL_Y)  R[R_ASSE_ATTIVO_VOL] = 1;		// Asse Y attivo 
else if (MANO && SEL_ASSE_VOL_Z)  R[R_ASSE_ATTIVO_VOL] = 2;		// Asse Z attivo 
else if (MANO && SEL_ASSE_VOL_A)  R[R_ASSE_ATTIVO_VOL] = 3;		// Asse A attivo 
else if (MANO && SEL_ASSE_VOL_C)  R[R_ASSE_ATTIVO_VOL] = 4;		// Asse C attivo 
else                              R[R_ASSE_ATTIVO_VOL] = 99;	// Nessun Asse attivo 


// Scelta moltiplica
SELETTORE_X1   = (FUNZ_MAN181 || FUNZ_MAN184 || FUNZ_MAN187 || FUNZ_MAN190 || FUNZ_MAN193);			// incremento=0.01 mm
SELETTORE_X10  = (FUNZ_MAN182 || FUNZ_MAN185 || FUNZ_MAN188 || FUNZ_MAN191 || FUNZ_MAN194);			// incremento=0.10 mm
SELETTORE_X100 = (FUNZ_MAN183 || FUNZ_MAN186 || FUNZ_MAN189 || FUNZ_MAN192 || FUNZ_MAN195);			// incremento=0.20 mm

// Selezione moltiplica
if      (SELETTORE_X1)    R[R_VELOCE_VOL] = 0;			// incremento=0.01 mm
else if (SELETTORE_X10)   R[R_VELOCE_VOL] = 1;			// incremento=0.10 mm
else if (SELETTORE_X100)  R[R_VELOCE_VOL] = 2;			// incremento=0.20 mm
else                      R[R_VELOCE_VOL] = 0;			// incremento=0.01 mm


// Abilitazione volantino (1) 
if (RP_VOL_ON)
			R[R_ABI_VOL] = 1;
		else
			R[R_ABI_VOL] = 0;


//Assegnazione volantini a canali di misura 
/*
RV0 = primo canale di misura libero
RV1 = secondo canale di misura libero
RV2 = terzo canale di misura libero 
In questo caso RV0 = canale di misura volantino
Mistero ISAC : perchè RV2 e non RV0 come nel Micromatic ?
Controllare le tre RV (0-1-2) ogni volta a scanso di equivoci
*/

// Misura volantino 1
MIS_VOL1_CH0 = RV_FIELD_0;
// Misura volantino 2 : non usato 
MIS_VOL2_CH0 = 0;
// Misura volantino 3 : non usato 
MIS_VOL3_CH0 = 0;


//
// GESTIONE VOLANTINI 
//
// DA NON MODIFICARE 
//
		
/*	Descrizione parametro AXVOL1 = 0xAB											
0x sono fissi  A indica il numero dell'asse abbinato al volantino 2					
B indica il numero dell'asse abbinato al volantino 1								
Descrizione parametro AXVOL3 = 0xCD													
0x sono fissi																		
C indica il numero dell'asse abbinato al volantino 3								
D non è significativo																
Descrizione parametro S_VOL1 = 1 : volantino 1 attivo									
Descrizione parametro S_VOL2 = 2 : volantino 2 attivo								
Descrizione parametro S_VOL3 = 3 : volantino 3 attivo								
Nel caso vi sia solo un volantino alternato sugli assi, mettere a 0 S_VOL2 e S_VOL3	
*/
	
if (PON)
		{
		// Assegnazione assi(num.max 12) a volantini(num.max 3) fissi 
		AXVOL2_CH0 = 0x00;			 // Assegnazione volantino 2 : non utilizzato 
		AXVOL3_CH0 = 0x00;			 // Assegnazione volantino 3 : non utilizzato 

		S_VOL1_CH0 = 1;				 // Ho un solo volantino attivo da selezionare sui vari assi 
		S_VOL2_CH0 = 0;
		S_VOL3_CH0 = 0;
		}

read_var(VL_FLOT, 4149, -1, -1, &R[R_READ_ACC_ASSI_VOL]);  //lettura variabile di accelerazione assi volantino

if(R[R_ABI_VOL] == 1)	//Richiesta aggancio volantini
		{
		// Abbino l'asse attivato dal sel.3 pos. al volantino relativo 
		R[R_WRITE_ACC_ASSI_VOL] = R[R_ACC_ASSI_VOL_XYAC];
		// Asse n.0 (X) attivo su volantino 1
		if	(R[R_ASSE_ATTIVO_VOL] == 0)
		{
						AXVOL1_CH0 = 0x00;
						R[R_WRITE_ACC_ASSI_VOL] = R[R_ACC_ASSI_VOL_XYAC];
		}
		// Asse n.1 (Y) attivo su volantino 1
		if	(R[R_ASSE_ATTIVO_VOL] == 1)
		{
						AXVOL1_CH0 = 0x01;
		                R[R_WRITE_ACC_ASSI_VOL] = R[R_ACC_ASSI_VOL_XYAC];
		}
		// Asse n.2 (Z) attivo su volantino 1
		if	(R[R_ASSE_ATTIVO_VOL] == 2)
		{
						AXVOL1_CH0 = 0x02;
		                R[R_WRITE_ACC_ASSI_VOL] = R[R_ACC_ASSI_VOL_Z];
		}
		// Asse n.3 (B) attivo su volantino 1
		if	(R[R_ASSE_ATTIVO_VOL] == 3)
		{
						AXVOL1_CH0 = 0x03;
		                R[R_WRITE_ACC_ASSI_VOL] = R[R_ACC_ASSI_VOL_XYAC];
		}
		// Asse n.4 (C) attivo su volantino 1
		if	(R[R_ASSE_ATTIVO_VOL] == 4)
		{
						AXVOL1_CH0 = 0x04;
		                R[R_WRITE_ACC_ASSI_VOL] = R[R_ACC_ASSI_VOL_XYAC];
		}

if( (R[R_READ_ACC_ASSI_VOL] > R[R_WRITE_ACC_ASSI_VOL]+0.0001) ||  (R[R_READ_ACC_ASSI_VOL] < R[R_WRITE_ACC_ASSI_VOL]-0.0001) )
    write_var(VL_FLOT, 4149, -1, -1, &R[R_WRITE_ACC_ASSI_VOL]); //scrittura variabile di accelerazione assi volantino

	//Selezione risoluzione per ogni impulso del volantino
	//Valore modificabile : La base è il millesimo , ossia 0,001 mm 
	//Valore massimo inseribile : 255 I_VFCS è uno shortINT 

		if(R[R_VELOCE_VOL] == 0)
					I_VFCS_CH0 = 10;		//Risoluzione 1 centesimo
		else if(R[R_VELOCE_VOL] == 1)
					I_VFCS_CH0 = 100;		//Risoluzione 1 decimo
		else if(R[R_VELOCE_VOL] == 2)
					I_VFCS_CH0 = 200;		//Risoluzione 2 decimi
		else 
					I_VFCS_CH0 = 1;			//Risoluzione in millesimi		
						
		//Abilitazione volantini
		RC_VOL_CH0 = 1;

		}
	else
		{
		//Disabilitazione volantini
		RC_VOL_CH0 = 0;
		}

#ifdef _CWIN32

	//Ch0
	if (!SerPlanPlc (&esito_CH0))
	{
		gestvol ();
	}

#endif

// FUNZIONE ESEGUITA 
VOLANT_FUNES_B = (FUNZ_MAN_VOL && RP_VOL_ON) || (FUNZ_MAN180 && ABIL_MANDRINO);

VOLANT_FUNES_A = (FUNZ_MAN_VOL && RP_VOL_ON) || (FUNZ_MAN180 && !ABIL_MANDRINO);

}

else 
	{
		ABIL_MANDRINO = 0;
	}


}

