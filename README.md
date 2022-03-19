# przeszukiwanie-grafu-BFS
projekt na zaliczenie przedmiotu "Algorytmy i struktury danych"


# Wstęp Teoretyczny

### Czym jest graf?

Graf jest modelem zbioru połączeń, przedstawiający relacje między obiektami,
składa się z wierzchołków oraz krawędzi. 


#### Wierzchołki i Krawędzie

Wierzchołki grafu mogą być ponumerowane lub nazwane i czasem stanowia reprezentacje jakichś obiektów.
Krawędzie natomiast reprezentują relacje między takimi obiektami np.

![image](https://user-images.githubusercontent.com/36795978/159125247-8e63bc9a-7be8-4bb9-8ae8-cdfe44aefbf1.png)

Jak widać Wierzchołki reprezentują miasta, natomiast krawędzie drogi między nimi.

### Przeszukiwanie grafu wszerz (BFS)

Algorytm BFS(ang. breadth-first search) odpowiada na dwa pytania:
- czy istnieje droga z wierzchołka A do B
- jaka jest najkrótsza droga z wierzchołka A do B

#### Jak sprawdzić czy istnieje droga z Krakowa do Warszawy?

Przez kolor czerwony oznaczamy obecnie sprawdzane miasto,
przez kolor żółty miasta, które znajdują się w kolejce do sprawdzenia,
przez kolor czarny miasta przetworzone.

Na początku dodajemy wszystkie sąsiednie wierzchołki miasta Kraków do kolejki.

![image](https://user-images.githubusercontent.com/36795978/159125961-34d1dddc-7a6f-4ef3-8fcc-17eeadc7973d.png)










