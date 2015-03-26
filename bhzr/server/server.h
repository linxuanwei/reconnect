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

using namespace basenet;
using namespace basenet::net;

class TServer
{
	public:
		TServer(basenet::net::EventLoop* loop,const basenet::net::InetAddress& listenAddr);
		void start();
	private:
		void onConnection(const basenet::net::TcpConnectionPtr& conn);
		void onMessage(const basenet::net::TcpConnectionPtr& conn,basenet::net::Buffer* buf);
	private:
		EventLoop *loop_;
		TcpServer server_;
};


