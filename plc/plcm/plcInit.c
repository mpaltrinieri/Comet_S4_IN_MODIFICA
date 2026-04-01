//ADDIN_DEAD_CODE
#define _INTERNAL_GENERATION
// 
#include "all.inc"

/*
The plcInit routine
*/
void RTPLC_ROUTINE stub_plcInit(LPVOID data, PPLCINIT_LOCVARS locvars) 
{
    plcStatus = 0;    
	#ifdef _DEBUG
	waitDebugger = RTPLC_TRUE;
	#endif
}

void RTPLC_ROUTINE plcInit(LPVOID data) {
  PULONG pt = (PULONG)data;
  PPLCINIT_LOCVARS pstruct = (PPLCINIT_LOCVARS)(pt + 1);
  stub_plcInit((LPVOID)(*pt), pstruct);
}
