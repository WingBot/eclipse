//============================================================================
// Name        : AgvTcpClient.cpp
// Author      : szr
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/timer/timer.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "data_definition.h"
union Timer_Stamp
{
    uint16_t value;     //单个轮子的轮速(RPM),注意单位的统一。
    uint8_t NumBit[2];     //轮速对应的四个字节。
};

/*
 * 主要流程如下：
通过tcp::socket类定义一个tcp client对象socket
通过connect函数连接服务器，打开socket连接。
通过read_some函数来读数据
另外，还可以通过write_some来写数据，通过close来关闭socket连接（这里是通过释放socket对象隐式释放连接）。
 *
 * */


typedef std::vector<uint8_t> Bytes;
using boost::asio::ip::tcp;
//boost::asio::deadline_timer m_Timer;

void start_read(boost::system::error_code &error, size_t &strlen,boost::asio::ip::tcp::socket &sock,const boost::posix_time::time_duration &expiry_time){


return;
}


    int test_main(int argc, char**argv)
    {
        try
        {
            boost::asio::io_service io_service;
            tcp::endpoint end_point(boost::asio::ip::address::from_string("192.168.1.33"), 2000);
            boost::asio::deadline_timer timer(io_service);
            tcp::socket socket(io_service);
            socket.connect(end_point);
            for (;;)
            {
            	Timer_Stamp Buffer;
                //boost::array<char, 128> buf;
                char Cbuff_read[1024];
                boost::system::error_code error;

                size_t slen = socket.read_some(boost::asio::buffer(Cbuff_read), error);
                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.
                Buffer.NumBit[0] = Cbuff_read[5];
                Buffer.NumBit[1] = Cbuff_read[6];
                //std::cout.write(buf.data(), len);
                std::cout<<"bytes:"<<slen<<"\ttime:"<<Buffer.value<<std::endl;
               // printf("time:%d!\n",Buffer.value);
                timer.expires_from_now(boost::posix_time::milliseconds(20));
                timer.wait();
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        return 0;
    }
