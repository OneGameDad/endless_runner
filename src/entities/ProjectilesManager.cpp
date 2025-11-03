#include "ProjectilesManager.h"

ProjectilesManager::ProjectilesManager(IState* pState, EnemyManager* pEnemManager)
    : m_pState(pState), enemManager(pEnemManager)
{}

ProjectilesManager::~ProjectilesManager()
{
    for(auto& item: pool)
        item->deactivate();
}

bool ProjectilesManager::initialise()
{
    pool.reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<Projectile>());
    }
    for (auto& item: pool)
    {
        item->init();
    }
    return true;
}

void ProjectilesManager::update(float deltaTime)
{
    for (auto& item: pool)
    {   
        item->update(deltaTime);
    }
}

void ProjectilesManager::render(sf::RenderTarget& target) const
{
    for (auto& item: pool)
        item->render(target);    
}

void ProjectilesManager::spawn(sf::Vector2f a_position, float a_lifetime, float a_speed)
{
   size_t item = getUseableItem();
   if (pool[item]->getCurrentState() != INACTIVE)
        pool[item]->deactivate();
    pool[item]->activate(a_position, a_lifetime, a_speed);
}

size_t ProjectilesManager::getUseableItem()
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