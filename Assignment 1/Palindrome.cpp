// Aidan Carr
// September 28, 2023
// Palindrome main file

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;
const int NUM_OF_ITEMS = 666;


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
    void push(Node* newTop){
        newTop->next = top;
        top = newTop;
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
        if(tail == nullptr || head == nullptr){
            return true;
        }
        return false;
    }

    //enqueue/add to back of queue
    void enqueue(Node* newTail){
        //add a head if it is the first in line
        if(isEmpty()){
            head = newTail;
            //cout << "i think its empty ";
        }
        else{
            //cout << "head before tail's next: " << head->itemName << '\n';
            //put new tail behind the old tail
            tail->next = newTail;
        }
        //make this queue's tail this new tail
        tail = newTail;
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


//return true if word is a palindrome
//create the stack and queue
bool isPalindrome(string item){
    Stack myStack;
    Queue myQueue;
    Node myStackNodes[item.length()];
    Node myQueueNodes[item.length()];
    string character;

    //create 2 nodes for each character (appropriately)
    for (int letterIndex = 0; letterIndex < item.length(); letterIndex++){

        if(item[letterIndex] != ' '){
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
 
    //std::cout << "\nnew word\n";

    bool isPalindrome = true;
    string dequeued = "";
    string popped = "";

    //compare letter by letter for palindrome
    //while the stack is filled
    while (!myQueue.isEmpty() && isPalindrome){

//FIX: dequeuing the tail for some reason!!
        dequeued = myQueue.dequeue();
        popped = myStack.pop();
        //cout << dequeued <<"=" << popped << "?\n";

        //compare the single character Nodes
        if(dequeued != popped){
        //if(0 ==0){
            isPalindrome = false;
        }
    }

    if(isPalindrome){
        return true;
    }
    return false;

    //Clear stack and queue
}


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
    
    //add to queue
    Queue years;
    years.enqueue(&n0);
    years.enqueue(&n1);
    years.enqueue(&n2);
    years.enqueue(&n3);

    /*pop out of stack
    cout << " BEGIN dequeuing\n";
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n';
    cout << years.dequeue() << '\n'; //will return error message
    
    string dequeued;
    for(int i = 0; i < 4; i++){
        dequeued = years.dequeue();
        cout << dequeued << "?\n";
    }


//*/
    ifstream itemsFile;
    itemsFile.open("magicItems.txt");
    string magicItems[NUM_OF_ITEMS]; 

    string currentLine;
    if (itemsFile.is_open()){
        
        //assign each line to an element in the array
        for (int i = 0; i < NUM_OF_ITEMS; i++) {
            std::getline(itemsFile, currentLine);
            magicItems[i] = currentLine;
            //std::cout << magicItems[i] << '\n';
        }
    }

    else{
        //cause issues
        //std::cout << "Couldn't open file. \n";
    }

    cout << "\n\n";
    //go through every magic item
    string item;

    for (int i = 0; i < NUM_OF_ITEMS; i++) {
        item = magicItems[i];

        if(isPalindrome(item)){
            cout << item << "!\n";
        }
        

    }   
    //*/  
}