#include "songpopup.hpp"

void SongPopup::onClose(CCObject*) {
    this->setKeypadEnabled(false);
    this->setTouchEnabled(false);
    this->removeFromParent();
}

bool SongPopup::init(GJGameLevel *level) {
    CCSize m_size = CCSize{ 300, 90 };
    CCTouchDispatcher::get()->registerForcePrio(this, 2);

    if (!this->initWithColor({ 0, 0, 0, 105 })) return false;
    
    auto winSize = CCDirector::get()->getWinSize();

    m_mainLayer = CCLayer::create();
    this->addChild(m_mainLayer);

    SongInfoObject *songInfo = (level->m_songID == 0) ? LevelTools::getSongObject(level->m_audioTrack) : SongInfoObject::create(level->m_songID);

    CustomSongWidget *songWidget = CustomSongWidget::create(
        songInfo,
        nullptr,
        false,
        false,
        true,
        level->m_songID == 0,
        false,
        false,
        0
    );

    m_mainLayer->addChild(songWidget);

    m_buttonMenu = CCMenu::create();
    m_buttonMenu->setZOrder(100);
    m_mainLayer->addChild(m_buttonMenu);

    m_mainLayer->ignoreAnchorPointForPosition(false);
    m_mainLayer->setPosition(winSize / 2);
    m_mainLayer->setContentSize(m_size);
    m_mainLayer->setLayout(
        CopySizeLayout::create()
            ->add(m_buttonMenu)
            ->add(songWidget)
    );

    this->setTouchEnabled(true);

    auto m_closeBtn = CCMenuItemExt::createSpriteExtraWithFrameName("GJ_closeBtn_001.png", 0.8f, [this](auto btn) {
        this->onClose(btn);
    });
    m_buttonMenu->addChildAtPosition(m_closeBtn, geode::Anchor::TopRight, { 3.f, -3.f });

    this->setKeypadEnabled(true);
    this->setTouchEnabled(true);

    return true;
}

SongPopup* SongPopup::create(GJGameLevel *level) {
    SongPopup *ret = new SongPopup();
    if (ret->init(level)) {
        ret->autorelease();
        return ret;
    }

    delete ret;
    return nullptr;
}

