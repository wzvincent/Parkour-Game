#include "Coin.h"

bool Coin::init(){
	Sprite::init();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist", "background.png");
	int coinbodyWidth = Sprite::createWithSpriteFrameName("coin0.png")->getContentSize().width;

	//创建物理对象
	auto Phycoin = PhysicsBody::createCircle(coinbodyWidth / 2, PHYSICSBODY_MATERIAL_DEFAULT);
	Phycoin->getShape(0)->setRestitution(1.0f);
	Phycoin->getShape(0)->setFriction(0.0f);
	Phycoin->getShape(0)->setDensity(1.0f);
	Phycoin->setGravityEnable(false);
	Phycoin->setCategoryBitmask(0x0001);
	Phycoin->setCollisionBitmask(0x0010);
	Phycoin->setContactTestBitmask(0x0001);
	setPhysicsBody(Phycoin);
	setTag(2);

	//加载金币动画
	Vector<SpriteFrame*> anims;
	for (int i = 0; i < 8; i++)
	{
		char name[100] = { 0 };
		sprintf(name, "coin%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		anims.pushBack(frame);
	}

	auto animation = Animation::createWithSpriteFrames(anims, 0.15f);
	auto animateAction = Animate::create(animation);
	auto rep = RepeatForever::create(animateAction);

	runAction(rep);

	return true;
}
