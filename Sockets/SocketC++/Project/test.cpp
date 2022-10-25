#include <iostream>
// #include <stdlib.h>

using namespace std;

int main()
{
  srand(time(0));
  for (int i = 0; i < 5; i++)
  {
    cout << rand() % 100 << endl;
  }

  return 0;
}