#pragma once

#include <string>

class IGameObserver {
public:
    virtual ~IGameObserver() = default;
    virtual void onGameChanged() = 0;
    virtual void onGameEvent(const std::string& text) = 0;
};