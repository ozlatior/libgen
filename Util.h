#ifndef __gen_util_h__
#define __gen_util_h__

#include <stdio.h>

#define DEBUG(x, ...) printf(x, __VA_ARGS__);

inline void HEX_DUMP(const void* const p, const size_t length) {
	unsigned char* c = (unsigned char*)p;
	for (size_t i=0; i<length; i++)
		printf("%02x ", 0xff & (unsigned int)(c[i]));
}

// TODO: this is a good random engine for testing, but might not be enough
#define RAND_BUF_SIZE	(1024)
static unsigned char rand_buf[RAND_BUF_SIZE];
static size_t rand_index = RAND_BUF_SIZE;

static inline void refill_rand_buffer(size_t size) {
	if (rand_index > RAND_BUF_SIZE-size) {
		FILE* dev_file = fopen("/dev/urandom", "r");
		fread((void*)rand_buf, sizeof(unsigned char), RAND_BUF_SIZE, dev_file);
		fclose(dev_file);
		rand_index = 0;
	}
}

inline bool rand_bool() {
	refill_rand_buffer(sizeof(unsigned char));
	bool ret = rand_buf[rand_index] % 2;
	rand_index++;
	return ret;
}

inline unsigned int rand_uint(unsigned int up_to) {
	refill_rand_buffer(sizeof(unsigned int));
	unsigned int* src = (unsigned int*)(&rand_buf[rand_index]);
	rand_index += sizeof(unsigned int);
	return (*src) % up_to;
}

#endif // __gen_util_h__
