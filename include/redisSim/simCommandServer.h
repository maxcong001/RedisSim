#pragma once
#include "logger/logger.h"
#include "redisSim/util.h"
#include "translib/tcpServer.h"
#include "redisSim/messageBus.h"
#include "redisSim/redisSim.h"
using namespace translib;

namespace RSim
{

class simCommandServer : public translib::TcpServer
{
  public:
    static simCommandServer *instance()
    {
        static simCommandServer *ins = new simCommandServer();
        return ins;
    }

  protected:
    virtual void onListenError()
    {
        __LOG(debug, "[command server] listen fail");
    }

    virtual void onSessionRead(translib::TcpSession *session)
    {

        uint32_t length = session->getInputBufferLength();
        uint8_t buff[MAX_BUFF_LEN];

        session->readInputBuffer(buff, length);

        __LOG(debug, "[command server] receive message with length : " << length << " data is " << std::string((char *)buff, length));

        msg_c2s msg = unpack_msg_c2s((char *)buff);
        auto bus = message_bus<simForwarder>::instance();
        switch (msg.type)
        {
        case ADD_FORWARDER:
            bus->call(ADD_F, buff);
            break;
        case DELETE_FORWARDER:
            bus->call(DELETE_F, buff);
            break;
        case UPDATE_DELAY:
            bus->call(UPDATE_DELAY_TIME, buff);
            break;
        default:
            __LOG(error, "unknown message type");
        }

        //  just for test.
        //forwarder_conn_info *tmp = new forwarder_conn_info("127.0.0.1", "2568", "127.0.0.1", "2565");
    }

    virtual void onSessionDisconnected(translib::TcpSession *session)
    {
        char tmp_ip[sizeof(sockaddr_in)];
        session->getAddr((struct sockaddr_in *)tmp_ip, uint32_t(sizeof(sockaddr_in)));
        __LOG(debug, "[command server] session with IP : " << std::string(tmp_ip, sizeof(sockaddr_in)) << " disconnected");
    }

    virtual void onNewSession(translib::TcpSession *session)
    {
        char tmp_ip[sizeof(sockaddr_in)];
        session->getAddr((struct sockaddr_in *)tmp_ip, uint32_t(sizeof(sockaddr_in)));
        __LOG(debug, "[command server] new session with IP : " << std::string(tmp_ip, sizeof(sockaddr_in)));
    }
};
}