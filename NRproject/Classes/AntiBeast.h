#ifndef _ANTI_BEAST_H_
#define _ANTI_BEAST_H_
#ifndef _FORT_H_
#define _FORT_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "SimpleAudioEngine.h"
#include "obstacle.h"

using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;

//cocos2d::Vector<Node*> PAPAPA;

#define ANTI_BEAST 0
#define ROCK 1
#define TREE 2
#define WOLF 3
#define MONSTER 4
#define FORT 5



class AntiBeast : public Obstacle
{
public:
	AntiBeast();
	bool init();
	virtual ~AntiBeast(void);


	CCRect rect();
	CCRect colRec();
	void operateAction();

	virtual CCObject* copyWithZone(CCZone *pZone);
	int getTrapType();
	
	void minusHP(int mHP);
	//AntiBeast* AntiBeast::paddleWithTexture(int type, int amount);
	int getattack();
	CCRect getrect();

	int getHPValue();

private:
	//bool exist;
	int trapType;
	int Attack;
	int HP;
	ControlSlider* Health;
};

class Fort : public Obstacle//, public TargetedTouchDelegate
{


public:
	Fort();
	virtual ~Fort(void);

	bool init();
	CCRect rect();
	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	//virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	virtual CCObject* copyWithZone(CCZone *pZone);

	int getTrapType();
	void minusHP(int mHP);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();
	int getattack();
	CCRect getrect();

	void spriteMoveFinished(CCNode* sender);

    CCRect colRec() ;

	int getHPValue() ;

private:
	int trapType;
	int Attack;
	int HP;
	ControlSlider* Health;
	
};

#endif
#endif