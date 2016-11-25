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

#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <mysql/mysql.h>
#include <stdbool.h>
#include "devlist.h"


struct database {
	MYSQL *base;
};


/**
 * Connecting to database
 * @db: database struct pointer
 * @ip: ip address of database
 * @user: database username
 * @passwd: password of user
 * @base: database name
 *
 * returns false: if fail connection
 * returns true: if connection ok
 */
bool database_connect(struct database *restrict db, const char *ip, const char *user, const char *passwd, const char *base);

/**
 * Getting devices list from base
 * @db: database struct pointer
 *
 * returns devices list
 * returns NULL: if error reading base
 */
struct dev_list *database_get_devices(struct database *restrict db);

/**
 * Update device info in base
 * @db: database structure pointer
 * @upd_dev: updated device
 *
 * returns false: if fail updating
 * returns true: if ok
 */
bool database_update_device(struct database *restrict db, struct device *restrict upd_dev);

bool database_add_device_info(struct database *restrict db, struct device *restrict dev, const char *time);

/*
 * Closing connection
 */
void database_close(struct database *restrict db);


#endif
