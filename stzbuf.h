#ifndef STZBUF_H
#define STZBUF_H

typedef struct {
	int size, full;
	char *buf;
} Stzbuf;

#define MINSTZBUFSIZE 10

Stzbuf *Sb_New(void);
void Sb_Free(Stzbuf *sb);
void Sb_Grow(Stzbuf *sb);
void Sb_Resize(Stzbuf *sb, int newsize);
void Sb_Cat(Stzbuf *sb, Stzbuf *src);
void Sb_Cpy(Stzbuf *sb, Stzbuf *src);
void Sb_AddStz(Stzbuf *sb, char *src);
void Sb_AddCh(Stzbuf *sb, char ch);
char *Sb_Stz(Stzbuf *sb);

#endif // STZBUF_H

