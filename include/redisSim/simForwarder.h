
#pragma once
#include "logger/logger.h"
#include "redisSim/messageBus.h"
namespace RSim
{

class simForwarder
{
    simForwarder(forwarder_conn_info info)
    {
        _info = info;
        auto bus = message_bus<redisSim>::instance();

        bus->register_handler(DELETE_F, this, [](void *objp, void *msgp, std::string topic) {
            if (!objp)
            {
                return;
            }
            if (!msgp)
            {
                return;
            }
            stop(forwarder_conn_info * msgp);
        });
    }

    void stop()
    {

        // do the stop work
        auto bus = message_bus<redisSim>::instance();

        bus->call(DELETE_F_INS, this);
    }

  private:
    forwarder_conn_info _info;
};
}