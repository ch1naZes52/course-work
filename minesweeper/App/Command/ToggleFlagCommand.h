#pragma once

#include "ICommand.h"
#include "../Controller/GameController.h"

class ToggleFlagCommand : public ICommand {
public:
    ToggleFlagCommand(GameController& controller, const CellPosition& position);
    bool execute() override;

private:
    GameController& m_controller;
    CellPosition m_position;
};