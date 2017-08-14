#pragma once
#define CS_PORT 2567
#define ADD_F "add_f"
#define UPDATE_F "update_f"
#define DELETE_F "delete_f"
#define ADD_S "add_s"
#define UPDATE_S "update_s"
#define DELETE_S "delete_s"
#define DELETE_F_INS "delete_f_ins"
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
