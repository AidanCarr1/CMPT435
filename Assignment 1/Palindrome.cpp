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

    Node(string itemNameInput){
        itemName = itemNameInput;
        next = nullptr;
    }
};


class Stack{

public:
    
    //Attributes
    Node* top;

    //Constructor
    Stack(){
        top = nullptr;
    }

    //Methods
    //return true if Empty
    bool isEmpty(){
        if (top == nullptr){
            return true;
        }
        return false;
    }

    //push/add to the top
    void push(Node newTop){
        newTop.next = top;
        top = &newTop;
    }

    //retrieve from the top
    string pop(){
        //cant pop if there is nothing to pop
        if(isEmpty()){
            return "EMPTY STACK";
        }
        string popping = top->itemName;
        top = top->next;
        return popping;
    }
};


int main () {

    /* TEST

    //create 4 nodes
    Node n0("Freshman");
    Node n1("Sophomore");
    Node n2("Junior");
    Node n3("Senior");

    //print variables
    cout << n0.itemName << '\n';
    cout << n1.itemName << '\n';
    cout << n2.itemName << '\n';
    cout << n3.itemName << '\n';
    
    //add to stack
    Stack years;
    years.push(n0);
    years.push(n1);
    years.push(n2);
    years.push(n3);

    //pop out of stack
    cout << years.pop() << '\n';
    cout << years.pop() << '\n';
    cout << years.pop() << '\n';
    cout << years.pop() << '\n';
    cout << years.pop() << '\n'; //will return error message
    */

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