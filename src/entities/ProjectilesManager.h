#pragma once

#include <memory>
#include <vector>
#include <limits>
#include "Projectile.h"
#include "gamestates/IState.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include "EnemyManager.h"
#include <cmath>

class Projectile;
class IState;

namespace sf { class RenderTarget; };

class ProjectilesManager
{
private:
    IState* m_pState;
    EnemyManager* enemManager;
    std::vector<std::unique_ptr<Projectile>> pool;
    static const size_t maxPoolSize = 50;

    sf::Texture* texture;

    size_t getUseableItem();

public:
    ProjectilesManager(IState* pState, EnemyManager* pEnemManager);
    ~ProjectilesManager();

    bool initialise();
    void update(float deltaTime);
    virtual void render(sf::RenderTarget& target) const;
    void spawn(sf::Vector2f a_position, float a_lifetime, float a_velocity);

    std::vector<std::unique_ptr<Projectile>>& getPool() { return (pool); }
};