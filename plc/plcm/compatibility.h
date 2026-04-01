#pragma once

#ifndef MAXCNC
#	define MAXCNC	12
#endif //MAXCNC

//Messaggi Pipe Interna
short __inline CnGetMessage (LPDWORD pCode, 
									LPVOID * lpBuffer,
									LPDWORD pLength) {
	//il messaggio viene scodato dalla cima della coda
	if (rec_queuetop >= 9)
		return -1; //non dovrebbe mai succedere
	if (rec_code[rec_queuetop]) {
		if (!pCode || !pLength || !lpBuffer) return -1;
		*pCode = rec_code[rec_queuetop];
		*pLength = rec_datalen[rec_queuetop];
		*lpBuffer = (LPVOID) rec_comm[rec_queuetop].rec_comm;
		return 1;
	} else return 0;
}

//invio messaggi della pipe interna
short __inline CnSendMessage (DWORD dwCode, 
									PBYTE pBuffer, 
									DWORD dwBufferLength){
	return SendExternMessage (dwCode, pBuffer, dwBufferLength);
}

void __inline dforzmo(void) {}
void __inline aforzmo(void) {}

short __inline QuoMi(  float * quota, unsigned short n_asse ) {
//	short ret;
	if (n_asse >= 12) return -1;
	else {
		*quota = (float) AXSTATUS[n_asse].pmicro;
		return 0;
	}
}

#define LegQuoMi QuoMi

short __inline QuoMi2(  double * quota, unsigned short n_asse ) {
//	short ret;
	if (n_asse >= 12) return -1;
	else {
		*quota = AXSTATUS[n_asse].pmicro;
		return 0;
	}
}
#define LegQuoMi2 QuoMi2

//todo: definire variabile globale CONFCN per configurazione CNC
//todo: definire variabile globale CNCSTATUS per stato CNC e CNCCTRL per controllo CNC
//todo: definire variabile globale TOOLSTATUS per stato utensile
//todo: definire variabile globale CNPLCHANDLE per handle CNC
//todo: definire variabile globale PROGRAMSTATUS per stato programma 
//todo: definire variabili globali AXCTRL e AXSTATUS array delle strutture di controllo e stato rispettivamente
//todo: definire variabili globali DIGITALIN, DIGITALOUT, ANALOGIN, ANALOGOUT, ENCODERVAL per DI, DO, AI, AO ed Encoder rispettivamente

//serve per non far includere le vecchie definizioni
#define _PLCSYN

#ifdef _MULTICHANNEL

#define	I_EME_CH0(x) AXCTRL[x].ctrlFlags.EME		/** Richiesta emergenza asse per l'asse di indice x */
#define	I_ANN_CH0(x) AXCTRL[x].ctrlFlags.ANN		/** Annulla richiesta di movimento in corso per l'asse di indice x */
#define	I_LSR_CH0(x) AXCTRL[x].ctrlFlags.LSR		/** Richiesta di libera servo per l'asse di indice x */
#define	I_HLD_CH0(x) AXCTRL[x].ctrlFlags.HLD		/** Hold asse indipendente per l'asse di indice x  */
#define	I_NAL_CH0(x) AXCTRL[x].ctrlFlags.NAL		/** Non fare blocco e allarme su cn per l'asse di indice x */
#define OVFRE_CH0(x) AXCTRL[x].overfre
#define	I_BLM_CH0(x) AXCTRL[x].ctrlFlags.BLM		/** Asse bloccato meccanicamente per l'asse di indice x */

#define CHECKBIT(_sts_, _bit_)	((_sts_) & (_bit_) ? TRUE : FALSE)

#define	O_VLN_CH0(x) AXSTATUS[x].statusFlags.VLN /** Velocita' lenta asse on/off per l'asse di indice x */
#define	O_VMD_CH0(x) AXSTATUS[x].statusFlags.VMD	/** Velocita' media asse on/off per l'asse di indice x */
#define	O_VRP_CH0(x) AXSTATUS[x].statusFlags.VRP	/** Velocita' rapida asse on/off per l'asse di indice x */
#define	O_AOK_CH0(x) AXSTATUS[x].statusFlags.AOK	/** Asse x ok, non in allarme */
#define	O_ATZ_CH0(x) AXSTATUS[x].statusFlags.ATZ	/** Attenzione su asse x */

#define	O_MRK_CH0(x) AXSTATUS[x].statusFlags.MRK	/** Segnale di Marca ottica dell'asse di indice x */
#define	O_MCR_CH0(x) AXSTATUS[x].statusFlags.MCR	/** Segnale di Micro dell'asse di indice x */
#define	O_SRF_CH0(x) AXSTATUS[x].statusFlags.SRF	/** Segno riferimento (se 1 negativo) dell'asse di indice x */
#define	O_SEE_CH0(x) AXSTATUS[x].statusFlags.SEE	/** Set assi eseguito dell'asse di indice x */
#define	O_QMC_CH0(x) AXSTATUS[x].statusFlags.QMC	/** Su pxv c'e' quota commutazione micro per l'asse di indice x */
#define	O_CTG_CH0(x) AXSTATUS[x].statusFlags.CTG	/** Asse agganciato in contouring per l'asse di indice x */
#define	O_AGG_CH0(x) AXSTATUS[x].statusFlags.AGG	/** Asse x agganciato */
#define	O_CBG_CH0(x) AXSTATUS[x].statusFlags.CBG	/** Velocita di cambio gamma raggiunta per l'asse di indice x */
#define	O_AVV_CH0(x) AXSTATUS[x].statusFlags.AVV	/** Asse agganciato in velocita' per l'asse di indice x */
#define	O_VOK_CH0(x) AXSTATUS[x].statusFlags.VOK	/** Velocita' mandrino ok per l'asse di indice x */
#define	O_AGY_CH0(x) AXSTATUS[x].statusFlags.AGY	/** Asse agganciato in gantry per l'asse di indice x */
#define	O_IND_CH0(x) AXSTATUS[x].statusFlags.IND	/** Asse indietro per l'asse di indice x */
#define	O_MOT_CH0(x) AXSTATUS[x].statusFlags.MOT	/** Si e' registrato un movimento dell'asse x */
#define	O_MOV_CH0(x) AXSTATUS[x].statusFlags.MOV	/** Movimento in corso per l'asse di indice x */

#define	O_BLM_CH0(x) AXSTATUS[x].statusFlags2.BLM	/** Asse x bloccabile meccanicamente */
#define	O_LSR_CH0(x) AXSTATUS[x].statusFlags2.LSR	/** Asse x in libera servo */
#define	O_LEASED_CH0(x) AXSTATUS[x].statusFlags2.LEASED /** Asse x condiviso appartenente al canale */
#define	O_LEASED_NOTUSED_CH0(x) AXSTATUS[x].statusFlags2.LEASED_NOTUSED /** Asse x condiviso rilasciato dal canale */

// Segnali composti
#define	ABAX_CH0(x)	O_AGG_CH0(x)&&O_AOK_CH0(x)	/** Abilitazione aggancio asse */ 
//:ENDSECTION	//;dfsinplcFile4

/* Definizioni delle correzioni assi */
#define	I_CORRECTION0_CH0	AXCTRL[0].correction
#define	I_CORRECTION1_CH0	AXCTRL[1].correction
#define	I_CORRECTION2_CH0	AXCTRL[2].correction
#define	I_CORRECTION3_CH0	AXCTRL[3].correction
#define	I_CORRECTION4_CH0	AXCTRL[4].correction
#define	I_CORRECTION5_CH0	AXCTRL[5].correction
#define	I_CORRECTION6_CH0	AXCTRL[6].correction
#define	I_CORRECTION7_CH0	AXCTRL[7].correction
#define	I_CORRECTION8_CH0	AXCTRL[8].correction
#define	I_CORRECTION9_CH0	AXCTRL[9].correction
#define	I_CORRECTION10_CH0	AXCTRL[10].correction
#define	I_CORRECTION11_CH0	AXCTRL[11].correction

/* Definzioni Input virtuali del PLC (IsDigital) */
#define DI_BREAKON_CH0(x)		AXCTRL[x].ctrlFlags.BRAKEON	/** Abilitazione freno Mechatrolink per l'asse x */
#define DI_SERVON_CH0(x)		AXCTRL[x].ctrlFlags.SERVON	/** Abilitazione potenza Mechatrolink per l'asse x */

/* Definizioni Output virtuali del PLC (IsDigital) */
#define DO_POT_CH0(x)		AXSTATUS[x].statusFlags2.POT	/** Forward direction limit switch input */
#define DO_NOT_CH0(x)		AXSTATUS[x].statusFlags2.NOT	/** Reverse direction limit switch input */
#define DO_DEC_CH0(x)		AXSTATUS[x].statusFlags2.DEC	/** Deceleration limit limit switch input */
#define DO_PA_CH0(x)		0	/** Encoder Phase A signal input */
#define DO_PB_CH0(x)		0	/** Encoder Phase B signal input */
#define DO_PC_CH0(x)		0	/** Encoder Phase C signal input */
#define DO_EXT1_CH0(x)		AXSTATUS[x].statusFlags2.EXT1	/** External-1 latch signal input */
#define DO_EXT2_CH0(x)		AXSTATUS[x].statusFlags2.EXT2	/** External-2 latch signal input */
#define DO_EXT3_CH0(x)		AXSTATUS[x].statusFlags2.EXT3	/** External-3 latch signal input */
#define DO_BRK_CH0(x)		AXSTATUS[x].statusFlags2.BRK	/** Brake status output */
#define DO_PWR_CH0(x)		AXSTATUS[x].statusFlags2.PWR	/** Power stauts */
#define DO_SON_CH0(x)		AXSTATUS[x].statusFlags2.SON	/** Servo  power status */
#define DO_POS_ALIGNING_CH0(x)	AXSTATUS[x].statusFlags2.POS_ALIGNING	/** axis is in alignment movement */
#define DO_LOCK_CH0(x)		0	/** Locked status */
#define DO_MCKO_CH0(x)		(!O_AOK_CH0(x))	/** Servo Alarm */
#define DO_GEDIG_CH0(x)		1	/** All axes can be used as digital */

#define	I_BLC_CH0		CNCCTRL.BLC	/* Blocco a CNC (assi + mandrino) */
#define	I_BLCAX_CH0		CNCCTRL.BLCAX	/* Blocco assi CNC */
#define	I_FHOLD_CH0		CNCCTRL.FHOLD	/* Feed hold assi CNC */
#define	I_INIMM_CH0		CNCCTRL.INIMM	/* Richiesta esecuzione int immediato */
#define	I_INSIN_CH0		CNCCTRL.INSIN	/* Richiesta esecuzione int sincrono */
#define	I_INASI_CH0		CNCCTRL.INASI	/* Richiesta esecuzione int asincrono */
#define	I_RFHLD_CH0		CNCCTRL.RFHLD	/* Richiesta Feed hold per Time Out PLC	*/
#define	I_AXEJG3_CH0	CNCCTRL.SELECTED_AXVOL3	/* Sel. asse per terzo volantino (bit12-15)*/

//#define	I_TST  D1.byte.l	/* Codice tasto CNC */
#define	I_OVRAP_CH0		CNCCTRL.OVRAP	/* Override rapido */

#define	I_OVFED_CH0		CNCCTRL.OVFED	/* Override feed */
#define	I_OVSPE_CH0		CNCCTRL.OVSPE	/* Codice override speed */

#define	I_JS_R_CH0		CNCCTRL.JS_R	/* Richiesta jog di spazio in rapido */
#define	I_JS_L_CH0		CNCCTRL.JS_L	/* Richiesta jog di spazio in lavoro */
#define	I_JV_R_CH0		CNCCTRL.JV_R	/* Richiesta jog di velocita' in rapido */
#define	I_JV_L_CH0		CNCCTRL.JV_L	/* Richiesta jog di velocita' in lavoro */

#define	I_RME_CH0		CNCCTRL.RME		/* Input rotazione mandrino esterno */
#define	I_SRME_CH0		CNCCTRL.SRME	/* Senso rotazione mandr. esterno 1 = orario */
#define	I_GAM1_CH0		CNCCTRL.GAM1	/* Peso "1" per gamma inserita */
#define	I_GAM2_CH0		CNCCTRL.GAM2	/* Peso "2" per gamma inserita */
#define	I_GAM4_CH0		CNCCTRL.GAM4	/* Peso "4" per gamma inserita */

#define	O_BLC_CH0 	CNCSTATUS.BLC	/* CNC in blocco (assi+mandrino) */
#define	O_BLCAX_CH0	CNCSTATUS.BLCAX	/* CNC in blocco assi */

#define	O_AXFER_CH0	CNCSTATUS.AXFER	/* Assi cnc fermi */
#define	O_M01_CH0  	CNCSTATUS.M01	/* CNC in stop per M01 */

#define	O_SKIP_CH0 	CNCSTATUS.SKIP	/* CNC esegue skip */
#define	O_ESEC_CH0 	CNCSTATUS.ESEC	/* CNC in esecuzione */

#define	O_INIZ_CH0 	CNCSTATUS.INIZ	/* CNC in condizioni iniziali */
#define	O_LAV_CH0  	CNCSTATUS.LAV	/* Assi cnc in movimento in lavoro */

#define	O_RESET_CH0	CNCSTATUS.RESET	/* Esecuzione RESET  */
#define	O_ALLAR_CH0	CNCSTATUS.ALLAR	/* CNC in allarme */

#define	O_JPOS_CH0 	CNCSTATUS.JPOS	/* JOG + premuto */
#define	O_JNEG_CH0 	CNCSTATUS.JNEG	/* JOG - premuto */

#define	O_VOL1_CH0 	CNCSTATUS.VOL1	/* Volantino 1 agganciato */

#define	O_VOL2_CH0 	CNCSTATUS.VOL2	/* Volantino 2 agganciato */
#define	O_VOL3_CH0 	CNCSTATUS.VOL3	/* Volantino 3 agganciato */

#define	O_NOALL_CH0	CNCSTATUS.NOALL	/* Se 1 no blocco CNC per allarme */
				/* Fuori Soglia assi indipend.    */
#define	O_CUAE_CH0	CNCSTATUS.CUAE	/* Cambio utensile automatico escluso	*/

#define	O_SEM_CH0  	CNCSTATUS.SEM	/* CNC in manuale */
#define	O_AUT_CH0  	CNCSTATUS.AUT	/* CNC in automatico */
#define	O_MAN_CH0  	CNCSTATUS.MAN	/* CNC in JOG */
#define	O_JOG_CH0  	CNCSTATUS.JOG	/* CNC in JOG */
#define	O_RIP_CH0  	CNCSTATUS.RIP	/* CNC in riposizionamento */
#define	O_SET_CH0  	CNCSTATUS.SET	/* CNC in SET */
#define	O_EXE_CH0  	CNCSTATUS.EXE	/* CNC in modo esecuzione */
#define	O_CNT_CH0  	CNCSTATUS.CNT	/* CNC in continua */
#define	O_FND_CH0  	CNCSTATUS.FND	/* CNC in modo ricerca */
#define	O_INIMM_CH0	CNCSTATUS.INIMM	/* Int immediato pronto o in corso */
#define	O_INSIN_CH0	CNCSTATUS.INSIN	/* Int sincrono pronto o in corso */
#define	O_INASI_CH0	CNCSTATUS.INASI	/* Int asincrono pronto o in corso */

#define	O_M_CH0    	CNCSTATUS.M	/* Codice  f.a.  M */

#define	O_H_CH0  	CNCSTATUS.H	/* Codice f.a. H  */

#define	O_T_CH0  	CNCSTATUS.T	/* Codice f.a. T  */

#define	O_ATTEN_CH0	CNCSTATUS.ATTEN	/* Codice attenzione TOOL  */

#define	O_TDS_CH0  	CNCSTATUS.TDS		/* Codice f.a. t,d,s */
#define	O_CODGN_CH0 CNCSTATUS.CODGN	/* Codice parametro generico  */
#define O_IDXTT_CH0 CNCSTATUS.IDXTT	/* Nemero  record  letto nel file TT.TAB */ 

#define	O_CGEN_CH0 	CNCSTATUS.CGEN	/* Codice CNC : se = 1 tasto rifiutato */
#define	O_CODAL_CH0	CNCSTATUS.CODAL	/* Codice allarme CNC		 */
#define	O_CODAT_CH0	CNCSTATUS.CODAT   	/* Codice attenzione asse	 */


#define	O_GN_CH0 	CNCSTATUS.GN.dword		/* Parametro generico  */
#define	O_GNL_CH0	CNCSTATUS.GNL	/*    "		"	low */
#define	O_GNH_CH0	CNCSTATUS.GNH	/*    "		"	high */

#define	O_MMSTP_CH0	CNCSTATUS.MMSTP	/* Mamut non aggiorna watchdog */

#define	O_NVM_CH0  	CNCSTATUS.NVM	/* Nuova f.a.  M */
#define	O_NVH_CH0	CNCSTATUS.NVH	/* Nuova f.a. H */
#define	O_NVT_CH0  	CNCSTATUS.NVT	/* Nuova f.a.  T */
#define	O_NVGN_CH0	CNCSTATUS.NVGN	/* Nuovo parametro generico in output dal cnc */
#define	O_NVS_CH0  	CNCSTATUS.NVS	/* Nuova f.a. S */
#define	O_AUTHL_CH0 CNCSTATUS.AUTHL	/* Part program sospeso in automatico */
#define	O_AKTST_CH0 CNCSTATUS.AKTST	/* Ack del codice tasto in input su I_TASTC */
#define	O_AKT_CH0	CNCSTATUS.AKT	/* Ack alla nuova "t" da tci */

#define	_TST_AX_CH0	CNCSTATUS._TST_AX	/* Abilita test contatori assi		*/
#define	_NUM_AX_CH0 CNCSTATUS._NUM_AX	/* Numero asse con errore		*/
#define	_SGL_VEL_CH0 CNCSTATUS._SGL_VEL		/* Soglia velocita`			*/
#define	_CNT_ERR_CH0 CNCSTATUS._CNT_ERR		/* Contatore errori			*/

#define CODAF_CH0 	CNCSTATUS.CODAF	/* Codice funzione ausiliaria da eseguire */
#define	STRCONS_CH0	CNCSTATUS.STRCONS	/* Sincronismo per la funzione Ausiliaria */
#define ACKCONS_CH0	CNCSTATUS.ACKCONS	/* Fatto per la funzione ausiliaria */

#define pon_CH0		CNCSTATUS.pon
	
#define	SEQVOL_CH0		CNCCTRL.SEQVOL	/* Sequenz. Gestione volantini */
//#define	OVRAP_CH0		CNCCTRL.OVRAP	/* Commutatore override rapido */
#define	OVRAP_CH0		CNCCTRL.memOVRAP	/* Commutatore override rapido */
//#define	OVFED_CH0	    CNCCTRL.OVFED	/* Commutatore override feed */
#define	OVFED_CH0	    CNCCTRL.memOVFED	/* Commutatore override feed */
//#define	OVSPE_CH0	    CNCCTRL.OVSPE	/* Commutatore override speed */
#define	OVSPE_CH0	    CNCCTRL.memOVSPE	/* Commutatore override speed */
#define	AXEJOGM_CH0	    CNCCTRL.memAXEJOG	/* Commutatore selezione assi */

#define NuPosMag_CH0	CNPLCHANDLE.NuPosMag	/* numero posti di magazzino	%V11002			*/
#define NUPOSMAG_CH0	CNPLCHANDLE.NuPosMag	/* numero posti di magazzino  %V11002 */ // Per visualizzazione Sin. II
#define NuPosMed_CH0	CNPLCHANDLE.NuPosMed	/* numero posti di MEDIO	%V11003			*/
#define NUPOSMED_CH0	CNPLCHANDLE.NuPosMed	/* numero posti di MEDIO  %V11003 */ // Per visualizzazione Sin. II
#define NuPosGra_CH0	CNPLCHANDLE.NuPosGra	/* numero posti di LARGO	%V11004			*/
#define NUPOSGRA_CH0	CNPLCHANDLE.NuPosGra	/* numero posti di LARGO %V11004 */ // Per visualizzazione Sin. II
#define	StaPosMag_CH0	CNPLCHANDLE.StaPosMag
#define	STAPOSMAG_CH0	CNPLCHANDLE.StaPosMag

#define FATM_CH0	CNPLCHANDLE.FATM
#define FATH_CH0	CNPLCHANDLE.FATH
#define FATT_CH0	CNPLCHANDLE.FATT
#define FATGN_CH0	CNPLCHANDLE.FATGN
#define FATS_CH0	CNPLCHANDLE.FATS
#define FATTCI_CH0	CNPLCHANDLE.FATTCI
#define FATPLC_CH0	CNPLCHANDLE.FATPLC

#define AM03_CH0	CNPLCHANDLE.AM03
#define AM04_CH0	CNPLCHANDLE.AM04
#define AM05_CH0	CNPLCHANDLE.AM05
#define AM19_CH0	CNPLCHANDLE.AM19
#define AMCG_CH0	CNPLCHANDLE.AMCG
#define PSET_CH0	CNPLCHANDLE.PSET
#define G84_CH0 	CNPLCHANDLE.G84 
#define G184_CH0	CNPLCHANDLE.G184
#define NVM_CH0		CNPLCHANDLE.NVM
#define NVH_CH0		CNPLCHANDLE.NVH
#define NVT_CH0		CNPLCHANDLE.NVT
#define NVGN_CH0	CNPLCHANDLE.NVGN
#define NVS_CH0	CNPLCHANDLE.NVS
#define AUTHL_CH0	CNPLCHANDLE.AUTHL
#define AKTST_CH0	CNPLCHANDLE.AKTST
#define AKT_CH0		CNPLCHANDLE.AKT

#define	JS_R_CH0	CNPLCHANDLE.JS_R
#define JS_L_CH0	CNPLCHANDLE.JS_L
#define JV_R_CH0	CNPLCHANDLE.JV_R
#define JV_L_CH0	CNPLCHANDLE.JV_L

#define AXVOL1_CH0		CNPLCHANDLE.AXVOL1
#define AXVOL2_CH0		CNPLCHANDLE.AXVOL2
#define AXVOL3_CH0		CNPLCHANDLE.AXVOL3
#define S_VOL1_CH0		CNPLCHANDLE.S_VOL1
#define S_VOL2_CH0		CNPLCHANDLE.S_VOL2
#define S_VOL3_CH0		CNPLCHANDLE.S_VOL3
#define MS_VOL1_CH0		CNPLCHANDLE.MS_VOL1
#define MS_VOL2_CH0		CNPLCHANDLE.MS_VOL2
#define MS_VOL3_CH0		CNPLCHANDLE.MS_VOL3
#define RC_VOL_CH0		CNPLCHANDLE.RC_VOL
#define V_VOL_CH0		CNPLCHANDLE.V_VOL
#define RS001_CH0		CNPLCHANDLE.RS001
#define RS010_CH0		CNPLCHANDLE.RS010
#define RS100_CH0		CNPLCHANDLE.RS100
#define O_VOL_CH0		CNPLCHANDLE.O_VOL
#define PLAVOL_CH0		CNPLCHANDLE.PLAVOL
#define JPLANCIA_CH0	CNPLCHANDLE.JPLANCIA
#define ABIASS_CH0		CNPLCHANDLE.ABIASS
#define MIS_VOL1_CH0	CNPLCHANDLE.MIS_VOL1
#define MIS_VOL2_CH0	CNPLCHANDLE.MIS_VOL2
#define MIS_VOL3_CH0	CNPLCHANDLE.MIS_VOL3
#define I_VFCS_CH0		CNPLCHANDLE.memVFCS

#define APP_IN_CH0		CNPLCHANDLE.APP_IN
#define EME_IN_CH0		CNPLCHANDLE.EME_IN
#define NUM_IN_CH0		CNPLCHANDLE.NUM_IN
#define FASE_IN_CH0 	CNPLCHANDLE.FASE_IN
#define ST_IN_CH0		CNPLCHANDLE.ST_IN
#define VERFALS_CH0		CNPLCHANDLE.VERFALS

#define STASEQZ_CH0	CNPLCHANDLE.STASEQZ	/* Stato sequenziatore zero assi da plc	*/
#define StaOpeTo_CH0 CNPLCHANDLE.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/
#define STAOPETO_CH0 CNPLCHANDLE.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/ // Per visualizzazione Sin. II
#define FlgRicTo_CH0 CNPLCHANDLE.FlgRicTo	/* Stato operazione routine ricerca tool	*/
#define FLGRICTO_CH0 CNPLCHANDLE.FlgRicTo	/* Stato operazione routine ricerca tool	*/ // Per visualizzazione Sin. II
#else
#define	I_EME(x) AXCTRL[x].ctrlFlags.EME		/** Richiesta emergenza asse per l'asse di indice x */
#define	I_ANN(x) AXCTRL[x].ctrlFlags.ANN		/** Annulla richiesta di movimento in corso per l'asse di indice x */
#define	I_HLD(x) AXCTRL[x].ctrlFlags.HLD		/** Hold asse indipendente per l'asse di indice x  */
#define	I_BLM(x) AXCTRL[x].ctrlFlags.BLM		/** Asse bloccato meccanicamente per l'asse di indice x */
#define	I_LSR(x) AXCTRL[x].ctrlFlags.LSR		/** Richiesta di libera servo per l'asse di indice x */
#define	I_NAL(x) AXCTRL[x].ctrlFlags.NAL		/** Non fare blocco e allarme su cn per l'asse di indice x */
#define OVFRE(x) AXCTRL[x].overfre

#define CHECKBIT(_sts_, _bit_)	((_sts_) & (_bit_) ? TRUE : FALSE)

#define	O_VLN(x) AXSTATUS[x].statusFlags.VLN /** Velocita' lenta asse on/off per l'asse di indice x */
#define	O_VMD(x) AXSTATUS[x].statusFlags.VMD	/** Velocita' media asse on/off per l'asse di indice x */
#define	O_VRP(x) AXSTATUS[x].statusFlags.VRP	/** Velocita' rapida asse on/off per l'asse di indice x */
#define	O_AOK(x) AXSTATUS[x].statusFlags.AOK	/** Asse x ok, non in allarme */
#define	O_ATZ(x) AXSTATUS[x].statusFlags.ATZ	/** Attenzione su asse x */

#define	O_MRK(x) AXSTATUS[x].statusFlags.MRK	/** Segnale di Marca ottica dell'asse di indice x */
#define	O_MCR(x) AXSTATUS[x].statusFlags.MCR	/** Segnale di Micro dell'asse di indice x */
#define	O_SRF(x) AXSTATUS[x].statusFlags.SRF	/** Segno riferimento (se 1 negativo) dell'asse di indice x */
#define	O_SEE(x) AXSTATUS[x].statusFlags.SEE	/** Set assi eseguito dell'asse di indice x */
#define	O_QMC(x) AXSTATUS[x].statusFlags.QMC	/** Su pxv c'e' quota commutazione micro per l'asse di indice x */
#define	O_CTG(x) AXSTATUS[x].statusFlags.CTG	/** Asse agganciato in contouring per l'asse di indice x */
#define	O_AGG(x) AXSTATUS[x].statusFlags.AGG	/** Asse x agganciato */
#define	O_CBG(x) AXSTATUS[x].statusFlags.CBG	/** Velocita di cambio gamma raggiunta per l'asse di indice x */
#define	O_AVV(x) AXSTATUS[x].statusFlags.AVV	/** Asse agganciato in velocita' per l'asse di indice x */
#define	O_VOK(x) AXSTATUS[x].statusFlags.VOK	/** Velocita' mandrino ok per l'asse di indice x */
#define	O_AGY(x) AXSTATUS[x].statusFlags.AGY	/** Asse agganciato in gantry per l'asse di indice x */
#define	O_IND(x) AXSTATUS[x].statusFlags.IND	/** Asse indietro per l'asse di indice x */
#define	O_MOT(x) AXSTATUS[x].statusFlags.MOT	/** Si e' registrato un movimento dell'asse x */
#define	O_MOV(x) AXSTATUS[x].statusFlags.MOV	/** Movimento in corso per l'asse di indice x */

#define	O_BLM(x) AXSTATUS[x].statusFlags2.BLM	/** Asse x bloccabile meccanicamente */
#define	O_LSR(x) AXSTATUS[x].statusFlags2.LSR	/** Asse x in libera servo */

// Segnali composti
#define	ABAX(x)	O_AGG(x)&&O_AOK(x)	/** Abilitazione aggancio asse */ 
//:ENDSECTION	//;dfsinplcFile4

/* Definizioni delle correzioni assi */
#define	I_CORRECTION0	AXCTRL[0].correction
#define	I_CORRECTION1	AXCTRL[1].correction
#define	I_CORRECTION2	AXCTRL[2].correction
#define	I_CORRECTION3	AXCTRL[3].correction
#define	I_CORRECTION4	AXCTRL[4].correction
#define	I_CORRECTION5	AXCTRL[5].correction
#define	I_CORRECTION6	AXCTRL[6].correction
#define	I_CORRECTION7	AXCTRL[7].correction
#define	I_CORRECTION8	AXCTRL[8].correction
#define	I_CORRECTION9	AXCTRL[9].correction
#define	I_CORRECTION10	AXCTRL[10].correction
#define	I_CORRECTION11	AXCTRL[11].correction

/* Definzioni Input virtuali del PLC (IsDigital) */
#define DI_BREAKON(x)		AXCTRL[x].ctrlFlags.BRAKEON	/** Abilitazione freno Mechatrolink per l'asse x */
#define DI_SERVON(x)		AXCTRL[x].ctrlFlags.SERVON	/** Abilitazione potenza Mechatrolink per l'asse x */

/* Definizioni Output virtuali del PLC (IsDigital) */
#define DO_POT(x)		AXSTATUS[x].statusFlags2.POT	/** Forward direction limit switch input */
#define DO_NOT(x)		AXSTATUS[x].statusFlags2.NOT	/** Reverse direction limit switch input */
#define DO_DEC(x)		AXSTATUS[x].statusFlags2.DEC	/** Deceleration limit limit switch input */
#define DO_PA(x)		0	/** Encoder Phase A signal input */
#define DO_PB(x)		0	/** Encoder Phase B signal input */
#define DO_PC(x)		0	/** Encoder Phase C signal input */
#define DO_EXT1(x)		AXSTATUS[x].statusFlags2.EXT1	/** External-1 latch signal input */
#define DO_EXT2(x)		AXSTATUS[x].statusFlags2.EXT2	/** External-2 latch signal input */
#define DO_EXT3(x)		AXSTATUS[x].statusFlags2.EXT3	/** External-3 latch signal input */
#define DO_BRK(x)		AXSTATUS[x].statusFlags2.BRK	/** Brake status output */
#define DO_PWR(x)		AXSTATUS[x].statusFlags2.PWR	/** Power stauts */
#define DO_SON(x)		AXSTATUS[x].statusFlags2.SON	/** Servo  power status */
#define DO_POS_ALIGNING(x)	AXSTATUS[x].statusFlags2.POS_ALIGNING	/** axis is in alignment movement */
#define DO_LOCK(x)		0	/** Locked status */
#define DO_MCKO(x)		(!O_AOK(x))	/** Servo Alarm */
#define DO_GEDIG(x)		1	/** All axes can be used as digital */

#define	I_BLC		CNCCTRL.BLC	/* Blocco a CNC (assi + mandrino) */
#define	I_BLCAX		CNCCTRL.BLCAX	/* Blocco assi CNC */
#define	I_FHOLD		CNCCTRL.FHOLD	/* Feed hold assi CNC */
#define	I_INIMM		CNCCTRL.INIMM	/* Richiesta esecuzione int immediato */
#define	I_INSIN		CNCCTRL.INSIN	/* Richiesta esecuzione int sincrono */
#define	I_INASI		CNCCTRL.INASI	/* Richiesta esecuzione int asincrono */
#define	I_RFHLD		CNCCTRL.RFHLD	/* Richiesta Feed hold per Time Out PLC	*/
#define	I_AXEJG3	CNCCTRL.SELECTED_AXVOL3	/* Sel. asse per terzo volantino (bit12-15)*/

//#define	I_TST  D1.byte.l	/* Codice tasto CNC */
#define	I_OVRAP		CNCCTRL.OVRAP	/* Override rapido */

#define	I_OVFED		CNCCTRL.OVFED	/* Override feed */
#define	I_OVSPE		CNCCTRL.OVSPE	/* Codice override speed */

#define	I_JS_R		CNCCTRL.JS_R	/* Richiesta jog di spazio in rapido */
#define	I_JS_L		CNCCTRL.JS_L	/* Richiesta jog di spazio in lavoro */
#define	I_JV_R		CNCCTRL.JV_R	/* Richiesta jog di velocita' in rapido */
#define	I_JV_L		CNCCTRL.JV_L	/* Richiesta jog di velocita' in lavoro */

#define	I_RME		CNCCTRL.RME		/* Input rotazione mandrino esterno */
#define	I_SRME		CNCCTRL.SRME	/* Senso rotazione mandr. esterno 1 = orario */
#define	I_GAM1		CNCCTRL.GAM1	/* Peso "1" per gamma inserita */
#define	I_GAM2		CNCCTRL.GAM2	/* Peso "2" per gamma inserita */
#define	I_GAM4		CNCCTRL.GAM4	/* Peso "4" per gamma inserita */

#define	O_BLC 	CNCSTATUS.BLC	/* CNC in blocco (assi+mandrino) */
#define	O_BLCAX	CNCSTATUS.BLCAX	/* CNC in blocco assi */

#define	O_AXFER	CNCSTATUS.AXFER	/* Assi cnc fermi */
#define	O_M01  	CNCSTATUS.M01	/* CNC in stop per M01 */

#define	O_SKIP 	CNCSTATUS.SKIP	/* CNC esegue skip */
#define	O_ESEC 	CNCSTATUS.ESEC	/* CNC in esecuzione */

#define	O_INIZ 	CNCSTATUS.INIZ	/* CNC in condizioni iniziali */
#define	O_LAV  	CNCSTATUS.LAV	/* Assi cnc in movimento in lavoro */

#define	O_RESET	CNCSTATUS.RESET	/* Esecuzione RESET  */
#define	O_ALLAR	CNCSTATUS.ALLAR	/* CNC in allarme */

#define	O_JPOS 	CNCSTATUS.JPOS	/* JOG + premuto */
#define	O_JNEG 	CNCSTATUS.JNEG	/* JOG - premuto */

#define	O_VOL1 	CNCSTATUS.VOL1	/* Volantino 1 agganciato */

#define	O_VOL2 	CNCSTATUS.VOL2	/* Volantino 2 agganciato */
#define	O_VOL3 	CNCSTATUS.VOL3	/* Volantino 3 agganciato */

#define	O_NOALL	CNCSTATUS.NOALL	/* Se 1 no blocco CNC per allarme */
				/* Fuori Soglia assi indipend.    */
#define	O_CUAE	CNCSTATUS.CUAE	/* Cambio utensile automatico escluso	*/

#define	O_SEM  	CNCSTATUS.SEM	/* CNC in manuale */
#define	O_AUT  	CNCSTATUS.AUT	/* CNC in automatico */
#define	O_MAN  	CNCSTATUS.MAN	/* CNC in JOG */
#define	O_JOG  	CNCSTATUS.JOG	/* CNC in JOG */
#define	O_RIP  	CNCSTATUS.RIP	/* CNC in riposizionamento */
#define	O_SET  	CNCSTATUS.SET	/* CNC in SET */
#define	O_EXE  	CNCSTATUS.EXE	/* CNC in modo esecuzione */
#define	O_CNT  	CNCSTATUS.CNT	/* CNC in continua */
#define	O_FND  	CNCSTATUS.FND	/* CNC in modo ricerca */
#define	O_INIMM	CNCSTATUS.INIMM	/* Int immediato pronto o in corso */
#define	O_INSIN	CNCSTATUS.INSIN	/* Int sincrono pronto o in corso */
#define	O_INASI	CNCSTATUS.INASI	/* Int asincrono pronto o in corso */

#define	O_M    	CNCSTATUS.M	/* Codice  f.a.  M */

#define	O_H  	CNCSTATUS.H	/* Codice f.a. H  */

#define	O_T  	CNCSTATUS.T	/* Codice f.a. T  */

#define	O_ATTEN	CNCSTATUS.ATTEN	/* Codice attenzione TOOL  */

#define	O_TDS  	CNCSTATUS.TDS		/* Codice f.a. t,d,s */
#define	O_CODGN CNCSTATUS.CODGN	/* Codice parametro generico  */
#define O_IDXTT CNCSTATUS.IDXTT	/* Nemero  record  letto nel file TT.TAB */ 

#define	O_CGEN 	CNCSTATUS.CGEN	/* Codice CNC : se = 1 tasto rifiutato */
#define	O_CODAL	CNCSTATUS.CODAL	/* Codice allarme CNC		 */
#define	O_CODAT	CNCSTATUS.CODAT   	/* Codice attenzione asse	 */


#define	O_GN 	CNCSTATUS.GN.dword		/* Parametro generico  */
#define	O_GNL	CNCSTATUS.GNL	/*    "		"	low */
#define	O_GNH	CNCSTATUS.GNH	/*    "		"	high */

#define	O_MMSTP	CNCSTATUS.MMSTP	/* Mamut non aggiorna watchdog */

#define	O_NVM  	CNCSTATUS.NVM	/* Nuova f.a.  M */
#define	O_NVH	CNCSTATUS.NVH	/* Nuova f.a. H */
#define	O_NVT  	CNCSTATUS.NVT	/* Nuova f.a.  T */
#define	O_NVGN	CNCSTATUS.NVGN	/* Nuovo parametro generico in output dal cnc */
#define	O_NVS  	CNCSTATUS.NVS	/* Nuova f.a. S */
#define	O_AUTHL CNCSTATUS.AUTHL	/* Part program sospeso in automatico */
#define	O_AKTST CNCSTATUS.AKTST	/* Ack del codice tasto in input su I_TASTC */
#define	O_AKT	CNCSTATUS.AKT	/* Ack alla nuova "t" da tci */

#define	_TST_AX	CNCSTATUS._TST_AX	/* Abilita test contatori assi		*/
#define	_NUM_AX CNCSTATUS._NUM_AX	/* Numero asse con errore		*/
#define	_SGL_VEL CNCSTATUS._SGL_VEL		/* Soglia velocita`			*/
#define	_CNT_ERR CNCSTATUS._CNT_ERR		/* Contatore errori			*/

#define CODAF 	CNCSTATUS.CODAF	/* Codice funzione ausiliaria da eseguire */
#define	STRCONS	CNCSTATUS.STRCONS	/* Sincronismo per la funzione Ausiliaria */
#define ACKCONS	CNCSTATUS.ACKCONS	/* Fatto per la funzione ausiliaria */

#define pon		CNCSTATUS.pon
	
#define	SEQVOL		CNCCTRL.SEQVOL	/* Sequenz. Gestione volantini */
#define	OVRAP		CNCCTRL.OVRAP	/* Commutatore override rapido */
#define	OVFED	    CNCCTRL.OVFED	/* Commutatore override feed */
#define	OVSPE	    CNCCTRL.OVSPE	/* Commutatore override speed */
#define	AXEJOGM	    CNCCTRL.memAXEJOG	/* Commutatore selezione assi */

#define NuPosMag	CNPLCHANDLE.NuPosMag	/* numero posti di magazzino	%V11002			*/
#define NUPOSMAG	CNPLCHANDLE.NuPosMag	/* numero posti di magazzino  %V11002 */ // Per visualizzazione Sin. II
#define NuPosMed	CNPLCHANDLE.NuPosMed	/* numero posti di MEDIO	%V11003			*/
#define NUPOSMED	CNPLCHANDLE.NuPosMed	/* numero posti di MEDIO  %V11003 */ // Per visualizzazione Sin. II
#define NuPosGra	CNPLCHANDLE.NuPosGra	/* numero posti di LARGO	%V11004			*/
#define NUPOSGRA	CNPLCHANDLE.NuPosGra	/* numero posti di LARGO %V11004 */ // Per visualizzazione Sin. II
#define	StaPosMag	CNPLCHANDLE.StaPosMag
#define	STAPOSMAG	CNPLCHANDLE.StaPosMag

#define FATM	CNPLCHANDLE.FATM
#define FATH	CNPLCHANDLE.FATH
#define FATT	CNPLCHANDLE.FATT
#define FATGN	CNPLCHANDLE.FATGN
#define FATS	CNPLCHANDLE.FATS
#define FATTCI	CNPLCHANDLE.FATTCI
#define FATPLC	CNPLCHANDLE.FATPLC

#define AM03	CNPLCHANDLE.AM03
#define AM04	CNPLCHANDLE.AM04
#define AM05	CNPLCHANDLE.AM05
#define AM19	CNPLCHANDLE.AM19
#define AMCG	CNPLCHANDLE.AMCG
#define PSET	CNPLCHANDLE.PSET
#define G84 	CNPLCHANDLE.G84 
#define G184	CNPLCHANDLE.G184
#define NVM		CNPLCHANDLE.NVM
#define NVH		CNPLCHANDLE.NVH
#define NVT		CNPLCHANDLE.NVT
#define NVGN	CNPLCHANDLE.NVGN
#define NVS		CNPLCHANDLE.NVS
#define AUTHL	CNPLCHANDLE.AUTHL
#define AKTST	CNPLCHANDLE.AKTST
#define AKT		CNPLCHANDLE.AKT

#define	JS_R	CNPLCHANDLE.JS_R
#define JS_L	CNPLCHANDLE.JS_L
#define JV_R	CNPLCHANDLE.JV_R
#define JV_L	CNPLCHANDLE.JV_L

#define AXVOL1		CNPLCHANDLE.AXVOL1
#define AXVOL2		CNPLCHANDLE.AXVOL2
#define AXVOL3		CNPLCHANDLE.AXVOL3
#define S_VOL1		CNPLCHANDLE.S_VOL1
#define S_VOL2		CNPLCHANDLE.S_VOL2
#define S_VOL3		CNPLCHANDLE.S_VOL3
#define MS_VOL1		CNPLCHANDLE.MS_VOL1
#define MS_VOL2		CNPLCHANDLE.MS_VOL2
#define MS_VOL3		CNPLCHANDLE.MS_VOL3
#define RC_VOL		CNPLCHANDLE.RC_VOL
#define V_VOL		CNPLCHANDLE.V_VOL
#define RS001		CNPLCHANDLE.RS001
#define RS010		CNPLCHANDLE.RS010
#define RS100		CNPLCHANDLE.RS100
#define O_VOL		CNPLCHANDLE.O_VOL
#define PLAVOL		CNPLCHANDLE.PLAVOL
#define JPLANCIA	CNPLCHANDLE.JPLANCIA
#define ABIASS		CNPLCHANDLE.ABIASS
#define MIS_VOL1	CNPLCHANDLE.MIS_VOL1
#define MIS_VOL2	CNPLCHANDLE.MIS_VOL2
#define MIS_VOL3	CNPLCHANDLE.MIS_VOL3
#define I_VFCS		CNPLCHANDLE.memVFCS

#define APP_IN		CNPLCHANDLE.APP_IN
#define EME_IN		CNPLCHANDLE.EME_IN
#define NUM_IN		CNPLCHANDLE.NUM_IN
#define FASE_IN 	CNPLCHANDLE.FASE_IN
#define ST_IN		CNPLCHANDLE.ST_IN
#define VERFALS		CNPLCHANDLE.VERFALS

#define STASEQZ	CNPLCHANDLE.STASEQZ	/* Stato sequenziatore zero assi da plc	*/
#define StaOpeTo CNPLCHANDLE.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/
#define STAOPETO CNPLCHANDLE.StaOpeTo  	/* Stato  sequenziatore gestione C.U.	*/ // Per visualizzazione Sin. II
#define FlgRicTo CNPLCHANDLE.FlgRicTo	/* Stato operazione routine ricerca tool	*/
#define FLGRICTO CNPLCHANDLE.FlgRicTo	/* Stato operazione routine ricerca tool	*/ // Per visualizzazione Sin. II
#endif



//Macro per Aree CNC
#define CNC_AREA_R(_x_) Aris[_x_]
#define CNC_AREA_CANC(_x_) Acus[_x_]
#define CNC_AREA_RRET(_x_) paretplc_v2->fvdrRe[_x_]
#define CNC_RETENTIVE_LENGTH(_unused_) (sizeof (MM_COMPATIBLE) / sizeof (USHORT))

//Definizioni elementi dati per I/O
#define PLC_BIT_0	bit._00
#define PLC_BIT_1	bit._01
#define PLC_BIT_2	bit._02
#define PLC_BIT_3	bit._03
#define PLC_BIT_4	bit._04
#define PLC_BIT_5	bit._05
#define PLC_BIT_6	bit._06
#define PLC_BIT_7	bit._07
#define PLC_BIT_8	bit._08
#define PLC_BIT_9	bit._09
#define PLC_BIT_10	bit._10
#define PLC_BIT_11	bit._11
#define PLC_BIT_12	bit._12
#define PLC_BIT_13	bit._13
#define PLC_BIT_14	bit._14
#define PLC_BIT_15	bit._15

#define PLC_BYTE_LOW	l
#define PLC_BYTE_HIGH	h
#define PLC_BYTE_0	PLC_BYTE_LOW
#define PLC_BYTE_1	PLC_BYTE_HIGH

//deinizione per IO
#define PLC_INPUT(node, word) ((PPLC_IO_DATA2) &DIGITALIN[node][word])
#define PLC_INPUT_BIT(plc_node, plc_word, plc_bit)		(PLC_INPUT(plc_node, plc_word)->PLC_BIT_##plc_bit)
#define PLC_INPUT_WORD(plc_node, plc_word)				(PLC_INPUT(plc_node, plc_word)->uword)
#define PLC_INPUT_SHORT(plc_node, plc_word)				(PLC_INPUT(plc_node, plc_word)->word)
#define PLC_INPUT_BYTE(plc_node, plc_word, plc_byte)	(PLC_INPUT(plc_node, plc_word)->byte.PLC_BYTE_##plc_byte)

#define PLC_OUTPUT(node, word) ((PPLC_IO_DATA2) &DIGITALOUT[node][word])
#define PLC_OUTPUT_BIT(plc_node, plc_word, plc_bit)		(PLC_OUTPUT(plc_node, plc_word)->PLC_BIT_##plc_bit)
#define PLC_OUTPUT_WORD(plc_node, plc_word)				(PLC_OUTPUT(plc_node, plc_word)->uword)
#define PLC_OUTPUT_SHORT(plc_node, plc_word)			(PLC_OUTPUT(plc_node, plc_word)->word)
#define PLC_OUTPUT_BYTE(plc_node, plc_word, plc_byte)	(PLC_OUTPUT(plc_node, plc_word)->byte.PLC_BYTE_##plc_byte)

#define PLC_AD(node, number)	(ANALOGIN[node][number])
#define PLC_DA(node, number)	(ANALOGOUT[node][number])

#define PLC_ENCODER_VALUE(node, element) (ENCODERVAL[node][element])

//Macro per il PLC
#define		R0		PLC_INPUT_WORD (0, 0)
#define		R1		PLC_INPUT_WORD (0, 1)
#define		R2		PLC_INPUT_WORD (0, 2)
#define		R3		PLC_INPUT_WORD (1, 0)
#define		R4		PLC_INPUT_WORD (1, 1)
#define		R5		PLC_INPUT_WORD (1, 2)
#define		R6		PLC_INPUT_WORD (2, 0)
#define		R7		PLC_INPUT_WORD (2, 1)
#define		R8		PLC_INPUT_WORD (2, 2)
#define		R9		PLC_INPUT_WORD (3, 0)
#define		R10		PLC_INPUT_WORD (3, 1)
#define		R11		PLC_INPUT_WORD (3, 2)

#define		R0_L		PLC_INPUT_BYTE (0, 0, 0)
#define		R0_H		PLC_INPUT_BYTE (0, 0, 1)
#define		R1_L		PLC_INPUT_BYTE (0, 1, 0)
#define		R1_H		PLC_INPUT_BYTE (0, 1, 1)
#define		R2_L		PLC_INPUT_BYTE (0, 2, 0)
#define		R2_H		PLC_INPUT_BYTE (0, 2, 1)
#define		R3_L		PLC_INPUT_BYTE (1, 0, 0)
#define		R3_H		PLC_INPUT_BYTE (1, 0, 1)
#define		R4_L		PLC_INPUT_BYTE (1, 1, 0)
#define		R4_H		PLC_INPUT_BYTE (1, 1, 1)
#define		R5_L		PLC_INPUT_BYTE (1, 2, 0)
#define		R5_H		PLC_INPUT_BYTE (1, 2, 1
#define		R6_L		PLC_INPUT_BYTE (2, 0, 0)
#define		R6_H		PLC_INPUT_BYTE (2, 0, 1)
#define		R7_L		PLC_INPUT_BYTE (2, 1, 0)
#define		R7_H		PLC_INPUT_BYTE (2, 1, 1)
#define		R8_L		PLC_INPUT_BYTE (2, 2, 0)
#define		R8_H		PLC_INPUT_BYTE (2, 2, 1)
#define		R9_L		PLC_INPUT_BYTE (3, 0, 0)
#define		R9_H		PLC_INPUT_BYTE (3, 0, 1)
#define		R10_L		PLC_INPUT_BYTE (3, 1, 0)
#define		R10_H		PLC_INPUT_BYTE (3, 1, 1)
#define		R11_L		PLC_INPUT_BYTE (3, 2, 0)
#define		R11_H		PLC_INPUT_BYTE (3, 2, 1)

#define		T0	PLC_OUTPUT_WORD (0, 0)
#define		T1	PLC_OUTPUT_WORD	(0, 1)
#define		T2	PLC_OUTPUT_WORD (1, 0)
#define		T3	PLC_OUTPUT_WORD (1, 1)
#define		T4	PLC_OUTPUT_WORD (2, 0)
#define		T5	PLC_OUTPUT_WORD (2, 1)
#define		T6	PLC_OUTPUT_WORD (3, 0)
#define		T7	PLC_OUTPUT_WORD (3, 1)

#define		T0_L	PLC_OUTPUT_BYTE (0, 0, 0)
#define		T0_H	PLC_OUTPUT_BYTE (0, 0, 1)
#define		T1_L	PLC_OUTPUT_BYTE (0, 1, 0)
#define		T1_H	PLC_OUTPUT_BYTE (0, 1, 1)
#define		T2_L	PLC_OUTPUT_BYTE (1, 0, 0)
#define		T2_H	PLC_OUTPUT_BYTE (1, 0, 1)
#define		T3_L	PLC_OUTPUT_BYTE (1, 1, 0)
#define		T3_H	PLC_OUTPUT_BYTE (1, 1, 1)
#define		T4_L	PLC_OUTPUT_BYTE (2, 0, 0)
#define		T4_H	PLC_OUTPUT_BYTE (2, 0, 1)
#define		T5_L	PLC_OUTPUT_BYTE (2, 1, 0)
#define		T5_H	PLC_OUTPUT_BYTE (2, 1, 1)
#define		T6_L	PLC_OUTPUT_BYTE (3, 0, 0)
#define		T6_H	PLC_OUTPUT_BYTE (3, 0, 1)
#define		T7_L	PLC_OUTPUT_BYTE (3, 1, 0)
#define		T7_H	PLC_OUTPUT_BYTE (3, 1, 1)

#define		MI_1W1		PLC_INPUT_WORD(0,0)
#define		MI_1W2		PLC_INPUT_WORD(0,1)
#define		MI_1W3		PLC_INPUT_WORD(0,2)

#define		MI_1_1		PLC_INPUT_BIT(0,0,0)
#define		MI_1_2		PLC_INPUT_BIT(0,0,1)
#define		MI_1_3		PLC_INPUT_BIT(0,0,2)
#define		MI_1_4		PLC_INPUT_BIT(0,0,3)
#define		MI_1_5		PLC_INPUT_BIT(0,0,4)
#define		MI_1_6		PLC_INPUT_BIT(0,0,5)
#define		MI_1_7		PLC_INPUT_BIT(0,0,6)
#define		MI_1_8		PLC_INPUT_BIT(0,0,7)
#define		MI_1_9		PLC_INPUT_BIT(0,0,8)
#define		MI_1_10		PLC_INPUT_BIT(0,0,9)
#define		MI_1_11		PLC_INPUT_BIT(0,0,10)
#define		MI_1_12		PLC_INPUT_BIT(0,0,11)
#define		MI_1_13		PLC_INPUT_BIT(0,0,12)
#define		MI_1_14		PLC_INPUT_BIT(0,0,13)
#define		MI_1_15		PLC_INPUT_BIT(0,0,14)
#define		MI_1_16		PLC_INPUT_BIT(0,0,15)

#define		MI_1_17		PLC_INPUT_BIT(0,1,0)
#define		MI_1_18		PLC_INPUT_BIT(0,1,1)
#define		MI_1_19		PLC_INPUT_BIT(0,1,2)
#define		MI_1_20		PLC_INPUT_BIT(0,1,3)
#define		MI_1_21		PLC_INPUT_BIT(0,1,4)
#define		MI_1_22		PLC_INPUT_BIT(0,1,5)
#define		MI_1_23		PLC_INPUT_BIT(0,1,6)
#define		MI_1_24		PLC_INPUT_BIT(0,1,7)
#define		MI_1_25		PLC_INPUT_BIT(0,1,8)
#define		MI_1_26		PLC_INPUT_BIT(0,1,9)
#define		MI_1_27		PLC_INPUT_BIT(0,1,10)
#define		MI_1_28		PLC_INPUT_BIT(0,1,11)
#define		MI_1_29		PLC_INPUT_BIT(0,1,12)
#define		MI_1_30		PLC_INPUT_BIT(0,1,13)
#define		MI_1_31		PLC_INPUT_BIT(0,1,14)
#define		MI_1_32		PLC_INPUT_BIT(0,1,15)

#define		MI_1_33		PLC_INPUT_BIT(0,2,0)
#define		MI_1_34		PLC_INPUT_BIT(0,2,1)
#define		MI_1_35		PLC_INPUT_BIT(0,2,2)
#define		MI_1_36		PLC_INPUT_BIT(0,2,3)
#define		MI_1_37		PLC_INPUT_BIT(0,2,4)
#define		MI_1_38		PLC_INPUT_BIT(0,2,5)
#define		MI_1_39		PLC_INPUT_BIT(0,2,6)
#define		MI_1_40		PLC_INPUT_BIT(0,2,7)
#define		MI_1_41		PLC_INPUT_BIT(0,2,8)
#define		MI_1_42		PLC_INPUT_BIT(0,2,9)
#define		MI_1_43		PLC_INPUT_BIT(0,2,10)
#define		MI_1_44		PLC_INPUT_BIT(0,2,11)
#define		MI_1_45		PLC_INPUT_BIT(0,2,12)
#define		MI_1_46		PLC_INPUT_BIT(0,2,13)
#define		MI_1_47		PLC_INPUT_BIT(0,2,14)
#define		MI_1_48		PLC_INPUT_BIT(0,2,15)

#define		MI_2W1		PLC_INPUT_WORD(1,0)
#define		MI_2W2		PLC_INPUT_WORD(1,1)
#define		MI_2W3		PLC_INPUT_WORD(1,2)

#define		MI_2_1		PLC_INPUT_BIT(1,0,0)
#define		MI_2_2		PLC_INPUT_BIT(1,0,1)
#define		MI_2_3		PLC_INPUT_BIT(1,0,2)
#define		MI_2_4		PLC_INPUT_BIT(1,0,3)
#define		MI_2_5		PLC_INPUT_BIT(1,0,4)
#define		MI_2_6		PLC_INPUT_BIT(1,0,5)
#define		MI_2_7		PLC_INPUT_BIT(1,0,6)
#define		MI_2_8		PLC_INPUT_BIT(1,0,7)
#define		MI_2_9		PLC_INPUT_BIT(1,0,8)
#define		MI_2_10		PLC_INPUT_BIT(1,0,9)
#define		MI_2_11		PLC_INPUT_BIT(1,0,10)
#define		MI_2_12		PLC_INPUT_BIT(1,0,11)
#define		MI_2_13		PLC_INPUT_BIT(1,0,12)
#define		MI_2_14		PLC_INPUT_BIT(1,0,13)
#define		MI_2_15		PLC_INPUT_BIT(1,0,14)
#define		MI_2_16		PLC_INPUT_BIT(1,0,15)

#define		MI_2_17		PLC_INPUT_BIT(1,1,0)
#define		MI_2_18		PLC_INPUT_BIT(1,1,1)
#define		MI_2_19		PLC_INPUT_BIT(1,1,2)
#define		MI_2_20		PLC_INPUT_BIT(1,1,3)
#define		MI_2_21		PLC_INPUT_BIT(1,1,4)
#define		MI_2_22		PLC_INPUT_BIT(1,1,5)
#define		MI_2_23		PLC_INPUT_BIT(1,1,6)
#define		MI_2_24		PLC_INPUT_BIT(1,1,7)
#define		MI_2_25		PLC_INPUT_BIT(1,1,8)
#define		MI_2_26		PLC_INPUT_BIT(1,1,9)
#define		MI_2_27		PLC_INPUT_BIT(1,1,10)
#define		MI_2_28		PLC_INPUT_BIT(1,1,11)
#define		MI_2_29		PLC_INPUT_BIT(1,1,12)
#define		MI_2_30		PLC_INPUT_BIT(1,1,13)
#define		MI_2_31		PLC_INPUT_BIT(1,1,14)
#define		MI_2_32		PLC_INPUT_BIT(1,1,15)

#define		MI_2_33		PLC_INPUT_BIT(1,2,0)
#define		MI_2_34		PLC_INPUT_BIT(1,2,1)
#define		MI_2_35		PLC_INPUT_BIT(1,2,2)
#define		MI_2_36		PLC_INPUT_BIT(1,2,3)
#define		MI_2_37		PLC_INPUT_BIT(1,2,4)
#define		MI_2_38		PLC_INPUT_BIT(1,2,5)
#define		MI_2_39		PLC_INPUT_BIT(1,2,6)
#define		MI_2_40		PLC_INPUT_BIT(1,2,7)
#define		MI_2_41		PLC_INPUT_BIT(1,2,8)
#define		MI_2_42		PLC_INPUT_BIT(1,2,9)
#define		MI_2_43		PLC_INPUT_BIT(1,2,10)
#define		MI_2_44		PLC_INPUT_BIT(1,2,11)
#define		MI_2_45		PLC_INPUT_BIT(1,2,12)
#define		MI_2_46		PLC_INPUT_BIT(1,2,13)
#define		MI_2_47		PLC_INPUT_BIT(1,2,14)
#define		MI_2_48		PLC_INPUT_BIT(1,2,15)

#define		MI_3W1		PLC_INPUT_WORD(2,0)
#define		MI_3W2		PLC_INPUT_WORD(2,1)
#define		MI_3W3		PLC_INPUT_WORD(2,2)
#define		MI_3W4		PLC_INPUT_WORD(2,3)

#define		MI_3_1		PLC_INPUT_BIT(2,0,0)
#define		MI_3_2		PLC_INPUT_BIT(2,0,1)
#define		MI_3_3		PLC_INPUT_BIT(2,0,2)
#define		MI_3_4		PLC_INPUT_BIT(2,0,3)
#define		MI_3_5		PLC_INPUT_BIT(2,0,4)
#define		MI_3_6		PLC_INPUT_BIT(2,0,5)
#define		MI_3_7		PLC_INPUT_BIT(2,0,6)
#define		MI_3_8		PLC_INPUT_BIT(2,0,7)
#define		MI_3_9		PLC_INPUT_BIT(2,0,8)
#define		MI_3_10		PLC_INPUT_BIT(2,0,9)
#define		MI_3_11		PLC_INPUT_BIT(2,0,10)
#define		MI_3_12		PLC_INPUT_BIT(2,0,11)
#define		MI_3_13		PLC_INPUT_BIT(2,0,12)
#define		MI_3_14		PLC_INPUT_BIT(2,0,13)
#define		MI_3_15		PLC_INPUT_BIT(2,0,14)
#define		MI_3_16		PLC_INPUT_BIT(2,0,15)

#define		MI_3_17		PLC_INPUT_BIT(2,1,0)
#define		MI_3_18		PLC_INPUT_BIT(2,1,1)
#define		MI_3_19		PLC_INPUT_BIT(2,1,2)
#define		MI_3_20		PLC_INPUT_BIT(2,1,3)
#define		MI_3_21		PLC_INPUT_BIT(2,1,4)
#define		MI_3_22		PLC_INPUT_BIT(2,1,5)
#define		MI_3_23		PLC_INPUT_BIT(2,1,6)
#define		MI_3_24		PLC_INPUT_BIT(2,1,7)
#define		MI_3_25		PLC_INPUT_BIT(2,1,8)
#define		MI_3_26		PLC_INPUT_BIT(2,1,9)
#define		MI_3_27		PLC_INPUT_BIT(2,1,10)
#define		MI_3_28		PLC_INPUT_BIT(2,1,11)
#define		MI_3_29		PLC_INPUT_BIT(2,1,12)
#define		MI_3_30		PLC_INPUT_BIT(2,1,13)
#define		MI_3_31		PLC_INPUT_BIT(2,1,14)
#define		MI_3_32		PLC_INPUT_BIT(2,1,15)

#define		MI_3_33		PLC_INPUT_BIT(2,2,0)
#define		MI_3_34		PLC_INPUT_BIT(2,2,1)
#define		MI_3_35		PLC_INPUT_BIT(2,2,2)
#define		MI_3_36		PLC_INPUT_BIT(2,2,3)
#define		MI_3_37		PLC_INPUT_BIT(2,2,4)
#define		MI_3_38		PLC_INPUT_BIT(2,2,5)
#define		MI_3_39		PLC_INPUT_BIT(2,2,6)
#define		MI_3_40		PLC_INPUT_BIT(2,2,7)
#define		MI_3_41		PLC_INPUT_BIT(2,2,8)
#define		MI_3_42		PLC_INPUT_BIT(2,2,9)
#define		MI_3_43		PLC_INPUT_BIT(2,2,10)
#define		MI_3_44		PLC_INPUT_BIT(2,2,11)
#define		MI_3_45		PLC_INPUT_BIT(2,2,12)
#define		MI_3_46		PLC_INPUT_BIT(2,2,13)
#define		MI_3_47		PLC_INPUT_BIT(2,2,14)
#define		MI_3_48		PLC_INPUT_BIT(2,2,15)

#define		MI_4W1		PLC_INPUT_WORD(3,0)
#define		MI_4W2		PLC_INPUT_WORD(3,1)
#define		MI_4W3		PLC_INPUT_WORD(3,2)

#define		MI_4_1		PLC_INPUT_BIT(3,0,0)
#define		MI_4_2		PLC_INPUT_BIT(3,0,1)
#define		MI_4_3		PLC_INPUT_BIT(3,0,2)
#define		MI_4_4		PLC_INPUT_BIT(3,0,3)
#define		MI_4_5		PLC_INPUT_BIT(3,0,4)
#define		MI_4_6		PLC_INPUT_BIT(3,0,5)
#define		MI_4_7		PLC_INPUT_BIT(3,0,6)
#define		MI_4_8		PLC_INPUT_BIT(3,0,7)
#define		MI_4_9		PLC_INPUT_BIT(3,0,8)
#define		MI_4_10		PLC_INPUT_BIT(3,0,9)
#define		MI_4_11		PLC_INPUT_BIT(3,0,10)
#define		MI_4_12		PLC_INPUT_BIT(3,0,11)
#define		MI_4_13		PLC_INPUT_BIT(3,0,12)
#define		MI_4_14		PLC_INPUT_BIT(3,0,13)
#define		MI_4_15		PLC_INPUT_BIT(3,0,14)
#define		MI_4_16		PLC_INPUT_BIT(3,0,15)

#define		MI_4_17		PLC_INPUT_BIT(3,1,0)
#define		MI_4_18		PLC_INPUT_BIT(3,1,1)
#define		MI_4_19		PLC_INPUT_BIT(3,1,2)
#define		MI_4_20		PLC_INPUT_BIT(3,1,3)
#define		MI_4_21		PLC_INPUT_BIT(3,1,4)
#define		MI_4_22		PLC_INPUT_BIT(3,1,5)
#define		MI_4_23		PLC_INPUT_BIT(3,1,6)
#define		MI_4_24		PLC_INPUT_BIT(3,1,7)
#define		MI_4_25		PLC_INPUT_BIT(3,1,8)
#define		MI_4_26		PLC_INPUT_BIT(3,1,9)
#define		MI_4_27		PLC_INPUT_BIT(3,1,10)
#define		MI_4_28		PLC_INPUT_BIT(3,1,11)
#define		MI_4_29		PLC_INPUT_BIT(3,1,12)
#define		MI_4_30		PLC_INPUT_BIT(3,1,13)
#define		MI_4_31		PLC_INPUT_BIT(3,1,14)
#define		MI_4_32		PLC_INPUT_BIT(3,1,15)

#define		MI_4_33		PLC_INPUT_BIT(3,2,0)
#define		MI_4_34		PLC_INPUT_BIT(3,2,1)
#define		MI_4_35		PLC_INPUT_BIT(3,2,2)
#define		MI_4_36		PLC_INPUT_BIT(3,2,3)
#define		MI_4_37		PLC_INPUT_BIT(3,2,4)
#define		MI_4_38		PLC_INPUT_BIT(3,2,5)
#define		MI_4_39		PLC_INPUT_BIT(3,2,6)
#define		MI_4_40		PLC_INPUT_BIT(3,2,7)
#define		MI_4_41		PLC_INPUT_BIT(3,2,8)
#define		MI_4_42		PLC_INPUT_BIT(3,2,9)
#define		MI_4_43		PLC_INPUT_BIT(3,2,10)
#define		MI_4_44		PLC_INPUT_BIT(3,2,11)
#define		MI_4_45		PLC_INPUT_BIT(3,2,12)
#define		MI_4_46		PLC_INPUT_BIT(3,2,13)
#define		MI_4_47		PLC_INPUT_BIT(3,2,14)
#define		MI_4_48		PLC_INPUT_BIT(3,2,15)

#define		MO_1W1		PLC_OUTPUT_WORD(0,0)
#define		MO_1W2		PLC_OUTPUT_WORD(0,1)
#define		MO_1W3		PLC_OUTPUT_WORD(0,2)

#define		MO_1_1		PLC_OUTPUT_BIT(0,0,0)
#define		MO_1_2		PLC_OUTPUT_BIT(0,0,1)
#define		MO_1_3		PLC_OUTPUT_BIT(0,0,2)
#define		MO_1_4		PLC_OUTPUT_BIT(0,0,3)
#define		MO_1_5		PLC_OUTPUT_BIT(0,0,4)
#define		MO_1_6		PLC_OUTPUT_BIT(0,0,5)
#define		MO_1_7		PLC_OUTPUT_BIT(0,0,6)
#define		MO_1_8		PLC_OUTPUT_BIT(0,0,7)
#define		MO_1_9		PLC_OUTPUT_BIT(0,0,8)
#define		MO_1_10		PLC_OUTPUT_BIT(0,0,9)
#define		MO_1_11		PLC_OUTPUT_BIT(0,0,10)
#define		MO_1_12		PLC_OUTPUT_BIT(0,0,11)
#define		MO_1_13		PLC_OUTPUT_BIT(0,0,12)
#define		MO_1_14		PLC_OUTPUT_BIT(0,0,13)
#define		MO_1_15		PLC_OUTPUT_BIT(0,0,14)
#define		MO_1_16		PLC_OUTPUT_BIT(0,0,15)

#define		MO_1_17		PLC_OUTPUT_BIT(0,1,0)
#define		MO_1_18		PLC_OUTPUT_BIT(0,1,1)
#define		MO_1_19		PLC_OUTPUT_BIT(0,1,2)
#define		MO_1_20		PLC_OUTPUT_BIT(0,1,3)
#define		MO_1_21		PLC_OUTPUT_BIT(0,1,4)
#define		MO_1_22		PLC_OUTPUT_BIT(0,1,5)
#define		MO_1_23		PLC_OUTPUT_BIT(0,1,6)
#define		MO_1_24		PLC_OUTPUT_BIT(0,1,7)
#define		MO_1_25		PLC_OUTPUT_BIT(0,1,8)
#define		MO_1_26		PLC_OUTPUT_BIT(0,1,9)
#define		MO_1_27		PLC_OUTPUT_BIT(0,1,10)
#define		MO_1_28		PLC_OUTPUT_BIT(0,1,11)
#define		MO_1_29		PLC_OUTPUT_BIT(0,1,12)
#define		MO_1_30		PLC_OUTPUT_BIT(0,1,13)
#define		MO_1_31		PLC_OUTPUT_BIT(0,1,14)
#define		MO_1_32		PLC_OUTPUT_BIT(0,1,15)

#define		MO_1_33		PLC_OUTPUT_BIT(0,2,0)
#define		MO_1_34		PLC_OUTPUT_BIT(0,2,1)
#define		MO_1_35		PLC_OUTPUT_BIT(0,2,2)
#define		MO_1_36		PLC_OUTPUT_BIT(0,2,3)
#define		MO_1_37		PLC_OUTPUT_BIT(0,2,4)
#define		MO_1_38		PLC_OUTPUT_BIT(0,2,5)
#define		MO_1_39		PLC_OUTPUT_BIT(0,2,6)
#define		MO_1_40		PLC_OUTPUT_BIT(0,2,7)
#define		MO_1_41		PLC_OUTPUT_BIT(0,2,8)
#define		MO_1_42		PLC_OUTPUT_BIT(0,2,9)
#define		MO_1_43		PLC_OUTPUT_BIT(0,2,10)
#define		MO_1_44		PLC_OUTPUT_BIT(0,2,11)
#define		MO_1_45		PLC_OUTPUT_BIT(0,2,12)
#define		MO_1_46		PLC_OUTPUT_BIT(0,2,13)
#define		MO_1_47		PLC_OUTPUT_BIT(0,2,14)
#define		MO_1_48		PLC_OUTPUT_BIT(0,2,15)

#define		MO_2W1		PLC_OUTPUT_WORD(1,0)
#define		MO_2W2		PLC_OUTPUT_WORD(1,1)
#define		MO_2W3		PLC_OUTPUT_WORD(1,2)

#define		MO_2_1		PLC_OUTPUT_BIT(1,0,0)
#define		MO_2_2		PLC_OUTPUT_BIT(1,0,1)
#define		MO_2_3		PLC_OUTPUT_BIT(1,0,2)
#define		MO_2_4		PLC_OUTPUT_BIT(1,0,3)
#define		MO_2_5		PLC_OUTPUT_BIT(1,0,4)
#define		MO_2_6		PLC_OUTPUT_BIT(1,0,5)
#define		MO_2_7		PLC_OUTPUT_BIT(1,0,6)
#define		MO_2_8		PLC_OUTPUT_BIT(1,0,7)
#define		MO_2_9		PLC_OUTPUT_BIT(1,0,8)
#define		MO_2_10		PLC_OUTPUT_BIT(1,0,9)
#define		MO_2_11		PLC_OUTPUT_BIT(1,0,10)
#define		MO_2_12		PLC_OUTPUT_BIT(1,0,11)
#define		MO_2_13		PLC_OUTPUT_BIT(1,0,12)
#define		MO_2_14		PLC_OUTPUT_BIT(1,0,13)
#define		MO_2_15		PLC_OUTPUT_BIT(1,0,14)
#define		MO_2_16		PLC_OUTPUT_BIT(1,0,15)

#define		MO_2_17		PLC_OUTPUT_BIT(1,1,0)
#define		MO_2_18		PLC_OUTPUT_BIT(1,1,1)
#define		MO_2_19		PLC_OUTPUT_BIT(1,1,2)
#define		MO_2_20		PLC_OUTPUT_BIT(1,1,3)
#define		MO_2_21		PLC_OUTPUT_BIT(1,1,4)
#define		MO_2_22		PLC_OUTPUT_BIT(1,1,5)
#define		MO_2_23		PLC_OUTPUT_BIT(1,1,6)
#define		MO_2_24		PLC_OUTPUT_BIT(1,1,7)
#define		MO_2_25		PLC_OUTPUT_BIT(1,1,8)
#define		MO_2_26		PLC_OUTPUT_BIT(1,1,9)
#define		MO_2_27		PLC_OUTPUT_BIT(1,1,10)
#define		MO_2_28		PLC_OUTPUT_BIT(1,1,11)
#define		MO_2_29		PLC_OUTPUT_BIT(1,1,12)
#define		MO_2_30		PLC_OUTPUT_BIT(1,1,13)
#define		MO_2_31		PLC_OUTPUT_BIT(1,1,14)
#define		MO_2_32		PLC_OUTPUT_BIT(1,1,15)

#define		MO_2_33		PLC_OUTPUT_BIT(1,2,0)
#define		MO_2_34		PLC_OUTPUT_BIT(1,2,1)
#define		MO_2_35		PLC_OUTPUT_BIT(1,2,2)
#define		MO_2_36		PLC_OUTPUT_BIT(1,2,3)
#define		MO_2_37		PLC_OUTPUT_BIT(1,2,4)
#define		MO_2_38		PLC_OUTPUT_BIT(1,2,5)
#define		MO_2_39		PLC_OUTPUT_BIT(1,2,6)
#define		MO_2_40		PLC_OUTPUT_BIT(1,2,7)
#define		MO_2_41		PLC_OUTPUT_BIT(1,2,8)
#define		MO_2_42		PLC_OUTPUT_BIT(1,2,9)
#define		MO_2_43		PLC_OUTPUT_BIT(1,2,10)
#define		MO_2_44		PLC_OUTPUT_BIT(1,2,11)
#define		MO_2_45		PLC_OUTPUT_BIT(1,2,12)
#define		MO_2_46		PLC_OUTPUT_BIT(1,2,13)
#define		MO_2_47		PLC_OUTPUT_BIT(1,2,14)
#define		MO_2_48		PLC_OUTPUT_BIT(1,2,15)

#define		MO_3W1		PLC_OUTPUT_WORD(2,0)
#define		MO_3W2		PLC_OUTPUT_WORD(2,1)
#define		MO_3W3		PLC_OUTPUT_WORD(2,2)

#define		MO_3_1		PLC_OUTPUT_BIT(2,0,0)
#define		MO_3_2		PLC_OUTPUT_BIT(2,0,1)
#define		MO_3_3		PLC_OUTPUT_BIT(2,0,2)
#define		MO_3_4		PLC_OUTPUT_BIT(2,0,3)
#define		MO_3_5		PLC_OUTPUT_BIT(2,0,4)
#define		MO_3_6		PLC_OUTPUT_BIT(2,0,5)
#define		MO_3_7		PLC_OUTPUT_BIT(2,0,6)
#define		MO_3_8		PLC_OUTPUT_BIT(2,0,7)
#define		MO_3_9		PLC_OUTPUT_BIT(2,0,8)
#define		MO_3_10		PLC_OUTPUT_BIT(2,0,9)
#define		MO_3_11		PLC_OUTPUT_BIT(2,0,10)
#define		MO_3_12		PLC_OUTPUT_BIT(2,0,11)
#define		MO_3_13		PLC_OUTPUT_BIT(2,0,12)
#define		MO_3_14		PLC_OUTPUT_BIT(2,0,13)
#define		MO_3_15		PLC_OUTPUT_BIT(2,0,14)
#define		MO_3_16		PLC_OUTPUT_BIT(2,0,15)

#define		MO_3_17		PLC_OUTPUT_BIT(2,1,0)
#define		MO_3_18		PLC_OUTPUT_BIT(2,1,1)
#define		MO_3_19		PLC_OUTPUT_BIT(2,1,2)
#define		MO_3_20		PLC_OUTPUT_BIT(2,1,3)
#define		MO_3_21		PLC_OUTPUT_BIT(2,1,4)
#define		MO_3_22		PLC_OUTPUT_BIT(2,1,5)
#define		MO_3_23		PLC_OUTPUT_BIT(2,1,6)
#define		MO_3_24		PLC_OUTPUT_BIT(2,1,7)
#define		MO_3_25		PLC_OUTPUT_BIT(2,1,8)
#define		MO_3_26		PLC_OUTPUT_BIT(2,1,9)
#define		MO_3_27		PLC_OUTPUT_BIT(2,1,10)
#define		MO_3_28		PLC_OUTPUT_BIT(2,1,11)
#define		MO_3_29		PLC_OUTPUT_BIT(2,1,12)
#define		MO_3_30		PLC_OUTPUT_BIT(2,1,13)
#define		MO_3_31		PLC_OUTPUT_BIT(2,1,14)
#define		MO_3_32		PLC_OUTPUT_BIT(2,1,15)

#define		MO_3_33		PLC_OUTPUT_BIT(2,2,0)
#define		MO_3_34		PLC_OUTPUT_BIT(2,2,1)
#define		MO_3_35		PLC_OUTPUT_BIT(2,2,2)
#define		MO_3_36		PLC_OUTPUT_BIT(2,2,3)
#define		MO_3_37		PLC_OUTPUT_BIT(2,2,4)
#define		MO_3_38		PLC_OUTPUT_BIT(2,2,5)
#define		MO_3_39		PLC_OUTPUT_BIT(2,2,6)
#define		MO_3_40		PLC_OUTPUT_BIT(2,2,7)
#define		MO_3_41		PLC_OUTPUT_BIT(2,2,8)
#define		MO_3_42		PLC_OUTPUT_BIT(2,2,9)
#define		MO_3_43		PLC_OUTPUT_BIT(2,2,10)
#define		MO_3_44		PLC_OUTPUT_BIT(2,2,11)
#define		MO_3_45		PLC_OUTPUT_BIT(2,2,12)
#define		MO_3_46		PLC_OUTPUT_BIT(2,2,13)
#define		MO_3_47		PLC_OUTPUT_BIT(2,2,14)
#define		MO_3_48		PLC_OUTPUT_BIT(2,2,15)

#define		MO_4W1		PLC_OUTPUT_WORD(3,0)
#define		MO_4W2		PLC_OUTPUT_WORD(3,1)
#define		MO_4W3		PLC_OUTPUT_WORD(3,2)

#define		MO_4_1		PLC_OUTPUT_BIT(3,0,0)
#define		MO_4_2		PLC_OUTPUT_BIT(3,0,1)
#define		MO_4_3		PLC_OUTPUT_BIT(3,0,2)
#define		MO_4_4		PLC_OUTPUT_BIT(3,0,3)
#define		MO_4_5		PLC_OUTPUT_BIT(3,0,4)
#define		MO_4_6		PLC_OUTPUT_BIT(3,0,5)
#define		MO_4_7		PLC_OUTPUT_BIT(3,0,6)
#define		MO_4_8		PLC_OUTPUT_BIT(3,0,7)
#define		MO_4_9		PLC_OUTPUT_BIT(3,0,8)
#define		MO_4_10		PLC_OUTPUT_BIT(3,0,9)
#define		MO_4_11		PLC_OUTPUT_BIT(3,0,10)
#define		MO_4_12		PLC_OUTPUT_BIT(3,0,11)
#define		MO_4_13		PLC_OUTPUT_BIT(3,0,12)
#define		MO_4_14		PLC_OUTPUT_BIT(3,0,13)
#define		MO_4_15		PLC_OUTPUT_BIT(3,0,14)
#define		MO_4_16		PLC_OUTPUT_BIT(3,0,15)

#define		MO_4_17		PLC_OUTPUT_BIT(3,1,0)
#define		MO_4_18		PLC_OUTPUT_BIT(3,1,1)
#define		MO_4_19		PLC_OUTPUT_BIT(3,1,2)
#define		MO_4_20		PLC_OUTPUT_BIT(3,1,3)
#define		MO_4_21		PLC_OUTPUT_BIT(3,1,4)
#define		MO_4_22		PLC_OUTPUT_BIT(3,1,5)
#define		MO_4_23		PLC_OUTPUT_BIT(3,1,6)
#define		MO_4_24		PLC_OUTPUT_BIT(3,1,7)
#define		MO_4_25		PLC_OUTPUT_BIT(3,1,8)
#define		MO_4_26		PLC_OUTPUT_BIT(3,1,9)
#define		MO_4_27		PLC_OUTPUT_BIT(3,1,10)
#define		MO_4_28		PLC_OUTPUT_BIT(3,1,11)
#define		MO_4_29		PLC_OUTPUT_BIT(3,1,12)
#define		MO_4_30		PLC_OUTPUT_BIT(3,1,13)
#define		MO_4_31		PLC_OUTPUT_BIT(3,1,14)
#define		MO_4_32		PLC_OUTPUT_BIT(3,1,15)

#define		MO_4_33		PLC_OUTPUT_BIT(3,2,0)
#define		MO_4_34		PLC_OUTPUT_BIT(3,2,1)
#define		MO_4_35		PLC_OUTPUT_BIT(3,2,2)
#define		MO_4_36		PLC_OUTPUT_BIT(3,2,3)
#define		MO_4_37		PLC_OUTPUT_BIT(3,2,4)
#define		MO_4_38		PLC_OUTPUT_BIT(3,2,5)
#define		MO_4_39		PLC_OUTPUT_BIT(3,2,6)
#define		MO_4_40		PLC_OUTPUT_BIT(3,2,7)
#define		MO_4_41		PLC_OUTPUT_BIT(3,2,8)
#define		MO_4_42		PLC_OUTPUT_BIT(3,2,9)
#define		MO_4_43		PLC_OUTPUT_BIT(3,2,10)
#define		MO_4_44		PLC_OUTPUT_BIT(3,2,11)
#define		MO_4_45		PLC_OUTPUT_BIT(3,2,12)
#define		MO_4_46		PLC_OUTPUT_BIT(3,2,13)
#define		MO_4_47		PLC_OUTPUT_BIT(3,2,14)
#define		MO_4_48		PLC_OUTPUT_BIT(3,2,15)

#define		AD1	PLC_AD(0, 0)
#define		AD2	PLC_AD(0, 1)
#define		AD3	PLC_AD(0, 2)
#define		AD4	PLC_AD(1, 0)
#define		AD5	PLC_AD(1, 1)
#define		AD6	PLC_AD(1, 2)
#define		AD7	PLC_AD(2, 0)
#define		AD8	PLC_AD(2, 1)

#define		DA1	PLC_DA(0, 0)
#define		DA2	PLC_DA(0, 1)
#define		DA3	PLC_DA(0, 2)
#define		DA4	PLC_DA(0, 3)

#define PosPic(_CodPos_)	_PositionToolSmall(&CNPLCHANDLE, _CodPos_)
#define PosMed(_CodPos_)	_PositionToolMedium(&CNPLCHANDLE, _CodPos_)
#define PosGra(_CodPos_)	_PositionToolLarge(&CNPLCHANDLE, _CodPos_)
#define BlkRec(_CodUte_, _CodPos_)	_BlkRec(&CNPLCHANDLE, _CodUte_, _CodPos_)
#define SblRec(_CodUte_, _CodPos_)	_SblRec(&CNPLCHANDLE, _CodUte_, _CodPos_)
#define CerPos(_CodUte_, _pcer_pos_)	_CerPos(&CNPLCHANDLE, _CodUte_, _pcer_pos_)
#define StsVit(_CodUte_, _CodPos_, _psts_vit_)	_StsVit(&CNPLCHANDLE, _CodUte_, _CodPos_, _psts_vit_)
#define ScrOff(_CodUte_, _CodPos_, _pscr_off_)	_ScrOff(&CNPLCHANDLE, _CodUte_, _CodPos_, _pscr_off_)
#define ScrMor(_CodUte_, _CodPos_)	_ScrMor(&CNPLCHANDLE, _CodUte_, _CodPos_)
#define ScrPos(_CodUte_, _CoCodPos_, _CoNuoPos_)	_ScrPos(&CNPLCHANDLE, _CodUte_, _CoCodPos_, _CoNuoPos_)
#define OfRaLu(_CodUte_, _CodPos_, _pof_ralu_)	_OfRaLu(&CNPLCHANDLE, _CodUte_, _CodPos_, _pof_ralu_)
#define BlkTab()	_BlkTab(&CNPLCHANDLE)
#define SblTab()	_SblTab(&CNPLCHANDLE)
#define ABSPIND(_numaxe_)	_ABSPIND(&CNCSTATUS, &CNPLCHANDLE, &AXSTATUS[_numaxe_])


short  __inline LegAtAx( unsigned short nasse ) {
	if (nasse >= 12) return -1;
	else return (short) AXSTATUS[nasse].warning;
}

short  __inline LegAlAx( unsigned short nasse ) {
	if (nasse >= 12) return -1;
	else return (short) AXSTATUS[nasse].alarm;
}

void __inline GetConfCn( CONF_CN * pconf ) {
	if (pconf) memcpy (pconf, &CONFCN, sizeof (CONFCN));
}

typedef struct	_STATO_TOL {
	long		tol_ta,			/* numero codice utensile 	*/
						/* attivo	                */
			tol_da;			/* numero posto in tabelle      */
						/* utensile attivo	        */
	long		tol_td;			/* numero codice utensile	*/
						/* desiderato (dle T letto).    */

	float		tol_ruta,	 	/* valore del raggio utensile   */
						/* desiderato attivo		*/
			tol_luta;	 	/* valore lunghezza utensile    */
						/* attivo	                */
	float		tol_rutd,	 	/* valore del raggio utensile   */
						/* desiderato (del T letto). 	*/
			tol_lutd;	 	/* valore lunghezza utensile    */
						/* desiderato (del T letto). 	*/
						/* desiderato.			*/
} STATO_TOL, *PSTATO_TOL;

typedef CNPLC_PROGRAM_STATUS STATO_PRO;
typedef PCNPLC_PROGRAM_STATUS PSTATO_PRO;

void __inline GetStaTol( STATO_TOL * pstato ) {
	pstato->tol_ta= TOOLSTATUS.tol_ta;
	pstato->tol_da= TOOLSTATUS.tol_da;
	pstato->tol_td= TOOLSTATUS.tol_td;

	pstato->tol_ruta= (float) TOOLSTATUS.tol_ruta;
	pstato->tol_luta= (float) TOOLSTATUS.tol_luta;
	pstato->tol_rutd= (float) TOOLSTATUS.tol_rutd;
	pstato->tol_lutd= (float) TOOLSTATUS.tol_lutd;
}


#define QREALE 	 0 
#define QPROGR	 1
#define QERROR	 2
#define DISTAN	 3

/* Struttura per invio quote e stato assi			*/
/* tramite routine : lquote(tipo, stassi, selasse)		*/
typedef struct _STASSI_V3 {
	double quota[MAXCNC];
	short  stato[MAXCNC];
} STASSI_V3, *PSTASSI_V3;

typedef struct _STASSI {
	float quota[MAXCNC];
	short  stato[MAXCNC];
} STASSI, *PSTASSI;

#define ASSE_ALL 1	/* Asse in allarme   		*/
#define ASSE_LIB 2	/* Asse in libera servo	    	*/
#define ASSE_NOSET 4	/* Zero asse non fatto		*/
#define ASSE_JOG 8	/* Asse in JOG		    	*/

void __inline lquote2( short format, STASSI_V3 *stassi, long selas ) {
	long index = 0,
		bit = 1;
	if (!stassi) return;
	memset (stassi, 0, sizeof (*stassi));
	for (; index < CNCSTATUS.axesNumber; index++, bit <<= 1) {
		if (!(bit & selas)) continue;
		switch (format) {
		case QREALE:
			stassi->quota [index] = AXSTATUS[index].preal; break;
		case QPROGR:
			stassi->quota [index] = AXSTATUS[index].pprog; break;
		case QERROR:
			stassi->quota [index] = AXSTATUS[index].perror; break;
		case DISTAN:
			stassi->quota [index] = AXSTATUS[index].pdist; break;
		default:
			return;
			break;
		}
		if (!AXSTATUS[index].statusFlags.AOK) stassi->stato[index] |= ASSE_ALL;
		if (AXSTATUS[index].statusFlags2.LSR) stassi->stato[index] |= ASSE_LIB;
		if (!AXSTATUS[index].statusFlags.SEE) stassi->stato[index] |= ASSE_NOSET;
		//todo: manca il flag ASSE_JOG
		//if (!AXSTATUS[index].statusFlags.SEE) stassi->stato[index] |= ASSE_JOG;
	}
}

void __inline lquote( short format, STASSI *stassi, long selas ) {
	STASSI_V3 loc_stassi;
	long index = 0,
		bit = 1;
	if (!stassi) return;
	memset (stassi, 0, sizeof (*stassi));
	lquote2 (format, &loc_stassi, selas);
	for (; index < CNCSTATUS.axesNumber; index++, bit <<= 1) {
		if (!(bit & selas)) continue;
		stassi->quota[index] = (float) loc_stassi.quota[index];
		stassi->stato[index] = loc_stassi.stato[index];
	}
}

void __inline lquote2_MC( CNPLC_CNCSTATUS CncSts, PCNCPLC_AXIS_STATUS AxisSts, short format, STASSI_V3 *stassi, long selas ) {
	long index = 0,
		 bit = 1;
	UCHAR axesNumber;

	axesNumber = CncSts.axesNumber & 0x0F;
	
	if (!stassi) return;
	memset (stassi, 0, sizeof (*stassi));
	for (; index < axesNumber; index++, bit <<= 1) {
		if (!(bit & selas)) continue;
		switch (format) {
		case QREALE:
			stassi->quota [index] = AxisSts[index].preal; break;
		case QPROGR:
			stassi->quota [index] = AxisSts[index].pprog; break;
		case QERROR:
			stassi->quota [index] = AxisSts[index].perror; break;
		case DISTAN:
			stassi->quota [index] = AxisSts[index].pdist; break;
		default:
			return;
			break;
		}
	
		if (!AxisSts[index].statusFlags.AOK) stassi->stato[index] |= ASSE_ALL;
		if (AxisSts[index].statusFlags2.LSR) stassi->stato[index] |= ASSE_LIB;
		if (!AxisSts[index].statusFlags.SEE) stassi->stato[index] |= ASSE_NOSET;
		//todo: manca il flag ASSE_JOG
		//if (!AxisSts[index].statusFlags.SEE) stassi->stato[index] |= ASSE_JOG;
	}
}

void __inline lquote_MC( CNPLC_CNCSTATUS CncSts, PCNCPLC_AXIS_STATUS AxisSts, short format, STASSI *stassi, long selas ) {
	STASSI_V3 loc_stassi;
	long index = 0,
		bit = 1;
	UCHAR axesNumber;

	if (!stassi) return;
	axesNumber = CncSts.axesNumber & 0x0F;
	memset (stassi, 0, sizeof (*stassi));
	lquote2_MC (CncSts, AxisSts, format, &loc_stassi, selas);
	for (; index < axesNumber; index++, bit <<= 1) {
		if (!(bit & selas)) continue;
		stassi->quota[index] = (float) loc_stassi.quota[index];
		stassi->stato[index] = loc_stassi.stato[index];
	}
}

short __inline SetMiVel2 (const unsigned short n_asse, const short n_node, const short n_word, const short n_ing) {
	return _SetMiVel2 (n_asse, n_node, n_word, n_ing, &AXCTRL[n_asse]);
}
short __inline SetMiVel3(unsigned short n_asse, LPVOID signal, ULONG format) {
	return _SetMiVel3 (n_asse, signal, format, &AXCTRL[n_asse]);
}
short __inline SetMiVelBit3(unsigned short n_asse, LPVOID signal, UCHAR bit) {
	return _SetMiVelBit3 (n_asse, signal, bit, &AXCTRL[n_asse]);
}
#define SetMiVel(n_asse, n_mor, n_ing)	SetMiVel2 (n_asse, n_mor, (n_ing -1) /(16), (n_ing -1) % (16))

short __inline SetMiVel2_MC (PCNPLC_CNCSTATUS cncstatus, PCNCPLC_AXIS_CTRL axctrl, const unsigned short n_asse, const short n_node, const short n_word, const short n_ing) {
	return _SetMiVel2_MC (cncstatus, &axctrl[n_asse], n_asse, n_node, n_word, n_ing);
}

#define SetMiVel_MC(cncstatus, axctrl, n_asse, n_mor, n_ing)	SetMiVel2_MC (cncstatus, axctrl, n_asse, n_mor, (n_ing -1) /(16), (n_ing -1) % (16))

//sostituiti. Tutti i SetMiVel sono sostiuiti con l'unica routine di cui sotto
SHORT __inline SetMicroHome (USHORT n_asse, RTPLC_BIT micro_value) {
	if (n_asse >= 12) return -1;
	AXCTRL[n_asse].microExtern = RTPLC_TRUE;
	AXCTRL[n_asse].microValue = micro_value;
}

#define overcnc() _overcnc(&CNPLCHANDLE)
#define overcnc_MC(_pCnHandle_)_overcnc(_pCnHandle_)

double	__inline dtg_tondi2( double qp, double qs, unsigned short index) {
	if (index >= ARRAY_SIZE(AXSTATUS)) return 0.;
	return _dtg_tondi2 (qp, qs, AXSTATUS+index);
}

float __inline dtg_tondi (float qp, float qs, unsigned short index) {
	//return (float) _dtg_tondi ((double) qp, (double) qs, index);
}

void __inline qv_normtnd2 (double *i_quota, unsigned short indice) {
	if (indice >= ARRAY_SIZE(AXSTATUS)) return;
	_qv_normtnd2 (i_quota, AXSTATUS+indice);
}

void __inline qv_normtnd (float *i_quota, unsigned short indice) {
	double dquota = (double) *i_quota;
	qv_normtnd2 (&dquota, indice);
	*i_quota = (float) dquota;
}

short int __inline qv_pollici2 (double *i_quota, unsigned short indice) {
	return _qv_pollici2(i_quota, &CNCSTATUS, AXSTATUS+indice);
}

short int __inline qv_pollici (float *i_quota, unsigned short indice) {
	double dquota = (double) *i_quota;
	short ret;
	ret = qv_pollici2 (&dquota, indice);
	*i_quota = (float) dquota;
	return ret;
}

void __inline GetStaPro( STATO_PRO * pstato ) {
	if (pstato) memcpy (pstato, &PROGRAMSTATUS, sizeof (PROGRAMSTATUS));
}

short __inline SendCnc ( short a, short b, char *app) {
	RTPLC_STRING szapp;
	if (NULL != app) {
	szapp.size = strlen (app)+1;
	szapp.sz = app;
	} else {
		szapp.size = 0;
		szapp.sz = NULL;
	}
	return _SendCnc (a, b, &szapp);
}

short __inline SendCnc_MC (PCNPLC_CNCSTATUS cncstatus, short a, short b, char *app) {
	RTPLC_STRING szapp;
	if (NULL != app) {
	szapp.size = _strlen (app)+1;
	szapp.sz = app;
	} else {
		szapp.size = 0;
		szapp.sz = NULL;
	}
	return _SendCnc_MC (cncstatus, a, b, &szapp);
}

#define SerJogMP(_nasse_) _SerJogMP(_nasse_, &CNCCTRL, &CNCSTATUS, &CNPLCHANDLE);
#define SerJogMP_MC(_nasse_, _pCncCtrl_, _pCncSts_, _pCncHandle_) _SerJogMP(_nasse_, _pCncCtrl_, _pCncSts_, _pCncHandle_);

short __inline WaitAx(short axindex) {
	if (axindex >= ARRAY_SIZE(AXSTATUS)) return 0;
	return _WaitAx (&CNCSTATUS, AXSTATUS+axindex);
}

short __inline sendcmd( char *str, unsigned char tasto) {
	RTPLC_STRING s;
	s.size = strlen (str);
	s.sz = str;
	return _sendcmd (&s, tasto);
}

short __inline sendcmd_MC( PCNPLC_CNCSTATUS cncstatus, char *str, unsigned char tasto) {
	RTPLC_STRING s;
	s.size = strlen (str);
	s.sz = str;
	return _sendcmd_MC(cncstatus, &s, tasto);
}

long __inline rampa( short mode, float acc, float *velx, float *velact, long *space) {
	double d_velx, d_velact;
	long ret= _rampa (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE, mode, acc, &d_velx, &d_velact, space, 0);
	*velx = (float) d_velx;
	*velact = (float) d_velact;
	return ret;
}

short __inline ScheCmd(short mod) {
	return _ScheCmd (mod, &CNCCTRL, &CNCSTATUS, AXCTRL, AXSTATUS);
}

void __inline sgavol(void) {
	_sgavol (&CNCCTRL, &CNPLCHANDLE);
}

void __inline schepro(void) {
	_schepro (&CNCSTATUS);
}

void __inline schepro_MC(CNPLC_CNCSTATUS *cncstatus) {
	_schepro (cncstatus);
}

unsigned char __inline overad3(SHORT nodeValue, SHORT numberValue, short maxover, short minover,  short mininc, unsigned char over) {
	return _overad (&CNPLCHANDLE, nodeValue, numberValue, maxover, minover, mininc, over);
}

unsigned char __inline overad2(unsigned short ADNode,  unsigned short ADNumber, short maxover, short mininc, unsigned char over)
{
	return overad3 (ADNode, ADNumber, maxover, 0, mininc, over);
}

unsigned char __inline overad(unsigned short ADNumber, short maxover, short mininc, unsigned char over) {
	return overad3 (0, ADNumber, maxover, 0, mininc, over);
}

//unsigned char __inline overad4_MC(RTPLC_BIT Execute, PCNPLC_CNCSTATUS cncstatus, PCNPLC_CNCCTRL cncctrl, PCNPLC_HANDLE cnplchandle, UCHAR overadCode, SHORT refValue, short maxover, short minover, short mininc) {
//	return _overad_MC(Execute, cncstatus, cncctrl, cnplchandle, overadCode, refValue, maxover, minover, mininc );
//}

unsigned char __inline overad3_MC(PCNPLC_HANDLE cnplchandle, SHORT nodeValue, SHORT numberValue, short maxover, short minover,  short mininc, unsigned char over) {
	return _overad (cnplchandle, nodeValue, numberValue, maxover, minover, mininc, over);
}

BOOL  __inline SerPlanPlc (short *esito) {
	return _SerPlanPlc (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE, esito) ? TRUE : FALSE;
}

BOOL  __inline SerPlanPlc_MC (CNPLC_CNCCTRL *CncCtrl, CNPLC_CNCSTATUS *CncSts, CNPLC_HANDLE *CncHandle, short *esito) {
	return _SerPlanPlc (CncCtrl, CncSts, CncHandle, esito) ? TRUE : FALSE;
}

void __inline gestvol (void) {
	_gestvol (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE);
}

void __inline gestvol_MC (CNPLC_CNCCTRL *CncCtrl, CNPLC_CNCSTATUS *CncSts, CNPLC_HANDLE *CncHandle) {
	_gestvol (CncCtrl, CncSts, CncHandle);
}

void __inline gestjgo(void) {
	_gestjgo (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE);
}

void __inline gestjgo_MC (CNPLC_CNCCTRL *CncCtrl, CNPLC_CNCSTATUS *CncSts, CNPLC_HANDLE *CncHandle){
	_gestjgo (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE);
}

short __inline ZeroAsse(PCNPLC_CNCCTRL cnctrl, PCNPLC_CNCSTATUS cnstatus, PCNPLC_HANDLE cnplchandle, PARZERA * parzera) {
	return _ZeroAsse (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE, parzera);
}

short __inline ZerLin(PCNPLC_CNCCTRL cnctrl, PCNPLC_CNCSTATUS cnstatus, PCNPLC_HANDLE cnplchandle, PARZERA * parzera) {
	return _ZerLin (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE, parzera);
}

short __inline ZerTondo(PCNPLC_CNCCTRL cnctrl, PCNPLC_CNCSTATUS cnstatus, PCNPLC_HANDLE cnplchandle, PARZERA * parzera) {
	return _ZerTondo (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE, parzera);
}

short __inline SelJog(unsigned short  n_asse, short tipjog, long par1 ) {
	return _SelJog (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE, n_asse, tipjog, par1);
}

short __inline SelJog_MC (PCNPLC_CNCCTRL cnctrl, PCNPLC_CNCSTATUS cncstatus, PCNPLC_HANDLE cnplchandle, unsigned short  n_asse, short tipjog, long par1 ) {
	return _SelJog_MC (cnctrl, cncstatus, cnplchandle, n_asse, tipjog, par1);
}

#define read_var(_tipovar_, _numvar_, _offset_, _nasse_, _indvar_) _read_var(_tipovar_, _numvar_, _offset_, _nasse_, _indvar_, sizeof(*_indvar_))
#define write_var(_tipovar_, _numvar_, _offset_, _nasse_, _indvar_) _write_var(_tipovar_, _numvar_, _offset_, _nasse_, _indvar_, sizeof(*_indvar_))

#define read_var_MC(_pCncSts_,_tipovar_, _numvar_, _offset_, _nasse_, _indvar_) _read_var_MC(_pCncSts_,_tipovar_, _numvar_, _offset_, _nasse_, _indvar_, sizeof(*_indvar_))
#define write_var_MC(_pCncSts_,_tipovar_, _numvar_, _offset_, _nasse_, _indvar_) _write_var_MC(_pCncSts_,_tipovar_, _numvar_, _offset_, _nasse_, _indvar_, sizeof(*_indvar_))

short __inline intp (unsigned short numint, short tipo) {
	return _intp(numint, tipo, &CNPLCHANDLE, &CNCSTATUS);
}

BOOL __inline ManageHandwheel (BOOL enable, SHORT axis, SHORT channel, SHORT val, SHORT increment) {
	return _ManageHandwheel (&CNCCTRL, &CNCSTATUS, &CNPLCHANDLE, enable, axis, channel, val, increment);
}



//routines di plcutil
short __inline iniplc(void) {return 0;}
void __inline AggSePlc(long a, long b, long c) {}

//routines che non devono essere presenti, sono quelle che inizializzano la navetta
#define IniVarPlc "IniVarPlc non deve essere definito"
#define LeggiPoint "LeggiPoint non deve essere definito"


//stringhe di appoggio che erano in p_dplc
__DEFINE char AppStrBuffer[80];
#define p_msg0 &AppStrBuffer[0]
#define p_msg1 &AppStrBuffer[41]

#define AXESEL_CH0(_nAxe_) ( (AXEJOGM_CH0) == _nAxe_ ? 1 : 0 )
