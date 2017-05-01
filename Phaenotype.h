#ifndef __gen_phaenotype_h__
#define __gen_phaenotype_h__

#include "Genotype.h"

namespace gen {

class Phaenotype {

private:
	Genotype* genotype;

protected:
	Phaenotype(Genotype* const genotype);
	~Phaenotype();
	Genotype* getGenotype();
	unsigned int getFitness();
};

};

#endif // __gen_phaenotype_h__
