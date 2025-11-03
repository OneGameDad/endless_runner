#include "EnemyManager.h"

EnemyManager::EnemyManager(IState* pState)
    : m_pState(pState)
{}

EnemyManager::~EnemyManager()
{
    for(auto& enemy: pool)
        enemy->deactivate();
}

bool EnemyManager::initialise()
{
    pool.reserve(maxPoolSize);
    for (size_t i = 0; i < maxPoolSize; i++)
    {
        pool.emplace_back(std::make_unique<Enemy>());
    }
    for (auto& enem: pool)
    {
        enem->init();
    }
    std::cout << "Enemy Manager & Enemies Initialized\n";
    return true;
}

void EnemyManager::update(float deltaTime)
{
    for (auto& enemy: pool)
    {   
        enemy->update(deltaTime);
    }
}

void EnemyManager::render(sf::RenderTarget& target) const
{
    for (auto& enemy: pool)
        enemy->render(target);    
}

void EnemyManager::spawn(sf::Vector2f a_position, float a_lifetime, float a_speed, float a_angle)
{
   size_t enemy = getUseableEnemy();
   if (pool[enemy]->getCurrentState() != INACTIVE)
        pool[enemy]->deactivate();
    pool[enemy]->activate(a_position, a_lifetime, a_speed);
}

size_t EnemyManager::getUseableEnemy()
{
    size_t enemy = 0;
    float currentLifeTime = 0.0f;
    float shortestLifeTime = std::numeric_limits<float>::max();
    for (size_t i = 0; i < pool.size(); i++)
    {
        if (pool[i]->getCurrentState() == INACTIVE)
        {
            enemy = i;
            return (enemy);
        }
        currentLifeTime = pool[i]->getLifetime();
        if (currentLifeTime < shortestLifeTime)
        {
            shortestLifeTime = currentLifeTime;
            enemy = i;
        }
    }
    return (enemy);
}