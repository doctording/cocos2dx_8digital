#include "Manager.h"

Manager * Manager::m_manager = NULL;

//在构造函数的初始化列表中初始化数组
Manager::Manager() : m_data()
{
}

Manager * Manager::getInstance()
{
	if (m_manager == NULL)
	{
		m_manager = new Manager();
	}

	return m_manager;
}

void Manager::freeInstance(void)
{
	if (m_manager != NULL)
	{
		delete m_manager;
		m_manager = NULL;
	}
}

Datanum* Manager::getZero()
{
	Vector<Datanum *> &vs = getDataVector();
	for (Datanum* sp: vs)
	{
		if (sp->no == 0)
			return sp;
	}
	return NULL;
}

Datanum* Manager::getZeroLeft(Datanum * spZero)
{
	int x = spZero->x;
	int y = spZero->y - 1;
	Vector<Datanum *> &vs = getDataVector();
	for (Datanum* sp : vs)
	{
		if (sp->x == x && sp->y == y)
			return sp;
	}
	return NULL;
}

Datanum* Manager::getZeroRight(Datanum * spZero)
{
	int x = spZero->x;
	int y = spZero->y + 1;
	Vector<Datanum *> &vs = getDataVector();
	for (Datanum* sp : vs)
	{
		if (sp->x == x && sp->y == y)
			return sp;
	}
	return NULL;
}

Datanum* Manager::getZeroUp(Datanum * spZero)
{
	int x = spZero->x-1;
	int y = spZero->y;
	Vector<Datanum *> &vs = getDataVector();
	for (Datanum* sp : vs)
	{
		if (sp->x == x && sp->y == y)
			return sp;
	}
	return NULL;
}

Datanum* Manager::getZeroDown(Datanum * spZero)
{
	int x = spZero->x+1;
	int y = spZero->y;
	Vector<Datanum *> &vs = getDataVector();
	for (Datanum* sp : vs)
	{
		if (sp->x == x && sp->y == y)
			return sp;
	}
	return NULL;
}

std::string Manager::getStr()
{
	std::string str;
	int num[3][3];
	Vector<Datanum *> &vs = getDataVector();
	for (Datanum* sp : vs)
	{
		num[sp->x][sp->y] = sp->no;
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			str += (num[i][j] + '0');
		}
	}
	return str;

}