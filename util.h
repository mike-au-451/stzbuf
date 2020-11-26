#ifndef UTIL_H
#define UTIL_H

void *Calloc(int num, int size);
void Free(void *any);
void Fatal(char *where, char *what);
void Error(char *where, char *what);

#endif // UTIL_H

