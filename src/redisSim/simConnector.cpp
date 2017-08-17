#include "redisSim/simConnector.h"
#include "redisSim/simForwarder.h"
namespace RSim
{

bool simConnector::init()
{
    auto bus = message_bus<simForwarder>::instance();

    bus->register_handler(UPDATE_DELAY_TIME, (void *)this, [&](void *objp, void *msgp, std::string topic) {
        if (!objp)
        {
            return;
        }
        if (!msgp)
        {
            return;
        }
        msg_c2s msg = unpack_msg_c2s((char *)msgp);
        ((simConnector *)objp)->_delay = *((uint32_t *)(msg.msg));
        __LOG(debug, "[simConnector] update delay timer to " << *((uint32_t *)(msg.msg)));
    });
    return true;
}
}