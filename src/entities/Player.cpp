#include "Player.h"
#include "ResourceManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

Player::Player()
{
}

bool Player::init()
{
    reset();
    const sf::Texture* pTexture = ResourceManager::getOrLoadTexture("player.png");
    if (pTexture == nullptr)
        return false;

    m_pSprite = std::make_unique<sf::Sprite>(*pTexture);
    if (!m_pSprite)
        return false;

    m_rotation = sf::degrees(0);
    sf::FloatRect localBounds = m_pSprite->getLocalBounds();
    m_pSprite->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});
    m_pSprite->setPosition(m_position);
    m_pSprite->setScale(sf::Vector2f(3.0f, 3.0f));
    m_collisionRadius = collisionRadius;

    return true;
}

void Player::update(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_position.y > 790)
    {
        m_isJumping = true;
    }

    if (m_position.y < 650)
        m_isJumping = false;

    if (m_isJumping)
        m_position.y -= 200 * dt;
    else if (!m_isJumping && m_position.y < 800)
        m_position.y += 200 * dt;
}

void Player::render(sf::RenderTarget& target) const
{
    m_pSprite->setRotation(m_rotation);
    m_pSprite->setPosition(m_position);
    target.draw(*m_pSprite);
}

void Player::reset()
{
    currentEnergy = 0.0f;
    currentHealth = maxHealth;
}

void Player::setIsDead()
{
    if (isDead)
        isDead = false;
}

void    Player::takeDamage(float num)
{
    if (num < 0.0f)
        return;
    currentHealth -= num;
    if (currentHealth <= 0.0f)
        setIsDead();
}

void    Player::heal(float num)
{
    if (num < 0.0f)
        return;
    if ((currentHealth + num) < maxHealth)
        currentHealth += num;
    else
        currentHealth = maxHealth;
}

void    Player::energize(float num)
{
    if (num < 0.0f)
        return;
    if ((currentEnergy + num) < maxEnergy)
        currentEnergy += num;    
    else
        currentEnergy = maxEnergy;
    std::cout << "Current Energy: " << getCurrentEnergy() << std::endl;
}

void    Player::drain(float num)
{
    if (num < 0.0f)
        return;
    if ((currentEnergy - num) >= 0.0f)
        currentEnergy = 0.0f;
    else
        currentEnergy -= num;
}

float   Player::getNormalizedEnergy() const
{
    float normalized = currentEnergy / maxEnergy;
    return (normalized);
}

float   Player::getNormalizedHealth() const
{
    float normalized = currentHealth / maxHealth;
    return (normalized);
}