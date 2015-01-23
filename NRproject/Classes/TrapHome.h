#ifndef _TRAP_HOME_H_
#define _TRAP_HOME_H_

#include "Trap.h"
#include "cocos2d.h"

USING_NS_CC;

#define ANTI_BEAST 0
#define ROCK 1
#define TREE 2
#define WOLF 3
#define MONSTER 4
#define FORT 5

class PresetTrap;
class TrapHome : public CCSprite
{
public:
	TrapHome(int type);
	TrapHome(int amount, int type);
	virtual ~TrapHome(void);

	CCRect rect();

	//bool containsTouchLocation(CCTouch* touch);

	//virtual CCObject* copyWithZone(CCZone *pZone);
	int getAmounts();
	void refreshAmounts();
	void plusAmounts();
	void minusAmounts();
	bool initTrap();
	//void setTrapHome(PresetTrap* Trap);
	bool initWithTexture(int type);
	//void setLabel();
	static TrapHome* paddleWithTexture(int type, int amount);
private:
	int amounts;
	CCTexture2D* texture;
	int trapType;
	//CCLabelTTF* pLabel;
};

#endif