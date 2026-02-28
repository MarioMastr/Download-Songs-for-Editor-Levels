#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>

#include "songpopup.hpp"

class $modify(SongELL, EditLevelLayer) {
    void onSongButton(CCObject* sender) {
        SongPopup::create(this->m_level)->show();
    }

    static void onModify(auto& self) {
        if (Loader::get()->getLoadedMod("mariomastr.progress_of_editor_levels")) {
            if (!self.setHookPriorityAfterPost("EditLevelLayer::init", "mariomastr.progress_of_editor_levels")) {
                geode::log::warn("Failed to set hook priority.");
            }
        }
    }

    bool init(GJGameLevel *level) {
        if (!EditLevelLayer::init(level))
            return false;

        NodeIDs::provideFor(this);

        CCNode *levelSong = this->getChildByID("level-song");
        CCPoint position = levelSong->getPosition();

        CCSprite *info = CCSprite::createWithSpriteFrameName("GJ_infoIcon_001.png");
        CCMenuItemSpriteExtra *levelSongButton = CCMenuItemSpriteExtra::create(info, this, menu_selector(SongELL::onSongButton));

        CCMenu *menu = CCMenu::createWithItem(levelSongButton);
        menu->setContentSize({0, 0});
        menu->setScale(0.5);
        menu->setPosition({position.x + 66, position.y + 5});

        this->addChild(menu);
        
        return true;
    }
};
