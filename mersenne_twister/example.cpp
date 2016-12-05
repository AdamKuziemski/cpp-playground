/** local **/
#include "mersennetwister.hpp"
/** STL **/
#include <iostream>
using namespace std;

int main()
{
  unsigned howmany = 200;
  MersenneTwister mt;
  
  cout <<"Generating "<< howmany <<" random numbers from 0 to 50:\n";

  for(unsigned i = 0; i < howmany; ++i)
  {
    cout << mt() % 50 <<' ';
    if(i && i % 20 == 0) cout <<'\n';
  }

  return 0;
}
