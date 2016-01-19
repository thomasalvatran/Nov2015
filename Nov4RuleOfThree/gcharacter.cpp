
/* Reel Learning youtube.com
 * GCharacter.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: tv
 */

#include "gcharacter.h"
using namespace std;

//Constructor
GCharacter::GCharacter(string n, int cap)
{
    name = n;
    capacity = cap;
    used = 0;
    toolHolder = new string[cap];
}
//Copy constructor
GCharacter::GCharacter(const GCharacter& source)
{
    cout << "Copy constructor called" << endl;
    this->name = source.name;
    this->capacity = source.capacity;
    used = source.used;
    toolHolder = new string[source.capacity];
    copy(source.toolHolder, source.toolHolder + used, toolHolder);
//	for(int i = 0 ; i < used; i++)
//	{
//		toolHolder[i] = source.toolHolder[i];
//	}
}
//Overload assignment
GCharacter& GCharacter::operator=(const GCharacter& source)
{
    cout << "Overload Assignment called" << endl;
    //Check for self assignment
    //gc1 = gc1
    if (this == &source)
    {
        return *this;
    }
    this->name = source.name;
    this->capacity = source.capacity;
    used = source.used;
    copy(source.toolHolder, source.toolHolder + used, this->toolHolder);
    return *this;
}
//Destructor
GCharacter::~GCharacter()
{
    cout << "Destructor called for " << this->name << "@ this memory location " << this << endl;
    delete[] toolHolder;
}
// Inserting a new tool into our toolHolder
void GCharacter::Insert(const string& toolName)
{
    if (used == capacity)
    {
        cout << "Tool Holder is full" << endl;
    }
    else
    {
        toolHolder[used] = toolName;
        used ++;
    }
}
std::ostream& operator<<(std::ostream& os, const GCharacter& gc)
{
    os << "Game Character " << gc.name << "\nhas the following tools" << endl;
    for (int i = 0; i < gc.used; i++)
    {
        os << gc.toolHolder[i] + "|";
    }
    return os << endl;
}



