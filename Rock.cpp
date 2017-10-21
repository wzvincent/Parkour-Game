#include "Rock.h"

bool Rock::init(){
	Sprite::init();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("background.plist", "background.png");
	auto s = Sprite::createWithSpriteFrameName("rock.png");
	this->createWithSpriteFrameName("rock.png");
	this->setTag(3);

	//创建物理对象
	log("<<<<<<<<<<<<<<<<<<<<<<<<Rock : %d", this->getContentSize().width);
	auto PhyRock = PhysicsBody::createBox(s->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	PhyRock->setDynamic(false);
	PhyRock->setCategoryBitmask(0x0001);
	PhyRock->setCollisionBitmask(0x0010);
	PhyRock->setContactTestBitmask(0x0001);
	setPhysicsBody(PhyRock);

	Vector<SpriteFrame*> anims;
	char name[100] = { 0 };
	sprintf(name, "rock.png");
	auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
	anims.pushBack(frame);

	auto animation = Animation::createWithSpriteFrames(anims, 0.15f);
	auto animateAction = Animate::create(animation);

	runAction(animateAction);

	return true;
}
