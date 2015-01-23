#include "HelloWorldScene.h"
#include "ChooseLevelScene.h"
#include "SimpleAudioEngine.h"


using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	isBGMpause = false;

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	pCloseItem->setPosition(ccp(size.width / 5, size.height / 5));

	CCSprite* newGameNormal = CCSprite::create("MenuButton.png", CCRectMake(0, 0, 126, 33));
	CCSprite* newGameSelected = CCSprite::create("MenuButton.png", CCRectMake(0, 33, 126, 33));
	CCSprite* newGameDisabled = CCSprite::create("MenuButton.png", CCRectMake(0, 33 * 2, 126, 33));

	CCSprite* Setting = CCSprite::create("MenuButton.png", CCRectMake(127, 0, 126, 33));
	CCSprite* SettingSelected = CCSprite::create("MenuButton.png", CCRectMake(127, 33, 126, 33));
	CCSprite* SettingDisabled = CCSprite::create("MenuButton.png", CCRectMake(127, 33 * 2, 126, 33));

	CCMenuItemSprite* newGame = CCMenuItemSprite::create(newGameNormal, newGameSelected, newGameDisabled, this, menu_selector(HelloWorld::newGame));
	CCMenuItemSprite* Option = CCMenuItemSprite::create(Setting, SettingSelected, SettingDisabled, this, menu_selector(HelloWorld::Mute));

    // create menu, it's an autorelease object
    CCMenu* menu = CCMenu::create(newGame, Option, pCloseItem, NULL);
	menu->alignItemsVerticallyWithPadding(10);
	this->addChild(menu, 1, 2);
	menu->setPosition(ccp(size.width / 2, size.height / 2 - 80));
    //pMenu->setPosition( CCPointZero );
    //this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	/*int a = 8;
	char time[10] = { 0 };
	sprintf(time, "%2d",a);*/
    label = CCLabelTTF::create("FAQ", "Thonburi", 34);

    // ask director the window size
    //CCSize size = CCDirector::sharedDirector()->getWinSize();

    // position the label on the center of the screen
    label->setPosition( ccp(size.width / 2, size.height - 20) );

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    //pSprite->setPosition( ccp(size.width/2, size.height/2) );
	pSprite->setAnchorPoint(ccp(0, 0));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0, 1);
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("happy.mp3", true);
   
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	//CCScene* pTScene = ChooseLevel::scene();
	//CCTransitionRotoZoom* pChooseLevel = CCTransitionRotoZoom::create(3.0f, pTScene);
	CCDirector::sharedDirector()->end();
	//ChooseLevel *clScene = ChooseLevel::create();
	//clScene->getLayer()->getLabel()->setString("You Lose :[");
	//CCDirector::sharedDirector()->replaceScene(clScene);

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::newGame(CCObject* pSender)
{
	CCScene* pTScene = ChooseLevel::scene();
	CCTransitionRotoZoom* pChooseLevel = CCTransitionRotoZoom::create(1.0f, pTScene);
	CCDirector::sharedDirector()->replaceScene(pChooseLevel);
	//ChooseLevel *clScene = ChooseLevel::create();
	//clScene->getLayer()->getLabel()->setString("You Lose :[");
	//CCDirector::sharedDirector()->replaceScene(clScene);
}

void HelloWorld::Mute(CCObject* pSender)
{
	if (!isBGMpause)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		isBGMpause = true;
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		isBGMpause = false;
	}
}

void HelloWorld::setLabel(char* str)
{
	this->label->setString(str);
}