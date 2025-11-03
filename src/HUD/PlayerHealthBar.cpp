#include "PlayerHealthBar.h"

PlayerHealthBar::PlayerHealthBar(Player* pPlayer)
    : m_pPlayer(pPlayer)
{
    try
    {
        rectangle = std::make_unique<sf::RectangleShape>();
    }
    catch (const std::bad_alloc& e)
    {
        std::cerr << "RectangleShape Allocation failed: " << e.what() << std::endl;
    }
}

PlayerHealthBar::~PlayerHealthBar(){}

void    PlayerHealthBar::initialize()
{
    this->setPosition(adjustPosition());
    playerScale = m_pPlayer->getSprite().getScale().x;
    playerHeight = m_pPlayer->getSprite().getTexture().getSize().y * playerScale;
    rectangle->setSize({playerHeight, maxHeight});
    rectangle->setOrigin({0.0f, 0.0f});
    rectangle->setFillColor(sf::Color::Red);
    rectangle->setPosition(getPosition());
    rectangle->setRotation(sf::degrees(90));
}

sf::Vector2f PlayerHealthBar::adjustPosition()
{
    static const float offsetX = -20.0f;
    static const float offsetY = 0.0f;
    sf::Vector2f pos = m_pPlayer->getPosition();
    sf::Vector2f adjustedPosition = {pos.x + offsetX, pos.y + offsetY};
    return (adjustedPosition);
}

void    PlayerHealthBar::update(float deltaTime)
{
    (void)deltaTime; //Todo use to animate
    float health = m_pPlayer->getNormalizedHealth();
    float currentWidth = playerHeight * health;
    
    rectangle->setSize({currentWidth, maxHeight});
    rectangle->setOrigin({0.0f, 0.f});
    
    sf::Vector2f pos = adjustPosition();
    setPosition(pos);
    rectangle->setPosition(getPosition());
}

void    PlayerHealthBar::render(sf::RenderTarget& target) const
{
    target.draw(*rectangle);
}