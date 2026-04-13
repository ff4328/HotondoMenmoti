#pragma once
#include "Vector2.h"
#include "Collision.h"

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
	void Draw(int graphHandle);

	/// <summary>
	/// 草の当たり判定の中心座標を取得
	/// </summary>
	/// <returns></returns>
	Vector2 GetCollisionCenterPos() const;

	const Collision* GetCollision() const { return m_collision; }

private:

	/// <summary>
	/// 草の画像ハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 表示拡大率
	/// </summary>
	float m_scale;

	/// <summary>
	/// 描画する座標
	/// </summary>
	Vector2 m_position;

	Collision* m_collision;

};