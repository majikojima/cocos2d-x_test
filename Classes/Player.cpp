//
//  Player.cpp
//  testAtest
//
//  Created by kojimatomo on 2015/05/22.
//
//

#include "Player.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

const Vec2 INIT_PLAYER_POSITION = Vec2(40,50);

Player::Player()
:_state(PlayerState::STAND)
{
    
}

Player::~Player(){
}

bool Player::init(){
    if(!Sprite::initWithFile("player.png")){
        return false;
    }
    
    this->setPosition(INIT_PLAYER_POSITION);
    
    return true;
}

void Player::update(float dt){

}

void Player::touchAction(){
    if(_state == PlayerState::STAND){
        _state = PlayerState::WHILEJUMP;
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("crash.mp3");
        this->jumpAction();
    }
    else if(_state == PlayerState::WHILEJUMP){
        
    }
    else if(_state == PlayerState::HITJUMP){
        this->setState(PlayerState::WHILEJUMP);
        this->jumpAction();
    }

}

void Player::jumpAction(){
    this->stopAllActions();
    
    auto jump = JumpTo::create(1.5, INIT_PLAYER_POSITION,60,1);
    auto land = CallFuncN::create([this](Node *node){
        _state = PlayerState::STAND;
    });
    auto sequence = Sequence::create(jump, land, NULL);
    this->runAction(sequence);
}