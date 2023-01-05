

#include "PauseScene1.h"
#include "gameScene1.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* PauseScene1::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = PauseScene1::create();

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
bool PauseScene1::init()
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
    auto backgroundSprite = Sprite::create("bg.png");
    backgroundSprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
    this->addChild(backgroundSprite, -1);
   
    

    /*adding menu*/
    auto resumeItem = MenuItemImage::create("resume.png",
                                            "resume.png",
                                            CC_CALLBACK_1(PauseScene1::Resume1, this));
    auto retryItem = MenuItemImage::create("retry.png",
                                            "retry.png",
                                            CC_CALLBACK_1(PauseScene1::Retry1, this));
    auto mainMenuItem = MenuItemImage::create("home.png", 
                                            "home.png",
                                            CC_CALLBACK_1(PauseScene1::GoToMainMenuScene1, this));
    auto menu = Menu::create(resumeItem, retryItem, mainMenuItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4); this->addChild(menu);

  

    return true;
}

   

void PauseScene1::Resume1(cocos2d::Ref* pSender) {
    Director::getInstance()->popScene(); 
}
void PauseScene1::GoToMainMenuScene1(cocos2d::Ref* pSender) {
    auto scene = HelloWorld::createScene();     
    Director::getInstance()->popScene();  
    Director::getInstance()->replaceScene(scene);
}
void PauseScene1::Retry1(cocos2d::Ref* pSender) { 
    auto scene = GameScene1::createScene();   
    Director::getInstance()->popScene();  
    Director::getInstance()->replaceScene(scene);
}