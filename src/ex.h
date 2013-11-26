#ifndef LinkedList_ex_h
#define LinkedList_ex_h

class listException 
{
public:
    listException(std::string m = "Index out of bounds");
    ~listException();
    std::string what();
    
private:
    std::string msg;
};

listException::listException(std::string m):msg(m) {}

listException::~listException() {}

std::string listException::what() {
    return msg;
}

#endif



