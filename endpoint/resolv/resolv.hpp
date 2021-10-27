#pragma once
#include <WinSock2.h>
#include <WinDNS.h>

#include <cstddef>
#include <cstdint>

namespace http {
	class resolv
	{
	public:
		class url;
		class v4_address;
		class v6_address;
	};
}