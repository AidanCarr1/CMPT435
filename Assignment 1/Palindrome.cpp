// Aidan Carr
// October 3, 2023
// Palindrome main file

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

//GLOBAL variables
const int _NUM_OF_ITEMS = 666;
const string _FILE_NAME = "magicitems.txt";



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


class Stack{

public:
    Node* top;

    //Constructor
    Stack(){
        top = nullptr;
    }

    //METHODS
    //return true if Empty
    bool isEmpty(){
        if (top == nullptr){
            return true;
        }
        return false;
    }

    //push/add to the top
    void push(Node* newTop){
        newTop->next = top;
        top = newTop;
    }

    //retrieve from the top
    string pop(){
        //cant pop if there is nothing to pop
        if (isEmpty()){
            return "EMPTY STACK";
        }
        string popping = top->itemName;
        top = top->next;
        return popping;
    }
};

class Queue{

public:
    Node* head;
    Node* tail;

    //Constructor
    Queue(){
        head = nullptr;
        tail = nullptr;
    }

    //METHODS
    //return true if Empty
    bool isEmpty(){
        if (tail == nullptr || head == nullptr){
            return true;
        }
        return false;
    }

    //enqueue/add to back of queue
    void enqueue(Node* newTail){
        //add a head if it is the first in line
        if (isEmpty()){
            head = newTail;
        }
        else {
            //put new tail behind the old tail
            tail->next = newTail;
        }
        //make this queue's tail this new tail
        tail = newTail;
    }

    //dequeue/retrieve from front of queue
    string dequeue(){
        //cant pop if there is nothing to pop
        if (isEmpty()){
            return "EMPTY STACK";
        }
        string dequeuing = head->itemName;
        head = head->next;
        return dequeuing;
    }
};


//return true if word is a palindrome
//create the stack and queue
bool isPalindrome(string item){
    Stack myStack;
    Queue myQueue;
    string character;
    //arrays are for storage purposes only
    Node myStackNodes[item.length()];
    Node myQueueNodes[item.length()];

    //create 2 nodes for each character (appropriately)
    for (int letterIndex = 0; letterIndex < item.length(); letterIndex++){

        if (item[letterIndex] != ' '){
            //convert current character to an uppercase string
            character = (1,toupper(item[letterIndex]));
            
            //make 2 nodes
            myStackNodes[letterIndex].itemName = character;
            myQueueNodes[letterIndex].itemName = character;

            //add each character to stack and queue
            myStack.push(&myStackNodes[letterIndex]);
            myQueue.enqueue(&myQueueNodes[letterIndex]);
        }         
    }  
 
    bool isPalindrome = true;
    string dequeued = "";
    string popped = "";
    
    //compare letter by letter for palindrome
    while (!myQueue.isEmpty() && isPalindrome){
        //search until all letters checked, or palindrome is proven wrong

        dequeued = myQueue.dequeue();
        popped = myStack.pop();

        //compare the single character Nodes
        if (dequeued != popped){
            isPalindrome = false;
        }
    }
    return isPalindrome;
}


int main () {

    ifstream itemsFile;
    itemsFile.open(_FILE_NAME);
    string magicItems[_NUM_OF_ITEMS]; 

    string currentLine;
    if (itemsFile.is_open()){
        
        //assign each line to an element in the array
        for (int i = 0; i < _NUM_OF_ITEMS; i++){
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
        }
    }

    else {}

    //go through every magic item, check if PALINDROME
    string item;
    for (int i = 0; i < _NUM_OF_ITEMS; i++){
        item = magicItems[i];

        if (isPalindrome(item)){
            cout << item << "\n";
        }
    }   
}