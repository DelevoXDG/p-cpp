// Maksim Zdobnikau

#include <iostream>

//#define NDEBUG // toggle Assert()
#include <cassert>

using std::cin; using std::cout; using std::endl; using std::string;

#define nullptr NULL
typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long long uint64;

//SECTION TODO LIST
//[X] Add enum switch maybe? (no)
//[X] Remove back pointers
//[ ] Implement get(),set() functions
//[ ] Implement top-level interface

//[ ] Change opSelection to switch 
//[ ] Namespaces

namespace IOS {


	// 	void Output() { std::cout << endl; }

	// 	template<typename FirstT, typename ... ArgsT>
	// 	void Output(FirstT first, ArgsT&... args) {
	// 		std::cout << first;
	// 		Output(args...);
	// 	}

	// 	void Input() { ; }

	// 	template <typename FirstT, typename ... ArgsT>
	// 	void Input(FirstT& first, ArgsT&...args) {
	// 		std::cin >> first;
	// 		Input(args...);
	// 	}

	void PrintError() {
		std::cout << "error" << endl;
	}
}

// static void assert(bool condition) {
// 	// try
// 	if (!condition);
// }

//SECTION STORAGE STRUCTS
namespace Storage_NS {

	const uint16 MAX_GOODS = 65535;
	const uint8 MAX_PLACE = 128;
	const uint8 MAX_SHELF = 128;
	const uint8 MAX_RACK = 128;
	const uint8 MAX_WAREHOUSE = 128;
	const uint8 MAX_STORAGE = 128;
	struct Shelf;
	struct Rack;
	struct Warehouse;
	struct Storage;

	uint64 goods_sum = 0; //[ ] REMOVE?

	enum PlaceState : bool {
		empty = 0 //Used to set empty label
	// Code that causes warning goes here
	};
	struct Link {
		// Shelf* parent[MAX_PLACE];
		Shelf* _parent;
		// uint8 _id = 0;
	};

	struct Place {
		uint16 _num_goods; //Number of goods stored in Place [0...65535]
		uint8 _label;     //  isLabeled ==> label in [0..99]
		bool _isLabeled;  // !isLabeled ==> label undefined
		// uint8 _id;
		// Shelf& parent;

		Place() : _num_goods(0), _isLabeled(false), _label(0) {}

		bool invariant();
		void Set_Label(uint8);
		uint8 Get_Label();
		bool Is_Labeled();
		void Clear();
		uint16 Set_Value(const uint16, const uint8);
		uint16 Set_Value(const uint16, const PlaceState);
		uint16 Put(uint16);
		uint16 Pop(uint16);
		void Move(Place&, uint16);
		uint16 Get_Num_Goods();
		void Set_Num_Goods(uint16);
	};
	struct Shelf {
		uint8 _size; //Number of Places stored in Shelf [0...128]
		Place 	_place[MAX_PLACE];
		uint64 _num_goods; //[0...MAX_PLACE*MAX_GOODS]
		//uint8 _id;

		Shelf() : _size(0), _num_goods(0) {
			// for (uint8 i = 0; i < MAX_PLACE; i++) {
			// 	_place[i]._id = i;
			// }
		}
		bool invariant();
		uint64 Set_Size(const uint8);
		uint64 Get_Num_Goods();
		Place& Get_Place(const uint8 p);
		void Set_Num_Goods(uint64);
	};
	struct Rack {

		uint8 _size; //Number of Shelves stored in Rack [0...128]
		Shelf _shelf[MAX_SHELF];
		uint64 _num_goods; // INV
		Rack() : _size(0) {	}
		bool invariant();
		uint64 Set_Size(const uint8, const uint8);
		uint64 Get_Num_Goods();
		void Set_Num_Goods(uint64);
	};
	struct Warehouse {

		uint8 _size; //Number of Racks stored in Warehouse [0...128]
		Rack _rack[MAX_RACK];
		Shelf _handyShelf;
		uint64 _num_goods; // INV
		bool invariant();
		Warehouse() : _size(0) {}
		uint64 Get_Num_Goods();
		uint64 Set_Size(const uint8, const uint8, const uint8);
		void Set_Num_Goods(uint64);
	};
	struct Storage {

		uint8 _size; //Number of Warehouses stored in Storage [0...128]
		Rack _handyRack;
		Shelf _handyShelf;
		Warehouse _warehouse[MAX_WAREHOUSE];
		uint64 _num_goods; // INV
		Storage() : _size(0) {}
		bool invariant();
		uint64 Set_Size(const uint8, const uint8, const uint8, const uint8);
		uint64 Get_Num_Goods();
		void Fill(const uint8, const uint8, const uint8, const uint8, uint8);
		bool ReadAndCheck(int* const, int* const, int* const, int* const,
			int* const,
			int* const, int* const, int* const, int* const);
		void Set_Num_Goods(uint64);
	};

	void Place::Set_Label(uint8 label) {
		assert(!_isLabeled); // TODO
		_label = label;
		_isLabeled = true;
	}
	uint8 Place::Get_Label() {
		assert(_isLabeled);
		return _label;
	}
	bool Place::Is_Labeled() {
		return _isLabeled;
	}
	// void Place::Clear() {
	// 	num_goods = 0;
	// 	label = 0;
	// 	isLabeled = false;
	// }
	uint16 Place::Set_Value(const uint16 num_goods, const uint8 nlabel) {
		uint16 delta = num_goods - _num_goods;
		_num_goods = num_goods;
		_isLabeled = true;
		_label = nlabel;

		return delta; //Delta
	}
	uint16 Place::Set_Value(const uint16 num_goods, PlaceState state) {
		assert(state == empty);
		uint16 delta = num_goods - _num_goods;
		_num_goods = num_goods;
		_isLabeled = false;

		return delta; //Delta
	}
	uint16 Place::Put(uint16 add) {
		add = (_num_goods + add <= MAX_GOODS) ? add : MAX_GOODS - _num_goods;
		_num_goods += add;
		// parent[id].sum += num_goods;

		return add; //Delta
	}
	uint16 Place::Pop(uint16 sub) {
		sub = (_num_goods - sub > 0) ? sub : _num_goods;
		_num_goods -= sub;

		return -sub; //Delta
	}
	void Place::Move(Place& target, uint16 a) {
		a = (a < _num_goods) ? a : _num_goods;
		a = (a + target._num_goods < MAX_GOODS) ? a : (MAX_GOODS - target._num_goods);
		_num_goods -= a;
		target._num_goods += a;
	}
	uint16 Place::Get_Num_Goods() {
		return _num_goods;
	}
	uint64 Shelf::Get_Num_Goods() {
		return _num_goods;
	}
	uint64 Rack::Get_Num_Goods() {
		return _num_goods;
	}
	uint64 Warehouse::Get_Num_Goods() {
		return _num_goods;
	}
	uint64 Storage::Get_Num_Goods() {
		return _num_goods;
	}
	void Place::Set_Num_Goods(uint16 num_goods) {
		_num_goods
	}
	void Shelf::Set_Num_Goods(uint64 num_goods) {

	}
	void Rack::Set_Num_Goods(uint64 num_goods) {

	}
	void Warehouse::Set_Num_Goods(uint64 num_goods) {

	}
	void Storage::Set_Num_Goods(uint64 num_goods) {

	}


	bool Place::invariant() {
		return (_num_goods <= MAX_GOODS)
			&& ((_isLabeled && (int)_label <= 99) || !_isLabeled);
	}
	bool Shelf::invariant() {
		return (_num_goods <= MAX_PLACE * MAX_GOODS);
	}
	bool Rack::invariant() {
		return (_num_goods <= MAX_SHELF * MAX_PLACE * MAX_GOODS);
	}
	bool Warehouse::invariant() {
		return (_num_goods <= (MAX_RACK * MAX_SHELF * MAX_PLACE * (uint64)MAX_GOODS
			+ (MAX_PLACE * MAX_GOODS))); //+handyShelf
	}
	bool Storage::invariant() {
		return (_num_goods <= (uint64)((MAX_RACK * MAX_SHELF * MAX_PLACE * (uint64)MAX_GOODS + (MAX_PLACE * (uint64)MAX_GOODS)) * MAX_WAREHOUSE
			+ (MAX_PLACE * (uint64)MAX_GOODS) //+handyShelf
			+ (MAX_SHELF * MAX_PLACE * (uint64)MAX_GOODS))); //+handyRack
	}


	uint64 Shelf::Set_Size(const uint8 ns0) { //BaCa won't allow n3w keyword
		uint8 a = _size < ns0 ? _size : ns0;
		uint8 b = _size > ns0 ? _size : ns0;

		uint64 delta = 0;
		for (int i = a; i < b; i++) {
			delta += _place[i].Set_Value(0, empty);
		}
		_size = ns0;
		_num_goods += delta;
		return delta;
	}
	uint64 Shelf::Get_Num_Goods() {
		return _num_goods;
	}
	Place& Shelf::Get_Place(const uint8 p) {
		return _place[p];
	}

	uint64 Rack::Set_Size(const uint8 ns0, const uint8 ns1) {
		uint8 a = _size < ns0 ? _size : ns0;
		uint8 b = _size > ns0 ? _size : ns0;
		uint64 delta = 0;
		for (int i = a; i < b; i++) {
			delta += _shelf[i].Set_Size(ns1);
		}
		_size = ns0;
		_num_goods += delta;
		return delta;
	}

	uint64 Warehouse::Set_Size(const uint8 ns0, const uint8 ns1, const uint8 ns2) {
		uint8 a = _size < ns0 ? _size : ns0;
		uint8 b = _size > ns0 ? _size : ns0;
		uint64 delta = 0;
		for (int i = a; i < b; i++) {
			delta += _rack[i].Set_Size(ns1, ns2);
		}
		_size = ns0;
		_num_goods += delta;
		return delta;
	}
	uint64 Storage::Set_Size(const uint8 ns0, const uint8 ns1, const uint8 ns2, const uint8 ns3) {
		uint8 a = _size < ns0 ? _size : ns0;
		uint8 b = _size > ns0 ? _size : ns0;
		uint64 delta = 0;
		for (int i = a; i < b; i++) {
			delta += _warehouse[i].Set_Size(ns1, ns2, ns3);
		}
		_size = ns0;
		_num_goods += delta;
		return delta;
	}


	bool Storage::ReadAndCheck(int* const w = 0, int* const r = 0, int* const s = 0, int* const p = 0,
		int* const a = 0,
		int* const w1 = 0, int* const r1 = 0, int* const s1 = 0, int* const p1 = 0) {

		if (w) cin >> *w;
		if (r) cin >> *r;
		if (s) cin >> *s;
		if (p) cin >> *p;
		if (w1) cin >> *w1;
		if (r1) cin >> *r1;
		if (s1) cin >> *s1;
		if (p1) cin >> *p1;
		if (a) cin >> *a;

		uint8 errorCount = 0;

		errorCount += w && (*w > MAX_WAREHOUSE || *w < 0);
		errorCount += r && (*r > MAX_RACK || *r < 0);
		errorCount += s && (*s > MAX_SHELF || *s < 0);
		errorCount += p && (*p > MAX_PLACE || *p < 0);
		errorCount += w1 && (*w1 > MAX_WAREHOUSE || *w1 < 0);
		errorCount += r1 && (*r1 > MAX_RACK || *r1 < 0);
		errorCount += s1 && (*s1 > MAX_SHELF || *s1 < 0);
		errorCount += p1 && (*p1 > MAX_PLACE || *p1 < 0);
		errorCount += a && (*a > MAX_GOODS || *a < 0);

		if (errorCount) {
			IOS::PrintError;
			return false;
		}
		else return true;
	}

	void Storage::Fill(const uint8 w, const uint8 r, const uint8 s, const uint8 p, uint8 a) {
		a = a < MAX_GOODS ? a : MAX_GOODS;
		//warehouse - i
		//shelf - k
		//rack - j
		//place - l
		uint64 delta = 0;
		_size = w;
		for (int i = 0; i < w; i++) {
			_warehouse[i]._size = r;
			for (int j = 0; j < r; j++) {
				_warehouse[i]._rack[j]._size = s;
				for (int k = 0; k < s; k++) {
					_warehouse[i]._rack[j]._shelf[k]._size = p;
					delta = 0;
					for (int l = 0; l < p; l++) {
						delta += _warehouse[i]._rack[j]._shelf[k]._place[l].Set_Value(a, empty);
					}
					_warehouse[i]._rack[j]._shelf[k].Set_Num_Goods(
						delta + _warehouse[i]._rack[j]._shelf[k].Get_Num_Goods());

				}
			}
			_warehouse[i]._handyShelf._size = p;
			for (int l = 0; l < p; l++) {
				delta += _warehouse[i]._handyShelf._place[l].Set_Value(a, empty);
			}
		}
		_handyRack._size = s;
		for (int k = 0; k < s; k++) {
			_handyRack._shelf[k]._size = p;
			for (int l = 0; l < p; l++) {
				delta += _handyRack._shelf[k]._place[l].Set_Value(a, empty);
			}
		}
		_handyShelf._size = p;
		for (int l = 0; l < _handyShelf._size; l++) {
			delta += _handyShelf._place[l].Set_Value(a, empty);
		}
	}

}
using namespace Storage_NS;

// struct store {
// 	static Storage storage;
// }

//SECTION MAIN
int main(int argc, const char** argv)
{
	static Storage storage;
	//static Storage special_storage(, num_racks=1);

	int w = 0;
	int r = 0;
	int s = 0;
	int p = 0;
	int a = 0;

	//Target Values:
	int w1 = 0;
	int r1 = 0;
	int s1 = 0;
	int p1 = 0;

	string opSelection = "\0";
	string arg = "\0";

	while (opSelection != "END")
	{
		cin >> opSelection;
		string OP = opSelection.find('-') != std::string::npos ?
			opSelection.substr(0, opSelection.find('-')) : opSelection;

		if (OP == "END") { //Note Exit

		}
		else if (OP == "SET") {
			arg = opSelection.substr(opSelection.find('-') + 1, opSelection.length() - OP.length());
			if (arg == "AP") { //Note SET-AP
				if (storage.ReadAndCheck(&w, &r, &s, &p))
					storage._warehouse[w]._rack[r]._shelf[s].Set_Size(p);
			}
			else if (arg == "AS") { //Note SET-AS
				if (storage.ReadAndCheck(&w, &r, &s, &p))
					storage._warehouse[w]._rack[r].Set_Size(s, p);
			}
			else if (arg == "AR") { //Note SET-AR
				if (storage.ReadAndCheck(&w, &r, &s, &p))
					storage._warehouse[w].Set_Size(r, s, p);
			}
			else if (arg == "AW") { //Note Set-AW
				if (storage.ReadAndCheck(&w, &r, &s, &p))
					storage._warehouse[w]._rack[r].Set_Size(s, p);
			}
			else if (arg == "HW") { //Note SET-HW
				if (storage.ReadAndCheck(&w, 0, 0, &p))
					storage._warehouse[w]._handyShelf.Set_Size(p);
			}
			else if (arg == "HR") { //Note SET-HR
				if (storage.ReadAndCheck(0, 0, &s, &p))
					storage._handyRack.Set_Size(s, p);
			}
			else if (arg == "HS") { //Note SET-HS
				if (storage.ReadAndCheck(0, 0, 0, &p))
					storage._handyShelf.Set_Size(p);
			}
		}
		else if (OP == "PUT") {
			arg = opSelection.substr(opSelection.find('-') + 1, opSelection.length() - OP.length());
			if (arg == "W") { //Note PUT-W
				if (storage.ReadAndCheck(&w, &r, &s, &p, &a))
					storage._warehouse[w]._rack[r]._shelf[s]._place[p].Put(a);
			}
			else if (arg == "H") { //Note PUT-H
				if (storage.ReadAndCheck(&w, &p, 0, 0, &a))
					storage._warehouse[w]._handyShelf._place[p].Put(a);
			}
			else if (arg == "R") { //Note PUT-R
				if (storage.ReadAndCheck(0, 0, &s, &p, &a))
					storage._handyRack._shelf[s]._place[p].Put(a);
			}
			else if (arg == "S") { //Note PUT-S
				if (storage.ReadAndCheck(0, 0, 0, &p, &a))
					storage._handyShelf._place[p].Put(a);
			}
		}
		else if (OP == "FILL") { //Note FILL
			if (storage.ReadAndCheck(&w, &r, &s, &p, &a))
				storage.Fill(w, r, s, p, a);
		}
		else if (OP == "POP") {
			arg = opSelection.substr(opSelection.find('-') + 1, opSelection.length() - OP.length());
			if (arg == "W") { //Note POP-W
				if (storage.ReadAndCheck(&w, &r, &s, &p, &a))
					storage._warehouse[w]._rack[r]._shelf[s]._place[p].Pop(a);
			}
			else if (arg == "H") { //Note POP-H
				if (storage.ReadAndCheck(&w, &p, 0, 0, &a))
					storage._warehouse[w]._handyShelf._place[p].Pop(a);
			}
			else if (arg == "R") { //Note POP-R
				if (storage.ReadAndCheck(0, 0, &s, &p, &a))
					storage._handyRack._shelf[s]._place[p].Pop(a);
			}
			else if (arg == "S") { //Note POP-S
				if (storage.ReadAndCheck(0, 0, 0, &p, &a))
					storage._handyShelf._place[p].Pop(a);
			}
		}
		else if (OP == "MOV")
			if (arg == "W") { //Note MOV-W
				if (storage.ReadAndCheck(&w, &r, &s, 0, &a, &w1, &r1, &s1, &p1))
					storage._warehouse[w]._rack[r]._shelf[s]._place[p1].Move(
						storage._warehouse[w1]._rack[r1]._shelf[s1]._place[p1], a);
			}
			else if (arg == "H") { //Note MOV-H
				if (storage.ReadAndCheck(&w, &r, &s, &p, &a))
					storage._warehouse[w]._rack[r]._shelf[s]._place[p].Move(
						storage._warehouse[w1]._handyShelf._place[p], a);
			}
			else if (arg == "R") { //Note MOV-R
				if (storage.ReadAndCheck(&w, &r, &s, 0, &a, 0, 0, &s1, &p1))
					storage._warehouse[w]._rack[r]._shelf[s]._place[p1].Move(
						storage._handyRack._shelf[s1]._place[p1], a);
			}
			else if (arg == "S") {  //Note MOV-S
				if (storage.ReadAndCheck(0, 0, &s, &p, &a))
					storage._handyRack._shelf[s]._place[p].Move(
						storage._handyShelf._place[p], a);
			}
			else if (OP == "GET")
			{
				if (arg == "E") { //Note GET-E
					cout << goods_sum << endl;
				}

				else if (arg == "SW") {
					if (storage.ReadAndCheck(&w, &r, &s))
						cout << storage._warehouse[w]._rack[r]._shelf[s].Get_Num_Goods() << endl;
				}
			}

	}

	return 0;
}