#pragma once
#include "logger/logger.h"
#include "redisSim/util.h"
#include "redisSim/simConnector.h"
#include "translib/tcpServer.h"
#include <unordered_map>

using namespace translib;
namespace RSim
{

class simServer : public translib::TcpServer
{
  public:
    typedef std::shared_ptr<simConnector> sc_ptr_p;
    typedef std::shared_ptr<Loop> loop_ptr_p;
    static simServer *instance()
    {
        static simServer *ins = new simServer();
        return ins;
    }
    bool start_simserver(forwarder_conn_info info)
    {
        _info = info;
        if (listen((info.serverIP).c_str(), uint16_t(std::stoi(info.serverPort))))
        {
            __LOG(debug, "[simServer] listen success, IP is : " << (info.serverIP).c_str() << " port is : " << uint16_t(std::stoi(info.serverPort)));
            return true;
        }
        else
        {
            __LOG(error, "[simServer] listen fail, IP is : " << (info.serverIP).c_str() << " port is : " << uint16_t(std::stoi(info.serverPort)));
            return false;
        }
    }

  protected:
    virtual void onListenError()
    {
        __LOG(debug, " sim sercer listen return error");
    }

    virtual void onSessionRead(translib::TcpSession *session)
    {

        uint32_t length = session->getInputBufferLength();

        uint8_t buff[MAX_BUFF_LEN];

        session->readInputBuffer(buff, length);
        std::string str((char *)buff, length);

        __LOG(debug, "receive message with length : " << length << " data is " << str << " now sizeof session map is : " << session_map.size());

        for (auto it : session_map)
        {
            if (it.first == session)
            {
                if ((it.second)->send((char *)buff, length))
                {
                    __LOG(debug, "[simServer] now send message via connector");
                    break;
                }
                else
                {
                    __LOG(error, "[simServer] connector send message to redis return fail");
                    return;
                }
            }
        }

        __LOG(debug, "[simServer] sesson id is : " << session->id());
    }

    virtual void onSessionDisconnected(translib::TcpSession *session)
    {
        session_map.erase(session_map.find(session));
        loop_map.erase(loop_map.find(session));
        __LOG(debug, " run here");
    }

    virtual void onNewSession(translib::TcpSession *session)
    {

        __LOG(debug, "[simServer] new session, now connect to redis, IP is : " << _info.connectorIP << ":" << _info.connectorPort);
        // new a connector and bind to a session
        loop_ptr_p loop(new Loop());
        sc_ptr_p sc(new simConnector(*loop));

        if (!(sc->connect_with_IP(_info.connectorIP, _info.connectorPort)))
        {
            __LOG(error, " connector connect to IP : " << _info.connectorIP << " fail");
            return;
        }
        loop->start(true);

        sc->setSession(session);
        session_map.emplace(session, sc);
        loop_map.emplace(session, loop);
        __LOG(debug, " run here");
    }

  public:
  private:
    forwarder_conn_info _info;
    std::unordered_map<translib::TcpSession *, sc_ptr_p> session_map;
    std::unordered_map<translib::TcpSession *, loop_ptr_p> loop_map;
};
}