#include "ChooseLevelScene.h"
#include "PresetObstacleScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "TrapHome.h"
#include "headers.h"


using namespace cocos2d;
using namespace CocosDenshion;

//static CCPoint s_tCurPos = CCPointZero;

CCScene* PresetObScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	PresetObScene *layer = PresetObScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool PresetObScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}
	/*CCLayer* backG = CCLayer::create();
	CCSprite* Map = CCSprite::create("Map.png");
	Map->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width + 640, CCDirector::sharedDirector()->getWinSize().height / 2));
	backG->addChild(Map);
	this->addChild(backG);*/
	/////////////////////////////
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_backMap = CCSprite::create("Map.png");
	m_backMap->setAnchorPoint(CCPointZero);
	//m_backMap->setPosition(ccp(size.width*1.5, size.height / 2));
	//this->addChild(m_backMap, 0);
	
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	m_pItemMap = CCTMXTiledMap::create("MainMap.tmx");
	m_pItemMap->addChild(m_backMap, -1, 56);
	//map->getGrid()->set2DProjection();
	this->addChild(m_pItemMap, 1, 55);
	//this->addChild(block);
	

	/*CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addImage("blocks.png");
	CCTexture2D* textureo = CCTextureCache::sharedTextureCache()->addImage("blockso.png");*/
	TrapHome* tpHome = TrapHome::paddleWithTexture(ANTI_BEAST, 10);
	tpHome->setPosition(ccp(size.width / 6, 100));
	//tpHome->setLabel();
	tpHome->initTrap();
	this->addChild(tpHome,2);

	//texture = CCTextureCache::sharedTextureCache()->addImage("block2.png");
	//textureo = CCTextureCache::sharedTextureCache()->addImage("block2o.png");
	TrapHome* tpHome2 = TrapHome::paddleWithTexture(FORT, 4);
	tpHome2->setPosition(ccp(size.width / 3, 100));
	//tpHome->setLabel();
	tpHome2->initTrap();
	this->addChild(tpHome2,2);

	TrapHome* tpHome3 = TrapHome::paddleWithTexture(ROCK, 2);
	tpHome3->setPosition(ccp(size.width / 2, 100));
	tpHome3->initTrap();
	this->addChild(tpHome3, 2);

	TrapHome* tpHome4 = TrapHome::paddleWithTexture(TREE, 2);
	tpHome4->setPosition(ccp(size.width / 2+200, 100));
	tpHome4->initTrap();
	this->addChild(tpHome4, 2);
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(PresetObScene::menuCloseCallback));
	pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

	// create menu, it's an autorelease object
	//CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	//pMenu->setPosition(CCPointZero);
	//this->addChild(pMenu, 1);

	CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(PresetObScene::backScene));
	pCloseItem2->setPosition(ccp(20, 20));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, pCloseItem2, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	
	this->setTouchEnabled(true);
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [this](Touch *pTouches, Event *pEvent){
	/*	CCSetIterator it = pTouches->();
		CCTouch* touch = (CCTouch*)(*it);?*/
		m_tBeginPos = pTouches->getLocation();
		auto target = static_cast<Sprite*>(pEvent->getCurrentTarget());
		Point locationInNode = target->convertToNodeSpace(pTouches->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		//Check the click area
		if (rect.containsPoint(locationInNode))
		{
			log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
			target->setOpacity(180);
			return true;
		}
		return false;
	};

	listener1->onTouchMoved = [this](Touch *touch, Event *event){
		
		CCPoint touchLocation = touch->getLocation();
		
		float nMoveX = touchLocation.x - m_tBeginPos.x;

		CCPoint curPos = m_pItemMap->getPosition();
		float a = curPos.x;
		CCPoint nextPos = ccp(curPos.x + nMoveX, curPos.y);

		if (nextPos.x > 0.0f)
		{
			m_pItemMap->setPosition(CCPointZero);
			return;
		}

		if (nextPos.x < (CCDirector::sharedDirector()->getWinSize().width - m_pItemMap->getContentSize().width))
		{
			m_pItemMap->setPosition((ccp((CCDirector::sharedDirector()->getWinSize().width - m_pItemMap->getContentSize().width), 0)));
			return;
		}

		m_pItemMap->setPosition(nextPos);
		m_tBeginPos = touchLocation;

	
	};
	//this->registerWithTouchDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this); //m_pItemMap
	//_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1->clone(), tpHome2);

	return true;
}

void PresetObScene::menuCloseCallback(CCObject* pSender)
{
	CCScene *pTScene = CCScene::create();

	//*********this is where everything changes*********
	PAPAPA= m_pItemMap->getChildren();
	//CCArray* children = m_pItemMap->getChildren();    
	
	PAPAPA.erase(0);
	
	/*for (int i = 0; i < children.size(); i++){
		children_array->addObject(children.at(i));
	}*/
	Scene* game = GameScene::createScene();
	pTScene->addChild(game);
	//CCScene* pTScene = GameScene::scene();
	//CCTransitionMoveInL* pGameScene = CCTransitionMoveInL::create(1.0f, pTScene);

	//NotificationCenter::sharedNotificationCenter()->postNotification("Obstacles",&children);

	CCDirector::sharedDirector()->replaceScene(pTScene);

}


void PresetObScene::backScene(CCObject* pSender)
{
	CCScene* pTScene = ChooseLevel::scene();
	CCTransitionMoveInL* pChooseLevel = CCTransitionMoveInL::create(1.0f, pTScene);

	CCDirector::sharedDirector()->replaceScene(pChooseLevel);

}












//********May be useful someday************
//void PresetObScene::7(CCSet *pTouches, CCEvent *pEvent)
//{
//	CCSetIterator it = pTouches->begin();
//	CCTouch* touch = (CCTouch*)(*it);
//
//	m_tBeginPos = touch->getLocation();
//}
//
//void PresetObScene::onTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
//{
//	CCSetIterator it = pTouches->begin();
//	CCTouch* touch = (CCTouch*)(*it);
//	//CCPoint touchLocation = pTouches->getLocation();
//	CCPoint touchLocation = touch->getLocation();
//	float nMoveX = touchLocation.x - m_tBeginPos.x;
//
//	CCPoint curPos = m_pItemMap->getPosition();
//	float a = curPos.x;
//	CCPoint nextPos = ccp(curPos.x + nMoveX, curPos.y);
//
//	if (nextPos.x > 0.0f)
//	{
//		m_pItemMap->setPosition(CCPointZero);
//		return;
//	}
//
//	if (nextPos.x < (CCDirector::sharedDirector()->getWinSize().width - m_pItemMap->getContentSize().width))
//	{
//		m_pItemMap->setPosition((ccp((CCDirector::sharedDirector()->getWinSize().width - m_pItemMap->getContentSize().width), 0)));
//		return;
//	}
//
//	m_pItemMap->setPosition(nextPos);
//	m_tBeginPos = touchLocation;
//}
//void PresetObScene::registerWithTouchDispatcher()
//{
//	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}
/*void HelloWorld::newGame(CCObject* pSender)
{
CCScene* pTScene = ChooseLevel::scene();
CCTransitionRotoZoom* pChooseLevel = CCTransitionRotoZoom::create(1.0f, pTScene);
CCDirector::sharedDirector()->replaceScene(pChooseLevel);
//ChooseLevel *clScene = ChooseLevel::create();
//clScene->getLayer()->getLabel()->setString("You Lose :[");
//CCDirector::sharedDirector()->replaceScene(clScene);
}*/