//Bartosz Milewski youtube C++ Concurrency Part 5
//home/tovantran/Ctest/k_r/thread/thread.cpp --> 2015-11-10 by ./.tv  owner: tovantran

#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <chrono>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  cout << "Main thread id: " << this_thread::get_id() << endl;
  vector<future<void>> futures;
  for(int i = 0; i < 10; i++)
  {
    auto fut = async([]
    {
        this_thread::sleep_for(chrono::seconds(2));
        cout << this_thread::get_id() << " ";
    });
    futures.push_back(move(fut)); //future no copy ctor so use move
  }
  for_each(futures.begin(), futures.end(), [](future<void> & fut)
  {
    fut.wait();
  });

  cout << endl;
  this_thread::sleep_for(chrono::seconds(10));
}
