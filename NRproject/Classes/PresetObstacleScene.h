 #ifndef __PRESET_OBSTACLE_SCENE_H__
#define __PRESET_OBSTACLE_SCENE_H__

#include "cocos2d.h"
//#include "headers.h"

USING_NS_CC;

#define ANTI_BEAST 0
#define ROCK 1
#define TREE 2
#define WOLF 3
#define MONSTER 4
#define FORT 5

extern cocos2d::Vector<Node*> PAPAPA;

class PresetObScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	// implement the "static node()" method manually
	void menuCloseCallback(CCObject* pSender);
	void backScene(CCObject* pSender);

	/* void onTouchesBegan(__Set *pTouches, Event *pEvent);
	void onTouchesMoved(__Set *pTouches, Event *pEvent);*/
	//virtual void registerWithTouchDispatcher();
	
	CREATE_FUNC(PresetObScene);

	//Vector<Node*> getObstacles();

private:
	CCPoint m_tBeginPos;
	CCTMXTiledMap* m_pItemMap;
	CCSprite* m_backMap;
	//Vector<Node*> children;
};

#endif // __HELLOWORLD_SCENE_H__
