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
	uint64 goods_sum = 0;

	enum PlaceState : bool {
		empty = 0 //Used to set empty label
	};

	struct Link {
		Shelf* parent[MAX_PLACE];
	};

	struct Place {


		uint16 num_goods; //Number of goods stored in Place upto 65535


		uint8 label;     //  isLabeled ==> label in [0..99]
		bool isLabeled;  // !isLabeled ==> label undefined
		// uint8 id;
		// Shelf& parent;

		Place() : num_goods(0), isLabeled(false), label(0) {}

		void SetLabel(uint8 label) {
			assert(!this->isLabeled); // TODO
			this->label = label;
			isLabeled = true;
		}

		uint8 GetLabel() {
			assert(this->isLabeled);
			return this->label;
		}

		bool CheckLabeled() {
			return this->isLabeled;
		}

		// Place() : goods(0), label(0), isLabeled(false), parent(nullptr) {}
		void Clear();
		void SetValue(const uint16, const uint8);
		void SetValue(const uint16, const PlaceState);
		void Put(uint16);
		void Pop(uint16);
		void Move(Place&, uint16);
		uint16 get_num_goods();

		bool invariant();
	};
	struct Shelf {
		uint8 size; //Number of Places stored in Shelf upto 128
		Place 	m_place[MAX_PLACE];
		uint64 num_goods;
		//uint8 id;

		Shelf() {
			size = 0;
			num_goods = 0;
			// 	for (uint8 i = 0; i < MAX_PLACE; i++) {
			// 		m_place[i].id = i;
			// 	}
			// 
		}
		inline void SetSize(const uint8);
		uint64 GetSum();

		Place& GetPlace(const uint8 p) {
			return m_place[p];
		}
	};

	struct Rack;
	struct Warehouse;
	struct Storage;

	void Place::Clear() {
		num_goods = 0;
		label = 0;
		isLabeled = false;
	}
	void Place::SetValue(const uint16 ngoods, const uint8 nlabel) {
		num_goods = ngoods;
		isLabeled = true;
		label = nlabel;

		goods_sum += (ngoods - num_goods);
	}
	void Place::SetValue(const uint16 ngoods, PlaceState state) {
		if (state == empty) {
			num_goods = ngoods;
			isLabeled = false;
		}

		goods_sum += (ngoods - num_goods);
	}

	void Place::Put(uint16 add) {
		add = (num_goods + add <= MAX_GOODS) ? add : MAX_GOODS - num_goods;
		num_goods += add;
		// parent[id].sum += num_goods;
		goods_sum += num_goods;
	}
	void Place::Pop(uint16 sub) {
		sub = (num_goods - sub > 0) ? sub : num_goods;
		num_goods -= sub;
		goods_sum -= sub;
	}
	void Place::Move(Place& target, uint16 a) {
		a = (a < num_goods) ? a : num_goods;
		a = (a + target.num_goods < MAX_GOODS) ? a : (MAX_GOODS - target.num_goods);
		num_goods -= a;
		target.num_goods += a;
	}
	uint16 Place::get_num_goods() {
		return num_goods;
	}

	bool Place::invariant() {
		return this->num_goods <= MAX_GOODS; //&&
	}


	void Shelf::SetSize(const uint8 ns0) { //BaCa won't allow n3w keyword
		uint8 a = size < ns0 ? size : ns0;
		uint8 b = size > ns0 ? size : ns0;

		for (size_t i = a; i < b; i++) {
			m_place[i].SetValue(0, empty);
		}
		size = ns0;
	}
	uint64 Shelf::GetSum() {
		return num_goods;
	}


	struct Rack {

		uint8 size; //Number of Shelves stored in Rack upto 128 
		Shelf m_shelf[MAX_SHELF];
		uint64 sum;
		Rack() : size(0) {	}

		void SetSize(const uint8 ns0, const uint8 ns1) {
			uint8 a = size < ns0 ? size : ns0;
			uint8 b = size > ns0 ? size : ns0;

			for (int i = a; i < b; i++) {
				m_shelf[i].SetSize(ns1);
			}
			size = ns0;
		}
		uint64 GetSum() {
			return sum;
		}
	};

	struct Warehouse {

		uint8 size; //Number of Racks stored in Warehouse upto 128
		Rack m_rack[MAX_RACK];
		Shelf m_handyShelf;

		Warehouse() : size(0) {}
		void SetSize(const uint8 ns0, const uint8 ns1, const uint8 ns2) {
			uint8 a = size < ns0 ? size : ns0;
			uint8 b = size > ns0 ? size : ns0;

			for (int i = a; i < b; i++) {
				m_rack[i].SetSize(ns1, ns2);
			}
			size = ns0;
		}
	};

	struct Storage {

		uint8 size; //Number of Warehouses stored in Storage upto 128
		Rack m_handyRack;
		Shelf m_handyShelf;
		Warehouse m_warehouse[MAX_WAREHOUSE];

		Storage() : size(0) {}
		void SetSize(const uint8 ns0, const uint8 ns1, const uint8 ns2, const uint8 ns3) {
			uint8 a = size < ns0 ? size : ns0;
			uint8 b = size > ns0 ? size : ns0;

			for (int i = a; i < b; i++) {
				m_warehouse[i].SetSize(ns1, ns2, ns3);
			}
			size = ns0;
		}
		bool ReadAndCheck(int* const w = 0, int* const r = 0, int* const s = 0, int* const p = 0,
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

		void Fill(const uint8 w, const uint8 r, const uint8 s, const uint8 p, uint8 a) {
			a = a < MAX_GOODS ? a : MAX_GOODS;
			//warehouse - i
			//shelf - k
			//rack - j
			//place - l

			size = w;
			for (int i = 0; i < w; i++) {
				m_warehouse[i].size = r;
				for (int j = 0; j < r; j++) {
					m_warehouse[i].m_rack[j].size = s;
					for (int k = 0; k < s; k++) {
						m_warehouse[i].m_rack[j].m_shelf[k].size = p;
						for (int l = 0; l < p; l++) {
							m_warehouse[i].m_rack[j].m_shelf[k].m_place[l].SetValue(a, empty);
						}
					}
				}
				m_warehouse[i].m_handyShelf.size = p;
				for (int l = 0; l < p; l++) {
					m_warehouse[i].m_handyShelf.m_place[l].isLabeled = false;
					m_warehouse[i].m_handyShelf.m_place[l].num_goods = a;
				}
			}
			m_handyRack.size = s;
			for (int k = 0; k < s; k++) {
				m_handyRack.m_shelf[k].size = p;
				for (int l = 0; l < p; l++) {
					m_handyRack.m_shelf[k].m_place[l].isLabeled = false;
					m_handyRack.m_shelf[k].m_place[l].num_goods = a;
				}
			}
			m_handyShelf.size = p;
			for (int l = 0; l < m_handyShelf.size; l++) {
				m_handyShelf.m_place[l].isLabeled = false;
				m_handyShelf.m_place[l].num_goods = a;
			}
		}
	};
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
					storage.m_warehouse[w].m_rack[r].m_shelf[s].SetSize(p);
			}
			else if (arg == "AS") { //Note SET-AS
				if (storage.ReadAndCheck(&w, &r, &s, &p))
					storage.m_warehouse[w].m_rack[r].SetSize(s, p);
			}
			else if (arg == "AR") { //Note SET-AR
				if (storage.ReadAndCheck(&w, &r, &s, &p))
					storage.m_warehouse[w].SetSize(r, s, p);
			}
			else if (arg == "AW") { //Note Set-AW
				if (storage.ReadAndCheck(&w, &r, &s, &p))
					storage.m_warehouse[w].m_rack[r].SetSize(s, p);
			}
			else if (arg == "HW") { //Note SET-HW
				if (storage.ReadAndCheck(&w, 0, 0, &p))
					storage.m_warehouse[w].m_handyShelf.SetSize(p);
			}
			else if (arg == "HR") { //Note SET-HR
				if (storage.ReadAndCheck(0, 0, &s, &p))
					storage.m_handyRack.SetSize(s, p);
			}
			else if (arg == "HS") { //Note SET-HS
				if (storage.ReadAndCheck(0, 0, 0, &p))
					storage.m_handyShelf.SetSize(p);
			}
		}
		else if (OP == "PUT") {
			arg = opSelection.substr(opSelection.find('-') + 1, opSelection.length() - OP.length());
			if (arg == "W") { //Note PUT-W
				if (storage.ReadAndCheck(&w, &r, &s, &p, &a))
					storage.m_warehouse[w].m_rack[r].m_shelf[s].m_place[p].Put(a);
			}
			else if (arg == "H") { //Note PUT-H
				if (storage.ReadAndCheck(&w, &p, 0, 0, &a))
					storage.m_warehouse[w].m_handyShelf.m_place[p].Put(a);
			}
			else if (arg == "R") { //Note PUT-R
				if (storage.ReadAndCheck(0, 0, &s, &p, &a))
					storage.m_handyRack.m_shelf[s].m_place[p].Put(a);
			}
			else if (arg == "S") { //Note PUT-S
				if (storage.ReadAndCheck(0, 0, 0, &p, &a))
					storage.m_handyShelf.m_place[p].Put(a);
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
					storage.m_warehouse[w].m_rack[r].m_shelf[s].m_place[p].Pop(a);
			}
			else if (arg == "H") { //Note POP-H
				if (storage.ReadAndCheck(&w, &p, 0, 0, &a))
					storage.m_warehouse[w].m_handyShelf.m_place[p].Pop(a);
			}
			else if (arg == "R") { //Note POP-R
				if (storage.ReadAndCheck(0, 0, &s, &p, &a))
					storage.m_handyRack.m_shelf[s].m_place[p].Pop(a);
			}
			else if (arg == "S") { //Note POP-S
				if (storage.ReadAndCheck(0, 0, 0, &p, &a))
					storage.m_handyShelf.m_place[p].Pop(a);
			}
		}
		else if (OP == "MOV")
			if (arg == "W") { //Note MOV-W
				if (storage.ReadAndCheck(&w, &r, &s, 0, &a, &w1, &r1, &s1, &p1))
					storage.m_warehouse[w].m_rack[r].m_shelf[s].m_place[p1].Move(
						storage.m_warehouse[w1].m_rack[r1].m_shelf[s1].m_place[p1], a);
			}
			else if (arg == "H") { //Note MOV-H
				if (storage.ReadAndCheck(&w, &r, &s, &p, &a))
					storage.m_warehouse[w].m_rack[r].m_shelf[s].m_place[p].Move(
						storage.m_warehouse[w1].m_handyShelf.m_place[p], a);
			}
			else if (arg == "R") { //Note MOV-R
				if (storage.ReadAndCheck(&w, &r, &s, 0, &a, 0, 0, &s1, &p1))
					storage.m_warehouse[w].m_rack[r].m_shelf[s].m_place[p1].Move(
						storage.m_handyRack.m_shelf[s1].m_place[p1], a);
			}
			else if (arg == "S") {  //Note MOV-S
				if (storage.ReadAndCheck(0, 0, &s, &p, &a))
					storage.m_handyRack.m_shelf[s].m_place[p].Move(
						storage.m_handyShelf.m_place[p], a);
			}
			else if (OP == "GET")
			{
				if (arg == "E") { //Note GET-E
					cout << goods_sum << endl;
				}

				else if (arg == "SW") {
					if (storage.ReadAndCheck(&w, &r, &s))
						cout << storage.m_warehouse[w].m_rack[r].m_shelf[s].GetSum() << endl;
				}
			}

	}

	return 0;
}