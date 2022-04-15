
# Wstęp Teoretyczny

## Czym jest graf?

Graf jest modelem zbioru połączeń, przedstawiający relacje między obiektami,
składa się z wierzchołków oraz krawędzi. 


### Wierzchołki i Krawędzie

Wierzchołki grafu mogą być ponumerowane lub nazwane i czasem stanowia reprezentacje jakichś obiektów.
Krawędzie natomiast reprezentują relacje między takimi obiektami np.

![graf](graf.png)


Jak widać Wierzchołki reprezentują miasta, natomiast krawędzie drogi między nimi.

## Przeszukiwanie grafu wszerz (BFS)

Algorytm BFS(ang. breadth-first search) odpowiada na dwa pytania:
- czy istnieje droga z wierzchołka A do B
- jaka jest najkrótsza droga z wierzchołka A do B

### Reprezentacja grafu w pamięci

graf w naszym programie jest reprezentowany za pomocą listy sąsiedztwa.
Lista ta przechowuje informacje o połączeniach z kolejnymi wierzchołkami.

![reprezentacja_grafu](reprezentacja.png)

W naszym wypadku najpierw stworzyliśmy liste wskaźników, które przechowywują wskaźnik na liste sąsiedztwa.

# Program

### siatka

Aby ułatwić sobie umieszczanie elementów na plaszy, powstała funkcja 
get_real_position_on_board(int position)
plansza posiada margines 150px oraz każdy punkt jed oddalony od siebie o 200px

![siatka](siatka.png)


## Generowanie krawędzi grafu

### założenia:
- wszystkie krawędzię będą dwukierunkowe tzn. że jeśli istnieje krawędź z wierzchołka a do b to również istnieje krawędź z wierzchołka b do a.
- krawędź może zostać wygenerowane między najbliższymi sąsiadami wierzchołka
- losowanie krawędzi zaczynamy po kolei od pierwszego wierzchołka

### obserwacja 1
Skoro wszystkie krawędzie są dwukierunkowe oraz mają być generowane między najbliższym sąsiadem to istnieją maksymalnie 4 krawędzie warte rozpatrzenia.
Jeżeli za id wylosowanego wierzchołka uznamy x to jego najbliżsi sąsiedzi mają id odpowiednio x+1, x+6, x+7. x+8. 
![obserwacja](obserwacja.png)

### obserwacja 2

Nie wszystkie wierzchołki mogą mieć 4 krawędzie do wylosowanie, aby zatem zydentyfikować je, należy zsumować jego najbliższych sąsiadów.

![grupy wierzchołków](grupy_wierzcholkow.png)

Z tego wynika że suma id wierzchołków grupy:
- lewa wynosi 16
- środkowej wynosi 22
- prawej wynosi prawej wynosi 13
- dolnej wynosi 1

### Losowanie

Losowanie polega na: 
 - wylosowaniu wierzchołka
 - identyfikacji do jakiej grupy należy
 - na podstawie grupy pobrać liste, w której znajdują się id wierzchołków 
