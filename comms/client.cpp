/// local
#include "device.hpp"
/// STL
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
using namespace std;

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
      cout <<"Echo: "<< client.message() << endl;

      if(client.message() == "quit")
        quit = true;
    }
  }

  SDLNet_Quit();
  return 0;
}
