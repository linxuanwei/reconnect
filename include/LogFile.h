#ifndef BASE_NET_LOGFILE_H
#define BASE_NET_LOGFILE_H

#include "Mutex.h"
#include "Types.h"
#include "NonCopyable.h"

#include <boost/scoped_ptr.hpp>

namespace basenet
{

class LogFile : private Noncopyable
{
 public:
  LogFile(const str_string& basename,
          size_t rollSize,
          bool threadSafe = true,
          int flushInterval = 3);
  ~LogFile();

  void append(const char* logline, int len);
  void flush();

 private:
  void append_unlocked(const char* logline, int len);

  static str_string getLogFileName(const string& basename, time_t* now);
  void rollFile();

  const str_string basename_;
  const size_t rollSize_;
  const int flushInterval_;

  int count_;

  boost::scoped_ptr<MutexLock> mutex_;
  time_t startOfPeriod_;
  time_t lastRoll_;
  time_t lastFlush_;
  class File;
  boost::scoped_ptr<File> file_;

  const static int kCheckTimeRoll_ = 1024;
  const static int kRollPerSeconds_ = 60*60*24;
};

}
#endif
