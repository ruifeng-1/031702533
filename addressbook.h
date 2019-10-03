#include<iostream>
#include<cstring>
#include <boost/regex.hpp>
#include<fstream>
#include <locale>
#include<cstdlib>
#include"cJSON.h"
using namespace std;
using namespace boost;

std::string wstos(const std::wstring &ws)//宽字符串转换为字符串
{
	setlocale(LC_CTYPE, "");                                          
	size_t convertNum;
	size_t wsize = wcslen(ws.c_str());
	size_t asize = wsize * 2 + 1;
	char* str = (char*)malloc(asize * sizeof(char));
	if (wcstombs_s(&convertNum, str, asize, ws.c_str(), asize))
	{
		cout << "转换失败" << endl;
	}
	std::string result = str;
	delete[]str;
	return result;
}

std::wstring stows(const std::string &s)//字符串转化为宽字符串
{
	setlocale(LC_CTYPE, "");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t* _Dest = new wchar_t[_Dsize];
	size_t i;
	mbstowcs_s(&i, _Dest, _Dsize, _Source, s.size());
	std::wstring result = _Dest;
	delete[] _Dest;
	return result;
}

char* json_printf(string s)//字符串转化为json格式
{
	char* json = NULL;
	cJSON* cjson = cJSON_Parse(s.c_str());
	if (cjson == NULL)
	{
		cout << "json pack into cjson error..." << endl;
	}
	else
	{
		json = cJSON_Print(cjson);
	}
	cJSON_Delete(cjson);
	return json;
}

class Text//文本类
{
public:
	Text() {}
	wstring select_level(wstring s);
	wstring find_name(wstring s);
	wstring find_number(wstring s);
	string returnText();
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
	wregex re(L"\\w+[^\\,]");
	wsmatch sm;
	if (regex_search(s, sm, re))//查找姓名
	{
		name = sm.str();
		return s.substr(name.length() + 1);
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
	size_t flag = s.find('.');
	if (i = flag-20)
		return address = s.substr(0, i);//合并剩下的字符串
	else
		return address = s.substr(0, i) + s.substr(i + 11);
}

wstring Text::Level()
{
	return level;
}

string Text::returnText()//输出姓名，手机号码
{
	string Text = "{\"姓名\":\"" + wstos(name) + "\",\"手机\":\"" + wstos(number) + "\",";
	//wcout << L"{\"姓名\":\"" << name << L"\"," << L"\"手机\":\"" << number << L"\",";
	return Text;
}

class Address//地址类
{
public:
	Address() {}
	void find_address(wstring s);
	wstring search_address(wstring wstr, wregex wre);
	bool match_address(wstring wstr, wregex wre);
	string returnAddress(wstring level);
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
	wregex wre1(L"(\\北京|\\天津|\\上海|\\重庆)\\市??|(\\河北|\\山西|\\辽宁|\\吉林|\\黑龙江|\\江苏|\\浙江|\\安徽|\\福建|\\江西|\\山东|\\河南|\\湖北|\\湖南|\\广东|\\海南|\\四川|\\贵州|\\云南|\\陕西|\\甘肃|\\青海)\\省?|(\\内蒙古|\\广西壮族|\\西藏|\\宁夏回族|\\新疆维吾尔)\\自治区?");
	wregex wre2(L"\\w+?\\市");
	wregex wre3(L"\\w+?(\\县|\\区)");
	wregex wre4(L"\\w+?(\\街道|\\镇|\\乡)");
	wregex wre5(L"\\w+?(\\路|\\街|\\巷)");
	wregex wre6(L".+?(\\号)");
	wregex wre7(L".+[^\\.]");
	wregex wre1_0(L"(\\北京|\\天津|\\上海|\\重庆)\\市?");

	province = search_address(s, wre1);//查找省, 直辖市
	if (!match_address(province, wre1_0))//匹配是否直辖市
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

wstring Address::search_address(wstring wstr, wregex wre)//正则表达式搜索
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

string Address::returnAddress(wstring level)//输出地址
{
	string address;
	if (level == L"1!")
	{
		address = "\"地址\":[\"" + wstos(province) + "\",\"" + wstos(city) + "\",\"" + wstos(county) + "\",\"" + wstos(town) + "\",\"" + wstos(road) + wstos(house_number) + wstos(detail) + "\"]}";
		//wcout << L"\"地址\":[\"" << province << L"\",\"" << city << L"\",\"" << county << L"\",\"" << town << L"\",\"" << road << house_number << detail << L"\"]}" << endl;
	}	
	else
	{
		address = "\"地址\":[\"" + wstos(province) + "\",\"" + wstos(city) + "\",\"" + wstos(county) + "\",\"" + wstos(town) + "\",\"" + wstos(road) + "\",\"" + wstos(house_number) + "\",\"" + wstos(detail) + "\"]}";
		//wcout << L"\"地址\":[\"" << province << L"\",\"" << city << L"\",\"" << county << L"\",\"" << town << L"\",\"" << road << L"\",\"" << house_number << L"\",\"" << detail << L"\"]}" << endl;
	}	
	return address;
}