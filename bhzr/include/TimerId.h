
#ifndef BASE_NET_TIMERID_H
#define BASE_NET_TIMERID_H

#include "copyable.h"

namespace basenet
{
namespace net
{

class Timer;

class TimerId : public basenet::copyable
{
 public:
  TimerId()
    : timer_(NULL),
      sequence_(0)
  {
  }

  TimerId(Timer* timer, int64_t seq)
    : timer_(timer),
      sequence_(seq)
  {
  }


  friend class TimerQueue;

 private:
  Timer* timer_;
  int64_t sequence_;
};

}
}

#endif
