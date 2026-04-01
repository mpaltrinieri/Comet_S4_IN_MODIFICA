/*
        --------------------------------------------------------------
        TITOLO:         Gruppo_FRL_connect
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    Gestione del misuratore della differenza di pressione
                        del flussometro e del sensore di temperatura
                        del basamento
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void    Gruppo_FRL_connect(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        INPUT:           
        --------------------------------------------------------------
        --------------------------------------------------------------
        OUTPUT:
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CR4 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           24-06-2024
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include        "all.inc"


void Gruppo_FRL_connect(void)
{

	if(AF_MISURATORE_PRESS_PRES==1)
	{

		// *************** set degli I/O del misuratore di pressione PSE203A ******************************
		APP_MISURA_CH1_BYTE_LOW =   MI_6W0_BL;               // INPUT: byte basso Misura CH1
		APP_MISURA_CH1_BYTE_HIGH =  MI_6W0_BH;               // INPUT: byte alto  Misura CH1
                                                            
		APP_MISURA_CH2_BYTE_LOW =   MI_6W1_BL;               // INPUT: byte basso Misura CH2
		APP_MISURA_CH2_BYTE_HIGH =  MI_6W1_BH;               // INPUT: byte alto  Misura CH2
                                                            
		APP_MISURA_CH3_BYTE_LOW =   MI_6W2_BL;               // INPUT: byte basso Misura CH3
		APP_MISURA_CH3_BYTE_HIGH =  MI_6W2_BH;               // INPUT: byte alto  Misura CH3
                                                            
		APP_MISURA_CH4_BYTE_LOW =   MI_6W3_BL;               // INPUT: byte basso Misura CH4
		APP_MISURA_CH4_BYTE_HIGH =  MI_6W3_BH;               // INPUT: byte alto  Misura CH4

		// *************** set degli I/O del flussometro PF3A801H ******************************
		APP_FLUSSO_BYTE_LOW =       MI_6W7_BL;               // INPUT: byte basso flusso
		APP_FLUSSO_BYTE_HIGH =      MI_6W7_BH;               // INPUT: byte alto  flusso
                                                            
		APP_TEMPERATURA_BYTE_LOW =  MI_6W8_BL;               // INPUT: byte basso temperatura
		APP_TEMPERATURA_BYTE_HIGH = MI_6W8_BH;               // INPUT: byte alto  temperatura
                                                            
		APP_PRESSIONE_BYTE_LOW =    MI_6W9_BL;               // INPUT: byte basso pressione
		APP_PRESSIONE_BYTE_HIGH =   MI_6W9_BH;               // INPUT: byte alto  pressione
                                                            
		APP_STATE_OUT_BYTE_LOW =    MI_6W10_BL;              // INPUT: byte basso Stato delle uscite programmate
		APP_STATE_OUT_BYTE_HIGH =   MI_6W10_BH;              // INPUT: byte alto  Stato delle uscite programmate

		// *************** set degli I/O del sensore di temperatura sul basamento della IFM ******************************
		APP_TEMP_BASAM_BYTE_LOW =   MI_6W11_BL;              // INPUT: byte basso flusso 
		APP_TEMP_BASAM_BYTE_HIGH =  MI_6W11_BH;              // INPUT: byte alto  flusso 

	}
	else if(AF_MISURATORE_PRESS_PRES==2)
	{

		// *************** set degli I/O dei pressostati iolink PSE540 a monte e a valle del filtro aria ******************************/
		// Pressostato iolink PSE540 a monte del filtro aria (canale CH1 della scheda OPRIOIOLM0)
		APP_MISURA_CH1_BYTE_LOW =   MI_6W0_BL;               // INPUT: byte basso Misura CH1 
		APP_MISURA_CH1_BYTE_HIGH =  MI_6W0_BH;               // INPUT: byte alto  Misura CH1 

		// Pressostato iolink PSE540 a valle del filtro aria (canale CH4 della scheda OPRIOIOLM0)
		APP_MISURA_CH2_BYTE_LOW =   MI_6W9_BL;               // INPUT: byte basso Misura CH2 
		APP_MISURA_CH2_BYTE_HIGH =  MI_6W9_BH;               // INPUT: byte alto  Misura CH2 

		// *************** set degli I/O del flussometro PF3A801H (canale CH2 della scheda OPRIOIOLM0) *****************************
		APP_FLUSSO_BYTE_LOW =       MI_6W4_BL;               // INPUT: byte basso flusso 
		APP_FLUSSO_BYTE_HIGH =      MI_6W4_BH;               // INPUT: byte alto  flusso 
                                  
		APP_TEMPERATURA_BYTE_LOW =  MI_6W5_BL;               // INPUT: byte basso temperatura 
		APP_TEMPERATURA_BYTE_HIGH = MI_6W5_BH;               // INPUT: byte alto  temperatura 
                                  
		APP_PRESSIONE_BYTE_LOW =    MI_6W6_BL;               // INPUT: byte basso pressione 
		APP_PRESSIONE_BYTE_HIGH =   MI_6W6_BH;               // INPUT: byte alto  pressione 
                                  
		APP_STATE_OUT_BYTE_LOW =    MI_6W7_BL;               // INPUT: byte basso Stato delle uscite programmate 
		APP_STATE_OUT_BYTE_HIGH =   MI_6W7_BH;               // INPUT: byte alto  Stato delle uscite programmate 

		// *************** set degli I/O del sensore di temperatura sul basamento della IFM (canale CH3 della scheda OPRIOIOLM0) *****************************
		APP_TEMP_BASAM_BYTE_LOW =   MI_6W8_BL;               // INPUT: byte basso flusso 
		APP_TEMP_BASAM_BYTE_HIGH =  MI_6W8_BH;               // INPUT: byte alto  flusso 

	}


	if(AF_MISURATORE_PRESS_PRES)
	{
		// APP_MISURA_CH1 = appoggio misura del CH1 letta da IOlink (pressione a monte del disoleatore)
		// APP_MISURA_CH2 = appoggio misura del CH2 letta da IOlink (pressione a valle del disoleatore)
		// APP_MISURA_CH3 = appoggio misura del CH3 letta da IOlink (ATTUALMENTE NON USATA)
		// APP_MISURA_CH4 = appoggio misura del CH4 letta da IOlink (ATTUALMENTE NON USATA)

		// QUI IL CODICE SE NON RICHIESTA INVERSIONE DEI BYTE
		// APP_MISURA_PSE203A_CH1 = (short int) ( ( (APP_MISURA_CH1_BYTE_HIGH << 8) & (0xFF00)) | (APP_MISURA_CH1_BYTE_LOW & (0x00FF)) );
		// APP_MISURA_PSE203A_CH2 = (short int) ( ( (APP_MISURA_CH2_BYTE_HIGH << 8) & (0xFF00)) | (APP_MISURA_CH2_BYTE_LOW & (0x00FF)) );
		// APP_MISURA_PSE203A_CH3 = (short int) ( ( (APP_MISURA_CH3_BYTE_HIGH << 8) & (0xFF00)) | (APP_MISURA_CH3_BYTE_LOW & (0x00FF)) );
		// APP_MISURA_PSE203A_CH4 = (short int) ( ( (APP_MISURA_CH4_BYTE_HIGH << 8) & (0xFF00)) | (APP_MISURA_CH4_BYTE_LOW & (0x00FF)) );

		// QUI IL CODICE SE RICHIESTA INVERSIONE DEI BYTE (da verificare in macchina)
		   APP_MISURA_PSE203A_CH1 = (short int) ( ( (APP_MISURA_CH1_BYTE_LOW << 8) & (0xFF00)) | (APP_MISURA_CH1_BYTE_HIGH & (0x00FF)) );
		   APP_MISURA_PSE203A_CH2 = (short int) ( ( (APP_MISURA_CH2_BYTE_LOW << 8) & (0xFF00)) | (APP_MISURA_CH2_BYTE_HIGH & (0x00FF)) );
		// APP_MISURA_PSE203A_CH3 = (short int) ( ( (APP_MISURA_CH3_BYTE_LOW << 8) & (0xFF00)) | (APP_MISURA_CH3_BYTE_HIGH & (0x00FF)) );
		// APP_MISURA_PSE203A_CH4 = (short int) ( ( (APP_MISURA_CH4_BYTE_LOW << 8) & (0xFF00)) | (APP_MISURA_CH4_BYTE_HIGH & (0x00FF)) );

		// Conversione dal valore letto sul registro al valore di pressione visualizzato sul display:
		// PD = valore di pressione letto sul registro (da process data)
		// Pr = valore di pressione a display
		// La conversione si ottiene applicando l'equazione di una retta:
		// Pr = a * PD + b
		// in cui, impostando il valore visualizzato a display in [bar], nel nostro caso a=0.0025 mentre b=0

		// Variabili da passare al plc iec
		   AF_PSE203A_MISURA_CH1 = (float) ( (0.0025 * APP_MISURA_PSE203A_CH1)+0 );
		   AF_PSE203A_MISURA_CH2 = (float) ( (0.0025 * APP_MISURA_PSE203A_CH2)+0 );
		// AF_PSE203A_MISURA_CH3 = (float) ( (0.0025 * APP_MISURA_CH3        )+0 );
		// AF_PSE203A_MISURA_CH4 = (float) ( (0.0025 * APP_MISURA_CH4        )+0 );

	}

	if(AF_FLUSSOMETRO_PRESS_PRES)
	{
		// APP_MISURA_PORTATA_FLUSS = appoggio misura del flusso d'aria [litri/min] letta da IOlink
		// APP_MISURA_TEMP_ARIA_FLUSS = appoggio misura della temperatura dell'aria [°C] letta da IOlink
		// APP_MISURA_PRESS_ARIA_FLUSS = appoggio misura della pressione dell'aria [bar] letta da IOlink

		// QUI IL CODICE SE NON RICHIESTA INVERSIONE DEI BYTE
		// APP_MISURA_PORTATA_FLUSS =    (short int) ( ( (APP_FLUSSO_BYTE_HIGH      << 8) & (0xFF00)) | (APP_FLUSSO_BYTE_LOW      & (0x00FF)) );
		// APP_MISURA_TEMP_ARIA_FLUSS =  (short int) ( ( (APP_TEMPERATURA_BYTE_HIGH << 8) & (0xFF00)) | (APP_TEMPERATURA_BYTE_LOW & (0x00FF)) );
		// APP_MISURA_PRESS_ARIA_FLUSS = (short int) ( ( (APP_PRESSIONE_BYTE_HIGH   << 8) & (0xFF00)) | (APP_PRESSIONE_BYTE_LOW   & (0x00FF)) );
                                                                                     
		// APP_DIAGN_OUTPUT_SW_FLUSS =   (short int) ( ( (APP_STATE_OUT_BYTE_HIGH   << 8) & (0xFF00)) | (APP_STATE_OUT_BYTE_LOW   & (0x00FF)) );


		// QUI IL CODICE SE RICHIESTA INVERTSIONE DEI BYTE (da verificare in macchina)
		APP_MISURA_PORTATA_FLUSS =    (short int) ( ( (APP_FLUSSO_BYTE_LOW      << 8) & (0xFF00)) | (APP_FLUSSO_BYTE_HIGH      & (0x00FF)) );
		APP_MISURA_TEMP_ARIA_FLUSS =  (short int) ( ( (APP_TEMPERATURA_BYTE_LOW << 8) & (0xFF00)) | (APP_TEMPERATURA_BYTE_HIGH & (0x00FF)) );
		APP_MISURA_PRESS_ARIA_FLUSS = (short int) ( ( (APP_PRESSIONE_BYTE_LOW   << 8) & (0xFF00)) | (APP_PRESSIONE_BYTE_HIGH   & (0x00FF)) );
                                                                                 
		APP_DIAGN_OUTPUT_SW_FLUSS =   (short int) ( ( (APP_STATE_OUT_BYTE_LOW   << 8) & (0xFF00)) | (APP_STATE_OUT_BYTE_HIGH   & (0x00FF)) );

		// Conversione dal valore letto sul registro al valore di flusso visualizzato sul display:
		// PD = valore di flusso letto sul registro (da process data)
		// Pr = valore di flusso a display
		// La conversione si ottiene applicando l'equazione di una retta:
		// Pr = a * PD + b
		// in cui, impostando il valore visualizzato a display in [litri/min], nel nostro caso a=0.25 mentre b=0

		AF_PORTATA_ARIA_FLUSS = (float) ( (0.25 * APP_MISURA_PORTATA_FLUSS)+0 );

		// Conversione dal valore letto sul registro al valore di flusso visualizzato sul display:
		// PD = valore di temperatura letto sul registro (da process data)
		// Pr = valore di temperatura a display
		// La conversione si ottiene applicando l'equazione di una retta:
		// Pr = a * PD + b
		// in cui, impostando il valore visualizzato a display in [°C], nel nostro caso a=0.1 mentre b=0

		AF_TEMP_ARIA_FLUSS = (float)  ( (0.1 * APP_MISURA_TEMP_ARIA_FLUSS)+0 );

		// Conversione dal valore letto sul registro al valore di pressione visualizzato sul display:
		// PD = valore di pressione letto sul registro (da process data)
		// Pr = valore di pressione a display
		// La conversione si ottiene applicando l'equazione di una retta:
		// Pr = a * PD + b
		// in cui, impostando il valore visualizzato a display in [bar], nel nostro caso a=0.01 mentre b=0
		
		AF_PRESSIONE_ARIA_FLUSS = (float) ( (0.01 * APP_MISURA_PRESS_ARIA_FLUSS)+0 );

		// E' stata programmata l'uscita 1 (OUT 1) come finestra di pressione tra 4 e 7 bar
		//if(APP_DIAGN_OUTPUT_SW_FLUSS & (0x0040))
		//   APP_INPUT_ARIA_PRES = 1;
		//else
		//	APP_INPUT_ARIA_PRES = 0;


		// N.B.--> usare la misura di pressione del flussometro come indicazione di aria presente per gestire allarme

	}
	else
	{
		APP_INPUT_ARIA_PRES = ARIA_PRES_I;
	}

	// Il sensore di temperatura su basamento TP3237 della IFM al momento non è legato al progetto connect, il valore letto non viene esposto
	// sul server OPCUA
	if(AF_SENS_TEMP_BASAMENTO_PRES)
	{
		// QUI IL CODICE SE NON RICHIESTA INVERTSIONE DEI BYTE
		// AF_TEMP_BASAM_IFM = (float) ( ( (APP_TEMP_BASAM_BYTE_HIGH<<8) & (0xFF00)) | (APP_TEMP_BASAM_BYTE_LOW & (0x00FF)) );

		// QUI IL CODICE SE RICHIESTA INVERTSIONE DEI BYTE (da verificare in macchina)
		   AF_TEMP_BASAM_IFM = (float) (( ( ( (APP_TEMP_BASAM_BYTE_LOW << 8) & (0xFF00)) | (APP_TEMP_BASAM_BYTE_HIGH & (0x00FF)) ) / 10.0) + AF_OFFSET_TEMP_BASAM_IFM);

	}
}