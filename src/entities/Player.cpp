#include "Player.h"
#include "ResourceManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <cmath>

Player::Player(ProjectilesManager* pProjManager)
    : projManager(pProjManager)
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
    recharge(dt);
   
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_position.y > 790)
    {
        jump();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_position.y < 790)
    {
        drop();
    }
/*    if (m_position.y > 790)
        onGround = true;
*/
    if (m_position.y < 650)
        m_isJumping = false;

    if (m_isJumping)
        m_position.y -= 200 * dt;
    else if (!m_isJumping && m_position.y < 800)
        m_position.y += 200 * dt;
/*
    float ySpeed = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && m_position.y > 790)
    {
        jump();
    }
    if (m_position.y >= 800.0f)
    {
        ySpeed = 0.0f;
        m_isJumping = false;
    }
    else
    {
        ySpeed += gravity * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_position.y < 790)
        {
            ySpeed += dropBoost * dt;
        }
    }
    if (m_isJumping)
    {
        ySpeed = maxYSpeed;
    }
    m_position.y += ySpeed;
    std::cout << "Player Y Pos: " <<  m_position.y << std::endl;
*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G))
    {
        fire();
    }
}

void Player::render(sf::RenderTarget& target) const
{
    m_pSprite->setRotation(m_rotation);
    m_pSprite->setPosition(m_position);
    target.draw(*m_pSprite);
}

void Player::reset()
{
    currentEnergy = startingEnergy;
    currentHealth = maxHealth;
    fireRate = defaultPlayerFireRate;
    jumpRate = defaultPlayerJumpRate;
    damageRate = defaultPlayerDamageRate;
    canFire = true;
    canJump = true;
    canTakeDamage = true;
}

void Player::setIsDead()
{
    if (isDead)
        isDead = false;
}

void    Player::takeDamage(float num)
{
    if (num <= 0.0f)
            return;
    if (canTakeDamage)
    {
        currentHealth -= num;
        if (currentHealth <= 0.0f)
            setIsDead();
        canTakeDamage = false;
    }
    
}

void    Player::heal(float num)
{
    if (num <= 0.0f)
        return;
    if ((currentHealth + num) < maxHealth)
        currentHealth += num;
    else
        currentHealth = maxHealth;
}

void    Player::energize(float num)
{
    if (num <= 0.0f)
        return;
    if ((currentEnergy + num) < maxEnergy)
        currentEnergy += num;    
    else
        currentEnergy = maxEnergy;
    std::cout << "Current Energy: " << getCurrentEnergy() << std::endl;
}

void    Player::drain(float num)
{
    if (num <= 0.0f)
            return;
    if (canBeDrained)
    {
        if ((currentEnergy - num) <= 0.0f)
            currentEnergy = 0.0f;
        else
            currentEnergy -= num;
        canBeDrained = false;
    }
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

void    Player::fire()
{
    if (canFire && currentEnergy > 0.0f)
    {
        spawnPoint = {getPosition().x + 10, getPosition().y};
        projManager->spawn(spawnPoint, defaultProjectileLifetime, defaultProjectileSpeed);
        canFire = false;
        currentEnergy -= 3.0f;
    }
}

void    Player::recharge(float deltaTime)
{
    if (!canFire)
    {
        fireRate -= deltaTime;
        if (fireRate <= 0.0f)
        {
            canFire = true;
            fireRate = defaultPlayerFireRate;
        }
    }
    if (!canJump)
    {
        jumpRate -= deltaTime;
        if (jumpRate <= 0.0f)
        {
            canJump = true;
            jumpRate = defaultPlayerJumpRate;
        }
    }
    if (!canTakeDamage)
    {
        damageRate -= deltaTime;
        if (damageRate <= 0.0f)
        {
            canTakeDamage = true;
            damageRate = defaultPlayerDamageRate;
        }
    }
    if (!canBeDrained)
    {
        drainRate -= deltaTime;
        if (drainRate <= 0.0f)
        {
            canBeDrained = true;
            drainRate = defaultPlayerDamageRate;
        }
    }
}

void    Player::jump()
{
    if (canJump)
    {
        canJump = false;
        m_isJumping = true;
    }
}

void    Player::drop()
{
    if (m_isJumping)
    {
        m_isJumping = false;
    }
}