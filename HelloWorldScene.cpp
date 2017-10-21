#include "HelloWorldScene.h"
#include <string>

USING_NS_CC;
using namespace std;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0,-250));
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

	layer->setPhyWorld(scene->getPhysicsWorld());

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
    if ( !Layer::init() )
    {
        return false;
    }

	//设置屏幕分辨率适配
	auto director = Director::getInstance();
	director->setContentScaleFactor(map1->getContentSize().height / 320);
	director->getOpenGLView()->setDesignResolutionSize(480, 320, ResolutionPolicy::FIXED_HEIGHT);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	addChild(coinlabel,2);
	coinlabel->setTag(4);
	coinlabel->setPosition(visibleSize / 2);

	//加载地图
	addChild(map1);
	addChild(map2);
	map2->setPositionX(map1->getContentSize().width);
	scheduleUpdate();

	//创建物理边界
	auto edge = Node::create();
	auto edgeBody = PhysicsBody::createEdgeBox(Size(99999999,visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT);
	edge->setPhysicsBody(edgeBody);
	edge->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 64));
	addChild(edge);

	//创建Runner
	auto runner = Runner::create();
	runner->setPosition(100, 92 + runner->getContentSize().height / 2);
	addChild(runner);

	//创建触摸事件
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [runner](Touch *t,Event *e){
		int station = runner->getposition();
		if (station == 0)
		{
			runner->runnerJumpup();
		}
		return false;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//加载地图和石块
	addcoins1(map1);
	addcoins2(map2);
	addrocks(map1);
	addrocks(map2);

    return true;
}

void HelloWorld::update(float dt){
	//地图循环滚动
	map1->setPositionX(map1->getPositionX() - 2);
	map2->setPositionX(map2->getPositionX() - 2);

	if (map1->getPositionX() == -(map1->getContentSize().width))
	{
		map1->setPositionX(map2->getContentSize().width);
		removecoins(map1);
		addcoins1(map1);
	}

	if (map2->getPositionX() == -(map2->getContentSize().width))
	{
		map2->setPositionX(map1->getContentSize().width);
		removecoins(map2);
		addcoins1(map2);
	}
}

void HelloWorld::addcoins1(TMXTiledMap* map){
	auto coins = map->getObjectGroup("coin");
	auto objects = coins->getObjects();
	for (ValueVector::iterator it = objects.begin(); it != objects.end(); it++)
	{
		auto obj = *it;
		ValueMap cc = obj.asValueMap();
		auto coin = Coin::create();

		map->addChild(coin);
		int x = cc["x"].asInt();
		int y = cc["y"].asInt();
		coin->setPosition(x, y);

		log("x = %d , y = %d", x, y);
	}
}

void HelloWorld::addcoins2(TMXTiledMap* map){
	auto coins = map->getObjectGroup("coin");
	auto objects = coins->getObjects();
	for (ValueVector::iterator it = objects.begin(); it != objects.end(); it++)
	{
		auto obj = *it;
		ValueMap cc = obj.asValueMap();
		auto coin = Coin::create();

		map->addChild(coin);
		int x = cc["x"].asInt();
		int y = cc["y"].asInt();
		coin->setPosition(x + map1->getContentSize().width, y);

		log("x = %d , y = %d", x, y);
	}
}

void HelloWorld::removecoins(TMXTiledMap* map){
	for (int i = 0; i < 8; i++)
	{
		map->removeChildByTag(2);
	}
}

void HelloWorld::addrocks(TMXTiledMap* map){
	auto rockobj = map->getObjectGroup("rock")->getObjects().begin();
	auto rock = Rock::create();
	map->addChild(rock);
	if (map == map1)
	{
		rock->setPosition(rockobj->asValueMap()["x"].asInt(), rockobj->asValueMap()["y"].asInt());
	}
	else if (map == map2)
	{
		rock->setPosition(rockobj->asValueMap()["x"].asInt() + map1->getContentSize().width, rockobj->asValueMap()["y"].asInt());
	}
	
}

void HelloWorld::onEnter(){
	Layer::onEnter();

	auto contactListener = EventListenerPhysicsContact::create();
	//设置监听器的碰撞开始函数  
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	//添加到事件分发器中  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	Sprite* spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	int tagA = spriteA->getTag();
	int tagB = spriteB->getTag();

	if (tagA == 1 && tagB == 2)
	{
		spriteB->removeFromParent();
		coinsnum++;
		length = sprintf(num, "%05d", coinsnum);
		this->removeChildByTag(4);
		coinlabel = Label::createWithTTF(num, "fonts/Marker Felt.ttf", 34);
		addChild(coinlabel);
		coinlabel->setPosition(visibleSize / 2);
		coinlabel->setTag(4);
	}
	else if (tagA == 2 && tagB == 1)
	{
		spriteA->removeFromParent();
		coinsnum++;
		length = sprintf(num, "%05d", coinsnum);
		this->removeChildByTag(4);
		coinlabel = Label::createWithTTF(num, "fonts/Marker Felt.ttf", 34);
		addChild(coinlabel);
		coinlabel->setPosition(visibleSize / 2);
		coinlabel->setTag(4);
	}

	if (tagA == 3 || tagB == 3)
	{
		MessageBox("Game Over", "游戏提示");
		log("Game Over");
	}

	return true;
}

