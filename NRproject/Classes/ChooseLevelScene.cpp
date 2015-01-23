#include "ChooseLevelScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "PresetObstacleScene.h"

//using namespace cocos2d;
//using namespace CocosDenshion;
USING_NS_CC;
CCScene* ChooseLevel::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	ChooseLevel *layer = ChooseLevel::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool ChooseLevel::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(ChooseLevel::menuCloseCallback));
	pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	//...........go back
	CCMenuItemImage *pBackItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(ChooseLevel::menuBackCallback));
	pBackItem->setPosition(ccp(20, 20));

	// create menu, it's an autorelease object
	CCMenu* pMenu2 = CCMenu::create(pBackItem, NULL);
	pMenu2->setPosition(CCPointZero);
	this->addChild(pMenu2, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label
	CCLabelTTF* pLabel = CCLabelTTF::create("ChooseLevel", "Thonburi", 34);

	// ask director the window size
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	// position the label on the center of the screen
	pLabel->setPosition(ccp(size.width / 2, size.height - 20));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "HelloWorld" splash screen"
	CCSprite* pSprite = CCSprite::create("ChooseLevel.png");

	// position the sprite on the center of the screen
	pSprite->setAnchorPoint(ccp(0, 0));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	return true;
}

void ChooseLevel::menuCloseCallback(CCObject* pSender)
{
	CCScene* pTScene = PresetObScene::scene();
	CCTransitionJumpZoom* pPreset = CCTransitionJumpZoom::create(1.0f, pTScene);
	CCDirector::sharedDirector()->replaceScene(pPreset);

}
void ChooseLevel::menuBackCallback(CCObject* pSender)
{
	CCScene* pTScene = HelloWorld::createScene();
	CCTransitionJumpZoom* pHelloWorld = CCTransitionJumpZoom::create(1.0f, pTScene);
	CCDirector::sharedDirector()->replaceScene(pHelloWorld);

}

