#ifndef CONTATORI_BRIDGE_SAVE_FILE_H_INCLUDED
#define CONTATORI_BRIDGE_SAVE_FILE_H_INCLUDED

/*

        ---------------------------------------------
        TITOLO:         CONTATORI_BRIDGE_SAVE_FILE.H
        ---------------------------------------------
        CLIENTE:
        ---------------------------------------------
        AUTORE:         Medici Stefano
        ---------------------------------------------

*/

//Attenzione, in funzione della cartella "base" configurata sulla macchina occorre definire in modo coerente il percorso
// SE base = "D:\Isac"			-> CB_FILE_NAME = "%base%\\usertar\\Counters.csv"
// SE base = "D:\Isac\Lav\Lav"	-> CB_FILE_NAME = "%base%\\..\\..\\usertar\\Counters.csv"

//COMET S4 : (HMI > SETTING > OMFILESETTING)  "%base% = D:\isac

#define CB_FILE_NAME   "%base%\\usertar\\Counters.csv" // Nome file contenente i tempi parziali

#define CB_BUFFER_SIZE	512


void contatori_bridge_create_string (void);
void contatori_bridge_save_file (void);
void contatori_bridge_save_file_pon (void);

#define CB_STATUS_IDLE			0
#define CB_STATUS_START			10
#define CB_STATUS_OPEN			20
#define CB_STATUS_WRITE			30
#define CB_STATUS_ABORT			40
#define CB_STATUS_CLOSE			50

#define CB_STATUS_TRYCLOSE_1	200
#define CB_STATUS_TRYCLOSE_2	201
#define CB_STATUS_TRYCLOSE_3	202

#define CB_STATUS_OPEN_ERR		1000
#define CB_STATUS_WRITE_ERR		1001
#define CB_STATUS_ABORT_ERR		1002
#define CB_STATUS_CLOSE_ERR		1003
#define CB_STATUS_WAIT_OPEN_ERR		1004
#define CB_STATUS_WAIT_WRITE_ERR	1005
#define CB_STATUS_WAIT_ABORT_ERR	1006
#define CB_STATUS_WAIT_CLOSE_ERR	1007
#define CB_STATUS_WAIT_ABORT2_ERR	1008
#define CB_STATUS_WAIT_CLOSE2_ERR	1009


#define CB_COMMAND_IDLE			0
#define CB_COMMAND_START		10
#define CB_COMMAND_RESET		20


#endif // CONFTIME_INC_INCLUDED

