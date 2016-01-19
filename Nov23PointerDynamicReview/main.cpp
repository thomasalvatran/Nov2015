// Youtube video Dive into C++11 - Memory management
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

int main() {
  {
    // block
  }
  {
    int var; // allocate memory in stack
    var = 5;
  } // variable out of scope or delocate or free
  //    var = 5; Error ouf of scope
//  {
    struct Example {
      int m_Id; // m = member of class m_Id or mId data member
      Example(int id) : m_Id(id) { std::cout << "Ctor " << m_Id << "\n"; }
      ~Example() { std::cout << "Ctor " << m_Id << "\n"; }
    };
    {
      Example ex1(1); // LIFO last in first out
      Example ex2(2); // LIFO
    }
//        return 0;  // run up to here
//  }
// Nested block
  {
     Example ex5(5);
     {
         Example ex6(6);
     }
     Example ex7(7);
  }
//    return 0;
    //type, name, value, address
    // int   i(10)        &i  (location memory / address of)
//    int i = 10;
//    int* = pointerToI(&i)  read from right pointer to I  of int* and initialize &k
    {
    int i(11); // only C++
    printf("%d\n", i);
    // * deref get value of pointer to  / *i is value of i
    //* operator derefence
    }
    {
    int i(10);
    float f(5.f);
    int k;
                            // int *pointertoI = &i;
    int *pointertoI(&i);   //* dereference the pointer
    float *pointertoF(&f);
    int *pointertoK(&k);
    std::cout << *pointertoI << " " << *&i << " " << i << "\n";
    std::cout << *pointertoF << " " << *&f << " " << f << "\n";
    *pointertoK = 15;
    std::cout << k << " ============== " << *pointertoK << "\n";
    }
    int *pointertoNested;
    {
        int nestedNumber(42); //in C++ only nestedNumber = 42;
        pointertoNested = &nestedNumber;
    }
    std::cout << *pointertoNested << "\n";
    std::vector<int>* pointerToVec;
    {
        std::vector<int> vec{1, 2, 3, 4}; //vec = {1, 2}
        pointerToVec = &vec;
        cout << vec.size() << endl;
        cout << pointerToVec->size() << endl; //(*pointerToVec).size();

        pointerToVec->push_back(1);

        cout << vec.size() << endl;
        cout << pointerToVec->size() << endl;  //(*pointerTovec).size() == pointerToVec->size()
    }//get out of scope
    pointerToVec->push_back(1);  //may print correct may garbage may crash
    cout << pointerToVec->size() << endl;

    pointerToVec->clear();
    cout << pointerToVec->size() << endl;

    int* dynamicNumber(new int{7}); //at run time  in HEAP NEED DELETE (NOT STACK)
    int *d = new int(12);
    d  = (int *)11;
    d  = new int{122}; // == new int(122);
//    d = (int *)14;
    delete dynamicNumber;
    dynamicNumber = nullptr; //invalid pointer / point to null

    //dynamic location is automatic will not be destroyed
    printf("%d\n", *d);
    delete d;
    d = nullptr; //good practice to set the pointer to null (invalid pointer)
//out of scope dynamic will not be destroyed automatic like automatic storage varialble
//array continue block of memory contains specific numbers of object (dynamic location)
    int automaticArray1[10];
    automaticArray1[0];
    automaticArray1[1];
/*
    constexpr int arraySize{5 + 5}; //C++11
//    valid arraySize is a compile time constant

    int automaticArray2[arraySize];
    int runtimeSize;
    cin >> runtimeSize;
    int* pointerToArray = new int[runtimeSize];
    pointerToArray[10] = 44;
    for(int i = 0; i < runtimeSize; i++)
        cout << pointerToArray[i] << " " << i << ",";
        cout << endl;
    delete pointerToArray; //WRONG
    delete[] pointerToArray; //delete dynamic allocate array
*/

    Example* ex1{new Example{1}}; //run time allocate free store /heap
    Example* ex2{nullptr};

    {
        Example* ex3{new Example{3}};
        ex2 = ex3;   //not copy assign the same address shallow copy
    }//end of the block ex3
    delete ex1;
    delete ex2;  //will delete ex3 as well both has the same address.

    struct NaiveVector
    {
        int capacity{2};
        int* ptrToArray{new int[capacity]};
        int size{0};  //size = 0;
        void push_back(int mvalue)
        {
            ptrToArray[size] = mvalue;
            ++size;
            if (capacity < size)
            {
                cout << "Reallocating internal array !" << endl;
                capacity *= 2;
                int* ptrToNewArray{ new int[capacity]};
                for (int i{0}; i < size; ++i)
                     ptrToNewArray[i] = ptrToArray[i];
                delete[] ptrToArray;
                ptrToArray = ptrToNewArray;
            }
        }
        void printValues()
        {
            cout << endl;
            for(int i = 0; i < size; i++)
                cout << ptrToArray[i] << ", ";
            cout << endl << "Size: " << size << endl;
            cout << "Capacity: " << capacity << endl << endl;
        }
    };
    NaiveVector nv;
    nv.push_back(1);
    nv.printValues();

    nv.push_back(2);
    nv.push_back(3);
    nv.push_back(4);
    nv.printValues();

    nv.push_back(5);
    nv.push_back(6);
    nv.push_back(7);
    nv.push_back(8);
    nv.push_back(9);
    nv.push_back(10);
    nv.push_back(11);
    nv.push_back(12);
    nv.push_back(13);
    nv.printValues();
}
