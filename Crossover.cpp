#include <stdlib.h>
#include <string.h>

#include "Crossover.h"
#include "Util.h"

gen::Crossover::Crossover(const gen::CrossoverParams params) {
	this->params = params;
}

gen::Crossover::~Crossover() {
	if (this->params.type == gen::UNIFORM)
		free(this->params.uniform.parent1);
	if (this->params.type == gen::HALF_UNIFORM)
		free(this->params.halfUniform.parent1);
}

static inline bool chromosomesAreCompatible(
	const gen::Chromosome* const c1, const gen::Chromosome* const c2) {
	if (c1->getGeneIndex() != c2->getGeneIndex())
		return false;
	if (c1->getLength() != c2->getLength())
		return false;
	return true;
}

static inline bool crossOnePoint(const gen::GeneIndex point,
	const gen::Chromosome* const parent1, const gen::Chromosome* const parent2,
	gen::Chromosome* const child1, gen::Chromosome* const child2) {

	if (!chromosomesAreCompatible(parent1, parent2) ||
		!chromosomesAreCompatible(parent1, child1) ||
		!chromosomesAreCompatible(parent1, child2)) {
		DEBUG("%s: incompatible chromosomes\n", __func__);
		return false;
	}

	if (point >= parent1->getLength()) {
		DEBUG("%s: point out of range\n", __func__);
		return false;
	}

	memcpy(child1->getGeneAt(0), parent1->getGeneAt(0), point * parent1->getGeneIndex());
	memcpy(child2->getGeneAt(0), parent2->getGeneAt(0), point * parent1->getGeneIndex());
	memcpy(child1->getGeneAt(point), parent2->getGeneAt(point),
		(parent1->getLength() - point) * parent1->getGeneIndex());
	memcpy(child2->getGeneAt(point), parent1->getGeneAt(point),
		(parent1->getLength() - point) * parent1->getGeneIndex());

	return true;
}

static inline bool crossTwoPoint(const gen::GeneIndex point1, const gen::GeneIndex point2,
	const gen::Chromosome* const parent1, const gen::Chromosome* const parent2,
	gen::Chromosome* const child1, gen::Chromosome* const child2) {

	if (!chromosomesAreCompatible(parent1, parent2) ||
		!chromosomesAreCompatible(parent1, child1) ||
		!chromosomesAreCompatible(parent1, child2)) {
		DEBUG("%s: incompatible chromosomes\n", __func__);
		return false;
	}

	memcpy(child1->getGeneAt(0), parent1->getGeneAt(0),
		parent1->getLength() * parent1->getGeneIndex());
	memcpy(child2->getGeneAt(0), parent2->getGeneAt(0),
		parent1->getLength() * parent1->getGeneIndex());
	memcpy(child1->getGeneAt(point1), parent2->getGeneAt(point1),
		(point2 - point1) * parent1->getGeneIndex());
	memcpy(child2->getGeneAt(point1), parent1->getGeneAt(point1),
		(point2 - point1) * parent1->getGeneIndex());

	return true;
}

static inline bool crossUniform(const gen::GeneIndex length, const bool* const p1,
	const gen::Chromosome* const parent1, const gen::Chromosome* const parent2,
	gen::Chromosome* const child1, gen::Chromosome* const child2) {

	if (!chromosomesAreCompatible(parent1, parent2) ||
		!chromosomesAreCompatible(parent1, child1) ||
		!chromosomesAreCompatible(parent1, child2)) {
		DEBUG("%s: incompatible chromosomes\n", __func__);
		return false;
	}

	memcpy(child1->getGeneAt(0), parent1->getGeneAt(0),
		parent1->getLength() * parent1->getGeneIndex());
	memcpy(child2->getGeneAt(0), parent2->getGeneAt(0),
		parent1->getLength() * parent1->getGeneIndex());

	gen::GeneIndex from = 0;
	gen::GeneIndex to = 0;
	while (from < length-1) {
		while (p1[from] == true) {
			from++;
			if (from >= length-1)
				break;
		}
		to = from;
		while (p1[to] == false) {
			to++;
			if (to >= length-1) {
				to = length-1;
				break;
			}
		}
		memcpy(child1->getGeneAt(from), parent2->getGeneAt(from),
			(to-from) * parent1->getGeneIndex());
		memcpy(child2->getGeneAt(from), parent1->getGeneAt(from),
			(to-from) * parent1->getGeneIndex());
		from = to;
	}

	return true;
}

static inline bool crossHalfUniform(const gen::GeneIndex length, const gen::GeneIndex* const p1,
	const gen::Chromosome* const parent1, const gen::Chromosome* const parent2,
	gen::Chromosome* const child1, gen::Chromosome* const child2) {

	if (!chromosomesAreCompatible(parent1, parent2) ||
		!chromosomesAreCompatible(parent1, child1) ||
		!chromosomesAreCompatible(parent1, child2)) {
		DEBUG("%s: incompatible chromosomes\n", __func__);
		return false;
	}

	memcpy(child1->getGeneAt(0), parent2->getGeneAt(0),
		parent1->getLength() * parent1->getGeneIndex());
	memcpy(child2->getGeneAt(0), parent1->getGeneAt(0),
		parent1->getLength() * parent1->getGeneIndex());

	for (gen::GeneIndex i=0; i<length; i++) {
		// TODO: all these memcpys will be quite slow, maybe figure something else out?
		memcpy(child1->getGeneAt(p1[i]), parent1->getGeneAt(p1[i]), parent1->getGeneIndex());
		memcpy(child2->getGeneAt(p1[i]), parent2->getGeneAt(p1[i]), parent1->getGeneIndex());
	}

	return true;
}

bool gen::Crossover::cross(
	const gen::Chromosome* const parent1, const gen::Chromosome* const parent2,
	gen::Chromosome* const child1, gen::Chromosome* const child2) const {

	switch (this->params.type) {
		case (gen::ONE_POINT):
			return crossOnePoint(this->params.onePoint.point,
				parent1, parent2, child1, child2);
		case (gen::TWO_POINT):
			return crossTwoPoint(this->params.twoPoint.point1, this->params.twoPoint.point2,
				parent1, parent2, child1, child2);
		case (gen::UNIFORM):
			return crossUniform(this->params.uniform.length, this->params.uniform.parent1,
				parent1, parent2, child1, child2);
		case (gen::HALF_UNIFORM):
			return crossHalfUniform(this->params.halfUniform.halfLength,
				this->params.halfUniform.parent1, parent1, parent2, child1, child2);
		default:
			DEBUG("%s: bad crossover type\n", __func__);
			return false;
	}

	DEBUG("%s: crossover failed\n", __func__);
	return false;
}

gen::CrossoverType gen::Crossover::getType() const {
	return this->params.type;
}

gen::OnePointCrossoverParams *gen::Crossover::getOnePointParams() {
	return &(this->params.onePoint);
}

gen::TwoPointCrossoverParams *gen::Crossover::getTwoPointParams() {
	return &(this->params.twoPoint);
}

gen::UniformCrossoverParams *gen::Crossover::getUniformParams() {
	return &(this->params.uniform);
}

gen::HalfUniformCrossoverParams *gen::Crossover::getHalfUniformParams() {
	return &(this->params.halfUniform);
}

gen::CrossoverParams gen::Crossover::OnePoint(const gen::GeneIndex point) {
	gen::CrossoverParams ret;
	ret.type = gen::ONE_POINT;
	ret.onePoint.point = point;
	return ret;
}

gen::CrossoverParams gen::Crossover::TwoPoint(
	const gen::GeneIndex point1, const gen::GeneIndex point2) {

	gen::CrossoverParams ret;
	ret.type = gen::TWO_POINT;
	ret.twoPoint.point1 = point1;
	ret.twoPoint.point2 = point2;
	return ret;
}

gen::CrossoverParams gen::Crossover::Uniform(
	const gen::GeneIndex length, const bool* const parent1) {

	gen::CrossoverParams ret;
	ret.type = gen::UNIFORM;
	ret.uniform.length = length;
	ret.uniform.parent1 = (bool*)malloc(sizeof(bool) * length);
	memcpy((void*)ret.uniform.parent1, (void*)parent1, sizeof(bool) * length);
	return ret;
}

gen::CrossoverParams gen::Crossover::HalfUniform(
	const gen::GeneIndex length, const gen::GeneIndex* const parent1) {

	gen::CrossoverParams ret;
	ret.type = gen::HALF_UNIFORM;
	ret.halfUniform.halfLength = length;
	ret.halfUniform.parent1 = (gen::GeneIndex*)malloc(sizeof(gen::GeneIndex) * length);
	memcpy((void*)ret.uniform.parent1, (void*)parent1, sizeof(gen::GeneIndex) * length);
	return ret;
}
