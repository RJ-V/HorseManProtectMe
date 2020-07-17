#include "Cloud.h"

USING_NS_CC;

bool Cloud::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	//ÿ֡���ã��ж��Ƶ�λ��
	scheduleUpdate();
    
    return true;
}

void Cloud::initCloud(int name_index)
{
	auto VSize = Director::getInstance()->getVisibleSize();

	//�ƶ�����
	String* name_str = String::createWithFormat("cloud%d.png", name_index);
	this->initWithFile(name_str->getCString());

	//�����Ʋ�����λ��
	Point cloud = ccp(VSize.width + random(2,5) * 60, 600 + random(2,8) * 10);
	
	this->setPosition(cloud);
}

void Cloud::update(float dt)
{
	//�ƶ��˶�
	auto point = this->getPositionX() -  3;
	this->setPositionX(point);

	//�ƶ��ƶ�����Ļ���Ƴ�
	if (point < -this->getContentSize().width)
	{
		this->removeFromParentAndCleanup(true);
	}
}
