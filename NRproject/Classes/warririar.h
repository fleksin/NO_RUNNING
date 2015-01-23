#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;

class Warriar: public Sprite
{
public:
	Warriar();
	~Warriar();
	void fight();
	void stopfight();

private:
	Animate* Fight;

};
