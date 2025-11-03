#pragma once

class TimeUtils
{
public:
    static float timeScale;
    static float getScaledDeltaTime(float deltaTime)
    {
        return timeScale * deltaTime;
    }
};