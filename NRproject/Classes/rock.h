#ifndef _ROCK_HEADER_
#define _ROCK_HEADER_

#include "cocos2d.h"
#include "obstacle.h"
USING_NS_CC;
class Rock :public Obstacle{
public:
	Rock();
	~Rock();
	
	CCRect colRec();	

	void minusHP(int hp);

	int getattack();	

	int getHPValue() ;

	//CCRect rect();
	//CCRect getrect() ;
	//CCObject* copyWithZone(CCZone *pZone);

	void onTouchEnded(Touch* touch, Event* evenT);

	bool onTouchbegan(Touch* touch, Event* evenT);

	bool containsTouchLocation(CCTouch* touch);

	Rect rect();
	

	

private:

	int HP;

	int attack;

	ControlSlider* HealthBar;

	int TrapType;

};




#endif