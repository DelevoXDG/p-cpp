// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl; using std::string;

typedef unsigned char uint8;
typedef unsigned short int uint16;

namespace MAX_CONSTS {
	const uint16 MAX_GOODS = 65535;
	const uint8 MAX_UNI = 128;
	const uint8 MAX_PLACE = 128;
	const uint8 MAX_SHELF = 128;
	const uint8 MAX_RACK = 128;
	const uint8 MAX_WAREHOUSE = 128;
	const uint8 MAX_STORAGE = 128;
}
using namespace MAX_CONSTS;


namespace IOS {

	void Output() { std::cout << endl; }

	template<typename FirstT, typename ... ArgsT>
	void Output(FirstT first, const ArgsT&... args) {
		std::cout << first << " ";
		Output(args...);
	}

	void Input() { ; }

	template <typename FirstT, typename ... ArgsT>
	void Input(FirstT& first, const ArgsT&...args) {
		std::cin >> first;
		Input(args...);
	}

	void PrintError() {
		std::cout << "error" << endl;
	}

}

namespace HelperFuncs {

}

//SECTION STORAGE STRUCTS
namespace Storage_Structs {

	struct Place {
	public:
		uint16 maxSize = MAX_GOODS;
		uint16 quantity; //Number of goods stored in Place upto 65535
		uint8 size;
		uint8 label = 0;
		bool isLabeled = false;

	public:
		Place() : quantity(0), isLabeled(false) {}

		void Clear() {
			quantity = 0;
			label = 0;
			isLabeled = false;
		}
		void PrintLabel() {
			printf("%02d", label);
		}

	};

	struct Shelf {
	public:
		uint8 maxSize = MAX_PLACE;
		uint8 size; //Number of Places stored in Shelf upto 128
		Place m_place[MAX_PLACE];


	public:
		Shelf() : size(0) {}
		void Clear(uint8 a, uint8 b) {
			for (size_t i = a; i < b; i++) {
				m_place[i].Clear();
			}
		}

		void SetSize(uint8 new_size_0) {
			size_t a = size < new_size_0 ? size : new_size_0;
			size_t b = size > new_size_0 ? size : new_size_0;

			for (size_t i = a; i < b; i++) {
				m_place[i].Clear();
			}
			size = new_size_0;
		}

	};


	struct Rack {
	public:
		uint8 maxSize = MAX_SHELF;
		uint8 size; //Number of Shelves stored in Rack upto 128 
		Shelf m_shelf[MAX_SHELF];

	public:
		Rack() : size(0) {}
		void Clear(uint8 a, uint8 b) {
			for (size_t i = a; i < b; i++) {
				m_shelf[i].Clear(0, 128);
			}
		}
		void SetSize(uint8 new_size_0, uint8 new_size_1) {
			size_t a = size < new_size_0 ? size : new_size_0;
			size_t b = size > new_size_0 ? size : new_size_0;

			for (size_t i = a; i < b; i++) {
				m_shelf[i].SetSize(new_size_1);
			}
			size = new_size_0;
		}
	};

	struct Warehouse {
	public:
		Warehouse() : size(0) {}
		uint8 maxSize = MAX_RACK;
		uint8 size; //Number of Racks stored in Warehouse upto 128
		Rack m_rack[MAX_RACK];
		Shelf m_handyShelf;

	public:
		void SetSize(uint8 new_size_0, uint8 new_size_1, uint8 new_size_2) {
			size_t a = size < new_size_0 ? size : new_size_0;
			size_t b = size > new_size_0 ? size : new_size_0;

			for (size_t i = a; i < b; i++) {
				m_rack[i].SetSize(new_size_1, new_size_2);
			}
			size = new_size_0;
		}
	};

	struct Storage {
	public:
		uint8 maxSize = MAX_WAREHOUSE;
		uint8 size; //Number of Warehouses stored in Storage upto 128
		Warehouse m_warehouse[MAX_WAREHOUSE];
		Rack m_handyRack;
		Shelf m_handyShelf;
	public:
		void SetSize(uint8 new_size_0, uint8 new_size_1, uint8 new_size_2, uint8 new_size_3) {
			size_t a = size < new_size_0 ? size : new_size_0;
			size_t b = size > new_size_0 ? size : new_size_0;

			for (size_t i = a; i < b; i++) {
				m_warehouse[i].SetSize(new_size_1, new_size_2, new_size_3);
			}
			size = new_size_0;
		}

	};

}
using namespace Storage_Structs;

//SECTION MAIN
int main(int argc, const char** argv)
{
	static Storage storage;

	uint16 w = 0;
	uint16 r = 0;
	uint16 s = 0;
	uint16 p = 0;

	string opSelection = "\0";
	string arg = "\0";


	while (opSelection != "END")
	{


		IOS::Input(opSelection);
		//IOS::Input<string&, uint16&>(opSelection, index);
		string OP = opSelection.substr(0, opSelection.find('-'));
		//IOS::Output(OP, 1, index);


		if (OP == "END") { //Note Exit

		}
		else if (OP == "SET") {
			arg = opSelection.substr(opSelection.find('-') + 1, 2);
			if (arg == "AP") { //Note SET-AP
				//IOS::Input(w, r, s, p);
				if (w > 128 || r > 128 || s > 128 || p > 128) {
					IOS::PrintError();
				}
				storage.m_warehouse[w].m_rack[r].m_shelf[s].SetSize(p);
			}
			else if (arg == "AS") { //Note SET-AS
				//IOS::Input(w, r, s, p);
				if (w > 128 || r > 128 || s > 128 || p > 128) {
					IOS::PrintError;
				}
				storage.m_warehouse[w].m_rack[r].SetSize(s, p);
			}
			else if (OP == "PUT") {

			}
			else if (OP == "FILL") {

			}

		}
		return 0;
	}
}