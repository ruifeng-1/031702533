#include<iostream>
#include<cstring>
#include <boost/regex.hpp>
#include<fstream>
#include <locale>
#include<cstdlib>
#include"cJSON.h"
using namespace std;
using namespace boost;

std::string wstos(const std::wstring &ws)//���ַ���ת��Ϊ�ַ���
{
	setlocale(LC_CTYPE, "");                                          
	size_t convertNum;
	size_t wsize = wcslen(ws.c_str());
	size_t asize = wsize * 2 + 1;
	char* str = (char*)malloc(asize * sizeof(char));
	if (wcstombs_s(&convertNum, str, asize, ws.c_str(), asize))
	{
		cout << "ת��ʧ��" << endl;
	}
	std::string result = str;
	delete[]str;
	return result;
}

std::wstring stows(const std::string &s)//�ַ���ת��Ϊ���ַ���
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

char* json_printf(string s)//�ַ���ת��Ϊjson��ʽ
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

class Text//�ı���
{
public:
	Text() {}
	wstring select_level(wstring s);
	wstring find_name(wstring s);
	wstring find_number(wstring s);
	string returnText();
	wstring Level();
private:
	wstring name;//����
	wstring number;//�ֻ�����
	wstring address;//��ַ
	wstring level;//�Ѷ�
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
	if (regex_search(s, sm, re))//��������
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
	if (regex_search(s, sm, re))//�����ֻ�����
		number = sm.str();
	else
		cout << "find_number error" << endl;
	size_t i = s.find_first_of(number);//�����ֻ���������λ��
	size_t flag = s.find('.');
	if (i = flag-20)
		return address = s.substr(0, i);//�ϲ�ʣ�µ��ַ���
	else
		return address = s.substr(0, i) + s.substr(i + 11);
}

wstring Text::Level()
{
	return level;
}

string Text::returnText()//����������ֻ�����
{
	string Text = "{\"����\":\"" + wstos(name) + "\",\"�ֻ�\":\"" + wstos(number) + "\",";
	//wcout << L"{\"����\":\"" << name << L"\"," << L"\"�ֻ�\":\"" << number << L"\",";
	return Text;
}

class Address//��ַ��
{
public:
	Address() {}
	void find_address(wstring s);
	wstring search_address(wstring wstr, wregex wre);
	bool match_address(wstring wstr, wregex wre);
	string returnAddress(wstring level);
private:
	wstring province;//ʡ
	wstring city;//��
	wstring county;//��
	wstring town;//��
	wstring road;//·
	wstring house_number;//���ƺ�
	wstring detail;//��ϸ��ַ
};

void Address::find_address(wstring s)
{
	wregex wre1(L"(\\����|\\���|\\�Ϻ�|\\����)\\��??|(\\�ӱ�|\\ɽ��|\\����|\\����|\\������|\\����|\\�㽭|\\����|\\����|\\����|\\ɽ��|\\����|\\����|\\����|\\�㶫|\\����|\\�Ĵ�|\\����|\\����|\\����|\\����|\\�ຣ)\\ʡ?|(\\���ɹ�|\\����׳��|\\����|\\���Ļ���|\\�½�ά���)\\������?");
	wregex wre2(L"\\w+?\\��");
	wregex wre3(L"\\w+?(\\��|\\��)");
	wregex wre4(L"\\w+?(\\�ֵ�|\\��|\\��)");
	wregex wre5(L"\\w+?(\\·|\\��|\\��)");
	wregex wre6(L".+?(\\��)");
	wregex wre7(L".+[^\\.]");
	wregex wre1_0(L"(\\����|\\���|\\�Ϻ�|\\����)\\��?");

	province = search_address(s, wre1);//����ʡ, ֱϽ��
	if (!match_address(province, wre1_0))//ƥ���Ƿ�ֱϽ��
		s = s.substr(province.length());//�и��ַ�������ͬ
	city = search_address(s, wre2);//������
	s = s.substr(city.length());
	county = search_address(s, wre3);//�����أ���
	s = s.substr(county.length());
	town = search_address(s, wre4);//���ҽֵ�������
	s = s.substr(town.length());
	road = search_address(s, wre5);//����·���֣���
	s = s.substr(road.length());
	house_number = search_address(s, wre6);//�������ƺ�
	detail = search_address(s.substr(house_number.length()), wre7);
}

wstring Address::search_address(wstring wstr, wregex wre)//������ʽ����
{
	wsmatch wsm;
	if (regex_search(wstr, wsm, wre))
		return wsm.str();
	else
		return  L"";
}

bool Address::match_address(wstring wstr, wregex wre)// ������ʽƥ��
{
	wsmatch wsm;
	if (regex_match(wstr, wsm, wre))
		return true;
	else
		return false;
}

string Address::returnAddress(wstring level)//�����ַ
{
	string address;
	if (level == L"1!")
	{
		address = "\"��ַ\":[\"" + wstos(province) + "\",\"" + wstos(city) + "\",\"" + wstos(county) + "\",\"" + wstos(town) + "\",\"" + wstos(road) + wstos(house_number) + wstos(detail) + "\"]}";
		//wcout << L"\"��ַ\":[\"" << province << L"\",\"" << city << L"\",\"" << county << L"\",\"" << town << L"\",\"" << road << house_number << detail << L"\"]}" << endl;
	}	
	else
	{
		address = "\"��ַ\":[\"" + wstos(province) + "\",\"" + wstos(city) + "\",\"" + wstos(county) + "\",\"" + wstos(town) + "\",\"" + wstos(road) + "\",\"" + wstos(house_number) + "\",\"" + wstos(detail) + "\"]}";
		//wcout << L"\"��ַ\":[\"" << province << L"\",\"" << city << L"\",\"" << county << L"\",\"" << town << L"\",\"" << road << L"\",\"" << house_number << L"\",\"" << detail << L"\"]}" << endl;
	}	
	return address;
}