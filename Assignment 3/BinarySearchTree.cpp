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
const int _NUM_OF_ITEMS = 26; //CONSTANT number of magic items
const string _FILE_NAME = "magicitems.txt";
const int _NUM_OF_SUB_ITEMS = 42; //CONSTANT number of items for searching
const string _SUB_FILE_NAME = "magicitems-find-in-bst.txt";



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


//Binary Search Tree class
class BinarySearchTree{

public:
    Node* root;

    //Constructor
    BinarySearchTree(){
        root = nullptr;
    }
};

//populate magicItems[] with the item names from the txt file
    //from Assignment 2
void setItemsArray(string items[], string file, int length){ 
    //Open the file
    ifstream itemsFile;
    itemsFile.open(file);

    string currentLine;
    if (itemsFile.is_open()){

        //assign each line to an element in the array
        for (int i = 0; i < length; i++){
            std::getline(itemsFile, currentLine);
            items[i] = currentLine;
        }
    }
    else {}
    itemsFile.close();
}


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



//insert a string into the BST
void insert(BinarySearchTree *tree, string name){
    
    //create a new node
    Node* newNode = new Node();
    newNode->itemName = name;

    Node* trailing = nullptr;
    Node* current = tree->root;

    //find a spot for the new Node
    while (current != nullptr){
        trailing = current;
        if (isLessThan(name, current->itemName)){
            current = current->left;
            std::cout << "L";
        }
        else {
            current = current->right;
            std::cout << "R";
        }
    }
    std::cout << endl;

    //put the new Node in the spot
    newNode->parent = trailing;
    if (trailing == nullptr){
        tree->root = newNode;
    }
    else if (isLessThan(name, trailing->itemName)){
        trailing->left = newNode;
    }
    else {
        trailing->right = newNode;
    }
}


//Main program!
//Open file, put into array, pick random 42, search, and print comparisons
int main () {

    //put 666 magic items into magicItems array
    string magicItems[_NUM_OF_ITEMS];
    setItemsArray(magicItems, _FILE_NAME, _NUM_OF_ITEMS);

    //create a Binary Search Tree
    BinarySearchTree magicBST;

    //insert all magic items into BST
    for (int i = 0; i < _NUM_OF_ITEMS; i++){
        std::cout << magicItems[i] << std::endl;
        insert(&magicBST, magicItems[i]);
    }


    //put 666 magic items into magicItems array
    string subMagicItems[_NUM_OF_SUB_ITEMS];
    setItemsArray(subMagicItems, _SUB_FILE_NAME, _NUM_OF_SUB_ITEMS);

    //Search for select items within BST
    for (int i = 0; i < _NUM_OF_SUB_ITEMS; i++){
        std::cout << subMagicItems[i] << std::endl;
    }


}