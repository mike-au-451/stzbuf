
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#include "stzbuf.h"
#include "util.h"

int t00(void)
{
	return 0;
}

int t01(void)
{
	Stzbuf *sb;

	sb = Sb_New();
	if (sb->size != 0 || sb->full != 0 || sb->buf != NULL) {
		return 1;
	}

	Sb_Free(sb);

	return 0;
}

int t02(void)
{
	Stzbuf *sb;

	sb = Sb_New();

	Sb_Grow(sb);

	if (sb->size != MINSTZBUFSIZE) {
		return 1;
	}

	if (sb->full != 0) {
		return 2;
	}

	if (sb->buf == NULL) {
		return 3;
	}

	Sb_Free(sb);

	return 0;
}

int t03(void)
{
	Stzbuf *sb;
	char *stz;
	int len;

	sb = Sb_New();
	stz = "1234567890";
	len = strlen(stz);

	Sb_AddStz(sb, stz);
	if (sb->size != len * 3 / 2 || sb->full != 10 || sb->buf == NULL) {
		return 1;
	}

	// buf is not terminated
	for (int ii = 0; ii < len; ii++) {
		if (sb->buf[ii] != stz[ii]) {
			return 2;
		}
	}

	Sb_Free(sb);

	return 0;
}

int t04(void)
{
	Stzbuf *sb;
	char *stz;
	int len;

	sb = Sb_New();
	stz = "1234567890";
	len = strlen(stz);

	Sb_Resize(sb, len);

	if (sb->size != len || sb->full != 0 || sb->buf == NULL) {
		return 1;
	}

	// Do not add the \0
	for (int ii = 0; stz[ii]; ii++) {
		Sb_AddCh(sb, stz[ii]);
	}

	if (sb->full != len) {
		return 2;
	}

	Sb_Stz(sb);
	if (sb->size != len * 3 / 2 || sb->full != len || sb->buf[len] != '\0') {
		return 3;
	}

	Sb_Free(sb);

	return 0;
}

int main(int argc, char **argv)
{
	int (*tests[])(void) = {
		t00,
		t01,
		t02,
		t03,
		t04,
		NULL
	};
	int ii, rc;

	for (ii = 0; tests[ii]; ii++) {
		if ((rc = tests[ii]()) != 0) {
			printf("failed at %d, %d\n", ii, rc);
			break;
		}
	}

	return 0;
}

