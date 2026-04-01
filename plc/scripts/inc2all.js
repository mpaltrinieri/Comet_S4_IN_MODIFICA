var params = {
    alStartString        : "ALARM_FIRST",
    msStartString        : "MESSAGE_FIRST",
    alEndString          : "ALARM_LAST",
    msEndString          : "MESSAGE_LAST",
    alNumBase            : 19600,
    msNumBase            : 21264,
    msMiBase             : 15500,
    msMoBase             : 15000
};

// Costanti usate dalle funzioni
var sys = {
    debugMode            :  false,
    ioForReading         :  1,
    ioForWriting         :  2,
    ioForAppending       :  8,
    ioTristateUseDefault : -2,
    ioTristateTrue       : -1,
    ioTristateFalse      :  0,
    EXIT_SUCCESS         :  0,
    EXIT_FAILURE         :  1
}

var std = {
    inp : WScript.StdIn,
    out : WScript.StdOut,
    err : WScript.StdErr
};

var version = "1.2.0";
//debugger;

// Estensioni
if (!String.prototype.trim)
  String.prototype.trim = function() { return this.replace(/^\s+|\s+$/g, ''); };

if (!String.prototype.trimLeft)
  String.prototype.trimLeft = function() { return this.replace(/^\s+/g, ''); };

if (!String.prototype.trimRight)
  String.prototype.trimRight = function() { return this.replace(/\s+$/g, ''); };

if (!String.prototype.padLeft)
    String.prototype.padLeft = function(n, c) { return new Array(Math.max(n - this.length + 1, 0)).join(c ? c : ' ') + this };

if (!String.prototype.padRight)
    String.prototype.padRight = function(n, c) { return this + new Array(Math.max(n - this.length, 0)).join(c ? c : ' ') };

if (!Number.prototype.intDiv)
    Number.prototype.intDiv = function(n) { var r = this/n; return (r>0) ? Math.floor(r) : Math.ceil(r); }

if (!Math.trunc)
    Math.trunc = function(n) { return (n>0) ? Math.floor(n) : Math.ceil(n); }

// Oggetto elaborazione allarmi e  messaggi
var alData = {
    alms    : new Array(),
    msgs    : new Array(),

    addData : function (arr, nome, word, bit, alnum, descrizione) {
        var data = new Object();

        data.nome = nome;
        data.word = (word == null) ? Math.floor((alnum - arr.aquireParams.startNum) / 16) : word;
        data.bit = (bit == null) ? Math.floor((alnum - arr.aquireParams.startNum) % 16) : bit;
        data.alnum = (alnum == null) ? arr.aquireParams.startNum + (word - arr.aquireParams.startWord) * 16 + bit : alnum;
        data.desc1 = "";
        data.desc2 = "";

        var descArray = descrizione.replace(data.alnum, "").split(" - ");
        if (descArray.length > 0) {
            data.desc1 = descArray[0].replace(/^\s+|\s+$/g, "");
            descArray.splice(0, 1);
        }
        if (descArray.length > 0)
            data.desc2 = descArray.join(" - ").replace(/^\s+|\s+$/g, "");

        delete descArray;

        arr.maxNameLen = (arr.maxNameLen) ? Math.max(arr.maxNameLen, nome.length) : nome.length;
        arr.push(data);
    },

    addAlm : function(nome, word, bit, alnum, descrizione) {
        if (!this.alms["aquireParams"]) this.alms.aquireParams = {};
        if (this.alms.aquireParams.endWord || this.alms.aquireParams.endNum) return;
        if ((nome == params.alStartString) && (word != null)) {
            this.alms.aquireParams.startWord = word;
            this.alms.aquireParams.startNum = parseInt(descrizione.match(/^\s*(\d+)\s+/)[1]);
            if (sys.debugMode) std.out.WriteLine("startWord: "+this.alms.aquireParams.startWord);
        } else if ((nome == params.alStartString) && (alnum != null)) {
            this.alms.aquireParams.startWord = parseInt(descrizione.match(/^\s*A(\d+)\s+/)[1]);
            this.alms.aquireParams.startNum = alnum;
            if (sys.debugMode) std.out.WriteLine("startNum: "+this.alms.aquireParams.startNum);
        } else if ((nome == params.alEndString) && (word != null)) {
            this.alms.aquireParams.endWord = word;
            this.alms.aquireParams.endNum = parseInt(descrizione.match(/^\s*(\d+)\s+/)[1]);
            if (sys.debugMode) std.out.WriteLine("endWord: "+this.alms.aquireParams.endWord);
        } else if ((nome == params.alEndString) && (alnum != null)) {
            this.alms.aquireParams.endWord = parseInt(descrizione.match(/^\s*A(\d+)\s+/)[1]);
            this.alms.aquireParams.endNum = alnum;
            if (sys.debugMode) std.out.WriteLine("endNum: "+this.alms.aquireParams.endNum);
        } else if (!this.alms.aquireParams.startWord && !this.alms.aquireParams.startNum) {
            return;
        }

        if (!word) word = this.alms.aquireParams.startWord + Math.floor((alnum - this.alms.aquireParams.startNum) / 16);
        if (!bit) bit = (alnum - this.alms.aquireParams.startNum) % 16;
        this.addData(this.alms, nome, word, bit, alnum, descrizione);
    },

    addMsg : function(nome, word, bit, alnum, descrizione) {
        if (!this.msgs["aquireParams"]) this.msgs.aquireParams = {};
        if (this.msgs.aquireParams.endWord || this.msgs.aquireParams.endNum) return;
        if ((nome == params.msStartString) && (word != null)) {
            this.msgs.aquireParams.startWord = word;
            this.msgs.aquireParams.startNum = parseInt(descrizione.match(/^\s*(\d+)\s+/)[1]);
            if (sys.debugMode) std.out.WriteLine("startWord: "+this.msgs.aquireParams.startWord);
        } else if ((nome == params.msStartString) && (alnum != null)) {
            this.msgs.aquireParams.startWord = parseInt(descrizione.match(/^\s*A(\d+)\s+/)[1]);
            this.msgs.aquireParams.startNum = alnum;
            if (sys.debugMode) std.out.WriteLine("startNum: "+this.msgs.aquireParams.startNum);
        } else if ((nome == params.msEndString) && (word != null)) {
            this.msgs.aquireParams.endWord = word;
            this.msgs.aquireParams.endNum = parseInt(descrizione.match(/^\s*(\d+)\s+/)[1]);
            if (sys.debugMode) std.out.WriteLine("endWord: "+this.msgs.aquireParams.endWord);
        } else if ((nome == params.msEndString) && (alnum != null)) {
            this.msgs.aquireParams.endWord = parseInt(descrizione.match(/^\s*A(\d+)\s+/)[1]);
            this.msgs.aquireParams.endNum = alnum;
            if (sys.debugMode) std.out.WriteLine("endNum: "+this.msgs.aquireParams.endNum);
        } else if (!this.msgs.aquireParams.startWord && !this.msgs.aquireParams.startNum) {
            return;
        }

        if (!word) word = this.msgs.aquireParams.startWord + Math.floor((alnum - this.msgs.aquireParams.startNum) / 16);
        if (!bit) bit = (alnum - this.msgs.aquireParams.startNum) % 16;
        this.addData(this.msgs, nome, word, bit, alnum, descrizione);
    },

    sort : function() {
        function sortHelper(a, b) {
            if (a.alnum < b.alnum) return -1;
            if (a.alnum > b.alnum) return 1;
            return 0; // Si potrebbe emettere un messaggio d'errore
        }

        this.alms.sort(sortHelper);
        this.msgs.sort(sortHelper);
    }
};

// Oggetto elaborazione ingressi ed uscite
var ioData = {};

ioData.addData = function (schema, tipo, dimensione, scheda, morsetto, descrizione) {
    for (var i = 0; i < dimensione; i++) {
        var ioObj = {
            schema      : schema,
            tipo        : tipo,
            dimensione  : dimensione,
            scheda      : scheda,
            morsetto    : (morsetto-1)*dimensione + i,
            descrizione : descrizione
        };
        ioObj["nodo"] = ioObj.scheda-1;
        ioObj["word"] = Math.trunc(ioObj.morsetto/16);
        ioObj["bit"]  = Math.trunc(ioObj.morsetto%16);

        if (!this.all) this.all = [];
        this.all.push(ioObj);

        if (!this.data) this.data = {};

        if (!this.data[ioObj.schema])
            this.data[ioObj.schema] = {
                schema: ioObj.schema,
                all: [],
                data: {}
            };

        this.data[ioObj.schema].all.push(ioObj);

        if (!this.data[ioObj.schema].data[ioObj.tipo])
            this.data[ioObj.schema].data[ioObj.tipo] = {
                schema: ioObj.schema,
                tipo: ioObj.tipo,
                all: [],
                data: {}
            };

        this.data[ioObj.schema].data[ioObj.tipo].all.push(ioObj);

        if (!this.data[ioObj.schema].data[ioObj.tipo].data[ioObj.scheda])
            this.data[ioObj.schema].data[ioObj.tipo].data[ioObj.scheda] = {
                schema: ioObj.schema,
                tipo: ioObj.tipo,
                scheda: ioObj.scheda,
                all: [],
                data: {}
            };
        this.data[ioObj.schema].data[ioObj.tipo].data[ioObj.scheda].all.push(ioObj);

        this.data[ioObj.schema].data[ioObj.tipo].data[ioObj.scheda].data[ioObj.morsetto] = ioObj;
    }
};

ioData.sort = function() {
    function sortHelper(a, b) {
        if (a.schema < b.schema) return -1;
        if (a.schema > b.schema) return 1;
        if (a.tipo < b.tipo) return -1;
        if (a.tipo > b.tipo) return 1;
        if (a.scheda < b.scheda) return -1;
        if (a.scheda > b.scheda) return 1;
        // Qui a.scheda == b.scheda
        if (a.morsetto < b.morsetto) return -1;
        if (a.morsetto > b.morsetto) return 1;
        return 0; // Si potrebbe emettere un messaggio d'errore
    }

    if (!this.all) return;
    this.all.sort(sortHelper);
    if (!this.data) return;
    for (var schema in this.data) {
        this.data[schema].all.sort(sortHelper);
        for (var tipo in this.data[schema].data) {
            this.data[schema].data[tipo].all.sort(sortHelper);
            for (var scheda in this.data[schema].data[tipo].data) {
                this.data[schema].data[tipo].data[scheda].all.sort(sortHelper);
            }
        }
    }
};

// Apertura e lettura file d'input
function parse(fileName, parseFunc) {
    var fso = new ActiveXObject("Scripting.FileSystemObject");

    if (!fileName) {
        std.err.WriteLine("File d'input mancante.");
        WScript.Quit(sys.EXIT_FAILURE);
    }

    if (!fso.FileExists(fileName)) {
        std.err.WriteLine("Impossibile trovare il file:\n" + fileName);
        WScript.Quit(sys.EXIT_FAILURE);
    }

    var f = fso.OpenTextFile(fileName, sys.ioForReading, false, sys.ioTristateFalse);
    if (!f) {
        std.err.WriteLine("Impossibile leggere il file:\n" + params.inputFileName);
        WScript.Quit(sys.EXIT_FAILURE);
    } else {
        parseFunc(f.ReadAll());
    }
    f.Close();
}


function parseAlmFile(txt) {
    var re = /\s*#define\s+(\w+)(_AL|_MS)\s+(\d+)(?:\s*\/\*([^\r\n]*)(?=\*\/)\*\/)?(?:\s*\/\*([^\r\n]*)(?=\*\/)\*\/)?(?:\s*\/\*([^\r\n]*)(?=\*\/)\*\/)?/gim
    var result;
    while (result = re.exec(txt)) {
        if (sys.debugMode) {
            std.out.WriteLine(result[0]);
            std.out.WriteLine("\t" + result[1]);
            std.out.WriteLine("\t" + result[2]);
            std.out.WriteLine("\t" + result[3]);
            std.out.WriteLine("\t" + result[4]);
            std.out.WriteLine("\t" + result[5]);
        }

        var nome = result[1].trim();
        var tag = result[2].trim();
        var alnum = parseInt(result[3], 10);
        var descrizione = "";
        if (result[4]) descrizione += result[4].trim();
        if (result[5]) descrizione += " - " + result[5].trim();
        if (result[6]) descrizione += " - " + result[6].trim();

        if (tag == "_AL") {
            alData.addAlm(nome, null, null, alnum, descrizione);
        } else if (tag == "_MS") {
            alData.addMsg(nome, null, null, alnum, descrizione);
        }
    }

    alData.sort();
}


function parseAFile(txt) {
    var re = /^\s*#define\s+(\w+)(_FAL|_FMS)\s+A(\d+)\.bit\._(\d+)\s*(?:\/\*([^\r\n]*)(?=\*\/)\*\/|\/\/([^\r\n]*)|)\s*$/gim;
    var result;
    while (result = re.exec(txt)) {
        if (sys.debugMode) {
            std.out.WriteLine(result[0]);
            std.out.WriteLine("\t" + result[1]);
            std.out.WriteLine("\t" + result[2]);
            std.out.WriteLine("\t" + result[3]);
            std.out.WriteLine("\t" + result[4]);
            std.out.WriteLine("\t" + result[5]);
        }

        var nome = result[1].trim();
        var tag = result[2].trim();
        var word = parseInt(result[3], 10);
        var bit = parseInt(result[4], 10);
        var descrizione = (result[5] ? result[5] : result[6]).trim();

        if (tag == "_FAL") {
            alData.addAlm(nome, word, bit, null, descrizione);
        } else if (tag == "_FMS") {
            alData.addMsg(nome, word, bit, null, descrizione);
    }
    }

    alData.sort();
}


function parseIoFile(txt) {
    var re = /^\s*#define\s+(\w+)\s+M(I|O)_(\d+)_(\d+)\s*(?:\/\*([^\r\n]*)(?=\*\/)\*\/|\/\/([^\r\n]*)|)\s*$/gim;
    var result;
    while (result = re.exec(txt)) {
        if (sys.debugMode) {
            std.out.WriteLine(result[0]);
            std.out.WriteLine("\t" + result[1]);
            std.out.WriteLine("\t" + result[2]);
            std.out.WriteLine("\t" + result[3]);
            std.out.WriteLine("\t" + result[4]);
        }

        ioData.addData(
            "",
            ({"i":"inputs","o":"outputs"})[result[2].toLowerCase()],
            1,
            parseInt(result[3]),
            parseInt(result[4]),
            (result[5] ? result[5] : result[6]).trim()
        );
    }

    ioData.sort();
}


function parseMcFile(txt) {
    var re = /(;).*$|(\w+)\s*=\s*(?:(\w+)|\(([\s\S]*?)\))\s*|(?:\r|\n|\r\n|\n\r)(\.)(?:\r|\n|\r\n|\n\r)/gim;
    var PrevIndex = null;
    var MessageFile = {
        MessageIdTypedef : "",
        SeverityNames    : new Array(),
        FacilityNames    : new Array(),
        LanguageNames    : new Array(),
        OutputBase       : 16,
        Messages         : new Array()
    };
    var CurrentLanguage = "English",
        CurrentSeverity = "Success",
        CurrentMessage = {
            MessageId    : -1,
            Facility     : "Application",
            SymbolicName : "",
            OutputBase   : -1,
            Text         : new Array()
        };

    while (result = re.exec(txt)) {
        if (RegExp.$5 == ".") {
            CurrentMessage.Text[CurrentLanguage.toLowerCase()] =
                txt.substr(PrevIndex, RegExp.index - PrevIndex)
                .replace(/[\r|\n]+(?!\w)/gm, "").replace(/[\r|\n]+/gm, " ");

            continue;
        }

        if (RegExp.$1 == ";")
            continue;

        PrevIndex = RegExp.lastIndex;

        switch (RegExp.$2.toLowerCase()) {
            case "messageidtypedef":
                //MessageFile.MessageIdTypedef = RegExp.$3;
                continue;

            case "severitynames":
                // MessageFile.SeverityNames = ReadSubKeys(RegExp.$4);
                // for (key in MessageFile.SeverityNames)
                    // if (MessageFile.Messages[key] == null)
                        // MessageFile.Messages[key] = new Array();
                continue;

            case "facilitynames":
                //MessageFile.FacilityNames = ReadSubKeys(RegExp.$4);
                continue;

            case "languagenames":
                //MessageFile.LanguageNames = ReadSubKeys(RegExp.$4);
                continue;

            case "outputbase":
                //MessageFile.OutputBase = parseInt(RegExp.$3);
                continue;

            case "messageid":
                var NewMessage = new Message(parseInt(RegExp.$3));

                MessageFile.Messages[CurrentSeverity.toLowerCase()].push(CurrentMessage);
                NewMessage.Facility = CurrentMessage.Facility;
                NewMessage.OutputBase = MessageFile.OutputBase;
                CurrentMessage = NewMessage;
                continue;

            case "severity":
                CurrentSeverity = RegExp.$3;
                continue;

            case "facility":
                CurrentMessage.Facility = RegExp.$3;
                continue;

            case "symbolicname":
                CurrentMessage.SymbolicName = RegExp.$3;
                continue;

            case "outputbase":
                CurrentMessage.OutputBase = parseInt(RegExp.$3);
                continue;

            case "language":
                CurrentLanguage = RegExp.$3;
                CurrentMessage.Text[CurrentLanguage.toLowerCase()] = "";
                continue;
        }

        if (DebugMode != 0) {
            // Nessun match, output dell'espressione sullo standard error
            StdErr.WriteLine("");
            StdErr.WriteLine("$1: <" + RegExp.$1 + ">");
            StdErr.WriteLine("$2: <" + RegExp.$2 + ">");
            StdErr.WriteLine("$3: <" + RegExp.$3 + ">");
            StdErr.WriteLine("$4: <" + RegExp.$4 + ">");
            StdErr.WriteLine("$5: <" + RegExp.$5 + ">");
            StdErr.WriteLine("$6: <" + RegExp.$6 + ">");
            StdErr.WriteLine("$7: <" + RegExp.$7 + ">");
            StdErr.WriteLine("$8: <" + RegExp.$8 + ">");
            StdErr.WriteLine("$9: <" + RegExp.$9 + ">");
            StdErr.WriteLine("right: <" + RegExp.lastIndex  + ">");
        }
    }

    if (CurrentMessage != null)
        MessageFile.Messages[CurrentSeverity.toLowerCase()].push(CurrentMessage);


}


function parseCncFile(txt) {
    var re = /\s*(\d+)\s*=\s*(.+)(?:\r|\n|\r\n|\n\r)|\s*\[(.+)\](?:\r|\n|\r\n|\n\r)|\s*(?:\r|\n|\r\n|\n\r)/gim;
    var result;
    while (result = re.exec(txt)) {
        var rowType = null;
        if (sys.debugMode) {
            std.out.WriteLine(result[0]);
            std.out.WriteLine("\t" + result[1]);
            std.out.WriteLine("\t" + result[2]);
            std.out.WriteLine("\t" + result[3]);
            std.out.WriteLine("\t" + result[4]);
            std.out.WriteLine("\t" + result[5]);
        }

        alnum = result[0].trim();
        if ((alnum == "[ALARM]") || (alnum == "[MSG]")) {
            rowType = alnum;
            continue;
        }

        switch (rowType) {
            case "[ALARM]":
                break;
            case "[MSG]":
                break;
        }
    }
}


function parseGioFile(txt) {
    var re1 = /^\s*#pragma\s+region\b([^\r\n]*)$([\s\S]+?)^\s*#pragma\s+endregion\b[^\r\n]*$/gim;
    var re2 = /^\s*(?:(\w+)\s*=\s*)?M(I|O)_(\d+)(_|W)(\d+)(?:\s*=\s*(\w+))?\s*;\s*(?:[^\/]+)?(?:\/\*([^\r\n]*)(?=\*\/)\*\/|\/\/([^\r\n]*)|)\s*$/gim;
    var result;

    while (result1 = re1.exec(txt)) {
        if (sys.debugMode) {
            std.out.WriteLine(result1[0]);
            std.out.WriteLine("\t" + result1[1]);
            std.out.WriteLine("\t" + result1[2]);
            std.out.WriteLine("\t" + result1[3]);
            std.out.WriteLine("\t" + result1[4]);
            std.out.WriteLine("\t" + result1[5]);
            std.out.WriteLine("\t" + result1[6]);
        }

        while (result2 = re2.exec(result1[2])) {
            if (sys.debugMode) {
                std.out.WriteLine(result2[0]);
                std.out.WriteLine("\t" + result2[1]);
                std.out.WriteLine("\t" + result2[2]);
                std.out.WriteLine("\t" + result2[3]);
                std.out.WriteLine("\t" + result2[4]);
                std.out.WriteLine("\t" + result2[5]);
                std.out.WriteLine("\t" + result2[6]);
            }

            if (result2[4].toLowerCase() == "w")
                debugger;

            ioData.addData(
                result1[1].trim(),
                ({"i":"inputs","o":"outputs"})[result2[2].toLowerCase()],
                ({"_":1,"w":16})[result2[4].toLowerCase()],
                parseInt(result2[3]),
                parseInt(result2[5]),
                (result2[7] ? result2[7] : result2[8]).trim()
            );
        }
    }

    ioData.sort();
}


// Scrittura file d'uscita
function writeAFile(fileName) {
    try {
        var fso = new ActiveXObject("Scripting.FileSystemObject");
        var f = fso.CreateTextFile(fileName, true);
    } catch (e) {
        std.err.WriteLine("Impossibile creare il file " + fileName + "\n");
        WScript.Quit(sys.EXIT_FAILURE);
    }

    function getDateStr() {
        var date = new Date();
        return date.getDate() + "/" + (date.getMonth() + 1) + "/" + date.getFullYear();
    }
    var paddingLen = Math.max(alData.alms.maxNameLen, alData.msgs.maxNameLen);
    paddingLen = Math.floor((paddingLen + 3) / 4) * 4 + 5;

    f.WriteLine("#ifndef A_INC_INCLUDED");
    f.WriteLine("#define A_INC_INCLUDED");
    f.WriteLine("//----------------------------------------------------------------------------");
    f.WriteLine("// TITOLO      : " + fso.GetFileName(fileName));
    f.WriteLine("// AUTORE      : Generato il " + getDateStr() + " da " + WScript.ScriptName);
    f.WriteLine("// DESCRIZIONE : Definizione letterali allarmi e messaggi generati da PLC");
    f.WriteLine("//----------------------------------------------------------------------------");
    f.WriteLine();
    f.WriteLine();
    f.WriteLine("//-- Allarmi macchina --------------------------------------------------------");
    f.WriteLine("//----------------------------------------------------------------------------");
    f.WriteLine("#pragma region Allarmi macchina");
    f.Write("#define "+params.alStartString+"_WORD")
    f.Write(Array(paddingLen - (params.alStartString+"_WORD").length + 1).join(" "))
    f.WriteLine("A"+alData.alms.aquireParams.startWord+".word  // Prima word allarmi");
    f.WriteLine();

    var oldWord = null;
    for (index in alData.alms) {
        if (!alData.alms[index].nome) continue;
        if (oldWord && (alData.alms[index].word != oldWord)) f.WriteLine();
        oldWord = alData.alms[index].word;
        var spaces = Array(paddingLen - alData.alms[index].nome.length + 1).join(" ");
        f.Write("#define "+alData.alms[index].nome+"_FAL"+spaces);
        f.Write("A"+alData.alms[index].word+".bit._"+String(alData.alms[index].bit).padLeft(2, '0'));
        f.Write(" // "+alData.alms[index].alnum+" "+alData.alms[index].desc1);
        f.WriteLine((alData.alms[index].desc2 != "") ? " - " + alData.alms[index].desc2 : "");
    }
    f.WriteLine();
    f.Write("#define "+params.alEndString+"_WORD")
    f.Write(Array(paddingLen - (params.alEndString+"_WORD").length + 1).join(" "))
    f.WriteLine("A"+alData.alms.aquireParams.endWord+".word  // Ultima word allarmi");
    f.WriteLine("#pragma endregion");

    f.WriteLine();
    f.WriteLine();
    f.WriteLine("//-- Messaggi macchina -------------------------------------------------------");
    f.WriteLine("//----------------------------------------------------------------------------");
    f.WriteLine("#pragma region Messaggi macchina");
    f.Write("#define "+params.msStartString+"_WORD")
    f.Write(Array(paddingLen - (params.msStartString+"_WORD").length + 1).join(" "))
    f.WriteLine("A"+alData.msgs.aquireParams.startWord+".word  // Prima word messaggi");
    f.WriteLine();

    oldWord = null;
    for (index in alData.msgs) {
        if (!alData.msgs[index].nome) continue;
        if (oldWord && (alData.msgs[index].word != oldWord)) f.WriteLine();
        oldWord = alData.msgs[index].word;
        var spaces = Array(paddingLen - alData.msgs[index].nome.length + 1).join(" ");
        f.Write("#define "+alData.msgs[index].nome+"_FMS"+spaces);
        f.Write("A"+alData.msgs[index].word+".bit._"+String(alData.msgs[index].bit).padLeft(2, '0'));
        f.Write(" // "+alData.msgs[index].alnum+" "+alData.msgs[index].desc1);
        f.WriteLine((alData.msgs[index].desc2 != "") ? " - " + alData.msgs[index].desc2 : "");
    }
    f.WriteLine();
    f.Write("#define "+params.msEndString+"_WORD")
    f.Write(Array(paddingLen - (params.msEndString+"_WORD").length + 1).join(" "))
    f.WriteLine("A"+alData.msgs.aquireParams.endWord+".word  // Ultima word messaggi");
    f.WriteLine("#pragma endregion");

    f.WriteLine();
    f.WriteLine("#endif // A_INC_INCLUDED");
    f.Close();
}


function writeAlmFile(fileName, cvt) {
    try {
        var fso = new ActiveXObject("Scripting.FileSystemObject");
        var f = fso.CreateTextFile(fileName, true);
    } catch (e) {
        std.err.WriteLine("Impossibile creare il file " + fileName + "\n");
        WScript.Quit(sys.EXIT_FAILURE);
    }

    function getDateStr() {
        var date = new Date();
        return date.getDate() + "/" + (date.getMonth() + 1) + "/" + date.getFullYear();
    }
    var paddingLen = Math.max(alData.alms.maxNameLen, alData.msgs.maxNameLen);
    paddingLen = Math.floor((paddingLen + 3) / 4) * 4 + 5;

    if (!cvt) f.WriteLine("#ifndef ALARMU_INC_INCLUDED");
    if (!cvt) f.WriteLine("#define ALARMU_INC_INCLUDED");
    f.WriteLine("//----------------------------------------------------------------------------");
    f.WriteLine("// TITOLO      : " + fso.GetFileName(fileName));
    f.WriteLine("// AUTORE      : Generato il " + getDateStr() + " da " + WScript.ScriptName);
    f.WriteLine("// DESCRIZIONE : Definizione letterali allarmi e messaggi generati da PLC");
    f.WriteLine("//----------------------------------------------------------------------------");
    f.WriteLine();
    f.WriteLine();
    f.WriteLine("//-- Allarmi macchina --------------------------------------------------------");
    f.WriteLine("//----------------------------------------------------------------------------");

    for (index in alData.alms) {
        if (!alData.alms[index].nome) continue;
        var spaces = Array(paddingLen - alData.alms[index].nome.length + 1).join(" ");
        f.WriteLine("#define "+alData.alms[index].nome+"_AL"+spaces+alData.alms[index].alnum+" /*"+alData.alms[index].desc1+"*/");
        if (alData.alms[index].desc2 != "") f.WriteLine("/*" + alData.alms[index].desc2 + "*/");
        f.WriteLine();
    }

    f.WriteLine();
    f.WriteLine();
    f.WriteLine("//-- Messaggi macchina -------------------------------------------------------");
    f.WriteLine("//----------------------------------------------------------------------------");

    for (index in alData.msgs) {
        if (!alData.msgs[index].nome) continue;
        var spaces = Array(paddingLen - alData.msgs[index].nome.length + 1).join(" ");
        f.WriteLine("#define "+alData.msgs[index].nome+"_MS"+spaces+alData.msgs[index].alnum+" /*"+alData.msgs[index].desc1+"*/");
        if (alData.msgs[index].desc2 != "") f.WriteLine("/*" + alData.msgs[index].desc2 + "*/");
        f.WriteLine();
    }

    if (!cvt) f.WriteLine("#endif // ALARMU_INC_INCLUDED");
    f.Close();
}


function writeMcFile(fileName) {
    try {
        var fso = new ActiveXObject("Scripting.FileSystemObject");
        var f = fso.CreateTextFile(fileName, true);
    } catch (e) {
        std.err.WriteLine("Impossibile creare il file " + fileName + "\n");
        WScript.Quit(sys.EXIT_FAILURE);
    }

    f.WriteLine(";#ifndef MESSAGES_H_INCLUDED");
    f.WriteLine(";#define MESSAGES_H_INCLUDED");
    f.WriteLine(";//*******************************************************************");
    f.WriteLine(";//");
    f.WriteLine(";// TITOLO:      " + fso.GetFileName(fileName));
    f.WriteLine(";//");
    f.WriteLine(";// DATA:        " + (new Date()).toLocaleDateString());
    f.WriteLine(";//");
    f.WriteLine(";// DESCRIZIONE: Generato automaticamente da " + WScript.ScriptName);
    f.WriteLine(";//");
    f.WriteLine(";//*******************************************************************");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//  NOTE: comments in the .mc file must use both ; and //.           ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//  Status values are 32 bit values layed out as follows:            ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1                     ");
    f.WriteLine(";//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 ");
    f.WriteLine(";//  +---+-+-------------------------+-------------------------------+");
    f.WriteLine(";//  |Sev|C|       Facility          |               Code            |");
    f.WriteLine(";//  +---+-+-------------------------+-------------------------------+");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//  where                                                            ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//      Sev - is the severity code                                   ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//          00 - Success                                             ");
    f.WriteLine(";//          01 - Informational                                       ");
    f.WriteLine(";//          10 - Warning                                             ");
    f.WriteLine(";//          11 - Error                                               ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//      C - is the Customer code flag                                ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//      Facility - is the facility code                              ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//      Code - is the facility's status code                         ");
    f.WriteLine(";//                                                                   ");
    f.WriteLine(";//*******************************************************************");
    f.WriteLine(";                                                                     ");

    f.WriteLine("MessageIdTypedef=DWORD");
    f.WriteLine();
    f.WriteLine("SeverityNames = (");
    f.WriteLine("    Success       = 0x0:STATUS_SEVERITY_SUCCESS");
    f.WriteLine("    Informational = 0x1:STATUS_SEVERITY_INFORMATIONAL");
    f.WriteLine("    Warning       = 0x2:STATUS_SEVERITY_WARNING");
    f.WriteLine("    Error         = 0x3:STATUS_SEVERITY_ERROR");
    f.WriteLine(")");
    f.WriteLine();
    f.WriteLine("LanguageNames = (");
    f.WriteLine("    Italian = 0x0410:it");
    f.WriteLine("    English = 0x0409:en");
    f.WriteLine(")");
    f.WriteLine();
    f.WriteLine("FacilityNames = (");
    f.WriteLine("    System = 0x0");
    f.WriteLine("    Plc    = 0x120:FACILITY_PLC");
    f.WriteLine(")");

    f.WriteLine();
    f.WriteLine();
    f.WriteLine(";//-- Allarmi macchina --------------------------------------------------------");
    f.WriteLine(";//----------------------------------------------------------------------------");
    var lastIdx = null;
    for (index in alData.alms) {
        if (!alData.alms[index].nome) continue;
        if (lastIdx && (alData.alms[index].alnum == alData.alms[lastIdx].alnum)) {
            f.WriteLine(";#define "+alData.alms[index].nome+"_AL    "+alData.alms[lastIdx].nome+"_AL");
            f.WriteLine(";");
            continue;
        }
        f.WriteLine("MessageId="+alData.alms[index].alnum+" Facility=Plc Severity=Error SymbolicName="+alData.alms[index].nome+"_AL");

        f.WriteLine("Language=Italian");
        if (alData.alms[index].desc2 != "")
            f.WriteLine(alData.alms[index].desc1 + " - " + alData.alms[index].desc2);
        else
            f.WriteLine(alData.alms[index].desc1);
        f.WriteLine(".");

        f.WriteLine();

        f.WriteLine("Language=English");
        if (alData.alms[index].desc2 != "")
            f.WriteLine(alData.alms[index].desc1 + " - " + alData.alms[index].desc2);
        else
            f.WriteLine(alData.alms[index].desc1);
        f.WriteLine(".");

        f.WriteLine();
        lastIdx = index;
    }

    f.WriteLine();
    f.WriteLine();
    f.WriteLine(";//-- Messaggi macchina -------------------------------------------------------");
    f.WriteLine(";//----------------------------------------------------------------------------");
    lastidx = null;
    for (index in alData.msgs) {
        if (!alData.alms[index].nome) continue;
        if (lastIdx && (alData.alms[index].alnum == alData.alms[lastIdx].alnum)) {
            f.WriteLine(";#define "+alData.alms[index].nome+"_MS    "+alData.alms[lastIdx].nome+"_MS");
            f.WriteLine(";");
            continue;
        }
        f.WriteLine("MessageId="+alData.msgs[index].alnum+" Facility=Plc Severity=Warning SymbolicName="+alData.msgs[index].nome+"_MS");

        f.WriteLine("Language=Italian");
        if (alData.msgs[index].desc2 != "")
            f.WriteLine(alData.msgs[index].desc1 + " - " + alData.msgs[index].desc2);
        else
            f.WriteLine(alData.msgs[index].desc1);
        f.WriteLine(".");

        f.WriteLine();

        f.WriteLine("Language=English");
        if (alData.msgs[index].desc2 != "")
            f.WriteLine(alData.msgs[index].desc1 + " - " + alData.msgs[index].desc2);
        else
            f.WriteLine(alData.msgs[index].desc1);
        f.WriteLine(".");

        f.WriteLine();
        lastIdx = index;
    }
    f.WriteLine(";#endif // MESSAGES_H_INCLUDED");
    f.Close();
}


function writeCncFile(fileName) {
    try {
        var fso = new ActiveXObject("Scripting.FileSystemObject");
        var f = fso.CreateTextFile(fileName, true);
    } catch (e) {
        WScript.Echo("Impossibile creare il file" + fileName + "\n");
        WScript.Quit(sys.EXIT_FAILURE);
    }

    f.WriteLine("[ALARM]");
    for (var index = 1; index < (alData.alms.length - 1); index++) {
        if (!alData.alms[index].nome) continue;
        f.WriteLine((alData.alms[index].alnum - alData.alms[0].alnum)+"="+alData.alms[index].desc1+" - "+ alData.alms[index].desc2);
    }

    f.WriteLine();
    f.WriteLine("[MSG]");
    for (var index = 1; index < (alData.msgs.length - 1); index++) {
        if (!alData.msgs[index].nome) continue;
        f.WriteLine((alData.msgs[index].alnum - alData.msgs[0].alnum)+"="+alData.msgs[index].desc1+" - "+alData.msgs[index].desc2);
    }

    f.Close();
}


function writeIoSynFile(fileName, data) {
    try {
        var fso = new ActiveXObject("Scripting.FileSystemObject");
        fileName = fso.GetAbsolutePathName(fileName)
        if (data.schema) {
            var folder = fso.GetParentFolderName(fileName);
            var base = fso.GetBaseName(fileName);
            var ext = fso.GetExtensionName(fileName);
            fileName = fso.BuildPath(folder, base + "_" + data.schema + (ext ? "." + ext : ""));
        }
        var f = fso.CreateTextFile(fileName, true);
    } catch (e) {
        WScript.Echo("Impossibile creare il file:\n" + OutputFileName);
        WScript.Quit(EXIT_FAILURE);
    }

    function padIo(n) { if (n < 10) return "0" + n.toString(); else return n.toString(); }

    if (data.data["inputs"]) {
        var rscIndex = params.msMiBase;
        f.WriteLine("#define\t\tMS_INGRESSI_F\t"+rscIndex+"\t/*INIZIO DESCRIZIONE INGRESSI*/");
        for (index = 0; index < data.data["inputs"].all.length; index++) {
            var d = data.data["inputs"].all[index];
            rscIndex++;
            f.WriteLine(
                  "#define"
                + "\t\tMS_MI_" + d.scheda + "_" + padIo(d.morsetto+1)
                + "\t\t\t" + rscIndex
                + "\t/*" + d.scheda + "_" + (d.morsetto+1)
                + " - " + d.descrizione + "*/");
        }
    }

    if (data.data["outputs"]) {
        f.WriteLine()
        rscIndex = params.msMoBase;
        f.WriteLine("#define\t\tMS_USCITE_F\t\t"+rscIndex+"\t/*INIZIO DESCRIZIONE USCITE*/");
        for (index = 0; index < data.data["outputs"].all.length; index++) {
            var d = data.data["outputs"].all[index];
            rscIndex++;
            f.WriteLine(
                  "#define"
                + "\t\tMS_MO_" + d.scheda + "_" + padIo(d.morsetto+1)
                + "\t\t\t" + rscIndex
                + "\t/*" + d.scheda + "_" + (d.morsetto+1)
                + " - " + d.descrizione + "*/");
        }
    }

    f.Close();
}


function writeIoXmlSynFile(fileName, data) {
    try {
        var fso = new ActiveXObject("Scripting.FileSystemObject");
        fileName = fso.GetAbsolutePathName(fileName)
        if (data.schema) {
            var folder = fso.GetParentFolderName(fileName);
            var base = fso.GetBaseName(fileName);
            var ext = fso.GetExtensionName(fileName);
            fileName = fso.BuildPath(folder, base + "_" + data.schema + (ext ? "." + ext : ""));
        }
        //var f = fso.CreateTextFile(fileName, true);
    } catch (e) {
        WScript.Echo("Impossibile creare il file:\n" + OutputFileName);
        WScript.Quit(EXIT_FAILURE);
    }

    function addNode(xmlo, parentNode, type, id, word, bit, desc) {
        function addChild(xmlo, parentNode, name, txt) {
            var ele = xmlo.createElement(name);
            ele.appendChild(xmlo.createTextNode(txt));
            parentNode.appendChild(ele);
        }

        var node = xmlo.createElement("Node");
        addChild(xmlo, node, "Type", type);
        addChild(xmlo, node, "IdNode", id);
        addChild(xmlo, node, "Word", word);
        addChild(xmlo, node, "Bit", bit);
        addChild(xmlo, node, "Description", desc);

        parentNode.appendChild(node);
        return node;
    }

    var xmlDoc = new ActiveXObject("MSXML2.DOMDocument");
    xmlDoc.async = false;
    xmlDoc.loadXML("<Nodes></Nodes>");

    var root = xmlDoc.documentElement;
    var nodes = xmlDoc.selectSingleNode("//Nodes");

    if (data.data["inputs"]) {
        for (index = 0; index < data.data["inputs"].all.length; index++) {
            var d = data.data["inputs"].all[index];
            addNode(xmlDoc, nodes, "DI", d.nodo, d.word, d.bit, d.descrizione);
        }
    }

    if (data.data["outputs"]) {
        for (index = 0; index < data.data["outputs"].all.length; index++) {
            var d = data.data["outputs"].all[index];
            addNode(xmlDoc, nodes, "DO", d.nodo, d.word, d.bit, d.descrizione);
        }
    }

    var adoStm = new ActiveXObject("ADODB.Stream");
    adoStm.CharSet = "utf-8"
    adoStm.Type = 1; // binary
    adoStm.Open();

    var xmlw = new ActiveXObject("MSXML2.MXXMLWriter");
    xmlw.byteOrderMark = true;
    xmlw.omitXMLDeclaration = false;
    xmlw.version = "1.0";
    xmlw.encoding = "utf-8";
    xmlw.standalone = true;
    xmlw.disableOutputEscaping = false;
    xmlw.indent = true;
    xmlw.output = adoStm;

    var xmlr = new ActiveXObject("MSXML2.SAXXMLReader");
    xmlr.contentHandler = xmlw;
    xmlr.putProperty("http://xml.org/sax/properties/lexical-handler", xmlw);
    xmlr.putProperty("http://xml.org/sax/properties/declaration-handler", xmlw);
    xmlr.parse(xmlDoc);

    adoStm.SaveToFile(fileName, 2); // overwrite
    adoStm.Close();
}

// Decodifica riga di comando
for (var i = 0; i < WScript.Arguments.length; i++) {
    try {
        switch (WScript.Arguments(i)) {
            // Filtri d'ingresso
            case "-ia" : // File di input tipo a.inc
                parse(WScript.Arguments(++i), parseAFile);
                break;
            case "-iio": // File di input tipo io.inc
                parse(WScript.Arguments(++i), parseIoFile);
            break;
            case "-ialm" : // File di input tipo alarmu.inc
                parse(WScript.Arguments(++i), parseAlmFile);
                break;
            case "-imc": // File di input tipo resdll.rc
                parse(WScript.Arguments(++i), parseMcFile);
            break;
            case "-icnc": // File di input tipo cnc.msg
                parse(WScript.Arguments(++i), parseCncFile);
            case "-igio": // File di input tipo getin / setout
                parse(WScript.Arguments(++i), parseGioFile);
            break;

            // Filtri d'uscita
            case "-oa" : // File testuale allarmi in formato a.inc
                writeAFile(WScript.Arguments(++i));
                break;
            case "-oalm" : // File testuale allarmi in formato "alarmu.inc"
                writeAlmFile(WScript.Arguments(++i), false);
                break;
            case "-oalmcvt" : // File testuale allarmi in formato "alarmu.inc" compatibile con alarmcvt
                writeAlmFile(WScript.Arguments(++i), true);
                break;
            case "-omc" : // File testuale allarmi in formato "resdll.mc"
                writeMcFile(WScript.Arguments(++i));
                break;
            case "-ocnc" : // File testuale in formato cnc.msg
                writeCncFile(WScript.Arguments(++i));
                break;
            case "-oio" : // File testuale sinonimi I/O
                writeIoSynFile(WScript.Arguments(++i), ioData.data[""]);
                break;
            case "-omio" : { // File testuali multipli sinonimi I/O
                var fileName = WScript.Arguments(++i);
                for (var schema in ioData.data)
                    writeIoSynFile(fileName, ioData.data[schema]);
                }
                break;
            case "-oioxml":  // File testuale sinonimi I/O in formato XML
                writeIoXmlSynFile(WScript.Arguments(++i), ioData.data[""]);
                break;
            case "-omioxml": { // File testuali multipli sinonimi I/O in formato XML
                var fileName = WScript.Arguments(++i);
                for (var schema in ioData.data)
                    writeIoXmlSynFile(fileName, ioData.data[schema]);
                }
                break;
            // Modificatori
            case "-mi" : // Codice del primo ingresso (se non trovato)
                params.msMiBase = parseInt(WScript.Arguments(++i));
                break;
            case "-mo" : // Codice della prima uscita (se non trovata)
                params.msMoBase = parseInt(WScript.Arguments(++i));
                break;
            case "-mal" : // Codice del primo allarme (se non trovato)
                params.alNumBase = parseInt(WScript.Arguments(++i));
                break;
            case "-mms" : // Codice del primo messaggio (se non trovato)
                params.msNumBase = parseInt(WScript.Arguments(++i));
                break;
            default: // Opzione non riconosciuta
                std.err.WriteLine("Scartata opzione: " + WScript.Arguments(i));
                break;
        }
    }
    catch (err) {
        std.err.WriteLine("Errore durante la lettura dell'argomento dell'opzione "+WScript.Arguments(i)+" alla posizione "+(i+1));
        WScript.Quit(sys.EXIT_FAILURE)
    }
}


WScript.Quit(sys.EXIT_SUCCESS);
