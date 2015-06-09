//
//  TitleScene.h
//  testAtest
//
//  Created by kojimatomo on 2015/05/30.
//
//

#ifndef __testAtest__TitleScene__
#define __testAtest__TitleScene__

#include "cocos2d.h"

class TitleScene :public cocos2d::Layer{
protected:
    TitleScene();
    virtual ~TitleScene();
    bool init() override;
public:
    static cocos2d::Scene* createScene();
    void onEnterTransitionDidFinish() override;
    CREATE_FUNC(TitleScene);
};

#endif /* defined(__testAtest__TitleScene__) */
