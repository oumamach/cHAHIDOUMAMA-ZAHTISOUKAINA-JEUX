#include "gameScene.h"
#include "gameScene1.h"
#include "GameOverScene.h"
#include "PauseScene.h"

#include <physics3d/CCPhysics3DObject.h>

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object

    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // 'layer' is an autorelease object

    auto layer = GameScene::create();

    layer->SetPhysicsWorld(scene->getPhysicsWorld());
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

bool GameScene::init()

{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    //pause menu
    auto pauseItem = MenuItemImage::create("pause.png", 
                                           "pause.png",
                                           CC_CALLBACK_1(GameScene::GoToPauseScene, this));
    pauseItem->setPosition(Point(pauseItem->getContentSize().width
        - (pauseItem->getContentSize().width / 4) 
        + origin.x, visibleSize.height - pauseItem->getContentSize().height 
        + (pauseItem->getContentSize().width / 4) + origin.y));
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Point::ZERO); this->addChild(menu,1);
   
    
    //setting image bg

    auto backgroundSprite = Sprite::create("background.jpg");
    backgroundSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    backgroundSprite->setScale(1.80f);
   


    auto texture = Director::getInstance()->getTextureCache()->addImage("background.jpg");
    if (backgroundSprite->initWithTexture(texture))
    {
        this->addChild(backgroundSprite);
    }
   

    // player
    mySprite = Sprite::create("classic.png");
    mySprite->setPosition(Vec2(visibleSize.width * 0.1, visibleSize.height * 0.22));

    auto body = PhysicsBody::createCircle(mySprite->getContentSize().width / 2); 
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    mySprite->setPhysicsBody(body);
    this->addChild(mySprite, 1);

    srand((unsigned int)time(nullptr));
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::addMonster), 1.5);

  
   

    //border
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);

    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    edgeNode->setPhysicsBody(edgeBody);

    this->addChild(edgeNode);

    

  

    auto eventListener = EventListenerKeyboard::create();

    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        // Set the velocity of the sprite based on the key that was pressed
        Vec2 velocity;
        switch (keyCode)
        {
        /*case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            velocity = Vec2(-50, 0);
            mySprite->setScaleX(-1); // Flip the sprite horizontally
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            velocity = Vec2(50, 0);
            mySprite->setScaleX(1); // Un-flip the sprite horizontally
            break;*/
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_SPACE:

            velocity = Vec2(0, 300);
            break;
        }

        // Apply the velocity to the sprite's physics body
        mySprite->getPhysicsBody()->setVelocity(velocity);

    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
    {
        Vec2 velocity = Vec2(0, 0);
        // When the left or right arrow key is released, stop the sprite
        switch (keyCode)
        {
        /*case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:*/
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
        case EventKeyboard::KeyCode::KEY_SPACE:
            mySprite->getPhysicsBody()->setVelocity(velocity);
        }
        };
        // Don't forget to add the event listener to the event dispatcher
        this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, mySprite);

        auto contactListener = EventListenerPhysicsContact::create();
        contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);



        return true;

    }

    bool GameScene::onContactBegin(PhysicsContact& contact) {
        GoToGameOverScene(this);
        return true;
    }
void GameScene::GoToPauseScene(cocos2d::Ref* pSender) {
    auto scene = PauseScene::createScene();  
    Director::getInstance()->pushScene(scene); 
}
void GameScene::GoToGameOverScene(cocos2d::Ref* pSender) {
    auto scene = GameOver::createScene();     
    Director::getInstance()->replaceScene(scene);
}

int functionCalls = 0;

void GameScene::addMonster(float ct) {
    auto monster = Sprite::create("monster.png");
    auto body = PhysicsBody::createCircle(monster->getContentSize().width / 2);
    body->setContactTestBitmask(true);
    body->setDynamic(true);
    monster->setPhysicsBody(body);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 1
    auto monsterContentSize = monster->getContentSize();
    auto selfContentSize = this->getContentSize();
    int minY = monsterContentSize.height / 2;
    int maxY = selfContentSize.height - monsterContentSize.height / 2;
    int rangeY = maxY - minY;
    int randomY = (rand() % rangeY) + minY;

    monster->setPosition(Vec2(visibleSize.width , visibleSize.height * 0.22));
    this->addChild(monster, 1);

    // 2
    int minDuration = 2.0;
    int maxDuration = 4.0;
    int rangeDuration = maxDuration - minDuration;
    int randomDuration = (rand() % rangeDuration) + minDuration;

    // 3
    auto actionMove = MoveTo::create(randomDuration, Vec2(-visibleSize.width, randomY));
    auto actionRemove = RemoveSelf::create();
    monster->runAction(Sequence::create(actionMove, actionRemove, nullptr));
    functionCalls++;

    if (functionCalls >= 5)
    {
        // Create a new scene to transition to
        auto scene = GameScene1::createScene();
        Director::getInstance()->pushScene(TransitionFade::create(1.0, scene));
        functionCalls = 0;
    }

    
}