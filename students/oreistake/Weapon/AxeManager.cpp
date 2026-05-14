#include "AxeManager.h"
#include "../students/oreistake/Camera.h"
#include "DxLib.h"

AxeManager::AxeManager():m_pPlayer(nullptr){}

AxeManager::AxeManager(PlayerMove* pPlayermove):m_pPlayer(pPlayermove){}

void AxeManager::Init(std::string name,
    float damage,
    float range,
    float attackRange,
    int coolTime,
    int weaponNum,
    Vector2 playerPos){}

void AxeManager::Spawn(std::string name,
    float damage,
    float range,
    float attackRange,
    int coolTime,
    int weaponNum,
    Vector2 playerPos)
{
    auto axe = std::make_unique<Axe>(name,
        damage,
        range,
        attackRange,
        coolTime,
        weaponNum,
        playerPos);
    axe->Init();
    axe->SetCamera(m_pCamera);     
    axe->Spawn(playerPos);

    m_axes.push_back(std::move(axe));
}

void AxeManager::Update()
{
    for (auto& axe : m_axes)
    {
        axe->Update();
    }

    // €‚ñ‚¾•€‚ğíœ
    m_axes.erase(
        std::remove_if(
            m_axes.begin(),
            m_axes.end(),
            [](const std::unique_ptr<Axe>& axe)
            {
                return !axe->IsAlive();   
            }),
        m_axes.end()
    );
}

void AxeManager::Draw()
{
    for (auto& axe : m_axes)
    {
        axe->Draw();
    }
}

std::vector<Rect> AxeManager::GetCheckRects() const
{
    std::vector<Rect> rects;

    for (const auto& axe : m_axes)   
    {
        rects.push_back(axe->GetRects());
    }

    return rects;
}

bool AxeManager::Create(
    std::string name,
    float damage,
    float range,
    float attackRange,
    int coolTime,
    int weaponNum,
    Vector2 playerPos)
{
    auto axe = std::make_unique<Axe>(
        name,
        damage,
        range,
        attackRange,
        coolTime,
        weaponNum,
        playerPos
    );
    Spawn(name,
        damage,
        range,
        attackRange,
        coolTime,
        weaponNum,
        playerPos);
 
    return true;
}