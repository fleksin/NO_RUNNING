#include "cocos2d.h"
#include "obstacle.h"

USING_NS_CC;

class Wood:public Obstacle
{
public:
	Wood();
	~Wood(){};
	
	Rect colRec() ;

	void minusHP(int hp)  ;

	int getattack()  { return Attack; };

	int getHPValue(){ return HP; };

	bool onTouchBegan(Touch* touch, Event* evenT){ 
		if (!containsTouchLocation(touch))return false;
		else
		{
			offset = touch->getLocation().x; this->setOpacity(180); return true;
		}
		
	};

	void onTouchMoved(Touch* touch, Event* evenT){ };

	void onTouchEnded(Touch* touch, Event* evenT);

	void testVelocity(float dt);

	bool moved;

	float offset;

	bool containsTouchLocation(CCTouch* touch);

	Rect rect();
private:
	int trapType;
	int Attack;
	int HP;
	//ControlSlider* Health;

};
