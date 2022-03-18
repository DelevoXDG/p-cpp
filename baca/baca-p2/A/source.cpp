//Maksim Zdobnikau


// SECTION DECLARATIONS
void Implace(char*, int*);
void Insert(char*, int*);
void Erase(char*, int*);
void Print(int, char*);
bool Emptiness(int);
bool Nonempty(int);
bool Member(char*, int);
bool Disjoint(int, int);
bool Conjunctive(int, int);
bool Equality(int, int);
bool Inclusion(int, int);
bool Union(int, int, int*);
void Intersection(int, int, int*);
void Symmetric(int, int, int*);
void Difference(int, int, int*);
void Complement(int, int*);
void Cardinality(int, int*);
bool LessThen(int, int);
bool LessEqual(int, int);
bool GreatEqual(int, int);
bool GreatThen(int, int);
int cstr_Length(char* const);

// SECTION NOTEPAD
// general idea: 
// int 32 bit == 32 possible sets 
//SECTION HELPERS 
int Set_Idx_Parse(char* const cstr, const int local_i) { // Parses cstr to decimal index in set  
	int Dec_Int = 1;
	// bitwise set (0|000 0000 0000 0000 0000 0000 0000 0000) == empty
	// bitwise set (0|000 0000 0000 0000 0000 0000 0000 0001) == (00000, )
	// bitwise set (0|000 0000 0000 0001 0000 0000 0000 0000) == (10000, )
	// bitwise set (0|000 0001 0000 0000 0000 0000 0000 0000) == (11000, )
	// bitwise set (0|001 0000 0000 0000 0000 0000 0000 0000) == (11100, )
	// bitwise set (0|100 0000 0000 0000 0000 0000 0000 0000) == (11110, )
	// bitwise set (1|000 0000 0000 0000 0000 0000 0000 0000) == (11111, ) 
	// FIX overflow ^   - sign 

	if (*(cstr + local_i + 0) == '1') { Dec_Int = Dec_Int << 16; }
	if (*(cstr + local_i + 1) == '1') { Dec_Int = Dec_Int << 8; }
	if (*(cstr + local_i + 2) == '1') { Dec_Int = Dec_Int << 4; }
	if (*(cstr + local_i + 3) == '1') { Dec_Int = Dec_Int << 2; }
	if (*(cstr + local_i + 4) == '1') { Dec_Int = Dec_Int << 1; }

	return Dec_Int;
}
// SECTION PROBLEM FUNCTIONS
void Insert(char* cstr, int* set) {
	static int i = 0;
	if (*(cstr + i) != '\0') { //Loop
		if (*(cstr + i) == ' ') { i++; }
		else {
			*set = *set | Set_Idx_Parse(cstr, i); //Getting set index
			i += 5;
		}
		Insert(cstr, set);
	}
	else { i = 0; } //Loop ends
}
void Emplace(char* cstr, int* set) {
	*set = 0;
	Insert(cstr, set);
}
void Print(int set, char* out) {
	static int seq_idx = 31; //Descending order; Starting from (11111) = 1|000 0000 0000 0000 0000 0000 0000 0000
	static int str_i = 0;
	if (set == 0) { //empty set
		seq_idx = 31;
		str_i = 0;
		*(out + 0) = 'e';
		*(out + 1) = 'm';
		*(out + 2) = 'p';
		*(out + 3) = 't';
		*(out + 4) = 'y';
		*(out + 5) = '\0';
		return;
	}
	else if (seq_idx < 0) { //Loop ends
		*(out + str_i) = '\0';
		seq_idx = 31;
		str_i = 0;
		return;
	}
	else if (set & (1 << seq_idx)) { // If sequence of seq_idx intersects with the set (seq is an element of the set)
		*(out + str_i + 0) = '0' + (seq_idx / 16) % 2; //Convert idx to set
		*(out + str_i + 1) = '0' + (seq_idx / 8) % 2;
		*(out + str_i + 2) = '0' + (seq_idx / 4) % 2;
		*(out + str_i + 3) = '0' + (seq_idx / 2) % 2;
		*(out + str_i + 4) = '0' + (seq_idx) % 2;
		*(out + str_i + 5) = ' ';
		str_i += 6;
	}
	seq_idx--;
	Print(set, out);
}
