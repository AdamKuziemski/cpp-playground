/** local **/
#include "dice.hpp"
#include "dice_cheats.hpp"
#include "dice_tools.hpp"
/** STL **/
#include <iostream>
using namespace std;

int main()
{
  std::shared_ptr<SimpleDice> sided = std::make_shared<SimpleDice>(2, 12);
  std::shared_ptr<RangedDice> ranged = std::make_shared<RangedDice>(20, 30);

  std::shared_ptr<HigherRollCheater> high = std::make_shared<HigherRollCheater>(sided);
  std::shared_ptr<HigherRollCheater> higher = std::make_shared<HigherRollCheater>(high);
  std::shared_ptr<HigherRollCheater> highest = std::make_shared<HigherRollCheater>(higher);

  std::shared_ptr<LowerRollCheater> low = std::make_shared<LowerRollCheater>(sided);
  std::shared_ptr<LowerRollCheater> lower = std::make_shared<LowerRollCheater>(low);
  std::shared_ptr<LowerRollCheater> lowest = std::make_shared<LowerRollCheater>(lower);

  std::shared_ptr<CoinFlipCheater> coin = std::make_shared<CoinFlipCheater>(lowest, highest);

  MultipleRoller roller {coin, ranged};
  Dice::Range range = roller.range();

  std::cout << "This Roller can roll these values:\n";
  for(int a : range)
    std::cout << a << ' ';

  std::cout << "\nThis Roller rolled these values: " << std::endl;
  for(int a : roller.evalElement(0, 100))
    std::cout << a << ' ';

  return 0;
}
