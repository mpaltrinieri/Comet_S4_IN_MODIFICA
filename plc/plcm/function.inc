#ifndef FUNCTION_INC_INCLUDED
#define FUNCTION_INC_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : function.inc
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Definizione funzioni PLC
//----------------------------------------------------------------------------

void appoggio_in            (void);
void appoggio_out           (void);

void  allarmi_ethercat_assi (void);
void  aspiratori            (void);
void  assi                  (void);
void  assi_standard         (void);
void  axparams              (void);
void  attivita_periodiche   (void);
void  battuta_precisione    (void);
void  cambut                (void);
void  central               (void);
void  cercainheads          (char STRINGA1[200]);
void  cercaintools          (char *STRINGA2, char *LETTURA);

void  check_battute         (void);
void  check_morse_aut       (void);

void  check_morse_trasc_x   (void);
void  check_posiz_morse     (void);
void  cktool                (void);
void  code_all              (void);
void  com_cnc               (void);
void  com_OPCUA_con_laser   (void);
void  conftime              (void);
void  contatori_bridge		(void);
void  count                 (int *OUT, int *IN, int *COUNT, int *MEMCOUNT, int *MEM, int NUM_PARAMETRO, char *COMMENTO);
void  crea_report           (void);
void  dati_utensile         (void);
void  debug                 (void);
void  enable_disable_filtri (void);
void  gestione_eventi_standard(unsigned long Num_evento);
void  eventi_industria_4_0  (void);
void  funz_m                (void);
void  funz_m_CH1            (void);
void  funz_m_CH2            (void);
void  funzman               (void);
void  gest_ava_utensili     (void);
void  gestione_morse        (void);
void  Gruppo_FRL_connect    (void);
void  jog_inc               (short NUMERO_ASSE, int FUNZ_MAN, int COM_A, int COM_B, int RP_COM_A, int RP_COM_B, int NO_OVERT, int *COM_AVA, int *COM_IND, int *MEM_AVA, int *MEM_IND, int *APP_INC1, int *APP_INC2, int *AB_ASSE);
void  jog_inc_MC            (PCNPLC_CNCCTRL cnctrl, PCNPLC_CNCSTATUS cncstatus, PCNPLC_HANDLE cnplchandle, short NUMERO_ASSE, int FUNZ_MAN, int COM_A, int COM_B, int RP_COM_A, int RP_COM_B, int NO_OVERT, int *COM_AVA, int *COM_IND, int *MEM_AVA, int *MEM_IND, int *APP_INC1, int *APP_INC2, int *AB_ASSE);
void  iomap                 (PPLCMAIN_LOCVARS locvars, BOOL direction);
void  led_ripari            (void);
void  lubrica               (void);
void  mandrino              (void);
void  marposs               (PPLCMAIN_LOCVARS locvars);

void  modulo_sicurezza      (void);

BOOL  Mg_MC                 (int nFunzM);
void  Mr_MC                 (int nFunzM);

void movpiece(PPLCMAIN_LOCVARS locvars);

BOOL  PLCMg_MC              (int nFunzM);
void  PLCMr_MC              (int nFunzM);

void  mgpilot               (void);

void  multipezzo            (void);

void  Oil_level             (void);

void  OPCUA_dati            (void);

void  plc                   (PPLCMAIN_LOCVARS locvars);
void  readconf              (void);
void  res_mes               (void);

void read_params_asse_X(void);
void read_params_asse_Y(void);
void read_params_asse_Z(void);
void read_params_asse_A(void);

void read_params_asse_W(void);

void  read_SDO_minimotor    (void);
void  ricerca_morse_aut     (void);
void  ricerca_morse_trasc_x (void);
void  riparo                (void);
void  riposmor              (void);
void  sendStartCNC_CH1      (void);
void  sendStartCNC_CH2      (void);
void  shared_Mem_MC         (void);
void  simulazione           (void);
void  street_m              (void);
void  Syn_0_MC              (void);
void  Syn_0_MC_RESET_1_all  (void);
void  Syn_1_MC              (void);
void  testhlock				(void);
void  time_cal              (void);
void  time_out              (void);
void  uscite                (void);
void  uscite_standard       (void);
void  utensili              (void);
void  utensili_standard     (void);

void  battuta_sx1_simu      (void);
void  battuta_dx4_simu      (void);
void  mandrino_simu         (void);
void  rilev_morse_ax_X_simu (void);
void  riparo_simu           (void);

void  tavola_simu           (void);
void  testhlock             (void);
void  trasc_ax_X_simu       (void);

void  visiera_bassa_simu    (void);
void  visiera_alta_simu     (void);

void  volantino             (void);
      
#endif // FUNCTION_INC_INCLUDED
