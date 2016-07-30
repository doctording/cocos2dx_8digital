#include "Entity.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

int TEight::q[Num];
int TEight::d[] = { 1, 3, -1, -3 }; //�� �� �� �ϣ� spac+d[i] Ϊ�ո��ƶ���λ��
int TEight::total = 0;

TEight::TEight(string inits, string finals)
{
	for (int i = 0; i < Num; i++)
	{
		p[i] = inits[i] - '0';
		if (inits[i] == '0')
			spac = i;

		q[i] = finals[i]-'0';
	}
	last = -1;
}

bool TEight::operator==(const TEight &T)
{
	for (int i = 0; i<Num;)
	if (T.p[i] != p[i++])
		return 0;
	return 1;
}

// ���ݷ�����չ����һ���ڵ�
bool TEight::Extend(int i)
{
	//�ո��޷�����ָ���ķ����ƶ�
	if ((i == 0 && spac % 3 == 2)
		|| (i == 1 && spac > 5)
		|| (i == 2 && spac % 3 == 0)
		|| (i == 3 && spac < 3)
		)
		return 0;

	int temp = spac;
	spac += d[i]; //�ı�ո�
	// �����ո���Ҫ�ƶ�λ�õ�����
	p[temp] = p[spac];
	p[spac] = 0;
	return 1;
}

void TEight::Printf()
{
	/*ofstream fout;
	fout.open("Eight_result.txt", ios::ate | ios::app);
	fout << total++ << "t";
	for (int i = 0; i<Num;)
		fout << "  " << p[i++];
	fout << endl;
	fout.close();*/

	cout << total++ << "t";
	for (int i = 0; i<Num;)
		cout << "  " << p[i++];
	cout << endl;
}

int TEight::getZeroPos()
{
	/*ofstream fout;
	fout.open("Eight_result.txt", ios::ate | ios::app);
	fout << total++ << "t";
	for (int i = 0; i<Num;)
	fout << "  " << p[i++];
	fout << endl;
	fout.close();*/

	for (int i = 0; i < Num;)
	{
		if (p[i] == 0)
			return i;
		i++;
	}
	return -1;
}