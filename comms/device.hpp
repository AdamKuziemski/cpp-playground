/**
*** WARNING: DO NOT USE THIS CODE AS RELIABLE.
*** The class Comms::Device is a part of a work-in-progress.
*** So far it only provides basic functionality with absolutely zero security.
*** It's going to be a simple interface for communicating between apps/computers,
*** created mostly to clean up the final code from unnecessary repetitions.
**/

#pragma once

/// SDL
#include <SDL.h>
#include <SDL_net.h>
/// STL
#include <string>

std::string cnv(Uint8);

namespace Comms
{
  class Device
  {
  public:
    enum Mode
    {
      Server, // host device
      Client, // client device
      Dummy // used as a recipient for sending messages
    };

    Device(Mode mode, const char* remote_ip = nullptr);
    virtual ~Device();

    bool receive() {
      return (SDLNet_UDP_Recv(socket, packet) != 0);
    }

    void send(Device* recipient, std::string message);

    std::string message() {
      return std::string((char*)packet->data);
    }

    IPaddress sender() {
      return packet->address;
    }

  protected:
    Mode mode;
    IPaddress ip;
    static UDPsocket socket;
    UDPpacket* packet;

    static const short buffer_size = 512;
    static const short port = 1337;

  public:
    std::string getIPString() const
    {
      Uint8* quad = (Uint8*)&ip.host;
      return std::to_string(quad[0]) + "." + std::to_string(quad[1]) + "."
        + std::to_string(quad[2]) + "." + std::to_string(quad[3]);
    }

    IPaddress& getIP() {
      return ip;
    }

    UDPsocket& getSocket() {
      return socket;
    }

    short getPort() const {
      return port;
    }

    short getBufferSize() const {
      return buffer_size;
    }
  };
}
