/*
 * =====================================================================================
 *
 *       Filename:  client.h
 *
 *    Description:  tclient
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 16时36分11秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "../include/EventLoop.h"
#include "../include/TcpClient.h"
#include <boost/noncopyable.hpp>

using namespace muduo;
using namespace muduo::net;

class TClient
{
	public:
		TClient(muduo::net::EventLoop* loop,const muduo::net::InetAddress& listenAddr);
		void connect();
		void OneMinuteLoop();
	private:
		void onConnection(const muduo::net::TcpConnectionPtr& conn);
		void onMessage(const muduo::net::TcpConnectionPtr& conn,muduo::net::Buffer* buf);
	private:
		EventLoop *loop_;
		TcpClient client_;
};


