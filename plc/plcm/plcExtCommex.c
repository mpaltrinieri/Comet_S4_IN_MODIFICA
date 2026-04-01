#define _INTERNAL_GENERATION

#include "all.inc"

/*
The commex routine
*/
void RTPLC_ROUTINE stub_plcExtCommex(PRTPLC_EXTCOMM_STRUCT data, PPLCEXTCOMMEX_LOCVARS locvars) 
{
    USHORT max = 256;

    // Il nuovo messaggio viene aggiunto in fondo alla coda
    if (rec_queuebottom >= ARRAY_SIZE(rec_code))
        return; //raggiunto il fondo della coda delle righe, messaggio perso
    rec_code[rec_queuebottom] = data->code;
    rec_datalen[rec_queuebottom] = (USHORT)data->datalen;
    if (data->datalen < max) max = (USHORT)data->datalen;
    memcpy (rec_comm[rec_queuebottom].rec_comm, data->data, max);
    rec_queuebottom++; //aumento del puntatore del fondo
    data->flags |= RTPLC_EXTCOMM_FINISH;
}

void RTPLC_ROUTINE plcExtCommex(PRTPLC_EXTCOMM_STRUCT data) {
  PULONG pt = (PULONG)data;
  PPLCEXTCOMMEX_LOCVARS pstruct = (PPLCEXTCOMMEX_LOCVARS)(pt + 1);
  stub_plcExtCommex((PRTPLC_EXTCOMM_STRUCT)(*pt), pstruct);
}
