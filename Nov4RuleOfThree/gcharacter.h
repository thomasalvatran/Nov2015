#ifndef GCHARACTER_H
#define GCHARACTER_H

#include <iostream>
#include <string>


class GCharacter {
    friend std::ostream& operator <<(std::ostream& os, const GCharacter& gc);
public:
    static const int DEFAULT_CAPACITY = 5;
    //constructor
    GCharacter(std::string name = "John", int capacity = DEFAULT_CAPACITY);
    //copy constructor
    GCharacter(const GCharacter& source);
    //Overload assignment
    GCharacter& operator=(const GCharacter& source);
    //Destructor
    ~GCharacter();
    //Insert a new tool
    void Insert(const std::string& toolName);
private:
    //data members
    std::string name;
    int capacity;
    int used;
    std::string *toolHolder;
};

#endif // GCHARACTER_H

