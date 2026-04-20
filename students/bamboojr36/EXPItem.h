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
	
	/// <summary>
	/// レクト取得
	/// </summary>
	/// <returns></returns>
	Rect GetRect();
	
	/// <summary>
	/// 当たり判定取得
	/// </summary>
	/// <returns></returns>
	Collision* GetCollision() const { return m_collision.get(); }
	
	/// <summary>
	/// 消す処理
	/// </summary>
	void Destroy();
	
	/// <summary>
	/// プレイヤーに向かっていく
	/// </summary>
	void GoPlayer();
	
	/// <summary>
	/// プレイヤーをセットする
	/// </summary>
	void SetPlayer(PlayerMove* pPlayer) { m_player = pPlayer; }

	/// <summary>
	/// 生成処理
	/// </summary>
	/// <param name="pos"></param>
	void Generate(Vector2 pos);

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

	/// <summary>
	/// 写すか
	/// </summary>
	bool canDraw = true;
	
	/// <summary>
	/// 速度
	/// </summary>
	float m_Speed;
private:
	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector2 m_position;
	
	/// <summary>
	/// 移動方向
	/// </summary>
	Vector2 m_moveDir;
	
	/// <summary>
	/// グラフハンドル
	/// </summary>
	int m_graphHandleEXPItem;
	
	/// <summary>
	/// 当たり判定ユニークポインタ
	/// </summary>
	std::unique_ptr<Collision>m_collision;
	
	/// <summary>
	/// プレイヤー生ポインタ
	/// </summary>
	PlayerMove* m_player;
};

