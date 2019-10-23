#include<stdio.h>
#include<iostream>
#include<vector>
#include"cardtype.h"
using namespace std;
typedef long long ll;

pair<char, int> a[14];//全局变量，牌组
vector<pair<char, int> > best1, best2, best3;//最优牌组
int max_weight = 0;//最大权值
int i = 0;//枚举次数

class Enume//枚举
{
public:
	vector<pair<char, int> > choose1, choose2, choose3;//三墩
	SimpleCardtype simple;
	void dfs1(vector<int> p, int r, int n);
	void dfs2(vector<int> p, int r, int n);
	void dfs3(vector<int> p, int r, int n);
	void best_choose();

};
void Enume::dfs1(vector<int> p, int r, int n) {
	for (ll s = (1 << r) - 1; s < 1 << n;) {
		choose1.clear();
		vector<int> cur = p;
		for (int j = n - 1; j >= 0; j--) {
			if (((s >> j) & 1)) choose1.push_back(a[p[j]]), cur.erase(cur.begin() + j, cur.begin() + j + 1);
		}
		dfs2(cur, 3, 8);
		ll x = s & -s;
		ll y = s + x;
		s = ((s&~y) / x >> 1) | y;
	}
}

void Enume::dfs2(vector<int> p, int r, int n) {
	for (ll s = (1 << r) - 1; s < 1 << n;) {
		choose3.clear();
		vector<int> cur = p;
		for (int j = n - 1; j >= 0; j--) {
			if (((s >> j) & 1)) choose3.push_back(a[p[j]]), cur.erase(cur.begin() + j, cur.begin() + j + 1);
		}
		dfs3(cur, 5, 5);
		ll x = s & -s;
		ll y = s + x;
		s = ((s&~y) / x >> 1) | y;
	}
}

void Enume::dfs3(vector<int> p, int r, int n) {
	choose2.clear();
	for (int j = 0; j < n; j++) {
		choose2.push_back(a[p[j]]);
	}
	//cout << ++i << endl;//输出枚举次数
	best_choose();
}

void Enume::best_choose()//权值
{
	int weight1 = simple.calculate_weights(choose1), 
		weight2 = simple.calculate_weights(choose2), 
		weight3 = simple.calculate_weights(choose3);
	if (weight1 > weight2 && weight2 > weight3)
	{
		int weight = weight1 + weight2 + weight3;
		if (weight > max_weight)
		{
			max_weight = weight;
			best1 = choose1;
			best2 = choose2;
			best3 = choose3;//把三墩牌存进最优牌组
		}
	}
}

void input_best()//出牌测试
{
	for (auto x : best3) {
		cout << x.first << x.second << " ";
	}
	cout << endl;
	for (auto x : best2) {
		cout << x.first << x.second << " ";
	}
	cout << endl;
	for (auto x : best1) {
		cout << x.first << x.second << " ";
	}
	cout << endl;

	SimpleCardtype simple;
	cout << simple.calculate_weights(best3) << endl;
	cout << simple.calculate_weights(best2) << endl;
	cout << simple.calculate_weights(best1) << endl;
	cout << max_weight << endl;
}

int main() {
	vector<int> p;
	Enume enume;
	for (int i = 1; i <= 13; i++)
		a[i] = { i % 4 + 'A', i }; // 字母花色， i牌大小
	for (int i = 1; i <= 13; i++)
		cout << a[i].first << a[i].second << " ";
	cout << endl;
	for (int i = 1; i <= 13; i++)
		p.push_back(i);
	enume.dfs1(p, 5, 13);
	input_best();
	system("pause");
}