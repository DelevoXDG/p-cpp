#include <iostream>

using std::cin; using std::cout; using std::endl; using std::string;

struct RopeID;
struct Bead;
struct Connection;
struct Rope;

template <typename T> struct Node;
template <typename T> struct LinkedList;

template <typename T>
struct Node {
public:
	T _data;
	Node<T>* _next;

	void InsertData(Bead);
	void Print() {
		_data.Print();
	}
};
template <typename T> struct LinkedList {
public:
	Node<T>* _first;

	LinkedList<T>() : _first(nullptr) {}
	void Insert(T);
	void Remove(T);
	Node<T>* Get_Node(T);


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
void LinkedList<T>::Insert(T newdata) {

	if (newdata < _first->data) {

	}


	Node<T>* cur_node = _first;
	while (cur_node != nullptr) {
		if (cur_node->_data == newdata) { return; }
		if (cur_node->_next == nullptr) { return; }
		// if (cur_node->_next->_data == newdata) { return; }

		if (newdata < cur_node->_data) {
			Node<T>* after_next = cur_node->_next;

			Node<T>* next = new Node<T>();
			next->_next = after_next;
			next->_data = newdata;

			cur_node->_next = next;
			return;
		}

		cur_node = cur_node->_next;	// "Incrementation"
	}
}
void Node<Rope>::InsertData(Bead new_bead) {
	_data.Insert(new_bead);
}
struct RopeID {
	char _id0;
	char _id1;
	char _id2;

	RopeID() {}
	RopeID(const char id0, const char id1, const char id2) : _id0(id0), _id1(id1), _id2(id2) {}

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
	bool operator<=(const RopeID rope) {
		if (_id0 != rope._id0) { return _id0 < rope._id0; }
		if (_id1 != rope._id1) { return _id1 < rope._id1; }
		if (_id2 != rope._id2) { return _id2 < rope._id2; }
		return true;
	}
};
struct Connection {
public:
	RopeID _rope;
	int _dest_beadID;
	Connection() {};

	bool operator==(const Connection link) {
		if (_rope != link._rope) { return false; }
		if (_dest_beadID != link._dest_beadID) { return false; }
		return true;
	}
	bool operator!=(const Connection link) {
		return !(*this == link);
	}
	bool operator<(const Connection link) {
		return _rope < link._rope;
	}
};
struct Rope {
private:
	RopeID _id;
	LinkedList<Bead> bead_list;

public:
	Rope() {}
	Rope(const char id0, const char id1, const char id2) : _id(id0, id1, id2) {}
	Rope(const RopeID rope_id) : _id(rope_id) {}
	RopeID Get_ID() {
		return _id;
	}
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
	void Print() {
		std::cout << _id._id0 << _id._id1 << _id._id2 << std::endl;
		// bead_List.Print();
	}
};
struct Bead {
private:
	int _id;
	RopeID _host_Rope;
	LinkedList<Connection> Attached_Beads;
public:

	Bead() {}
	Bead(const RopeID destRope, const int id) : _host_Rope(destRope), _id(id) {}

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
		connection._rope = rope;
		connection._dest_beadID = bead_id;
		//[ ] pending adding to LL
	}
	void Detach_From(RopeID rope, int bead_id) {
		Connection connection;
		connection._rope = rope;
		connection._dest_beadID = bead_id;
		//[ ] pending removal to LL
	}
	void Print() {
		// [ ] print links		
	}
};

int main(int argc, const char** argv)
{
	char 				OP = 0;
	LinkedList<Rope> 	RopeList;


	switch (OP) {
	case 'S': {
		char sn0 = 0;
		char sn1 = 0;
		char sn2 = 0;

		cin >> sn0 >> sn1 >> sn2;	// Rope ID

		RopeList.Insert(Rope(sn0, sn1, sn2));

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

		Node<Rope>* dest_Rope = RopeList.Get_Node(tmp_Rope);

		if (dest_Rope != nullptr) {
			Bead new_bead(sn, kr);
			dest_Rope->InsertData(new_bead);
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
		break;
	}
	case 'M': {
		break;
	}
	case 'R': {
		break;
	}
	case 'P': {
		break;
	}
	}




	return 0;
}