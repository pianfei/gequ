/*
 * jtype.h
 *
 *  Created on: Mar 17, 2025
 *      Author: Administrator
 */

#ifndef JTYPE_H_
#define JTYPE_H_

typedef unsigned char  u8;
typedef unsigned int   u32;
typedef unsigned short u16;

#define log_a(format,...) printf(format"\n",## __VA_ARGS__)
#define log_b(format,...) printf(format,## __VA_ARGS__)

typedef struct MemManager MemManager;
typedef struct AgiMember AgiMember;

#endif /* JTYPE_H_ */
