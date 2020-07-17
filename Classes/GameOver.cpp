#include "GameOver.h"
#include "GameScene.h"
#include "HelloWorld.h"

USING_NS_CC;
//定义全局变量用来传值
int GameOver::SceneNum = 0;

Scene* GameOver::createScene()
{
    return GameOver::create();
}

bool GameOver::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto VSize = Director::getInstance()->getVisibleSize();
	
	auto background = Sprite::create("overbackground.png");
	background->setPosition(Vec2(VSize.width / 2, VSize.height / 2));
	this->addChild(background);

	sprite = Sprite::create();
	sprite->setPosition(Vec2(VSize.width / 2, VSize.height / 2 - 100));
	this->addChild(sprite);

	//回主页按钮精灵
	auto back = Sprite::create("Back.png");
	back->setScale(0.8);
	//重来按钮精灵
	auto again = Sprite::create("Again.png");
	again->setScale(0.8);
	//按钮回调
	auto backItem = MenuItemSprite::create(back, back, CC_CALLBACK_0(GameOver::GameBack, this));
	backItem->setPosition(Vec2(150, VSize.height / 2 - 100));
	auto againItem = MenuItemSprite::create(again, again, CC_CALLBACK_0(GameOver::GameAgain, this));
	againItem->setPosition(Vec2(1180, VSize.height / 2 - 100));

	auto menu = Menu::create(backItem, againItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 2);
	

	//结局判断
	if (SceneNum == 1)
	{
		//log("%i", SceneNum);
		GameOver_Stone();
	}
	else if (SceneNum == 2)
	{
		//log("%i", SceneNum);
		GameOver_Dog();
	}

	//分数设置
	auto label_score = Label::create("Now", "fonts/arial.ttf", 40);
	label_score->setPosition(Vec2(VSize.width / 2 + 100, VSize.height / 2 + 150));
	label_score->setColor(Color3B(0, 0, 0));
	this->addChild(label_score, 2);

	auto label_score_num = Label::create();
	label_score_num->setSystemFontSize(30);
	label_score_num->setPosition(Vec2(VSize.width / 2 + 200, VSize.height / 2 + 150));
	label_score_num->setColor(Color3B(0, 0, 0));
	this->addChild(label_score_num, 2);
	//最高分
	auto label_best_score = Label::create("High", "fonts/arial.ttf", 40);
	label_best_score->setPosition(Vec2(VSize.width / 2 - 200, VSize.height / 2 + 150));
	label_best_score->setColor(Color3B(0, 0, 0));
	this->addChild(label_best_score, 2);

	auto label_best_score_num = Label::create();
	label_best_score_num->setSystemFontSize(30);
	label_best_score_num->setPosition(Vec2(VSize.width / 2 - 100, VSize.height / 2 + 150));
	label_best_score_num->setColor(Color3B(0, 0, 0));
	this->addChild(label_best_score_num, 2);

	//获取最高分
	auto score_high = UserDefault::getInstance()->getIntegerForKey("High");
	auto score_now = UserDefault::getInstance()->getIntegerForKey("Now");

	//最高分
	label_best_score_num->setString(String::createWithFormat("%d", score_high)->getCString());
	label_score_num->setString(String::createWithFormat("%d", score_now)->getCString());
    return true;
}
void GameOver::GameOver_Stone()
{
	auto VSize = Director::getInstance()->getVisibleSize();
	auto label = Sprite::create("GameOver_Stone_label.png");
	label->setPosition(Vec2(VSize.width / 2, VSize.height / 2 + 270));
	label->setScale(0.6);
	this->addChild(label, 2);

	auto animation = Animation::create();
	for (int i = 1; i <= 2; ++i)
	{
		auto name_str = String::createWithFormat("GameOver_Stone%d.png", i);
		animation->addSpriteFrameWithFile(name_str->getCString());
	}
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(-1);
	sprite->runAction(Animate::create(animation));
}

void GameOver::GameOver_Dog()
{
	auto VSize = Director::getInstance()->getVisibleSize();
	auto label = Sprite::create("GameOver_Dog_label.png");
	label->setPosition(Vec2(VSize.width / 2, VSize.height / 2 + 270));
	label->setScale(0.6);
	this->addChild(label, 2);

	auto animation = Animation::create();
	for (int i = 1; i <= 3; ++i)
	{
		auto name_str = String::createWithFormat("GameOver_Dog%d.png", i);
		animation->addSpriteFrameWithFile(name_str->getCString());
	}
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(-1);
	sprite->runAction(Animate::create(animation));
}

void GameOver::GameBack()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, HelloWorld::create()));
}

void GameOver::GameAgain()
{
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
}
