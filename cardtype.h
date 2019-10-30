#include<vector>
using namespace std;

#pragma once
class SimpleCardtype//墩
{
private:
	int judge_cardtype();//判断牌型
	bool checkSameColor();//判断同花
	bool checkStraight();//判断顺子
public:
	SimpleCardtype();
	SimpleCardtype(vector<pair<char, int> >& choose);
	vector<pair<char, int> > poker; // 该墩扑克
	int type[11];// 该墩扑克张数组成
	bool sameColor, straight;// 是否是同花，顺子
	int weight;// 该墩评分
	void init(vector<pair<char, int> >& choose);//初始化
};

bool cmp(const pair<char, int>& a, const pair<char, int>& b); //定义排序逻辑
