#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include"cardtype.h"
#include"json/json.h"
#include"include/curl/curl.h"
using namespace std;
typedef long long ll;
pair<char, int> a[14] = { {'&',0 },{'&',2 },{'&',3 },{'&',4 },{'&',5 },{'&',6 }, {'*',13 } ,{'&',13 }, {'#',13 }, {'$',13 }, {'$',9 }, {'#',9 }, {'*',9 }, {'&',7} };//全局变量，牌组
SimpleCardtype best1, best2, best3;//最优牌组
Json::FastWriter writer;
int ID;
int max_weight = 0;//最大权值
int i = 0, t1 = 0, t2 = 0;

class Enume//枚举
{
public:
    SimpleCardtype front, mid, back;
	void dfs1(vector<int> &p, int r, int n);
	void dfs2(vector<int> &p, int r, int n);
	void dfs3(vector<int> &p, int r, int n);
	vector<pair<char, int> > choose;
	void best_choose();
};

void Enume::dfs1(vector<int> &p, int r, int n) {
	for (ll s = (1 << r) - 1; s < 1 << n;) {
        t1 = s;
		choose.clear();
		vector<int> cur = p;
		for (int j = n - 1; j >= 0; j--) {
			if (((s >> j) & 1)) choose.push_back(a[p[j]]), cur.erase(cur.begin() + j, cur.begin() + j + 1);
		}
		back.init(choose);
		dfs2(cur, 5, 8);
		ll x = s & -s;
		ll y = s + x;
		s = ((s&~y) / x >> 1) | y;
	}
}

void Enume::dfs2(vector<int> &p, int r, int n) {
	for (ll s = (1 << r) - 1; s < 1 << n;) {
	    t2 = s;
		choose.clear();
		vector<int> cur = p;
		for (int j = n - 1; j >= 0; j--) {
			if (((s >> j) & 1)) choose.push_back(a[p[j]]), cur.erase(cur.begin() + j, cur.begin() + j + 1);
		}
		mid.init(choose);
		ll x = s & -s;
		ll y = s + x;
		s = ((s&~y) / x >> 1) | y;
		if(mid.weight > back.weight) continue;
		dfs3(cur, 3, 3);
	}
}

void Enume::dfs3(vector<int> &p, int r, int n) {
	choose.clear();
	for (int j = 0; j < n; j++) {
		choose.push_back(a[p[j]]);
	}
	front.init(choose);
	if(front.weight > mid.weight) return ;
	best_choose();
}

void Enume::best_choose()//权值
{
    int weight = front.weight + mid.weight + back.weight;
    if (weight > max_weight)
    {
        max_weight = weight;
        best1 = front;
        best2 = mid;
        best3 = back;
    }
}

void input_best()//出牌测试
{
	for (auto x : best1.poker) {
		cout << x.first << x.second << " ";
	}
	cout << endl;
	for (auto x : best2.poker) {
		cout << x.first << x.second << " ";
	}
	cout << endl;
	for (auto x : best3.poker) {
		cout << x.first << x.second << " ";
	}
	cout << endl;
}

SimpleCardtype transform(SimpleCardtype best1)//转换
{
	for (int i = 0; i < best1.poker.size(); i++)
	{
		string str = "0";
		str[0] = best1.poker[i].first;
		if (best1.poker[i].second < 10)
			best1.input.push_back(str + to_string(best1.poker[i].second));
		else if (best1.poker[i].second == 11)
			best1.input.push_back(str + "J");
		else if (best1.poker[i].second == 12)
			best1.input.push_back(str + "Q");
		else if (best1.poker[i].second == 13)
			best1.input.push_back(str + "K");
		else if (best1.poker[i].second == 14) 
			best1.input.push_back(str + "A");
	}
	return best1;
}

void input_best_2()
{
	best1 = transform(best1);
	best2 = transform(best2);
	best3 = transform(best3);
	for (auto x : best1.input) {
		cout << x << " ";
	}
	cout << endl;
	for (auto x : best2.input) {
		cout << x << " ";
	}
	cout << endl;
	for (auto x : best3.input) {
		cout << x << " ";
	}
	cout << endl;
}

Json::Value data_to_json(SimpleCardtype best1, SimpleCardtype best2, SimpleCardtype best3,int ID)
{
	string str;
	Json::Value data;
	data["id"] = Json::Value(ID);
	str = best1.input[0];
	for (int i = 1; i < best1.input.size(); i++)
	{
		str += " " + best1.input[i];
	}
	data["card"].append(str);
	str = best2.input[0];
	for (int i = 1; i < best2.input.size(); i++)
	{
		str += " " + best2.input[i];
	}
	data["card"].append(str);
	str = best3.input[0];
	for (int i = 1; i < best3.input.size(); i++)
	{
		str += " " + best3.input[i];
	}
	data["card"].append(str);
	cout << writer.write(data) << endl;
	return data;
}

void json_to_data(Json::Value data)
{
	string str;
	str = writer.write(data["id"]);//解析ID
	ID = atoi(str.c_str());//保存ID
	str = writer.write(data["card"]);//解析牌组
	int k = 1;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == ' ')
			break;
		a[k].first = str[i++];
		if (str[i] >= '2'&&str[i] <= '9')
		{
			if (str[i] != '1')
				a[k++].second = str[i] - '0';
			else
			{
				a[k++].second = 10;
				i++;
			}
		}
		else
		{
			if (str[i] == 'J')
				a[k++].second = 11;
			if (str[i] == 'Q')
				a[k++].second = 12;
			if (str[i] == 'K')
				a[k++].second = 13;
			if (str[i] == 'A')
				a[k++].second = 14;
		}
	}
}

int main() {
	vector<int> p;
	Enume enume;
	for (int i = 1; i <= 13; i++)
		cout << a[i].first << a[i].second << " ";
	cout << endl;
	for (int i = 1; i <= 13; i++)
		p.push_back(i);
	enume.dfs1(p, 5, 13);
	input_best();//输出测试1
	input_best_2();//输出测试2
	Json::Value data = data_to_json(best1, best2, best3, 1001);
	system("pause");
    return 0;
}
