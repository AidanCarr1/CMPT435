// Aidan Carr
// December 1, 2023
// SSSP: Directed Graphs

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
using namespace std;


//GLOBAL variables
const string _FILE_NAME = "graphs2.txt";
const int _INFINITY = 1000000007; 


//Compare 2 strings for equality
bool isEqual(string first, string second){

    //find correct length to avoid out of bounds error when comparing
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

    //if the two words have passed, they ARE equal
    return true;
}


//VERTEX CLASS
class Vertex {

public:
    string id;
    bool isProcessed;
    vector<Vertex*> neighbors; //array of neighbors

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


//EDGE CLASS
class Edge {

public:
    //this makes the Graph directed
    Vertex* from;
    Vertex* to;
    int weight;

    //Constructor
    Edge(Vertex* fromInput, Vertex* toInput, int weightInput){
        from = fromInput;
        to = toInput;
        weight = weightInput;
    }
};


//Direected GRAPH CLASS
class Graph {

public:
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    
    //constructor
    Graph(){
    }    

    //METHODS:
    //return int location of Vertex in Graph given string id
    int findVertexById(string target){
        
        //traverse the vector of Vertices
        for (int i = 0; i < vertices.size(); i++){
            if (isEqual(target, vertices[i]->id)){
                //return index
                return i;
            }
        }
        return -1;
    }

    //return true if no Vertices in vector
    bool isEmpty(){
        return vertices.empty();
    }

    //add Vertex
    void addVertex(string id){
        Vertex* myVertex = new Vertex(id);
        //add new Vertex to the list
        vertices.push_back(myVertex);
    }

    //add Edge
    void addEdge(int index1, int index2, int weight){
        //only add edge if the Vertices exist in vertices vector
        if (index1 != -1 && index2 != -1){
            vertices[index1]->addNeighbor(vertices[index2]);
            Edge* myEdge = new Edge(vertices[index1], vertices[index2], weight);
            edges.push_back(myEdge);
        }
    }

    //test line
    //method not needed
    //adjacency list
    void printAsAdjacencyList(){
        int size = vertices.size();
    
        std::cout << "\nGRAPH AS AN ADJACENCY LIST:\n" << std::endl;

        for (int i = 0; i < size; i++){
            //print line title
            std::cout << "[" << vertices[i]->id << "]";
            
            //search and print i's neighbors
            for (int j = 0; j < vertices[i]->neighbors.size(); j++){
                std::cout << " " << vertices[i]->neighbors[j]->id;
            }
            std::cout << std::endl;
        }
    }

    //delete all Graph contents
    void reset(){
        //delete each Vertex
        for (int i = 0; i < vertices.size(); i++){
            delete vertices[i];
        }
        //reset the Vertices vector
        vertices.clear();

        //delete each Edge
        for (int i = 0; i < edges.size(); i++){
            delete edges[i];
        }
        //reset the Edges vector
        edges.clear();
    }
};


//Main Program!
//Read the file,

int main(){

    //create Graph object (will be reused for all Graphs)
    Graph myGraph = Graph();

    //open the file
    std::ifstream graphsFile;
    graphsFile.open(_FILE_NAME);
    
    //create vector
    int fileLength = 0;
    vector<string> fileCommands;

    string currentLine;
    if (graphsFile.is_open()){

        //read the file into a vector
        while (graphsFile){
            //insert commands into vector
            std::getline(graphsFile, currentLine); 
            fileCommands.push_back(currentLine);
            fileLength++;
        }

        //IO duplicates final line, delete it
        fileCommands.pop_back(); 
        //print out final graph
        fileCommands.push_back("new graph");
    }    
    else {}
    graphsFile.close();   

    /* //test lines
    for(int i = 0; i < fileCommands.size(); i++){
        std::cout << fileCommands[i] << endl;
    }
    //*/


    //INTERPRET ALL COMMANDS
    for(int line = 0; line < fileLength; line ++){

        //get line as a string, and find length
        string currentLine = fileCommands[line]; 
        int strLength = currentLine.length();

        //empty line, ignore line
        if (currentLine.compare(0,1,"") == 0){
        }

        //comment, ignore line
        else if (currentLine.compare(0,2,"--") == 0){
        }

        //new Graph
        else if (currentLine.compare(0,3,"new") == 0){
            
            //if there is a previous Graph, process it
            if (! myGraph.isEmpty()){
                
                //process Graph
                myGraph.printAsAdjacencyList(); //test line

                //reset Graph object (+ Vector objects and Edge objects)
                myGraph.reset();

            }
        }

        //new Vertex
        else if (currentLine.compare(4,6,"vertex") == 0){
            string id = currentLine.substr(11, 11-strLength);
            
            //add Vertex to Graph by id
            myGraph.addVertex(id);

        }

        //new edge
        else if (currentLine.compare(4,4,"edge") == 0){
            
            //find first id
            int dashIndex = currentLine.find("-");
            string id1 = currentLine.substr(9, dashIndex - 10);
            
            //find second id
            int id2strLength = currentLine.substr(dashIndex+2, strLength-dashIndex-2).find(" ");
            string id2 = currentLine.substr(dashIndex+2, id2strLength);

            //find weight
            int weightIndex = dashIndex+2+id2strLength;
            string weightStr = currentLine.substr(weightIndex, strLength - weightIndex);
            int weight = std::stof(weightStr);

            //find index of each id
            int index1 = myGraph.findVertexById(id1);
            int index2 = myGraph.findVertexById(id2);
            
            //add edge in the graph using the Vertex indexes
            myGraph.addEdge(index1, index2, weight);
        }

        //error check
        //line in file doesn't follow my rules: tell the world, skip it, keep going
        else {
            std::cout << "ERROR on line " << line+1 << ":\n\t'" << currentLine << "'" << std::endl;
        }
    }
}