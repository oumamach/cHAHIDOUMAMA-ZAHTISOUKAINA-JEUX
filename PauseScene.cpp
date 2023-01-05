

#include "PauseScene.h"
#include "gameScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = PauseScene::create();

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
bool PauseScene::init()
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
                                            CC_CALLBACK_1(PauseScene::Resume, this));
    auto retryItem = MenuItemImage::create("retry.png",
                                            "retry.png",
                                            CC_CALLBACK_1(PauseScene::Retry, this));
    auto mainMenuItem = MenuItemImage::create("home.png", 
                                            "home.png",
                                            CC_CALLBACK_1(PauseScene::GoToMainMenuScene, this));
    auto menu = Menu::create(resumeItem, retryItem, mainMenuItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height / 4); this->addChild(menu,1);

  

    return true;
}

   

void PauseScene::Resume(cocos2d::Ref* pSender) {
    Director::getInstance()->popScene(); 
}
void PauseScene::GoToMainMenuScene(cocos2d::Ref* pSender) {
    auto scene = HelloWorld::createScene();     
    Director::getInstance()->popScene();  
    Director::getInstance()->replaceScene(scene);
}
void PauseScene::Retry(cocos2d::Ref* pSender) { 
    auto scene = GameScene::createScene();   
    Director::getInstance()->popScene();  
    Director::getInstance()->replaceScene(scene);
}