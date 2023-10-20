# Działanie 

![ezgif com-video-to-gif (1)](https://github.com/WojciechGos/przeszukiwanie-grafu-BFS/assets/36795978/154c1b4e-9b2c-4fb1-bd65-a8755d842aa7)

Plansza na środku przedstawia graf
Na dole w żółtych kwadratach znajduje się kolejka algorytmu BFS
Po prawej znajduję się kod, który przedstawia aktualnie wykonywaną linijkę kodu algorytmu BFS.


# Wstęp Teoretyczny

## Czym jest graf?

Graf jest modelem zbioru połączeń, przedstawiający relacje między obiektami,
składa się z wierzchołków oraz krawędzi. 


### Wierzchołki i Krawędzie

Wierzchołki grafu mogą być ponumerowane lub nazwane i czasem stanowia reprezentacje jakichś obiektów.
Krawędzie natomiast reprezentują relacje między takimi obiektami np.

![graf](https://github.com/WojciechGos/przeszukiwanie-grafu-BFS/assets/36795978/7a8ced37-3edf-494e-a573-ddd0fa678bed)


Jak widać Wierzchołki reprezentują miasta, natomiast krawędzie drogi między nimi.

## Przeszukiwanie grafu wszerz (BFS)

Algorytm BFS(ang. breadth-first search) odpowiada na dwa pytania:
- czy istnieje droga z wierzchołka A do B
- jaka jest najkrótsza droga z wierzchołka A do B

### Reprezentacja grafu w pamięci

graf w naszym programie jest reprezentowany za pomocą listy sąsiedztwa.
Lista ta przechowuje informacje o połączeniach z kolejnymi wierzchołkami.

![reprezentacja](https://github.com/WojciechGos/przeszukiwanie-grafu-BFS/assets/36795978/ed4c495a-6e01-47d7-a5dd-62e5d6fde15e)


W naszym wypadku najpierw stworzyliśmy liste wskaźników, które przechowywują wskaźnik na liste sąsiedztwa.

# Program

### siatka

Aby ułatwić sobie umieszczanie elementów na plaszy, powstała funkcja 
get_real_position_on_board(int position)
plansza posiada margines 150px oraz każdy punkt jed oddalony od siebie o 200px

![siatka](https://github.com/WojciechGos/przeszukiwanie-grafu-BFS/assets/36795978/406a2d11-25a0-434e-a857-9b906226ca14)


## Generowanie krawędzi grafu

### założenia:
- wszystkie krawędzię będą dwukierunkowe tzn. że jeśli istnieje krawędź z wierzchołka a do b to również istnieje krawędź z wierzchołka b do a.
- krawędź może zostać wygenerowane między najbliższymi sąsiadami wierzchołka
- losowanie krawędzi zaczynamy po kolei od pierwszego wierzchołka

### obserwacja 1
Skoro wszystkie krawędzie są dwukierunkowe oraz mają być generowane między najbliższym sąsiadem to istnieją maksymalnie 4 krawędzie warte rozpatrzenia.
Jeżeli za id wylosowanego wierzchołka uznamy x to jego najbliżsi sąsiedzi mają id odpowiednio x+1, x+6, x+7. x+8. 

![obserwacja](https://github.com/WojciechGos/przeszukiwanie-grafu-BFS/assets/36795978/083f29ab-fb84-4ff3-a89e-3f3812e85a94)

### obserwacja 2

Nie wszystkie wierzchołki mogą mieć 4 krawędzie do wylosowanie, aby zatem zydentyfikować je, należy zsumować jego najbliższych sąsiadów.

![grupy_wierzcholkow](https://github.com/WojciechGos/przeszukiwanie-grafu-BFS/assets/36795978/125b0dd7-0090-49ed-aca2-e2b77ebc54e1)

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
