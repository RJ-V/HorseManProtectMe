#include "GameScene.h"

#include "Cloud.h"
#include "Stone.h"
#include "Dog.h"
#include "Bullet.h"

#include "ManagerBase.h"

#include "HelloWorld.h"
#include "GameOver.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto VSize = Director::getInstance()->getVisibleSize();

	Running = false;

	//scheduleUpdate();
	
	//���屳��ͼ
	spr_bg1 = Sprite::create("background1.png");
	spr_bg1->setAnchorPoint(Vec2(0, 0));
	spr_bg1->setPosition(Vec2(0, 0));
	this->addChild(spr_bg1);

	spr_bg2 = Sprite::create("background2.png");
	spr_bg2->setAnchorPoint(Vec2(0, 0));
	spr_bg2->setPosition(Vec2(spr_bg1->getContentSize().width - 2, 0));
	this->addChild(spr_bg2);

	spr_bg3 = Sprite::create("background3.png");
	spr_bg3->setAnchorPoint(Vec2(0, 0));
	spr_bg3->setPosition(Vec2(spr_bg1->getContentSize().width - 2 + spr_bg2->getContentSize().width - 2, 0));
	this->addChild(spr_bg3);

	Jump_Button = Sprite::create("JumpButton.png");
	Jump_Button->setScale(0.7);
	auto JumpItem = MenuItemSprite::create(Jump_Button, Jump_Button, CC_CALLBACK_0(GameScene::Hourse_Jump, this));
	JumpItem->setAnchorPoint(Vec2(0.5, 0.5));
	JumpItem->setPosition(Vec2(170, 120));

	Fire_Button = Sprite::create("FireButton.png");
	Fire_Button->setScale(0.7);
	auto FireItem = MenuItemSprite::create(Fire_Button, Fire_Button, CC_CALLBACK_0(GameScene::Hourse_Fire, this));
	FireItem->setAnchorPoint(Vec2(0.5, 0.5));
	FireItem->setPosition(1150, 120);

	auto menu = Menu::create(JumpItem, FireItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);

	//Ұ���˴���
	HourseHero = Sprite::create();
	HourseHero->setPosition(Vec2(200, 270));
	this->addChild(HourseHero, 2);
	init_hourse();

	//����
	label_score_num_ = Label::create();
	label_score_num_->setSystemFontSize(30);
	label_score_num_->setAnchorPoint(Vec2(0, 0.5));
	label_score_num_->setColor(Color3B(0, 0, 0));
	label_score_num_->setPosition(Vec2(1150, 680));
	this->addChild(label_score_num_, 3);

	//��߷�
	auto label_best_score = Label::create("HIGH","fonts/arial.ttf",40);
	label_best_score->setAnchorPoint(Vec2(0.5, 0.5));
	label_best_score->setColor(Color3B(0, 0, 0));
	label_best_score->setPosition(Vec2(100, 680));
	this->addChild(label_best_score,3);

	label_best_score_num_ = Label::create();
	label_best_score_num_->setString(String::createWithFormat("0")->getCString());
	label_best_score_num_->setSystemFontSize(30);
	label_best_score_num_->setAnchorPoint(Vec2(0, 0.5));
	label_best_score_num_->setColor(Color3B(0, 0, 0));
	label_best_score_num_->setPosition(Vec2(200, 680));
	this->addChild(label_best_score_num_,3);

	//��ǰ��߷�
	int score_win = UserDefault::getInstance()->getIntegerForKey("High");
	label_best_score_num_->setString(String::createWithFormat("%d", score_win)->getCString());

    return true;
}

//----------------֡����-------------//
void GameScene::update(float dt)
{
	//ʵ�ֱ�������		����СС��ɻ��ķ���
	//���嵥�������������ƶ��ı仯ֵ
	float x1 = spr_bg1->getPositionX() - 4;
	float x2 = spr_bg2->getPositionX() - 4;
	float x3 = spr_bg3->getPositionX() - 4;

	spr_bg1->setPositionX(x1);
	spr_bg2->setPositionX(x2);
	spr_bg3->setPositionX(x3);
	
	//�жϱ���ͼ		�����ű���ͼ�����໥����
	if (x1 < -spr_bg1->getContentSize().width)
		spr_bg1->setPositionX(spr_bg2->getPositionX() + spr_bg2->getContentSize().width - 2);
	else if (x2 < -spr_bg2->getContentSize().width)
		spr_bg2->setPositionX(spr_bg3->getPositionX() + spr_bg3->getContentSize().width - 2);
	else if (x3 < -spr_bg3->getContentSize().width)
		spr_bg3->setPositionX(spr_bg1->getPositionX() + spr_bg1->getContentSize().width - 2);

	if (Running)//�л�����
	{
		HourseHero->stopAction(HourseRun);
	}

}
void GameScene::updateOnce(float dt)
{
	Running = false;
	init_hourse();
}
void GameScene::onEnterTransitionDidFinish()
{
	Scene::onEnterTransitionDidFinish();
	scheduleUpdate();
	//�ƶ�����
	this->schedule(SEL_SCHEDULE(&GameScene::add_cloud), 4.0f);
	//ʯͷ����
	this->schedule(SEL_SCHEDULE(&GameScene::add_stone), 3.0f);
	//��������
	this->schedule(SEL_SCHEDULE(&GameScene::add_dog), 4.0f);
	//��ײ���
	this->schedule(SEL_SCHEDULE(&GameScene::is_Crash));
	//��������
	this->schedule(SEL_SCHEDULE(&GameScene::add_score),0.3f);
}
void GameScene::onExit()
{
	unscheduleUpdate();
	Scene::onExit();
}

//------------------��ɫ����-------------//
void GameScene::init_hourse()
{
	if (!Running)
	{
		auto VSize = Director::getInstance()->getVisibleSize();
		//������ɫ
		auto spriteFrameCache = SpriteFrameCache::getInstance();
		spriteFrameCache->addSpriteFramesWithFile("HourseRun.plist");
		Vector<SpriteFrame*> spriteFrames;
		for (int i = 1; i < 5; i++)
		{
			auto str_name = String::createWithFormat("hourse%i.png", i);
			auto sprite = spriteFrameCache->getSpriteFrameByName(str_name->getCString());
			spriteFrames.pushBack(sprite);
		}
		auto animation = Animation::createWithSpriteFrames(spriteFrames);
		animation->setDelayPerUnit(0.2); //�����л��ٶ�
		animation->setLoops(-1);

		HourseRun = Animate::create(animation);//��·��������
		HourseHero->runAction(HourseRun);
	}
}
//-------------------��ť����------------------------//
void GameScene::Hourse_Jump()
{
	Running = true;

	auto spriteFrameCache = SpriteFrameCache::getInstance();
	spriteFrameCache->addSpriteFramesWithFile("HourseJump.plist");
	Vector<SpriteFrame*> spriteFrames;
	for (int i = 1; i < 6; i++)
	{
		auto str_name = String::createWithFormat("hoursejump%i.png", i);
		auto sprite = spriteFrameCache->getSpriteFrameByName(str_name->getCString());
		spriteFrames.pushBack(sprite);
	}
	auto animation = Animation::createWithSpriteFrames(spriteFrames);
	animation->setDelayPerUnit(0.2); //�����л��ٶ�
	animation->setLoops(1);//��Ծѭ����һ��

	auto jump1 = JumpTo::create(1, Vec2(200, 600), 1, 1);
	auto jump2 = JumpTo::create(1, Vec2(200, 265), 1, 1);
	
	HourseJump = Animate::create(animation);//��Ծ��������
	HourseHero->runAction(Spawn::create(HourseJump, Sequence::create(jump1, jump2, NULL), NULL));

	this->scheduleOnce(schedule_selector(GameScene::updateOnce), 2.1);
}

void GameScene::Hourse_Fire()
{
	int index = random(1, 2);//�������һ����
	auto bullet = Bullet::create(); //��������
	bullet->initBullet(index);//����ʵ����
	//���ö������Ұ���˵�����
	auto point = ccp(HourseHero->getPositionX() + 100, HourseHero->getPositionY());
	//����λ��
	bullet->setScale(0.5);
	bullet->setPosition(point);
	this->addChild(bullet, 2);

	ManagerBase::getInstance()->set_Bullet_list(bullet);
	SimpleAudioEngine::getInstance()->playEffect("biu.mp3");

	/*auto fire = Sprite::create("Fire1.png");
	fire->setPosition(HourseHero->getPositionX() + 100, HourseHero->getPositionY());
	this->addChild(fire, 2);

	fire->runAction(Sequence::create(DelayTime::create(0.5), RemoveSelf(), NULL));*/
}

//---------------------��Ӹ�������ϰ���----------------------//
void GameScene::add_cloud(float dt)
{
	//����ƶ�
	int cloud_x = random(1, 2);
	auto cloud = Cloud::create();
	cloud->initCloud(cloud_x);
	this->addChild(cloud);
}
void GameScene::add_stone(float dt)
{
	//���ʯͷ
	auto stone = Stone::create();
	stone->initStone();
	this->addChild(stone,2);
	//��ʯͷ�����������
	ManagerBase::getInstance()->set_Stone_list(stone);
}
void GameScene::add_dog(float dt)
{
	//��ӹ���
	auto dog = Dog::create();
	dog->initDog();
	dog->setScale(0.9);
	this->addChild(dog, 2);

	ManagerBase::getInstance()->set_Dog_list(dog);
}
void GameScene::add_score(float dt)
{
	score += 1;
	label_score_num_->setString(String::createWithFormat("%d", score)->getCString());
	//log("%d", score);
}

//---------------��ײ���-------------//
void GameScene::is_Crash(float dt)
{
	//��������������Ķ���,�����ײ
	auto & stone_list = ManagerBase::getInstance()->getStoneList();
	auto & bullet_list = ManagerBase::getInstance()->getBulletList();
	auto & dog_list = ManagerBase::getInstance()->getDogList();

	//�������������ײ�ж�
	for (int i = stone_list.size() - 1; i >= 0; --i)
	{//Ұ����ײʯͷ��
		auto stone = stone_list.at(i);

		auto stoneRect = stone->getBoundingBox();
		auto HourseRect = HourseHero->getBoundingBox(); //����Ұ���˵ľ��ο�

		if (HourseRect.intersectsRect(stoneRect)) //�ж�Ұ���˾����Ƿ���ʯͷ�ཻ
		{
			Game_Over(1);
		}
	}
	for (int i = dog_list.size() - 1; i > 0; --i)
	{//��ţ��������
		auto dog = dog_list.at(i);
		//�����ڿ��ܴ��������ٵĿն���ֱ������
		if(dog->get_hp() == NULL)
			continue;
		if (dog->get_hp() <= 0)//�����ٵĲ��ؼ��
			continue;
		
		//���ڶ�ȡ����Ȩ�޳�ͻ��dog-> �� 0x1���ж�, ��������Խ�����
		auto dogRect = dog->getBoundingBox();
		auto HourseRect = HourseHero->getBoundingBox(); //����Ұ���˵ľ��ο�
		if (HourseRect.intersectsRect(dogRect)) //�ж�Ұ���˾����Ƿ��빷���ཻ
		{
			Game_Over(2);
		}
	}
	for (int i = dog_list.size() - 1; i >= 0; --i)
	{//�ڰ׵����й���
		auto dog = dog_list.at(i);

		//�����ڿ��ܴ��������ٵĿն���ֱ������
		if (dog->get_hp() == NULL)
			continue;
		if (dog->get_hp() <= 0)//�����ٵĲ��ؼ��
			continue;

		//���ڶ�ȡ����Ȩ�޳�ͻ��dog-> �� 0x1���ж�, ��������Խ�����
		auto dogRect = dog->getBoundingBox();

		//�ӵ�����
		for (int j = bullet_list.size() - 1; j >= 0; --j)
		{
			auto bullet = bullet_list.at(j);
			if (dogRect.containsPoint(bullet->getPosition())) //�ж��ӵ��빷����ײ
			{
				dog->set_hp(dog->get_hp() - 1);
				//�ӵ�û��
				bullet->removeFromParentAndCleanup(true);
				ManagerBase::getInstance()->remove_Bullet_list(bullet);

				//�������� 
				//����������жϣ��ж�����Ϊdog->0xDDDDD������һֻ�������������޷������ٴ�����(�ѽ��)
				if (dog->get_hp() <= 0)
					dog->dog_death();
			}
		}
	}
}
//------------��Ϸ����----------------//
void GameScene::Game_Over(int num)
{
	UserDefault::getInstance()->setIntegerForKey("Now", score);
	//�洢��߷�
	int high_score = UserDefault::getInstance()->getIntegerForKey("High");
	if (score>high_score)
	{
		UserDefault::getInstance()->setIntegerForKey("High", score);
	}

	//��ͣ��ǰ��ʱ���Ͷ���
	this->unschedule(SEL_SCHEDULE(&GameScene::add_cloud));
	this->unschedule(SEL_SCHEDULE(&GameScene::add_stone));
	this->unschedule(SEL_SCHEDULE(&GameScene::add_dog));
	this->unschedule(SEL_SCHEDULE(&GameScene::is_Crash));
	this->unschedule(SEL_SCHEDULE(&GameScene::add_score));
	this->stopAllActions();

	//������ȫ��ֹͣ
	//Director::getInstance()->stopAnimation();

	if (num == 1)
		GameOver::SceneNum = num;
		
	if (num == 2)
		GameOver::SceneNum = num;

	ManagerBase::deleteInstance();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, GameOver::create()));
}
