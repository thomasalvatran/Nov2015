//Bartosz Milewski youtube C++ Concurrency Part 3 - using move
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>
#include <cassert>
//#include <Windows.h>

//void threadFunction()
//{
//	std::cout << "Hello From Thread ! \n"; //Worker thread 
//}
//          (int i)
void thFunc(int &i)  //THREAD FUNCTION  SHARE I as Ref.
	{
		std::cout << "Hello From Thread ! " << i <<  "\n"; //Worker thread define inline  / parallelism then join (task/thread base program)
															//non determinism in concurrency program very clear from video 
	}
void test(std::vector<std::thread> & workers)
{
for (int i = 0; i < 10; i++)
	{															// i              //THREAD CTOR
		auto th = std::thread(&thFunc, std::ref(i));  //pass argument to thread ctor
		workers.push_back(std::move(th));
	  assert(!th.joinable());
  }
}
int main()
{
	std::vector<std::thread> workers;
  test(workers);	
	
	std::cout << "Hello World From Main \n";
	//Sleep(2000);
	std::for_each(workers.begin(), workers.end(), [](std::thread &th)
	{
		th.join();
	});
	return 0;
}	


