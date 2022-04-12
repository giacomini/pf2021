<!-- omit in toc -->
# Progetto d'esame

- [Introduzione](#introduzione)
- [Consegna](#consegna)
- [Valutazione](#valutazione)

## Introduzione

Il progetto d'esame consiste nell'implementazione di uno o più programmi in C++, accompagnati da una breve relazione di
presentazione.

I temi possibili oggetto del progetto sono due:

- [Simulazione dell'evoluzione di una pandemia](epidemia.md)
- [Simulazione del comportamento di stormi](boids.md)

## Consegna

Il progetto può essere svolto in gruppo, fino a un massimo di quattro persone.

Il programma deve essere scritto in C++ standard, seguendo le indicazioni e le
raccomandazioni fornite a lezione nel corso dell'anno. E' ammesso l'uso di
librerie esterne (ad esempio per la grafica), ma queste devono essere
disponibili sulla piattaforma di riferimento (Ubuntu 20.04, con il compilatore
gcc v. 9.3).

Ogni programma deve essere costituito da **almeno due** *translation unit*.
Indicativamente la logica del programma va suddivisa tra uno o più header file
(`.hpp`) e tra uno o più file di implementazione (`.cpp`); la funzionalità va
poi richiamata da un ulteriore file contenente il `main`.

La compilazione e l'esecuzione non devono generare messaggi diagnostici
compilando il codice con le opzioni `-Wall -Wextra -fsanitize=address`.

Il codice deve essere formattato adeguatamente (con `clang-format` o tool
equivalente). Il file di configurazione del tool di formattazione (ad es.
`.clang-format`) deve essere consegnato insieme al programma.

Ci si attende che nomi di file, funzioni, tipi, variabili, ecc. siano
descrittivi e che si seguano convenzioni uniformi. I nomi di file e directory
non devono contenere spazi.

E' fortemente raccomandata la scrittura di unit test, usando *Doctest* o altro
strumento analogo.

La consegna avverrà su virtuale.unibo.it tramite un file archivio `.zip` o
`.tgz`. Ogni studente/studentessa deve inviare l'archivio, anche se il lavoro è
svolto in gruppo. La consegna va fatta ogni volta che ci si iscrive per un appello,
indipendentemente dal fatto che nel frattempo siano intercorse modifiche al codice.

L'archivio deve contenere:

- il codice sorgente e tutte le risorse necessarie all'esecuzione (ad esempio
  eventuali immagini e font)
- una breve relazione di accompagnamento

Il file **non** dovrà contenere:

- eseguibili/binari ottenuti compilando il sorgente
- directory quali `__MACOSX` o simili

Prima di creare l'archivio, verificate il contenuto e fate pulizia di tutto
quanto non va consegnato.

Supponendo che tutto il codice e la relazione si trovino in una cartella `progetto`,
per creare un archivio `zip`

```shell
$ ls
progetto
$ zip -r progetto.zip progetto
$ ls
progetto progetto.zip
```

Per creare un archivio `tgz`

```shell
$ ls
progetto
$ tar zcf progetto.tgz progetto
$ ls
progetto progetto.tgz
```

Prima di produrre l'archivio sincerarsi che la directory contenga la relazione.

La relazione di accompagnamento rappresenta una guida alla comprensione del
codice e alla valutazione del lavoro nel suo complesso. Indicativamente deve
contenere:

- autore o autori del lavoro

- descrizione delle principali scelte progettuali e implementative

- istruzioni su come compilare, testare, eseguire

- descrizione del formato di input e di output, possibilmente con degli esempi

- interpretazione dei risultati ottenuti

- strategia di test per verificare che quanto ottenuto sia ragionevolmente
  esente da errori

- ogni altra informazione utile agli obiettivi sopra citati

La relazione deve essere in formato `pdf` o *markdown* (il formato con cui è
composto questo testo). Per un risultato tipografico eccellente si suggerisce di
provare LaTeX, o sul proprio PC o su strumenti online, ad es.
[overleaf](https://overleaf.com). Se si usano altri sistemi (ad es. MS Word o
LibreOffice), ricordarsi di esportare in formato `pdf`.

Pur non essendo necessari, saranno valutati positivamente l'uso di *CMake* per
la compilazione, l'uso di *Git* come strumento collaborativo e l'adozione di
ogni altro strumento utile al miglioramento del software prodotto. Per *CMake*
in particolare, gli esempi disponibili in questa repository dovrebbero essere
sufficienti per le esigenze di questo progetto.

Se lo sviluppo avviene in una repository *Git*, potete indicarne l'indirizzo
nella relazione; se la repository è privata ed è tenuta su
[GitHub](https://github.com/), potete condividerla con noi aggiungendo gli account `giacomini`, `battibass` e `rsreds` tra i membri del progetto. Naturalmente questo
non sostituisce la consegna secondo le modalità indicate sopra.

## Valutazione

La valutazione si basa su cinque criteri:

- La **qualità della relazione** intende valutare la capacità della relazione di
  accompagnare il lettore nella comprensione del programma, nelle varie scelte
  di design, di implementazione, di ricerca della correttezza. Si tiene inoltre
  in conto la correttezza lessicale e grammaticale, nonché l'uso corretto della
  lingua italiana.

- La **qualità del design** del programma intende valutare quanto il design
  dell'applicazione è appropriato per risolvere il problema proposto. Elementi
  considerati sono, a titolo esemplificativo, la suddivisione del codice in
  classi e funzioni, la loro progettazione e il loro uso secondo le indicazioni
  date a lezione, la suddivisione eventuale del codice in più file sorgente, il
  riuso di componenti terzi, in particolare della standard library.

- La **qualità dell'implementazione** del programma intende valutare l'applicazione
  corretta dei costrutti del linguaggio C++ nell'implementazione del programma
  secondo le convenzioni consolidate e proposte a lezione. Verranno anche
  considerati, ad esempio, la corretta formattazione del codice e l'utilizzo di
  nomi significativi per denotare le entità rappresentate nel codice.

- La **correttezza del programma** intende valutare quanto il comportamento del
  programma in esecuzione sia aderente a quanto specificato nella consegna e,
  per quel che riguarda aspetti non specificati o eventuali varianti, nella
  relazione. Verranno anche considerate le strategie e le tecniche utilizzate
  per verificare che il programma si comporti correttamente.

- L'**originalità della soluzione** intende valutare innanzitutto il rispetto della
  consegna, almeno nella sua opzione di base. Un giudizio oltre la sufficienza
  dipende dall'esplorazione di altre opzioni e varianti ovvero dall'utilizzo di
  strumenti, librerie, tecniche aggiuntivi.

Ogni criterio sarà valutato secondo la scala: *insufficiente*, *sufficiente*,
*buono*, *ottimo*. Indipendentemente dalla valutazione complessiva ottenuta, la
sufficienza si intende acquisita solo se la valutazione di ogni singolo criterio
è almeno sufficiente.
