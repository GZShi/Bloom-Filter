#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "bloom.h"

int main(int argc, char** argv)
{
  char* src_path = NULL;
	FILE *fp1 = NULL;
	Bloom *b1 = NULL;
	char line[1024];
	int count = 0;

	if(argc == 2)
	{
		src_path = argv[1];
	}
	else
	{
		puts("input the source file\'s' path:");
		fflush(stdin);
		gets(src_path);
	}

	if(!(fp1 = fopen(src_path, "r")))
	{
		printf("err: can\'t open %s.\n", src_path);
		return 1;
	}

	// 100*1024*1024 byte
	b1 = create_bloom(100*1024*1024, 3, bkdr_hash, ap_hash, djb_hash);
	if(!(b1))
		return 1;

	while(fgets(line, 1024, fp1))
	{
		line[strlen(line) - 1] = '\0';
		add_record(b1, line);
		count++;
		// if(count > 1000)
		// 	break;
	}

	fclose(fp1);

	printf("log: added %d records\n", count);

	while(1)
	{
		fflush(stdin);
		puts("input a string:");
		gets(line);
		if(check_record(b1, line))
		{
			printf("--matched!\n");
		}
		else
		{
			printf("--didnt match!\n");
		}
		if(0 == strcmp("q", line))
			break;
	}
	destroy_bloom(b1);

	return 0;
}
