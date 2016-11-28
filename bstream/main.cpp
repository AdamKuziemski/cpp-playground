/** local **/
#include "biostream.hpp"
/** STL **/
#include <iostream>
using namespace std;

int main()
{
  ifstream fin("board.txt");
  bostream bout("board.dat");
  
  int a, b, c;
  
  fin >> a >> b >> c;
  bout << a << b << c;

  return 0;
}
