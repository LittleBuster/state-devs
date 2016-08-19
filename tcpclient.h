/* State devs project
 *
 * Copyright (C) 2016 Sergey Denisov.
 * Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
 *
 * This application is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public Licence
 * as published by the Free Software Foundation; either version 3
 * of the Licence, or (at your option) any later version.
 */

#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define INVALID_SOCKET (SOCKET)(~0)
#define SOCKET_ERROR (-1)
#define SOCKET int


struct tcp_client {
    /* Socket id */
    SOCKET s;
};


/**
 * Connect to other socket
 * @sock: socket struct
 * @ip: ip address of other socket
 * @port: tcp port of other socket
 *
 * Returns true if succeful connection
 * Returns false if fail connection
 */
bool tcp_client_connect(struct tcp_client *restrict sock, const char *ip, const unsigned port);

/*
 * Close connection
 */
void tcp_client_close(struct tcp_client *restrict sock);


#endif
