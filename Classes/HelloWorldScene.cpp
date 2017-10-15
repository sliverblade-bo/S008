#include "HelloWorldScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{

    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();

	auto startItem = MenuItemImage::create(
		"UI/start.png",
		"UI/start1.png",
		CC_CALLBACK_1(HelloWorld::menuStartCallback, this));
	startItem->setAnchorPoint(Vec2(0.5,0.5));
	startItem->setPosition(Vec2(visibleSize.width  / 2,
		visibleSize.height / 4 + 50));

    auto closeItem = MenuItemImage::create(
			"UI/quit.png",
			"UI/quit1.png",
        CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(visibleSize.width / 2,
		visibleSize.height / 4 - 50));


    auto menu = Menu::create(startItem,closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


    auto sprite = Sprite::create("UI/Main.png");
	startItem->setAnchorPoint(Vec2(0.5, 0.5));
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::menuStartCallback(Ref* pSender)
{
    auto scene = GameScene::createScene();
	auto director = Director::getInstance();
    // run
	auto reScene = CCTransitionPageTurn::create(1.0, scene, false);
	CCDirector::sharedDirector()->replaceScene(reScene);

}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
