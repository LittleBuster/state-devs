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

#include "database.h"


bool database_connect(struct database *db, const char *ip, const char *user, const char *passwd, const char *base)
{
	db->base = mysql_init(NULL);

    mysql_options(db->base, MYSQL_SET_CHARSET_NAME, "utf8");
    db->base = mysql_real_connect(db->base, ip, user, passwd, base, 3306, NULL, 0);
    if (db->base == NULL)
    	return false;
	return true;
}

struct dev_list *database_get_devices(struct database *db)
{
	return NULL;
}

bool database_update_device(struct database *db, struct device *upd_dev)
{
	return true;
}

void database_close(struct database *db)
{
	mysql_close(db->base);
}