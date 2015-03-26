#include "client.h"
#include <iostream>
#include <boost/bind.hpp>

TClient:: TClient(basenet::net::EventLoop* loop,const basenet::net::InetAddress& serverAddr)
	:loop_(loop),client_(loop,serverAddr,"TClient")
{
	client_.setConnectionCallback(boost::bind(&TClient::onConnection, this, _1));
	client_.setMessageCallback(boost::bind(&TClient::onMessage, this, _1, _2));
//	client_.enableRetry();
}

void TClient::connect()
{
	client_.connect();
}

void TClient::onConnection(const TcpConnectionPtr& conn)
{
	if(conn->connected())
	{
		std::cout<<conn->localAddress().toIpPort()<<" -> "<<conn->peerAddress().toIpPort()<< " is "<<(conn->connected() ? "UP" : "DOWN")<<std::endl;
	}
}

void TClient::onMessage(const TcpConnectionPtr& conn, Buffer* buf)
{

}

int main()
{
	EventLoop loop;
	InetAddress serverAddr("127.0.0.1", 2007);
	TClient client(&loop,serverAddr);
	client.connect();
	loop.loop();
}
