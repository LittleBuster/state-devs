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

#ifndef __LOG_H__
#define __LOG_H__

#include <stdbool.h>
#include "devlist.h"

enum {
	LOG_ERROR,
	LOG_WARNING,
	LOG_INFO
};


/**
 * Setting path for main log file
 * @path: path with filename
 *
 * returns true: if setted
 * returns false: if path size to long
 */
bool log_set_path(const char *path);

/**
 * Setting path for state operations of device
 * 
 * returrns true: if setted
 * returns false: if path size to long
 */
bool log_set_state_path(const char *path);

/**
 * Writing message to local log file
 * @message: writing message
 * @log_type: type of log message
 */
void log_local(const char *message, unsigned log_type);

/**
 * Writting message to local sync log file
 * @dev: device structure pointer
 * @state: state of device
 */
void log_state(struct device *restrict dev, bool state);


#endif