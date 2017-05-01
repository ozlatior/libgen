#ifndef __gen_chromosome_h__
#define __gen_chromosome_h__

#include "Gene.h"

namespace gen {

typedef unsigned char GeneBase;
typedef unsigned int GeneIndex;

struct ChromosomeParams {
	GeneIndex geneSize;
	GeneIndex length;
};

class Chromosome {

private:
	GeneIndex geneSize;
	GeneIndex length;
	GeneBase* data;

public:
	Chromosome(const ChromosomeParams params);
	Chromosome(const GeneIndex geneSize, const GeneIndex length);
	~Chromosome();

	GeneIndex getGeneIndex() const;
	GeneIndex getLength() const;
	ChromosomeParams getParams() const;

	Gene* getGeneAt(const GeneIndex index) const;
	void setGeneAt(const GeneIndex index, const Gene* const gene);

};

};

#endif // __gen_chromosome_h__
