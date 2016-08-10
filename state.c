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
#include "devlist.h"
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
	struct dev_list *dlist;
	struct db_cfg *dbc = (struct db_cfg *)configs_get_db();

	if (!database_connect(&st_devs.db, dbc->ip, dbc->user, dbc->passwd, dbc->base)) {
		log_local("Can not connect to database.", LOG_ERROR);
		return;
	}
	dlist = database_get_devices(&st_devs.db);
	if (dlist == NULL) {
		log_local("Fail reading devices list from database.", LOG_ERROR);
		database_close(&st_devs.db);
		return;
	}
	/*
	 * Checking state of each device
	 */
	for (struct dev_list *l = dlist; l != NULL; l = dev_list_next(l)) {
		struct device *dev = dev_list_get_device(l);

		if (!tcp_client_connect(&st_devs.client, dev->ip, dev->port)) {
			// Send telegram message
			continue;
		}
		//Check status. If changed send telegram message
		tcp_client_close(&st_devs.client);
	}
	/*
	 * End.
	 */
	dev_list_free_all(dlist);
	database_close(&st_devs.db);
}


bool state_run(void)
{
	struct state_cfg *state = (struct state_cfg *)configs_get_state();

    for (;;) {
        struct timeval tv = {state->interval, 0};
        if (select(0, NULL, NULL, NULL, &tv) == -1)
            if (EINTR == errno)
                continue;
        state_handle();
    }
    return false;
}