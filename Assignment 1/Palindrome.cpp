// Aidan Carr
// September 28, 2023
// Palindrome main file

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
const int NUM_OF_ITEMS = 6;


class Node {

public:
    string itemName;
    Node* next;

    Node(string itemNameInput){
        itemName = itemNameInput;
        next = nullptr;
    }

    void setNext(Node newNext){
        next = &newNext;
    }

    string getName(){
        return itemName;
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

    //METHODS
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

class Queue{

public:
    
    //Attributes
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
        if (head == nullptr){
            return true;
        }
        return false;
    }

    void setTail(Node newTail){
        tail = &newTail;
    }

    //enqueue/add to back of queue
    void enqueue(Node newTail){
        //add a head if it is the first in line
        if(isEmpty()){
            head = &newTail;
        }

//FIX: this line!!!
//Let former tail's next value point to the new tail
        
        //*tail->next = newTail;
        //tail.setNext(&newTail);
        //tail->getName();
        //Node *myTail = tail;
        //cout << myTail->setNext(n1) << "----";
        //myTail->setNext(newTail);
        //tail->setNext(newTail);
        //tail->next->setNext(newTail);
        
        //idea:
        //make a new node (myTail) with a new next pointer (newTail) and set this.tail = myTail

        tail = &newTail;
    }

    //dequeue/retrieve from front of queue
    string dequeue(){
        //cant pop if there is nothing to pop
        if(isEmpty()){
            return "EMPTY STACK";
        }
        string dequeuing = head->itemName;
        head = head->next;
        return dequeuing;
    }
};


int main () {

    //* TEST

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
    
    //add to queue
    Queue years;
    years.enqueue(n0);
    years.enqueue(n1);
    years.enqueue(n2);
    years.enqueue(n3);

    //pop out of stack
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n'; //will return error message
    //*/

    ifstream itemsFile;
    itemsFile.open("letters.txt");
    string magicItems[NUM_OF_ITEMS]; 

/*
    string currentLine;
    if (itemsFile.is_open()){
        
        //assign each line to element in the array
        for (int i = 0; i < NUM_OF_ITEMS; i++) {
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
            std::cout << magicItems[i] << '\n';
        }
    }

    else{
        std::cout << "Couldn't open file. \n";
    }


    //go through every magic item
    string item;
    Stack myStack;
    Queue myQueue;

    for (int i = 0; i < NUM_OF_ITEMS; i++) {
        item = magicItems[i];

        //clear the stack and queue
        myStack.top = nullptr;
        myQueue.head = nullptr;
        myQueue.tail = nullptr;

        //add letter to stack and queue (appropriately)
        for (int j = 0; j < item.length(); j++){
            
            if(magicItems[i][j] != ' '){
                
                //convert current character to an uppercase string
                string character(1,toupper(magicItems[i][j]));
                
                //push character to stack
                Node myStackNode(character);
                myStack.push(myStackNode);
                //test line:
                std::cout << (myStack.top)->itemName << '\n';

                //enqueue character to queue
                Node myQueueNode(character);
                myQueue.enqueue(myQueueNode);
                //test line:
                std::cout << (myQueue.tail)->itemName << '\n';

            }         
        }  

        bool isPalindrome = true;

        //compare letter by letter for palidrome
        //while the stack is filled
        while (! myStack.isEmpty()){
            
            string dequeued = myQueue.dequeue();
            string popped = myStack.pop();

            //compare the single character Nodes
            if(dequeued[0] != popped[0]){
                isPalindrome = false;
                false;
            }
        }

        if(isPalindrome){
            
        }
        std::cout << item << '\n';

    }

    */
     
}