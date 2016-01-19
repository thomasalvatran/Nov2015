//#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <algorithm>
using namespace std;


void toSin(list<double>&& list)
{
    //this_thread::sleep_for(chrono::seconds(1));
    for_each(list.begin(), list.end(), [](double & x)
    {
        x = sin(x);
    });

    for_each(list.begin(), list.end(), [](double & x)
    {
        int count = static_cast<int>(10*x+10.5);
        for (int i=0; i<count; ++i)
        {
            cout.put('*');
        }
        cout << endl;
    });
}    

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
    list<double> list;

    const double pi = 3.1415926;
    const double epsilon = 0.00000001;
    for (double x = 0.0; x<2*pi+epsilon; x+=pi/16)
    {
        list.push_back(x);
    }

    thread th(&toSin, /*std::ref(list)*/std::move(list));
    th.join();    

    return 0;
}
