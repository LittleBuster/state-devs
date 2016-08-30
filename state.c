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

#define _GNU_SOURCE
#include "state.h"
#include "configs.h"
#include "devlist.h"
#include "telegram.h"
#include "database.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


static struct {
	struct database db;
} st_devs;


static int ping(char *ipaddr)
{
	char *command = NULL;
	FILE *fp;
	int stat = 0;
	if (!asprintf (&command, "%s %s -q 2>&1", "fping", ipaddr))
		return -1;
	fp = popen(command, "r");
	if (fp == NULL) {
		fprintf(stderr, "Failed to execute fping command\n");
		free(command);
		return -1;
	}
	stat = pclose(fp);
	free(command);
	return stat;
}

static void state_handle(void)
{
	struct dev_list *dlist;
	struct db_cfg *dbc = (struct db_cfg *)configs_get_db();
	struct tg_cfg *tg = (struct tg_cfg *)configs_get_tg();

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

		printf("Trying to connect to: %s ... ", dev->ip);
		if (!ping(dev->ip)) {
			puts("[FAIL]");
			if (dev->status != 0) {
				char dt[DATETIME_SIZE];
				char tg_msg[1024];

				date_time_now(dt);
				dev->status = 0;
				strncpy(dev->down_time, dt, DATETIME_SIZE);
				if (!database_update_device(&st_devs.db, dev))
					log_local("Can not update device.", LOG_ERROR);
				strcpy(tg_msg, "New%20Issue%0ADevice:%20");
				strcat(tg_msg, dev->name);
				strcat(tg_msg, "%0AIP:%20");
				strcat(tg_msg, dev->ip);
				strcat(tg_msg, "%0ADate:%20");
				strcat(tg_msg, dev->down_time);
				strcat(tg_msg, "%0AIssue:%20Device%20is%20DOWN.");
				telegram_send(tg->key, tg->id, tg_msg);
				log_state(dev, false);
			}
			continue;
		}
		puts("[OK]");
		if (dev->status != 1) {
			char tg_msg[1024];
			char dt[DATETIME_SIZE];

			date_time_now(dt);
			strncpy(dev->up_time, dt, DATETIME_SIZE);
			dev->status = 1;
			if (!database_update_device(&st_devs.db, dev))
				log_local("Can not update device.", LOG_ERROR);
			log_state(dev, true);
			
			strcpy(tg_msg, "New%20Issue%0ADevice:%20");
			strcat(tg_msg, dev->name);
			strcat(tg_msg, "%0AIP:%20");
			strcat(tg_msg, dev->ip);
			strcat(tg_msg, "%0ADate:%20");
			strcat(tg_msg, dev->up_time);
			strcat(tg_msg, "%0AIssue:%20Device%20is%20UP.");
			telegram_send(tg->key, tg->id, tg_msg);
			log_state(dev, false);	
		}
	}
	/*
	 * End.
	 */
	dev_list_free_all(dlist);
	database_close(&st_devs.db);
	puts("============================================================");
}


bool state_run(void)
{
	struct state_cfg *state = (struct state_cfg *)configs_get_state();

        state_handle();
    for (;;) {
        struct timeval tv = {state->interval, 0};
        if (select(0, NULL, NULL, NULL, &tv) == -1)
            if (EINTR == errno)
                continue;
        state_handle();
    }
    return false;
}
