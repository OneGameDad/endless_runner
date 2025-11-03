#pragma once

#include "Entity.h"
#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>
#include "ProjectilesManager.h"

namespace sf { class Sprite; }

class Player final : public Entity
{
private:

    static constexpr float maxHealth = 100.0f;
    float currentHealth = maxHealth;

    static constexpr float maxEnergy = 50.0f;
    static constexpr float startingEnergy = 5.0f;
    float currentEnergy = startingEnergy;

    bool isDead = true;
    bool wasSpacePressed = false;

    const float fireCost = 1.0f;
    bool canFire = true;
    float fireRate = defaultPlayerFireRate;
    sf::Vector2f spawnPoint;

    bool canJump = true;
    float jumpRate = defaultPlayerJumpRate;

    const float gravity = 150.0f;
    const float maxYSpeed = -30.0f;
    const float dropBoost = 8.0f;

    bool canTakeDamage = true;
    float damageRate = defaultPlayerDamageRate;

    bool canBeDrained = true;
    float drainRate = defaultPlayerDamageRate;

    ProjectilesManager* projManager;
    void    reset();
    void    fire();
    void    recharge(float deltaTime);
    void    jump();
    void    drop();

public:
    static constexpr float collisionRadius = 42.0f;

    Player(ProjectilesManager* pProjManager);
    virtual ~Player() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

    bool m_isJumping = false;

    bool    getIsDead() const { return (isDead); }
    void    setIsDead();

    void    takeDamage(float num);
    void    heal(float num);
    
    void    energize(float num);
    void    drain(float num);

    float   getNormalizedEnergy() const;
    float   getNormalizedHealth() const;
    float   getCurrentEnergy() const { return (currentEnergy); }
    float   getCurrentHealth() const { return (currentHealth); }

    
};
