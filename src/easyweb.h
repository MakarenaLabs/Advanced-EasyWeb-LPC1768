#ifndef __EASYWEB_H
#define __EASYWEB_H

#include <stdio.h>
#include <string.h>

const unsigned char GetResponse[] =              // 1st thing our server sends to a client
{
  "HTTP/1.0 200 OK\r\n"                          // protocol ver 1.0, code 200, reason OK
  "Content-Type: text/html\r\n"                  // type of data we want to send
  "\r\n"                                         // indicate end of HTTP-header
};
void start(void);
void HTTPServer(void);

unsigned char *PWebSide;                         // pointer to webside
unsigned int HTTPBytesToSend;                    // bytes left to send

unsigned char HTTPStatus;                        // status byte 
#define HTTP_SEND_PAGE               0x01        // help flag

#endif

