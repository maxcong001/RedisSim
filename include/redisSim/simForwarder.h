
#pragma once
#include "logger/logger.h"
#include "redisSim/messageBus.h"
#include "redisSim/util.h"
#include "redisSim/simServer.h"

namespace RSim
{

class simForwarder
{
  public:
    simForwarder(forwarder_conn_info info);

    void stop_f(forwarder_conn_info *msgp);
    void start();
    void stop();

  private:
    forwarder_conn_info _info;
    simServer ss;
};
}