// Class template for holding a linked list node
#ifndef NODE_H
#define NODE_H

template <class T>
class node 
{
private:
    T val;      // node value
    node<T> *next; // pointer to the next node
public:
    node();
        // Default constructor
    node(T);
        // Constructor that takes a T type argument
    ~node();
        // Destructor
    template <class> friend class LinkList;
        // Allow LinkList class to access private member variables
};

//*******************************************************
// Default Constructor                                  *
// Creates an empty node with a NULL pointer            *
//*******************************************************
template <class T>
node<T>::node() {
    next = NULL;
}

//*******************************************************
// Constructor                                          *
// Creates a node with val = item and a NULL pointer    *
//*******************************************************
template <class T>
node<T>::node(T item) {
    next = NULL;
    val = item;
}

//*******************************************************
// Destructor                                           *
// Prints value of node as it is deleted                *
//*******************************************************
template <class T>
node<T>::~node() {
    std::cout << "Destructing node: " << val << std::endl;
}



template <>
class node<char*> 
{
private:
    char* val;      // node value
    node<char*> *next; // pointer to the next node
public:
    node();
    // Default constructor
    node(char*);
    // Constructor that takes a T type argument
    ~node();
    // Destructor
    template <class> friend class LinkList;
    // Allow LinkList class to access private member variables
};

//*******************************************************
// Default Constructor                                  *
// Creates an empty node with a NULL pointer            *
//*******************************************************
node<char*>::node() {
    next = NULL;
}

//*******************************************************
// Constructor                                          *
// Creates a node with val = item and a NULL pointer    *
//*******************************************************
node<char*>::node(char* item) {
    next = NULL;
    val = item;
}

//*******************************************************
// Destructor                                           *
// Prints value of node as it is deleted                *
//*******************************************************
node<char*>::~node() {
    std::cout << "Destructing node: " << val << std::endl;
}

#endif
