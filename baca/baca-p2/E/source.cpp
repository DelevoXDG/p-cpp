// Maksim Zdobnikau

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
	FRUIT_CLASS* getFruitPointer(unsigned int); // Return fruit growing on given distance from branch
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
	// void addGapCount(const unsigned int);
	// void subGapCount(const unsigned int);
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
	// unsigned int gapCount;

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
		curFruit = nextFruit;
	}
	this->subBranchCount(1);
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
	this->subTreeCount(1);

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
			curBranch = newBranch;

			return;
		}
	}
}
BRANCH_CLASS* TREE_CLASS::getBranchPointer(unsigned int offset) {
	if (offset > this->height) {
		return nullptr;
	}
	if (offset % 3 != 0) {
		return nullptr;
	}
	for (BRANCH_CLASS* curBranch = this->last; curBranch; curBranch = curBranch->getPrev()) {
		if (curBranch->getHeight() == offset) {
			return curBranch;
		}
	}
	return nullptr;
}
// Section GARDEN_CLASS
GARDEN_CLASS::GARDEN_CLASS() :
	weight(0),
	fruitCount(0), branchCount(0), treeCount(0),
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
}
void GARDEN_CLASS::deleteTree(TREE_CLASS* node) {
	if (node == nullptr) {
		return;
	}

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
	if (this->last == nullptr) {
		return nullptr;
	}
	if (this->last->getNumber() == this->treeCount - 1) {
		return this->last;
	}
	TREE_CLASS* curTree = this->first;
	if (curTree->getNumber() > 0) {
		return nullptr;
	}

	TREE_CLASS* prevTree = curTree;
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