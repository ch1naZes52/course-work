#pragma once

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual bool execute() = 0;
};