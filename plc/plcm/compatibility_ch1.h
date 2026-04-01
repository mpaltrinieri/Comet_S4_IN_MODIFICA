#pragma once

#define	I_EME_CH1(x) AXCTRL_CH1[x].ctrlFlags.EME		/** Richiesta emergenza asse per l'asse di indice x */
#define	I_ANN_CH1(x) AXCTRL_CH1[x].ctrlFlags.ANN		/** Annulla richiesta di movimento in corso per l'asse di indice x */
#define	I_HLD_CH1(x) AXCTRL_CH1[x].ctrlFlags.HLD		/** Hold asse indipendente per l'asse di indice x  */
#define	I_BLM_CH1(x) AXCTRL_CH1[x].ctrlFlags.BLM		/** Asse bloccato meccanicamente per l'asse di indice x */
#define	I_LSR_CH1(x) AXCTRL_CH1[x].ctrlFlags.LSR		/** Richiesta di libera servo per l'asse di indice x */
#define	I_NAL_CH1(x) AXCTRL_CH1[x].ctrlFlags.NAL		/** Non fare blocco e allarme su cn per l'asse di indice x */
#define OVFRE_CH1(x) AXCTRL_CH1[x].overfre
//
//#define CHECKBIT(_sts_, _bit_)	((_sts_) & (_bit_) ? TRUE : FALSE)
//
#define	O_VLN_CH1(x) AXSTATUS_CH1[x].statusFlags.VLN /** Velocita' lenta asse on/off per l'asse di indice x */
#define	O_VMD_CH1(x) AXSTATUS_CH1[x].statusFlags.VMD	/** Velocita' media asse on/off per l'asse di indice x */
#define	O_VRP_CH1(x) AXSTATUS_CH1[x].statusFlags.VRP	/** Velocita' rapida asse on/off per l'asse di indice x */
#define	O_AOK_CH1(x) AXSTATUS_CH1[x].statusFlags.AOK	/** Asse x ok, non in allarme */
#define	O_ATZ_CH1(x) AXSTATUS_CH1[x].statusFlags.ATZ	/** Attenzione su asse x */
//
#define	O_MRK_CH1(x) AXSTATUS_CH1[x].statusFlags.MRK	/** Segnale di Marca ottica dell'asse di indice x */
#define	O_MCR_CH1(x) AXSTATUS_CH1[x].statusFlags.MCR	/** Segnale di Micro dell'asse di indice x */
#define	O_SRF_CH1(x) AXSTATUS_CH1[x].statusFlags.SRF	/** Segno riferimento (se 1 negativo) dell'asse di indice x */
#define	O_SEE_CH1(x) AXSTATUS_CH1[x].statusFlags.SEE	/** Set assi eseguito dell'asse di indice x */
#define	O_QMC_CH1(x) AXSTATUS_CH1[x].statusFlags.QMC	/** Su pxv c'e' quota commutazione micro per l'asse di indice x */
#define	O_CTG_CH1(x) AXSTATUS_CH1[x].statusFlags.CTG	/** Asse agganciato in contouring per l'asse di indice x */
#define	O_AGG_CH1(x) AXSTATUS_CH1[x].statusFlags.AGG	/** Asse x agganciato */
#define	O_CBG_CH1(x) AXSTATUS_CH1[x].statusFlags.CBG	/** Velocita di cambio gamma raggiunta per l'asse di indice x */
#define	O_AVV_CH1(x) AXSTATUS_CH1[x].statusFlags.AVV	/** Asse agganciato in velocita' per l'asse di indice x */
#define	O_VOK_CH1(x) AXSTATUS_CH1[x].statusFlags.VOK	/** Velocita' mandrino ok per l'asse di indice x */
#define	O_AGY_CH1(x) AXSTATUS_CH1[x].statusFlags.AGY	/** Asse agganciato in gantry per l'asse di indice x */
#define	O_IND_CH1(x) AXSTATUS_CH1[x].statusFlags.IND	/** Asse indietro per l'asse di indice x */
#define	O_MOT_CH1(x) AXSTATUS_CH1[x].statusFlags.MOT	/** Si e' registrato un movimento dell'asse x */
#define	O_MOV_CH1(x) AXSTATUS_CH1[x].statusFlags.MOV	/** Movimento in corso per l'asse di indice x */
//
#define	O_BLM_CH1(x) AXSTATUS_CH1[x].statusFlags2.BLM	/** Asse x bloccabile meccanicamente */
#define	O_LSR_CH1(x) AXSTATUS_CH1[x].statusFlags2.LSR	/** Asse x in libera servo */
#define	O_LEASED_CH1(x) AXSTATUS_CH1[x].statusFlags2.LEASED /** Asse x condiviso appartenente al canale */
#define	O_LEASED_NOTUSED_CH1(x) AXSTATUS_CH1[x].statusFlags2.LEASED_NOTUSED /** Asse x condiviso rilasciato dal canale */
//
// Segnali composti
#define	ABAX_CH1(x)	O_AGG_CH1(x)&&O_AOK_CH1(x)	/** Abilitazione aggancio asse */ 
//:ENDSECTION	//;dfsinplcFile4
//
/* Definizioni delle correzioni assi */
#define	I_CORRECTION0_CH1	AXCTRL_CH1[0].correction
#define	I_CORRECTION1_CH1	AXCTRL_CH1[1].correction
#define	I_CORRECTION2_CH1	AXCTRL_CH1[2].correction
#define	I_CORRECTION3_CH1	AXCTRL_CH1[3].correction
#define	I_CORRECTION4_CH1	AXCTRL_CH1[4].correction
#define	I_CORRECTION5_CH1	AXCTRL_CH1[5].correction
#define	I_CORRECTION6_CH1	AXCTRL_CH1[6].correction
#define	I_CORRECTION7_CH1	AXCTRL_CH1[7].correction
#define	I_CORRECTION8_CH1	AXCTRL_CH1[8].correction
#define	I_CORRECTION9_CH1	AXCTRL_CH1[9].correction
#define	I_CORRECTION10_CH1	AXCTRL_CH1[10].correction
#define	I_CORRECTION11_CH1	AXCTRL_CH1[11].correction
//
///* Definzioni Input virtuali del PLC (IsDigital) */
#define DI_BREAKON_CH1(x)		AXCTRL_CH1[x].ctrlFlags.BRAKEON	/** Abilitazione freno Mechatrolink per l'asse x */
#define DI_SERVON_CH1(x)		AXCTRL_CH1[x].ctrlFlags.SERVON	/** Abilitazione potenza Mechatrolink per l'asse x */
//
///* Definizioni Output virtuali del PLC (IsDigital) */
#define DO_POT_CH1(x)		AXSTATUS_CH1[x].statusFlags2.POT	/** Forward direction limit switch input */
#define DO_NOT_CH1(x)		AXSTATUS_CH1[x].statusFlags2.NOT	/** Reverse direction limit switch input */
#define DO_DEC_CH1(x)		AXSTATUS_CH1[x].statusFlags2.DEC	/** Deceleration limit limit switch input */
#define DO_PA_CH1(x)		0	/** Encoder Phase A signal input */
#define DO_PB_CH1(x)		0	/** Encoder Phase B signal input */
#define DO_PC_CH1(x)		0	/** Encoder Phase C signal input */
#define DO_EXT1_CH1(x)		AXSTATUS_CH1[x].statusFlags2.EXT1	/** External-1 latch signal input */
#define DO_EXT2_CH1(x)		AXSTATUS_CH1[x].statusFlags2.EXT2	/** External-2 latch signal input */
#define DO_EXT3_CH1(x)		AXSTATUS_CH1[x].statusFlags2.EXT3	/** External-3 latch signal input */
#define DO_BRK_CH1(x)		AXSTATUS_CH1[x].statusFlags2.BRK	/** Brake status output */
#define DO_PWR_CH1(x)		AXSTATUS_CH1[x].statusFlags2.PWR	/** Power stauts */
#define DO_SON_CH1(x)		AXSTATUS_CH1[x].statusFlags2.SON	/** Servo  power status */
#define DO_POS_ALIGNING_CH1(x)	AXSTATUS_CH1[x].statusFlags2.POS_ALIGNING	/** axis is in alignment movement */
#define DO_LOCK_CH1(x)		0	/** Locked status */
#define DO_MCKO_CH1(x)		(!O_AOK_CH1(x))	/** Servo Alarm */
#define DO_GEDIG_CH1(x)		1	/** All axes can be used as digital */
//
#define	I_BLC_CH1		CNCCTRL_CH1.BLC	/* Blocco a CNC (assi + mandrino) */
#define	I_BLCAX_CH1		CNCCTRL_CH1.BLCAX	/* Blocco assi CNC */
#define	I_FHOLD_CH1		CNCCTRL_CH1.FHOLD	/* Feed hold assi CNC */
#define	I_INIMM_CH1		CNCCTRL_CH1.INIMM	/* Richiesta esecuzione int immediato */
#define	I_INSIN_CH1		CNCCTRL_CH1.INSIN	/* Richiesta esecuzione int sincrono */
#define	I_INASI_CH1		CNCCTRL_CH1.INASI	/* Richiesta esecuzione int asincrono */
#define	I_RFHLD_CH1		CNCCTRL_CH1.RFHLD	/* Richiesta Feed hold per Time Out PLC	*/
#define	I_AXEJG3_CH1	CNCCTRL_CH1.SELECTED_AXVOL3	/* Sel. asse per terzo volantino (bit12-15)*/
//
////#define	I_TST  D1.byte.l	/* Codice tasto CNC */
#define	I_OVRAP_CH1		CNCCTRL_CH1.OVRAP	/* Override rapido */
//
#define	I_OVFED_CH1		CNCCTRL_CH1.OVFED	/* Override feed */
#define	I_OVSPE_CH1		CNCCTRL_CH1.OVSPE	/* Codice override speed */
//
#define	I_JS_R_CH1		CNCCTRL_CH1.JS_R	/* Richiesta jog di spazio in rapido */
#define	I_JS_L_CH1		CNCCTRL_CH1.JS_L	/* Richiesta jog di spazio in lavoro */
#define	I_JV_R_CH1		CNCCTRL_CH1.JV_R	/* Richiesta jog di velocita' in rapido */
#define	I_JV_L_CH1		CNCCTRL_CH1.JV_L	/* Richiesta jog di velocita' in lavoro */
//
#define	I_RME_CH1		CNCCTRL_CH1.RME		/* Input rotazione mandrino esterno */
#define	I_SRME_CH1		CNCCTRL_CH1.SRME	/* Senso rotazione mandr. esterno 1 = orario */
#define	I_GAM1_CH1		CNCCTRL_CH1.GAM1	/* Peso "1" per gamma inserita */
#define	I_GAM2_CH1		CNCCTRL_CH1.GAM2	/* Peso "2" per gamma inserita */
#define	I_GAM4_CH1		CNCCTRL_CH1.GAM4	/* Peso "4" per gamma inserita */
//
#define	O_BLC_CH1 	CNCSTATUS_CH1.BLC	/* CNC in blocco (assi+mandrino) */
#define	O_BLCAX_CH1	CNCSTATUS_CH1.BLCAX	/* CNC in blocco assi */
//
#define	O_AXFER_CH1	CNCSTATUS_CH1.AXFER	/* Assi cnc fermi */
#define	O_M01_CH1  	CNCSTATUS_CH1.M01	/* CNC in stop per M01 */
//
#define	O_SKIP_CH1 	CNCSTATUS_CH1.SKIP	/* CNC esegue skip */
#define	O_ESEC_CH1 	CNCSTATUS_CH1.ESEC	/* CNC in esecuzione */
//
#define	O_INIZ_CH1 	CNCSTATUS_CH1.INIZ	/* CNC in condizioni iniziali */
#define	O_LAV_CH1  	CNCSTATUS_CH1.LAV	/* Assi cnc in movimento in lavoro */
//
#define	O_RESET_CH1	CNCSTATUS_CH1.RESET	/* Esecuzione RESET  */
#define	O_ALLAR_CH1	CNCSTATUS_CH1.ALLAR	/* CNC in allarme */
//
#define	O_JPOS_CH1 	CNCSTATUS_CH1.JPOS	/* JOG + premuto */
#define	O_JNEG_CH1 	CNCSTATUS_CH1.JNEG	/* JOG - premuto */
//
#define	O_VOL1_CH1 	CNCSTATUS_CH1.VOL1	/* Volantino 1 agganciato */
//
#define	O_VOL2_CH1 	CNCSTATUS_CH1.VOL2	/* Volantino 2 agganciato */
#define	O_VOL3_CH1 	CNCSTATUS_CH1.VOL3	/* Volantino 3 agganciato */

#define	O_NOALL_CH1	CNCSTATUS_CH1.NOALL	/* Se 1 no blocco CNC per allarme */
				/* Fuori Soglia assi indipend.    */
#define	O_CUAE_CH1	CNCSTATUS_CH1.CUAE	/* Cambio utensile automatico escluso	*/
//
#define	O_SEM_CH1  	CNCSTATUS_CH1.SEM	/* CNC in manuale */
#define	O_AUT_CH1  	CNCSTATUS_CH1.AUT	/* CNC in automatico */
#define	O_MAN_CH1  	CNCSTATUS_CH1.MAN	/* CNC in JOG */
#define	O_JOG_CH1  	CNCSTATUS_CH1.JOG	/* CNC in JOG */
#define	O_RIP_CH1  	CNCSTATUS_CH1.RIP	/* CNC in riposizionamento */
#define	O_SET_CH1  	CNCSTATUS_CH1.SET	/* CNC in SET */
#define	O_EXE_CH1  	CNCSTATUS_CH1.EXE	/* CNC in modo esecuzione */
#define	O_CNT_CH1  	CNCSTATUS_CH1.CNT	/* CNC in continua */
#define	O_FND_CH1  	CNCSTATUS_CH1.FND	/* CNC in modo ricerca */
#define	O_INIMM_CH1	CNCSTATUS_CH1.INIMM	/* Int immediato pronto o in corso */
#define	O_INSIN_CH1	CNCSTATUS_CH1.INSIN	/* Int sincrono pronto o in corso */
#define	O_INASI_CH1	CNCSTATUS_CH1.INASI	/* Int asincrono pronto o in corso */
//
#define	O_M_CH1    	CNCSTATUS_CH1.M	/* Codice  f.a.  M */
//
#define	O_H_CH1  	CNCSTATUS_CH1.H	/* Codice f.a. H  */
//
#define	O_T_CH1  	CNCSTATUS_CH1.T	/* Codice f.a. T  */
//
#define	O_ATTEN_CH1	CNCSTATUS_CH1.ATTEN	/* Codice attenzione TOOL  */
//
#define	O_TDS_CH1  	CNCSTATUS_CH1.TDS		/* Codice f.a. t,d,s */
#define	O_CODGN_CH1 CNCSTATUS_CH1.CODGN	/* Codice parametro generico  */
#define O_IDXTT_CH1 CNCSTATUS_CH1.IDXTT	/* Nemero  record  letto nel file TT.TAB */ 

#define	O_CGEN_CH1 	CNCSTATUS_CH1.CGEN	/* Codice CNC : se = 1 tasto rifiutato */
#define	O_CODAL_CH1	CNCSTATUS_CH1.CODAL	/* Codice allarme CNC		 */
#define	O_CODAT_CH1	CNCSTATUS_CH1.CODAT   	/* Codice attenzione asse	 */
//
//
#define	O_GN_CH1 	CNCSTATUS_CH1.GN.dword		/* Parametro generico  */
#define	O_GNL_CH1	CNCSTATUS_CH1.GNL	/*    "		"	low */
#define	O_GNH_CH1	CNCSTATUS_CH1.GNH	/*    "		"	high */
//
#define	O_MMSTP_CH1	CNCSTATUS_CH1.MMSTP	/* Mamut non aggiorna watchdog */
//
#define	O_NVM_CH1  	CNCSTATUS_CH1.NVM	/* Nuova f.a.  M */
#define	O_NVH_CH1	CNCSTATUS_CH1.NVH	/* Nuova f.a. H */
#define	O_NVT_CH1  	CNCSTATUS_CH1.NVT	/* Nuova f.a.  T */
#define	O_NVGN_CH1	CNCSTATUS_CH1.NVGN	/* Nuovo parametro generico in output dal cnc */
#define	O_NVS_CH1  	CNCSTATUS_CH1.NVS	/* Nuova f.a. S */
#define	O_AUTHL_CH1 CNCSTATUS_CH1.AUTHL	/* Part program sospeso in automatico */
#define	O_AKTST_CH1 CNCSTATUS_CH1.AKTST	/* Ack del codice tasto in input su I_TASTC */
#define	O_AKT_CH1	CNCSTATUS_CH1.AKT	/* Ack alla nuova "t" da tci */
//
#define	_TST_AX_CH1	CNCSTATUS_CH1._TST_AX	/* Abilita test contatori assi		*/
#define	_NUM_AX_CH1 CNCSTATUS_CH1._NUM_AX	/* Numero asse con errore		*/
#define	_SGL_VEL_CH1 CNCSTATUS_CH1._SGL_VEL		/* Soglia velocita`			*/
#define	_CNT_ERR_CH1 CNCSTATUS_CH1._CNT_ERR		/* Contatore errori			*/
//
#define CODAF_CH1 	CNCSTATUS_CH1.CODAF	/* Codice funzione ausiliaria da eseguire */
#define	STRCONS_CH1	CNCSTATUS_CH1.STRCONS	/* Sincronismo per la funzione Ausiliaria */
#define ACKCONS_CH1	CNCSTATUS_CH1.ACKCONS	/* Fatto per la funzione ausiliaria */
//
#define pon_CH1		CNCSTATUS_CH1.pon
//	
#define	SEQVOL_CH1		CNCCTRL_CH1.SEQVOL	/* Sequenz. Gestione volantini */
#define	OVRAP_CH1		CNCCTRL_CH1.memOVRAP	/* Commutatore override rapido */
#define	OVFED_CH1	    CNCCTRL_CH1.memOVFED	/* Commutatore override feed */
#define	OVSPE_CH1	    CNCCTRL_CH1.memOVSPE	/* Commutatore override speed */
#define	AXEJOGM_CH1	    CNCCTRL_CH1.memAXEJOG	/* Commutatore selezione assi */
//
#define NuPosMag_CH1	CNPLCHANDLE_CH1.NuPosMag	/* numero posti di magazzino	%V11002			*/
#define NUPOSMAG_CH1	CNPLCHANDLE_CH1.NuPosMag	/* numero posti di magazzino  %V11002 */ // Per visualizzazione Sin. II
#define NuPosMed_CH1	CNPLCHANDLE_CH1.NuPosMed	/* numero posti di MEDIO	%V11003			*/
#define NUPOSMED_CH1	CNPLCHANDLE_CH1.NuPosMed	/* numero posti di MEDIO  %V11003 */ // Per visualizzazione Sin. II
#define NuPosGra_CH1	CNPLCHANDLE_CH1.NuPosGra	/* numero posti di LARGO	%V11004			*/
#define NUPOSGRA_CH1	CNPLCHANDLE_CH1.NuPosGra	/* numero posti di LARGO %V11004 */ // Per visualizzazione Sin. II
#define	StaPosMag_CH1	CNPLCHANDLE_CH1.StaPosMag
#define	STAPOSMAG_CH1	CNPLCHANDLE_CH1.StaPosMag
//
#define FATM_CH1	CNPLCHANDLE_CH1.FATM
#define FATH_CH1	CNPLCHANDLE_CH1.FATH
#define FATT_CH1	CNPLCHANDLE_CH1.FATT
#define FATGN_CH1	CNPLCHANDLE_CH1.FATGN
#define FATS_CH1	CNPLCHANDLE_CH1.FATS
#define FATTCI_CH1	CNPLCHANDLE_CH1.FATTCI
#define FATPLC_CH1	CNPLCHANDLE_CH1.FATPLC
//
#define AM03_CH1	CNPLCHANDLE_CH1.AM03
#define AM04_CH1	CNPLCHANDLE_CH1.AM04
#define AM05_CH1	CNPLCHANDLE_CH1.AM05
#define AM19_CH1	CNPLCHANDLE_CH1.AM19
#define AMCG_CH1	CNPLCHANDLE_CH1.AMCG
#define PSET_CH1	CNPLCHANDLE_CH1.PSET
#define G84_CH1 	CNPLCHANDLE_CH1.G84 
#define G184_CH1	CNPLCHANDLE_CH1.G184
#define NVM_CH1		CNPLCHANDLE_CH1.NVM
#define NVH_CH1		CNPLCHANDLE_CH1.NVH
#define NVT_CH1		CNPLCHANDLE_CH1.NVT
#define NVGN_CH1	CNPLCHANDLE_CH1.NVGN
#define NVS_CH1		CNPLCHANDLE_CH1.NVS
#define AUTHL_CH1	CNPLCHANDLE_CH1.AUTHL
#define AKTST_CH1	CNPLCHANDLE_CH1.AKTST
#define AKT_CH1		CNPLCHANDLE_CH1.AKT
//
#define	JS_R_CH1	CNPLCHANDLE_CH1.JS_R
#define JS_L_CH1	CNPLCHANDLE_CH1.JS_L
#define JV_R_CH1	CNPLCHANDLE_CH1.JV_R
#define JV_L_CH1	CNPLCHANDLE_CH1.JV_L
//
#define AXVOL1_CH1		CNPLCHANDLE_CH1.AXVOL1
#define AXVOL2_CH1		CNPLCHANDLE_CH1.AXVOL2
#define AXVOL3_CH1		CNPLCHANDLE_CH1.AXVOL3
#define S_VOL1_CH1		CNPLCHANDLE_CH1.S_VOL1
#define S_VOL2_CH1		CNPLCHANDLE_CH1.S_VOL2
#define S_VOL3_CH1		CNPLCHANDLE_CH1.S_VOL3
#define MS_VOL1_CH1		CNPLCHANDLE_CH1.MS_VOL1
#define MS_VOL2_CH1		CNPLCHANDLE_CH1.MS_VOL2
#define MS_VOL3_CH1		CNPLCHANDLE_CH1.MS_VOL3
#define RC_VOL_CH1		CNPLCHANDLE_CH1.RC_VOL
#define V_VOL_CH1		CNPLCHANDLE_CH1.V_VOL
#define RS001_CH1		CNPLCHANDLE_CH1.RS001
#define RS010_CH1		CNPLCHANDLE_CH1.RS010
#define RS100_CH1		CNPLCHANDLE_CH1.RS100
#define O_VOL_CH1		CNPLCHANDLE_CH1.O_VOL
#define PLAVOL_CH1		CNPLCHANDLE_CH1.PLAVOL
#define JPLANCIA_CH1	CNPLCHANDLE_CH1.JPLANCIA
#define ABIASS_CH1		CNPLCHANDLE_CH1.ABIASS
#define MIS_VOL1_CH1	CNPLCHANDLE_CH1.MIS_VOL1
#define MIS_VOL2_CH1	CNPLCHANDLE_CH1.MIS_VOL2
#define MIS_VOL3_CH1	CNPLCHANDLE_CH1.MIS_VOL3
#define I_VFCS_CH1		CNPLCHANDLE_CH1.memVFCS

#define APP_IN_CH1		CNPLCHANDLE_CH1.APP_IN
#define EME_IN_CH1		CNPLCHANDLE_CH1.EME_IN
#define NUM_IN_CH1		CNPLCHANDLE_CH1.NUM_IN
#define FASE_IN_CH1 	CNPLCHANDLE_CH1.FASE_IN
#define ST_IN_CH1		CNPLCHANDLE_CH1.ST_IN
#define VERFALS_CH1		CNPLCHANDLE_CH1.VERFALS

#define STASEQZ_CH1	CNPLCHANDLE_CH1.STASEQZ	/* Stato sequenziatore zero assi da plc	*/
#define StaOpeTo_CH1 CNPLCHANDLE_CH1.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/
#define STAOPETO_CH1 CNPLCHANDLE_CH1.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/ // Per visualizzazione Sin. II
#define FlgRicTo_CH1 CNPLCHANDLE_CH1.FlgRicTo	/* Stato operazione routine ricerca tool	*/
#define FLGRICTO_CH1 CNPLCHANDLE_CH1.FlgRicTo	/* Stato operazione routine ricerca tool	*/ // Per visualizzazione Sin. II
//
////Macro per Aree CNC
#define CNC_AREA_R_CH1(_x_) Aris_CH1[_x_]
#define CNC_AREA_CANC_CH1(_x_) Acus_CH1[_x_]
#define CNC_AREA_RRET_CH1(_x_) paretplc_v2_CH1->fvdrRe[_x_]
//#define CNC_RETENTIVE_LENGTH(_unused_) (sizeof (MM_COMPATIBLE) / sizeof (USHORT))

//#define AXESEL_CH1(_nAxe_) ( (AXEJOGM_CH1) == _nAxe_ ? 1 : 0 )
