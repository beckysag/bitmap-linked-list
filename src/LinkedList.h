// Class template for holding a linked list

#ifndef LINK_LIST_H
#define LINK_LIST_H
#include "NodeClass.h"
#include "ex.h"

template <class T> 
class LinkList 
{
private:
    node<T> *head, *tail;   // Head and tail pointers
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
    void push_front(const T&);
        // Inserts an item at the front of the list
    void push_back(const T&);
        // Inserts an item at the back of the list
    void pop_front();
        // Deletes the node at the front of the list
    void pop_back();
        // Deletes the node at the end of the list
    void remove(int i);
        // Deletes the node at position i in the list
    void clear();
        // Removes all nodes from the linked list
    T get(int i) const throw (listException);
        // Returns a copy of the ith node in the list
    int find(const T&) const;
        // Returns the index of the node passed, if found
        // Else returns ‐1
    int size() const;
        // Returns the number of elements in the list
};
//*******************************************************
// Copy constructor
//*******************************************************
template <class T>
LinkList<T>::LinkList(const LinkList& src) {
    head = tail = NULL;
    *this = src;
}

//*******************************************************
// Overloaded assignment operator
//*******************************************************
template <class T>
const LinkList<T>& LinkList<T>::operator=(const LinkList& rhs) 
{
    node<T> *rhsPtr;       // To point to current node in rhs list
    node<T> *newNode;       // To create new nodes
    node<T> *temp;          // To point to current node in new list
    
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
        newNode = new node<T>;
        head = newNode;
                
        // Copy value of val into new node        
        newNode->val = rhsPtr->val;
        
        // Position temp at head
        temp = head;
        
        // Move rhsPtr to next node
        rhsPtr = rhsPtr->next;
        
        // Keep adding nodes until rhsPtr reaches end of list
        while (rhsPtr != NULL) {
            // Create a new node
            newNode = new node<T>;
            
            // Create a link to the new node
            temp->next = newNode;
            
            // Position temp at new node
            temp = newNode;
                        
            // Copy value of val into new node
            newNode->val = rhsPtr->val;
            
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
template <class T>
void LinkList<T>::push_front(const T& item) {
    
    // Create new node
    node<T> *newNode = new node<T>(item);

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
template <class T>
void LinkList<T>::push_back(const T& item) {
    node<T> *newNode;               // To point to new node
    newNode = new node<T>(item);    // Allocate node & store item
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
template <class T>
void LinkList<T>::pop_front() 
{
    node<T> *temp;      // To point to head
    
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
template <class T>
void LinkList<T>::pop_back() 
{
    node<T> *temp;      // To traverse the list
    node<T> *nextNode;
    
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
template <class T>
void LinkList<T>::remove(int i) 
{
    int count = 1;      // To count position in list, from 1  
    node<T> *current;   // To point to current node while traversing
    node<T> *prevNode;  // To point to previous node
    
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
template<class T>
void LinkList<T>::clear() 
{
    node<T> *current;       // To point to current node
    node<T> *nextNode;      // To point to next node 
    
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
template <class T>
T LinkList<T>::get(int i) const throw (listException)
{
    int count = 1;          // To count position in list    
    node<T> *temp;          // To point to current node
    
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
template<class T>
int LinkList<T>::find(const T& item) const 
{
    int count = 1;          // To count position in list
    node<T> *temp;          // To point to current node
    
    // Position temp at head of list
    temp = head;               
    
    // Move through list until node with item is found
    while (temp != NULL && temp->val != item) { 
        temp=temp->next;
        count++;
    }
    
    // If end of list was reached with no match found,
    // return -1. Else, return count
    if (!temp) 
        count = -1;    
    return count;
}

//*******************************************************
// size returns an int with the number of elements in
// the linked list
//*******************************************************
template <class T>
int LinkList<T>::size() const {
    return numElements; 
}

//*******************************************************
// Default Constructor                                  *
// Creates an empty list                                *
//*******************************************************
template <class T>
LinkList<T>::LinkList() {
    head = tail = NULL;
    numElements=0;
}

//*******************************************************
// Destructor                                           *
// Deletes every node in the list                       *
//*******************************************************
template <class T>
LinkList<T>::~LinkList() 
{
    node<T> *current;       // To point to current node
    node<T> *nextNode;      // To point to next node 
    
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
















