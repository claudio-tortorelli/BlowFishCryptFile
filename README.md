# BlowFishCryptFile
Gui tool to crypt/decrypt files using BlowFish standard algorithm

CLAUDIOSOFT 2005 - BlowFishFileCrypt
--------------------------------------

Obiettivo:
---------
Ho realizzato una piccola classe che automatizza l'applicazione dell'algoritmo di criptazione BlowFish a stream di file. 

Classi fondamentali:
-----------------
Le classi fondamentali sono:
- BlowFish.h	- algoritmo vero e proprio come è stato scritto da Bruce Schneier
-	BlowFish.cpp - algoritmo vero e proprio come è stato scritto da Bruce Schneier
-	Encryption_i.h - header necessario a BlowFish
-	sbox.h - header necessario a BlowFish
-	BlowFishCryptFile.h - header della classe per l'applicazione ai file
-	BlowFishCryptFile.cpp	- implementazione

Tali classi sono da includere in un proprio progetto. Non sono MFC.

Esempio:
---------
Voglio gestire un file qualsiasi (immagine, audio, testo...). In questo caso "prova.txt" ha il seguente contenuto:

ciao, sono Claudio

Quindi

```
[...]
CString filePath("C:\\prova.txt");
int numKey = 0;
CBlowFishFileCrypt blow(filePath.GetBuffer(0), numKey);
[...]
```

Lo cripto
```
[...]
blow.DoCrypt(FALSE);
[...]
```
Ho impostato bOverWrite = FALSE quindi viene prodotto un nuovo file criptato dal nome prova_enc.txt con il seguente contenuto:
```
Bä;DgÅemœv[©ˆ12â}±×Ø´
```

Lo voglio decriptare. Devo riaprire il file impostando la STESSA chiave di criptazione.
```
[...]
CString filePath2("C:\\prova_enc.txt");
numKey = 0;
CBlowFishFileCrypt blow2(filePath2.GetBuffer(0), numKey);
blow2.DoCrypt(FALSE);
[...]
```
Anche in questo caso non viene sovrascritto il file. Si ottiene il file prova_enc_dec.txt che ritorna a contenere:
ciao, sono Claudio

Note
----
In BlowFishCryptFile.cpp è presente la definizione delle chiavi usate per crittare/decrittare i files. Le ho definite in questo modo (assegnando ad un array statico di char i valori uno ad uno) perchè credo sia un buon metodo per evitare che le chiavi stesse siano rappresentate in chiaro ad un'analisi attenta del codice sorgente binario. E' possibile definire un numero proprio di chiavi aumentando il numero di righe della matrice 'matrixKey'. Il numero di caratteri di ogni riga deve rimanere un multiplo di 8.

Si noti che BlowFish non fallisce in nessun caso: se ad un file criptato con chiave A si applica una decrittazione con chiave B, BlowFish semplicemente produce un altro file illeggibile, perchè la chiave B non impedisce all'algoritmo di funzionare ma non consente la corretta applicazione della funzione di Hash che riordina i byte del file. Per lo stesso motivo la decrittazione di un file non crittato corrisponde ad una crittazione.
	
Appendice: Blowfish, Da Wikipedia, l’enciclopedia libera
---------
In crittologia, Blowfish è un algoritmo a chiave simmetrica a blocchi, ideato nel 1993 da Bruce Schneier e implementato in molti software di crittografia. Sebbene a tutt’oggi non sia reperibile una crittanalisi di Blowfish, questo algoritmo sta suscitando nuovamente interesse se implementato con una maggior
dimensione dei blocchi, come nel caso di AES o Twofish. Schneier progetto Blowfish per essere un algoritmo di utilizzo generale, utile a rimpiazzare l’allora decadente DES, e libero da problemi caratterstici di altri algorimtmi. All’epoca molti altri sistemi di cifratura erano proprietari, coperti da brevetto o da segreti governativi. Schneier dichiaro: Blowfish è libero da brevetti, e rimarr`a tale in tutte le nazioni. L’algoritmo è di pubblico dominio, e può essere usato liberamente da chiunque. Due delle caratteristiche
di rilievo di Blowfish sono S-box dipendenti dalla chiave, e una lista di chiavi estremamente complessa.

Blowfish ha una dimensione blocco a 64bit e una lunghezza di chiave variabile fra i 32 e i 448 bit. Ha una cifratura Feistel a 16 cicli, e usa S-box grandi e dipendenti dalla chiave. Ha una struttura simile al sistema CAST-128, che usa però S-Box fisse. 

Non esistono, o perlomeno non sono conosciute, crittanalisi di Blowfish, almeno fino al 2004, dato che una dimensione di blocco di 64bit è oggi considerata troppo piccola, e codificando più di 232 blocchi si potrebbero rivelare alcuni frammenti del testo originale, a causa del paradosso del compleanno.
Nonostante questo, Blowfish fino ad oggi sembra abbastanza sicuro. Mentre la ridotta dimensione del blocco non crea problemi per applicazioni tradizionali come l’e-mail, potrebbe rendere inutilizzabile Blowfish per la cifratura di testi di grandi dimensioni, come ad esempio in caso di archivi. Nel 1996 Serge Vaudenay escogitò un attacco che permetteva di forzare la cifratura di un testo conoscendo 28r+1 testi in chiaro con la stessa chiave, dove r identifica il numero di cicli (rounds). Inoltre trovò una classe di
chiavi deboli che possono essere identificate e rotte, con lo stesso attacco, conoscendo solo 24r + 1 testi in chiaro. Questo attacco non può essere usato contro il Blowfish implementato con tutti i 16 cicli. Vaudenay utilizzò una variante basata su meno cicli di cifratura. Vincent Rijmen, nella sua tesi di dottorato, introdusse un attacco differenziale di secondo grado in grado di forzare non più di 4 cicli. Non rimane quindi nessuna via conosciuta per forzare un testo codificato con 16 cicli, tranne ovviamente la forza bruta. Nel 2005 Dieter Schmidt studiò la lista delle chiavi di Blowfish e notò che le sottochiavi del terzo e quarto ciclo sono indipendenti dai primi 64 bit della chiave utente.

Blowfish è uno degli alogoritmi di codifica a blocchi più veloci in circolazione, eccetto quando si cambi la chiave. Ogni nuova chiave richiede un tempo di elaborazione equivalente alla codifica di 4Kb di testo, che è molto se confrontato con altri sistemi di cifratura a blocchi. Questo impedisce che venga usato in alcune applicazioni, ma non è un problema in altre. In un caso, è addirittura un vantaggio: il metodo di hashing basato su password utilizzato in OpenBSD usa un algoritmo derivato dal Blowfish che sfrutta la
lentezza di elaborazione delle chiavi; l’idea è che il maggior tempo di calcolo necessario dia protezione da un attacco basato su dizionario. In alcune implementazioni Blowfish usa un’area di memoria molto superiore ai 4Kb teorici di RAM. Questo non è un problema nemmeno per i personal computer più vecchi, ma ne impedisce l’uso in piccoli sistemi integrati come le prime smartcard. Blowfish non è soggetto a nessun brevetto ed `e quindi liberamente utilizzabile da chiunque. Questo ha contribuito alla sua popolarità nei software di crittografia.
