#pragma once
#include "logger/logger.h"
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

        uint8_t buff[1024];

        session->readInputBuffer(buff, length);
        std::string str((char *)buff, length);

        __LOG(debug, "[command server] receive message with length : " << length << " data is " << str);

        //  just for test.
        

        __LOG(debug, "[command server] sesson id is : " << session->id());
    }

    virtual void onSessionDisconnected(translib::TcpSession *session)
    {
        char tmp_ip[sizeof(sockaddr_in)];
        session->getAddr(tmp_ip, sizeof(sockaddr_in));
        __LOG(debug, "[command server] session with IP : " << std::string(tmp_ip, sizeof(sockaddr_in)) << " disconnected");
    }

    virtual void onNewSession(translib::TcpSession *session)
    {
        char tmp_ip[sizeof(sockaddr_in)];
        session->getAddr(tmp_ip, sizeof(sockaddr_in));
        __LOG(debug, "[command server] new session with IP : " << std::string(tmp_ip, sizeof(sockaddr_in)));
    }
};
}