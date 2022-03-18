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
void Union(int, int, int*);
void Intersection(int, int, int*);
void Symmetric(int, int, int*);
void Difference(int, int, int*);
void Complement(int, int*);
void Cardinality(int, int*);
bool LessThen(int, int);
bool LessEqual(int, int);
bool GreatEqual(int, int);
bool GreatThen(int, int);
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
	// OK  overflow ^
	// bitwise set (0|001 0000 0000 0001 0000 0000 0000 0000) == (11100, 10000)

	if (*(cstr + local_i + 0) == '1') { Dec_Int = Dec_Int << 16; }
	if (*(cstr + local_i + 1) == '1') { Dec_Int = Dec_Int << 8; }
	if (*(cstr + local_i + 2) == '1') { Dec_Int = Dec_Int << 4; }
	if (*(cstr + local_i + 3) == '1') { Dec_Int = Dec_Int << 2; }
	if (*(cstr + local_i + 4) == '1') { Dec_Int = Dec_Int << 1; }

	return Dec_Int;
}
int Lexicographically_Bigger(int A, int B) {
	if (A < 0 || B < 0) { //Taking care of sign 
		if (B < 0 && A > 0) 	return -1; 		// -1	A < B
		if (B == A) 			return 0;  				//  0  	A == B
		if (A < 0 && B > 0) 	return 1;		// 	1 	A > B
	}
	else {
		if (A < B)				return -1;
		if (A == B) 			return 0;
		if (A > B) 				return 1;
	}
	return 0;
}
// SECTION PROBLEM FUNCTIONS
void Insert(char* cstr, int* set) {
	static int i = 0;
	if (*(cstr + i) == '\0') { i = 0; return; } // 	Loop exit condition
	else if (*(cstr + i) == ' ') { i++; }
	else {
		*set = *set | Set_Idx_Parse(cstr, i); 	//	Bitwise union: seq index added to set
		i += 5;
	}
	Insert(cstr, set);
}
void Emplace(char* cstr, int* set) {
	*set = 0;
	Insert(cstr, set);
}
void Erase(char* cstr, int* set) {
	static int i = 0;
	if (*(cstr + i) == '\0') { i = 0; return; } 	// 	Loop exit condition
	else if (*(cstr + i) == ' ') { i++; }
	else {
		*set = *set & (~Set_Idx_Parse(cstr, i)); 	//	Bitwise A\{x}= A&~x
		i += 5;
	}
	Erase(cstr, set);
}
void Print(int set, char* out) {
	static int seq_idx = 31; 	//	Descending order; Starting from (11111) = 1|000 0000 0000 0000 0000 0000 0000 0000
	static int str_i = 0; 		//	current idx of destination char array
	if (set == 0) { 			//	empty set
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
	else if (seq_idx < 0) { 	// Loop exit condition
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
void Complement(int input_set, int* set) {
	*set = ~input_set;
}
bool Emptiness(int set) {
	return set == 0;
}
bool Nonempty(int set) {
	return set != 0;
}
bool Member(char* cstr, int set) {
	static int i = 0;
	if (*(cstr + i) == '\0') { i = 0; } 		// 	Loop exit condition
	else if (*(cstr + i) == ' ') { i++; }
	else {
		bool result = set & Set_Idx_Parse(cstr, i); 	//	Intersection of set and singleton of seq
		i = 0;
		return result;
	}
	return Member(cstr, set);
}
bool Disjoint(int A, int B) {
	return !(A & B);
}
bool Conjunctive(int A, int B) {
	return (A & B);
}
bool Equality(int A, int B) {
	return A == B;
}
bool Inclusion(int A, int B) {
	return (A | B) == B;
}
void Union(int A, int B, int* C) {
	*C = A | B;
}
void Intersection(int A, int B, int* C) {
	*C = A & B;
}
void Symmetric(int A, int B, int* C) {
	*C = (A & ~B) | (B & ~A);
}
void Difference(int A, int B, int* C) {
	*C = (A & ~B);
}
int Cardinality(int set) { // Number of 1s int bitwise set representation 
	static int i = 31;

	if (i < 0) { // Loop exit condition
		i = 31;
		return 0;
	}
	if (set & (1 << i)) {
		i--;
		return Cardinality(set) + 1;
	}
	else i--;
	return Cardinality(set);

}
bool LessThen(int A, int B) { // A < B ?
	int cardA = Cardinality(A);
	int cardB = Cardinality(B);
	if (cardA == cardB) {
		// int lexbigger = Lexicographically_Bigger(A, B);
		// if (lexbigger == -1) 	return true;
		// if (lexbigger == 0) 	return false;
		// if (lexbigger == 1)		return false;
		return A < B;
	}
	return cardA < cardB;
}
bool LessEqual(int A, int B) { // A <= B ?
	int cardA = Cardinality(A);
	int cardB = Cardinality(B);
	if (cardA == cardB) {
		// int lexbigger = Lexicographically_Bigger(A, B);
		// if (lexbigger == -1) 	return true;
		// if (lexbigger == 0) 	return true;
		// if (lexbigger == 1)		return false;
		return A <= B;
	}
	return cardA < cardB;
}
bool GreatEqual(int A, int B) { // A >= B ?
	int cardA = Cardinality(A);
	int cardB = Cardinality(B);
	if (cardA == cardB) {
		// int lexbigger = Lexicographically_Bigger(A, B);
		// if (lexbigger == -1) 	return false;
		// if (lexbigger == 0) 	return true;
		// if (lexbigger == 1)		return true;
		return A >= B;
	}
	return cardA >= cardB;
}
bool GreatThen(int A, int B) { // A > B ?
	int cardA = Cardinality(A);
	int cardB = Cardinality(B);
	if (cardA == cardB) {
		// int lexbigger = Lexicographically_Bigger(A, B);
		// if (lexbigger == -1) 	return false;
		// if (lexbigger == 0) 	return false;
		// if (lexbigger == 1)		return true;
		return A > B;
	}
	return cardA > cardB;
}