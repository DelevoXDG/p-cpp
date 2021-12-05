#include <iostream>
#include <bits/stdc++.h>
#include <sstream>

using std::cin; using std::cout; using std::endl; using std::string;

string IP_bin_to_dec(string inIP)
{
	string ip_string;
	inIP += ".";
	for (int i = 0; i < 4; i++) {
		int pos = inIP.find(".");
		inIP.erase(0, pos + 1);
		ip_string.append(std::to_string(std::stoi(inIP.substr(0, pos)))); //Converts current 8bits from BIN to DEC
		if (i < 3) ip_string.append(".");
	}
	return ip_string;
}

string dec_to_bin(int value) {
	std::stringstream stream;
	stream << std::bitset<8>(value);
	return stream.str();
}
string dec_to_hex(int value) {
	std::stringstream stream;
	stream << std::hex << std::uppercase << value;
	return stream.str();
}

string IP_to_base(string inIP, short int base)
{
	int ipv4[4];
	sscanf(inIP.c_str(), "%d.%d.%d.%d", &ipv4[0], &ipv4[1], &ipv4[2], &ipv4[3]);
	string ip_string;
	// if (base == 2) ip_string.append("0b");
	// if (base == 16) ip_string.append("0x");

	for (int i = 0; i < 4; i++) {
		string tmp = ""; //Current 8 bits of ip adress
		if (base == 10) tmp = ipv4[i];
		else if (base == 2) tmp = dec_to_bin(ipv4[i]);
		else if (base == 16) tmp = dec_to_hex(ipv4[i]);
		else return "-1";
		ip_string.append(tmp);
		if (i < 3) ip_string.append(".");
	}
	return ip_string;
}

bool isIP(string IP)
{
	std::regex ipv4("(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])");
	return std::regex_match(IP, ipv4) ? 1 : 0;
}
bool isMask(string mask)
{
	std::regex subnetMask("((128|192|224|240|248|252|254)\\.0\\.0\\.0)|(255\\.(((0|128|192|224|240|248|252|254)\\.0\\.0)|(255\\.(((0|128|192|224|240|248|252|254)\\.0)|255\\.(0|128|192|224|240|248|252|254)))))$");
	return std::regex_match(mask, subnetMask) ? 1 : 0;
}
string subnetMask(string inIP, string inMask) {
	if (!(isIP(inIP) && isMask(inMask))) return "-1";
	int ipv4[4];
	int snetMask[4];
	string snetAddress_string;
	sscanf(inIP.c_str(), "%d.%d.%d.%d", &ipv4[0], &ipv4[1], &ipv4[2], &ipv4[3]);
	sscanf(inMask.c_str(), "%d.%d.%d.%d", &snetMask[0], &snetMask[1], &snetMask[2], &snetMask[3]);

	for (int i = 0; i < 4; i++) {
		std::bitset<8> ipv4_oct(ipv4[i]);
		std::bitset<8> mask_oct(snetMask[i]);
		snetAddress_string.append((ipv4_oct & mask_oct).to_string());
		if (i < 3) snetAddress_string.append(".");
	}
	return IP_bin_to_dec(snetAddress_string);
}



int main(int argc, const char** argv)
{
	string ipv4_string = ""; //
	string mask_string = "";
	string subnetAdress_string = "";
	cin >> ipv4_string;
	cin >> mask_string;

	subnetAdress_string = subnetMask(ipv4_string, mask_string);

	if (subnetAdress_string == "-1") cout << "Incorrect input." << endl;
	else {
		int ipv4;
		cout << std::setw(6) << std::left << "# " << std::setw(40) << std::left << "IPv4" << std::setw(40) << std::left << "Subnet Mask" << std::setw(40) << std::left << "Subnet Adress" << endl << endl;
		cout << std::setw(6) << std::left << "DEC " << std::setw(40) << std::left << ipv4_string << std::setw(40) << std::left << mask_string << std::setw(40) << std::left << subnetAdress_string << endl;
		cout << std::setw(6) << std::left << "BIN " << std::setw(40) << std::left << IP_to_base(ipv4_string, 2) << std::setw(40) << std::left << IP_to_base(mask_string, 2) << std::setw(40) << std::left << IP_to_base(subnetAdress_string, 2) << endl;
		cout << std::setw(6) << std::left << "OCT " << std::setw(40) << std::left << IP_to_base(ipv4_string, 8) << std::setw(40) << std::left << IP_to_base(mask_string, 8) << std::setw(40) << std::left << IP_to_base(subnetAdress_string, 8) << endl;
		cout << std::setw(6) << std::left << "HEX " << std::setw(40) << std::left << IP_to_base(ipv4_string, 16) << std::setw(40) << std::left << IP_to_base(mask_string, 16) << std::setw(40) << std::left << IP_to_base(subnetAdress_string, 16) << endl;
	}
	return 0;
}