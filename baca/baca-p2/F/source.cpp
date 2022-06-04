//Maksim Zdobnikau

#include "iostream"
#include "string"


#define nullptr 0
using std::cout;
using std::string;

class pNode;
class pList;

class PLAYER_CLASS;
class CAESAR_CLASS;
class PLAYER_CLASS;
class BERSERKER_CLASS;
class BEAST_CLASS;
class SQUAD_CLASS;
class ARENA_CLASS;

	// SECTION Fighting rules
// 1. Fight doesnt happen if one of the players is dead
// 2. First player - first argument, second player - second argument
// 3. Player with more agility becomes first, if agility is the same first remains first
// 4. Before battle call printParams of first player, than second player
// 5. First gives damage by calling takeDamage on second
// print results
// 6. The same in reverse 
// print results
// 7. Death:
// if after attack health goes to zero, the player dies 
// 8. Battle ends if :
// Health of one of the players goes below 10
// 40 attacks been made
// 9. Trial:
// Every player gets judged
// Prints its paremeters
// 12. Victors:
// Every player remaining alive after trial
// 13. Increase attackPoints by 2 and agilityPoins by 2 calling applyWinnerReward
// 14. Restoring health to maxHealth

struct pNode {
private:
	pNode* next;
	PLAYER_CLASS* data;
public:
	pNode(PLAYER_CLASS*, pNode* = nullptr);

	void setNext(pNode* next) { this->next = next; }
	pNode* getNext() { return this->next; }
	PLAYER_CLASS& getData() { return *data; }
};
struct pList {
private:
	pNode* first;
	unsigned int size;
public:
	pList();
	~pList();

	pNode* getFirst() { return this-> first; }
	void setFirst(pNode* first) { this->first = first; }
	pNode* at();
	bool contains(PLAYER_CLASS*);
	bool isEmpty();
	unsigned int getSize();
	pNode* getNode(PLAYER_CLASS*);
	void insertFirst(PLAYER_CLASS*);
	void deleteAfter(pNode*);
	void insertLast(pNode*);
	pNode* getMid(pNode*);
	pNode* merge(pNode*, pNode*);
	void mergeSort(pNode**);
	void sort();

	void printList();
};

class PLAYER_CLASS {
	friend class CAESAR_CLASS;
	friend class SQUAD_CLASS;
protected:
	unsigned int maxHP;
	unsigned int HP;
	unsigned int attackPoints;
	unsigned int agilityPoints;
public:
	PLAYER_CLASS();
	PLAYER_CLASS(unsigned int, unsigned int, unsigned int, unsigned int);

	virtual unsigned int getRemainingHealth();
	virtual unsigned int getMaxHP();
	virtual unsigned int getHP();
	virtual unsigned int getDamage();
	virtual unsigned int getAgility();
	virtual void takeDamage(unsigned int);
	virtual void applyWinnerReward();
	virtual void cure();
	virtual void printParams() = 0;
	virtual unsigned int getDefense();
	virtual unsigned int getArmor();
	// virtual std::string toString();
	virtual std::string getName() = 0;
	virtual bool isDead();
	virtual bool isAlive();

	bool operator <= (PLAYER_CLASS&);
private:
	virtual void die();
};
class CAESAR_CLASS {
private:
	unsigned int trialCount;
public:
	unsigned int attackCount;

public:
	void judgeDeathOfLife(PLAYER_CLASS*);
};
class ARENA_CLASS {
private:
	CAESAR_CLASS judge;

public:
	ARENA_CLASS(CAESAR_CLASS*);

	void fight(PLAYER_CLASS*, PLAYER_CLASS*);
};


// Section Player Types 
class HUMAN_CLASS : public virtual PLAYER_CLASS {
protected:
	int armorPoints;
private:
	std::string name;
public:
	HUMAN_CLASS(std::string);

	void printParams();

	std::string getName();
	unsigned int getArmor();
	unsigned int getDefense();
};

class BEAST_CLASS : public virtual PLAYER_CLASS {
private:
	std::string name;
	bool isHuman;
public:
	BEAST_CLASS(std::string);

	unsigned int getDamage();
	void printParams();

	std::string getName();
	unsigned int getArmor() { return 0; };
	unsigned int getDefense();
};

class BERSERKER_CLASS : public virtual HUMAN_CLASS, public virtual BEAST_CLASS {
public:
	BERSERKER_CLASS(std::string, std::string);

	unsigned int getAgility();
	unsigned int getDamage();
	void takeDamage(unsigned int);
	void printParams();

	bool isBeast();
	std::string getName();
	unsigned int getArmor();
	unsigned int getDefense();
};

class SQUAD_CLASS : public virtual PLAYER_CLASS {
private:
	std::string name;
	pList playerList;

public:
	SQUAD_CLASS(std::string);

	void addPlayer(PLAYER_CLASS*);
	unsigned int getAgility();
	unsigned int getDamage();
	unsigned int getRemainingHealth();
	void takeDamage(unsigned int);
	void printParams();
	void die();
	void cure();
	void applyWinnerReward();

	std::string getName();
	void removeDead();
	unsigned int playerCount();
};

// SECTION LIST


pNode::pNode(PLAYER_CLASS* data, pNode* next) :data(data), next(next) {
}
pList::pList() : first(nullptr), size(0) {
}
pList::~pList() {
	for (pNode* cur = this->first; cur;) {
		pNode* nextNode = cur->getNext();
		delete cur;
		cur = nextNode;
	}
}
void pList::insertFirst(PLAYER_CLASS* data) {
	pNode* newNode = new pNode(data, this->first);
	this->first = newNode;
	this->size++;
}

void pList::deleteAfter(pNode* prev) {
	if (this->first == nullptr) {
		return;
	}
	pNode* toDelete = nullptr;
	if (prev == nullptr) {
		toDelete = this->first;
		if (this->first->getNext() == nullptr) {
			this->first = nullptr;
		} else {
			this->first = this->first->getNext();
		}
	} else {
		if (prev->getNext() == nullptr) {
			return;
		}
		toDelete = prev->getNext();
		prev->setNext(prev->getNext()->getNext());
	}
	if (toDelete == nullptr) {
		return;
	}
	// toDelete->setNext(nullptr);

	delete toDelete;
	this->size--;
}
bool pList::contains(PLAYER_CLASS* data) {
	if (data == nullptr) {
		return false;
	}
	for (pNode* cur = this->first; cur; cur = cur->getNext()) {
		if (&(cur->getData()) == data) {
			return true;
		}
	}
	return false;
}
pNode* pList::getNode(PLAYER_CLASS* data) {
	for (pNode* cur = this->first; cur; cur = cur->getNext()) {
		if (&(cur->getData()) == data) {
			return cur;
		}
	}
	return nullptr;
}
void pList::printList() {
	pNode* curNode = this->first;
	while (curNode != NULL) {
		// cout += curNode->getData().toString() + "\n";
		curNode->getData().printParams();
		curNode = curNode->getNext();
	}
	return;
}
pNode* pList::merge(pNode* nodeA, pNode* nodeB) {
	pNode* prev = nullptr;
	pNode* cur = nullptr;
	pNode* first = nullptr;

	while (nodeA != nullptr && nodeB != nullptr) {
		if (nodeA->getData() <= nodeB->getData()) {
			cur = nodeA;
			nodeA = nodeA->getNext();
		} else {
			cur = nodeB;
			nodeB = nodeB->getNext();
		}
		if (prev == nullptr) {
			first = cur;
		} else {
			prev->setNext(cur);
		}
		prev = cur;
	}

	if (nodeA == nullptr) {
		prev->setNext(nodeB);
	} else {
		prev->setNext(nodeA);
	}

	return first;
}
pNode* pList ::getMid(pNode* root) {
	pNode* toMid = root;
	for (pNode* toEnd = root->getNext(); toEnd != nullptr; ) {
		toEnd = toEnd->getNext();
		if (toEnd != nullptr) {
			toMid = toMid->getNext();
			toEnd = toEnd->getNext();
		}
	}
	pNode* mid = toMid->getNext();
	toMid->setNext(nullptr);
	return mid;
}
void pList::mergeSort(pNode** root) {
	pNode* cur = *root;
	if (cur == nullptr) {
		return;
	}
	if (cur->getNext() == nullptr) {
		return;
	}
	if (cur->getNext() == cur) {
		std::cout << "panic\n";
	}

	pNode* L = cur;
	pNode* mid = getMid(cur);

	mergeSort(&L);
	mergeSort(&mid);

	*root = merge(L, mid);
}
void pList::sort() {
	this->mergeSort(&(first));
}
bool pList::isEmpty() {
	return this->first == nullptr;
}
unsigned int pList::getSize() {
	return this->size;
}
// SECTION PLAYER
PLAYER_CLASS::PLAYER_CLASS() : maxHP(0), HP(0), attackPoints(0), agilityPoints(0) {

};
PLAYER_CLASS::PLAYER_CLASS(unsigned int maxHP, unsigned int HP, unsigned int attackPoints, unsigned int agilityPoints) : maxHP(maxHP), HP(HP), attackPoints(attackPoints), agilityPoints(agilityPoints) {
};
unsigned int PLAYER_CLASS::getArmor() {
	return 0;
}
bool PLAYER_CLASS::isDead() {
	return this->getRemainingHealth() == 0;
}
bool PLAYER_CLASS::isAlive() {
	return this->getRemainingHealth() != 0;
}
unsigned int PLAYER_CLASS::getRemainingHealth() {
	unsigned int hpPercentage = ((this->HP * 100) / this->maxHP);
	return hpPercentage;
}
unsigned int PLAYER_CLASS::getDamage() {
	return this->attackPoints;
}
unsigned int PLAYER_CLASS::getAgility() {
	return this->agilityPoints;
}
unsigned int PLAYER_CLASS::getHP() {
	return this->HP;
}
unsigned int PLAYER_CLASS::getMaxHP() {
	return this->maxHP;
}
unsigned int PLAYER_CLASS::getDefense() {
	return 0;
}
void PLAYER_CLASS::takeDamage(unsigned int damage) {
	unsigned int dmgDebuff = this->getDefense();
	if (dmgDebuff > damage) {
		damage = 0;
		return;
	} else {
		damage -= dmgDebuff;
	}
	if (damage >= this->HP) {
		this->die();
		return;
	}

	this->HP -= damage;
}
void PLAYER_CLASS::applyWinnerReward() {
	this->attackPoints += 2;
	this->agilityPoints += 2;
}
void PLAYER_CLASS::die() {
	this->HP = 0;
}
void PLAYER_CLASS::cure() {
	this->HP = this->maxHP;
}
// std::string PLAYER_CLASS::toString() {
// 	std::string str("");
// 	str += this->getMaxHP() + ":";
// 	str += this->getHP() + ":";
// 	str += this->getRemainingHealth() + "%:";
// 	str += this->getDamage() + ":";
// 	str += this->getAgility();
// 	return str;
// }
// void PLAYER_CLASS::printParams() {
	// std::cout << this->toString() << "\n";
// }
// SECTION HUMAN
HUMAN_CLASS::HUMAN_CLASS(std::string name) :
	PLAYER_CLASS(200, 200, 30, 10),
	armorPoints(10),
	name(name) {
}
unsigned int HUMAN_CLASS::getArmor() {
	return this->armorPoints;
}
unsigned int HUMAN_CLASS::getDefense() {
	return this->getArmor() + this->getAgility();
}
std::string HUMAN_CLASS::getName() {
	return this->name;
}
std::string BEAST_CLASS::getName() {
	return this->name;
}
bool PLAYER_CLASS::operator <= (PLAYER_CLASS& B) {
	if (this->getName() != B.getName()) {
		return this->getName() <= B.getName();
	}
	if (this->getMaxHP() != B.getMaxHP()) {
		return this->getMaxHP() <= B.getMaxHP();
	}
	if (this->getHP() != B.getHP()) {
		return this->getHP() <= B.getHP();
	}
	if (this->getDamage() != B.getDamage()) {
		return this->getDamage() <= B.getDamage();
	}
	if (this->getRemainingHealth() != B.getRemainingHealth()) {
		return this->getRemainingHealth() <= B.getRemainingHealth();
	}
	if (this->getAgility() != B.getAgility()) {
		return this->getAgility() <= B.getAgility();
	}
	if (this->getArmor() != B.getArmor()) {
		return this->getArmor() <= B.getArmor();
	}
	return true;
}
// std::string HUMAN_CLASS::toString() {
// 	std::string str("");
// 	str += this->getName() + ":";
// 	switch (this->getHP()) {
// 		case 0: {
// 			str += ":R.I.P.";
// 			break;
// 		}
// 		default: {
// 			str += this->PLAYER_CLASS::toString();
// 			str += ":" + this->getArmor();
// 			break;
// 		}

// 	}
// 	return str;
// }
void HUMAN_CLASS::printParams() {
	if (this->isDead()) {
		std::cout << this->getName()
			<< ":R.I.P."
			<< "\n";
		return;
	}

	std::cout << this->getName() << ":" << std::flush
		<< this->getMaxHP() << ":" << std::flush
		<< this->getHP() << ":" << std::flush
		<< this->getRemainingHealth() << "%:" << std::flush
		<< this->getDamage() << ":" << std::flush
		<< this->getAgility() << ":" << std::flush
		<< this->getArmor()
		<< "\n";
}

// SECTION BEAST
BEAST_CLASS::BEAST_CLASS(std::string name) :
	PLAYER_CLASS(150, 150, 40, 20),
	name(name) {

}
unsigned int BEAST_CLASS::getDamage() {
	if (this->getRemainingHealth() < 25) {
		return this->attackPoints * 2;
	}
	return this->attackPoints;
}

unsigned int BEAST_CLASS::getDefense() {
	return this->getAgility() / 2;
}
// std::string BEAST_CLASS::toString() {
// 	std::string str("");
// 	str += this->getName() + ":";
// 	switch (this->getHP()) {
// 		case 0: {
// 			str += ":R.I.P.";
// 			break;
// 		}
// 		default: {
// 			str += this->PLAYER_CLASS::toString();
// 			break;
// 		}
// 	}
// 	return str;
// }
void BEAST_CLASS::printParams() {
	if (this->isDead()) {
		std::cout << this->getName()
			<< ":R.I.P."
			<< "\n";
		return;
	}

	std::cout << this->getName() << ":"
		<< this->getMaxHP() << ":"
		<< this->getHP() << ":"
		<< this->getRemainingHealth() << "%:"
		<< this->getDamage() << ":"
		<< this->getAgility()
		<< "\n";
}

// SECTION BERSERKER
BERSERKER_CLASS::BERSERKER_CLASS(std::string name1, std::string name2) :
	PLAYER_CLASS(200, 200, 35, 5),
	HUMAN_CLASS(name1), BEAST_CLASS(name2)
{
	this->HUMAN_CLASS::armorPoints = 15;
}
bool BERSERKER_CLASS::isBeast() {
	return this->getRemainingHealth() > 0 && this->getRemainingHealth() < 25;
}
unsigned int BERSERKER_CLASS::getDamage() {
	if (this->isBeast()) {
		return BEAST_CLASS::getDamage();
	}
	return this->HUMAN_CLASS::getDamage();
}
void BERSERKER_CLASS::takeDamage(unsigned int damage) {
	if (this->isBeast()) {
		return BEAST_CLASS::takeDamage(damage);
	}
	return this->HUMAN_CLASS::takeDamage(damage);
}
unsigned int BERSERKER_CLASS::getAgility() {
	if (this->isBeast()) {
		return BEAST_CLASS::getAgility();
	}
	return this->HUMAN_CLASS::getAgility();
}
unsigned int BERSERKER_CLASS::getDefense() {
	if (this->isBeast()) {
		return BEAST_CLASS::getDefense();
	}
	return this->HUMAN_CLASS::getDefense();
}
// std::string BERSERKER_CLASS::toString() {
// 	if (this->isBeast()) {
// 		return BEAST_CLASS::toString();
// 	}
// 	return this->HUMAN_CLASS::toString();
// }
std::string BERSERKER_CLASS::getName() {
	if (this->isBeast()) {
		return this->BEAST_CLASS::getName();
	}
	return this->HUMAN_CLASS::getName();
}
unsigned int BERSERKER_CLASS::getArmor() {
	if (this->isBeast()) {
		return this->BEAST_CLASS::getArmor();
	}
	return this->HUMAN_CLASS::getArmor();
}
void BERSERKER_CLASS::printParams() {
	if (this->isBeast()) {
		return BEAST_CLASS::printParams();
	}
	return HUMAN_CLASS::printParams();
}

// SECTION SQUAD
SQUAD_CLASS::SQUAD_CLASS(std::string name) :
	PLAYER_CLASS(1, 1, 1, 1),
	name(name) {
}
void SQUAD_CLASS::addPlayer(PLAYER_CLASS* player) {
	if (player == nullptr) {
		return;
	}
	if (player->isDead()) {
		return;
	}
	if (this->playerList.contains(player)) {
		return;
	}

	this->playerList.insertFirst(player);
}
unsigned int  SQUAD_CLASS::getAgility() {
	if (this->playerList.isEmpty()) {
		return 0;
	}
	unsigned int minAgility = this->playerList.getFirst()->getData().getAgility();

	for (pNode* cur = this->playerList.getFirst()->getNext();
	cur; cur = cur->getNext()) {
		if (cur->getData().getAgility() < minAgility) {
			minAgility = cur->getData().getAgility();
		}
	}
	return minAgility;
}
unsigned int SQUAD_CLASS::getDamage() {
	if (this->playerList.isEmpty()) {
		return 0;
	}

	unsigned int squadDamage = 0;
	for (pNode* cur = this->playerList.getFirst();
	cur; cur = cur->getNext()) {
		squadDamage += cur->getData().getDamage();
	}
	return squadDamage;
}
void SQUAD_CLASS::takeDamage(unsigned int damage) {
	if (this->playerList.isEmpty()) {
		return;
	}
	// pNode* prev = nullptr;
	unsigned damageEach = damage / this->playerList.getSize();
	for (pNode* cur = this->playerList.getFirst();
	 cur; ) {
		pNode* next = cur->getNext();
		cur->getData().takeDamage(damageEach);
		// if (cur->getData().isDead()) {
		// 	this->playerList.deleteAfter(prev);
		// }
		// prev = cur;
		cur = next;
	}
	this->removeDead();
}
unsigned int SQUAD_CLASS::getRemainingHealth() {
	if (this->playerList.isEmpty()) {
		return 0;
	}
	unsigned int maxHealthPercentage = this->playerList.getFirst()->getData().getRemainingHealth();

	for (pNode* cur = this->playerList.getFirst()->getNext();
	cur; cur = cur->getNext()) {
		if (cur->getData().getRemainingHealth() > maxHealthPercentage) {
			maxHealthPercentage = cur->getData().getRemainingHealth();
		}
	}
	return maxHealthPercentage;
}
void SQUAD_CLASS::die() {
	this->HP = 0;

	// pNode* prev = nullptr;
	for (pNode* cur = this->playerList.getFirst();
	cur; ) {
		pNode* next = cur->getNext();
		cur->getData().die();
		// playerList.deleteAfter(prev);

		// prev = cur;
		cur = next;
	}
	this->removeDead();
}
void SQUAD_CLASS::removeDead() {
	if (this->playerList.isEmpty()) {
		return;
	}
	if (this->playerCount() == 0) {
		return;
	}
	pNode* prev = nullptr;
	for (pNode* cur = this->playerList.getFirst();
	cur; ) {
		pNode* next = cur->getNext();
		if (cur->getData().isDead()) {
			this->playerList.deleteAfter(prev);
		} else {
			prev = cur;
		}
		cur = next;
	}
}
unsigned int SQUAD_CLASS::playerCount() {
	return this->playerList.getSize();
}
void SQUAD_CLASS::applyWinnerReward() {
	for (pNode* cur = this->playerList.getFirst();
	cur; cur = cur->getNext()) {
		cur->getData().applyWinnerReward();
	}
}
void SQUAD_CLASS::cure() {
	for (pNode* cur = this->playerList.getFirst();
	cur; cur = cur->getNext()) {
		cur->getData().cure();
	}
}
void SQUAD_CLASS::printParams() {
	this->removeDead();
	if (this->playerList.isEmpty()) {
		std::cout << this->getName()
			<< ":nemo"
			<< "\n";
		return;
	}
	std::cout << this->getName() << ":"
		<< this->playerCount() << ":"
		<< this->getRemainingHealth() << "%:"
		<< this->getDamage() << ":"
		<< this->getAgility()
		<< "\n";

	this->playerList.sort();

	for (pNode* cur = this->playerList.getFirst();
	cur; cur = cur->getNext()) {
		cur->getData().printParams();
	}
}
std::string SQUAD_CLASS::getName() {
	return this->name;
}
	// SECTION CAESAR
void CAESAR_CLASS::judgeDeathOfLife(PLAYER_CLASS* defendant) {
	this->trialCount++;

	if (this->trialCount % 3 == 0) {
		trialCount = 0;
		if (this->attackCount % 2 == 0) {
			defendant->die();
		}
	}
}
ARENA_CLASS::ARENA_CLASS(CAESAR_CLASS* judge) :
	judge(*judge) {
}
void ARENA_CLASS::fight(PLAYER_CLASS* A, PLAYER_CLASS* B) {
	if (A->isDead()) {
		return;
	}
	if (B->isDead()) {
		return;
	}
	if (A->getAgility() < B->getAgility()) {	// Decide first
		PLAYER_CLASS* tmp = A;
		A = B;
		B = tmp;
	}

	A->printParams();
	B->printParams();

	int fightCount = 0;
	for (fightCount = 0;
	fightCount < 40
	&& A->getRemainingHealth() >= 10
	&& B->getRemainingHealth() >= 10
	; fightCount++) {
		B ->takeDamage(A->getDamage());
		B ->printParams();
		this->judge.attackCount++;
		if (B->getRemainingHealth() >= 10) {
			A->takeDamage(B->getDamage());
			A->printParams();
			this->judge.attackCount++;
		}
	}

	if (A->isAlive()) {
		this->judge.judgeDeathOfLife(A);
		A->printParams();
		if (A->isAlive()) {
			A->cure();
			A->applyWinnerReward();
		}
	}
	if (B->isAlive()) {
		this->judge.judgeDeathOfLife(B);
		B->printParams();
		if (B->isAlive()) {
			B->cure();
			B->applyWinnerReward();
		}
	}

	A->printParams();
	B->printParams();
	this->judge.attackCount = 0;
}

// int main() {
// 	HUMAN_CLASS human1("warrior");
// 	HUMAN_CLASS human2("warrior");
// 	HUMAN_CLASS human3("warrior");
// 	HUMAN_CLASS human4("warrior");
// 	HUMAN_CLASS human5("warrior");
// 	HUMAN_CLASS human6("warrior");
// 	HUMAN_CLASS human7("warrior");
// 	HUMAN_CLASS human8("warrior");
// 	HUMAN_CLASS human9("awarrior");
// 	HUMAN_CLASS human10("warrio");

// 	SQUAD_CLASS avengers("avengers");
// 	avengers.addPlayer(&human1);
// 	avengers.addPlayer(&human2);
// 	avengers.addPlayer(&human3);
// 	avengers.addPlayer(&human4);
// 	avengers.addPlayer(&human5);
// 	avengers.addPlayer(&human6);
// 	avengers.addPlayer(&human7);
// 	avengers.addPlayer(&human8);
// 	avengers.addPlayer(&human9);
// 	avengers.addPlayer(&human10);

// 	avengers.printParams();

// 	human1.takeDamage(50);
// 	human2.takeDamage(50);
// 	human3.takeDamage(50);
// 	human4.takeDamage(50);
// 	human5.takeDamage(50);
// 	human6.takeDamage(50);
// 	human7.takeDamage(60);
// 	human10.takeDamage(10);

// 	avengers.printParams();

// 	human1.applyWinnerReward();
// 	human2.applyWinnerReward();
// 	human3.applyWinnerReward();
// 	human4.applyWinnerReward();

// 	avengers.printParams();

// 	BERSERKER_CLASS berserker1("warrior", "warrior");
// 	BERSERKER_CLASS berserker2("warrior", "warrior");
// 	BERSERKER_CLASS berserker3("warrior", "warrior");
// 	BERSERKER_CLASS berserker4("warrior", "warrior");
// 	BERSERKER_CLASS berserker5("warrior", "warrior");
// 	BERSERKER_CLASS berserker6("warrior", "warrior");
// 	BERSERKER_CLASS berserker7("warrior", "warrior");
// 	BERSERKER_CLASS berserker8("warrior", "warrior");
// 	BERSERKER_CLASS berserker9("warrior", "warrior");
// 	BERSERKER_CLASS berserker10("warrior", "warrior");

// 	avengers.addPlayer(&berserker1);
// 	avengers.addPlayer(&berserker2);
// 	avengers.addPlayer(&berserker3);
// 	avengers.addPlayer(&berserker4);
// 	avengers.addPlayer(&berserker5);
// 	avengers.addPlayer(&berserker6);
// 	avengers.addPlayer(&berserker7);
// 	avengers.addPlayer(&berserker8);
// 	avengers.addPlayer(&berserker9);
// 	avengers.addPlayer(&berserker10);

// 	avengers.printParams();

// 	berserker1.takeDamage(190);
// 	berserker2.takeDamage(190);
// 	berserker3.takeDamage(195);
// 	berserker4.takeDamage(170);
// 	berserker5.takeDamage(175);
// 	berserker6.takeDamage(10);
// 	berserker10.takeDamage(10);

// 	avengers.printParams();

// 	berserker1.applyWinnerReward();
// 	berserker2.applyWinnerReward();
// 	berserker3.applyWinnerReward();
// 	berserker4.applyWinnerReward();
// 	berserker6.applyWinnerReward();
// 	berserker7.applyWinnerReward();

// 	avengers.printParams();

// 	BEAST_CLASS beast1("warrior");
// 	BEAST_CLASS beast2("warrior");
// 	BEAST_CLASS beast3("warrior");
// 	BEAST_CLASS beast4("warrior");
// 	BEAST_CLASS beast5("warrior");
// 	BEAST_CLASS beast6("warrior");
// 	BEAST_CLASS beast7("warrior");
// 	BEAST_CLASS beast8("warrior");
// 	BEAST_CLASS beast9("awarrior");
// 	BEAST_CLASS beast10("warrio");

// 	avengers.addPlayer(&beast1);
// 	avengers.addPlayer(&beast2);
// 	avengers.addPlayer(&beast3);
// 	avengers.addPlayer(&beast4);
// 	avengers.addPlayer(&beast5);
// 	avengers.addPlayer(&beast6);
// 	avengers.addPlayer(&beast7);
// 	avengers.addPlayer(&beast8);
// 	avengers.addPlayer(&beast9);
// 	avengers.addPlayer(&beast10);

// 	avengers.printParams();

// 	beast1.takeDamage(130);
// 	beast2.takeDamage(145);
// 	beast3.takeDamage(155);
// 	beast4.takeDamage(100);
// 	beast5.takeDamage(149);
// 	beast10.takeDamage(10);

// 	avengers.printParams();

// 	beast1.applyWinnerReward();
// 	beast3.applyWinnerReward();
// 	beast4.applyWinnerReward();
// 	beast5.applyWinnerReward();
// 	beast6.applyWinnerReward();
// 	beast10.applyWinnerReward();

// 	avengers.printParams();

// 	human1.cure();
// 	berserker1.cure();
// 	beast1.cure();

// 	avengers.printParams();

// 	avengers.takeDamage(1000);

// 	avengers.printParams();
// }