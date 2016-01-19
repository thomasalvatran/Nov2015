//Bartosz Milewski youtube C++ Concurrency Part 1
//home/tovantran/Ctest/k_r/thread/thread.cpp --> 2015-11-10 by ./.tv  owner: tovantran

#include <iostream>
#include <thread>
#include <future>
#include <string>

using namespace std;

//class MyException : public Exception
//{
//public:
//   MyException(string strError) { m_strError = strError; }
//   string m_strError;
//};

std::string taskFunction()
{
	const char* msg = "Exception from task";
	std::string str("Hello from future !"); //Worker thread 
	throw(std::exception());
	return str;
}

int main()
{
	auto ftr = std::async(&taskFunction);  // not thread but running task
	std::cout << "Hello from main" << std::endl;
	try
	{
	std::string str = ftr.get();
	std::cout << str << std::endl;
  }
  catch(std::exception & e)
  {
  	std::cout << e.what() << std::endl;
  }
//  th.join(); no thread now WE ARE RUNNING TASK 
  return 0;
}	
