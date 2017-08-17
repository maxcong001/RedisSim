#pragma once
#include "logger/logger.h"
#include "util/singleton.h"
#include "redisSim/util.h"
#include "translib/tcpClient.h"
#include "translib/tcpSession.h"
#include "translib/timerManager.h"
using namespace translib;
namespace RSim
{
class simConnector : public translib::TcpClient
{
  public:
    simConnector(const translib::Loop &loop) : translib::TcpClient(loop)
    {
        _connected = false;
        _delay = 1000;
        init();
    }
    bool init();

    bool connect_with_IP(std::string IP, std::string Port)
    {
        __LOG(debug, "[simConnector] connect to " << IP << ":" << Port);
        _IP = IP;
        _Port = Port;
        return connect(IP.c_str(), uint16_t(std::stoi(Port)));
    }
    bool isConnected()
    {
        return _connected;
    }
    void setDelay(uint32_t delay)
    {
        delay = _delay;
    }

  protected:
    virtual void onRead()
    {
        uint32_t length = getInputBufferLength();
        // tmp solution, later use malloc according to the message length
        msg_with_len *tmp = new msg_with_len();
        tmp->length = length;

        readInputBuffer((uint8_t *)(tmp->msg), length);
        __LOG(debug, "[simConnector]  get buffer " << std::string(((char *)tmp->msg), length) << " length is : " << length);
        auto timerM = Singleton<translib::TimerManager>::Instance();
        auto timer = timerM->getTimer();
        timer->startOnce(_delay, (void *)tmp, [&](void *usrdata) {

            (this->session)->send((char *)(((msg_with_len *)usrdata)->msg), ((msg_with_len *)usrdata)->length);
            __LOG(error, "[simConnector]  send buffer to client with len : " << ((msg_with_len *)usrdata)->length);
            //(this->session)->send("aa", length);
            delete (msg_with_len *)usrdata;
            usrdata = NULL;

        });
    }

    virtual void onDisconnected()
    {
        reconnect();
        __LOG(debug, " run here");
    }

    virtual void onConnected(int error)
    {
        __LOG(debug, " run here");
    }
    virtual bool reconnect()
    {
        return connect_with_IP(_IP, _Port);
    }

  public:
    virtual void setSession(translib::TcpSession *sessionP)
    {
        session = sessionP;
    }

  private:
    std::string _IP;
    std::string _Port;
    translib::TcpSession *session;
    bool _connected;
    uint32_t _delay;
};
}