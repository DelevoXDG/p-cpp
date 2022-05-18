// Maksim Zdobnikau

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::string;
#define nullptr NULL

class Fruit;
class Branch;
class Tree;
class Garden;

// SECTION DECLARATIONS
class Fruit {
private:
	unsigned int weight;
	unsigned int length;
	Branch* parent;
	Fruit* next;

public:
	//Note Required
	Fruit();
	Fruit(unsigned int, Branch*);
	// Fruit();
	unsigned int getLength(void);
	unsigned int getWeight(void);
	void growthFruit(void);
	void fadeFruit(void);
	void pluckFruit(void);
	Branch* getBranchPointer(void);

	//Note Helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	Fruit* getNext(void);
	void hookNext(Fruit*);
	void setBranchPointer(Branch*);


};
class Branch {
private:
	unsigned int length;
	unsigned int height;
	unsigned int weight;
	unsigned int childCount;
	Tree* parent;

	Fruit* first;
	Fruit* last;
	Fruit* next;

public:
	// Note required
	Branch();
	unsigned int getFruitsTotal(void);
	unsigned int getWeightTotal(void);
	unsigned int getHeight(void);
	unsigned int getLength(void);
	void growthBranch(void);
	void fadeBranch(void);
	void harvestBranch(unsigned int);
	void cutBranch(unsigned int);
	Fruit* getFruitPointer(unsigned int length); // Return fruit growing on distance of "length" from branch
	Tree* getTreePointer(void);

	// Note Helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void setWeightTotal(unsigned int);

};
class Tree {
private:
	unsigned int number;
	unsigned int height;
	unsigned int weight;
	unsigned int childCount;
	unsigned int fruitCount;
	Garden* parent;


public:
	// Note requied
	unsigned int getBranchesTotal(void);
	unsigned int getFruitsTotal(void);
	unsigned int getWeightTotal(void);
	unsigned int getNumber(void);
	unsigned int getHeight(void);
	void growthTree(void);
	void fadeTree(void);
	void harvestTree(unsigned int); // weight >=
	void cutTree(unsigned int); // new height
	void cloneBranch(Branch*);
	Garden* getGardenPointer();
	Branch* getBranchPointer();

	// Note helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void setWeightTotal(unsigned int);

};
class Garden {
private:
	unsigned int weight;
	unsigned int childCount;
	unsigned int branchCount;
	unsigned int fruitCount;
	Tree* first;
	Tree* last;

public:
	// Note required
	unsigned int getTreesTotal(void);
	unsigned int getBranchesTotal(void);
	unsigned int getFruitsTotal(void);
	unsigned int getWeightTotal(void);
	void plantTree(void);
	void extractTree(unsigned int);
	void growthTree(unsigned int);
	void fadeGarden(void);
	void harvestGaden(unsigned int);
	Tree* getTreePointer(unsigned int);
	void cloneTree(unsigned int);

	// Note helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);

};
// Section FRUIT_CLASS
Fruit::Fruit() {

}
void Fruit::addWeight(unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Fruit::subWeight(unsigned int delta) {
	if (this-> weight <= 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->subWeight(delta);
}

unsigned int Fruit::getLength(void) {
	return this->length;
}
unsigned int Fruit::getWeight(void) {
	return this->weight;
}
void Fruit::growthFruit(void) {
	this->addWeight(1);
}
void Fruit::fadeFruit(void) {
	this->subWeight(1);
}

void Fruit::pluckFruit(void) {
	this->subWeight(this->weight);
}
Branch* Fruit::getBranchPointer(void) {
	return this->parent;
}
Fruit* Fruit::getNext(void) {
	return this->next;
}
void Fruit::hookNext(Fruit* next) {
	this-> next = next;
}


// Section BRANCH_CLASS

unsigned int Branch::getFruitsTotal(void) {
	return this->childCount;
}
unsigned int Branch::getWeightTotal(void) {
	return this->weight;
}
unsigned int Branch::getHeight(void) {
	return this->height;
}
unsigned int Branch::getLength(void) {
	return this->length;
}
void Branch::growthBranch(void) {
	this->length++;

	for (Fruit* cur = first; cur != nullptr; cur = cur->getNext()) {
		cur->addWeight(1);
	}
	if (length == 0) {
		return;
	}
	if (length % 2 == 0) {
		// [ ] Pending
		Fruit* newFruit = new Fruit(length, this);
		if (first == nullptr) {
			first = newFruit;
		}
	}


}
void Branch::addWeight(unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Branch::subWeight(unsigned int delta) {
	if (this-> weight <= 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Branch::setWeightTotal(unsigned int weight) {
	this->weight = weight;
}


// Section TREE_CLASS
unsigned int Tree::getBranchesTotal(void) {
	return this->childCount;
}
unsigned int Tree::getFruitsTotal(void) {
	return this->fruitCount;
}
unsigned int Tree::getWeightTotal(void) {
	return this->weight;
}
unsigned int Tree::getNumber(void) {
	return this->number;
}
unsigned int Tree::getHeight(void) {
	return this->height;
}

void Tree::addWeight(unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Tree::subWeight(unsigned int delta) {
	if (this-> weight <= 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}

// Section GARDEN_CLASS 
void Garden::addWeight(unsigned int delta) {
	this->weight += delta;
}
void Garden::subWeight(unsigned int delta) {
	if (this-> weight <= 0) {
		return;
	}
	this->weight -= delta;
}




int main() {
	return 0;
}





