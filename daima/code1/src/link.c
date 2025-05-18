/*
 * link.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Administrator
 */
#include "agi.h"
#include "link.h"

//这个有问题的，传入的应该是pAgi，因为这个函数是给外面用的，而不是内部的独立模块
void* Malloc2(MemManager* pMem,u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;
}

void Free2(MemManager* pMem,void *p){
    free(p);
}

void* Realloc2(MemManager* pMem,void *p,u32 size,u32 old_size)
{
    void *pPre;
    pPre = p;
    p = Malloc2(pMem,size);
    memcpy(p,pPre,old_size);
    memset(pPre,0,old_size);
    Free2(pMem,pPre);
   // p = realloc(p,size);
    return p;
}

//不确定是固定还是动态分配
void* MallocX(MemManager* pMem,u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;
}

void* RawMalloc(u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;
}

void RawFree(void *p)
{
    free(p);
}

void* Malloc1(MemManager* pMem,u32 size)
{
    void *p = malloc(size);
    memset(p,0,size);
    return p;

}

void Free1(MemManager* pMem,void *p){
    free(p);
}

