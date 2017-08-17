#pragma once
#include "logger/logger.h"
#include "redisSim/util.h"
namespace RSim
{

class SimClient : public translib::TcpClient
{
public:
  SimClient(const translib::Loop &loop) : translib::TcpClient(loop)
  {
  }

protected:
  virtual void onRead()
  {

    uint32_t length = this->getInputBufferLength();

    uint8_t *buff = new uint8_t[MAX_BUFF_LEN];
    this->readInputBuffer(buff, length);
    __LOG(debug, "[SimClient] receive message " << buff);
  }

  virtual void onDisconnected()
  {
    __LOG(error, "[SimClient] disconnected");
  }

  virtual void onConnected(int errorr)
  {
    __LOG(debug, "[SimClient] connected successfully");
  }

private:
};
}