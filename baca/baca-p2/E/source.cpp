// Maksim Zdobnikau

#include <iostream>
// #include <stddef.h>
#define nullptr 0
using namespace std;

class Fruit;
class Branch;
class Tree;
class Garden;

// [x] Remove unused variables
// [ ] Add _CLASS
// [ ] Check names
// [ ] Remove [ ] and other symbols
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
	Fruit(const Fruit&, Branch* = nullptr);
	~Fruit();

	unsigned int getLength(void) { return this-> length; };
	unsigned int getWeight(void) { return this-> weight; };
	void growthFruit(void);
	void fadeFruit(void);
	void pluckFruit(void);
	Branch* getBranchPointer(void) const { return this->parent; };

	//Note Helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);

	Fruit* getPrev(void) const { return this->prev; };
	Fruit* getNext(void) const { return this->next; };
	void hookNext(Fruit* next) { this->next = next; };
	void hookPrev(Fruit* prev) { this->prev = prev; };
	void setBranchPointer(Branch* parent) { this-> parent = parent; };

	void displayAll();


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
	Branch(const Branch&, Tree* = nullptr, unsigned int* = nullptr, Branch* = nullptr, Branch* = nullptr);
	~Branch();

	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightsTotal(void) { return this->weight; }
	unsigned int getHeight(void) { return this->height; }
	unsigned int getLength(void) { return this->length; }
	void growthBranch(void);
	void fadeBranch(void);
	void harvestBranch(unsigned int);
	void cutBranch(unsigned int);
	Fruit* getFruitPointer(unsigned int length);// Return fruit growing on distance of "length" from branch
	Tree* getTreePointer(void) const { return this->parent; }

	// Note Helpers
	void setWeightTotal(unsigned int);
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);
	void addBranchCount(const unsigned int);
	void subBranchCount(const unsigned int);

	Branch* getPrev(void) const { return this->prev; }
	Branch* getNext(void) const { return this->next; }
	void hookNext(Branch* next) { this->next = next; }
	void hookPrev(Branch* prev) { this->prev = prev; }
	void insertLastFruit(const unsigned int);
	void insertLastFruit(Fruit* newFruit);
	void deleteFruit(Fruit*);
	void removeHigherThan(const unsigned int);

	void displayAll();

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
	Tree(const Tree&, Garden* = nullptr, unsigned int* = nullptr, Tree* = nullptr, Tree* = nullptr);

	~Tree();
	unsigned int getBranchesTotal(void) { return this->branchCount; }
	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightsTotal(void) { return this->weight; }

	unsigned int getNumber(void) { return this->number; }
	unsigned int getHeight(void) { return this->height; }
	void growthTree(void);
	void fadeTree(void);
	void harvestTree(unsigned int); // weight >=
	void cutTree(unsigned int); // new height
	void cloneBranch(Branch*);
	Garden* getGardenPointer() { return this->parent; }
	Branch* getBranchPointer(unsigned int);

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

	Branch* getFirst(void) const { return this-> first; }
	Branch* getLast(void) const { return this-> last; }
	Tree* getPrev(void) const { return this->prev; }
	Tree* getNext(void) const { return this->next; }
	void hookNext(Tree* next) { this->next = next; }
	void hookPrev(Tree* prev) { this->prev = prev; }
	void insertLastBranch(const unsigned int);
	void deleteBranch(Branch*);

	void displayAll();


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

	unsigned int getTreesTotal(void) { return this->treeCount; }
	unsigned int getBranchesTotal(void) { return this->branchCount; }
	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightsTotal(void) { return this->weight; }
	void plantTree(void);
	void extractTree(unsigned int);
	void growthGarden(void);
	void fadeGarden(void);
	void harvestGarden(unsigned int);
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
	void deleteTree(Tree*);
	Tree* findTreeBeforeGap();

	void displayAll();


};
// Section Fruit
// [x] Fruits Done
Fruit::Fruit() :
	length(0), weight(0), parent(nullptr), next(nullptr), prev(nullptr) {
	this->addFruitCount(1);
}
Fruit::Fruit(unsigned int length, Branch* parent, Fruit* next, Fruit* prev) :
	weight(0),
	length(length), parent(parent), next(next), prev(prev) {
	this->addFruitCount(1);
}
Fruit::Fruit(const Fruit& source, Branch* newParent) :
	weight(0), length(source.length), next(source.next), prev(source.prev) {
	if (newParent == nullptr) {
		this->parent = source.parent;
	}
	else {
		this->parent = newParent;
	}
	this->addFruitCount(1);
	this->addWeight(source.weight);
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
	this->parent->addWeight(delta);
}
void Fruit::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subWeight(delta);
}
void Fruit::addFruitCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addFruitCount(delta);
}
void Fruit::subFruitCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->subFruitCount(delta);
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
// Section Branch
Branch::Branch() :
	length(0), height(0), weight(0), fruitCount(0), parent(nullptr), first(nullptr), last(nullptr), next(nullptr), prev(nullptr) {
	this->addBranchCount(1);
}
Branch::Branch(unsigned int height, Tree* parent, Branch* next, Branch* prev) :
	height(height), parent(parent),
	next(next), prev(prev),
	weight(0), fruitCount(0), length(0)
{
	this->first = nullptr;
	this->last = nullptr;
	this->addBranchCount(1);
}
Branch::Branch(const Branch& source, Tree* parent, unsigned int* height, Branch* next, Branch* prev) :
	length(source.length), height(source.height), parent(source.parent), next(next), prev(prev),
	weight(0), fruitCount(source.fruitCount),
	first(nullptr), last(nullptr)
{
	   // Note override copying
	if (parent != nullptr) { 		// Might be cloning branch from other tree
		this->parent = parent;
	}
	if (height != nullptr) {
		this->height = *height;
	}

	this->addBranchCount(1);
	if (this->fruitCount == 0) {
		return;
	}

	this->fruitCount = 0;
	// FIXME
	Fruit* curSource = source.first;
	Fruit* curNew = nullptr;
	curNew = new Fruit(*curSource, this);
	Fruit* prevNew = nullptr;

	this->first = curNew;
	prevNew = curNew;
	curSource = curSource->getNext();

	while (curSource != nullptr) {
		curNew = new Fruit(*curSource, this);
		curNew->hookPrev(prevNew);
		prevNew->hookNext(curNew);
		prevNew = curNew;
		curSource = curSource->getNext();
	}
	prevNew->hookNext(nullptr);
	this->last = prevNew;

}
Branch::~Branch() {
	Fruit* curFruit = this->first;
	while (curFruit != nullptr) {
		Fruit* nextFruit = curFruit->getNext();
		deleteFruit(curFruit);
		curFruit = nullptr;
		curFruit = nextFruit;
	}
	this->subBranchCount(1);
	this->weight = 0;
	this->fruitCount = 0;
	this->length = 0;
	this->height = 0;
	this->first = nullptr;
	this->last = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
	this->parent = nullptr;

}

void Branch::insertLastFruit(const unsigned int length) {
	Fruit* oldLast = this->last;
	this->last = new Fruit(length, this, nullptr, oldLast);
	if (oldLast == nullptr) {
		this->first = this->last;
	}
	else {
		oldLast->hookNext(last);
	}
}
void Branch::insertLastFruit(Fruit* newFruit) {
	Fruit* oldLast = this->last;
	this->last = newFruit;
	if (oldLast == nullptr) {
		this->first = this->last;
	}
	else {
		oldLast->hookNext(this->last);
	}
}

void Branch::growthBranch(void) {
	this->length++;

	for (Fruit* cur = this->first; cur; cur = cur->getNext()) {
		cur->growthFruit();
	}
	if (length % 2 == 0) {
		// [x] Pending
		this->insertLastFruit(this->length);
	}
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

	// this->subFruitCount(1);
	delete node;
	node = nullptr;

}

void Branch::fadeBranch(void) {
	if (this->length == 0) {
		return;
	}
	this->length--;
	if (this->fruitCount == 0) {
		return;
	}
	Fruit* curFruit = this->first;
	while (curFruit != nullptr) {
		Fruit* nextFruit = curFruit->getNext();
		curFruit->fadeFruit();
		if (curFruit->getLength() > this->length) {
			this->deleteFruit(curFruit);
			curFruit = nullptr;
		}
		curFruit = nextFruit;
	}
}
void Branch::harvestBranch(unsigned int minWeight) {
	if (this->fruitCount == 0) {
		return;
	}
	for (Fruit* curFruit = this->first; curFruit; curFruit = curFruit->getNext()) {
		if (curFruit->getWeight() >= minWeight) {
			curFruit->pluckFruit();
		}
	}
}

Fruit* Branch::getFruitPointer(unsigned int offset) {
	if (offset > this->length) {
		return nullptr;
	}
	if (offset % 2 != 0) {
		return nullptr;
	}
	for (Fruit* curFruit = this->last; curFruit; curFruit = curFruit->getPrev()) {
		if (curFruit->getLength() == offset) {
			return curFruit;
		}
	}
	return nullptr;
}
void Branch::cutBranch(unsigned int newLength) {
	this->length = newLength;
	// [x] go from last for performance 
	// [ ] pending check
	Fruit* curFruit = this->last;
	while (curFruit != nullptr && curFruit->getLength() > newLength) {
		Fruit* nextFruit = curFruit->getPrev();
		deleteFruit(curFruit);
		curFruit = nullptr;
		curFruit = nextFruit;
	}
}

void Branch::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addWeight(delta);
}
void Branch::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subWeight(delta);
}
void Branch::setWeightTotal(unsigned int weight) {
	this->weight = weight;
}
void Branch::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addFruitCount(delta);
}
void Branch::subFruitCount(const unsigned int delta) {
	if (fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subFruitCount(delta);
}
void Branch::addBranchCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addBranchCount(delta);
}
void Branch::subBranchCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->subBranchCount(delta);
}



// Section Tree
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
Tree::Tree(const Tree& source, Garden* parent, unsigned int* number, Tree* next, Tree* prev) :
	number(source.number), height(source.height),
	parent(parent),
	fruitCount(0), weight(0), branchCount(source.branchCount),
	first(nullptr), last(nullptr),
	next(next), prev(prev)
{
	if (parent != nullptr) { 		// Might be cloning branch from other tree
		this->parent = parent;
	}
	if (number != nullptr) {
		this->number = *number;
	}
	this->addTreeCount(1);
	if (this->branchCount == 0) {
		return;
	}

	this->branchCount = 0;
	this->fruitCount = 0;
	Branch* curNew = nullptr;
	Branch* curSource = nullptr;
	Branch* prevNew = nullptr;

	curSource = source.first;
	curNew = new Branch(*curSource, this);
	this->first = curNew;
	prevNew = curNew;
	curSource = curSource->getNext();

	while (curSource != nullptr) {
		// nextSource = curSource->getNext();
		curNew = new Branch(*curSource, this);
		curNew->hookPrev(prevNew);
		prevNew->hookNext(curNew);
		prevNew = curNew;
		curSource = curSource->getNext();
	}
	prevNew->hookNext(nullptr);
	this->last = prevNew;
}
Tree::~Tree() {
	Branch* curBranch = this->first;
	while (curBranch != nullptr) {
		Branch* nextBranch = curBranch->getNext();
		deleteBranch(curBranch);
		curBranch = nullptr;

		curBranch = nextBranch;
	}
	this->subTreeCount(1);
	this->number = 0;
	this->weight = 0;
	this->fruitCount = 0;
	this->branchCount = 0;
	this->height = 0;
	this->first = nullptr;
	this->last = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
	this->parent = nullptr;
}


void Tree::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addWeight(delta);
}
void Tree::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subWeight(delta);
}
void Tree::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addFruitCount(delta);
}
void Tree::subFruitCount(const unsigned int delta) {
	if (this->fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subFruitCount(delta);
}
void Tree::addBranchCount(const unsigned int delta) {
	this->branchCount += delta;
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addBranchCount(delta);
}
void Tree::subBranchCount(const unsigned int delta) {
	if (this->branchCount == 0) {
		return;
	}
	this->branchCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subBranchCount(delta);
}
void Tree::addTreeCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addTreeCount(delta);
}
void Tree::subTreeCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->subTreeCount(delta);
}
void Tree::insertLastBranch(const unsigned int height) {
	Branch* oldLast = this->last;
	this->last = new Branch(height, this, nullptr, oldLast);
	if (oldLast == nullptr) {
		this->first = this->last;
	}
	else {
		oldLast->hookNext(this->last);
	}
}
void Tree ::growthTree(void) {
	this->height++;
	for (Branch* curBranch = first; curBranch; curBranch = curBranch->getNext()) {
		curBranch->growthBranch();
	}
	if (this->height % 3 == 0) {
		this->insertLastBranch(this->height);
	}
}
void Tree::fadeTree(void) {
	if (this->height == 0) {
		return;
	}
	this->height--;
	if (this->branchCount == 0) {
		return;
	}
	Branch* curBranch = this->first;
	while (curBranch != nullptr) {
		Branch* nextBranch = curBranch->getNext();
		curBranch->fadeBranch();
		if (curBranch->getHeight() > this->height) {
			this->deleteBranch(curBranch);
			curBranch = nullptr;
		}
		curBranch = nextBranch;
	}
}
void Tree:: harvestTree(unsigned int minWeight) {
	if (this->branchCount == 0) {
		return;
	}
	for (Branch* curBranch = this->first; curBranch; curBranch = curBranch->getNext()) {
		curBranch->harvestBranch(minWeight);
	}
}
void Tree::deleteBranch(Branch* node) {
	if (node == nullptr) {
		return;
	}
	if (this->first == nullptr || this->last == nullptr) {
		return;
	}
	Branch* prev = node->getPrev();
	Branch* next = node->getNext();

	if (node == this->first) {
		this->first = nullptr;
	}
	if (node == this->last) {
		this->last = nullptr;
	}


	if (prev == nullptr) {
		this->first = next;
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
	node = nullptr;
}
void Tree::cutTree(unsigned int newHeight) {
	this->height = newHeight;

	Branch* curBranch = this->last;
	while (curBranch != nullptr && curBranch->getHeight() > newHeight) {
		Branch* nextBranch = curBranch->getPrev();
		deleteBranch(curBranch);
		curBranch = nullptr;
		curBranch = nextBranch;
	}
}

void Tree:: cloneBranch(Branch* source) {
	if (source == nullptr) {
		return;
	}
	for (Branch* curBranch = this->first; curBranch; curBranch = curBranch->getNext()) {
		if (curBranch->getLength() == 0) {
			unsigned int curHeight = curBranch->getHeight();
			Branch* newBranch = new Branch(*source, this, &curHeight, curBranch->getNext(), curBranch->getPrev());
			if (newBranch->getPrev() != nullptr) {
				newBranch->getPrev()->hookNext(newBranch);
			}
			else {
				this->first = newBranch;
			}
			if (newBranch->getNext() != nullptr) {
				newBranch->getNext()->hookPrev(newBranch);
			}
			else {
				this->last = newBranch;
			}

			delete curBranch;
			curBranch = nullptr;
			curBranch = newBranch;

			return;
		}
	}
}
Branch* Tree::getBranchPointer(unsigned int distance) {
	if (distance > this->height) {
		return nullptr;
	}
	if (distance % 3 != 0) {
		return nullptr;
	}

	for (Branch* curBranch = this->last; curBranch; curBranch = curBranch->getPrev()) {
		if (curBranch->getHeight() == distance) {
			return curBranch;
		}
	}

	return nullptr;
}

// Section GARDEN_CLASS
Garden::Garden() :
	weight(0),
	fruitCount(0), branchCount(0), treeCount(0),
	first(nullptr), last(nullptr) {
}
Garden::~Garden() {
	Tree* curTree = this->first;
	while (curTree != nullptr) {
		Tree* nextTree = curTree->getNext();
		deleteTree(curTree);
		curTree = nullptr;
		curTree = nextTree;
	}
	this->subTreeCount(1);
	this->weight = 0;
	this->fruitCount = 0;
	this->branchCount = 0;
	this->treeCount = 0;
	this->first = nullptr;
	this->last = nullptr;
}
void Garden::deleteTree(Tree* node) {
	if (node == nullptr) {
		return;
	}
	if (this->first == nullptr || this->last == nullptr) {
		return;
	}
	Tree* prev = node->getPrev();
	Tree* next = node->getNext();

	if (prev == nullptr) {
		this->first = next;
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
	node = nullptr;
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
Tree* Garden::getTreePointer(unsigned int num) {
	if (this->last->getNumber() < num) {
		return nullptr;
	}
	for (Tree* curTree = this->last; curTree; curTree = curTree->getPrev()) {
		if (curTree->getNumber() == num) {
			return curTree;
		}
	}
	return nullptr;
}
Tree* Garden::findTreeBeforeGap() {

	Tree* curTree = this->first;
	if (curTree == nullptr) {
		return nullptr;
	}
	if (curTree->getNumber() > 0) {
		return nullptr;
	}

	Tree* prevTree = curTree;
	curTree = curTree->getNext();

	while (curTree != nullptr) {
		if (curTree->getNumber() - prevTree->getNumber() > 1) {
			return curTree->getPrev();
		}

		prevTree = curTree;
		curTree = curTree->getNext();
	}
	return this->last;
}

void Garden::plantTree(void) {
	Tree* treeBefore = findTreeBeforeGap();
	Tree* newTree = nullptr;
	if (treeBefore == nullptr) {
		newTree = new Tree(0, this, this->first, nullptr);
		this->first = newTree;
	}
	else {
		unsigned int gapNum = treeBefore->getNumber() + 1;
		newTree = new Tree(gapNum, this, treeBefore->getNext(), treeBefore);
		treeBefore->hookNext(newTree);
	}
	if (newTree->getNext() == nullptr) {
		this->last = newTree;
	}
	else {
		newTree->getNext()->hookPrev(newTree);
	}
}
void Garden::extractTree(unsigned int num) {
	Tree* deleteTree = this->getTreePointer(num);
	this->deleteTree(deleteTree);
	deleteTree = nullptr;
}
void Garden::growthGarden(void) {
	for (Tree* cur = this->first; cur; cur = cur->getNext()) {
		cur->growthTree();
	}
}
void Garden::fadeGarden(void) {
	for (Tree* cur = this->first; cur; cur = cur->getNext()) {
		cur->fadeTree();
	}
}
void Garden::harvestGarden(unsigned int minWeight) {
	for (Tree* cur = this->first; cur; cur = cur->getNext()) {
		cur->harvestTree(minWeight);
	}
}
void Garden::cloneTree(unsigned int num) {
	Tree* source = this->getTreePointer(num);
	if (source == nullptr) {
		return;
	}
	Tree* treeBefore = findTreeBeforeGap();
	Tree* newTree = nullptr;
	if (treeBefore == nullptr) {
		unsigned int gapNum = 0;
		newTree = new Tree(*source, this, &gapNum, this->first, nullptr);
		this->first = newTree;
	}
	else {
		unsigned int gapNum = treeBefore->getNumber() + 1;
		newTree = new Tree(*source, this, &gapNum, treeBefore->getNext(), treeBefore);
		treeBefore->hookNext(newTree);
	}
	if (newTree->getNext() == nullptr) {
		this->last = newTree;
	}
	else {
		newTree->getNext()->hookPrev(newTree);
	}
}

void Garden::displayAll() {
	std::cout << "GARDEN:" << std::endl;
	std::cout << "fruit_count:" << getFruitsTotal() << " ";
	std::cout << "tree_count:" << getTreesTotal() << " ";
	std::cout << "branch_count:" << getBranchesTotal() << " ";
	std::cout << "weights:" << getWeightsTotal() << std::endl;
	std::cout << "trees: \n";
	int max = getTreesTotal(), i = 0;
	while (i <= max) {
		Tree* tree = getTreePointer(i);
		if (tree != NULL) {
			std:: cout << "tree nr " << i << std::endl;
			tree->displayAll();
			std::cout << std::endl;
		}
		i++;
	}
	std::cout << std::endl;
	std::cout << "/ / / / / / / /";
	std::cout << std::endl << std::endl;
}

void Tree::displayAll() {
	std::cout << ">>fruit_count:" << getFruitsTotal() << " ";
	std::cout << "branch_count:" << getBranchesTotal() << " ";
	std::cout << "weights:" << getWeightsTotal() << std::endl;
	int max = getBranchesTotal(), i = 3;
	if (max > 0) std::cout << ">>branches: \n";
	while (i <= 3 * max) {
		Branch* branch = getBranchPointer(i);
		if (branch != NULL) {
			std:: cout << "-----branch at " << i << std::endl;
			branch->displayAll();
		}
		i += 3;
	}
}

void Branch::displayAll() {
	std::cout << "-----fruit_count:" << getFruitsTotal() << " ";
	std::cout << "weights:" << getWeightsTotal() << std::endl;
	int max = getFruitsTotal(), i = 2;
	if (max > 0) std::cout << "-----fruits: \n";
	while (i <= 2 * max) {
		Fruit* fruit = getFruitPointer(i);
		if (fruit != NULL) {
			std:: cout << "*fruit at " << i << std::endl;
			std::cout << "*length: " << fruit->getLength() << " weight: " << fruit->getWeight() << std::endl;
		}
		i += 2;
	}
}



// int main() {

// 	//testy na wycieki pamieci

// 	Garden* GARDEN = new Garden();
// 	GARDEN->plantTree();
// 	GARDEN->plantTree();
// 	GARDEN->plantTree();
// 	GARDEN->plantTree();
// 	GARDEN->extractTree(2);
// 	GARDEN->displayAll();

// 	GARDEN->plantTree();
// 	GARDEN->growthGarden();
// 	GARDEN->plantTree();
// 	GARDEN->growthGarden();
// 	GARDEN->plantTree();
// 	GARDEN->growthGarden();
// 	GARDEN->plantTree();
// 	GARDEN->growthGarden();
// 	GARDEN->plantTree();
// 	GARDEN->plantTree();
// 	GARDEN->growthGarden();
// 	GARDEN->displayAll();

// 	GARDEN->extractTree(3);
// 	GARDEN->extractTree(3);
// 	GARDEN->growthGarden();
// 	GARDEN->growthGarden();
// 	GARDEN->fadeGarden();
// 	GARDEN->fadeGarden();
// 	GARDEN->fadeGarden();
// 	GARDEN->fadeGarden();
// 	GARDEN->growthGarden();
// 	GARDEN->growthGarden();
// 	GARDEN->growthGarden();
// 	GARDEN->displayAll();

// 	GARDEN->harvestGarden(3);
// 	GARDEN->cloneTree(3);
// 	GARDEN->cloneTree(1);
// 	GARDEN->cloneTree(8);
// 	GARDEN->growthGarden();
// 	GARDEN->growthGarden();
// 	GARDEN->displayAll();

// 	delete GARDEN;

// 	Tree* TREE = new Tree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->displayAll();
// 	std::cout << std::endl;

// 	TREE->cutTree(3);
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->displayAll();

// 	delete TREE;

// }
// int main() {
// 	Garden* garden = new Garden();
// 	garden->plantTree();
// 	garden->plantTree();
// 	garden->plantTree();
// 	garden->plantTree();
// 	garden->extractTree(2);
// 	garden->plantTree();
// 	garden->growthGarden();
// 	garden->plantTree();
// 	garden->growthGarden();
// 	garden->plantTree();
// 	garden->growthGarden();
// 	garden->plantTree();
// 	garden->growthGarden();
// 	garden->plantTree();
// 	garden->plantTree();
// 	garden->growthGarden();
// 	garden->extractTree(3);
// 	garden->extractTree(3);
// 	garden->displayAll();
// 	garden->growthGarden();
// 	garden->growthGarden();
// 	garden->fadeGarden();
// 	garden->fadeGarden();
// 	garden->fadeGarden();
// 	garden->fadeGarden();
// 	garden->growthGarden();
// 	garden->growthGarden();
// 	garden->growthGarden();
// 	garden->growthGarden();
// 	garden->harvestGarden(3);
// 	garden->cloneTree(3);
// 	garden->cloneTree(1);
// 	garden->cloneTree(8);
// 	garden->displayAll();
// 	garden->getTreePointer(3)->cutTree(1);
// 	garden->getTreePointer(1)->cutTree(5);
// 	garden->extractTree(3);
// 	garden->harvestGarden(2);
// 	garden->getTreePointer(2)->growthTree();
// 	garden->getTreePointer(2)->growthTree();
// 	garden->fadeGarden();
// 	garden->displayAll();
// 	delete garden;
// }

// int main() {
// 	Tree* TREE = new Tree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->displayAll();

// 	std::cout << "///////" << std::endl;

// 	TREE->getBranchPointer(6)->fadeBranch();
// 	TREE->getBranchPointer(6)->fadeBranch();
// 	TREE->getBranchPointer(6)->fadeBranch();
// 	TREE->getBranchPointer(6)->fadeBranch();
// 	TREE->getBranchPointer(6)->fadeBranch();
// 	TREE->displayAll();

// 	std::cout << "///////" << std::endl;

// 	TREE->cloneBranch(TREE->getBranchPointer(3));
// 	TREE->displayAll();
// 	delete TREE;
// }


// int main() {
// 	Tree* TREE = new Tree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->growthTree();
// 	TREE->displayAll();
// 	std::cout << "///////" << std::endl << std::endl;
// 	TREE->getBranchPointer(3)->fadeBranch();
// 	TREE->getBranchPointer(3)->fadeBranch();
// 	TREE->getBranchPointer(3)->fadeBranch();
// 	TREE->getBranchPointer(3)->fadeBranch();
// 	TREE->getBranchPointer(3)->fadeBranch();
// 	TREE->getBranchPointer(3)->fadeBranch();
// 	TREE->getBranchPointer(3)->fadeBranch();
// 	TREE->displayAll();
// 	std::cout << "///////" << std::endl << std::endl;
// 	TREE->cloneBranch(
// 		TREE->getBranchPointer(6)
// 	);
// 	TREE->displayAll();
// 	delete TREE;
// }