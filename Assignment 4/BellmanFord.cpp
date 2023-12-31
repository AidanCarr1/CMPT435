// Aidan Carr
// December 4, 2023
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
const string FILE_NAME = "graphs2.txt";
const int ALMOST_INFINITY = 100000000; 


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
    
    //for Bellman-Ford:
    int distance;
    Vertex* predecessor;

    //Constructor
    Vertex(string idInput){
        id = idInput;
        isProcessed = false;
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


//NODE CLASS, used in Stack class
class Node {

public:
    Vertex* content;
    Node* next;

    //Constructors
    Node(Vertex* input){
        content = input;
        next = nullptr;
    }
};


//STACK CLASS
class Stack{

public:
    Node* top;

    //Constructor
    Stack(){
        top = nullptr;
    }

    //METHODS
    //return true if Empty
    bool isEmpty(){
        if (top == nullptr){
            return true;
        }
        return false;
    }

    //push a Vertex to the top
    void push(Vertex* newVertexTop){
        Node* myNode = new Node(newVertexTop);
        push(myNode);
    }
    //push a Node to the top
    void push(Node* newTop){
        newTop->next = top;
        top = newTop;
    }

    //retrieve from the top
    void pop(){
        //can only pop if there is something there
        if (! isEmpty()){
            string popping = top->content->id;
            top = top->next;
            std::cout << popping;
        }
    }
};


//Directed GRAPH CLASS
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
            Edge* myEdge = new Edge(vertices[index1], vertices[index2], weight);
            edges.push_back(myEdge);
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


    //Bellman-Ford Algorithm
    bool bellmanFord(int sourceVectorIndex){

        //INIT-SINGLE SOURCE
        //for every Vertex...
        for (int v = 0; v < vertices.size(); v++){
            vertices[v]->distance = ALMOST_INFINITY;
            vertices[v]->predecessor = nullptr;
        }
        //distance from start to yourself = 0
        vertices[sourceVectorIndex]->distance = 0;

        //loop through all Vertices
        for (int i = 1; i < vertices.size(); i++){
            
            //loop through all Edges
            for(int e = 0; e < edges.size(); e++){

                //variables for RELAX
                Vertex* fromU = edges[e]->from;
                Vertex* toV = edges[e]->to;
                int weight = edges[e]->weight;

                //RELAX
                //if previously defined distance > new found distance, appoint new path
                if (toV->distance > fromU->distance + weight){
                    toV->distance = fromU->distance + weight;
                    toV->predecessor = fromU;
                }
            }
        }

        //loop through Edges to check for negative weight cycles
        for(int e = 0; e < edges.size(); e++){
            
            //variables for negative weight cycle check
            Vertex* fromU = edges[e]->from;
            Vertex* toV = edges[e]->to;
            int weight = edges[e]->weight;

            if (toV->distance > fromU->distance + weight){
                return false;
            }
        }
        //Bellman-Ford complete!
        return true;
    }


    //print Bellman-Ford
    void printBellmanFord(int startIndex){
        for (int endIndex = 1; endIndex < vertices.size(); endIndex ++){
            std::cout << vertices[startIndex]->id << " → " << vertices[endIndex]->id;
            std::cout << " cost is " << vertices[endIndex]->distance << "; path: ";
            
            //name this path and push it to a Stack
            Vertex* pathNode = vertices[endIndex];
            Stack* path = new Stack();

            //traverse predecessors, push to Stack until the start is reached
            while (pathNode != nullptr){
                path->push(pathNode);
                pathNode = pathNode->predecessor;
            }
            
            //pop and print out the Stack
            path->pop();
            while (! path->isEmpty()){
                std::cout << " → ";
                path->pop();
            }
            std::cout << std::endl;
        }
    }
};



//Main Program!
//Read the file,

int main(){

    //create Graph object (will be reused for all Graphs)
    Graph myGraph = Graph();

    //open the file
    std::ifstream graphsFile;
    graphsFile.open(FILE_NAME);
    
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
                if (myGraph.bellmanFord(0)){
                    //print Bellman-Ford output
                    std::cout << "Bellman-Ford SSSP:" << std::endl;
                    myGraph.printBellmanFord(0);
                    std::cout << std::endl;
                }
                else {
                    std::cout << "Bellman-Ford SSSP not possible.\n" << std::endl;
                }

                //reset Graph object (+ Vector objects and Edge objects)
                myGraph.reset();
            }
        }

        //add Vertex
        else if (currentLine.compare(4,6,"vertex") == 0){
            string id = currentLine.substr(11, 11-strLength);
            
            //add Vertex to Graph by id
            myGraph.addVertex(id);
        }

        //add Edge
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
            
            //add Edge in the graph using the Vertex indexes and weight
            myGraph.addEdge(index1, index2, weight);
        }

        //error check
        //line in file doesn't follow my rules: tell the world, skip it, keep going
        else {
            std::cout << "ERROR on line " << line+1 << ":\n\t'" << currentLine << "'" << std::endl;
        }
    }
}