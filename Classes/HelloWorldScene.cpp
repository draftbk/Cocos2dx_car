#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <string>
#include <stdlib.h>
#include  <iostream>
#include <limits>
#include <sstream>
#include<stack>
#include<queue>


using namespace std;

USING_NS_CC;

using namespace cocostudio::timeline;
stack<int> stk;
stack<int> stk2;
queue<int> q;
int tag_number=0;
int load_hight_y=220;
int carport_x=600;
int q_loc_1_x=538;//队列中的车最多八量
int s1_carport_1_y=767;//进去的车最多9辆
int s2_outcar_1_x=652;//开出来的车最多8辆

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    
    if ( !Layer::init() )
    {
        return false;
    }
    auto spr0=Sprite::create("backgr.png");
    spr0->setAnchorPoint(Point(0,0));
    this->addChild(spr0);
    
    //添加按钮
    auto sprBt=Sprite::create("add.png");
    sprBt->setPosition(Point(1160,760));
    this->addChild(sprBt);
    
    //把路画出来
    auto sprline= Sprite::create("cfxg.png");
    sprline->setPosition(Point(580,520));
    sprline->setRotation(0);
    sprline->setScale(0.04,5.6);
    this->addChild(sprline);
    auto sprline1= Sprite::create("cfxg.png");
    sprline1->setPosition(Point(620,520));
    sprline1->setRotation(0);
    sprline1->setScale(0.04,5.6);
    this->addChild(sprline1);
    

    CCLOG("%f",1.0);
//设置监听
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    return true;
}

void HelloWorld::moveInPort(int time,Point location,int tag)
{
    auto carSprcp=getChildByTag(tag);
    Point carPositon=carSprcp->getPosition();
    auto action=MoveTo::create(time/3, Point(location.x,carPositon.y));
    auto action1=RotateBy::create(time/6, 270);
    auto action2=MoveTo::create(time/3, location);
    auto sq=Sequence::create(action,action1,action2,NULL);
    carSprcp->runAction(sq);
    stk.push(tag);
    //队列抛出
    q.pop();
    //后面的车跟上
    for (int i=1; i<=q.size(); i++) {
        auto front=q.front();
        auto carSprcp=getChildByTag(front);
        auto moveForward=MoveTo::create(2,Point(carSprcp->getPositionX()+62,load_hight_y) );
        carSprcp->runAction(moveForward);
        q.pop();
        q.push(front);
    }
}

void HelloWorld::moveInPortAgain(int time,Point location,int tag)
{
    auto carSprcp=getChildByTag(tag);
    Point carPositon=carSprcp->getPosition();
    auto action=MoveTo::create(time*(carPositon.x-location.x)/400, Point(location.x,carPositon.y));
    auto action1=RotateBy::create(time/6, 90);
    auto action2=MoveTo::create(time/3, location);
    auto sq=Sequence::create(action,action1,action2,NULL);
    carSprcp->runAction(sq);
    stk.push(tag);
    //栈抛出
    stk2.pop();
}

void HelloWorld::moveOutPort1(int time,Point location,int tag)
{
    auto carSprcp=getChildByTag(tag);
    Point carPositon=carSprcp->getPosition();
    auto action=MoveTo::create(time*(carPositon.y-location.y)/400, Point(carPositon.x,location.y));
    auto action1=RotateBy::create(time/6, -90);
    auto action2=MoveTo::create(time/3, location);
    auto sq=Sequence::create(action,action1,action2,NULL);
    carSprcp->runAction(sq);
}

void HelloWorld::moveOutPort2(int n)
{
    for (int i=n-2; i>=0; i--) {
        auto top=stk.top();
        moveOutPort1(4,Point(s2_outcar_1_x+62*i,load_hight_y),top);
        stk2.push(top);
        stk.pop();
    }
   // moveOutPort1(3, Point(s2_outcar_1_x,load_hight_y), 1);
    //选中的车开走
     auto carSprcp=getChildByTag(stk.top());
    auto action1=MoveTo::create(7, Point(600,150));
    auto action2=RotateBy::create(0.5, 90);
    auto action3=MoveTo::create(0.5,Point(500,150) );
     auto action4=MoveTo::create(1,Point(1300,150) );
    //其他车再开回去
    auto funcall= CallFunc::create(this, callfunc_selector(HelloWorld::callbackC));
    auto delay=DelayTime::create(3.1);
    auto funcall2= CallFunc::create(this, callfunc_selector(HelloWorld::callbackC2));
    auto sq=Sequence::create(action1,action2,action3,action4,funcall,delay,funcall2,NULL);
    carSprcp->runAction(sq);
    //最后开走了的车，虽然放在这里，这个代码应该在callfunc_selector前
     stk.pop();
}
void HelloWorld::callbackC(){
    auto size=stk2.size();
   
    for (int i=1; i<=size; i++) {
        auto top=stk2.top();
        CCLOG("%d",top);
        moveInPortAgain(3,Point(600,s1_carport_1_y-62*stk.size()) , top);
    }
   }

void HelloWorld::callbackC2(){
    if(q.size()>0){
    moveInPort(3,Point(600,s1_carport_1_y-62*stk.size()), q.front());
    }
   
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
    auto iftouched=false;
    auto isbtn=false;
    auto spr_number=0;
    //坐标点
    Point location=touch->getLocation();
    //生成小车
    if(location.getDistance(Point(1160,760))<=30){
        auto carSpr=Sprite::create("car.png");
        carSpr->setPosition(0, load_hight_y);
        carSpr->setTag(++tag_number);
        addChild(carSpr);
       
        isbtn=true;
        if (stk.size()<9) {
             q.push(tag_number);
            moveInPort(3, Point(600,s1_carport_1_y-62*stk.size()), tag_number);
        }else{
            auto show=MoveTo::create(2,Point(q_loc_1_x-62*q.size(), load_hight_y) );
            carSpr->runAction(show);
            q.push(tag_number);
        }
    }
    //检测是哪辆车
    if (!isbtn) {//检测不是按到按钮了
        for (int i=1; i<=tag_number; i++) {
            auto carSprcp=getChildByTag(i);
            if (carSprcp->getPosition().getDistance(location)<30) {
                iftouched=true;
                spr_number=i;
                break;
            }
        }
    }
    
    //触摸到队列中的小车了
    if (iftouched&&!isbtn&&location.x<578) {
        //第一辆车开进去
        auto carSprcp=getChildByTag(spr_number);
        auto jumpto = JumpTo ::create(0.2, carSprcp->getPosition(), 20, 2 );
        carSprcp->runAction(jumpto);
       
    }
    //触摸到中间栈中的小车
    if (iftouched&&!isbtn&&location.x>582&&location.x<618) {
        int x=stk.size()-(s1_carport_1_y+30+62-location.y)/62+2;
        CCLOG("%d",x);
        //
        moveOutPort2(x);
        
    }
    
    return true;
}



