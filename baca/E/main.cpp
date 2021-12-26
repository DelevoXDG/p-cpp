// Maksim Zdobnikau

#include <iostream>
using std::cin; using std::cout; using std::endl; using std::string;

typedef unsigned char uint8;
typedef unsigned short int uint16;

namespace MAX_CONSTS {
	const uint16 MAX_PLACE = 65535;
	const uint8 MAX_SHELF = 128;
	const uint8 MAX_RACK = 128;
	const uint8 MAX_WAREHOUSE = 128;
	const uint8 MAX_STORAGE = 128;
}

using namespace MAX_CONSTS;

namespace IOS {

	void Write() { std::cout << endl; }

	template<typename FirstT, typename ... ArgsT>
	void Write(FirstT first, const ArgsT&... args) {
		std::cout << first << " ";
		Write(args...);
	}

	void Read() { ; }

	template <typename FirstT, typename ... ArgsT>
	void Read(FirstT& first, const ArgsT&...args) {
		std::cin >> first;
		Read(args...);
	}

	void ShowError() {
		std::cout << "error" << endl;
	}
}

//SECTION STORAGE STRUCTS
struct Place {
public:
	// uint16 maxSize = MAX_PLACE;
	uint16 size;
	char label = 0;
	bool isLabeled = false;

public:
	//void Set


};

struct Shelf {
public:
	// uint8 maxSize = MAX_SHELF;
	uint8 size;
	Place m_place[MAX_PLACE];
};

struct Rack {
public:
	// uint8 maxSize = MAX_RACK;
	uint8 size;
	Shelf m_shelf[MAX_SHELF];

};

struct Warehouse {
public:
	// uint8 maxSize = MAX_WAREHOUSE;
	uint8 size;
	Rack m_rack[MAX_RACK];
	Shelf m_handyShelf[MAX_PLACE];

};

struct Storage {
public:
	// uint8 maxSize = MAX_STORAGE;
	uint8 size;
	Rack m_handyRack[MAX_RACK];
	Shelf m_handyShelf[MAX_SHELF];
};


//SECTION MAIN
int main(int argc, const char** argv)
{
	string opSelection = "\0";
	string arg = "\0";
	while (opSelection != "END")
	{
		uint16 index = 0;
		IOS::Read<string&, uint16&>(opSelection, index);
		string OP = opSelection.substr(0, opSelection.find('-'));
		IOS::Write(OP, 1, index);


		if (OP == "END") { //Note Exit

		}
		else if (OP == "SET") {
			arg = opSelection.substr(opSelection.find('-') + 1, 2);
			if (arg == "AP") { //Note SET-AP

			}
		}
		else if (OP == "PUT") {

		}
		else if (OP == "FILL") {

		}

	}
	return 0;
}