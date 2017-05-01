#ifndef __gen_genotype_h__
#define __gen_genotype_h__

#include "Crossover.h"

namespace gen {

class Genotype {

private:
	bool initialized;
	GeneIndex size;
	ChromosomeParams* params;
	CrossoverType* crossoverType;
	MutationInfo* mutationInfo;
	Chromosome** chromosome;

protected:
	Genotype(const GeneIndex size);
	~Genotype();

	GeneIndex getSize();

	bool setChromosomeParams(const GeneIndex index, const ChromosomeParams params);
	bool setChromosomeParams(const GeneIndex index,
		const GeneIndex geneSize, const GeneIndex length);
	ChromosomeParams getChromosomeParams(const GeneIndex index) const;

	void init();

	bool setCrossoverType(const GeneIndex index, const CrossoverType type);
	CrossoverType getCrossoverType(const GeneIndex index) const;

	bool setMutationInfo(const GeneIndex index, const MutationInfo info);
	MutationInfo getMutationInfo(const GeneIndex index) const;

	/* the chromosome object can be directly retrieved for reading or writing */
	Chromosome* getChromosome(const GeneIndex index);

	/* run a single mutation cycle; returns the number of genes mutated */
	unsigned int mutationCycle();

	/* check if this genotype is compatible with another */
	bool isCompatible(const Genotype* const other) const;

	/*
     * Crossover with the other "parent" to generate two children; the children Genotype
	 * objects are entirely the user's responsibility, both for creating and deleting them
	 * this method also runs mutation cycles on the two genotypes
	 */
	bool cross(const Genotype* const p2, Genotype* const c1, Genotype* const c2) const;

	void populate();

};

};

#endif // __gen_genotype_h__
