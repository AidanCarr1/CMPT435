// Aidan Carr
// September 18, 2023
// Palindrome main file

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node {

public:
    string itemName;
    Node* next;
    //object nextNode;

    Node(string itemNameInput){
        itemName = itemNameInput;
        next = nullptr;
        //object nextNode;
    }
    /*
    node getNextNode() {
        return nextNode;
    }
    */
};


class Stack{

public:
    //pointer top;
    Stack(){
        //top = null;
    }

};


int main () {

    //create test nodes
    Node n0(0, "Freshman");
    Node n1(1, "Sophomore");
    Node n2(2, "Junior");
    Node n3(3, "Senior");

    //print variables
    cout << n0.itemName;
    cout << n1.itemName;
    cout << n2.itemName;
    cout << n3.itemName;


    
    ifstream itemsFile;
    itemsFile.open("magicitems.txt");
    string magicItems[666]; 

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
