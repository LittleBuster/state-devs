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
#include <string.h>


bool database_connect(struct database *restrict db, const char *ip, const char *user, const char *passwd, const char *base)
{
	db->base = mysql_init(NULL);

    mysql_options(db->base, MYSQL_SET_CHARSET_NAME, "utf8");
    db->base = mysql_real_connect(db->base, ip, user, passwd, base, 3306, NULL, 0);
    if (db->base == NULL)
    	return false;
	return true;
}

struct dev_list *database_get_devices(struct database *restrict db)
{
    int ret_val;
    size_t count;
    MYSQL_RES *result;
    MYSQL_ROW row;
    struct dev_list *dlist = NULL;

    ret_val = mysql_query(db->base, "SELECT * FROM devices");
    if (ret_val != 0)
        return NULL;

    result = mysql_store_result(db->base);
    count = mysql_num_rows(result);
    if (count == 0) {
        mysql_free_result(result);
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        struct device *dev = (struct device *)malloc(sizeof(struct device));

        row = mysql_fetch_row(result);
        strncpy(dev->ip, row[1], 15);
        strncpy(dev->name, row[2], 254);
        strncpy(dev->type, row[3], 254);
	sscanf(row[4], "%u", &dev->port);
	strncpy(dev->down_time, row[5], DATETIME_SIZE);
	strncpy(dev->up_time, row[6], DATETIME_SIZE);
	sscanf(row[7], "%u", &dev->status);

        dlist = dev_list_append(dlist, dev);
    }
    mysql_free_result(result);
    return dlist;
}

bool database_update_device(struct database *restrict db, struct device *restrict upd_dev)
{
    int ret_val;
    char sql[255];
char num[255];

    strcpy(sql, "UPDATE devices SET status=");
    sprintf(num, "%u", upd_dev->status);
    strcat(sql, num);
    strcat(sql, ", down=\"");
    strcat(sql, upd_dev->down_time);
    strcat(sql, "\", up=\"");
    strcat(sql, upd_dev->up_time);
    strcat(sql, "\" WHERE ip=\"");
    strcat(sql, upd_dev->ip);
    strcat(sql, "\"");

    ret_val = mysql_query(db->base, sql);
    if (ret_val != 0)
        return false;
	return true;
}

void database_close(struct database *restrict db)
{
	mysql_close(db->base);
}
