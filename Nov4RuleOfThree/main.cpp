/*Reel Learning youtube.com
 * GCApp.cpp
 *
 *  Created on: Jun 24, 2014
 *      Author: tv
 */
#include "gcharacter.h"
using namespace std;

GCharacter exCopyConstructor(GCharacter tempGC)
{
    cout << "Copy constructor called twice" << endl;
    cout << "Once for the formal parameter being passed by value" << endl;
    cout << "Once for the return value" << endl;
    return tempGC;
}

int main()

{
    GCharacter gc1;

    gc1.Insert("potion");
    gc1.Insert("crossbow");
    gc1.Insert("candle");
    gc1.Insert("cloak");
    gc1.Insert("sword");
//	gc1.Insert("book of spells");

    cout << gc1;  // << endl;
    GCharacter gc2("Bob", 5);
    gc2.Insert("ax");
    cout << gc2 << endl;
    exCopyConstructor(gc2);
    cout << "--" << endl;
//    GCharacter gc3 = gc2;  	//copy constructor gc3 object is not created
    GCharacter gc3(gc2);        //copy constructor gc3(gc2) == gc3=gc2
    cout << "--" << endl;
    gc2 = gc1;				//overload assignment both objects gc2 and gc1 are created
    cout << "--" << endl;
    cout << "gc1: " << gc1 << endl;
    cout << "gc2: " << gc2 << endl;
    cout << "gc3: " << gc3 << endl;
    return 0;

}

