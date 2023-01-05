

#include "GameOverScene.h"
#include "gameScene.h"
#include "HelloWorldScene.h"
#include "PauseScene.h"


USING_NS_CC;

Scene* GameOver::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameOver::create();

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
bool GameOver::init()
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
    /*auto background = DrawNode::create();
    background->drawSolidRect(origin, visibleSize, Color4F(1.0, 1.0, 1.0, 1.0));
    this->addChild(background);*/
    auto backgroundSprite = Sprite::create("bg.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);
    

    /*adding menu*/
    auto menuTitle = MenuItemImage::create("over.png",
                                            "over.png");
    auto retryItem = MenuItemImage::create("retry.png", 
                                           "retry.png",
                                           CC_CALLBACK_1(GameOver::GoToGameScene, this));
    auto mainMenuItem = MenuItemImage::create("home.png",
                                             "home.png", 
                                              CC_CALLBACK_1(GameOver::GoToMainMenuScene, this));
    auto menu = Menu::create(menuTitle, retryItem, mainMenuItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4); this->addChild(menu,1);

    return true;
}

   
void GameOver::GoToGameScene(cocos2d::Ref* pSender) {
    auto scene = GameScene::createScene();   
    Director::getInstance()->replaceScene(scene);
}
void GameOver::GoToMainMenuScene(cocos2d::Ref* pSender) {
    auto scene = HelloWorld::createScene();    
    Director::getInstance()->replaceScene(scene);
}

  