#pragma once

#include <Geode/Geode.hpp>
using namespace geode::prelude;

class SongPopup : public geode::Popup {
protected:
    bool init(GJGameLevel *level);
    void onClose(CCObject*);
public:
    static SongPopup *create(GJGameLevel *level);
};
