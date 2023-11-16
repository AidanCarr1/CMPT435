// Aidan Carr
// November 16, 2023
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



//VERTEX CLASS
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

//NODE CLASS, used in Queue class
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

//QUEUE CLASS, used in BFT
class Queue{

public:
    Node* head;
    Node* tail;

    //Constructor
    Queue(){
        head = nullptr;
        tail = nullptr;
    }

    //METHODS
    //return true if Empty
    bool isEmpty(){
        if (tail == nullptr || head == nullptr){
            return true;
        }
        return false;
    }

    //enqueue/add to back of queue
    void enqueue(Node* newTail){
        //add a head if it is the first in line
        if (isEmpty()){
            head = newTail;
        }
        else {
            //put new tail behind the old tail
            tail->next = newTail;
        }
        //make this queue's tail this new tail
        tail = newTail;
    }
    //enqueue a Vertex (use enqueue() method with a new Node)
    void enqueue(Vertex* myVertex){
        Node* myNode = new Node(myVertex);
        enqueue(myNode);
    }

    //dequeue/retrieve from front of queue
    Vertex* dequeue(){
        //cant dequeue if there is nothing to dequeue
        if (isEmpty()){
            return nullptr;
        }
        //return the head Vertex
        Vertex* dequeuing = head->content;
        head = head->next;
        return dequeuing;
    }
};



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



//GRAPH CLASS
class Graph {

public:
    vector<Vertex*> vertices;
    
    //constructor
    Graph(){
    }    

    //METHODS:
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

    //add Vertex
    void addVertex(string id){
        Vertex* myVertex = new Vertex(id);
        //add new Vertex to the list
        vertices.push_back(myVertex);
    }

    //add edge
    void addEdge(int index1, int index2){
        //add neighbor for both Vertices
        vertices[index1]->addNeighbor(vertices[index2]);
        vertices[index2]->addNeighbor(vertices[index1]);
    }


    //PRINT/DISPLAY methods:

    //matrix
    void printAsMatrix(){
        int size = vertices.size();
        
        //print header
        std::cout << "\nGRAPH AS A MATRIX:\n" << std::endl;
        std::cout << "\t";
        for (int i = 0; i < size; i++){
            std::cout << vertices[i]->id << "\t";
        }
        std::cout << std::endl;

        for (int r = 0; r < size; r++){
            //print header
            std::cout << vertices[r]->id << "\t";
            
            for (int c = 0; c < size; c++){
                bool isEdge = false;
                
                //search r's neighbors for c
                for (int j = 0; j < vertices[r]->neighbors.size(); j++){
                    if (isEqual(vertices[r]->neighbors[j]->id, vertices[c]->id)){
                        std::cout << "1";
                        isEdge = true;
                        break;
                    }
                }
                if (! isEdge){
                    std::cout << ".";
                }
                std::cout << "\t";
            }
            std::cout << std::endl;
        }
    }

    //adjacency list
    void printAsAdjacencyList(){
        int size = vertices.size();
    
        std::cout << "\nGRAPH AS AN ADJACENCY LIST:\n" << std::endl;

        for (int i = 0; i < size; i++){
            //print header
            std::cout << "[" << vertices[i]->id << "]";
            
            //search and print i's neighbors
            for (int j = 0; j < vertices[i]->neighbors.size(); j++){
                std::cout << " " << vertices[i]->neighbors[j]->id;
            }
            std::cout << std::endl;
        }
    }


    //TRAVERSAL METHODS:
    
    //depth-ft
    void depthFirstTraversal(Vertex* fromVertex){
        if (! fromVertex->isProcessed){
            std::cout << fromVertex->id << " ";
            fromVertex->isProcessed = true;
        }
        for (int i = 0; i < fromVertex->neighbors.size(); i++){
            if (! fromVertex->neighbors[i]->isProcessed){
                depthFirstTraversal(fromVertex->neighbors[i]);
            }
        }
    }

    //unprocess all
    void unprocessAll(){
        for (int i = 0; i < vertices.size(); i++){
            vertices[i]->isProcessed = false;
        }
    }

    //breadth-ft
    void breadthFirstTraversal(Vertex* fromVertex){
        Queue* myQueue = new Queue();
        myQueue->enqueue(fromVertex);
        fromVertex->isProcessed = true;

        while (! myQueue->isEmpty()){
            Vertex* currentVertex = myQueue->dequeue();
            std::cout << currentVertex->id << " ";

            for (int i = 0; i < currentVertex->neighbors.size(); i++){
                //check this level's neighbors first (breadth first)
                if (! currentVertex->neighbors[i]->isProcessed){
                    myQueue->enqueue(currentVertex->neighbors[i]);
                    currentVertex->neighbors[i]->isProcessed = true;
                }
            }
        }
    }
};



//Main Program!
//Read graphs file and interpret: make Graphs, Vertices, edges
int main() {

    //create Graph
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
        string currentLine;

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

        //interpret file commands
        for(int line = 0; line < fileLength; line ++){
            //get line as a string, and find length
            string currentLine = fileCommands[line]; 
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

            //new Graph
            else if (currentLine.compare(0,3,"new") == 0){
                //std::cout << "NEW Graph" << endl;               
                
                //if there is a previous Graph, process it
                if (! myGraph.isEmpty()){
                    
                    //process Graph
                    myGraph.printAsMatrix();
                    myGraph.printAsAdjacencyList();
                    //myGraph.printAsLinkedObjects();

                    std::cout << "\nDEPTH-FIRST TRAVERSAL" << std::endl;
                    myGraph.depthFirstTraversal(myGraph.vertices[0]);
                    std::cout << "\n" <<std::endl;
                    myGraph.unprocessAll();

                    std::cout << "BREADTH-FIRST TRAVERSAL" << std::endl;
                    myGraph.breadthFirstTraversal(myGraph.vertices[0]);
                    std::cout << "\n\n\n" <<std::endl;
                    
                    //delete Graph
                }
            }

            //new Vertex
            else if (currentLine.compare(4,6,"vertex") == 0){
                string id = currentLine.substr(11, 11-strLength);
                //std::cout << id << std::endl; //test line
               
                //add Vertex to Graph by id
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
                //cout << "ID1: " << id1 << ". ID2: " << id2 << endl; //test line

                //find index of each id
                int index1 = myGraph.findVertexById(id1);
                int index2 = myGraph.findVertexById(id2);
                //cout << "Index: " << index1 << ", " << index2 << endl; //test line
                
                //add edge in the graph using the Vertex indexes
                myGraph.addEdge(index1, index2);
            }

            else {
                std::cout << "ERROR: '" << currentLine << "'" << std::endl;
            }
        }
}