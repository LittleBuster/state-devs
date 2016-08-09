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

#ifndef __UTILS_H__
#define __UTILS_H__

#define TIME_SIZE 15
#define DATE_SIZE 15
#define DATETIME_SIZE 30


/*
 * Getting now time string
 */
void time_now(char *time);

/*
 * Getting now date string
 */
void date_now(char *date);

/*
 * Getting now date and time string
 */
void date_time_now(char *date_time);


#endif