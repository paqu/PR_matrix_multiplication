# PR_matrix_multiplication
### projekt zaliczeniowy


## LINK DO TRAVIS BUILD
https://travis-ci.org/paqu/PR_matrix_multiplication/builds 

## ZADANIE

Mnożenie macierzy - porównanie efektywności metod:
- 3 pętle - kolejność pętli: jki (szeregowanie statyczne blokowe i
  cykliczne), równoległość i podział pracy na poziomie pętli zew.
- 6 pętli - kolejność pętli: jki

## WYMAGANIA

1. Analiza zadania pod kontem poprawności i efektywności przetwarzania.
2. Określenie warunków efektywności – lokalności przetwarzania i wielkości
   testowanych instancji (dla wersji sekwencyjnej i równoległej)
3. Przygotowanie kodów programów.
4. Uruchomienie przetwarzania sekwencyjnego i równoległego.
5. Wyznaczenie miar efektywności przetwarzania dla określonych (wg analizy
   efektywnościowej) instancji, parametrów metody i liczby procesorów (1,
   maksimum, połowa maksymalnej, procesory fizyczne):
  * Czas przetwarzania [sekundu]
  * Prędkość przetwarzania [Mflops]
  * Przyspieszenie i efektywność jako miary efektywności przetwarzania
    równoległego implementowanych metod równoległych.
  * Efektywność przetwarzania   funkcji nominalnej mocy procesora MFlops/W
    TDP (ang. Thermal Design Power) i kosztu (mierzonego powierzchnią krzemu
    wykorzystywanego układu scalonego) MFlops/mm2
6. Uwagi do eksperymentu:
  * wyznaczenie najlepszego czasu przetwarzania dla obliczeń sekwencyjnych
    (optymalizowana wersja kodu opcja Release kompilatora) – czasu będącego
    punktem  odniesienia dla obliczeń  przyspieszenia i efektywności w funkcji
    liczby
7. Sprawozdanie zawierać powinno:
  * Opis metody w kontekście:
    *  lokalności czasowej przetwarzania sekwencyjnego (dostęp do danych
       dostępnych w pamięci podręcznej)
    * lokalności przestrzennej przetwarzania sekwencyjnego (zakres
      wykorzystywanych 4kB stron pamięci wirtualnej)
    * podział pracy na wątki, określenie który wątek jakie wyniki generuje i z
      jakich danych korzysta
    * ocena synchronizacji przetwarzania wątków i kosztów zrównoleglenia
      poprawności przetwarzania równoległego
    * wpływ przetwarzania równoległego na lokalność czasową i przestrzenną.
8. Wymagana jest wersja sprawozdania elektroniczna. ma zawierać kluczowe
   fragmenty kodu sekwencyjnego i równoległego

