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
const string _FILE_NAME = "graphs0.txt";
const int _LINES_IN_FILE = 375; //number of lines in graphs1.txt



//Compare 2 strings for equality
bool isEqual(string first, string second){

    //find correct length to avoid out of bound error when comparing
    //different lengths means definetly not equal
    int length1 = first.length();
    int length2 = second.length();
    if (length1 != length2){
        return false;
    }

    //compare letter by letter until an unequal character string is found
    for (int i = 0; i < length1; i++){
        if (first.at(i) != second.at(i)){
            return false;
        }
    }

    //if the two words have passed, its equal
    return true;
}


//Vertex class
class Vertex {

public:
    string id;
    bool isProcessed;
    vector<Vertex*> neighbors; //array of neightbors

    //Constructor
    Vertex(string idInput){
        id = idInput;
        isProcessed = false;
    }

    //add a vertex neighbor
    void addNeighbor(Vertex* newNeighbor){
        neighbors.push_back(newNeighbor);
    }
};


class Graph {

public:
    vector<Vertex*> vertices;
    
    //Constructor
    Graph(){
    }    

    //Method:
    int findVertexById(string target){
        for (int i = 0; i < vertices.size(); i++){
            if (isEqual(target, vertices[i]->id)){
                return i;
            }
        }
    }
};


//Main Program!
//Read graphs file and interpret: make graphs, vertices, edges
int main() {

    //Open the file
    std::ifstream graphsFile;
    graphsFile.open(_FILE_NAME);

    string currentLine;
    if (graphsFile.is_open()){

        //go line by line in the file
        while (graphsFile){

            //get line as a string
            std::getline(graphsFile, currentLine); 
            //std::cout << currentLine << endl; //test line

            //empty line, ignore line
            if (currentLine.compare(0,1,"") == 0){
                //std::cout << "empty line" << endl; //test line
            }

            //comment, ignore line
            else if (currentLine.compare(0,2,"--") == 0){
                //std::cout << "comment" << endl; //test line
            }

            //new graph
            else if (currentLine.compare(0,3,"new") == 0){
                //std::cout << "NEW graph" << endl;
                //if first graph, create graph
                Graph myGraph = Graph();
                //process the previous graph (if previous exists)
                //delete graph
            }

            //new vertex
            else if (currentLine.compare(4,6,"vertex") == 0){
                int strLength = currentLine.length();
                string id = currentLine.substr(11,11-strLength);
                std::cout << id << endl; //test line

                //create vertex object
                Vertex myVertex = Vertex(id);
                
                //BOOKMARK HERE
                //add vertex to graph
                myGraph.addVertex(id);

            }

            //new edge
            else if (currentLine.compare(4,4,"edge") == 0){
                //create neighbor for first vertex
                //create neighbor for second vertex
            }

            else {
                std::cout << "ERROR!\n";
                std::cout << currentLine << "\n" << std::endl;
            }
        }
    }
    else {}
    graphsFile.close();
}