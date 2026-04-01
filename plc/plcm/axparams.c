//----------------------------------------------------------------------------
// TITOLO      : axparams.c
// AUTORE      : Mattia Grandi
// DESCRIZIONE : Funzioni di supporto per caricamento / lettura parametri assi
//----------------------------------------------------------------------------
#include "all.inc"


void axparams(void) 
{
    static RTPLC_STATUS status = 0;
    static CmdAxisStruct s = {0};
    RTPLC_STATUS fbResult = FB_EXIT_FAILURE;

    //if (fbReset) {
    //    FB_RESET();
    //    status = 0;
    //    FB_EXIT(FB_EXIT_SUCCESS);
    //}

    switch (status) {
        case 0:
            if (REQ_FF_SPINDLE_100) {
                setFeedForward(0, AX_Q_CH0, 100, &s);
                JUMP_STATUS(status, 10, "Richiesto feed forward mandrino al 100%%");
            } else if (REQ_FF_SPINDLE_R) {
                setFeedForward(0, AX_Q_CH0, R[R_F_F_SPINDLE], &s);
                JUMP_STATUS(status, 20, "Richiesto feed forward mandrino al %f", R[R_F_F_SPINDLE]);
            } else if (Mg_MC(262)) {
                setAxisCorrection(0, AX_X_CH0, FALSE, &s);
                JUMP_STATUS(status, 30, "Richiesta disabilitazione correzioni asse X");
            } else if (Mg_MC(263)) {
                if (FTB(R[R_ABIL_CORR_ASSE_X])) {
                    setAxisCorrection(0, AX_X_CH0, TRUE, &s);
                    JUMP_STATUS(status, 40, "Richiesta abilitazione correzioni asse X");
                } else {
                    RESET_STATUS(status, "Ignoro abilitazione correzioni asse X come da confmac");
                    Mr_MC(263);
                }
            } else if (Mg_MC(260)) {
                setAxisCorrection(0, AX_A_CH0, FALSE, &s);
                JUMP_STATUS(status, 50, "Richiesta disabilitazione correzioni asse A");
            } else if (Mg_MC(261)) {
                if (FTB(R[R_ABIL_CORR_ASSE_A])) {
                    setAxisCorrection(0, AX_A_CH0, TRUE, &s);
                    JUMP_STATUS(status, 60, "Richiesta abilitazione correzioni asse A");
                } else {
                    RESET_STATUS(status, "Ignoro abilitazione correzioni asse A come da confmac");
                    Mr_MC(261);
                }
            }else if (Mg_MC(268)) {
                setAxisCorrection(0, AX_C_CH0, FALSE, &s);
                JUMP_STATUS(status, 110, "Richiesta disabilitazione correzioni asse C");
            } else if (Mg_MC(269)) {
                if (FTB(R[R_ABIL_CORR_ASSE_C])) {
                    setAxisCorrection(0, AX_C_CH0, TRUE, &s);
                    JUMP_STATUS(status, 120, "Richiesta abilitazione correzioni asse C");
                } else {
                    RESET_STATUS(status, "Ignoro abilitazione correzioni asse C come da confmac");
                    Mr_MC(269);
                }
            } else if (Mg_MC(306)) {
                setAxisCorrection(0, AX_Y_CH0, FALSE, &s);
                JUMP_STATUS(status, 130, "Richiesta disabilitazione correzioni asse Y");
            } else if (Mg_MC(307)) {
                if (FTB(R[R_ABIL_CORR_ASSE_Y])) {
                    setAxisCorrection(0, AX_Y_CH0, TRUE, &s);
                    JUMP_STATUS(status, 140, "Richiesta abilitazione correzioni asse Y");
                } else {
                    RESET_STATUS(status, "Ignoro abilitazione correzioni asse Y come da confmac");
                    Mr_MC(307);
                }
            } else if (Mg_MC(308)) {
                setAxisCorrection(0, AX_Z_CH0, FALSE, &s);
                JUMP_STATUS(status, 150, "Richiesta disabilitazione correzioni asse Z");
            } else if (Mg_MC(309)) {
                if (FTB(R[R_ABIL_CORR_ASSE_Z])) {
                    setAxisCorrection(0, AX_Z_CH0, TRUE, &s);
                    JUMP_STATUS(status, 160, "Richiesta abilitazione correzioni asse Z");
                } else {
                    RESET_STATUS(status, "Ignoro abilitazione correzioni asse Z come da confmac");
                    Mr_MC(309);
                }
            }
            break;

        case 10:
        case 20:
        case 30:
        case 40:
        case 50:
        case 60:
        case 70:
        case 80:
        case 90:
        case 100:
        case 110:
        case 120:
        case 130:
        case 140:
        case 150:
        case 160:
        case 170:
			fbResult = AxisCmd(s.channel, s.axis, s.command, &(s.param));
            if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } else {
                NEXT_STATUS(status, "Inviato comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            }
            break;

        case 11:
        case 21:
        case 31:
        case 41:
        case 51:
        case 61:
        case 71:
        case 81:
        case 91:
        case 101:
        case 111:
        case 121:
        case 131:
        case 141:
        case 151:
        case 161:
        case 171:
			fbResult = GetAxisCmdResult(s.channel, s.axis, &s.param);
            if (FB_SUCCESS(fbResult)) {
                NEXT_STATUS(status, "Eseguito comando (%d) canale (%d) asse (%d) risultato parametri (%f,%f,%f,%f)", 
                    s.command, s.channel, s.axis,
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s.command, s.channel, s.axis, 
                    s.param.param[0], s.param.param[1], s.param.param[2], s.param.param[3]);
            }
            break;

        case 12:
            REQ_FF_SPINDLE_100 = 0;
            RESET_STATUS(status, "Feed forward mandrino al 100%%");
            break;
        case 22:
            REQ_FF_SPINDLE_R = 0;
            RESET_STATUS(status, "Feed forward mandrino al %f", R[R_F_F_SPINDLE]);
            break;
        case 32:
            Mr_MC(262);
            RESET_STATUS(status, "Correzioni asse X disabilitate");
            break;
        case 42:
            Mr_MC(263);
            RESET_STATUS(status, "Correzioni asse X abilitate");
            break;
        case 52:
            Mr_MC(260);
            RESET_STATUS(status, "Correzioni asse A disabilitate");
            break;
        case 62:
            Mr_MC(261);
            RESET_STATUS(status, "Correzioni asse A abilitate");
            break;  
        case 72:
            break;
        case 82:
            break;
        case 92:
            break;
        case 102:
            break;
        case 112:
            Mr_MC(268);
            RESET_STATUS(status, "Correzioni asse C disabilitate");
            break;
        case 122:
            Mr_MC(269);
            RESET_STATUS(status, "Correzioni asse C abilitate");
            break;
        case 132:
            Mr_MC(306);
            RESET_STATUS(status, "Correzioni asse Y disabilitate");
            break;
        case 142:
            Mr_MC(307);
            RESET_STATUS(status, "Correzioni asse Y abilitate");
            break;
        case 152:
            Mr_MC(308);
            RESET_STATUS(status, "Correzioni asse Z disabilitate");
            break;
        case 162:
            Mr_MC(309);
            RESET_STATUS(status, "Correzioni asse Z abilitate");
            break;

        default:
            RESET_STATUS(status, "");
            break;
    }
}


RTPLC_STATUS getParam(CmdAxisStruct* s, BOOL fbReset)
{
    static RTPLC_STATUS status = 0;
    RTPLC_STATUS fbResult = FB_EXIT_FAILURE;

    FB_ENTER();

    if (fbReset) {
        FB_RESET();
        status = 0;
        FB_EXIT(FB_EXIT_SUCCESS);
    }

    switch (status) {
        case 0:
            NEXT_STATUS(status, "");

        case 1:
			fbResult = AxisCmd(s->channel, s->axis, s->command, &s->param);
            if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s->command, s->channel, s->axis, 
                    s->param.param[0], s->param.param[1], s->param.param[2], s->param.param[3]);
            } else {
                NEXT_STATUS(status, "");
            }
            break;

        case 2:
			fbResult = GetAxisCmdResult(s->channel, s->axis, &s->param);
            if (FB_SUCCESS(fbResult)) {
                *s->outValue = s->param.param[0];
                RESET_STATUS(status, "");
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s->command, s->channel, s->axis, 
                    s->param.param[0], s->param.param[1], s->param.param[2], s->param.param[3]);
            }
            break;

        default:
            break;
    }

    FB_EXIT(status);
}


RTPLC_STATUS setParam(CmdAxisStruct* s, BOOL fbReset)
{
    static RTPLC_STATUS status = 0;
    RTPLC_STATUS fbResult = FB_EXIT_FAILURE;

    FB_ENTER();

    if (fbReset) {
        FB_RESET();
        status = 0;
        FB_EXIT(FB_EXIT_SUCCESS);
    }

    switch (status) {
        case 0:
            NEXT_STATUS(status, "");

        case 1:
			fbResult = AxisCmd(s->channel, s->axis, s->command, &s->param);
            if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore (%d) su invio comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s->command, s->channel, s->axis, 
                    s->param.param[0], s->param.param[1], s->param.param[2], s->param.param[3]);
            } else {
                NEXT_STATUS(status, "");
            }
            break;

        case 2:
			fbResult = GetAxisCmdResult(s->channel, s->axis, &s->param);
            if (FB_SUCCESS(fbResult)) {
                RESET_STATUS(status, "Eseguito comando (%d) canale (%d) asse (%d) con parametri (%f,%f,%f,%f)", 
                    s->command, s->channel, s->axis,
                    s->param.param[0], s->param.param[1], s->param.param[2], s->param.param[3]);
            } else if (FB_FAILURE(fbResult)) {
                ERROR_STATUS(status, "Errore (%d) su lettura risultato comando (%d) canale (%d) asse (%d) parametri (%f,%f,%f,%f)", 
                    RTPLC_STATUS2W32(fbResult), s->command, s->channel, s->axis, 
                    s->param.param[0], s->param.param[1], s->param.param[2], s->param.param[3]);
            }
            break;

        default:
            break;
    }

    FB_EXIT(status);
}


void getJerk(USHORT channel, USHORT axis, double *jerkValue, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_GETPARAM;
    s->param.param[0] = axgpcJerk;
    s->outValue = jerkValue;
}

void setJerk(USHORT channel, USHORT axis, double jerkValue, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_PUTPARAM;
    s->param.param[0] = axgpcJerk;
    s->param.param[1] = jerkValue;
}

void getEncRatio(USHORT channel, USHORT axis, double *ratioValue, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_GETPARAM;
    s->param.param[0] = axgpcEncoderRatio;
    s->outValue = ratioValue;
}

void setEncRatio(USHORT channel, USHORT axis, double ratioValue, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_PUTPARAM;
    s->param.param[0] = axppcEncoderRatio;
    s->param.param[1] = ratioValue;
}

void getFeedForward(USHORT channel, USHORT axis, double *feedForward, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_GETPARAM;
    s->param.param[0] = axgpcFeedForward;
    s->outValue = feedForward;
}

void setFeedForward(USHORT channel, USHORT axis, double feedForward, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_PUTPARAM;
    s->param.param[0] = axppcFeedForward;
    s->param.param[1] = feedForward;
}

void setAxisCorrection(USHORT channel, USHORT axis, BOOL enable, CmdAxisStruct* s) {
    s->channel = channel;
    s->axis = axis;
    s->command = OMCNC_CMD_SET_CORRECTION;
    s->param.param[0] = enable ? 1.0 : 0.0;
}
