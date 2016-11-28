#include "HelloWorldScene.h"


HelloWorld::HelloWorld() {

}
HelloWorld::~HelloWorld() {
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("spritesheet.plist");
	
}

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);
    
    auto label = Label::createWithTTF("SpriteIlluminator", "fonts/Marker Felt.ttf", 24);
	label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);

	// 背景
    auto bg = Sprite::create("background.png");
	bg->setVisible(false);
	bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(bg, 0);

	// 燈泡
	this->_sBulb = Sprite::create("lightbulb.png");
	this->_sBulb->setPosition(Vec2(960,800));
	this->addChild(this->_sBulb, 15);

	// 燈光特效
	this->_effect = LightEffect::create();
	this->_effect->retain();

	this->_vlightPos = Vec3(512, 800, 100);
	this->_effect->setLightPos(this->_vlightPos);
	this->_effect->setLightCutoffRadius(2000);
	this->_effect->setBrightness(1.5f);

	// 森林
	Sprite *sp = Sprite::create("foreground.png");
	auto tree = EffectSprite::createWithSpriteFrame(sp->getSpriteFrame());
	tree->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(tree, 1);

	//// 森林與光源效果連結
	tree->setEffect(this->_effect, "foreground_n.png");

	// 載入Plist檔
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spritesheet.plist");
	// 設定影格
	Vector<SpriteFrame*> animFrames;
	char str[100];
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "boy_run_%02d.png", i);
		animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(str));
	}
	// 主角
	this->_sMan = EffectSprite::createWithSpriteFrame(animFrames.front());
	Animation *animation = Animation::createWithSpriteFrames(animFrames, 1.0f / 11);
	this->_sMan->runAction(RepeatForever::create(Animate::create(animation)));
	this->_sMan->setPosition(Vec2(960, 350));
	this->addChild(this->_sMan, 10);
	
	// 主角與光源效果連結
	this->_sMan->setEffect(this->_effect, "spritesheet_n.png");


	//// 光源位置
	//this->_vlightPos = Vec3(960, 350, 100);
	//this->_effect->setLightPos(this->_vlightPos);

	//// 光源顏色
	//this->_effect->setLightColor(Color3B::YELLOW);

	// 環境光源顏色
	this->_effect->setAmbientLightColor(Color3B::BLACK);

	//// 光源亮度
	//this->_effect->setBrightness(2.0f);

	//// 光源最大半徑
	//this->_effect->setLightCutoffRadius(1000.0f);

	//// 光源半亮度距離
	//this->_effect->setLightHalfRadius(0.5f);

	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::TouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::TouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::TouchEnded, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool HelloWorld::TouchBegan(CCTouch* touch, CCEvent* event) {
	Point touchLocation = touch->getLocation();
	this->_sBulb->setPosition(touchLocation);
	this->_vlightPos = Vec3(this->_sBulb->getPositionX(), this->_sBulb->getPositionY(), 100);
	this->_effect->setLightPos(this->_vlightPos);
	return true;
}
void HelloWorld::TouchMoved(CCTouch* touch, CCEvent* event) {
	Point touchLocation = touch->getLocation();
	this->_sBulb->setPosition(touchLocation);
	this->_vlightPos = Vec3(this->_sBulb->getPositionX(), this->_sBulb->getPositionY(), 100);
	this->_effect->setLightPos(this->_vlightPos);
}
void HelloWorld::TouchEnded(CCTouch* touch, CCEvent* event) {
	Point touchLocation = touch->getLocation();
	this->_sBulb->setPosition(touchLocation);
	this->_vlightPos = Vec3(this->_sBulb->getPositionX(), this->_sBulb->getPositionY(), 100);
	this->_effect->setLightPos(this->_vlightPos);
}

