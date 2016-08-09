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

#include "devlist.h"
#include <stdlib.h>


static struct dev_list *dev_list_last(struct dev_list *restrict list)
{
    if (list)
        while (list->next)
            list = list->next;
    return list;
}


struct dev_list *dev_list_append(struct dev_list *list, struct device *device)
{
    struct dev_list *new_list;
    struct dev_list *last;

    new_list = (struct dev_list *)malloc(sizeof(new_list));
    new_list->device = device;
    new_list->next = NULL;

    if (list) {
        last = dev_list_last(list);
        last->next = new_list;
        return list;
    }
    return new_list;
}

struct device *dev_list_get_device(struct dev_list *list)
{
    return list->device;
}

struct dev_list *dev_list_next(struct dev_list *list)
{
    return list->next;
}

void dev_list_free_all(struct dev_list *list)
{
    struct dev_list *tmp;

    if (!list)
        return;

    while (list) {
        tmp = list;
        list = list->next;
        free(tmp);
    }
}