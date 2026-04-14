#pragma once
#include "Vector2.h"
#include <vector>
#include <memory>

#include "DxLib.h"
#include "Heal.h"
#include "Magnet.h"
#include "Bomb.h"
#include "EXPItem.h"

class Collision;

class Items
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Items();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Items() = default;

	/// <summary>
	/// 初期設定
	/// </summary>
	void Init();

	/// <summary>
	/// 終了処理
	/// </summary>
	void End();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 定位置生成
	/// </summary>
	/// <param name="position">position</param>
	/// <returns></returns>
	bool Create(const Vector2& position);

	/// <summary>
	/// ランダム生成
	/// </summary>
	/// <param name="Length">ステージのサイズ</param>
	/// <returns></returns>
	bool RamdumCreate(float Length);

	/// <summary>
	/// 生成物削除
	/// </summary>
	/// <param name="index"></param>
	void Remove(int index);

	/// <summary>
	/// デバッグ
	/// </summary>
	void DebugDraw();

private:

	/// <summary>
	/// 画像ハンドル
	/// </summary>

	int m_graphHandleHeal;
	int m_graphHandleMagnet;
	int m_graphHandleBomb;
	int m_graphHandleEXPItem;

	std::unique_ptr<Heal> m_heal;
	std::unique_ptr<Magnet>m_magnet;
	std::unique_ptr<Bomb>m_bomb;
	std::unique_ptr<EXPItem>m_EXPItem;
	std::unique_ptr<Collision>m_collision;


};

