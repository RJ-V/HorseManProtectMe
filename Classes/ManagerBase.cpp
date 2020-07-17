#include "ManagerBase.h"
#include "GameScene.h"

USING_NS_CC;

ManagerBase* ManagerBase::manager = NULL;

//���캯������������
ManagerBase::ManagerBase(){}
ManagerBase::~ManagerBase(){}//����δ����ĺ������Զ�����

ManagerBase * ManagerBase::getInstance()
{
	//����λ��û�У����½�һ������λ
	if (manager == NULL)
		manager = new ManagerBase();
	return manager;
}
void ManagerBase::deleteInstance()
{
	if (manager)
	{
		delete manager;
		manager = NULL;
	}
}

//����������������ջɾ������
void ManagerBase::set_Stone_list(Stone * stone) { Stone_list.pushBack(stone); }

void ManagerBase::set_Bullet_list(Bullet * bullet) { /*log("bulletPush"); */Bullet_list.pushBack(bullet); }

void ManagerBase::set_Dog_list(Dog * dog) { log("dogPush"); Dog_list.pushBack(dog); }


void ManagerBase::remove_Stone_list(Stone* stone) { Stone_list.eraseObject(stone); }

void ManagerBase::remove_Bullet_list(Bullet * bullet) { /*log("bulletRemove");*/ Bullet_list.eraseObject(bullet); }

void ManagerBase::remove_Dog_list(Dog * dog) { log("DogRemove"); Dog_list.eraseObject(dog); }