#include "StateMenu.h"
#include "StatePlaying.h"
#include "StateStack.h"
#include "ResourceManager.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

StateMenu::StateMenu(StateStack& stateStack)
    : m_stateStack(stateStack)
{
    
}

bool StateMenu::init()
{
    const sf::Font* pFont = ResourceManager::getOrLoadFont("Lavigne.ttf");
    if (pFont == nullptr)
        return false;

    m_pText = std::make_unique<sf::Text>(*pFont);
    if (!m_pText)
        return false;

    m_pTutorial1 = std::make_unique<sf::Text>(*pFont);
    if (!m_pTutorial1)
        return false;

    m_pTutorial2 = std::make_unique<sf::Text>(*pFont);
    if (!m_pTutorial2)
        return false;
    
    m_pTutorial3 = std::make_unique<sf::Text>(*pFont);
    if (!m_pTutorial3)
        return false;

    m_pText->setString("PRESS <ENTER> TO PLAY");
    m_pText->setStyle(sf::Text::Bold);
    sf::FloatRect localBounds = m_pText->getLocalBounds();
    m_pText->setOrigin({localBounds.size.x / 2.0f, localBounds.size.y / 2.0f});

    m_pTutorial1->setString("While playing press <SPACE> to jump");
    m_pTutorial1->setStyle(sf::Text::Italic);
    sf::FloatRect Tut1localBounds = m_pTutorial1->getLocalBounds();
    m_pText->setOrigin({Tut1localBounds.size.x / 2.0f, Tut1localBounds.size.y / 2.0f});

    m_pTutorial2->setString("While playing press <DOWN ARROW> to drop faster");
    m_pTutorial2->setStyle(sf::Text::Italic);
    sf::FloatRect Tut2localBounds = m_pTutorial2->getLocalBounds();
    m_pText->setOrigin({Tut2localBounds.size.x / 2.0f, Tut2localBounds.size.y / 2.0f});

    m_pTutorial3->setString("While playing press <G> to shoot");
    m_pTutorial3->setStyle(sf::Text::Italic);
    sf::FloatRect Tut3localBounds = m_pTutorial3->getLocalBounds();
    m_pText->setOrigin({Tut3localBounds.size.x / 2.0f, Tut3localBounds.size.y / 2.0f});

    return true;
}

void StateMenu::update(float dt)
{
    (void)dt;
    m_hasStartKeyBeenPressed |= sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
    if (m_hasStartKeyBeenReleased)
    {
        m_hasStartKeyBeenPressed = false;
        m_hasStartKeyBeenReleased = false;
        m_stateStack.push<StatePlaying>();
    }
    m_hasStartKeyBeenReleased |= m_hasStartKeyBeenPressed && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter);
}

void StateMenu::render(sf::RenderTarget& target) const
{
    m_pText->setPosition({target.getSize().x * 0.5f, target.getSize().y * 0.5f});
    target.draw(*m_pText);

    m_pTutorial1->setPosition({(target.getSize().x * 0.5f) - 220, (target.getSize().y * 0.5f) + 40.0f});
    target.draw(*m_pTutorial1);

    m_pTutorial2->setPosition({(target.getSize().x * 0.5f) - 220, (target.getSize().y * 0.5f) + 80.0f});
    target.draw(*m_pTutorial2);

    m_pTutorial3->setPosition({(target.getSize().x * 0.5f) - 220, (target.getSize().y * 0.5f) + 120.0f});
    target.draw(*m_pTutorial3);
}
