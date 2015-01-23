#include "TrapHome.h"



TrapHome::TrapHome(int type)
{
	//CCTexture2D* tex;
	this->trapType = type;
	switch (trapType)
	{
	case ANTI_BEAST:texture = TextureCache::sharedTextureCache()->addImage("blocks.png"); break;
	case FORT:texture = TextureCache::sharedTextureCache()->addImage("block2.png"); break;
	case ROCK:texture = TextureCache::sharedTextureCache()->addImage("ball.png"); break;
	case TREE:texture = TextureCache::sharedTextureCache()->addImage("wood.png"); break;
	default:texture = TextureCache::sharedTextureCache()->addImage("blocks.png"); break;
	}
	amounts = 1;
	//initTrap();
}

TrapHome::TrapHome(int amount, int type)                                                                                          //向preset场景底栏里加东西
{
	amounts = amount;
	this->trapType = type;
	switch (trapType)
	{
	case ANTI_BEAST:texture = TextureCache::sharedTextureCache()->addImage("blocks.png"); break;                   
	case FORT:texture = TextureCache::sharedTextureCache()->addImage("block2.png"); break;
	case ROCK:texture = TextureCache::sharedTextureCache()->addImage("ball.png"); break;
	case TREE:texture = TextureCache::sharedTextureCache()->addImage("wood.png"); break;
	default:texture = TextureCache::sharedTextureCache()->addImage("blocks.png"); break;
	}
	//initTrap();
}

TrapHome::~TrapHome(void)
{
}

CCRect TrapHome::rect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

void TrapHome::refreshAmounts()
{
	this->removeChildByTag(21, true);
	char str[10] = { 0 };
	sprintf(str, "%2d", amounts);
	CCLabelTTF* pLabel = CCLabelTTF::create(str, "Thonburi", 34);
	float ax = this->getPosition().x;
	float ay = this->getPosition().y;
	float az = this->rect().size.height / 2;


	pLabel->setPosition(ccp(-(this->rect().size.width / 2), this->rect().size.height / 2));

	// add the label as a child to this layer
	this->addChild(pLabel, 1, 21);
}

void TrapHome::plusAmounts()
{
	amounts++;
	refreshAmounts();
}

void TrapHome::minusAmounts()
{
	amounts--;
	refreshAmounts();
}

int TrapHome::getAmounts()
{
	return amounts;
}

bool TrapHome::initTrap()
{
	if (amounts > 0)
	{
		PresetTrap* initTrap = PresetTrap::paddleWithTexture(texture);
		initTrap->setPosition(ccp(this->getContentSize().width / 2, this->getContentSize().height / 2));//this->getPosition());
		//setTrapHome(initTrap);
		initTrap->setTrapHome(this);
		initTrap->setTrapType(this->trapType);
		refreshAmounts();
		this->addChild(initTrap);
		return true;
	}
	refreshAmounts();
	return false;
}

//void TrapHome::setTrapHome(PresetTrap* Trap)
//{
//	Trap->setTrapHome(this);
//}

bool TrapHome::initWithTexture(int type)
{
	CCTexture2D* aTexture;
	switch (type)
	{
	case ANTI_BEAST:aTexture = TextureCache::sharedTextureCache()->addImage("blockso.png"); break;
	case FORT:aTexture = TextureCache::sharedTextureCache()->addImage("block2o.png"); break;
	case ROCK:aTexture = TextureCache::sharedTextureCache()->addImage("ball.png"); break;
	case TREE:aTexture = TextureCache::sharedTextureCache()->addImage("wood.png"); break;
	default:aTexture = TextureCache::sharedTextureCache()->addImage("blockso.png"); break;
	}
	CCSprite::initWithTexture(aTexture);
	return true;
}

TrapHome* TrapHome::paddleWithTexture(int type, int amount)
{
	TrapHome* traphome = new TrapHome(amount, type);
	traphome->initWithTexture(type);
	traphome->setTag(type);
	//traphome->s
	traphome->autorelease();

	return traphome;
}