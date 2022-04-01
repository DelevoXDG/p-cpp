//Maksim Zdobnikau

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
size_t allocated = 0;
size_t deleted = 0;

#define nullptr NULL

void* operator new(size_t size) {
	void* pointer = malloc(size);
	allocated++;
	return pointer;
}

void operator delete(void* pointer) {
	free(pointer);
	deleted++;
}

void check_leaks() {
	if (allocated == deleted) cout << "OK\n";
	else cout << "MEMORY LEAKS\n";
}


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
	Node<T>(T data, Node<T>* next) : _data(data), _next(next) {}
	void Insert_Data(Bead);
	T& Get_Data();
};
template <typename T> struct LinkedList {
public:
	Node<T>* _first;

	LinkedList<T>() : _first(nullptr) {}

	void Insert(T);		//Insert element before element of bigger value
	void Remove(T);
	void RemoveLinks(RopeID, int);
	void Clean(LinkedList<Rope>*);
	void Clean_All();
	Node<T>* Get_Node(T);
	void Print();
};



struct RopeID {
	char _id0;
	char _id1;
	char _id2;

	RopeID() {}
	RopeID(const char id0, const char id1, const char id2) : _id0(id0), _id1(id1), _id2(id2) {}

	friend ostream& operator<<(ostream& os, const RopeID& rope_id) {
		os << rope_id._id0 << rope_id._id1 << rope_id._id2;
		return os;
	}

	bool operator==(const RopeID rope) {
		if (_id0 != rope._id0) { return false; }
		if (_id1 != rope._id1) { return false; }
		if (_id2 != rope._id2) { return false; }
		return true;
	}
	bool operator!=(const RopeID rope) {
		if (_id0 != rope._id0) { return true; }
		if (_id1 != rope._id1) { return true; }
		if (_id2 != rope._id2) { return true; }
		return false;
	}
	bool operator<(const RopeID rope) {
		if (_id0 != rope._id0) { return _id0 < rope._id0; }
		if (_id1 != rope._id1) { return _id1 < rope._id1; }
		if (_id2 != rope._id2) { return _id2 < rope._id2; }
		return false;
	}
};

struct Connection {
public:
	RopeID _dest_rope_id;
	int _dest_bead_ID;
	Connection() {};

	bool operator==(const Connection link) {
		if (_dest_rope_id != link._dest_rope_id) { return false; }
		if (_dest_bead_ID != link._dest_bead_ID) { return false; }
		return true;
	}
	bool operator!=(const Connection link) {
		return !(*this == link);
	}
	bool operator<(const Connection link) {
		return _dest_rope_id < link._dest_rope_id;
	}

	friend ostream& operator<<(ostream& os, const Connection& link) {
		os << link._dest_rope_id << " " << link._dest_bead_ID;
		return os;
	}
};
struct Bead {
public:
	RopeID _host_Rope;
	int _id;
	LinkedList<Connection> _Attached_Beads;


	Bead() {}
	Bead(const RopeID destRope, const int id) : _host_Rope(destRope), _id(id) {}

	int Get_ID() {
		return _id;
	}

	bool operator==(const Bead bead) {
		return _id == bead._id;
	}
	bool operator!=(const Bead bead) {
		return _id != bead._id;
	}
	bool operator<(const Bead bead) {
		return _id < bead._id;
	}
	void Attach_To(RopeID rope, int bead_id) {
		Connection connection;
		connection._dest_rope_id = rope;
		connection._dest_bead_ID = bead_id;
		// [ ] pending adding to LL
	}
	void Detach_From(RopeID rope, int bead_id) {
		Connection connection;
		connection._dest_rope_id = rope;
		connection._dest_bead_ID = bead_id;
		// [ ] pending removal to LL
	}
	friend ostream& operator<<(ostream& os, const Bead& bead) {
		os << bead._id;
		for (Node<Connection>* cur_link = bead._Attached_Beads._first; cur_link; cur_link = cur_link->_next) {
			os << " " << cur_link->_data._dest_rope_id << " " << cur_link->_data._dest_bead_ID;
		}
		return os;
	}
};
struct Rope {
public:
	RopeID _id;
	LinkedList<Bead> bead_list;

	Rope() {}
	Rope(const char id0, const char id1, const char id2) : _id(id0, id1, id2) {}
	Rope(const RopeID rope_id) : _id(rope_id) {}
	RopeID Get_ID() {
		return _id;
	}
	LinkedList<Bead>& GetBeads();
	void Set_ID(const RopeID id) {
		_id = id;
	}
	void Set_ID(const char id0, const char id1, const char id2) {
		_id._id0 = id0;
		_id._id1 = id1;
		_id._id2 = id2;
	}

	bool operator==(const Rope rope) { return _id == rope._id; }
	bool operator!=(const Rope rope) { return _id != rope._id; }
	bool operator<(const Rope rope) { return _id < rope._id; }

	friend ostream& operator <<(ostream& os, const Rope& rope) {
		os << rope._id << " " << std::endl;

		for (Node<Bead>* cur_bead = rope.bead_list._first; cur_bead; cur_bead = cur_bead->_next) {
			os << cur_bead->_data << std::endl;
		}
		return os;
	}

};

template <typename T>
Node<T>* LinkedList<T>::Get_Node(T object) {
	Node<T>* cur_node = _first;
	while (cur_node != nullptr) {
		if (object == cur_node->_data) { return cur_node; }

		cur_node = cur_node->_next;
	}
	return nullptr;
}
template <typename T>
void LinkedList<T>::Insert(T newData) {
	if (_first == nullptr) {
		_first = new Node<T>(newData, nullptr);
		return;
	}

	Node<T>* cur_node = _first;
	Node<T>* prev = nullptr;

	while (cur_node != nullptr
		&& cur_node->_data != newData //  Only unique items
		) {
		if (newData < cur_node->_data) { // Inserting before element of bigger value to maintain sort
			Node<T>* new_Node = new Node<T>(newData, cur_node);	//new data node
			if (prev == nullptr) {
				_first = new_Node;
				return;
			}

			prev->_next = new_Node;
			return;
		}
		prev = cur_node;			// Previous node
		cur_node = cur_node->_next;	// "Incrementation"
	}
	// if newdata contains biggest element

	prev->_next = new Node<T>(newData, nullptr);
}
template <typename T>
void LinkedList<T>::Remove(T removedData) {
	if (_first == nullptr) {
		return;
	}
	if (_first->_data == removedData) {
		Node<T>* next = _first->_next;
		delete _first;
		_first = next;
		return;
	}
	Node<T>* cur_node = _first->_next;
	Node<T>* prev = nullptr;
	while (cur_node != nullptr) {
		if (cur_node->_data == removedData) {
			prev->_next = cur_node->_next;
			delete cur_node;
			return;
		}
		prev = cur_node;
		cur_node = cur_node->_next;
	}
}

template <>
void LinkedList<Rope>::RemoveLinks(RopeID rope_id, int bead_id) {
	for (Node<Rope>* cur_rope = this->_first; cur_rope; cur_rope = cur_rope->_next) {
		for (Node<Bead>* cur_bead = cur_rope->_data.bead_list._first; cur_bead; cur_bead = cur_bead->_next) {
			for (Node<Connection>* cur_link = cur_bead->_data._Attached_Beads._first; cur_link; cur_link = cur_link->_next) {
				if (cur_link->_data._dest_bead_ID == bead_id && cur_link->_data._dest_bead_ID == bead_id) {
					cur_bead->_data._Attached_Beads.Remove(cur_link->_data);
				}
			}
		}
	}
}
template <>
void LinkedList<Bead>::Clean(LinkedList<Rope>* rope_list) {
	for (Node<Bead>* cur_bead = _first; cur_bead; ) {
		Node<Bead>* next_node = cur_bead->_next;
		rope_list->RemoveLinks(cur_bead->_data._host_Rope, cur_bead->_data.Get_ID());
		this->Remove(cur_bead->_data);
		cur_bead = next_node;
	}
}
template <>
void Node<Rope>::Insert_Data(Bead new_bead) {
	_data.bead_list.Insert(new_bead);
}


template <>
void LinkedList<Rope>::Print() {
	for (Node<Rope>* cur_rope = _first; cur_rope; cur_rope = cur_rope->_next) {
		cout << cur_rope->_data;
	}
	// cout << endl;
}

template <>
void LinkedList<Rope>::Clean_All() {
	for (Node<Rope>* cur_rope = this->_first; cur_rope; cur_rope = cur_rope->_next) {
		cur_rope->_data.bead_list.Clean(this);
		this->Remove(cur_rope->_data);
	}
}

int main()
{
	char 				OP = 0;
	LinkedList<Rope> 	AllRopes;
	while (OP != 'F') {
		cin >> OP;
		switch (OP) {
		case 'S': {
			char sn0 = 0;
			char sn1 = 0;
			char sn2 = 0;

			cin >> sn0 >> sn1 >> sn2;	// Rope ID

			AllRopes.Insert(Rope(sn0, sn1, sn2));

			break;
		}
		case 'B': {
			int kr = 0;
			char sn0 = 0;
			char sn1 = 0;
			char sn2 = 0;

			cin >> kr;					// Bead ID
			cin >> sn0 >> sn1 >> sn2;	// Rope ID

			RopeID sn(sn0, sn1, sn2);
			Rope tmp_Rope(sn);			// Rope needed to be checked for presence in ropelist

			Node<Rope>* dest_Rope = AllRopes.Get_Node(tmp_Rope);

			if (dest_Rope != nullptr) {
				Bead new_bead(sn, kr);
				dest_Rope->Insert_Data(new_bead);
			}
			// else no destination rope to add to

			break;
		}

		case 'L': {
			break;
		}
		case 'U': {
			break;
		}
		case 'D': {
			int kr = 0;
			char sn0 = 0;
			char sn1 = 0;
			char sn2 = 0;

			cin >> kr;					// Bead ID
			cin >> sn0 >> sn1 >> sn2;	// Rope ID

			RopeID sn(sn0, sn1, sn2);
			Rope tmp_Rope(sn);
			Bead tmp_Bead(sn, kr);

			AllRopes.RemoveLinks(sn, kr);

			Node<Rope>* host_Rope = AllRopes.Get_Node(tmp_Rope);
			if (host_Rope == nullptr) break;
			Node<Bead>* removed_Bead = host_Rope->_data.bead_list.Get_Node(tmp_Bead);
			if (removed_Bead == nullptr) break;

			host_Rope->_data.bead_list.Remove(removed_Bead->_data);

			break;
		}
		case 'M': {
			break;
		}
		case 'R': {
			break;
		}
		case 'P': {
			AllRopes.Print();
			break;
		}
		case 'F': {
			AllRopes.Clean_All();
		}
		}
	}
	check_leaks();



	return 0;
}

