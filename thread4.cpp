//Bartosz Milewski youtube C++ Concurrency Part 1
//home/tovantran/Ctest/k_r/thread/thread.cpp --> 2015-11-10 by ./.tv  owner: tovantran

#include <iostream>
#include <thread>
#include <future>

void threadFunction(std::promise<std::string> && prms)
{
	std::string str("Hello from future !"); //Worker thread 
	prms.set_value(str);
}

int main()
{
	std::promise<std::string> prms;
	std::future<std::string> ftr = prms.get_future();
	std::thread th(&threadFunction, std::move(prms));
	std::cout << "Hello World From Main \n";
	std::string str = ftr.get();
	std::cout << str << std::endl;
	th.join();
  return 0;
}	
