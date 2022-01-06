
#include<string>
using std::string;

string subs(string str, int begin, int end) {
	string substr = 0;
	for (int i = begin; i < end; i++) {
		substr += str[i];
	}
}

string FormatujNapis(string str, string arg_1, string arg_2, string arg_3) {
	short int n = 0;
	char c = 0;
	string hold = 0;
	string done = 0;
	string pending = 0;

	int i = 0;
	while (i < str.size()) {
		if (str[i] == '{') {
			n = int(str[i + 3]) - int('0'); //Get n int value 
			char OP = str[i + 1]; //Get instruction name
			switch (OP) {
			case 'p': {  //Note {p:n:c}
				c = str[i + 5]; // Get c
				string insert(n, c);
				pending = subs(str, i + 7, str.size());
				str = done + insert + pending;
				break;
			}
			case 'u': { //Note {u:n}
				pending = subs(str, i + 5 + n, str.size());
				str = done + pending;
				break;
			}
			case 'U': //Note {U:n}
			{
				done.resize(str.size() - n);
				break;

			}
			}

			// i--; //Compensated by i++, go back to current pos
		}
		else {
			done += str[i];
			i++; //Next pos if no formattign occurs
		}
	}
	return str;
}

string NajwiekszeSlowo(string str) {
	return str;
}


string NormalizujNapis(string str) {
	return str;
}

string UsunSlowo(string str, int num) {
	return str;
}

