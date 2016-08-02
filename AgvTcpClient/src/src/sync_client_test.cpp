/*
 * sync_client_test.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: agv
 */

#include "syncsocket.h"
#include "agvcmd.h"
#include "boost/thread.hpp"
const int TEST_LEFT_PWM = -20;
const int TEST_RIGHT_PWM = -20;
const int TIMEOUT = 40;//单位：ms
int main(int argc, char **argv) {
	try {

		std::cout<<"waiting..."<<std::endl;
		boost::asio::io_service io_;
		tcp::endpoint endpoint_(boost::asio::ip::address::from_string("192.168.1.33"),2000);
		tcpclient client(io_);
		client.connect(endpoint_);
		//std::cout<<"read_handle"<<std::endl;
		//client.read_handle(TIMEOUT);
		//std::cout<<"fill"<<std::endl;
		ControlPackge cmd_test;
		FillCommand(TEST_LEFT_PWM,TEST_RIGHT_PWM,cmd_test);
		//std::cout<<"write"<<std::endl;
		//client.write_handle(cmd_test,TIMEOUT);

		boost::thread thread2(boost::bind(&tcpclient::write_handle,&client,cmd_test,TIMEOUT));
		boost::thread thread1(boost::bind(&tcpclient::read_handle,&client,TIMEOUT));

	    thread2.join();
	    thread1.join();
	} catch (std::exception &e) {
		std::cerr<<e.what()<<std::endl;
	}
	return 0;
}

