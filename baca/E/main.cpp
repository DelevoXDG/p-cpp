// Maksim Zdobnikau

#include <iostream>

using std::cin; using std::cout; using std::endl; using std::string;

#define nullptr NULL
typedef unsigned char uint8;
typedef unsigned short int uint16;

namespace IOS {

	void Output() { std::cout << endl; }

	template<typename FirstT, typename ... ArgsT>
	void Output(FirstT first, ArgsT&... args) {
		std::cout << first;
		Output(args...);
	}

	void Input() { ; }

	template <typename FirstT, typename ... ArgsT>
	void Input(FirstT& first, ArgsT&...args) {
		std::cin >> first;
		Input(args...);
	}

	void PrintError() {
		std::cout << "error" << endl;
	}
}

//SECTION STORAGE STRUCTS
namespace Storage_NS {

	const uint16 MAX_GOODS = 65535;
	const uint8 MAX_PLACE = 128;
	const uint8 MAX_SHELF = 128;
	const uint8 MAX_RACK = 128;
	const uint8 MAX_WAREHOUSE = 128;
	const uint8 MAX_STORAGE = 128;

	struct Place {

		uint16 goods; //Number of goods stored in Place upto 65535
		uint8 label;
		bool isLabeled;

		Place() : goods(0), label(0), isLabeled(false) {}

		void Clear() {
			goods = 0;
			label = 0;
			isLabeled = false;
		}
		void SetValue(const uint16 ngoods, const bool nisLabeled, const uint8 nlabel) {
			goods = ngoods;
			isLabeled = nisLabeled;
			label = nlabel;
		}
		void Put(const uint16 add) {
			goods = (goods + add < MAX_GOODS) ? (goods + add) : MAX_GOODS;
		}
		void Pop(const uint16 sub) {
			goods = (goods - sub > 0) ? (goods - sub) : 0;
		}
		void Move(Place& target, uint16 a) {
			a = (a < goods) ? a : goods;
			a = (a + target.goods < MAX_GOODS) ? a : (MAX_GOODS - target.goods);

			goods -= a;
			target.goods += a;
		}
	};

	struct Shelf {
		uint8 size; //Number of Places stored in Shelf upto 128
		Place m_place[MAX_PLACE];

		Shelf() : size(0) {}

		void SetSize(const uint8 ns0) { //BaCa won't allow n3w keyworc
			uint8 a = size < ns0 ? size : ns0;
			uint8 b = size > ns0 ? size : ns0;

			for (size_t i = a; i < b; i++) {
				m_place[i].SetValue(0, false, 0);
			}
			size = ns0;
		}

	};

	struct Rack {

		uint8 size; //Number of Shelves stored in Rack upto 128 
		Shelf m_shelf[MAX_SHELF];


		Rack() : size(0) {}

		void SetSize(const uint8 ns0, const uint8 ns1) {
			uint8 a = size < ns0 ? size : ns0;
			uint8 b = size > ns0 ? size : ns0;

			for (int i = a; i < b; i++) {
				m_shelf[i].SetSize(ns1);
			}
			size = ns0;
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
			a = a <= MAX_GOODS ? a : MAX_GOODS;
			size = w;
			for (int i = 0; i < w; i++) {
				m_warehouse[i].size = r;
				for (int j = 0; j < r; j++) {
					m_warehouse[i].m_rack[j].size = s;
					for (int k = 0; k < s; k++) {
						m_warehouse[i].m_rack[j].m_shelf[k].size = p;
						for (int l = 0; l < p; l++) {
							m_warehouse[i].m_rack[j].m_shelf[k].m_place[l].SetValue(a, false, 0);
						}
					}
				}
				m_warehouse[i].m_handyShelf.size = p;
				for (int l = 0; l < p; i++) {
					m_warehouse[i].m_handyShelf.m_place[l].SetValue(a, false, 0);
				}
			}
			m_handyRack.size = r;
			for (int i = 0; i < r; i++) {
				m_handyRack.m_shelf[i].size = s;
				for (int j = 0; j < p; j++)
					m_handyRack.m_shelf[i].m_place[j].SetValue(a, false, 0);
			}
			m_handyShelf.size = p;
			for (int i = 0; i < p; i++) {
				m_handyShelf.m_place[i].SetValue(a, false, 0);
			}
		}
	};

}
using namespace Storage_NS;

//SECTION MAIN
int main(int argc, const char** argv)
{
	static Storage storage;

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
		IOS::Input(opSelection);
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

	}

	return 0;
}