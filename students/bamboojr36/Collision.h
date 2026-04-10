#pragma once
#include "Vector2.h"

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
	/// デバッグ
	/// </summary>
	void DebugDraw() const;

private:
	/// <summary>
	/// 大きさ設定
	/// </summary>
	/// <param name="size"></param>
	void SetSize(const Vector2& size) { m_size = size; }
public:
	Vector2 m_position;
	Vector2 m_size;
};

