#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
class GameScene : public cocos2d::Scene
{
public:
	Sprite *spr_bg1;
	Sprite *spr_bg2;
	Sprite *spr_bg3;

	Sprite *Jump_Button;
	Sprite *Fire_Button;

	Sprite *HourseHero;

	Animate *HourseRun;
	Animate *HourseJump;

public:
	bool Running;

	int score;
	Label* label_score_num_; //当前分
	Label* label_best_score_num_; // 最高分

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void update(float dt); //每帧调用
	void updateOnce(float dt); //单次计时器调用
	//周期函数调用
	void onEnterTransitionDidFinish();
	void onExit();

	void add_cloud(float dt);//云朵生成
	void add_stone(float dt);//石头生成
	void add_dog(float dt);//狗子生成

	void add_score(float dt);
    
public:
	//野马人横空出世
	void init_hourse();

	//按钮回调
	void Hourse_Jump();//野马人跳
	void Hourse_Fire();//野马人开火，生成子弹  ???以及 火?焰

	void is_Crash(float dt);//碰撞检测
	void Game_Over(int num);//游戏结束

    CREATE_FUNC(GameScene);
};

#endif
