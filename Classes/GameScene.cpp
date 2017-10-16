#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    
	auto sprite = Sprite::create("UI/main.png");
	sprite->setAnchorPoint(Vec2(0.5, 0.5));
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(sprite, 0);

	this->timeAxis = Sprite::create("UI/timeAxis.png");
	this->timeAxis->setAnchorPoint(Vec2(0.5, 0.5));
	this->timeAxis->setPosition(Vec2(375, 1234));
	this->addChild(timeAxis, 1);

	this->nowCard = Sprite::create("Cards/01/Cards.png");
	this->nowCard->setAnchorPoint(Vec2(0.5, 0.5));
	this->nowCard->setPosition(Vec2(375, 814));
	this->addChild(nowCard, 1);

	this->textBackground = Sprite::create("UI/textBackground.png");
	this->textBackground->setAnchorPoint(Vec2(0.5, 0.5));
	this->textBackground->setPosition(Vec2(375, 274));
	this->addChild(textBackground, 1);

	auto button1 = MenuItemImage::create(
		"UI/button1Up.png",
		"UI/button1Down.png",
		CC_CALLBACK_1(GameScene::button1Callback, this));
	button1->setAnchorPoint(Vec2(0.5, 0.5));
	button1->setPosition(Vec2(40,
		44));

	auto button2 = MenuItemImage::create(
		"UI/button2Up.png",
		"UI/button2Down.png",
		CC_CALLBACK_1(GameScene::button2Callback, this));

	button2->setAnchorPoint(Vec2(0.5, 0.5));
	button2->setPosition(Vec2(710,
		44));

	auto button3 = MenuItemImage::create(
		"UI/button3Up.png",
		"UI/button3Down.png",
		CC_CALLBACK_1(GameScene::button3Callback, this));

	button3->setAnchorPoint(Vec2(0.5, 0.5));
	button3->setPosition(Vec2(375,
		44));

	this->mainButtons = Menu::create(button1, button2, button3, NULL);
	mainButtons->setPosition(Vec2::ZERO);
	this->addChild(mainButtons, 1);
	
	auto myListener = EventListenerTouchOneByOne::create();
	myListener->setSwallowTouches(true);
	myListener->onTouchBegan = [=](Touch* touch, Event* event)->bool
	{
		Vec2 location = touch->getLocation();
		this->startDragCard(location);
		return true;
	};

	myListener->onTouchMoved = [=](Touch* touch, Event* event)->bool
	{
		Vec2 location = touch->getLocation();
		this->dragCard(location);
		return true;
	};

	myListener->onTouchEnded = [=](Touch* touch, Event* event)->bool
	{
		Vec2 location = touch->getLocation();
		this->endDragCard(location);
		return true;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(myListener, this);
	this->scheduleUpdate();

	return true;
}

void GameScene::button1Callback(cocos2d::Ref* pSender) {}

void GameScene::button2Callback(cocos2d::Ref* pSender) {}

void GameScene::button3Callback(cocos2d::Ref* pSender) {}

void GameScene::update(float dt) {}

void GameScene::startDragCard(Vec2 location) {
	Rect rect = Rect(this->nowCard->getPosition().x, this->nowCard->getPosition().y, this->nowCard->getContentSize().width, this->nowCard->getContentSize().height);
	if (this->nowCard->getBoundingBox().containsPoint(location)) {
		this->isCardDrag = true;
		this->dragStartPositon = location;
		this->dragCard(location);
	}
}

void GameScene::dragCard(Vec2 location) {
	if (this->isCardDrag) {
		float dragX = dragStartPositon.x - location.x;
		float dragY = dragStartPositon.y - location.y;
		
		if (dragX > 50) {
			dragX = 50;
		}
		else if (dragX < -50) {
			dragX = -50;
		}
		if (dragY > 50) {
			dragY = 50;
		}
		else if (dragY < -50) {
			dragY = -50;
		}
		this->nowCard -> setPosition(Vec2(375 - dragX, 814 - dragY));
	}
}


void GameScene::endDragCard(Vec2 location) {
	this->nowCard->setPosition(Vec2(375, 814));
	this->isCardDrag = false;
}