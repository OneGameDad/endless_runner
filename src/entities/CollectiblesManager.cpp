#include "CollectiblesManager.h"

CollectiblesManager::CollectiblesManager(IState* pState)
    : m_pState(pState)
{}

CollectiblesManager::~CollectiblesManager()
{
    for(auto& item: pool)
        item->deactivate();
}

bool CollectiblesManager::initialise()
{
    pool.reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<Collectible>());
    }
    for (auto& item: pool)
    {
        item->init();
    }
    std::cout << "item Manager & Enemies Initialized\n";
    return true;
}

void CollectiblesManager::update(float deltaTime)
{
    for (auto& item: pool)
    {   
        item->update(deltaTime);
    }
}

void CollectiblesManager::render(sf::RenderTarget& target) const
{
    for (auto& item: pool)
        item->render(target);    
}

void CollectiblesManager::spawn(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle)
{
   size_t item = getUseableItem();
   if (pool[item]->getCurrentState() != INACTIVE)
        pool[item]->deactivate();
    pool[item]->activate(a_position, a_lifetime, a_speed);
    std::cout << "Collectible Spawned\n";
}

size_t CollectiblesManager::getUseableItem()
{
    size_t item = 0;
    float currentLifeTime = 0.0f;
    float shortestLifeTime = std::numeric_limits<float>::max();
    for (size_t i = 0; i < pool.size(); i++)
    {
        if (pool[i]->getCurrentState() == INACTIVE)
        {
            item = i;
            return (item);
        }
        currentLifeTime = pool[i]->getLifetime();
        if (currentLifeTime < shortestLifeTime)
        {
            shortestLifeTime = currentLifeTime;
            item = i;
        }
    }
    return (item);
}