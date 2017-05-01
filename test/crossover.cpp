#include <stdio.h>
#include "infra.h"

#include "Crossover.h"
#include "BoolGene.h"

static void init(gen::Chromosome* c1, gen::Chromosome* c2) {
	for (gen::GeneIndex i=0; i<c1->getLength(); i++)
		((gen::BoolGene*)(c1->getGeneAt(i)))->setValue(false);
	for (gen::GeneIndex i=0; i<c2->getLength(); i++)
		((gen::BoolGene*)(c2->getGeneAt(i)))->setValue(true);
}

int runOnePointTest(gen::Chromosome* p1, gen::Chromosome* p2) {
	int ret = 1;
	init(p1, p2);
	gen::GeneIndex point = 42;

	gen::Chromosome* c1 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Chromosome* c2 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Crossover* co = new gen::Crossover(gen::Crossover::OnePoint(point));
	co->cross(p1, p2, c1, c2);

	for (gen::GeneIndex i=0; i<p1->getLength(); i++) {
		if (i < point) {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 2")) {
				ret = 0;
				goto bail;
			}
		}
		else {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 2")) {
				ret = 0;
			}
		}
	}

pass:
	printf("PASS\n");
bail:
	delete c1;
	delete c2;
	delete co;
	return ret;
}

int runTwoPointTest(gen::Chromosome* p1, gen::Chromosome* p2) {
	int ret = 1;
	init(p1, p2);
	gen::GeneIndex point1 = 13;
	gen::GeneIndex point2 = 42;

	gen::Chromosome* c1 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Chromosome* c2 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Crossover* co = new gen::Crossover(gen::Crossover::TwoPoint(point1, point2));
	co->cross(p1, p2, c1, c2);

	for (gen::GeneIndex i=0; i<p1->getLength(); i++) {
		if (i < point1 || i >= point2) {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 2")) {
				ret = 0;
				goto bail;
			}
		}
		else {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 2")) {
				ret = 0;
			}
		}
	}

pass:
	printf("PASS\n");
bail:
	delete c1;
	delete c2;
	delete co;
	return ret;
}

int runUniformTest(gen::Chromosome* p1, gen::Chromosome* p2) {
	int ret = 1;
	init(p1, p2);
	bool parent1[64];
	for (int i=0; i<64; i++)
		if (i%3 == 0 || i%5 == 0)
			parent1[i] = true;
		else
			parent1[i] = false;

	gen::Chromosome* c1 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Chromosome* c2 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Crossover* co = new gen::Crossover(gen::Crossover::Uniform(64, parent1));
	co->cross(p1, p2, c1, c2);

	for (gen::GeneIndex i=0; i<p1->getLength(); i++) {
		if (parent1[i]) {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 2")) {
				ret = 0;
				goto bail;
			}
		}
		else {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 2")) {
				ret = 0;
			}
		}
	}

pass:
	printf("PASS\n");
bail:
	delete c1;
	delete c2;
	delete co;
	return ret;
}

int runHalfUniformTest(gen::Chromosome* p1, gen::Chromosome* p2) {
	int ret = 1;
	init(p1, p2);
	gen::GeneIndex parent1[32];
	for (int i=0; i<32; i++)
		parent1[i] = 2*i;

	gen::Chromosome* c1 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Chromosome* c2 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Crossover* co = new gen::Crossover(gen::Crossover::HalfUniform(32, parent1));
	co->cross(p1, p2, c1, c2);

	for (gen::GeneIndex i=0; i<p1->getLength(); i++) {
		bool found = false;
		for (int j=0; j<32; j++)
			if (parent1[j] == i) {
				found = true;
				break;
			}

		if (found) {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 2")) {
				ret = 0;
				goto bail;
			}
		}
		else {
			if (!check(((gen::BoolGene*)(c1->getGeneAt(i)))->getValue() == true,
				"bad value (false) in child 1")) {
				ret = 0;
				goto bail;
			}
			if (!check(((gen::BoolGene*)(c2->getGeneAt(i)))->getValue() == false,
				"bad value (true) in child 2")) {
				ret = 0;
			}
		}
	}

pass:
	printf("PASS\n");
bail:
	delete c1;
	delete c2;
	delete co;
	return ret;
}

int runCrossoverTests() {
	int ret = 1;
	printf("  Running crossover tests on boolean chromosomes\n");

	gen::Chromosome* c1 = new gen::Chromosome(sizeof(gen::BoolGene), 64);
	gen::Chromosome* c2 = new gen::Chromosome(sizeof(gen::BoolGene), 64);

	printf("    One Point Crossover ... ");
	ret *= runOnePointTest(c1, c2);

	printf("    Two Point Crossover ... ");
	ret *= runTwoPointTest(c1, c2);

	printf("    Uniform Crossover ... ");
	ret *= runUniformTest(c1, c2);

	printf("    Half Uniform Crossover ... ");
	ret *= runHalfUniformTest(c1, c2);

	delete c1;
	delete c2;

	return ret;
}
