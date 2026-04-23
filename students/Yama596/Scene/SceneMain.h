#pragma once
#include "SceneBase.h"

#include "../students/Yama596/Enemy/EnemyYama.h"
#include "../students/Yama596/Enemy/EnemyManagerYama.h"
#include "../students/bamboojr36/Items.h"

#include "DxLib.h"

class PlayerMove;
class Map;
class Collision;
class EnemyYama;
class Item;
class EXPBar;
class Timer;
class LotteryPassive;
class WeaponStatus;
class PlayerStatus;
class Camera;
class Katana;
class DeathEnemyCounter;

class SceneMain : public SceneBase
{

public:

	/// <summary>
	/// SceneMain画面のコンストラクタ
	/// </summary>
	SceneMain();

	/// <summary>
	/// SceneMainのデストラクタ
	/// </summary>
	virtual ~SceneMain() override = default;

	/// <summary>
	/// 初期設定
	/// 画面の初期設定を行う
	/// </summary>
	void Init() override;

	/// <summary>
	/// 後処理
	/// 画面の後処理を行う
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新処理
	/// SceneMain画面の処理を行う
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw() override;

private:

	/// <summary>
	/// 最初のフレームかどうか
	/// </summary>
	bool m_firstFrame;

	/// <summary>
	/// ボスが死んでるかどうか
	/// </summary>
	bool m_bossDead;

	/// <summary>
	/// プレイヤーが死んでるかどうか
	/// </summary>
	bool m_playerDead;

	/// <summary>
	/// プレイヤーが敵と当たっているかどうか
	/// </summary>
	bool m_playerHit;

	/// <summary>
	/// プレイヤーがダメージを食らった時の無敵時間
	/// </summary>
	float m_playerInvincibleTime;

	/// <summary>
	/// ポーズしているかどうか
	/// </summary>
	bool m_Pause;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// 敵のポインタ
	/// </summary>
	EnemyYama* m_pEnemy;

	/// <summary>
	/// 敵マネージャーのポインタ
	/// </summary>
	EnemyManagerYama* m_pEnemyMgr;

	/// <summary>
	/// マップのポインタ
	/// </summary>
	Map* m_pMap;

	/// <summary>
	/// コリジョンのポインタ
	/// </summary>
	Collision* m_pCollision;

	/// <summary>
	/// アイテムのポインタ
	/// </summary>
	std::unique_ptr<Items>m_Item;

	std::unique_ptr<Timer>m_pTimer;

	std::unique_ptr<DeathEnemyCounter>m_pD_E_Counter;

	LotteryPassive* m_pLotteryPassive;

	WeaponStatus* m_pWeaponManager;

	PlayerStatus* m_pPlayerStatus;

	EXPBar* m_pEXPBar;

	Camera* m_pCamera;

};
