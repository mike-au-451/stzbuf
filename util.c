#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "util.h"

// TODO
void *Calloc(int num, int size)
{
	void *any;

	assert(num > 0);
	assert(size > 0);

	any = calloc(num, size);
	return any;
}

// TODO
void Free(void *any)
{
	assert(any);
	free(any);
}

void Fatal(char *where, char *what)
{
	assert(where);
	assert(what);

	printf("FATAL: %s: %s\n", where, what);
	exit(1);
}

void Error(char *where, char *what)
{
	assert(where);
	assert(what);

	printf("ERROR: %s: %s\n", where, what);
}

