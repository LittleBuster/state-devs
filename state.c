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

#include "state.h"
#include "configs.h"
#include "tcpclient.h"
#include "database.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>


static struct {
	struct tcp_client client;
	struct database db;
} st_devs;


static void state_handle(void)
{

}


bool state_run(void)
{
	struct state_cfg *state = configs_get_state();

    for (;;) {
        struct timeval tv = {state->interval, 0};
        if (select(0, NULL, NULL, NULL, &tv) == -1)
            if (EINTR == errno)
                continue;
        state_handle();
    }
    return false;
}