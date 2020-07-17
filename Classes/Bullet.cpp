#include "Bullet.h"
#include "ManagerBase.h"

USING_NS_CC;
bool Bullet::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }

    auto VSize = Director::getInstance()->getVisibleSize();
    

    
    return true;
}
//----------------子弹帧调用---------------//
void Bullet::onEnterTransitionDidFinish()
{
	Sprite::onEnterTransitionDidFinish();
	scheduleUpdate();
}
void Bullet::onExit()
{
	unscheduleUpdate();
	Sprite::onExit();
}

//----------------子弹生成----------------//
void Bullet::initBullet(int index)
{
	auto VSize = Director::getInstance()->getVisibleSize();

	//子弹初始化
	auto spr_name = String::createWithFormat("Bullet%i.png", index);
	this->initWithFile(spr_name->getCString());
}

void Bullet::update(float dt)
{
	//让子弹飞
	this->setPositionX(this->getPositionX() + 5); 

	//移动到屏幕外移除
	if (this->getPositionX() > Director::getInstance()->getVisibleSize().width - 200)
	{
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_Bullet_list(this);
	}
}
