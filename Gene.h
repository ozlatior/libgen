#ifndef __gen_gene_h__
#define __gen_gene_h__

namespace gen {

enum MutationType {
	NOT_SET,
	COMPLETE
};

struct MutationParams {
	MutationType type;
};

//TODO: refactor these so they are consistent
struct MutationInfo {
	MutationType type;
	unsigned int rate; // 1 out of <mutationRate> gets mutated
	// here comes a union of mutation info structures once these are defined
};

class Gene {

protected:
	Gene();
	~Gene();

public:
	virtual bool mutate(const MutationParams* const params);
	void populate();

};

};

#endif // __gen_gene_h__
