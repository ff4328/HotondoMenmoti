#pragma once

#include<vector>
#include "Arrow.h"

class Arrow;
class Vector2;
class PlayerMove;

class ArrowManager
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	ArrowManager();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="pPlayermove">プレイヤー</param>
	ArrowManager(PlayerMove* pPlayermove);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~ArrowManager() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 終了
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	
	/// <summary>
	/// 表示
	/// </summary>
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


	/// <summary>
	/// 矢の当たり判定の矩形
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

	/// <summary>
	/// 矩形のゲッター
	/// </summary>
	/// <returns></returns>
	std::vector<Rect> GetCheckRects();

private:

	/// <summary>
	/// 矢の配列
	/// 可変長配列の宣言
	/// std::vector<どの型の配列> 可変長配列名;
	/// </summary>
	// std::array<Grass*, kMaxGrassNum> m_arrow;
	std::vector<std::unique_ptr<Arrow>> m_arrow;

	/// <summary>
	/// 画像のハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayermove;
};

