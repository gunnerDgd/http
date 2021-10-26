#pragma once

#define HTTP_MESSAGE_MTU	   4096 * 3
#define HTTP_MESSAGE_PAGE_SIZE 4096

#define HTTP_MESSAGE_ALLOCATE(raw) raw = new char[HTTP_MESSAGE_MTU]
#define HTTP_MESSAGE_DEALLOCATE(raw) delete[] raw

#define HTTP_MESSAGE_BORDER_COLUMN "\r\n"
#define HTTP_MESSAGE_BORDER_DATA   "\r\n\r\n"

#define HTTP_EXCEPTION_THROW(cond, excp) if(cond) throw excp;
#define HTTP_EXCEPTION_TRY(expr, excp, hndl) try { expr; } catch(excp) { hndl; }