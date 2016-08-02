/*
 * boostsocket.cpp
 *
 *  Created on: Aug 1, 2016
 *      Author: agv
 */
#ifndef SYNCSOCKET_H_
#define SYNCSOCKET_H_

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/timer/timer.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "data_definition.h"

const size_t MAX_RCV_SIZE = 1024*2;
const size_t MAX_SEND_SIZE = sizeof(ControlPackge);

using boost::asio::ip::tcp;


class tcpclient{
public:
	tcpclient(boost::asio::io_service &io_service)
						:soc_(io_service),
						 timer_(io_service)
				{}
	void connect(tcp::endpoint &iendpoint)
	{
		boost::system::error_code error;
		soc_.connect(iendpoint,error);
		if (error) {
			std::cout<<"reconnect."<<std::endl;
			soc_.connect(iendpoint);
		}

	}
	int read_handle(int timeout)
	{
		for(;;){
			AGVDATA agv_buffer_;
		VBytes read_buff_;
		read_buff_.resize(MAX_RCV_SIZE);
		boost::system::error_code error;
		size_t slen_ = soc_.read_some(boost::asio::buffer(read_buff_),error);
		if (error == boost::asio::error::eof)
			break;
		else if (error)
			throw boost::system::error_code(error);
		agv_buffer_.SensorsData.TimeStamp.bit[0] = read_buff_[5];
		agv_buffer_.SensorsData.TimeStamp.bit[1] = read_buff_[6];
		std::cout<<"recv bytes:"<<slen_<<"\ttime:"<<agv_buffer_.SensorsData.TimeStamp.value<<std::endl;
		timer_.expires_from_now(boost::posix_time::milliseconds(timeout));
		timer_.wait();
	    }
		return 0;
	}

	int write_handle(ControlPackge &cmd,int timeout)
	{
		for(;;){
		//ControlPackge Buffer;
		char write_buff[sizeof(ControlPackge)];
		memset(write_buff,'0',sizeof(write_buff));
		FillCmd2Buff(write_buff,cmd);
		boost::system::error_code error;
		size_t slen_ = soc_.write_some(boost::asio::buffer(write_buff),error);
		if (error == boost::asio::error::eof)
			break;
		else if (error)
			throw boost::system::error_code(error);
		std::cout<<"cmd"<<cmd.cmd.WheelLeft.value<<std::endl;
		std::cout<<"send bytes:"<<slen_<<std::endl;
		timer_.expires_from_now(boost::posix_time::milliseconds(timeout));
		timer_.wait();
		}
		return 0 ;
	}
	void FillCmd2Buff(char* write_buff,ControlPackge &Buffer)
		{
			write_buff[0] = Buffer.FrameDataHeader.FrameHeader.bit[0];
			write_buff[1] = Buffer.FrameDataHeader.FrameHeader.bit[1];
			write_buff[2] = Buffer.FrameDataHeader.DatasLength;
			write_buff[3] = Buffer.cmd.DataHeader;
			write_buff[4] = Buffer.cmd.DataLenght;
			write_buff[5] = Buffer.cmd.WheelLeft.bit[0];
			write_buff[6] = Buffer.cmd.WheelLeft.bit[1];
			write_buff[7] = Buffer.cmd.WheelLeft.bit[2];
			write_buff[8] = Buffer.cmd.WheelLeft.bit[3];
			write_buff[9] = Buffer.cmd.WheelRight.bit[0];
			write_buff[10] = Buffer.cmd.WheelRight.bit[1];
			write_buff[11] = Buffer.cmd.WheelRight.bit[2];
			write_buff[12] = Buffer.cmd.WheelRight.bit[3];
			write_buff[13] = Buffer.checksum;
		}


	void AppendCmd2Buff(VBytes &send_buf,ControlPackge &cmdpack)
	{
		send_buf.resize(MAX_SEND_SIZE);
		send_buf.push_back(cmdpack.FrameDataHeader.FrameHeader.bit[0]);
		send_buf.push_back(cmdpack.FrameDataHeader.FrameHeader.bit[1]);
		send_buf.push_back(cmdpack.FrameDataHeader.DatasLength);
		send_buf.push_back(cmdpack.cmd.DataHeader);
		send_buf.push_back(cmdpack.cmd.DataLenght);
		send_buf.push_back(cmdpack.cmd.WheelLeft.bit[0]);
		send_buf.push_back(cmdpack.cmd.WheelLeft.bit[1]);
		send_buf.push_back(cmdpack.cmd.WheelLeft.bit[2]);
		send_buf.push_back(cmdpack.cmd.WheelLeft.bit[3]);
		send_buf.push_back(cmdpack.cmd.WheelRight.bit[0]);
		send_buf.push_back(cmdpack.cmd.WheelRight.bit[1]);
		send_buf.push_back(cmdpack.cmd.WheelRight.bit[2]);
		send_buf.push_back(cmdpack.cmd.WheelRight.bit[3]);
		send_buf.push_back(cmdpack.checksum);
	}


private:
tcp::socket soc_;
boost::asio::deadline_timer timer_;
};

#endif

