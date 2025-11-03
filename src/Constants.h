#pragma once

enum e_entity_state
{
    INACTIVE,
    SPAWNING,
    ACTIVE,
    DYING,
};

const float defaultEnemySpeed = 200.0f;
const float defaultEnemyLifetime = 5.0f;

const float defaultProjectileSpeed = 300.0f;
const float defaultProjectileLifetime = 5.0f;

const float groundYPos = 800.0f;

const float defaultPlayerFireRate = 0.5f;
const float defaultPlayerJumpRate = 0.5f;