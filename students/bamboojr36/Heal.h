#pragma once
#include "Vector2.h"
#include "Collision.h"
#include <memory>
#include "DxLib.h"

class Heal
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Heal() = default;

	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="position"></param>
	Heal(Vector2 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Heal() = default;

	/// <summary>
	/// 初期化
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

	Rect GetRect();

	Collision* GetCollision() const { return m_collision.get(); }
	void Destroy();
public:
	bool GetIsDown()const { return isDown; }
	bool isDown = true;

private:
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector2 m_position;

	int m_graphHandleHeal;

	std::unique_ptr<Collision>m_collision;

};