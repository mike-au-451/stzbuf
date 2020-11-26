#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "stzbuf.h"
#include "util.h"

Stzbuf *Sb_New(void)
{
	// TODO
	Stzbuf *sb = Calloc(1, sizeof(Stzbuf));

	return sb;
}

void Sb_Free(Stzbuf *sb)
{
	// TODO
	assert(sb);

	if (sb->buf) {
		assert(sb->size > 0);
		Free(sb->buf);
	}

	Free(sb);
}

void Sb_Grow(Stzbuf *sb)
{
	assert(sb);
	Sb_Resize(sb, sb->size * 3 / 2);
}

void Sb_Resize(Stzbuf *sb, int newsize)
{
	char *newbuf;

	assert(sb);
	assert(newsize >= 0);

	if (newsize < MINSTZBUFSIZE) {
		newsize = MINSTZBUFSIZE;
	}

	if ((newbuf = Calloc(newsize, sizeof(char))) == NULL) {
		Fatal("Sb_Resize", "no memory");
	}

	if (sb->buf) {
		assert(sb->size > 0);
		memcpy(newbuf, sb->buf, sb->full * sizeof(char));
		Free(sb->buf);
	}

	sb->buf = newbuf;
	sb->size = newsize;
}

void Sb_Cat(Stzbuf *sb, Stzbuf *src)
{
	assert(sb);
	assert(src);

	if (sb->full + src->full >= sb->size) {
		Sb_Resize(sb, (sb->full + src->full) * 3 / 2);
	}

	memcpy(sb->buf + sb->full, src->buf, src->full * sizeof(char));
	sb->full += src->full;
}

void Sb_Cpy(Stzbuf *sb, Stzbuf *src)
{
	assert(sb);
	assert(src);

	if (src->full >= sb->size) {
		Sb_Resize(sb, src->full * 3 / 2);
	}

	memcpy(sb->buf, src->buf, src->full * sizeof(char));
	sb->full = src->full;
}

void Sb_AddStz(Stzbuf *sb, char *src)
{
	int len;

	assert(sb);
	assert(src);

	len = strlen(src);

	if (sb->full + len >= sb->size) {
        Sb_Resize(sb, (sb->full + len) * 3 / 2);
    }

    memcpy(sb->buf + sb->full, src, len * sizeof(char));
    sb->full += len;
}

/*
TODO:
1.  Consider whether adding \0 should be treated specially.
    If the buffer is binary adding \0 should increase the length,
    if the buffer is a terminated string, adding \0 should not increase the length.
*/
void Sb_AddCh(Stzbuf *sb, char ch)
{
	assert(sb);

	if (sb->full >= sb->size) {
		Sb_Resize(sb, sb->size * 3 / 2);
	}

	assert(sb->full < sb->size);
	sb->buf[sb->full++] = ch;
}

/*
Return a terminated string, not just the buffer.
*/
char *Sb_Stz(Stzbuf *sb)
{
	assert(sb);

	if (sb->full >= sb->size) {
		Sb_Resize(sb, sb->size * 3 / 2);
	}

	assert(sb->full < sb->size);
	sb->buf[sb->full] = '\0';

	return sb->buf;
}



