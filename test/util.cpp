#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"

int runRandomBoolPickTest(bool pick) {
	int count = 0;
	while (rand_bool() != pick) {
		printf("#");
		count++;
	}
	printf(" PASS\n");
	return 1;
}

int runRandomBoolDistributionTest() {
	unsigned int t = 0;
	unsigned int f = 0;
	for (unsigned int i=0; i<1000000; i++)
		if (rand_bool())
			t++;
		else
			f++;
	printf("%u/%u ", f, t);
	if (abs(t-f) > 2000) {
		printf("FAIL\n");
		return 0;
	}
	printf("PASS\n");
	return 1;
}

int runRandomNumberPickTest(unsigned int pick, unsigned int from) {
	int count = 0;
	while (rand_uint(from) != pick)
		count++;
	printf("%d PASS\n", count);
	return 1;
}

int runRandomNumberDistribution(unsigned int steps) {
	unsigned int count[steps];
	memset(count, 0x00, sizeof(count));
	for (unsigned int i=0; i<1000000; i++)
		count[rand_uint(steps)]++;
	printf("\n      ");
	for (unsigned int i=0; i<steps; i++) {
		printf("%u ", count[i]);
		if (i % 5 == 4)
			printf("\n      ");
	}
	printf("PASS\n");
	return 1;
}

int runRandomTests() {
	int ret = 1;

	printf("    Random bool pick (false) ... ");
	ret *= runRandomBoolPickTest(false);

	printf("    Random bool pick (true) ... ");
	ret *= runRandomBoolPickTest(true);

	printf("    Random bool distribution ... ");
	ret *= runRandomBoolDistributionTest();

	printf("    Random number pick (1/10) ... ");
	ret *= runRandomNumberPickTest(0, 10);

	printf("    Random number pick (1/1000) ... ");
	ret *= runRandomNumberPickTest(0, 1000);

	printf("    Random number distribution ... ");
	ret *= runRandomNumberDistribution(10);

	return ret;
}

int runUtilTests() {
	int ret = 1;
	printf("  Running util tests\n");

	ret *= runRandomTests();

	return ret;
}
