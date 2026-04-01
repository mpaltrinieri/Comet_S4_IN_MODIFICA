#ifndef TEMP_INC_INCLUDED
#define TEMP_INC_INCLUDED
//----------------------------------------------------------------------------
// TITOLO      : temp.inc
// AUTORE      : Pecchi Andrea
// DESCRIZIONE : Definizione temporizzatori
//----------------------------------------------------------------------------

// Descrizione dei simbolici
//  T_  : numero temporizzatore
//  P_  : segnale pilota
//  RP_ : ritardo positivo
//  RN_ : ritardo negativo
//  DP_ : derivata positiva
//  DN_ : derivata negativa

// @ libero

extern void templc(void);

#define         T_AUXON                 0
#define         P_AUXON             SIG00
#define         RP_AUXON            RP_00
#define         RN_AUXON            RN_00
#define         DP_AUXON            DP_00
#define         DN_AUXON            DN_00

#define         T_FREE_01		        1

#define         T_PRES_ARIA             2
#define         P_PRES_ARIA         SIG02
#define         RP_PRES_ARIA        RP_02
#define         RN_PRES_ARIA        RN_02

#define         P_MANU              SIG03
#define         DP_MANU             DP_03
#define         DN_MANU             DN_03

#define         P_AUTO              SIG04
#define         RP_AUTO             RP_04
#define         DP_AUTO             DP_04

#define         T_STARTASP			   05
#define         P_STARTASP			SIG05
#define         RN_STARTASP			RN_05

#define         T_COMANDO_A             6
#define         P_COMANDO_A         SIG06
#define         RP_COMANDO_A        RP_06
#define         RN_COMANDO_A        RN_06
#define         DP_COMANDO_A        DP_06
#define         DN_COMANDO_A        DN_06

#define         T_COMANDO_B             7
#define         P_COMANDO_B         SIG07
#define         RP_COMANDO_B        RP_07
#define         RN_COMANDO_B        RN_07
#define         DP_COMANDO_B        DP_07
#define         DN_COMANDO_B        DN_07

#define         P_NVM_CH0           SIG08
#define         DP_NVM_CH0          DP_08

#define         T_START_CYCLE           9
#define         P_START_CYCLE       SIG09
#define         DP_START_CYCLE      DP_09
#define         RN_START_CYCLE      RN_09

#define         T_PON                  10
#define         P_PON               SIG10
#define         RP_PON              RP_10
#define         DP_PON              DP_10
#define         DN_PON              DN_10

#define         T_AUX_OSCILL           11
#define         P_AUX_OSCILL        SIG11
#define         RP_AUX_OSCILL       RP_11

#define         T_OSCILLATORE          12
#define         P_OSCILLATORE       SIG12
#define         RP_OSCILLATORE      RP_12
#define         DP_OSCILLATORE      DP_12

// Controllo solo i fronti della pressione del pulsante
#define         P_PRESSIONE_PLS_START_CYCLE			SIG13
#define         DP_PRESSIONE_PLS_START_CYCLE		DP_13
#define         DN_PRESSIONE_PLS_START_CYCLE		DN_13

#define         T_IMPRST_INV           14
#define         P_IMPRST_INV        SIG14
#define         RP_IMPRST_INV       RP_14

#define         T_LUBRICA_OFF          15
#define         P_LUBRICA_OFF       SIG15
#define         RP_LUBRICA_OFF      RP_15

#define         T_LUBRICA_ON           16
#define         P_LUBRICA_ON        SIG16
#define         RP_LUBRICA_ON       RP_16

#define         T_UT_AGGAN             17
#define         P_UT_AGGAN          SIG17
#define         RP_UT_AGGAN         RP_17
#define         RN_UT_AGGAN         RN_17
#define         DP_UT_AGGAN         DP_17

#define         T_UT_SGANC             18
#define         P_UT_SGANC          SIG18
#define         RP_UT_SGANC         RP_18
#define         RN_UT_SGANC         RN_18
#define         DP_UT_SGANC         DP_18
#define         DN_UT_SGANC         DN_18

#define         T_AUXPREA              19
#define         P_AUXPREA           SIG19
#define         RN_AUXPREA          RN_19

#define         T_OUTMAC_ABIL          20
#define         P_OUTMAC_ABIL       SIG20
#define         RP_OUTMAC_ABIL      RP_20
#define         DP_OUTMAC_ABIL      DP_20

#define         T_VEL_0                21
#define         P_VEL_0             SIG21
#define         RP_VEL_0            RP_21

#define         T_LAMP_PER_MESS          22
#define         P_LAMP_PER_MESS       SIG22
#define         RP_LAMP_PER_MESS      RP_22
#define         DP_LAMP_PER_MESS      DP_22

#define         T_STOP_INV             23
#define         P_STOP_INV          SIG23
#define         RP_STOP_INV         RP_23

#define         P_MANDR_DISALIM     SIG24
#define         DP_MANDR_DISALIM    DP_24

#define         T_ALIM_PRES            25
#define         P_ALIM_PRES         SIG25
#define         RP_ALIM_PRES        RP_25

#define         T_RIP_CH               26
#define         P_RIP_CH            SIG26
#define         RP_RIP_CH           RP_26


#define         T_START_INV            28
#define         P_START_INV         SIG28
#define         RP_START_INV        RP_28
#define         DP_START_INV        DP_28

#define         T_IMP_SBL_RITENUTA     29
#define         P_IMP_SBL_RITENUTA  SIG29
#define         RN_IMP_SBL_RITENUTA RN_29


#define         P_FRONTE_ALLARMI				SIG30
#define         DP_FRONTE_ALLARMI				DP_30

#define         T_START_STRINGA					   31
#define         P_START_STRINGA					SIG31
#define         RP_START_STRINGA			    RP_31

#define         P_FRONTE_STRINGA				SIG32
#define         DP_FRONTE_STRINGA			    DP_32

#define         P_START_SX						SIG33
#define         DP_START_SX						DP_33
#define         DN_START_SX						DN_33

#define         P_START_DX						SIG34
#define         DP_START_DX						DP_34
#define         DN_START_DX						DN_34

#define         T_AUX_OSCFAST					   37
#define         P_AUX_OSCFAST					SIG37
#define         RP_AUX_OSCFAST					RP_37

#define         T_OSCFAST				  		   38
#define         P_OSCFAST						SIG38
#define         RP_OSCFAST						RP_38

#define         T_CONDIZ_AX_OK                     43
#define         P_CONDIZ_AX_OK                  SIG43
#define         RP_CONDIZ_AX_OK                 RP_43

#define         P_RIT_PON                       SIG45
#define         DP_RIT_PON                      DP_45

#define         T_LIV_LUB_NOT_BASSO				   46
#define         P_LIV_LUB_NOT_BASSO				SIG46 
#define         RP_LIV_LUB_NOT_BASSO			RP_46

#define         T_LIV_LUB_NOT_ALTO				   48
#define         P_LIV_LUB_NOT_ALTO				SIG48 
#define         RP_LIV_LUB_NOT_ALTO				RP_48

#define         T_BORDO_SENSIB_OK				   49
#define         P_BORDO_SENSIB_OK				SIG49
#define         RN_BORDO_SENSIB_OK				RN_49


#define          T_CHECK_BATTERY_ON				   50
#define          P_CHECK_BATTERY_ON				SIG50
#define         RP_CHECK_BATTERY_ON				RN_50

#define          T_CHECK_BATTERY_OFF			   51
#define          P_CHECK_BATTERY_OFF			SIG51
#define         RP_CHECK_BATTERY_OFF			RN_51

#define         T_CKTOOL                           52
#define         P_CKTOOL                        SIG52
#define         RP_CKTOOL                       RP_52

#define         P_PRESETTER                     SIG53
#define         DP_PRESETTER                    DP_53

#define         T_START_MARPOSS					   54
#define         P_START_MARPOSS					SIG54
#define         RP_START_MARPOSS				RP_54
#define         DP_START_MARPOSS				DP_54

#define         T_POT_ZERO						   55
#define         P_POT_ZERO						SIG55 
#define         RP_POT_ZERO						RP_55

#define         P_RIL_MORSE_X					SIG60
#define         DP_RIL_MORSE_X				    DP_60

#define         T_MICRO_MORSA_ASSENTE_X			   61
#define         P_MICRO_MORSA_ASSENTE_X			SIG61 
#define         RP_MICRO_MORSA_ASSENTE_X		RP_61

#define			T_TRASC_INSERITO_X				   62
#define         P_TRASC_INSERITO_X				SIG62 
#define         RP_TRASC_INSERITO_X				RP_62


#define     	T_BATT_PREC_INS                    65
#define         P_BATT_PREC_INS                 SIG65
#define         RP_BATT_PREC_INS                RP_65

#define     	T_ALL_BATT_PREC_NO_INS             66
#define         P_ALL_BATT_PREC_NO_INS          SIG66
#define         RP_ALL_BATT_PREC_NO_INS         RP_66

#define     	T_ALL_BATT_PREC_NO_DIS             67
#define         P_ALL_BATT_PREC_NO_DIS          SIG67
#define         RP_ALL_BATT_PREC_NO_DIS         RP_67

#define          T_MEM_INVERTER_KO                 68
#define          P_MEM_INVERTER_KO              SIG68
#define         RN_MEM_INVERTER_KO              RN_68

#define          T_START2_INV                      69
#define          P_START2_INV                   SIG69
#define         RN_START2_INV                   RN_69

#define          T_SCAMB_CAL_MANDR                 70
#define          P_SCAMB_CAL_MANDR              SIG70
#define         RP_SCAMB_CAL_MANDR              RP_70

// @ libero

#define         P_NVT_CH0						SIG72
#define         DP_NVT_CH0						DP_72

#define         T_VOL_ON		  				   73
#define         P_VOL_ON		                SIG73
#define         RP_VOL_ON	                    RP_73

#define         P_I_BLC_CH0						SIG74
#define         DN_I_BLC_CH0					DN_74

#define         T_MEM_MASCRIG					   75
#define         P_MEM_MASCRIG					SIG75
#define         RP_MEM_MASCRIG					RP_75

#define         T_LIVGRASS_NOK                     76
#define         P_LIVGRASS_NOK                  SIG76
#define         RP_LIVGRASS_NOK                 RP_76

#define         T_INGRASS_OFF                      77
#define         P_INGRASS_OFF                   SIG77
#define         RP_INGRASS_OFF                  RP_77
#define         DP_INGRASS_OFF                  DP_77

#define         T_INGRASS_ON                       78
#define         P_INGRASS_ON                    SIG78
#define         RP_INGRASS_ON                   RP_78
#define         DP_INGRASS_ON                   DP_78

#define         T_IMP_RESET                        80
#define         P_IMP_RESET                     SIG80
#define         RP_IMP_RESET                    RP_80

#define         T_AUX_INSER                        85
#define         P_AUX_INSER                     SIG85 
#define         RN_AUX_INSER                    RN_85

#define         P_I_BLC_CH1						SIG86
#define         DN_I_BLC_CH1					DN_86

#define         P_I_BLC_CH2						SIG87
#define         DN_I_BLC_CH2					DN_87


// @

#endif // TEMP_INC_INCLUDED
