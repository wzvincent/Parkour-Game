#include "Runner.h"

bool Runner::init(){
	Sprite::init();

	//创建runner
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("running.plist", "running.png");
	int bodyWidth = Sprite::createWithSpriteFrameName("runner0.png")->getContentSize().width;
	int bodyHeight = Sprite::createWithSpriteFrameName("runner0.png")->getContentSize().height;
	this->setTag(1);

	//创建物理对象
	auto runner0 = Sprite::createWithSpriteFrameName("runner0.png");
	auto Phyrunner = PhysicsBody::createBox(Size(runner0->getContentSize().width, runner0->getContentSize().height), PHYSICSBODY_MATERIAL_DEFAULT);
	Phyrunner->getShape(0)->setRestitution(0.0f);
	Phyrunner->getShape(0)->setFriction(0.0f);
	Phyrunner->getShape(0)->setDensity(1.0f);
	Phyrunner->getShape(0)->setMass(1);
	Phyrunner->setRotationEnable(false);
	Phyrunner->setCategoryBitmask(0x0001);
	Phyrunner->setCollisionBitmask(0x0001);
	Phyrunner->setContactTestBitmask(0x0001);
	setPhysicsBody(Phyrunner);

	this->run();

	scheduleUpdate();

	return true;
}

void Runner::run(){
	position = 0;

	//加载动画
	Vector<SpriteFrame*> animFrames;
	for (int i = 0; i < 8; i++)
	{
		char name[100] = { 0 };
		sprintf(name, "runner%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animFrames.pushBack(frame);
	}
	auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	auto animateAction = Animate::create(animation);
	auto rep = RepeatForever::create(animateAction);

	runAction(rep);
}

void Runner::runnerJumpup(){

	if (position == 0)
	{
		position = 1;
	}

	Vector<SpriteFrame*> animJumpUp;
	for (int i = 0; i < 4; i++)
	{
		char name[100] = { 0 };
		sprintf(name, "runnerJumpUp%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animJumpUp.pushBack(frame);
	}

	auto JumpUp = Animation::createWithSpriteFrames(animJumpUp, 0.1f);
	auto JumpUpAction = Animate::create(JumpUp);

	stopAllActions();
	this->getPhysicsBody()->applyImpulse(Vec2(0, 250.0f));
	runAction(JumpUpAction);
}

void Runner::runnerJumpdown(){

	if (position == 1)
	{
		position = 2;
	}

	Vector<SpriteFrame*> animJumpDown;
	for (int i = 0; i < 2; i++)
	{
		char name[100] = { 0 };
		sprintf(name, "runnerJumpDown%d.png", i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
		animJumpDown.pushBack(frame);
	}

	auto JumpDown = Animation::createWithSpriteFrames(animJumpDown, 0.2f);
	auto JumpDownAction = Animate::create(JumpDown);
	stopAllActions();
	runAction(JumpDownAction);
}

void Runner::update(float dt){
	//log("%d",position);
	switch (position)
	{
	case 1 :
		if (this->getPhysicsBody()->getVelocity().y < 0.01)
		{
			this->runnerJumpdown();
		}
		   break;
	case 2 :
		if (this->getPhysicsBody()->getVelocity().y > -0.01)
		{
			this->run();
		}
			break;
	}
}