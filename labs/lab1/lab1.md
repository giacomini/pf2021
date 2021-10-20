# Lab 1

Gli obiettivi di questo laboratorio sono:
- prendere confidenza con VSCode e la compilazione dei programmi con `g++`;
- apprendere come utilizzare _clang-format_ per gestire la formattazione del 
  codice;
- impratichirsi con alcuni concetti di base della programmazione (variabili, 
  cicli, input/output da terminale);
- (opzionale) iniziare a familiarizzare con alcune librerie del C++ (es. quella 
  che include le funzioni trigonometriche).

Allo scopo, verranno sviluppati due semplici programmi:
- il primo calcola &pi; in maniera approssimata avvalendosi di un integrale;
- il secondo _simula_ il moto parabolico di un proiettile.

---

- [Lab 1](#lab-1)
  - [Area di lavoro](#area-di-lavoro)
  - [Primi passi](#primi-passi)
  - [Esercizio 1.: calcolo di &pi;](#esercizio-1-calcolo-di-π)
    - [Immissione delle condizioni iniziali](#immissione-delle-condizioni-iniziali)
    - [Calcolo approssimato dell'integrale](#calcolo-approssimato-dellintegrale)
    - [Stampa a schermo e verifica dei risultati](#stampa-a-schermo-e-verifica-dei-risultati)
  - [Esercizio 2.: Moto parabolico](#esercizio-2-moto-parabolico)
    - [Immissione delle condizioni iniziali](#immissione-delle-condizioni-iniziali-1)
    - [Elaborazione dei parametri immessi](#elaborazione-dei-parametri-immessi)
    - [Simulazione e campionamento del moto](#simulazione-e-campionamento-del-moto)
    - [Stampa a schermo e verifica dei risultati](#stampa-a-schermo-e-verifica-dei-risultati-1)
  - [Esempi di soluzioni](#esempi-di-soluzioni)
  - [Consegna del lavoro svolto](#consegna-del-lavoro-svolto)
  - [Bonus](#bonus)

---


## Area di lavoro

Qualora non si sia già provveduto a farlo, suggeriamo di creare una directory (cartella) di lavoro 
(diversa da quella di un eventuale download locale del 
[repository GitHub del corso](https://github.com/giacomini/pf2021)) dove mantenere i programmi 
sviluppati durante i laboratori e lo svolgimento degli esercizi. Salvo casi particolari, suggeriamo 
creare sottocartelle separate per ciascuno di essi.

Creiamo quindi una struttura di directory, che ospiterà tutti i file del nostro progetto. 
La directory del primo laboratorio `lab1/` inizialmente risulterà vuota.

```bash
$ pwd
/home/carlo
$ mkdir -p pf2021_labs/lab1
$ cd pf2021_labs/lab1
$ ls -al
total 0
drwxr-xr-x  2 carlo  staff  64 17 Ott 18:09 .
drwxr-xr-x  3 carlo  staff  96 17 Ott 18:09 ..
```

> __NOTA:__ la scelta della strutture del nome della directory `pf2021_labs` è totalmente 
> arbitraria, scegliere liberamente un nome diverso in base alle proprie preferenze.

> __NOTA:__ è possibile controllare, tramite l'uso di `man`, il significato dell'opzione `-p` di 
> `mkdir`.


## Primi passi

Durante il corso, utilizzeremo 
[_clang-format_](https://www.kernel.org/doc/html/latest/translations/it_IT/process/clang-format.html),
uno strumento per mantenere il codice formattato in modo uniforme e sensato. L'uso di standard per la 
formattazione del codice verrà discusso più estensivamente a lezione, per ora ci limitiamo a generare 
un configurazione di default (`.clang-format`).

Tale file può essere generato utilizzando il comando `clang-format`, e specificando 
l'opzione `--dump-config`, come segue:

```bash
$ clang-format --dump-config -style=google > .clang-format
$ cat .clang-format
---
Language:        Cpp
# BasedOnStyle:  Google
AccessModifierOffset: -1
AlignAfterOpenBracket: Align
AlignConsecutiveMacros: None
AlignConsecutiveAssignments: None
AlignConsecutiveBitFields: None
AlignConsecutiveDeclarations: None
AlignEscapedNewlines: Left
AlignOperands:   Align
...
```

Esistono molti stili di formattazione; qui si è scelto di partire dalla versione usata da Google 
per il proprio codice.

> __NOTA:__ la sintassi `> .clang-format` permette di scrivere l'output del comando `clang-format` 
> direttamente nel file `.clang-format`, invece di visualizzarlo a schermo. Il termine tecnico per 
> questa operazione è _redirezione dello standard output_.

Per verificare il funzionamento di _clang-format_ creiamo, tramite VSCode, lo scheletro del primo 
programma da sviluppare durante questo laboratorio.

Innanzitutto, dall'interno della nostra directory di lavoro, apriamo VSCode da terminale:

```bash
$ pwd
/home/carlo/pf2021_labs/lab1
$ code .
```

Poi creiamo un nuovo file vuoto (es. per ora utilizziamo l'interfaccia grafica), e salviamolo 
col nome `pi_with_integral.cpp`.

Immettiamo poi nel file `pi_with_integral.cpp` il seguente code snippet (frammento di codice):

```c++
int main() 
{



  }
```

salviamo di nuovo il file ed eseguiamo nel terminale il seguente comando:

```bash
$ clang-format -i pi_with_integral.cpp
```

Se tutto ha funzionato correttamente, il codice dovrebbe risultare formattato come segue:

```c++
int main() {}
```

Utilizzando l'opzione `-i`, abbiamo chiesto a `clang-format` di effettuare le modifiche di 
formattazione direttamente al file `pi_with_integral.cpp`.

> __NOTA:__ cosa sarebbe successo se non avessimo specificato l'opzione `-i`?

Quando si utilizza VSCode, è possibile formattare il codice C++ sulla base del file 
`.clang-format` presente all'interno dell'area di lavoro eseguendo il comando 
_Format Document_:
- su Linux il comando è associato ai tasti di scelta rapida `Ctrl + Shift + I`;
- su Windows il comando è associato ai tasti di scelta rapida `Alt + Shift + F`.
- su mac OS il comando è associato ai tasti di scelta rapida `option + shift + F`.

> __NOTA:__ verifica rapidamente l'utilizzo di clang-format tramite VSCode, modificando tramite 
> l'editor il file `pi_with_integral.cpp` ed utilizzando ai tasti di scelta rapida definiti
> sopra.

> __NOTA:__ come molti altri programmi, VSCode offre un'ampia gamma di ai tasti di scelta rapida.
> È opportuno imparare, sin dal principio, ad utilizzare quelli più comuni. È possibile scaricare
> un file `.pdf` che ne contiene una lista, dalla _Guida_ (_Help_) di VSCode, cliccando su 
> _Riferimento per tasti di scelta rapida_ (_Keyboard Shortcuts Reference_).

Prima di procedere oltre, compiliamo lo scheletro del programma `pi_with_integral.cpp` (per ora 
minimale), tramite il seguente comando:

```bash
$ g++ -Wall -Wextra pi_with_integral.cpp -o pi_with_integral
```

> __NOTA:__ ricordiamo che chi utilizza mac OS dovrà avvalersi del comando `g++-11` invece di 
> `g++`.

> __NOTA:__ le opzioni `-Wall` e `-Wextra` abilitano messaggi di _warning_ opzionali che possono 
> evidenziare problemi nel codice.

## Esercizio 1.: calcolo di &pi;

È possibile calcolare &pi; avvalendosi della seguente relazione:

&emsp;&emsp;<img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue}\LARGE\int_{0}^{1} \frac{4}{1%2Bx^{2}}dx = \pi">

e considerando che:
- il risultato dell'integrale definito, calcolato tra _x_ = 0 e _x_ = 1, corrisponde all'area 
  sottesa dalla funzione ![formula](https://render.githubusercontent.com/render/math?math=\color{RoyalBlue}\large\frac{4}{1%2Bx^{2}}) 
  nell l'intervallo di valori di _x_ corrispondente a [0,1];
- è possibile dividere l'intervallo [0,1] in _n_ sotto-intervalli &Delta;_x_, tutti della 
  stessa dimensione; 
- si può quindi approssimare il calcolo dell'integrale alla sommatoria delle aree di _n_ rettangoli, 
  tutti di base &Delta;_x_, secondo la: 
  <sub><img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue}\large\sum_{i=0}^{n-1} \frac{4}{1%2Bx_{i}^{2}}\Delta x"></sub>, dove
  <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue}\x_{i} = \Delta x \cdot i">;
- nel limite _n_ &rarr; &infin;, il risultato del calcolo basato sui rettangoli coincide col risultato 
  dell'integrale.

Il nostro obiettivo è scrivere un programma che:
1. legge da tastiera il numero di sotto-intervalli  _n_;
1. avvalendosi di un ciclo (loop), effettua il il calcolo di &pi;, approssimando l'integrale alla 
   somma delle aree degli _n_ rettangoli corrispondenti a ciascun sotto-intervallo;
1. stampa a schermo il risultato dell'operazione.

Come discusso a lezione, la descrizione del programma è stata suddivisa __di proposito__ in varie 
__parti__ che sono, tra loro, __logicamente distinte__.

Ad esempio, la parte del calcolo dell'integrale (2.) è logicamente indipendente da quella della 
stampa del risultato (3.).

In programmi più complessi, questo tipo di separazione è tipicamente reso più esplicito tramite 
l'uso di astrazioni (es. funzioni, classi, ...), ma vale la pena abituarsi ad identificare (e non 
mischiare) già da ora le parti del programma che svolgono funzioni distinte, il che porta allo 
sviluppo di un "buon codice".

#### Immissione delle condizioni iniziali

Come discusso a lezione, l'input/output da terminale verrà gestito tramite l'uso di `std::cin` 
e `std::cout`.

> __NOTA:__ in questo primo laboratorio, non ci curiamo di verificare la correttezza dell'input
> da tastiera (es. assumiamo che quanto digitato quando viene richiesto di immettere un valore 
> per _n_, corrisponda un numero intero positivo).

> __NOTA:__ mentre si scrive il codice, familiarizzare con le funzionalità di editing di VSCode:
> - cosa succede quando si inizia a digitare il nome di una variabile che avevi già definito?
> - cosa succede quando si inizia a digitare l'espressione `std::cin`?
> - cosa succede se si sbaglia a digitare il nome di una variabile?

#### Calcolo approssimato dell'integrale

Nella seguente parte del programma, sfruttiamo l'approccio del calcolo delle aree dei rettangoli, 
per approssimare il calcolo dell'integrale.

Sebbene non sia strettamente necessario, è buona prassi definire esplicitamente le costanti
che corrispondo agli estremi di integrazione, così che non appaiano come "numeri magici" 
direttamente all'interno del programma, facendolo così risultare più leggibile:

```c++
const double x_min = 0.0;
const double x_max = 1.0;
```

Come si può notare, in questo code snippet, abbiamo utilizzato le keywords `const` e `double`.

Durante il corso si parlerà in maniera approfondita di entrambe, per ora basti sapere che:
- `double` definisce un tipo di variabile che, con alcune limitazioni, viene utilizzato per 
  descrivere numeri reali;
- in questo contesto, `const` "promette" che le variabili appena definite non verranno 
  modificate.

Infine, come potete notare, i limiti di integrazione, sono espressi tramite i letterali di
`0.0` ed `1.0` (tipo `double`), invece che tramite i letterali interi `0` ed `1`.

> __HINT__: per capire perché, verificare cosa viene stampato a schermo nei seguenti casi:

```c++
std::cout << 1/2 << '\n';
std::cout << 1.0/2.0 << '\n';
```

> __NOTA__: tipicamente, in caso si voglia assegnare il risultato di operazioni matematiche 
> (es. prodotto) tra numeri `double` ad un'altra variabile, quello che si vuole fare è
> definire come `double` anche la variabile che conterrà il risultato:

```c++
double base = 2.11;
double altezza = 4.2;
double area = base * altezza;
std::cout << altezza << '\n';
```
> __HINT__: provare a definire `area` come `int` invece di `double` e controllare cosa succede.

Dati `x_min`, `x_max` ed _n_, abbiamo tutti gli ingredienti per calcolare &Delta;_x_.
Considerando inoltre che possiamo utilizzare la funzione 
<sub><img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue}\large\sum_{i=0}^{n-1} \frac{4}{1%2Bx_{i}^{2}}\Delta x"></sub>
per calcolare le altezze dei rettangoli nei diversi punti come descritto sopra, siamo pronti 
per risolvere il problema avvalendoci di un _loop_.

> __DOMANDA__: in questo caso è più appropriato utilizzare un _for loop_ o un _while loop_?

#### Stampa a schermo e verifica dei risultati

Infine, dobbiamo stampare il valore approssimato dell'integrale avvalendoci di `std::cout`.

Compiliamo il programma e risolviamo tutti gli eventuali errori di compilazione e i warning:

```bash
$ g++ -Wall -Wextra pi_with_integral.cpp -o pi_with_integral
```

Verifichiamo quindi il funzionamento del programma, per esempio:

```bash
$ ./pi_with_integral
Inserisci il numero di sotto-intervalli per il calcolo di pi greco: 100
Integrale : 3.15158
```

> __NOTA:__ una volta immesso il valore per _n_ proposto sopra, il tempo di esecuzione 
> del programma dovrebbe essere tipicamente inferiore al secondo. Se, per via di qualche 
> errore, il programma dovesse entrare in un loop infinito, è possibile interromperlo 
> digitando `Ctrl + C` (Linux), oppure `command + C` (mac OS).
> Ovviamente il tempo di esecuzione del programma può crescere se si immettono valori
> molto grandi per _n_.

Possiamo infine controllare cosa succede se:
- immettiamo _n_ = 0, oppure _n_ = 1;
- immettiamo valori "non ragionevoli" per _n_ (stringe, numeri non interi, numeri negativi).

## Esercizio 2.: Moto parabolico

Il moto parabolico di un proiettile "sparato" all'istante _t_ = 0 s tramite un cannone (posizionato 
per semplicità nell'origine di un piano cartesiano) è descritto dalle seguenti equazioni:

- _x_(_t_) = |__v__| cos(_&alpha;_) _t_
- _y_(_t_) = |__v__| sin(_&alpha;_) _t_ - &#189; |__g__| _t_<sup>2</sup>

Dove:
- |__v__| : è il modulo della velocità iniziale del proiettile;
- _&alpha;_ : è l'angolo di alzo del cannone;
- __g__ : è l'accelerazione di gravità.

Il nostro obiettivo è scrivere un programma che:
1. legge da tastiera le variabili |__v__| ed _&alpha;_ (assumendo che |__v__| sia espresso in m/s
   ed _&alpha;_ sia espresso in gradi);
1. le converte nelle componenti cartesiane v<sub>x</sub> e v<sub>y</sub>, poi stampa queste ultime a 
   schermo;
1. ad intervalli di tempo definiti (es. &Delta;_t_ = 0.001 s), _campiona_ la traiettoria del proiettile:
   - registra il valore massimo (_y_<sub>max</sub>) dell'altezza dal suolo che il proiettile raggiunge 
     nei punti campionati;
   - assumendo che il cannone sia posizionato su un piano orizzontale, registra:
      - il valore del tempo di volo (_t_<sub>max</sub>);
      - la gittata (_x_<sub>max</sub>);
      - entrambi definiti come gli ultimi valori assunti durante il campionamento *prima* che il proiettile 
        tocchi il suolo;
1. una volta terminato il campionamento, stampa a schermo _y_<sub>max</sub>, _x_<sub>max</sub> e 
   _t_<sub>max</sub>.

Creiamo quindi, tramite VSCode, un file vuoto e salviamolo col nome `projectile_motion.cpp`.

#### Immissione delle condizioni iniziali

Anche in questo caso, l'input/output da terminale verrà gestito tramite l'uso di `std::cin` 
e `std::cout`.

> __NOTA:__ come anticipato prima, per oggi non ci curiamo di verificare la correttezza dell'input
> da tastiera (es. assumiamo che quanto digitato quando viene richiesto di immettere valori per 
> |__v__| ed _&alpha;_ sia corretto).

#### Elaborazione dei parametri immessi

Partendo da |__v__| e _&alpha;_, procediamo poi a derivare le componenti cartesiane 
del vettore velocità: v<sub>x</sub> e v<sub>y</sub>.

Per farlo possiamo avvalerci delle funzioni `std::cos()` e `std::sin()`, disponibili nella 
libreria [`cmath`](https://en.cppreference.com/w/cpp/header/cmath#Functions)
(`#include <cmath>`). 

Non ci preoccupiamo troppo di definire in dettaglio cosa sia una funzione per ora (anche questo 
verrà fatto a lezione), ma ci limitiamo a notare che:
- funzioni come `std::cos()` funzionano in modo molto simile alle funzioni trigonometriche delle 
  moderne calcolatrici;
- è possibile fornire loro sia letterali (es. di tipo `double`), che variabili come _input_:

```c++
double alpha = 0.5;
std::cout << std::cos(0.5) << '\n';
std::cout << std::cos(alpha) << '\n';
```

- `cmath` include un ampia gamma di funzioni utili per il calcolo numerico.

Va notato `std::cos()` e `std::sin()` assumono che il loro argomento di input (es: `0.5` o `alpha`
nell'esempio sopra), sia espresso __in radianti__. 

Al fine di effettuare la conversione in radianti di _&alpha;_ (espresso in gradi), calcoliamo, solo 
una volta all'interno del programma, &pi; nel seguente modo:

```c++
const double pi = std::acos(-1.0);
```

Una volta effettuata la conversione, stampare a schermo v<sub>x</sub> e v<sub>y</sub> avvalendosi 
di `std::cout`.

#### Simulazione e campionamento del moto

In questa parte del programma, si richiede di utilizzare le equazioni 
[definite sopra](#moto-parabolico) per _simulare_ l'evoluzione del moto del proiettile,
campionandolo ad intervalli di tempo regolari.

Anche in questo caso, è buona prassi definire esplicitamente le costanti
utilizzate durante la simulazione, come &Delta;_t_ e __g__:

```c++
const double delta_t = 0.001;
const double g = -9.80419;
```

Per campionare la traiettoria del proiettile possiamo semplicemente avvalerci di un loop
ed, interromperlo, come richiesto, quando il proiettile "tocca terra".

> __DOMANDA__: in questo caso è più appropriato utilizzare un _for loop_ o un _while loop_?

Ricordiamo che, durante il campionamento del moto, è richiesto registrare:
- il valore di altezza massimo (_y_<sub>max</sub>) raggiunto dal proiettile;
- la gittata (_x_<sub>max</sub>), ed il tempo di volo (_t_<sub>max</sub>), misurati subito 
  prima che il proiettile tocchi il suolo.

#### Stampa a schermo e verifica dei risultati

Stampiamo quindi a schermo i valori di _y_<sub>max</sub>, _x_<sub>max</sub> 
e _t_<sub>max</sub> registrati utilizzando `std::cout`.

Compiliamo il programma e risolviamo tutti gli eventuali errori di compilazione e i warning:

```bash
$ g++ -Wall -Wextra projectile_motion.cpp -o projectile_motion
```

Verifichiamo quindi il funzionamento del programma, immettendo per esempio:

```bash
$ ./projectile_motion
Inserisci modulo della velocità (in m/s) : 19.5
Inserisci angolo di alzata (in gradi) : 25
Componenti della velocità iniziale del proiettile: v_x = 17.673 m/s - v_y = 8.24106 m/s
Gittata : 29.7083 m
Altezza massima : 3.46357 m
Tempo di volo : 1.681 s
```

> __NOTA:__ una volta immessi i valori di |__v__| ed _&alpha;_ proposti sopra, il tempo 
> di esecuzione del programma dovrebbe essere tipicamente inferiore al secondo. Se, per 
> via di qualche errore, il programma dovesse entrare in un loop infinito, è possibile 
> interromperlo digitando `Ctrl + C` (Linux), oppure `command + C` (mac OS).

Possiamo infine controllate che tutto funzioni come ci aspettiamo se:
- immettiamo valori "non ragionevoli" per |__v__| ed _&alpha;_;
- immettiamo |__v__| = 0 (valore, in linea di principio, valido)
- immettiamo |__v__| = 25 ed _&alpha;_ = 0 (valori, in linea di principio, validi)
- immettiamo |__v__| = 25 ed _&alpha;_ = 90 (valori, in linea di principio, validi)

> __NOTA:__ si suggerisce di verificare quanto i risultati ottenuti in questo modo discostino 
> da quelli che si ottengono risolvendo problema in modo analitico.

## Esempi di soluzioni

Dopo l'esercitazione, le soluzioni degli esercizi proposti saranno disponibili qui:
- Esercizio 1.: [`pi_with_integral.cpp`](pi_with_integral.cpp).
- Esercizio 2.: [`projectile_motion.cpp`](projectile_motion.cpp).

## Consegna del lavoro svolto

La consegna del lavoro svolto in laboratorio è:
- __obbligatoria__ per coloro che hanno seguito il laboratorio __da remoto__;
- __facoltativa__ per coloro che anno seguito il laboratorio __in presenza__.

Nel primo caso, la consegna è utilizzata come strumento per verificare l'effettivo
svolgimento del laboratorio. Nel secondo, la consegna è un'opzione che lasciamo a
quegli studenti che, incerti su alcuni punti, vogliono presentare il lavoro svolto
per chiarire i loro dubbi.

In entrambi i casi, le consegne del lavoro svolto in laboratorio __non verranno 
valutate__ e __NON contribuiscono, in alcun modo al risultato finale dell'esame__.

La consegna deve avvenire, da parte dei singoli studenti, tramite
[questo link](https://virtuale.unibo.it/mod/assign/view.php?id=722994) che riporta 
ad un'apposita pagina all'interno dell'area relativa al corso su virtuale.unibo.it
e deve consistere nell'upload di un file archivio `.zip` o `.tgz`. 

Supponendo che tutto il materiale sia nella cartella `lab1/` (come suggerito ad 
inizio laboratorio), e supponendo di trovarsi in tale cartella, per creare un 
archivio `.zip` procedere come segue:

```bash
$ pwd
/home/carlo/pf2021_labs/lab1
$ cd ..
$ zip -r lab1.zip lab1
$ ls
lab1 lab1.zip
```

Per creare un archivio `.tgz` procedere come segue:

```bash
$ pwd
/home/carlo/pf2021_labs/lab1
$ cd ..
$ tar czvf lab1.tgz lab1
$ ls
lab1 lab1.tgz
```

Chi utilizza WSL, può riferirsi alle seguenti istruzioni, per accedere all'archivio appena
generato, e caricarlo sulla pagina di virtuale.unibo.it:

> Con una distribuzione Ubuntu, si può navigare nelle cartelle Linux semplicemente inserendo 
> nella Barra degli Indirizzi di Esplora Risorse `\\wsl$\Ubuntu\` e da lì accedere alla propria 
> home utente.
>
> In alternativa è sufficiente lanciare il comando `explorer.exe` dalla bash di WSL, specificando 
> in argomento la cartella in cui navigare.
>
> Si può passare l'argomento . (punto) per aprire Esplora Risorse nella cartella WSL aperta in 
> quel momento tramite il terminale:
> ```bash
> $ explorer.exe .
>```
> A questo punto è possibile operare sui file in maniera usuale.

> __NOTA:__ quando viene eseguito il comando `explorer.exe .` (non dimenticate il `.`) ricordarsi
> di farlo quando ci si trova nella directory dove si è creato l'archivio. È possibile verificarlo
> utilizzando il comando `ls`.

## Bonus

Per chi fosse interessato ad "sperimentare ulteriormente" gli argomenti presentati in questo 
laboratorio, vengono proposti alcuni possibili approfondimenti __opzionali__:

- se si è già familiari coi concetti base della programmazione, ma non con il C++ o gli altri 
  tool presentati oggi, è possibile:
   - esplorare le funzionalità di VSCode;
   - studiare la documentazione relativa a clang-format;
   - esplorare la documentazione della libreria 
     [`cmath`](https://en.cppreference.com/w/cpp/header/cmath#Functions).

- alternativamente è possibile estendere il programma per il calcolo di &pi;:
   - immettendo tramite `std::cin` un valore di precisione minima che si vuole raggiungere 
     per il calcolo dell'integrale (es. 0.0001) rispetto ad un valore di riferimento di &pi;;
   - ripetendo il calcolo di &pi; iterativamente (tramite un secondo loop), incrementando _n_ 
     fino a quando non si supera la precisione minima richiesta;
   - stampando a schermo, oltre al risultato del calcolo dell'integrale, anche il valore di 
     _n_ per cui si supera la soglia di precisione richiesta.

> __HINTS__:
> - come descritto nel secondo esercizio, avvalersi di `std::acos(-1.0)` per ottenere un valore 
> di riferimento di &pi;;
> - `cmath` fornisce la funzione `std::abs(double x)` che permette di calcolare il valore assoluto 
> (es: della differenza tra due numeri)

> __HINT__: una possibile soluzione di questo esercizio è: 
> [`pi_with_integral_prec.cpp`](pi_with_integral_prec.cpp).

- inoltre è possibile estendere il programma per la _simulazione_ del moto parabolico:
   - per identificare l'angolo _&alpha;_<sub>max</sub> che massimizza la gittata
   - per introdurre la possibilità di leggere da tastiera possibili coordinate "di 
     atterraggio" del proiettile (_y_<sub>atterraggio</sub>) minori di 0;

> __HINT__: per stimare _&alpha;_<sub>max</sub>, si ripeta, tramite un loop, la simulazione 
> per una serie di valori di _&alpha;_, nel range [0,90]&deg; partendo da 0, ed incrementando
> ad ogni iterazione del loop, _&alpha;_ in step &Delta;_&alpha;_ = 0.05&deg;.

- fatto ciò:
   - si ricavi _&alpha;_<sub>max</sub> con questa versione del programma per il caso: |__v__| = 
     25 m/s;
   - si verifichi la stima ottenuta al calcolatore ricavando la soluzione analitica del problema.

- infine è possibile provare ad utilizzare l'espressione `std::cin.good()`, che restituisce `true` 
  se l'operazione più recente, effettuata tramite `std::cin` è andata a buon fine, per capire come 
  sarebbe possibile controllare la correttezza dei parametri passati in input ai due programmi;
- oltre al check tramite `std::cin.good()`:
   - per il programma che calcola &pi;, si suggerisce di richiedere che _n_ assuma valori 
     "ragionevoli" (cioè sia strettamente maggiore di 0).
   - per il programma che _simula_ il moto parabolico, si suggerisce di controllare quanto 
     segue:
     - |__v__| è il modulo di un vettore, è quindi necessario che il suo valore non sia 
       negativo;
     - ricordando che abbiamo assunto che che _&alpha;_ sia immesso in gradi;
     - richiediamo che il cannone non possa sparare verso il basso;
     - richiediamo che il cannone non possa sparare "all'indietro" (al massimo gli permettiamo 
       di sparare "in verticale").

> __HINT:__ all'interno dell'_if statement_ si possono utilizzare gli operatoti `||` (OR logico) 
> e/o `&&` (AND logico) per verificare più di una singola condizione.
