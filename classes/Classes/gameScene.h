#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void endGame(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);

    cocos2d::Sprite* mySprite;
    cocos2d::Sprite* door;
    void addMonster(float dt);

    cocos2d::PhysicsWorld* sceneWorld;
    void GoToGameOverScene(Ref* pSender);
    void GoToPauseScene(Ref* pSender);



private:

    void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { 
        sceneWorld = world;
    };
    bool onContactBegin(cocos2d::PhysicsContact& contact); cocos2d::PhysicsWorld* mWorld;

};


#endif // GAME_SCENE_H