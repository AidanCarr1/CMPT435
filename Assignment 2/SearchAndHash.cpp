// Aidan Carr
// October 20, 2023
// Searching and Hashing

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <time.h>
#include <cmath>
using namespace std;


//GLOBAL variables
const int _NUM_OF_ITEMS = 666; //CONSTANT number of magic items
const string _FILE_NAME = "magicitems.txt";
int _comparisons = 0; //count comparisons for each search method
int _SUB_ITEMS = 42; //CONSTANT number of items for searching
int _HASH_TABLE_SIZE = 250; //CONSTANT number of "spots" in hash table


//populate magicItems[] with the item names from the txt file
void setMagicItemsArray(string items[]){ 
    //Open the file
    ifstream itemsFile;
    itemsFile.open(_FILE_NAME);

    string currentLine;
    if (itemsFile.is_open()){

        //assign each line to an element in the array
        for (int i = 0; i < _NUM_OF_ITEMS; i++){
            std::getline(itemsFile, currentLine);
            items[i] = currentLine;
        }
    }
    else {}
}


//Compare 2 strings in alphabetical order
//return true is first string comes first or they are equal, false if second string is first
bool isLessThanOrEqual(string first, string second){
    
    //+1 comparison
    _comparisons++;

    //find correct length to avoid out of bound error when comparing
    int length1 = first.length();
    int length2 = second.length();
    int length = (length1<length2)? length1 : length2;

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
    //if lengths are equal, strings are equal at this point: return true!
    return (length1<=length2)? true : false;
}


//Compare 2 strings in alphabetical order
//return true is first string comes first, false if second string is first
bool isEqual(string first, string second){
    
    //+1 comparison
    _comparisons++;

    //find correct length to avoid out of bound error when comparing
    int length1 = first.length();
    int length2 = second.length();
    if(length1 != length2){
        return false;
    }

    //compare letter by letter until an unequal character string is found
    for (int i = 0; i < length1; i++){
        if (first.at(i) != second.at(i)){
            return false;
        }
    }

    //if the two words have passed its equal
    return true;
}


//Swap 2 element positions given the array and both positions 
void swap(string items[], int position1, int position2){
    string temp = items[position1];
    items[position1] = items[position2];
    items[position2] = temp;
}


//Shuffle the given array O(n)
void shuffle(string items[]){
    srand(time(NULL)); //set RNG seed based on current time

    int length = _NUM_OF_ITEMS;
    int randomIndex;
    for (int i = length-1; i > 0; i--){
        randomIndex = rand() % i;
        swap(items,i,randomIndex);
    }

    //reset comparisons count after each shuffle
    _comparisons = 0;
}


//Merge Sort Algorithm, sort given array with length (recursive)
//From Assignment 1/Sorting.cpp
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
            else if (isLessThanOrEqual(half1[firstPos],half2[secondPos])){
                items[sortingPos] = half1[firstPos];
                firstPos ++;
            }
            else {
                items[sortingPos] = half2[secondPos];
                secondPos ++;
            }
            
            //move to next position to be sorted
            sortingPos ++;
        }
    }
}


//Select 42 random items from the array
void random42(string input[], string output[]){
    for(int i = 0; i < 42; i++){
        output[i] = input[i];
    }
}


//Linear Search, find target in O(n) complexity
int linearSearch(string items[], string target){
    for(int i = 0; i < _NUM_OF_ITEMS; i++){
        if(isEqual(items[i], target)){
            return i;
        }
    }
    return -1;
}


//Binary Search, find target in O(log2n) complexity
//Psuedocode from CLRS textbook pg 799
int binarySearch(string items[], string target){
    int low = 0;
    int high = _NUM_OF_ITEMS;
    int mid;
    while(low < high){
        mid = floor((low+high)/2);
        if(isLessThanOrEqual(target, items[mid])){
            high = mid;
        }
        else{
            low = mid + 1;
        }
    }
    return high;
}


//Node class, used for each element in a hash table
class Node {

public:
    string itemName;
    Node* next;

    //Constructors
    Node(string itemNameInput){
        itemName = itemNameInput;
        next = nullptr;
    }
    Node(){
        itemName = "";
        next = nullptr;
    }
};


//Make a hash code: given a string, output an index
int makeHashCode(string item){
    int asciiTotal = 0;
    //Add up the ASCII values of all chars in the item
    for(int i = 0; i < item.length(); i++){
        asciiTotal += item[i];
    }
    return asciiTotal % _HASH_TABLE_SIZE;
}


//Insert a string into a given hash table
void insert(Node* hashTable[], string item){
    
    //find the hash location
    int index = makeHashCode(item);
    //create a node
    Node myNode(item);
    cout << index << "\n";
    
    return;

    //if first item in chain, place in hashtable array
    if(hashTable[index] == nullptr){
        hashTable[index] = &myNode;
    }
    //follow the chain and place at the end
    else{
        
    }
}


//Search the hash table for the string, return the index
int hashSearch(Node* hashTable[], string item){
    
    //index = hashcode the item
    //check hashtable[index]
    //check the chain
    //return index
    //return -1 if not found
}

//Main program!
//Open file, put into array, pick random 42, search, and print comparisons
int main () {

    //put 666 magic items into magicItems array
    string magicItems[_NUM_OF_ITEMS];
    setMagicItemsArray(magicItems);

    //Shuffle the magic items, store the names the first 42
    string randomItems[42];
    shuffle(magicItems);
    random42(magicItems, randomItems);

    //Sort the magic items
    mergeSort(magicItems, _NUM_OF_ITEMS);
    //std::cout << "Merge Sort Comparisons: "  ;
    //std::cout << _comparisons  << '\n';


    /*
    std::cout << "\nSORTED!\n\n";
    for (int i = 0; i < _NUM_OF_ITEMS; i++){
        std::cout << magicItems[i] << '\n';
    }

    std::cout << "\n42!\n\n";
    for (int i = 0; i < 42; i++){
        std::cout << randomItems[i] << '\n';
    }
    //*/
    

    //LINEAR SEARCH on sorted array for each of the 42 items
    int linearComparisons = 0;
    string item;
    int index;
    for (int i = 0; i < 42; i++){
        
        _comparisons = 0;
        item = randomItems[i];
        index = linearSearch(magicItems, item);
        linearComparisons += _comparisons;

        //print num of comparisons for the item
        std::cout << item << "\n\tComparisons: " << _comparisons << "\n";
    }

    //calculate avg comparisons, round 2 decimal place, print
    float avgLinearComparisons = linearComparisons / 42.0;
    avgLinearComparisons = (int) ((avgLinearComparisons + 0.005) * 100) / 100.0;
    std::cout << "\nAverage Linear Search Comparisons: "<< avgLinearComparisons << "\n\n";


    //BINARY SEARCH on sorted array for each of the same 42 items
    int binaryComparisons = 0;
    for (int i = 0; i < 42; i++){
        
        _comparisons = 0;
        item = randomItems[i];
        index = binarySearch(magicItems, item);
        binaryComparisons += _comparisons;

        //print num of comparisons for the item
        std::cout << item << "\n\tComparisons: " << _comparisons << "\n";
    }

    //calculate avg comparisons, round 2 decimal place, print
    float avgBinaryComparisons = binaryComparisons / 42.0;
    avgBinaryComparisons = (int) ((avgBinaryComparisons + 0.005) * 100) / 100.0;
    std::cout << "\nAverage Binary Search Comparisons: "<< avgBinaryComparisons << "\n\n";


    //create hash table
    Node* magicHash[_HASH_TABLE_SIZE];

    //load HASH TABLE with all 666 items
    for (int i = 0; i < _NUM_OF_ITEMS; i++){
        insert(magicHash, magicItems[i]);
    }


    //SEARCH hash table for each of the same 42 items
    int hashComparisons = 0;
    for (int i = 0; i < 42; i++){
        
        _comparisons = 0;
        item = randomItems[i];
        index = 15;//hashSearch(magicHash, item);
        hashComparisons += _comparisons;

        //print num of comparisons for the item
        std::cout << item << "\n\tComparisons: " << _comparisons << "\n";
    }

    //calculate avg comparisons (get and chaining), round 2 decimal place, print
    float avgHashComparisons = hashComparisons / 42.0;
    avgHashComparisons = (int) ((avgHashComparisons + 0.005) * 100) / 100.0;
    std::cout << "\nAverage Hash Search Comparisons: "<< avgHashComparisons << "\n\n";
}