
#ifndef BASE_NET_TCPSERVER_H
#define BASE_NET_TCPSERVER_H

#include "NonCopyable.h"
#include "Types.h"
#include "TcpConnection.h"

#include <map>
#include <boost/scoped_ptr.hpp>

namespace basenet
{
namespace net
{

class Acceptor;
class EventLoop;
class EventLoopThreadPool;

class TcpServer : private Noncopyable
{
 public:
  typedef boost::function<void(EventLoop*)> ThreadInitCallback;
  enum Option
  {
    kNoReusePort,
    kReusePort,
  };

  TcpServer(EventLoop* loop,
            const InetAddress& listenAddr,
            const str_string& nameArg,
            Option option = kNoReusePort);
  ~TcpServer(); 

  const str_string& hostport() const { return hostport_; }
  const str_string& name() const { return name_; }
  EventLoop* getLoop() const { return loop_; }

  void setThreadNum(int numThreads);
  void setThreadInitCallback(const ThreadInitCallback& cb)
  { threadInitCallback_ = cb; }

  void start();

  void setConnectionCallback(const ConnectionCallback& cb)
  { connectionCallback_ = cb; }

  void setMessageCallback(const MessageCallback& cb)
  { messageCallback_ = cb; }

  void setWriteCompleteCallback(const WriteCompleteCallback& cb)
  { writeCompleteCallback_ = cb; }

 private:
  void newConnection(int sockfd, const InetAddress& peerAddr);
  void removeConnection(const TcpConnectionPtr& conn);
  void removeConnectionInLoop(const TcpConnectionPtr& conn);

  typedef std::map<str_string, TcpConnectionPtr> ConnectionMap;

  EventLoop* loop_; 
  const str_string hostport_;
  const str_string name_;
  boost::scoped_ptr<Acceptor> acceptor_;
  boost::scoped_ptr<EventLoopThreadPool> threadPool_;
  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCompleteCallback_;
  ThreadInitCallback threadInitCallback_;
  bool started_;
  int nextConnId_;
  ConnectionMap connections_;
};

}
}

#endif
