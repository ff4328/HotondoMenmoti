#pragma once
#include "Vector2.h"
#include "Collision.h"
#include <memory>
#include "DxLib.h"
#include "../oreistake/Player.h"

class EXPItem
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EXPItem():m_Speed(10), m_position(Vector2(1.0f, 1.0f)), m_moveDir(Vector2()), m_graphHandleEXPItem(-1), m_collision(nullptr),m_player(nullptr) {};
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
	/// <summary>
	/// プレイヤーをセットする
	/// </summary>
	void SetPlayer(PlayerMove* pPlayer) { m_player = pPlayer; }

	void Generate(Vector2 pos);

public:
	bool GetIsDown()const { return isDown; }
	bool isDown = true;

	bool canDraw = true;
	float m_Speed;
private:
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector2 m_position;
	Vector2 m_moveDir;
	int m_graphHandleEXPItem;
	std::unique_ptr<Collision>m_collision;
	PlayerMove* m_player;
};

