// Maksim Zdobnikau

#include <iostream>

using std::cin; using std::cout; using std::endl;
//Replaced str1ng with char str1ngs just in case

typedef unsigned char uint8;
typedef unsigned short int uint16;
typedef unsigned long long uint64;

enum Instruction {
	//lowercase - location
	//UPPERCASE - n3w value 

	SET_AP, //w r s P
	SET_AS, //w r S P 
	SET_AR, //w R S P 
	SET_AW,	//W R S P 
	SET_HW, //w 0 0 P
	SET_HR, //S 0 0 P 
	SET_HS,	//0 0 0 P

	FILL, //W R S P A 

	PUT_W, //w r s p A 
	PUT_H, //w 0 0 p A
	PUT_R, //s 0 0 p A 
	PUT_S, //0 0 0 p A

	POP_W, //w r s p A 
	POP_H, //w p A
	POP_R, //s p A 
	POP_S, //p A

	MOV_W, //w r s 0 w1 r1 s1 p1 A
	MOV_H, //w r s p A 
	MOV_R, //w r s 0 0 0 0 s1 p A
	MOV_S, //s p A

	GET_E, //
	GET_W, //w
	GET_RW, // w r
	GET_RH, //
	GET_SW, //w r s 
	GET_SH, //w
	GET_SR, //s
	GET_S, //

	SET_LW, //w r s p dd 
	SET_LH, //w p dd
	SET_LR, //s p dd 
	SET_LS, // p dd

	GET_LW, //w r s p
	GET_LH, //w p 
	GET_LR, //s p
	GET_LS, //p

	END,
	undefined = 404
};

int cstr_find(char* str, char key) {

	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == key) return i; //Return position of Character
	}
	return -1; //Returns -1 if position was not found
}

void cstr_substr(char* str, char* substr, int begin, int end)
{
	int j = 0;
	for (int i = begin; i < end; i++) {
		substr[j] = str[i];
		j++;
	}
	substr[j] = '\0';
	//return substr;
}

int cstr_length(char* str) {
	int size = 0;
	for (int i = 0; str[i] != 0; i++) {
		size++;
	}
	return size;
}
int cstr_length(const char* str) {
	int size = 0;
	for (int i = 0; str[i] != 0;i++) {
		size++;
	}
	return size;
}
void cstr_copy(char* from, char* to) {
	int i = 0;
	for (i = 0; from[i] != 0;i++) {
		to[i] = from[i];
	}
	to[i] = '\0';

}
bool cstr_compare(char* str1, const char* str2) {
	if (cstr_length(str1) != cstr_length(str2)) return false;
	for (int i = 0; str1[i] != 0; i++) {
		if (str1[i] != str2[i]) return false;
	}

	return true; //cstrs are equal
}

Instruction opParse(char opSelection[]) {
	int dashPos = cstr_find(opSelection, '-');
	char OP[5] = { 0,0,0,0,0 };
	char arg[3] = { 0,0,0 };
	if (dashPos != -1) {
		int a = dashPos + 1;
		int b = cstr_length(opSelection) - cstr_length(OP);
		cstr_substr(opSelection, OP, 0, dashPos);
		cstr_substr(opSelection, arg, a, b);
	}
	else {
		cstr_copy(opSelection, OP);
	}

	if (cstr_compare(OP, "END")) return END; //Note Exit
	else if (cstr_compare(OP, "SET")) {
		if (cstr_compare(arg, "AP")) return SET_AP; //Note SET-AP
		else if (cstr_compare(arg, "AS")) return SET_AS;  //Note SET-AS
		else if (cstr_compare(arg, "AR")) return SET_AR; //Note SET-AR
		else if (cstr_compare(arg, "AW")) return SET_AW; //Note Set-AW
		else if (cstr_compare(arg, "HW")) return SET_HW; //Note SET-HW
		else if (cstr_compare(arg, "HR")) return SET_HR; //Note SET-HR
		else if (cstr_compare(arg, "HS")) return SET_HS; //Note SET-HS
		else if (cstr_compare(arg, "LW")) return SET_LW; //Note SET-LW
		else if (cstr_compare(arg, "LH")) return SET_LH; //Note SET-LH
		else if (cstr_compare(arg, "LR")) return SET_LR; //Note SET-LR
		else if (cstr_compare(arg, "LS")) return SET_LS; //Note SET-LS
	}
	else if (cstr_compare(OP, "FILL")) return FILL; //Note FILL
	else if (cstr_compare(OP, "PUT")) {
		if (cstr_compare(arg, "W")) return PUT_W; //Note PUT-W
		else if (cstr_compare(arg, "H")) return PUT_H;  //Note PUT-H
		else if (cstr_compare(arg, "R")) return PUT_R; //Note PUT-R
		else if (cstr_compare(arg, "S")) return PUT_S; //Note PUT-S
	}
	else if (cstr_compare(OP, "POP")) {
		if (cstr_compare(arg, "W")) return POP_W; //Note POP-W
		else if (cstr_compare(arg, "H")) return POP_H;  //Note POP-H
		else if (cstr_compare(arg, "R")) return POP_R; //Note POP-R
		else if (cstr_compare(arg, "S")) return POP_S; //Note POP-S
	}
	else if (cstr_compare(OP, "MOV")) {
		if (cstr_compare(arg, "W")) return MOV_W; //Note MOV-W
		else if (cstr_compare(arg, "H")) return MOV_H;  //Note MOV-H
		else if (cstr_compare(arg, "R")) return MOV_R; //Note MOV-R
		else if (cstr_compare(arg, "S")) return MOV_S; //Note MOV-S
	}
	else if (cstr_compare(OP, "GET")) {
		if (cstr_compare(arg, "E")) return GET_E; //Note GET-E
		else if (cstr_compare(arg, "W")) return GET_W; //Note GET-W
		else if (cstr_compare(arg, "RW")) return GET_RW; //Note GET-RW
		else if (cstr_compare(arg, "RH")) return GET_RH; //Note GET-RH
		else if (cstr_compare(arg, "SW")) return GET_SW; //Note GET-SW
		else if (cstr_compare(arg, "SH")) return GET_SH; //Note GET-SH
		else if (cstr_compare(arg, "SR")) return GET_SR; //Note GET-SR
		else if (cstr_compare(arg, "S")) return GET_S; //Note GET-S
		else if (cstr_compare(arg, "LW")) return GET_LW; //Note GET-LW
		else if (cstr_compare(arg, "LH")) return GET_LH; //Note GET-LH
		else if (cstr_compare(arg, "LR")) return GET_LR; //Note GET-LR
		else if (cstr_compare(arg, "LS")) return GET_LS; //Note GET-LS
	}
	return undefined;
}
//SECTION STORAGE STRUCTS
namespace Storage_NS {
	// namespace IOS {
	// 	void PrintError() {
	// 		std::cout << "error" << endl;
	// 	}
	// 	void PrintDD(char** const dd) {
	// 		std::cout << dd[0] << dd[1] << endl;
	// 	}
	// }
	namespace Storage_Params {
		const uint16 MAX_GOODS = 65535;
		const uint8 MAX_PLACE = 128;
		const uint8 MAX_SHELF = 128;
		const uint8 MAX_RACK = 128;
		const uint8 MAX_WAREHOUSE = 128;
		const uint8 MAX_STORAGE = 128;
		char LABEL_EMPTY[2] = { '-','-' };
		uint64 Storage_Sum = 0;
	}
	using namespace Storage_Params;
	uint64 errorCount = 0;

	struct Place;
	struct Shelf;
	struct Rack;
	struct Warehouse;
	struct Storage;

	enum PlaceArgs  /*: uint8  * scoped enums only available with '-std=c++11' or '-std=gnu++11'/ */ {
		LabelEmpty = 10, //Used to set empty label
		LabelOld = 11,
		ValueClear = 20, //Old value is cleared, used for FILL
	};

	struct Place {
	private:
		uint16 _num_goods; //Number of goods stored in Place [0...65535]
		char _label[2];    // [0..9][0...9]

	public:
		Place() : _num_goods(0)/*, _label{ '\0','\0' }*/ {
			//warning: extended initializer lists only available with '-std=c++11'  or '-std=gnu++11'
			_label[0] = '\0';
			_label[1] = '\0';
		}
		//Note Getters 
		char* Get_Label();
		uint16 Get_Num_Goods();
		bool Is_Labeled();

		//Note Setters
		void Set_Label(char[2]);
		void Set_Value(const uint16, const char[2]);
		void Set_Value(const uint16, const PlaceArgs);
		void Set_Value(const uint16, const PlaceArgs, const PlaceArgs);
		void Set_Num_Goods(const uint16);

		//Note Methods
		void Put(uint16);
		void Pop(uint16);
		void Move(Place&, uint16);

	};
	struct Shelf {
	private:
		uint8 _size; //Number of Places stored in Shelf [0...128]
	public:
		Place _place[MAX_PLACE];

		Shelf() : _size(0) {}

		//Note Getters 
		uint64 Get_Num_Goods();

		//Note Setters 
		void Set_All_Sizes(const uint8);
		uint8 Get_Size();
		void Set_Size(const uint8);

		//Note Methods
		uint64 Count_Sum();
	};
	struct Rack {
	private:
		uint8 _size; //Number of Shelves stored in Rack [0...128]
	public:
		Shelf _shelf[MAX_SHELF];
		Rack() : _size(0) {	}

		//Note Getters
		uint8 Get_Size();

		//Note Setters
		void Set_All_Sizes(const uint8, const uint8);
		void Set_Size(const uint8);

		//Note Methods
		uint64 Count_Sum();
	};
	struct Warehouse {
	private:
		uint8 _size; //Number of Racks stored in Warehouse [0...128]
	public:
		Rack _rack[MAX_RACK];
		Shelf _handyShelf;
		Warehouse() : _size(0) {}

		//Note Getters
		uint8 Get_Size();
		uint64 Get_Num_Goods();

		//Note Setters
		void Set_All_Sizes(const uint8, const uint8, const uint8);
		void Set_Size(const uint8);

		//Note Methods
		uint64 Count_Sum();
	};
	struct
		Storage {
	private:
		uint8 _size; //Number of Warehouses stored in Storage [0...128]
	public:

		Rack _handyRack;
		Shelf _handyShelf;
		Warehouse _warehouse[MAX_WAREHOUSE];

		Storage() : _size(0) {}
		//Note Getters
		uint8 Get_Size();
		static uint64 Get_Sum_Goods();

		//Note Setters
		void Set_All_Sizes(const uint8, const uint8, const uint8, const uint8);
		void Set_Size(const uint8);
		static void Set_Sum_Goods(const uint64);

		//Note Methods
		void Fill(const uint8, const uint8, const uint8, const uint8, uint16);
		uint64 Count_Sum();
		static void Add_Num_Goods(uint64);

		//Note ReadInputs
		bool ReadAndCheck(int* const, int* const, int* const, int* const,
			int* const,
			int* const, int* const, int* const, int* const,
			char* const);
		bool Check_Warehouse(const int w);
		bool Check_Rack(const int w, const int r);
		bool Check_Shelf(const int w, const int r, const int s);
		bool Check_Place(const int w, const int r, const int s, const int p);
		bool Check_Handy_Rack(const int s);
		bool Check_Handy_Rack_Shelf(const int s, const int p);
		bool Check_Handy_Shelf(const int p);
		bool Check_Warehouse_Handy_Shelf(const int w, const int p);
	};

	void Place::Set_Label(char label[2]) {
		_label[0] = label[0];
		_label[1] = label[1];
	}
	char* Place::Get_Label() {
		return (this->Is_Labeled() ? _label : LABEL_EMPTY);
	}
	bool Place::Is_Labeled() {
		return !(_label[0] == '\0' && _label[1] == '\0');
	}
	void Place::Set_Value(const uint16 num_goods, const char label[2]) {
		Storage::Add_Num_Goods(num_goods - _num_goods);
		_num_goods = num_goods;
		_label[0] = label[0];
		_label[1] = label[1];
	}
	void Place::Set_Value(const uint16 num_goods, const PlaceArgs labelState) {
		Storage::Add_Num_Goods(num_goods - _num_goods);
		_num_goods = num_goods;
		if (labelState == LabelOld) return;
		_label[0] = '\0';
		_label[1] = '\0';
	}
	void Place::Set_Value(const uint16 num_goods, const PlaceArgs labelState, const PlaceArgs changeState) {
		Storage::Add_Num_Goods(num_goods);
		_num_goods = num_goods;
		if (labelState == LabelOld) return;
		_label[0] = '\0';
		_label[1] = '\0';
	}

	void Place::Put(uint16 add) {
		add = (_num_goods + add <= MAX_GOODS) ? add : MAX_GOODS - _num_goods;
		_num_goods += add;
		Storage::Add_Num_Goods(add);
	}
	void Place::Pop(uint16 sub) {
		sub = (_num_goods - sub > 0) ? sub : _num_goods;
		_num_goods -= sub;
		Storage::Add_Num_Goods(-sub);
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
	void Place::Set_Num_Goods(const uint16 num_goods) {
		_num_goods = num_goods;
	}
	uint64 Storage::Get_Sum_Goods() {
		return Storage_Sum;
	}
	void Storage::Set_Sum_Goods(const uint64 num_goods) {
		Storage_Sum = num_goods;
	}
	void Storage::Add_Num_Goods(uint64 delta) {
		Storage_Sum += delta;
	}
	uint8 Shelf::Get_Size() {
		return _size;
	}
	uint8 Rack::Get_Size() {
		return _size;
	}
	uint8 Warehouse::Get_Size() {
		return _size;
	}
	uint8 Storage::Get_Size() {
		return _size;
	}
	void Shelf::Set_Size(const uint8 size) {
		_size = size;
	}
	void Rack::Set_Size(const uint8 size) {
		_size = size;
	}
	void Warehouse::Set_Size(const uint8 size) {
		_size = size;
	}
	void Storage::Set_Size(const uint8 size) {
		_size = size;
	}
	void Shelf::Set_All_Sizes(const uint8 size0) {
		for (int i = _size; i < size0; i++) {
			_place[i].Set_Value(0, LabelEmpty);
		}
		for (int i = _size; i-- > size0; ) {
			_place[i].Set_Value(0, LabelEmpty);
		}
		_size = size0;
	}
	void Rack::Set_All_Sizes(const uint8 size0, const uint8 size1) {
		for (int i = 0; i < size0; i++) {
			_shelf[i].Set_All_Sizes(size1);
		}
		for (int i = _size; i-- > size0; ) {
			_shelf[i].Set_All_Sizes(0);
		}
		_size = size0;
	}
	void Warehouse::Set_All_Sizes(const uint8 size0, const uint8 size1, const uint8 size2) {
		for (int i = 0; i < size0; i++) {
			_rack[i].Set_All_Sizes(size1, size2);
		}
		for (int i = _size; i-- > size0; ) {
			_rack[i].Set_All_Sizes(0, 0);
		}
		_size = size0;
	}
	void Storage::Set_All_Sizes(const uint8 size0, const uint8 size1, const uint8 size2, const uint8 size3) {
		for (int i = 0; i < size0; i++) {
			_warehouse[i].Set_All_Sizes(size1, size2, size3);
		}
		for (int i = _size; i-- > size0; ) {
			_warehouse[i].Set_All_Sizes(0, 0, 0);
		}
		_size = size0;
	}
	bool Storage::Check_Warehouse(const int w) {
		bool check = (w < _size);

		errorCount += !check;
		return check;
	}
	bool Storage::Check_Rack(const int w, const int r) {

		bool check = (
			this->Check_Warehouse(w)
			&& r < _warehouse[w].Get_Size());

		errorCount += !check;
		return check;
	}
	bool Storage::Check_Shelf(const int w, const int r, const int s) {
		bool check = (
			this->Check_Rack(w, r)
			&& s < _warehouse[w]._rack[r].Get_Size());

		errorCount += !check;
		return check;
	}
	bool Storage::Check_Place(const int w, const int r, const int s, const int p) {
		bool check = (
			this->Check_Shelf(w, r, s)
			&& p < _warehouse[w]._rack[r]._shelf[s].Get_Size());

		errorCount += !check;
		return check;
	}
	bool Storage::Check_Warehouse_Handy_Shelf(const int w, const int p) {
		bool check = (
			this->Check_Warehouse(w)
			&& p < _warehouse[w]._handyShelf.Get_Size());

		errorCount += !check;
		return check;
	}
	bool Storage::Check_Handy_Rack(const int s) {
		bool check = (
			s < _handyRack.Get_Size());

		errorCount += !check;
		return check;
	}
	bool Storage::Check_Handy_Rack_Shelf(const int s, const int p) {
		bool check = (
			this->Check_Handy_Rack(s)
			&& p < _handyRack._shelf[s].Get_Size());

		errorCount += !check;
		return check;
	}
	bool Storage::Check_Handy_Shelf(const int p) {
		bool check = (
			p < _handyShelf.Get_Size());

		errorCount += !check;
		return check;
	}

	bool Storage::ReadAndCheck(
		int* const w = 0, int* const r = 0, int* const s = 0, int* const p = 0,
		int* const a = 0,
		int* const w1 = 0, int* const r1 = 0, int* const s1 = 0, int* const p1 = 0,
		char* const dd = 0) {

		if (w) cin >> *w;
		if (r) cin >> *r;
		if (s) cin >> *s;
		if (p) cin >> *p;
		if (w1) cin >> *w1;
		if (r1) cin >> *r1;
		if (s1) cin >> *s1;
		if (p1) cin >> *p1;
		if (a) cin >> *a;
		if (dd) {
			char dd_str[3];
			cin >> dd_str;
			dd[0] = dd_str[0];
			dd[1] = dd_str[1];
		}
		errorCount = 0;

		errorCount += w && (*w > MAX_WAREHOUSE || *w < 0);
		errorCount += r && (*r > MAX_RACK || *r < 0);
		errorCount += s && (*s > MAX_SHELF || *s < 0);
		errorCount += p && (*p > MAX_PLACE || *p < 0);
		errorCount += w1 && (*w1 > MAX_WAREHOUSE || *w1 < 0);
		errorCount += r1 && (*r1 > MAX_RACK || *r1 < 0);
		errorCount += s1 && (*s1 > MAX_SHELF || *s1 < 0);
		errorCount += p1 && (*p1 > MAX_PLACE || *p1 < 0);
		errorCount += a && (*a > MAX_GOODS || *a < 0);
		errorCount += dd && (
			((dd[0] < '0' || dd[0]>'9') && (dd[0] != '\0' && dd[0] != '\0'))
			|| ((dd[1] < '0' || dd[1]>'9') && (dd[1] != '\0' && dd[1] != '\0')));

		if (errorCount) return false;

		return true;
	}
	void Storage::Fill(const uint8 w, const uint8 r, const uint8 s, const uint8 p, uint16 a) {
		a = a < MAX_GOODS ? a : MAX_GOODS;
		//warehouse - i
		//shelf - k
		//rack - j
		//place - l
		this->Set_Sum_Goods(0);
		this->Set_Size(w);
		for (int i = 0; i < w; i++) {
			_warehouse[i].Set_Size(r);
			for (int j = 0; j < r; j++) {
				_warehouse[i]._rack[j].Set_Size(s);
				for (int k = 0; k < s; k++) {
					_warehouse[i]._rack[j]._shelf[k].Set_Size(p);
					for (int l = 0; l < p; l++) {
						_warehouse[i]._rack[j]._shelf[k]._place[l].Set_Value(a, LabelEmpty, ValueClear);
					}
				}
			}
			_warehouse[i]._handyShelf.Set_Size(p);
			for (int l = 0; l < p; l++) {
				_warehouse[i]._handyShelf._place[l].Set_Value(a, LabelEmpty, ValueClear);
			}
		}
		_handyRack.Set_Size(s);
		for (int k = 0; k < s; k++) {
			_handyRack._shelf[k].Set_Size(p);
			for (int l = 0; l < p; l++) {
				_handyRack._shelf[k]._place[l].Set_Value(a, LabelEmpty, ValueClear);
			}
		}
		_handyShelf.Set_Size(p);
		for (int l = 0; l < p; l++) {
			_handyShelf._place[l].Set_Value(a, LabelEmpty, ValueClear);
		}
	}
	uint64 Shelf::Count_Sum() {
		uint64 count = 0;
		for (int l = 0; l < this->Get_Size(); l++) {
			count += _place[l].Get_Num_Goods();
		}
		return count;
	}
	uint64 Rack::Count_Sum() {
		uint64 count = 0;
		for (int k = 0; k < this->Get_Size(); k++) {
			count += _shelf[k].Count_Sum();
		}
		return count;
	}
	uint64 Warehouse::Count_Sum() {
		uint64 count = 0;
		for (int j = 0; j < this->Get_Size(); j++) {
			count += _rack[j].Count_Sum();
		}
		count += _handyShelf.Count_Sum();
		return count;
	}
	// uint64 Storage::Count_Sum() {
	// 	uint64 count = 0;
	// 	for (int i = 0; i < this->Get_Size();i++) {
	// 		count += _warehouse[i].Count_Sum();
	// 	}
	// 	count += _handyShelf.Count_Sum();
	// 	count += _handyRack.Count_Sum();
	// 	return count;
	// }
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

	char dd[2] = { '\0','\0' };
	char* ddptr = &dd[0];

	char opSelection[10] = "\0";

	while (!cstr_compare(opSelection, "END"))
	{
		// bool success = false;
		errorCount = 0;

		cin >> opSelection;
		Instruction OP = opParse(opSelection);
		switch (OP)
		{
		case END: {  //Note Exit
			break;
		}
		case SET_AP: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p)) break;
			if (!storage.Check_Shelf(w, r, s)) break;
			if (errorCount) break;

			storage._warehouse[w]._rack[r]._shelf[s].Set_All_Sizes(p);
			break;
		}
		case SET_AS: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p)) break;
			if (!storage.Check_Rack(w, r)) break;
			if (errorCount) break;

			storage._warehouse[w]._rack[r].Set_All_Sizes(s, p);
			break;
		}
		case SET_AR: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p)) break;
			if (!storage.Check_Warehouse(w)) break;
			if (errorCount) break;

			storage._warehouse[w].Set_All_Sizes(r, s, p);
			break;
		}
		case SET_AW: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p)) break;
			if (errorCount) break;

			storage.Set_All_Sizes(w, r, s, p);
			break;
		}
		case SET_HW: {
			if (!storage.ReadAndCheck(&w, 0, 0, &p)) break;
			if (!storage.Check_Warehouse(w)) break;
			if (errorCount) break;

			storage._warehouse[w]._handyShelf.Set_All_Sizes(p);
			break;
		}
		case SET_HR: {
			if (!storage.ReadAndCheck(0, 0, &s, &p)) break;
			if (errorCount) break;

			storage._handyRack.Set_All_Sizes(s, p);
			break;
		}
		case SET_HS: {
			if (!storage.ReadAndCheck(0, 0, 0, &p)) break;
			if (errorCount) break;

			storage._handyShelf.Set_All_Sizes(p);
			break;
		}
		case PUT_W: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p, &a)) break;
			if (!storage.Check_Place(w, r, s, p)) break;

			storage._warehouse[w]._rack[r]._shelf[s]._place[p].Put(a);
			break;
		}
		case PUT_H: {
			if (!storage.ReadAndCheck(&w, &p, 0, 0, &a)) break;
			if (!storage.Check_Warehouse_Handy_Shelf(w, p)) break;

			storage._warehouse[w]._handyShelf._place[p].Put(a);

			break;
		}
		case PUT_R: {
			if (!storage.ReadAndCheck(0, 0, &s, &p, &a)) break;
			if (!storage.Check_Handy_Rack_Shelf(s, p)) break;

			storage._handyRack._shelf[s]._place[p].Put(a);
			break;
		}
		case PUT_S: {
			if (!storage.ReadAndCheck(0, 0, 0, &p, &a)) break;
			if (!storage.Check_Handy_Shelf(p)) break;

			storage._handyShelf._place[p].Put(a);
			break;
		}
		case FILL: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p, &a)) break;

			storage.Fill(w, r, s, p, a);
			break;
		}
		case POP_W: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p, &a)) break;
			if (!storage.Check_Place(w, r, s, p)) break;

			storage._warehouse[w]._rack[r]._shelf[s]._place[p].Pop(a);
			break;
		}
		case POP_H: {
			if (!storage.ReadAndCheck(&w, &p, 0, 0, &a)) break;
			if (!storage.Check_Warehouse_Handy_Shelf(w, p)) break;

			storage._warehouse[w]._handyShelf._place[p].Pop(a);
			break;
		}
		case POP_R: {
			if (!storage.ReadAndCheck(0, 0, &s, &p, &a)) break;
			if (!storage.Check_Handy_Rack_Shelf(s, p)) break;

			storage._handyRack._shelf[s]._place[p].Pop(a);
			break;
		}
		case POP_S: {
			if (!storage.ReadAndCheck(0, 0, 0, &p, &a)) break;
			if (!storage.Check_Handy_Shelf(p)) break;

			storage._handyShelf._place[p].Pop(a);
			break;
		}
		case MOV_W: {
			if (!storage.ReadAndCheck(&w, &r, &s, 0, &a, &w1, &r1, &s1, &p1)) break;
			if (!storage.Check_Place(w, r, s, p1)) break;
			if (!storage.Check_Place(w1, r1, s1, p1)) break;

			storage._warehouse[w]._rack[r]._shelf[s]._place[p1].Move(
				storage._warehouse[w1]._rack[r1]._shelf[s1]._place[p1], a);

			break;
		}
		case MOV_H: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p, &a)) break;
			if (!storage.Check_Place(w, r, s, p)) break;
			if (!storage.Check_Warehouse_Handy_Shelf(w, p)) break;

			storage._warehouse[w]._rack[r]._shelf[s]._place[p].Move(
				storage._warehouse[w1]._handyShelf._place[p], a);
			break;
		}
		case MOV_R: {
			if (!storage.ReadAndCheck(&w, &r, &s, 0, &a, 0, 0, &s1, &p1)) break;
			if (!storage.Check_Place(w, r, s, p1)) break;
			if (!storage.Check_Handy_Rack_Shelf(s1, p1)) break;

			storage._warehouse[w]._rack[r]._shelf[s]._place[p1].Move(
				storage._handyRack._shelf[s1]._place[p1], a);
			break;
		}
		case MOV_S: {
			if (!storage.ReadAndCheck(0, 0, &s, &p, &a)) break;
			if (!storage.Check_Handy_Rack_Shelf(s, p)) break;
			if (!storage.Check_Handy_Shelf(p)) break;

			storage._handyRack._shelf[s]._place[p].Move(
				storage._handyShelf._place[p], a);
			break;
		}
		case GET_E: {
			cout << storage.Get_Sum_Goods() << endl;
			break;
		}

		case GET_W: {
			if (!storage.ReadAndCheck(&w)) break;
			if (!storage.Check_Warehouse(w)) break;

			cout << storage._warehouse[w].Count_Sum() << endl;
			break;
		}
		case GET_RW: {
			if (!storage.ReadAndCheck(&w, &r)) break;
			if (!storage.Check_Rack(w, r)) break;

			cout << storage._warehouse[w]._rack[r].Count_Sum() << endl;
			break;
		}
		case GET_RH: {
			cout << storage._handyRack.Count_Sum() << endl;
			break;
		}
		case GET_SW: {
			if (!storage.ReadAndCheck(&w, &r, &s)) break;
			if (!storage.Check_Shelf(w, r, s)) break;

			cout << storage._warehouse[w]._rack[r]._shelf[s].Count_Sum() << endl;
			break;
		}
		case GET_SH: {
			if (!storage.ReadAndCheck(&w)) break;
			if (!storage.Check_Warehouse(w)) break;

			cout << storage._warehouse[w]._handyShelf.Count_Sum() << endl;
			break;
		}
		case GET_SR: {
			if (!storage.ReadAndCheck(0, 0, &s)) break;
			if (!storage.Check_Handy_Rack(s)) break;

			cout << storage._handyRack._shelf[s].Count_Sum() << endl;
			break;
		}

		case GET_S: {
			cout << storage._handyShelf.Count_Sum() << endl;
			break;
		}
		case SET_LW: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p, 0, 0, 0, 0, 0, &dd[0])) break;
			if (!storage.Check_Place(w, r, s, p)) break;

			storage._warehouse[w]._rack[r]._shelf[s]._place[p].Set_Label(dd);
			break;
		}
		case SET_LH: {
			if (!storage.ReadAndCheck(&w, 0, 0, &p, 0, 0, 0, 0, 0, &dd[0])) break;
			if (!storage.Check_Warehouse_Handy_Shelf(w, p)) break;

			storage._warehouse[w]._handyShelf._place[p].Set_Label(dd);
			break;
		}
		case SET_LR: {
			if (!storage.ReadAndCheck(0, 0, &s, &p, 0, 0, 0, 0, 0, &dd[0])) break;
			if (!storage.Check_Handy_Rack_Shelf(s, p)) break;

			storage._handyRack._shelf[s]._place[p].Set_Label(dd);
			break;
		}
		case SET_LS: {
			if (!storage.ReadAndCheck(0, 0, 0, &p, 0, 0, 0, 0, 0, &dd[0])) break;
			if (!storage.Check_Handy_Shelf(p)) break;

			storage._handyShelf._place[p].Set_Label(dd);
			break;
		}
		case GET_LW: {
			if (!storage.ReadAndCheck(&w, &r, &s, &p, 0, 0, 0, 0, 0, 0)) break;
			if (!storage.Check_Place(w, r, s, p)) break;

			ddptr = storage._warehouse[w]._rack[r]._shelf[s]._place[p].Get_Label();
			cout << ddptr[0] << ddptr[1] << endl;
			break;
		}
		case GET_LH: {
			if (!storage.ReadAndCheck(&w, 0, 0, &p, 0, 0, 0, 0, 0, 0)) break;
			if (!storage.Check_Warehouse_Handy_Shelf(w, p)) break;

			ddptr = storage._warehouse[w]._handyShelf._place[p].Get_Label();
			cout << ddptr[0] << ddptr[1] << endl;
			break;
		}
		case GET_LR: {
			if (!storage.ReadAndCheck(0, 0, &s, &p, 0, 0, 0, 0, 0, 0)) break;
			if (!storage.Check_Handy_Rack_Shelf(s, p)) break;

			ddptr = storage._handyRack._shelf[s]._place[p].Get_Label();
			cout << ddptr[0] << ddptr[1] << endl;
			break;
		}
		case GET_LS: {
			if (!storage.ReadAndCheck(0, 0, 0, &p, 0, 0, 0, 0, 0, 0)) break;
			if (!storage.Check_Handy_Shelf(p)) break;

			ddptr = storage._handyShelf._place[p].Get_Label();
			cout << ddptr[0] << ddptr[1] << endl;
			break;
		}
		default:
			//cout << "unexpected" << endl;
			break;
		}
		if (errorCount) cout << "error" << endl;
	}

	return 0;
}