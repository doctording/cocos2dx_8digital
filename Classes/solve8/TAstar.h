#ifndef __TASTAR_H__
#define __TASTAR_H__

#include "Entity.h"
#include "TList.h"
#include <string>
#include <vector>

using namespace std;

class TAstar :public TEight
{
public:
	TAstar(){}                           //���캯��   
	TAstar(string inits,string finals);   //���������캯��    
	virtual void Search();               //A*������   
private:
	int f, g, h;                               //���ۺ���     
	int r[Num];                              //�洢״̬�и�������λ�õĸ�������   
	static int s[Num];                       //�洢Ŀ��״̬�и�������λ�õĸ�������   
	static int e[];                           //�洢����������Ծ���ĸ�������      
	void Printl(TList<TAstar> L);       //��Ա�������������·��    
	int Expend(int i);                        //��Ա������A*�㷨��״̬��չ����    
	int Calcuf();                             //��Ա������������ۺ���   
	void Sort(TList<TAstar>& L, int k);  //��Ա������������չ��㰴f��С����˳��������չ������   
	int Repeat(TList<TAstar> &L);       //��Ա������������Ƿ��ظ�  

public:
	static vector<int> rs;
};

#endif