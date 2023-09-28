// Aidan Carr
// September 28, 2023
// Sorting main file

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
//#include <cctype>
using namespace std;

int main () {

    ifstream itemsFile;
    itemsFile.open("magicitems.txt");
    string magicItems[666]; 

    string item;
    string currentLine;
    if (itemsFile.is_open()){
        
        //assign each line to element in the array
        for (int i = 0; i < 666; i++) {
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
            std::cout << magicItems[i] << '\n';
        }
    }

    else{
        std::cout << "Couldnt open file. \n";
    }

    //
    for (int i = 0; i < 666; i++) {
        item = magicItems[i];
    }


}