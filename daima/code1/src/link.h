/*
 * link.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Administrator
 */

#ifndef LINK_H_
#define LINK_H_
#include "jtype.h"

struct MemManager
{
    AgiMember *pAgi;
};


void* Malloc2(AgiMember *pDemo,u32 size);
void Free2(AgiMember *pDemo,void *p);

void* Realloc2(AgiMember *pDemo,void *p,u32 size,u32 old_size);
void* RawMalloc(u32 size);
void RawFree(void *p);
void* MallocX(AgiMember *pDemo,u32 size);

void* Malloc1(AgiMember *pDemo,u32 size);
void Free1(AgiMember *pDemo,void *p);

#endif /* LINK_H_ */
