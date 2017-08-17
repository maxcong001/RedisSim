#include "redisSim/redisSim.h"
#include "redisSim/simCommandServer.h"
#include "redisSim/simForwarder.h"
#include <functional>
namespace RSim
{
//using namespace std::placeholders;
bool redisSim::init()
{
    __LOG(debug, "[redisSim] init is called!");
    auto cs = simCommandServer::instance();
    if (!cs->listen("127.0.0.1", CS_PORT))
    {
        __LOG(error, "command server listen failed, check the port");
        return false;
    }
    __LOG(debug, "[redisSim] command server listen success on port : " << CS_PORT);
    //auto _func = std::bind(&redisSim::add, this);
    auto bus = message_bus<simForwarder>::instance();
    bus->register_handler(ADD_F, this, [&](void *objp, void *msgp, std::string topic) {
        if (!objp)
        {
            return;
        }
        if (!msgp)
        {
            return;
        }
        // new a forwarder and record the pointer in the internal map
        // start a new thread
        msg_c2s msg = unpack_msg_c2s((char *)msgp);

        forwarder_conn_info tmp;

        tmp.str_to_forwarder_conn_info(std::string((char *)(msg.msg), msg.len));
        tmp.dump();
        using namespace std::placeholders;
        auto _func = std::bind(&redisSim::add, this, tmp);
        std::thread forwarder_t(_func);
        forwarder_t.detach();
        //add((forwarder_conn_info *)msgp);
    });

    bus->register_handler(DELETE_F_INS, this, [&](void *objp, void *msgp, std::string topic) {
        if (!objp)
        {
            return;
        }
        if (!msgp)
        {
            return;
        }
        // delete form internal map
        ((redisSim *)objp)->delete_f((simForwarder *)msgp);
    });
    __LOG(debug, "[redisSim] register handler success, then call redis command server wait function wait for client's input");
    cs->wait();
    return true;
}

void redisSim::add(forwarder_conn_info &info)
{
    std::lock_guard<std::mutex> lck(mtx);
    __LOG(debug, "[redisSim] now new a sim forwarder, IP info :");
    info.dump();

    auto tmp = new simForwarder(info);
    __LOG(debug, "[redisSim] add the simForwarder to the forwarder map");
    f_map.emplace(tmp);
    tmp->start();
    __LOG(error, "[redisSim] exit the new forwarder thread");
}
bool redisSim::delete_f(simForwarder *msgp)
{
    std::lock_guard<std::mutex> lck(mtx);
    __LOG(debug, "[redisSim] now delete a sim forwarder");
    msgp->stop();
    f_map.erase(msgp);
    delete msgp;
    msgp = NULL;
    return true;
}
}