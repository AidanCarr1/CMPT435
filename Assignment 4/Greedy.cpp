// Aidan Carr
// November 27, 2023
// Greedy Algorithm: The Spice Heist

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>
#include <vector>
using namespace std;


//GLOBAL variables
const string _FILE_NAME = "spice.txt";


//SPICE CLASS
class Spice {

public:
    string name;
    float totalPrice;
    int quantity;
    float unitPrice;
    bool isAvailable;

    //Constructor
    Spice(string nameInput, float priceInput, int qtyInput){
        name = nameInput;
        totalPrice = priceInput;
        quantity = qtyInput;
        unitPrice = totalPrice / quantity;
        isAvailable = false;
    }
};


//Main Program!
//Read the file,

int main(){

    //open the file
    std::ifstream spiceFile;
    spiceFile.open(_FILE_NAME);
    
    //create vector
    int fileLength = 0;
    vector<string> fileCommands;

    string currentLine;
    if (spiceFile.is_open()){

        //read the file into a vector
        while (spiceFile){
            //insert commands into vector
            std::getline(spiceFile, currentLine); 
            fileCommands.push_back(currentLine);
            fileLength++;
        }

        //IO duplicates final line, delete it
        fileCommands.pop_back(); 
        fileLength--;
    }    
    else {}
    spiceFile.close();   

    //create vectors for all information
    vector<int> knapsackCapacities;
    vector<Spice*> spices;


    //INTERPRET ALL COMMANDS
    for(int line = 0; line < fileLength; line ++){

        //get line as a string, and find length
        string currentLine = fileCommands[line]; 
        int strLength = currentLine.length();

        //empty line, ignore line
        if (currentLine.compare(0,1,"") == 0){
        }

        //comment, ignore line
        else if (currentLine.compare(0,2,"--") == 0){
        }

        //new Spice
        else if (currentLine.compare(0,5,"spice") == 0){
            
            //get name
            int equalsIndex = currentLine.find("=");
            int colonIndex = currentLine.find(";");
            string name = currentLine.substr(equalsIndex +2, colonIndex - equalsIndex-2);

            //get total_price
            currentLine = currentLine.substr(colonIndex +2, strLength - colonIndex-2);
            equalsIndex = currentLine.find("=");
            colonIndex = currentLine.find(";");
            string strPrice = currentLine.substr(equalsIndex +2, colonIndex - equalsIndex-2);
            float totalPrice = std::stof(strPrice);

            //get qty
            currentLine = currentLine.substr(colonIndex +2, strLength - colonIndex-2);
            equalsIndex = currentLine.find("=");
            colonIndex = currentLine.find(";");
            string strQuantity = currentLine.substr(equalsIndex +2, colonIndex - equalsIndex-2);
            int quantity = std::stof(strQuantity);

            //std::cout << "Name: " << name << ". Total Price: $" << totalPrice << ". Quantity: " << quantity << "." << endl; //test line
            
            //create Spice object using data
            Spice* mySpice = new Spice(name, totalPrice, quantity);
            spices.push_back(mySpice);

        }

        //new knapsack size
        else if (currentLine.compare(0,4,"knap") == 0){
            int equalsIndex = currentLine.find("=");
            string strCapacity = currentLine.substr(equalsIndex +2, strLength - equalsIndex -3);
            int capacity = std::stof(strCapacity);
            //add capacity to vector of knapsacks
            knapsackCapacities.push_back(capacity);

        }

        //error check
        else {
            std::cout << "ERROR on line " << line+1 << ":\n\t'" << currentLine << "'" << std::endl;
        }
            
    }

    //sort spices in value order

    //loop through all knapsack capacities 
    for(int cap = 0; cap < knapsackCapacities.size(); cap++){

        //reset all spices to availible

        //while loop to loop through all spices (in most valueble order)
            //take most possible spice, so to next spice 
            //print?
        //
    }
            
}