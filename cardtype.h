#include<stdio.h>
#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

bool cmp(const pair<char, int> &a, const pair<char, int> &b) //定义排序逻辑
{
	if (a.second == b.second)
		return a.first < b.first;
	return a.second < b.second;
}

class SimpleCardtype//普通牌型
{
public:
	int calculate_weights(vector<pair<char, int>> choose)//计算权值
	{
		sort(choose.begin(), choose.end(), cmp);//
		vector<pair<int, int> > tmp;
		for (int i = 0; i <= 13; i++) tmp.push_back({ 0, i });
		for (int i = 0; i < choose.size(); i++)
			tmp[choose[i].second].first++;
		sort(tmp.begin(), tmp.end(), greater<pair<int, int> >());
		int val = 0;
		for (int i = 0; i < tmp.size() && tmp[i].first != 0; i++)
			val = 20 * val + tmp[i].second;
		int k = 1e8;
		int weight = judge_cardtype(choose)*k;
		return weight + val;
	}
	int judge_cardtype(vector<pair<char, int>> choose)//判断牌型
	{
		if (choose.size() == 5)
		{
			if (cardtype1(choose) & cardtype2(choose))
				return 8;
			if (cardtype3(choose))
				return 7;
			if (cardtype4(choose) & cardtype5(choose))
				return 6;
			if (cardtype1(choose))
				return 5;
			if (cardtype2(choose))
				return 4;
			if (cardtype4(choose))
				return 3;
			if (cardtype6(choose))
				return 2;
			if (cardtype5(choose))
				return 1;
			return 0;
		}
		else
		{
			if (cardtype4(choose))
				return 3;
			if (cardtype5(choose))
				return 1;
			return 0;
		}
		
	}
	bool cardtype1(vector<pair<char, int>> choose)//同花
	{
		char color = choose[0].first;
		for (int i = 1; i < 5; i++)
		{
			if (choose[i].first != color)
				return false;
		}
		return true;
	}
	bool cardtype2(vector<pair<char, int>> choose)//顺子
	{
		for (int i = 0; i < 4; i++)
		{
			if (choose[i].second != choose[i + 1].second - 1)
				return false;
		}
		return true;
	}
	bool cardtype3(vector<pair<char, int>> choose)//炸弹
	{
		for (int i = 0; i < 2; i++)
		{
			int ok = 1;
			int number = choose[i].second;
			for (int j = i + 1; j < i + 4; j++)
			{
				if (choose[j].second != number)
				{
					ok = 0;
					break;
				}
			}
			if (ok)
				return true;
		}
		return false;
	}
	bool cardtype4(vector<pair<char, int>> choose)//三条
	{
		if (choose.size() == 5)
		{
			for (int i = 0; i < 3; i++)
			{
				int ok = 1;
				int number = choose[i].second;
				for (int j = i + 1; j < i + 3; j++)
				{
					if (choose[j].second != number)
					{
						ok = 0;
						break;
					}
				}
				if (ok)
					return true;
			}
			return false;
		}
		else
		{
			for (int i = 1; i < 3; i++)
			{
				if (choose[i].second != choose[0].second)
					return false;
			}
			return true;
		}
		
	}
	bool cardtype5(vector<pair<char, int>> choose)//对子
	{
		for (int i = 0; i < choose.size()-1; i++)
		{
			if (choose[i].second == choose[i + 1].second)
				return true;
		}
		return false;
	}
	bool cardtype6(vector<pair<char, int>> choose)//两对
	{
		int ok = 0;
		for (int i = 0; i < 4; i++)
		{
			if (choose[i].second == choose[i + 1].second)
				ok++;
		}
		if (ok == 2)
			return true;
		else
			return false;
	}
};

class SpecialCardtype//特殊牌型
{
public:
	bool judge_cardtype(vector<pair<char, int>> group)//判断牌型
	{
		sort(group.begin(), group.end(), cmp);//升序排序
	}
	bool cardtype1(vector<pair<char, int>> group)//一条龙&至尊清龙
	{
		for (int i = 0; i < group.size(); i++)
		{
			if (group[i].second != group[i + 1].second - 1)
				return false;
		}
		return true;
	}
	 bool cardtype2(vector<pair<char, int>> group)//十二皇族
	 {
		 int ok = 0;
		 for (int i = 0; i < group.size(); i++)
		 {
			 if (group[i].second <= 9)
				 ok ++;
			 if (ok >= 2)
				 return false;
		 }
		 return true;
	 }
	 bool cardtype3(vector<pair<char, int>> group)//三同花顺
	 {

	 }
	 bool cardtype4(vector<pair<char, int>> group)//三分天下
	 {
		 int ok = 0;
		 for (int i = 0; i < group.size() - 3; i++)
		 {

		 }
	 }
	 bool cardtype5(vector<pair<char, int>> group)//全大
	 {
		 for (int i = 0; i < group.size(); i++)
		 {
			 if (group[i].second < 7)
				 return false;
		 }
		 return true;
	 }
	 bool cardtype6(vector<pair<char, int>> group)//全小
	 {
		 for (int i = 0; i < group.size(); i++)
		 {
			 if (group[i].second > 7)
				 return false;
		 }
		 return true;
	 }
	 bool cardtype7(vector<pair<char, int>> group)//凑一色
	 {
		 char color = group[0].first;
		 if(color=='*'&&color=='#')//方块或梅花
			 for (int i = 1; i < group.size(); i++)
			 {
				 if (group[i].first != '*'&&group[i].first != '#')
					 return false;
			 }
		 else//红桃或黑桃
			 for (int i = 1; i < group.size(); i++)
			 {
				 if (group[i].first != '&'&&group[i].first != '$')
					 return false;
			 }
		 return true;
	 }
	 bool cardtype8(vector<pair<char, int>> group)//双怪冲三
	 {

	 }
	 bool cardtype9(vector<pair<char, int>> group)//四套三条
	 {

	 }
	 bool cardtype10(vector<pair<char, int>> group)//五对三条
	 {

	 }
	 bool cardtype11(vector<pair<char, int>> group)//六对半
	 {

	 }
	 bool cardtype12(vector<pair<char, int>> group)//三顺子
	 {

	 }
	 bool cardtype13(vector<pair<char, int>> group)//三同花
	 {

	 }
};
