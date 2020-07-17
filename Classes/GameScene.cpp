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
	
	//定义背景图
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

	//野马人创建
	HourseHero = Sprite::create();
	HourseHero->setPosition(Vec2(200, 270));
	this->addChild(HourseHero, 2);
	init_hourse();

	//分数
	label_score_num_ = Label::create();
	label_score_num_->setSystemFontSize(30);
	label_score_num_->setAnchorPoint(Vec2(0, 0.5));
	label_score_num_->setColor(Color3B(0, 0, 0));
	label_score_num_->setPosition(Vec2(1150, 680));
	this->addChild(label_score_num_, 3);

	//最高分
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

	//当前最高分
	int score_win = UserDefault::getInstance()->getIntegerForKey("High");
	label_best_score_num_->setString(String::createWithFormat("%d", score_win)->getCString());

    return true;
}

//----------------帧调用-------------//
void GameScene::update(float dt)
{
	//实现背景滚动		运用小小打飞机的方法
	//定义单个变量做背景移动的变化值
	float x1 = spr_bg1->getPositionX() - 4;
	float x2 = spr_bg2->getPositionX() - 4;
	float x3 = spr_bg3->getPositionX() - 4;

	spr_bg1->setPositionX(x1);
	spr_bg2->setPositionX(x2);
	spr_bg3->setPositionX(x3);
	
	//判断背景图		由三张背景图进行相互交换
	if (x1 < -spr_bg1->getContentSize().width)
		spr_bg1->setPositionX(spr_bg2->getPositionX() + spr_bg2->getContentSize().width - 2);
	else if (x2 < -spr_bg2->getContentSize().width)
		spr_bg2->setPositionX(spr_bg3->getPositionX() + spr_bg3->getContentSize().width - 2);
	else if (x3 < -spr_bg3->getContentSize().width)
		spr_bg3->setPositionX(spr_bg1->getPositionX() + spr_bg1->getContentSize().width - 2);

	if (Running)//切换动作
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
	//云朵生成
	this->schedule(SEL_SCHEDULE(&GameScene::add_cloud), 4.0f);
	//石头生成
	this->schedule(SEL_SCHEDULE(&GameScene::add_stone), 3.0f);
	//狗子生成
	this->schedule(SEL_SCHEDULE(&GameScene::add_dog), 4.0f);
	//碰撞检测
	this->schedule(SEL_SCHEDULE(&GameScene::is_Crash));
	//分数增加
	this->schedule(SEL_SCHEDULE(&GameScene::add_score),0.3f);
}
void GameScene::onExit()
{
	unscheduleUpdate();
	Scene::onExit();
}

//------------------角色创建-------------//
void GameScene::init_hourse()
{
	if (!Running)
	{
		auto VSize = Director::getInstance()->getVisibleSize();
		//建立角色
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
		animation->setDelayPerUnit(0.2); //动画切换速度
		animation->setLoops(-1);

		HourseRun = Animate::create(animation);//走路动画创建
		HourseHero->runAction(HourseRun);
	}
}
//-------------------按钮功能------------------------//
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
	animation->setDelayPerUnit(0.2); //动画切换速度
	animation->setLoops(1);//跳跃循环，一次

	auto jump1 = JumpTo::create(1, Vec2(200, 600), 1, 1);
	auto jump2 = JumpTo::create(1, Vec2(200, 265), 1, 1);
	
	HourseJump = Animate::create(animation);//跳跃动作创建
	HourseHero->runAction(Spawn::create(HourseJump, Sequence::create(jump1, jump2, NULL), NULL));

	this->scheduleOnce(schedule_selector(GameScene::updateOnce), 2.1);
}

void GameScene::Hourse_Fire()
{
	int index = random(1, 2);//随机生成一个数
	auto bullet = Bullet::create(); //创建对象
	bullet->initBullet(index);//对象实例化
	//设置对象相对野马人的坐标
	auto point = ccp(HourseHero->getPositionX() + 100, HourseHero->getPositionY());
	//设置位置
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

//---------------------添加附属物和障碍物----------------------//
void GameScene::add_cloud(float dt)
{
	//添加云朵
	int cloud_x = random(1, 2);
	auto cloud = Cloud::create();
	cloud->initCloud(cloud_x);
	this->addChild(cloud);
}
void GameScene::add_stone(float dt)
{
	//添加石头
	auto stone = Stone::create();
	stone->initStone();
	this->addChild(stone,2);
	//把石头放入管理器中
	ManagerBase::getInstance()->set_Stone_list(stone);
}
void GameScene::add_dog(float dt)
{
	//添加狗子
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

//---------------碰撞检测-------------//
void GameScene::is_Crash(float dt)
{
	//创建管理内数组的对象,检测碰撞
	auto & stone_list = ManagerBase::getInstance()->getStoneList();
	auto & bullet_list = ManagerBase::getInstance()->getBulletList();
	auto & dog_list = ManagerBase::getInstance()->getDogList();

	//遍历数组进行碰撞判断
	for (int i = stone_list.size() - 1; i >= 0; --i)
	{//野马人撞石头了
		auto stone = stone_list.at(i);

		auto stoneRect = stone->getBoundingBox();
		auto HourseRect = HourseHero->getBoundingBox(); //创建野马人的矩形框

		if (HourseRect.intersectsRect(stoneRect)) //判断野马人矩形是否与石头相交
		{
			Game_Over(1);
		}
	}
	for (int i = dog_list.size() - 1; i > 0; --i)
	{//蜗牛被狗吃了
		auto dog = dog_list.at(i);
		//容器内可能存在已销毁的空对象，直接跳过
		if(dog->get_hp() == NULL)
			continue;
		if (dog->get_hp() <= 0)//已销毁的不必检测
			continue;
		
		//存在读取访问权限冲突，dog-> 是 0x1。中断, 存在数组越界情况
		auto dogRect = dog->getBoundingBox();
		auto HourseRect = HourseHero->getBoundingBox(); //创建野马人的矩形框
		if (HourseRect.intersectsRect(dogRect)) //判断野马人矩形是否与狗子相交
		{
			Game_Over(2);
		}
	}
	for (int i = dog_list.size() - 1; i >= 0; --i)
	{//黑白弹打中狗子
		auto dog = dog_list.at(i);

		//容器内可能存在已销毁的空对象，直接跳过
		if (dog->get_hp() == NULL)
			continue;
		if (dog->get_hp() <= 0)//已销毁的不必检测
			continue;

		//存在读取访问权限冲突，dog-> 是 0x1。中断, 存在数组越界情况
		auto dogRect = dog->getBoundingBox();

		//子弹遍历
		for (int j = bullet_list.size() - 1; j >= 0; --j)
		{
			auto bullet = bullet_list.at(j);
			if (dogRect.containsPoint(bullet->getPosition())) //判断子弹与狗子相撞
			{
				dog->set_hp(dog->get_hp() - 1);
				//子弹没了
				bullet->removeFromParentAndCleanup(true);
				ManagerBase::getInstance()->remove_Bullet_list(bullet);

				//狗子死了 
				//会出现意外中断，中断问题为dog->0xDDDDD，可能一只狗吃了两发，无法进行再次消除(已解决)
				if (dog->get_hp() <= 0)
					dog->dog_death();
			}
		}
	}
}
//------------游戏结束----------------//
void GameScene::Game_Over(int num)
{
	UserDefault::getInstance()->setIntegerForKey("Now", score);
	//存储最高分
	int high_score = UserDefault::getInstance()->getIntegerForKey("High");
	if (score>high_score)
	{
		UserDefault::getInstance()->setIntegerForKey("High", score);
	}

	//暂停当前计时器和动画
	this->unschedule(SEL_SCHEDULE(&GameScene::add_cloud));
	this->unschedule(SEL_SCHEDULE(&GameScene::add_stone));
	this->unschedule(SEL_SCHEDULE(&GameScene::add_dog));
	this->unschedule(SEL_SCHEDULE(&GameScene::is_Crash));
	this->unschedule(SEL_SCHEDULE(&GameScene::add_score));
	this->stopAllActions();

	//导演类全局停止
	//Director::getInstance()->stopAnimation();

	if (num == 1)
		GameOver::SceneNum = num;
		
	if (num == 2)
		GameOver::SceneNum = num;

	ManagerBase::deleteInstance();
	Director::getInstance()->replaceScene(TransitionFadeBL::create(1, GameOver::create()));
}
