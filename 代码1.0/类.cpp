#include<iostream>
#include<cstring>
#include <boost/regex.hpp>
#include<fstream>
#include <locale>
using namespace std;
using namespace boost;

class Text//文本类
{
public:
	Text(){}
	string find_name(string s);
	string find_number(string s);
	void show();
private:
	string name;//姓名
	string number;//手机号码
	string address;//地址
};

string Text::find_name(string s)
{
	regex re("\\w+\\,");
	smatch sm;
	if (regex_search(s, sm, re))//查找姓名
	{
		size_t i = s.find_first_of(",");
		name = s.substr(0, i);
		return s.substr(i + 1);
	}
	else
		cout << "find_name error" << endl;
	return s;
	
}

string Text::find_number(string s)
{
	regex re("[0-9]{11}");
	smatch sm;
	if (regex_search(s, sm, re))//查找手机号码
		number = sm.str();
	else
		cout << "find_number error" << endl;
	size_t i = s.find_first_of(number);//查找手机号码所在位置
	return s.substr(0,i)+s.substr(i+11);//合并剩下的字符串
}

void Text::show()//输出姓名，手机号码
{
	cout << "\"姓名\":\"" << name << "\",\"手机\":\"" << number << "\"";
}

class Address//地址类
{
public:
	void find_address(string s);
	wstring search_address(wstring wstr, wregex wre);
	bool match_address(wstring wstr, wregex wre);
	void show();
private:
	wstring province;//省
	wstring city;//市
	wstring county;//县
	wstring town;//镇
	wstring road;//路
	wstring house_number;//门牌号
	wstring detail;//详细地址
};

void Address::find_address(string s)
{
	wregex wre1(L"(\\北京|\\天津|\\上海|\\重庆)\\市??|(\\河北|\\山西|\\辽宁|\\吉林|\\黑龙江|\\江苏|\\浙江|\\安徽|\\福建|\\江西|\\山东|\\河南|\\湖北|\\湖南|\\广东|\\海南|\\四川|\\贵州|\\云南|\\陕西|\\甘肃|\\青海)\\省?");
	wregex wre2(L"\\w+?\\市");
	wregex wre3(L"\\w+?(\\县|\\区)");
	wregex wre4(L"\\w+?(\\街道|\\镇|\\乡)");
	wregex wre5(L"\\w+?(\\路|\\街|\\巷)");
	wregex wre6(L"\\d+?(\\号)");
	wregex wre7(L".+[^\\.]");
	wregex wre1_0(L"(\\北京|\\天津|\\上海|\\重庆)\\市?");
	setlocale(LC_CTYPE, "");
	size_t len = mbstowcs(NULL, s.c_str(), s.length()); // 计算转换后宽字符串的长度
	wchar_t *wch = new wchar_t[len + 1];
	size_t len0 = mbstowcs(wch, s.c_str(), s.length()); // 转换为宽字符串（转换后的字符串有结束符）
	wstring s0(wch);
	delete[]wch;
	province = search_address(s0, wre1);//查找省, 直辖市
	if(!match_address(province,wre1_0))//匹配是否直辖市
		s0 = s0.substr(province.length());//切割字符串，下同
	city = search_address(s0, wre2);//查找市
	s0 = s0.substr(city.length());
	county = search_address(s0, wre3);//查找县，区
	s0 = s0.substr(county.length());
	town = search_address(s0, wre4);//查找街道，镇，乡
	s0 = s0.substr(town.length());
	road = search_address(s0,wre5);//查找路，街，巷
	s0 = s0.substr(road.length());
	house_number = search_address(s0, wre6);
	s0 = s0.substr(house_number.length());
	detail = search_address(s0, wre7);
}

wstring Address::search_address(wstring wstr,wregex wre)//正则表达式搜索
{
	wsmatch wsm;
	if (regex_search(wstr, wsm, wre))
		return wsm.str();
	else
		return  L"";
}

bool Address::match_address(wstring wstr, wregex wre)// 正则表达式匹配
{
	wsmatch wsm;
	if (regex_match(wstr, wsm, wre))
		return true;
	else
		return false;
}

void Address::show()//输出地址
{
	wcout << L",\"地址\":[\"" << province << L"\",\"" << city << L"\",\"" << county << L"\",\"" << town << L"\",\"" << road << L"\",\"" << house_number << L"\",\"" << detail << L"\"]" << endl;
}

int main()
{
	string s;
	Text text;
	Address add;
	cout << "please enter name,number and address!" << endl;
	cout << "enter END to exit." << endl;
	while (getline(cin, s)&&s !="END")
	{
		add.find_address(text.find_number(text.find_name(s)));
		text.show();
		add.show();
	}
	system("pause");
}