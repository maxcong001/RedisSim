#pragma once
#include <string>
#include <unistd.h>
#include <logger/logger.h>

namespace RSim
{
// command server listen port
#define CS_PORT 2567
#define ADD_F "add_f"
#define UPDATE_F "update_f"
#define DELETE_F "delete_f"
#define ADD_S "add_s"
#define UPDATE_S "update_s"
#define DELETE_S "delete_s"
// delete sim forwarder in the redis sim
#define DELETE_F_INS "delete_f_ins"

// update delay timer
#define UPDATE_DELAY_TIME "up_d_t"

#define MAX_BUFF_LEN 1024
struct simServer_conn_info
{
    std::string serverIP;
    std::string serverPort;
};
struct conector_conn_info
{
    std::string connectorIP;
    std::string connectorPort;
};
// we do not combine simServer_conn_info and conector_conn_info
// for later serialization perpose
struct forwarder_conn_info
{

    std::string serverIP;
    std::string serverPort;
    std::string connectorIP;
    std::string connectorPort;
    forwarder_conn_info()
    {
        __LOG(debug, "[forwarder_conn_info] default constructure!");
    }

    forwarder_conn_info(std::string _serverIP, std::string _serverPort, std::string _connectorIP, std::string _connectorPort)
    {
        serverIP = _serverIP;
        serverPort = _serverPort;
        connectorIP = _connectorIP;
        connectorPort = _connectorPort;
    }
    inline bool operator==(forwarder_conn_info rhs)
    {
        return (!serverIP.compare(rhs.serverIP) && serverPort.compare(rhs.serverPort) && connectorIP.compare(rhs.connectorIP) && connectorPort.compare(rhs.connectorPort));
    }
    std::string seralize()
    {
        return "$*$" + serverIP + "$*$" + serverPort + "$*$" + connectorIP + "$*$" + connectorPort;
    }
    bool str_to_forwarder_conn_info(std::string input)
    {
        std::string tmp = input;
        //temp solution
        std::size_t found = tmp.find_last_of("$*$");
        if (found != std::string::npos)
        {
            std::size_t len = tmp.size() - found - 1;
            std::string IP(tmp, found + 1, len);
            connectorPort = IP;
            std::cout << "connectorPort : " << IP << std::endl;
            tmp.resize(found - 2);
        }
        else
        {
            return false;
        }
        found = tmp.find_last_of("$*$");
        if (found != std::string::npos)
        {
            std::size_t len = tmp.size() - found - 1;
            std::string IP(tmp, found + 1, len);
            connectorIP = IP;
            std::cout
                << "connectorIP : " << IP << std::endl;
            tmp.resize(found - 2);
        }
        else
        {
            return false;
        }
        found = tmp.find_last_of("$*$");
        if (found != std::string::npos)
        {
            std::size_t len = tmp.size() - found - 1;
            std::string IP(tmp, found + 1, len);
            serverPort = IP;
            std::cout << "serverPort : " << IP << std::endl;
            tmp.resize(found - 2);
        }
        else
        {
            return false;
        }
        found = tmp.find_last_of("$*$");
        if (found != std::string::npos)
        {
            std::size_t len = tmp.size() - found - 1;
            std::string IP(tmp, found + 1, len);
            serverIP = IP;
            std::cout << "serverIP : " << IP << std::endl;
            tmp.resize(found - 2);
        }
        else
        {
            return false;
        }
        return true;
    }
    void dump()
    {
        __LOG(debug, "serverIP is : " << serverIP << " serverPort is : " << serverPort << " connectorIP is : " << connectorIP << " connectorPort is : " << connectorPort);
    }
};
struct update_forwarder_conn_info
{
    std::string old_serverIP;
    std::string old_serverPort;
    std::string old_connectorIP;
    std::string old_connectorPort;
    std::string serverIP;
    std::string serverPort;
    std::string connectorIP;
    std::string connectorPort;
};
enum type_c2s
{
    ADD_FORWARDER = 0,
    UPDATE_DELAY,
    DELETE_FORWARDER

};
struct msg_c2s
{
    type_c2s type;
    uint32_t len;
    void *msg;
};

std::string pack_msg_c2s(type_c2s type, const char *msg, uint32_t len);

msg_c2s unpack_msg_c2s(char *buff);

struct msg_with_len
{
    int length;
    char msg[MAX_BUFF_LEN];
};
}
