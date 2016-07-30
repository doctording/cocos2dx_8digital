#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Datanum.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // �رղ˵�
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

public:
	Point getPos(int x, int y, float cw, float ch);

	void onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
	void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);

	void change(Datanum* sp1, Datanum* sp2);

	std::string inits;//��ʼ״̬
	std::string finals;//���յ�״̬

	void Move(float dt);

	std::vector<int> dirs; // �����㷨��� ���εķ���

	// Astar�˵�
	void menuAstarCallback(cocos2d::Ref* pSender);

	int scoreTime;
	LabelTTF *label;
	void timeSchedule(float dt);
};

#endif // __HELLOWORLD_SCENE_H__