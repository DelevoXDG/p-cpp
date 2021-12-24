// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl; using std::string;

typedef unsigned char uint8;
typedef unsigned short int uint16;

const uint16 MAX_PLACE = 65535;
const uint8 MAX_SHELF = 128;
const uint8 MAX_RACK = 128;
const uint8 MAX_WAREHOUSE = 128;
const uint8 MAX_STORAGE = 128;

struct Place {
public:

	uint16 PlaceSize;

};

struct Shelf {
public:

	uint8 ShelfSize;
	Place m_place[MAX_PLACE];
};

struct Rack {
public:

	uint8 RackSize;
	Shelf m_shelf[MAX_SHELF];

};

struct Warehouse {
public:

	uint8 WarehouseSize;
	Rack m_rack[MAX_RACK];
	Shelf m_handyShelf_warehouse[MAX_PLACE];

};

struct Storage {
public:

	uint8 storageSize;
	Rack m_handyRack_storage[MAX_RACK];
	Shelf m_handyShelf_storage[MAX_SHELF];
};

//SECTION HELPER FUNCTIONS
struct IOS {
public:

	static void Output() {
		std::cout << std::endl;
	}

	template<typename First, typename ... T>
	static void Output(First arg, const T&... rest) {
		std::cout << arg << " ";
		Output(rest...);
	}
	static void Input() { ; }

	template <typename First, typename ... T>
	static void Input(First& arg, const T&...rest) {
		cin >> arg;
		Input(rest...);
	}
};


//SECTION MAIN
int main(int argc, const char** argv)
{
	string opSelection = "\0";
	string arg = "\0";
	while (opSelection != "END")
	{
		uint16 index = 0;
		IOS::Input<string&, uint16&>(opSelection, index);
		string OP = opSelection.substr(0, opSelection.find('-'));
		IOS::Output(OP, 1, index);


		if (OP == "END") {
		}
		else if (OP == "SET") {
			arg = opSelection.substr(opSelection.find('-') + 1, 2);
			if (arg == "AP") {

			}
		}
		else if (OP == "PUT") {

		}
		else if (OP == "FILL") {

		}

	}
	return 0;
}