
#ifndef _GAMESCENE1_SCENE_H_
#define _GAMESCENE1_SCENE_H_

#include "cocos2d.h"

class GameScene1 : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);


    // implement the "static create()" method manually
    CREATE_FUNC(GameScene1);
    void GoToPauseScene1(cocos2d::Ref* pSender);

private:
    cocos2d::Sprite* _classic;
    cocos2d::Vector<cocos2d::Sprite*> _fishs;
    void initializeTouch();
    void monsterfish(float dt);
    void initializePhysics(cocos2d::Sprite* sprite);
    void movePlayer(cocos2d::Touch* toque, cocos2d::Event* event);
};

#endif // _HELLOWORLD_SCENE_H_