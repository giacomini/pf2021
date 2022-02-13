# Esercizi

1. Scrivi un programma che legge tre numeri dallo standard input e scrive il più piccolo sullo standard output.

1. Scrivi un programma che legge un numero arbitrario di numeri dallo standard input e scrive il più piccolo sullo standard output.

    Suggerimento 1: Premi Ctrl-D per dire al programma che non c'è più niente da leggere dallo standard input.

    Suggerimento 2. L'espressione `std::cin.good()` indica se è ancora possibile leggere qualcosa dallo standard input.

1. Scrivi una funzione `pow` che prende due `int` e calcola e ritorna il valore del primo (la base) elevato al secondo (l'esponente).

1. Scrivi una funzione `gcd` che prende due `int` e calcola e ritorna il massimo comune divisore tra i due numeri usando l'algoritmo di Euclide

    Variante 1. Implementa la funzione in forma iterativa.

    Variante 2. Implementa la funzione in forma ricorsiva.

1. Scrivi una funzione `lcm` che prende due `int` e calcola e ritorna il minimo comune multiplo tra i due numeri.

1. Scrivi una funzione `is_prime` che prende un `int` e indica se il numero è primo.

1. Scrivi una funzione che calcola la soluzione di un'equazione di primo grado
   <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large a \, x %2B b = 0"> , dati i due coefficienti.

1. Calcola perimetro, area, volume, ecc. di figure geometriche bidimensionali e tridimensionali, dati i loro parametri.

1. Scrivi una funzione che ha come parametro un `char` e ritorna la corrispondente lettera minuscola se è una lettera, lo stesso carattere altrimenti.

    Ad esempio `A` &#8594; `a`, `a` &#8594; `a`, `;` &#8594; `;`

1. Scrivi una funzione `compute` che prende due operandi numerici di tipo `double` e un operatore di tipo `char` e ritorna il risultato ottenuto applicando l'operatore ai due operandi.

    Ad esempio, se i due operandi hanno valore `2.0` e `3.5` e l'operatore è `+`, allora la funzione ritorna `5.5`.

    Variante 1. Se l'operatore o uno degli operandi ha un valore invalido, la funzione ritorna `0.`.

    Variante 2. Se l'operatore o uno degli operandi ha un valore invalido, la funzione solleva un'eccezione di tipo `std::runtime_error` con un messaggio d'errore appropriato.

    Variante 3. Se l'operatore o uno degli operandi ha un valore invalido, la funzione solleva un'eccezione di una classe da definire. Tale classe ha costruttori e metodi che permettono di passare al chiamante di `compute` le informazioni relative all'operatore o agli operandi invalidi.

    Variante 4. Indicare con `assert` espressioni che indichino la validità di operatore e operandi.

1. Scrivi un programma che permette all'utente di inserire semplici  espressioni aritmetiche (ad es. `1 + 2` o anche in _notazione polacca inversa_ `+ 1 2`) da passare alla funzione `compute`, di cui al punto precedente. Verifica il comportamento diverso delle quattro varianti.

1. Scrivi una classe `Complex`, completa di operatori di confronto, addizione, sottrazione, moltiplicazione, divisione e di metodi/funzioni per norma e radice quadrata.

    Variante 1. La rappresentazione interna è in forma cartesiana.

    Variante 2. La rappresentazione interna è in forma polare.

1. Scrivi una funzione che calcola le soluzioni di un'equazione di secondo grado <img src="https://render.githubusercontent.com/render/math?math=\color{RoyalBlue} \large a \, x^{2} %2B  b \, x %2B c = 0"> , dati i tre coefficienti.

    Suggerimento: Il tipo ritornato può essere una `struct` (da definire) contenente due `Complex`.

Ricordarsi di scrivere i test, usando ad esempio [doctest](https://github.com/doctest/doctest).
