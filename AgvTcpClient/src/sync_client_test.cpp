/*
 * sync_client_test.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: agv
 */

#include "agvcmdFunction.h"
#include "boost/thread.hpp"

#include "syncsocket.h"
const int TEST_LEFT_PWM = 400;
const int TEST_RIGHT_PWM = -400;
const int READ_TIMEOUT = 100;//单位：ms 20HZ
const int TIMEOUT = 50;//单位：ms
int main(int argc, char **argv) {
	try {

		std::cout<<"waiting..."<<std::endl;
		boost::asio::io_service io_;
		tcp::endpoint endpoint_(boost::asio::ip::address::from_string("192.168.1.33"),2000);
		//tcp::endpoint endpoint_(boost::asio::ip::address::from_string("127.0.0.1"),2000);
		tcpclient client(io_);
		client.connect(endpoint_);
		//bool ReadData = false;
		std::cout<<"connecting..."<<std::endl;
		//std::cout<<"read_handle"<<std::endl;
		//bool OdometryInitialized = false;
		ODOM OdomMsg;
		OdomMsg.Vx = 0.0;
		OdomMsg.Vyaw = 0.0;
		OdomMsg.Pose_X = 0.0;
		OdomMsg.Pose_Y = 0.0;
		OdomMsg.Pose_Theta = 0.0;
		//client.read_handle(TIMEOUT);
		//std::cout<<"fill"<<std::endl;
		//ControlPackge cmd_test;
		//FillCommand(TEST_LEFT_PWM,TEST_RIGHT_PWM,cmd_test);
		//std::cout<<"write"<<std::endl;
		//client.write_handle(cmd_test,TIMEOUT);

		//boost::thread thread2(boost::bind(&tcpclient::write_handle,&client,cmd_test,TIMEOUT));
		boost::thread thread1(boost::bind(&tcpclient::read_handle,&client,READ_TIMEOUT,OdomMsg));

	   // thread2.join();
	    thread1.join();
	} catch (std::exception &e) {
		std::cerr<<e.what()<<std::endl;
	}
	return 0;
}

