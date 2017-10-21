#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Runner.h"
#include "Coin.h"
#include "Rock.h"

class HelloWorld : public cocos2d::Layer
{

private:
	cocos2d::TMXTiledMap* map1 = cocos2d::TMXTiledMap::create("map00.tmx");
	cocos2d::TMXTiledMap* map2 = cocos2d::TMXTiledMap::create("map01.tmx");
	int coinsnum = 0;
	char num[8];
	int length = sprintf(num, "%05d", coinsnum);
	Label* coinlabel = Label::createWithTTF(num, "fonts/Marker Felt.ttf", 34);

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	//创建物理世界
	cocos2d::PhysicsWorld* m_world;
	void setPhyWorld(cocos2d::PhysicsWorld* world){
		m_world = world;
	}

	void addcoins1(TMXTiledMap* map);
	void addcoins2(TMXTiledMap* map);
	void addrocks(TMXTiledMap* map);
	void removecoins(TMXTiledMap* map);
	bool onContactBegin(const PhysicsContact& contact);
	void HelloWorld::update(float dt);
	virtual void onEnter();
};

#endif // __HELLOWORLD_SCENE_H__
