#pragma once
#include <cstddef>
#include <http/endpoint/session/connection/connection.hpp>
#include <http/endpoint/session/connection/secured_connection.hpp>

namespace http    {
	class message
	{
	public:
		class response;
		class request ;

	public:
		typedef endpoint::session::connection::sender   sender_type;
		typedef endpoint::session::connection::receiver receiver_type;

		typedef endpoint::session::secured_connection::sender   sec_sender_type;
		typedef endpoint::session::secured_connection::receiver sec_receiver_type;

		typedef std::pair<char*, std::size_t>			raw_type;

	private:
		message(char* __pa_raw, std::size_t __pa_size);
	public:
		message ();
		message (message&);
		message (message&&);

		~message();

	public:
		message& operator= (message&);
		message& operator= (message&&);

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

		friend sec_sender_type& operator << (sec_sender_type& __pa_snd, message& __pa_msg)
		{
			__pa_snd << raw_type(__pa_msg.raw_message, __pa_msg.raw_size);
			return __pa_snd;
		}

		friend sec_receiver_type& operator >> (sec_receiver_type& __pa_rcv, message& __pa_msg)
		{
			__pa_rcv >> raw_type(__pa_msg.raw_message, __pa_msg.raw_size);
			return __pa_rcv;
		}

	protected:
		char*		raw_message;
		std::size_t raw_size;
	};
}

http::message::message(char* __pa_raw, std::size_t __pa_size)
	: raw_message(__pa_raw), raw_size(__pa_size)
{
	HTTP_DEBUG_PRINT("[MESSAGE] Message Block Constructed (Internally) :: "s + std::to_string((uint64_t)raw_message));
}

http::message::message() : raw_size(HTTP_MESSAGE_MTU)
{
	HTTP_MESSAGE_ALLOCATE(raw_message);
	HTTP_DEBUG_PRINT	 ("[MESSAGE] Message Block Constructed :: "s + std::to_string((uint64_t)raw_message));
}

http::message::message(message& __pa_copy)
	: raw_message(__pa_copy.raw_message),
	  raw_size   (__pa_copy.raw_size)
{
	__pa_copy.raw_message = nullptr;
	__pa_copy.raw_size    = 0;
}

http::message::message(message&& __pa_move)
	: raw_message(__pa_move.raw_message),
	  raw_size   (__pa_move.raw_size)
{
	__pa_move.raw_message = nullptr;
	__pa_move.raw_size    = 0;
}

http::message::~message()
{
	HTTP_MESSAGE_DEALLOCATE(raw_message);
	HTTP_DEBUG_PRINT("[MESSAGE] Message Block Destructed :: "s + std::to_string((uint64_t)raw_message));
}

http::message& http::message::operator= (message& __pa_copy)
{
	raw_message = __pa_copy.raw_message;
	raw_size    = __pa_copy.raw_size;

	__pa_copy.raw_message = nullptr;
	__pa_copy.raw_size    = 0;

	return *this;
}

http::message& http::message::operator= (message&& __pa_move)
{
	raw_message = __pa_move.raw_message;
	raw_size    = __pa_move.raw_size;

	__pa_move.raw_message = nullptr;
	__pa_move.raw_size    = 0;

	return *this;
}