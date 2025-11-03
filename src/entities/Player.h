#pragma once

#include "Entity.h"
#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <iostream>

namespace sf { class Sprite; }

class Player final : public Entity
{
private:

    static constexpr float maxHealth = 100.0f;
    float currentHealth = maxHealth;

    static constexpr float maxEnergy = 10.0f;
    float currentEnergy = 0.0f;

    bool isDead = true;

    void reset();

public:
    static constexpr float collisionRadius = 42.0f;

    Player();
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
