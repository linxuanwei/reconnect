
#ifndef BASE_NET_TCPCONNECTION_H
#define BASE_NET_TCPCONNECTION_H

#include "Mutex.h"
#include "StringPiece.h"
#include "Types.h"
#include "NonCopyable.h"
#include "Callbacks.h"
#include "Buffer.h"
#include "InetAddress.h"

#include <boost/any.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace basenet
{
namespace net
{

class Channel;
class EventLoop;
class Socket;

class TcpConnection : private Noncopyable,
                      public boost::enable_shared_from_this<TcpConnection>
{
 public:
  TcpConnection(EventLoop* loop,
                const str_string& name,
                int sockfd,
                const InetAddress& localAddr,
                const InetAddress& peerAddr);
  ~TcpConnection();

  EventLoop* getLoop() const { return loop_; }
  const str_string& name() const { return name_; }
  const InetAddress& localAddress() { return localAddr_; }
  const InetAddress& peerAddress() { return peerAddr_; }
  bool connected() const { return state_ == kConnected; }

  void send(const void* message, size_t len);
  void send(const StringPiece& message);
  void send(Buffer* message);
  void shutdown(); 
  void setTcpNoDelay(bool on);

  void setContext(const boost::any& context)
  { context_ = context; }

  const boost::any& getContext() const
  { return context_; }

  boost::any* getMutableContext()
  { return &context_; }

  void setConnectionCallback(const ConnectionCallback& cb)
  { connectionCallback_ = cb; }

  void setMessageCallback(const MessageCallback& cb)
  { messageCallback_ = cb; }

  void setWriteCompleteCallback(const WriteCompleteCallback& cb)
  { writeCompleteCallback_ = cb; }

  void setHighWaterMarkCallback(const HighWaterMarkCallback& cb, size_t highWaterMark)
  { highWaterMarkCallback_ = cb; highWaterMark_ = highWaterMark; }

  Buffer* inputBuffer()
  { return &inputBuffer_; }

  void setCloseCallback(const CloseCallback& cb)
  { closeCallback_ = cb; }

  void connectEstablished();
  void connectDestroyed();

 private:
  enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };
  void handleRead(Timestamp receiveTime);
  void handleWrite();
  void handleClose();
  void handleError();
  void sendInLoop(const StringPiece& message);
  void sendInLoop(const void* message, size_t len);
  void shutdownInLoop();
  void setState(StateE s) { state_ = s; }

  EventLoop* loop_;
  str_string name_;
  StateE state_;
  boost::scoped_ptr<Socket> socket_;
  boost::scoped_ptr<Channel> channel_;
  InetAddress localAddr_;
  InetAddress peerAddr_;
  ConnectionCallback connectionCallback_;
  MessageCallback messageCallback_;
  WriteCompleteCallback writeCompleteCallback_;
  HighWaterMarkCallback highWaterMarkCallback_;
  CloseCallback closeCallback_;
  size_t highWaterMark_;
  Buffer inputBuffer_;
  Buffer outputBuffer_; 
  boost::any context_;
};

typedef boost::shared_ptr<TcpConnection> TcpConnectionPtr;

}
}

#endif
