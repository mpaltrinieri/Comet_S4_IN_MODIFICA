#define _INTERNAL_GENERATION

#include "all.inc"

/*
The plcGestTasto routine
*/
void RTPLC_ROUTINE stub_plcGestTasto(PRTPLC_EXTCOMM_STRUCT data, PPLCGESTTASTO_LOCVARS locvars) 
{
    //TODO: inserire la corrispondenza tra il tasto vecchio e quello nuovo
    rec_tasto = (ULONG) data->code;
}

void RTPLC_ROUTINE plcGestTasto(PRTPLC_EXTCOMM_STRUCT data) {
  PULONG pt = (PULONG)data;
  PPLCGESTTASTO_LOCVARS pstruct = (PPLCGESTTASTO_LOCVARS)(pt + 1);
  stub_plcGestTasto((PRTPLC_EXTCOMM_STRUCT)(*pt), pstruct);
}
