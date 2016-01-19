#include <algorithm>


void scan( int* a, int length, std::function<void(int)> process)
{
  for(int i=0; i<length; i++) {
    process(a[i]);
  }
}
int main()
{
  int a[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  int threshold = 5;
  scan(a, 10,
    [threshold](int v)
    { if (v>threshold) { printf("%i ", v); } }
  );
  printf("\n");
  return 0;
}
