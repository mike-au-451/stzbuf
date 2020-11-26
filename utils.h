#ifndef UTILS_H
#define UTILS_H

void *Calloc(int num, int size);
void Free(void *any);

void error(char *where, char *what);
void fatal(char *where, char *what);

#endif // UTILS_H
