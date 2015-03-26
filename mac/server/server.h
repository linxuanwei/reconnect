/*
 * =====================================================================================
 *
 *       Filename:  server.h
 *
 *    Description:  test server
 *
 *        Version:  1.0
 *        Created:  2015年03月26日 10时23分48秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../include/EventLoop.h"
#include "../include/TcpServer.h"
#include <boost/noncopyable.hpp>

using namespace muduo;
using namespace muduo::net;

class TServer
{
	public:
		TServer(muduo::net::EventLoop* loop,const muduo::net::InetAddress& listenAddr);
		void start();
	private:
		void onConnection(const muduo::net::TcpConnectionPtr& conn);
		void onMessage(const muduo::net::TcpConnectionPtr& conn,muduo::net::Buffer* buf);
	private:
		EventLoop *loop_;
		TcpServer server_;
};


