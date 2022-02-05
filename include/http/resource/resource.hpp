#pragma once

#include <cstdint>
#include <cstddef>

#include <string>
#include <Windows.h>

#include <http/types/exception.hpp>
#include <http/types/define.hpp>

namespace http {
	class resource
	{
		typedef HANDLE handle_type;
	public:
		char*		get_resource() { return __m_res_iomap_pointer; }
		std::size_t get_size    () { return __m_res_iomap_size   ; }

	private:
		resource(handle_type, handle_type, char*);
	public:
		resource() = delete;

		static resource from_file	  (handle_type);
		static resource from_file_name(std::string);

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