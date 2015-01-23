#ifndef _TRAP_H_
#define _TRAP_H_

#include "cocos2d.h"
#include "TrapHome.h"
#define AVAILABLE_GID 66

USING_NS_CC;


#define ANTI_BEAST 0
#define ROCK 1
#define TREE 2
#define WOLF 3
#define MONSTER 4
#define FORT 5

class TrapHome;
typedef enum tagTrapSettedState
{
	kPaddleStateGrabbed,
	kPaddleStateUngrabbed
} TrapState;

typedef enum tagTrapLayerState
{
	foward,
	back
} TrapLayerState;

class PresetTrap : public CCSprite //
{
	TrapState m_state;
	TrapLayerState ml_state;

public:
	PresetTrap(void);
	virtual ~PresetTrap(void);

	
	CCRect rect();
	bool initWithTexture(CCTexture2D* aTexture);
	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	bool onTouchBegan(Touch* touch, Event* event);
	void onTouchMoved(Touch* touch, Event* event);
	//virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);*/
	virtual CCObject* copyWithZone(CCZone *pZone);
	void setTrapHome(TrapHome* Home);
	bool isPositionAvailable();
	CCPoint tileCoordForPosition(CCPoint pos);
	int getTrapType();
	void setTrapType(int tp);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();

	static PresetTrap* paddleWithTexture(CCTexture2D* aTexture);
	void setListener();
	void AdjustPosition(float dt);
	void onTouchEnded(Touch* touch, Event* event);
private:
	TrapHome* tHome;
	int trapType;
	int originalGid;// = 0;
	//Sprite *Target;
};



#endif
