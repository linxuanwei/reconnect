
#ifndef BASE_NET_SINGLETON_H
#define BASE_NET_SINGLETON_H

#include "NonCopyable.h"

#include <pthread.h>
#include <stdlib.h>

namespace basenet
{

	template<typename T>
		class Singleton : private Noncopyable
	{
		public:
			static T& instance()
			{
				pthread_once(&ponce_, &Singleton::init);
				return *value_;
			}

		private:
			Singleton();
			~Singleton();

			static void init()
			{
				value_ = new T();
				::atexit(destroy);
			}

			static void destroy()
			{
				typedef char T_must_be_complete_type[sizeof(T) == 0 ? -1 : 1];
				T_must_be_complete_type dummy; (void) dummy;

				delete value_;
			}

		private:
			static pthread_once_t ponce_;
			static T*             value_;
	};

	template<typename T>
		pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

	template<typename T>
		T* Singleton<T>::value_ = NULL;

}
#endif
