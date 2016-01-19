//Bartosz Milewski youtube C++ Concurrency Part 1
//home/tovantran/Ctest/k_r/thread/thread.cpp --> 2015-11-10 by ./.tv  owner: tovantran

#include <iostream>
#include <thread>
#include <future>

void threadFunction(std::promise<std::string> & prms)
{
	std::string str("Hello from future !"); //Worker thread 
	std::cout << "String data: " << (void *)str.data() << std::endl;  //raw pointer
	prms.set_value(str);
}

int main()
{
	std::promise<std::string> prms;
	std::thread th(&threadFunction, std::ref(prms));
	std::cout << "Hello World From Main \n";
	std::future<std::string> ftr = prms.get_future();
	std::string str = ftr.get();
	std::cout << str << std::endl;
	std::cout << "String data: " << (void *)str.data() << std::endl;  //raw pointer
	th.join();
  return 0;
}	
