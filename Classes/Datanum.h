#ifndef __DATA_H__
#define __DATA_H__

#include "cocos2d.h"

USING_NS_CC;

class  Datanum : public Sprite
{
public:

	Datanum(void){}
	~Datanum(void){}

public:

	virtual bool init();
	CREATE_FUNC(Datanum);
	
public:
	
	void initDatanum(std::string name, int no, int x, int y);
	int no;
	int x, y;
};

#endif
