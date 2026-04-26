#pragma once

#include<vector>
#include "Arrow.h"

class Arrow;
class Vector2;
class PlayerMove;

class ArrowManager
{
public:
	ArrowManager();
	ArrowManager(PlayerMove* pPlayermove);
	~ArrowManager() = default;


	void Init();
	void End();
	void Update();
	void Draw();


	/// <summary>
	/// 指定した座標にGrassクラスのインスタンスを生成
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	bool Create(std::string name,
		float damage,
		float range,
		float attackRange,
		int coolTime,
		int weaponNum,
		Vector2 playerPos);

	Rect GetCheckRect();

	/// <summary>
	/// 指定したインデックスの草を削除
	/// </summary>
	/// <param name="index"></param>
	//void Remove(int index);

	/// <summary>
	/// 草の数を取得
	/// </summary>
	/// <returns></returns>
	//int GetArrowCount() const { return m_arrow.size(); }

	/// <summary>
	/// 引数の敵と草が当たっているか調べる
	/// </summary>
	/// <param name="other"></param>
	//void CheckHitSphere();

private:

	/// <summary>
	/// デバッグ情報を表示する
	/// </summary>
	//void DebugDraw();

private:

	/// <summary>
	/// 草の配列
	/// 可変長配列の宣言
	/// std::vector<どの型の配列> 可変長配列名;
	/// </summary>
	// std::array<Grass*, kMaxGrassNum> m_grasses;
	// std::vector<Grass*> m_grasses;
	std::vector<std::unique_ptr<Arrow>> m_arrow;

	/// <summary>
	/// 草の数
	/// </summary>
	/// 可変長配列の場合なくても制御できる
	// int m_grassCount;

	/// <summary>
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle;


	PlayerMove* m_pPlayermove;
};

