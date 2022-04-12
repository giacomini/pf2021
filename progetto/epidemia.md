# Simulazione dell'evoluzione di un'epidemia

## Descrizione del problema

Esiste un semplice modello teorico per descrivere la diffusione di un'epidemia
all'interno di una popolazione chiusa. Il modello è detto SIR dalle iniziali di

- *Suscettibili*: le persone che si possono infettare
- *Infetti*: le persone infette e che possono infettare
- *Rimossi*: le persone guarite, decedute o in isolamento, che non possono più
  né infettarsi né infettare

Lo stato di una persona può andare in una direzione sola, prima da *S* a *I* e
poi da *I* a *R*.

Il modello esposto è per forza di cose semplificato, ma aiuta a cogliere
l'andamento reale di un'epidemia.

## Il modello SIR

Il modello si basa su tre equazioni differenziali

$$
\frac{dS}{dt} = -\beta \frac{S}{N} I \\[3mm]
\frac{dI}{dt} = \beta \frac{S}{N} I - \gamma I \\[3mm]
\frac{dR}{dt} = \gamma I
$$

da cui si ricava che $S + I + R = N$, con $N$ costante, il numero
totale di persone nella popolazione.

Il modello ha due parametri:

- $\beta \in [0,1]$ è una misura della probabilità di contagio in seguito a contatti
  tra infetti e suscettibili
- $\gamma \in [0,1]$ è la probabilità di guarigione (o morte) di un infetto ed è
  l'inverso del tempo medio di risoluzione dell'infezione

I parametri $\beta$ e $\gamma$ nel modello sono costanti, ma nella realtà
sono tipicamente variabili e dipendono ad esempio dalle misure di mitigazione
messe in atto.

Notate come $dI/dt > 0$, cioè l'epidemia è in espansione, se $\beta S/N >
\gamma$, cioè se $S/N > \gamma / \beta$; l'epidemia è in contrazione nel
caso opposto. In altre parole, quando il numero di suscettibili rispetto al
totale della popolazione supera la soglia $\gamma / \beta$ il numero di
infetti comincerà a calare. In particolare, al tempo $t=0$, quando $S
\approx N$, l'epidemia partirà se $R_0 = \beta / \gamma > 1$

Discretizzando le equazioni differenziali citate sopra e considerando $\Delta T
= 1$, abbiamo

$$
S_i = S_{i-1} - \beta \frac{S_{i-1}}{N} I_{i-1} \\[3mm]
I_i = I_{i-1} + \beta \frac{S_{i-1}}{N} I_{i-1} - \gamma I_{i-1} \\[3mm]
R_i = R_{i-1} + \gamma I_{i-1}
$$

con i vincoli

$$
S + I + R = N \\[3mm]
S, I, R \in \N
$$

## Parte I: implementazione del modello SIR

La prima parte del progetto è obbligatoria e consiste nell'implementazione del
modello SIR descritto sopra, calcolando i valori di S, I e R al variare del tempo.

L'input del programma è costituito dai parametri del modello $\beta$ e
$\gamma$, dai valori iniziali di S, I e R e dalla durata in giorni della
simulazione $T$. I parametri vanno presi o da standard input o da riga di
comando.

L'output del programma è costituito da una tabulazione dei valori di S, I e R
su standard output. In aggiunta è possibile utilizzare SFML (o altro sistema
grafico, purché disponibile sulla piattaforma di riferimento Ubuntu 20.04) per
la rappresentazione grafica dell'andamento delle tre variabili.

## Parte II: simulazione tramite automa cellulare

La seconda parte del progetto è facoltativa e consiste nell'implementazione
della simulazione della pandemia tramite automa cellulare: ogni membro della
popolazione è rappresentato come una cella su una griglia bidimensionale e può
assumere valori diversi. La griglia può poi evolvere secondo alcune semplici
regole di infezione e guarigione, a intervalli di tempo discreti.

Ogni cella in questo caso può essere in uno degli stati S, I o R (o vuota). Come
nel modello SIR, una cella S può diventare I e una cella I può diventare R. Il
passaggio da S a I avviene in base a una certa probabilità $\beta$ combinata
opportunamente con il numero di vicini infetti. Il passaggio da I a R avviene in
base a una certa probabilità $\gamma$. Per la gestione dei numeri casuali
usate la libreria standard `<random>`.

Come nella [parte I](#parte-i-implementazione-del-modello-sir), l'input del
programma è costituito almeno dalla durata in giorni della simulazione $T$ e
dai parametri di probabilità $\beta$ e $\gamma$. I parametri vanno presi o
da standard input o da riga di comando. Parametri aggiuntivi possono essere
richiesti per determinare la configurazione iniziale.

L'output del programma è costituito dalla rappresentazione della griglia
istante dopo istante, accompagnata dai valori di S, I e R. E' possibile
utilizzare SFML (o altro sistema grafico, purché disponibile sulla piattaforma
di riferimento Ubuntu 20.04) per la rappresentazione grafica.

## Variazioni sul tema

Per entrambe le parti è possibile introdurre ulteriori elementi per rendere
più elaborato il modello. A titolo di esempio:

- introdurre misure di mitigazione durante il corso dell'epidemia (quarantena,
  vaccinazioni, lockdown, ...)

- introdurre la possibilità che le persone si spostino sulla griglia
  dell'automa cellulare

- ...
