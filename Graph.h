#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cctype>
#include <list>
#include <iterator>
#include <random>
#include <ostream>
#include <ctime>
#include <algorithm>
#include <climits>



#define NL putchar('\n'); // returns "\n"
#define FIND(l,n) std::find(l.begin(), l.end(), n) != l.end()
#define V1 (int)it.Get(1)
#define V2 (int)it.Get(2)
#define LEN (int)it.Get(3)
#define MAX 32767



using namespace std;




int isdigit(const string&); // Overloaded function isdigit() for string values
ostream& operator<<(ostream&, const list<int>&); // Overloaded output for integer elements list



class Edge { // Edge contains two vertexes v1 and v2, and length between them;
private:
    int v1;
    int v2;
    int length;
public:
    Edge(int, int, int); // Constructor for Edge
    void Change(int,int,int); // Change the private data values
    int Get(int) const; // Get a private data value; v1 - 1, v2 - 2, length - 3
    friend bool operator<(Edge&, Edge&); // Length comparison
    friend bool operator==(Edge&, Edge&); // Length comparison
    friend bool vert_inq(Edge&, Edge&); // Compares Edge vertexes on inequality
    friend ostream& operator<<(ostream&, const Edge&); // Overloaded output for Edge
    friend ostream& operator<<(ostream&, const list<Edge>&); // Overloaded output for Edge elements list
};





class Graph { // Graph contains List of Vertexes and Edges
private:
    list<int> Vert;
    list<Edge> El;
public:
    Graph(); // Constructor for getting the Input Data
    list<int>& Get_V(); // Get List of Vertexes
    list<Edge>& Get_E(); // Get List of Edges
    static void Del_El(list<Edge>&, list<Edge>::iterator &); // Deletes the same elements in list
    list<int>::iterator Rand_V(); // Returns a Random vertex
    int Vert_Degree(int); // Returns the value of Vertex Degree
    void FloydAlg(int**); // Floyd Algorithm
    int *Radius(); // Graph's Radius
    int *Diameter(); // Graph's Diameter
    static bool Is_Bridge(list<Edge>&, int); // Returns true if Edge is the Bridge, false if it is not
    bool FleuryAlg(list<Edge>&, list<int>&, int, int); // Fleury Algorithm for Eulerian Cycle; Recursive method
    string Is_Eulerian(int); // Checks Graph is Eulerian; returns 0 if None; returns 1 if Eulerian; returns 2 if Half Eulerian
    string Is_Hamiltonian(int); // Checks Graph is Hamiltonian; returns 0 if None; returns 1 if Hamiltonian; returns 2 if Half Hamiltonian
    void Depth_FS(list<int> &, int);
    void Rec_Call(bool, int, list<int>&); // Function for calling recursive function DFS
    void Keys(); // Asks a Keys
};


#endif // GRAPH_H
