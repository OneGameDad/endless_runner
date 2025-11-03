#pragma once

#include "Entity.h"
#include <memory>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf { class Sprite; }

class Collectible final : public Entity
{
private:
    float speed = defaultEnemySpeed;
    float lifetime = defaultEnemyLifetime;
    
    void setSpeed(float a_speed);
public:
    static constexpr float collisionRadius = 24.0f;

    Collectible() = default;
    virtual ~Collectible() = default;
    
    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

    void activate(sf::Vector2f a_position, float a_lifetime, float a_speed);
    void deactivate();
    void reset();

    float getLifetime() const { return (lifetime); }
    float getSpeed() const { return (speed); }
};
