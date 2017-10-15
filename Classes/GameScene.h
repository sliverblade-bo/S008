#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	Sprite* timeAxis;
	Sprite* nowCard;
	Sprite* textBackground;

	Menu* mainButtons;

	void button1Callback(cocos2d::Ref* pSender);

	void button2Callback(cocos2d::Ref* pSender);

	void button3Callback(cocos2d::Ref* pSender);
};
