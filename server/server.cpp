#include <boost/bind.hpp>
#include <iostream>
#include "server.h"

TServer:: TServer(EventLoop* loop,const InetAddress& listenAddr):
		loop_(loop),server_(loop,listenAddr,"TServer")
{
	server_.setConnectionCallback(boost::bind(&TServer::onConnection, this, _1));
	server_.setMessageCallback(boost::bind(&TServer::onMessage, this, _1, _2));
}

void TServer::start()
{
	server_.start();
}

void TServer::onConnection(const TcpConnectionPtr& conn)
{
	if(conn->connected())
	{

	}
}

void TServer::onMessage(const TcpConnectionPtr& conn,Buffer* buf)
{

}

int main()
{
	EventLoop loop;
	InetAddress serverAddress(2007);
	TServer server(&loop,serverAddress);
	server.start();
	loop.loop();
}
