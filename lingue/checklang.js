// Costanti usate dalle funzioni
var con = {
	io : {
		forReading: 1,
		forWriting: 2, 
		forAppending: 8,
		tDefault: -2, 
		tTrue: -1, 
		tFalse: 0
	},	
	func : {
		EXIT_SUCCESS: 0,
		EXIT_FAILURE: 1
	}
};

var StdIn = WScript.StdIn,
	StdOut = WScript.StdOut,
	StdErr = WScript.StdErr;

// Riga di comando
var options = {
	inputPath: ".",
	debugMode: false,
	execAction: false,
	fileType: new Array({		
		description: "file di lingua",
		filenameRe: /^MANMESS.MSG$/,
		maxLinesCount: 200,
		maxLineLength: 40,
		lineSyntaxRe: /^\s*[0-9]+\s*;[0-9]+\s+(.*)$/,
		charsetRe: /[^\x20-\x7E]/,
		report: {
			emptyFile: true,
			emptyLine: false,
			emptyText: true,
			lineSyntaxError: true,
			textLengthError: true,
			charsetError: true,
			linesCountError: true
		},
		action: {
			addEndSpace: true
		}
	}, {
		description: "file di contesto",
		filenameRe: /^MANCNTX.MSG$/,
		maxLinesCount: 10,
		maxLineLength: 21,
		lineSyntaxRe: /^(.*)$/,
		charsetRe: /[^\x20-\x7E]/,
		report: {
			emptyFile: true,
			emptyLine: false,
			emptyText: true,
			lineSyntaxError: true,
			textLengthError: true,
			charsetError: true,
			linesCountError: true
		},
		action: {
			addEndSpace: false
		}
	})
};

function printHelp() {
	StdOut.WriteLine("Uso: "+WScript.ScriptName+" [OPZIONE] [PERCORSO]");
	StdOut.WriteLine("Analizza i files MANMESS.MSG e MANCNTX.MSG contenuti in PERCORSO e");
	StdOut.WriteLine("nelle sue sottodirectory ed individua eventuali errori di formato.");
	StdOut.WriteLine("Esempio: "+WScript.ScriptName+" .\\lang");
	StdOut.WriteLine("");
	StdOut.WriteLine("Opzioni:");
	StdOut.WriteLine("-d, --debug       Stampa i messaggi di debug.");
	StdOut.WriteLine("-a, --action      Corregge lunghezza riga e mancanza spazio");
	StdOut.WriteLine("                  finale e sovrascrive il file.");
	StdOut.WriteLine("-h, --help        Visualizza il presente testo d'aiuto.");
	StdOut.WriteLine("");
	StdOut.WriteLine("L'invocazione senza percorso equivale a \".\" (directory corrente)");
}

for (var i = 0; i < WScript.Arguments.length; i++) {
	try {
		switch (WScript.Arguments(i)) {
			case "-d" :
			case "--debug":
				options.debugMode = true;
				break;			
			case "-a":
			case "--action":
				options.execAction = true;
				break;
			case "-h":
			case "--help":
				printHelp();
				WScript.Quit(con.func.EXIT_SUCCESS);
				break;
			default :
				options.inputPath = WScript.Arguments(i);
				break;
		}
	} 
	catch (err) {
		StdErr.WriteLine("Errore durante la lettura dell'argomento dell'opzione "+WScript.Arguments(i)+" alla posizione "+(i+1));
		printHelp();
		WScript.Quit(con.func.EXIT_FAILURE)
	}
}
	
var fso = new ActiveXObject("Scripting.FileSystemObject");

function DebugMsg(msg) {
	if (!options.debugMode) return;
	StdOut.WriteLine(msg);
}

function checkFileConformance(file, opt) {
	DebugMsg(file.Path + " - In verifica come " + opt.description);
	var ts = file.OpenAsTextStream(con.io.forReading, con.io.tFalse);
	var lineNum = 0;
	
	var noError = true;
	var correctedStream = "";
	while (!ts.AtEndOfStream) {
		var line = ts.ReadLine();
		lineNum++;

		if (line.replace(/\s+/gi, "").length == 0) {
			if (opt.report.emptyLine)
				StdErr.WriteLine(file.Path + " - Linea " + lineNum + " - Vuota");
			if (noError && options.execAction)
				correctedStream += "\r\n";
			continue;
		}

		if (lineNum > opt.maxLinesCount) {
			if (opt.report.linesCountError)
				StdErr.WriteLine(file.Path + " - Superato numero massimo di righe consentito (massimo " + opt.maxLinesCount + ")");
			noError = false;
			break;
		}
	  
		// Verifica sul contenuto
		var match = opt.lineSyntaxRe.exec(line);
		if (!match || (match.length < 2)) {
			if (opt.report.lineSyntaxError)
				StdErr.WriteLine(file.Path + " - Linea " + lineNum + " - Sintassi errata");
			noError = false;
		} else if (!match[1] || (match[1].length == 0)) {
			if (opt.report.emptyText)
				StdErr.WriteLine(file.Path + " - Linea " + lineNum + " - Testo assente");
			noError = false;
		} else {
			if (match[1].length > opt.maxLineLength) { // Lunghezza linea
				if (opt.report.textLengthError)
					StdErr.WriteLine(file.Path + " - Linea " + lineNum + " - lunghezza errata (" + match[1].length + " caratteri, massimo " + opt.maxLineLength + ")");
				noError = false;
			}			
			if (opt.charsetRe.test(match[1])) { // Charset
				if (opt.report.charsetError)
					StdErr.WriteLine(file.Path + " - Linea " + lineNum + " - Set di caratteri errato");
				noError = false;
			}
		}

		if (noError && options.execAction) {
			correctedStream += line
			if (opt.action.addEndSpace) {			
				if ((line.charAt(line.length - 1) != " ") && (match[1].length < opt.maxLineLength))
					correctedStream += " ";
			}
			
			correctedStream += "\r\n";					
		}
	}
		
	if (lineNum == 0) {
		if (opt.report.emptyFile)
			StdErr.WriteLine(file.Path + " - File Vuoto");
		noError = false;
	}
	ts.Close();

	if (noError && options.execAction && (correctedStream.length > 0)) {
		ts = file.OpenAsTextStream(con.io.forWriting, con.io.tFalse);
		ts.Write(correctedStream);
		ts.Close();
	}
		

	DebugMsg(file.Path + " - Fine verifica come" + opt.description);
}

(function checkFiles(folder) {
	DebugMsg(folder.Path + " - Inizio enumerazione files");
	var fc = new Enumerator(folder.files);
	for (; !fc.atEnd(); fc.moveNext()) {
		var item = fc.item();
		for (var i = 0; i < options.fileType.length; i++)
			if (options.fileType[i].filenameRe.test(item.Name.toUpperCase())) {
				DebugMsg(item.Path + " - Individuato come " + options.fileType[i].description);
				checkFileConformance(item, options.fileType[i]);
				break;
			}
		if (i == options.fileType.length)
			DebugMsg(item.Path + " - Scartato (nessuna verifica applicata)");
	}

	fc = new Enumerator(folder.SubFolders);
	for (; !fc.atEnd(); fc.moveNext())
		checkFiles(fc.item());

	DebugMsg(folder.Path + " - Fine enumerazione files");
})(fso.GetFolder(options.inputPath));
