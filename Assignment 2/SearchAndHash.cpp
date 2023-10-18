// Aidan Carr
// October 18, 2023
// Searching and Hashing

//Compiled using g++

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <time.h>
using namespace std;


//GLOBAL variables
const int _NUM_OF_ITEMS = 666; //CONSTANT number of magic items
const string _FILE_NAME = "magicitems.txt";
int _comparisons = 0; //count comparisons for each search method


//Compare 2 strings in alphabetical order
//return true is first string comes first, false if second string is first
bool isLessThan(string first, string second){
    
    //find correct length to avoid out of bound error when comparing
    int length1 = first.length();
    int length2 = second.length();
    int length = (length1<length2)? length1 : length2;

    //+1 comparison
    _comparisons++;

    //compare letter by letter until an alphabetically 'smaller' string is found (disregard CAPs)
    for (int i = 0; i < length; i++){
        if (toupper(first.at(i)) < toupper(second.at(i))){
            return true;
        }
        else if (toupper(first.at(i)) > toupper(second.at(i))){
            return false;
        }
    }

    //tie goes to the shorter string
    return (length1<=length2)? true : false;
}


//Merge Sort Algorithm, sort given array with length (recursive)
//From Assignment 1/Sorting.cpp
void mergeSort(string items[], int length){
    //Base case: when length 1, start conquering, until then, divide
    if (length > 1){
        
        int firstHalfLength = length/2;
        int secondHalfLength = length - firstHalfLength;
        string half1[firstHalfLength];
        string half2[secondHalfLength];

        //fill in half1
        for (int i = 0; i < firstHalfLength; i++){
            half1[i] = items[i];
        }

        //fill in half2
        for (int i = 0; i < secondHalfLength; i++){
            half2[i] = items[firstHalfLength+i];
        }

        //sort each half
        mergeSort(half1, firstHalfLength);
        mergeSort(half2, secondHalfLength);
        
        int sortingPos = 0;
        int firstPos = 0;
        int secondPos = 0;

        while (sortingPos < length){
  
            //if one half is completely put into sorted array, 
            //put the rest of the other half into sorted array
            if (firstPos == firstHalfLength){
                items[sortingPos] = half2[secondPos];
                secondPos ++;
            }
            else if (secondPos == secondHalfLength){
                items[sortingPos] = half1[firstPos];
                firstPos ++;
            }

            //sort 2 ordered arrays into one larger array
            else if (isLessThan(half1[firstPos],half2[secondPos])){
                items[sortingPos] = half1[firstPos];
                firstPos ++;
            }
            else {
                items[sortingPos] = half2[secondPos];
                secondPos ++;
            }
            
            //move to next position to be sorted
            sortingPos ++;
        }
    }
}