
#include "GameScene.h"
#include "headers.h";
#include "GameOverScene.h"
#include "TrapHome.h"
#include "rock.h"
#include "PresetObstacleScene.h"
#include "ChooseLevelScene.h"
#include "SimpleAudioEngine.h"
#include "Wood.h"

using namespace cocos2d;
using namespace CocosDenshion;

cocos2d::Vector<Node*> PAPAPA;
Vector<Sprite*> Bullets;
Vector<Sprite*> Arrows;


//static CCPoint s_tCurPos = CCPointZero;
Scene* GameScene::createScene(){
	auto scene = Scene::createWithPhysics();
	//auto scene = Scene::create();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = GameScene::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	layer->setTag(877);
	scene->addChild(layer);
	scene->setTag(878);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	visibleSize.height = visibleSize.height*0.75;
	visibleSize.width = visibleSize.width * 10;
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 6, visibleSize.height / 2+visibleSize.height*0.32));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

	scene->getPhysicsWorld()->setGravity(Vect(0, -98));

	return scene;
}

GameScene::GameScene()
{
	
}


GameScene::~GameScene(void)
{
}

bool GameScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize s = CCDirector::sharedDirector()->getWinSize();
	type = -1;
	//create physical scene in midlayer

	midlayer = ParallaxNode::create();
	this->addChild(midlayer,0,1);
	

	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	//m_pItemMap = CCTMXTiledMap::create("MainMap.tmx");
	////map->getGrid()->set2DProjection();
	//midlayer->addChild(m_pItemMap, 0, 55);

	m_pItemMap = CCSprite::create("Map.png");
	m_pItemMap->setAnchorPoint(CCPointZero);
	//m_pItemMap->setPosition(ccp(s.width*1.5,s.height/2));
	//midlayer->addChild(m_pItemMap, 0, 55);
	midlayer->addChild(m_pItemMap,-1,Point(1,0),CCPointZero);
	

	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(PresetObScene::backScene));
	pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));



	CCMenuItemImage *pCloseItem2 = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(PresetObScene::backScene));
	pCloseItem2->setPosition(ccp(20, 20));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, pCloseItem2, NULL);
	pMenu->setPosition(CCPointZero);

	//CCLayer* buttonLayer = CCLayer::create();
	
	this->addChild(pMenu, 1);
	//this->addChild(buttonLayer);
	
	//_heros = new Array;
	_herosbullets = new Array;
	//_obstaclesbullets = new Array;
	//_obstacles = new Array;
	//_arrows = new Array;

	setObstacles(PAPAPA);

	//AntiBeast* m_grossinio = new AntiBeast();// CCSprite::create();
	//m_grossini = CCSprite::create();
	//m_grossini->addChild(m_grossinio);
	//m_grossinio->setPosition(ccp(-s.width / 4, m_grossinio->getContentSize().height/2));
	//midlayer->addChild(m_grossini);
	//m_grossini->setPosition(ccp(-200, 192));// s.height / 2));
	//
	//CCActionInterval* move_back = move->reverse();
	//CCFiniteTimeAction* pause = CCCallFuncN::create(this, callfuncN_selector(GameScene::stopmoving));
	//CCFiniteTimeAction* seq = CCSequence::create(move, pause, NULL);
	//CCAction* rep = CCRepeatForever::create((CCActionInterval*)seq);
    /*CCActionInterval* move = CCMoveBy::create(1, ccp(s.width * 3.25/30, 0));
	CCAction* moveforever = CCRepeatForever::create((CCActionInterval*)move);
	m_grossini->runAction(moveforever);

	midlayer->runAction(CCFollow::create(m_grossini, CCRectMake(0, 0, s.width * 3, s.height)));*/

	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	///////////the following belongs to Zhoufan He////////////////////////////////////

	
	//this->getObstacles(children);
	this->newcoach =new coach();
	hero* newhero = new hero();
	archer* newarcher = new archer();
	newcoach->setPosition(ccp(s.width / 2, s.height ));
	newhero->setPosition(ccp(s.width*0.2, s.height*0.32));
	Point heroPos = newhero->getPosition();
	newarcher->setPosition(ccp(newhero->getPositionX() - 80, newhero->getPositionY()));
	//this->newcoach->setTag(COACH);                                                                                                                         ///setTag Part
	//newhero->setTag(HERO);
	newarcher->setTag(ARCHER);
//	this->mid_archer = newarcher;
	_arrows = newarcher->getarrow();

	//adding to ccarray;
	_heros.pushBack(newhero);
	_heros.pushBack(newarcher);	
	//_heros->addObject(newcoach);
	//midlayer->addChild(newcoach,-1,Point(1,0),CCPointZero);
	m_pItemMap->addChild(newcoach);
	//CCObject* _he = NULL;
	///newarcher->tookdamage(500);

	auto CloseTree = Sprite::create("trunk.png");

	Size MapSize = m_pItemMap->getContentSize();

	//CloseTree->setPosition(Point(MapSize.width / 4, MapSize.height));

	int TrunkNumber = 5;

	//for (int i = 1; i <= TrunkNumber; i++){                                                                                 ///当midlayer是parallaxNode的时候
	//	auto CloseTree = Sprite::create("trunk.png");

	//	midlayer->addChild(CloseTree, 1, Point(2.0, 0), Point(MapSize.width*i / TrunkNumber, MapSize.height*0.5));

	//	//CloseTree->runAction(CCFollow::create(newcoach, CCRectMake(0, 0, s.width * 3, s.height)));

	//}

	for (size_t i = 0; i < _heros.size(); i++)
	{
		Champions* theone = _heros.at(i);
		//midlayer->addChild(theone, -1, Point(1, 0), CCPointZero);
		m_pItemMap->addChild(theone);
	}
	
	

	//midlayer->runAction(CCFollow::create(this->newcoach, CCRectMake(0, 0, s.width * 3, s.height)));
	m_pItemMap->runAction(CCFollow::create(this->newcoach, CCRectMake(0, 0, s.width * 3, s.height)));

//midlayer->runAction(Follow::create(this->newcoach, CCRectMake(0, 0, s.width * 3, s.height)));
	//trying camera -> discarded
	//Camera* cam =



	//
	moving = true;
	this->schedule(schedule_selector(GameScene::updategame));
    schedule(schedule_selector(GameScene::ObMovBackWards));                                                                             ///////////schedule反向移动的地方
	schedule(schedule_selector(GameScene::rockSimulator));
	schedule(schedule_selector(GameScene::RockHitHero));
	schedule(schedule_selector(GameScene::WoodHitHero));

	//////////////above belongs to Zhoufan He./////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////

	return true;
}

void GameScene::backScene(CCObject* pSender)
{
	CCScene* pTScene = ChooseLevel::scene();
	CCTransitionMoveInL* pChooseLevel = CCTransitionMoveInL::create(1.0f, pTScene);

	CCDirector::sharedDirector()->replaceScene(pChooseLevel);

}

void GameScene::setObstacles(Vector<Node*> children)                                                                              /////////将obstacle加入场景
{
	PresetTrap* child = NULL;
	//CCObject* pObject = NULL;
	//this->getObstacles(children);
	if (children.size() > 1){
		for (int i = 0; i < children.size(); i++){
			child = (PresetTrap*)children.at(i);
			if (!child)
				break;
			//CCPoint position = child->getPosition();
			int type = child->getTrapType();
			//TrapHome* tpHome;
			if (child->getPosition().y >= 32 * 6)
			{
				if (type == ANTI_BEAST)
				{
					AntiBeast* AntiB = new AntiBeast();
					//AntiB->init();
					AntiB->setPosition(child->getPosition());
					m_pItemMap->addChild(AntiB);
					//this->addChild(AntiB);
					//midlayer->addChild(AntiB);
					AntiB->setTag(ANTI_BEAST);
					this->_obstacles.pushBack(AntiB);
				}
				else if (type == FORT)
				{
					Fort* Ft = new Fort();
					//Ft->init();
					Ft->setPosition(child->getPosition());
					Point pt = child->getPosition();
					//Ft->setPhysicsBody(PhysicsBody::createBox(Ft->getContentSize()));
					m_pItemMap->addChild(Ft);
					//this->addChild(Ft);
					//midlayer->addChild(Ft);
					Ft->setTag(FORT);
					this->_obstacles.pushBack(Ft);
				}
				else if (type == ROCK)
				{
					Rock *rock = new Rock();
					rock->setPosition(child->getPosition());
					//Point pt = child->getPosition();
					m_pItemMap->addChild(rock);
					rock->setTag(ROCK);
					_obstacles.pushBack(rock);
				}
				else if (type == TREE){
					Wood *wood = new Wood();
					wood->setPosition(child->getPosition());
					m_pItemMap->addChild(wood);
					wood->setTag(TREE);
					_obstacles.pushBack(wood);
				}
			}

		}
	} 
	
}


//CCARRAY_FOREACH(children, pObject)
//{
//	child = (PresetTrap*)pObject;
//	if (!child)
//		break;
//	//CCPoint position = child->getPosition();
//	int type = child->getTrapType();
//	//TrapHome* tpHome;
//	if (child->getPosition().y >= 32 * 6)
//	{
//		if (type == ANTI_BEAST)
//		{
//			AntiBeast* AntiB = new AntiBeast();	
//			AntiB->init();
//			AntiB->setPosition(child->getPosition());
//			m_pItemMap->addChild(AntiB);
//			AntiB->setTag(ANTI_BEAST);
//			this->_obstacles->addObject(AntiB);
//		}
//		else if (type == FORT)
//		{
//			Fort* Ft = new Fort();
//			//Ft->init();
//			Ft->setPosition(child->getPosition());
//			m_pItemMap->addChild(Ft);
//			Ft->setTag(FORT);
//			this->_obstacles->addObject(Ft);
//		}

//	}
//}


/////////////////////////////////////////////
////////belong to Zhoufan He////////////////////////////////////////

///////////////////Bowen Jiao added/////////////////////
void GameScene::collisionHeroAndObstacle()
{
	for (size_t i = 0; i < _heros.size(); i++)
	{
		Champions* everyhero = _heros.at(i);
		for (size_t i = 0; i < _obstacles.size(); i++)
		{
			Obstacle* obstacle = _obstacles.at(i);
			CCRect obrect = CCRectMake(
				obstacle->getPosition().x - (obstacle->getContentSize().width / 2),
				obstacle->getPosition().y - (obstacle->getContentSize().height / 2),
				obstacle->getContentSize().width,
				obstacle->getContentSize().height
				);
			if (everyhero->getrect().intersectsRect(obrect))
			{
				type = obstacle->getTag();

				switch (type)
				{
				case ANTI_BEAST:
					everyhero->jumpback();
					this->newcoach->jumpback();
					everyhero->tookdamage(obstacle->getattack());
					_obstacles.eraseObject(obstacle, true);
					obstacle->removeFromParentAndCleanup(true);
					break;
				case FORT:
					//hero stop moving
					//CCActionInterval* pause = CCMoveBy::create(1, ccp(0, 0));
					//hero start to fight;
					this->newcoach->pause();
					for (size_t i = 0; i < _heros.size(); i++)
					{
						Champions* eachone = _heros.at(i);
						//fighting = true;
						eachone->pause();                                                                         //////修改的地方
						/*eachone->stopByObstacle();*/
						eachone->fight();

					}
					//_obstacles->removeObject(obstacle, true);
					break;
				default:moving = true; break;
				}
			}
		}
	}
}
/////////////////Bowen Jiao added end//////////////

void GameScene::updategame(float dt)
{
	this->WinOrLose();
	CCObject* _ob = NULL;
	//CCObject* _he = NULL;
	CCSize s = CCDirector::sharedDirector()->getWinSize();
	moving = true;                                                                                                          //////////////////修改的地方
	bool fighting = true;
	bool archerfighting = false;
	//this->_arrows = this->mid_archer->getarrow();
	//char t[5] = { 0 };
	if (this->_obstacles.size() == 0)
	{
		for (size_t i = 0; i < _heros.size(); i++)
		{
			Champions* everyhero = _heros.at(i);
			everyhero->stopfight();

		}
		
	}
	if (this->_heros.size() == 0){ this->WinOrLose(); }


	////////////////////////////////////////////////////////////////////////////////////////
	//// what hero act when contact with obstacles
	for (size_t i = 0; i < _obstacles.size(); i++)
	{
		Obstacle* obstacle = _obstacles.at(i);	
		if (obstacle->getHPValue() <= 0){
			_obstacles.eraseObject(obstacle);
			obstacle->removeFromParentAndCleanup(true);
		}
		else
		{		CCRect obrect = CCRectMake(
				obstacle->getPosition().x - (obstacle->getContentSize().width / 2),
				obstacle->getPosition().y - (obstacle->getContentSize().height / 2),
				obstacle->getContentSize().width,
				obstacle->getContentSize().height
				);
			//CCObject* _everyherocollison = NULL;

			for (size_t i = 0; i < _heros.size(); i++)
			{
				Champions* everyhero = _heros.at(i);
				//everyhero->isfighting = false;
				//everyhero->fight();
				if (!fighting){ everyhero->stopfight(); }
				if (everyhero->getrect().intersectsRect(obrect))
				{
					moving = false;
					type = obstacle->getTag();

					switch (type)
					{
					case ANTI_BEAST:
						everyhero->jumpback();
						this->newcoach->jumpback();
						everyhero->tookdamage(obstacle->getattack());
						_obstacles.eraseObject(obstacle, true);
						obstacle->removeFromParentAndCleanup(true);
						break;
					case FORT:
						//hero stop moving
						//CCActionInterval* pause = CCMoveBy::create(1, ccp(0, 0));
						//hero start to fight;
						this->newcoach->pause();
						for (size_t i = 0; i < _heros.size(); i++)
						{
							Champions* eachone = _heros.at(i);
							fighting = true;
							eachone->pause();                                                                         //////修改的地方
							/*eachone->stopByObstacle();*/
							eachone->fight();

						}
						//_obstacles->removeObject(obstacle, true);
						break;
					default:moving = true; break;
					}
				}
				else
				{
					moving = true;
				}

			}
		}
	}


	//if (!moving){
	//	this->newcoach->stopByObstacle();                                                                /////////////////////////////////////////////coach的移动
	//}
	if (moving){
		this->newcoach->move();                                                                /////////////////////////////////////////////coach的移动
	}

	//hero hit by obstacle bullets
	for (size_t i = 0; i < _heros.size(); i++)
	{
		Champions* eachone = _heros.at(i);
		if(eachone->hp()<=0)
		{
			this->_heros.eraseObject(eachone);
			eachone->removeFromParentAndCleanup(true);
		}
		else
		{
			if (moving){
				eachone->move();                                                          ////////////////////////////////////////////eachone的移动

			}
			for (size_t i = 0; i < Bullets.size(); i++)  //_obstaclesbullets
			{
				Sprite* obstacleb = Bullets.at(i);   //_obstaclesbullets
				if (obstacleb->getPositionX() < 0 || obstacleb->getPositionX() > s.width*3 || obstacleb->getPositionY() < 0 || obstacleb->getPositionY() > s.height)
				{
					//_obstaclesbullets.eraseObject(obstacleb);
					Bullets.eraseObject(obstacleb);
					obstacleb->removeFromParentAndCleanup(true);
					continue;
				}
		
				Rect hero = makeRec(eachone);
				Rect bullet = makeRec(obstacleb);

				if (hero.intersectsRect(bullet))
				{
					//_obstaclesbullets.eraseObject(obstacleb);
					Bullets.eraseObject(obstacleb);
					//eachone->tookdamage(obstacleb->getTag());
					eachone->tookdamage(100);
					obstacleb->removeFromParentAndCleanup(true);
				}
			}
		}



	}
	
	if(!Arrows.empty())    //if (!_arrows.empty())
	{
		for (size_t i = 0; i < _obstacles.size(); i++)
		{
			Obstacle* obstacle = _obstacles.at(i);
			if (obstacle->getTag() == FORT)
			{
				for (size_t i = 0; i < Arrows.size(); i++)
				{
					Sprite* this_arrow = Arrows.at(i);
				
					Rect fort = makeRec(obstacle);
					Rect arrow = makeRec(this_arrow);
					if (arrow.intersectsRect(fort))                                                         ///////////////////////////////////////////////////////////////////////////////////////////
					{
						Arrows.eraseObject(this_arrow);  //this->_arrows
						this_arrow->removeFromParentAndCleanup(true);
						obstacle->minusHP(50);
					}
				}
			}
		}
		//for (size_t i = 0; i < Arrows.size(); i++)  // _arrows
		//{
		//	CCSprite* this_arrow = Arrows.at(i);  // _arrows
		//	for (size_t i = 0; i < _obstacles.size(); i++)
		//	{
		//		Obstacle* obstacle = _obstacles.at(i);
		//		if (obstacle->getTag() == FORT)
		//		{
		//			Rect fort = makeRec(obstacle);
		//			Rect arrow = makeRec(this_arrow);
		//			if (arrow.intersectsRect(fort))                                                         ///////////////////////////////////////////////////////////////////////////////////////////
		//			{
		//				Arrows.eraseObject(this_arrow);  //this->_arrows
		//				this_arrow->removeFromParent();
		//				obstacle->minusHP(50);
		//			}
		//			//Rect arrow = makeRec(this_arrow);
		//			//Rect fort = makeRec(obstacle);
		//			//if (arrow.intersectsRect(fort))                                                         ///////////////////////////////////////////////////////////////////////////////////////////
		//			//{
		//			//	Arrows.eraseObject(this_arrow);  //this->_arrows
		//			//	this_arrow->removeFromParentAndCleanup(true);
		//			//	obstacle->minusHP(50);
		//			//}
		//		}
		//	}
		//}
	}
    /////////////////////////////////////////////////////////////////////////////////////////////




	///archer shoot when in sight
	
	for (size_t i = 0; i < _heros.size(); i++)
	{
		Champions* everyhero = _heros.at(i);
		if (everyhero->getTag() == ARCHER)
		{
			/*CCRect hero_rect = CCRectMake(
				everyhero->getPositionX(),
				0,
				CCDirector::sharedDirector()->getWinSize().width*0.7,
				CCDirector::sharedDirector()->getWinSize().height
				);*/
			for (auto everyobstacle:_obstacles)
			{
				float distance = everyobstacle->getPositionX() - everyhero->getPositionX();
				if (distance > 0 && distance < 0.7*(s.width))
				{
					//everyhero->isfighting = true;
					everyhero->fight();
					break;
				}
				else
					everyhero->stopfight();
				
				//Obstacle* everyobstacle = _obstacles.at(i);
				//if (hero_rect.intersectsRect(everyobstacle->colRec()))                                                                       //everyobstacle->getTag() == FORT
				//{
				//	if (everyobstacle->getTag() == FORT)                                                                             //hero_rect.intersectsRect(everyobstacle->colRec())
				//	{
				//		everyhero->fight();
				//		break;
				//	}
				//	else
				//	{
				//		everyhero->stopfight();
				//		break;
				//	}
					//if (everyobstacle->getTag()==TREE)
				//}
			}
		}
	}




}

//
//void GameScene::getObstacles(CCArray* obstacles)
//{
//	this->_obstacles = obstacles;
//}

void GameScene::stopmoving(CCNode* sender)
{

}

Vector<Sprite*> GameScene::getObstaclesBullets()
{
	return this->_obstaclesbullets;
}

Vector<Sprite*> GameScene::getarrows()
{
	return this->_arrows;
}

void GameScene::WinOrLose()
{
	CCObject* _hr = NULL;
	if (_heros.size() == 0)
	{
		GameOverScene* gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Win!");
		CCDirector::sharedDirector()->replaceScene(gameOverScene);
	}
	for (size_t i = 0; i < _heros.size(); i++)
	{
		Champions* hero = _heros.at(i);
		CCSize winsize = CCDirector::sharedDirector()->getWinSize();
		if (hero->getPositionX() >= (winsize.width * 2 + 896 + (hero->getContentSize().width) / 2 + (hero->getContentSize().width)*(_heros.size() - 1)))
		{
			GameOverScene* gameOverScene = GameOverScene::create();
			gameOverScene->getLayer()->getLabel()->setString("You Lose!");
			CCDirector::sharedDirector()->replaceScene(gameOverScene);
		}
	}
}





	//auto contactListener = EventListenerPhysicsContact::create();

	//contactListener->onContactBegin = CC_CALLBACK_2(GameScene::onContactBegin, this);

	//auto dispatcher = Director::getInstance()->getEventDispatcher();
	//
	//dispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);



bool GameScene::onContactBegin(EventCustom* event, const PhysicsContact& contact){
	auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	if (spriteA->getTag() == 1)
	{
		spriteA->removeFromParentAndCleanup(true);
	}

	if (spriteB->getTag() == 1)
	{
		spriteB->removeFromParentAndCleanup(true);
	}

	return true;
}

void GameScene::ObMovBackWards(float dt){
	ActionInterval* Move = MoveBy::create(dt, ccp(-dt, 0));
	if (moving){
		
		for (auto _obs:_obstacles){
			//_obs->stopAllActions();
			
			_obs->runAction(Move->clone());
		}
		//m_pItemMap->runAction(Move->clone());
	}

}

Rect GameScene::makeRec(Node* object){
	Rect rect = CCRectMake(
		object->getParent()->convertToWorldSpace(object->getPosition()).x - (object->getContentSize().width / 2),
		object->getParent()->convertToWorldSpace(object->getPosition()).y - (object->getContentSize().height / 2),
		object->getContentSize().width,
		object->getContentSize().height);

	//object->get
	return rect;
}

void GameScene::rockSimulator(float dt){
	
	Size visionSize = Director::getInstance()->getVisibleSize();

	for (auto one : _obstacles){
		if (one->getTag() == TREE){
			/*if (one->getPosition().y <= (one->getContentSize().height / 2+visionSize.height*0.32)){
				float velocity = one->getPhysicsBody()->getVelocity().y;
				float vDivide = velocity / 1000000;
			}*/
			for (auto eachHero : _heros){
				if (one->colRec().intersectsRect(eachHero->getrect())){
					float velocity = one->getPhysicsBody()->getVelocity().y;
					float vDivide = velocity / 1000000;
				}
			}



		}
	}

}


void GameScene::RockHitHero(float dt){

	Size visionSize = Director::getInstance()->getVisibleSize();

	for (auto eachObstacle : _obstacles){
		if (eachObstacle->getTag() == ROCK){
			for (auto eachHero : _heros){
				if (eachHero->getrect().intersectsRect(eachObstacle->colRec())){
					float vDivide = eachObstacle->getPhysicsBody()->getVelocity().y;
					if (vDivide <= -270){
						eachHero->tookdamage(eachObstacle->getattack());
					}
				}
			}
			/*if (eachObstacle->getPosition().y <= (eachObstacle->getContentSize().height / 2 + visionSize.height*0.32)){
				auto speed = eachObstacle->getPhysicsBody()->getVelocity().y;
				if (speed < 10 && speed >  -10){
					eachObstacle->getPhysicsBody()->setCollisionBitmask(1);
				}
				
			}*/

		}
	}

}


Rect GameScene::NormalMakeRec(Node* object){
	Rect rect = CCRectMake(
		object->convertToWorldSpace(object->getPosition()).x - (object->getContentSize().width / 2),
		object->convertToWorldSpace(object->getPosition()).y - (object->getContentSize().height / 2),
		object->getContentSize().width,
		object->getContentSize().height);

	//object->get
	return rect;
}

void GameScene::WoodHitHero(float dt){

	Size visionSize = Director::getInstance()->getVisibleSize();
	int JumpBackTag = 333;
	Action* jumpBack = JumpBy::create(0.8, Point(-100, 0), 30, 1);
	//jumpBack->setTag(JumpBackTag);

	for (auto eachObstacle : _obstacles){
		if (eachObstacle->getTag() == TREE){
			for (auto eachHero : _heros){
				Action* TheOnlyJumpBack = jumpBack->clone();
				TheOnlyJumpBack->setTag(JumpBackTag);
				if (eachHero->getrect().intersectsRect(eachObstacle->colRec())){
					float vDivide = eachObstacle->getPhysicsBody()->getVelocity().y;					
					if (vDivide <= -75){
						auto test = eachHero->getActionByTag(JumpBackTag);
						if (test == NULL){
							Action* AnotherJumpBack = jumpBack->clone();
							eachHero->tookdamage(eachObstacle->getattack());
							eachHero->runAction(TheOnlyJumpBack);
						}
						auto coachAction = newcoach->getActionByTag(JumpBackTag);

						if ( coachAction == NULL){
							Action* AnotherJumpBack = jumpBack->clone();
							AnotherJumpBack->setTag(JumpBackTag);
							newcoach->runAction(AnotherJumpBack);
						}
					}
				}
			}
	

		}
	}

}