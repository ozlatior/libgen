#ifndef __gen_bool_gene_h__
#define __gen_bool_gene_h__

#include "Gene.h"

namespace gen {

class BoolGene : Gene {

private:
	bool value;

public:
	BoolGene();
	BoolGene(const bool value);
	~BoolGene();

	bool mutate();
	bool mutate(const MutationParams* const params);
	void setValue(const bool value);
	bool getValue() const;

	void populate();

};

};

#endif // __gen_bool_gene_h__
