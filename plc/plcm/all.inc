#ifndef ALL_INC_INCLUDED
#define ALL_INC_INCLUDED

// L'inclusione di tchar.h e stdlib.h non servirebbe ma, è necessaria. Evita che 
// "df_syn.inc" includa gli stessi file in una posizione dove conpatibility_routine_str.h 
// non può cambiare le definizioni di alcune funzioni di manipolazione delle stringhe.
// Se non si blocca questo processo rtplc.h, incluso da df_syn.inc, finisce per far 
// riferimento a dei simboli non definiti durante il collegamento dei file oggetto 
// del programma (macro hell).

#include <tchar.h>
#include <stdlib.h>
#include <conpatibility_routine_str.h> // Routines rinominate per manipolazione stringhe

#include <df_syn.inc>		// Provvede tutte le inclusioni
#include "compatibility_MC.h" //Include le definizioni per il multicanale

#include <rtplc.h>			// Inclusioni RTPLC
#include <rtplc_14_extensions.h> // Inclusioni RTPLC per accesso a Ethercat
#include <iosoptmod.h>           // Inclusioni per FB di accesso ai canali Ethercat

#include <omcan.h>          // Funzioni di comunicazione con canbus
#include <ScheCmd2.inc>
#include "common.inc"		// Definizioni, debug e miscellanee
#include "utils.h"			// Routines d'utilità per plc
#include "caricaconfmac.h"	// Caricamento confmac dopo RET
#include "caricafman.h"     // Caricamento funzioni manuali
#include "mgpilot.h"

#include "a.inc"
#include "m.inc"
#include "rdef.inc"
#include "cdef.inc"
#include "i_o.inc"
#include "temp.inc"
#include "assi.inc"

#include "timerssuppl.inc"
#include "timerssimu.inc"

#include "conf_mac.inc"
#include "function.inc"

#include "OPCUA_dati.inc"

#include "I_O_DEVICE_IOLINK.inc"

#endif // ALL_INC_INCLUDED
