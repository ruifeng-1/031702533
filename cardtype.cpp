#include"cardtype.h"
#include<algorithm>
using namespace std;

bool cmp(const pair<char, int>& a, const pair<char, int>& b) //∂®“Â≈≈–Ú¬ﬂº≠
{
	if (a.second == b.second)
		return a.first < b.first;
	return a.second < b.second;
}

int SimpleCardtype::judge_cardtype()//≈–∂œ≈∆–Õ
{
	if (poker.size() == 5)
	{
		if (sameColor && straight)
			return 9;
		if (type[4])
			return 8;
		if (type[3] && type[2])
			return 7;
		if (sameColor)
			return 6;
		if (straight)
			return 5;
		if (type[3])
			return 4;
		if (type[2] >= 2) {
			if (tmp[0].second == tmp[1].second + 1 || tmp[0].second == tmp[1].second - 1) return 3;
			return 2;
		}
		if (type[2])
			return 1;
		return 0;
	}
	else
	{
		if (type[3])
			return 3;
		if (type[2])
			return 1;
		return 0;
	}
}

bool SimpleCardtype::checkSameColor() {
	if (poker.size() != 5) return false;
	char color = poker[0].first;
	for (int i = 1; i < 5; i++)
		if (poker[i].first != color)
			return false;
	return true;
}

bool SimpleCardtype::checkStraight() {
	if (poker.size() != 5) return false;
	for (int i = 0; i < 4; i++)
		if (poker[i].second != poker[i + 1].second - 1)
			return false;
	return true;
}


SimpleCardtype::SimpleCardtype() {}
SimpleCardtype::SimpleCardtype(vector<pair<char, int> > & choose) {
	init(choose);
}

void SimpleCardtype::init(vector<pair<char, int> > & choose) {
	swap(choose, poker);
	fill(type, type + 11, 0);
	sort(poker.begin(), poker.end(), cmp);
	tmp.clear();
	for (int i = 0; i <= 14; i++) tmp.push_back({ 0, i });
	for (int i = 0; i < poker.size(); i++)
		tmp[poker[i].second].first++;
	sort(tmp.begin(), tmp.end(), greater<pair<int, int> >());
	int val = 0;
	for (int i = 0; i < tmp.size() && tmp[i].first != 0; i++) {
		val = 20 * val + tmp[i].second;
		type[tmp[i].first] ++;
	}
	if (poker.size() == 3) val *= 400;
	sameColor = checkSameColor();
	straight = checkStraight();
	int k = 1e7;
	weight = judge_cardtype() * k + val;
}