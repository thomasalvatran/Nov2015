// home/tovantran/Ctest/smartpointerQC.cpp --> 2014-06-22 by ./.tv  owner:
// Youtube video Dive into C++11
// http://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <memory> //unique_ptr
using namespace std;
 //ownership smart pointer
    struct Resource {};
    void passByValue(unique_ptr<Resource> mResPtr){}
    void passByConstRef(const unique_ptr<Resource>& mResPtr){}
    void passByRawPtr(Resource* mResPtr){}
void whatShouldIPassByToMaintainOriginalOwership()
{
    unique_ptr<Resource> resPtr{new Resource}; //ownership is resPtr
//    passByValue(resPtr); //unique pointer cannot copy
    passByConstRef(resPtr); //OK
    passByRawPtr(resPtr.get()); //OK
}
void iHaveToTransferOwnershipWhatNow() //move semantics transfer ownership
{                                      //move ownership
    unique_ptr<Resource> resPtr(new Resource);
    {
        string source{"Hello"};
        string target{move(source)};  //source->target move semantics
    }
    std::unique_ptr<Resource> newOwner{std::move(resPtr)};
    passByValue(std::move(newOwner));
}

struct Resource1{};         //share resources expensive to copy so share

struct NaiveGameEffect
{
    Resource animation;     //expensive move or copy a lot to copy
    Resource backgroundTexture;
    Resource particleTexture;
    Resource sound;
};

struct GameEffect //share the resources gameEffect owner but sharing
{
    std::shared_ptr<Resource> animation; //object alive share pointer alive
    shared_ptr<Resource> backgroundTexture;
    shared_ptr<Resource> particleTexture;
    shared_ptr<Resource> sound;
};

class FreeStorePoint {
public:
  FreeStorePoint(int *mInt) : pointer{mInt}
  {
    cout << "Ctor FreeStorePointer" << endl;
  }
  ~FreeStorePoint() {
    cout << "Dtor FreeStorePointer" << endl;
    delete pointer;
  }
  int *get() { return pointer; }

  int *getPointer() const;
  void setPointer(int *value);

private:
  int *pointer;  //pointer to object (points to our free-store-allocated 'int'
};
int *FreeStorePoint::getPointer() const { return pointer; }

void FreeStorePoint::setPointer(int *value) { pointer = value; }

class Person {
  string Name;
  int age;
  // main.cpp:12: warning: 'Person::pName' will be initialized after [-Wreorder]

public:
  Person() : Name(0), age(0) {}
  Person(const string Name, const int age) : Name(Name), age(age) {}
  ~Person() { cout << "Dtor1" << endl; }

  void Display() {
    cout << Name << " " << age << endl;
    printf("Name = %s Age = %d \n", Name.c_str(), age);
    // cannot pass objects of non-trivially-copyable type 'const string {aka
    // const struct std::basic_string<char>}' through '...'
  }
  void Shout() { printf("Ooooooooooooooooo"); }
};
template <class T>
class SP {
private:
  T *pData; // pointer to person class
public:
  SP(T *pValue) : pData(pValue) {}
  ~SP() {
    // pointer no longer required
    cout << "Dtor2" << endl;
    delete pData;
  }
  T &operator*() { return *pData; }

  T *operator->() { return pData; }
};
int main(int argc, char *argv[]) {
  char msg[] = "Scott";
  char *msg1 =
      (char *)"Scott"; // warning: deprecated conversion from string constant
  string msg2 = "Scott";
  SP<Person> p(new Person{
      "Scott", 25}); // warning: deprecated conversion from string constant
                     //    SP<Person> p(new Person(msg1, 25)); //OK
  p->Display(); //OR below //need *operator->
  p.operator *().Display(); //need &operator*
  p.operator ->().Diplay(); //Do nothing

  // Dont need to delete Person pointer..
  // Dont need to delete Person pointer..
  {
      FreeStorePoint test = new int(10);
      FreeStorePoint test1(new int(11)); //same as above
      cout << *(test.getPointer()) << endl; //not test.getPointer()
//      FreeStorePoint *p = new int(10); //pass pointer to ctor
                                     //cannot convert int* to FreeStorePoint*
      std::unique_ptr<int> test2(new int(10)); //generic
  } //Out of scope
  {
      unique_ptr<double> smartPointers{new double{20.3}};
      unique_ptr<string> are {new string{"extremely"}};
      unique_ptr<char> versatile{new char{'!'}};
  }
  {
      size_t runtimeSize(10);
      unique_ptr<int[]> array{new int[runtimeSize]};
      auto pointertoArray(array.get()); //raw pointer just to refer no owner
  }
  {
      string testString{"This string is not on the free store"}; //stack
      string* pointerToString(&testString); //raw pointer
  } //out of scope stack delete
  struct TextureResource
  {
      TextureResource() { cout << "Ctor TextureResource" << endl; }
      ~TextureResource() {cout << "Dtor TextureResource" << endl; }
      //Non-copyable(using C++11's new = 'delete' feature)
      TextureResource(const TextureResource&) = delete;
      TextureResource& operator=(const TextureResource&) = delete;
  };//no allocation and dellocation slows down the game
  shared_ptr<TextureResource> source(new TextureResource); //share pointer increment 1
  struct TextureObject
  {
      shared_ptr<TextureResource> texture;
  };
  {
      TextureObject to1;
      to1.texture = source;  //share pointer increment 2
  }//out of scope share pointer increment back to 1
  {
      TextureObject to2; to2.texture = source; //TextureObject
      TextureObject to3; to3.texture = source; // is shared by
      TextureObject to4; to4.texture = source; // all objects
      TextureObject to5; to5.texture = source; // to2 - to6
      TextureObject to6; to6.texture = source;
  }
  std::shared_ptr<TextureResource> newOwner{source}; //share ownership count = 2
  source.reset(); //share pointer increase (not abuse) run time operator
  return 0;
}
