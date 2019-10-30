#include"cardtype.h"
#include<vector>

#pragma once
class Enume//Ã¶¾Ù
{
public:
	vector<pair<char, int> > poker;
	SimpleCardtype best[4];
	int max_weight;
	SimpleCardtype front, mid, back;
	void dfs1(vector<int>& p, int r, int n);
	void dfs2(vector<int>& p, int r, int n);
	void dfs3(vector<int>& p, int r, int n);
	vector<pair<char, int> > choose;
	void best_choose();
	Enume();
	Enume(vector<pair<char, int> >& _a);
	void clear(vector<pair<char, int> >& _a);
};