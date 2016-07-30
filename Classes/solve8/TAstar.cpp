#include "TAstar.h"
#include <string>
using namespace std;

int TAstar::s[Num];
int TAstar::e[Num*Num];
vector<int> TAstar::rs;

//0 1 2 1 2 3 2 3 4
//1 0 1 2 1 2 3 2 3
//2 1 0 3 2 1 4 3 2
//1 2 3 0 1 2 1 2 3
//2 1 2 1 0 1 2 1 2
//3 2 1 2 1 0 3 2 1
//2 3 4 1 2 3 0 1 2
//3 2 3 2 1 2 1 0 1
//4 3 2 3 2 1 2 1 0

TAstar::TAstar(string inits, string finals) :TEight(inits, finals)
{
	for (int i = 0; i<Num;)
	{
		r[p[i]] = i;   //�洢��ʼ״̬�������ֵ�λ��   
		s[q[i]] = i; //�洢Ŀ��״̬�������ֵ�λ��   
		i++;
	}
	f = g = h = 0;       //���ۺ�����ʼֵ   

	int tmp[Num][Num]= {
		{ 0, 1, 2, 1, 2, 3, 2, 3, 4 },
		{ 1, 0, 1, 2, 1, 2, 3, 2, 3 },
		{ 2, 1, 0, 3, 2, 1, 4, 3, 2 },
		{ 1, 2, 3, 0, 1, 2, 1, 2, 3 },
		{ 2, 1, 2, 1, 0, 1, 2, 1, 2 },
		{ 3, 2, 1, 2, 1, 0, 3, 2, 1 },
		{ 2, 3, 4, 1, 2, 3, 0, 1, 2 },
		{ 3, 2, 3, 2, 1, 2, 1, 0, 1 },
		{ 4, 3, 2, 3, 2, 1, 2, 1, 0 }

	};
	int cnt = 0;
	for (int i = 0; i < Num;i++)
	for (int j = 0; j < Num; j++)
		e[cnt++] = tmp[i][j];
}

void TAstar::Printl(TList<TAstar> L)
{
	TAstar T = *this;
	if (T.last == -1)
		return;
	else
	{
		T = L.GetData(T.last);
		T.Printl(L);
		//T.Printf();
		//printf("%d\n", T.getZeroPos());
		this->rs.push_back(T.getZeroPos());
	}
}

int TAstar::Expend(int i)
{
	if (Extend(i))   //������չ   
	{
		int temp = r[p[r[0]]];   //�ı�״̬������λ�ñ仯���洢�ı���λ��    
		r[p[r[0]]] = r[0];
		r[0] = temp;
		return 1;
	}
	return 0;
}

int TAstar::Calcuf()
{
	h = 0;
	for (int i = 0; i<Num; i++)  //������ۺ�����h   
		h += e[Num*r[i] + s[i]];
	return ++g + h;
}

void TAstar::Sort(TList<TAstar>& L, int k)
{
	int n = L.Getlen();
	int i;
	for (i = k + 1; i<n; i++)
	{
		TAstar T = L.GetData(i);
		if (this->f <= T.f)
			break;
	}
	L.Insert(*this, i);
}

int TAstar::Repeat(TList<TAstar> &L)
{
	int n = L.Getlen();
	int i;
	for (i = 0; i<n; i++)
	if (L.GetData(i) == *this)
		break;
	return i;
}

void TAstar::Search()
{
	TAstar T = *this;              //��ʼ���   
	T.f = T.Calcuf();               //��ʼ���Ĺ��ۺ���   
	TList<TAstar> L;           //��������   
	L.Append(T);                 //��ʼ������   
	int head = 0, tail = 0;           //����ͷ��βָ��   
	while (head <= tail)           //���в�����ѭ��   
	{
		for (int i = 0; i<4; i++)            //�ո�����ƶ�����   
		{
			T = L.GetData(head);   //ȥ����ͷ���   
			if (T.h == 0)                   //��Ŀ����   
			{
				T.Printl(L);//�������·��   
				//T.Printf();    //���Ŀ��״̬   
				//printf("%d\n", T.getZeroPos());
				this->rs.push_back(T.getZeroPos());
				return;        //����   
			}
			if (T.Expend(i))          //��������չ   
			{
				int k = T.Repeat(L); //����������չ����ظ������        
				if (k<head)               //����ǲ�����չ�Ľ��   
					continue; //����   
				T.last = head;      //���ǲ�����չ�Ľ�㣬��¼�����   
				T.f = T.Calcuf(); //����f   
				if (k <= tail)         //�½�������չ����ظ�   
				{
					TAstar Temp = L.GetData(k);
					if (Temp.g>T.g)         //�Ƚ������gֵ   
						L.SetData(T, k); //����gֵС��   
					continue;
				}
				T.Sort(L, head);            //�½��������չ������        
				tail++;        //����βָ�����    
			}
		}
		head++; //һ����㲻������չ������ͷָ��ָ����һ���   
	}
}