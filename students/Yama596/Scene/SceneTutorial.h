#pragma once
#include "SceneBase.h"

class PlayerMove;
class BatManager;
class PlayerStatus;
class Map;
class Collision;
class Camera;

class SceneTutorial : public SceneBase
{

public:

	/// <summary>
	/// SceneTutorial画面のコンストラクタ
	/// </summary>
	SceneTutorial();

	/// <summary>
	/// SceneTutorial画面のデストラクタ
	/// </summary>
	virtual ~SceneTutorial() override = default;

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
	/// SceneTutorial画面の処理を行う
	/// </summary>
	/// <returns></returns>
	SceneBase* Update() override;

	/// <summary>
	/// 描画処理
	/// SceneTutorial画面の描画を行う
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
	/// 生成タイマー
	/// </summary>
	float m_spawnTimer;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// バットマネージャーのポインタ
	/// </summary>
	BatManager* m_pBatMgr;

	/// <summary>
	/// プレイヤーステータスのポインタ
	/// </summary>
	PlayerStatus* m_pPlayerStatus;

	/// <summary>
	/// マップのポインタ
	/// </summary>
	Map* m_pMap;

	/// <summary>
	/// コリジョンのポインタ
	/// </summary>
	Collision* m_pCollision;

	/// <summary>
	/// カメラのポインタ
	/// </summary>
	Camera* m_pCamera;

};
