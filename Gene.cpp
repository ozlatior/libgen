#include "Gene.h"
#include <stdio.h>

gen::Gene::Gene() {
}

gen::Gene::~Gene() {
}

bool gen::Gene::mutate(const gen::MutationParams* const params) {
	printf("gene mutate\n");
	(void)params;
	return false;
}

void gen::Gene::populate() {
}
