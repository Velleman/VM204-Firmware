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
#include "FreeRTOS.h"
#include "timers.h"
#include "shared.h"
#include "relays.h"
void startPulse(int id,int periodInSeconds)
{
    TimerHandle_t timer = xTimers[id];
    if(xTimerIsTimerActive(timer))
    {

    }
    else
    {
        /* xTimer is not active, change its period to 500ms.  This will also
        cause the timer to start.  Block for a maximum of 100 ticks if the
        change period command cannot immediately be sent to the timer
        command queue. */
        if( xTimerChangePeriod( timer, (periodInSeconds*1000) / portTICK_PERIOD_MS, 50 ) == pdPASS )
        {
            /* Start the timer.  No block time is specified, and even if one was
             it would be ignored because the RTOS scheduler has not yet been
             started. */
             if( xTimerStart( timer, 0 ) != pdPASS )
             {
                 
             }
             else
             {
                 setRelayValue(id,TRUE);
             }
        }
        else
        {
            /* The command could not be sent, even after waiting for 100 ticks
            to pass.  Take appropriate action here. */
        }
    }
}
