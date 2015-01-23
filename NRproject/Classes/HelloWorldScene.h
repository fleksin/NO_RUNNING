#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	//set physical world
	void setPhyWorld(cocos2d::PhysicsWorld* world){ m_world = world; }

	//add physical sprite
	void addNewSpriteAtPosition(cocos2d::Point p);

	//add event
	bool onContactBegin(const cocos2d::PhysicsContact& contact);

	//convert from 2.2

	// a selector callback
	//void menuCloseCallback(CCObject* pSender);
	void Mute(CCObject* pSender);
	void setLabel(char* str);


	void newGame(CCObject* pSender);

private:
	cocos2d::PhysicsWorld* m_world;
	cocos2d::CCSize winSize;
	bool isBGMpause;// = false;
	CCLabelTTF* label;

};

#endif // __HELLOWORLD_SCENE_H__
