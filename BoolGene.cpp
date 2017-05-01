#include "BoolGene.h"
#include "Util.h"
#include <stdio.h>

gen::BoolGene::BoolGene() {
	this->value = false;
}

gen::BoolGene::BoolGene(const bool value) {
	this->value = value;
}

gen::BoolGene::~BoolGene() {
}

bool gen::BoolGene::mutate() {
	this->value = !this->value;
	return true;
}

bool gen::BoolGene::mutate(const gen::MutationParams* const params) {
	(void)params;
	this->value = !this->value;
	return true;
}

void gen::BoolGene::setValue(const bool value) {
	this->value = value;
}

bool gen::BoolGene::getValue() const {
	return this->value;
}

void gen::BoolGene::populate() {
	this->value = rand_bool();
}
