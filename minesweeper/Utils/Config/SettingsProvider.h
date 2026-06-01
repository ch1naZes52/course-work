#pragma once

#include "../../Core/Game/GameDifficulty.h"
#include "../../Core/Game/GameSettings.h"

#include <QString>
#include <vector>

class SettingsProvider {
public:
    std::vector<GameDifficulty> difficulties() const;

    QString difficultyName(GameDifficulty difficulty) const;
    QString modeText(const GameSettings& settings) const;
    GameSettings settingsFor(GameDifficulty difficulty) const;
};