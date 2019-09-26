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
	string find_name(string s);
	string find_number(string s);
	void show();
private:
	string name;//����
	string number;//�ֻ�����
	string address;//��ַ
};

string Text::find_name(string s)
{
	regex re("\\w+\\,");
	smatch sm;
	if (regex_search(s, sm, re))//��������
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
	if (regex_search(s, sm, re))//�����ֻ�����
		number = sm.str();
	else
		cout << "find_number error" << endl;
	size_t i = s.find_first_of(number);//�����ֻ���������λ��
	return s.substr(0,i)+s.substr(i+11);//�ϲ�ʣ�µ��ַ���
}

void Text::show()//����������ֻ�����
{
	cout << "\"����\":\"" << name << "\",\"�ֻ�\":\"" << number << "\"";
}

class Address//��ַ��
{
public:
	void find_address(string s);
	wstring search_address(wstring wstr, wregex wre);
	bool match_address(wstring wstr, wregex wre);
	void show();
private:
	wstring province;//ʡ
	wstring city;//��
	wstring county;//��
	wstring town;//��
	wstring road;//·
	wstring house_number;//���ƺ�
	wstring detail;//��ϸ��ַ
};

void Address::find_address(string s)
{
	wregex wre1(L"(\\����|\\���|\\�Ϻ�|\\����)\\��??|(\\�ӱ�|\\ɽ��|\\����|\\����|\\������|\\����|\\�㽭|\\����|\\����|\\����|\\ɽ��|\\����|\\����|\\����|\\�㶫|\\����|\\�Ĵ�|\\����|\\����|\\����|\\����|\\�ຣ)\\ʡ?");
	wregex wre2(L"\\w+?\\��");
	wregex wre3(L"\\w+?(\\��|\\��)");
	wregex wre4(L"\\w+?(\\�ֵ�|\\��|\\��)");
	wregex wre5(L"\\w+?(\\·|\\��|\\��)");
	wregex wre6(L"\\d+?(\\��)");
	wregex wre7(L".+[^\\.]");
	wregex wre1_0(L"(\\����|\\���|\\�Ϻ�|\\����)\\��?");
	setlocale(LC_CTYPE, "");
	size_t len = mbstowcs(NULL, s.c_str(), s.length()); // ����ת������ַ����ĳ���
	wchar_t *wch = new wchar_t[len + 1];
	size_t len0 = mbstowcs(wch, s.c_str(), s.length()); // ת��Ϊ���ַ�����ת������ַ����н�������
	wstring s0(wch);
	delete[]wch;
	province = search_address(s0, wre1);//����ʡ, ֱϽ��
	if(!match_address(province,wre1_0))//ƥ���Ƿ�ֱϽ��
		s0 = s0.substr(province.length());//�и��ַ�������ͬ
	city = search_address(s0, wre2);//������
	s0 = s0.substr(city.length());
	county = search_address(s0, wre3);//�����أ���
	s0 = s0.substr(county.length());
	town = search_address(s0, wre4);//���ҽֵ�������
	s0 = s0.substr(town.length());
	road = search_address(s0,wre5);//����·���֣���
	s0 = s0.substr(road.length());
	house_number = search_address(s0, wre6);
	s0 = s0.substr(house_number.length());
	detail = search_address(s0, wre7);
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

void Address::show()//�����ַ
{
	wcout << L",\"��ַ\":[\"" << province << L"\",\"" << city << L"\",\"" << county << L"\",\"" << town << L"\",\"" << road << L"\",\"" << house_number << L"\",\"" << detail << L"\"]" << endl;
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