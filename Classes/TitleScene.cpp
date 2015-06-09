//
//  TitleScene.cpp
//  testAtest
//
//  Created by kojimatomo on 2015/05/30.
//
//

#include "TitleScene.h"
#include "MainScene.h"

USING_NS_CC;

TitleScene::TitleScene(){
    
}

TitleScene::~TitleScene(){
    
}

Scene* TitleScene::createScene(){
    auto scene = Scene::create();
    auto layer = TitleScene::create();
    scene->addChild(layer);
    return scene;
}

bool TitleScene::init(){
    if(!Layer::init()){
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto background = Sprite::create("title_background.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    auto logo = Sprite::create("title_logo.png");
    logo->setPosition(Vec2(winSize.width / 2.0, winSize.height - 150));
    this->addChild(logo);
    
    auto touchToStart = Sprite::create("title_start.png");
    touchToStart->setPosition(Vec2(winSize.width / 2.0, 90));
    auto blink = Sequence::create(FadeTo::create(0.5, 127),
                                  FadeTo::create(0.5, 255),
                                  NULL);
    touchToStart->runAction(RepeatForever::create(blink));
    this->addChild(touchToStart);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *touch,Event *event){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("decide.mp3");
        
        this->getEventDispatcher()->removeAllEventListeners();
        auto delay = DelayTime::create(0.5);
        auto startGame = CallFunc::create([]{
            auto scene = MainScene::createScene();
            auto transition = TransitionPageTurn::create(0.5,scene,true);
            Director::getInstance()->replaceScene(transition);
        });
        this->runAction(Sequence::create(delay,
                                         startGame,
                                         NULL));
        
        return true;
    };
    
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

void TitleScene::onEnterTransitionDidFinish(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("title.mp3", true);
}