#include "OpenCellCommand.h"

OpenCellCommand::OpenCellCommand(GameController& controller, const CellPosition& position) : m_controller(controller), m_position(position) {}

bool OpenCellCommand::execute() {
    return m_controller.openCell(m_position);
}