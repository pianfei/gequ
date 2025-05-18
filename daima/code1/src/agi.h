/*
 * agi.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Administrator
 */

#ifndef AGI_H_
#define AGI_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <pthread.h>
#include "jtype.h"
#include <assert.h>
#include <mqueue.h>

typedef struct AgiMember AgiMember;
struct AgiMember
{
    MemManager *pMem;
    u8 bOpen;
};

AgiMember *AgiOpen(int myId);
void DemoTask1(AgiMember *pDemo);

#endif /* AGI_H_ */
