#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <string>
using namespace std;

const int Num = 9;

class TEight
{
public:
	TEight(){}
	TEight(string inits,string finals);
	virtual void Search() = 0;
protected:
	int p[Num];
	int last, spac;
	static int q[Num], d[], total;
	void Printf();
	bool operator==(const TEight &T);
	bool Extend(int i);
public:
	int getZeroPos();
};

#endif