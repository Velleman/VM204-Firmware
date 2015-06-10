/**
 * @file os_port.h
 * @brief RTOS abstraction layer
 *
 * @section License
 *
 * Copyright (C) 2010-2015 Oryx Embedded SARL. All rights reserved.
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
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.6.0
 **/

#ifndef _OS_PORT_H
#define _OS_PORT_H

//Dependencies
#include "os_port_config.h"
#include "compiler_port.h"

//Compilation flags used to enable/disable features
#define ENABLED  1
#define DISABLED 0

//Deprecated API support
#ifndef OS_DEPRECATED_API_SUPPORT
   #define OS_DEPRECATED_API_SUPPORT DISABLED
#elif (OS_DEPRECATED_API_SUPPORT != ENABLED && OS_DEPRECATED_API_SUPPORT != DISABLED)
   #error OS_DEPRECATED_API_SUPPORT parameter is not valid
#endif

#define PTR_OFFSET(addr, offset) ((void *) ((uint8_t *) (addr) + (offset)))

#define timeCompare(t1, t2) ((int32_t) ((t1) - (t2)))

//Miscellaneous macros
#ifndef FALSE
   #define FALSE 0
#endif

#ifndef TRUE
   #define TRUE 1
#endif

#ifndef LSB
   #define LSB(x) ((x) & 0xFF)
#endif

#ifndef MSB
   #define MSB(x) (((x) >> 8) & 0xFF)
#endif

#ifndef MIN
   #define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
   #define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef arraysize
   #define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif

//Inifinite delay
#define INFINITE_DELAY ((uint_t) -1)

//Invalid handle value
#define OS_INVALID_HANDLE NULL

//ChibiOS/RT port?
#if defined(USE_CHIBIOS)
   #include "os_port_chibios.h"
//CMSIS-RTOS port?
#elif defined(USE_CMSIS_RTOS)
   #include "os_port_cmsis_rtos.h"
//FreeRTOS port?
#elif defined(USE_FREERTOS)
   #include "os_port_freertos.h"
//Keil RTX port?
#elif defined(USE_RTX)
   #include "os_port_rtx.h"
//Micrium uC/OS-II port?
#elif defined(USE_UCOS2)
   #include "os_port_ucos2.h"
//Micrium uC/OS-III port?
#elif defined(USE_UCOS3)
   #include "os_port_ucos3.h"
//Windows port?
#elif defined(_WIN32)
   #include "os_port_windows.h"
//No RTOS defined?
#else
   #include "os_port_none.h"
#endif

//Delay routines
#define usleep(delay) {volatile uint32_t n = delay * 4; while(n > 0) n--;}
#define sleep(delay) {volatile uint32_t n = delay * 4000; while(n > 0) n--;}

//Deprecated API (conflicts with CMSIS-RTOS API)
#if (OS_DEPRECATED_API_SUPPORT == ENABLED)
   #define osTaskCreate osCreateTask
   #define osTaskCreateStatic osCreateStaticTask
   #define osTaskDelete osDeleteTask
   #define osTaskSuspendAll osSuspendAllTasks
   #define osTaskResumeAll osResumeAllTasks
   #define osTaskSwitch osSwitchTask
   #define osTaskSwitchFromIrq osSwitchTaskFromIsr

   #define osEventCreate osCreateEvent
   #define osEventClose osDeleteEvent
   #define osEventSet osSetEvent
   #define osEventReset osResetEvent
   #define osEventWait osWaitForEvent
   #define osEventSetFromIrq osSetEventFromIsr

   #define osSemaphoreCreate osCreateSemaphore
   #define osSemaphoreClose osCloseSemaphore
   #define osSemaphoreWait osWaitForSemaphore
   #define osSemaphoreRelease osReleaseSemaphore

   #define osMutexCreate osCreateMutex
   #define osMutexClose osDeleteMutex
   #define osMutexAcquire osAcquireMutex
   #define osMutexRelease osReleaseMutex

   #define osDelay osDelayTask
   #define osGetTickCount osGetSystemTime

   #define osMemAlloc osAllocMem
   #define osMemFree osFreeMem
#endif

#endif
