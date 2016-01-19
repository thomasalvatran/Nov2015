//Bartosz Milewski youtube C++ Concurrency Part 1
//home/tovantran/Ctest/k_r/thread/thread.cpp --> 2015-11-10 by ./.tv  owner: tovantran

#include <iostream>
#include <thread>
#include <future>
#include <string>

void threadFunction(std::promise<std::string> & prms)
{
	const char* message = "Exception from future";
  try
  {
	std::string str("Hello from future !"); //Worker thread 
	throw(std::exception());
	prms.set_value(str);
  }
  catch(...)  //catch all exception ...
  {
  	prms.set_exception(std::current_exception());
  }
}

int main()
{
	std::promise<std::string> prms;
	std::thread th(&threadFunction, std::ref(prms));
	std::cout << "Hello World From Main \n";
	std::future<std::string> ftr = prms.get_future();
	try
	{
	std::string str = ftr.get();
	std::cout << str << std::endl;
	}
	catch(std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}
	th.join();
  return 0;
}	
