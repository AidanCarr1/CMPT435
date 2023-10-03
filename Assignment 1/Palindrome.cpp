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

    void setNext(Node* newNext){
        next = newNext;
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

    //Destructor
    //~Stack(){
    //}

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

    //Destructor
    //~Queue(){
    //}

    //METHODS
    //return true if Empty
    bool isEmpty(){
        if(head == nullptr){
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
        else{
            tail->next = &newTail;
        }
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
    cout << " BEGIN dequeuing\n";
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n'; //will return error message
    //*/

//*/
    ifstream itemsFile;
    itemsFile.open("letters.txt");
    string magicItems[NUM_OF_ITEMS]; 

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
        //cause issues
        //std::cout << "Couldn't open file. \n";
    }


    //go through every magic item
    string item;

    for (int i = 0; i < NUM_OF_ITEMS; i++) {
        item = magicItems[i];

        //create the stack and queue
        Stack myStack;
        Queue myQueue;

        //add each letter to stack and queue (appropriately)
        for (int j = 0; j < item.length(); j++){
            
            if(magicItems[i][j] != ' '){
                
                //convert current character to an uppercase string
                string character(1,toupper(magicItems[i][j]));
                
                //push character to stack
                //Node myStackNode(character);
                myStack.push(Node(character));
                //test line:
                //std::cout << (myStack.top)->itemName << '+';

                //enqueue character to queue
                //Node myQueueNode(character);
                myQueue.enqueue(Node(character));
                //test line:
                //std::cout << (myQueue.tail)->itemName << ' ';

            }         
        }  
        std::cout << "\nnew word\n";

        bool isPalindrome = true;
        string dequeued;
        string popped;

        //compare letter by letter for palindrome
        //while the stack is filled
        while (!myQueue.isEmpty() && isPalindrome){

//FIX: dequeuing the tail for some reason!!
            dequeued = myQueue.dequeue();
            popped = myStack.pop();
            cout << dequeued <<"=" << popped << "?\n";

            //compare the single character Nodes
            if(dequeued != popped){
            //if(0 ==0){
                isPalindrome = false;
            }
            isPalindrome = false;
        }

        if(isPalindrome){
            std::cout << item << '\n';
        }

        //Clear stack and queue

    }   
    //*/  
}