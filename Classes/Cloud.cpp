#include "Cloud.h"

USING_NS_CC;

bool Cloud::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	//每帧调用，判断云的位置
	scheduleUpdate();
    
    return true;
}

void Cloud::initCloud(int name_index)
{
	auto VSize = Director::getInstance()->getVisibleSize();

	//云朵生成
	String* name_str = String::createWithFormat("cloud%d.png", name_index);
	this->initWithFile(name_str->getCString());

	//设置云层的随机位置
	Point cloud = ccp(VSize.width + random(2,5) * 60, 600 + random(2,8) * 10);
	
	this->setPosition(cloud);
}

void Cloud::update(float dt)
{
	//云朵运动
	auto point = this->getPositionX() -  3;
	this->setPositionX(point);

	//云朵移动到屏幕外移除
	if (point < -this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
	}
}
