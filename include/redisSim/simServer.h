#pragma once
#include "logger/logger.h"
namespace RSim
{

class simServer : public translib::TcpServer
{
  public:
    static simServer *instance()
    {
        static simServer *ins = new simServer();
        return ins;
    }

  protected:
    virtual void onListenError()
    {
        __LOG(debug, " run here");
    }

    virtual void onSessionRead(translib::TcpSession *session)
    {

        uint32_t length = session->getInputBufferLength();

        uint8_t buff[1024];

        session->readInputBuffer(buff, length);
        std::string str((char *)buff, length);

        __LOG(debug, "receive message with length : " << length << " data is " << str);

        __LOG(debug, "sesson id is : " << session->id());
    }

    virtual void onSessionDisconnected(translib::TcpSession *session)
    {
        __LOG(debug, " run here");
    }

    virtual void onNewSession(translib::TcpSession *session)
    {
        __LOG(debug, " run here");
    }
};
}