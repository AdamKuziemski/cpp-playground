#pragma once

/** STL **/
#include <algorithm> // set_union
#include <memory> // shared_ptr
#include <vector>
#include <random> // mt19937

/***********
*** Dice ***
***********/

class Dice
{
public:
  class Range;

  void capValue() {cap_value = true;}
  void adjustShift(int x) {shift_by = x;}

  virtual int roll() const = 0;
  virtual Range range() const = 0;

  int operator()() const {return roll();}

protected:
  int rolls = 1;
  int sides = 6;
  int shift_by = 0;
  bool cap_value = false;

  Dice();
  int random(int mod) const {return (*randomNumberGenerator)() % mod;}
  int performRoll() const
  {
    int value = rolls;
    int n = rolls;

    while(n--)
      value += random(sides);

    value += shift_by;

    return (cap_value ? cap(value) : value);
  }

  virtual int cap(int value) const = 0;

private:
  static std::shared_ptr<std::mt19937> randomNumberGenerator;
};

/******************
*** Dice::Range ***
******************/

class Dice::Range
{
public:
  struct Bounds
  {
    int lower;
    int upper;

    Bounds(int lower = 0, int upper = 0) : lower(lower), upper(upper) {}

    size_t size() const { return (upper == lower ? 0 : std::abs(upper - lower) + 1);}

    bool inBounds(int value) const {return value >= lower && value <= upper;}
    bool intersects(const Bounds& other) const {return other.lower >= lower && other.lower <= upper;}
    bool contains(const Bounds& other) const {return other.lower >= lower && other.upper <= upper;}

    bool operator==(const Bounds& other) const {return (upper == other.upper) && (lower == other.lower);}
    bool operator!=(const Bounds& other) const {return (upper != other.upper) && (lower != other.lower);}
    bool operator<(const Bounds& other) const  {return (lower < other.lower);}
    bool operator<=(const Bounds& other) const {return (lower <= other.lower);}
    bool operator>(const Bounds& other) const  {return (lower > other.lower);}
    bool operator>=(const Bounds& other) const {return (lower >= other.lower);}
  };

  class Iterator
  {
  public:
    Iterator(const Range* r, bool end = false);
    int operator*() { return value; }

    Iterator operator++(); // prefix
    Iterator operator++(int); // postfix

    Iterator operator--(); // prefix
    Iterator operator--(int); // postfix

    bool operator==(const Iterator& it) const
    { return (range == it.range) && (end == it.end) && (current_bounds == it.current_bounds) && (value == it.value); }

    bool operator!=(const Iterator& it) const { return (range == it.range) && (end != it.end) && (value != it.value); }
    bool operator<(const Iterator& it) const { return value < it.value; }
    bool operator<=(const Iterator& it) const { return value <= it.value; }
    bool operator>(const Iterator& it) const { return value > it.value; }
    bool operator>=(const Iterator& it) const { return value >= it.value; }

  private:
    const Range* range;
    bool end;
    std::vector<Range::Bounds>::const_iterator current_bounds;
    int value;

    void setToBegin();
    void setToEnd();
  };

  Range(int lower_bound = 0, int upper_bound = 0);

  bool inBounds(int x) const;
  size_t size() const;

  Iterator begin() const { return Iterator(this); }
  Iterator end() const { return Iterator(this, true); }

  operator std::vector<int>() const;

  Range operator+(Range const& other) const
  {
    std::vector<Bounds> all(bounds.size() + other.bounds.size());
    std::vector<Bounds>::iterator it;

    it = std::set_union(bounds.begin(), bounds.end(), other.bounds.begin(), other.bounds.end(), all.begin());
    all.resize(it - all.begin());

    size_t finish = all.size();
    Range result;

    for(size_t i = 0; i < finish;)
    {
      Bounds ins(all[i].lower, all[i].upper);

      size_t k = i + 1;
      for(; k < finish && ins.intersects(all[k]); ++k)
      {
        if(ins.contains(all[k])) continue;
        else ins.upper = all[k].upper;
      }
      i = k;

      result.bounds.push_back(ins);
    }

    return result;
  }

private:
  std::vector<Bounds> bounds;
};
