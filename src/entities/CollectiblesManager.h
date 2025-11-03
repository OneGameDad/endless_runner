#pragma once

#include <memory>
#include <vector>
#include <limits>
#include "Collectible.h"
#include "gamestates/IState.h"
#include "ResourceManager.h"
#include "Constants.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

class Collectible;
class IState;

namespace sf { class RenderTarget; };

class CollectiblesManager
{
private:
    IState* m_pState;
    std::vector<std::unique_ptr<Collectible>> pool;
    static const size_t maxPoolSize = 50;

    sf::Texture* texture;

    size_t getUseableItem();
public:
    CollectiblesManager(IState* pState);
    ~CollectiblesManager();

    bool initialise();
    void update(float deltaTime);
    virtual void render(sf::RenderTarget& target) const;
    void spawn(sf::Vector2f a_position, float a_lifetime, float a_velocity, float a_direction);

    std::vector<std::unique_ptr<Collectible>>& getPool() { return (pool); }
};