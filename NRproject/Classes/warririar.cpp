#include "warririar.h"

Warriar::Warriar()
{
	this->setTag(WARRIAR);
	SpriteBatchNode* spritebatch = SpriteBatchNode::create("grossini.png");
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("grossini.plist");

	Sprite::initWithSpriteFrameName("grossini_dance_00.png");
	
	//now is the 3.0 version
	this->addChild(spritebatch);
	Vector<SpriteFrame*> animframe = Vector<SpriteFrame*>::Vector();
	char str[100] = { 0 };
	for (int i = 0; i < 5; i++)
	{
		//animframe->addObject(frame);*/
		sprintf(str, "grossini_dance_%02d.png", i);

		//*CCString* filename = CCString::createWithFormat("grossini_dance_%02d.png", i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);

		//auto frame = SpriteFrame::create(str, Rect(0, 0, 40, 40)); //we assume that the sprites' dimentions are 40*40 rectangles. <--copied from official guide
		//********error spot*************************
		if (frame != nullptr)
			animframe.pushBack(frame);
	}
	Animation* newanimation = Animation::createWithSpriteFrames(animframe, 0.9f);
	AnimationCache::sharedAnimationCache()->addAnimation(newanimation, "fight");
}

Warriar::~Warriar()
{
}

void Warriar::fight(){

	Animation* fight = AnimationCache::sharedAnimationCache()->animationByName("fight");

	Fight = Animate::create(fight);

	this->runAction(Fight);
}

void Warriar::stopfight(){
	this->stopAction(Fight);
	
}