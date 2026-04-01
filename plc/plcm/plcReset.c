#define _INTERNAL_GENERATION

#include "all.inc"

/*
The plcReset routine
*/
void RTPLC_ROUTINE stub_plcReset(LPVOID data, PPLCRESET_LOCVARS locvars) 
{
    plcStatus = 0;
	#ifdef _DEBUG
	waitDebugger = RTPLC_TRUE;
	#endif
}

void RTPLC_ROUTINE plcReset(LPVOID data) {
  PULONG pt = (PULONG)data;
  PPLCRESET_LOCVARS pstruct = (PPLCRESET_LOCVARS)(pt + 1);
  stub_plcReset((LPVOID)(*pt), pstruct);
}
