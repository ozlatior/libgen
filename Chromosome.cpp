#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Chromosome.h"

gen::Chromosome::Chromosome(const gen::ChromosomeParams params) {
	this->geneSize = params.geneSize;
	this->length = params.length;
	this->data = (GeneBase*)malloc(geneSize * length);
}

gen::Chromosome::Chromosome(const gen::GeneIndex geneSize, const gen::GeneIndex length) {
	this->geneSize = geneSize;
	this->length = length;
	this->data = (GeneBase*)malloc(geneSize * length);
}

gen::Chromosome::~Chromosome() {
	free(this->data);
	this->data = NULL;
}

gen::GeneIndex gen::Chromosome::getGeneIndex() const {
	return this->geneSize;
}

gen::GeneIndex gen::Chromosome::getLength() const {
	return this->length;
}

gen::ChromosomeParams gen::Chromosome::getParams() const {
	gen::ChromosomeParams ret;
	ret.geneSize = this->geneSize;
	ret.length = this->length;
	return ret;
}

gen::Gene* gen::Chromosome::getGeneAt(const gen::GeneIndex index) const {
	gen::GeneBase* ret = (GeneBase*)(&(this->data[this->geneSize * index]));
	return (Gene*)ret;
}

void gen::Chromosome::setGeneAt(const gen::GeneIndex index, const gen::Gene* const gene) {
	memcpy((void*)&this->data[this->geneSize * index], (void*)gene, this->geneSize);
}
