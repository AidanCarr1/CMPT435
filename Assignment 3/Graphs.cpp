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
                //print the previous graph (if previous exists)
                //delete graph
            }

            //new vertex
            else if (currentLine.compare(4,6,"vertex") == 0){
                int strLength = currentLine.length();
                int vertexNum = stoi(currentLine.substr(11,11-strLength));
                std::cout << vertexNum << endl; //test line

                //create vertex object
            }

            //new edge
            else if (currentLine.compare(4,4,"edge") == 0){

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