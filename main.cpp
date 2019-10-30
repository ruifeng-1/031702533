#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<sstream>
#include <Windows.h>
#include"cardtype.h"
#include"Enume.h"
#include"HttpConn.h"
#include"json/json.h"
#include"dataGet.h"
using namespace std;

map<int, string> status;

class User {
public:
	int user_id;
	string token;
	bool logined;
	User() {
		logined = false;
	}
};

class Menu {
public:
	HttpConn http;
	DataGet dt;
	User user;
	Enume enume;
	Menu() {
		http.host = "http://api.revth.com";
		status[0] = "�ɹ�";
		status[1] = "�������޻�Ӧ";
		status[1001] = "�û����ѱ�ʹ��";
		status[1002] = "ѧ���Ѱ�";
		status[1003] = "������֤ʧ��";
		status[1004] = "Token����";
		status[1005] = "�û������������";
		status[2001] = "δ����ս�ֹ���";
		status[2002] = "��ǧ������";
		status[2003] = "���Ϸ�����";
		status[2004] = "ս�ֲ����ڻ��ѽ���";
		status[2005] = "��ʽ����";
		status[2006] = "��ʱ";
		status[3001] = "ս�ֲ����ڻ�δ����";
		status[3002] = "��Ҳ�����";
		status[5000] = "�뿴���屨��������Ǵ����������";
	}
	void showRank() {
		Json::Reader reader;
		Json::Value input;
		int re = http.ope("/rank", "rank", "GET", "", "");
		if (re) {
			cout << re << "�������޻�Ӧ"<< endl;
			return;
		}
		reader.parse(dt.getRank(), input);
		cout << "            ���id           ����            �ǳ�    " << endl;
		for (int i = 0; i < input.size(); i++) {
			printf("%16d %16d %16s\n", input[i]["player_id"].asInt(), input[i]["score"].asInt(), input[i]["name"].asCString());
		}
	}
	Json::Value login(const string& username, const string& password) {
		Json::Value post;
		post["username"] = username;
		post["password"] = password;
		int re = http.ope("/auth/login", "status", "POST", "Content-Type: application/json\r\n", post.toStyledString());
		if (re) {
			cout << re;
			post["status"] = 1;
			return post;
		}
		Json::Value ret;
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value reg(const string& username, const string& password) {
		Json::Value post;
		post["username"] = username;
		post["password"] = password;
		int re = http.ope("/auth/register", "status", "POST", "Content-Type: application/json\r\n", post.toStyledString());
		if (re) {
			cout << re;
			post["status"] = 1;
			return post;
		}
		Json::Value ret;
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value regAndBind(const string& username, const string& password, const string& student_number, const string& student_password) {
		Json::Value post;
		post["username"] = username;
		post["password"] = password;
		post["student_number"] = student_number;
		post["student_password"] = student_password;
		int re = http.ope("/auth/register2", "status", "POST", "Content-Type: application/json\r\n", post.toStyledString());
		if (re) {
			cout << re;
			post["status"] = 1;
			return post;
		}
		Json::Value ret;
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value logout() {
		Json::Value ret;
		int re = http.ope("/auth/logout", "status", "POST", "X-Auth-Token: \"" + user.token + "\"\r\n", "");
		if (re) {
			cout << re;
			ret["status"] = 1;
			return ret;
		}
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value bind(const string& student_number, const string& student_password) {
		Json::Value post;
		post["student_number"] = student_number;
		post["student_password"] = student_password;
		int re = http.ope("/auth/bind", "status", "POST", "X-Auth-Token: \"" + user.token + "\",Content-Type: application/json\r\n", post.toStyledString());
		if (re) {
			cout << re;
			post["status"] = 1;
			return post;
		}
		Json::Value ret;
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value start() {
		Json::Value ret;
		int re = http.ope("/game/open", "status", "POST", "X-Auth-Token: " + user.token + "\r\n", "");
		if (re) {
			cout << re;
			ret["status"] = 1;
			return ret;
		}
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value submit(const Json::Value& post) {
		Json::Value ret;
		int re = http.ope("/game/submit", "status", "POST", "X-Auth-Token: " + user.token + ",Content-Type: application/json\r\n", post.toStyledString());
		if (re) {
			cout << re;
			ret["status"] = 1;
			return ret;
		}
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value history(const int& limit, const int& page) {
		Json::Value post;
		post["player_id"] = user.user_id;
		post["limit"] = limit;
		post["page"] = page;
		int re = http.ope("/history", "status", "GET", "X-Auth-Token: \"" + user.token + "\"\r\n", post.toStyledString());
		if (re) {
			cout << re;
			post["status"] = 1;
			return post;
		}
		Json::Value ret;
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	Json::Value historyDetail(const string& id) {
		Json::Value post;
		int re = http.ope("/history/" + id, "status", "GET", "X-Auth-Token: " + user.token + "\r\n", post.toStyledString());
		if (re) {
			cout << re;
			post["status"] = 1;
			return post;
		}
		Json::Value ret;
		Json::Reader reader;
		reader.parse(dt.getStatus(), ret);
		return ret;
	}
	void showLogin() {
		cout << "1. ע��" << endl;
		cout << "2. ע�Ტ��ѧ��" << endl;
		cout << "3. ��¼" << endl;
		cout << "0. �˳�" << endl;
		cout << "������������:";
	}
	void loginMenu() {
		system("cls");
		showLogin();
		Json::FastWriter writer;
		int opt;
		string _a, _b, _c, _d;
		Json::Value res;
		cin >> opt;
		system("cls");
		switch (opt)
		{
		case 0:
			exit(0);
			break;
		case 1:
			cout << "������ע���˺�:";
			cin >> _a;
			cout << "����������:";
			cin >> _b;
			res = reg(_a, _b);
			cout << status[res["status"].asInt()] << endl;
			break;
		case 2:
			cout << "������ע���˺�:";
			cin >> _a;
			cout << "����������:";
			cin >> _b;
			cout << "������ѧ��:";
			cin >> _c;
			cout << "����������:";
			cin >> _d;
			res = regAndBind(_a, _b, _c, _d);
			cout << status[res["status"].asInt()] << endl;
			break;
		case 3:
			cout << "�������˺�:";
			cin >> _a;
			cout << "����������:";
			cin >> _b;
			res = login(_a, _b);
			cout << status[res["status"].asInt()] << endl;
			if (res["status"].asInt() == 0) {
				user.user_id = res["data"]["user_id"].asInt();
				user.token = res["data"]["token"].asString();
				user.logined = true;
			}
			break;
		default:
			break;
		}
		system("pause");
	}
	void showMain() {
		cout << "�ҵ�token:" << user.token << endl;
		cout << "�ҵ�id:" << user.user_id << endl;
		cout << "1. ע��" << endl;
		cout << "2. ��" << endl;
		cout << "3. ����ս��" << endl;
		cout << "4. ���а�" << endl;
		cout << "5. ��ʷս��" << endl;
		cout << "6. ��ʷս������" << endl;
		cout << "0. �˳�" << endl;
		cout << "������������:";
	}
	vector<pair<char, int> > jsonToPoker(const Json::Value& jso) {
		vector<pair<char, int> > ret;
		ret.push_back({ '0', 0 });
		string card = jso["data"]["card"].asString();
		stringstream st;
		st << card;
		string cur;
		while (st >> cur) {
			int val;
			if (cur.size() == 3) val = 10;
			else if (cur[1] == 'J') val = 11;
			else if (cur[1] == 'Q') val = 12;
			else if (cur[1] == 'K') val = 13;
			else if (cur[1] == 'A') val = 14;
			else val = cur[1] - '0';
			ret.push_back({ cur[0], val });
		}
		return ret;
	}
	Json::Value pokerToJson(SimpleCardtype best[]) {
		Json::Value ret;
		for (int i = 1; i <= 3; i++) {
			string cur;
			for (int j = 0; j < best[i].poker.size(); j++) {
				if (j) cur.push_back(' ');
				cur.push_back(best[i].poker[j].first);
				if (best[i].poker[j].second == 10) cur += "10";
				else if (best[i].poker[j].second == 11) cur.push_back('J');
				else if (best[i].poker[j].second == 12) cur.push_back('Q');
				else if (best[i].poker[j].second == 13) cur.push_back('K');
				else if (best[i].poker[j].second == 14) cur.push_back('L');
				else cur.push_back(best[i].poker[j].second + '0');
			}
			ret["card"].append(cur);
		}
		return ret;
	}
	void mainMenu() {
		system("cls");
		showMain();
		int opt, tmpid, _ia, _ib;
		Json::FastWriter writer;
		Json::Value res;
		string _a, _b, _c, _d;
		vector<pair<char, int> > tmp;
		cin >> opt;
		system("cls");
		switch (opt)
		{
		case 0:
			exit(0);
			break;
		case 1:
			res = logout();
			cout << status[res["status"].asInt()] << endl;
			if (res["status"].asInt() == 0) user.logined = false;
			break;
		case 2:
			cout << "������ѧ��:";
			cin >> _a;
			cout << "����������:";
			cin >> _b;
			res = bind(_a, _b);
			cout << status[res["status"].asInt()] << endl;
			break;
		case 3:
			res = start();
			cout << status[res["status"].asInt()] << endl;
			tmpid = res["data"]["id"].asInt();
			cout << writer.write(res) << endl;
			tmp = jsonToPoker(res);
			enume.clear(tmp);
			res = pokerToJson(enume.best);
			res["id"] = tmpid;
			cout << writer.write(res) << endl;
			res = submit(res);
			break;
		case 4:
			showRank();
			break;
		case 5:
			cout << "ÿҳ��ʾ����:";
			cin >> _ia;
			cout << "�ڼ�ҳ:";
			cin >> _ib;
			res = history(_ia, _ib);
			cout << status[res["status"].asInt()] << endl;
			cout << "     ս��id    ǰ��      �ж�      ���      �÷�     ����ʱ��" << endl;
			cout << writer.write(res) << endl;
			break;
		case 6:
			cout << "����ս��id:";
			cin >> _a;
			res = historyDetail(_a);
			cout << status[res["status"].asInt()] << endl;
			cout << writer.write(res) << endl;
			break;
		default:
			break;
		}
		system("pause");
	}
};

int main() {
	Menu menu;
	while (true) {
		if (menu.user.logined) menu.mainMenu();
		else menu.loginMenu();
	}
	system("pause");
	return 0;
}
