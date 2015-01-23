#ifndef _CHAMPIONS_H
#define _CHAMPIONS_H

#include"cocos2d.h"

USING_NS_CC;

class Champions : public Sprite
{
public:
	Champions(){};
	~Champions(){};
	virtual void fight() = 0;
	virtual void stopfight() = 0;
	virtual void move() = 0;
	virtual void jumpback() = 0;
	virtual Rect getrect() = 0;
	virtual void tookdamage(int damage) = 0;
	virtual void pause() = 0;
	virtual int hp() = 0;
	
	/*virtual void stopByObstacle() = 0;
	virtual void StartMoveAgain() = 0;*/
};
//void Champions::pause()
//{
//	CCActionInterval* stop = CCMoveBy::create(1.0f, ccp(0, 0));
//	this->runAction(stop);
//}


//void Champion::jumpback(){
//	CCFiniteTimeAction* jumpup = CCMoveBy::create((float)0.2, ccp(-30, 20));
//	CCFiniteTimeAction* falldown = CCMoveBy::create((float)0.5, ccp(-24, -20));
//	this->runAction(CCSequence::create(jumpup, falldown, NULL));
//
//}
//
//Rect Champion::getrect(){
//	Rect herorect = CCRectMake(
//		this->getPosition().x - (this->getContentSize().width / 2),
//		this->getPosition().y - (this->getContentSize().height / 2),
//		this->getContentSize().width,
//		this->getContentSize().height
//		);
//	float a = getPosition().x;
//	return herorect;
//
//	
//}

#endif