#include "archer.h"
#include "GameScene.h"
using namespace cocos2d;

extern Vector<Sprite*> Arrows;

archer::archer()
{
	
}

archer::~archer()
{
}

void archer::shoot(float dt)
{
	CCSprite* arrow = CCSprite::create("arrow.png");
	/*arrow->setPhysicsBody(PhysicsBody::createBox(arrow->getContentSize()));
	arrow->getPhysicsBody()->setGravityEnable(false);
	arrow->getPhysicsBody()->setCollisionBitmask(0x01);*/
	int duration = 6;
	CCSize winsize = CCDirector::sharedDirector()->getVisibleSize();
	CCActionInterval* fly = CCMoveBy::create((float)duration, ccp(winsize.width*0.6,0));
	CCFiniteTimeAction* disappear = CCCallFuncN::create(this, callfuncN_selector(archer::stopflying));
	arrow->setPosition(ccp(this->getContentSize().width, this->getContentSize().height/2));
	arrow->setTag(ARROW);
	float x = this->getPositionX();
	float y = this->getPositionY();
	arrow->runAction(CCSequence::create(fly, disappear,NULL));
	this->_arrows.pushBack(arrow);
	Arrows.pushBack(arrow);
	//this->getParent()->addChild(arrow);
	this->addChild(arrow);
	//((GameScene*)(this->getParent()))->getarrows()->addObject(arrow);
	
}

void archer::stopflying(CCNode* psender)
{
	CCSprite *sprite = (CCSprite *)psender;
	//this->getParent()->removeChild(sprite, true);
	Arrows.eraseObject(sprite, true);
	sprite->removeFromParentAndCleanup(true);
}

void archer::fight()
{
	/*if (isfighting){
		this->schedule(schedule_selector(archer::shoot), 1.1f);
	}
	else{ this->unschedule(schedule_selector(archer::shoot)); }*/
	this->schedule(schedule_selector(archer::shoot), 1.1f);
}

Vector<CCSprite*> archer::getarrow()
{
	return this->_arrows;
}


void archer::stopfight()
{
	this->unschedule(schedule_selector(archer::shoot));
}
//void archer::tookdamage(int damage	)
//{
//	this->HP = this->HP - damage;
//	Health->setValue(HP);
//
//}
//////////////////////////////////////////////////////////////////////////////

coach::coach()
{
	//this->removeAllChildrenWithCleanup(true);
	CCSprite::initWithFile("null.png");
	this->speed = 1;
	setTag(COACH);
	isMoving = false;
} 

coach::~coach()
{

}



void coach::move()
{
	if (!isMoving){
		CCActionInterval* Move = CCMoveBy::create(1, Point(40*3, 0));
		this->runAction(RepeatForever::create( Move));
		isMoving = true;
	}
}

void coach::fight(){}

void coach::stopfight(){}
void coach::jumpback(){}
Rect coach::getrect(){
	Rect herorect = CCRectMake(
				this->getPosition().x - (this->getContentSize().width / 2),
				this->getPosition().y - (this->getContentSize().height / 2),
				this->getContentSize().width,
				this->getContentSize().height
				);
			float a = getPosition().x;
			return herorect;

}

void coach::tookdamage(int damage){}

int coach::hp(){ return 255; }

void coach::pause()
{
	this->stopAllActions();
	isMoving = false;
}