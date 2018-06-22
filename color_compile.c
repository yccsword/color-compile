/*
 * color_compile.c - handle compile command
 *
 * Copyright (c) 2014-2015 Alan Wang <alan@wrcode.com>
 *
 * This file is released under the Apache Licene 2.0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int auto_cat(char ** target, int target_size, char * src, int src_len)
{
	  char * buf = NULL;
	  char * org = *target;
	  int buf_size = src_len + target_size;
		buf = realloc(org, buf_size + 1);
		if (buf != NULL)
		{
				org = buf;
				*target = org;
		}
		else
		{
				printf("buf malloc error!\n");
				return -1;	
		}
		memcpy(org + target_size, src, src_len);
		org[buf_size] = '\0';
		//printf("org:%s org_size:%d src:%s src_len:%d\n", org, target_size, src, src_len);
		return buf_size;
}


int main(int argc, char *argv[])
{
	int i;
	char * buf = NULL;
	int buf_size = 0;

	if (argc < 2 || 0 != strcmp(argv[0], "color_compile") )
	{
		fprintf(stderr, "[color_compile] bad argument...\n");
		return 1;
	}

	// declude make menuconfig
	if (3 == argc && 0 == strcmp(argv[1], "make") && 
	    0 == strcmp(argv[2], "menuconfig") )
	{
		system("make menuconfig");
		return 0;
	}
	// copy cmd
	//buf[0] = '\0';
	for (i = 1; i < argc; ++i)
	{
		buf_size = auto_cat(&buf, buf_size, argv[i], strlen(argv[i]));
		buf_size = auto_cat(&buf, buf_size, " ", strlen(" "));
	}

	// add out_color_info
	buf_size = auto_cat(&buf, buf_size, "2>&1 | out_color_info", strlen("2>&1 | out_color_info"));
	//printf("buf:%s\n", buf);
	// true exec
	return system(buf);
}

