#ifndef __BUTTLE_H__
#define __BUTTLE_H__

#include "cocos2d.h"
USING_NS_CC;

class Bullet : public cocos2d::Sprite
{
public:
	Sprite *bullet;
public:
    virtual bool init();

	void onEnterTransitionDidFinish();
	void onExit();

	void update(float dt);

	//³õÊ¼»¯×Óµ¯
	void initBullet(int index);

    CREATE_FUNC(Bullet);
};

#endif
