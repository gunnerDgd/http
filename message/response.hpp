#pragma once
#include <cstdint>
#include <string_view>
#include <unordered_map>

#include <http/types/exception.hpp>
#include <http/message/message.hpp>
#include <http/types/define.hpp>

#include <string_tools/serialize/serialize.hpp>
#include <string_tools/extract/extract.hpp>
#include <string_tools/token/token.hpp>

namespace http {
	class message::response
	{
	public:
		class prefix;
		class header;

		static message::response from_message(message&);
		static message			 to_message  (prefix&, header&);

	private:
		std::uint64_t __m_border_prefix,
					  __m_border_header;

		char*		  __m_message_raw;
		std::size_t	  __m_message_length;
	};

	class message::response::prefix
	{
	public:
		friend class response;
		
		prefix(message::response&);
		prefix(std::string, uint16_t, std::string);

		std::string message   () { return __m_message; }
		uint16_t	reply_code() { return __m_rcode	 ; }
		std::string version   () { return __m_version; }
		std::string to_string () { return __m_version + std::to_string(__m_rcode) + __m_message; }

	private:
		std::string __m_version, __m_message;
		uint16_t    __m_rcode;
	};

	class message::response::header
	{
	public:
		friend class response;
		class column
		{
		public:
			column() = default;
			column(std::string __pa_pref, std::string __pa_cont)
				: __m_prefix  (__pa_pref),
				  __m_context (__pa_cont) { }

			const std::string& prefix   () { return __m_prefix ; }
			const std::string& context  () { return __m_context; }
			std::string		   to_string() { return __m_prefix + ":" + __m_context; }

		private:
			std::string __m_prefix, __m_context;
		};
		
	public:
		static message::response::header parse_from(message::response&);

		column& operator[](std::string);

		void append(column&);
		void append(std::string, std::string);

		void erase (std::string __pa_pref);
		bool exist (std::string __pa_pref);

	protected:
		std::unordered_map<std::string, column> __m_column;
	};
}

http::message::response::prefix::prefix(std::string __pa_ver, uint16_t __pa_rcode, std::string __pa_msg)
	: __m_version(std::move(__pa_ver)),
	  __m_rcode  (__pa_rcode)		  ,
	  __m_message(std::move(__pa_msg)) {  }

http::message::response http::message::response::from_message(message& __pa_msg)
{
	http::message::response msg_res;
	std::string_view	    msg_raw_viewer(__pa_msg.raw_message);

	msg_res.__m_message_raw	   = __pa_msg.raw_message;
	msg_res.__m_message_length = __pa_msg.raw_size;

	msg_res.__m_border_prefix  = msg_raw_viewer.find(HTTP_MESSAGE_BORDER_COLUMN, 0);
	msg_res.__m_border_header  = msg_raw_viewer.find(HTTP_MESSAGE_BORDER_DATA  , 0);

	return msg_res;
}

http::message http::message::response::to_message(prefix& __pa_pref, header& __pa_header)
{
	HTTP_MESSAGE_ALLOCATE(char* res_message_raw);

	std::string&& res_pref = __pa_pref.to_string() + "\r\n";
	std::string   res_header;

	for (auto&& [key, col] : __pa_header.__m_column)
		res_header += col.to_string() + "\r\n";
		res_header += "\r\n";

	string_tools::serialize(res_message_raw, res_pref, res_header);
	return    http::message(res_message_raw, res_pref.length() + res_header.length());
}

http::message::response::prefix::prefix(message::response& __pa_req)
{
	std::string_view	  pref_view(__pa_req.__m_message_raw, __pa_req.__m_border_prefix);
	string_tools::extract(pref_view, " ", __m_version, __m_rcode, __m_message);

	HTTP_EXCEPTION_THROW((__m_version.empty() || __m_message.empty()),
						  http::exception::parse_exception("Parse Error while Parsing Prefix."));
}

http::message::response::header http::message::response::header::parse_from(message::response& __pa_req)
{
	char*	    parse_pointer = __pa_req.__m_message_raw   + __pa_req.__m_border_prefix + 2;
	std::size_t parse_size    = __pa_req.__m_border_header - __pa_req.__m_border_prefix;

	http::message::response::header parse_res;
	std::string_view			    parse_view(parse_pointer, parse_size);

	auto parsed_column = string_tools::tokenize(parse_view, HTTP_MESSAGE_BORDER_COLUMN);
	for (auto&& col    : parsed_column)
	{
		std::string						column_prefix, column_header;
		string_tools::extract(col, ":", column_prefix, column_header);

		parse_res.__m_column.insert  ({ column_prefix, column(column_prefix, column_header) });
	}

	return parse_res;
}

http::message::response::header::column& http::message::response::header::operator[](std::string __pa_prefix)
{
	HTTP_EXCEPTION_THROW(!exist(__pa_prefix), http::exception::parse_exception("Cannot Find Header."));
	return				__m_column[__pa_prefix];
}

void http::message::response::header::append(column& __pa_col)
{
	__m_column.insert(std::pair<std::string, column>(__pa_col.prefix(),  __pa_col));
}

void http::message::response::header::append(std::string __pa_prefix, std::string __pa_context)
{
	__m_column.insert({ __pa_prefix, column(__pa_prefix, __pa_context) });
}

void http::message::response::header::erase(std::string __pa_pref) { __m_column.erase(__pa_pref); }
bool http::message::response::header::exist(std::string __pa_pref) { return (__m_column.find(__pa_pref) != __m_column.end()); }