/** local **/
#include "dice.hpp"
#include "dice_cheats.hpp"
#include "dice_tools.hpp"
/** STL **/
#include <iostream>
#include <map>
using namespace std;

int main()
{
  auto sided = make_shared<SimpleDice>(2, 12); // 2d12 roll

  auto high = make_shared<HigherRollCheater>(sided); // roll 2d12 twice
  auto higher = make_shared<HigherRollCheater>(high); // roll the double roll twice
  auto highest = make_shared<HigherRollCheater>(higher); // and so on

  auto low = make_shared<LowerRollCheater>(sided); // roll 2d12 twice
  auto lower = make_shared<LowerRollCheater>(low); // roll the double roll twice
  auto lowest = make_shared<LowerRollCheater>(lower); // and so on

  auto coin = make_shared<CoinFlipCheater>(lowest, highest); // roll both and return a random result

  // the easiest way to see how it works is to play around with a MultipleRoller
  // you can roll one of the double rolls instead and see how the graph changes
  MultipleRoller roller {coin};
  Dice::Range range = roller.range();

  cout << "This Roller can roll these values:\n";
  for(int a : range)
    cout << a << ' ';

  cout << "\nThis Roller rolled these values: " << endl;
  map<int, int> vals;
  for(int a : roller.evalElement(0, 200))
  {
    cout << a << ' ';
    vals[a]++;
  }

  cout << "\n\nWhich looks like this on a graph:\n\n";
  for(auto it = vals.begin(); it != vals.end(); ++it)
    cout << it->first <<'\t'<< string(it->second, '*') << endl;

  return 0;
}
