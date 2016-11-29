/// local
#include "device.hpp"
/// STL
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
using namespace std;

void typeText(string text, int showFor = 0)
{
  static mt19937 mt(chrono::system_clock::now().time_since_epoch().count());

  for(char c : text)
  {
    cout << c;
    this_thread::sleep_for(chrono::milliseconds(40 + (mt() % 460)));
  }

  if(showFor > 0)
    this_thread::sleep_for(chrono::milliseconds(showFor));
}

int main(int argc, char** argv)
{
  cout << "Hello.\n";
  if(SDLNet_Init() < 0)
  {
    cout <<"SDLNet_Init: "<< SDLNet_GetError() <<"\nBye."<< endl;
    return 1;
  }

  cout <<"You can throw your messages at the server. They will be bounced back.\n";

  Comms::Device serv(Comms::Device::Dummy, "localhost");
  Comms::Device client(Comms::Device::Client);
  bool quit;
  string message;

  while(!quit)
  {
    cout <<"> ";
    getline(cin, message);
    client.send(&serv, message);

    while(!client.receive()) // wait for server reply
    {
      cout <<"Echo: ";
      typeText(client.message());
      cout << endl;

      if(client.message() == "quit")
        quit = true;
    }
  }

  SDLNet_Quit();
  return 0;
}
