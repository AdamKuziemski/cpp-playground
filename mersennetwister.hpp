#pragma once
/** STL **/
#include <cstdint>

class MersenneTwister
{
public:
  MersenneTwister();
  MersenneTwister(uint32_t);

  uint32_t operator()() {return get();}
  uint32_t get();

private:
  uint32_t MT[623];
  uint32_t index;

  void generateNumbers();
};
