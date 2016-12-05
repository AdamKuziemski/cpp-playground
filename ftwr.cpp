/**
*** This is purely a toy.
*** I mean, you could use the same idea for displaying dialogues in a jRPG,
*** or sending packets at random intervals, or playing distracting sounds in a game.
**/

/** STL **/
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
using namespace std;

void typeText(string text, int showFor = 0, bool clear = false)
{
  static mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
  using ms = chrono::milliseconds;

  for(char c : text)
  {
    cout << c;
    // sleep for random times to achieve the effect of typing
    this_thread::sleep_for(ms(40 + (rnd() % 460)));
  }

  if(showFor > 0)
    this_thread::sleep_for(ms(showFor));

  if(clear)
    cout <<'\r'<< string(text.size(), ' ') <<'\r';
}

int main()
{
  typeText("Wake up, Neo...", 3000, true);
  typeText("The Matrix has you...", 3000, true);
  typeText("Follow the white rabbit.", 3000, true);
  cout << "Knock, knock, Neo.\a";

  return 0;
}

