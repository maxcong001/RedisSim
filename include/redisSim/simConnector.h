#pragma once
#include "logger/logger.h"
namespace RSim
{

class simConnector : public translib::TcpClient
{
  public:
    simConnector(const translib::Loop &loop) : translib::TcpClient(loop)
    {
    }

  protected:
    virtual void onRead()
    {
    }

    virtual void onDisconnected()
    {
        __LOG(debug, " run here");
    }

    virtual void onConnected(int error)
    {
        __LOG(debug, " run here");
    }

  private:
    translib::Loop _loop;
};
}