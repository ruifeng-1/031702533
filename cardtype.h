#include<vector>
using namespace std;

#pragma once
class SimpleCardtype//��
{
private:
	int judge_cardtype();//�ж�����
	bool checkSameColor();//�ж�ͬ��
	bool checkStraight();//�ж�˳��
public:
	SimpleCardtype();
	SimpleCardtype(vector<pair<char, int> >& choose);
	vector<pair<char, int> > poker; // �ö��˿�
	int type[11];// �ö��˿��������
	bool sameColor, straight;// �Ƿ���ͬ����˳��
	int weight;// �ö�����
	void init(vector<pair<char, int> >& choose);//��ʼ��
};

bool cmp(const pair<char, int>& a, const pair<char, int>& b); //���������߼�
