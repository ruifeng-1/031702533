#include<iostream>
#include<cstring>
#include<boost/regex.hpp>
#include<locale>
#include<fstream>
#include<cstdlib>
#include"addressbook.h"
using namespace std;
using namespace boost;

int main()
{
	/*wstring s;
	Text text;
	Address address;
	cout << "please write name,number and address!" << endl;
	cout << "enter END to exit." << endl;
	setlocale(LC_CTYPE, "");
	while (getline(wcin, s) && s != L"END")
	{
		s = text.select_level(s);
		address.find_address(text.find_number(text.find_name(s)));
		text.show();
		address.show(text.Level());
	}*/
	int count = 1;
	ifstream ifs("input");
	ofstream ofs("output.json");
	string s;
	Text text;
	Address address;
	setlocale(LC_CTYPE, "");
	ifs.open("input.txt", ios::in);//读文件打开
	if (!ifs.is_open())
	{
		cout << "文件打开失败！" << endl;
	}
	ofs << "[" << endl;
	while(getline(ifs, s))
	{
		if (count >= 2)
		{
			ofs << "," << endl;
		}
		else
			count++;
		cout << "read:\r\n" << s << endl;
		wstring ws = stows(s);
		ws = text.select_level(ws);
		address.find_address(text.find_number(text.find_name(ws)));
		s = text.returnText() + address.returnAddress(text.Level());
		ofs << json_printf(s) << endl;
	}
	ofs << "]" << endl;
	ofs.close();
	system("pause");
}