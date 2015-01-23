#include "Trap.h"
#include "PresetObstacleScene.h"

//float contentY;
//Sprite *Target;

//int TyPe;

PresetTrap::PresetTrap(void)
{
	ml_state = foward;
	

}

PresetTrap::~PresetTrap(void)
{
}

CCRect PresetTrap::rect()
{
	CCSize s = getTexture()->getContentSize();
	return CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
}

PresetTrap* PresetTrap::paddleWithTexture(CCTexture2D* aTexture)
{
	PresetTrap* presetTrap = new PresetTrap();
	presetTrap->initWithTexture(aTexture);
	Size sz = presetTrap->getContentSize();
	presetTrap->autorelease();


	return presetTrap;
}

bool PresetTrap::initWithTexture(CCTexture2D* aTexture)
{
	if (CCSprite::initWithTexture(aTexture))
	{
		m_state = kPaddleStateUngrabbed;
		//Size sz = this->getContentSize();
	}
	
	return true;
}

void PresetTrap::onEnter()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
//	pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	CCSprite::onEnter();
	this->setListener();
}

void PresetTrap::onExit()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	//pDirector->getTouchDispatcher()->removeDelegate(this);
	CCSprite::onExit();
}

bool PresetTrap::containsTouchLocation(CCTouch* touch)
{
	return rect().containsPoint(convertTouchToNodeSpaceAR(touch));
}





CCObject* PresetTrap::copyWithZone(CCZone *pZone)
{
	this->retain();
	return this;
}



void PresetTrap::touchDelegateRetain()
{
	this->retain();
}

void PresetTrap::touchDelegateRelease()
{
	this->release();
}


void PresetTrap::setTrapHome(TrapHome* Home)
{
	this->tHome = Home;
}

bool PresetTrap::isPositionAvailable()
{
	CCPoint currentPos = ccp(this->getPosition().x + this->tHome->getPosition().x - this->getContentSize().width / 2, this->getPosition().y + this->tHome->getPosition().y - this->getContentSize().height / 2);
	float a = this->getPosition().y;
	float aa = currentPos.y;
	float aaa = this->tHome->getPosition().y;
	float ay = currentPos.y;
	TMXTiledMap* map = (CCTMXTiledMap*)((PresetObScene*)this->tHome->getParent())->getChildByTag(55);
	CCPoint cPosForMap = ccp(currentPos.x - map->getPosition().x, currentPos.y - map->getPosition().y + this->getContentSize().height / 2);
	CCPoint cPosForMapL = ccp(cPosForMap.x - this->getContentSize().width / 2, cPosForMap.y - this->getContentSize().height / 2);
	CCPoint cPosForMapR = ccp(cPosForMap.x + this->getContentSize().width / 2, cPosForMap.y - this->getContentSize().height / 2);
	CCPoint cPosForMapB = ccp(cPosForMap.x, cPosForMap.y - this->getContentSize().height);

	/*if (cPosForMapL.x < 0 || cPosForMapR.x > map->getContentSize().width || cPosForMap.y > map->getContentSize().height || cPosForMapB.y < 0)
		return false;*/
	float b = cPosForMap.x;
	float by = cPosForMap.y;
	CCTMXLayer* bcgrd = map->layerNamed("backGround");
	CCPoint tiledPos = tileCoordForPosition(cPosForMap);
	CCPoint tiledPosL = tileCoordForPosition(cPosForMapL);
	CCPoint tiledPosR = tileCoordForPosition(cPosForMapR);
	CCPoint tiledPosB = tileCoordForPosition(cPosForMapB);
	float c = tileCoordForPosition(cPosForMapB).x;
	float cy = tileCoordForPosition(cPosForMapB).y;
	
	if (tiledPosL.x <= 0 || tiledPosR.x >= bcgrd->getLayerSize().width || tiledPosB.y >= bcgrd->getLayerSize().height || tiledPos.y <= 0)
		return false;

	int tiledGid = bcgrd->tileGIDAt(tiledPos);
	int tiledGidL = bcgrd->tileGIDAt(tiledPosL);
	int tiledGidR = bcgrd->tileGIDAt(tiledPosR);
	int tiledGidB = bcgrd->tileGIDAt(tiledPosB);

	float cby = tileCoordForPosition(cPosForMapB).y;


	if (tiledGid * tiledGidL * tiledGidR * tiledGidB != 0)
	{
		
		Value propertiesDict = map->propertiesForGID(tiledGid);

		ValueMap getMap = propertiesDict.asValueMap();

		auto prop = getMap.at("Avalible").asString();		
		//propertiesDict = map->propertiesForGID(tiledGidL);

		getMap = map->propertiesForGID(tiledGidL).asValueMap();
		auto propL = getMap.at("Avalible").asString() ;

		//propertiesDict = map->propertiesForGID(tiledGidR);
		getMap = map->propertiesForGID(tiledGidR).asValueMap();
		auto propR = getMap.at("Avalible").asString();

		//propertiesDict = map->propertiesForGID(tiledGidB);
		getMap = map->propertiesForGID(tiledGidB).asValueMap();
		auto propB = getMap.at("Avalible").asString();

		if ((prop.compare("false"))*(propL.compare("false"))*(propR.compare("false"))*(propB.compare("false")) == 0)
		{
			return false;
		}
	}
	else
	{
		return false;
	}



	return true;
}

CCPoint PresetTrap::tileCoordForPosition(CCPoint pos)
{
	CCTMXTiledMap* map = (CCTMXTiledMap*)((PresetObScene*)this->tHome->getParent())->getChildByTag(55);
	CCSize mapTiledNum = map->getMapSize();
	CCSize tiledSize = map->getTileSize();

	int x = pos.x / tiledSize.width;
	//float y = pos.y / tiledSize.height;

	int y = mapTiledNum.height - pos.y / tiledSize.height;

	return ccp(x, y);
}

int PresetTrap::getTrapType()
{
	return trapType;
}

void PresetTrap::setTrapType(int tp)
{
	this->trapType = tp;
}

void PresetTrap::setListener(){
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(PresetTrap::onTouchBegan, this);
	listener1->onTouchMoved = CC_CALLBACK_2(PresetTrap::onTouchMoved, this);

	listener1->onTouchEnded = CC_CALLBACK_2(PresetTrap::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
}

void PresetTrap::AdjustPosition(float dt){
	if (this != NULL){

	}

}

void PresetTrap::onTouchEnded(Touch* touch, Event* event)
{
	//	CCAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");
	//float a = convertToWorldSpace(this->getPosition()).x;
	//float fff = touch->getLocation().x;
	CCTMXTiledMap* temp = (CCTMXTiledMap*)((PresetObScene*)this->tHome->getParent())->getChildByTag(55);//->addChild(this);
	CCTMXLayer* bcgrd = temp->layerNamed("backGround");
	auto test1 = event->getCurrentTarget();

	if (ml_state != back)
	{
		if (isPositionAvailable())
		{
			m_state = kPaddleStateGrabbed;
			this->tHome->minusAmounts();
			this->tHome->initTrap();

			//this->removeFromParentAndCleanup(false);
			//auto *target = static_cast<Sprite*>(event->getCurrentTarget());

			//Size sz2 = Target->getContentSize();
			//Target->setPosition(ccp(touch->getLocation().x - temp->getPosition().x, 192));//touch->getLocation().y));//

			//int t = getTag();
			PresetTrap* newTrap = paddleWithTexture(this->getTexture());
			newTrap->ml_state = back;
			newTrap->m_state = kPaddleStateUngrabbed;
			newTrap->trapType = this->trapType;
			newTrap->tHome = this->tHome;
			
			Point TrapPos;

			switch (trapType)                                                                                                         //////////////////////obstacle摆放位置的变化
			{
			case(ROCK) : TrapPos=(ccp(touch->getLocation().x - temp->getPosition().x, newTrap->getContentSize().height / 2 + 600)); break;
			default:TrapPos = (ccp(touch->getLocation().x - temp->getPosition().x, newTrap->getContentSize().height / 2 + 192));
				break;
			}
			
		
			newTrap->setPosition(TrapPos);
			temp->addChild(newTrap, 2, trapType);
			//prt->removeChild(this, false);
			

			//Point pt = this->getPosition();

			CCPoint cPosition = newTrap->getPosition();
			CCPoint currentTilePosition = tileCoordForPosition(cPosition);
			int wiStart = tileCoordForPosition(ccp(cPosition.x - newTrap->getContentSize().width / 2, cPosition.y)).x;
			int wiEnd = tileCoordForPosition(ccp(cPosition.x + newTrap->getContentSize().width / 2, cPosition.y)).x;
			newTrap->originalGid = bcgrd->tileGIDAt(ccp(wiStart, 5));

			for (int wi = wiStart; wi <= wiEnd; wi++)
			{
				for (int hi = 5; hi < 17; hi++)
				{
					bcgrd->removeTileAt(ccp(wi, hi));
				}
			}
			this->removeFromParentAndCleanup(true);

		}
		else
		{
			this->tHome->initTrap();
			this->removeFromParentAndCleanup(true);

		}
	}
	else
	{
		m_state = kPaddleStateGrabbed;
		this->tHome->plusAmounts();
		if (this->tHome->getAmounts() == 1)
			this->tHome->initTrap();
		CCPoint cPosition = this->getPosition();
		CCPoint currentTilePosition = tileCoordForPosition(cPosition);
		int wiStart = tileCoordForPosition(ccp(cPosition.x - this->getContentSize().width / 2, cPosition.y)).x;
		int wiEnd = tileCoordForPosition(ccp(cPosition.x + this->getContentSize().width / 2, cPosition.y)).x;
		for (int wi = wiStart; wi <= wiEnd; wi++)
		{
			for (int hi = 5; hi < 17; hi++)
			{
				bcgrd->setTileGID(originalGid, ccp(wi, hi));
			}
		}

		this->removeFromParentAndCleanup(true);
	}
}

bool PresetTrap::onTouchBegan(Touch* touch, Event* event)
{
	//target = static_cast<Sprite*>(event->getCurrentTarget());

	//Size sz = Target->getContentSize();
	if (m_state != kPaddleStateUngrabbed) return false;
	if (!containsTouchLocation(touch)) return false;

	auto *target = static_cast<Sprite*>(event->getCurrentTarget());
	

	m_state = kPaddleStateGrabbed;
	return true;
}

void PresetTrap::onTouchMoved(Touch* touch, Event* event)
{
	// If it weren't for the TouchDispatcher, you would need to keep a reference
	// to the touch from touchBegan and check that the current touch is the same
	// as that one.
	// Actually, it would be even more complicated since in the Cocos dispatcher
	// you get CCSets instead of 1 UITouch, so you'd need to loop through the set
	// in each touchXXX method.

	//	CCAssert(m_state == kPaddleStateGrabbed, L"Paddle - Unexpected state!");
	auto* Target = static_cast<Sprite*>(event->getCurrentTarget());
	Size sz3 = Target->getContentSize();
	//int TyPe = Target->getTag();
	if (ml_state != back)
	{
		CCPoint touchPoint = touch->getLocation();
		//setAnchorPoint(ccp(touchPoint.x - this->tHome->getPosition().x, touchPoint.y - this->tHome->getPosition().y));
		//setPosition(ccp(touchPoint.x - this->tHome->getPosition().x, touchPoint.y - this->tHome->getPosition().y));
		setPosition(ccp(touchPoint.x - this->tHome->getPosition().x + this->getContentSize().width / 2, touchPoint.y - this->tHome->getPosition().y + this->getContentSize().height / 2));
		if (!isPositionAvailable())
		{
			//this->getTexture()->getName();
			CCTexture2D* aTexture;
			switch (trapType)
			{
			case ANTI_BEAST:aTexture = TextureCache::sharedTextureCache()->addImage("blocksb.png"); break;
			case FORT:aTexture = TextureCache::sharedTextureCache()->addImage("block2b.png"); break;
			case ROCK:aTexture = TextureCache::sharedTextureCache()->addImage("ball.png"); break;
			case TREE:aTexture = TextureCache::sharedTextureCache()->addImage("wood.png"); break;
			default:aTexture = TextureCache::sharedTextureCache()->addImage("blocksb.png"); break;
			}
			this->setTexture(aTexture);
		}
		else
		{
			CCTexture2D* aTexture;
			switch (trapType)
			{
			case ANTI_BEAST:aTexture = TextureCache::sharedTextureCache()->addImage("blocks.png"); break;
			case FORT:aTexture = TextureCache::sharedTextureCache()->addImage("block2.png"); break;
			case ROCK:aTexture = TextureCache::sharedTextureCache()->addImage("ball.png"); break;
			case TREE:aTexture = TextureCache::sharedTextureCache()->addImage("wood.png"); break;
			default:aTexture = TextureCache::sharedTextureCache()->addImage("blocks.png"); break;
			}
			this->setTexture(aTexture);
		}

	}
}