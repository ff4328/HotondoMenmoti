#pragma once
#include "Goblin.h"

#include <array>

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

};

