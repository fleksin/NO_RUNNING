#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "archer.h"
#include "AntiBeast.h"
//#include "headers.h";

USING_NS_CC;

//cocos2d::Vector<Node*> PAPAPA;

class coach;

class GameScene : public cocos2d::CCLayer
{
public:


	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
	//GameScene(CCArray* children);
	GameScene();
	virtual ~GameScene(void);
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	//bool init(CCArray* children);
	bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	//static cocos2d::CCScene* scene();
	// implement the "static node()" method manually
	//void menuCloseCallback(CCObject* pSender);
	void backScene(CCObject* pSender);
	void setObstacles(CCArray* children);
	void setObstacles(Vector<Node*> children);
	//void getObstacles(CCArray* obstacles);

	//virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	//virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	//virtual void registerWithTouchDispatcher();
	void updategame(float dt);
	void stopmoving(CCNode* sender);
	//void invisiblemove();
	//CREATE_FUNC(GameScene);
	Vector<Sprite*> getObstaclesBullets();
	Vector<Sprite*> getarrows();
	void WinOrLose();
	void setPhyWorld(PhysicsWorld* world){ m_world = world; }
	//virtual void onEnter();
	bool onContactBegin(EventCustom* event, const PhysicsContact& contact);

	static Scene* createScene();

	//Vector<Node*> children;

	GameScene *layer;

	void ObMovBackWards(float dt);

	Rect makeRec(Node* object);

	void rockSimulator(float dt);

	void RockHitHero(float dt);

	Rect NormalMakeRec(Node* object);

	void WoodHitHero(float dt);

	void collisionHeroAndObstacle();

private:
	PhysicsWorld* m_world;
	Sprite* m_pItemMap;
	Vector<Champions*> _heros;
	Vector<Obstacle*> _obstacles;
	Array* _herosbullets;
	Vector<Sprite*> _obstaclesbullets;
	Vector<Sprite*> _arrows;
	CCSprite* m_grossini;
	//archer* mid_archer;
	int type;
	ParallaxNode* midlayer;
	//Layer* midlayer;
	coach* newcoach;
	bool moving;
	float m_z;

};

#endif // __HELLOWORLD_SCENE_H__
