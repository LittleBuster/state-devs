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

#include "telegram.h"
#include <curl/curl.h>
#include <stdio.h>
#include <string.h>


bool telegram_send(const char *key, unsigned chat_id, const char *message)
{
	char num[50];
	char url[1024];
	CURL *curl_handle;

	sprintf(num, "%u", chat_id);

    strcpy(url, "https://api.telegram.org/bot");
    strcat(url, key);
    strcat(url, "/sendMessage?chat_id=");
    strcat(url, num);
    strcat(url, "&text=");
    strcat(url, message);
    
	curl_handle = curl_easy_init();
    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_perform(curl_handle);
        curl_easy_cleanup(curl_handle);
        return true;
	}
	return false;
}
