#include <string.h>
#include <assert.h>

#include "utils.h"
#include "stzbuf.h"

Stz *Stz_new(void)
{
	return Calloc(1, sizeof(Stz));
}

void Stz_free(Stz *stz)
{
	assert(stz);
	Free(stz);
}

#define MINSTZBUFSIZE 100

void Stz_resize(Stz *stz, int newsize)
{
	assert(stz);

	char *newbuf;

	if (newsize < MINSTZBUFSIZE) {
		newsize = MINSTZBUFSIZE;
	}

	if ((newbuf = Calloc(newsize, sizeof(char))) == NULL) {
		fatal("Stz_resize", "no memory");
	}

	if (stz->size) {
		assert(stz->buf);
		memcpy(newbuf, stz->buf, stz->full * sizeof(char));
		Free(stz->buf);

		assert(stz->full < newsize);
		stz->buf[stz->full] = '\0';
	}

	stz->buf = newbuf;
	stz->size = newsize;
}

void Stz_add(Stz *stz, char ch)
{
	assert(stz);

	if (stz->full + 1 > stz->size) {
		Stz_resize(stz, stz->size * 3 / 2);
	}

	stz->buf[stz->full++] = ch;
	assert(stz->full < stz->size);
	stz->buf[stz->full] = '\0';
}

void Stz_cpy(Stz *stz, char *buf)
{
	assert(stz);
	assert(buf);

	int len;

	len = strlen(buf);

	if (len + 1 >= stz->size) {
		Stz_resize(stz, (len + 1) * 3 / 2);
	}

	strcpy(stz->buf, buf);
	stz->full = len;
}

void Stz_cat(Stz *stz, char *buf)
{
	assert(stz);
	assert(buf);

	int len;

	len = strlen(buf);

	if (stz->full + len + 1 >= stz->size) {
		Stz_resize(stz, (stz->full + len + 1) * 3 / 2);
	}

	// buffer is always terminated
	assert(stz->buf[stz->full] == '\0');
	strcat(stz->buf + stz->full, buf);
	stz->full += len;
	assert(stz->full + 1 < stz->size);
	stz->buf[stz->full] = '\0';
}
