/** local **/
#include "dice_cheats.hpp"

/******************
*** DiceCheater ***
******************/

inline int DiceCheater::performRoll(std::shared_ptr<Dice> dice) const
{
  if(dice)
    return dice->roll();

  return 0;
}

inline Dice::Range DiceCheater::range() const
{
  if(!cheated_dice)
    return Range(0, 0);

  return cheated_dice->range();
}

/******************
*** DiceCheater ***
******************/

inline int HigherRollCheater::roll() const
{
  int roll1 = performRoll(cheated_dice);
  int roll2 = performRoll(cheated_dice);

  return std::max(roll1, roll2);
}

/***********************
*** LowerRollCheater ***
***********************/

inline int LowerRollCheater::roll() const
{
  int roll1 = performRoll(cheated_dice);
  int roll2 = performRoll(cheated_dice);

  return std::min(roll1, roll2);
}

/**********************
*** CoinFlipCheater ***
**********************/

inline int CoinFlipCheater::roll() const
{
  int roll1 = performRoll(cheated_dice);
  int roll2 = performRoll(second_cheated_dice ? second_cheated_dice : cheated_dice);

  return (random(2) ? roll1 : roll2);
}

inline Dice::Range CoinFlipCheater::range() const
{
  if(!cheated_dice)
    return Range(0, 0);

  Range r = cheated_dice->range();

  return (second_cheated_dice ? r + second_cheated_dice->range() : r);
}

/*************************
*** UniqueValueCheater ***
*************************/

int UniqueValueCheater::roll() const
{
  return 0; /// TODO
}

/*************************
*** DoubleRollOnChance ***
*************************/

DoubleRollOnChance::DoubleRollOnChance(std::shared_ptr<Dice> cheated_dice, uint8_t chance_for_double)
  : DiceCheater(cheated_dice), chance_for_double(chance_for_double)
{
  if(chance_for_double > 100) chance_for_double = 100; // cap the percent value
}

inline int DoubleRollOnChance::roll() const
{
  int value = performRoll(cheated_dice);

  if(random(100) < chance_for_double)
    value += performRoll(cheated_dice);

  return value;
}

/**************************
*** DoubleValueOnChance ***
**************************/

inline int DoubleValueOnChance::roll() const
{
  int value = performRoll(cheated_dice);

  if(random(100) < chance_for_double)
    value *= 2;

  return value;
};
