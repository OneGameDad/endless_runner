#pragma once

#include "HUDComponent.h"
#include "entities/Player.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>
#include <iostream>

class Player;

class PlayerHealthBar: public HUDComponent
{
private:
    Player* m_pPlayer;
    std::unique_ptr<sf::RectangleShape> rectangle;
    float playerHeight = 0.0f;
    float playerScale = 0.0f;
    const float maxWidth = 100.0f;
    const float maxHeight = 10.0f;

    sf::Vector2f    adjustPosition();
public:
    explicit PlayerHealthBar(Player* pPlayer);
    ~PlayerHealthBar();
    
    void    initialize() override;
    void    update(float deltaTime) override;
    void    render(sf::RenderTarget& target) const override;
};