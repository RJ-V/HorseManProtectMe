#ifndef __DOG_H__
#define __DOG_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

class Dog : public cocos2d::Sprite
{
public:
    virtual bool init();

	void initDog();

	void dog_death();
	void remove_dog();

	virtual void update(float dt);

	//¹·×ÓµÄÑª
	int dog_hp_;
	void set_hp(int hp);
	int get_hp() { return dog_hp_; }

	//ÅÐ¶ÏËÀÍö
	bool is_death;

    CREATE_FUNC(Dog);
};

#endif
