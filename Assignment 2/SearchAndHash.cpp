// Aidan Carr
// October 26, 2023
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
const int _SUB_ITEMS = 42; //CONSTANT number of items for searching
const int _HASH_TABLE_SIZE = 250; //CONSTANT number of "spots" in hash table
int _comparisons = 0; //count comparisons for each search method



//Node class, used for each element in a hash table
    //From Assignment 1/Palindrome.cpp
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
bool isLessThan(string first, string second){

    //find correct length to avoid out of bound error when comparing
    int length1 = first.length();
    int length2 = second.length();
    int length = (length1 < length2)? length1 : length2;

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
    return (length1 <= length2)? true : false;
}


//Compare 2 strings in alphabetical order
//return true is first string comes first, false if second string is first
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

    //if the two words have passed its equal
    return true;
}


//Swap 2 element positions given the array and both positions 
    //From Assignment 1/Sorting.cpp
void swap(string items[], int position1, int position2){
    string temp = items[position1];
    items[position1] = items[position2];
    items[position2] = temp;
}


//Shuffle the given array O(n)
    //From Assignment 1/Sorting.cpp
void shuffle(string items[]){
    srand(time(NULL)); //set RNG seed based on current time

    int length = _NUM_OF_ITEMS;
    int randomIndex;
    for (int i = length-1; i > 0; i--){
        randomIndex = rand() % i;
        swap(items, i, randomIndex);
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
            else if (isLessThan(half1[firstPos], half2[secondPos])){
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


//Linear Search, find target in O(n) complexity
int linearSearch(string items[], string target){
    for (int i = 0; i < _NUM_OF_ITEMS; i++){
        _comparisons ++;
        if (isEqual(items[i], target)){
            return i;
        }
    }
    return -1;
}


//Binary Search, find target in O(log2n) complexity
    //Psuedocode from CLRS textbook pg 799
int binarySearch(string items[], string target){
    int low = 0;              //inclusive
    int high = _NUM_OF_ITEMS; //exclusive
    int mid;

    while (low < high){
        mid = floor((low+high)/2);
        _comparisons ++;
        if (isEqual(target, items[mid])){
            return mid;
        }
        else if (isLessThan(target, items[mid])){
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }

    return -1;
}


//Make a hash code: given a string, output an index
int makeHashCode(string item){
    
    int asciiTotal = 0;
    //Add up the ASCII values of all chars in the item
    for (int i = 0; i < item.length(); i++){
        asciiTotal += item[i];
    }
    return asciiTotal % _HASH_TABLE_SIZE;
}


//Insert a string into a given hash table
void insert(Node* hashTable[], string item){
    
    //find the hash location
    int index = makeHashCode(item);
    
    //create a node
    Node* myNode = new Node();
    myNode->itemName = item;

    //place this node in front of previous node at hash index
    myNode->next = hashTable[index];
    hashTable[index] = myNode;
}


//Search the hash table for the string, return the index
int hashSearch(Node* hashTable[], string item){
    
    //find the hash location
    int index = makeHashCode(item);

    _comparisons ++;

    if (hashTable[index] == nullptr){
        return -1;
    } 
    else if (isEqual(item, hashTable[index]->itemName)){
        return index;
    }   

    //check the chain
    else {
        Node* temp = new Node();                 
        temp = hashTable[index]->next;

        //is next spot availible? if not, move to next node
        //+1 comparison for every
        while (_comparisons ++ && temp != NULL){
            if (isEqual(temp->itemName, item)){
                return index;
            }
            temp = temp->next;
        }
        //not found in chain
        return -1;
    }
}



//Main program!
//Open file, put into array, pick random 42, search, and print comparisons
int main () {

    //put 666 magic items into magicItems array
    string magicItems[_NUM_OF_ITEMS];
    setMagicItemsArray(magicItems);

    //Shuffle the magic items, store the names the first 42
    string randomItems[_SUB_ITEMS];
    shuffle(magicItems);
    for (int i = 0; i < _SUB_ITEMS; i++){
        randomItems[i] = magicItems[i];
    }

    //Sort the magic items
    mergeSort(magicItems, _NUM_OF_ITEMS);



    //LINEAR SEARCH on sorted array for each of the 42 items
    std::cout << "\nLINEAR SEARCH" << "\n" << std::endl;
    int linearComparisons = 0;
    string item;
    int index;
    for (int i = 0; i < _SUB_ITEMS; i++){
        
        _comparisons = 0;
        item = randomItems[i];
        index = linearSearch(magicItems, item);
        linearComparisons += _comparisons;

        //print num of comparisons for the item
        std::cout << item << "\n\tComparisons: " << _comparisons << std::endl;
    }

    //calculate avg comparisons, round 2 decimal place, print
    float avgLinearComparisons = (float) linearComparisons / _SUB_ITEMS;
    avgLinearComparisons = (int) ((avgLinearComparisons + 0.005) * 100) / 100.0;
    std::cout << "\nAverage Linear Search Comparisons: "<< avgLinearComparisons << "\n" << std::endl;



    //BINARY SEARCH on sorted array for each of the same 42 items
    std::cout << "\nBINARY SEARCH" << "\n" << std::endl;
    int binaryComparisons = 0;
    for (int i = 0; i < _SUB_ITEMS; i++){
        
        _comparisons = 0;
        item = randomItems[i];
        index = binarySearch(magicItems, item);
        binaryComparisons += _comparisons;

        //print num of comparisons for the item
        std::cout << item << "\n\tComparisons: " << _comparisons << std::endl;
    }

    //calculate avg comparisons, round 2 decimal place, print
    float avgBinaryComparisons = (float) binaryComparisons / _SUB_ITEMS;
    avgBinaryComparisons = (int) ((avgBinaryComparisons + 0.005) * 100) / 100.0;
    std::cout << "\nAverage Binary Search Comparisons: "<< avgBinaryComparisons << "\n" << std::endl;



    //create an empty HASH TABLE
    std::cout << "\nHASH TABLE" << "\n" << std::endl;
    Node* magicHash[_HASH_TABLE_SIZE];
    for (int i = 0; i < _HASH_TABLE_SIZE; i++){
        magicHash[i] = nullptr;
    }

    //load HASH TABLE with all 666 items
    for (int i = 0; i < _NUM_OF_ITEMS; i++){
        insert(magicHash, magicItems[i]);
    }

    //SEARCH hash table for each of the same 42 items
    int hashComparisons = 0;
    for (int i = 0; i < _SUB_ITEMS; i++){
        
        _comparisons = 0;
        item = randomItems[i];
        index = hashSearch(magicHash, item);
        hashComparisons += _comparisons;

        //print num of comparisons for the item
        std::cout << item << "\n\tComparisons: " << _comparisons << std::endl;
    }

    //calculate avg comparisons (get and chaining), round 2 decimal place, print
    float avgHashComparisons = (float) hashComparisons / _SUB_ITEMS;
    avgHashComparisons = (int) ((avgHashComparisons + 0.005) * 100) / 100.0;
    std::cout << "\nAverage Hash Search Comparisons: "<< avgHashComparisons << "\n" << std::endl;
}