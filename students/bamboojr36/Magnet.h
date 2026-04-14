#pragma once
#include "Vector2.h"
#include "Collision.h"
#include <memory>
#include "DxLib.h"

class Magnet {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Magnet(): m_position(), m_graphHandleMagnet(-1), m_collision(nullptr) {}

	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="position"></param>
	Magnet(Vector2 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Magnet() = default;

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

	Rect GetCheckRrect();

	Collision* GetCollision() const { return m_collision.get(); }


private:
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector2 m_position;

	int m_graphHandleMagnet;

	std::unique_ptr<Collision>m_collision;

};

