#pragma once
#include <vector>
#include <memory>
#include <algorithm>

#include "../students/bamboojr36/Vector2.h"
#include "../students/bamboojr36/Collision.h"
#include "Axe.h"
#include "../students/oreistake/Player.h"

class Camera;

class AxeManager
{
public:
    AxeManager();
    AxeManager(PlayerMove* pPlayermove);
    ~AxeManager() = default;

    void Init(std::string name,
        float damage,
        float range,
        float attackRange,
        int coolTime,
        int weaponNum,
        Vector2 playerPos);
    void Update();
    void Draw();

    void Spawn(std::string name,
        float damage,
        float range,
        float attackRange,
        int coolTime,
        int weaponNum,
        Vector2 playerPos);

    // 全ての斧の当たり判定を返す
    std::vector<Rect> GetCheckRects() const;

    // Camera をセット
    void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

    bool Create(std::string name,
        float damage,
        float range,
        float attackRange,
        int coolTime,
        int weaponNum,
        Vector2 playerPos);

private:
    std::vector<std::unique_ptr<Axe>> m_axes;
    PlayerMove* m_pPlayer;
    Camera* m_pCamera = nullptr;

};