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
#include "entities/ProjectilesManager.h"

class StatePlaying : public IState
{
public:
    StatePlaying(StateStack& stateStack);
    ~StatePlaying() = default;

    bool init() override;
    void update(float dt) override;
    void render(sf::RenderTarget& target) const override;
    std::unique_ptr<Player>& getPlayer() { return (m_pPlayer); }
    std::unique_ptr<EnemyManager>& getEnemies() { return (enemManager); }

private:
    static constexpr const float enemySpawnInterval = 2.0f;
    static constexpr const float collSpawnInterval = 1.5f;
    float m_timeUntilEnemySpawn = enemySpawnInterval;
    float m_timeUntilCollSpawn = collSpawnInterval;

    StateStack& m_stateStack;
    std::unique_ptr<Player> m_pPlayer;
    sf::RectangleShape m_ground;
    bool m_hasPauseKeyBeenReleased = true;

    
    void updateEnemySpawns(float dt);
    void updateEnemyCollisions();

    void updateCollectibleSpawns(float dt);
    void updateCollectibleCollisions();

    std::unique_ptr<EnemyManager> enemManager;
    std::unique_ptr<CollectiblesManager> collManager;
    std::unique_ptr<ProjectilesManager> projManager;

    bool initText();
    void updateText();
    std::unique_ptr<sf::Text> playerHealthNotification;
    const std::string healthStr = "Player Health: ";
    std::unique_ptr<sf::Text> playerEnergyNotification;
    const std::string energyStr = "Player Energy: ";
};
