#ifndef __MANAGERBASE_H__
#define __MANAGERBASE_H__

#include "cocos2d.h"
#include "Bullet.h"
#include "Stone.h"
#include "Dog.h"

USING_NS_CC;

class ManagerBase //�Խ�������,����Ҫ�̳�������
{
	ManagerBase();
	~ManagerBase();
private:
	//��������λ
	static ManagerBase* manager;

public:
	//�Խ���������
	static ManagerBase* getInstance();
	//�Խ�ɾ������
	static void deleteInstance();
	
	//�������ɾ��������
	Vector<Stone*> Stone_list;
	Vector<Bullet*> Bullet_list;
	Vector<Dog*> Dog_list;

public:
	//���������ڵ�������ĵ�λ
	Vector<Stone*>&getStoneList() { return Stone_list; }
	Vector<Bullet*>&getBulletList() { return Bullet_list; }
	Vector<Dog*>&getDogList() { return Dog_list; }

	//��Ӿ��鵽������
	void set_Stone_list(Stone* stone);
	void set_Bullet_list(Bullet* bullet);
	void set_Dog_list(Dog* dog);

	//�Ƴ������������ڵĵ�λ����
	void remove_Bullet_list(Bullet* bullet);
	void remove_Dog_list(Dog* dog);
	void remove_Stone_list(Stone* stone);
};

#endif
