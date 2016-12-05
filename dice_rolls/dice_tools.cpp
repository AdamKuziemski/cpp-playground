/** local **/
#include "dice_tools.hpp"

/*********************
*** MultipleRoller ***
*********************/

std::vector<int> MultipleRoller::eval() const
{
  std::vector<int> copy(dice.size());

  for(size_t i = 0; i < copy.size(); ++i)
    copy[i] = (dice[i] ? dice[i]->roll() : 0);

  return copy;
}

std::vector<int> MultipleRoller::evalElement(size_t pos, long long how_many) const
{
  std::vector<int> results(how_many);
  size_t dice_size = dice.size();

  for(int& a : results)
    a = (pos < dice_size && dice[pos] ? dice[pos]->roll() : 0);

  return results;
}

std::vector<std::vector<int>> MultipleRoller::evalManyTimes(long long how_many) const
{
  std::vector<std::vector<int>> results(how_many);

  for(std::vector<int>& a : results)
    a = eval();

  return results;
}

Dice::Range MultipleRoller::range() const
{
  size_t size = dice.size();
  if(size == 0)
    return Dice::Range(0, 0);

  Dice::Range returned(dice[0]->range());

  for(size_t i = 1; i < size; ++i)
    if(dice[i])
      returned = returned + dice[i]->range();

  return returned;
}
