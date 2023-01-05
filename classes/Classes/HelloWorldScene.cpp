

#include "HelloWorldScene.h"
#include "gameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    //2
   
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
   
    // 3 setting grey background
    
    auto backgroundSprite = Sprite::create("poster.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);
    

    /*adding menu*/


    auto playItem = MenuItemImage::create("playy.png",
                                          "playy.png",
                     CC_CALLBACK_1(HelloWorld::Play, this));
    auto menu = Menu::create( playItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
    this->addChild(menu);

    return true;
}

    void HelloWorld::Play(cocos2d::Ref* pSender)
    {
        CCLOG("Play callback function called");
        auto scene = GameScene::createScene();
        Director::getInstance()->pushScene(TransitionFade::create(1.0, scene));
    }

   

  