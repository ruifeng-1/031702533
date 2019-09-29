#include<iostream>
#include<cstring>
#include <boost/regex.hpp>
#include<fstream>
#include <locale>
using namespace std;
using namespace boost;

class Text//�ı���
{
public:
	Text(){}
	wstring select_level(wstring s);
	wstring find_name(wstring s);
	wstring find_number(wstring s);
	void show();
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
	wregex re(L"\\w+?[^\\,]");
	wsmatch sm;
	if (regex_search(s, sm, re))//��������
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
	if (regex_search(s, sm, re))//�����ֻ�����
		number = sm.str();
	else
		cout << "find_number error" << endl;
	size_t i = s.find_first_of(number);//�����ֻ���������λ��
	return address = s.substr(0,i)+s.substr(i+11);//�ϲ�ʣ�µ��ַ���
}

wstring Text::Level()
{
	return level;
}

void Text::show()//����������ֻ�����
{
	wcout << L"\"����\":\"" << name << L"\"," << "\r\n" << L"\"�ֻ�\":\"" << number << L"\"," << "\r\n";
}

class Address//��ַ��
{
public:
	Address(){}
	void find_address(wstring s);
	wstring search_address(wstring wstr, wregex wre);
	bool match_address(wstring wstr, wregex wre);
	void show(wstring diff);
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
	wregex wre1(L"(\\����|\\���|\\�Ϻ�|\\����)\\��??|(\\�ӱ�|\\ɽ��|\\����|\\����|\\������|\\����|\\�㽭|\\����|\\����|\\����|\\ɽ��|\\����|\\����|\\����|\\�㶫|\\����|\\�Ĵ�|\\����|\\����|\\����|\\����|\\�ຣ)\\ʡ?");
	wregex wre2(L"\\w+?\\��");
	wregex wre3(L"\\w+?(\\��|\\��)");
	wregex wre4(L"\\w+?(\\�ֵ�|\\��|\\��)");
	wregex wre5(L"\\w+?(\\·|\\��|\\��)");
	wregex wre6(L"\\d+?(\\��)");
	wregex wre7(L".+[^\\.]");
	wregex wre1_0(L"(\\����|\\���|\\�Ϻ�|\\����)\\��?");

	province = search_address(s, wre1);//����ʡ, ֱϽ��
	if(!match_address(province,wre1_0))//ƥ���Ƿ�ֱϽ��
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

wstring Address::search_address(wstring wstr,wregex wre)//������ʽ����
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

void Address::show(wstring diff)//�����ַ
{
	if(diff==L"1!")
		wcout << L"\"��ַ\":[\r\n\"" << province << L"\",\r\n\"" << city << L"\",\r\n\"" << county << L"\",\r\n\"" << town << L"\",\r\n\"" << road << house_number << detail << L"\"\r\n]" <<endl;
	if(diff==L"2!")
		wcout << L"\"��ַ\":[\r\n\"" << province << L"\",\r\n\"" << city << L"\",\r\n\"" << county << L"\",\r\n\"" << town << L"\",\r\n\"" << road << L"\",\r\n\"" << house_number << L"\",\r\n\"" << detail << L"\"\r\n]" <<endl;
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