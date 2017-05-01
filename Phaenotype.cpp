#include "Phaenotype.h"

gen::Phaenotype::Phaenotype(gen::Genotype* const genotype) {
	this->genotype = genotype;
}

gen::Phaenotype::~Phaenotype() {
	this->genotype = 0;
}

gen::Genotype* gen::Phaenotype::getGenotype() {
	return this->genotype;
}

unsigned int gen::Phaenotype::getFitness() {
	return 0;
}
