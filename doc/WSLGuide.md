# Installazione del Windows Subsystem for Linux

- [Installazione del Windows Subsystem for Linux](#installazione-del-windows-subsystem-for-linux)
  - [Installazione manuale WSL 2 - Build 18362 o superiori](#installazione-manuale-wsl-2---build-18362-o-superiori)
    - [1. Abilitare Windows Subsystem for Linux](#1-abilitare-windows-subsystem-for-linux)
    - [2. Abilitare Virtual Machine](#2-abilitare-virtual-machine)
    - [3. Riavviare](#3-riavviare)
    - [4. Scaricare il Kernel Linux](#4-scaricare-il-kernel-linux)
    - [5. Impostare WSL2 come versione predefinita](#5-impostare-wsl2-come-versione-predefinita)
    - [6. Installare una distribuzione Linux](#6-installare-una-distribuzione-linux)
  - [Installazione manuale WSL 1 - Build da 16215 a 18360](#installazione-manuale-wsl-1---build-da-16215-a-18360)
  - [Installazione semplificata WSL 2 - Build 20262 o superiore](#installazione-semplificata-wsl-2---build-20262-o-superiore)
  - [Configurare la distribuzione](#configurare-la-distribuzione)
  - [Installazione di Visual Studio Code](#installazione-di-visual-studio-code)
    - [1. Installare Visual Studio Code](#1-installare-visual-studio-code)
    - [2. Installare l'estensione Remote Development](#2-installare-lestensione-remote-development)
    - [3. Aprire una cartella remota](#3-aprire-una-cartella-remota)
  - [Passare file tra Windows e WSL](#passare-file-tra-windows-e-wsl)
    - [Accedere a Windows file system da WSL](#accedere-a-windows-file-system-da-wsl)
    - [Accedere al filesystem Linux da Windows](#accedere-al-filesystem-linux-da-windows)
  - [Cambiare la versione di WSL](#cambiare-la-versione-di-wsl)

Questa guida descrive i passi necessari per configurare la propria macchina Windows 10 in preparazione per il corso di Programmazione per la Fisica.

La procedura comporterà l'installazione dei seguenti strumenti software:

- [Windows Subsystem for Linux](https://docs.microsoft.com/it-it/windows/wsl/) (WSL) - che permette di eseguire un
  ambiente GNU/Linux direttamente in Windows;
- [Visual Studio Code](https://code.visualstudio.com/) - un editor di codice sorgente, disponibile sia per Windows che
  per MacOS e Linux;

Con questi due strumenti è possibile lavorare in un ambiente Linux, con strumenti da riga di comando, direttamente in Windows, senza ricorrere a soluzioni più complesse, quali macchine virtuali o configurazioni dual boot (che comunque sono accettabili).

> **Nota alla riga di comando**
>
> Quando indicato nel testo, potrebbe essere necessario inserire un comando da un'applicazione detta _Terminale_. In
> questa guida i comandi sono preceduti da un simbolo detto `prompt`, che può variare in base al terminale utilizzato o
> al sistema operativo. Tipicamente su Windows il simbolo è `>`, su Linux `$` e su MacOs `%`.
>
> È possibile individuare il prompt all'inizio della linea di comando quando il terminale è in attesa di istruzioni. Seppur riportato, non si deve inserire il simbolo di prompt nello scrivere i comandi presentati in questa guida.
>
> Dopo aver inserito un comando è possibile eseguirlo battendo il tasto _Invio_.

Le istruzioni per l'installazione di WSL (nonché la sua versione) variano in base alla versione di Windows installata
sulla macchina. Prima di proseguire nell'installazione, controlla la versione installata navigando in Impostazioni ->
Sistema -> Informazioni, verificando la corrispondenza del numero **Build sistema operativo**.

> In caso di problemi con l'installazione, fai riferimento a [questa
> guida](https://docs.microsoft.com/it-it/windows/wsl/install-win10#troubleshooting-installation).

## Installazione manuale WSL 2 - Build 18362 o superiori

### 1. Abilitare Windows Subsystem for Linux

Apri il Pannello di controllo -> Programmi e funzionalità -> Attivazione o disattivazione delle funzionalità Windows.

Seleziona *Sottosistema Windows per Linux* (*Windows Subsystem for Linux*).

> **In alternativa**
>
> Se preferisci usare la linea di comando, apri Powershell come Amministratore e copia il seguente comando:
>  
> ```Powershell
> > dism.exe /online /enable-feature /featurename:Microsoft-Windows-Subsystem-Linux /all /norestart
> ```
>
> Eseguilo premendo Invio, per abilitare la funzionalità facoltativa Sottosistema Windows per Linux.

### 2. Abilitare Virtual Machine

Sempre nel menù Attivazione o disattivazione delle funzionalità Windows seleziona *Piattaforma macchina virtuale* (*Virtual machine platform*).

> **In alternativa**
>
> Se preferisci usare la linea di comando, apri Powershell come Amministratore e copia il seguente comando:
>  
> ```Powershell
> > dism.exe /online /enable-feature /featurename:VirtualMachinePlatform /all /norestart
> ```
>
> Eseguilo premendo Invio, per abilitare la funzionalità facoltativa Piattaforma macchina virtuale.

### 3. Riavviare

Premi Ok per applicare le modifiche e al termine dell'installazione Riavvia il dispositivo.

### 4. Scaricare il Kernel Linux

Scarica il pacchetto al seguente link: [WSL2 Linux kernel update package for x64 machines](https://wslstorestorage.blob.core.windows.net/wslblob/wsl_update_x64.msi)

Installa il pacchetto scaricato.

### 5. Impostare WSL2 come versione predefinita

Apri Powershell come amministratore e copia il seguente comando

```powershell
> wsl --set-default-version 2
```

Batti Invio per eseguire il comando.

### 6. Installare una distribuzione Linux

Apri il Microsoft Store e cerca la distribuzione preferita di Linux. Per il corso la distribuzione consigliata è [Ubuntu 20.04 LTS](https://www.microsoft.com/store/apps/9n6svws3rx71).

Nella pagina della distribuzione fai clic su "Ottieni" per scaricarla e installarla.

## Installazione manuale WSL 1 - Build da 16215 a 18360

Per il corso di programmazione per la fisica è suggerito utilizzare WSL2. Nel caso in cui il proprio dispositivo non lo supporti e non sia possibile aggiornare la versione di Windows installata, è possibile installare la versione precedente di WSL.

Per installare WSL1 seguire i soli passaggi 1, 3 e 6 presentati nella sezione [precedente](#installazione-manuale-wsl-2---build-18362-o-superiori).

## Installazione semplificata WSL 2 - Build 20262 o superiore

Se il proprio sistema operativo è aggiornato alla versione Preview 20262 o superiore, è possibile utilizzare il comando semplificato di installazione.

Per farlo è sufficiente aprire una finstera di comando come amministratore (powershell o cmd) e lanciare il comando.

```cmd
> wsl.exe --install
```

Dopo un riavvio WSL sarà pronta all'uso.
Con questo comando verrà installata di default l'ultima versione di Ubuntu. Se si preferisce una diversa distribuzione di Linux è possibile usare il comando:

```powershell
> wsl.exe --install -d <Nome Distribuzione>
```

## Configurare la distribuzione

Avvia la distribuzione cercando Ubuntu nel menù di start; per gli avvii successivi potrai anche farlo lanciando i comandi `bash` o `wsl` da Powershell o dal Prompt dei Comandi.

Al primo avvio si aprirà una finestra della console e ti verrà richiesto di attendere qualche minuto per la decompressione e l'archiviazione dei file nel PC.

Ti verrà poi chiesto di immettere un nome utente e una password. Questi sono specifici della distribuzione di Linux installata e non hanno alcuna relazione con nome utente e password di Windows.

> Il nome utente inserito deve soddisfare i requisiti di Unix `NAME_REGEX="^[a-z][-a-z0-9_]*$"`. Può quindi essere composto solo da lettere minuscole, numeri, il carattere speciale '-' e deve iniziare con una lettera minuscola.

Durante l'inserimento della password, per motivi di sicurezza, non vedrai i caratteri inseriti, né il movimento del cursore. Il sistema chiederà l'inserimento della password due volte; se le password inserite non coincidono, la procedura verrà ripetuta.

> Se dimentichi la password della distribuzione di Linux fai riferimento a [questa guida](https://docs.microsoft.com/it-it/windows/wsl/user-support#forgot-your-password) per recuperarla.

Aggiorna quindi il catalogo pacchetti della distribuzione. Per Ubuntu è possibile farlo eseguendo il seguente comando dal terminale:

``` bash
$ sudo apt update && sudo apt upgrade
```

Il comando `sudo`, usato come prefisso al comando `apt`, consente di eseguire quest'ultimo come amministratore di sistema (detto *root* nel gergo Unix) e richiede l'inserimento della password utente.
Si raccomanda di aggiornare periodicamente la distribuzione, indicativamente una volta alla settimana.

Per installare ulteriori pacchetti, utilizza il comando `sudo apt install`. Ad esempio, per installare `clang-format` e `g++`, usa il comando:

``` bash
$ sudo apt install clang-format g++
```

## Installazione di Visual Studio Code

Il WSL è pensato per essere usato soprattutto da linea di comando all'interno di un terminale testuale. E' quindi possibile eseguire agevolmente ad esempio la compilazione di un programma con `g++` o la formattazione del suo codice sorgente con `clang-format`.

Però, per chi non ha troppa familiarità con il terminale, altre azioni sono invece meno agevoli, prima fra tutte la possibilità di editare dei file. Editor testuali, quali `nano`, `vim` e `emacs`, sono certamente disponibili (dopo eventuale installazione), ma esiste anche la possibilità di editare file direttamente da Windows, usando editor quali Visual Studio Code (VS Code).

L'estensione **Visual Studio Code Remote - WSL**, in particolare, permette di usare WSL come ambiente di sviluppo direttamente da VS Code.

> Prima di iniziare, assicurarsi di aver completato l'installazione di WSL.

### 1. Installare Visual Studio Code

Scarica e installa [VS Code](https://code.visualstudio.com/) su Windows

> **NON** installare VS Code nella distribuzione Linux in ambiente WSL.

Durante l'installazione assicurarsi di selezionare l'opzione "Add to PATH" così da poter aprire VS Code con il comando `code` da terminale.

### 2. Installare l'estensione [Remote Development](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.vscode-remote-extensionpack)

### 3. Aprire una cartella remota

Una volta configurato VS Code, sarà possibile aprire una cartella interna a WSL direttamente in VS Code.

1. Per prima cosa apri WSL (selezionando Ubuntu nel menù di start o lanciando `wsl` da Powershell)

1. Esegui il comando `code` da terminale.

Dopo qualche istante si aprirà una nuova finestra di VS Code, ed eseguirà l'installazione e la configurazione automaticamente. Una volta completato apparirà un nuovo indicatore nell'angolo in basso a sinistra, indicando la riuscita dell'operazione.

![WSL indicator in VS Code](https://code.visualstudio.com/assets/docs/remote/wsl/wsl-statusbar-indicator.png)

> Guarda la [documentazione ufficiale](https://code.visualstudio.com/docs/remote/wsl) per ulteriori dettagli.

## Passare file tra Windows e WSL

### Accedere a Windows file system da WSL

Da WSL è possibile accedere ai file presenti sulla propria macchina Windows tramite un Mount point.

Per farlo è sufficiente navigare su `/mnt/<Drive>` sostituendo a `<Drive>` la lettera corrispondente al disco da raggiungere.

Per esempio, per navigare nel disco `C:\` il comando da lanciare su WSL è:

```bash
$ cd /mnt/C/
```

A questo punto possono essere utili i comandi `cp` o `mv` per trasferire i file da e su WSL.

> Si raccomanda la massima attenzione quando si naviga nelle cartelle di sistema, per evitare di causare danni al sistema operativo Windows.

### Accedere al filesystem Linux da Windows

Il filesystem Linux è salvato in una posizione nascosta e non facilmente raggiungibile del sistema PER BUONE RAGIONI.

Il metodo di accesso ai file di un sistema NT (come Windows) è differente rispetto a sistemi Unix (come Linux) e accedere direttamente ai file salvati sulla distribuzione Linux da Windows causerebbe certamente danni al file stesso o peggio all'intero filesystem.

Per poter accedere/creare/modificare file presenti nel filesystem della distribuzione Linux da tool e applicazioni Windows, bisogna necessariamente passare da un Mount point.

Questo si trova in `\\wsl$\<Distro>` con `<Distro>` che corrisponde al nome della distribuzione di Linux scelta, che si può trovare come descritto nella sezione ['Cambiare la versione di WSL'](#cambiare-la-versione-di-wsl).

Per esempio, con una distribuzione Ubuntu, si può navigare nelle cartelle Linux semplicemente inserendo nella Barra degli Indirizzi di Esplora Risorse `\\wsl$\Ubuntu\` e da lì accedere alla propria home utente.

In alternativa è sufficiente lanciare il comando `explorer.exe` dalla bash di WSL, specificando in argomento la cartella in cui navigare.

```bash
$ explorer.exe /home/user/
```

Per esempio il comando sopra aprirà Esplora Risorse nella cartella home dell'utente user.

> Si può passare l'argomento `.`(punto) per aprire Esplora Risorse nella cartella WSL aperta in quel momento dalla command line
>
> ```bash
> $ explorer.exe .
> ```
>

A questo punto è possibile operare sui file in maniera usuale.

## Cambiare la versione di WSL

Nel caso in cui sia già stata installata una distribuzione Linux e vi sia intenzione di cambiare la versione di WSL per la specifica distribuzione, è possibile farlo da Powershell.

Aprire Powershell come amministratore.

Copiare ed eseguire il seguente comando:

``` Powershell
> wsl -l -v
```

per visualizzare la lista delle distribuzioni Linux installate sulla macchina e la versione di WSL in uso per ciascuna.

Eseguire il seguente comando:

``` Powershell
> wsl --set-version <DISTRO> <VERSION>
```

sostituendo `<Distro>` (compresi `<` e `>`) con il nome della distribuzione da modificare, come visualizzato nella lista precedente, e `<Version>` con 1 se si vuole passare a WSL 1 o 2 se si vuole passare a WSL 2.

Per esempio, se avessimo installato una distribuzione Ubuntu con WSL 1 e volessimo aggiornare a WSL 2 il comando da lanciare sarebbe:

``` Powershell
> wsl --set-version Ubuntu 2
```

> Si ricorda che per poter aggiornare a WSL 2 è necessario aver attivato la funzionalità aggiuntiva "Virtual Machine Platform" come spiegato nel punto 1 della guida.
