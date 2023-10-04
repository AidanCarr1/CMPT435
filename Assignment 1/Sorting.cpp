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
const int NUM_OF_ITEMS = 10; //CONSTANT number of magic items
const string FILE_NAME = "letters.txt";
int comparisons = 0; //count comparisons for each sorting method (resets on shuffle)

//Swap 2 element positions given the array and both positions 
void swap(string items[], int position1, int position2){
    string temp = items[position1];
    items[position1] = items[position2];
    items[position2] = temp;
}


//Shuffle the given array O(n)
void shuffle(string items[]){
    srand(time(NULL)); //set RNG seed based on current time

    int length = NUM_OF_ITEMS;
    for (int i = length-1; i > 0; i--){
        int randomIndex;
        randomIndex = rand() % i;
        swap(items,i,randomIndex);
    }

    //reset comparisons count
    comparisons = 0;
}


//Compare 2 strings in alphabetical order
//return true is first string comes first, false if second string is first
bool isLessThan(string first, string second){
    
    //find correct length to avoid out of bound error when comparing
    int length1 = first.length();
    int length2 = second.length();
    int length = (length1<length2)? length1 : length2;

    //+1 comparison
    comparisons++;

    //compare letter by letter until an alphabetically 'smaller' string is found (disregard CAPs)
    for (int i = 0; i < length; i++){
        if (toupper(first.at(i)) < toupper(second.at(i))){
            return true;
        }
        else if (toupper(first.at(i)) > toupper(second.at(i))){
            return false;
        }
    }

    //tie goes to the shorter string
    return (length1<length2)? true : false;
}


//Selection Sort Algorithm, sort the given array O(n^2)
void selectionSort(string items[]){
    int minPosition;
    
    for (int i = 0; i <= NUM_OF_ITEMS - 2; i++){
        minPosition = i;
        
        for (int j = i+1; j <= NUM_OF_ITEMS - 1; j++){

            //compare for alphabetical order
            if (isLessThan(items[j],items[minPosition])){
                minPosition = j;
            }
        }
        swap(items, i, minPosition);
    }
}


//Insertion Sort Algorithm, sort the given array O(n^2)
void insertionSort(string items[]){

    for (int i = 1; i < NUM_OF_ITEMS; i ++){
        int sortedIndex = i - 1;
        int sortingIndex = i;

        //find item[i]'s spot in the already sorted part of list
        while(sortedIndex >= 0 && isLessThan(items[sortingIndex],items[sortedIndex]) && comparisons++){
            swap(items, sortedIndex, sortingIndex);
            sortedIndex --;
            sortingIndex --;
        }
    }
}


//Merge Sort Algorithm, sort given array with length (recursive) O(log2n)
void mergeSort(string items[], int length){
    //Base case: when length 1, start conquering, until then, divide
    if (length > 1){
        
        int firstHalfLength = length/2;
        int secondHalfLength = length - firstHalfLength;
        string half1[firstHalfLength];
        string half2[secondHalfLength];

        //fill in half1
        for (int i = 0; i < firstHalfLength; i++){
            half1[i] = items[i];
        }

        //fill in half2
        for (int i = 0; i < secondHalfLength; i++){
            half2[i] = items[firstHalfLength+i];
        }

        //sort each half
        mergeSort(half1, firstHalfLength);
        mergeSort(half2, secondHalfLength);
        
        int sortingPos = 0;
        int firstPos = 0;
        int secondPos = 0;

        while (sortingPos < length){
  
            //if one half is completely put into sorted array, 
            //put the rest of the other half into sorted array
            if (firstPos == firstHalfLength){
                items[sortingPos] = half2[secondPos];
                secondPos ++;
            }
            else if (secondPos == secondHalfLength){
                items[sortingPos] = half1[firstPos];
                firstPos ++;
            }

            //sort 2 ordered arrays into one larger array
            else if (isLessThan(half1[firstPos],half2[secondPos])){
                items[sortingPos] = half1[firstPos];
                firstPos ++;
            }
            else {
                items[sortingPos] = half2[secondPos];
                secondPos ++;
            }
            
            //move to next sorted position
            sortingPos ++;
        }
    }
}


//Partition Algorithm, part of quick sort organize array with pivot in correct spot
int partition(string items[], int splitIndex, int length){
    swap(items, splitIndex, length-1);

    //This variable tracks the lowest index of elements the belong higher than the pivot value
    int higherPos = -1;
    for (int checking = 0; checking < length-1; checking++){
        
        if(isLessThan(items[checking], items[length-1])){
            higherPos++;
            //move higher values higher
            swap(items, higherPos, checking);
        }
    }
    swap(items, length-1, higherPos+1);
    return higherPos + 1;
}


//Quick Sort Algorithm, sort given array O(log2n)
void quickSort(string items[], int length){
    
    srand(time(NULL)); //set RNG seed based on current time

    if (length > 1){
        int splitIndex;
        //choose 3 pivot candidates 
        if (length >= 3){
            int rand1 = rand() % length;
            int rand2 = (rand1 + 1) % length;
            int rand3 = (rand1 + 2) % length;

            string item1 = items[rand1];
            string item2 = items[rand2];
            string item3 = items[rand3];
            cout << item1 << ", " << item2 << ", " << item3 << "\n"; //test

            //pick middle valued index
            if ( (isLessThan(item2,item1) && isLessThan(item1,item3)) || (isLessThan(item3,item1)) && (isLessThan(item1,item2)) ){
                splitIndex = rand1;
            }
            else if ( (isLessThan(item1,item2) && isLessThan(item2,item3)) || (isLessThan(item3,item2)) && (isLessThan(item2,item1)) ){
                splitIndex = rand2;
            }
            else {
                splitIndex = rand3;
            }

            cout << "pivot: " << items[splitIndex] << "\n\n"; //test
        }
        //choose 1 pivot index if there aren't enough candidates
        else {
            splitIndex = rand() % length;
        }

        int r = partition(items, splitIndex, length);

        for (int i = 0; i < NUM_OF_ITEMS; i++){
            std::cout << items[i] << '\n';
        }
        
        //Merge Sort Code: (Might be useful)
        int firstHalfLength = r;
        int secondHalfLength = length - r - 1;
        string half1[firstHalfLength];
        string half2[secondHalfLength];

        //quickSort(items,)
    }
    
    
}


//Main program!
int main () {

    ifstream itemsFile;
    itemsFile.open(FILE_NAME);
    string magicItems[NUM_OF_ITEMS]; 

    //string item;
    string currentLine;
    if (itemsFile.is_open()){

        //assign each line to an element in the array
        for (int i = 0; i < NUM_OF_ITEMS; i++){
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
        }
    }

    else {
        //causing weird issues:
        //std::cout << "Couldn't open file. \n";
    }

/*
    //Shuffle
    shuffle(magicItems);

    //Selection Sort
    selectionSort(magicItems);
    std::cout << "Selection Sort Comparisons: "  ;
    std::cout << comparisons  << '\n';

    //Shuffle
    shuffle(magicItems);

    //Insertion Sort
    insertionSort(magicItems);
    std::cout << "Insertion Sort Comparisons: "  ;
    std::cout << comparisons  << '\n';

    //Shuffle
    shuffle(magicItems);

    //Merge Sort
    mergeSort(magicItems, NUM_OF_ITEMS);
    std::cout << "Merge Sort Comparisons: "  ;
    std::cout << comparisons  << '\n';
*/
    //Shuffle
    shuffle(magicItems);

    std::cout << "Shuffled: " << '\n';
    for (int i = 0; i < NUM_OF_ITEMS; i++){
        std::cout << magicItems[i] << '\n';
    }
    std::cout << '\n';

    //Quick Sort
    quickSort(magicItems, NUM_OF_ITEMS);
    //std::cout << "Quick Sort Comparisons: "  ;
    //std::cout << comparisons  << '\n';

/*
    for (int i = 0; i < NUM_OF_ITEMS; i++){
        std::cout << magicItems[i] << '\n';
    }
//*/

}