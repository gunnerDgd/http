#pragma once
#include <http/endpoint/resolv/v4_backend.hpp>
using namespace http::endpoint::resolv;

static IP4_ADDRESS default_resolver;

v4_backend::v4_backend(std::string resolv_config) : __M_v4_conf_fstream(resolv_config, std::ifstream::binary)
{
	Json::String conf_err;
	Json::parseFromStream(__M_v4_conf_reader, __M_v4_conf_fstream, &__M_v4_conf, &conf_err);
}

v4_backend::~v4_backend()
{
	__M_v4_conf_fstream.close();
}

v4_backend::count_result v4_backend::resolve(host_type resolv_host, address_result& resolv_result)
{
	auto query_ret = DnsQuery_A(resolv_host.c_str(), DNS_TYPE_A, DNS_QUERY_BYPASS_CACHE, );
}

v4_backend::count_result v4_backend::resolve(host_type, canonical_result&)
{
}