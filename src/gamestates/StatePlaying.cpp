#include "StatePlaying.h"
#include "StatePaused.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include <memory>
#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>

StatePlaying::StatePlaying(StateStack& stateStack)
    : m_stateStack(stateStack),
    enemManager(std::make_unique<EnemyManager>(this)),
    collManager(std::make_unique<CollectiblesManager>(this))
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
    collManager->initialise();
    return true;
}

void StatePlaying::update(float dt)
{
    updateEnemySpawns(dt);
    updateCollectibleSpawns(dt);
    
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
    collManager->update(dt);

    // Detect collisions
    bool playerDied = false;
    playerDied = updateEnemyCollisions();
    updateCollectibleCollisions();
    

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
    collManager->render(target);
    m_pPlayer->render(target);
}

void StatePlaying::updateCollectibleSpawns(float dt)
{
    m_timeUntilCollSpawn -= dt;

    if (m_timeUntilCollSpawn < 0.0f)
    {
        m_timeUntilCollSpawn = collSpawnInterval;
        collManager->spawn(sf::Vector2f{1000, 800}, 10.0f, defaultEnemySpeed, defaultEnemyLifetime);
    }
}

void StatePlaying::updateEnemySpawns(float dt)
{
    m_timeUntilEnemySpawn -= dt;

    if (m_timeUntilEnemySpawn < 0.0f)
    {
        m_timeUntilEnemySpawn = enemySpawnInterval;
        enemManager->spawn(sf::Vector2f{1000, 800}, 10.0f, defaultEnemySpeed, defaultEnemyLifetime);
    }
}

bool StatePlaying::updateEnemyCollisions()
{
    for (auto& pEnemy : enemManager->getPool())
    {
        float distance = (m_pPlayer->getPosition() - pEnemy->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + pEnemy->getCollisionRadius(), 2.0f);
        const sf::Vector2f playerPosition = m_pPlayer->getPosition();

        if (distance <= minDistance)
        {
            return (true);
        }
    }
    return (false);
}

void StatePlaying::updateCollectibleCollisions()
{
    for (auto& pColl : collManager->getPool())
    {
        float distance = (m_pPlayer->getPosition() - pColl->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + pColl->getCollisionRadius(), 2.0f);
        const sf::Vector2f playerPosition = m_pPlayer->getPosition();

        if (distance <= minDistance)
        {
            pColl->deactivate();
        }
    }
}