#pragma once
#include "Mushroom.h"

#include <array>

class MushroomManager
{

	static constexpr int kMaxMushroomNum = 1000;

public:

	MushroomManager();

	~MushroomManager() = default;

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
	/// マッシュルーム構造体のテーブル
	/// </summary>
	std::array<Mushroom*, kMaxMushroomNum> m_mushrooms;

	/// <summary>
	/// マッシュルームポインタ
	/// </summary>
	Mushroom* m_pMushroom;

};

