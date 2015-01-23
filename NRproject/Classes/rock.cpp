#include "rock.h"
#include "cocos2d.h"

USING_NS_CC;


Rock::Rock(){
	Sprite::initWithFile("ball.png");

	setTag(ROCK);

	TrapType = ROCK;

	attack = 1000;

	HP = 1000;


	this->setPhysicsBody(PhysicsBody::createCircle(this->getContentSize().height/2,PHYSICSBODY_MATERIAL_DEFAULT,Point::ZERO));
	getPhysicsBody()->setGravityEnable(false);
	getPhysicsBody()->setCollisionBitmask(0x01);

	auto *listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchEnded = CC_CALLBACK_2(Rock::onTouchEnded, this);
	listener->onTouchBegan = CC_CALLBACK_2(Rock::onTouchbegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

};

Rock::~Rock(){


};


Rect Rock::colRec(){
	CCRect rect = CCRectMake(
		this->getPosition().x - (this->getContentSize().width / 2),
		this->getPosition().y - (this->getContentSize().height / 2),
		this->getContentSize().width,
		this->getContentSize().height
		);
	return rect;

};

void Rock::minusHP(int hp)
{
	HP = HP - hp;
	HealthBar->setValue(HP);
}

int Rock::getattack(){

	return attack;
};

int Rock::getHPValue(){

	return HP;
};


void Rock::onTouchEnded(Touch* touch, Event* evenT){
	if (containsTouchLocation(touch))
		getPhysicsBody()->setGravityEnable(true);
}

bool Rock::onTouchbegan(Touch* touch, Event* evenT){

	if (!containsTouchLocation(touch)) return false;
	else
	{
		return true;
	}
	
}

bool Rock::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

Rect Rock::rect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}
