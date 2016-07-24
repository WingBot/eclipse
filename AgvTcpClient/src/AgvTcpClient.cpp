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
boost::asio::deadline_timer m_Timer;

size_t Receive(Bytes& rData, float timeout, boost::system::error_code& rErrorCode)
  {
    m_Timer.expires_from_now(boost::posix_time::milliseconds(timeout));

    rErrorCode = boost::asio::error::would_block;
    size_t size = 0;

    Socket.async_receive(boost::asio::buffer(m_ReadBuffer), boost::bind(&Impl::Handle, _1, _2, &rErrorCode, &size));

    do
    {
      m_IoService.run_one();
    }
    while (rErrorCode == boost::asio::error::would_block);

    if (size >= rData.size())
    {
      size_t startIdx = size - rData.size();
      rData.assign(m_ReadBuffer.begin() + startIdx, m_ReadBuffer.end() - 1);
    }
    else
    {
      rData.assign(m_ReadBuffer.begin(), m_ReadBuffer.end() - 1);
    }

    return size;
  }

    int main(int argc, char* argv[])
    {
        try
        {
            boost::asio::io_service io_service;
            tcp::endpoint end_point(boost::asio::ip::address::from_string("192.168.1.33"), 2000);

            tcp::socket socket(io_service);
            socket.connect(end_point);

            for (;;)
            {
            	//AGVDATA Buffer;
                boost::array<char, 128> buf;
                boost::system::error_code error;

                size_t len = socket.read_some(boost::asio::buffer(buf), error);

                if (error == boost::asio::error::eof)
                    break; // Connection closed cleanly by peer.
                else if (error)
                    throw boost::system::system_error(error); // Some other error.

                std::cout.write(buf.data(), len);
            }
        }
        catch (std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }

        return 0;
    }
