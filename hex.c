#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

uint8_t  x8[64];
uint16_t x16[32];
uint32_t x32[16];

int main(int argc, char **argv)
{
	long long n;
	char *end;

	printf("<items>\n");

	errno = 0;
	n = strtoll(argv[1], &end, 0);
	if (errno != 0) {
		printf("<item uid=\"err\"><title>oops: %s</title></item>\n", strerror(errno));

	} else {
		long long _n;
		int i, skip;

		_n = n;
		for (i = 63; i >= 0 && _n > 0; i--) {
			x8[i] = _n & 0xff;
			_n = _n >> 8;
		}

		_n = n;
		for (i = 31; i >= 0 && _n > 0; i--) {
			x16[i] = _n & 0xffff;
			_n = _n >> 16;
		}

		_n = n;
		for (i = 15; i >= 0 && _n > 0; i--) {
			x32[i] = _n & 0xffffffff;
			_n = _n >> 32;
		}


		printf("<item uuid=\"hex\"><title>");
		for (skip = 1, i = 0; i < 64; i++) {
			if (x8[i] == 0 && skip) {
				continue;
			}
			skip = 0;
			printf("%02x ", x8[i]);
		}
		printf("</title><subtitle>hex</subtitle></item>\n");

		printf("<item uuid=\"oct\"><title>");
		for (skip = 1, i = 0; i < 64; i++) {
			if (x8[i] == 0 && skip) {
				continue;
			}
			skip = 0;
			printf("%04o ", x8[i]);
		}
		printf("</title><subtitle>octal</subtitle></item>\n");

		printf("<item uuid=\"ascii\"><title>");
		for (skip = 1, i = 0; i < 64; i++) {
			if (x8[i] == 0 && skip) {
				continue;
			}
			skip = 0;
			printf("%c ", isprint(x8[i]) ? x8[i] : '.');
		}
		printf("</title><subtitle>ascii</subtitle></item>\n");

		printf("<item uuid=\"dec8\"><title>");
		for (skip = 1, i = 0; i < 64; i++) {
			if (x8[i] == 0 && skip) {
				continue;
			}
			skip = 0;
			printf("%d ", x8[i]);
		}
		printf("</title><subtitle>decimal 8</subtitle></item>\n");

		printf("<item uuid=\"dec16\"><title>");
		for (skip = 1, i = 0; i < 32; i++) {
			if (x16[i] == 0 && skip) {
				continue;
			}
			skip = 0;
			printf("%d ", x16[i]);
		}
		printf("</title><subtitle>decimal 16</subtitle></item>\n");

		printf("<item uuid=\"dec32\"><title>");
		for (skip = 1, i = 0; i < 16; i++) {
			if (x32[i] == 0 && skip) {
				continue;
			}
			skip = 0;
			printf("%d ", x32[i]);
		}
		printf("</title><subtitle>decimal 32</subtitle></item>\n");

	}

	printf("</items>\n");
	return 0;
}
