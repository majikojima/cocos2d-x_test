//
//  MainScene.cpp
//  testAtest
//
//  Created by kojimatomo on 2015/03/03.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const int FRUIT_TOP_MARGIN = 45;
const int FRUIT_SPAWN_RATE = 60;
const int FONT_SIZE = 23;
const float TIME_LIMIT_SECOND = 60;

MainScene::MainScene()
:_player(nullptr)
,_score(0)
,_scoreLabel(NULL)
,_second(TIME_LIMIT_SECOND)
,_secondLabel(NULL)
,_gameState(GameState::PLAYING)
,_ms(NULL)
{
    
}

MainScene::~MainScene(){
    CC_SAFE_RELEASE_NULL(_player);
    CC_SAFE_RELEASE_NULL(_scoreLabel);
    CC_SAFE_RELEASE_NULL(_ms);
}

Scene* MainScene::createScene(){
    auto scene = Scene::create();
    auto layer = MainScene::create();
    
    scene->addChild(layer);
    return scene;
}

bool MainScene::init(){
    if(!Layer::init()){
        return false;
    }
    
    auto winSize = Director::getInstance()->getWinSize();
    
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(winSize.width / 2.0, winSize.height / 2.0));
    this->addChild(background);
    
    auto scoreLabel = Label::createWithSystemFont(StringUtils::toString(_score),
                                                  "Marker Felt",
                                                  FONT_SIZE);
    scoreLabel->enableShadow(Color4B::BLACK, Size(0.5, 0.5), 3);
    scoreLabel->enableOutline(Color4B::BLACK, 1.5);
    scoreLabel->setPosition(Vec2(winSize.width / 2 * 1.5, winSize.height - 40));
    this->setScoreLabel(scoreLabel);
    this->addChild(scoreLabel);
    
    auto scoreLabelHeader = Label::createWithSystemFont("SCORE", "Marker Felt", FONT_SIZE);
    scoreLabelHeader->setPosition(Vec2(winSize.width / 2 * 1.5, winSize.height - 20));
    this->addChild(scoreLabelHeader);
    
    int second = static_cast<int>(_second);
    auto secondLabel = Label::createWithSystemFont(StringUtils::toString(second),
                                                   "Marker Felt",
                                                   FONT_SIZE);
    secondLabel->setPosition(Vec2(winSize.width / 2, winSize.height - 40));
    this->setSecondLabel(secondLabel);
    this->addChild(secondLabel);
    
    auto secondLabelHeader = Label::createWithSystemFont("TIME", "Marker Felt", FONT_SIZE);
    secondLabelHeader->setPosition(Vec2(winSize.width / 2, winSize.height - 20));
    this->addChild(secondLabelHeader);
    
    auto player = Player::create();
    //player->setPosition(Vec2(40,50));
    this->addChild(player);
    this->setPlayer(player);
    
    auto ms = MotionStreak::create(1.0, 13.0f, 50.0f, Color3B::WHITE, "player.png");
    ms->setPosition(player->getPosition());
    this->setMs(ms);
    this->addChild(ms);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [this](Touch *touch, Event *event){
        _player->touchAction();
//        auto jump = JumpTo::create(5, _player->getPosition(),200,1);
//        _player->runAction(jump);
        return true;
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();

    return true;
}

void MainScene::update(float dt){
    if(_gameState == GameState::PLAYING){
        _second -= dt;
        int second = static_cast<int>(_second);
        _secondLabel->setString(StringUtils::toString(second));
    
        int random = rand() % FRUIT_SPAWN_RATE;
        if(random == 0){
            this->addFruit();
        }
    
        for(auto& fruit: _fruits){
            Vec2 playerPosition = _player->getPosition();
            Rect boundingBox = fruit->getBoundingBox();
            bool isHit = boundingBox.containsPoint(playerPosition);
            if(isHit){
                this->hitFruit(fruit);
            }
        }
        
//        auto msPosition = _ms->getPosition();
//        msPosition.x++;
        _ms->setPosition(_player->getPosition());
        
        if(_second < 0){
            this->onResult();
        }
    }
}

void MainScene::hitFruit(Sprite *fruit){
    this->removeFruit(fruit);
    _player->getState();
    if(_player->getState() == Player::PlayerState::STAND){
        this->removeFruit(fruit);
    }
    else if((_player->getState() == Player::PlayerState::HITJUMP)
            ||(_player->getState() == Player::PlayerState::WHILEJUMP)){
        _score += 1;
        _scoreLabel->setString(StringUtils::toString(_score));
        _player->setState(Player::PlayerState::HITJUMP);
        _player->jumpAction();
        this->removeFruit(fruit);
    }
}

Sprite* MainScene::addFruit()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    std::string filename = StringUtils::format("fruit.png");
    auto fruit = Sprite::create(filename);
    
    auto fruitSize = fruit->getContentSize();
    fruit->setPosition(Vec2(winSize.width, FRUIT_TOP_MARGIN));
    this->addChild(fruit);
    _fruits.pushBack(fruit);
    
    auto move = MoveTo::create(5, Vec2(0, FRUIT_TOP_MARGIN));
    
    auto remove = CallFuncN::create([this](Node *node){
        auto sprite = dynamic_cast<Sprite *>(node);
        this->removeFruit(sprite);
    });
    
    auto sequence = Sequence::create(move, remove, NULL);
    fruit->runAction(sequence);
    
    return fruit;
}

bool MainScene::removeFruit(Sprite *fruit)
{
    if(_fruits.contains(fruit)){
        fruit->removeFromParent();
        _fruits.eraseObject(fruit);
        return true;
    }
    return false;
}

void MainScene::onResult(){
    _gameState = GameState::RESULT;
    auto winSize = Director::getInstance()->getWinSize();
    
    auto replayButton =
        MenuItemImage::create("replay_button.png",
                              "replay_button_pressed.png",
                              [](Ref* ref){
                                  auto scene = MainScene::createScene();
                                  auto transition = TransitionFade::create(0.5, scene);
                                  Director::getInstance()->replaceScene(transition);
                              });
//    auto titleButton =
//        MenuItemImage::create("title_button.png",
//                              "title_button_pressed.png",
//                              [](Ref* ref){
//                                  
    //                              });
//    auto menu = Menu::create(replayButton, titleButton, NULL);
    auto menu = Menu::create(replayButton, NULL);
    menu->alignItemsVerticallyWithPadding(15);
    menu->setPosition(Vec2(winSize.width / 2, winSize.height / 2));
    this->addChild(menu);
}

void MainScene::onEnterTransitionDidFinish(){
    Layer::onEnterTransitionDidFinish();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("main.mp3", true);
}