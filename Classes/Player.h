  //
//  Player.h
//  testAtest
//
//  Created by kojimatomo on 2015/05/22.
//
//

#ifndef __testAtest__Player__
#define __testAtest__Player__

#include "cocos2d.h"

class Player :public cocos2d::Sprite
{
private:
    
protected:
    bool init() override;
public:
    enum class PlayerState{
        STAND,
        WHILEJUMP,
        HITJUMP
    };
    
    Player();
    ~Player();
    
    void touchAction();
    void jumpAction();
    
    void update(float dt) override;
    
    CC_SYNTHESIZE(PlayerState, _state, State);
    CREATE_FUNC(Player);
};

#endif /* defined(__testAtest__Player__) */
