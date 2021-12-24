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
	Shelf m_handyShelf_storage[MAX_PLACE];
};



int main(int argc, const char** argv)
{
	string opSelection = NULL;

	while (opSelection != "END")
	{
		cin >> opSelection;
		string OP = opSelection.substr(0, opSelection.find('-'));
		char arg = opSelection[4];


		if (OP == "END") {
			return 0;
		}
		else if (OP == "SET") {

		}
		else if (OP == "PUT") {

		}
		else if (OP == "FILL") {

		}

	}
	return 0;
}