// Aidan Carr
// September 18, 2023
// Palindrome main file

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main () {
    ifstream itemsFile;
    itemsFile.open("magicitems.txt");
    string magicItems[666]; 

    string currentLine;
    if (itemsFile.is_open()){
        
        //assign each line to element in the array
        for (int i = 0; i < 666; i++) {
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
            //std::cout << magicItems[i] << '\n';
        }
    }

    else{
        std::cout << "Couldnt open file. \n";
    }
    
    string item;
    for (int i = 0; i < 666; i++) {
        item = magicItems[i];

        //create stack

        //create queue

        //add letter to stack and queue (appropriately)
        for (int i = 0; i < item.length(); i++){

        }

        //compare
    }  
}
