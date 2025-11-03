#include "StatePlaying.h"
#include "StatePaused.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include <memory>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

StatePlaying::StatePlaying(StateStack& stateStack)
    : m_stateStack(stateStack),
    enemManager(std::make_unique<EnemyManager>(this))
{
}

bool StatePlaying::init()
{
    m_ground.setSize({1024.0f, 256.0f});
    m_ground.setPosition({0.0f, groundYPos});
    m_ground.setFillColor(sf::Color::Green);

    m_pPlayer = std::make_unique<Player>();
    if (!m_pPlayer || !m_pPlayer->init())
        return false;

    m_pPlayer->setPosition(sf::Vector2f(200, groundYPos));
    enemManager->initialise();
    return true;
}

void StatePlaying::update(float dt)
{
    m_timeUntilEnemySpawn -= dt;

    if (m_timeUntilEnemySpawn < 0.0f)
    {
        m_timeUntilEnemySpawn = enemySpawnInterval;
        enemManager->spawn(sf::Vector2f{1000, 800}, 10.0f, defaultEnemySpeed, defaultEnemyLifetime);
    }

    bool isPauseKeyPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);
    m_hasPauseKeyBeenReleased |= !isPauseKeyPressed;
    if (m_hasPauseKeyBeenReleased && isPauseKeyPressed)
    {
        m_hasPauseKeyBeenReleased = false;
        m_stateStack.push<StatePaused>();
    }

    m_pPlayer->update(dt);

/*    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
    {
        pEnemy->update(dt);
    }
*/

    enemManager->update(dt);

    // Detect collisions
    bool playerDied = false;
    for (auto& pEnemy : enemManager->getPool())
    {
        float distance = (m_pPlayer->getPosition() - pEnemy->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + pEnemy->getCollisionRadius(), 2.0f);
        const sf::Vector2f playerPosition = m_pPlayer->getPosition();

        if (distance <= minDistance)
        {
            playerDied = true;
            break;
        }
    }

    // End Playing State on player death
    if (playerDied)
        m_stateStack.popDeferred();
}

void StatePlaying::render(sf::RenderTarget& target) const
{
    target.draw(m_ground);
//    for (const std::unique_ptr<Enemy>& pEnemy : m_enemies)
//        pEnemy->render(target);
    enemManager->render(target);
    m_pPlayer->render(target);
}
