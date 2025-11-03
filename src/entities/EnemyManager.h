#pragma once

#include <memory>
#include <vector>
#include <limits>
#include "Enemy.h"
#include "gamestates/IState.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

class Enemy;
class IState;

namespace sf { class RenderTarget; };

class EnemyManager
{
private:
    IState* m_pState;
    std::vector<std::unique_ptr<Enemy>> pool;
    static const size_t maxPoolSize = 50;

    sf::Texture* texture;

    size_t getUseableEnemy();
public:
    EnemyManager(IState* pState);
    ~EnemyManager();

    bool initialise();
    void update(float deltaTime);
    virtual void render(sf::RenderTarget& target) const;
    void spawn(sf::Vector2f a_position, float a_lifetime, float a_velocity, float a_direction);

    std::vector<std::unique_ptr<Enemy>>& getPool() { return (pool); }
};