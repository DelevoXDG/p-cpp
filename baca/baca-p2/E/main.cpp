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

// [ ] Remove unused variables
// [ ] Remove [ ] and other symbols
// [ ] Add _CLASS
// [ ] Check names
// [ ] More...

// SECTION DECLARATIONS
class Fruit {
private:
	unsigned int weight;
	unsigned int length;

	Branch* parent;
	Fruit* next;
	Fruit* prev;

public:
	//Note Required
	Fruit();
	Fruit(unsigned int, Branch*, Fruit* = nullptr, Fruit* = nullptr);
	~Fruit();

	unsigned int getLength(void) { return this-> length; };
	unsigned int getWeight(void) { return this-> weight; };
	void growthFruit(void);
	void fadeFruit(void);
	void pluckFruit(void);
	Branch* getBranchPointer(void) { return this->parent; };

	//Note Helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);

	Fruit* getPrev(void) { return this->prev; };
	Fruit* getNext(void) { return this->next; };
	void hookNext(Fruit* next) { this->next = next; };
	void hookPrev(Fruit* prev) { this->prev = prev; };
	void setBranchPointer(Branch* parent) { this-> parent = parent; };

};
class Branch {
private:
	unsigned int length;
	unsigned int height;
	unsigned int weight;
	unsigned int fruitCount;
	Tree* parent;

	Fruit* first;
	Fruit* last;

	Branch* next;
	Branch* prev;

public:
	// Note required
	Branch();
	Branch(unsigned int, Tree*, Branch* = nullptr, Branch* = nullptr);
	~Branch();

	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightTotal(void) { return this->weight; }
	unsigned int getHeight(void) { return this->height; }
	unsigned int getLength(void) { return this->length; }
	void growthBranch(void);
	void fadeBranch(void);
	void harvestBranch(unsigned int);
	void cutBranch(unsigned int);
	Fruit* getFruitPointer(unsigned int length);// Return fruit growing on distance of "length" from branch
	Tree* getTreePointer(void) { return this->parent; }

	// Note Helpers
	void setWeightTotal(unsigned int);
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);
	void addBranchCount(const unsigned int);
	void subBranchCount(const unsigned int);

	Branch* getPrev(void) { return this->prev; }
	Branch* getNext(void) { return this->next; }
	void hookNext(Branch* next) { this->next = next; }
	void hookPrev(Branch* prev) { this->prev = prev; }
	void insertLast(const unsigned int);
	void deleteFruit(Fruit*);
	void removeHigherThan(const unsigned int);
};
class Tree {
private:
	unsigned int number;
	unsigned int height;
	unsigned int weight;
	unsigned int branchCount;
	unsigned int fruitCount;
	Garden* parent;

	Branch* first;
	Branch* last;
	Tree* next;
	Tree* prev;

public:
	// Note requied
	Tree();
	Tree(unsigned int, Garden*, Tree* = nullptr, Tree* = nullptr);
	~Tree();
	unsigned int getBranchesTotal(void) { return this->branchCount; }
	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightTotal(void) { return this->weight; }

	unsigned int getNumber(void) { return this->number; }
	unsigned int getHeight(void) { return this->height; }
	void growthTree(void);
	void fadeTree(void);
	void harvestTree(unsigned int); // weight >=
	void cutTree(unsigned int); // new height
	void cloneBranch(Branch*);
	Garden* getGardenPointer() { return this->parent; }
	Branch* getBranchPointer();

	// Note helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void setWeightTotal(unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);
	void addBranchCount(const unsigned int);
	void subBranchCount(const unsigned int);
	void addTreeCount(const unsigned int);
	void subTreeCount(const unsigned int);

};
class Garden {
private:
	unsigned int weight;
	unsigned int treeCount;
	unsigned int branchCount;
	unsigned int fruitCount;
	Tree* first;
	Tree* last;

public:
	// Note required
	Garden();
	~Garden();

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
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);
	void addBranchCount(const unsigned int);
	void subBranchCount(const unsigned int);
	void addTreeCount(const unsigned int);
	void subTreeCount(const unsigned int);

};
// Section FRUIT_CLASS
// [x] Fruits Done
Fruit::Fruit() : length(0), weight(0), parent(nullptr), next(nullptr), prev(nullptr) {
	this->addFruitCount(1);
}
Fruit::Fruit(unsigned int length, Branch* parent, Fruit* next, Fruit* prev) : length(length), parent(parent), next(next), prev(prev) {
	this->addFruitCount(1);
}
Fruit::~Fruit() {
	this->subFruitCount(1);
	this->subWeight(this->weight);
	parent = nullptr;
	next = nullptr;
	prev = nullptr;
	weight = 0;
	length = 0;
}

void Fruit::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Fruit::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->subWeight(delta);
}
void Fruit::addFruitCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	parent->addFruitCount(delta);
}
void Fruit::subFruitCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	parent->subFruitCount(delta);
}

// unsigned int Fruit::getLength(void) {
// 	return this->length;
// }
// unsigned int Fruit::getWeight(void) {
// 	return this->weight;
// }
void Fruit::growthFruit(void) {
	this->addWeight(1);
}
void Fruit::fadeFruit(void) {
	this->subWeight(1);
}

void Fruit::pluckFruit(void) {
	this->subWeight(this->weight);
}
// Branch* Fruit::getBranchPointer(void) {
// 	return this->parent;
// }
// Fruit* Fruit::getNext(void) {
// 	return this->next;
// }
// void Fruit::hookNext(Fruit* next) {
// 	this-> next = next;
// }


// Section BRANCH_CLASS
// [x] Branches done
// unsigned int Branch::getFruitsTotal(void) {
// 	return this->fruitCount;
// }
// unsigned int Branch::getWeightTotal(void) {
// 	return this->weight;
// }
// unsigned int Branch::getHeight(void) {
// 	return this->height;
// }
// unsigned int Branch::getLength(void) {
// 	return this->length;
// }
Branch::Branch() : length(0), height(0), weight(0), fruitCount(0), parent(nullptr), first(nullptr), last(nullptr), next(nullptr), prev(nullptr) {
	this->addBranchCount(1);
}
Branch::Branch(unsigned int height, Tree* parent, Branch* next, Branch* prev) : height(height), parent(parent), next(next), prev(prev) {
	this->first = nullptr;
	this->last = nullptr;
	this->addBranchCount(1);
}

void Branch::insertLast(const unsigned int length) {
	// if (last == nullptr) {
	// 	Fruit* newFruit = new Fruit(length, this, nullptr, nullptr);
	// 	first = newFruit;
	// 	last = newFruit;
	// 	return;
	// }
	Fruit* oldLast = this->last;
	this->last = new Fruit(length, this, nullptr, oldLast);
	if (oldLast == nullptr) {
		first = last;
	}
	else {
		oldLast->hookNext(last);
	}
}
void Branch::growthBranch(void) {
	this->length++;

	for (Fruit* cur = first; cur != nullptr; cur = cur->getNext()) {
		cur->addWeight(1);
	}

	if (length % 2 == 0) {
		// [x] Pending
		insertLast(length);
	}
}
void Branch::removeHigherThan(const unsigned int length) {
	Fruit* curFruit = this->last;
	// while (curFruit != nullptr && curFruit->getLength() > length) {
	// 	if (curFruit->getPrev() == nullptr) {

	// 	}
	// 	curFruit->getPrev()->hookNext(curFruit->getNext());

	// }
}
void Branch::deleteFruit(Fruit* node) {

	if (node == nullptr) {
		return;
	}
	if (this->first == nullptr || this->last == nullptr) {
		return;
	}
	Fruit* prev = node->getPrev();
	Fruit* next = node->getNext();

	if (prev == nullptr) {
		this->first = next;
		// next->hookPrev(nullptr);
	}
	else {
		prev->hookNext(next);
	}
	if (next == nullptr) {
		this->last = prev;
	}
	else {
		next->hookPrev(prev);
	}
	delete node;
	this->subFruitCount(1);
}

void Branch::fadeBranch(void) {
	if (this->length == 0) {
		return;
	}
	this->length--;
	if (fruitCount == 0) {
		return;
	}
	Fruit* curFruit = this->first;
	while (curFruit != nullptr) {
		Fruit* nextFruit = curFruit->getNext();
		curFruit->fadeFruit();
		if (curFruit->getLength() > this->length) {
			this->deleteFruit(curFruit);
		}
		curFruit = nextFruit;
	}
}
void Branch::harvestBranch(unsigned int minWeight) {
	for (Fruit* curFruit = first; curFruit != nullptr; curFruit = curFruit->getNext()) {
		if (curFruit->getWeight() >= minWeight) {
			curFruit->pluckFruit();
		}
	}
}

Fruit* Branch::getFruitPointer(unsigned int offset) {
	if (offset > this->length) {
		return nullptr;
	}
	if (offset <= 0) {
		return nullptr;
	}
	if (offset % 2 != 0) {
		return nullptr;
	}
	for (Fruit* curFruit = first; curFruit != nullptr; curFruit = curFruit->getNext()) {
		if (curFruit->getLength() == offset) {
			return curFruit;
		}
	}
	return nullptr;
}
void Branch::cutBranch(unsigned int newLength) {
	// [x] go from last for performance 
	Fruit* curFruit = this->last;
	while (curFruit != nullptr && curFruit->getLength() > newLength) {
		Fruit* nextFruit = curFruit->getPrev();
		deleteFruit(curFruit);
		curFruit = curFruit->getPrev();
	}
}

void Branch::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Branch::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
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
void Branch::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addFruitCount(delta);
}
void Branch::subFruitCount(const unsigned int delta) {
	if (fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->subFruitCount(delta);
}
void Branch::addBranchCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	parent->addFruitCount(delta);
}
void Branch::subBranchCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	parent->subFruitCount(delta);
}



// Section TREE_CLASS
// unsigned int Tree::getBranchesTotal(void) {
// 	return this->branchCount;
// }
// unsigned int Tree::getFruitsTotal(void) {
// 	return this->fruitCount;
// }
// unsigned int Tree::getWeightTotal(void) {
// 	return this->weight;
// }
// unsigned int Tree::getNumber(void) {
// 	return this->number;
// }
// unsigned int Tree::getHeight(void) {
// 	return this->height;
// }

Tree::Tree() :
	number(0), parent(0), height(0), weight(0), fruitCount(0), branchCount(0),
	next(nullptr), prev(nullptr),
	first(nullptr), last(nullptr) {
	this->addTreeCount(1);
}
Tree::Tree(unsigned int number, Garden* parent, Tree* next, Tree* prev) :
	number(number), parent(parent),
	next(next), prev(prev),
	height(0), weight(0), fruitCount(0), branchCount(0),
	first(nullptr), last(nullptr) {
	this->addTreeCount(1);
}


void Tree::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Tree::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addWeight(delta);
}
void Tree::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->addFruitCount(delta);
}
void Tree::subFruitCount(const unsigned int delta) {
	if (fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->subFruitCount(delta);
}
void Tree::addBranchCount(const unsigned int delta) {
	this->branchCount += delta;
	if (this->parent == nullptr) {
		return;
	}
	parent->addFruitCount(delta);
}
void Tree::subBranchCount(const unsigned int delta) {
	if (branchCount == 0) {
		return;
	}
	this->branchCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	parent->subFruitCount(delta);
}
void Tree::addTreeCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	parent->addFruitCount(delta);
}
void Tree::subTreeCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	parent->subFruitCount(delta);
}
void Tree ::growthTree(void) {
	this->height++;
	for (Branch* curBranch = first; curBranch != nullptr; curBranch = curBranch->getNext()) {
		curBranch->growthBranch();
	}


}



// Section GARDEN_CLASS
Garden::Garden() :
	weight(0), fruitCount(0), branchCount(0), treeCount(0), first(nullptr), last(nullptr) {
}

void Garden::addWeight(const unsigned int delta) {
	this->weight += delta;
}
void Garden::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;
}
void Garden::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;
}
void Garden::subFruitCount(const unsigned int delta) {
	if (fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;
}
void Garden::addBranchCount(const unsigned int delta) {
	this->branchCount += delta;
}
void Garden::subBranchCount(const unsigned int delta) {
	if (branchCount == 0) {
		return;
	}
	this->branchCount -= delta;
}
void Garden::addTreeCount(const unsigned int delta) {
	this->treeCount += delta;
}
void Garden::subTreeCount(const unsigned int delta) {
	if (treeCount == 0) {
		return;
	}
	this->treeCount -= delta;
}




int main() {
	return 0;
}





