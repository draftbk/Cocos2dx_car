#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    
    virtual void moveInPort(int time,Point location,int tag);
    virtual void moveInPortAgain(int time,Point location,int tag);
    virtual void moveOutPort1(int time,Point location,int tag);
    virtual void moveOutPort2(int n);
    virtual void callbackC();
    virtual void callbackC2();
};

#endif // __HELLOWORLD_SCENE_H__
