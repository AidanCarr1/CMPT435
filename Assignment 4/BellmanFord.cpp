// Aidan Carr
// November 27, 2023
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

//Main Program!
//Read the file,

int main(){

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

    //* //test lines
    for(int i = 0; i < fileCommands.size(); i++){
        std::cout << fileCommands[i] << endl;
    }
    //*/
}