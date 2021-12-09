# Lab 2

Gli obiettivi di questo laboratorio sono:

- familiarizzare con l'attività unit-testing (avvalendoci di [doctest](https://github.com/doctest/doctest));
- scrivere un programma che calcoli la retta di regressione di un insieme di
  punti nel piano (usando una classe).

- [Lab 2](#lab-2)
  - [Area di lavoro](#area-di-lavoro)
    - [Prime prove con doctest (opzionale)](#prime-prove-con-doctest-opzionale)
  - [Retta di regressione](#retta-di-regressione)
    - [Definizione test della classe `Regression`](#definizione-test-della-classe-regression)
    - [Implementazione della classe `Regression`](#implementazione-della-classe-regression)
    - [Aggiungere altri test](#aggiungere-altri-test)
    - [Soluzione](#soluzione)
  - [Consegna del lavoro svolto](#consegna-del-lavoro-svolto)
  - [Bonus](#bonus)

## Area di lavoro

Creiamo una nuova directory di lavoro (ad esempio `pf2021_labs/lab2`) e
aggiungiamo i file `doctest.h` e `.clang-format`. Possiamo copiare `.clang-format`
dalla directory utilizzata per il primo laboratorio, o generarlo ex-novo. Possiamo
scaricare il file
[`doctest.h`](https://raw.githubusercontent.com/giacomini/pf2021/main/code/doctest.h)
tramite i seguenti comandi:

- su Linux / Windows (in questo caso, dentro WSL):

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ wget https://raw.githubusercontent.com/giacomini/pf2021/main/code/doctest.h
```

- su mac OS:

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ curl https://raw.githubusercontent.com/giacomini/pf2021/main/code/doctest.h -o doctest.h
```

Fatto ciò, l'area di lavoro deve trovarsi in questo stato:

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ ls -A
.clang-format  doctest.h
```

### Prime prove con doctest (opzionale)

Chi non l'avesse ancora fatto, può familiarizzare velocemente con doctest
scaricando il programma d'esempio presentato a lezione
([isqrt.cpp](https://raw.githubusercontent.com/giacomini/pf2021/main/code/isqrt.cpp)),
tramite i seguenti comandi:

- su Linux / Windows (in questo caso, dentro WSL):

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ wget https://raw.githubusercontent.com/giacomini/pf2021/main/code/isqrt.cpp
```

- su mac OS:

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ curl https://raw.githubusercontent.com/giacomini/pf2021/main/code/isqrt.cpp -o isqrt.cpp
```

Dopo averlo scaricato, l'area di lavoro dovrebbe risultare analoga alla seguente:

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ ls -A
.clang-format  doctest.h isqrt.cpp
```

Possiamo compilare questo programma con `g++ -Wall -Wextra isqrt.cpp -o isqrt`,
ed eseguirlo con `./isqrt`. Verificandone poi l'output.

> __NOTA__: chi utilizza macOS ricordi di compilare tramite il comando `g++-11`.

Possiamo quindi aprire la directory di lavoro tramite VSCode `code .`, aprire il
file `isqrt.cpp` e provare a modificarlo, ad esempio aggiungendo test che ci
aspettiamo funzionino o falliscano. Riproviamo poi a compilare il programma ed
eseguirlo (facendo attenzione a come cambia l'output).

## Retta di regressione

Dato un insieme di <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue}\Large N"> punti
<img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large (x_i, y_i)">, i coefficienti della retta di regressione
<img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large y = A %2B B \cdot x"> sono dati da:

<img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \LARGE \: \: A = \frac {\sum y_{i} \sum x_{i}^{2} - \sum x_{i} \sum x_{i} y_{i}}{N \sum x_{i}^{2} - (\sum x_{i})^{2}}">

<img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \LARGE \: \: B = \frac {N \sum x_{i}y_{i} - \sum x_{i} \sum y_{i}}{N \sum x_{i}^{2} - (\sum x_{i})^{2}}">

### Definizione test della classe `Regression`

L'obiettivo di oggi è di risolvere l'esercizio sviluppando una classe che
calcoli i coefficienti della retta di regressione.

Cominciamo identificando le funzionalità _minime_ che l'interfaccia della classe
`Regression` deve garantire:

- un metodo `add` per accettare nuovi punti (uno alla volta per ora);
- un metodo `fit` che ritorni i coefficienti `A` e `B` della retta di
  regressione (calcolati sui punti inseriti fino ad un dato momento).

Come detto a lezione, è buona prassi iniziare lo sviluppo identificando quello
che ci aspettiamo che la classe faccia (ovvero prevedendo il suo comportamento
in casi specifici), prima di addentrarci nell'implementazione del codice.
Creiamo quindi uno scheletro di programma contenente un test basato su doctest.

```c++
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

TEST_CASE("Testing Regression") {
  Regression reg;
  reg.add(0., 1.);
  reg.add(1., 2.);
  auto result = reg.fit();
  CHECK(result.A == doctest::Approx(1.));
  CHECK(result.B == doctest::Approx(1.));
}
```

> __NOTA__: Dato che confrontiamo numeri _floating-point_, possiamo usare
> `Approx`, in modo da tollerare errori di arrotondamento durante i test.

Apriamo VSCode nell'area di lavoro, creiamo un nuovo file (es:
`regression.test.cpp` - dove la parte `.test` del nome ci ricorda che è un file
di test) ed inseriamo il testo riportato sopra:

```bash
$ pwd
/home/carlo/pf2021_labs/lab2
$ code .
```

> __NOTA__: consigliamo di controllare la combinazione di tasti di scelta
> rapida associata alla creazione di un file vuoto in VSCode e, d'ora in poi,
> abituarsi ad utilizzarla con regolarità.

Se proviamo a compilare il programma, nello stato in cui si trova ora (es.: `g++
-Wall -Wextra regression.test.cpp`), otteniamo errori di compilazione perché la
classe `Regression` non è definita.

> __NOTA__: chi utilizza macOS ricordi di compilare tramite il comando `g++-11`.

È importante provare a compilare e leggere attentamente gli errori di
compilazione: spesso, anche se non sempre, gli errori contengono informazioni e
suggerimenti utili a risolvere immediatamente il problema.

### Implementazione della classe `Regression`

Procediamo quindi a creare la classe `Regression`, aggiungendo quanto segue al
file `regression.test.cpp` __prima__ del `TEST_CASE`:

```c++
class Regression
{
};
```

Ripetendo la compilazione (verifichiamo!) otteniamo errori (diversi da prima)
legati alla mancanza dei metodi `add` e `fit`.

Ovviare alla mancanza di `add` è facile, basta aggiungerlo alla classe:

```c++
class Regression
{
 public:
  void add(double x, double y) {}
};
```

> __Notiamo che, in `add`__:
>
> - il _return type_ è `void`, in quanto il metodo non deve restituire nulla;
> - i due argomenti sono entrambi di tipo `double`;
> - l'implementazione per ora non fa nulla; il comportamento è naturalmente
>   sbagliato, ma ci permette di iniziare a definire l'interfaccia e risolve
>   l'errore di compilazione;
> - il fatto che non stiamo ancora utilizzando le variabili `x` e `y`
>   nell'implementazione di `add` genera dei _warning_ (avvertimenti) in fase di
>   compilazione (se si usano le opzioni `-Wall -Wextra`).

Aggiungere il metodo `fit` richiede maggiore attenzione, perché dobbiamo prima
definire il tipo ritornato. Dall'uso che viene fatto di `result`, vediamo che
deve avere due dati membri pubblici, chiamati `A` e `B`, entrambi di tipo
`double`. Potremmo quindi definire una `struct` (o una `class`, specificando
però l'accesso `public`) con quei due campi, che potremmo chiamare `Result`.

Il nostro codice diventerebbe quindi:

```c++
struct Result
{
  double A{};
  double B{};
};

class Regression
{
 public:
  void add(double x, double y) {}
  Result fit()
  {
    return Result{};
  }
};
```

> __Notiamo che `fit`__:
>
> - non ha argomenti;
> - per ora la sua implementazione restituisce una `struct` `Result` con i
>   campi semplicemente azzerati (ci preoccuperemo di implementare
>   correttamente la logica della regressione tra poco).

Con queste modifiche il programma compila correttamente (provate!), ma fallisce
entrambi i test.

> __NOTA__: controllate esattamente che informazione riportano i test quando
> falliscono.

Pensiamo quindi a come implementare i due metodi, così che __facciano
quello che vogliamo__. Nel caso dell'implementazione di una classe, la cosa
spesso implica anche chiedersi: "cosa abbiamo bisogno di memorizzare, in termini
di variabili membro (private) della classe, per raggiungere i nostri scopi?"

Nel nostro caso, la domanda sopra si traduce in questa: "ci serve
davvero mantenere in memoria tutti i punti che inseriti tramite il metodo `add`,
per un loro utilizzo quando viene chiamato il metodo `fit`, o ci sono
alternative?"

Se si osservano attentamente le formule indicate sopra, si può notare che non
c'è bisogno di farlo, ma è sufficiente mantenere alcuni _accumulatori_ di valori:

- <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large N">
- <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large \sum x_i">
- <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large \sum y_i">
- <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large \sum x_i^2">
- <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large \sum x_i y_i">

che possiamo aggiornare man mano che viene chiamato il metodo `add`. Questi
valori verranno poi opportunamente combinati nel momento in cui viene chiamato
il metodo `fit` per calcolare il risultato.

Come si implementa questa idea in C++?

```c++
class Regression
{
  int N_{};
  double sum_x_{};
  double sum_y_{};
  // ...

 public:
  void add(double x, double y)
  {
    ++N_;
    sum_x_ += x;
    sum_y_ += y;
    // ...
  }

  Result fit()
  {
    double const a = // ...
    double const b = // ...
    return {a, b};
  }
}
```

Completate il codice dove trovate `// ...`

> __NOTA__: tipicamente, si utilizzando criteri per distinguere le variabili
> membro di una classe da quelle definite nello _scope_ di una determinata
> funzione membro. Nel caso sopra, abbiamo introdotto un "_" alla fine del nome
> della variabile (es.: `N_`).
>
> __NOTA__: notare che le variabili membro sono costituite da tipi primitivi,
> quindi devono essere inizializzate, altrimenti il loro valore iniziale risulta
> indeterminato. Qui proponiamo di inizializzarle direttamente dove sono
> dichiarate, usando la sintassi `{}`. In questo modo sono _value-initialized_,
> che per gli `int` e i `double` significa "inizializzati a zero". In
> alternativa si potrebbe:
>
> - usare la sintassi più esplicita `int n = 0;`, `double sum_x = 0.;`, etc ...;
> - definire esplicitamente un costruttore di default, che nella sua
>   _initialization-list_ inizializzi tutti i valori a zero.
>
> Se vi rimane tempo potete provare a sperimentare tutte le alternative.

Se l'implementazione è corretta, entrambi i test devono passare con successo.

Facciamo un'ultima modifica al codice della classe, dichiarando `fit` come
`const` in quanto **non modifica** i dati membri.

> __NOTA__: in generale, è importante identificare tutte le funzioni membro
> della nostra classe che sono, o che ci aspettiamo debbano essere, `const` e
> specificarle come tali.

```c++
class Regression
{
  // ...
  Result fit() const
  {
    // ...
  }
  // ...
};
```

### Aggiungere altri test

Ora che la classe `Regression` è implementata e soddisfa il nostro test
minimale, è opportuno aggiungere altri casi di test.

Ricordiamo che l'obiettivo dei test non è di confermare che il programma
funzioni; al contrario, l'obiettivo è di **rompere** il codice. Cercare
attivamente potenziali "punti deboli" dal principio ci permette di evidenziare
e risolvere problemi sin da subito. Eseguire poi i test definiti in questo
momento ad ogni nuovo sviluppo, permette di verificare che tali problemi non
appaiano in futuro.

A titolo esemplificativo, cosa vorremmo che succeda se:

- chiamiamo `fit` senza aggiungere alcun punto?
- chiamiamo `fit` dopo aver aggiunto un solo punto?
- chiamiamo `fit` dopo aver aggiunto due punti uguali?
- chiamiamo `fit` dopo aver aggiunto due punti allineati verticalmente (cioè con
  la stessa <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large x">)?

>__HINT__: per verificare se la retta ha pendenza verticale, possiamo sfruttare
>il fatto che, in questo caso, esiste una relazione ben definita tra
> <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large \sum x_i">
> e <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large \sum x_i^2">,
> quale?
>
>__NOTA__: per gestire in modo appropriato il comportamento del metodo `fit`
> nei casi sopra citati, possiamo avvalerci di assertions o exceptions.
> Per capire come implementare test con doctest in questi casi, consultare la
> sezione [Assertion
> macros](https://github.com/doctest/doctest/blob/master/doc/markdown/assertions.md)
> della documentazione.

Inoltre si possono aggiungere alcuni test che utilizzano tre o più punti,
possibilmente non allineati, e inserire nei `CHECK` i valori calcolati di `A` e
`B`. I calcoli si possono fare con carta e penna, si può usare
[WolframAlpha](https://www.wolframalpha.com), oppure si possono utilizzare i
dati raccolti durante le prove pratiche del corso di laboratorio di Meccanica e
Termodinamica.

>__NOTA__: quando si implementano più test, è possibile esprimerli utilizzando i
>`SUBCASE`, così da partire sempre con un oggetto di tipo `Regression` vuoto.
>Per una comprensione più dettagliata dei `SUBCASE`, possiamo consultare la
>[documentazione](https://github.com/doctest/doctest/blob/master/doc/markdown/tutorial.md#test-cases-and-subcases).
>
> __NOTA__: Potrebbe essere necessario avere maggior controllo quando si
> confrontano numeri _floating-point_ rispetto al semplice uso di `Approx`.
> Doctest fornisce anche la funzione `epsilon`, che permette di specificare
> l'errore percentuale tollerato.
> Un esempio concreto è: `CHECK(result.A == doctest::Approx(1.2).epsilon(0.01));`
> Per una comprensione più dettagliata, possiamo consultare la
> [documentazione](http://bit.ly/doctest-docs), in particolare la sezione
> "Floating point comparisons" in [Assertion
> macros](https://github.com/doctest/doctest/blob/master/doc/markdown/assertions.md).

### Soluzione

Dopo l'esercitazione, la soluzione dell'esercizio proposto sarà disponibile in
[`regression.test.cpp`](regression.test.cpp).

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

1. utilizzare, all'interno della versione programma sviluppata al punto
   precedente, una `struct` `Point` per trattare i singoli punti, in modo simile
   a quanto fatto nel caso della `struct` `Result`.
   > __HINT__: fatto ciò, è possibile implementare l'operatore `==` per
   > verificare se due punti hanno le stesse coordinate (tale operatore tornerà
   > utile durante lo svolgimento della la seconda parte opzionale
   > dell'esercizio).
   >
   > __DOMANDA__: prima di procedere con l'implementazione, pensate a come
   > modificare i test. In che modo bisogna modificare quelli esistenti? Ci sono
   > altri test che vanno aggiunti?

1. estendere il programma in modo che si possa decidere, in un secondo momento,
   di rimuovere alcuni punti __precedentemente inseriti__.
   > __HINT__: in questo caso è necessario tenere traccia di tutti i punti
   > inseriti fino ad un dato momento, lo si può fare utilizzando un vettore di
   > punti: `std::vector<Point>` (`std::vector<>` sara trattato estensivamente a
   > lezione in futuro, chi fosse curioso di sperimentare già da ora, può
   > trovare la documentazione necessaria
   > [qui](https://en.cppreference.com/w/cpp/container/vector)).
   >
   > __HINT__: l'operatore `==` definito al punto precedente dovrebbe aiutare
   > con l'implementazione di questa funzionalità opzionale.
   >
   > __DOMANDA__: prima di procedere con l'implementazione, pensate a come
   > modificare i test. Bisogna modificare quelli esistenti? Ci sono altri test
   > che dobbiamo aggiungere?
