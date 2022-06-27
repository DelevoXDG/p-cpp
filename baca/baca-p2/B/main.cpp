//Maksim Zdobnikau

#include <iostream>
// #include "memory_check.h"

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

#define nullptr NULL

namespace Leaks {
	size_t allocated = 0;
	size_t deleted = 0;

	void Check_Leaks() {
		if (allocated == deleted) {
			cout << "OK\n";
			return;
		}

		cout << "MEMORY LEAKS\n";
		cout << "Allocated: " << allocated << "\n";
		cout << "Deleted: " << deleted << "\n";
	}
}

// Section Declarations
struct RopeID;
struct Rope;
struct Bead;
struct Connection;

template <typename T> struct Node;
template <typename T> struct LinkedList;

template <typename T> struct Node {
public:
	T _data;
	Node<T>* _next;
public:
	Node<T>() : _next(nullptr) {}
	Node<T>(T data, Node<T>* next) : _data(data), _next(next) {}

	void Insert_Data(const Bead);
};
template <typename T> struct LinkedList {
public:
	Node<T>* _first;
public:
	LinkedList<T>() : _first(nullptr) {}

	friend ostream& operator << (ostream&, const LinkedList<Rope>&);

	void Insert(T);		//Insert element before element of bigger value
	void Remove(T);
	void Remove_Backlinks_To_Bead(const RopeID, const unsigned short int);
	void Remove_Backlinks_To_Rope(const RopeID);
	void Clear_Rope(LinkedList<Rope>*);
	void Clear_All();
	Node<T>* Get_Node(T);
};

struct RopeID {
public:
	char _id0;
	char _id1;
	char _id2;
public:
	RopeID() {}
	RopeID(const char id0, const char id1, const char id2) : _id0(id0), _id1(id1), _id2(id2) {}

	friend ostream& operator << (ostream&, const RopeID&);
	friend istream& operator >> (istream&, RopeID&);

	bool operator == (const RopeID&);
	bool operator != (const RopeID&);
	bool operator <  (const RopeID&);
};
struct Connection {
public:
	RopeID _dest_rope_id;
	unsigned short int _dest_bead_id;

public:
	Connection() {};
	Connection(const RopeID rid, const unsigned short int bid) : _dest_rope_id(rid), _dest_bead_id(bid) {};

	friend ostream& operator << (ostream&, const Connection&);

	bool operator == (const Connection&);
	bool operator != (const Connection&);
	bool operator <  (const Connection&);
};
struct Bead {
public:
	RopeID _host_Rope;
	unsigned short int _id;
	LinkedList<Connection> _Attached_Beads;

public:
	Bead() {}
	Bead(const RopeID destRope, const unsigned short int id) : _host_Rope(destRope), _id(id) {}

	unsigned short int Get_ID();

	friend ostream& operator << (ostream&, const Bead&);

	bool operator == (const Bead&);
	bool operator != (const Bead&);
	bool operator < (const Bead&);

	void Add_Link_To(const RopeID, const unsigned short int);
	void Remove_Link_To(const RopeID, const unsigned short int);
	void Remove_Links();
};
struct Rope {
public:
	RopeID _id;
	LinkedList<Bead> _Bead_List;

public:
	Rope() {}
	Rope(const char id0, const char id1, const char id2) : _id(id0, id1, id2) {}
	Rope(const RopeID rope_id) : _id(rope_id) {}

	RopeID Get_ID() { return _id; }

	friend ostream& operator << (ostream&, const Rope&);

	bool operator == (const Rope& rope) { return _id == rope._id; }
	bool operator != (const Rope& rope) { return _id != rope._id; }
	bool operator < (const Rope& rope) { return _id < rope._id; }

};

// Section External methods
ostream& operator << (ostream& os, const RopeID& rope_id) {
	os << rope_id._id0 << rope_id._id1 << rope_id._id2;
	return os;
}
istream& operator >> (istream& is, RopeID& rope_id) {
	is >> rope_id._id0 >> rope_id._id1 >> rope_id._id2;
	return is;
}
ostream& operator << (ostream& os, const Connection& link) {
	os << link._dest_rope_id << " " << link._dest_bead_id;
	return os;
}
ostream& operator << (ostream& os, const Bead& bead) {
	os << bead._id;
	for (Node<Connection>* cur_link = bead._Attached_Beads._first; cur_link; cur_link = cur_link->_next) {
		os << " " << cur_link->_data._dest_rope_id << " " << cur_link->_data._dest_bead_id;
	}
	return os;
}
ostream& operator << (ostream& os, const Rope& rope) {
	os << rope._id << " " << std::endl;
	for (Node<Bead>* cur_bead = rope._Bead_List._first; cur_bead; cur_bead = cur_bead->_next) {
		os << cur_bead->_data << std::endl;
	}
	return os;
}
ostream& operator << (ostream& os, const LinkedList<Rope>& rope_list) {
	for (Node<Rope>* cur_rope = rope_list._first; cur_rope; cur_rope = cur_rope->_next) {
		os << cur_rope->_data;
	}
	return os;
}

// Section Internal methods
bool RopeID::operator == (const RopeID& rope) {
	if (_id0 != rope._id0) { return false; }
	if (_id1 != rope._id1) { return false; }
	if (_id2 != rope._id2) { return false; }
	return true;
}
bool RopeID::operator != (const RopeID& rope) {
	if (_id0 != rope._id0) { return true; }
	if (_id1 != rope._id1) { return true; }
	if (_id2 != rope._id2) { return true; }
	return false;
}
bool RopeID::operator < (const RopeID& rope) {
	if (_id0 != rope._id0) { return _id0 < rope._id0; }
	if (_id1 != rope._id1) { return _id1 < rope._id1; }
	if (_id2 != rope._id2) { return _id2 < rope._id2; }
	return false;
}
bool Bead::operator == (const Bead& bead) {
	return _id == bead._id;
}
bool Bead::operator != (const Bead& bead) {
	return _id != bead._id;
}
bool Bead::operator < (const Bead& bead) {
	return _id < bead._id;
}
bool Connection::operator == (const Connection& link) {
	if (_dest_rope_id != link._dest_rope_id) { return false; }
	if (_dest_bead_id != link._dest_bead_id) { return false; }
	return true;
}
bool Connection::operator != (const Connection& link) {
	return !(*this == link);
}
bool Connection::operator < (const Connection& link) {
	return _dest_rope_id != link._dest_rope_id ? _dest_rope_id < link._dest_rope_id : _dest_bead_id < link._dest_bead_id;
}
unsigned short int Bead::Get_ID() {
	return _id;
}
void Bead::Add_Link_To(const RopeID rope, const unsigned short int bead_id) {
	_Attached_Beads.Insert(Connection(rope, bead_id));
}
void Bead::Remove_Link_To(const RopeID rope, const unsigned short int bead_id) {
	_Attached_Beads.Remove(Connection(rope, bead_id));
}
void Bead::Remove_Links() {
	Node<Connection>* cur_node = _Attached_Beads._first;
	while (cur_node) {
		Node<Connection>* next_node = cur_node->_next;
		_Attached_Beads.Remove(cur_node->_data);
		cur_node = next_node;
	}
}
template <typename T>
Node<T>* LinkedList<T>::Get_Node(T object) {
	for (Node<T>* cur_node = _first; cur_node; cur_node = cur_node->_next) {
		if (object == cur_node->_data) {
			return cur_node;
		}
	}
	return nullptr;
}
template <typename T>
void LinkedList<T>::Insert(T newData) {
	if (_first == nullptr) {
		_first = new Node<T>(newData, nullptr);
		Leaks::allocated++;

		return;
	}

	Node<T>* prev = nullptr;
	for (Node<T>* cur_node = _first;			// Base case
	cur_node //  && cur_node->_data != newData	// Avoiding duplicates (not needed?)
	;cur_node = cur_node->_next) { 				// Incrementation
		if (newData < cur_node->_data) { // Inserting before element of bigger value to maintain sort
			Node<T>* new_Node = new Node<T>(newData, cur_node);
			Leaks::allocated++;
			if (prev == nullptr) {
				_first = new_Node;
				return;
			}

			prev->_next = new_Node;
			return;
		}
		prev = cur_node;			// Previous node in next iteration
	}
	// if newdata contains biggest element
	if (prev == nullptr) {
		_first = new Node<T>(newData, nullptr);;
		Leaks::allocated++;
		return;
	}
	prev->_next = new Node<T>(newData, nullptr);
	Leaks::allocated++;
}
template <typename T>
void LinkedList<T>::Remove(T removedData) {
	if (_first == nullptr) { 			// Case 1 empty list
		return;
	}
	if (_first->_data == removedData) {	// Case 2 first element to be removed
		Node<T>* next = _first->_next;
		delete _first;
		Leaks::deleted++;
		_first = next;
		return;
	}
	Node<T>* cur_node = _first->_next;
	Node<T>* prev = _first;
	while (cur_node != nullptr) {		// Base case
		if (cur_node->_data == removedData) {
			prev->_next = cur_node->_next;
			delete cur_node;
			Leaks::deleted++;
			return;
		}
		prev = cur_node;
		cur_node = cur_node->_next;
	}

}
template <>
void LinkedList<Rope>::Remove_Backlinks_To_Bead(const RopeID rope_id, const unsigned short int bead_id) {
	Connection removed_link(rope_id, bead_id);

	for (Node<Rope>* cur_rope = this->_first; cur_rope; cur_rope = cur_rope->_next) {
		for (Node<Bead>* cur_bead = cur_rope->_data._Bead_List._first; cur_bead; cur_bead = cur_bead->_next) {
			for (Node<Connection>* cur_link = cur_bead->_data._Attached_Beads._first; cur_link; ) {
				Node<Connection>* next_node = cur_link->_next;
				if (cur_link->_data == removed_link) {
					cur_bead->_data._Attached_Beads.Remove(cur_link->_data);
				}
				cur_link = next_node;
			}
		}
	}
}
template <>
void LinkedList<Rope>::Remove_Backlinks_To_Rope(const RopeID rope_id) {
	for (Node<Rope>* cur_rope = this->_first; cur_rope; cur_rope = cur_rope->_next) {
		for (Node<Bead>* cur_bead = cur_rope->_data._Bead_List._first; cur_bead; cur_bead = cur_bead->_next) {
			for (Node<Connection>* cur_link = cur_bead->_data._Attached_Beads._first; cur_link; ) {
				Node<Connection>* next_node = cur_link->_next;
				if (cur_link->_data._dest_rope_id == rope_id) {
					cur_bead->_data._Attached_Beads.Remove(cur_link->_data);
				}
				cur_link = next_node;
			}
		}
	}
}
template <>
void Node<Rope>::Insert_Data(const Bead new_bead) {
	_data._Bead_List.Insert(new_bead);
}
template <>
void LinkedList<Bead>::Clear_Rope(LinkedList<Rope>* rope_list) {
	for (Node<Bead>* cur_bead = this->_first; cur_bead; ) {
		Node<Bead>* next_node = cur_bead->_next;
		cur_bead->_data.Remove_Links();
		rope_list->Remove_Backlinks_To_Bead(cur_bead->_data._host_Rope, cur_bead->_data.Get_ID());
		this->Remove(cur_bead->_data);
		cur_bead = next_node;
	}
}
template <>
void LinkedList<Rope>::Clear_All() {
	for (Node<Rope>* cur_rope = this->_first; cur_rope; ) {
		Node<Rope>* next_node = cur_rope->_next;
		cur_rope->_data._Bead_List.Clear_Rope(this);
		this->Remove(cur_rope->_data);
		cur_rope = next_node;
	}
}

int main(int argc, const char** argv)
{
	char 				OP = 0;
	LinkedList<Rope> 	All_Ropes;

	while (OP != 'F') {
		cin >> OP;
		switch (OP) {
			case 'S': {
				char sn0 = 0;
				char sn1 = 0;
				char sn2 = 0;

				cin >> sn0 >> sn1 >> sn2;	// Rope ID

				All_Ropes.Insert(Rope(sn0, sn1, sn2));

				break;
			}
			case 'B': {
				unsigned short int kr = 0;
				char sn0 = 0;
				char sn1 = 0;
				char sn2 = 0;

				cin >> kr;					// Bead ID
				cin >> sn0 >> sn1 >> sn2;	// Rope ID

				RopeID sn(sn0, sn1, sn2);
				Rope tmp_Rope(sn);			// Rope needed to be checked for presence in ropelist

				Node<Rope>* dest_Rope = All_Ropes.Get_Node(tmp_Rope);

				if (dest_Rope != nullptr) {
					Bead new_bead(sn, kr);
					dest_Rope->Insert_Data(new_bead);
				}
				// else no destination rope to add to

				break;
			}

			case 'L': {
				RopeID sS;
				RopeID dS;
				unsigned short int sK = 0;
				unsigned short int dK = 0;

				cin >> sK;
				cin >> sS;
				cin >> dK;
				cin >> dS;

				Rope source_Rope(sS);
				Bead source_Bead(sS, sK);
				Rope dest_Rope(dS);
				Bead dest_Bead(dS, dK);

				Node<Rope>* SR_node = All_Ropes.Get_Node(source_Rope);
				if (SR_node == nullptr) { break; }
				Node<Bead>* SB_node = SR_node->_data._Bead_List.Get_Node(source_Bead);
				if (SB_node == nullptr) { break; }
				Node<Rope>* DR_node = All_Ropes.Get_Node(dest_Rope);
				// if (DR_node == nullptr) { break; }
				// Node<Bead>* DB_node = DR_node->_data._Bead_List.Get_Node(dest_Bead);
				// if (DB_node == nullptr) { break; }

				SB_node->_data.Add_Link_To(dS, dK);

				break;
			}
			case 'U': {
				RopeID sS;
				RopeID dS;
				unsigned short int sK = 0;
				unsigned short int dK = 0;

				cin >> sK;
				cin >> sS;
				cin >> dK;
				cin >> dS;

				Rope source_Rope(sS);
				Bead source_Bead(sS, sK);
				Rope dest_Rope(dS);
				Bead dest_Bead(dS, dK);

				Node<Rope>* SR_node = All_Ropes.Get_Node(source_Rope);
				if (SR_node == nullptr) { break; }
				Node<Bead>* SB_node = SR_node->_data._Bead_List.Get_Node(source_Bead);
				if (SB_node == nullptr) { break; }
				// Node<Rope>* DR_node = All_Ropes.Get_Node(dest_Rope);
				// if (DR_node == nullptr) { break; }
				// Node<Bead>* DB_node = DR_node->_data._Bead_List.Get_Node(dest_Bead);
				// if (DB_node == nullptr) { break; }

				SB_node->_data.Remove_Link_To(dS, dK);

				break;
			}
			case 'D': {
				unsigned short int kr = 0;
				char sn0 = 0;
				char sn1 = 0;
				char sn2 = 0;

				cin >> kr;					// Bead ID
				cin >> sn0 >> sn1 >> sn2;	// Rope ID

				RopeID sn(sn0, sn1, sn2);
				Rope tmp_Rope(sn);
				Bead tmp_Bead(sn, kr);

				All_Ropes.Remove_Backlinks_To_Bead(sn, kr);

				Node<Rope>* host_Rope = All_Ropes.Get_Node(tmp_Rope);
				if (host_Rope == nullptr) { break; }
				Node<Bead>* removed_Bead = host_Rope->_data._Bead_List.Get_Node(tmp_Bead);
				if (removed_Bead == nullptr) { break; }

				removed_Bead->_data.Remove_Links();
				host_Rope->_data._Bead_List.Remove(removed_Bead->_data);

				break;
			}
			case 'M': {
				RopeID sS;
				RopeID dS;
				unsigned short int kr = 0;

				cin >> kr;
				cin >> sS;
				cin >> dS;

				Rope source_Rope(sS);
				Bead source_Bead(sS, kr);
				Rope dest_Rope(dS);

				Node<Rope>* SR_node = All_Ropes.Get_Node(source_Rope);
				if (SR_node == nullptr) { break; }
				Node<Bead>* SB_node = SR_node->_data._Bead_List.Get_Node(source_Bead);
				if (SB_node == nullptr) { break; }
				Node<Rope>* DR_node = All_Ropes.Get_Node(dest_Rope);
				if (DR_node == nullptr) { break; }

				Bead dest_Bead(SB_node->_data);
				dest_Bead._host_Rope = dS;
				SR_node->_data._Bead_List.Remove(source_Bead);
				DR_node->_data._Bead_List.Insert(dest_Bead);

				break;
			}
			case 'R': {
				RopeID sn;
				cin >> sn;
				Rope removed_Rope(sn);
				Node<Rope>* removed_Node = All_Ropes.Get_Node(sn);
				removed_Node->_data._Bead_List.Clear_Rope(&All_Ropes);

				All_Ropes.Remove_Backlinks_To_Rope(sn);	// Case of deleting backlinks to removed elements
				All_Ropes.Remove(removed_Node->_data);

				break;
			}
			case 'P': {
				cout << All_Ropes;

				break;
			}
			case 'F': {
				All_Ropes.Clear_All();

				break;
			}
		}
	}
	// Leaks::Check_Leaks();
	// _MemoryCheck();

	return 0;
}