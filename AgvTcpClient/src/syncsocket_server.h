/*
 * syncsocket_server.h
 *
 *  Created on: Aug 2, 2016
 *      Author: agv
 */

#ifndef SYNCSOCKET_SERVER_H_
#define SYNCSOCKET_SERVER_H_
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/timer/timer.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "data_definition.h"
#include "agvcmdFunction.h"


class tcpserver {
public:
	tcpserver(boost::asio::io_service &io_service,boost::asio::ip::tcp::endpoint &iendpoint)
							:soc_(io_service),
							 acceptor_(io_service,iendpoint),
							 timer_(io_service)
							{}
	~tcpserver(){}
	void acceptor()
	{

		std::cout<<"accepting..."<<std::endl;
		boost::system::error_code error;
		acceptor_.accept(soc_,error);
		if (!error)
			std::cout<<"acceptor success"<<std::endl;
		else {
			std::cout<<"acceptor fail."<<std::endl;
			acceptor();
			std::cout<<"reaccepting..."<<std::endl;
		}
		//timer_.expires_from_now(boost::posix_time::milliseconds(timeout));
		//timer_.wait();

	}

	int write_handle(int timeout)
	{

		boost::system::error_code error;
		HANsFeedbackData send_temp_;
		FillStaticFeedback(send_temp_);//填充固定反馈
		unsigned char send_buff_[sizeof(HANsFeedbackData)];

		for (int i = 0;i<1000;++i) {
			//填充时间
			send_temp_.Data.SensorsData.TimeStamp.value = i;
			send_temp_.Data.SensorsData.WheelLeft_Encoder.value = i+100;
			send_temp_.Data.SensorsData.WheelRight_Encoder.value = i+100;
			send_temp_.Data.Gyromsg.Angle.value = 0;//跟上面速度对应
			send_temp_.Data.Gyromsg.AngleRate.value = i+5;
			//mempcpy(send_buff_,send_temp_.bit,0,sizeof(send_temp_));
			for (int var = 0; var < 34; ++var)//拷贝发送指令到缓存
				{
				send_buff_[var] = send_temp_.bit[var];

				}
			std::cout <<"time:"
								<<send_temp_.Data.SensorsData.TimeStamp.value \
								<<"\tleft:"
								<<send_temp_.Data.SensorsData.WheelLeft_Encoder.value \
								<<"\tright:"
								<<send_temp_.Data.SensorsData.WheelRight_Encoder.value<< std::endl;
			soc_.write_some(boost::asio::buffer(send_buff_),error);
			timer_.expires_from_now(boost::posix_time::milliseconds(timeout));
			timer_.wait();
		}
			return 0;
	}



private:
	boost::asio::ip::tcp::socket soc_;
	boost::asio::ip::tcp::acceptor acceptor_;
	boost::asio::deadline_timer timer_;

};



#endif /* SYNCSOCKET_SERVER_H_ */
