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
const int NUM_OF_ITEMS = 666;


//Swap 2 element positions given the array and both positions 
void swap(string items[], int position1, int position2){
    string temp = items[position1];
    items[position1] = items[position2];
    items[position2] = temp;
}


//Shuffle the given array O(n)
void shuffle(string items[]){
    srand(time(NULL)); //RNG seed

    int length = NUM_OF_ITEMS;
    for(int i = length-1; i > 0; i--){
        int randomIndex;
        randomIndex = rand() % i;
        swap(items,i,randomIndex);
    }
}


//Compare 2 strings in alphabetical order
//return true is first string comes first, false if second string is first
bool isLessThan(string first, string second){
    
    //find correct length to avoid out of bound error when comparing
    int length1 = first.length();
    int length2 = second.length();
    int length = (length1<length2)? length1 : length2;

    //compare letter by letter until an alphabetically 'smaller' string is found (disregard CAPs)
    for(int i = 0; i < length; i++){
        if(toupper(first.at(i)) < toupper(second.at(i))){
            return true;
        }
        else if (toupper(first.at(i)) > toupper(second.at(i))){
            return false;
        }
    }

    //tie goes to the shorter string
    return (length1<length2)? true : false;
}


//Selection Sort Algoritm, sort the given array O(n^2)
void selectionSort(string items[]){
    int comparisons = 0;
    int minPosition;
    
    for(int i = 0; i <= NUM_OF_ITEMS - 2; i++){
        minPosition = i;
        
        for(int j = i+1; j <= NUM_OF_ITEMS - 1; j++){
            comparisons ++;
            
            //compare for alphabetical order
            if (isLessThan(items[j],items[minPosition])){
                minPosition = j;
            }
        }
        swap(items, i, minPosition);
    }
    std::cout << comparisons << '\n';
}


//Main program!
int main () {

    ifstream itemsFile;
    itemsFile.open("magicitems.txt");
    string magicItems[NUM_OF_ITEMS]; 

    string item;
    string currentLine;
    if (itemsFile.is_open()){
        
        //assign each line to an element in the array
        for (int i = 0; i < NUM_OF_ITEMS; i++) {
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
            std::cout << magicItems[i] << '\n';
        }
    }

    else{
        //causing weird issues:
        //std::cout << "Couldn't open file. \n";
    }

    //Shuffle
    shuffle(magicItems);

    //Shuffle test print
    std::cout << "--" << '\n';    
    for (int i = 0; i < NUM_OF_ITEMS; i++) {
        std::cout << magicItems[i] << '\n';
    }

    //Selection Sort
    selectionSort(magicItems);

    std::cout << "--After sort--" << '\n';    
    for (int i = 0; i < NUM_OF_ITEMS; i++) {
        std::cout << magicItems[i] << '\n';
    }

    //Shuffle
    shuffle(magicItems);

    // Insertion Sort


    //Merge Sort


    //Quick Sort

}