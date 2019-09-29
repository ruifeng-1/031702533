#include<iostream>
#include<cstring>
#include<boost/regex.hpp>
#include<locale>
#include<fstream>
#include"addressbook.h"
using namespace std;
using namespace boost;

int main()
{
	wstring s;
	Text text;
	Address address;
	cout << "please write name,number and address!" << endl;
	cout << "enter END to exit." << endl;
	while (getline(wcin, s) && s != L"END")
	{
		s = text.select_level(s);
		address.find_address(text.find_number(text.find_name(s)));
		text.show();
		address.show(text.Level());
	}
	system("pause");
}