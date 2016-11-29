/** local **/
#include "bstream.hpp"
/** STL **/
#include <iostream>
using namespace std;

int main()
{
  bostream bout("board.dat"); // create a binary file
  vector<int> vec {1337, 666, 777};

  bout << "Hello world!" << 3.1415 << true << 'c' << vec;

  bout.closeFile(); // close the file
  vec.clear();

  char* s; // will work the same if it's a std::string
  double d;
  bool b;
  char c;
  const char _ = ' '; // I hate the apostrophes. Kappa

  bistream bin("board.dat");

  bin >> s >> d >> b >> c >> vec;
  cout << s <<_<< d <<_<< b <<_<< c <<_;
    for(int x : vec)
      cout << x <<_;

  return 0;
}
