#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct file
{
	char *data;
	size_t len;
	bool isValid;
}File;

File read_file(const char *path);
int write_file(void *buffer, size_t size,const char *path);
