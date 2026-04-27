#pragma once
#include "Mushroom.h"
#include "EnemyManagerBase.h"

#include <array>

class Mushroom;
class PlayerMove;
class Collision;
class Camera;
class Bat;
class Goblin;
class Skeleton;

class MushroomManager : public EnemyManagerBase
{

	static constexpr int kMaxMushroomNum = 1000;

	static constexpr int kStatusMushroomNum = 20;

public:

	MushroomManager();

	~MushroomManager() = default;

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
	/// マッシュの生成処理を行う
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
	/// マッシュルームを取得する
	/// </summary>
	/// <param name="outEnemies"></param>
	void GetEnemies(std::vector<EnemyBase*>& outEnemies) override;

	/// <summary>
	/// マッシュルームが死んだかどうか
	/// </summary>
	/// <returns></returns>
	bool CheckDead() override;

private:

	/// <summary>
	/// 敵のグラフィックハンドル
	/// </summary>
	int m_graphHandle[kMushroomMotionNum][kStatusMushroomNum];

	/// <summary>
	/// マッシュルーム構造体のテーブル
	/// </summary>
	std::array<Mushroom*, kMaxMushroomNum> m_mushrooms;
	//std::vector<EnemyBase*> m_mushrooms;

	/// <summary>
	/// マッシュルームポインタ
	/// </summary>
	Mushroom* m_pMushroom;

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

