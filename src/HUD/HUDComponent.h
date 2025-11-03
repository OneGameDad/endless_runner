#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sf { class RenderTarget; };

class HUDComponent: public sf::Transformable
{
protected:
    
public:
    HUDComponent() = default;
    virtual ~HUDComponent() = 0;

    virtual void    initialize() = 0;
    virtual void    update(float deltaTime) = 0;
    virtual void    render(sf::RenderTarget& target) const = 0;
};