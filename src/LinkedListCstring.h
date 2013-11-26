
#ifndef LINK_LIST_C_STRING_H
#define LINK_LIST_C_STRING_H

#include "LinkedList.h"
#include "NodeClass.h"
#include "ex.h"

template <> 
class LinkList<char*>
{
private:
    node<char*> *head, *tail;   // Head and tail pointers
    int numElements;        // Size of list
public:
    LinkList();
    // Default constructor
    ~LinkList();
    // Destructor
    
    // Operator functions
    LinkList (const LinkList&);
    // Copy constructor
    const LinkList &operator=(const LinkList &rhs);
    // overloaded assignment operator
    
    // Linked list operations
    void push_front(char*);
    // Inserts an item at the front of the list
    void push_back(char*);
    // Inserts an item at the back of the list
    void pop_front();
    // Deletes the node at the front of the list
    void pop_back();
    // Deletes the node at the end of the list
    void remove(int i);
    // Deletes the node at position i in the list
    void clear();
    // Removes all nodes from the linked list
    char* get(int i) const throw (listException);
    // Returns a copy of the ith node in the list
    int find(char*) const;
    // Returns the index of the node passed, if found
    // Else returns ‐1
    int size() const;
    // Returns the number of elements in the list
};

//*******************************************************
// Copy constructor
//*******************************************************
LinkList<char*>::LinkList(const LinkList& src) {
    head = tail = NULL;
    *this = src;
}

//*******************************************************
// Overloaded assignment operator
//*******************************************************
const LinkList<char*>& LinkList<char*>::operator=(const LinkList& rhs) 
{
    node<char*> *rhsPtr;       // To point to current node in rhs list
    node<char*> *newNode;       // To create new nodes
    node<char*> *temp;          // To point to current node in new list
    
    // Check for self assignment
    if (this == &rhs) {         
        return *this;
    }
    
    // Free any memory in use
    clear();    
    
    // Position head to point to head of rhs list
    rhsPtr = rhs.head; 

    // Create all the nodes
    if (rhsPtr != NULL) 
    {
        // Create a new head node
        newNode = new node<char*>;
        head = newNode;
        
        // Allocate memory to store val in new node
        newNode->val = new char[strlen(rhsPtr->val) + 1];
        
        // Copy value of val into new node
        strcpy(newNode->val, rhsPtr->val);
        
        // Position temp at head
        temp = head;
        
        // Move rhsPtr to next node
        rhsPtr = rhsPtr->next;

        // Keep adding nodes until rhsPtr reaches end of list
        while (rhsPtr != NULL) {   
            // Create a new node
            newNode = new node<char*>;
            
            // Create a link to the new node
            temp->next = newNode;
            
            // Position temp at new node
            temp = newNode;
            
            // Allocate memory to store val in new node
            newNode->val = new char[strlen(rhsPtr->val) + 1];

            // Copy value of val into new node
            strcpy(newNode->val, rhsPtr->val);

            // Move rhsPtr to next node
            rhsPtr = rhsPtr->next;
        }
        
        // Position tail at last node in new list
        tail = temp;
    }
    
    // Copy numElements
    numElements = rhs.numElements;
    
    return *this;
}

//*******************************************************
// push_front appends a new node containing the value 
// of item, to the front of the list
//*******************************************************
void LinkList<char*>::push_front(char* item) {
    
    // Create new node
    node<char*> *newNode = new node<char*>(item);
    
    // Link new node behind old head node
    newNode->next = head;
    
    // Position head at new node
    head = newNode;
    
    numElements++;
    
    // If list was empty, point tail to head 
    if (tail == NULL) tail = head;
}

//*******************************************************
// push_back appends a new node containing the value    *
// of item, to the end of the list                      *
//*******************************************************
void LinkList<char*>::push_back(char* item) {
    node<char*> *newNode;               // To point to new node
    newNode = new node<char*>(item);    // Allocate node & store item
    if (head == NULL) { //if list is empty
        head = newNode;
        tail = head;
        numElements++;
    }
    else {
        tail->next = newNode;  // Insert newNode as last node in list 
        tail = newNode;        // Move tail to the end
        numElements++;
    }
}


//*******************************************************
// pop_front deletes the node at the front of the list  *
//*******************************************************
void LinkList<char*>::pop_front() 
{
    node<char*> *temp;      // To point to head
    
    // If list is not empty
    if (head != NULL) {
        
        // Position temp at head node
        temp = head;        
        
        // Move head pointer to second node
        head = temp->next;
        
        // Remove first node from memory
        delete temp;
        numElements--;
        
        // If list is empty after deleting head, set tail = NULL
        if (head == NULL) tail = NULL;
    }
}

//*******************************************************
// pop_back deletes the node at the end of the list     *
//*******************************************************
void LinkList<char*>::pop_back() 
{
    node<char*> *temp;      // To traverse the list
    node<char*> *nextNode;
    
    // If list is not empty
    if (head != NULL)
    {
        // If only one node, execute pop_front
        if (head==tail) pop_front();
        else 
        {
            // Initialize temp to head of list
            temp = head;       
            nextNode = temp->next;
            
            // Move until nextNode points to tail node
            while (nextNode->next != NULL) {
                temp = nextNode;                
                nextNode = temp->next;
            }
            
            // Remove last node from list & move tail pointer back
            tail = temp;
            tail->next = NULL;
            
            // Delete last node from memory
            delete nextNode;        
            numElements--;                
        }
    }    
}

//*******************************************************
// remove moves to the ith node in the list, removes it
// and deletes it from memory
//*******************************************************
void LinkList<char*>::remove(int i) 
{
    int count = 1;      // To count position in list, from 1  
    node<char*> *current;   // To point to current node while traversing
    node<char*> *prevNode;  // To point to previous node
    
    // Position current at head node
    current = head;
    
    // Check that i is in scope
    if (i >= 1 && i <= numElements) {
        
        // If i == 1, pop_front
        if (i == 1) 
            pop_front();
        else
        {
            // Move through list, until the ith node 
            while (current != NULL && count != i) {
                prevNode = current;
                current = prevNode->next;            
                count++;
            }
            
            // Remove ith node from the list by linking 
            // previous node to node after it
            prevNode->next = current->next;
            
            // If the tail node was removed, move the tail
            if (prevNode->next == NULL) tail = prevNode;
            
            // Delete node from memory
            delete current;
            numElements--;
        }
    }
}
//*******************************************************
// clear deletes every node in the linked list and      *
// sets the head and tail pointers to NULL              *
//*******************************************************
void LinkList<char*>::clear() 
{
    node<char*> *current;       // To point to current node
    node<char*> *nextNode;      // To point to next node 
    
    // Position current at the head of the list
    current = head;
    
    // Move to the end of the list
    while (current != NULL) {     
        
        // Save a pointer to the next node
        nextNode = current->next;
        
        // Delete current from memory
        delete current;
        
        // Position current at the next node
        current = nextNode;
        
        // Decrement numElements
        numElements--;
    }
    
    // Set head and tail to NULL
    head = tail = NULL;
}

//*******************************************************
// get returns a copy of the item stored at position    *
// i in the link list                                   *
//*******************************************************
char* LinkList<char*>::get(int i) const throw (listException)
{
    int count = 1;          // To count position in list    
    node<char*> *temp;          // To point to current node
    
    // Postion temp at first node
    temp = head;
    
    // Throw listException error if i is out of bounds
    if (i < 1 || i > numElements)
        throw listException();
    
    // Move through list until ith node
    while (temp != NULL && count != i) {
        temp = temp->next;
        count++;
    }
    
    // Return current node's val
    return temp->val;
}

//*******************************************************
// find returns the index of elem, if found;            *
// else returns ‐1                                      *
//*******************************************************
int LinkList<char*>::find(char* item) const 
{
    int count = 1;          // To count position in list
    node<char*> *temp;          // To point to current node
    
    // Position temp at head of list
    temp = head;               
    
    // Move through list until node with item is found
    while ((temp != NULL) && (strcmp(item, temp->val) !=0)) { 
        temp=temp->next;
        count++;
    }
    
    // If end of list was reached with no match found,
    // return -1. Else, return count
    if (temp==NULL) 
        count = -1;    
    return count;
}

//*******************************************************
// size returns an int with the number of elements in
// the linked list
//*******************************************************
int LinkList<char*>::size() const {
    return numElements; 
}

//*******************************************************
// Default Constructor                                  *
// Creates an empty list                                *
//*******************************************************
LinkList<char*>::LinkList() {
    head = tail = NULL;
    numElements=0;
}

//*******************************************************
// Destructor                                           *
// Deletes every node in the list                       *
//*******************************************************
LinkList<char*>::~LinkList() 
{
    node<char*> *current;       // To point to current node
    node<char*> *nextNode;      // To point to next node 
    
    // Position current at the head of the list
    current = head;
    
    // Move to the end of the list
    while (current != NULL) {     
        
        // Save a pointer to the next node
        nextNode = current->next;
        
        // Delete current from memory
        delete current;
        
        // Position current at the next node
        current = nextNode;
        
        // Decrement numElements
        numElements--;
    }
    
    // Set head and tail to NULL
    head = tail = NULL;
}

#endif
