#ifndef __STONE_H__
#define __STONE_H__

#include "cocos2d.h"
USING_NS_CC;
class Stone : public cocos2d::Sprite
{
public:
	Sprite* stone;
public:

    virtual bool init();

	void initStone();
	void update(float dt);

    CREATE_FUNC(Stone);
};

#endif
