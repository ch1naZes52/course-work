#pragma once

#include "ICommand.h"
#include "../Controller/GameController.h"
#include "../../Core/Game/GameDifficulty.h"

class RestartGameCommand : public ICommand {
public:
    RestartGameCommand(GameController& controller, GameDifficulty difficulty);

    bool execute() override;

private:
    GameController& m_controller;
    GameDifficulty m_difficulty;
};