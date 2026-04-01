/*
--------------------------------------------------------------
TITOLO:         Oil_level()
--------------------------------------------------------------
--------------------------------------------------------------
DESCRIZIONE:    Gestione livello olio lubrica
--------------------------------------------------------------
RELEASE:        QUA 1.5
--------------------------------------------------------------
--------------------------------------------------------------
DATA:           03-2025
--------------------------------------------------------------
--------------------------------------------------------------
AUTORI:         Medici Stefano
--------------------------------------------------------------
--------------------------------------------------------------
AGGIORNAMENTI:
--------------------------------------------------------------

*/


#include        "all.inc"

#define IFM_LR300_COAXIAL_TUBE_OFFSET 9

void Oil_level_1(void);
void Oil_level_1_not_present(void);

void Oil_level(void)
{	
	switch ((int) AF_LIVELLO_OLIO_EN) 
	{
	case 1:                  // livellostato IOLINK della IFM
		Oil_level_1();
		break;
	default:
		Oil_level_1_not_present();
		break;
	}
}

void Oil_level_1(void)
{
	//**** INSERIRE LA GESTIONE SE E QUANDO IL DISPOSITIVO VERRA' INDSERITO IN MACCHINA
	////////**** RESET ALLARMI *****
	//////if (RESET_ALL || RESET_MC)
	//////{
	//////}

	////////Misura restituita dal misuratore di livello [mm]
	//////OIL_LEVEL_MIS = ((SENS_LIVELLO_OLIO_I  & 0x00FF) << 4) | ((SENS_LIVELLO_OLIO_I & 0xF000) >> 12) + IFM_LR300_COAXIAL_TUBE_OFFSET;

	//////LIV_LUB_OK_FLAG = (OIL_LEVEL_MIS >= R[R_OIL_LEVEL_MIN]);
	//////
	////////Livello olio [mm]
	//////OIL_LEVEL = OIL_LEVEL_MIS + (float) R[R_OIL_LEVEL_OFFSET];
	//////R[R_OIL_LEVEL] = OIL_LEVEL;

	////////Volume olio [l=dm^3]
	//////R[R_OIL_VOLUME] = R[R_OIL_LEVEL_AREA] * OIL_LEVEL / 10000.0f;
	//////
	////////Pubblicazione valore su OPCUA
	//////AF_LIVELLO_OLIO = (float) R[R_OIL_VOLUME];
	
}
void Oil_level_1_not_present(void)
{
	////////LIV_LUB_OK_FLAG = LIV_LUB_OK_I;  // Il flag dovrà sostituire l'ingresso di livello olio
}
