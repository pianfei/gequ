/*
 * agi.c
 *
 *  Created on: Mar 17, 2025
 *      Author: Administrator
 */
#include "agi.h"
#include "link.h"

AgiMember *AgiOpen(int myId)
{
    AgiMember *pDemo = (AgiMember*)RawMalloc(sizeof(AgiMember));
    log_a("demo %d",myId);
    pDemo->bOpen = 1;
    pDemo->pMem = (MemManager*)RawMalloc(sizeof(MemManager));
    pDemo->pMem->pAgi = pDemo;
    return pDemo;
}


void DemoTask1(AgiMember *pDemo)
{
    log_a("open %d",pDemo->bOpen);
}
