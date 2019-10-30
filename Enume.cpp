#include"Enume.h"
#include<algorithm>
using namespace std;

Enume::Enume(){}
Enume::Enume(vector<pair<char, int> > &_a){
	swap(poker, _a);
}

void Enume::clear(vector<pair<char, int> >& _a) {
	swap(poker, _a);
	max_weight = 0;
	vector<int> p;
	for (int i = 1; i <= 13; i++)
		p.push_back(i);
	dfs1(p, 5, 13);
}

void Enume::dfs1(vector<int>& p, int r, int n) {
	for (int s = (1 << r) - 1; s < 1 << n;) {
		choose.clear();
		vector<int> cur = p;
		for (int j = n - 1; j >= 0; j--) {
			if (((s >> j) & 1)) choose.push_back(poker[p[j]]), cur.erase(cur.begin() + j, cur.begin() + j + 1);
		}
		back.init(choose);
		dfs2(cur, 5, 8);
		int x = s & -s;
		int y = s + x;
		s = ((s & ~y) / x >> 1) | y;
	}
}

void Enume::dfs2(vector<int> & p, int r, int n) {
	for (int s = (1 << r) - 1; s < 1 << n;) {
		choose.clear();
		vector<int> cur = p;
		for (int j = n - 1; j >= 0; j--) {
			if (((s >> j) & 1)) choose.push_back(poker[p[j]]), cur.erase(cur.begin() + j, cur.begin() + j + 1);
		}
		mid.init(choose);
		int x = s & -s;
		int y = s + x;
		s = ((s & ~y) / x >> 1) | y;
		if (mid.weight > back.weight) continue;
		dfs3(cur, 3, 3);
	}
}

void Enume::dfs3(vector<int> & p, int r, int n) {
	choose.clear();
	for (int j = 0; j < n; j++) {
		choose.push_back(poker[p[j]]);
	}
	front.init(choose);
	if (front.weight > mid.weight) return;
	best_choose();
}

void Enume::best_choose()//Ȩֵ
{
	int weight = front.weight + mid.weight + back.weight;
	if (weight > max_weight)
	{
		max_weight = weight;
		best[1] = front;
		best[2] = mid;
		best[3] = back;
	}
}