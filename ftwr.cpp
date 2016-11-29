/**
*** This is purely a toy.
*** I mean, you could use it for displaying dialogues in a jRPG.
*** Or sending packets at random intervals.
*** Or playing distracting sounds in a game.
*** Or something.
*** This comment looks like this on purpose.
*** It would be funny if metaprogrammed.
*** Yep. I'm evil.
*** Anyways, thanks for reading!
**/

#include <iostream>
#include <chrono>
#include <thread>
#include <random>
using namespace std;

void typeText(string text, int showFor = 0, bool clear = true)
{
  static mt19937 mt(chrono::system_clock::now().time_since_epoch().count());

  for(char c : text)
  {
    cout << c;
    // sleep for random amounts of time to achieve the effect of typing
    this_thread::sleep_for(chrono::milliseconds(40 + (mt() % 460)));
  }

  if(showFor > 0)
    this_thread::sleep_for(chrono::milliseconds(showFor));

  if(clear)
    cout <<'\r'<< string(text.size(), " ") <<'\r';
}

int main()
{
  typeText("Wake up, Neo...", 3000);
  typeText("The Matrix has you...", 3000);
  typeText("Follow the white rabbit.", 3000);
  cout << "Knock, knock, Neo.\a";

  return 0;
}
