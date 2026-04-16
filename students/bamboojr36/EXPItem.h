#pragma once
#include "Vector2.h"
#include "Collision.h"
#include <memory>
#include "DxLib.h"

class EXPItem
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EXPItem(): m_position(), m_graphHandleEXPItem(-1), m_collision(nullptr) {};
	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="position"></param>
	EXPItem(Vector2 position);
	
	/// <summary>
	/// デストラクタ
	/// </summary>
	~EXPItem() = default;
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
	/// <summary>
	/// プレイヤーに向かっていく
	/// </summary>
	void GoPlayer();

public:
	bool canDraw = true;
private:
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector2 m_position;
	int m_graphHandleEXPItem;
	std::unique_ptr<Collision>m_collision;
};

