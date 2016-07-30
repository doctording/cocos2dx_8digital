#include "HelloWorldScene.h"
#include "Manager.h"
#include "solve8\TAstar.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
#if 0
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
#endif 
	
	//菜单
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto astarItem = MenuItemImage::create(
		"astar.png",
		"astar.png",
		CC_CALLBACK_1(HelloWorld::menuAstarCallback, this));

	astarItem->setPosition(Point(origin.x + visibleSize.width - astarItem->getContentSize().width,
		origin.y + visibleSize.height/2 + astarItem->getContentSize().height));

	// 创建菜单，添加菜单项
	auto menu = Menu::create(closeItem,astarItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 2);


	//inits = "203184765";
	//finals = "123804765";

	inits = "012345678";
	finals = "123456780";

	int num[3][3];
	int final_num[3][3];
	for (int i = 0; i < 9; i++)
	{
		num[i / 3][i % 3] = inits[i] - '0';
		final_num[i / 3][i % 3] = finals[i] - '0';
	}
	//初态
	/*int num[3][3] = {
		{2,0,3},
		{1,8,4},
		{7,6,5}
	};*/
	//终态
	/*int final_num[3][3] = {
		{ 1, 2, 3 },
		{ 8, 0, 4 },
		{ 7, 6, 5 }
	};*/

	auto sprite = Sprite::create("0.png");
	//sprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	//this->addChild(sprite, 0);

	float cw = sprite->getContentSize().width;
	float ch = sprite->getContentSize().height;

	auto & vs = Manager::getInstance()->getDataVector();

	// 最终的图形
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto frameName = __String::createWithFormat("small\\%d.png", final_num[i][j]);
			//将传入的字符串和frameName拼接起来，str是最后使用的spriteframe的名字
			std::string picPath = frameName->getCString();

			auto sp = Sprite::create(picPath);
			float x = visibleSize.width/10 + j * 30;
			float y = visibleSize.width/2 + (1- i) * 30;
			sp->setPosition(Point(x,y));
			this->addChild(sp,2);
		}
	}
	//操作帮助图
	auto spHelp = Sprite::create("help2.png");
	float x = visibleSize.width / 10 + 30;
	float y = visibleSize.height / 2 - spHelp->getContentSize().height *0.3;
	spHelp->setPosition(Point(x, y));
	this->addChild(spHelp, 2);

	//初始图片
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			auto frameName = __String::createWithFormat("%d.png", num[i][j]);
			//将传入的字符串和frameName拼接起来，str是最后使用的spriteframe的名字
			std::string picPath = frameName->getCString();

			Datanum* s2 = Datanum::create();
			s2->initDatanum(picPath, num[i][j], i, j);
			s2->setPosition(this->getPos(i, j, cw, ch));
			this->addChild(s2, 0);
			vs.pushBack(s2);
		}
	}

	//键盘监听器
	auto listenerKeyPad = EventListenerKeyboard::create();
	listenerKeyPad->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listenerKeyPad->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyPad, this);

	//时间板
	scoreTime = 0;
	auto timeStr = __String::createWithFormat("used/s:%d", scoreTime);
	label = LabelTTF::create(timeStr->getCString(), "Arial", 24);
	label->setPosition(Point(400, 30));
	this->addChild(label, 1);
	//this->schedule(schedule_selector(HelloWorld::timeSchedule), 1.0f);//每隔1.0f执行一次，省略参数则表示每帧都要执行 

    return true;
}

void HelloWorld::timeSchedule(float dt)
{
	scoreTime ++;
	auto timeStr = __String::createWithFormat("used/s:%d", scoreTime);
	label->setString(timeStr->getCString());
}

void HelloWorld::Move(float dt)
{
	int len = dirs.size();
	static int i=0;

	if (i >= len)
	{
		this->unschedule(schedule_selector(HelloWorld::Move));
		MessageBox("ok", "ok");
		return;
	}
	int dir = dirs[i];
	if (dir == 1){
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spRight = Manager::getInstance()->getZeroRight(spZero);

		if (spRight != NULL)
		{
			change(spZero, spRight);
		}
	}
	else if(dir == 3){
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spDown = Manager::getInstance()->getZeroDown(spZero);

		if (spDown != NULL)
		{
			change(spZero, spDown);
		}
	}
	else if (dir == -1)
	{
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spLeft = Manager::getInstance()->getZeroLeft(spZero);
		if (spLeft != NULL)
		{
			change(spZero, spLeft);
		}
	}
	else if(dir == -3)
	{
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spUp = Manager::getInstance()->getZeroUp(spZero);

		if (spUp != NULL)
		{
			change(spZero, spUp);
		}
	}else{
	}
	i++;
#if 0
	/*TAstar aStar("203184765", "123804765");
	aStar.Search();
	int len = aStar.rs.size();
	int tt;
	for (int i = 1; i < len; i++)
	{
		tt = aStar.rs[i] - aStar.rs[i - 1];
	}*/

	//LOG("baibai");
	int steps[3] = { 3, 2, 1 };
	static int st = 0;

	int dir = steps[st];

	if (dir == 1){
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spRight = Manager::getInstance()->getZeroRight(spZero);

		if (spRight != NULL)
		{
			change(spZero, spRight);
		}
	}
	else if(dir == 2){
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spDown = Manager::getInstance()->getZeroDown(spZero);

		if (spDown != NULL)
		{
			change(spZero, spDown);
		}
	}
	else if (dir == 3)
	{
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spLeft = Manager::getInstance()->getZeroLeft(spZero);
		if (spLeft != NULL)
		{
			change(spZero, spLeft);
		}
	}
	else if(dir == 4)
	{
		Datanum* spZero = Manager::getInstance()->getZero();
		Datanum* spUp = Manager::getInstance()->getZeroUp(spZero);

		if (spUp != NULL)
		{
			change(spZero, spUp);
		}
	}
	else{

	}


	st++;
	if (st == 3)
	{
		this->unschedule(schedule_selector(HelloWorld::Move));
		//MessageBox("you win", "GameOver");
	}
#endif
}


void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
	{
			Datanum* spZero = Manager::getInstance()->getZero();
			Datanum* spLeft = Manager::getInstance()->getZeroLeft(spZero);
			if (spLeft != NULL)
			{
				change(spZero, spLeft);
			}
	}
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
	{
			Datanum* spZero = Manager::getInstance()->getZero();
			Datanum* spRight = Manager::getInstance()->getZeroRight(spZero);

			if (spRight != NULL)
			{
				change(spZero, spRight);
			}
	}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
	{
			Datanum* spZero = Manager::getInstance()->getZero();
			Datanum* spUp = Manager::getInstance()->getZeroUp(spZero);

			if (spUp != NULL)
			{
				change(spZero, spUp);
			}
	}
		break;
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
	{
			Datanum* spZero = Manager::getInstance()->getZero();
			Datanum* spDown = Manager::getInstance()->getZeroDown(spZero);

			if (spDown != NULL)
			{
				change(spZero, spDown);
			}
	}
		break;
	}
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
	// 检测是否已经完成了拼图
	std::string str = Manager::getInstance()->getStr();
	if (str == finals)
	{
		MessageBox("you win", "GameOver");
	}

}

void HelloWorld::change(Datanum* sp1, Datanum* sp2)
{
	auto frameName1 = __String::createWithFormat("%d.png", sp2->no);
	std::string picPath1 = frameName1->getCString();

	Datanum* s1 = Datanum::create();
	s1->initDatanum(picPath1, sp2->no, sp1->x, sp1->y);
	s1->setPosition(this->getPos(s1->x, s1->y, 89, 89));

	auto frameName2 = __String::createWithFormat("%d.png", sp1->no);
	std::string picPath2 = frameName2->getCString();

	Datanum* s2 = Datanum::create();
	s2->initDatanum(picPath2, sp1->no, sp2->x, sp2->y);
	s2->setPosition(this->getPos(s2->x, s2->y, 89, 89));

	sp1->removeFromParentAndCleanup(true);
	sp2->removeFromParentAndCleanup(true);
	Manager::getInstance()->getDataVector().erase(Manager::getInstance()->getDataVector().find(sp1));
	Manager::getInstance()->getDataVector().erase(Manager::getInstance()->getDataVector().find(sp2));


	auto & vs = Manager::getInstance()->getDataVector();
	vs.pushBack(s1);
	vs.pushBack(s2);

	this->addChild(s1);
	this->addChild(s2);
}

Point HelloWorld::getPos(int i, int j, float cw, float ch)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	int px = (j - 1)*cw;
	int py = (1 - i)*ch;
	return Point(px + visibleSize.width / 2 + origin.x, py + visibleSize.height / 2 + origin.y);
}

/* 关闭菜单 */
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

/* Astar菜单 */
void HelloWorld::menuAstarCallback(Ref* pSender)
{
	// 判断是否有解
	// TODO

	// 求解
	TAstar aStar(inits, finals);
	aStar.Search();
	int len = aStar.rs.size();
	for (int i = 1; i < len; i++)
	{
		dirs.push_back(aStar.rs[i] - aStar.rs[i - 1]); // -1 1 -3 3
	}

	// 开始自己移动
	MessageBox("please watch the moves", "confirm to start");

	// 开启定时器，让程序自动运行
	this->schedule(schedule_selector(HelloWorld::Move), 1.0f);//每隔1.0f执行一次，省略参数则表示每帧都要执行 
}