#include "Datanum.h"

USING_NS_CC;


bool Datanum::init()
{
	if (!Sprite::init())
		return false;

	return true;
}

void Datanum::initDatanum(std::string name, int no,int x,int y)
{
	this->initWithFile(name);
	this->no = no;
	this->x = x;
	this->y = y;
}
