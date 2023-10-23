#include <errno.h>
#include "../types.h"
#include "../util.h"
#include "io.h"

#define IO_READ_CHUNK_SIZE  50000
#define IO_READ_ERROR_GENERAL "Failed to read file. %s. Errno:%d\n" 
#define IO_READ_ERROR_MEMORY "Not enough memory to read file. %s. Errno:%d\n"

File read_file(const char *path) // not eff
{
	File file = {0};
	file.isValid = false;
	FILE *fp = fopen(path,"rb");
	if(fp == NULL)
	{
		ERROR_RETURN(file,IO_READ_ERROR_GENERAL,path,errno);
	}
	char *data = NULL;
	char *tmp;
	size_t used = 0;
	size_t size = 0;
	size_t n;

	while(true)
	{
		if(size <= 0)
		{
			size = used + IO_READ_CHUNK_SIZE + 1;	
			tmp = (char *)realloc(data,size);
			if(!tmp)
			{
				free(data);
				ERROR_RETURN(file,IO_READ_ERROR_MEMORY,path);
			}
			data = tmp;
		}
		n = fread(data+used,1,IO_READ_CHUNK_SIZE,fp);
		if(n == 0)
			break;
		used += n;
	}

	if(ferror(fp))
	{
		free(data);
		ERROR_RETURN(file,IO_READ_ERROR_GENERAL,path);
	}
	fclose(fp);
	data[used] = 0; //null terminator
	file.data = data;
	file.len = used;
	file.isValid = true;
	return file;
}

int write_file(void *buffer, size_t size,const char *path) // implement later
{
	return 0;
}
