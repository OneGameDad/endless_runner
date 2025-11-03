#pragma once

enum e_entity_state
{
    INACTIVE,
    SPAWNING,
    ACTIVE,
    DYING,
};

const float defaultEnemySpeed = 200.0f;
const float defaultEnemyLifetime = 10.0f;

const float groundYPos = 800.0f;