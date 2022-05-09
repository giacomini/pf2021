# Esempio di uso di CMake e SFML

L'esempio in questa cartella parte dalla classe `Chain` sviluppata nei laboratori [4](../../labs/lab4/) e
[5](../../labs/lab5/) e la utilizza per creare una rappresentazione visuale della simulazione.

## SFML

La parte grafica e' basata sulla libreria [SFML](https://sfml-dev.org/) (*Simple and Fast Multimedia Library*), che
offre, tra le varie funzionalita' disponibili, la possibilita' di creare, manipolare e visualizzare graficamente
figure bidimensionali.

Per usare SFML e' necessario installare alcune librerie. Su Ubuntu 20.04 e' sufficiente eseguire il comando `sudo apt
install libsfml-dev`.

Come anche descritto nel [tutorial](https://www.sfml-dev.org/tutorials/2.5/start-linux.php), un programma contenente
chiamate a funzionalita' SFML puo' essere compilato con `g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system`.
Naturalmente se il nostro programma contiene piu' file sorgente (.cpp), e' necessario e sufficiente elencarli tutti
quanti e non solo `main.cpp`. Notare che nel tutorial le chiamate al compilatore e al linker sono distinte, ma cio' non
e' strettamente necessario e si puo' quindi utilizzare il comando sopracitato.

## CMake

Le classi `Chain`, `Hooke` e `PPState` sono state suddivise in piu' file, sia header che di implementazione, cosi' da
avere piu' *translation unit* legate tra loro da dipendenze non ovvie. Il progetto include anche un file contenente
unit test. La presenza di vari eseguibili formati da vari sorgenti e' espressa utilizzando [CMake](https://cmake.org/),
un sistema di *build* che astrae i dettagli di quali comandi eseguire, con quali opzioni e in quale ordine per generare i
prodotti voluti (tipicamente dei binari, siano essi eseguibili e/o librerie).

L'uso di CMake o di strumenti analoghi (ce ne sono diversi) permette cioe' di gestire in modo sostenibile progetti che
contengono molti file. In particolare durante la fase di sviluppo, uno strumento come CMake e' indispensabile per
minimizzare le ri-compilazioni necessarie in caso di modifiche a file sorgente.

La descrizione dei *target* di un progetto avviene in un file chiamato `CMakeLists.txt`, secondo un linguaggio
specifico. Un target si puo' immaginare come un prodotto che vogliamo ottenere. Tipicamente per ogni target vengono
indicati il suo tipo (ad es. eseguibile o libreria), i file che concorrono alla sua produzione, le sue dipendenze,
nonche' altre informazioni utili.

Ad esempio, nel CMakeLists.txt di questo progetto, l'eseguibile principale e' specificato nel modo seguente:

```cmake
add_executable(chain-sfml main.cpp chain.cpp ppstate.cpp)
target_link_libraries(chain-sfml PRIVATE sfml-graphics)
```

il cui significato e':

* `chain-sfml` e' un eseguibile
* e' formato dai file sorgente `main.cpp`, `chain.cpp` e `ppstate.cpp`
* deve essere linkato con la libreria `sfml-graphics`

Da notare che non e' necessario specificare anche la dipendenza dalle librerie `sfml-window` e `sfml-system`, come fatto durante la compilazione manuale, perche' CMake e' in grado di determinarle automaticamente.

Il modo canonico di utilizzare CMake prevede due fasi:

* configurazione
* build

Durante la fase di configurazione viene creata (se non esiste gia') una directory di lavoro e vengono generati dei file con le istruzioni specifiche per produrre gli artefatti corrispondenti ai target. La configurazione fallisce se le direttive incontrate nel `CMakeLists.txt` contengono degli errori.

Tipicamente la configurazione avviene con un comando come il seguente, dato dalla *root* directory del progetto, quella
cioe' in cui sta il file `CMakeLists.txt`:

```shell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
```

il cui significato e':

* la root directory e' questa (`-S .`)
* la directory di lavoro e' `build` (`-B build`)
* produci istruzioni per produrre eseguibili con incorporate informazioni di debug (`-DCMAKE_BUILD_TYPE=Debug`)

In genere il tipo di build e' di debug solo durante sviluppo e test; nel momento in cui si vuole invece produrre l'eseguibile da utilizzare *in produzione* si usa il tipo di build chiamato *Release*, usando l'opzione `-DCMAKE_BUILD_TYPE=Release`.

Notare che si possono specificare directory di lavoro diverse per i vari tipi di build.

Durante la fase di build vengono invece eseguite le istruzioni generate nella fase precedente. Il comando tipico utilizzato e' il seguente:

```shell
cmake --build build
```

il cui significato e': esegui il target di default delle istruzioni di build (`--build`) contenute nella directory `build`. Il target di default fa il build di tutti i target specificati.

Se il `CMakeLists.txt` contiene anche direttive per i test (e questo progetto le prevede), CMake consente anche di eseguire i test, usando il comando:

```shell
cmake --build build --target test
```

In quest'ultimo comando abbiamo specificato esplicitamente che vogliamo eseguire il target `test` (che si puo'
considerare come una specie di target virtuale, non associato a un prodotto vero e proprio), a partire dalle istruzioni
di build contenute nella directory `build`.

**NB** Nel caso di modifiche ai file sorgente, non e' necessario ri-configurare la directory di lavoro (`cmake -S . -B
build ...`), anzi e' sconsigliato perche' e' una perdita di tempo; e' sufficiente ri-buildare (`cmake --build build`) e
ri-testare (`cmake --build build --target test`). Cio' non toglie che se la directory di lavoro per qualche motivo
appare corrotta, si puo' tranquillamente rimuovere (`rm -rf build`) e ripartire da capo.

### CMake e Visual Studio Code

VSCode offre un esteso supporto per l'uso di CMake. Raccomandiamo di installare l'estensione [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools), che e' comunque compresa nel [C/C++ Extension Pack](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools-extension-pack).