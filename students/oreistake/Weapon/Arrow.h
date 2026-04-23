#pragma once
#include <string>
#include <memory>
#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"


class PlayerMove;

class Arrow
{
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Arrow();

	/// <summary>
	/// 引数ありのコンストラクタ
	/// </summary>
	/// <param name="name">武器名</param>
	/// <param name="damage">武器の与ダメージ</param>
	/// <param name="range">武器の射程</param>
	/// <param name="attackRange">武器の攻撃範囲</param>
	/// <param name="coolTime">武器のクールタイム</param>
	/// <param name="weaponNum">武器ナンバー</param>
	/// <param name="playerPos">プレイヤーの座標</param>
	Arrow(
		std::string name,
		float damage,
		float range,
		float attackRange,
		int coolTime,
		int weaponNum,
		Vector2 playerPos);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Arrow() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	void Init();

	/// <summary>
	/// 終了
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

private:

	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 武器の射程
	/// </summary>
	float m_range;

	/// <summary>
	/// 武器のクールタイム
	/// </summary>
	int m_coolTime;

	/// <summary>
	/// 武器の出現時間
	/// </summary>
	int m_appearTime;

	/// <summary>
	/// 武器自体の角度
	/// </summary>
	float m_angle;

	Vector2 m_currentPos;

	PlayerMove* m_pPlayerMove;

};
