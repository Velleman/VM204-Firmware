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
#include "inputs.h"
#include "IoDataTypes.h"
#include "shared.h"
int getInputStatus(int i) {
    int status;
    
    switch (i) {
        case 0:
            status = READIN1 ? TRUE : FALSE;
            break;
        case 1:
            status = READIN2 ? TRUE : FALSE;
            break;
        case 2:
            status = READIN3 ? TRUE : FALSE;
            break;
        case 3:
            status = READIN4 ? TRUE : FALSE;
            break;
        default:
            status = FALSE;
            break;
    }
    return status;
}

Input_t* getInputs()
{
    return appSettings.IoSettings.inputs;
}

