/*
 * File:   shared.h
 * Author: bn
 *
 * Created on 28 april 2014, 14:27
 */

#ifndef SHARED_H
#define	SHARED_H
#include "settings.h"
#include "FreeRTOS.h"
#include "timers.h"

#ifdef	__cplusplus
extern "C" {
#endif
extern Settings appSettings;
extern TimerHandle_t xTimers[5];
#ifdef	__cplusplus
}
#endif

#endif	/* SHARED_H */

