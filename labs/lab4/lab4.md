# Lab 4

In questo laboratorio metteremo in pratica le nozioni apprese durante il corso
introduttivo su Git.

Qualora lo riteneste necessario, potete tenere aperte le [slide](https://github.com/rsreds/git_course)
presentate a lezione.

- [Lab 4](#lab-4)
  - [Configurazione iniziale di Git](#configurazione-iniziale-di-git)
  - [Effettuare il clone della repository del corso](#effettuare-il-clone-della-repository-del-corso)
  - [Area di lavoro](#area-di-lavoro)
    - [Creare una repository Git](#creare-una-repository-git)
  - [Utilizzo di Git (locale)](#utilizzo-di-git-locale)
    - [Ispezionare lo stato della repo](#ispezionare-lo-stato-della-repo)
    - [Aggiungere file alla repo](#aggiungere-file-alla-repo)
    - [Aggiungere `.gitignore`](#aggiungere-gitignore)
    - [Controllare le differenze tra due commit](#controllare-le-differenze-tra-due-commit)
  - [Applicare una modifica al progetto](#applicare-una-modifica-al-progetto)
  - [Due brevi sessioni interattive](#due-brevi-sessioni-interattive)
    - [Git e Visual Studio Code](#git-e-visual-studio-code)
    - [Utilizzo di Git (remoto) e GitHub](#utilizzo-di-git-remoto-e-github)
  - [Soluzione](#soluzione)
  - [Consegna del lavoro svolto](#consegna-del-lavoro-svolto)
  - [Bonus](#bonus)

## Configurazione iniziale di Git

Git dovrebbe essere già installato nei nostri setup di Linux/WSL e macOS, per
prima cosa verifichiamolo:

```bash
$ git --version
git version 2.35.1
```

Una volta effettuata la verifica, procediamo quindi configurando Git per
riconoscere chi siamo quando, d'ora in poi, aggiungeremo file alle _repository_
(o _repo_) con cui lavoreremo.

Scegliamo in seguito di utilizzare `main` come nome del ramo (_branch_)
principale di sviluppo invece di `master`.

Ed, infine, impostiamo `nano` (strumento _leggero_ e facile da utilizzare) come
editor di default per Git.

Le informazioni sulla configurazione di Git vengono salvate in un file chiamato
`.gitconfig` che si trova nella cartella home.
Possiamo ispezionarlo tramite il comando `cat`.

```bash
$ git config --global user.email "carlo.battilana@cern.ch"
$ git config --global user.name "Carlo Battilana"
$ git config --global init.defaultBranch "main"
$ git config --global core.editor "nano"
$ cat ~/.gitconfig
[user]
        email = carlo.battilana@cern.ch
        name = Carlo Battilana
[init]
       defaultBranch = main
[core]
        editor = nano
...
```

## Effettuare il clone della repository del corso

Rivedremo alcuni passi relativi all'utilizzo del provider remoto GitHub durante
la [seconda parte del laboratorio](#utilizzo-di-git-remoto-e-github).
Per ora, chi non l'ha già fatto, si posizioni in una cartella che ritiene
opportuna (in queste istruzioni abbiamo utilizzato `/home/carlo/`) e scarichi (o
_cloni_) la versione attuale della repo del corso tramite il comando `git clone`:

```bash
$ pwd
/home/carlo/
$ git clone https://github.com/giacomini/pf2021.git 
Cloning into 'pf2021'...
remote: Enumerating objects: 259, done.
remote: Counting objects: 100% (259/259), done.
remote: Compressing objects: 100% (179/179), done.
remote: Total 259 (delta 111), reused 202 (delta 65), pack-reused 0
Receiving objects: 100% (259/259), 1.96 MiB | 21.10 MiB/s, done.
Resolving deltas: 100% (111/111), done.
```

Verifichiamo quindi il successo dell'operazione e la presenza della soluzione
relativa al terzo laboratorio:

```bash
$ ls -la
...
drwxr-xr-x  12 carlo  staff    384 28 Mar 15:03 pf2021
...
$ ls -la pf2021/labs/lab3/solution 
total 1896
drwxr-xr-x  9 carlo  staff     288 28 Mar 14:46 .
drwxr-xr-x  4 carlo  staff     128 28 Mar 14:47 ..
-rw-r--r--  1 carlo  staff     749 28 Mar 14:46 regression.cpp
-rw-r--r--  1 carlo  staff     330 28 Mar 14:46 regression.hpp
-rw-r--r--  1 carlo  staff    1207 28 Mar 14:46 regression.test.cpp
```

## Area di lavoro

Come fatto durante i precedenti laboratori, creiamo una cartella di lavoro
dedicata (ad esempio: `pf2021_labs/lab4`), nella quale copiamo i file `.cpp` e
`.hpp` relativi al risultato ottenuto alla fine del
[terzo laboratorio](../lab3/lab3.md).

Potete usare quanto avete prodotto voi stessi, oppure scaricare la
[soluzione](../lab3/solution/) da noi proposta, dalla quale siamo
partiti per preparare questa esercitazione.
Se scegliete questa opzione, consigliamo (come al solito) di prendervi un po'
di tempo per familiarizzare con il codice.

Questa volta potete copiare i file relativi alla soluzione dalla repo del corso
che avete appena clonato (nel caso di questo esempio, situata in `/home/carlo/pf2021`):

```bash
$ pwd
/home/carlo/pf2021_labs/lab4
$ cp /home/carlo/pf2021/labs/lab3/solution/*.{hpp,cpp} .
```

Aggiungiamo poi i file `doctest.h` e `.clang-format`, in modo da ottenere la
seguente area di lavoro:

```bash
$ pwd
/home/carlo/pf2021_labs/lab4
$ ls -a
.clang-format  doctest.h regression.cpp regression.hpp regression.test.cpp
```

### Creare una repository Git

A questo punto creiamo la repo Git e verifichiamo che viene aggiunta una
cartella nascosta (`.git`):

```bash
$ git init
Initialized empty Git repository in /home/carlo/pf2021_labs/lab4/.git/
$ ls -la
total 1216
drwxr-xr-x  8 carlo  staff     256 18 Mar 17:58 .
drwxr-xr-x  4 carlo  staff     128 18 Mar 17:55 ..
-rw-r--r--  1 carlo  staff    5372 18 Mar 17:56 .clang-format
drwxr-xr-x  9 carlo  staff     288 18 Mar 17:56 .git
-rw-r--r--  1 carlo  staff  299373 18 Mar 17:58 doctest.h
-rw-r--r--  1 carlo  staff     724 18 Mar 17:58 regression.cpp
-rw-r--r--  1 carlo  staff  299373 18 Mar 17:58 regression.hpp
-rw-r--r--  1 carlo  staff     724 18 Mar 17:58 regression.test.cpp
```

> __NOTA__: la cartella nascosta `.git` contiene le informazioni relative alla
> repo.

## Utilizzo di Git (locale)

### Ispezionare lo stato della repo

I due comandi che tipicamente vengono usati per ispezionare lo stato di una repo
sono `git status` e `git log`, spesso accompagnati da una o più delle diverse
opzioni disponibili.

Proviamoli:

```bash
$ git status
On branch main

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        .clang-format
        doctest.h
        regression.cpp
        regression.hpp
        regression.test.cpp

nothing added to commit but untracked files present (use "git add" to track)
$ git log
fatal: your current branch 'main' does not have any commits yet
```

Come possiamo notare, il fatto che i file del nostro progetto fossero già
presenti al momento di creazione della repo, non li rende automaticamente parte
di essa.

Inoltre, siccome non abbiamo ancora eseguito nessun commit, risulta inutile
ispezionare la storia della nostra repo con `git log`, che (in questo caso)
produce un errore.

### Aggiungere file alla repo

Aggiungiamo quindi i file relativi al progetto nella nostra repo:

```bash
$ git add .clang-format doctest.h regression.cpp regression.hpp regression.test.cpp
$ git status
On branch main

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)
        new file:   .clang-format
        new file:   doctest.h
        new file:   regression.cpp
        new file:   regression.hpp
        new file:   regression.test.cpp

$ git commit -m "Add first project version"
[main (commit radice) 04a520f] Add first project version
 5 files changed, 13418 insertions(+)
 create mode 100644 .clang-format
 create mode 100644 doctest.h
 create mode 100644 regression.cpp
 create mode 100644 regression.hpp
 create mode 100644 regression.test.cpp
```

Come possiamo notare, dopo aver eseguito il comando `git add` ci viene ricordata
la lista dei file che verranno aggiunti alla repository al commit successivo,
come il secondo comando (appunto `git commit`) conferma.

Proviamo quindi a verificare nuovamente lo stato della repo:

```bash
$ git status
On branch main
nothing to commit, working tree clean
$ git log
commit 8476457208b06d448f83f90aa235c4c1e4bad643 (HEAD -> main)
Author: Carlo Battilana <carlo.battilana@cern.ch>
Date:   Sat Mar 19 14:46:30 2022 +0100

    Add first project version
```

A questo punto il comando `git status` ci informa che la nostra area di lavoro
non mostra modifiche rispetto all'ultima versione del codice nel branch `main`
della repo.

Il comando `git log`, invece evidenzia la presenza di un singolo commit (nel
branch `main`) e ne fornisce alcuni dettagli.

### Aggiungere `.gitignore`

Procediamo quindi a compilare ed eseguire il progetto:

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

Per poi verificare di nuovo lo stato della repo:

```bash
$ git status
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        a.out

nothing added to commit but untracked files present (use "git add" to track)
```

Sicuramente non vogliamo tracciare (cioè, inserire nella repo) il file `a.out`,
in primis perché è un binario, ma soprattutto perché è un file generato. Ha poco
senso tracciare qualcosa che può essere generato a partire da altri file
tracciati.

Per evitare che Git ci ricordi continuamente che abbiamo un file non tracciato
indichiamogli di ignorarlo, creando il file `.gitignore` dove andiamo ad
aggiungere la singola riga `a.out`.

Verifichiamone poi il contenuto con il comando `cat`, controlliamo come cambia
l'output del comando `git status`, infine procediamo ad aggiungere e committare
`.gitignore`:

```bash
$ code .gitignore
$ cat .gitignore
a.out
$ git status
On branch main
Untracked files:
  (use "git add <file>..." to include in what will be committed)
        .gitignore

nothing added to commit but untracked files present (use "git add" to track)
$ git add .gitignore
$ git commit -m "Add gitignore"
[main d92deb5] Add gitignore
 1 file changed, 1 insertion(+)
 create mode 100644 .gitignore
 ```

Controlliamo quindi, ancora una volta, lo stato della repo:

```bash
$ git status
On branch main
nothing to commit, working tree clean
$ git log
commit 68bc18840914d81b527a8a0f1c25e91b1c14d24b (HEAD -> main)
Author: Carlo Battilana <carlo.battilana@cern.ch>
Date:   Sat Mar 19 14:49:11 2022 +0100

    Add gitignore

commit 8476457208b06d448f83f90aa235c4c1e4bad643
Author: Carlo Battilana <carlo.battilana@cern.ch>
Date:   Sat Mar 19 14:46:30 2022 +0100

    Add first project version
```

Notiamo che `git log` mostra in cima nuove informazioni, lasciando inalterate
quelle precedenti. Allo stesso tempo le etichette `HEAD` e `main` vengono
sempre spostate in corrispondenza dell'ultimo commit.

### Controllare le differenze tra due commit

A volte è preferibile una versione più compatta dell'output di `git log`, che possiamo ottenere, ad esempio, aggiungendo l'opzione `--oneline`:

```bash
$ git log --oneline
68bc188 (HEAD -> main) Add gitignore
8476457 Add first project version
```

Possiamo notare che all'inizio di ogni riga di output del comando precedente
mostra gli _hash_ dei singoli commit, che possiamo ad esempio utilizzare per
verificare la differenza tra due commit qualsiasi, usando `git diff`:

```bash
$ git diff 68bc188 8476457
diff --git a/.gitignore b/.gitignore
deleted file mode 100644
index cba7efc..0000000
--- a/.gitignore
+++ /dev/null
@@ -1 +0,0 @@
-a.out
```

## Applicare una modifica al progetto

Questa prima versione di `Regression` non memorizza la "storia" dei punti che
sono stati aggiunti tramite il metodo `add`. Potrebbe essere necessario
memorizzare all'interno della classe tale informazione, ad esempio se si
vuole permettere la rimozione di un punto, qualora questo fosse stato già
inserito (come richiesto nella parte [opzionale](#bonus) di questo laboratorio).

In tale caso è più pratico combinare le coordinate _x_ ed _y_ di ciascun punto
che verrà utilizzato per il calcolo della retta di regressione in una `struct`
`Point`.

Decidiamo pertanto di modificare il progetto scegliendo questo approccio.

Sarebbe possibile procedere con lo sviluppo committando direttamente eventuali
cambiamenti nel branch `main`, il che ci permetterebbe già di tenere traccia di
tutte le modifiche apportate al codice, così da poter "viaggiare nel tempo" e
ripristinare eventualmente versioni precedenti del progetto.

Nella pratica, però, quando collaboriamo a progetti che sono condivisi con altre
persone (siano essi semplici utilizzatori, o sviluppatori coi quali
lavoriamo), torna spesso utile la capacità di Git di gestire linee di sviluppo
indipendenti, che si svolgono su _branch_ separati, ed unirle
(farne il _merge_, o _mergiarle_), in un secondo tempo.

Pertanto procederemo ad effettuare le modifiche del nostro codice in un branch
separato, che chiameremo `add_point_struct`.

Per creare il nuovo branch e spostarci su di esso, procediamo nel seguente modo:

```bash
$ git checkout -b add_point_struct
Switched to a new branch 'add_point_struct'
$ git status
On branch add_point_struct
nothing to commit, working tree clean
$ git log --oneline
68bc188 (HEAD -> add_point_struct, main) Add gitignore
8476457 Add first project version
```

Ora stiamo lavorando sul branch `add_point_struct`, che, per il momento,
risulta essere identico al branch `main`.

> __NOTA__: il comando `git checkout -b add_point_struct` è equivalente all
> coppia di comandi:
>
> ```bash
> $ git branch add_point_struct
> $ git checkout add_point_struct
> Switched to a new branch 'add_point_struct'
> ```

A questo punto procediamo modificando la classe `Regression` per includere un
`std::vector<Point>` nella sua parte privata:

```c++
#ifndef REGRESSION_HPP
#define REGRESSION_HPP

#include<vector>
...
class Regression {
  struct Point {
    double x;
    double y;
  };

  std::vector<Point> points_{};
  int N{};
  ...
};
```

Aggiungendo un dato membro privato, la prima cosa che dobbiamo chiederci è quale
sia l'impatto sull'__invariante di classe__, cioè la relazione esistente tra i
dati membri di una classe.

In questo caso, __in ogni momento__, si dovrebbe garantire che:

- `N` sia _sempre_ uguale a `points_.size()`;
- i vari campi corrispondenti alle sommatorie siano _sempre_ calcolabili a partire dai punti in `points_`;

Pertanto, preservare tutti questi dati membro renderebbe l'informazione nella
parte privata di `Regression` altamente ridondante, generando una classe
_difficile da mantenere_.

D'altro canto, rimuovere tutte variabili relative alle somme parziali ci imporrebbe di calcolarle il risultato della regressione da zero, a partire da
`points_`, direttamente nel metodo `fit`, il che avrebbe verosimilmente impatto sulla performance di `fit`.

Decidiamo di optare per __la prima opzione, più facile da implementare e
mantenere__.

> __NOTA__: lavorando su un branch separato, possiamo decidere di
> _buttarlo via_ in ogni momento, qualora la nuova soluzione implementata
> risultasse inappropriata (es: troppo lenta), senza mai avere interferito con
> lo stato del branch `main`.

Rimuoviamo quindi tutte le variabili membro di regression ad eccezione di
`points_` e procediamo con le modifiche necessarie a `regression.cpp`.

Ad esempio `add` diventerebbe semplicemente:

```c++
...
void Regression::add(double x, double y) {
  points_.push_back({x,y});
}
...
```

mentre sarebbe necessario ricalcolare le somme all'interno di `fit`:

```c++
...
Result Regression::fit() const {
  ...

  double sum_x{};
  double sum_y{};
  double sum_xy{};
  double sum_x2{};

  for (auto const& p : points_) {
    sum_x += p.x;
    sum_y += p.y;
    sum_xy += p.x * p.y;
    sum_x2 += p.x * p.x;
  }

  ...
}
...
```

L'implementazione dei cambiamenti necessari è volutamente lasciata in uno stato
parziale.

__Completate voi le modifiche__ e verificate che il programma compili
e funzioni come deve prima di procedere.

> __NOTA__: in questo caso particolare non abbiamo modificato per nulla
> l'interfaccia della classe `Regression` e non abbiamo aggiunto nessuna nuova
> funzionalità, pertanto non è stato necessario aggiungere nessun test in
> `regression.test.cpp`.

Una volta verificato che il programma si comporti come atteso, controlliamo le
modifiche che stiamo per committare tramite `git diff`:

``` bash
$ git diff
diff --git a/regression.cpp b/regression.cpp
index c9a9fec..2bd53eb 100644
--- a/regression.cpp
+++ b/regression.cpp
@@ -2,30 +2,40 @@
 
 #include <stdexcept>
 
-int Regression::size() const { return N_; }
+int Regression::size() const { return points_.size(); }
 
 void Regression::add(double x, double y) {
-  ++N_;
-  sum_x_ += x;
-  sum_y_ += y;
-  sum_xy_ += x * y;
-  sum_x2_ += x * x;
+  points_.push_back({x,y});
 }
 ...
 ```

tale comando, eseguito senza argomenti, mostra la differenza tra la nostra area
di lavoro e lo stato del branch in cui stiamo lavorando.

> __NOTA__: possiamo scorrere la lista delle differenze tramite i tasti freccia,
> qualora risulti troppo lunga per essere visualizzata nel terminale tutta
> insieme.

Procediamo poi includendo i cambiamenti nel branch `add_point_struct`:

```bash
$ git add regression.cpp regression.hpp
$ git commit -m "Use vector of 2D points in Regression"
[add_point_struct a4f03ea] Use vector of 2D points in Regression
 2 files changed, 50 insertions(+), 31 deletions(-)
 rewrite regression.cpp (63%)
$ git status                 
On branch add_point_struct
nothing to commit, working tree clean
```

Poi ritorniamo al branch `main` ed effettuiamo il merge:

```bash
$ git log --oneline   
* a4f03ea (HEAD -> add_point_struct) Use vector of 2D points in Regression
* 68bc188 (main) Add gitignore
* 8476457 Add first project version
$ git checkout main
Switched to branch 'main'
$ git merge --no-ff add_point_struct
Merge made by the 'ort' strategy.
 regression.cpp | 36 +++++++++++++++++++++++-------------
 regression.hpp |  9 +++++++++
 2 files changed, 32 insertions(+), 13 deletions(-)
$ git log --oneline --graph         
*   10ffa5a (HEAD -> main) Merge branch 'add_point_struct'
|\  
| * a4f03ea (add_point_struct) Use vector of 2D points in Regression
|/  
* 68bc188 Add gitignore
* 8476457 Add first project version
```

Possiamo notare alcune cose:

1. è necessario eseguire il comando `git add` prima del commit anche quando si
   modificano file già inclusi nella repo;
2. `git log` inizialmente ci mostra che `add_point_struct` si discosta di un
   commit rispetto a `main`;
3. dopo il commit, tramite `git log --oneline --graph`, risulta evidente
   l'evoluzione del progetto (incluso il merge).

> __NOTA__: dopo essere ritornati sul branch `main`, ma prima di effettuare il
> merge, potete (se volete) ispezionare i file `regression.cpp` e
> `regression.hpp` per verificare che sono ritornati com'erano prima di
> introdurre le modifiche relative all'uso di  `std::vector<Points>`.
>
> __NOTA__: a volte i cambiamenti effettuati in un branch separato (es:
> `add_point_struct`) sono lineari rispetto a quelli del branch in cui viene
> mergiato (es.: `main`), ovvero non ci sono sviluppi concorrenti.
> In questi casi, Git può decidere di "dimenticarsi completamente"
> dell'esistenza del branch separato, ed aggiungere tutta la storia dei commit
> effettuati direttamente all'interno del branch in cui questo viene integrato.
> L'opzione `--no-ff`, utilizzata in questo caso durante il merge, previene
> questo comportamento. L'abbiamo usata a fini esemplificativi, per rendere
> evidente lo sviluppo in un branch separato quanto abbiamo controllato
> l'evoluzione della repo con `git log --oneline --graph`, molto spesso tale
> opzione non viene utilizzata, lasciando decidere a Git come comportarsi.

In questo caso "semplice" il merge non ha dato _conflitti_. Quando si effettuano
sviluppi concorrenti sui medesimi file, a volte, è necessario intervenire
manualmente durante il merge, nel caso Git non riesca a combinarli in modo
automatico.

## Due brevi sessioni interattive

Procediamo ora a schermo, mostrando alcune funzionalità di Visual Studio Code e
con la configurazione di un account GitHub.

__Entrambe le sessioni interattive sono opzionali__, chi preferisse procedere
con la parte [bonus](#bonus) dell'esercitazione, può farlo liberamente.

### Git e Visual Studio Code

Qualora un progetto sia gestito tramite una un sistema di Version Control (es.:
una repo Git), Visual Studio Code offre strumenti per effettuare alcune delle
operazioni comuni, [direttamente tramite l'interfaccia di
sviluppo](https://code.visualstudio.com/docs/editor/versioncontrol#_git-support)
.

Andiamo a mostrare brevemente alcune di queste funzionalità in modo
_interattivo_ nei prossimi minuti, tuttavia:

- consigliamo di iniziare ad utilizzarle solo dopo aver appreso il funzionamento
  dei comandi base di Git da terminale;
- utilizzare sempre Git da terminale quando si intende adoperare funzionalità
  "complesse".

### Utilizzo di Git (remoto) e GitHub

Procediamo ancora in modo _interattivo_ per aiutare chi ne avesse bisogno a
configurare un account GitHub ed il relativo accesso tramite una coppia di
chiavi _ssh_.

Ricordiamo brevemente i passi che seguiremo in questa fase nelle prossime righe,
ma consigliamo di aprire le [slide](https://github.com/rsreds/git_course)
presentate a lezione.

1. Create un account alla pagina
   [https://github.com/join](https://github.com/join)
   - ci riferiremo al vostro nome utente su GitHub come  `<github_username>`
2. Create una repo remota alla pagina
   [https://github.com/new](https://github.com/new) (senza selezionare nessuna
   delle opzioni di inizializzazione)
   - ci riferiremo alla vostra repo GitHub come  `<github_repo_name>`
3. Una volta creata la repo, copiate il link url ssh relativo ad essa
   - ci riferiremo al link url ssh della vostra repo come `<repository_ssh_url>`
4. Create di una coppia di chiavi ssh e __prendete nota__ della posizione del
   file `.pub` (in questo caso: `/home/carlo/.ssh/id_rsa.pub`):

   ```bash
   $ ssh-keygen -t rsa
   Generating public/private rsa key pair.
   Enter file in which to save the key (/home/carlo/.ssh/id_rsa): 
   Enter passphrase (empty for no passphrase): 
   Enter same passphrase again: 
   Your identification has been saved in /home/carlo/.ssh/id_rsa.
   Your public key has been saved in /home/carlo/.ssh/id_rsa.pub.
   The key fingerprint is:
   SHA256:KPYiVP4jzm4ljPgxzzeR4LUcUZlbU6CrIBv9a+R1yB4 carlo@MacBook-Pro-di-Carlo.local
   The key randomart image is:
   +---[RSA 3072]----+
   |       ..o.o.    |
   |      . o.o      |
   |    .  ..o .     |
   |   +. o...       |
   | .++*+.=S.       |
   |..+=+*B.E .      |
   | .o=o=*+ o       |
   |  .++o=o.        |
   |   o+o..         |
   +----[SHA256]-----+
   ```

5. Andate alla pagina
   [https://github.com/settings/keys](https://github.com/settings/keys):
   - create una nuova chiave
   - aprite il file `.pub` e copiatene il contenuto nel form della pagina web
6. Dall'area di lavoro del laboratorio eseguite `git remote add` (sostituendo a
   `<repository_ssh_url>` il link ottenuto al punto 3.):

   ```bash
   $ git remote add origin <repository_ssh_url>
   $ git remote -v
   origin  git@github.com:<github_username>/<github_repo_name>.git (fetch)
   origin  git@github.com:<github_username>/<github_repo_name>.git (push)
   ```

7. Eseguite il `push` del branch `main` nella vostra repository remota:

   ```bash
   $ git push -u origin main
   Enumerating objects: 4, done.
   Counting objects: 100% (4/4), done.
   Delta compression using up to 8 threads
   Compressing objects: 100% (3/3), done.
   Writing objects: 100% (3/3), 3.29 KiB | 3.29 MiB/s, done.
   Total 3 (delta 0), reused 0 (delta 0), pack-reused 0
   To github.com:<github_username>/<github_repo_name>.git
   2decf39..57fa4cb  main -> main
   ```

8. Verificate lo stato della repo remota nella vostra pagina GitHub

## Soluzione

Nei giorni successivi a questa esercitazione, la soluzione dell'esercizio (che
include anche lo sviluppo dell'approfondimento [bonus](#bonus)) sarà reso
disponibile nella cartella [solution](solution/).

## Consegna del lavoro svolto

Come per gli altri laboratori, la consegna del lavoro svolto è:

- __obbligatoria__ per coloro che hanno seguito il laboratorio __da remoto__;
- __facoltativa__ per coloro che anno seguito il laboratorio __in presenza__.

Nel primo caso, la consegna è utilizzata come strumento per verificare
l'effettivo svolgimento dell'attività di laboratorio. Nel secondo, la consegna è
un'opzione che lasciamo a quegli studenti che, incerti su alcuni punti, vogliono
presentare il lavoro svolto per chiarire i loro dubbi.

In entrambi i casi, le consegne del lavoro svolto in laboratorio __non verranno
valutate__ e __NON contribuiscono al risultato dell'esame__.

La consegna deve avvenire, da parte dei singoli studenti, tramite
[questo link](https://virtuale.unibo.it/mod/assign/view.php?id=865752), seguendo
una procedura analoga a quella discussa [durante il primo laboratorio](https://github.com/giacomini/pf2021/blob/main/labs/lab1/lab1.md#consegna-del-lavoro-svolto).

Il link permette il solo caricamento di file `.zip` o `.tgz`.

Tutti coloro che effettuano una consegna facoltativa, sono pregati di riportare,
come commento alla consegna stessa, dubbi o domande sull'elaborato per i quali
è richiesto feedback esplicito da parte dei docenti.

> __NOTA:__ in genere non è opportuno aggiungere la cartella `.git` ed il file
> `.gitignore` alle consegne (ad esempio suggeriamo vivamente di non farlo
> durante la consegna del progetto d'esame). Però, visto che questo laboratorio
> tratta proprio l'uso di Git, vi richiediamo, eccezionalmente, di aggiungerli.

## Bonus

Qualora rimanga tempo prima della fine del laboratorio, viene proposto un approfondimento:

Provate ad aggiungere una funzione membro `remove(x, y)` che accetti in input
due `double`, li trasformi in un `Point` e, qualora il punto da rimuovere
risulti presente nel vettore `points_` all'interno di `Regression`, lo
rimuova.

Per farlo suggeriamo di procedere per passi:

- Decidete la strategia da utilizzare con Git (es. creare un nuovo branch di
  cui farete un merge alla fine), e procedete a configurare la repo.
- Per verificare se due `Point` sono uguali tra loro prima di rimuoverli, è
  utile implementare un operatore `==`, potete farlo in:

  ```c++
  struct Point {
    double x;
    double y;
    bool operator==(Point const& other) const
    {
      ...
    }
  };
  ```

  o al di fuori della dichiarazione di `Point`.
- Prima di implementare `remove`, ricordatevi di implementare i test necessari
  per verificarne il funzionamento.
- Un possibile suggerimento da cui partire per implementare `remove` potrebbe
  essere:
  
  ```c++
  bool remove(double x, double y)
  {
    Regression:Point p_rm{x,y}
    for (auto p_it = points_.begin(), p_end = points_.end(); p_it != p_end; ++p_it) {
      if ((*p_it) == p_rm) {
        points_.erase(p_it);
        return true;
      }
    }
    return false;
  }
  ```

  provate a migliorarla, ad esempio utilizzando l'algoritmo
  [`std::find()`](https://en.cppreference.com/w/cpp/algorithm/find).
