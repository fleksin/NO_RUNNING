#include "AntiBeast.h"
#include "GameScene.h"

extern Vector<Sprite*> Bullets;
AntiBeast::AntiBeast()
{
	//HP = hp;
	//Attack = att;
	CCSprite::initWithFile("blocks.png");
	//exist = true;
	trapType = ANTI_BEAST;
	this->Attack = 50;
	this->HP = 400;

	Health = ControlSlider::create("sliderTrack.png", "sliderProgress.png", "null.png");

	Health->setMinimumValue(0); // Sets the min value of range
	Health->setMaximumValue(HP); // Sets the max value of range
	Health->setValue(HP);
	Health->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 10));
	Health->setEnabled(false);

	addChild(Health);
	Health->setVisible(false);

	//this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize()));

}

bool AntiBeast::init()
{
	//trapType = ANTI_BEAST;
	//this->Attack = 50;
	//this->HP = 50;
	//
	//Health = CCControlSlider::create("sliderTrack.png", "sliderProgress.png", "null.png");

	//Health->setMinimumValue(0); // Sets the min value of range
	//Health->setMaximumValue(HP); // Sets the max value of range
	//Health->setValue(HP);
	//Health->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 10));
	//Health->setEnabled(false);

	//addChild(Health);
	//Health->setVisible(false);
	return true;
}

AntiBeast::~AntiBeast(void)
{
}

CCRect AntiBeast::rect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

CCRect AntiBeast::colRec()
{
	CCRect disrect = CCRectMake(
		this->getPosition().x - (this->getContentSize().width / 2),
		this->getPosition().y - (this->getContentSize().height / 2),
		this->getContentSize().width,
		this->getContentSize().height
		);
	return disrect;
}

void AntiBeast::operateAction()
{
}

int AntiBeast::getHPValue()
{
	return HP;
}

void AntiBeast::minusHP(int hp)
{
	HP = HP - hp;
	//this->Health->setValue(HP);
	//Health->setValue(0);
}

CCObject* AntiBeast::copyWithZone(CCZone *pZone)
{
	this->retain();
	return this;
}

//AntiBeast* AntiBeast::paddleWithTexture(int type, int amount)
//{
//	AntiBeast* antiB = new AntiBeast(amount, type);
//	antiB->initWithTexture(type);
//	antiB->autorelease();
//
//	return traphome;
//}

int AntiBeast::getTrapType()
{
	return trapType;
}
int AntiBeast::getattack()
{
	return this->Attack;
}
CCRect AntiBeast::getrect()
{
	CCRect this_rect = CCRectMake(
		this->getPosition().x - (this->getContentSize().width / 2),
		this->getPosition().y - (this->getContentSize().height / 2),
		this->getContentSize().width,
		this->getContentSize().height
		);
	return this_rect;
}


//---------------------------------------------------------

Fort::Fort()
{
	
	this->HP = 400;
	this->Attack = 50;
	CCSprite::initWithFile("block2.png");
	trapType = FORT;
	/*this->Attack = 50;
	this->HP = 50;*/

	Health = ControlSlider::create("sliderTrack.png", "sliderProgress.png", "null.png");

	Health->setMinimumValue(0); // Sets the min value of range
	Health->setMaximumValue(HP); // Sets the max value of range
	Health->setValue(HP);
	Health->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 10));
	Health->setEnabled(false);

	addChild(Health);
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [this](Touch* touch, Event* event){
		if (!containsTouchLocation(touch)) return false;
		CCTexture2D* aTexture;
		aTexture = CCTextureCache::sharedTextureCache()->addImage("block2b.png");
		this->setTexture(aTexture);
		//Health->setValue(HP - 50);
		return true; };
	//listener1->onTouchMoved=
	listener1->onTouchEnded = [this](Touch* touch, Event* event){
		CCTexture2D* aTexture;
		aTexture = CCTextureCache::sharedTextureCache()->addImage("block2.png");
		this->setTexture(aTexture);
		if (!containsTouchLocation(touch))
		{
			CCSprite* Bullet = CCSprite::create("CloseSelected.png");
			Bullet->setTag(Attack);
			//((CCLayer*)((CCSprite*)this->getParent())->getParent())->addChild(Bullet);
			//((GameScene*)((CCSprite*)((CCSprite*)this->getParent())->getParent())->getParent())->getObstaclesBullets().pushBack(Bullet);
			Bullets.pushBack(Bullet);
			
			//Bullet->setPosition(Point(getContentSize().width/2,getContentSize().height/2));

			Bullet->setPosition((getPosition()));

			Point testPos=Bullet->getPosition();

			getParent()->addChild(Bullet);


			float distance = ccpDistance(Bullet->getPosition(), ccpAdd(Bullet->getPosition(), convertToNodeSpaceAR(touch->getLocation())));
			CCActionInterval* move = CCMoveBy::create(distance / 500, convertToNodeSpaceAR(touch->getLocation()));
			CCFiniteTimeAction* seq = CCSequence::create(move, NULL);
			CCAction* rep = CCRepeatForever::create((CCActionInterval*)seq);

			Bullet->runAction(rep);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
		};
		
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
   
	//this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize()));
}

bool Fort::init()
{
	//trapType = FORT;
	///*this->Attack = 50;
	//this->HP = 50;*/
	//
	//Health = CCControlSlider::create("sliderTrack.png", "sliderProgress.png", "null.png");

	//Health->setMinimumValue(0); // Sets the min value of range
	//Health->setMaximumValue(HP); // Sets the max value of range
	//Health->setValue(HP);
	//Health->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 10));
	//Health->setEnabled(false);

	//addChild(Health);
    return true;
}
Fort::~Fort(void)
{
}

CCRect Fort::rect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}


void Fort::onEnter()
{
	//CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	Sprite::onEnter();
}

void Fort::onExit()
{
	//CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->removeDelegate(this);
	Sprite::onExit();
}

bool Fort::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}

bool Fort::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	if (!containsTouchLocation(touch)) return false;
	CCTexture2D* aTexture;
	aTexture = CCTextureCache::sharedTextureCache()->addImage("block2b.png");
	this->setTexture(aTexture);
	Health->setValue(HP-50);
	return true;
}

void Fort::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	// If it weren't for the TouchDispatcher, you would need to keep a reference
	// to the touch from touchBegan and check that the current touch is the same
	// as that one.
	// Actually, it would be even more complicated since in the Cocos dispatcher
	// you get CCSets instead of 1 UITouch, so you'd need to loop through the set
	// in each touchXXX method.


}

CCObject* Fort::copyWithZone(CCZone *pZone)
{
	this->retain();
	return this;
}

//void Fort::ccTouchEnded(CCTouch* touch, CCEvent* event)
//{
//	CCTexture2D* aTexture;
//	aTexture = CCTextureCache::sharedTextureCache()->addImage("block2.png");
//	this->setTexture(aTexture);
//	if (!containsTouchLocation(touch))
//	{
//		CCSprite* Bullet = CCSprite::create("CloseSelected.png");
//		Bullet->setTag(Attack);
//		((CCLayer*)((CCSprite*)this->getParent())->getParent())->addChild(Bullet);
//		((GameScene*)((CCSprite*)((CCSprite*)this->getParent())->getParent())->getParent())->getObstaclesBullets()->addObject(Bullet); 
//		Bullet->setPosition(this->getPosition());
//		
//
//		float distance = ccpDistance(Bullet->getPosition(), ccpAdd(Bullet->getPosition(), convertToNodeSpaceAR(touch->getLocation())));
//		CCActionInterval* move = CCMoveBy::create(distance/500, convertToNodeSpaceAR(touch->getLocation()));
//		CCFiniteTimeAction* seq = CCSequence::create(move,NULL);
//		CCAction* rep = CCRepeatForever::create((CCActionInterval*)seq);
//
//		Bullet->runAction(rep);
//		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav");
//		/*Bullet->runAction(CCSequence::create(move, CCCallFuncN::create(this,
//			callfuncN_selector(Fort::spriteMoveFinished)), NULL));*/
//		
//	}
//}

void Fort::spriteMoveFinished(CCNode* sender)
{
	CCSprite *sprite = (CCSprite *)sender;

	((GameScene*)((CCSprite*)((CCSprite*)this->getParent())->getParent())->getParent())->getObstaclesBullets().eraseObject(sprite);
	sprite->removeFromParentAndCleanup(true);
}

void Fort::touchDelegateRetain()
{
	this->retain();
}

void Fort::touchDelegateRelease()
{
	this->release();
}

void Fort::minusHP(int hp)
{
	this->HP = this->HP - hp;
	this->Health->setValue(HP);
}

int Fort::getTrapType()
{
	return trapType;
}

int Fort::getattack()
{
	return this->Attack;
}

CCRect Fort::getrect()
{
	CCRect this_rect = CCRectMake(
		this->getPosition().x - (this->getContentSize().width / 2),
		this->getPosition().y - (this->getContentSize().height / 2),
		this->getContentSize().width,
		this->getContentSize().height
		);
	return this_rect;
}

int Fort::getHPValue(){
	return this->HP;
}

CCRect Fort::colRec()
{
	CCRect herorect = CCRectMake(
		this->getPosition().x - (this->getContentSize().width / 2),
		this->getPosition().y - (this->getContentSize().height / 2),
		this->getContentSize().width,
		this->getContentSize().height
		);
	return herorect;
}

//-----------------------------------------------

