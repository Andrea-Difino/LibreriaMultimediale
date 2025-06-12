# LibreriaMultimediale
Progetto di programmazione ad oggetti del secondo anno di Università. Laurea triennale in Informatica all'Università di Padova, A.A. 2024/2025.

## Descrizione
Libreria Multimediale è un gestionale che consente di aggiungere, modificare, cancellare e cercare i media presenti al suo interno. I contenuti gestibili sono di diversa natura: libri, film e musica, ciascuno caratterizzato da attributi specifici e da una propria modalità di visualizzazione.

<br/>

L'applicazione è dotata di un'interfaccia grafica moderna, progettata per essere \textbf{user-friendly}. Sono stati utilizzati contrasti visivi elevati per mettere in risalto sia i media che le principali funzionalità, come la cancellazione, la modifica e la visualizzazione dei contenuti.

Il motore di ricerca si basa su un algoritmo semplice, che utilizza il nome del media come chiave di ricerca. Per migliorarne l’efficacia, è stato integrato un sistema basilare di filtraggio che consente di selezionare gli elementi in base alla tipologia desiderata (libro, film o musica).

<br/>

L’impiego di diverse tipologie di media ha rappresentato inoltre un’ottima occasione per applicare il polimorfismo in maniera concreta e non banale, come richiesto dalle specifiche, consentendo di gestire ciascun tipo in modo modulare ma coerente.

## Tecnologie usate
* C++
* Qt
* JSON
<hr/>

## Istruzioni
Per compilare LibreriaMultimediale, clonare o scaricare questo repository, digita `qmake` e poi `make`:

```bash
 git clone https://github.com/Andrea-Difino/LibreriaMultimediale.git
 cd LibreriaMultimediale/LibreriaMultimediale/src
 qmake
 make
```

Assicurare di avere Qt, make e un compilatore C++ installati e disponibili nel tuo percorso.

Per eseguire l'applicazione, digita:

```bash
./LibreriaMultimediale
```