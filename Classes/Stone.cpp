#include "Stone.h"
#include "ManagerBase.h"

USING_NS_CC;

bool Stone::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	scheduleUpdate();
    return true;
}

void Stone::initStone()
{
	auto VSize = Director::getInstance()->getVisibleSize();
	//石头生成
	String* name_str = String::create("Stone.png");
	this->initWithFile(name_str->getCString());

	//设置石头的随机位置
	Point Tree = ccp(VSize.width + random(2, 3) * 150, 220);
	this->setPosition(Tree);
}

void Stone::update(float dt)
{
	auto point = this->getPositionX() - 4;
	this->setPositionX(point);

	//移动到屏幕外移除
	if (point < -this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_Stone_list(this);
	}
}
