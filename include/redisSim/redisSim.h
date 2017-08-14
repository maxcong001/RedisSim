#pragma once
#include < unordered_set>
#include "logger/logger.h"
namespace RSim
{

class redisSim
{
    bool init()
    {
        auto cs = simCommandServer::instance();
        if (!cs.listen("127.0.0.1", CS_PORT))
        {
            __LOG(error, "command server listen failed, check the port");
            return;
        }

        auto bus = message_bus<redisSim>::instance();
        bus->register_handler(ADD_F, this, [](void *objp, void *msgp, std::string topic) {
            if (!objp)
            {
                return;
            }
            if (!msgp)
            {
                return;
            }
            // new a forwarder and record the pointer in the internal map
            add(forwarder_conn_info * info);
        });

        bus->register_handler(DELETE_F_INS, this, [](void *objp, void *msgp, std::string topic) {
            if (!objp)
            {
                return;
            }
            if (!msgp)
            {
                return;
            }
            // delete form internal map
            delete ((simForwarder *)msgp);
        });

        bool add(forwarder_conn_info * info)
        {
            auto tmp = new simForwarder(info);
            f_map.emplace(tmp);
        }
        bool delete (simForwarder * msgp)
        {
            f_map.erase(msgp);
        }

        std::unordered_set<int, simForwarder *>
            f_map;
    }
};
}