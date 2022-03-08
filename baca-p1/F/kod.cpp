//Maksim Zdobnikau

#include<string>
using std::string;

string subs(const string str, const size_t begin, const size_t end) {
	string sub_str = "";
	for (size_t i = begin; i < end; i++) {
		sub_str += str[i];
	}
	return sub_str;
}

string FormatujNapis(string str, const string arg_1, const string arg_2, const string arg_3) {
	const string args[3] = { arg_1, arg_2, arg_3 };

	unsigned char n = 0;
	string doneStr = "";

	size_t i = 0;
	while (i < str.size()) {
		if (str[i] == '{') {
			char OP = str[i + 1];
			n = int(str[i + 3]) - int('0');

			switch (OP) {
			case 'p': {  //Note {p:n:c}
				char c = str[i + 5];
				string pendingStr = subs(str, i + 7, str.size());
				string inserStr(n, c);
				str = doneStr + inserStr + pendingStr;
				break;
			}
			case 'u': { //Note {u:n}
				string pendingStr = subs(str, i + 5 + n, str.size());
				str = doneStr + pendingStr;
				break;
			}
			case 'U': { //Note {U:n}
				string pendingStr = subs(str, i + 5, str.size());
				doneStr.resize(doneStr.size() - n);

				i -= n; //Reset pos
				str = doneStr + pendingStr;
				break;
			}
			case 'w': { //Note {w:n}
				string pendingStr = subs(str, i + 5, str.size());
				string inserStr = args[n - 1];
				str = doneStr + inserStr + pendingStr;
				break;
			}
			case 'W': { //Note {W:n:m}
				unsigned char m = int(str[i + 5]) - int('0');

				string pendingStr = subs(str, i + 7, str.size());
				string inserStr = args[n - 1];
				if (inserStr.size() < m) {
					string fill(m - inserStr.size(), ' ');
					inserStr += fill;
				}
				else if (inserStr.size() > m) {
					inserStr.resize(m);
				}
				str = doneStr + inserStr + pendingStr;
				break;
			}
			}
		}
		else {
			doneStr += str[i];
			i++; //Next pos if no formatting occurs
		}
	}
	return str;
}

string NajwiekszeSlowo(const string str) {
	string curWord = "";
	string bigWord = "";

	size_t i = 0;
	while (i < str.size()) {
		if (str[i] == ' ') {
			bigWord = curWord <= bigWord ? bigWord : curWord;
			curWord = "";
		}
		else {
			curWord += str[i];
			if (i == str.size() - 1) {
				bigWord = curWord <= bigWord ? bigWord : curWord;
			}
		}
		i++;
	}
	return bigWord;
}

string NormalizujNapis(const string str) {
	//_, - remove _
	//_. - remove _
	//__ - remove all except last _
	//, - add _
	//. - add _

	string doneStr = "";

	size_t i = 0;
	while (i < str.size()) {
		bool beforeNorm = (
			str[i] != ' ' || (
				str[i + 1] != ','
				&& str[i + 1] != '.'
				&& str[i + 1] != ' '
				&& i < str.size() - 1
				&& doneStr.size() > 0
				));
		if (beforeNorm) {
			doneStr += str[i]; //Write only last symbol
			bool afterNorm = (
				(str[i] != ',' && str[i] != '.')
				|| str[i + 1] == ' '
				|| i == str.size() - 1
				);
			if (!afterNorm) {
				doneStr += ' ';
			}
		}
		i++;
	}

	return doneStr;
}

string UsunSlowo(const string str, const int removed_word_num) {
	string doneStr = "";
	unsigned int wordCount = 0;
	unsigned int wordLen = 0;

	size_t i = 0;
	while (i < str.size() && wordCount < removed_word_num) {
		doneStr += str[i];
		if (str[i] == ' ' && !(i == 0 || str[i - 1] == ' ')) {
			wordCount++;
			if (wordCount == removed_word_num) {
				string pendingStr = subs(str, i, str.size());
				doneStr.resize(doneStr.size() - wordLen - 1);
				doneStr += pendingStr;
			}
			wordLen = 0;
		}
		else {
			wordLen++;
			if (i == str.size() - 1) {
				wordCount++;
				if (wordCount == removed_word_num) {
					doneStr.resize(doneStr.size() - wordLen);
				}
			}
		}
		i++;
	}
	return doneStr;
}