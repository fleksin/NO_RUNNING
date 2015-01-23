#include "hero.h"




using namespace cocos2d;


hero::hero()
{
	//animation;
	this->HP = 888*3;
	//this->attack = 50;
	//******sprite sheet and frames are loaded**************
	this->spritebatch = SpriteBatchNode::create("grossini.png");
	this->cache = SpriteFrameCache::getInstance();
	this->cache->addSpriteFramesWithFile("grossini.plist");
	
	//herosprite = CCSprite::createWithSpriteFrameName("grossini_dance_00.png");
	Sprite::initWithSpriteFrameName("grossini_dance_00.png");
	//CCArray *animframe = CCArray::createWithCapacity(5);    <--this method of creating animation frames is used in 2.2 version

	//this->setPhysicsBody(PhysicsBody::createBox(this->getContentSize()));

	//now is the 3.0 version
	this->addChild(spritebatch);
	//Vector<SpriteFrame*> animframe;
	//char str[100] = { 0 };
	//for (int i = 0; i < 5; i++)
	//{	
	//	//animframe->addObject(frame);*/
	//	sprintf(str, "grossini_dance_%02d.png", i);

	//	//*CCString* filename = CCString::createWithFormat("grossini_dance_%02d.png", i);
	//	SpriteFrame* frame = cache->getSpriteFrameByName(str);	

	//	//auto frame = SpriteFrame::create(str, Rect(0, 0, 40, 40)); //we assume that the sprites' dimentions are 40*40 rectangles. <--copied from official guide
	//	//********error spot*************************
	//	//if (frame!=nullptr)
	//		animframe.pushBack(frame);

	//	
	//}
	//this->newanimation = Animation::createWithSpriteFrames(animframe, 0.3f);
	//AnimationCache::getInstance()->addAnimation(newanimation, "fight");
	this->speed = 1;
	this->Health = ControlSlider::create("sliderTrack.png", "sliderProgress.png", "null.png");

	this->Health->setMinimumValue(0); // Sets the min value of range
	this->Health->setMaximumValue(HP); // Sets the max value of range
	this->Health->setValue(HP);
	this->Health->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height + 10));
	this->Health->setEnabled(false);

	addChild(Health);

	//this->herotype = HERO;
	setTag(HERO);
	FromMoveToStop = false;
	FromStopToMove = true;
	//schedule(schedule_selector(hero::CheckMoving));
	movee = MoveBy::create(1, ccp(1, 0));
	MoveTag = 1;
	isMoving = false;
	/*movee->setTag(MoveTag);
	Director::getInstance()->getActionManager()->addAction(Move, this, true);*/
}


hero::~hero()
{
}



void hero::fight()
{
	if (this->isfighting){
		CCAnimation* fight = CCAnimationCache::sharedAnimationCache()->animationByName("fight");
		this->runAction((CCAnimate::create(fight)));
	}



}
 



void hero::move()
{
	if (!isMoving)
	{
		int actualDuration = 1;
		//CCSize winsize = CCDirector::sharedDirector()->getVisibleSize();
		CCActionInterval* Move = CCMoveBy::create((float)actualDuration, Point(40*3, 0));
	


		Vector<SpriteFrame*> animframe;
		char str[100] = { 0 };
		for (int i = 0; i < 5; i++)
		{
			//animframe->addObject(frame);*/
			sprintf(str, "grossini_dance_%02d.png", i);

			//*CCString* filename = CCString::createWithFormat("grossini_dance_%02d.png", i);
			SpriteFrame* frame = cache->getSpriteFrameByName(str);

			//auto frame = SpriteFrame::create(str, Rect(0, 0, 40, 40)); //we assume that the sprites' dimentions are 40*40 rectangles. <--copied from official guide
			//********error spot*************************
			//if (frame!=nullptr)
			animframe.pushBack(frame);


		}
		this->newanimation = Animation::createWithSpriteFrames(animframe, 0.3f);
		AnimationCache::getInstance()->addAnimation(newanimation, "fight");

		runAction(RepeatForever::create( Animate::create(newanimation)));


		Move->setTag(2);
		this->runAction(RepeatForever::create( Move));
		FromStopToMove = true;
		
		//this->addChild(herosprite);
		isMoving = true;
	}
}




void hero::initAniwithPic()
{
	

}

void hero::jumpback()
{
	CCFiniteTimeAction* jumpup = CCMoveBy::create((float)0.2, ccp(-30, 20));
	CCFiniteTimeAction* falldown = CCMoveBy::create((float)0.5, ccp(-24, -20));
	this->runAction(CCSequence::create(jumpup, falldown, NULL));
}

CCRect hero::getrect()
{
	CCRect herorect = CCRectMake(
		this->getPosition().x - (this->getContentSize().width / 2),
		this->getPosition().y - (this->getContentSize().height / 2),
		this->getContentSize().width,
		this->getContentSize().height
		);
	float a = getPosition().x;
	return herorect;

}

void hero::tookdamage(int damage)
{
	HP = HP - damage;
	Health->setValue(HP);
}

int hero::gettype()
{
	return this->herotype;
}
void hero::pause()
{
	Action* test = this->getActionByTag(2);
	this->stopAllActions();
	isMoving = false;
}

void hero::stopfight(){}

int hero::hp(){
	return HP;
}


////////////////////////////////////////never used i guess////////////////////////////////////////////////////////////

bool hero::init()
{
	return true;
}

//void hero::stopByObstacle(){
//	FromMoveToStop = true;
//	FromStopToMove = false;
//
//}
//
//void hero::StartMoveAgain(){
//	FromStopToMove = true;
//	FromMoveToStop = false;
//}

void hero::CheckMoving(float dt){
	if (FromStopToMove){
		//move = MoveBy::create(10, ccp(100, 0));
		//runaction--animate while moving;
		Animation* fight = AnimationCache::getInstance()->getAnimation("fight");
		//this->runAction(RepeatForever::create(move));
		this->runAction(RepeatForever::create(Animate::create( fight)));
		FromStopToMove = false;
		//this->geta
	}
	/*if (FromMoveToStop){
		this->stopAction(move);
		FromMoveToStop = false;
	}*/
}