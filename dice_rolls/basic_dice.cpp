/** local **/
#include "basic_dice.hpp"
/** STL **/
#include <chrono>

/***********
*** Dice ***
***********/

std::shared_ptr<std::mt19937> Dice::randomNumberGenerator = nullptr;

Dice::Dice()
{
  if(randomNumberGenerator == nullptr)
    randomNumberGenerator = std::make_shared<std::mt19937>(std::chrono::system_clock::now().time_since_epoch().count());
}

/******************
*** Dice::Range ***
******************/

Dice::Range::Range(int lower_bound, int upper_bound)
{
  if(lower_bound != upper_bound)
  {
    if(lower_bound > upper_bound) std::swap(lower_bound, upper_bound);

    bounds.push_back(Bounds(lower_bound, upper_bound));
  }
}

inline Dice::Range::operator std::vector<int>() const
{
  size_t vecsize = size();
  std::vector<int> result(vecsize);
  Iterator val = begin();

  for(size_t i = 0; i < vecsize; ++i)
    result[i] = *(val++);

  return result;
}

inline bool Dice::Range::inBounds(int value) const
{
  for(Bounds b : bounds)
    if(b.inBounds(value))
      return true;

  return false;
}

inline size_t Dice::Range::size() const
{
  size_t result = 0;

  for(Bounds b : bounds)
    result += b.size();

  return result;
}

/**********************
*** Range::Iterator ***
**********************/

Dice::Range::Iterator::Iterator(const Range* r, bool end) : range(r), end(end)
{
  if(!end)
    setToBegin();
  else
    setToEnd();
}

Dice::Range::Iterator Dice::Range::Iterator::operator++()
{
  if(!end && !current_bounds->inBounds(++value))
  {
    if(++current_bounds != range->bounds.end())
      value = current_bounds->lower;
    else
      setToEnd();
  }
  return *this;
}

Dice::Range::Iterator Dice::Range::Iterator::operator++(int)
{
  Iterator ret = *this;
  ++(*this);
  return ret;
}

Dice::Range::Iterator Dice::Range::Iterator::operator--()
{
  if(!end && !current_bounds->inBounds(--value))
  {
    if(--current_bounds != range->bounds.end())
      value = current_bounds->upper;
    else
      setToEnd();
  }
  return *this;
}

Dice::Range::Iterator Dice::Range::Iterator::operator--(int)
{
  Iterator ret = *this;
  --(*this);
  return ret;
}

void Dice::Range::Iterator::setToBegin()
{
  current_bounds = range->bounds.begin();
  if(current_bounds != range->bounds.end())
    value = current_bounds->lower;
  else
    value = 0;
  end = false;
}

void Dice::Range::Iterator::setToEnd()
{
  current_bounds = range->bounds.end();
  value = 0;
  end = true;
}
