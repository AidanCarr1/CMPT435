// Aidan Carr
// September 28, 2023
// Sorting main file

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <time.h>
using namespace std;


//Swap 2 element positions given the array and both positions 
void swap(string items[], int position1, int position2){
    string temp = items[position1];
    items[position1] = items[position2];
    items[position2] = temp;
}

void shuffle(string items[]){
    srand(time(NULL)); //RNG seed
//FIX find actual length    
    int length = 6;
    for(int i = length-1; i > 0; i--){
        int randomIndex;
        randomIndex = rand() % i;
        swap(items,i,randomIndex);
    }
}


int main () {

    ifstream itemsFile;
    itemsFile.open("letters.txt");
    string magicItems[6]; 

    string item;
    string currentLine;
    if (itemsFile.is_open()){
        
        //assign each line to an element in the array
        for (int i = 0; i < 6; i++) {
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
            std::cout << magicItems[i] << '\n';
        }
    }

    else{
        std::cout << "Couldnt open file. \n";
    }

    //Shuffle
    shuffle(magicItems);

    //Shuffle test print
    std::cout << "-------" << '\n';    
    for (int i = 0; i < 6; i++) {
        std::cout << magicItems[i] << '\n';
    }

    //Selection Sort


    // Insertion Sort


    //Merge Sort


    //Quick Sort

}