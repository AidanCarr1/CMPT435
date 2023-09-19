// Aidan Carr
// September 11, 2023
// Node Class

#include <iostream>
#include <string>
using namespace std;

class Node {

public:
    int id;
    string itemName;
    //object nextNode;
    Node(int idInput, string itemNameInput){
        idInput = id;
        itemName = itemNameInput;
        //object nextNode;
    }
    /*
    node getNextNode() {
        return nextNode;
    }
    */
};

int main(){
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
}