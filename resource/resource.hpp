#pragma once

#include <cstdint>
#include <cstddef>

#include <string>
#include <Windows.h>

#include <http/endpoint/session/connection/connection.hpp>
#include <http/endpoint/session/connection/secured_connection.hpp>

namespace http {
	class resource
	{
	private:
		typedef HANDLE										  handle_type  ;
		typedef http::endpoint::session::connection::receiver receiver_type;
		typedef http::endpoint::session::connection::sender   sender_type  ;

		typedef http::endpoint::session::secured_connection::sender   sec_sender_type;
		typedef http::endpoint::session::secured_connection::receiver sec_receiver_type;

		typedef std::pair<char*, std::size_t>				  raw_type     ;

	private:
		resource(handle_type, handle_type, char*);
		resource()						 = delete;
		 
	public:
		static resource from_file	  (handle_type);
		static resource from_file_name(std::string);

	public:
		friend sender_type& operator << (sender_type& __pa_snd, resource& __pa_res)
		{
			__pa_snd << raw_type(__pa_res.__m_res_iomap_pointer, __pa_res.__m_res_iomap_size);
			return __pa_snd;
		}

		friend sec_sender_type& operator << (sec_sender_type& __pa_snd, resource& __pa_res)
		{
			__pa_snd << raw_type(__pa_res.__m_res_iomap_pointer, __pa_res.__m_res_iomap_size);
			return __pa_snd;
		}

	private:
		handle_type __m_res_iomap_handle;
		handle_type __m_res_iomap_file;

		char*		__m_res_iomap_pointer;
		std::size_t __m_res_iomap_size;
	};
}

http::resource::resource(handle_type __pa_iomap, handle_type __pa_file, char* __pa_raw)
	:  __m_res_iomap_handle (__pa_iomap),
	   __m_res_iomap_file   (__pa_file) ,
	   __m_res_iomap_pointer(__pa_raw)  
{
	HTTP_EXCEPTION_THROW(__pa_iomap == NULL, http::exception::resource_exception("NULL IOMAP Input"));
	HTTP_EXCEPTION_THROW(__pa_file  == INVALID_HANDLE_VALUE, http::exception::resource_exception("Invalid IOMAP File."));

	DWORD iomap_size_high,
		  iomap_size_low = GetFileSize(__m_res_iomap_file, &iomap_size_high);

	__m_res_iomap_size = (iomap_size_high << 32) | iomap_size_low;
}

http::resource http::resource::from_file(handle_type __pa_handle)
{
	handle_type			 iomap_handle  = ::CreateFileMapping(__pa_handle, NULL, PAGE_READWRITE, 0, 0, NULL);
	HTTP_EXCEPTION_THROW(iomap_handle == NULL, http::exception::resource_exception("Failed to Open IOMAP Handle."));
	char*				 iomap_pointer = (char*)::MapViewOfFile	  (iomap_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	return http::resource(iomap_handle, __pa_handle, iomap_pointer);
}

http::resource http::resource::from_file_name(std::string __pa_name)
{
	handle_type			 iomap_file  = ::CreateFileA(__pa_name.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, 0, 0);
	HTTP_EXCEPTION_THROW(iomap_file == INVALID_HANDLE_VALUE, http::exception::resource_exception("Failed to Open File."));

	handle_type			 iomap_handle  = ::CreateFileMapping(iomap_file, NULL, PAGE_READWRITE, 0, 0, NULL);
	HTTP_EXCEPTION_THROW(iomap_handle == NULL, http::exception::resource_exception("Failed to Open IOMAP Handle."));

	char* iomap_pointer = (char*)::MapViewOfFile(iomap_handle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	return http::resource(iomap_handle, iomap_file, iomap_pointer);
}