#ifndef CARICACONFMAC_H_INCLUDED
#define CARICACONFMAC_H_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : caricaconfmac.h
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Gestione caricamento variabili da configurazione macchina
//----------------------------------------------------------------------------

#include <rtplc.h>

// Configurazione
#define CONFMAC_FILE_NAME       "%base%\\lav\\lav\\CONFMAC.CS4" // Percorso file delle variabili supplementari
#define CONFMAC_SEPARATOR       "\r\n"  // Separatore fra i record delle assegnazioni
#define CONFMAC_ERRORONPARSE    (FALSE) // Emetti un errore se non è possibile interpretare un token


// Export funzioni
extern RTPLC_STATUS processConfmac(BOOL reset);

#endif // CARICACONFMAC_H_INCLUDED
