#ifndef __HELLOWORLD_H__
#define __HELLOWORLD_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class HelloWorld : public cocos2d::Scene
{
public:
	Sprite* BackGround;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void StartGame();
	void Setting();
	void Exit();

    CREATE_FUNC(HelloWorld);
};

#endif
