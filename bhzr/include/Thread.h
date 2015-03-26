
#ifndef BASE_NET_THREAD_H
#define BASE_NET_THREAD_H

#include "Atomic.h"
#include "Types.h"
#include "NonCopyable.h"

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <pthread.h>

namespace basenet
{
	class Thread : private Noncopyable
	{
		public:
			typedef boost::function<void ()> ThreadFunc;

			explicit Thread(const ThreadFunc&, const str_string& name = str_string());
			~Thread();

			void start();
			int join(); // return pthread_join()

			bool started() const { return started_; }
			// pthread_t pthreadId() const { return pthreadId_; }
			pid_t tid() const { return *tid_; }
			const str_string& name() const { return name_; }

			static int numCreated() { return numCreated_.get(); }

		private:
			bool       started_;
			bool       joined_;
			pthread_t  pthreadId_;
			boost::shared_ptr<pid_t> tid_;
			ThreadFunc func_;
			str_string     name_;

			static AtomicInt32 numCreated_;
	};

}
#endif
