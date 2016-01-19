//http://en.cppreference.com/w/cpp/algorithm/for_each
#include <vector>
#include <algorithm>
#include <iostream>
 
struct Sum {
    Sum() { sum = 0; }
    void operator()(int n) { sum += n; }
    int sum;
} s;
 
int main()
{
    std::vector<int> nums{3, 4, 2, 1, 56, 2, 4, 65, 2, 9, 8, 5, 7};
 
    std::cout << "before:";
    for (auto n : nums) {
        std::cout << ' ' << n;
    }
    std::cout << '\n';
 
    std::for_each(nums.begin(), nums.end(), [](int &n){ n++; });
 
    // Calls Sum::operator() for each number
//    Sum s1();
    Sum s1;
    Sum s = std::for_each(nums.begin(), nums.end(), /*Sum()*/ s1);  //() operator/default ctor
 
    std::cout << "after: ";
    for (auto n : nums) {
        std::cout << ' ' << n;
    }
    std::cout << '\n';
    std::cout << "sum: " << s.sum << '\n';
}
