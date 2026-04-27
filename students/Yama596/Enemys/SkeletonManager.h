#pragma once
#include "Skeleton.h"
#include "EnemyManagerBase.h"

#include <array>

class Skeleton;
class PlayerMove;
class Collision;
class Camera;
class Bat;
class Goblin;
class Mushroom;

class SkeletonManager : public EnemyManagerBase
{

	static constexpr int kMaxSkeletonNum = 1000;

	static constexpr int kStatusSkeletonNum = 20;

public:

	SkeletonManager();

	~SkeletonManager() = default;

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
	/// スケルトンの生成処理を行う
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
	/// スケルトンを取得する
	/// </summary>
	/// <param name="outEnemies"></param>
	void GetEnemies(std::vector<EnemyBase*>& outEnemies) override;

	/// <summary>
	/// スケルトンが死んだかどうか
	/// </summary>
	/// <returns></returns>
	bool CheckDead() override;

private:

	/// <summary>
	/// 敵のグラフィックハンドル
	/// </summary>
	int m_graphHandle[kSkeletonMotionNum][kStatusSkeletonNum];

	/// <summary>
	/// スケルトン構造体のテーブル
	/// </summary>
	std::array<Skeleton*, kMaxSkeletonNum> m_skeletons;
	//std::vector<EnemyBase*> m_skeletons;

	/// <summary>
	/// スケルトンのポインタ
	/// </summary>
	Skeleton* m_pSkeleton;

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

	/// <summary>
	/// バットのポインタ
	/// </summary>
	Bat* m_pBat;

	/// <summary>
	/// ゴブリンのポインタ
	/// </summary>
	Goblin* m_pGoblin;

	/// <summary>
	/// マッシュルームのポインタ
	/// </summary>
	Mushroom* m_pMushroom;

};

