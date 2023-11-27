// Aidan Carr
// November 27, 2023
// Greedy Algorithm: Spice Heist

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
using namespace std;


//GLOBAL variables
const string _FILE_NAME = "spice.txt";


//Main Program!
//Read the file,

int main(){

    //open the file
    std::ifstream spiceFile;
    spiceFile.open(_FILE_NAME);
    
    //create vector
    int fileLength = 0;
    vector<string> fileCommands;

    string currentLine;
    if (spiceFile.is_open()){

        //read the file into a vector
        while (spiceFile){
            //insert commands into vector
            std::getline(spiceFile, currentLine); 
            fileCommands.push_back(currentLine);
            fileLength++;
        }

        //IO duplicates final line, delete it
        fileCommands.pop_back(); 
    }    
    else {}
    spiceFile.close();   

    /* //test lines
    for(int i = 0; i < fileCommands.size(); i++){
        std::cout << fileCommands[i] << endl;
    }
    //*/
}