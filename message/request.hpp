#pragma once
#include <cstdint>
#include <string_view>
#include <unordered_map>

#include <http/types/exception.hpp>
#include <http/types/define.hpp>

#include <http/message/message.hpp>

#include <string_tools/serialize/serialize.hpp>
#include <string_tools/extract/extract.hpp>
#include <string_tools/token/token.hpp>

namespace http {
	class message::request
	{
	public:
		class prefix;
		class header;

		static message::request from_message(message&);
		static message			to_message  (prefix&, header&);

	private:
		std::uint64_t __m_border_prefix,
					  __m_border_header;

		char*		  __m_message_raw;
		std::size_t	  __m_message_length;
	};

	class message::request::prefix
	{
	public:
		prefix(message::request&);
		prefix(std::string, std::string, std::string);

		friend class request;

		std::string method   () { return __m_method ; }
		std::string path     () { return __m_path   ; }
		std::string version  () { return __m_version; }
		std::string to_string() { return __m_method + " " + __m_path + " " + __m_version; }

	private:
		std::string __m_method, __m_path, __m_version;
	};

	class message::request::header
	{
	public:
		friend class request;
		class column
		{
		public:
			column() = default;
			column(std::string __pa_pref, std::string __pa_cont)
				: __m_prefix (__pa_pref),
				  __m_context(__pa_cont) { }
			 
			const std::string& prefix   () { return __m_prefix ; }
			const std::string& context  () { return __m_context; }
			std::string		   to_string() { return __m_prefix + ":" + __m_context; }

		private:
			std::string __m_prefix, __m_context;
		};
		
	public:
		static message::request::header parse_from(message::request&);
		column&							operator[](std::string);
		
		void append(column&);
		void append(std::string, std::string);

		void erase (std::string __pa_pref) { __m_column.erase(__pa_pref); }
		bool exist (std::string __pa_pref) { return (__m_column.find(__pa_pref) != __m_column.end()); }

	protected:
		std::unordered_map<std::string, column> __m_column;
	};
	
}


http::message http::message::request::to_message(prefix& __pa_pref, header& __pa_header)
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

http::message::request http::message::request::from_message(message& __pa_msg)
{
	http::message::request msg_res;
	std::string_view	   msg_raw_viewer(__pa_msg.raw_message);

	msg_res.__m_message_raw    = __pa_msg.raw_message;
	msg_res.__m_message_length = __pa_msg.raw_size;

	msg_res.__m_border_prefix  = msg_raw_viewer.find(HTTP_MESSAGE_BORDER_COLUMN, 0);
	msg_res.__m_border_header  = msg_raw_viewer.find(HTTP_MESSAGE_BORDER_DATA  , 0);
	
	return msg_res;
}

http::message::request::prefix::prefix(message::request& __pa_req)
{
	std::string_view	  pref_view(__pa_req.__m_message_raw, __pa_req.__m_border_prefix);
	string_tools::extract(pref_view, " ", __m_method, __m_path, __m_version);

	HTTP_EXCEPTION_THROW((__m_method.empty() || __m_path.empty() || __m_version.empty()),
						  http::exception::parse_exception("Parse Error while Parsing Prefix."));
}

http::message::request::prefix::prefix(std::string __pa_method, std::string __pa_path, std::string __pa_ver)
	: __m_method (std::move(__pa_method)),
	  __m_path   (std::move(__pa_path))  ,
	  __m_version(std::move(__pa_ver))   {  }

http::message::request::header http::message::request::header::parse_from(message::request& __pa_req)
{
	char*		parse_pointer = __pa_req.__m_message_raw   + __pa_req.__m_border_prefix + 2;
	std::size_t parse_size    = __pa_req.__m_border_header - __pa_req.__m_border_prefix;

	http::message::request::header parse_res;
	std::string_view			   parse_view(parse_pointer, parse_size);

	auto parsed_column = string_tools::tokenize(parse_view, HTTP_MESSAGE_BORDER_COLUMN);
	for (auto&& col    : parsed_column)
	{
		std::string   				    column_prefix, column_header;
		string_tools::extract(col, ":", column_prefix, column_header);
		
		parse_res.__m_column.insert	 ({ column_prefix, column(column_prefix, column_header) });
	}

	return parse_res;
}

http::message::request::header::column& http::message::request::header::operator[](std::string __pa_prefix)
{
	HTTP_EXCEPTION_THROW(!exist(__pa_prefix), http::exception::parse_exception("Cannot Find Header."));
	return				__m_column[__pa_prefix];
}

void http::message::request::header::append(column& __pa_col)
{
	__m_column.insert(std::pair<std::string, column>(__pa_col.prefix(), __pa_col));
}

void http::message::request::header::append(std::string __pa_prefix, std::string __pa_context)
{
	__m_column.insert({ __pa_prefix, column(__pa_prefix, __pa_context) });
}