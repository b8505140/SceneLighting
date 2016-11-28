#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "EffectSprite/LightEffect.h"
#include "EffectSprite/EffectSprite.h"

USING_NS_CC;

class HelloWorld : public Layer
{
public:
	HelloWorld();
	~HelloWorld();

	// ¿Oªw
	Sprite *_sBulb;
	LightEffect *_effect;
	Vec3 _vlightPos;

	// ¥D¨¤
	EffectSprite *_sMan;

    static Scene* createScene();
    virtual bool init();
    void menuCloseCallback(Ref* pSender);

	virtual bool TouchBegan(CCTouch* touch, CCEvent* event);
	virtual void TouchMoved(CCTouch* touch, CCEvent* event);
	virtual void TouchEnded(CCTouch* touch, CCEvent* event);
  
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__








