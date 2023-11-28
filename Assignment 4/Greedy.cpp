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


//Return vector of Spices in unit price descending order (valuable->cheap)
vector<Spice*> sortValues(vector<Spice*> spices){
    int maxPosition;
    
    for (int i = 0; i < spices.size() - 1; i++){
        maxPosition = i;
        
        for (int j = i+1; j < spices.size(); j++){

            //compare for alphabetical order
            if (spices[j]->unitPrice > spices[maxPosition]->unitPrice){
                maxPosition = j;
            }
        }
        //swap
        Spice* temporarySpice = spices[maxPosition];
        spices[maxPosition] = spices[i];
        spices[i] = temporarySpice;
    }
    return spices;
}



//Main Program!
//Read the file, create Spices, create knapsacks, sort Spices, find optimal Spice combinations for each knapsack

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
    for (int line = 0; line < fileLength; line ++){

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
        else if (currentLine.compare(0,8,"knapsack") == 0){
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

    //sort spices in most valuable order
    spices = sortValues(spices);


    //loop through all knapsacks 
    for (int sackNumber = 0; sackNumber < knapsackCapacities.size(); sackNumber++){
        
        //reset all spices to availible
        for (int i = 0; i < spices.size(); i++){
            spices[i]->isAvailable = true;
        }

        int capacity = knapsackCapacities[sackNumber];
        int spiceNumber = 0;
        int sackQuantity = 0;
        float sackPrice = 0.0;
        bool isFull = false;

        //while loop to loop through all spices (in most valuable order)
        while (! isFull && spiceNumber < spices.size()){
            
            //if there is enough space, take all of the spice
            if (spices[spiceNumber]->quantity <= capacity){
                sackQuantity += spices[spiceNumber]->quantity;
                sackPrice += spices[spiceNumber]->totalPrice;
            }

            //if not, take what you can
            else{
                int remainingSpace = capacity - sackQuantity;
                sackQuantity += remainingSpace;
                //add only what you can
                sackPrice += spices[spiceNumber]->unitPrice * remainingSpace;
            }

            //check if sack is full
            if(sackQuantity == capacity){
                isFull = true;
            }
            spiceNumber ++;
        }
        cout << "Capacity: " << capacity << "\n\tQuantity: " << sackQuantity << "\n\tPrice: $" << sackPrice << endl; //test line
    }    
}