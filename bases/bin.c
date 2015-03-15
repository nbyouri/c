#include <assert.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * unsigned binary utilities
 *
 */
unsigned char bit(uint64_t num, uint64_t place) {
	return (num & place) > 0 ? '1' : '0';
}

char *binStr(uint64_t num) {
	char *str = NULL;
	size_t length = sizeof(str) == 8 ? 64 : 32;

	str = malloc(length);
	assert(str != NULL);

	str = memset(str, '0', length);

	uint64_t ind = 0;
	for (unsigned int i = 0; i < length; i++) {
		ind = 1 << i;
		str[length - i] = bit(num, ind);
		printf("%s\n", str);
	}
	return str;
}

int main(void) {
	uint64_t num = 234230501;

	char *str = binStr(num);

	printf("%" PRIi64 " == %s\n", num, str);

	free(str);
	str = NULL;
	return 0;
}
