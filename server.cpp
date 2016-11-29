/// local
#include "device.hpp"
/// STL
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
  if(SDLNet_Init() < 0)
  {
    cout <<"SDLNet_Init: "<< SDLNet_GetError() << endl;
    return 1;
  }

  Comms::Device serv(Comms::Device::Server);
  Comms::Device client(Comms::Device::Dummy);
  bool quit;

  cout <<"Server started. IP: "<< serv.getIPString() << endl;

  while(!quit)
  {
    if(serv.receive())
    {
      client.getIP() = serv.sender();
      string msg = serv.message();
      serv.send(&client, msg);

      if(msg == "quit")
        quit = true;
      else
        cout <<"Message: "<< msg << endl;
    }
  }

  SDLNet_Quit();
  return 0;
}
