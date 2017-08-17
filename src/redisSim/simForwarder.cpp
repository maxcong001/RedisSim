#include "redisSim/simForwarder.h"
#include "redisSim/redisSim.h"
namespace RSim
{

simForwarder::simForwarder(forwarder_conn_info info)
{
    _info = info;
    auto bus = message_bus<simForwarder>::instance();

    bus->register_handler(DELETE_F, (void *)this, [&](void *objp, void *msgp, std::string topic) {
        if (!objp)
        {
            return;
        }
        if (!msgp)
        {
            return;
        }

        msg_c2s msg = unpack_msg_c2s((char *)msgp);

        forwarder_conn_info tmp;

        tmp.str_to_forwarder_conn_info(std::string((char *)(msg.msg), msg.len));

        this->stop_f((forwarder_conn_info *)(&msgp));
    });

    // start listener
    ss.start_simserver(info);
}

void simForwarder::start()
{
    ss.wait();
}
void simForwarder::stop()
{
    ss.stop();
}
void simForwarder::stop_f(forwarder_conn_info *msgp)
{
    // check if the message is ourself
    if (*msgp == _info)
    {
        // do the stop work
        stop();

        // send to message bus
        auto bus = message_bus<simForwarder>::instance();
        bus->call(DELETE_F_INS, this);
    }
    else
    {
        // not us
        return;
    }
}
}