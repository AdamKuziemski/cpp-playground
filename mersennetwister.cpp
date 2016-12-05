/** local **/
#include "mersennetwister.hpp"
/** STL **/
#include <chrono>

MersenneTwister::MersenneTwister()
: MersenneTwister(std::chrono::system_clock::now().time_since_epoch().count()) {}

MersenneTwister::MersenneTwister(uint32_t seed)
{
  MT[0] = seed;
  index = 0;

  for(unsigned i = 1; i < 623; ++i)
    MT[i] = (0x6c078965 * (MT[i-1] ^ ((MT[i-1] >> 30))) + i);
}

uint32_t MersenneTwister::get()
{
  if(!index) generateNumbers();

  int y = MT[index];
  y = y ^ (y >> 11);
  y = y ^ ((y << 7) & 0x9d2c5680);
  y = y ^ ((y << 15) & 0xefc60000);
  y = y ^ (y >> 18);

  index = (index + 1) % 624;

  return y;
}

void MersenneTwister::generateNumbers()
{
  for(unsigned i = 0; i < 623; ++i)
  {
    int y = (MT[i] & 0x80000000) + (MT[(i + 1) % 624] & 0x7FFFFFFF);
    MT[i] = MT[(i + 397) % 624] ^ (y >> 1);
    if(y % 2) MT[i] = MT[i] ^ 0x9908b0df;
  }
}
