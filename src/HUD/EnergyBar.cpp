#include "EnergyBar.h"

EnergyBar::EnergyBar(Player* pPlayer)
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

EnergyBar::~EnergyBar(){}

void    EnergyBar::initialize()
{
    this->setPosition(adjustPosition());
    playerScale = m_pPlayer->getSprite().getScale().x;
    playerHeight = m_pPlayer->getSprite().getTexture().getSize().y * playerScale;
    rectangle->setSize({playerHeight, maxHeight});
    rectangle->setOrigin({0.0f, 0.0f});
    rectangle->setFillColor(sf::Color::Yellow);
    rectangle->setPosition(getPosition());
    rectangle->setRotation(sf::degrees(90));
}

sf::Vector2f EnergyBar::adjustPosition()
{
    static const float offsetX = -10.0f;
    static const float offsetY = 0.0f;
    sf::Vector2f pos = m_pPlayer->getPosition();
    sf::Vector2f adjustedPosition = {pos.x + offsetX, pos.y + offsetY};
    return (adjustedPosition);
}

void    EnergyBar::update(float deltaTime)
{
    (void)deltaTime; //Todo use to animate
    float amount = m_pPlayer->getNormalizedEnergy();
    float currentWidth = playerHeight * amount;
    
    rectangle->setSize({currentWidth, maxHeight});
    rectangle->setOrigin({0.0f, 0.f});
    
    sf::Vector2f pos = adjustPosition();
    setPosition(pos);
    rectangle->setPosition(getPosition());
}

void    EnergyBar::render(sf::RenderTarget& target) const
{
    target.draw(*rectangle);
}