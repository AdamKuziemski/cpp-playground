#pragma once

/** local **/
#include "basic_dice.hpp"

/*****************
*** SimpleDice ***
*****************/

class SimpleDice : public Dice
{
public:
  SimpleDice(int rolls = 1, int sides = 6, int shift = 0);

  virtual int roll() const override;
  virtual Range range() const override;

protected:
  virtual int cap(int value) const override;
};

/*******************
*** UncappedDice ***
*******************/

class UncappedDice : public SimpleDice
{
public:
  void capValue() = delete;

protected:
  virtual int cap(int value) const override final {return value;}
};

/*****************
*** RangedDice ***
*****************/

class RangedDice : public UncappedDice
{
public:
  RangedDice(int lower_bound, int upper_bound);

  void exclusive();
  void exclusiveLeft() {inclusive_left = false;}
  void exclusiveRight() {inclusive_right = false;}
  void inclusive();
  void inclusiveLeft() {inclusive_left = true;}
  void inclusiveRight() {inclusive_right = true;}

  virtual int roll() const override;
  virtual Range range() const override;

protected:
  bool inclusive_left = true;
  bool inclusive_right = true;
};

/***********************
*** CustomValuedDice ***
***********************/

class CustomValuedDice : public UncappedDice
{
public:
  CustomValuedDice(std::initializer_list<int> possible_results);

  virtual int roll() const override;
  virtual Range range() const override;

private:
  std::vector<int> possible_results;
};
