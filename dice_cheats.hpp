#pragma once

/** local **/
#include "dice.hpp"

/******************
*** DiceCheater ***
******************/

class DiceCheater : public UncappedDice
{
public:
  DiceCheater(std::shared_ptr<Dice> cheated_dice = nullptr) : cheated_dice(cheated_dice) {}

  virtual int roll() const = 0;
  virtual Range range() const override;

protected:
  std::shared_ptr<Dice> cheated_dice;

  int performRoll(std::shared_ptr<Dice> dice) const;
};

/************************
*** HigherRollCheater ***
************************/

class HigherRollCheater : public DiceCheater
{
public:
  HigherRollCheater(std::shared_ptr<Dice> cheated_dice = nullptr) : DiceCheater(cheated_dice) {}
  virtual int roll() const override; /// return the higher of two rolls
};

/***********************
*** LowerRollCheater ***
***********************/

class LowerRollCheater : public DiceCheater
{
public:
  LowerRollCheater(std::shared_ptr<Dice> cheated_dice = nullptr) : DiceCheater(cheated_dice) {}
  virtual int roll() const override; /// return the lower of two rolls
};

/**********************
*** CoinFlipCheater ***
**********************/

class CoinFlipCheater : public DiceCheater
{
public:
  CoinFlipCheater(std::shared_ptr<Dice> cheated_dice = nullptr, std::shared_ptr<Dice> second_cheated_dice = nullptr)
    : DiceCheater(cheated_dice), second_cheated_dice(second_cheated_dice) {}

  virtual int roll() const override; // return a random of two rolls based on a "coin flip"
  virtual Range range() const override;

protected:
  std::shared_ptr<Dice> second_cheated_dice;
};

/*************************
*** UniqueValueCheater ***
*************************/

class UniqueValueCheater : public DiceCheater
{
public:
  virtual int roll() const override;
  void switchResetWhenEmpty() {reset_when_empty = !reset_when_empty;}
  bool resets() const {return reset_when_empty;}

protected:
  bool reset_when_empty = true;
};

/*************************
*** DoubleRollOnChance ***
*************************/

class DoubleRollOnChance : public DiceCheater
{
public:
  DoubleRollOnChance(std::shared_ptr<Dice> rolled_dice, uint8_t chance_for_double);

  virtual int roll() const override;

protected:
  uint8_t chance_for_double;
};

/**************************
*** DoubleValueOnChance ***
**************************/

class DoubleValueOnChance : public DoubleRollOnChance
{
public:
  DoubleValueOnChance(std::shared_ptr<Dice> rolled_dice, uint8_t chance_for_double) : DoubleRollOnChance(rolled_dice, chance_for_double) {}

  virtual int roll() const override;
};
