 // You tube lambda expression in  C++ Bradley Needham
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
using namespace std;

auto glambda = [](auto a) { return a; }; //generic lambda

struct isEven {
  template <typename T>
  bool operator()(T x) { std::cout << "isEven" << "\n"; return !(x % 2); }
};

template <typename Col> // remember template can not in block code of main must be here.
long fun(Col const& col) {
//    auto c = std::count_if(begin(col), end(col), [](typename Col::value_type x) {return !(x % 2);});
//    auto c = std::count_if(begin(col), end(col), [](auto x) {
//        std::cout << "test" << "\n";
//        return !(x % 2);});
   auto c1 = std::count_if(begin(col), end(col), isEven());

    cout << "--generic lambda with auto-- " << c1 << " " << c1 << " " << "\n";
  return c1;
}
//closure type
struct isOdd // decoration ---> type
{
  bool operator()(int x) { return x % 2; } // definition
};

//template <typename T>
//void fun(T &lam) {}

int main() {
    //Lambda
    auto isOdd1 = [](int x) { return x % 2; }; //shorthand syntax overload operator() parentheses
    auto a = isOdd1(3); // return true    --> invoking

    printf("%s\n", isOdd1(4) ? "Even" : "Odd");
    auto x = isOdd1(3) ? "Even" : "Odd"; //auto need initialize with something
    std::cout << ((isOdd1(3)) ? "Even" : "Odd") << " " << x << "\n"; //cout string need <string> and bracket

    isOdd obj; //class functor is function object override operator()
    std::cout << (obj.operator ()(3) ? "Even" : "Odd") << "\n";

  auto mult = 3;
  //  auto isMultipleOf = [](int x) { return x % 2; };
  auto isMultipleOf = [mult](int x) { return !(x % mult); };  //capture value

  std::vector<int> v{3, 4, 2, 1, 56, 2, 4, 65, 2, 9, 8, 5, 7};
  auto c = std::count_if(begin(v), end(v), isOdd()); // creation/initiation
  auto c1 = std::count_if(begin(v), end(v), [](int x) { return x % 2; });
  auto c2 = std::count_if(begin(v), end(v), isMultipleOf);
  std::cout << c << " " << c1 << " " << c2 << "\n";

  std::count_if(begin(v), end(v), [](int x) {
    printf("%2d   %s\n", x, x % 2 ? "Even" : "Odd");
    return x % 2;  //lamda need to return anything return 0;
  });
  //  printf("%s\n", v[1] % 2 ? "Even" : "Odd");
  //  printf("%s\n", v[2] == 0 ? "Even" : "Odd");
  // std::cout << 1 ? "Odd":"Even"  << "\n"; cannot using cout unless including <string> and using() bracket

//  auto isOdd = [](int x) { return x % 2; };
  auto fn = isOdd();
  auto c3 = std::count_if(begin(v), end(v), fn);

  std::cout << c3 << "\n";

  std::function<void(int)> fn1;
  {
    auto sum = 0; // capture lambda by reference be careful of dangling ref.
    fn1 = [&sum](int x) { sum += x; };
  }
  auto sum = 0;
  std::for_each(begin(v), end(v), [&sum](int x) { sum += x; });  //capture ref. sum by value only read
  //  std::for_each(begin(v), end(v), fn1);
  std::cout << sum << "\n";

  // int capture
  struct Sum {
    Sum(int s) : mySum(s){};
    void operator()(int x) { mySum += x; }
    int mySum;
  };

  auto sum1 = 0;
  std::for_each(begin(v), end(v), [&mySum = sum1](int x) { mySum += x; });
  std::cout << "sum1 = " << sum1 << "\n";
   //scope to resuse variable sum1

  auto sum2 = 0;
  auto fn2 = [myVec = std::move(v), &sum2](){  //g++14 can use inside lambda
      std::for_each(begin(myVec), end(myVec), [&mySum2 = sum2](int x) { mySum2 += x; });
  };
  fn2();
  std::cout << "sum2 = "<< sum2 << "\n";

  std::cout << fun(v) << "\n";

}
