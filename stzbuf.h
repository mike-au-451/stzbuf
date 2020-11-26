#ifndef STZBUF_H
#define STZBUF_H

typedef struct {
	int size, full;
	char *buf;
} Stz;

Stz *Stz_new(void);
void Stz_free(Stz *stz);
void Stz_add(Stz *stz, char ch);
void Stz_cpy(Stz *stz, char *buf);
void Stz_cat(Stz *stz, char *buf);

#endif // STZBUF_H
