#include <stdio.h>

int runUtilTests();
int runBasicTests();
int runCrossoverTests();

int main(void) {
	int ret = 1;
	printf("Running complete gen test suite\n");
	ret *= runUtilTests();
	ret *= runBasicTests();
	ret *= runCrossoverTests();

	if (ret == 1)
		printf("All tests were successful!\n");
	else
		printf("Some tests have failed.\n");

	return 0;
}
