#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template <typename Col> //lanbda
long fun(Col const& v)
{
  auto sum = 0, i = 0;
	std::for_each(begin(v), end(v), [&sum = sum, &i](auto x) {cout << ++i << endl; sum +=x; });
//	                                            i                   ++i error only read use ref. is ok
	return sum;
}

static int sum1 = 0;

int func1 (int i) {  // function:
  sum1 += i;
  return sum1;
}

struct Sum {         //class object
    Sum() { sum = 0; }
    void operator()(int n) { sum += n; }
    int sum;
} s;

template <typename T>
auto func(T const& v)
{
  std::for_each(begin(v), end(v), func1);     //function func1
  Sum c = std::for_each(begin(v), end(v), s);  //object s
	return c;
}



int main()
{
 std::vector<int> v{3, 4, 2, 1, 56, 2, 4, 65, 2, 9, 8, 5, 7};
 auto sum = fun(v);
 std::cout << "sum = " << sum << "\n";   //lambda

 func(v);

 cout << "sum1 = " << sum1 << endl;     //function
 
 cout << "sum2 = " << func(v).sum << endl;  //object
 
 
 cout << "\n";
 int i = 10;
 int *j = &i;
 (*j)++;
 cout << *j << endl;
}
