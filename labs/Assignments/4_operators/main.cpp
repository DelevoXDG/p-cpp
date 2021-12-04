#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <arpa/inet.h>

using std::cin; using std::cout; using std::endl; using std::string;

string IP_bin_to_dec(string inIP)
{
	string ipv4[4];
	string ipv4_string;
	size_t pos;
	int i = 0;
	inIP += ".";
	while (i < 4) {
		pos = inIP.find(".");
		ipv4[i] = inIP.substr(0, pos);
		inIP.erase(0, pos + 1);
		i++;
	}
	for (int i = 0; i < 4; i++) {
		int num = std::stoi(ipv4[i], 0, 2);
		ipv4_string.append(std::to_string(num));
		if (i < 3) ipv4_string.append(".");
	}
	return ipv4_string;
}

string int_to_bin(int value) {
	std::stringstream stream;
	stream << std::bitset<8>(value);
	return stream.str();
}
string int_to_oct(int value) {
	std::stringstream stream;
	stream << std::oct << value;
	return stream.str();
}
string int_to_hex(int value) {
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
	// if (base == 8) ip_string.append("0");
	// if (base == 16) ip_string.append("0x");
	for (int i = 0; i < 4; i++) {
		string tmp = ""; //current 8 bits of ip adress
		if (base == 2) tmp = int_to_bin(ipv4[i]);
		else if (base == 8) tmp = int_to_oct(ipv4[i]);
		else if (base == 16) tmp = int_to_hex(ipv4[i]);
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
	int i1, i2, i3, i4;
	int ipv4[4];
	sscanf(inIP.c_str(), "%d.%d.%d.%d", &ipv4[0], &ipv4[1], &ipv4[2], &ipv4[3]);
	int snetMask[4];
	sscanf(inMask.c_str(), "%d.%d.%d.%d", &snetMask[0], &snetMask[1], &snetMask[2], &snetMask[3]);

	//string ipv4_string;
	//string snetMask_string;
	string snetAddress_string;

	for (int i = 0; i < 4; i++) {
		std::bitset<8> ipv4_oct(ipv4[i]);
		//ipv4_string.append(ipv4_oct.to_string());
		std::bitset<8> mask_oct(snetMask[i]);
		//snetMask_string.append(mask_oct.to_string());
		snetAddress_string.append((ipv4_oct & mask_oct).to_string());
		if (i < 3) snetAddress_string.append(".");
	}
	//std::bitset<32> ipv4_binary(ipv4_string);
	//std::bitset<32> snetMask_binary(snetMask_string);
	// return (ipv4_binary & snetMask_binary).to_string();
	return (snetAddress_string);
}



int main(int argc, const char** argv)
{
	string ipv4_string = "";
	string mask_string = "";
	cin >> ipv4_string;
	cin >> mask_string;
	//cout << ipv4 << " is " << (isMask(ipv4) ? "true" : "false") << endl;
	string subnetAdress_bin_string = "";
	subnetAdress_bin_string = subnetMask(ipv4_string, mask_string);

	if (subnetAdress_bin_string == "-1") cout << "Wrong input." << endl;
	else {
		int ipv4;
		// int subnetAdress = std::stoi(subnetAdress_bin_string, 0, 2);
		string subnetAdress_string = IP_bin_to_dec(subnetAdress_bin_string);
		//cout << subnetAdress_bin_string << endl;
		//cout << subnetAdress_string << endl;
		cout << std::setw(6) << std::left << "# " << std::setw(40) << std::left << "IPv4" << std::setw(40) << std::left << "Subnet Mask" << std::setw(40) << std::left << "Subnet Adress" << endl << endl;
		cout << std::setw(6) << std::left << "DEC " << std::setw(40) << std::left << ipv4_string << std::setw(40) << std::left << mask_string << std::setw(40) << std::left << subnetAdress_string << endl;
		cout << std::setw(6) << std::left << "BIN " << std::setw(40) << std::left << IP_to_base(ipv4_string, 2) << std::setw(40) << std::left << IP_to_base(mask_string, 2) << std::setw(40) << std::left << IP_to_base(subnetAdress_string, 2) << endl;
		cout << std::setw(6) << std::left << "OCT " << std::setw(40) << std::left << IP_to_base(ipv4_string, 8) << std::setw(40) << std::left << IP_to_base(mask_string, 8) << std::setw(40) << std::left << IP_to_base(subnetAdress_string, 8) << endl;
		cout << std::setw(6) << std::left << "HEX " << std::setw(40) << std::left << IP_to_base(ipv4_string, 16) << std::setw(40) << std::left << IP_to_base(mask_string, 16) << std::setw(40) << std::left << IP_to_base(subnetAdress_string, 16) << endl;

	}
	return 0;
}