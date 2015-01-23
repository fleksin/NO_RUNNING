#ifndef _ARHCER_H
#define _ARHCER_H

#include <cocos2d.h>
#include "hero.h"



using namespace cocos2d;

class archer :public hero	
{
public:
	archer();
	~archer();
	//start fight
	//void fight();
	////is hero fighting;
	//bool isfighting;
	////is hero moving;
	//bool ismoving;
	////is hero dead;
	//bool isdead;
	//void move();
	//void jumpback();
	//void initAniwithPic();
	//CCRect getrect();
	void shoot(float dt);
	void stopflying(CCNode* psender);
	void fight();
	void stopfight();
	//void tookdamage(int damage);
	//Vector<Sprite*>* getarrow();
	Vector<CCSprite*> getarrow();
private:
	CCSpriteFrameCache* cache;
	CCSpriteBatchNode* spritebatch;
	CCAnimation* newanimation;
	int speed;
	int HP;
	ControlSlider* Health;
	int herotype;
	//Vector<Sprite*>* _arrows;
	Vector<CCSprite*> _arrows;
};

class coach :public Champions
{
public:
	coach();
	~coach();
	
	void move();
	void fight();
	void stopfight();
	void jumpback();
	Rect getrect();
	void tookdamage(int damage);
	int hp();
	bool isMoving;
	void pause();


private:
	 int speed;

};

#endif