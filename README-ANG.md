# Action 

![ezgif com-video-to-gif (1)](https://github.com/WojciechGos/przeszukiwanie-grafu-BFS/assets/36795978/154c1b4e-9b2c-4fb1-bd65-a8755d842aa7)

The board in the middle shows the graph.  
At the bottom in the yellow squares is the queue of the BFS algorithm.  
On the right is the code, which represents the currently executed line of code of the BFS algorithm.  


# Theoretical Introduction

## What is a graph?

A graph is a model of a set of connections, representing relationships between objects,
It consists of vertices and edges. 


### Vertices and Edges.

The vertices of a graph can be numbered or named and sometimes represent some objects.
Edges, on the other hand, represent relationships between such objects, e.g.

![graph](graph.png)


As you can see, the vertices represent the cities, while the edges represent the roads between them.

## Breadth-first search (BFS) of a graph.

The BFS(breadth-first search) algorithm answers two questions:
- whether there is a path from vertex A to B
- what is the shortest path from vertex A to B

### Representation of a graph in memory

The graph in our program is represented using a neighborhood list.
This list stores information about connections to consecutive vertices.

![representation_graph](representation.png)

In our case, we first created a pointer list that stores a pointer to the neighborhood list.


# program


### grid


To make it easier to place elements on the platter, a function was created 
get_real_position_on_board(int position)The board has a margin of 150px and each point jed 200px away from each other


![grid](grid.png)




## Generate the edges of the graph


### assumptions:- all edges will be bidirectional i.e. if there is an edge from vertex a to b then there is also an edge from vertex b to a.
- an edge can be generated between the nearest neighbors of a vertex
- we start drawing edges one by one from the first vertex


### observation 1
Since all edges are bidirectional and are to be generated between nearest neighbor then there are at most 4 edges worth considering.
If we take x as the id of the drawn vertex then its nearest neighbors have id of x+1, x+6, x+7. x+8 respectively. 


![observation](observation.png)### observation 2


Not all vertices can have 4 edges to draw, so in order to zdentify it, its nearest neighbors must be summed.


![vertex groups](groups_vertices.png)


From this it follows that the sum of the id of the vertices of group:
- left is 16- middle is 22
- right is 13
- bottom is 1


### Drawing


The draw consists of: 
 - drawing a vertex
 - identifying to which group it belongs
 - on the basis of the group to retrieve the list, which includes the id of the vertices
