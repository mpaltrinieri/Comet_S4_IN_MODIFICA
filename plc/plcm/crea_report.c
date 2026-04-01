/*

        --------------------------------------------------------------
        TITOLO          REPORT
        --------------------------------------------------------------
        --------------------------------------------------------------
        DESCRIZIONE:    EMMEGI COMET S58
        --------------------------------------------------------------
        --------------------------------------------------------------
        CHIAMATA:       void crea_report(void)
        --------------------------------------------------------------
        --------------------------------------------------------------
        RELEASE:        CT6 0.0
        --------------------------------------------------------------
        --------------------------------------------------------------
        DATA:           04-12-2017
        --------------------------------------------------------------
        --------------------------------------------------------------
        AUTORI:         Formuso Daniele
        --------------------------------------------------------------
        --------------------------------------------------------------
        AGGIORNAMENTI:
        --------------------------------------------------------------

*/

#include "all.inc"

#define STATO_FILE_REPT_IDLE        0    // Stato inattivo
#define STATO_FILE_REPT_EXIST       10   // Stato di verifica esistenza del file
#define STATO_FILE_REPT_OPEN        20   // Stato di apertura del file: se non esiste viene creato
#define STATO_FILE_REPT_WRHEAD      30   // Stato di scrittura della riga di testa del file
#define STATO_FILE_REPT_WRTIME      40   // Stato di scrittura della riga data e ora
#define STATO_FILE_REPT_ENDWRITE    50   // Stato di fine scrittura del file 
#define STATO_FILE_REPT_CLOSE       60   // Stato di chiusura del file 
#define STATO_FILE_REPT_ERROR       1000 // Stato di errore


RTPLC_STATUS Esito_REPT_omfileexistsR;
RTPLC_STATUS Esito_REPT_omfileopenR;
RTPLC_STATUS Esito_REPT_omfilewritelineT;
RTPLC_STATUS Esito_REPT_omfilewritelineR;
RTPLC_STATUS Esito_REPT_omfilewritelineF;
RTPLC_STATUS Esito_REPT_omfilecloseR;
RTPLC_STATUS Esito_REPT_omfilecloseERR;

BOOL omfileexistsR_REPT_eseguita;
BOOL omfileopenR_REPT_eseguita;
BOOL omfilewritelineT_REPT_eseguita;
BOOL omfilewritelineR_REPT_eseguita;
BOOL omfilewritelineF_REPT_eseguita;
BOOL omfilecloseR_REPT_eseguita;
BOOL omfilecloseERR_REPT_eseguita;

ULONG handle_fileREPT;			//handle del file

RTPLC_STRING nomefileREPT;
RTPLC_STRING openmode_fileREPT;
RTPLC_STRING testa_fileREPT;
RTPLC_STRING formato_rigaREPT;
RTPLC_STRING riga_fileREPT;
RTPLC_CHARSTRING riga_fileREPT_buffer[255];


RTPLC_BIT file_REPT_exist;
long long APP_highresClk;
int no_reset_highresClk;



void crea_report()
{
	if(PON)
	{
		SCRIVI_FILE_REPORT = 0;
		CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_IDLE;
		APP_highresClk = 0;
		no_reset_highresClk = 0;

		Esito_REPT_omfileexistsR = 0;
		Esito_REPT_omfileopenR = 0;
		Esito_REPT_omfilewritelineT = 0;
		Esito_REPT_omfilewritelineR = 0;
		Esito_REPT_omfilewritelineF = 0;
		Esito_REPT_omfilecloseR = 0;
		Esito_REPT_omfilecloseERR = 0;

		file_REPT_exist = 0;

		omfileexistsR_REPT_eseguita = 0;
		omfileopenR_REPT_eseguita = 0;
		omfilewritelineT_REPT_eseguita = 0;
		omfilewritelineR_REPT_eseguita = 0;
		omfilewritelineF_REPT_eseguita = 0;
		omfilecloseR_REPT_eseguita = 0;
		omfilecloseERR_REPT_eseguita = 0;
	}


	nomefileREPT.sz = "%base%\\REPORT_VAR_R.TXT";
	nomefileREPT.size = strlen(nomefileREPT.sz);

	testa_fileREPT.sz = "Giorno/Mese/Anno;Ore:Minuti:Secondi;Tempo[ms];R01;R02;R03;R04;R05;R06;R07;R08;R09;R10";
	testa_fileREPT.size = strlen(testa_fileREPT.sz);

	riga_fileREPT.size = ARRAY_SIZE(riga_fileREPT_buffer);	// definizione del buffer riga
	riga_fileREPT.sz = riga_fileREPT_buffer;				// setta e istanzia


	if(Mg_MC(253) && AUTO_CICLOMAN) //Condizione che determina la partenza della scrittura del file REPORT
	{
		SCRIVI_FILE_REPORT = 1;
	}

	switch (CASE_WRITE_FILE_REPORT)
	{
	case STATO_FILE_REPT_IDLE:
		if(SCRIVI_FILE_REPORT)
		{
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_EXIST;
		}
		break;
	case STATO_FILE_REPT_EXIST:
		// VERIFICA ESISTENZA FILE REPORT /////////////////////////////////////////////////////////////////////////
		if (!omfileexistsR_REPT_eseguita)		// verifica se file report esiste già
		{
			rtplctrace(1,_T("Scrivi REPORT - esegue omfileexists"));

			Esito_REPT_omfileexistsR = omfileexists( &(nomefileREPT),  &(file_REPT_exist));
			if(Esito_REPT_omfileexistsR > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfileexistsR_REPT_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if (Esito_REPT_omfileexistsR < 0)	
		{
			//Errore in verifica file
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN VERIFICA FILE REPORT  Esito_REPT_omfileexistsR=%d"),Esito_REPT_omfileexistsR);
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_ERROR;
		}
		if(!Esito_REPT_omfileexistsR && !file_REPT_exist && omfileexistsR_REPT_eseguita)
		{
			openmode_fileREPT.size = strlen("a");	    // definisce lunghezza
	        openmode_fileREPT.sz = "a";					// setta e istanzia
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_OPEN; //crea il file e appende alla fine
			omfileexistsR_REPT_eseguita = 0;				// reset flag
		}
		if(!Esito_REPT_omfileexistsR && file_REPT_exist && omfileexistsR_REPT_eseguita)
		{
			openmode_fileREPT.size = strlen("w");	    // definisce lunghezza
	        openmode_fileREPT.sz = "w";				    // setta e istanzia
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_OPEN; //apri il file in scrittura cancellandone il contenuto
			omfileexistsR_REPT_eseguita = 0;				// reset flag
		}	
		break;
	case STATO_FILE_REPT_OPEN:
		// APERTURA FILE REPORT  /////////////////////////////////////////////////////////////////////////
		if (!omfileopenR_REPT_eseguita)	// 
		{
			rtplctrace(1,_T("Apertura File REPORT - esegue omfileopen"));
			nomefileREPT.size = strlen(nomefileREPT.sz);
			Esito_REPT_omfileopenR = omfileopen(&nomefileREPT, &openmode_fileREPT, &handle_fileREPT);
			if(Esito_REPT_omfileopenR > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfileopenR_REPT_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if ( (Esito_REPT_omfileopenR < 0) || (handle_fileREPT == 0) )	
		{
			//Errore in apertura file
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN APERTURA FILE REPORT  Esito_REPT_omfileopenR=%d"),Esito_REPT_omfileopenR);
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN APERTURA FILE REPORT  handle_fileREPT=%d"),handle_fileREPT);
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_ERROR;
		}
		if(!Esito_REPT_omfileopenR && omfileopenR_REPT_eseguita)
		{
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_WRHEAD;
			omfileopenR_REPT_eseguita = 0;				// reset flag
		}
		break;

	case STATO_FILE_REPT_WRHEAD: //scrive riga di testa file REPORT
		// SCRITTURA RIGA TESTA NEL FILE REPORT ////////////////////////////////////////////////////////////////////////
		if ( !omfilewritelineT_REPT_eseguita && (handle_fileREPT != 0) )
		{
			rtplctrace(1,_T("Scrivi REPORT - esegue omfilewritelineT"));
			Esito_REPT_omfilewritelineT = omfilewriteline( handle_fileREPT , &testa_fileREPT );

			if(Esito_REPT_omfilewritelineT > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfilewritelineT_REPT_eseguita = 1;				// anche in caso di esito negativo x errore
			rtplctrace(1,_T("Scrivi REPORT - SCRITTA RIGA TESTA -  testa_fileREPT.sz=%s"),testa_fileREPT.sz);
		}

		if ( (Esito_REPT_omfilewritelineT < 0) || (handle_fileREPT == 0) )	
		{
			//Errore in apertura file
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN SCRITTURA FILE REPORT  Esito_REPT_omfilewritelineT=%d"),Esito_REPT_omfilewritelineT);
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN SCRITTURA FILE REPORT  handle_fileREPT=%d"),handle_fileREPT);
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_ERROR;
		}
		if(!Esito_REPT_omfilewritelineT && omfilewritelineT_REPT_eseguita)
		{
			no_reset_highresClk = 0;
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_WRTIME;
			omfilewritelineT_REPT_eseguita = 0;				// reset flag
		}
		break;

	case STATO_FILE_REPT_WRTIME:     //scrive le righe data, ora e le variabili R

		if ( !omfilewritelineR_REPT_eseguita && (handle_fileREPT != 0) )
		{
			rtplctrace(1,_T("Scrivi REPORT - esegue omfilewritelineR"));
			
			if(!no_reset_highresClk)
			{
				APP_highresClk = highresClk;
				no_reset_highresClk = 1;
			}

			// accoda riga nel file REPORT
			formato_rigaREPT.sz = "%02d/%02d/%02d;%02d:%02d:%02d;%f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f;%.3f";
			formato_rigaREPT.size = strlen(formato_rigaREPT.sz);
			rtplctrace(1, formato_rigaREPT.sz);

			vsrprintf(&riga_fileREPT, &formato_rigaREPT, dateTime.dayInMonth, dateTime.month, dateTime.year,
				dayTime.hour, dayTime.min, dayTime.sec, (highresClk-APP_highresClk)/1000.0,
				R[R_REPORT_01],R[R_REPORT_02],R[R_REPORT_03],R[R_REPORT_04],R[R_REPORT_05],
				R[R_REPORT_06],R[R_REPORT_07],R[R_REPORT_08],R[R_REPORT_09],R[R_REPORT_10]);

			riga_fileREPT.size = strlen(riga_fileREPT.sz); 

			rtplctrace(1, riga_fileREPT.sz, dateTime.dayInMonth, dateTime.month, dateTime.year,
				dayTime.hour, dayTime.min, dayTime.sec, (highresClk-APP_highresClk)/1000.0);

			Esito_REPT_omfilewritelineR = omfilewriteline( handle_fileREPT , &riga_fileREPT);

			if(Esito_REPT_omfilewritelineR > 0) return;		// 1=in corso  0=terminato  <0=errore
			omfilewritelineR_REPT_eseguita = 1;				// anche in caso di esito negativo x errore
			rtplctrace(1,_T("crea_report - SCRITTA RIGA -  riga_fileREPT.sz=%s"),riga_fileREPT.sz);
		}

		if ( (Esito_REPT_omfilewritelineR < 0) || (handle_fileREPT == 0) )	
		{
			//Errore in apertura file
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN SCRITTURA FILE REPORT  Esito_REPT_omfilewritelineR=%d"),Esito_REPT_omfilewritelineR);
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN SCRITTURA FILE REPORT  handle_fileREPT=%d"),handle_fileREPT);
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_ERROR;
			break;
		}
		if(!Esito_REPT_omfilewritelineR && omfilewritelineR_REPT_eseguita)
		{
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_ENDWRITE;
			omfilewritelineR_REPT_eseguita = 0;				// reset flag
		}
    break; 
	
	case STATO_FILE_REPT_ENDWRITE: //Stato di fine scrittura file report
	    if(Mg_MC(254) || RESET_MC)
		{
			Mr_MC(253);
			Mr_MC(254);
			SCRIVI_FILE_REPORT = 0;
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_CLOSE;
		}
		else
		{
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_WRTIME;
		}
		break;

	case STATO_FILE_REPT_CLOSE: //chiusura del file REPORT
		// CHIUSURA FILE REPORT /////////////////////////////////////////////////////////////////////////
		if(handle_fileREPT && !omfilecloseR_REPT_eseguita)	
		{
			rtplctrace(1,_T("Scrivi REPORT - esegue omfileclose"));
			Esito_REPT_omfilecloseR = omfileclose(handle_fileREPT);
			if (Esito_REPT_omfilecloseR > 0) return;		// 1/2=in corso  0=terminato  <0=errore
			omfilecloseR_REPT_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if (Esito_REPT_omfilecloseR < 0)
		{
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN CHIUSURA FILE REPORT  Esito_REPT_omfilecloseR=%d"),Esito_REPT_omfilecloseR);
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN CHIUSURA FILE REPORT  handle_fileREPT=%d"),handle_fileREPT);
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_ERROR;
		}
		if(!Esito_REPT_omfilecloseR && omfilecloseR_REPT_eseguita)
		{
			SCRIVI_FILE_REPORT = 0;		// reset flag abilitaz scrittura file (se l'esecuzione arriva quì, son terminate tutte le 4 fasi)
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_IDLE;
			omfilecloseR_REPT_eseguita = 0;
		}
		break;

	case STATO_FILE_REPT_ERROR:
		//Reset di tutti i flag restituiti dalle funzioni di OMFILE
		if( Esito_REPT_omfileexistsR || Esito_REPT_omfileopenR || Esito_REPT_omfilewritelineT || Esito_REPT_omfilewritelineR ||
			Esito_REPT_omfilewritelineF || Esito_REPT_omfilecloseR || file_REPT_exist)
		{
			Esito_REPT_omfileexistsR = 0;
			Esito_REPT_omfileopenR = 0;
			Esito_REPT_omfilewritelineT = 0;
			Esito_REPT_omfilewritelineR = 0;
			Esito_REPT_omfilewritelineF = 0;
			Esito_REPT_omfilecloseR = 0;

			file_REPT_exist = 0;
		}
        //Reset di tutti i flag delle funzioni OMFILE eseguite
		if(omfileexistsR_REPT_eseguita || omfileopenR_REPT_eseguita || omfilewritelineT_REPT_eseguita || omfilewritelineR_REPT_eseguita ||
		   omfilewritelineF_REPT_eseguita || omfilecloseR_REPT_eseguita)
		{
			omfileexistsR_REPT_eseguita = 0;
			omfileopenR_REPT_eseguita = 0;
			omfilewritelineT_REPT_eseguita = 0;
			omfilewritelineR_REPT_eseguita = 0;
			omfilewritelineF_REPT_eseguita = 0;
			omfilecloseR_REPT_eseguita = 0;
		}
        
		// CHIUSURA FILE REPORT /////////////////////////////////////////////////////////////////////////
		if(handle_fileREPT && !omfilecloseERR_REPT_eseguita)	
		{
			rtplctrace(1,_T("Scrivi REPORT - esegue omfileclose"));
			Esito_REPT_omfilecloseERR = omfileclose(handle_fileREPT);
			if (Esito_REPT_omfilecloseR > 0) return;		// 1/2=in corso  0=terminato  <0=errore
			omfilecloseERR_REPT_eseguita = 1;				// anche in caso di esito negativo x errore
		}

		if (Esito_REPT_omfilecloseERR < 0)
		{
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN CHIUSURA FILE REPORT  Esito_REPT_omfilecloseR=%d"),Esito_REPT_omfilecloseERR);
			rtplctrace(1,_T("Scrivi REPORT - ERRORE IN CHIUSURA FILE REPORT  handle_fileREPT=%d"),handle_fileREPT);
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_ERROR;
		}
		if(!Esito_REPT_omfilecloseERR && omfilecloseERR_REPT_eseguita)
		{
			SCRIVI_FILE_REPORT = 0;		// reset flag abilitaz scrittura file
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_IDLE;
			omfilecloseERR_REPT_eseguita = 0;

		}
		else if(!handle_fileREPT && !omfilecloseERR_REPT_eseguita) //se non vi sono file aperti salta a stato iniziale
		{
			SCRIVI_FILE_REPORT = 0;		// reset flag abilitaz scrittura file
			CASE_WRITE_FILE_REPORT = STATO_FILE_REPT_IDLE;
			omfilecloseERR_REPT_eseguita = 0;
			Mr_MC(253);
			Mr_MC(254);
		}
		break;
	}

}