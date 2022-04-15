
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

### siatka

Aby ułatwić sobie umieszczanie elementów na plaszy, powstała funkcja 
get_real_position_on_board(int position)


![siatka](siatka.png)


## Generowanie krawędzi grafu

### założenia:
- wszystkie krawędzię będą dwukierunkowe tzn. że jeśli istnieje krawędź z wierzchołka a do b to również istnieje krawędź z wierzchołka b do a.
- krawędź może zostać wygenerowane między najbliższymi sąsiadami wierzchołka

### obserwacja

![obserwacja](obserwacja.png)
















