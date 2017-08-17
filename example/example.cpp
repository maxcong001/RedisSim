//============================================================================
// Name        : test.cpp
// Author      :
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <string>
#include <map>
#include "redisSim/simCommandServer.h"
#include "redisSim/simClient.h"
#include "redisSim/fakeRedis.h"
#include "redisSim/appClient.h"
#include "redisSim/util.h"
#include "translib/define.h"

using namespace std;

void start_command_server()
{
	auto ins = RSim::simCommandServer::instance();
	ins->wait();
}
void app_send_message(RSim::AppClient &ac)
{
	__LOG(debug, "now send message");
	if (ac.send("aaa", 2))
	{
		__LOG(debug, "app client send message success");
	}
	else
	{
		__LOG(error, "app client send message fail");
	}
	sleep(1);
	if (ac.send("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 10))
	{
		__LOG(debug, "app client send message success");
	}
	else
	{
		__LOG(error, "app client send message fail");
	}
}

int main(int argc, char *argv[])
{
	//port:
	//command server  2567
	//sim server 2568
	//fake redis 2565

	// now start fake redis
	__LOG(debug, "now start fake redis");
	RSim::fakeRedis fr;
	if (!fr.listen("127.0.0.1", 2565))
	{
		__LOG(error, " fake redis listen return fail!");
	}

	// redis simulator thread
	__LOG(debug, "now start redis simulator");
	RSim::redisSim rs;
	auto rs_f = std::bind(&RSim::redisSim::init, &rs);
	std::thread sim_thread(rs_f);
	sim_thread.detach();

	sleep(1);

	//simulator client thread
	__LOG(debug, "now start client");
	Loop loop;
	RSim::SimClient sc(loop);
	if (!sc.connect("127.0.0.1", CS_PORT))
	{
		__LOG(error, " connector connect to command server return fail!");
	}
	loop.start(true);
	sleep(1);

	//  just for test.
	RSim::forwarder_conn_info tmp = RSim::forwarder_conn_info("127.0.0.1", "2568", "127.0.0.1", "2565");
	std::string tmp_str = tmp.seralize();
	std::string message = RSim::pack_msg_c2s(RSim::ADD_FORWARDER, tmp_str.c_str(), (uint32_t)tmp_str.size());
	__LOG(debug, "message after pack is " << message);

	sc.send(message.c_str(), (uint32_t)(message.size()));

	sleep(1);
	// now start the APP client
	Loop loop1;
	__LOG(debug, "now start the APP client");
	RSim::AppClient ac(loop1);
	if (!ac.connect("127.0.0.1", 2568))
	{
		__LOG(error, " app client connect to sim server return fail!");
	}
	loop1.start();

	// now App send message
	sleep(1);
	app_send_message(ac);
	sleep(1);
	app_send_message(ac);

	// now update the delay timer
	uint32_t delay = 10000;
	std::string message_001 = RSim::pack_msg_c2s(RSim::UPDATE_DELAY, (char *)(&delay), (uint32_t)(sizeof(uint32_t)));
	__LOG(debug, "update the delay timer to 10s");
	sc.send(message_001.c_str(), (uint32_t)(message_001.size()));

	// now App send message
	sleep(1);
	app_send_message(ac);
	sleep(1);
	app_send_message(ac);

	loop.wait();
	__LOG(error, "exit example!");
	return 0;
}
