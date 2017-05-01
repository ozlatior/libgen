#ifndef __ann_test_infra_h__
#define __ann_test_infra_h__

inline int check(bool condition, const char* message) {
	if (condition)
		return 1;
	printf("FAIL\n");
	printf("      (%s)\n", message);
	return 0;
}

#endif // __ann_test_infra_h__
