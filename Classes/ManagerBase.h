#ifndef __MANAGERBASE_H__
#define __MANAGERBASE_H__

#include "cocos2d.h"
#include "Bullet.h"
#include "Stone.h"
#include "Dog.h"

USING_NS_CC;

class ManagerBase //自建管理类,不需要继承其他类
{
	ManagerBase();
	~ManagerBase();
private:
	//创建管理单位
	static ManagerBase* manager;

public:
	//自建创建函数
	static ManagerBase* getInstance();
	//自建删除函数
	static void deleteInstance();
	
	//创建生成精灵的容器
	Vector<Stone*> Stone_list;
	Vector<Bullet*> Bullet_list;
	Vector<Dog*> Dog_list;

public:
	//管理容器内的数组里的单位
	Vector<Stone*>&getStoneList() { return Stone_list; }
	Vector<Bullet*>&getBulletList() { return Bullet_list; }
	Vector<Dog*>&getDogList() { return Dog_list; }

	//添加精灵到容器中
	void set_Stone_list(Stone* stone);
	void set_Bullet_list(Bullet* bullet);
	void set_Dog_list(Dog* dog);

	//移除容器内数组内的单位精灵
	void remove_Bullet_list(Bullet* bullet);
	void remove_Dog_list(Dog* dog);
	void remove_Stone_list(Stone* stone);
};

#endif
