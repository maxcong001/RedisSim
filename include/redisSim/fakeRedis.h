#pragma once
#include "logger/logger.h"
#include "redisSim/util.h"
#include "translib/tcpServer.h"
#include "redisSim/messageBus.h"
#include "redisSim/redisSim.h"
using namespace translib;

namespace RSim
{

class fakeRedis : public translib::TcpServer
{
  public:
    static fakeRedis *instance()
    {
        static fakeRedis *ins = new fakeRedis();
        return ins;
    }

  protected:
    virtual void onListenError()
    {
        __LOG(debug, "[fakeRedis] listen fail");
    }

    virtual void onSessionRead(translib::TcpSession *session)
    {

        uint32_t length = session->getInputBufferLength();

        uint8_t buff[MAX_BUFF_LEN];

        session->readInputBuffer(buff, length);
        std::string str((char *)buff, length);

        __LOG(debug, "[fakeRedis] receive message with length : " << length << " data is " << str);
        // send back message

        session->send((char *)buff, length);

        __LOG(debug, "[fakeRedis] sesson id is : " << session->id());
    }

    virtual void onSessionDisconnected(translib::TcpSession *session)
    {
        char tmp_ip[sizeof(sockaddr_in)];
        session->getAddr((struct sockaddr_in *)tmp_ip, uint32_t(sizeof(sockaddr_in)));
        __LOG(debug, "[fakeRedis] session with IP : " << std::string(tmp_ip, sizeof(sockaddr_in)) << " disconnected");
    }

    virtual void onNewSession(translib::TcpSession *session)
    {
        char tmp_ip[sizeof(sockaddr_in)];
        session->getAddr((struct sockaddr_in *)tmp_ip, uint32_t(sizeof(sockaddr_in)));
        __LOG(debug, "[fakeRedis] new session with IP : " << std::string(tmp_ip, sizeof(sockaddr_in)));
    }
};
}