#pragma once
#ifndef _HERO_H
#define _HERO_H
#include <cocos2d.h>
#include "cocos-ext.h"
#include "champion.h"

USING_NS_CC_EXT;


#define COACH 255
#define ANTI_BEAST 0
#define ROCK 1
#define TREE 2
#define WOLF 3
#define MONSTER 4
#define FORT 5
#define WARRIAR 6
#define HERO 7
#define ARCHER 8
#define ARROW 9
#define BULLET 10

using namespace cocos2d;


class hero: public Champions
{
public:
	hero(void);
	~hero();
	
	bool init();
	virtual void fight();
	virtual void stopfight();
	bool isfighting;
	
	void move();
	void jumpback();
	void initAniwithPic();
	CCRect getrect();
	void tookdamage(int damage);
	int gettype();
	void pause();
	int hp();	
	int HP;
	
	void CheckMoving(float dt);
	bool isMoving;
private	:
	 
	
	SpriteFrameCache* cache;
	SpriteBatchNode* spritebatch;
	Animation* newanimation; 
	int speed;
	ControlSlider* Health;
	int herotype;
	//int attack;
	bool FromMoveToStop;
	bool FromStopToMove;
	ActionInterval* movee;
	int MoveTag ;


};

#endif