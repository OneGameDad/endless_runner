#pragma once

#include <SFML/System/Clock.hpp>

class GameTime
{
private:
    sf::Clock frameClock;
    sf::Clock realTimeClock;
    double startTime = 0.0;
    double currentTime = 0.0;
    double currentTimeUnscaled = 0.0;
    double deltaTime = 0.0;
    double deltaTimeUnscaled = 0.0;
    double timeScale = 1.0;

    GameTime() = default;
public:
    GameTime(const GameTime &copy) = delete;
    GameTime &operator=(const GameTime &copy) = delete;
    static GameTime &getInstance()
    {
        static GameTime instance;
        return (instance); 
    }

    void   setTime()
    {
        startTime = static_cast<double>(frameClock.restart().asSeconds());
        currentTimeUnscaled = startTime;
        deltaTimeUnscaled = startTime;
        deltaTime = startTime;
        currentTime = startTime;
    };

    void   updateTime()
    {
        deltaTimeUnscaled = static_cast<double>(frameClock.restart().asSeconds());
        currentTimeUnscaled += deltaTimeUnscaled;
        deltaTime = deltaTimeUnscaled * timeScale;
        currentTime += deltaTime;
    };

    void setTimeScale(double t)
    {
        timeScale = t;
    }

    double getCurrentTime() const { return (currentTime); }
    double getCurrrentTimeUnscaled() const { return (currentTimeUnscaled); }
    double getDeltaTime() const { return (deltaTime); }
    double getDeltaTimeUnscaled() const { return (deltaTimeUnscaled); }
    double getStartTime() const { return (startTime); }
    double getTimeScale() const { return (timeScale); }
    float getRealTime() { return (realTimeClock.getElapsedTime().asSeconds()); }
};