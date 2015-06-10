/* 
 * File:   main.h
 * Author: bn
 *
 * Created on 24 maart 2015, 15:14
 */

#ifndef MAIN_H
#define	MAIN_H


#ifdef	__cplusplus
extern "C" {
#endif


void updateTask(void *parameters);
void updateTask(void *parameters);
void blinkTask(void *parameters);
void notificationTask(void *parameters);
void ioInit(void);
char* createJSONData();
const char* bool2str(int value);
#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

