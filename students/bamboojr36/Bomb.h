#pragma once
#include "Vector2.h"
#include "Collision.h"
#include <memory>
#include "DxLib.h"

class Bomb
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Bomb() : m_position(), m_graphHandleBomb(-1), m_collision(nullptr) {}

	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="position"></param>
	Bomb(Vector2 position);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Bomb() = default;

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

	/// <summary>
	/// レクト取得
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

	/// <summary>
	/// 当たり判定取得
	/// </summary>
	/// <returns></returns>
	Collision* GetCollision() const { return m_collision.get(); }
	
	/// <summary>
	/// 消す処理
	/// </summary>
	void Destroy();
public:
	/// <summary>
	/// 取得したか確認
	/// </summary>
	/// <returns></returns>
	bool GetIsDown()const { return isDown; }
	
	/// <summary>
	/// 取得したか
	/// </summary>
	bool isDown = true;

private:
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector2 m_position;

	/// <summary>
	/// グラフハンドル
	/// </summary>
	int m_graphHandleBomb;

	/// <summary>
	/// 当たり判定ユニークポインタ
	/// </summary>
	std::unique_ptr<Collision>m_collision;

};