#pragma once
#include "Goblin.h"

#include <array>

class Goblin;
class PlayerMove;
class Collision;

class GoblinManager
{

	static constexpr int kMaxGoblinNum = 1000;

public:

	GoblinManager();

	~GoblinManager() = default;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init();

	/// <summary>
	/// 後処理を行う
	/// </summary>
	void End();

	/// <summary>
	/// 更新処理を行う
	/// </summary>
	void Update();

	/// <summary>
	/// 表示処理を行う
	/// </summary>
	void Draw();

	/// <summary>
	/// ゴブリンの生成処理を行う
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

	/// <summary>
	///	プレイヤーを渡す処理を行う
	/// </summary>
	/// <param name="player"></param>
	void SetPlayer(PlayerMove* player);

private:

	/// <summary>
	/// 敵のグラフィックハンドル
	/// </summary>
	int m_graphHandle[kMotionNum];

	/// <summary>
	/// ゴブリン構造体のテーブル
	/// </summary>
	std::array<Goblin*, kMaxGoblinNum> m_goblins;

	/// <summary>
	/// ゴブリンのポインタ
	/// </summary>
	Goblin* m_pGoblin;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayer;

	/// <summary>
	/// コリジョンのポインタ
	/// </summary>
	Collision* m_pCollision;

};

