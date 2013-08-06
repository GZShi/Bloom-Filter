#include "hash.h"

unsigned int bkdr_hash(char *str)
{
  unsigned int seed = 13131;
	unsigned int hash = 0;
	while(*str)
		hash = hash * seed + (*str++);
	return (hash & 0x7fffffff);
}

unsigned int ap_hash(char *str)
{
	unsigned int hash = 0;
	int i = 0;
	while(*str)
	{
		if((i & 1) == 0)
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		else
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		++i;
	}
	return (hash & 0x7fffffff);
}

unsigned int djb_hash(char *str)
{
	unsigned int hash = 5381;
	while(*str)
		hash += (hash << 5) + (*str++);
	return (hash & 0x7fffffff);
}
