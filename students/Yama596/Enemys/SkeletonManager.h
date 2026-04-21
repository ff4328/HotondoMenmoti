#pragma once
#include "Skeleton.h"

#include <array>

class SkeletonManager
{

	static constexpr int kMaxSkeletonNum = 1000;

public:

	SkeletonManager();

	~SkeletonManager() = default;

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
	/// スケルトン構造体のテーブル
	/// </summary>
	std::array<Skeleton*, kMaxSkeletonNum> m_skeletons;

	/// <summary>
	/// スケルトンのポインタ
	/// </summary>
	Skeleton* m_pMushroom;

};

