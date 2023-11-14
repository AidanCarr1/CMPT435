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

    //Methods:
    //return int location of Vertex in Graph given string id
    int findVertexById(string target){
        
        //cout << "Size of Vertices vector: " << vertices.size() << endl; //test line
        for (int i = 0; i < vertices.size(); i++){
            //cout << "current vector id: " << vertices[i]->id << endl; //test line
            if (isEqual(target, vertices[i]->id)){
                return i;
            }
        }
        return -1;
    }

    //return true if no Vertices in vector
    bool isEmpty(){
        return vertices.empty();
    }

    //add vertex
    void addVertex(string id){
        Vertex* myVertex = new Vertex(id);
        //add new Vertex to the list
        vertices.push_back(myVertex);
    }
};


//Main Program!
//Read graphs file and interpret: make graphs, vertices, edges
int main() {

    //create graph
    Graph myGraph = Graph();

    //Open the file
    std::ifstream graphsFile;
    graphsFile.open(_FILE_NAME);

    string currentLine;
    if (graphsFile.is_open()){

        //go line by line in the file
        while (graphsFile){
            
            //get line as a string, and find length
            std::getline(graphsFile, currentLine); 
            int strLength = currentLine.length();

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
                
                //if there is a previous graph, process it
                if (! myGraph.isEmpty()){
                    //process graph
                    //delete graph
                }
            }

            //new vertex
            else if (currentLine.compare(4,6,"vertex") == 0){
                string id = currentLine.substr(11, 11-strLength);
                std::cout << id << endl; //test line
               
                //add vertex to graph by id
                myGraph.addVertex(id);

            }

            //new edge
            else if (currentLine.compare(4,4,"edge") == 0){
                //Watch out for error: if final line in file is edge, the edge will be repeated
                //cout << "Edge" << endl; //test line
                
                //find first and second id
                int dashIndex = currentLine.find("-");
                //cout << "Dash at: " << dashIndex << endl; //test line
                string id1 = currentLine.substr(9, dashIndex - 10);
                string id2 = currentLine.substr(dashIndex + 2, strLength);
                cout << "ID1: " << id1 << ". ID2: " << id2 << endl; //test line

                //ERROR
                int index1 = myGraph.findVertexById(id1);
                int index2 = myGraph.findVertexById(id2);
                cout << "Index: " << index1 << ", " << index2 << endl; //test line
                
                //create neighbors for both Vertices
                myGraph.vertices[index1]->addNeighbor(myGraph.vertices[index2]);
                myGraph.vertices[index2]->addNeighbor(myGraph.vertices[index1]);
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