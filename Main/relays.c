/**
 * @file relay.c
 * @brief Embedded resource management
 *
 * @section License
 *
 * Copyright (C) 2014 Velleman nv. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Velleman nv (www.velleman.eu)
 * @version 1.0.0
 **/
#include "relays.h"
#include "os_port.h"
#include "shared.h"
int getRelayValue(int i) {
    int status;

    switch (i) {
        case 1:
            status = READRY1;
            break;
        case 2:
            status = READRY2;
            break;
        case 3:
            status = READRY3;
            break;
        case 4:
            status = READRY4;
            break;
        default:
            status = FALSE;
            break;
    }
    return status;
}

void setRelayValue(int relay,int status)
{
    if(status != 0)
    {
        status = 1;
    }
    switch (relay) {
        case 1:
            RY1 = status;
            break;
        case 2:
            RY2 = status;
            break;
        case 3:
            RY3 = status;
            break;
        case 4:
            RY4 = status;
            break;
        default:
            break;
    }
    
}