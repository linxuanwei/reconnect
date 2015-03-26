
#ifndef BASE_NET_TCPCLIENT_H
#define BASE_NET_TCPCLIENT_H


#include "NonCopyable.h"
#include "Mutex.h"
#include "TcpConnection.h"

namespace basenet
{
namespace net
{

class Connector;
typedef boost::shared_ptr<Connector> ConnectorPtr;

class TcpClient : private Noncopyable
{
 public:
  TcpClient(EventLoop* loop,
            const InetAddress& serverAddr,
            const str_string& name);
  ~TcpClient(); 

  void connect();
  void disconnect();
  void stop();

  TcpConnectionPtr connection() const
  {
    MutexLockGuard lock(mutex_);
    return connection_;
  }

  EventLoop* getLoop() const { return loop_; }
  bool retry() const;
  void enableRetry() { retry_ = true; }

  void setConnectionCallback(const ConnectionCallback& cb)
  { connectionCallback_ = cb; }

  void setMessageCallback(const MessageCallback& cb)
  { messageCallback_ = cb; }

  void setWriteCompleteCallback(const WriteCompleteCallback& cb)
  { writeCompleteCallback_ = cb; }

 private:
  void newConnection(int sockfd);
  void removeConnection(const TcpConnectionPtr& conn);

  EventLoop* loop_;
  ConnectorPtr connector_; 
  const str_string name_;
  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCompleteCallback_;
  bool retry_;  
  bool connect_;
  int nextConnId_;
  mutable MutexLock mutex_;
  TcpConnectionPtr connection_;
};

}
}

#endif  
