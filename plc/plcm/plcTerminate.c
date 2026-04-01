#define _INTERNAL_GENERATION

#include "all.inc"

/*
The plcTerminate routine 
*/
void RTPLC_ROUTINE stub_plcTerminate(LPVOID data, PPLCTERMINATE_LOCVARS locvars) 
{
#if defined(GIANO_DEFINED) || defined(GIANO_DEFINED_71)
    ScheCmd2_plcClose();
    ScheCmd2_close(g_Handle[0]);   // Gestore multiprocesso SX
    ScheCmd2_close(g_Handle[1]);   // Gestore multiprocesso DX
#endif
    //endSharedMem();

    plcStatus = 0;
}

void RTPLC_ROUTINE plcTerminate(LPVOID data) {
  PULONG pt = (PULONG)data;
  PPLCTERMINATE_LOCVARS pstruct = (PPLCTERMINATE_LOCVARS)(pt + 1);
  stub_plcTerminate((LPVOID)(*pt), pstruct);
}
