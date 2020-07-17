#ifndef __SETTING_H__
#define __SETTING_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class Setting : public cocos2d::Scene
{
public:
	Sprite* BackGround;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	bool EffectFlag;
	bool BackGroundMusicFlag;
    
	void menuEffect(Ref* pSender);
	void menuBackGroundMusic(Ref* pSender);
	void Back();

    CREATE_FUNC(Setting);
};

#endif
