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


void* Malloc2(MemManager* pMem,u32 size);
void Free2(MemManager* pMem,void *p);

void* Realloc2(MemManager* pMem,void *p,u32 size,u32 old_size);
void* RawMalloc(u32 size);
void RawFree(void *p);
void* MallocX(MemManager* pMem,u32 size);

void* Malloc1(MemManager* pMem,u32 size);
void Free1(MemManager* pMem,void *p);

#endif /* LINK_H_ */
