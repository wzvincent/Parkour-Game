#include "cocos2d.h"
#ifndef __PARKOUR__RUNNER__
#define __PARKOUR__RUNNER__

USING_NS_CC;

class Runner : public Sprite
{
private:
	int position = 0;

public:
	virtual bool init();
	CREATE_FUNC(Runner);

	int getposition(){
		return position;
	}

	void run();
	void runnerJumpup();
	void runnerJumpdown();

	void update(float dt) override;
};

#endif