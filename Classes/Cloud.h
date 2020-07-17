#ifndef __CLOUD_H__
#define __CLOUD_H__

#include "cocos2d.h"
USING_NS_CC;

class Cloud : public cocos2d::Sprite
{
public:

    virtual bool init();
    
	void initCloud(int name_index);
	void update(float dt);

    CREATE_FUNC(Cloud);
};

#endif
