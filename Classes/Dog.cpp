#include "Dog.h"
#include "ManagerBase.h"

USING_NS_CC;

bool Dog::init()
{
    if ( !Sprite::init() )
    {
        return false;
    }

	scheduleUpdate();

	dog_hp_ = 1;

	is_death = false;

    return true;
}

void Dog::initDog()//��������
{
	//��ʼ������Ѫ��
	dog_hp_ = 1;

	is_death = false;

	auto VSize = Director::getInstance()->getVisibleSize();

	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("Dog.plist");
	Vector<SpriteFrame*> spriteFrames;
	for (int i = 1; i < 3; i++)
	{
		auto str_name = String::createWithFormat("Dog%i.png", i);
		auto sprite = spriteFrameCache->getSpriteFrameByName(str_name->getCString());
		spriteFrames.pushBack(sprite);
	}
	auto animation = Animation::createWithSpriteFrames(spriteFrames);
	animation->setDelayPerUnit(0.2); //�����л��ٶ�
	animation->setLoops(-1);

	this->setPosition(Vec2(VSize.width + random(3, 8) * 100, 260));
	this->runAction(Animate::create(animation));
	//����������������޷���ֵ��GameScene�У���ʵ�ֲ��˾�����ײ���
}

void Dog::dog_death()
{
	is_death = true;

	this->stopAllActions();
	SimpleAudioEngine::getInstance()->playEffect("what.mp3");

	auto animation = Animation::create();
	for (int i = 1; i <= 2; ++i)
	{
		auto name_str = String::createWithFormat("DogDie%d.png", i);
		animation->addSpriteFrameWithFile(name_str->getCString());
	}
	animation->setDelayPerUnit(0.2f);
	animation->setLoops(1);

	this->runAction(Sequence::create(Animate::create(animation), RemoveSelf::create(),
		CallFunc::create(CC_CALLBACK_0(Dog::remove_dog, this)), NULL));
}

void Dog::remove_dog()
{
	this->removeFromParentAndCleanup(true);
	ManagerBase::getInstance()->remove_Dog_list(this);
}

void Dog::set_hp(int hp)
{
	dog_hp_ = hp;
}

void Dog::update(float dt)
{
	//����������ƶ�
	if (is_death)
		return;

	auto point = this->getPositionX() - 6;
	this->setPositionX(point);
	//�ƶ�����Ļ���Ƴ�
	if (this->getPositionX() < -Director::getInstance()->getVisibleSize().width - 1000)
	{
		this->removeFromParentAndCleanup(true);
		ManagerBase::getInstance()->remove_Dog_list(this);
	}
}
