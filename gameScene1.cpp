#include "gameScene1.h"
#include "PauseScene1.h"

#include <physics3d/CCPhysics3DObject.h>
#include "cocos2d.h"
#include"AppDelegate.h"


USING_NS_CC;
using namespace cocos2d;


Scene* GameScene1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vect(0, 0));

    // 'layer' is an autorelease object
    auto layer = GameScene1::create();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void GameScene1::movePlayer(Touch* touche, Event* evento)
{
    auto positionTouch = touche->getLocation();
    if (_classic->getBoundingBox().containsPoint(positionTouch)) {
        _classic->setPositionX(positionTouch.x);
    }

}

void GameScene1::initializePhysics(cocos2d::Sprite* sprite)
{
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    sprite->setPhysicsBody(body);
}

void GameScene1::monsterfish(float ct)
{
    auto director = Director::getInstance();
    auto size = director->getWinSize();
    Sprite* fish = nullptr;
    for (int i = 0; i < 3; i++)
    {
        fish = Sprite::create("image.jpeg");
        fish->setAnchorPoint(Vec2::ZERO);
        fish->setPosition(CCRANDOM_0_1() * size.width, size.height);
        initializePhysics(fish);
        fish->getPhysicsBody()->setVelocity(Vect(0, ((CCRANDOM_0_1() + 0.2f) * -250)));
        _fishs.pushBack(fish);
        this->addChild(fish, 1);


    }
}


void GameScene1::initializeTouch()
{
    auto auditeur = EventListenerTouchOneByOne::create();
    auditeur->onTouchBegan = [](Touch* touch, Event* event) { return true; };
    auditeur->onTouchMoved = CC_CALLBACK_2(GameScene1::movePlayer, this);
    auditeur->onTouchEnded = [=](Touch* touch, Event* event) {};
    _eventDispatcher->addEventListenerWithSceneGraphPriority(auditeur, this);



}


// on "init" you need to initialize your instance
bool GameScene1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {


        return false;

    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    //pause menu
    auto pauseItem = MenuItemImage::create("pause.png",
        "pause.png",
        CC_CALLBACK_1(GameScene1::GoToPauseScene1, this));
    pauseItem->setPosition(Point(pauseItem->getContentSize().width
        - (pauseItem->getContentSize().width / 4)
        + origin.x, visibleSize.height - pauseItem->getContentSize().height
        + (pauseItem->getContentSize().width / 4) + origin.y));
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO); this->addChild(menu,1);


    auto director = Director::getInstance();
    auto size = director->getWinSize();
    auto spritebackground = Sprite::create("pp.jpeg");
    spritebackground->setAnchorPoint(Vec2::ZERO);
    spritebackground->setPosition(0, 0);
    addChild(spritebackground, 0);
    _classic = Sprite::create("classic.png");
    _classic->setPosition(size.width / 2, size.height * 0.23);
    initializePhysics(_classic);
    addChild(_classic, 1);
    initializeTouch();

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene1::monsterfish), 5.0f);





    return true;
}


void GameScene1::GoToPauseScene1(cocos2d::Ref* pSender) {
    auto scene = PauseScene1::createScene();
    Director::getInstance()->pushScene(scene);
}

void GameScene1::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}