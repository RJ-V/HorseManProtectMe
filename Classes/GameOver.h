#ifndef __GAMEOVER_H__
#define __GAMEOVER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class GameOver : public cocos2d::Scene
{
public:
	Sprite* sprite;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	static int SceneNum;
    
	//怎么死的就是那个对应结局
	void GameOver_Stone();
	void GameOver_Dog();

	void GameBack();//回到主界面
	void GameAgain();//重新进入游戏

    CREATE_FUNC(GameOver);
};

#endif
