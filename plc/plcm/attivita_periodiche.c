/*
        --------------------------------------------------------------
        TITOLO:         Attivita_periodiche.c
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione attivita periodiche
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void attivita_periodiche (void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:			INGRASS_LIV_OK_I
						INGRASS_ATTIVO_I
						CONF_INGRASS_PATT
						FUNZ_MAN50
						R[R_INGRASS_PATT]
						R[R_INGRASS_INTERVALLO]
						R[R_NUM_CICLI_INGRASS]
						R[R_POMPA_ON]
						R[R_POMPA_OFF]
                        R[R_INGRASS_OFF_IF_OK]
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:			INGRASSAGGIO_AUTO_O
                        R[R_ORE_LAVORATE]
						R[R_CICLI_INGR_NOK]
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        K30 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           07-04-2009
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Borsari Guido
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------


*/

#include        "all.inc"

extern float TAU;
extern int   TAUPC;


void attivita_periodiche(void)
{

// INIZIALIZZAZIONE TEMPORIZZATORI USATI NELLA ROUTINE 
if (PON)
{
	lotime (  T_LIVGRASS_NOK, (float)  240           ); // Ritardo allarme livello grasso basso 
	lotime (  T_INGRASS_ON  , (float)  R[R_POMPA_ON]);	// Caricamento tempo pompa ON 
	lotime (  T_INGRASS_OFF , (float)  R[R_POMPA_OFF]);	// Caricamento tempo pompa OFF
	// carico valore da memoria retentiva
	R[R_ORE_LAVORATE]   = M_ORE_LAVORATE;
	R[R_CICLI_INGR_NOK] = M_CICLI_INGR_NOK;
}

// Analisi CONFMAC
if (R[R_INGRASS_PATT] > 0.5)
	CONF_INGRASS_PATT = 1;
else
	CONF_INGRASS_PATT = 0;

// **** Ingrassaggio automatico pattini *****

if (!CONF_INGRASS_PATT) 
	{
	INGRASS_LIV_FAL = 0;
	INGRASS_EV_FAL = 0;
	INGRASS_ORE_FAL = 0;
	SINGOL_POMP_FAL = 0;
	if (R[R_INGRASS_PATT] == 0)
		INGRASS_DISAB_FMS = 1;
	if (INGRASS_DISAB_FMS)
		attenz (INGRASS_DISAB_MS);	// mex di Ingrassaggio Automatico disabilitato
	}
else
	{


	INGRASS_DISAB_FMS = 0;
	if (INGRASS_DISAB_FMS)
		attenz (INGRASS_DISAB_MS);	// mex di Ingrassaggio Automatico disabilitato


	// RESET ALLARMI
	if (RESET_ALL || RESET_MC)
		{
		INGRASS_LIV_FAL = 0;
		INGRASS_EV_FAL = 0;
		INGRASS_ORE_FAL = 0;
		SINGOL_POMP_FAL = 0;
		}


	CICLO_ATTIVO = CICLO_ON;


	// Aggiorno ore lavorate e minuti di ingrassaggio
	if ( CICLO_ATTIVO )
		{
		R[R_ORE_LAVORATE] = R[R_ORE_LAVORATE] + ( TAU * TAUPC / 60000 / 60);		//ore
		}


	// Abilitazione ingrassaggio automatico
	if( R[R_ORE_LAVORATE] >= R[R_INGRASS_INTERVALLO] )	
		ABIL_INGRASS = 1;


	// Lubrificazione avvenuta entro il numero di pompate massimo
	if (START_INGRASS)
	{
		if ((INGRASS_ATTIVO_I && !MEM_INGRASSAGGIO_ATTIVO || !INGRASS_ATTIVO_I && MEM_INGRASSAGGIO_ATTIVO) && !COMMUTAZIONE_MICRO_OK)
		{
			COMMUTAZIONE_MICRO_OK = 1;
			NUM_POMPATE_COMMUTAZ_MICRO = NUM_POMPATE;
		}

		if (COMMUTAZIONE_MICRO_OK && (NUM_POMPATE >= (NUM_POMPATE_COMMUTAZ_MICRO + R[R_NUM_POMP_DOPO_OK])))
		{	
			INGRASS_OK = 1;
			INGRASS_EV_FAL = 0;
			INGRASS_ORE_FAL = 0;
			SINGOL_POMP_FAL = 0;
			if (MANO && FUNZ_MAN50 && COMANDO_B)
				NUM_POMPATE = (short)(R[R_NUM_CICLI_INGRASS] + 1);
		}
	}
	else
	{
		INGRASS_OK = 0;
		COMMUTAZIONE_MICRO_OK = 0;
		NUM_POMPATE_COMMUTAZ_MICRO = 0;
	}


	// Conteggio numero pompate
	if (DP_INGRASS_ON)
		NUM_POMPATE++;
	if (!START_INGRASS)
		NUM_POMPATE = 0;


	if( NUM_POMPATE > R[R_NUM_CICLI_INGRASS] && START_INGRASS)
	{
		R[R_ORE_LAVORATE] = 0;
		ABIL_INGRASS = 0;
		NUM_POMPATE = 0;
		// Ingrassaggio non Ok (nessun cambio stato durante il ciclo di ingrassaggio)
		if (!INGRASS_OK)
		{
			INGRASS_EV_FAL = 1;
			R[R_CICLI_INGR_NOK]++;
		}
		// Ingrassaggio Ok (almeno un cambio stato durante il ciclo di ingrassaggio)
		if (INGRASS_OK)
		{
			INGRASS_EV_FAL = 0;
			R[R_CICLI_INGR_NOK] = 0;
		}
	}


	// Commutazione sensore avvenuto nell'ambito della singola pompata
	if (INGRASSAGGIO_AUTO_O)
	{
		if (INGRASS_ATTIVO_I && !MEM_INGRASSAGGIO_ATTIVO || !INGRASS_ATTIVO_I && MEM_INGRASSAGGIO_ATTIVO)
			SINGOL_POMP_OK = 1;
	}
	else if (!DP_INGRASS_OFF)
		SINGOL_POMP_OK = 0;

	MEM_INGRASSAGGIO_ATTIVO = INGRASS_ATTIVO_I;



	// aggiorno costantemente i valori su memoria retentiva
	M_ORE_LAVORATE   = (float)R[R_ORE_LAVORATE];
	M_CICLI_INGR_NOK = (float)R[R_CICLI_INGR_NOK];

	
	// Start Ingrassaggio
	START_INGRASS = ((ABIL_INGRASS) || (MANO && FUNZ_MAN50 && COMANDO_B)) && INGRASS_LIV_OK_I;


	// Gestione Out Ingrassaggio
	if (R[R_INGRASS_OFF_IF_OK] == 0)
		{
		INGRASSAGGIO_AUTO_O = START_INGRASS && P_INGRASS_ON;				// Numero di pompate fisse
		R[R_NUM_POMP_DOPO_OK] = 0;										// Lavorando a pompate fisse azzero il numero di pompate dopo commutazione micro
		}
	if (R[R_INGRASS_OFF_IF_OK] == 1)
		INGRASSAGGIO_AUTO_O = START_INGRASS && P_INGRASS_ON && !INGRASS_OK;	// Numero di pompate variabile; si arresta sulla commutazione del sensore


	// Allarme livello grasso scarso
	if (ALIM_PRES_I && RP_LIVGRASS_NOK)
			INGRASS_LIV_FAL = 1;
	if (INGRASS_LIV_FAL)
			allarm (INGRASS_LIV_AL);


	// Allarme Ingrassaggio Automatico in anomalia
	if (R[R_INGRASS_PATT] == 3)
		INGRASS_EV_FAL = 0;		// Eliminato il controllo sul ciclo di ingrassaggio
	if (INGRASS_EV_FAL)
			allarm (INGRASS_EV_AL);


	// Allarme mancata commutazione sulla singola pompata
	if (START_INGRASS && DP_INGRASS_OFF && !SINGOL_POMP_OK && (R[R_INGRASS_PATT] == 2)&& (NUM_POMPATE>0))
			SINGOL_POMP_FAL = 1;
	if (SINGOL_POMP_FAL)
			allarm (SINGOL_POMP_AL);


	// Allarme se non avviene l'ingrassaggio per troppo tempo
	if (AUTO && (R[R_CICLI_INGR_NOK] > 2))
			INGRASS_ORE_FAL = 1;
	if (INGRASS_ORE_FAL)
			allarm (INGRASS_ORE_AL);



	// GESTIONE FUNZIONE ESEGUITA 
		INGRASS_FUNES_B = MANO && FUNZ_MAN50 && COMANDO_B && P_OSCILLATORE || INGRASS_OK;

	}
}
