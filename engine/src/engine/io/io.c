#include <errno.h>
#include "../types.h"
#include "../util.h"
#include "io.h"

#define IO_READ_CHUNK_SIZE 2097152
#define IO_READ_ERROR_GENERAL "Failed to read file. %s. Errno:%d\n" 
#define IO_READ_ERROR_MEMORY "Not enough memory to read file. %s. Errno:%d\n"

File read_file(const char *path)
{
	File file = {.isValid = false};
	FILE *fp = fopen(path,"rb");
	if(ferror(fp))
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
		if(used+IO_READ_CHUNK_SIZE+1 > size)
		{
			size = used + IO_READ_CHUNK_SIZE + 1;	
			if(size <= used)
			{
				free(data);
				ERROR_RETURN(file,"Input file too large. %s\n",path);
			}
			tmp = realloc(data,size);
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
	tmp = realloc(data,used+1);
	if(!tmp)
	{
		free(data);
		ERROR_RETURN(file,IO_READ_ERROR_MEMORY,path);
	}
	data = tmp;
	data[used] = 0;
	file.data = data;
	file.len = used;
	file.isValid = true;
	return file;
}

int write_file(void *buffer, size_t size,const char *path)
{
	int success = 0;
	return success;
}
