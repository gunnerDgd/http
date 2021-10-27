#pragma once
#include <cstddef>
#include <http/endpoint/session/connection/connection.hpp>

namespace http    {
	class message
	{
	public:
		class response;
		class request ;

	public:
		typedef endpoint::session::connection::sender   sender_type;
		typedef endpoint::session::connection::receiver receiver_type;
		typedef std::pair<char*, std::size_t>			raw_type;

	public:
		message () : raw_size(HTTP_MESSAGE_MTU) { HTTP_MESSAGE_ALLOCATE(raw_message); }
		~message()								{ delete[] raw_message; }

	public:
		friend sender_type& operator << (sender_type& __pa_snd, message& __pa_msg) 
		{
			__pa_snd << raw_type(__pa_msg.raw_message, __pa_msg.raw_size);
			return __pa_snd;
		}

		friend receiver_type& operator >> (receiver_type& __pa_rcv, message& __pa_msg)
		{
			__pa_rcv >> raw_type(__pa_msg.raw_message, __pa_msg.raw_size);
			return __pa_rcv;
		}

	protected:
		char*		raw_message;
		std::size_t raw_size;
	};
}