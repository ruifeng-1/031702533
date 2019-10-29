#include<stdio.h>
#include<iostream>
#include<vector>
#include <algorithm>
#include<string>
#include"json/json.h"
#include"include/curl/curl.h"
using namespace std;

bool cmp(const pair<char, int> &a, const pair<char, int> &b) //定义排序逻辑
{
	if (a.second == b.second)
		return a.first < b.first;
	return a.second < b.second;
}

class SimpleCardtype//普通牌型
{
private:
	int judge_cardtype()//判断牌型
	{
		if (poker.size() == 5)
		{
			if (sameColor && straight)
				return 8;
			if (type[4])
				return 7;
			if (type[3] && type[2])
				return 6;
			if (sameColor)
				return 5;
			if (straight)
				return 4;
			if (type[3])
				return 3;
			if (type[2] >= 2)
				return 2;
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
	bool checkSameColor() {
		if (poker.size() != 5) return false;
		char color = poker[0].first;
		for (int i = 1; i < 5; i++)
			if (poker[i].first != color)
				return false;
		return true;
	}
	bool checkStraight() {
		if (poker.size() != 5) return false;
		for (int i = 0; i < 4; i++)
			if (poker[i].second != poker[i + 1].second - 1)
				return false;
		return true;
	}
public:
	vector<pair<char, int> > poker;
	vector<string > input;
	int type[11];
	bool sameColor, straight;
	int weight;
	SimpleCardtype() {}
	SimpleCardtype(vector<pair<char, int> > &choose) {
		init(choose);
	}
	void init(vector<pair<char, int> > &choose) {
		swap(choose, poker);
		fill(type, type + 11, 0);
		sort(poker.begin(), poker.end(), cmp);
		vector<pair<int, int> > tmp;
		for (int i = 0; i <= 13; i++) tmp.push_back({ 0, i });
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
		weight = judge_cardtype()*k + val;
	}
};


/*int write_data(char* buffer, size_t size, size_t nmemb, void* userp)//回调函数
{
	std::string * str = dynamic_cast<std::string *>((std::string *)userp);
	str->append((char *)buffer, size * nmemb);
	return nmemb;
}

void sign_in()
{

}

void open(string token,string* response)
{
	curl_global_init(CURL_GLOBAL_ALL);
	CURL* curl;
	struct curl_slist *headers = NULL;
	token = "X-Auth-Token:" + token;
	headers = curl_slist_append(headers,token.c_str());
	curl = curl_easy_init();
	if (!curl)
	{
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);//请求头
		curl_easy_setopt(curl, CURLOPT_URL, "http://api.revth.com/game/open");//URL
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);//回调函数
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)response);//错误信息
		int status_code = curl_easy_perform(curl);   // 执行
	}
}*/



