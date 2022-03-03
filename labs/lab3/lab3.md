# Lab 3

L'obiettivo di questo laboratorio è di distribuire su più file il codice
scritto nel secondo laboratorio per implementare e testare la classe
`Regression`.

Per lo svolgimento, consigliamo di tenere aperta la parte inerente al
_compilation model_ delle
[slide](https://github.com/giacomini/pf2021/releases/tag/pdf_20220228)
presentate a lezione.

- [Lab 3](#lab-3)
  - [Area di lavoro](#area-di-lavoro)
  - [Distribuzione del codice in più file](#distribuzione-del-codice-in-più-file)
    - [Preparazione di `regression.hpp`](#preparazione-di-regressionhpp)
    - [Test della _One-Definition Rule_ ed uso di _include guard_](#test-della-one-definition-rule-ed-uso-di-include-guard)
    - [Utilizzo di `Regression` in più di una translation-unit](#utilizzo-di-regression-in-più-di-una-translation-unit)
    - [Definizione di funzioni in `regression.cpp`](#definizione-di-funzioni-in-regressioncpp)
    - [Soluzione](#soluzione)
  - [Consegna del lavoro svolto](#consegna-del-lavoro-svolto)
  - [Bonus](#bonus)

## Area di lavoro

Come fatto durante i precedenti laboratori, cominciamo creando una cartella di
lavoro dedicata (ad esempio: `pf2021_labs/lab3`), nella quale copiamo i file:

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ ls -A
.clang-format  doctest.h  regression.test.cpp
```

Il file `regression.test.cpp` è il risultato ottenuto alla fine del
[secondo laboratorio](../lab2/lab2.md).

Potete usare quanto avete prodotto voi stessi, oppure scaricare la
[soluzione](../lab2/regression.test.cpp) da noi proposta, dalla quale siamo
partiti per preparare questa esercitazione, utilizzando i seguenti comandi:

- su Linux / Windows (in questo caso, dentro WSL):

```bash
$ pwd
/home/carlo/pf2021_labs/lab3
$ wget https://raw.githubusercontent.com/giacomini/pf2021/main/labs/lab2/regression.test.cpp
```

- su mac OS:

```bash
$ pwd
/home/carlo/pf2021_labs/lab3
$ curl https://raw.githubusercontent.com/giacomini/pf2021/main/labs/lab2/regression.test.cpp -o regression.test.cpp
```

In questo secondo caso, prendetevi un po' di tempo per prendere familiarità con
il codice.

## Distribuzione del codice in più file

Quello che ci prefiggiamo di fare durante questa esercitazione è separare il
codice presente all'interno di `regression.test.cpp`, in modo tale da giungere in una situazione in cui ci siano:

- due file `regression.hpp` e `regression.cpp` con tutto il codice necessario al
  calcolo della retta di regressione, quindi tutte le classi e le funzioni a
  esclusione dei test;
- un file `regression.test.cpp` contenente solo i test e il supporto per la loro
  esecuzione.

In particolare, vogliamo raggiungere una condizione finale in cui:

- `regression.hpp` contenga la definizione della classe `Regression`, ma
  includa solo le dichiarazioni delle funzioni membro in essa contenute, così
  come la dichiarazione della funzione libera `fit`;
- le definizioni dei metodi relativi a `Regression` (`size`, `add` e `fit`) e
  della funzione libera `fit` dovranno invece essere implementate all'interno di
  `regression.cpp`.

Ciò ci permetterà di comprendere l'uso delle _include guard_, della parola
chiave `inline` e di familiarizzare con alcuni errori comuni di compilazione e
linking.

### Preparazione di `regression.hpp`

Cominciamo creando un nuovo file `regression.hpp`, dove spostiamo tutte
le classi e le funzioni contenute in `regression.test.cpp`.
In quest'ultimo, deve rimanere solamente il contenuto relativo ai test:

```c++
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Testing Regression") {
  ...
}
```

Se proviamo a compilare ora `regression.test.cpp` otterremo errori di
compilazione, dovuti alla mancanza di `Regression`:

```bash
$ g++ -Wall -Wextra regression.test.cpp
regression.test.cpp: In function 'void _DOCTEST_ANON_FUNC_8()':
regression.test.cpp:6:3: error: 'Regression' was not declared in this scope
    6 |   Regression reg;
      |   ^~~~~~~~~~
In file included from regression.test.cpp:3:
...
```

Per risolverli, è sufficiente inserire `#include "regression.hpp"` dove prima
c'era il codice che abbiamo spostato.
Dopotutto il preprocessore si può immaginare come un motore di copia/incolla
del contenuto del file incluso nel punto in cui avviene l'inclusione.

```c++
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "regression.hpp"

TEST_CASE("testing Regression") {
  ...
}
```

### Test della _One-Definition Rule_ ed uso di _include guard_

Cosa succede se includiamo `regression.hpp` __due__ volte? Abbiamo visto che può
capitare che lo stesso header file possa essere incluso, direttamente o
indirettamente, più volte nella stessa _translation unit_ (TU).

Proviamo quindi a farlo:

```c++
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "regression.hpp"
#include "regression.hpp"  // Included for test purposes 

TEST_CASE("testing Regression") {
  ...
}
```

e compiliamo:

```bash
$ g++ -Wall -Wextra regression.test.cpp
In file included from regression.test.cpp:6:
regression.hpp:4:8: error: redefinition of 'struct Result'
    4 | struct Result {
      |        ^~~~~~
In file included from regression.test.cpp:5:
regression.hpp:4:8: note: previous definition of 'struct Result'
    4 | struct Result {
      |    
...
```

Possiamo notare ridefinizioni, sia della struct `Result` che della classe
`Regression`. Siccome siamo all'interno della stessa TU, il compilatore è in
grado di diagnosticare queste violazioni della _One-Definition Rule_.

Anche in questo caso la soluzione è semplice: inseriamo un'_include guard_ in
`regression.hpp`, in modo tale che, se l'header file viene incluso più volte
nella stessa TU, il suo contenuto venga considerato solo la prima volta.

Aggiungiamo quindi all'inizio e alla fine del file:

```c++
#ifndef REGRESSION_HPP
#define REGRESSION_HPP

...

#endif
```

> __NOTA__: `REGRESSION_HPP` è una _macro_ del preprocessore. Invece di
> `REGRESSION_HPP` avremmo potuto scegliere un nome qualsiasi, ma è necessario
> garantirne l'unicità tra tutti gli header file che fanno parte del nostro
> progetto, o che appartengono ad altri progetti ma sono inclusi dal nostro.
> Scegliere un nome che richiami il nome del file, scritto tutto in lettere
> maiuscole, è una delle convenzioni maggiormente utilizzate (che quindi
> adottiamo anche noi).

A questo punto siamo in grado di compilare ed eseguire correttamente i nostri
test. Ci siamo ricondotti ad una situazione stabile:

```bash
$ g++ -Wall -Wextra regression.test.cpp
$ ./a.out
[doctest] doctest version is "2.4.6"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:  1 |  1 passed | 0 failed | 0 skipped
[doctest] assertions: 15 | 15 passed | 0 failed |
[doctest] Status: SUCCESS!
```

Dopo questa verifica, provvediamo a rimuovere lo statement `#include` duplicato
in:

```c++
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "regression.hpp"
#include "regression.hpp" // Included for test purposes

TEST_CASE("testing Regression") {
  ...
}
```

che abbiamo utilizzato per il test.

### Utilizzo di `Regression` in più di una translation-unit

Supponiamo ora che il nostro componente software sia parte, o venga usato, in un
progetto con molti file e che quindi `regression.hpp` possa essere incluso in
più TU.

Il modo più semplice per porsi in tale situazione, e quindi di verificare che
stiamo facendo le cose per bene, è di aggiungere una TU formata da un file
sorgente che si limiti a includere l'header corrispondente. Questa TU viene poi
integrata nel nostro comando di compilazione.

Creiamo quindi un file `regression.cpp`, il cui contenuto sia semplicemente:

```c++
#include "regression.hpp"
```

Prima di aggiungerlo al comando di compilazione precedente, proviamo a
compilarlo separatamente (cioè come singola TU).

Questo permette di verificare che l'header file `regression.hpp` sia completo,
che cioè includa tutto ciò che serve alle entità che dichiara/definisce.

```bash
$ g++ -Wall -Wextra -c regression.cpp
$ ls -t | grep regression
regression.o
regression.hpp
regression.cpp
regression.test.cpp
```

> __NOTA__: in questo caso si è aggiunta l'opzione `-c` al comando di
> compilazione, per dire al compilatore di non eseguire la fase di _linking_ e
> creare solamente _file oggetto_.  `regression.o`

Verificato che sia tutto a posto, possiamo provare a compilare tutto insieme:

```bash
$ g++ -Wall -Wextra regression.test.cpp regression.cpp
duplicate symbol '__Z3fitRK10Regression' in:
    /var/folders/q6/6y06s2c90sj5ycyfbsbz9pbr0000gn/T//ccM22Cgu.o
    /var/folders/q6/6y06s2c90sj5ycyfbsbz9pbr0000gn/T//cca78Sv6.o
ld: 1 duplicate symbol for architecture x86_64
collect2: error: ld returned 1 exit status
```

Possiamo notare un errore di _linking_, dovuto alla funzione
`auto fit(Regression const &reg)`, definita al di fuori della classe
`Regression`.

Ciò è dovuto al fatto che, essendo definita in un header file, ed essendo questo
header file incluso in due TU, `auto fit(Regression const &reg)` risulta
definita due volte all'interno dello stesso programma.

Prima di risolvere il problema, replichiamolo anche per una funzione membro
(metodo), ad esempio `Regression::add(double x, double y)`.

Dentro la classe ci limitiamo a dichiararla e spostiamo la definizione
all'esterno:

```c++
class Regression {
  ...
  void add(double x, double y);
  ...
};

...

void Regression::add(double x, double y) {
  ++N_;
  sum_x_ += x;
  sum_y_ += y;
  sum_xy_ += x * y;
  sum_x2_ += x * x;
}
```

> __NOTA__: ricordarsi di aggiungere il nome della classe seguito dallo _scope
> operator_ (cioè `Regression::`) davanti al nome del metodo.

Se riproviamo a compilare, oltre all'errore precedente, ne otteniamo un altro:

```bash
$ g++ -Wall -Wextra regression.test.cpp regression.cpp
duplicate symbol '__Z3fitRK10Regression' in:
    /var/folders/q6/6y06s2c90sj5ycyfbsbz9pbr0000gn/T//ccC1YLM8.o
    /var/folders/q6/6y06s2c90sj5ycyfbsbz9pbr0000gn/T//ccCMOqjG.o
duplicate symbol '__ZN10Regression3addEdd' in:
    /var/folders/q6/6y06s2c90sj5ycyfbsbz9pbr0000gn/T//ccC1YLM8.o
    /var/folders/q6/6y06s2c90sj5ycyfbsbz9pbr0000gn/T//ccCMOqjG.o
ld: 2 duplicate symbols for architecture x86_64
collect2: error: ld returned 1 exit status
```

Per risolvere il problema è sufficiente aggiungere la parola chiave `inline` di
fronte alle definizioni delle funzioni definite fuori dalla classe:

```c++
inline auto fit(Regression const& reg) { 
  ... 
}
inline void Regression::add(double x, double y) { 
  ... 
}
```

Verifichiamo a questo punto che il codice compili e funzioni correttamente:

```bash
$ g++ -Wall -Wextra regression.test.cpp regression.cpp
$ ./a.out
[doctest] doctest version is "2.4.6"
[doctest] run with "--help" for options
===============================================================================
[doctest] test cases:  1 |  1 passed | 0 failed | 0 skipped
[doctest] assertions: 15 | 15 passed | 0 failed |
[doctest] Status: SUCCESS!
```

### Definizione di funzioni in `regression.cpp`

Come discusso a lezione, la configurazione raggiunta al punto precedente è di
per se sufficiente per ottenere la separazione necessaria per utilizzare
`Regression` all'interno di molteplici TU di uno stesso programma.

Un'altra alternativa è quella di spostare la definizione delle funzioni
contenute in `regression.hpp` all'interno di `regression.cpp`, mantenendo in
`regression.hpp` solo la loro dichiarazione.

__Entrambe le strategie hanno vantaggi e svantaggi__, siccome il nostro scopo è
quello di impratichirci con tutte le possibili opzioni di suddivisione del
codice, proviamo ad implementarle entrambe.

Cominciamo spostando la definizione di `Regression::add(double x, double y)`
all'interno di `regression.cpp`, che diventa:

```c++
#include "regression.hpp"

void Regression::add(double x, double y) { 
  ... 
}
```

Verifichiamo quindi che compilazione e test vadano a buon fine.

> __NOTA__: una funzione può essere definita `inline` __se e
> solo se la sua definizione è in un header file__, cosa succede se la parola
> chiave `inline` non viene rimossa quando spostiamo la definizione nel file
> `regression.cpp`?.

Procediamo nello stesso modo spostando anche `fit(Regression const& reg)`.
Compilando possiamo notare che non ci sono errori, ma è facile verificare che,
a questo punto, tale funzione appena non è più visibile al di fuori di
`regression.cpp`.

Per farlo, possiamo semplicemente sostituire una qualsiasi
chiamata a `Regression::fit()` all'interno di `regression.test.cpp` con una
chiamata a `fit(Regression const& reg)`, ad esempio:

```c++
...
TEST_CASE("Testing Regression") {
  Regression reg;

  REQUIRE(reg.size() == 0);

  SUBCASE("Fitting with no points throws") { CHECK_THROWS(fit(reg)); }
}
...
```

e provare a compilare di nuovo.

Per renderla di nuovo accessibile, possiamo dichiarare (ma non definire)
`fit(Regression const& reg)` all'interno di `regression.hpp`, dopo che
`Regression` è stata dichiarata:

```c++
...
Result fit(Regression const &reg);

#endif
```

> __NOTA__: in questo caso è necessario definire esplicitamente il tipo
> ritornato dalla funzione (`Result`). Cosa succede se non lo facciamo?.

Per completare quest'ultimo punto dell l'esercizio, procediamo ripetendo la
procedura per le funzioni membro:

```c++
int size() const { ... }
Result fit() const {
  ...
}
```

Ricordandoci, ad ogni passaggio, di compilare e di eseguire i test.

### Soluzione

Dopo l'esercitazione, la soluzione dell'esercizio proposto sarà disponibile
nella cartella [solution](solution).

## Consegna del lavoro svolto

Come per il primo laboratorio, la consegna del lavoro svolto è:

- __obbligatoria__ per coloro che hanno seguito il laboratorio __da remoto__;
- __facoltativa__ per coloro che anno seguito il laboratorio __in presenza__.

Nel primo caso, la consegna è utilizzata come strumento per verificare
l'effettivo svolgimento dell'attività di laboratorio. Nel secondo, la consegna è
un'opzione che lasciamo a quegli studenti che, incerti su alcuni punti, vogliono
presentare il lavoro svolto per chiarire i loro dubbi.

In entrambi i casi, le consegne del lavoro svolto in laboratorio __non verranno
valutate__ e __NON contribuiscono al risultato dell'esame__.

La consegna deve avvenire, da parte dei singoli studenti, tramite
[questo link](https://virtuale.unibo.it/mod/assign/view.php?id=775795), seguendo
una procedura analoga a quella discussa [durante il primo laboratorio](https://github.com/giacomini/pf2021/blob/main/labs/lab1/lab1.md#consegna-del-lavoro-svolto).

Il link prevede il solo caricamento di file `.zip` o `.tgz`.

Tutti coloro che effettuano una consegna facoltativa, sono pregati di riportare,
come commento alla consegna stessa, dubbi o domande sull'elaborato per i quali
è richiesto feedback esplicito da parte dei docenti.

## Bonus

Per chi fosse interessato a "sperimentare ulteriormente" gli argomenti
presentati in questo laboratorio, vengono proposti alcuni possibili
approfondimenti __opzionali__:

1. Provate ad aggiungere un nuovo file `main.cpp` contenente una funzione
   `main` che usa i componenti definiti sopra. Il programma accetta dall'utente comandi:
   - `a`: per aggiungere un punto (x,y) scrivendo `a x y`. Ad esempio, per  
     aggiungere il punto (0,0), scrive `a 0 0`
   - `f` per eseguire il fit e stampare l'equazione della retta di regressione
