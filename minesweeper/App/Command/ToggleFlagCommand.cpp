#include "ToggleFlagCommand.h"

ToggleFlagCommand::ToggleFlagCommand(GameController& controller, const CellPosition& position)
    : m_controller(controller),
    m_position(position) {
}

bool ToggleFlagCommand::execute() {
    return m_controller.toggleFlag(m_position);
}