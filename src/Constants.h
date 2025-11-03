#pragma once

enum e_entity_state
{
    INACTIVE,
    SPAWNING,
    ACTIVE,
    DYING,
};

enum e_enemy_kind
{
    FIZZ,
    BUZZ,
};

const float defaultEnemySpeed = 200.0f;
const float defaultEnemyLifetime = 5.0f;
const float defaultEnemyRadius = 2.0f;

const float defaultProjectileSpeed = 300.0f;
const float defaultProjectileLifetime = 5.0f;

const float defaultCollectibleRadius = 1.5f;

const float groundYPos = 800.0f;

const float defaultPlayerFireRate = 0.5f;
const float defaultPlayerJumpRate = 0.5f;
const float defaultPlayerDamageRate = 0.75f;