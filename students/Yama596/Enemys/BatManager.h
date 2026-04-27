#pragma once
#include "Bat.h"
#include "EnemyManagerBase.h"

#include <array>

class Bat;
class PlayerMove;
class Collision;
class Camera;
class Goblin;
class Mushroom;
class Skeleton;

class BatManager : public EnemyManagerBase
{

	static constexpr int kMaxBatNum = 1000;

	static constexpr int kStatusBatNum = 20;

public:

	BatManager();

	~BatManager() = default;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init() override;

	/// <summary>
	/// 後処理を行う
	/// </summary>
	void End() override;

	/// <summary>
	/// 更新処理を行う
	/// </summary>
	EnemyManagerBase* Update() override;

	/// <summary>
	/// 表示処理を行う
	/// </summary>
	void Draw() override;

	/// <summary>
	/// バットの生成処理を行う
	/// </summary>
	/// <param name="pos"></param>
	void Spawn(const Vector2& pos);

	/// <summary>
	/// ランダムな位置に生成する
	/// </summary>
	/// <returns></returns>
	Vector2 GetRandomSpawnPos();

	/// <summary>
	/// ダメージ処理を行う
	/// </summary>
	/// <param name="damage"></param>
	void CheckHitAttack(int damage);

	/// <summary>
	/// ダメージ処理を行う
	/// </summary>
	/// <param name="damage"></param>
	bool CheckHitPlayer(const Rect& playerRect);

	bool CheckHitWeapon(const Rect& playerRect, int damage);

	/// <summary>
	///	プレイヤーを渡す処理を行う
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(PlayerMove* player) override;

	/// <summary>
	/// カメラを渡す処理を行う
	/// </summary>
	/// <param name="camera"></param>
	void SetCamera(Camera* camera) override { m_pCamera = camera; }

	/// <summary>
	/// 生成する敵を決める
	/// </summary>
	/// <returns></returns>
	EnemyBase* CreateEnemy() override;

	/// <summary>
	/// バットを取得する
	/// </summary>
	/// <param name="outEnemies"></param>
	void GetEnemies(std::vector<EnemyBase*>& outEnemies) override;

	/// <summary>
	/// バットが死んだかどうか
	/// </summary>
	/// <returns></returns>
	bool CheckDead() override;

private:

	/// <summary>
	/// 敵のグラフィックハンドル
	/// </summary>
	int m_graphHandle[kBatMotionNum][kStatusBatNum];

	/// <summary>
	/// ステータスの変数
	/// </summary>
	Status m_status;

	/// <summary>
	/// バット構造体のテーブル
	/// </summary>
	 std::array<Bat*, kMaxBatNum> m_bats;
	// std::vector<EnemyBase*> m_bats;

	/// <summary>
	/// バットのポインタ
	/// </summary>
	Bat* m_pBat;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// コリジョンのポインタ
	/// </summary>
	Collision* m_pCollision;

	/// <summary>
	/// カメラのポインタ
	/// </summary>
	Camera* m_pCamera;

};

