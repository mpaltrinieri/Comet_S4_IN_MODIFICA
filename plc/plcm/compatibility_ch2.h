#pragma once

#define	I_EME_CH2(x) AXCTRL_CH2[x].ctrlFlags.EME		/** Richiesta emergenza asse per l'asse di indice x */
#define	I_ANN_CH2(x) AXCTRL_CH2[x].ctrlFlags.ANN		/** Annulla richiesta di movimento in corso per l'asse di indice x */
#define	I_HLD_CH2(x) AXCTRL_CH2[x].ctrlFlags.HLD		/** Hold asse indipendente per l'asse di indice x  */
#define	I_BLM_CH2(x) AXCTRL_CH2[x].ctrlFlags.BLM		/** Asse bloccato meccanicamente per l'asse di indice x */
#define	I_LSR_CH2(x) AXCTRL_CH2[x].ctrlFlags.LSR		/** Richiesta di libera servo per l'asse di indice x */
#define	I_NAL_CH2(x) AXCTRL_CH2[x].ctrlFlags.NAL		/** Non fare blocco e allarme su cn per l'asse di indice x */
#define OVFRE_CH2(x) AXCTRL_CH2[x].overfre
//
//#define CHECKBIT(_sts_, _bit_)	((_sts_) & (_bit_) ? TRUE : FALSE)
//
#define	O_VLN_CH2(x) AXSTATUS_CH2[x].statusFlags.VLN /** Velocita' lenta asse on/off per l'asse di indice x */
#define	O_VMD_CH2(x) AXSTATUS_CH2[x].statusFlags.VMD	/** Velocita' media asse on/off per l'asse di indice x */
#define	O_VRP_CH2(x) AXSTATUS_CH2[x].statusFlags.VRP	/** Velocita' rapida asse on/off per l'asse di indice x */
#define	O_AOK_CH2(x) AXSTATUS_CH2[x].statusFlags.AOK	/** Asse x ok, non in allarme */
#define	O_ATZ_CH2(x) AXSTATUS_CH2[x].statusFlags.ATZ	/** Attenzione su asse x */
//
#define	O_MRK_CH2(x) AXSTATUS_CH2[x].statusFlags.MRK	/** Segnale di Marca ottica dell'asse di indice x */
#define	O_MCR_CH2(x) AXSTATUS_CH2[x].statusFlags.MCR	/** Segnale di Micro dell'asse di indice x */
#define	O_SRF_CH2(x) AXSTATUS_CH2[x].statusFlags.SRF	/** Segno riferimento (se 1 negativo) dell'asse di indice x */
#define	O_SEE_CH2(x) AXSTATUS_CH2[x].statusFlags.SEE	/** Set assi eseguito dell'asse di indice x */
#define	O_QMC_CH2(x) AXSTATUS_CH2[x].statusFlags.QMC	/** Su pxv c'e' quota commutazione micro per l'asse di indice x */
#define	O_CTG_CH2(x) AXSTATUS_CH2[x].statusFlags.CTG	/** Asse agganciato in contouring per l'asse di indice x */
#define	O_AGG_CH2(x) AXSTATUS_CH2[x].statusFlags.AGG	/** Asse x agganciato */
#define	O_CBG_CH2(x) AXSTATUS_CH2[x].statusFlags.CBG	/** Velocita di cambio gamma raggiunta per l'asse di indice x */
#define	O_AVV_CH2(x) AXSTATUS_CH2[x].statusFlags.AVV	/** Asse agganciato in velocita' per l'asse di indice x */
#define	O_VOK_CH2(x) AXSTATUS_CH2[x].statusFlags.VOK	/** Velocita' mandrino ok per l'asse di indice x */
#define	O_AGY_CH2(x) AXSTATUS_CH2[x].statusFlags.AGY	/** Asse agganciato in gantry per l'asse di indice x */
#define	O_IND_CH2(x) AXSTATUS_CH2[x].statusFlags.IND	/** Asse indietro per l'asse di indice x */
#define	O_MOT_CH2(x) AXSTATUS_CH2[x].statusFlags.MOT	/** Si e' registrato un movimento dell'asse x */
#define	O_MOV_CH2(x) AXSTATUS_CH2[x].statusFlags.MOV	/** Movimento in corso per l'asse di indice x */
//
#define	O_BLM_CH2(x) AXSTATUS_CH2[x].statusFlags2.BLM	/** Asse x bloccabile meccanicamente */
#define	O_LSR_CH2(x) AXSTATUS_CH2[x].statusFlags2.LSR	/** Asse x in libera servo */
#define	O_LEASED_CH2(x) AXSTATUS_CH2[x].statusFlags2.LEASED /** Asse x condiviso appartenente al canale */
#define	O_LEASED_NOTUSED_CH2(x) AXSTATUS_CH2[x].statusFlags2.LEASED_NOTUSED /** Asse x condiviso rilasciato dal canale */
//
// Segnali composti
#define	ABAX_CH2(x)	O_AGG_CH2(x)&&O_AOK_CH2(x)	/** Abilitazione aggancio asse */ 
//:ENDSECTION	//;dfsinplcFile4
//
/* Definizioni delle correzioni assi */
#define	I_CORRECTION0_CH2	AXCTRL_CH2[0].correction
#define	I_CORRECTION1_CH2	AXCTRL_CH2[1].correction
#define	I_CORRECTION2_CH2	AXCTRL_CH2[2].correction
#define	I_CORRECTION3_CH2	AXCTRL_CH2[3].correction
#define	I_CORRECTION4_CH2	AXCTRL_CH2[4].correction
#define	I_CORRECTION5_CH2	AXCTRL_CH2[5].correction
#define	I_CORRECTION6_CH2	AXCTRL_CH2[6].correction
#define	I_CORRECTION7_CH2	AXCTRL_CH2[7].correction
#define	I_CORRECTION8_CH2	AXCTRL_CH2[8].correction
#define	I_CORRECTION9_CH2	AXCTRL_CH2[9].correction
#define	I_CORRECTION10_CH2	AXCTRL_CH2[10].correction
#define	I_CORRECTION11_CH2	AXCTRL_CH2[11].correction
//
///* Definzioni Input virtuali del PLC (IsDigital) */
#define DI_BREAKON_CH2(x)		AXCTRL_CH2[x].ctrlFlags.BRAKEON	/** Abilitazione freno Mechatrolink per l'asse x */
#define DI_SERVON_CH2(x)		AXCTRL_CH2[x].ctrlFlags.SERVON	/** Abilitazione potenza Mechatrolink per l'asse x */
//
///* Definizioni Output virtuali del PLC (IsDigital) */
#define DO_POT_CH2(x)		AXSTATUS_CH2[x].statusFlags2.POT	/** Forward direction limit switch input */
#define DO_NOT_CH2(x)		AXSTATUS_CH2[x].statusFlags2.NOT	/** Reverse direction limit switch input */
#define DO_DEC_CH2(x)		AXSTATUS_CH2[x].statusFlags2.DEC	/** Deceleration limit limit switch input */
#define DO_PA_CH2(x)		0	/** Encoder Phase A signal input */
#define DO_PB_CH2(x)		0	/** Encoder Phase B signal input */
#define DO_PC_CH2(x)		0	/** Encoder Phase C signal input */
#define DO_EXT1_CH2(x)		AXSTATUS_CH2[x].statusFlags2.EXT1	/** External-1 latch signal input */
#define DO_EXT2_CH2(x)		AXSTATUS_CH2[x].statusFlags2.EXT2	/** External-2 latch signal input */
#define DO_EXT3_CH2(x)		AXSTATUS_CH2[x].statusFlags2.EXT3	/** External-3 latch signal input */
#define DO_BRK_CH2(x)		AXSTATUS_CH2[x].statusFlags2.BRK	/** Brake status output */
#define DO_PWR_CH2(x)		AXSTATUS_CH2[x].statusFlags2.PWR	/** Power stauts */
#define DO_SON_CH2(x)		AXSTATUS_CH2[x].statusFlags2.SON	/** Servo  power status */
#define DO_POS_ALIGNING_CH2(x)	AXSTATUS_CH2[x].statusFlags2.POS_ALIGNING	/** axis is in alignment movement */
#define DO_LOCK_CH2(x)		0	/** Locked status */
#define DO_MCKO_CH2(x)		(!O_AOK_CH2(x))	/** Servo Alarm */
#define DO_GEDIG_CH2(x)		1	/** All axes can be used as digital */
//
#define	I_BLC_CH2		CNCCTRL_CH2.BLC	/* Blocco a CNC (assi + mandrino) */
#define	I_BLCAX_CH2		CNCCTRL_CH2.BLCAX	/* Blocco assi CNC */
#define	I_FHOLD_CH2		CNCCTRL_CH2.FHOLD	/* Feed hold assi CNC */
#define	I_INIMM_CH2		CNCCTRL_CH2.INIMM	/* Richiesta esecuzione int immediato */
#define	I_INSIN_CH2		CNCCTRL_CH2.INSIN	/* Richiesta esecuzione int sincrono */
#define	I_INASI_CH2		CNCCTRL_CH2.INASI	/* Richiesta esecuzione int asincrono */
#define	I_RFHLD_CH2		CNCCTRL_CH2.RFHLD	/* Richiesta Feed hold per Time Out PLC	*/
#define	I_AXEJG3_CH2	CNCCTRL_CH2.SELECTED_AXVOL3	/* Sel. asse per terzo volantino (bit12-15)*/
//
////#define	I_TST  D1.byte.l	/* Codice tasto CNC */
#define	I_OVRAP_CH2		CNCCTRL_CH2.OVRAP	/* Override rapido */
//
#define	I_OVFED_CH2		CNCCTRL_CH2.OVFED	/* Override feed */
#define	I_OVSPE_CH2		CNCCTRL_CH2.OVSPE	/* Codice override speed */
//
#define	I_JS_R_CH2		CNCCTRL_CH2.JS_R	/* Richiesta jog di spazio in rapido */
#define	I_JS_L_CH2		CNCCTRL_CH2.JS_L	/* Richiesta jog di spazio in lavoro */
#define	I_JV_R_CH2		CNCCTRL_CH2.JV_R	/* Richiesta jog di velocita' in rapido */
#define	I_JV_L_CH2		CNCCTRL_CH2.JV_L	/* Richiesta jog di velocita' in lavoro */
//
#define	I_RME_CH2		CNCCTRL_CH2.RME		/* Input rotazione mandrino esterno */
#define	I_SRME_CH2		CNCCTRL_CH2.SRME	/* Senso rotazione mandr. esterno 1 = orario */
#define	I_GAM1_CH2		CNCCTRL_CH2.GAM1	/* Peso "1" per gamma inserita */
#define	I_GAM2_CH2		CNCCTRL_CH2.GAM2	/* Peso "2" per gamma inserita */
#define	I_GAM4_CH2		CNCCTRL_CH2.GAM4	/* Peso "4" per gamma inserita */
//
#define	O_BLC_CH2 	CNCSTATUS_CH2.BLC	/* CNC in blocco (assi+mandrino) */
#define	O_BLCAX_CH2	CNCSTATUS_CH2.BLCAX	/* CNC in blocco assi */
//
#define	O_AXFER_CH2	CNCSTATUS_CH2.AXFER	/* Assi cnc fermi */
#define	O_M01_CH2  	CNCSTATUS_CH2.M01	/* CNC in stop per M01 */
//
#define	O_SKIP_CH2 	CNCSTATUS_CH2.SKIP	/* CNC esegue skip */
#define	O_ESEC_CH2 	CNCSTATUS_CH2.ESEC	/* CNC in esecuzione */
//
#define	O_INIZ_CH2 	CNCSTATUS_CH2.INIZ	/* CNC in condizioni iniziali */
#define	O_LAV_CH2  	CNCSTATUS_CH2.LAV	/* Assi cnc in movimento in lavoro */
//
#define	O_RESET_CH2	CNCSTATUS_CH2.RESET	/* Esecuzione RESET  */
#define	O_ALLAR_CH2	CNCSTATUS_CH2.ALLAR	/* CNC in allarme */
//
#define	O_JPOS_CH2 	CNCSTATUS_CH2.JPOS	/* JOG + premuto */
#define	O_JNEG_CH2 	CNCSTATUS_CH2.JNEG	/* JOG - premuto */
//
#define	O_VOL1_CH2 	CNCSTATUS_CH2.VOL1	/* Volantino 1 agganciato */
//
#define	O_VOL2_CH2 	CNCSTATUS_CH2.VOL2	/* Volantino 2 agganciato */
#define	O_VOL3_CH2 	CNCSTATUS_CH2.VOL3	/* Volantino 3 agganciato */

#define	O_NOALL_CH2	CNCSTATUS_CH2.NOALL	/* Se 1 no blocco CNC per allarme */
				/* Fuori Soglia assi indipend.    */
#define	O_CUAE_CH2	CNCSTATUS_CH2.CUAE	/* Cambio utensile automatico escluso	*/
//
#define	O_SEM_CH2  	CNCSTATUS_CH2.SEM	/* CNC in manuale */
#define	O_AUT_CH2  	CNCSTATUS_CH2.AUT	/* CNC in automatico */
#define	O_MAN_CH2  	CNCSTATUS_CH2.MAN	/* CNC in JOG */
#define	O_JOG_CH2  	CNCSTATUS_CH2.JOG	/* CNC in JOG */
#define	O_RIP_CH2  	CNCSTATUS_CH2.RIP	/* CNC in riposizionamento */
#define	O_SET_CH2  	CNCSTATUS_CH2.SET	/* CNC in SET */
#define	O_EXE_CH2  	CNCSTATUS_CH2.EXE	/* CNC in modo esecuzione */
#define	O_CNT_CH2  	CNCSTATUS_CH2.CNT	/* CNC in continua */
#define	O_FND_CH2  	CNCSTATUS_CH2.FND	/* CNC in modo ricerca */
#define	O_INIMM_CH2	CNCSTATUS_CH2.INIMM	/* Int immediato pronto o in corso */
#define	O_INSIN_CH2	CNCSTATUS_CH2.INSIN	/* Int sincrono pronto o in corso */
#define	O_INASI_CH2	CNCSTATUS_CH2.INASI	/* Int asincrono pronto o in corso */
//
#define	O_M_CH2    	CNCSTATUS_CH2.M	/* Codice  f.a.  M */
//
#define	O_H_CH2  	CNCSTATUS_CH2.H	/* Codice f.a. H  */
//
#define	O_T_CH2  	CNCSTATUS_CH2.T	/* Codice f.a. T  */
//
#define	O_ATTEN_CH2	CNCSTATUS_CH2.ATTEN	/* Codice attenzione TOOL  */
//
#define	O_TDS_CH2  	CNCSTATUS_CH2.TDS		/* Codice f.a. t,d,s */
#define	O_CODGN_CH2 CNCSTATUS_CH2.CODGN	/* Codice parametro generico  */
#define O_IDXTT_CH2 CNCSTATUS_CH2.IDXTT	/* Nemero  record  letto nel file TT.TAB */ 

#define	O_CGEN_CH2 	CNCSTATUS_CH2.CGEN	/* Codice CNC : se = 1 tasto rifiutato */
#define	O_CODAL_CH2	CNCSTATUS_CH2.CODAL	/* Codice allarme CNC		 */
#define	O_CODAT_CH2	CNCSTATUS_CH2.CODAT   	/* Codice attenzione asse	 */
//
//
#define	O_GN_CH2 	CNCSTATUS_CH2.GN.dword		/* Parametro generico  */
#define	O_GNL_CH2	CNCSTATUS_CH2.GNL	/*    "		"	low */
#define	O_GNH_CH2	CNCSTATUS_CH2.GNH	/*    "		"	high */
//
#define	O_MMSTP_CH2	CNCSTATUS_CH2.MMSTP	/* Mamut non aggiorna watchdog */
//
#define	O_NVM_CH2  	CNCSTATUS_CH2.NVM	/* Nuova f.a.  M */
#define	O_NVH_CH2	CNCSTATUS_CH2.NVH	/* Nuova f.a. H */
#define	O_NVT_CH2  	CNCSTATUS_CH2.NVT	/* Nuova f.a.  T */
#define	O_NVGN_CH2	CNCSTATUS_CH2.NVGN	/* Nuovo parametro generico in output dal cnc */
#define	O_NVS_CH2  	CNCSTATUS_CH2.NVS	/* Nuova f.a. S */
#define	O_AUTHL_CH2 CNCSTATUS_CH2.AUTHL	/* Part program sospeso in automatico */
#define	O_AKTST_CH2 CNCSTATUS_CH2.AKTST	/* Ack del codice tasto in input su I_TASTC */
#define	O_AKT_CH2	CNCSTATUS_CH2.AKT	/* Ack alla nuova "t" da tci */
//
#define	_TST_AX_CH2	CNCSTATUS_CH2._TST_AX	/* Abilita test contatori assi		*/
#define	_NUM_AX_CH2 CNCSTATUS_CH2._NUM_AX	/* Numero asse con errore		*/
#define	_SGL_VEL_CH2 CNCSTATUS_CH2._SGL_VEL		/* Soglia velocita`			*/
#define	_CNT_ERR_CH2 CNCSTATUS_CH2._CNT_ERR		/* Contatore errori			*/
//
#define CODAF_CH2 	CNCSTATUS_CH2.CODAF	/* Codice funzione ausiliaria da eseguire */
#define	STRCONS_CH2	CNCSTATUS_CH2.STRCONS	/* Sincronismo per la funzione Ausiliaria */
#define ACKCONS_CH2	CNCSTATUS_CH2.ACKCONS	/* Fatto per la funzione ausiliaria */
//
#define pon_CH2		CNCSTATUS_CH2.pon
//	
#define	SEQVOL_CH2		CNCCTRL_CH2.SEQVOL	/* Sequenz. Gestione volantini */
#define	OVRAP_CH2		CNCCTRL_CH2.memOVRAP	/* Commutatore override rapido */
#define	OVFED_CH2	    CNCCTRL_CH2.memOVFED	/* Commutatore override feed */
#define	OVSPE_CH2	    CNCCTRL_CH2.memOVSPE	/* Commutatore override speed */
#define	AXEJOGM_CH2	    CNCCTRL_CH2.memAXEJOG	/* Commutatore selezione assi */
//
#define NuPosMag_CH2	CNPLCHANDLE_CH2.NuPosMag	/* numero posti di magazzino	%V11002			*/
#define NUPOSMAG_CH2	CNPLCHANDLE_CH2.NuPosMag	/* numero posti di magazzino  %V11002 */ // Per visualizzazione Sin. II
#define NuPosMed_CH2	CNPLCHANDLE_CH2.NuPosMed	/* numero posti di MEDIO	%V11003			*/
#define NUPOSMED_CH2	CNPLCHANDLE_CH2.NuPosMed	/* numero posti di MEDIO  %V11003 */ // Per visualizzazione Sin. II
#define NuPosGra_CH2	CNPLCHANDLE_CH2.NuPosGra	/* numero posti di LARGO	%V11004			*/
#define NUPOSGRA_CH2	CNPLCHANDLE_CH2.NuPosGra	/* numero posti di LARGO %V11004 */ // Per visualizzazione Sin. II
#define	StaPosMag_CH2	CNPLCHANDLE_CH2.StaPosMag
#define	STAPOSMAG_CH2	CNPLCHANDLE_CH2.StaPosMag
//
#define FATM_CH2	CNPLCHANDLE_CH2.FATM
#define FATH_CH2	CNPLCHANDLE_CH2.FATH
#define FATT_CH2	CNPLCHANDLE_CH2.FATT
#define FATGN_CH2	CNPLCHANDLE_CH2.FATGN
#define FATS_CH2	CNPLCHANDLE_CH2.FATS
#define FATTCI_CH2	CNPLCHANDLE_CH2.FATTCI
#define FATPLC_CH2	CNPLCHANDLE_CH2.FATPLC
//
#define AM03_CH2	CNPLCHANDLE_CH2.AM03
#define AM04_CH2	CNPLCHANDLE_CH2.AM04
#define AM05_CH2	CNPLCHANDLE_CH2.AM05
#define AM19_CH2	CNPLCHANDLE_CH2.AM19
#define AMCG_CH2	CNPLCHANDLE_CH2.AMCG
#define PSET_CH2	CNPLCHANDLE_CH2.PSET
#define G84_CH2 	CNPLCHANDLE_CH2.G84 
#define G184_CH2	CNPLCHANDLE_CH2.G184
#define NVM_CH2		CNPLCHANDLE_CH2.NVM
#define NVH_CH2		CNPLCHANDLE_CH2.NVH
#define NVT_CH2		CNPLCHANDLE_CH2.NVT
#define NVGN_CH2	CNPLCHANDLE_CH2.NVGN
#define NVS_CH2		CNPLCHANDLE_CH2.NVS
#define AUTHL_CH2	CNPLCHANDLE_CH2.AUTHL
#define AKTST_CH2	CNPLCHANDLE_CH2.AKTST
#define AKT_CH2		CNPLCHANDLE_CH2.AKT
//
#define	JS_R_CH2	CNPLCHANDLE_CH2.JS_R
#define JS_L_CH2	CNPLCHANDLE_CH2.JS_L
#define JV_R_CH2	CNPLCHANDLE_CH2.JV_R
#define JV_L_CH2	CNPLCHANDLE_CH2.JV_L
//
#define AXVOL1_CH2		CNPLCHANDLE_CH2.AXVOL1
#define AXVOL2_CH2		CNPLCHANDLE_CH2.AXVOL2
#define AXVOL3_CH2		CNPLCHANDLE_CH2.AXVOL3
#define S_VOL1_CH2		CNPLCHANDLE_CH2.S_VOL1
#define S_VOL2_CH2		CNPLCHANDLE_CH2.S_VOL2
#define S_VOL3_CH2		CNPLCHANDLE_CH2.S_VOL3
#define MS_VOL1_CH2		CNPLCHANDLE_CH2.MS_VOL1
#define MS_VOL2_CH2		CNPLCHANDLE_CH2.MS_VOL2
#define MS_VOL3_CH2		CNPLCHANDLE_CH2.MS_VOL3
#define RC_VOL_CH2		CNPLCHANDLE_CH2.RC_VOL
#define V_VOL_CH2		CNPLCHANDLE_CH2.V_VOL
#define RS001_CH2		CNPLCHANDLE_CH2.RS001
#define RS010_CH2		CNPLCHANDLE_CH2.RS010
#define RS100_CH2		CNPLCHANDLE_CH2.RS100
#define O_VOL_CH2		CNPLCHANDLE_CH2.O_VOL
#define PLAVOL_CH2		CNPLCHANDLE_CH2.PLAVOL
#define JPLANCIA_CH2	CNPLCHANDLE_CH2.JPLANCIA
#define ABIASS_CH2		CNPLCHANDLE_CH2.ABIASS
#define MIS_VOL1_CH2	CNPLCHANDLE_CH2.MIS_VOL1
#define MIS_VOL2_CH2	CNPLCHANDLE_CH2.MIS_VOL2
#define MIS_VOL3_CH2	CNPLCHANDLE_CH2.MIS_VOL3
#define I_VFCS_CH2		CNPLCHANDLE_CH2.memVFCS

#define APP_IN_CH2		CNPLCHANDLE_CH2.APP_IN
#define EME_IN_CH2		CNPLCHANDLE_CH2.EME_IN
#define NUM_IN_CH2		CNPLCHANDLE_CH2.NUM_IN
#define FASE_IN_CH2 	CNPLCHANDLE_CH2.FASE_IN
#define ST_IN_CH2		CNPLCHANDLE_CH2.ST_IN
#define VERFALS_CH2		CNPLCHANDLE_CH2.VERFALS

#define STASEQZ_CH2	CNPLCHANDLE_CH2.STASEQZ	/* Stato sequenziatore zero assi da plc	*/
#define StaOpeTo_CH2 CNPLCHANDLE_CH2.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/
#define STAOPETO_CH2 CNPLCHANDLE_CH2.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/ // Per visualizzazione Sin. II
#define FlgRicTo_CH2 CNPLCHANDLE_CH2.FlgRicTo	/* Stato operazione routine ricerca tool	*/
#define FLGRICTO_CH2 CNPLCHANDLE_CH2.FlgRicTo	/* Stato operazione routine ricerca tool	*/ // Per visualizzazione Sin. II
//
////Macro per Aree CNC
#define CNC_AREA_R_CH2(_x_) Aris_CH2[_x_]
#define CNC_AREA_CANC_CH2(_x_) Acus_CH2[_x_]
#define CNC_AREA_RRET_CH2(_x_) paretplc_v2_CH2->fvdrRe[_x_]
//#define CNC_RETENTIVE_LENGTH(_unused_) (sizeof (MM_COMPATIBLE) / sizeof (USHORT))

//#define AXESEL_CH2(_nAxe_) ( (AXEJOGM_CH2) == _nAxe_ ? 1 : 0 )
