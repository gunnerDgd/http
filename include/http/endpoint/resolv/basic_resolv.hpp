#pragma once
#include <WinDNS.h>
#include <WinSock2.h>

#include <string>
#include <variant>

#include <type_traits>

namespace http::endpoint::resolv {
	template <typename ResolvBackend>
	class basic_ip_resolver
	{
	public:
		typedef			 ResolvBackend			  backend_type;
		
		typedef typename ResolvBackend::addr_type address_type;
		typedef typename ResolvBackend::host_type host_type;

		typedef typename ResolvBackend::canonical_result canonical_result;
		typedef typename ResolvBackend::address_result   address_result  ;

	public:
		canonical_result resolve_address  (address_type);
		address_result   resolve_canonical(address_type);

	public:
		
	};
}

