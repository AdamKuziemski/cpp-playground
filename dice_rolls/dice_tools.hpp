#pragma once

/** local **/
#include "basic_dice.hpp"

/*********************
*** MultipleRoller ***
*********************/

class MultipleRoller
{
public:
  MultipleRoller(std::initializer_list<std::shared_ptr<Dice>> dice) : dice(dice) {}

  std::vector<int> eval() const;
  std::vector<int> evalElement(size_t position, long long how_many = 1) const;
  std::vector<std::vector<int>> evalManyTimes(long long how_many) const;

  Dice::Range range() const;

protected:
  std::vector<std::shared_ptr<Dice>> dice;
};
