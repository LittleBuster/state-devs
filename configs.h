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

#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include <stdbool.h>
#include <stdint.h>


enum error_codes {
    CFG_FILE_NOT_FOUND,
    CFG_STATE_INTERVAL_ERR,
    CFG_DB_IP_ERR,
    CFG_DB_USER_ERR,
    CFG_DB_PASSWD_ERR,
    CFG_DB_BASE_ERR,
    CFG_TG_ID_ERR,
    CFG_TG_KEY_ERR,
    CFG_OK
};

/**
 * Loading configs from file to RAM
 * @filename: name of configs file
 *
 * returns error codes: if fail loading
 * returns CFG_OK: if succefful loading
 */
uint8_t configs_load(const char *filename);


struct state_cfg {
	unsigned interval;	
};

/*
 * State timer configs
 */
struct state_cfg *configs_get_state(void);


struct db_cfg {
	char ip[16];
    char user[255];
    char passwd[255];
    char base[255];
};

/*
 * Database configs
 */
struct db_cfg *configs_get_db(void);

struct tg_cfg {
	unsigned id;
	char key[255];
};

/*
 * Telegram configs
*/
struct tg_cfg *configs_get_tg(void);


#endif
