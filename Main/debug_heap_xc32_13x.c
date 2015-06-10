/*-------------------------------------------------------------------------
 * !! UNSUPPORTED !! - debug_heap() function for MPLAB XC32 v1.3x
 *
 * Copyright (c) 2014, Microchip Technology Inc. and its subsidiaries ("Microchip")
 * All rights reserved.
 * 
 * This software is developed by Microchip Technology Inc. and its
 * subsidiaries ("Microchip").
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are 
 * met:
 * 
 * 1.      Redistributions of source code must retain the above copyright
 *         notice, this list of conditions and the following disclaimer.
 * 2.      Redistributions in binary form must reproduce the above 
 *         copyright notice, this list of conditions and the following 
 *         disclaimer in the documentation and/or other materials provided 
 *         with the distribution.
 * 3.      Microchip's name may not be used to endorse or promote products
 *         derived from this software without specific prior written 
 *         permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL MICROCHIP BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING BUT NOT LIMITED TO
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWSOEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */


#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

typedef void * VOIDPTR;
extern void * sbrk (int n);

struct store
{
 struct store * ptr;
 char flag;
};
extern struct store __allocs[2];
extern struct store * __allocp;
extern struct store * __alloct;
extern struct store __allocx;

extern unsigned char __attribute__((section("__linkerdefined"))) _heap;
extern unsigned char __attribute__((section("__linkerdefined"))) _min_heap_size;
void debug_heap()
{
        struct store *p, *q;
        int i, used = 0, free = 0;
        
        for(p = &__allocs[0] ; p && p!= __alloct ; p = q) {
                q = p->ptr;
                if(((int)p >= (int)&_heap) && (int)p <= (int)((char*)(&_heap)+(int)(&_min_heap_size))){
                        fprintf(stderr,"***   %4.4x %5d %s\n",(unsigned)p,((unsigned)q!=((unsigned)((char*)(&_heap)+(int)(&_min_heap_size))-4)) ?
                                        (i=(unsigned)q-(unsigned)p) :
                                        (i=(unsigned)q-(unsigned)p+4),
                                ((*p).flag & 1) ? "BUSY" : "FREE");

                        if(((*p).flag & 1))
                                used += i;
                        else
                                free += i;
                }
        }
        fprintf(stderr, "***   %d used, %d free, %4.4x end\n\n",
                used, free, (unsigned)__alloct);
}
