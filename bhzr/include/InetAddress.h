
#ifndef BASE_NET_INETADDRESS_H
#define BASE_NET_INETADDRESS_H

#include "copyable.h"
#include "StringPiece.h"

#include <netinet/in.h>

namespace basenet
{
	namespace net
	{

		class InetAddress : public basenet::copyable
		{
			public:
				explicit InetAddress(uint16_t port);

				InetAddress(const StringPiece& ip, uint16_t port);

				InetAddress(const struct sockaddr_in& addr)
					: addr_(addr)
				{ }

				str_string toIp() const;
				str_string toIpPort() const;
				str_string toHostPort() const __attribute__ ((deprecated))
				{ return toIpPort(); }


				const struct sockaddr_in& getSockAddrInet() const { return addr_; }
				void setSockAddrInet(const struct sockaddr_in& addr) { addr_ = addr; }

				uint32_t ipNetEndian() const { return addr_.sin_addr.s_addr; }
				uint16_t portNetEndian() const { return addr_.sin_port; }

			private:
				struct sockaddr_in addr_;
		};

	}
}

#endif
