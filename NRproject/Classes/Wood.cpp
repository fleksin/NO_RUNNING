#include "Wood.h"

Wood::Wood(){
	initWithFile("wood.png");
	trapType = TREE;
	Attack = 150;
	HP = 100;
	
	setPhysicsBody(PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, Point::ZERO));
	schedule(schedule_selector(Wood::testVelocity));
	getPhysicsBody()->setDynamic(true);

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(Wood::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(Wood::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(Wood::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//moved = false;
}

Rect Wood::colRec(){
	Rect disrect = CCRectMake(
		this->getPosition().x - (this->getContentSize().width / 2),
		this->getPosition().y - (this->getContentSize().height / 2),
		this->getContentSize().width,
		this->getContentSize().height
		);
	return disrect; 
}

void Wood::minusHP(int hp){
	HP = HP - hp;
}

void Wood::testVelocity(float dt){
	auto velo = getPhysicsBody()->getVelocity().y;

}

void Wood::onTouchEnded(Touch* touch, Event* evenT){
	offset = offset - touch->getLocation().x;
	if (offset > 0){
		getPhysicsBody()->applyImpulse(Vect(-250000, 0),Point(0,80));
	}
}


bool Wood::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

Rect Wood::rect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}
