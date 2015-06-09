//
//  MainScene.h
//  testAtest
//
//  Created by kojimatomo on 2015/03/03.
//
//

#ifndef __testAtest__MainScene__
#define __testAtest__MainScene__

#include "cocos2d.h"
#include "Player.h"

class MainScene :public cocos2d::Layer{
private:
    enum class GameState{
        PLAYING,
        RESULT
    };
    
    cocos2d::Sprite* addFruit();
    bool removeFruit(cocos2d::Sprite* fruit);
    void hitFruit(cocos2d::Sprite* fruit);
    void onResult();
    void displayHitScore();
protected:
    MainScene();
    virtual ~MainScene();
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(MainScene);

    void update(float dt);
    void onEnterTransitionDidFinish();
    
//    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite* , _player, Player);
    CC_SYNTHESIZE_RETAIN(Player *, _player, Player);
    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _fruits, Fruits);
    CC_SYNTHESIZE(int, _score, Score);
    CC_SYNTHESIZE(int, _scoreUpWidth, ScoreUpWidth);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _scoreLabel, ScoreLabel);
    CC_SYNTHESIZE(float, _second, Second);
    CC_SYNTHESIZE_RETAIN(cocos2d::Label *, _secondLabel, SecondLabel);
    CC_SYNTHESIZE(GameState, _gameState, GameState);
    CC_SYNTHESIZE_RETAIN(cocos2d::MotionStreak *, _ms, Ms);
};

#endif /* defined(__testAtest__MainScene__) */
