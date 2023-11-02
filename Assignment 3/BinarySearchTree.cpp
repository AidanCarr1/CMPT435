// Aidan Carr
// November 2, 2023
// Binary Search Tree

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


//Node class of BST, 2 children, 1 parent
class Node {

public:
    string itemName;
    Node* parent;
    Node* left;
    Node* right;

    //Constructors
    Node(string itemNameInput){
        itemName = itemNameInput;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
    Node(){
        itemName = "";
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};


//Compare 2 strings in alphabetical order
//return true is first string comes first, false if second string is first
bool isLessThan(string first, string second){

    //find correct length to avoid out of bounds error when comparing
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

    //shorter string is less than larger
    //returns false if strings are equal
    return (length1 < length2)? true : false;
}