#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditLevelLayer.hpp>

#include "songpopup.hpp"

class $modify(SongELL, EditLevelLayer) {
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
        CCNode *songText = levelSong->getChildByIndex(1);
        CCPoint position = songText->getPosition();

        CCMenuItemSpriteExtra *levelSongButton = CCMenuItemExt::createSpriteExtraWithFrameName(
            "GJ_infoIcon_001.png",
            1.0f,
            [level](CCMenuItemSpriteExtra *btn) {
                SongPopup::create(level)->show();
            }
        );

        CCMenu *levelSongMenu = CCMenu::createWithItem(levelSongButton);

        float xOffset = ((songText->getContentWidth() / 2) * songText->getScale()) + 5;
        float xPosition = position.x + xOffset;
        float yPosition = position.y + 6;

        levelSongMenu->setContentSize({0, 0});
        levelSongMenu->setScale(0.5);
        levelSongMenu->setPosition({xPosition, yPosition});
        levelSongMenu->setID("level-song-menu");

        levelSong->addChild(levelSongMenu);
        
        return true;
    }
};
