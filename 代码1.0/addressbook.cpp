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
	wstring select_level(wstring s);
	wstring find_name(wstring s);
	wstring find_number(wstring s);
	void show();
	wstring Level();
private:
	wstring name;//姓名
	wstring number;//手机号码
	wstring address;//地址
	wstring level;//难度
};

wstring Text::select_level(wstring s)
{
	wregex re(L"[1-3]!");
	wsmatch sm;
	if (regex_search(s, sm, re))
	{
		level = sm.str();
		return s.substr(level.length());
	}
	else
		cout << "select_difficulty error" << endl;
	return s;
}

wstring Text::find_name(wstring s)
{
	wregex re(L"\\w+?[^\\,]");
	wsmatch sm;
	if (regex_search(s, sm, re))//查找姓名
	{
		name = sm.str();
		return s.substr(name.length()+1);
	}
	else
		cout << "find_name error" << endl;
	return s;
	
}

wstring Text::find_number(wstring s)
{
	wregex re(L"[0-9]{11}");
	wsmatch sm;
	if (regex_search(s, sm, re))//查找手机号码
		number = sm.str();
	else
		cout << "find_number error" << endl;
	size_t i = s.find_first_of(number);//查找手机号码所在位置
	return address = s.substr(0,i)+s.substr(i+11);//合并剩下的字符串
}

wstring Text::Level()
{
	return level;
}

void Text::show()//输出姓名，手机号码
{
	wcout << L"\"姓名\":\"" << name << L"\"," << "\r\n" << L"\"手机\":\"" << number << L"\"," << "\r\n";
}

class Address//地址类
{
public:
	Address(){}
	void find_address(wstring s);
	wstring search_address(wstring wstr, wregex wre);
	bool match_address(wstring wstr, wregex wre);
	void show(wstring diff);
private:
	wstring province;//省
	wstring city;//市
	wstring county;//县
	wstring town;//镇
	wstring road;//路
	wstring house_number;//门牌号
	wstring detail;//详细地址
};

void Address::find_address(wstring s)
{
	wregex wre1(L"(\\北京|\\天津|\\上海|\\重庆)\\市??|(\\河北|\\山西|\\辽宁|\\吉林|\\黑龙江|\\江苏|\\浙江|\\安徽|\\福建|\\江西|\\山东|\\河南|\\湖北|\\湖南|\\广东|\\海南|\\四川|\\贵州|\\云南|\\陕西|\\甘肃|\\青海)\\省?");
	wregex wre2(L"\\w+?\\市");
	wregex wre3(L"\\w+?(\\县|\\区)");
	wregex wre4(L"\\w+?(\\街道|\\镇|\\乡)");
	wregex wre5(L"\\w+?(\\路|\\街|\\巷)");
	wregex wre6(L"\\d+?(\\号)");
	wregex wre7(L".+[^\\.]");
	wregex wre1_0(L"(\\北京|\\天津|\\上海|\\重庆)\\市?");

	province = search_address(s, wre1);//查找省, 直辖市
	if(!match_address(province,wre1_0))//匹配是否直辖市
		s = s.substr(province.length());//切割字符串，下同
	city = search_address(s, wre2);//查找市
	s = s.substr(city.length());
	county = search_address(s, wre3);//查找县，区
	s = s.substr(county.length());
	town = search_address(s, wre4);//查找街道，镇，乡
	s = s.substr(town.length());
	road = search_address(s, wre5);//查找路，街，巷
	s = s.substr(road.length());
	house_number = search_address(s, wre6);//查找门牌号
	detail = search_address(s.substr(house_number.length()), wre7);
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

void Address::show(wstring diff)//输出地址
{
	if(diff==L"1!")
		wcout << L"\"地址\":[\r\n\"" << province << L"\",\r\n\"" << city << L"\",\r\n\"" << county << L"\",\r\n\"" << town << L"\",\r\n\"" << road << house_number << detail << L"\"\r\n]" <<endl;
	if(diff==L"2!")
		wcout << L"\"地址\":[\r\n\"" << province << L"\",\r\n\"" << city << L"\",\r\n\"" << county << L"\",\r\n\"" << town << L"\",\r\n\"" << road << L"\",\r\n\"" << house_number << L"\",\r\n\"" << detail << L"\"\r\n]" <<endl;
}

int main()
{
	wstring s;
	Text text;
	Address address;
	setlocale(LC_CTYPE, "");
	cout << "please enter name,number and address!" << endl;
	cout << "enter END to exit." << endl;
	while (getline(wcin, s)&&s != L"END")
	{
		s = text.select_level(s);
		address.find_address(text.find_number(text.find_name(s)));
		text.show();
		address.show(text.Level());
	}
	system("pause");
}