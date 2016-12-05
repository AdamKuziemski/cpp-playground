/** local **/
#include "dice.hpp"
/** STL **/
#include <algorithm> // min_element, max_element

/*****************
*** SimpleDice ***
*****************/

SimpleDice::SimpleDice(int rolls, int sides, int shift)
{
  this->rolls = rolls;
  this->sides = sides;
  this->shift_by = shift;
}

inline int SimpleDice::roll() const
{
  return performRoll();
}

inline int SimpleDice::cap(int value) const
{
  static int rts = rolls * sides;

  if(value < rolls) return rolls;
  if(value > rts) return rts;
  return value;
}

inline Dice::Range SimpleDice::range() const
{
  int lower_bound = (cap_value ? cap(rolls + shift_by) : rolls + shift_by);
  int upper_bound = (cap_value ? cap(sides + shift_by) : rolls * sides + shift_by);

  return Range(lower_bound, upper_bound);
}

/*****************
*** RangedDice ***
*****************/

RangedDice::RangedDice(int lower_bound, int upper_bound)
{
  sides = std::abs(upper_bound - lower_bound) + 1;
  shift_by = lower_bound;
};

inline int RangedDice::roll() const
{
  int lbound = shift_by + (!inclusive_left ? 1 : 0);
  int mod = sides - (inclusive_right ? 0 : 1) - (!inclusive_right && !inclusive_left ? 1 : 0);

  return lbound + random(mod);
}

inline Dice::Range RangedDice::range() const
{
  int lbound = shift_by + (!inclusive_left ? 1 : 0);
  int rbound = sides - (inclusive_right ? 0 : 1) - (!inclusive_right && !inclusive_left ? 1 : 0);

  return Range(lbound, lbound + rbound - 1);
}

inline void RangedDice::exclusive()
{
  exclusiveRight();
  exclusiveLeft();
}

inline void RangedDice::inclusive()
{
  inclusiveRight();
  inclusiveLeft();
}

/***********************
*** CustomValuedDice ***
***********************/

CustomValuedDice::CustomValuedDice(std::initializer_list<int> possible_results) : possible_results(possible_results)
{
  sides = possible_results.size();
}

inline int CustomValuedDice::roll() const
{
  return possible_results[random(sides)];
}

/// this method should be marked as deleted as it can create confusion
inline Dice::Range CustomValuedDice::range() const
{
  auto mine = std::min_element(possible_results.begin(), possible_results.end());
  auto maxe = std::max_element(possible_results.begin(), possible_results.end());
  return Range(*mine, *maxe);
}
