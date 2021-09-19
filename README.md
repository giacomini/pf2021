# Programmazione per la Fisica 2021/2022

Questa repository contiene materiale a supporto dell'insegnamento di "Programmazione per la Fisica", corso di laurea in
Fisica, Università di Bologna, Anno Accademico 2021/2022.

La directory `tex` contiene il sorgente della presentazione mostrata a lezione, scritta in LaTeX. Il `pdf` viene
prodotto automaticamente a ogni modifica ed è disponibile nella sezione "Releases".

La directory `code` contiene codice di esempio mostrato a lezione.

La directory `doc` contiene documentazione varia.

Il contenuto della repository è scaricabile sul proprio computer usando il comando `git`:

```shell
git clone https://github.com/giacomini/pf2021.git
```

oppure scaricando direttamente un file `zip`.

A breve verrà resa disponibile e illustrata a lezione una introduzione a Git.

## Piattaforma di riferimento

La piattaforma di riferimento del corso è la distribuzione Linux Ubuntu 20.04.

Gli strumenti software minimi richiesti sono:

* shell: `bash`
* version control: `git`
* compilatore C++: `g++`
* formattatore di codice: `clang-format`
* editor/IDE: a scelta. Esempi: `nano`, `vi`, `emacs`, _Visual Studio Code_, _Eclipse_

La shell è disponibile già con l'installazione di default di Ubuntu. Gli altri strumenti sono disponibili nel catalogo
ufficiale dei pacchetti software della distribuzione. Per l'installazione si usa il comando `apt`; ad esempio per
installare `git`, `g++` e `clang-format` è sufficiente eseguire il seguente comando:

```shell
sudo apt install git g++ clang-format
```

(viene richiesta la password utente)

Durante il corso verranno usati ulteriori strumenti: [`CMake`](https://cmake.org/) come _build system_ e [SFML](https://sfml-dev.org/) per la creazione di semplici interfacce grafiche. L'installazione è altrettanto semplice:

```shell
sudo apt install cmake libsfml-dev
```

Per prendere familiarità con Linux si suggeriscono le seguenti guide:

* [Introduzione a Linux](https://www.sci.unich.it/~amato/teaching/old/labdati10/lezioni/linux/linux.php) è una sintetica
  introduzione a Linux e alla shell, scritta dal prof. Gianluca Amato dell'Università di Chieti per un corso di
  "Laboratorio di Sistemi Operativi". Il testo è un po' datato e la pagina presenta qualche errore di formattazione, ma
  il contenuto è ancora valido.
* [Linux tutorial](https://ryanstutorials.net/linuxtutorial/) è una guida esauriente a Linux e alla Bash scritta da Ryan
  Chadwick. I capitoli "The Command Line", "Basic Navigation", "File Manipulation" contengono informazioni essenziali;
  gli altri possono essere approfonditi con calma; alcuni ("Vi Text Editor", "Scripting") possono essere considerati
  superflui per questo corso (ma comunque utili).

## Altre piattaforme

Prodotti software analoghi sono disponibili su altre piattaforme di uso comune, quali Windows e macOS.

Per Windows si suggerisce di installare il Windows Subsystem for Linux, secondo la [guida](doc/WSLGuide.md) dispondibile
in questa repository.

Per macOS, essendo simile a Linux, la configurazione è semplificata ed è illustrata in [questa
guida](doc/macOSGuide.md).

## Editor

Per uniformità tra tutte le piattaforme, l'editor consigliato è [Visual Studio Code](https://code.visualstudio.com/). Si
rimanda alla pagina indicata per l'installazione.
