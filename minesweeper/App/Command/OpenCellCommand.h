#pragma once

#include "ICommand.h"
#include "../Controller/GameController.h"

class OpenCellCommand : public ICommand {
public:
    OpenCellCommand(GameController& controller, const CellPosition& position);
    bool execute() override;

private:
    GameController& m_controller;
    CellPosition m_position;
};