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
    }    
    else {}
    spiceFile.close();   

    vector<int> knapsackCapacities;


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

            std::cout << "Name: " << name << ". Total Price: $" << totalPrice << ". Quantity: " << quantity << "." << endl; //test line
            
            //create spice object? using data

        }

        //new knapsack size
        else if (currentLine.compare(0,4,"knap") == 0){
            int equalsIndex = currentLine.find("=");
            string strCapacity = currentLine.substr(equalsIndex +2, strLength - equalsIndex -3);
            int capacity = std::stof(strCapacity);
            //add capacity to vector of knapsacks
            knapsackCapacities.push_back(capacity);

        }
            
    }
            
}