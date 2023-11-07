// Aidan Carr
// November 6, 2023
// Undirected Graphs

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
using namespace std;


//GLOBAL variables
const string _FILE_NAME = "graphs1.txt";
const int _LINES_IN_FILE = 375; //number of lines in graphs1.txt



//Node class of BST, 2 children, 1 parent
class Vertex {

public:
    int id;
    vector<Vertex*> neighbors; //array of neightbors

    //Constructor
    Vertex(int idInput){
        id = idInput;
    }

    //add a vertex neighbor
    void addNeighbor(Vertex* newNeighbor){
        neighbors.push_back(newNeighbor);
    }
};