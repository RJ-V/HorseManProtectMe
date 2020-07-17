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
    
	//��ô���ľ����Ǹ���Ӧ���
	void GameOver_Stone();
	void GameOver_Dog();

	void GameBack();//�ص�������
	void GameAgain();//���½�����Ϸ

    CREATE_FUNC(GameOver);
};

#endif
