

#ifndef CONTATORI_BRIDGE_INCLUDED
#define CONTATORI_BRIDGE_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : contatori_bridge.h
// AUTORE      : Medici Stefano
// DESCRIZIONE : Gestione contatori su Bridge Isac
//----------------------------------------------------------------------------



// #define CNT_MM_INDEX							10		// Indice della variabile retentiva M per la verifica della verginità del Bridge

#define CNT_BRIDGE_CONTROL_WORD_DEFAULT			16371	// = 0011 1111 1111 0011 (0=contatore eventi, 1=contatore a tempo)
														//   |->contatore 16   |->Contatore 1
#define CNT_MAX_NUM								16		// Numero massimo contatori

#define CNT_CONVERSIONE							10.0	// Conversione per passare da conteggi a secondi

// __________ Parametri comunicazione ETHERCAT __________________________________

#define CNT_WRITE_TIMEOUT						150		//Timeout scrittura [msec]
#define CNT_READ_TIMEOUT						150		//Timeout lettura [msec]



// __________ Indirizzi ETHERCAT __________________________________

#define BRIDGE_ADDRESS							"ethercat|1001"	//Indirizzo Ethercat Bridge con contatori


#define CNT_PDO_CONTROL_INDEX					0x5014		// Indice PDO definizione del tipo di contatori
	#define CNT_PDO_CONTROL_SUBINDEX			1			// Sottoindice:1

#define CNT_PDO_ACCESS_PASSWORD_INDEX			0x5014		// Indice PDO delle password (UDINT)
	#define CNT_PDO_ACCESS_PASSWORD_SUBINDEX_1	2			// Sottoindice password contatori 1,2,3,4
	#define CNT_PDO_ACCESS_PASSWORD_SUBINDEX_2	3			// Sottoindice password contatori 5,6,7,8
	#define CNT_PDO_ACCESS_PASSWORD_SUBINDEX_3	4			// Sottoindice password contatori 9,10,11,12,
	#define CNT_PDO_ACCESS_PASSWORD_SUBINDEX_4	5			// Sottoindice password contatori 13,14,15,16


#define CNT_PDO_VALUE_INDEX						0x5015		// Indirizzo PDO dei contatori (il valore 0x5011:0 è RO e ritorna 16) (UDINT)
	#define CNT_PDO_VALUE_SUBINDEX_1			1			// Sottoindice contatore 1 
	#define CNT_PDO_VALUE_SUBINDEX_2			2			// Sottoindice contatore 2 
	#define CNT_PDO_VALUE_SUBINDEX_3			3			// Sottoindice contatore 3 
	#define CNT_PDO_VALUE_SUBINDEX_4			4			// Sottoindice contatore 4 
	#define CNT_PDO_VALUE_SUBINDEX_5			5			// Sottoindice contatore 5 
	#define CNT_PDO_VALUE_SUBINDEX_6			6			// Sottoindice contatore 6 
	#define CNT_PDO_VALUE_SUBINDEX_7			7			// Sottoindice contatore 7 
	#define CNT_PDO_VALUE_SUBINDEX_8			8			// Sottoindice contatore 8 
	#define CNT_PDO_VALUE_SUBINDEX_9			9			// Sottoindice contatore 9 
	#define CNT_PDO_VALUE_SUBINDEX_10			10			// Sottoindice contatore 10 
	#define CNT_PDO_VALUE_SUBINDEX_11			11			// Sottoindice contatore 11 
	#define CNT_PDO_VALUE_SUBINDEX_12			12			// Sottoindice contatore 12 
	#define CNT_PDO_VALUE_SUBINDEX_13			13			// Sottoindice contatore 13 
	#define CNT_PDO_VALUE_SUBINDEX_14			14			// Sottoindice contatore 14 
	#define CNT_PDO_VALUE_SUBINDEX_15			15			// Sottoindice contatore 15 
	#define CNT_PDO_VALUE_SUBINDEX_16			16			// Sottoindice contatore 16 



//________ Password __________________________

#define CNT_PASSWORD_BASE_1						0			// Password default contatori 1,2,3,4
#define CNT_PASSWORD_BASE_2						0			// Password default contatori 5,6,7,8
#define CNT_PASSWORD_BASE_3						0			// Password default contatori 9,10,11,12,
#define CNT_PASSWORD_BASE_4						0			// Password default contatori 13,14,15,16


#define CNT_PASSWORD_EMMEGISOFT_1				101			// Password emmegi contatori 1,2,3,4
#define CNT_PASSWORD_EMMEGISOFT_2				202			// Password emmegi contatori 5,6,7,8
#define CNT_PASSWORD_EMMEGISOFT_3				303			// Password emmegi contatori 9,10,11,12,
#define CNT_PASSWORD_EMMEGISOFT_4				404			// Password emmegi contatori 13,14,15,16




// _____ Macchina a stati ___________________

#define CNT_BRIDGE_STATE_INIT					0
#define CNT_BRIDGE_STATE_OPEN					10
#define CNT_BRIDGE_CHECK_IF_CLOSE				20
#define CNT_BRIDGE_STATE_CLOSE					22
#define CNT_BRIDGE_STATE_WAIT_BEFOR_REOPEN		24

#define CNT_BRIDGE_STATE_IDLE					30

#define CNT_BRIDGE_STATE_INI_PASSWORD_1			100
#define CNT_BRIDGE_STATE_INI_PASSWORD_2			101
#define CNT_BRIDGE_STATE_INI_PASSWORD_3			102
#define CNT_BRIDGE_STATE_INI_PASSWORD_4			103

#define CNT_BRIDGE_STATE_SET_PASSWORD_1			104
#define CNT_BRIDGE_STATE_SET_PASSWORD_2			105
#define CNT_BRIDGE_STATE_SET_PASSWORD_3			106
#define CNT_BRIDGE_STATE_SET_PASSWORD_4			107
#define CNT_BRIDGE_STATE_SET_CONTROL_WORD		108

#define CNT_BRIDGE_STATE_END_INI				109

#define CNT_BRIDGE_STATE_COMMAND_WRITE_START	120
#define CNT_BRIDGE_STATE_COMMAND_WRITE_CONT		121
#define CNT_BRIDGE_STATE_COMMAND_WRITE_END		122

#define CNT_BRIDGE_STATE_RESET_ALL_START		130
#define CNT_BRIDGE_STATE_RESET_ALL_LOOP			131

#define CNT_BRIDGE_STATE_READ_CONT_START		140
#define CNT_BRIDGE_STATE_READ_CONT_LOOP			141

#define CNT_BRIDGE_STATE_WRITE					800

#define CNT_BRIDGE_STATE_READ					900

#define CNT_BRIDGE_STATE_ERR_OPENING			1000
#define CNT_BRIDGE_STATE_ERR_READING			1010
#define CNT_BRIDGE_STATE_ERR_WRITING			1020
#define CNT_BRIDGE_STATE_ERR_COMMAND			1030
#define CNT_BRIDGE_STATE_ERR_CLOSING			1040

#define CNT_BRIDGE_WRITE_CONT_STATE_IDLE		10
#define CNT_BRIDGE_WRITE_CONT_STATE_WRITE		20
#define CNT_BRIDGE_WRITE_CONT_STATE_3			30




#define CNT_BRIDGE_REOPEN_DELAY_INI_DEFAULT		300		// Valore defautl per contatore ritardo prima di riprovare ad aprore la comunicazione con il Bridge
#define CNT_DELAY_POLLING_CONT_INI_DEFAULT		1000	// Valore di default per il periodo di polling dei contatori [msec]



//________ Comandi ____________________

//Lista dei possibili comandi
#define CNT_COMMAND_SET_CONT					10		//Scrive la R_CNT_VALUE nel contatore R_CNT_INDEX (per Drill solo contatori 5-16)
#define CNT_COMMAND_RESET_ALL					99		//Azzera tutti i contatori (non accessibile da Drill)

//Lista dei possibili risultati dei comandi
#define CNT_RESULT_COMMAND_STARTED				1
#define CNT_RESULT_COMMAND_OK					2
#define CNT_RESULT_COMMAND_KO					-1




#endif // CONTATORI_BRIDGE_INCLUDED
