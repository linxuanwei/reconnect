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

using namespace basenet;
using namespace basenet::net;

class TClient
{
	public:
		TClient(basenet::net::EventLoop* loop,const basenet::net::InetAddress& listenAddr);
		void connect();
	private:
		void onConnection(const basenet::net::TcpConnectionPtr& conn);
		void onMessage(const basenet::net::TcpConnectionPtr& conn,basenet::net::Buffer* buf);
	private:
		EventLoop *loop_;
		TcpClient client_;
};


