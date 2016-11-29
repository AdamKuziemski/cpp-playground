/// local
#include "device.hpp"
/// STL
#include <iostream>
using namespace std;

namespace Comms
{
  Device::Device(Mode mode, const char* remote_ip) : mode(mode)
  {
    // get host IP address
    SDLNet_ResolveHost(&ip, SDLNet_ResolveIP(&ip), port);

    if(mode == Server)
    {
      socket = SDLNet_UDP_Open(port);
      packet = SDLNet_AllocPacket(buffer_size);
    }
    else if(mode == Client)
    {
      socket = SDLNet_UDP_Open(0);
      packet = SDLNet_AllocPacket(buffer_size);
    }
    else if(remote_ip != nullptr)
      SDLNet_ResolveHost(&ip, remote_ip, port);
  }

  Device::~Device()
  {
    SDLNet_FreePacket(packet);
  }

  void Device::send(Device* recipient, std::string message)
  {
    packet->address.host = recipient->ip.host;
    packet->address.port = recipient->ip.port;
    packet->data = (Uint8*)message.c_str();
    packet->len = message.length() + 1;
    packet->status = 0;

    SDLNet_UDP_Send(socket, -1, packet);
  }

  UDPsocket Device::socket;
}
