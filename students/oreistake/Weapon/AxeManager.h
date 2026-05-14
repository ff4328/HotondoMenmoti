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
    /// <summary>
    /// コンストラクタ
    /// </summary>
    AxeManager();

    /// <summary>
    /// 引数ありコンストラクタ
    /// </summary>
    /// <param name="pPlayermove"></param>
    AxeManager(PlayerMove* pPlayermove);
    
    /// <summary>
    /// デストラクタ
    /// </summary>
    ~AxeManager() = default;

    /// <summary>
    /// 初期設定
    /// </summary>
    /// <param name="name">名前</param>
    /// <param name="damage">ダメージ</param>
    /// <param name="range">範囲</param>
    /// <param name="attackRange">攻撃範囲</param>
    /// <param name="coolTime">クールタイム</param>
    /// <param name="weaponNum">武器番号</param>
    /// <param name="playerPos">プレイヤーの位置</param>
    void Init(std::string name,
        float damage,
        float range,
        float attackRange,
        int coolTime,
        int weaponNum,
        Vector2 playerPos);
    
    /// <summary>
    /// 更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// 描画処理
    /// </summary>
    void Draw();

    /// <summary>
    /// 斧を生成する
    /// </summary>
    /// <param name="name">名前</param>
    /// <param name="damage">ダメージ</param>
    /// <param name="range">範囲</param>
    /// <param name="attackRange">攻撃範囲</param>
    /// <param name="coolTime">クールタイム</param>
    /// <param name="weaponNum">武器番号</param>
    /// <param name="playerPos">プレイヤーの位置</param>
    void Spawn(std::string name,
        float damage,
        float range,
        float attackRange,
        int coolTime,
        int weaponNum,
        Vector2 playerPos);

    /// <summary>
    /// 全ての斧の当たり判定を返す
    /// </summary>
    /// <returns>斧の当たり判定のベクター</returns>
    std::vector<Rect> GetCheckRects() const;

    /// <summary>
    /// カメラセッター
    /// </summary>
    /// <param name="pCamera"></param>
    void SetCamera(Camera* pCamera) { m_pCamera = pCamera; }

    /// <summary>
	/// 生成処理
    /// </summary>
    /// <param name="name">名前</param>
    /// <param name="damage">ダメージ</param>
    /// <param name="range">範囲</param>
    /// <param name="attackRange">攻撃範囲</param>
    /// <param name="coolTime">クールタイム</param>
    /// <param name="weaponNum">武器番号</param>
    /// <param name="playerPos">プレイヤーの位置</param>
    /// <returns>生成に成功したかどうか</returns>
    bool Create(std::string name,
        float damage,
        float range,
        float attackRange,
        int coolTime,
        int weaponNum,
        Vector2 playerPos);

private:
    /// <summary>
	/// ユニークポインタのベクターで斧を管理
    /// </summary>
    std::vector<std::unique_ptr<Axe>> m_axes;
    
    /// <summary>
    /// プレイヤー生ポインタ
    /// </summary>
    PlayerMove* m_pPlayer;
    
    /// <summary>
	/// カメラ生ポインタ
    /// </summary>
    Camera* m_pCamera = nullptr;

};