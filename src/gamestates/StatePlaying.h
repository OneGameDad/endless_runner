#pragma once

#include "IState.h"
#include "entities/Player.h"
#include "entities/Enemy.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>
#include "entities/EnemyManager.h"
#include <iostream>
#include "entities/CollectiblesManager.h"

class StatePlaying : public IState
{
public:
    StatePlaying(StateStack& stateStack);
    ~StatePlaying() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;

private:
    static constexpr const float enemySpawnInterval = 2.0f;
    static constexpr const float collSpawnInterval = 1.5f;
    float m_timeUntilEnemySpawn = enemySpawnInterval;
    float m_timeUntilCollSpawn = collSpawnInterval;

    StateStack& m_stateStack;
    std::unique_ptr<Player> m_pPlayer;
//  std::vector<std::unique_ptr<Enemy>> m_enemies;
    sf::RectangleShape m_ground;
    bool m_hasPauseKeyBeenReleased = true;

    
    void updateEnemySpawns(float dt);
    bool updateEnemyCollisions();

    void updateCollectibleSpawns(float dt);
    void updateCollectibleCollisions();

    std::unique_ptr<EnemyManager> enemManager;
    std::unique_ptr<CollectiblesManager> collManager;
};
