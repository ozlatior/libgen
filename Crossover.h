#ifndef __gen_crossover_h__
#define __gen_crossover_h__

#include "Chromosome.h"
#include "Gene.h"

namespace gen {

/*
 * Terminology: in order to easily explain crossovers, we are going to assume
 * 		a crossover operation always takes the form
 *			{c1, c2} = cross({p1, p2}), where c and p are children and parents
 *		we are going to call the parents `primary` and `secondary` based on
 *		wether they have the same index or not; therefore:
 *			c1 has a primary parent p1 and a secondary parent p2
 *			c2 has a primary parent p2 and a secondary parent p1
 * Different crossover types that are allowed
 * one point - everything before a chosen index goes to primary parent,
 *		everything after goes to the secondary parent
 * two point - everything between two chosen indices but not including the last
 *		goes to the secondary parent, everything after to the primary
 * symmetric - this is a variation of two-point where the chosen points are
 *		equidistant to the middle of the chromosome; since this information
 *		can be specified using the two-point model, the symmetric type is not
 *		used for crossovers, it is only used as extra-information in the
 *		Genotype classes
 * uniform - this is a crossover based on a mask which tells wether the children
 *		receive the corresponding gene from the primary or secondary parent
 * half-uniform - this is a crossover where exactly have of the genes come from
 *		each parent; it is based on an array of gene indices for genes which should
 *		come from the primary parent in each child
 */
enum CrossoverType {
	CO_TYPE_NOT_SET,
	ONE_POINT,
	TWO_POINT,
	SYMMETRIC,
	UNIFORM,
	HALF_UNIFORM
};

struct OnePointCrossoverParams {
	GeneIndex point;
};

struct TwoPointCrossoverParams {
	GeneIndex point1;
	GeneIndex point2;
};

struct UniformCrossoverParams {
	GeneIndex length;
	bool *parent1;
};

struct HalfUniformCrossoverParams {
	GeneIndex halfLength;
	GeneIndex *parent1;
};

struct CrossoverParams {
	CrossoverType type;
	union {
		OnePointCrossoverParams onePoint;
		TwoPointCrossoverParams twoPoint;
		UniformCrossoverParams uniform;
		HalfUniformCrossoverParams halfUniform;
	};
};

class Crossover {

private:
	CrossoverParams params;

public:
	Crossover(const CrossoverParams params);
	~Crossover();

	bool cross(const Chromosome* const parent1, const Chromosome* const parent2,
		Chromosome* const child1, Chromosome* const child2) const;

	CrossoverType getType() const;
	OnePointCrossoverParams *getOnePointParams();
	TwoPointCrossoverParams *getTwoPointParams();
	UniformCrossoverParams *getUniformParams();
	HalfUniformCrossoverParams *getHalfUniformParams();

	static CrossoverParams OnePoint(const GeneIndex point);
	static CrossoverParams TwoPoint(const GeneIndex point1, const GeneIndex point2);
	static CrossoverParams Uniform(const GeneIndex length, const bool* const parent1);
	static CrossoverParams HalfUniform(
		const GeneIndex halfLength, const GeneIndex* const parent1);
};

};

#endif // __gen_crossover_h__
