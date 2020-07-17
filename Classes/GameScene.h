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
	Label* label_score_num_; //��ǰ��
	Label* label_best_score_num_; // ��߷�

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void update(float dt); //ÿ֡����
	void updateOnce(float dt); //���μ�ʱ������
	//���ں�������
	void onEnterTransitionDidFinish();
	void onExit();

	void add_cloud(float dt);//�ƶ�����
	void add_stone(float dt);//ʯͷ����
	void add_dog(float dt);//��������

	void add_score(float dt);
    
public:
	//Ұ���˺�ճ���
	void init_hourse();

	//��ť�ص�
	void Hourse_Jump();//Ұ������
	void Hourse_Fire();//Ұ���˿��������ӵ�  ???�Լ� ��?��

	void is_Crash(float dt);//��ײ���
	void Game_Over(int num);//��Ϸ����

    CREATE_FUNC(GameScene);
};

#endif
