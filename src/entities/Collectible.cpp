#include "Collectible.h"
#include "ResourceManager.h"
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>

bool Collectible::init()
{
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("laser_blue.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_pSprite->setScale(sf::Vector2f(2.5f, 2.5f));
    m_collisionRadius = collisionRadius;
    
    currentState = INACTIVE;
    return true;
}

void Collectible::update(float dt)
{
    switch(currentState)
    {
        case INACTIVE:
        {
            return;
            break;
        }
        case SPAWNING:
        {
            currentState = ACTIVE;
            break;
        }
        case ACTIVE:
        {
            lifetime -= dt;
            m_position.x -= speed * dt;
            if (lifetime <= 0.0f)
                deactivate();
            break;
        }
        case DYING:
            break;
        default:
            break;
    }
}

void Collectible::render(sf::RenderTarget& target) const
{
    if (currentState == SPAWNING || currentState == ACTIVE)
    {
        m_pSprite->setPosition(m_position);
        target.draw(*m_pSprite);
    }
}

void Collectible::activate(sf::Vector2f a_position, float a_lifetime, float a_speed)
{
    reset();
    currentState = SPAWNING;
    setPosition(a_position);
    setSpeed(a_speed);
    lifetime = a_lifetime;
}

void Collectible::deactivate()
{
    currentState = INACTIVE;
}

void Collectible::reset()
{
    currentState = INACTIVE;
    m_position = {0.0f, 0.0f};
    lifetime = defaultEnemyLifetime;
    speed = defaultEnemySpeed;
}

void Collectible::setSpeed(float a_speed)
{
    if (speed < a_speed)
        speed = a_speed;
}