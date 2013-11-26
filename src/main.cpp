/*
 * Rebecca Sagalyn
 * Georgetown University
 * CS052 - Computer Science II
 * Bitmap Linked List
 * 
 * This project creates a linked list of bitmap images and displays them
 * on the screen
 * 
 */


#include <iostream>
#include "CImg.h"
#include "LinkedList.h"
#include "LinkedListCstring.h"
#include "ex.h"
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

using namespace std;
using namespace cimg_library;

//***********************************************************
// function to print out the contents of a Linked List      *
// prints "Empty List" if list is empty
//***********************************************************
template <typename T>
const void printList(const T& list, string name = "Linked List") {
    cout << "Contents of " << name << "..." << endl; 

    if (list.size() == 0) {
        cout << "Empty List" << endl;
    }
    else {
        for(int i = 1; i <= list.size(); i++)
            cout << "Content of " << name << " [" << i << "]: " << list.get(i) << endl;

        cout << endl;           
    }
}


int main(int argc, const char * argv[])
{       
    // Linked list & CImg variables
    LinkList<char*>cList;
    CImgList<unsigned char> list;
    CImg<unsigned char> *img;
    
    // Directory variables
    char *drPath = NULL;
    DIR *dir = NULL;
    struct dirent *drnt= NULL;
    char *given = NULL;     // To hold path supplied by user
    string input;           // To hold path supplied by user
    
    // Check for file name on command line
    if (argv[1] == NULL ) { 
        cout << "Please enter directory.\n";
        cin >> input;
        given = new char[strlen(input.c_str() + 1)]; 
        strcpy(given, input.c_str());
    }  else {
        given = new char[strlen(argv[1] + 1)]; 
        strcpy(given, argv[1]);        
        cout << "Directory supplied: " << given << endl;
    }
    
    // Check if user ended directory with a forward slash; if not, add one    
    char lastChar = given[strlen(given)-1];

    if (lastChar != '/') {
        drPath = new char[strlen(given) + 2];
        strcpy(drPath, given);
        strcat(drPath, "/");
    }
    else {
        drPath = new char[strlen(given) + 1];
        strcpy(drPath, given);
    }
    
    
    
        
    //***********************************************************
    // Example of linked list with integers                     *
    //***********************************************************

    // Create list
    LinkList<int> myList;   
    
    // Add nodes
    myList.push_back(101);
    myList.push_back(102);
    myList.push_back(103);
    myList.push_back(104);
    myList.push_back(105);
    
    printList(myList, "Integer List");
    
    // Pop front example
    myList.pop_front(); cout << endl;
    cout << "Contents of Integer list after pop_front..." << endl; 
    printList(myList, "Integer List");
    
    // pop back example
    myList.pop_back(); cout << endl;
    cout << "Contents of Integer List after pop_back..." << endl; 
    printList(myList, "Integer List");

    // Copy constructor
    LinkList<int> newIntList(myList);
    printList(newIntList, "New Integer List");
    
    // Clear list
    cout << "Clearing myList...\n\n"; 
    myList.clear(); cout << endl;
    


    //***********************************************************
    // Read image names from file                               *
    //***********************************************************
    
    // Open dir directory stream using the syscall opendir
    dir = opendir(drPath);    
    
    // If directory can't be found, then close stream & exit
    if (dir == NULL) {
        cout << "Error" << endl;
        exit(-1);
    }
    
    // Otherwise, directory was found and continue...
    else {
        
        // Read each directory entry in directory stream
        // until reaching the null pointer
        while ((drnt = readdir(dir)) != NULL) {
            
            // Skip the "." & ".." because I dont know what they are
            if (strcmp(drnt->d_name, ".") != 0 && 
                (strcmp(drnt->d_name, "..") != 0) ) {                
                
                // create new c-string large enough to store full filename        
                //char *filePath; 
                //filePath = new char[strlen(drnt->d_name) + strlen(drPath) + 2];  
                
                //concat filename to end of directory path
               // strcpy(filePath, drPath);
              //  strcat(filePath, drnt->d_name);

                cList.push_back(drnt->d_name);
            }
        }//end while
    }//end if
        
    // Close directory stream
    closedir(dir);
    
    
    //***********************************************************
    // examples of operations of c-string type linked list      *
    //***********************************************************
    
    // Copy constructor
    LinkList<char*> newList(cList);
    printList(newList, "new List");

    try {
        // Print contents of cList
        printList(cList, "cList");
        
        //Show pop_front
        cout << "Executing pop_front...\n\n"; 
        cList.pop_front(); cout << endl;
        printList(cList, "cList");
        
        //Show pop_back
        cout << "Executing pop_back...\n\n"; 
        cList.pop_back(); cout << endl;
        printList(cList, "cList");
        
        //Show remove
        cout << "Removing first node...\n\n"; 
        cList.remove(1); cout << endl;
        printList(cList, "cList");
        
        //Show get
        cout << "Getting node 1...\n"; 
        cout << "Node 1: " << cList.get(1) << endl << endl;

    } catch (listException &ex) {
        cout << ex.what() << endl;
    }
    
    //Show find
    char* item = new char[13];
    strcpy(item, "raindrops.bmp");    
    cout << "Finding 'raindrops.bmp' ...\n"; 
    cout << "Index: " << cList.find(item) << endl << endl;

    //Show clear 
    cout << "Clearing list...\n\n"; 
    cList.clear(); cout << endl;
    printList(cList, "cList");
    

    
    //***********************************************************
    // Display bitmaps on screen                                *
    //***********************************************************
    for (int i=1; i < newList.size()+1; i++) {
        char* fname = newList.get(i);     
        char *filePath = new char[strlen(fname) + strlen(drPath) + 2];  
        
        strcpy(filePath, drPath);
        strcat(filePath, fname);
                
        img = new CImg<unsigned char>(filePath);
        list.insert(*img);        
        delete filePath;
    }
    list.display("Bitmap Linked List");
    
    return 0;
}

