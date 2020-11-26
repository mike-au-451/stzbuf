#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "utils.h"

void *Calloc(int num, int size)
{
	// TODO
	return calloc(num, size);
}

void Free(void *any)
{
	assert(any);
	free(any);
}

void error(char *where, char *what)
{
	assert(where);
	assert(what);
	printf("ERROR: %s: %s\n", where, what);
}

void fatal(char *where, char *what)
{
	assert(where);
	assert(what);
	printf("FATAL: %s: %s\n", where, what);
	exit(1);
}
