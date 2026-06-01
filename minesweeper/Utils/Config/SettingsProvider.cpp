#include "SettingsProvider.h"

std::vector<GameDifficulty> SettingsProvider::difficulties() const {
    return {
        GameDifficulty::Beginner,
        GameDifficulty::Intermediate,
        GameDifficulty::Expert
    };
}

QString SettingsProvider::difficultyName(GameDifficulty difficulty) const {
    if (difficulty == GameDifficulty::Beginner) {
        return "Новичок";
    }

    if (difficulty == GameDifficulty::Intermediate) {
        return "Любитель";
    }

    if (difficulty == GameDifficulty::Expert) {
        return "Эксперт";
    }

    return "Пользовательский";
}

QString SettingsProvider::modeText(const GameSettings& settings) const {
    if (settings.difficulty() == GameDifficulty::Beginner) {
        return "Новичок 9x9";
    }

    if (settings.difficulty() == GameDifficulty::Intermediate) {
        return "Любитель 16x16";
    }

    if (settings.difficulty() == GameDifficulty::Expert) {
        return "Эксперт 16x30";
    }

    return QString("Пользовательский %1x%2")
        .arg(settings.boardSize().rows())
        .arg(settings.boardSize().columns());
}

GameSettings SettingsProvider::settingsFor(GameDifficulty difficulty) const {
    if (difficulty == GameDifficulty::Beginner) {
        return GameSettings::beginner();
    }

    if (difficulty == GameDifficulty::Intermediate) {
        return GameSettings::intermediate();
    }

    if (difficulty == GameDifficulty::Expert) {
        return GameSettings::expert();
    }

    return GameSettings::beginner();
}