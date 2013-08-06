#include "bloom.h"

Bloom* create_bloom(unsigned int length, unsigned int func_n, ...)
{
	Bloom* b = NULL;
	va_list l;
	unsigned int i = 0;

	// 申请内存
	if(!(b = (Bloom*)malloc(sizeof(Bloom))))
		return NULL;
	if(!(b->buffer = (char*)malloc(sizeof(char) * length)))
	{
		free(b);
		return NULL;
	}
	if(!(b->func_p = (hash_func_p*)malloc(sizeof(hash_func_p) * func_n)))
	{
		free(b->buffer);
		free(b);
		return NULL;
	}

	// 初始化缓冲区
	memset(b->buffer, 0, length * sizeof(char));
	
	// 初始化hash函数列表
	va_start(l, func_n);
	for(i = 0; i < func_n; ++i)
	{
		*(b->func_p + i) = va_arg(l, hash_func_p);
	}
	va_end(l);

	// 初始化常数变量
	b->length = length * sizeof(char);
	b->func_n = func_n;

	return b;
}

void destroy_bloom(Bloom *b)
{
	free(b->buffer);
	free(b->func_p);
	free(b);
	b = NULL;
}

void set_bit(char *buf, unsigned int n)
{
	buf[n >> 3] |= 1 << (n & 7);
}

int get_bit(char *buf, unsigned int n)
{
	return (buf[n >> 3] & (1 << (n & 7)));
}

void add_record(Bloom *b, const char* str)
{
	unsigned int i = 0;
	for(	; i < b->func_n; ++i)
	{
		set_bit(b->buffer, (*(b->func_p + i))(str) % b->length);
	}
}

int check_record(Bloom *b, const char* str)
{
	unsigned int i = 0;
	for(	; i < b->func_n; ++i)
		if(!get_bit(b->buffer, (*(b->func_p + i))(str) % b->length))
			return 0;
	return 1;
}
