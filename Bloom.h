#ifndef __BLOOM__H__
#define __BLOOM__H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

typedef unsigned int (*hash_func_p)(const char*);	// hash 函数指针

typedef struct tagBloom
{
	unsigned int length;	// 缓冲区长度
	char* buffer;
	unsigned int func_n;	// hash函数个数
	hash_func_p* func_p;	// 函数指针数组
} Bloom;

extern Bloom * create_bloom(unsigned int, unsigned int, ...);
extern void destroy_bloom(Bloom *);
extern void add_record(Bloom *, const char *);
extern int check_record(Bloom *, const char *);

#endif
