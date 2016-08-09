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

#ifndef __DEVICE_LIST_H__
#define __DEVICE_LIST_H__

#include <stdio.h>
#include <stdbool.h>
#include "utils.h"


struct device {
	char ip[16];					/* IP of device */
	char name[255];					/* Name of device */
	char type[255];					/* Type of device: office, production, etc. */
	unsigned port;					/* TCP port of device */
	char down_time[DATETIME_SIZE];	/* Last down time of device */
	char up_time[DATETIME_SIZE];	/* Last up time of device */
	bool status;					/* Device life status */
	bool alarm;						/* Send alarm status */
};


struct dev_list {
    struct device *device;		/* device */
    struct dev_list *next; 	/* next device */
};

/**
 * Add new device in list
 * @list: devices list struct
 * @dev: user's data
 *
 * returns device list with added device
 */
struct dev_list *dev_list_append(struct dev_list *dlist, struct device *dev);

/*
 * Next device of list
 */
struct dev_list *dev_list_next(struct dev_list *dlist);

/*
 * Getting current device
 */
struct device *dev_list_get_device(struct dev_list *dlist);

/*
 * Free list of devices
 */
void dev_list_free_all(struct dev_list *dlist);


#endif