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

#ifndef __TELEGRAM_H__
#define __TELEGRAM_H__

#include <stdbool.h>


/**
 * Sending telegram mesage for bot
 * @key: telegram bot key
 * @chat_id: telegram chat id
 * @message: sending message
 *
 * returns false: if fail sending message
 * returns true: if sending ok
 */
bool telegram_send(const char *key, unsigned chat_id, const char *message);


#endif