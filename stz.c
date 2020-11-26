#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "utils.h"

int trimright(char *buf, int len, char *brs)
{
	assert(buf);
	assert(len >= 0);
	assert(brs);

	int ii, jj;

	for (ii = len - 1; ii >= 0; ii--) {
		for (jj = 0; brs[jj]; jj++) {
			if (buf[ii] == brs[jj]) {
				break;
			}
		}

		if (brs[jj] == '\0') {
			break;
		}
	}

	assert(ii + 1 <= len);
	buf[ii + 1] = '\0';

	return ii + 1;
}

int trimleft(char *buf, int len, char *brs)
{
	assert(buf);
	assert(len >= 0);
	assert(brs);

	int ii, jj;

	for (ii = 0; ii < len && buf[ii]; ii++) {
		for (jj = 0; brs[jj]; jj++) {
			if (buf[ii] == brs[jj]) {
				break;
			}
		}
		if (brs[jj] == '\0') {
			break;
		}
	}

	if (ii > 0) {
		for (jj = 0; buf[ii]; ii++, jj++) {
			buf[jj] = buf[ii];
		}

		assert(jj < len);
		buf[jj] = '\0';
		len = jj;
	}

	return len;
}

int trim(char *buf, int len, char *brs)
{
	assert(buf);
	assert(len >= 0);
	assert(brs);

	len = trimleft(buf, len, brs);
	len = trimright(buf, len, brs);

	return len;
}

