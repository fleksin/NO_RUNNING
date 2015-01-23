#ifndef _OBSTACLE_H
#define _OBSTACLE_H
#include <cocos2d.h>
#include "hero.h"

USING_NS_CC;
class Obstacle : public Sprite
{
public:
	Obstacle(){};

	virtual ~Obstacle(){};
		
	virtual CCRect colRec()=0;
	
	virtual void minusHP(int hp) = 0;

	virtual int getattack() = 0;

	virtual int getHPValue() = 0;


};


#endif