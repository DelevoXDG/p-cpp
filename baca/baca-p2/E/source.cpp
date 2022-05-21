// Maksim Zdobnikau

#include <iostream>
#define nullptr 0

class FRUIT_CLASS;
class BRANCH_CLASS;
class TREE_CLASS;
class GARDEN_CLASS;

// SECTION DECLARATIONS
class FRUIT_CLASS {
private:
	unsigned int weight;
	unsigned int length;
	BRANCH_CLASS* parent;

	FRUIT_CLASS* next;
	FRUIT_CLASS* prev;

public:
	//Note Required
	FRUIT_CLASS();
	FRUIT_CLASS(unsigned int, BRANCH_CLASS*, FRUIT_CLASS* = nullptr, FRUIT_CLASS* = nullptr);
	FRUIT_CLASS(const FRUIT_CLASS&, BRANCH_CLASS* = nullptr);
	~FRUIT_CLASS();

	unsigned int getLength(void) { return this-> length; };
	unsigned int getWeight(void) { return this-> weight; };
	void growthFruit(void);
	void fadeFruit(void);
	void pluckFruit(void);
	BRANCH_CLASS* getBranchPointer(void) const { return this->parent; };

	//Note Helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);

	FRUIT_CLASS* getPrev(void) { return this->prev; };
	FRUIT_CLASS* getNext(void) { return this->next; };
	void hookNext(FRUIT_CLASS* next) { this->next = next; };
	void hookPrev(FRUIT_CLASS* prev) { this->prev = prev; }

};
class BRANCH_CLASS {
private:
	unsigned int length;
	unsigned int height;
	unsigned int weight;
	unsigned int fruitCount;
	TREE_CLASS* parent;

	FRUIT_CLASS* first;
	FRUIT_CLASS* last;

	BRANCH_CLASS* next;
	BRANCH_CLASS* prev;

public:
	// Note required
	BRANCH_CLASS();
	BRANCH_CLASS(unsigned int, TREE_CLASS*, BRANCH_CLASS* = nullptr, BRANCH_CLASS* = nullptr);
	BRANCH_CLASS(const BRANCH_CLASS&, TREE_CLASS* = nullptr, unsigned int* = nullptr, BRANCH_CLASS* = nullptr, BRANCH_CLASS* = nullptr);
	~BRANCH_CLASS();

	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightsTotal(void) { return this->weight; }
	unsigned int getHeight(void) { return this->height; }
	unsigned int getLength(void) { return this->length; }
	void growthBranch(void);
	void fadeBranch(void);
	void harvestBranch(unsigned int);
	void cutBranch(unsigned int);
	FRUIT_CLASS* getFruitPointer(unsigned int); // Return fruit growing on distance of "length" from branch
	TREE_CLASS* getTreePointer(void) { return this->parent; }

	// Note Helpers
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);
	void addBranchCount(const unsigned int);
	void subBranchCount(const unsigned int);

	BRANCH_CLASS* getPrev(void) { return this->prev; }
	BRANCH_CLASS* getNext(void) { return this->next; }
	void hookNext(BRANCH_CLASS* next) { this->next = next; }
	void hookPrev(BRANCH_CLASS* prev) { this->prev = prev; }
	void insertLastFruit(const unsigned int);
	void insertLastFruit(FRUIT_CLASS* newFruit);
	void deleteFruit(FRUIT_CLASS*);
	void removeHigherThan(const unsigned int);
};
class TREE_CLASS {
private:
	unsigned int number;
	unsigned int height;
	unsigned int weight;
	unsigned int fruitCount;
	unsigned int branchCount;
	GARDEN_CLASS* parent;

	BRANCH_CLASS* first;
	BRANCH_CLASS* last;

	TREE_CLASS* next;
	TREE_CLASS* prev;

public:
	// Note requied
	TREE_CLASS();
	TREE_CLASS(unsigned int, GARDEN_CLASS*, TREE_CLASS* = nullptr, TREE_CLASS* = nullptr);
	TREE_CLASS(const TREE_CLASS&, GARDEN_CLASS* = nullptr, unsigned int* = nullptr, TREE_CLASS* = nullptr, TREE_CLASS* = nullptr);
	~TREE_CLASS();

	unsigned int getBranchesTotal(void) { return this->branchCount; }
	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightsTotal(void) { return this->weight; }

	unsigned int getNumber(void) { return this->number; }
	unsigned int getHeight(void) { return this->height; }
	void growthTree(void);
	void fadeTree(void);
	void harvestTree(unsigned int); // weight >=
	void cutTree(unsigned int); // new height
	void cloneBranch(BRANCH_CLASS*);
	GARDEN_CLASS* getGardenPointer() { return this->parent; }
	BRANCH_CLASS* getBranchPointer(unsigned int);

	// Note helpers
	void addGapCount(const unsigned int);
	void subGapCount(const unsigned int);
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);
	void addBranchCount(const unsigned int);
	void subBranchCount(const unsigned int);
	void addTreeCount(const unsigned int);
	void subTreeCount(const unsigned int);

	TREE_CLASS* getPrev(void) { return this->prev; }
	TREE_CLASS* getNext(void) { return this->next; }
	void hookNext(TREE_CLASS* next) { this->next = next; }
	void hookPrev(TREE_CLASS* prev) { this->prev = prev; }
	void insertLastBranch(const unsigned int);
	void deleteBranch(BRANCH_CLASS*);
};
class GARDEN_CLASS {
private:
	unsigned int weight;
	unsigned int fruitCount;
	unsigned int branchCount;
	unsigned int treeCount;
	unsigned int gapCount;

	TREE_CLASS* first;
	TREE_CLASS* last;

public:
	// Note required
	GARDEN_CLASS();
	~GARDEN_CLASS();

	unsigned int getTreesTotal(void) { return this->treeCount; }
	unsigned int getBranchesTotal(void) { return this->branchCount; }
	unsigned int getFruitsTotal(void) { return this->fruitCount; }
	unsigned int getWeightsTotal(void) { return this->weight; }
	void plantTree(void);
	void extractTree(unsigned int);
	void growthGarden(void);
	void fadeGarden(void);
	void harvestGarden(unsigned int);
	TREE_CLASS* getTreePointer(unsigned int);
	void cloneTree(unsigned int);

	// Note helpers
	void addGapCount(const unsigned int);
	void subGapCount(const unsigned int);
	void addWeight(const unsigned int);
	void subWeight(const unsigned int);
	void addFruitCount(const unsigned int);
	void subFruitCount(const unsigned int);
	void addBranchCount(const unsigned int);
	void subBranchCount(const unsigned int);
	void addTreeCount(const unsigned int);
	void subTreeCount(const unsigned int);
	void deleteTree(TREE_CLASS*);
	TREE_CLASS* findTreeBeforeGap(void);
};


// Section Fruit
FRUIT_CLASS::FRUIT_CLASS() :
	length(0), weight(0), parent(nullptr), next(nullptr), prev(nullptr) {
	this->addFruitCount(1);
}
FRUIT_CLASS::FRUIT_CLASS(unsigned int length, BRANCH_CLASS* parent, FRUIT_CLASS* next, FRUIT_CLASS* prev) :
	weight(0),
	length(length), parent(parent), next(next), prev(prev) {
	this->addFruitCount(1);
}
FRUIT_CLASS::FRUIT_CLASS(const FRUIT_CLASS& source, BRANCH_CLASS* newParent) :
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

FRUIT_CLASS::~FRUIT_CLASS() {
	this->subFruitCount(1);
	this->subWeight(this->weight);
	this->parent = nullptr;
	this->next = nullptr;
	this->prev = nullptr;
	this->weight = 0;
	this->length = 0;
}

void FRUIT_CLASS::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addWeight(delta);
}
void FRUIT_CLASS::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subWeight(delta);
}
void FRUIT_CLASS::addFruitCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addFruitCount(delta);
}
void FRUIT_CLASS::subFruitCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->subFruitCount(delta);
}
void FRUIT_CLASS::growthFruit(void) {
	this->addWeight(1);
}
void FRUIT_CLASS::fadeFruit(void) {
	this->subWeight(1);
}
void FRUIT_CLASS::pluckFruit(void) {
	this->subWeight(this->weight);
}
// Section Branch
BRANCH_CLASS::BRANCH_CLASS() :
	length(0), height(0), weight(0), fruitCount(0), parent(nullptr), first(nullptr), last(nullptr), next(nullptr), prev(nullptr) {
	this->addBranchCount(1);
}
BRANCH_CLASS::BRANCH_CLASS(unsigned int height, TREE_CLASS* parent, BRANCH_CLASS* next, BRANCH_CLASS* prev) :
	height(height), parent(parent),
	next(next), prev(prev),
	weight(0), fruitCount(0), length(0)
{
	this->first = nullptr;
	this->last = nullptr;
	this->addBranchCount(1);
}
BRANCH_CLASS::BRANCH_CLASS(const BRANCH_CLASS& source, TREE_CLASS* parent, unsigned int* height, BRANCH_CLASS* next, BRANCH_CLASS* prev) :
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
	FRUIT_CLASS* curNew = nullptr;
	FRUIT_CLASS* curSource = nullptr;
	FRUIT_CLASS* prevNew = nullptr;

	curSource = source.first;
	curNew = new FRUIT_CLASS(*curSource, this);

	this->first = curNew;
	prevNew = curNew;
	curSource = curSource->getNext();

	while (curSource != nullptr) {
		curNew = new FRUIT_CLASS(*curSource, this);
		curNew->hookPrev(prevNew);
		prevNew->hookNext(curNew);
		prevNew = curNew;
		curSource = curSource->getNext();
	}
	prevNew->hookNext(nullptr);
	this->last = prevNew;

}
BRANCH_CLASS::~BRANCH_CLASS() {
	FRUIT_CLASS* curFruit = this->first;
	while (curFruit != nullptr) {
		FRUIT_CLASS* nextFruit = curFruit->getNext();
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

void BRANCH_CLASS::insertLastFruit(const unsigned int length) {
	FRUIT_CLASS* oldLast = this->last;
	this->last = new FRUIT_CLASS(length, this, nullptr, oldLast);
	if (oldLast == nullptr) {
		this->first = this->last;
	}
	else {
		oldLast->hookNext(last);
	}
}
void BRANCH_CLASS::insertLastFruit(FRUIT_CLASS* newFruit) {
	FRUIT_CLASS* oldLast = this->last;
	this->last = newFruit;
	if (oldLast == nullptr) {
		this->first = this->last;
	}
	else {
		oldLast->hookNext(this->last);
	}
}

void BRANCH_CLASS::growthBranch(void) {
	this->length++;

	for (FRUIT_CLASS* cur = this->first; cur; cur = cur->getNext()) {
		cur->growthFruit();
	}
	if (this->length % 2 == 0) {
		this->insertLastFruit(this->length);
	}
}
void BRANCH_CLASS::deleteFruit(FRUIT_CLASS* node) {
	if (node == nullptr) {
		return;
	}

	FRUIT_CLASS* prev = node->getPrev();
	FRUIT_CLASS* next = node->getNext();

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
	// node = nullptr;

}

void BRANCH_CLASS::fadeBranch(void) {
	if (this->length == 0) {
		return;
	}
	this->length--;
	if (this->fruitCount == 0) {
		return;
	}
	FRUIT_CLASS* curFruit = this->first;
	while (curFruit != nullptr) {
		FRUIT_CLASS* nextFruit = curFruit->getNext();
		curFruit->fadeFruit();
		if (curFruit->getLength() > this->length) {
			this->deleteFruit(curFruit);
			curFruit = nullptr;
		}
		curFruit = nextFruit;
	}
}
void BRANCH_CLASS::harvestBranch(unsigned int minWeight) {
	if (this->fruitCount == 0) {
		return;
	}
	for (FRUIT_CLASS* curFruit = this->first; curFruit; curFruit = curFruit->getNext()) {
		if (curFruit->getWeight() >= minWeight) {
			curFruit->pluckFruit();
		}
	}
}

FRUIT_CLASS* BRANCH_CLASS::getFruitPointer(unsigned int offset) {
	if (offset > this->length) {
		return nullptr;
	}
	if (offset % 2 != 0) {
		return nullptr;
	}
	for (FRUIT_CLASS* curFruit = this->last; curFruit; curFruit = curFruit->getPrev()) {
		if (curFruit->getLength() == offset) {
			return curFruit;
		}
	}
	return nullptr;
}
void BRANCH_CLASS::cutBranch(unsigned int newLength) {
	this->length = newLength;

	FRUIT_CLASS* curFruit = this->last;
	while (curFruit != nullptr && curFruit->getLength() > newLength) {
		FRUIT_CLASS* nextFruit = curFruit->getPrev();
		deleteFruit(curFruit);
		curFruit = nullptr;
		curFruit = nextFruit;
	}
}

void BRANCH_CLASS::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addWeight(delta);
}
void BRANCH_CLASS::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subWeight(delta);
}
void BRANCH_CLASS::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addFruitCount(delta);
}
void BRANCH_CLASS::subFruitCount(const unsigned int delta) {
	if (fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subFruitCount(delta);
}
void BRANCH_CLASS::addBranchCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addBranchCount(delta);
}
void BRANCH_CLASS::subBranchCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->subBranchCount(delta);
}



// Section Tree
TREE_CLASS::TREE_CLASS() :
	number(0), parent(0), height(0), weight(0), fruitCount(0), branchCount(0),
	next(nullptr), prev(nullptr),
	first(nullptr), last(nullptr) {
	this->addTreeCount(1);
}
TREE_CLASS::TREE_CLASS(unsigned int number, GARDEN_CLASS* parent, TREE_CLASS* next, TREE_CLASS* prev) :
	number(number), parent(parent),
	next(next), prev(prev),
	height(0), weight(0), fruitCount(0), branchCount(0),
	first(nullptr), last(nullptr) {
	this->addTreeCount(1);
}
TREE_CLASS::TREE_CLASS(const TREE_CLASS& source, GARDEN_CLASS* parent, unsigned int* number, TREE_CLASS* next, TREE_CLASS* prev) :
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
	BRANCH_CLASS* curNew = nullptr;
	BRANCH_CLASS* curSource = nullptr;
	BRANCH_CLASS* prevNew = nullptr;

	curSource = source.first;
	curNew = new BRANCH_CLASS(*curSource, this);

	this->first = curNew;
	prevNew = curNew;
	curSource = curSource->getNext();

	while (curSource != nullptr) {
		// nextSource = curSource->getNext();
		curNew = new BRANCH_CLASS(*curSource, this);
		curNew->hookPrev(prevNew);
		prevNew->hookNext(curNew);
		prevNew = curNew;
		curSource = curSource->getNext();
	}
	prevNew->hookNext(nullptr);
	this->last = prevNew;
}
TREE_CLASS::~TREE_CLASS() {
	BRANCH_CLASS* curBranch = this->last;
	while (curBranch != nullptr) {
		BRANCH_CLASS* nextBranch = curBranch->getPrev();
		deleteBranch(curBranch);

		curBranch = nextBranch;
	}
	if (this->next != nullptr) {
		this->addGapCount(1);
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
void TREE_CLASS::addGapCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addGapCount(delta);
}
void TREE_CLASS::subGapCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->subGapCount(delta);
}

void TREE_CLASS::addWeight(const unsigned int delta) {
	this->weight += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addWeight(delta);
}
void TREE_CLASS::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subWeight(delta);
}
void TREE_CLASS::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->addFruitCount(delta);
}
void TREE_CLASS::subFruitCount(const unsigned int delta) {
	if (this->fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subFruitCount(delta);
}
void TREE_CLASS::addBranchCount(const unsigned int delta) {
	this->branchCount += delta;
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addBranchCount(delta);
}
void TREE_CLASS::subBranchCount(const unsigned int delta) {
	if (this->branchCount == 0) {
		return;
	}
	this->branchCount -= delta;

	if (this->parent == nullptr) {
		return;
	}
	this->parent->subBranchCount(delta);
}
void TREE_CLASS::addTreeCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->addTreeCount(delta);
}
void TREE_CLASS::subTreeCount(const unsigned int delta) {
	if (this->parent == nullptr) {
		return;
	}
	this->parent->subTreeCount(delta);
}
void TREE_CLASS::insertLastBranch(const unsigned int height) {
	BRANCH_CLASS* oldLast = this->last;
	this->last = new BRANCH_CLASS(height, this, nullptr, oldLast);
	if (oldLast == nullptr) {
		this->first = this->last;
	}
	else {
		oldLast->hookNext(this->last);
	}
}
void TREE_CLASS ::growthTree(void) {
	this->height++;
	for (BRANCH_CLASS* curBranch = first; curBranch; curBranch = curBranch->getNext()) {
		curBranch->growthBranch();
	}
	if (this->height % 3 == 0) {
		this->insertLastBranch(this->height);
	}
}
void TREE_CLASS::fadeTree(void) {
	if (this->height == 0) {
		return;
	}
	this->height--;
	if (this->branchCount == 0) {
		return;
	}
	BRANCH_CLASS* curBranch = this->first;
	while (curBranch != nullptr) {
		BRANCH_CLASS* nextBranch = curBranch->getNext();
		curBranch->fadeBranch();
		if (curBranch->getHeight() > this->height) {
			this->deleteBranch(curBranch);
			curBranch = nullptr;
		}
		curBranch = nextBranch;
	}
}
void TREE_CLASS:: harvestTree(unsigned int minWeight) {
	if (this->branchCount == 0) {
		return;
	}
	for (BRANCH_CLASS* curBranch = this->first; curBranch; curBranch = curBranch->getNext()) {
		curBranch->harvestBranch(minWeight);
	}
}
void TREE_CLASS::deleteBranch(BRANCH_CLASS* node) {
	if (node == nullptr) {
		return;
	}

	BRANCH_CLASS* prev = node->getPrev();
	BRANCH_CLASS* next = node->getNext();


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
	// node = nullptr;
}
void TREE_CLASS::cutTree(unsigned int newHeight) {
	this->height = newHeight;

	BRANCH_CLASS* curBranch = this->last;
	while (curBranch != nullptr && curBranch->getHeight() > newHeight) {
		BRANCH_CLASS* nextBranch = curBranch->getPrev();
		deleteBranch(curBranch);
		curBranch = nullptr;
		curBranch = nextBranch;
	}
}

void TREE_CLASS:: cloneBranch(BRANCH_CLASS* source) {
	if (source == nullptr) {
		return;
	}
	for (BRANCH_CLASS* curBranch = this->first; curBranch; curBranch = curBranch->getNext()) {
		if (curBranch->getLength() == 0) {
			unsigned int curHeight = curBranch->getHeight();
			BRANCH_CLASS* newBranch = new BRANCH_CLASS(*source, this, &curHeight, curBranch->getNext(), curBranch->getPrev());
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
BRANCH_CLASS* TREE_CLASS::getBranchPointer(unsigned int distance) {
	if (distance > this->height) {
		return nullptr;
	}
	if (distance % 3 != 0) {
		return nullptr;
	}
	for (BRANCH_CLASS* curBranch = this->last; curBranch; curBranch = curBranch->getPrev()) {
		if (curBranch->getHeight() == distance) {
			return curBranch;
		}
	}
	return nullptr;
}
// Section GARDEN_CLASS
GARDEN_CLASS::GARDEN_CLASS() :
	weight(0),
	fruitCount(0), branchCount(0), treeCount(0), gapCount(0),
	first(nullptr), last(nullptr) {
}
GARDEN_CLASS::~GARDEN_CLASS() {
	TREE_CLASS* curTree = this->first;
	while (curTree != nullptr) {
		TREE_CLASS* nextTree = curTree->getNext();
		deleteTree(curTree);
		curTree = nullptr;
		curTree = nextTree;
	}
	this->subTreeCount(1);
	this->weight = 0;
	this->fruitCount = 0;
	this->branchCount = 0;
	this->treeCount = 0;
	this->gapCount = 0;
	this->first = nullptr;
	this->last = nullptr;
}
void GARDEN_CLASS::deleteTree(TREE_CLASS* node) {
	if (node == nullptr) {
		return;
	}
	// if (this->first == nullptr || this->last == nullptr) {
	// 	return;
	// }
	TREE_CLASS* prev = node->getPrev();
	TREE_CLASS* next = node->getNext();

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
	// node = nullptr;
}
void GARDEN_CLASS::addGapCount(const unsigned int delta) {
	this->gapCount += delta;
}
void GARDEN_CLASS::subGapCount(const unsigned int delta) {
	this->gapCount -= delta;
}

void GARDEN_CLASS::addWeight(const unsigned int delta) {
	this->weight += delta;
}
void GARDEN_CLASS::subWeight(const unsigned int delta) {
	if (this-> weight == 0) {
		return;
	}
	this->weight -= delta;
}
void GARDEN_CLASS::addFruitCount(const unsigned int delta) {
	this->fruitCount += delta;
}
void GARDEN_CLASS::subFruitCount(const unsigned int delta) {
	if (fruitCount == 0) {
		return;
	}
	this->fruitCount -= delta;
}
void GARDEN_CLASS::addBranchCount(const unsigned int delta) {
	this->branchCount += delta;
}
void GARDEN_CLASS::subBranchCount(const unsigned int delta) {
	if (branchCount == 0) {
		return;
	}
	this->branchCount -= delta;
}
void GARDEN_CLASS::addTreeCount(const unsigned int delta) {
	this->treeCount += delta;
}
void GARDEN_CLASS::subTreeCount(const unsigned int delta) {
	if (treeCount == 0) {
		return;
	}
	this->treeCount -= delta;
}
TREE_CLASS* GARDEN_CLASS::getTreePointer(unsigned int num) {
	if (this->last->getNumber() < num) {
		return nullptr;
	}
	if (this->first->getNumber() == num) {
		return this->first;
	}
	for (TREE_CLASS* curTree = this->last; curTree; curTree = curTree->getPrev()) {
		if (curTree->getNumber() == num) {
			return curTree;
		}
	}
	return nullptr;
}
TREE_CLASS* GARDEN_CLASS::findTreeBeforeGap(void) {
	if (this->gapCount == 0) {
		return this->last;
	}
	TREE_CLASS* curTree = this->first;
	if (curTree == nullptr) {
		return nullptr;
	}
	if (curTree->getNumber() > 0) {
		return nullptr;
	}


	TREE_CLASS* prevTree = curTree;
	curTree = curTree->getNext();
	int counter = 0;
	while (curTree != nullptr) {
		counter++;
		if (counter > 100) {
			if (curTree == nullptr) {

				int a = 1;
				int b = 0;
				std::cout << a / b;
			}
		}
		if (curTree->getNumber() - prevTree->getNumber() > 1) {
			return curTree->getPrev();
		}

		prevTree = curTree;
		curTree = curTree->getNext();
	}
	return this->last;
}

void GARDEN_CLASS::plantTree(void) {

	TREE_CLASS* treeBefore = findTreeBeforeGap();
	TREE_CLASS* newTree = nullptr;

	if (treeBefore == nullptr) {
		newTree = new TREE_CLASS(0, this, this->first, nullptr);
		this->first = newTree;
	}
	else {
		unsigned int gapNum = treeBefore->getNumber() + 1;
		newTree = new TREE_CLASS(gapNum, this, treeBefore->getNext(), treeBefore);
		treeBefore->hookNext(newTree);
	}
	if (newTree->getNext() == nullptr) {
		this->last = newTree;
	}
	else {
		newTree->getNext()->hookPrev(newTree);
	}
}
void GARDEN_CLASS::extractTree(unsigned int num) {
	TREE_CLASS* deleteTree = this->getTreePointer(num);
	this->deleteTree(deleteTree);
}
void GARDEN_CLASS::growthGarden(void) {
	for (TREE_CLASS* cur = this->first; cur; cur = cur->getNext()) {
		cur->growthTree();
	}
}
void GARDEN_CLASS::fadeGarden(void) {
	for (TREE_CLASS* cur = this->first; cur; cur = cur->getNext()) {
		cur->fadeTree();
	}
}
void GARDEN_CLASS::harvestGarden(unsigned int minWeight) {
	for (TREE_CLASS* cur = this->first; cur; cur = cur->getNext()) {
		cur->harvestTree(minWeight);
	}
}
void GARDEN_CLASS::cloneTree(unsigned int num) {
	TREE_CLASS* source = this->getTreePointer(num);
	if (source == nullptr) {
		return;
	}
	TREE_CLASS* treeBefore = findTreeBeforeGap();
	TREE_CLASS* newTree = nullptr;
	if (treeBefore == nullptr) {
		unsigned int gapNum = 0;
		newTree = new TREE_CLASS(*source, this, &gapNum, this->first, nullptr);
		this->first = newTree;
	}
	else {
		unsigned int gapNum = treeBefore->getNumber() + 1;
		newTree = new TREE_CLASS(*source, this, &gapNum, treeBefore->getNext(), treeBefore);
		treeBefore->hookNext(newTree);
	}
	if (newTree->getNext() == nullptr) {
		this->last = newTree;
	}
	else {
		newTree->getNext()->hookPrev(newTree);
	}
}

#include <iostream>
int main() {
	std::cout << "\n";
	/*
	FruitLengthWeight
	*/
	{
		std::cout << "----------------------------------------\n" << "FruitLengthWeight\n\n";

		FRUIT_CLASS* fruit = new FRUIT_CLASS();

		if (0 != fruit->getWeight()) { std::cout << "BLAD - #1\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (0 != fruit->getLength()) { std::cout << "BLAD - #2\n" << fruit->getLength() << "\n"; }
		else { std::cout << "OK - #2\n"; };

		delete fruit;
	}

	/*
	FruitGrowth
	*/
	{
		std::cout << "----------------------------------------\n" << "FruitGrowth\n\n";

		FRUIT_CLASS* fruit = new FRUIT_CLASS();

		if (0 != fruit->getWeight()) { std::cout << "BLAD - #1\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		fruit->growthFruit();
		if (1 != fruit->getWeight()) { std::cout << "BLAD - #2\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		fruit->growthFruit();
		fruit->growthFruit();
		fruit->growthFruit();
		if (4 != fruit->getWeight()) { std::cout << "BLAD - #3\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #3\n"; };

		delete fruit;
	}

	/*
	FruitFade
	*/
	{
		std::cout << "----------------------------------------\n" << "FruitFade\n\n";
		FRUIT_CLASS* fruit = new FRUIT_CLASS();

		if (0 != fruit->getWeight()) { std::cout << "BLAD - #1\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		fruit->growthFruit();
		fruit->growthFruit();
		fruit->growthFruit();
		fruit->growthFruit();
		if (4 != fruit->getWeight()) { std::cout << "BLAD - #2\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #2\n"; };

		fruit->fadeFruit();
		if (3 != fruit->getWeight()) { std::cout << "BLAD - #3\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #3\n"; };
		fruit->fadeFruit();
		fruit->fadeFruit();
		fruit->fadeFruit();
		if (0 != fruit->getWeight()) { std::cout << "BLAD - #4\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #4\n"; };

		fruit->fadeFruit();
		if (0 != fruit->getWeight()) { std::cout << "BLAD - #5\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #5\n"; };

		delete fruit;
	}

	/*
	FruitPluck
	*/
	{
		std::cout << "----------------------------------------\n" << "FruitPluck\n\n";
		FRUIT_CLASS* fruit = new FRUIT_CLASS();

		if (0 != fruit->getWeight()) { std::cout << "BLAD - #1\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		fruit->growthFruit();
		fruit->growthFruit();
		fruit->growthFruit();
		fruit->growthFruit();
		if (4 != fruit->getWeight()) { std::cout << "BLAD - #2\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		fruit->pluckFruit();
		if (0 != fruit->getWeight()) { std::cout << "BLAD - #3\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #3\n"; };
		fruit->pluckFruit();
		if (0 != fruit->getWeight()) { std::cout << "BLAD - #4\n" << fruit->getWeight() << "\n"; }
		else { std::cout << "OK - #4\n"; };

		delete fruit;
	}

	/*
	BranchConstructor
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchConstructor\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		if (0 != branch.getFruitsTotal()) { std::cout << "BLAD - #1\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #2\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
	}

	/*
	BranchGrowth
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchGrowth\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		if (0 != branch.getLength()) { std::cout << "BLAD - #1a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1a\n"; };
		if (0 != branch.getFruitsTotal()) { std::cout << "BLAD - #1b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #1b\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #1c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #1c\n"; };

		branch.growthBranch();
		if (1 != branch.getLength()) { std::cout << "BLAD - #2a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #2a\n"; };
		if (0 != branch.getFruitsTotal()) { std::cout << "BLAD - #2b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2b\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #2c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #2c\n"; };

		branch.growthBranch();
		if (2 != branch.getLength()) { std::cout << "BLAD - #3a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #3a\n"; };
		if (1 != branch.getFruitsTotal()) { std::cout << "BLAD - #3b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #3b\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #3c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3c\n"; };

		branch.growthBranch();
		if (3 != branch.getLength()) { std::cout << "BLAD - #4a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #4a\n"; };
		if (1 != branch.getFruitsTotal()) { std::cout << "BLAD - #4b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #4b\n"; };
		if (1 != branch.getWeightsTotal()) { std::cout << "BLAD - #4c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #4c\n"; };

		branch.growthBranch();
		if (4 != branch.getLength()) { std::cout << "BLAD - #5a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #5a\n"; };
		if (2 != branch.getFruitsTotal()) { std::cout << "BLAD - #5b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #5b\n"; };
		if (2 != branch.getWeightsTotal()) { std::cout << "BLAD - #5c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #5c\n"; };

		branch.growthBranch();
		if (5 != branch.getLength()) { std::cout << "BLAD - #6a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #6a\n"; };
		if (2 != branch.getFruitsTotal()) { std::cout << "BLAD - #6b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #6b\n"; };
		if (4 != branch.getWeightsTotal()) { std::cout << "BLAD - #6c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #6c\n"; };

		branch.growthBranch();
		if (6 != branch.getLength()) { std::cout << "BLAD - #7a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #7a\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #7b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #7b\n"; };
		if (6 != branch.getWeightsTotal()) { std::cout << "BLAD - #7c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #7c\n"; };

		branch.growthBranch();
		if (7 != branch.getLength()) { std::cout << "BLAD - #8a\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #8a\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #8b\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #8b\n"; };
		if (9 != branch.getWeightsTotal()) { std::cout << "BLAD - #8c\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #8c\n"; };
	}

	/*
	BranchHarvestMid
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchHarvestMid\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();

		branch.harvestBranch(3);

		if (7 != branch.getLength()) { std::cout << "BLAD - #1\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #2\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (1 != branch.getWeightsTotal()) { std::cout << "BLAD - #3\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };
	}

	/*
	BranchHarvestLast
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchHarvestLast\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();

		branch.harvestBranch(1);

		if (7 != branch.getLength()) { std::cout << "BLAD - #1\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #2\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #3\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };
	}

	/*
	BranchHarvestFirst
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchHarvestFirst\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();

		branch.harvestBranch(5);

		if (7 != branch.getLength()) { std::cout << "BLAD - #1\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #2\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (4 != branch.getWeightsTotal()) { std::cout << "BLAD - #3\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };
	}

	/*
	BranchCut
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchCut\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();

		if (7 != branch.getLength()) { std::cout << "BLAD - #1\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #2\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (9 != branch.getWeightsTotal()) { std::cout << "BLAD - #3\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };

		branch.cutBranch(6);
		if (6 != branch.getLength()) { std::cout << "BLAD - #4\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #4\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #5\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #5\n"; };
		if (9 != branch.getWeightsTotal()) { std::cout << "BLAD - #6\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #6\n"; };

		branch.cutBranch(3);
		if (3 != branch.getLength()) { std::cout << "BLAD - #7\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #7\n"; };
		if (1 != branch.getFruitsTotal()) { std::cout << "BLAD - #8\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #8\n"; };
		if (5 != branch.getWeightsTotal()) { std::cout << "BLAD - #9\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #9\n"; };

		branch.cutBranch(0);
		if (0 != branch.getLength()) { std::cout << "BLAD - #10\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #10\n"; };
		if (0 != branch.getFruitsTotal()) { std::cout << "BLAD - #11\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #11\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #12\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #12\n"; };
	}

	/*
	BranchFindFruit
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchFindFruit\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();

		if (7 != branch.getLength()) { std::cout << "BLAD - #1\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #2\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (9 != branch.getWeightsTotal()) { std::cout << "BLAD - #3\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };

		if (2 != branch.getFruitPointer(2)->getLength()) { std::cout << "BLAD - #4\n" << branch.getFruitPointer(2)->getLength() << "\n"; }
		else { std::cout << "OK - #4\n"; };
		if (4 != branch.getFruitPointer(4)->getLength()) { std::cout << "BLAD - #5\n" << branch.getFruitPointer(4)->getLength() << "\n"; }
		else { std::cout << "OK - #5\n"; };
		if (6 != branch.getFruitPointer(6)->getLength()) { std::cout << "BLAD - #6\n" << branch.getFruitPointer(6)->getLength() << "\n"; }
		else { std::cout << "OK - #6\n"; };

		if (branch.getFruitPointer(0)) { std::cout << "BLAD - #7\n" << branch.getFruitPointer(0) << "\n"; }
		else { std::cout << "OK - #7\n"; };
		if (branch.getFruitPointer(7)) { std::cout << "BLAD - #8\n" << branch.getFruitPointer(7) << "\n"; }
		else { std::cout << "OK - #8\n"; };
		if (branch.getFruitPointer(8)) { std::cout << "BLAD - #9\n" << branch.getFruitPointer(8) << "\n"; }
		else { std::cout << "OK - #9\n"; };
		if (branch.getFruitPointer(-1)) { std::cout << "BLAD - #10\n" << branch.getFruitPointer(-1) << "\n"; }
		else { std::cout << "OK - #10\n"; };
	}

	/*
	BranchFade
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchFade\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();

		if (7 != branch.getLength()) { std::cout << "BLAD - #1\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #2\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (9 != branch.getWeightsTotal()) { std::cout << "BLAD - #3\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };

		branch.fadeBranch();
		if (6 != branch.getLength()) { std::cout << "BLAD - #4\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #4\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #5\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #5\n"; };
		if (6 != branch.getWeightsTotal()) { std::cout << "BLAD - #6\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #6\n"; };

		branch.fadeBranch();
		if (5 != branch.getLength()) { std::cout << "BLAD - #7\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #7\n"; };
		if (2 != branch.getFruitsTotal()) { std::cout << "BLAD - #8\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #8\n"; };
		if (4 != branch.getWeightsTotal()) { std::cout << "BLAD - #9\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #9\n"; };

		branch.fadeBranch();
		if (4 != branch.getLength()) { std::cout << "BLAD - #10\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #10\n"; };
		if (2 != branch.getFruitsTotal()) { std::cout << "BLAD - #11\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #11\n"; };
		if (2 != branch.getWeightsTotal()) { std::cout << "BLAD - #12\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #12\n"; };

		branch.fadeBranch();
		if (3 != branch.getLength()) { std::cout << "BLAD - #13\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #13\n"; };
		if (1 != branch.getFruitsTotal()) { std::cout << "BLAD - #14\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #14\n"; };
		if (1 != branch.getWeightsTotal()) { std::cout << "BLAD - #15\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #15\n"; };

		branch.fadeBranch();
		if (2 != branch.getLength()) { std::cout << "BLAD - #16\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #16\n"; };
		if (1 != branch.getFruitsTotal()) { std::cout << "BLAD - #17\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #17\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #18\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #18\n"; };

		branch.fadeBranch();
		if (1 != branch.getLength()) { std::cout << "BLAD - #19\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #19\n"; };
		if (0 != branch.getFruitsTotal()) { std::cout << "BLAD - #20\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #20\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #21\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #21\n"; };

		branch.fadeBranch();
		if (0 != branch.getLength()) { std::cout << "BLAD - #22\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #22\n"; };
		if (0 != branch.getFruitsTotal()) { std::cout << "BLAD - #23\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #23\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #24\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #24\n"; };

		branch.fadeBranch();
		if (0 != branch.getLength()) { std::cout << "BLAD - #25\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #25\n"; };
		if (0 != branch.getFruitsTotal()) { std::cout << "BLAD - #26\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #26\n"; };
		if (0 != branch.getWeightsTotal()) { std::cout << "BLAD - #27\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #27\n"; };
	}

	/*
	BranchCopyConstructor
	*/
	{
		std::cout << "----------------------------------------\n" << "BranchCopyConstructor\n\n";
		BRANCH_CLASS branch = BRANCH_CLASS();

		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();
		branch.growthBranch();

		if (7 != branch.getLength()) { std::cout << "BLAD - #1\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #2\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (9 != branch.getWeightsTotal()) { std::cout << "BLAD - #3\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };

		BRANCH_CLASS branch2 = BRANCH_CLASS(branch);

		if (branch.getTreePointer() != branch2.getTreePointer()) { std::cout << "BLAD - #4\n" << branch.getTreePointer() << " " << branch2.getTreePointer() << "\n"; }
		else { std::cout << "OK - #4\n"; };

		branch2.growthBranch();
		if (8 != branch2.getLength()) { std::cout << "BLAD - #5\n" << branch2.getLength() << "\n"; }
		else { std::cout << "OK - #5\n"; };
		if (4 != branch2.getFruitsTotal()) { std::cout << "BLAD - #6\n" << branch2.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #6\n"; };
		if (12 != branch2.getWeightsTotal()) { std::cout << "BLAD - #7\n" << branch2.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #7\n"; };

		if (7 != branch.getLength()) { std::cout << "BLAD - #8\n" << branch.getLength() << "\n"; }
		else { std::cout << "OK - #8\n"; };
		if (3 != branch.getFruitsTotal()) { std::cout << "BLAD - #9\n" << branch.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #9\n"; };
		if (9 != branch.getWeightsTotal()) { std::cout << "BLAD - #10\n" << branch.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #10\n"; };
	}

	/*
	TreeConstructor
	*/
	{
		std::cout << "----------------------------------------\n" << "TreeConstructor\n\n";
		TREE_CLASS tree = TREE_CLASS();

		if (0 != tree.getHeight()) { std::cout << "BLAD - #1\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #2\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #3\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #4\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #4\n"; };
	}

	/*
	TreeGrowth
	*/
	{
		std::cout << "----------------------------------------\n" << "TreeGrowth\n\n";
		TREE_CLASS tree = TREE_CLASS();
		if (0 != tree.getHeight()) { std::cout << "BLAD - #1\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #2\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #3\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #4\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #4\n"; };

		tree.growthTree();
		if (1 != tree.getHeight()) { std::cout << "BLAD - #5\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #5\n"; };
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #6\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #6\n"; };
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #7\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #7\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #8\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #8\n"; };

		tree.growthTree();
		if (2 != tree.getHeight()) { std::cout << "BLAD - #9\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #9\n"; };
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #10\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #10\n"; };
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #11\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #11\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #12\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #12\n"; };

		tree.growthTree();
		if (3 != tree.getHeight()) { std::cout << "BLAD - #13\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #13\n"; };
		if (1 != tree.getBranchesTotal()) { std::cout << "BLAD - #14\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #14\n"; };
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #15\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #15\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #16\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #16\n"; };

		tree.growthTree();
		if (4 != tree.getHeight()) { std::cout << "BLAD - #17\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #17\n"; };
		if (1 != tree.getBranchesTotal()) { std::cout << "BLAD - #18\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #18\n"; };
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #19\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #19\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #20\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #20\n"; };

		tree.growthTree();
		if (5 != tree.getHeight()) { std::cout << "BLAD - #21\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #21\n"; };
		if (1 != tree.getBranchesTotal()) { std::cout << "BLAD - #22\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #22\n"; };
		if (1 != tree.getFruitsTotal()) { std::cout << "BLAD - #23\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #23\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #24\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #24\n"; };

		tree.growthTree();
		if (6 != tree.getHeight()) { std::cout << "BLAD - #25\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #25\n"; };
		if (2 != tree.getBranchesTotal()) { std::cout << "BLAD - #26\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #26\n"; };
		if (1 != tree.getFruitsTotal()) { std::cout << "BLAD - #27\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #27\n"; };
		if (1 != tree.getWeightsTotal()) { std::cout << "BLAD - #28\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #28\n"; };

		tree.growthTree();
		if (7 != tree.getHeight()) { std::cout << "BLAD - #29\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #29\n"; };
		if (2 != tree.getBranchesTotal()) { std::cout << "BLAD - #30\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #30\n"; };
		if (2 != tree.getFruitsTotal()) { std::cout << "BLAD - #31\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #31\n"; };
		if (2 != tree.getWeightsTotal()) { std::cout << "BLAD - #32\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #32\n"; };

		tree.growthTree();
		if (8 != tree.getHeight()) { std::cout << "BLAD - #33\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #33\n"; };
		if (2 != tree.getBranchesTotal()) { std::cout << "BLAD - #34\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #34\n"; };
		if (3 != tree.getFruitsTotal()) { std::cout << "BLAD - #35\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #35\n"; };
		if (4 != tree.getWeightsTotal()) { std::cout << "BLAD - #36\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #36\n"; };

		for (int i = 0; i < 100; i++) {
			tree.growthTree();
		}

		if (108 != tree.getHeight()) { std::cout << "BLAD - #37\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #37\n"; };
		if (36 != tree.getBranchesTotal()) { std::cout << "BLAD - #38\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #38\n"; };
		if (936 != tree.getFruitsTotal()) { std::cout << "BLAD - #39\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #39\n"; };
		if (32607 != tree.getWeightsTotal()) { std::cout << "BLAD - #40\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #40\n"; };
	}

	/*
	TreeFade
	*/
	{
		std::cout << "----------------------------------------\n" << "TreeFade\n\n";
		TREE_CLASS tree = TREE_CLASS();
		if (0 != tree.getHeight()) { std::cout << "BLAD - #1\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #1\n"; };
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #2\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #2\n"; };
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #3\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #3\n"; };
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #4\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #4\n"; };

		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();

		int calc = 5;
		if (9 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (3 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (4 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (7 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		tree.fadeTree();
		if (8 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (3 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (4 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		tree.fadeTree();
		if (7 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (6 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (5 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (4 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (3 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (2 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (1 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (0 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.fadeTree();
		if (0 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
	}

	/*
	TreeFindBranch
	*/
	{
		std::cout << "----------------------------------------\n" << "TreeFindBranch\n\n";

		auto tree = TREE_CLASS();
		int calc = 1;
		if (tree.getGardenPointer()) { std::cout << "BLAD - #" << calc << "\n" << tree.getGardenPointer() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(0)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(0) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(1)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(1) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(2)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(2) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(3)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(3) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		tree.growthTree();

		if (tree.getBranchPointer(0)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(0) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(1)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(1) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(2)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(2) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(3)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(3) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;


		tree.growthTree();
		tree.growthTree();

		if (tree.getBranchPointer(0)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(0) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(1)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(1) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(2)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(2) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchesTotal() != 1) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(3)->getHeight() != 3) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(3)->getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(4)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(4) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
	}

	/*
	TreeCloneBranch
	*/
	{
		std::cout << "----------------------------------------\n" << "TreeCloneBranch\n\n";
		TREE_CLASS tree = TREE_CLASS();

		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();

		int calc = 1;
		if (12 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (4 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (8 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (23 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		tree.getBranchPointer(6)->fadeBranch();
		tree.getBranchPointer(6)->fadeBranch();
		tree.getBranchPointer(6)->fadeBranch();
		tree.getBranchPointer(6)->fadeBranch();
		tree.getBranchPointer(6)->fadeBranch();
		tree.getBranchPointer(6)->fadeBranch();
		BRANCH_CLASS* to_clone = tree.getBranchPointer(3);

		for (int i = 0; i < 100; i++) {
			to_clone->growthBranch();
		}
		tree.cloneBranch(to_clone);
		to_clone->growthBranch();
		// tree.tellmeyourfruitsize();
		if (12 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (4 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (110 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (5887 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
	}

	/*
	TreeCopyConstructor
	*/
	{
		std::cout << "----------------------------------------\n" << "TreeCopyConstructor\n\n";
		TREE_CLASS tree = TREE_CLASS();

		int calc = 1;
		if (0 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();
		tree.growthTree();

		if (9 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (3 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (4 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (7 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		auto tree2 = TREE_CLASS(tree);

		if (tree.getBranchesTotal() != tree2.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << " " << tree2.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getFruitsTotal() != tree2.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << " " << tree2.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getWeightsTotal() != tree2.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << " " << tree2.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getHeight() != tree2.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << " " << tree2.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getNumber() != tree2.getNumber()) { std::cout << "BLAD - #" << calc << "\n" << tree.getNumber() << " " << tree2.getNumber() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getGardenPointer() != tree2.getGardenPointer()) { std::cout << "BLAD - #" << calc << "\n" << tree.getGardenPointer() << " " << tree2.getGardenPointer() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(3) == tree2.getBranchPointer(3)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(3) << " " << tree2.getBranchPointer(3) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		tree2.growthTree();
		if (10 != tree2.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree2.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (3 != tree2.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree2.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (5 != tree2.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree2.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (11 != tree2.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree2.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		if (tree.getBranchesTotal() != tree2.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << " " << tree2.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getFruitsTotal() == tree2.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << " " << tree2.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getWeightsTotal() == tree2.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << " " << tree2.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getHeight() == tree2.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << " " << tree2.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getNumber() != tree2.getNumber()) { std::cout << "BLAD - #" << calc << "\n" << tree.getNumber() << " " << tree2.getNumber() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getGardenPointer() != tree2.getGardenPointer()) { std::cout << "BLAD - #" << calc << "\n" << tree.getGardenPointer() << " " << tree2.getGardenPointer() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (tree.getBranchPointer(3) == tree2.getBranchPointer(3)) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchPointer(3) << " " << tree2.getBranchPointer(3) << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;

		if (9 != tree.getHeight()) { std::cout << "BLAD - #" << calc << "\n" << tree.getHeight() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (3 != tree.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (4 != tree.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (7 != tree.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << tree.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
	}

	/*
	GardenConstructor
	*/
	{
		std::cout << "----------------------------------------\n" << "GardenConstructor\n\n";
		GARDEN_CLASS garden = GARDEN_CLASS();
		int calc = 1;
		if (0 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;
	}

	/*
	GardenPlant
	*/
	{
		std::cout << "----------------------------------------\n" << "GardenPlant\n\n";
		GARDEN_CLASS garden = GARDEN_CLASS();

		for (int i = 0; i < 1000000; i++) {
			garden.plantTree();
		}
		int calc = 1;
		if (1000000 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;
	}

	/*
	GardenGrowth
	*/
	{
		std::cout << "----------------------------------------\n" << "GardenGrowth\n\n";
		GARDEN_CLASS garden = GARDEN_CLASS();

		garden.plantTree();
		garden.plantTree();

		int calc = 1;
		if (2 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;

		garden.growthGarden();
		garden.growthGarden();
		garden.growthGarden();

		if (2 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;

		garden.growthGarden();
		garden.growthGarden();

		if (2 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;
	}

	/*
	GardenHarvest
	*/
	{
		std::cout << "----------------------------------------\n" << "GardenHarvest\n\n";

		GARDEN_CLASS garden = GARDEN_CLASS();

		garden.plantTree();
		garden.plantTree();

		int calc = 1;
		if (2 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;

		for (int i = 0; i < 100; ++i) {
			garden.growthGarden();
		}

		if (2 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (66 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1600 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (51472 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;
	}

	/*
	GardenClone
	*/
	{
		std::cout << "----------------------------------------\n" << "GardenClone\n\n";
		GARDEN_CLASS garden = GARDEN_CLASS();

		garden.plantTree();
		garden.plantTree();
		garden.plantTree();

		int calc = 1;
		if (3 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;

		TREE_CLASS* cloned = garden.getTreePointer(0);
		cloned->growthTree();
		cloned->growthTree();
		cloned->growthTree();

		if (3 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;

		garden.cloneTree(0);

		if (4 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;

		garden.getTreePointer(3)->growthTree();
		garden.getTreePointer(3)->growthTree();
		if (4 != garden.getTreesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getTreesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (2 != garden.getBranchesTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getBranchesTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (1 != garden.getFruitsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getFruitsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;
		if (0 != garden.getWeightsTotal()) { std::cout << "BLAD - #" << calc << "\n" << garden.getWeightsTotal() << "\n"; }
		else { std::cout << "OK - #" << calc << "\n"; }; calc++;;
	}
	/*
	Bez:
	- FruitCreateDestroy
	- FruitGetParent
	- GardenExtract
	*/
	return 0;
}