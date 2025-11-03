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
    collManager(std::make_unique<CollectiblesManager>(this)),
    projManager(std::make_unique<ProjectilesManager>(this, enemManager.get()))
{}

bool StatePlaying::init()
{
    m_ground.setSize({1024.0f, 256.0f});
    m_ground.setPosition({0.0f, groundYPos});
    m_ground.setFillColor(sf::Color::Green);

    m_pPlayer = std::make_unique<Player>(projManager.get());
    if (!m_pPlayer || !m_pPlayer->init())
        return false;

    m_pPlayer->setPosition(sf::Vector2f(200, groundYPos));
    enemManager->initialise();
    collManager->initialise();
    projManager->initialise();

    initText();

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

    projManager->update(dt);
    enemManager->update(dt);
    collManager->update(dt);
    

    // Detect collisions
    updateEnemyCollisions();

    // End Playing State on player death
    if (m_pPlayer->getIsDead() == false)
        m_stateStack.popDeferred();

    updateCollectibleCollisions();
    updateText();
}

void StatePlaying::render(sf::RenderTarget& target) const
{
    target.draw(m_ground);
    projManager->render(target);
    enemManager->render(target);
    collManager->render(target);
    m_pPlayer->render(target);
    target.draw(*playerHealthNotification);
    target.draw(*playerEnergyNotification);
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
        enemManager->spawn(sf::Vector2f{1000, 800}, 10.0f, defaultEnemyLifetime, defaultEnemySpeed);
    }
}

void StatePlaying::updateEnemyCollisions()
{
    for (auto& pEnemy : enemManager->getPool())
    {
        float distance = (m_pPlayer->getPosition() - pEnemy->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + pEnemy->getCollisionRadius(), 2.0f);
        //const sf::Vector2f playerPosition = m_pPlayer->getPosition();

        if (distance <= minDistance)
        {
            m_pPlayer->setIsDead();
            return;
        }
    }

    for (auto& pProj: projManager->getPool())
    {
        for (auto& pEnemy : enemManager->getPool())
        {
            float distance = (pProj->getPosition() - pEnemy->getPosition()).lengthSquared();
            float minDistance = std::pow(pProj->getCollisionRadius() + pEnemy->getCollisionRadius(), 2.0f);
            //const sf::Vector2f playerPosition = m_pPlayer->getPosition();

            if (distance <= minDistance)
            {
                pEnemy->deactivate();
                pProj->deactivate();
                return;
            }
        }
    }
}

void StatePlaying::updateCollectibleCollisions()
{
    for (auto& pColl : collManager->getPool())
    {
        float distance = (m_pPlayer->getPosition() - pColl->getPosition()).lengthSquared();
        float minDistance = std::pow(Player::collisionRadius + pColl->getCollisionRadius(), 2.0f);
        //const sf::Vector2f playerPosition = m_pPlayer->getPosition();

        if (distance <= minDistance)
        {
            pColl->deactivate();
            m_pPlayer->energize(1.0f);
            return;
        }
    }
}

bool StatePlaying::initText()
{
    const sf::Font* pFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
    if (pFont == nullptr)
        return false;

    playerHealthNotification = std::make_unique<sf::Text>(*pFont);
    if (!playerHealthNotification)
        return false;
    std::string tempStr1 = healthStr + std::to_string((int)m_pPlayer->getCurrentHealth());
    playerHealthNotification->setString(tempStr1);
    playerHealthNotification->setStyle(sf::Text::Bold);
    playerHealthNotification->setCharacterSize(24);
    sf::FloatRect HPlocalBounds = playerHealthNotification->getLocalBounds();
    playerHealthNotification->setOrigin({HPlocalBounds.size.x / 2.0f, HPlocalBounds.size.y / 2.0f});
    playerHealthNotification->setPosition({150.0f, 30.0f});

    playerEnergyNotification = std::make_unique<sf::Text>(*pFont);
    if (!playerEnergyNotification)
        return false;
    std::string tempStr2 = energyStr + std::to_string((int)m_pPlayer->getCurrentEnergy());
    playerEnergyNotification->setString(tempStr2);
    playerEnergyNotification->setStyle(sf::Text::Bold);
    playerEnergyNotification->setCharacterSize(24);
    sf::FloatRect NRGlocalBounds = playerEnergyNotification->getLocalBounds();
    playerEnergyNotification->setOrigin({NRGlocalBounds.size.x / 2.0f, NRGlocalBounds.size.y / 2.0f});
    playerEnergyNotification->setPosition({150.0f, 60.0f});

    return true;
}

void StatePlaying::updateText()
{
    std::string tempStr1 = healthStr + std::to_string((int)m_pPlayer->getCurrentHealth());
    playerHealthNotification->setString(tempStr1);
//    sf::FloatRect HPlocalBounds = playerHealthNotification->getLocalBounds();
//    playerHealthNotification->setOrigin({HPlocalBounds.size.x / 2.0f, HPlocalBounds.size.y / 2.0f});

    std::string tempStr2 = energyStr + std::to_string((int)m_pPlayer->getCurrentEnergy());
    playerEnergyNotification->setString(tempStr2);

//    sf::FloatRect NRGlocalBounds = playerEnergyNotification->getLocalBounds();
//    playerEnergyNotification->setOrigin({NRGlocalBounds.size.x / 2.0f, NRGlocalBounds.size.y / 2.0f});
}