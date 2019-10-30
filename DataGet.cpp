#include"dataGet.h"
#include<iostream>
#include<fstream>
#include<locale>
#include<codecvt>

std::string DataGet::getRank() {
	std::ifstream f;
	f.open("rank.json", std::ios::in);
	if (!f.is_open()) {
		std::cout << "open file Error" << std::endl;
		return "";
	}
	std::string cur;
	std::string ret;
	while (getline(f, cur)) {
		ret += cur;
	}
	return ret;
}

std::string DataGet::getStatus() {
	std::ifstream f;
	f.open("status.json", std::ios::in);
	if (!f.is_open()) {
		std::cout << "open file Error" << std::endl;
		return "";
	}
	std::string cur;
	std::string ret;
	while (getline(f, cur)) {
		ret += cur;
	}
	return ret;
}