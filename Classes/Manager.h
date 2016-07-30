#include "cocos2d.h"
#include "Datanum.h"

USING_NS_CC;

class  Manager
{
public:
    
	static Manager * getInstance();
	static void Manager::freeInstance(void);

public:
	static Manager * m_manager;
	Manager();
	bool init();

public:
	Vector<Datanum *> m_data;
	Vector<Datanum *> & getDataVector(){ return m_data; };

public:
	Datanum* getZero();
	Datanum* getZeroLeft(Datanum *spZero);
	Datanum* getZeroRight(Datanum *spZero);
	Datanum* getZeroUp(Datanum *spZero);
	Datanum* getZeroDown(Datanum *spZero);

	std::string getStr();
};