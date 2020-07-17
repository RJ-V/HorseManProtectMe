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
//----------------�ӵ�֡����---------------//
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

//----------------�ӵ�����----------------//
void Bullet::initBullet(int index)
{
	auto VSize = Director::getInstance()->getVisibleSize();

	//�ӵ���ʼ��
	auto spr_name = String::createWithFormat("Bullet%i.png", index);
	this->initWithFile(spr_name->getCString());
}

void Bullet::update(float dt)
{
	//���ӵ���
	this->setPositionX(this->getPositionX() + 5); 

	//�ƶ�����Ļ���Ƴ�
	if (this->getPositionX() > Director::getInstance()->getVisibleSize().width - 200)
	{
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_Bullet_list(this);
	}
}
