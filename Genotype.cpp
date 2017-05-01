#include <stdio.h>
#include <stdlib.h>
#include "Genotype.h"
#include "Util.h"

gen::Genotype::Genotype(const gen::GeneIndex size) {
	this->initialized = false;
	this->size = size;
	this->params = (gen::ChromosomeParams*)malloc(sizeof(gen::ChromosomeParams)*size);
	this->crossoverType = (gen::CrossoverType*)malloc(sizeof(gen::CrossoverType)*size);
	this->mutationInfo = (gen::MutationInfo*)malloc(sizeof(gen::MutationInfo)*size);
	this->chromosome = (gen::Chromosome**)malloc(sizeof(gen::Chromosome*)*size);
}

gen::Genotype::~Genotype() {
	for (gen::GeneIndex i=0; i<this->size; i++)
		delete this->chromosome[i];
	free(this->params);
	free(this->crossoverType);
	free(this->mutationInfo);
	free(this->chromosome);
}

gen::GeneIndex gen::Genotype::getSize() {
	return this->size;
}

bool gen::Genotype::setChromosomeParams(
	const gen::GeneIndex index, const gen::ChromosomeParams params) {

	if (index >= this->size)
		return false;
	this->params[index].geneSize = params.geneSize;
	this->params[index].length = params.length;
	return true;
}

bool gen::Genotype::setChromosomeParams(const gen::GeneIndex index,
	const gen::GeneIndex geneSize, const gen::GeneIndex length) {

	if (index >= this->size)
		return false;
	this->params[index].geneSize = geneSize;
	this->params[index].length = length;
	return true;
}

gen::ChromosomeParams gen::Genotype::getChromosomeParams(const gen::GeneIndex index) const {
	if (index >= this->size)
		return {0,0};
	return this->params[index];
}

void gen::Genotype::init() {
	for (gen::GeneIndex i=0; i<this->size; i++)
		this->chromosome[i] = new gen::Chromosome(this->params[i]);
}

bool gen::Genotype::setCrossoverType(
	const gen::GeneIndex index, const gen::CrossoverType type) {

	if (index >= this->size)
		return false;
	this->crossoverType[index] = type;
	return true;
}

gen::CrossoverType gen::Genotype::getCrossoverType(const gen::GeneIndex index) const {
	if (index >= this->size)
		return gen::CO_TYPE_NOT_SET;
	return this->crossoverType[index];
}

bool gen::Genotype::setMutationInfo(
	const gen::GeneIndex index, const gen::MutationInfo info) {

	if (index >= this->size)
		return false;
	this->mutationInfo[index] = info;
	return true;
}

gen::MutationInfo gen::Genotype::getMutationInfo(const gen::GeneIndex index) const {
	if (index >= this->size) {
		gen::MutationInfo ret;
		ret.type = gen::NOT_SET;
		return ret;
	}
	return this->mutationInfo[index];
}

gen::Chromosome* gen::Genotype::getChromosome(const gen::GeneIndex index) {
	if (index >= this->size)
		return NULL;
	return this->chromosome[index];
}

unsigned int gen::Genotype::mutationCycle() {
	return 0;
}

bool gen::Genotype::isCompatible(const gen::Genotype* const other) const {
	if (this->size != other->size)
		return false;
	for (gen::GeneIndex i=0; i<this->size; i++) {
		if (this->params[i].geneSize != other->params[i].geneSize)
			return false;
		if (this->params[i].length != other->params[i].length)
			return false;
		if (this->crossoverType[i] != other->crossoverType[i])
			return false;
	}
	return true;
}

//TODO: I don't like this, maybe split up into smaller functions?
bool gen::Genotype::cross(const gen::Genotype* const p2,
	gen::Genotype* const c1, gen::Genotype* const c2) const {

	if (!this->isCompatible(p2))
		return false;

	for (gen::GeneIndex i=0; i<this->size; i++) {
		static gen::CrossoverParams params;
		params.type = this->crossoverType[i];
		switch (this->crossoverType[i]) {
			case gen::ONE_POINT:
				params.onePoint.point = rand_uint(this->params[i].length);
				break;
			case gen::TWO_POINT:
				params.twoPoint.point1 = rand_uint(this->params[i].length);
				do {
					params.twoPoint.point2 = rand_uint(this->params[i].length);
				} while (params.twoPoint.point1 == params.twoPoint.point2);
				break;
			case gen::SYMMETRIC: {
				// the "SYMMETRIC" type is only useful up to here, from here on
				// this crossover is just a special TWO_POINT crossover
				params.type = gen::TWO_POINT;
				gen::GeneIndex middle = this->params[i].length/2;
				gen::GeneIndex range = rand_uint(middle);
				params.twoPoint.point1 = middle-range;
				params.twoPoint.point2 = middle+range;
				break;
			}
			case gen::UNIFORM: {
				params.uniform.parent1 = (bool*)malloc(sizeof(bool)*this->params[i].length);
				for (gen::GeneIndex j=0; j<this->params[i].length; j++)
					params.uniform.parent1[j] = rand_bool();
				break;
			}
			case gen::HALF_UNIFORM: {
				params.halfUniform.parent1 =
					(GeneIndex*)malloc(sizeof(gen::GeneIndex)*this->params[i].length/2);
				gen::GeneIndex j = 0;
				while (j < this->params[i].length/2) {
					bool found = false;
					gen::GeneIndex pick = rand_uint(this->params[i].length);
					for (gen::GeneIndex k=0; k<j; k++) {
						if (params.halfUniform.parent1[k] == pick) {
							found = true;
							break;
						}
					}
					if (found)
						continue;
					params.halfUniform.parent1[j] = pick;
					j++;
				}
				break;
			}
			default:
				DEBUG("%s: bad crossover type\n", __func__);
		}

		gen::Crossover* cross = new gen::Crossover(params);
		cross->cross(this->chromosome[i], p2->chromosome[i],
			c1->chromosome[i], c2->chromosome[i]);
		delete cross;
	}

	return true;
}

void gen::Genotype::populate() {
}
