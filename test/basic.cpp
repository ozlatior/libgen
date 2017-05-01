#include <stdio.h>
#include "infra.h"

#include "Chromosome.h"
#include "BoolGene.h"

int runConstructorTest(gen::Chromosome **c) {
	(*c) = new gen::Chromosome(sizeof(gen::BoolGene), 64);

	if (!check((*c)->getGeneIndex() == sizeof(gen::BoolGene), "bad gene size"))
		return 0;

	if (!check((*c)->getLength() == 64, "bad chromosome length"))
		return 0;

	for (gen::GeneIndex i=0; i<64; i++)
		((gen::BoolGene*)((*c)->getGeneAt(i)))->setValue(false);

	printf("PASS\n");
	return 1;
}

int runGettingGenesTest(gen::Chromosome *c, bool value) {
	for (gen::GeneIndex i=0; i<c->getLength(); i++) {
		if (!check(((gen::BoolGene*)(c->getGeneAt(i)))->getValue() == value, "bad value"))
			return 0;
	}
	printf("PASS\n");
	return 1;
}

int runSettingGenesTest(gen::Chromosome *c, bool value) {
	for (gen::GeneIndex i=0; i<c->getLength(); i++)
		((gen::BoolGene*)(c->getGeneAt(i)))->setValue(value);
	return runGettingGenesTest(c, value);
}

int runDestructorTest(gen::Chromosome *c) {
	delete c;
	printf("PASS\n");
	return 1;
}

int runBasicTests() {
	int ret = 1;
	printf("  Running basic 1-chromosome tests\n");

	gen::Chromosome *c1;

	printf("    Constructor ... ");
	ret *= runConstructorTest(&c1);

	printf("    Getting genes ... ");
	ret *= runGettingGenesTest(c1, false);

	printf("    Setting genes (true) ... ");
	ret *= runSettingGenesTest(c1, true);

	printf("    Setting genes (false) ... ");
	ret *= runSettingGenesTest(c1, false);

	printf("    Destructor ... ");
	ret *= runDestructorTest(c1);

	return ret;
}
