#include "HelloWorld.h"
#include "GameScene.h"
#include "Setting.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto VSize = Director::getInstance()->getVisibleSize();
	//±³¾°°å
	auto background = Sprite::create("overbackground.png");
	background->setPosition(Vec2(VSize.width / 2, VSize.height / 2));
	this->addChild(background);

	auto title = Sprite::create("title.png");
	title->setPosition(Vec2(VSize.width / 2, VSize.height / 2));
	this->addChild(title,1);
	//¿ªÊ¼±³¾°¶¯»­
	BackGround = Sprite::create();
	BackGround->setPosition(VSize.width / 2, VSize.height / 2);
	BackGround->setOpacity(80);
	this->addChild(BackGround);

	auto animation = Animation::create();
	for (int i = 1; i <= 4; ++i)
	{
		auto name_str = String::createWithFormat("StartBack%d.png", i);
		animation->addSpriteFrameWithFile(name_str->getCString());
	}
	animation->setDelayPerUnit(0.3f);
	animation->setLoops(-1);
	BackGround->runAction(Animate::create(animation));

	auto StartItem = MenuItemImage::create("Start_Button1.png", "Start_Button2.png",
		CC_CALLBACK_0(HelloWorld::StartGame, this));
	StartItem->setScale(0.6);
	StartItem->setPosition(Vec2(VSize.width / 2, VSize.height / 2 + 250));

	auto SetItem = MenuItemImage::create("Set_Button1.png", "Set_Button2.png",
		CC_CALLBACK_0(HelloWorld::Setting, this));
	SetItem->setScale(0.6);
	SetItem->setPosition(Vec2(VSize.width / 2, VSize.height / 2));

	auto ExitItem = MenuItemImage::create("Exit_Button1.png", "Exit_Button2.png",
		CC_CALLBACK_0(HelloWorld::Exit, this));
	ExitItem->setScale(0.6);
	ExitItem->setPosition(Vec2(VSize.width / 2, VSize.height / 2 - 250));

	auto HelloMenu = Menu::create(StartItem, SetItem, ExitItem, NULL);
	HelloMenu->setPosition(Vec2::ZERO);
	this->addChild(HelloMenu);
	
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bgm_cocos.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("biu.mp3");
	SimpleAudioEngine::getInstance()->preloadEffect("what.mp3");

	SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_cocos.mp3");
    return true;
}

void HelloWorld::StartGame()
{
	Director::getInstance()->replaceScene((TransitionFade::create(0.5, GameScene::create())));
}

void HelloWorld::Setting()
{
	Director::getInstance()->pushScene(Setting::create());
}

void HelloWorld::Exit()
{
	Director::getInstance()->end();
}
