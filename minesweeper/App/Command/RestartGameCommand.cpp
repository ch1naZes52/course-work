#include "RestartGameCommand.h"

RestartGameCommand::RestartGameCommand(GameController& controller, GameDifficulty difficulty) : m_controller(controller), m_difficulty(difficulty) {}

bool RestartGameCommand::execute() {
    m_controller.restart(m_difficulty);
    return true;
}