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

#include <stdio.h>
#include <string.h>
#include "log.h"
#include "configs.h"
#include "state.h"


int main(void)
{
	if (!log_set_path("/var/log/sdevs.log")) {
		puts("Log path is to long!");
		return -1;
	}
	if (!log_set_state_path("/var/log/state.log")) {
		log_local("Log state path is to long!", LOG_ERROR);
		return -1;
	}
	if (configs_load("/etc/sdevs.conf") != CFG_OK) {
		log_local("Fail loading configs.", LOG_ERROR);
		return -1;	
	}
	if (!state_run()) {
		log_local("Fail starting state checker.", LOG_ERROR);
		return -1;
	}
	return 0;
}
