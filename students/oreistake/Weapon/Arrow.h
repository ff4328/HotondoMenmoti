#pragma once
#include <string>
#include <memory>
#include "../students/bamboojr36/Collision.h"
#include "../students/bamboojr36/Vector2.h"


class PlayerMove;

/// <summary>
/// 矢の状態
/// </summary>
enum class A_State
{
	Idle,
	Throw,
};

class Arrow
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Arrow();

	/// <summary>
	/// 引数ありコンストラクタ
	/// </summary>
	/// <param name="name">武器名</param>
	/// <param name="damage">与ダメージ</param>
	/// <param name="range">射程</param>
	/// <param name="attackRange">攻撃範囲</param>
	/// <param name="coolTime">クールタイム</param>
	/// <param name="weaponNum">武器番号</param>
	/// <param name="playerPos">プレイヤーの位置</param>
	/// <param name="pPlayerMove">プレイヤー</param>
	Arrow(
		std::string name,
		float damage,
		float range,
		float attackRange,
		int coolTime,
		int weaponNum,
		Vector2 playerPos,
		PlayerMove* pPlayerMove);

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
	/// 刀の動きの基準になるプレイヤーの座標を設定する
	/// </summary>
	/// <param name="playerPos">プレイヤーの座標</param>
	void SetPlayerPos(Vector2 playerPos) { m_startPosX = playerPos.x; m_startPosY = playerPos.y; }

	/// <summary>
	/// レクト取得
	/// </summary>
	/// <returns></returns>
	Rect GetCheckRect();

	/// <summary>
	/// 矢がなくなったかどうか
	/// </summary>
	/// <returns></returns>
	bool IsDead();


private:

	/// <summary>
	/// グラフィックハンドル
	/// </summary>
	int m_graphHandle;

	/// <summary>
	/// 武器名
	/// </summary>
	std::string m_name;

	/// <summary>
	/// 武器の与ダメージ
	/// </summary>
	float m_damage;

	/// <summary>
	/// 武器の射程
	/// </summary>
	float m_range;

	/// <summary>
	/// 武器の攻撃範囲
	/// </summary>
	float m_attackRange;

	/// <summary>
	/// 武器のクールタイム
	/// </summary>
	int m_coolTime;

	/// <summary>
	/// 武器ナンバー
	/// </summary>
	int m_weaponNum;

	/// <summary>
	/// 武器の出現時間
	/// </summary>
	int m_appearTime;

	/// <summary>
	/// 武器自体の角度
	/// </summary>
	float m_angle;

	/// <summary>
	/// 矢の半径
	/// </summary>
	float m_radius;

	/// <summary>
	/// 矢の発射位置
	/// </summary>
	int m_startPosX;
	int m_startPosY;

	/// <summary>
	/// 矢の現在の位置
	/// </summary>
	Vector2 m_currentPos;

	/// <summary>
	/// プレイヤーのポインタ
	/// </summary>
	PlayerMove* m_pPlayerMove;

	/// <summary>
	/// 矢のステータス状態
	/// </summary>
	A_State m_state;

};
