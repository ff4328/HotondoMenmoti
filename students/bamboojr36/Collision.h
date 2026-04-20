#pragma once
#include "Vector2.h"

/// <summary>
/// 左,上,右,下
/// </summary>
struct Rect
{
	int left;
	int top;
	int right;
	int bottom;
};

class Collision
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Collision() = default;

	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="position">position</param>
	/// <param name="size">size</param>
	Collision(const Vector2& position, const Vector2& size) : m_position(position), m_size(size) {}
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Collision() = default;

	/// <summary>
	/// 衝突判定
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool CheckCollision(const Collision& other) const;

	/// <summary>
	/// 座標更新
	/// </summary>
	/// <param name="position"></param>
	void SetPosition(const Vector2& position) { m_position = position; }

	/// <summary>
	/// 座標取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetPosition() const { return m_position; }

	/// <summary>
	/// 当たっているか
	/// </summary>
	/// <param name="posX">X座標</param>
	/// <param name="posY">Y座標</param>
	/// <param name="box">箱の種類</param>
	/// <returns></returns>
	bool CheckPointInRange(float posX, float posY, Rect box);

	/// <summary>
	/// 当たり判定確認
	/// </summary>
	/// <param name="myBox">自分</param>
	/// <param name="checkBox">相手</param>
	/// <returns></returns>
	bool CheckRectCommon(Rect myBox, Rect checkBox);

	/// <summary>
	/// デバッグ
	/// </summary>
	void DebugDraw(Rect myBox, Rect checkBox);

private:
	/// <summary>
	/// 大きさ設定
	/// </summary>
	/// <param name="size"></param>
	void SetSize(const Vector2& size) { m_size = size; }
public:
	/// <summary>
	/// ポジション
	/// </summary>
	Vector2 m_position;
	
	/// <summary>
	/// サイズ
	/// </summary>
	Vector2 m_size;
};