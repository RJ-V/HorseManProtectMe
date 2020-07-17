#include "Setting.h"

USING_NS_CC;

Scene* Setting::createScene()
{
    return Setting::create();
}

bool Setting::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	EffectFlag = true;
	BackGroundMusicFlag = true;


    auto VSize = Director::getInstance()->getVisibleSize();

	BackGround = Sprite::create();
	BackGround->setPosition(VSize.width / 2, VSize.height / 2);
	this->addChild(BackGround);

	auto animation = Animation::create();
	for (int i = 1; i <= 2; ++i)
	{
		auto name_str = String::createWithFormat("SetBackGround%d.png", i);
		animation->addSpriteFrameWithFile(name_str->getCString());
	}
	animation->setDelayPerUnit(1.0f);
	animation->setLoops(-1);
	BackGround->runAction(Animate::create(animation));
	//---------------------��Ƶ��������---------------------//
	auto Effect_Label = Label::create("Effect", "fonts/arial.ttf", 60);
	Effect_Label->setPosition(Vec2(850, 400));
	Effect_Label->setColor(Color3B(255, 255, 255));
	this->addChild(Effect_Label, 1);

	auto Music_Label = Label::create("Music", "fonts/arial.ttf", 60);
	Music_Label->setPosition(Vec2(850, 600));
	Music_Label->setColor(Color3B(255, 255, 255));
	this->addChild(Music_Label, 1);
	//��Toggle�����õ�����ť
	auto EffectOnMenuItem = MenuItemImage::create("SetOn.png", "SetOn.png");
	EffectOnMenuItem->setScale(0.6);
	auto EffectOffMenuItem = MenuItemImage::create("SetOff.png", "SetOff.png");
	EffectOffMenuItem->setScale(0.6);
	//������İ�ť�󶨵�Toggle��
	auto SoundToggle1 = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Setting::menuEffect, this), EffectOnMenuItem, EffectOffMenuItem, NULL);
	SoundToggle1->setPosition(Vec2(1100, 400));
	
	auto MusicOnMenuItem = MenuItemImage::create("SetOn.png", "SetOn.png");
	MusicOnMenuItem->setScale(0.6);
	auto MusicOffMenuItem = MenuItemImage::create("SetOff.png", "SetOff.png");
	MusicOffMenuItem->setScale(0.6);

	auto SoundToggle2 = MenuItemToggle::createWithCallback(
		CC_CALLBACK_1(Setting::menuBackGroundMusic, this), MusicOnMenuItem, MusicOffMenuItem, NULL);
	SoundToggle2->setPosition(Vec2(1100, 600));

	//----------------���غ���------------------//
	auto SetBack = MenuItemImage::create("SetBack1.png", "SetBack2.png",
		CC_CALLBACK_0(Setting::Back, this));
	SetBack->setPosition(Vec2(1100, 100));

	auto setmenu = Menu::create(SoundToggle1, SoundToggle2, SetBack, NULL);
	setmenu->setPosition(Vec2::ZERO);
	this->addChild(setmenu, 1);

    return true;
}

void Setting::menuEffect(Ref* pSender)
{
	if (EffectFlag)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
		EffectFlag = false;
	}
	else
	{
		//SimpleAudioEngine::getInstance()->playEffect();
		EffectFlag = true;
	}
}

void Setting::menuBackGroundMusic(Ref* pSender)
{
	if (BackGroundMusicFlag)
	{
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		BackGroundMusicFlag = false;
	}
	else
	{
		log("%d", BackGroundMusicFlag);
		SimpleAudioEngine::getInstance()->playBackgroundMusic("bgm_cocos.mp3");
		BackGroundMusicFlag = true;
	}
}
void Setting::Back()
{
	Director::getInstance()->popScene();
}